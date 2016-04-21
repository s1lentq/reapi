#include "precompiled.h"

/*
 * Hook API function that are available into enum
 * Look at the enum's for parameter lists.
 *
 * @param function	The function to hook.
 * @param callback	The forward to call.
 * @param post		Whether or not to forward this in post.
 * @return 		Returns a handle to the hook. Use EnableHookChain/DisableHookChain to toggle the forward on or off.
 *
 * native RegisterHookChain(any:function_id, const callback[], post = 0);
 */

static cell AMX_NATIVE_CALL RegisterHookChain(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_func, arg_handler, arg_post };

	int func = params[arg_func];
	int post = params[arg_post];
	auto hook = g_hookManager.getHook(func);

	if (hook == nullptr)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "RegisterHookChain: function with id (%d) doesn't exist in current API version.", func);
		return 0;
	}

	if (!hook->checkRequirements())
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "RegisterHookChain: function (%s) is not available, %s required", hook->func_name, hook->depend_name);
		return 0;
	}

	int funcid;
	const char *funcname = getAmxString(amx, params[arg_handler]);
	if (g_amxxapi.amx_FindPublic(amx, funcname, &funcid) != AMX_ERR_NONE)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "RegisterHookChain: public function \"%s\" not found.", funcname);
		return 0;
	}

	int fwid = hook->registerForward(amx, funcname);
	if (fwid == -1)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "RegisterHookChain: register forward failed.");
		return 0;
	}

	return g_hookManager.addHandler(amx, func, fwid, post != 0);
}

/*
 * Enable hook by handle.
 * Use the return value from RegisterHookChain as the parameter here!
 *
 * @param fwd		The hook to re-enable.
 * @return		Returns if the function is successful executed true otherwise false
 *
 * native bool:EnableHookChain(any:fwd);
 */

static cell AMX_NATIVE_CALL EnableHookChain(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_handle_hook };

	auto hook = g_hookManager.getAmxxHook(params[arg_handle_hook]);

	if (hook == nullptr)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "EnableHookChain: invalid HookChain handle.");
		return FALSE;
	}

	hook->SetState(FSTATE_ENABLED);
	return TRUE;
}

/*
 * Disable hook by handle.
 * Use the return value from RegisterHookChain as the parameter here!
 *
 * @param fwd		The hook to stop.
 *
 * native bool:DisableHookChain(any:fwd);
 */

static cell AMX_NATIVE_CALL DisableHookChain(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_handle_hook };

	auto hook = g_hookManager.getAmxxHook(params[arg_handle_hook]);

	if (hook == nullptr)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "DisableHookChain: invalid HookChain handle.");
		return FALSE;
	}

	hook->SetState(FSTATE_STOPPED);
	return TRUE;
}

/*
 * Sets the return value of a hookchain.
 * This needs to be used in conjunction with RH_OVERRIDE or RH_SUPERCEDE.
 *
 * @param type		To specify the type RHV_*, look at the enum AType
 * @param value		The value to set the return to.
 *
 * native SetHookChainReturn(AType:type, any:...);
 */

static cell AMX_NATIVE_CALL SetHookChainReturn(AMX *amx, cell *params)
{
	if (!g_hookCtx)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Trying to set return value without active hook.");
		return FALSE;
	}

	enum args_e { arg_count, arg_type, arg_value };
	auto& retVal = g_hookCtx->retVal;

	if (params[arg_type] != retVal.type)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Trying to set incompatible return type.");
		return FALSE;
	}

	cell* srcAddr = getAmxAddr(amx, params[arg_value]);

	switch (retVal.type)
	{
	case ATYPE_INTEGER:
	case ATYPE_FLOAT:
		retVal._interger = *srcAddr;
		break;
	
	case ATYPE_STRING:
	{
		if (retVal._string != nullptr)
			delete[] retVal._string;

		size_t len;
		const char *dest = getAmxString(srcAddr, &len);
		retVal._string = strcpy(new char[len + 1], dest);
		break;
	}
	case ATYPE_CLASSPTR:
		retVal._classptr = CBaseEntity::Instance(INDEXENT(*srcAddr));
		break;
	default:
		return FALSE;
	}

	retVal.set = true;
	return TRUE;
}

/*
* Get the return value of a hookchain.
* This needs to be used in conjunction with RH_OVERRIDE or RH_SUPERCEDE.
*
* @param value		The value to set the return to.
* @param [maxlen]	Max length of string (optional)
* @return		Returns if the function is successful executed true otherwise false
*
* native GetHookChainReturn(AType:type, any:...);
*/

static cell AMX_NATIVE_CALL GetHookChainReturn(AMX *amx, cell *params)
{
	if (!g_hookCtx)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Trying to get return value without active hook.");
		return FALSE;
	}

	enum args_e { arg_count, arg_value, arg_maxlen };

	auto& retVal = g_hookCtx->retVal;
	cell* dstAddr = getAmxAddr(amx, params[arg_value]);

	switch (retVal.type)
	{
	case ATYPE_INTEGER:
	case ATYPE_FLOAT:
		*dstAddr = retVal._interger;
		break;
	case ATYPE_STRING:
	{
		if (PARAMS_COUNT != 2)
			return FALSE;

		setAmxString(dstAddr, retVal._string, params[arg_maxlen]);
		break;
	}
	case ATYPE_CLASSPTR:
		*dstAddr = retVal._classptr->entindex();
		break;
	default:
		return FALSE;
	}

	return TRUE;
}

/*
* Set hookchain argument.
* This needs to be used in conjunction with RH_OVERRIDE or RH_SUPERCEDE.
*
* @param number		Number of argument
* @param value		New value
* @param [maxlen]	Max length of string (optional)
* @return		Returns if the function is successful executed true otherwise false
*
* native SetHookChainArg(number, AType:type, any:...);
*/

static cell AMX_NATIVE_CALL SetHookChainArg(AMX *amx, cell *params)
{
	if (!g_hookCtx)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Trying to get return value without active hook.");
		return FALSE;
	}

	enum args_e { arg_count, arg_number, arg_type, arg_value };
	size_t number = params[arg_number] - 1;

	if (number >= g_hookCtx->args_count)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "SetHookChainArg: can't set argument %i of hookchain with %i args.", params[arg_number], g_hookCtx->args_count);
		return FALSE;
	}

	AType type = g_hookCtx->args_type[number];

	if (params[arg_type] != type)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "SetHookChainArg: invalid argument type provided.");
		return FALSE;
	}

	static char temp_strings[MAX_ARGS][1024];

	cell* srcAddr = getAmxAddr(amx, params[arg_value]);
	size_t destAddr = g_hookCtx->args_ptr + number * sizeof(int);

	switch (type)
	{
	case ATYPE_INTEGER:
	case ATYPE_FLOAT:
		*(cell *)destAddr = *srcAddr;
		break;
	case ATYPE_STRING:
		*(char **)destAddr = getAmxStringTemp(srcAddr, temp_strings[number], 1023);
		break;
	case ATYPE_CLASSPTR:
		*(CBaseEntity **)destAddr = CBaseEntity::Instance(INDEXENT(*srcAddr));
		break;
	}

	return TRUE;
}

AMX_NATIVE_INFO HookChain_Natives[] =
{
	{ "RegisterHookChain", RegisterHookChain },

	{ "EnableHookChain", EnableHookChain },
	{ "DisableHookChain", DisableHookChain },
	
	{ "SetHookChainReturn", SetHookChainReturn },
	{ "GetHookChainReturn", GetHookChainReturn },

	{ "SetHookChainArg", SetHookChainArg },

	{ nullptr, nullptr }
};

void RegisterNatives_HookChains()
{
	g_amxxapi.AddNatives(HookChain_Natives);
}
