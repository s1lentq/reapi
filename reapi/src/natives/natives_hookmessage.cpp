#include "precompiled.h"

enum MessageHook
{
	INVALID_MESSAGEHOOK = 0
};

/**
* Registers a callback function to be called when a game message with the specified ID is received.
*
* @param msg_id     The ID of the message to register the callback for.
* @param callback   The name of the callback function.
* @param post       Whether the callback should be invoked before or after processing the message. (optional)
*
* @note             You can modify the message content using SetMessageParam native before the original function is invoked.
*                   Also can reading the message content using GetMessageParam native.
*
*                   In the callback function, use the return values from Hookchain return types, such as HC_CONTINUE, HC_SUPERCEDE, etc.
*                   to control the flow of message processing.
*
* @return           Returns a handle to the registered message hook.
*
* native MessageHook:RegisterMessage(const msg_id, const callback[], post = 0);
*/
cell AMX_NATIVE_CALL RegisterMessage(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_id, arg_handler, arg_post };

	CHECK_REQUIREMENTS(ReHLDS);

	int msg_id = params[arg_id];

	// svc_bad (0) is not allowed for hook
	if (msg_id <= 0 || msg_id >= MAX_USERMESSAGES)
		return INVALID_MESSAGEHOOK;

	char namebuf[256];
	const char *funcname = getAmxString(amx, params[arg_handler], namebuf);

	int funcid;
	if (unlikely(g_amxxapi.amx_FindPublic(amx, funcname, &funcid) != AMX_ERR_NONE))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: public function \"%s\" not found.", __FUNCTION__, funcname);
		return INVALID_MESSAGEHOOK;
	}

	int post = params[arg_post];
	return g_messageHookManager.addHook(amx, msg_id, funcname, post != 0);
}

/**
* Unregisters a game message hook identified by the specified handle.
*
* @param handle     The handle of the message hook to unregister.
*
* @return           Returns true if the message hook is successfully unregistered, otherwise false.
*
* native bool:UnregisterMessage(const MessageHook:handle);
*/
cell AMX_NATIVE_CALL UnregisterMessage(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_handle };

	CHECK_REQUIREMENTS(ReHLDS);

	if (!g_messageHookManager.removeHook(amx, params[arg_handle]))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: Failed to remove message hook with handle %d.", __FUNCTION__, params[arg_handle]);
		return FALSE;
	}

	return TRUE;
}

/**
* Enables a game message hook identified by the specified handle.
*
* @param handle     The handle of the message hook to enable.
*
* @return           Returns true if the message hook is successfully enabled, otherwise false.
*
* native bool:EnableHookMessage(const MessageHook:handle);
*/
cell AMX_NATIVE_CALL EnableHookMessage(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_handle };

	CHECK_REQUIREMENTS(ReHLDS);

	cell handle = params[arg_handle];
	auto hook = g_messageHookManager.getAmxxHook(handle);
	if (!hook)
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: Message hook with handle %d not found.", __FUNCTION__, handle);
		return FALSE;
	}

	hook->SetState(FSTATE_ENABLED);
	return TRUE;
}

/**
* Disables a game message hook identified by the specified handle.
*
* @param handle     The handle of the message hook to disable.
*
* @return           Returns true if the message hook is successfully disabled, otherwise false.
*
* native bool:DisableHookMessage(const MessageHook:handle);
*/
cell AMX_NATIVE_CALL DisableHookMessage(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_handle };

	CHECK_REQUIREMENTS(ReHLDS);

	cell handle = params[arg_handle];
	auto hook = g_messageHookManager.getAmxxHook(handle);
	if (!hook)
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: Message hook with handle %d not found.", __FUNCTION__, handle);
		return FALSE;
	}

	hook->SetState(FSTATE_STOPPED);
	return TRUE;
}

/**
* Sets the parameter value for the specified index in the current game message.
*
* @param index      The index of the parameter to set.
* @param value      The value to set for the parameter.
*
* @return           Returns true if the parameter value is successfully set, otherwise false.
*
* native bool:SetMessageParam(const number, any:...);
*/
cell AMX_NATIVE_CALL SetMessageParam(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_number, arg_value };

	CHECK_REQUIREMENTS(ReHLDS);

	if (!g_activeMessageContext)
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: trying to set argument without active hook.", __FUNCTION__);
		return FALSE;
	}

	size_t number = params[arg_number] - 1;

	cell *value = getAmxAddr(amx, params[arg_value]);

	switch (g_activeMessageContext->getParamType(number))
	{
	case IMessage::ParamType::String:
		char stringbuf[256];
		g_activeMessageContext->setParamString(number, getAmxString(amx, params[arg_value], stringbuf));
		break;
	case IMessage::ParamType::Angle:
	case IMessage::ParamType::Coord:
		g_activeMessageContext->setParamFloat(number, *(float *)value);
		break;
	default:
		g_activeMessageContext->setParamInt(number, *value);
		break;
	}

	return TRUE;
}

/**
* Retrieves the parameter value for the specified index in the current game message.
*
* @param index      The index of the parameter to retrieve.
* @param ...        Additional parameters depending on the type of the parameter being retrieved.
*
* @return           Returns the retrieved parameter value.
*
* native any:GetMessageParam(const number, any:...);
*/
cell AMX_NATIVE_CALL GetMessageParam(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_number, arg_value, arg_maxlen };

	CHECK_REQUIREMENTS(ReHLDS);

	if (!g_activeMessageContext)
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: trying to get argument without active hook.", __FUNCTION__);
		return FALSE;
	}

	size_t number = params[arg_number] - 1;

	cell *dstAddr = getAmxAddr(amx, params[arg_value]);

	switch (g_activeMessageContext->getParamType(number))
	{
	case IMessage::ParamType::String:
	{
		if (PARAMS_COUNT != 3)
			return FALSE;

		const char *argString = g_activeMessageContext->getParamString(number);
		setAmxString(dstAddr, argString ? argString : "", params[arg_maxlen]);
		return TRUE;
	}
	case IMessage::ParamType::Angle:
	case IMessage::ParamType::Coord:
	{
		float flValue = g_activeMessageContext->getParamFloat(number);
		if (PARAMS_COUNT > 1)
			*dstAddr = flValue;
		return flValue;
	}
	case IMessage::ParamType::Entity:
	case IMessage::ParamType::Byte:
	case IMessage::ParamType::Char:
	case IMessage::ParamType::Short:
	case IMessage::ParamType::Long:
		return g_activeMessageContext->getParamInt(number);
	default:
		break;
	}

	return FALSE;
}

/**
* Retrieves the type of the parameter at the specified index in the current game message.
*
* @param index      The index of the parameter to retrieve the type for.
*
* @return           Returns the type of the parameter, look at the enum MsgParamType
*
* native MsgParamType:GetMessageParamType(const number);
*/
cell AMX_NATIVE_CALL GetMessageParamType(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_number };

	CHECK_REQUIREMENTS(ReHLDS);

	if (!g_activeMessageContext)
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: trying to get argument without active hook.", __FUNCTION__);
		return FALSE;
	}

	size_t number = params[arg_number] - 1;

	size_t paramCount = g_activeMessageContext->getParamCount();
	if (number < 0 || number >= paramCount)
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: invalid message argument %d.", __FUNCTION__, number);
		return FALSE;
	}

	return static_cast<cell>(g_activeMessageContext->getParamType(number));
}

/**
* Retrieves the number of parameters in the current game message.
*
* @return           Returns the number of parameters in the current game message.
*
* native GetMessageParamCount();
*/
cell AMX_NATIVE_CALL GetMessageParamCount(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_number };

	CHECK_REQUIREMENTS(ReHLDS);

	if (!g_activeMessageContext)
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: trying to get argument without active hook.", __FUNCTION__);
		return FALSE;
	}

	return g_activeMessageContext->getParamCount();
}

/**
* Retrieves the origin of the current game message.
*
* @param origin     An array to store the origin coordinates of the game message.
*
* @return           Returns true if the origin is successfully retrieved, otherwise false.
*
* native bool:GetMessageOrigin(Float:origin[3]);
*/
cell AMX_NATIVE_CALL GetMessageOrigin(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_number, arg_origin };

	CHECK_REQUIREMENTS(ReHLDS);

	if (!g_activeMessageContext)
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: trying to get argument without active hook.", __FUNCTION__);
		return FALSE;
	}

	const float *messageOrigin = g_activeMessageContext->getOrigin();
	if (!messageOrigin)
		return FALSE;

	Vector &outVec = *(Vector *)getAmxAddr(amx, params[arg_origin]);
	outVec = messageOrigin;
	return TRUE;
}

/**
* Retrieves the destination of the current message.
*
* @return           Returns the destination of the current message.
*
* native GetMessageDest();
*/
cell AMX_NATIVE_CALL GetMessageDest(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_number, arg_origin };

	CHECK_REQUIREMENTS(ReHLDS);

	if (!g_activeMessageContext)
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: trying to get argument without active hook.", __FUNCTION__);
		return -1;
	}

	return static_cast<cell>(g_activeMessageContext->getDest());
}

/**
* Sets the block type for the specified message ID.
*
* @param msgid      The ID of the message to set the block type for.
* @param type       The type of block to set for the message, look at the enum MsgBlockType
*
* @return           Returns true if the block type is successfully set, otherwise false.
*
* native bool:SetMessageBlock(const msgid, MsgBlockType:type);
*/
cell AMX_NATIVE_CALL SetMessageBlock(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_id, arg_type };

	CHECK_REQUIREMENTS(ReHLDS);

	int msg_id = params[arg_id];

	// svc_bad (0) is not allowed for hook
	if (msg_id <= 0 || msg_id >= MAX_USERMESSAGES)
		return FALSE;

	g_RehldsMessageManager->setMessageBlock(msg_id, static_cast<IMessage::BlockType>(params[arg_type]));
	return TRUE;
}

/**
* Retrieves the block type for the specified message ID.
*
* @param msgid      The ID of the message to retrieve the block type for.
*
* @return           Returns the block type of the specified message, look at the enum MsgBlockType
*
* native MsgBlockType:GetMessageBlock(const msgid);
*/
cell AMX_NATIVE_CALL GetMessageBlock(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_id };

	CHECK_REQUIREMENTS(ReHLDS);

	int msg_id = params[arg_id];

	// svc_bad (0) is not allowed for hook
	if (msg_id <= 0 || msg_id >= MAX_USERMESSAGES)
		return FALSE;

	return static_cast<cell>(g_RehldsMessageManager->getMessageBlock(params[arg_id]));
}

AMX_NATIVE_INFO HookMessage_Natives[] =
{
	{ "RegisterMessage",      RegisterMessage      },
	{ "UnregisterMessage",    UnregisterMessage    },

	{ "EnableHookMessage",    EnableHookMessage    },
	{ "DisableHookMessage",   DisableHookMessage   },

	{ "GetMessageParam",      GetMessageParam      },
	{ "GetMessageParamType",  GetMessageParamType  },
	{ "GetMessageParamCount", GetMessageParamCount },

	{ "GetMessageOrigin",     GetMessageOrigin     },
	{ "GetMessageDest",       GetMessageDest       },

	{ "SetMessageParam",      SetMessageParam      },

	{ "SetMessageBlock",      SetMessageBlock      },
	{ "GetMessageBlock",      GetMessageBlock      },

	{ nullptr, nullptr }
};

void RegisterNatives_HookMessage()
{
	g_amxxapi.AddNatives(HookMessage_Natives);
}
