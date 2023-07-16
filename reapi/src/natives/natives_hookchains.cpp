#include "precompiled.h"

/*
* Hook API function that are available into enum.
* Look at the enums for parameter lists.
*
* @param function   The function to hook
* @param callback   The forward to call
* @param post       Whether or not to forward this in post
*
* @return           Returns a hook handle. Use EnableHookChain/DisableHookChain to toggle the forward on or off
*
* native HookChain:RegisterHookChain(any:function_id, const callback[], post = 0);
*/
cell AMX_NATIVE_CALL RegisterHookChain(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_func, arg_handler, arg_post };

	int func = params[arg_func];
	int post = params[arg_post];
	auto hook = g_hookManager.getHook(func);

	if (unlikely(hook == nullptr))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: function with id (%d) doesn't exist in current API version.", __FUNCTION__, func);
		return INVALID_HOOKCHAIN;
	}

	if (unlikely(!hook->checkRequirements()))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: function (%s) is not available, %s required.", __FUNCTION__, hook->func_name, hook->depend_name);
		return INVALID_HOOKCHAIN;
	}

	char namebuf[256];
	const char *funcname = getAmxString(amx, params[arg_handler], namebuf);

	int funcid;
	if (unlikely(g_amxxapi.amx_FindPublic(amx, funcname, &funcid) != AMX_ERR_NONE))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: public function \"%s\" not found.", __FUNCTION__, funcname);
		return INVALID_HOOKCHAIN;
	}

	int fwid = hook->registerForward(amx, funcname);
	if (unlikely(fwid == -1))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: register forward failed.", __FUNCTION__);
		return INVALID_HOOKCHAIN;
	}

	return g_hookManager.addHandler(amx, func, funcname, fwid, post != 0);
}

/*
* Starts a hook back up.
* Use the return value from RegisterHookChain as the parameter here!
*
* @param hook       The hook to re-enable
*
* @return           Returns true if the function is successfully executed, otherwise false
*
* native bool:EnableHookChain(HookChain:hook);
*/
cell AMX_NATIVE_CALL EnableHookChain(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_handle_hook };

	auto hook = g_hookManager.getAmxxHook(params[arg_handle_hook]);

	if (unlikely(hook == nullptr))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: invalid HookChain handle.", __FUNCTION__);
		return FALSE;
	}

	hook->SetState(FSTATE_ENABLED);
	return TRUE;
}

/*
* Stops a hook from triggering.
* Use the return value from RegisterHookChain as the parameter here!
*
* @param hook       The hook to stop
*
* native bool:DisableHookChain(HookChain:hook);
*/
cell AMX_NATIVE_CALL DisableHookChain(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_handle_hook };

	auto hook = g_hookManager.getAmxxHook(params[arg_handle_hook]);

	if (unlikely(hook == nullptr))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: invalid HookChain handle.", __FUNCTION__);
		return FALSE;
	}

	hook->SetState(FSTATE_STOPPED);
	return TRUE;
}

static CTempAnyData<Vector, 16> s_tmpVectors;
static CTempAnyData<char, 16, 1024> s_tmpStrings;

/*
* Sets the return value of a hookchain.
*
* @param type       To specify the ATYPE_* parameter, look at the enum AType
* @param value      The value to set the return to
*
* native SetHookChainReturn(AType:type, any:...);
*/
cell AMX_NATIVE_CALL SetHookChainReturn(AMX *amx, cell *params)
{
	if (unlikely(!g_hookCtx))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: trying to set return value without active hook.", __FUNCTION__);
		return FALSE;
	}

	enum args_e { arg_count, arg_type, arg_value };
	auto& retVal = g_hookCtx->retVal;

	if (unlikely(params[arg_type] != retVal.type))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE,
			"%s: trying to set return value with incompatible type, expected '%s'; got '%s'",
			__FUNCTION__,
			getATypeStr(retVal.type),
			getATypeStr(static_cast<AType>(params[arg_type]))
		);

		return FALSE;
	}

	char string[2048];
	cell* srcAddr = getAmxAddr(amx, params[arg_value]);

	switch (retVal.type)
	{
	case ATYPE_INTEGER:
	case ATYPE_FLOAT:
		retVal._integer = *srcAddr;
		break;
	case ATYPE_BOOL:
		retVal._integer = (*srcAddr != 0) ? TRUE : FALSE;
		break;

	case ATYPE_STRING:
	{
		size_t len;
		const char *dest = getAmxString(srcAddr, string, &len);
		retVal._string = strcpy(s_tmpStrings.Alloc(), dest);
		break;
	}
	case ATYPE_CLASSPTR:
		retVal._classptr = getPrivate<CBaseEntity>(*srcAddr);
		break;
	case ATYPE_EDICT:
		retVal._edict = edictByIndexAmx(*srcAddr);
		break;
	case ATYPE_EVARS:
		retVal._pev = PEV(*srcAddr);
		break;
	case ATYPE_VECTOR:
		retVal._vector  = s_tmpVectors.Alloc();
		*retVal._vector = *(Vector *)srcAddr;
		break;
	default:
		return FALSE;
	}

	retVal.set = true;
	return TRUE;
}

/*
* Gets the return value of the current hookchain.
* This has no effect in pre hookchain.
*
* @param type       To specify the ATYPE_* parameter, look at the enum AType
* @param [maxlen]   Max length of string (optional)
*
* @return           If an integer or boolean or one byte or float, array or everything else is passed via 1st argument and more
*
* native any:GetHookChainReturn(AType:type, any:...);
*/
cell AMX_NATIVE_CALL GetHookChainReturn(AMX *amx, cell *params)
{
	if (unlikely(!g_hookCtx))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: trying to get return value without active hook.", __FUNCTION__);
		return FALSE;
	}

	enum args_e { arg_count, arg_type, arg_value, arg_maxlen };
	auto& retVal = g_hookCtx->retVal;

	if (unlikely(params[arg_type] != retVal.type))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE,
			"%s: trying to get return value with incompatible type, expected '%s'; got '%s'",
			__FUNCTION__,
			getATypeStr(retVal.type),
			getATypeStr(static_cast<AType>(params[arg_type]))
		);

		return FALSE;
	}

	if (unlikely(!retVal.set))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: return value isn't set.", __FUNCTION__);
		return FALSE;
	}

	cell* dstAddr = getAmxAddr(amx, params[arg_value]);

	switch (retVal.type)
	{
	case ATYPE_INTEGER:
	case ATYPE_FLOAT:
		return retVal._integer;
	case ATYPE_BOOL:
		return retVal._integer != 0 ? TRUE : FALSE;
	case ATYPE_STRING:
	{
		if (PARAMS_COUNT != 3)
			return FALSE;

		setAmxString(dstAddr, retVal._string, params[arg_maxlen]);
		break;
	}
	case ATYPE_CLASSPTR:
		return indexOfEdict(retVal._classptr->pev);
	case ATYPE_EDICT:
		return indexOfEdict(retVal._edict);
	case ATYPE_EVARS:
		return indexOfEdict(retVal._pev);
	case ATYPE_VECTOR:
	{
		if (PARAMS_COUNT != 2)
			return FALSE;

		Vector &pDest = *(Vector *)dstAddr;
		pDest = *retVal._vector;
		return TRUE;
	}
	default:
		return FALSE;
	}

	return TRUE;
}

/*
* Set hookchain argument.
* This has no effect in post hookchain.
*
* @param number     Number of argument
* @param value      New value
* @param [maxlen]   Max length of string (optional)
*
* @return           Returns true if the function is successfully executed, otherwise false
*
* native SetHookChainArg(number, AType:type, any:...);
*/
cell AMX_NATIVE_CALL SetHookChainArg(AMX *amx, cell *params)
{
	if (unlikely(!g_hookCtx))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: trying to set argument without active hook.", __FUNCTION__);
		return FALSE;
	}

	enum args_e { arg_count, arg_number, arg_type, arg_value };
	size_t number = params[arg_number] - 1;

	if (unlikely(number >= g_hookCtx->args_count))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: can't set argument %i of hookchain with %i args.", __FUNCTION__, params[arg_number], g_hookCtx->args_count);
		return FALSE;
	}

	AType type = g_hookCtx->args[number].type;
	if (unlikely(params[arg_type] != type))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE,
			"%s: invalid argument type provided, expected '%s'; got '%s'",
			__FUNCTION__,
			getATypeStr(type),
			getATypeStr(static_cast<AType>(params[arg_type]))
		);

		return FALSE;
	}

	cell* srcAddr = getAmxAddr(amx, params[arg_value]);
	size_t destAddr = g_hookCtx->args[number].handle;

	switch (type)
	{
	case ATYPE_INTEGER:
	case ATYPE_FLOAT:
		*(cell *)destAddr = *srcAddr;
		break;
	case ATYPE_BOOL:
		*(bool *)destAddr = *srcAddr != 0;
		break;
	case ATYPE_STRING:
		*(char **)destAddr = getAmxString(srcAddr, g_hookCtx->get_temp_string(amx), CTempStrings::STRING_LEN);
		break;
	case ATYPE_CLASSPTR:
		*(CBaseEntity **)destAddr = getPrivate<CBaseEntity>(*srcAddr);
		break;
	case ATYPE_EDICT:
		*(edict_t **)destAddr = edictByIndexAmx(*srcAddr);
		break;
	case ATYPE_EVARS:
		*(entvars_t **)destAddr = PEV(*srcAddr);
		break;
	case ATYPE_TRACE:
		**(TraceResult **)destAddr = *(TraceResult *)(*srcAddr);
		break;
	default:
		return FALSE;
	}

	return TRUE;
}

/*
* Return call state of original API function (that are available into enum).
* Look at the enums for parameter lists.
*
* @param func       The function to get state
*
* @return           Returns true if the API original function was called, otherwise false
*
* native bool:IsReapiHookOriginalWasCalled(any:function_id);
*/
cell AMX_NATIVE_CALL IsReapiHookOriginalWasCalled(AMX* amx, cell* params)
{
	enum args_e { arg_count, arg_func };

	int func = params[arg_func];
	auto hook = g_hookManager.getHook(func);

	if (unlikely(hook == nullptr))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: function with id (%d) doesn't exist in current API version.", __FUNCTION__, func);
		return INVALID_HOOKCHAIN;
	}

	if (unlikely(!hook->checkRequirements()))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: function (%s) is not available, %s required.", __FUNCTION__, hook->func_name, hook->depend_name);
		return INVALID_HOOKCHAIN;
	}

	return hook->wasCalled ? TRUE : FALSE;
}

/*
* Returns the current hookchain handle.
*
* @return           Returns the hook handle
*
* native HookChain:GetCurrentHookChainHandle();
*/
cell AMX_NATIVE_CALL GetCurrentHookChainHandle(AMX* amx, cell* params)
{
	if (unlikely(!g_hookCtx))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: trying to get handle without active hook.", __FUNCTION__);
		return FALSE;
	}

	return g_hookCtx->index;
}

AMX_NATIVE_INFO HookChain_Natives[] =
{
	{ "RegisterHookChain", RegisterHookChain },

	{ "EnableHookChain", EnableHookChain },
	{ "DisableHookChain", DisableHookChain },

	{ "SetHookChainReturn", SetHookChainReturn },
	{ "GetHookChainReturn", GetHookChainReturn },

	{ "SetHookChainArg", SetHookChainArg },

	{ "IsReapiHookOriginalWasCalled", IsReapiHookOriginalWasCalled },

	{ "GetCurrentHookChainHandle", GetCurrentHookChainHandle },

	{ nullptr, nullptr }
};

void RegisterNatives_HookChains()
{
	g_amxxapi.AddNatives(HookChain_Natives);
}
