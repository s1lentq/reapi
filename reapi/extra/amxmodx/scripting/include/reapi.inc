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

enum hooks_tables_e
{
	ht_engine,
	ht_gamedll,
	ht_animating,
	ht_player,
	ht_gamerules
};

enum members_tables_e
{
	mt_gamerules,
	mt_base,
	mt_animating,
	mt_basemonster,
	mt_player,
	mt_entvars,
	mt_playermove,
	mt_movevars,
	mt_usercmd,
	mt_pmtrace,
	mt_csplayer,
	mt_baseitem,
	mt_baseweapon,
	mt_weaponbox,
	mt_armoury
};

// Is like FNullEnt
#define is_nullent(%0)			(%0 != 0 && is_entity(%0) == false)

#define MAX_REGION_RANGE		1024

#define BEGIN_FUNC_REGION(%0)		(any:MAX_REGION_RANGE * hooks_tables_e:ht_%0)
#define BEGIN_MEMBER_REGION(%0)		(any:MAX_REGION_RANGE * members_tables_e:mt_%0)

#include <cssdk_const>

#include <reapi_engine>		// NOTE: only for ReHLDS
#include <reapi_gamedll>	// NOTE: only for gamedll Counter-Strike (ReGameDLL_CS)
#include <reapi_addons>		// NOTE: 3rd party addons
#include <reapi_version>

// hookchain return type
enum
{
	HC_CONTINUE = 0,	// Plugin didn't take any action
	HC_SUPERCEDE,		// Skip real function, use my return value
	HC_BREAK		// Skip all forwards and real function, use my return value
				// @note Warning: Be very careful, using this type of return will skip calls for all following AMXX plugins
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
* Hook API function that are available into enum.
* Look at the enums for parameter lists.
*
* @param function	The function to hook
* @param callback	The forward to call
* @param post		Whether or not to forward this in post
* @return 		Returns a hook handle. Use EnableHookChain/DisableHookChain to toggle the forward on or off
*
*/
native HookChain:RegisterHookChain({EngineFunc, GamedllFunc, GamedllFunc_CBaseAnimating, GamedllFunc_CBasePlayer, GamedllFunc_CSGameRules}:function_id, const callback[], post = 0);

/*
* Stops a hook from triggering.
* Use the return value from RegisterHookChain as the parameter here!
*
* @param hook		The hook to stop
*
*/
native bool:DisableHookChain(HookChain:hook);

/*
* Starts a hook back up.
* Use the return value from RegisterHookChain as the parameter here!
*
* @param hook		The hook to re-enable
* @return		Returns true if the function is successfully executed, otherwise false
*
*/
native bool:EnableHookChain(HookChain:hook);

/*
* Sets the return value of a hookchain.
*
* @param type		To specify the ATYPE_* parameter, look at the enum AType
* @param value		The value to set the return to
*
*/
native SetHookChainReturn(AType:type, any:...);

/*
* Gets the return value of the current hookchain.
* This has no effect in pre hookchain.
*
* @param type		To specify the ATYPE_* parameter, look at the enum AType
* @param [maxlen]	Max length of string (optional)
* @return		If an integer or boolean or one byte or float, array or everything else is passed via 1st argument and more
*
*/
native any:GetHookChainReturn(AType:type, any:...);

/*
* Set hookchain argument.
* This has no effect in post hookchain.
*
* @param number		Number of argument
* @param value		New value
* @param [maxlen]	Max length of string (optional)
* @return		Returns true if the function is successfully executed, otherwise false
*
*/
native SetHookChainArg(number, AType:type, any:...);

/*
* Compares the entity to a specified classname.
* @note This native also checks the validity of an entity.
*
* @return		true/false
*
*/
native bool:FClassnameIs(const entityIndex, const className[]);

/*
* Check if the entity is valid.
*
* @return		true/false
*
*/
native bool:is_entity(const entityIndex);

/*
* Check if ReHLDS is available.
*
* @return		true/false
*
*/
native bool:is_rehlds();

/*
* Check if ReGameDLL is available.
*
* @return		true/false
*
*/
native bool:is_regamedll();

/*
* Check if Reunion is available.
*
* @return		true/false
*
*/
native bool:has_reunion();

/*
* Check if VTC is available.
*
* @return		true/false
*
*/
native bool:has_vtc();

/*
* This is the callback from the module that gives major/minor versions for verifying compatibility for ReAPI versions.
* If an AMXX plugin gets a failure, then you do need to upgrade to the latest version of the ReAPI module or update the files included for AMXX plugins.
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