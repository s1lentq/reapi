#if defined _reapi_engine_const_included
	#endinput
#endif

#define _reapi_engine_const_included

enum EngineFunc
{
	/**
	 * Description:		-
	 * Params:		(const recipients, const entity, const channel, const sample[], const volume, Float:attenuation, const fFlags, const pitch)
	 */
	RH_SV_StartSound = 0,

	/**
	 * Description:		-
	 * Params:		(const client, bool:crash, const fmt[])
	 */
	RH_SV_DropClient,

	/**
	 * Description:		-
	 * Params:		(const runPhysics)
	 */
	RH_SV_ActivateServer,

	/**
	 * Description:		-
	 * Params:		(pcvar, const value[])
	 */
	RH_Cvar_DirectSet,

	// [...]
	RH_EngineFunc_End
};
