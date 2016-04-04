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

	if (hooklist[func] == nullptr)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Function (%d) doesn't match hook definition.", func);
		return 0;
	}

	if (!hooklist[func]->availableFunc())
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Function (%s) is not available, required %s", hooklist[func]->func_name, hooklist[func]->depend_name);
		return 0;
	}

	int funcid, len;
	const char *funcname = g_amxxapi.GetAmxString(amx, params[arg_handler], 0, &len);
	if (g_amxxapi.amx_FindPublic(amx, funcname, &funcid) != AMX_ERR_NONE)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Public function \"%s\" not found.", funcname);
		return 0;
	}

	int fwid = hooklist[func]->registerForward(amx, funcname);
	if (fwid == -1)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Public function \"%s\" not found.", funcname);
		return 0;
	}

	return (cell)g_hookManager.addHandler(func, fwid, post != 0);
}

/*
 * Starts a hook back up.
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

	CHook *hook = reinterpret_cast<CHook *>(params[arg_handle_hook]);

	if (hook == nullptr)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Invalid HookChain handle.");
		return 0;
	}

	hook->m_state = FSTATE_OK;
	return 1;
}

/*
 * Stops a hook from triggering.
 * Use the return value from RegisterHookChain as the parameter here!
 *
 * @param fwd		The hook to stop.
 *
 * native bool:DisableHookChain(any:fwd);
 */

static cell AMX_NATIVE_CALL DisableHookChain(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_handle_hook };

	CHook *hook = reinterpret_cast<CHook *>(params[arg_handle_hook]);

	if (hook == nullptr)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Invalid HookChain handle.");
		return 0;
	}

	hook->m_state = FSTATE_STOP;
	return 1;
}

/*
 * Sets the return value of a hookchain.
 * This needs to be used in conjunction with RH_OVERRIDE or RH_SUPERCEDE.
 *
 * @param type		To specify the type RHV_*, look at the enum HookChainReturn
 * @param value		The value to set the return to.
 *
 * native SetHookChainReturn(HookChainReturn:type, any:...);
 */

static cell AMX_NATIVE_CALL SetHookChainReturn(AMX *amx, cell *params)
{
	if (!g_currentHookChain)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Trying get return value without active hook.");
		return 0;
	}

	enum args_e { arg_count, arg_type, arg_value };

	switch (params[arg_type])
	{
	case RHV_STRING:
	{
		if (g_currentHookChain->m_data.m_string != NULL) {
			delete [] g_currentHookChain->m_data.m_string;
		}

		int len;
		char *dest = g_amxxapi.GetAmxString(amx, params[arg_value], 0, &len);
		g_currentHookChain->m_data.m_string = new char [len + 1];
		strcpy(g_currentHookChain->m_data.m_string, dest);
		break;
	}
	case RHV_FLOAT:
		g_currentHookChain->m_data.m_float = *(float *)g_amxxapi.GetAmxAddr(amx, params[arg_value]);
		break;
	case RHV_INTEGER:
		g_currentHookChain->m_data.m_interger = *g_amxxapi.GetAmxAddr(amx, params[arg_value]);
		break;
	case RHV_CLASSPTR:
		g_currentHookChain->m_data.m_classptr = CBaseEntity::Instance(INDEXENT(*g_amxxapi.GetAmxAddr(amx, params[arg_value])));
		break;
	default:
		return 0;
	}

	return 1;
}

AMX_NATIVE_INFO Func_Natives[] =
{
	{ "RegisterHookChain", RegisterHookChain },

	{ "EnableHookChain", EnableHookChain },
	{ "DisableHookChain", DisableHookChain },
	
	{ "SetHookChainReturn", SetHookChainReturn },

	{ nullptr, nullptr }
};

void RegisterNatives()
{
	g_amxxapi.AddNatives(Func_Natives);
	g_amxxapi.AddNatives(Member_Natives);
}
