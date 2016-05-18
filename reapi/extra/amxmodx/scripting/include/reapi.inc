#if defined _reapi_included
	#endinput
#endif

#define _reapi_included

#if AMXX_VERSION_NUM >= 175
	#pragma reqlib reapi
	#if !defined AMXMODX_NOAUTOLOAD
		#pragma loadlib reapi
	#endif
#else
	#pragma library reapi
#endif

#define NULLENT -1

#include <reapi_engine.inc>	// NOTE: only for ReHLDS
#include <reapi_gamedll.inc>	// NOTE: only for gamedll Counter-Strike (ReGameDLL_CS)
#include <reapi_addons.inc>	// NOTE: 3-rd party addons
#include <reapi_version.inc>

// hookchain return type
enum
{
	HC_CONTINUE = 0,	// plugin didn't take any action
	HC_OVERRIDE,		// call real function, but use my return value
	HC_SUPERCEDE,		// skip real function, use my return value
	HC_BREAK		// skip a call each forward in AMXX plugins
};

// hookchain types
enum AType
{
	ATYPE_INTEGER = 0,
	ATYPE_FLOAT,
	ATYPE_STRING,
	ATYPE_CLASSPTR,
	ATYPE_EDICT
};

enum HookChain
{
	INVALID_HOOKCHAIN = 0
};

/*
* Hook API function that are available into enum
* Look at the enum's for parameter lists.
*
* @param function	The function to hook.
* @param callback	The forward to call.
* @param post		Whether or not to forward this in post.
* @return 		Returns a handle to the hook. Use EnableHookChain/DisableHookChain to toggle the forward on or off.
*
*/
native HookChain:RegisterHookChain(any:function_id, const callback[], post = 0);

/*
* Stops a hook from triggering.
* Use the return value from RegisterHookChain as the parameter here!
*
* @param hook		The hook to stop.
*
*/
native bool:DisableHookChain(HookChain:hook);

/*
* Starts a hook back up.
* Use the return value from RegisterHookChain as the parameter here!
*
* @param hook		The hook to re-enable.
* @return		Returns if the function is successful executed true otherwise false
*
*/
native bool:EnableHookChain(HookChain:hook);

/*
* Sets the return value of a hookchain.
* This needs to be used in conjunction with RH_OVERRIDE or RH_SUPERCEDE.
*
* @param type		To specify the type ATYPE_*, look at the enum AType
* @param value		The value to set the return to.
*
*/
native SetHookChainReturn(AType:type, any:...);

/*
* Gets the return value of the current hookchain.
* This has no effect in pre hookchain.
*
* @param [maxlen]	Max length of string (optional)
* @return		If an integer or boolean or one byte or float, array or everything else is passed via 1rd argument and more
*
*/
native any:GetHookChainReturn(any:...);

/*
* Set hookchain argument.
* This has no effect in post hookchain.
*
* @param number		Number of argument
* @param value		New value
* @param [maxlen]	Max length of string (optional)
* @return		Returns if the function is successful executed true otherwise false
*
*/
native SetHookChainArg(number, AType:type, any:...);

/*
* This is the callback from the module that gives major/minor versions for verifying compatibility reapi API versions
* If will be amxx plugin a failure, then you do need to upgrade to the latest version of the module reapi or do update files included for amxx plugins
* Do not modify this!
*/
public __reapi_version_check(const majorVersion, const minorVersion)
{
	if (majorVersion != REAPI_VERSION_MAJOR)
	{
		new temp[512];
		formatex(temp, sizeof temp - 1, "[ReAPI]: Api major version mismatch; expected %d, real %d", REAPI_VERSION_MAJOR, majorVersion);
		set_fail_state(temp);
		return;
	}

	if (minorVersion < REAPI_VERSION_MINOR)
	{
		new temp[512];
		formatex(temp, sizeof temp - 1, "[ReAPI]: Api minor version mismatch; expected at least %d, real %d", REAPI_VERSION_MINOR, minorVersion);
		set_fail_state(temp);
		return;
	}
}
