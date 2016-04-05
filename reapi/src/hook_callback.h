#pragma once

enum
{
	RH_UNSET = 0,
	RH_IGNORED,		// plugin didn't take any action
	RH_HANDLED,		// plugin did something, but real function should still be called
	RH_OVERRIDE,		// call real function, but use my return value
	RH_SUPERCEDE		// skip real function; use my return value
};

// for hookchain return
enum HookChainReturn
{
	RHV_STRING = 0,
	RHV_FLOAT,
	RHV_INTEGER,
	RHV_CLASSPTR
};

extern CHook *g_currentHookChain;

template <typename ...t_args>
inline bool callVoidForward_Pre(int func, t_args... args)
{
	auto hook = hooklist[func];
	register int ret = RH_UNSET;
	for (auto it = hook->pre.begin(), end = hook->pre.end(); it != end; ++it)
	{
		if ((*it)->GetState() == FSTATE_OK)
		{
			ret = g_amxxapi.ExecuteForward((*it)->GetForwardID(), args...);
		}
	}

	// no supercede, continue to call original func
	return (ret < RH_SUPERCEDE);
}

template <typename ...t_args>
inline void callVoidForward_Post(int func, t_args... args)
{
	auto hook = hooklist[func];
	for (auto it = hook->post.begin(), end = hook->post.end(); it != end; ++it)
	{
		if ((*it)->GetState() == FSTATE_OK)
		{
			g_currentHookChain = (*it);
			g_amxxapi.ExecuteForward((*it)->GetForwardID(), args...);
		}
	}
}

template <typename t_chain, typename ...t_args>
inline void callVoidForward(t_chain chain, int func, t_args... args)
{
	auto hook = hooklist[func];
	register int ret = RH_UNSET;
	for (auto it = hook->pre.begin(), end = hook->pre.end(); it != end; ++it)
	{
		if ((*it)->GetState() == FSTATE_OK)
		{
			ret = g_amxxapi.ExecuteForward((*it)->GetForwardID(), args...);
		}
	}

	// no supercede, continue to call original func
	if (ret < RH_SUPERCEDE)
	{
		chain->callNext(args...);
	}

	// Post
	for (auto it = hook->post.begin(), end = hook->post.end(); it != end; ++it)
	{
		if ((*it)->GetState() == FSTATE_OK)
		{
			g_currentHookChain = (*it);
			g_amxxapi.ExecuteForward((*it)->GetForwardID(), args...);
		}
	}
}

template <typename ...t_args>
inline bool callForward_Pre(int func, t_args... args)
{
	auto hook = hooklist[func];
	register int ret = RH_UNSET;
	for (auto it = hook->pre.begin(), end = hook->pre.end(); it != end; ++it)
	{
		if ((*it)->GetState() == FSTATE_OK)
		{
			ret = g_amxxapi.ExecuteForward((*it)->GetForwardID(), args...);
		}
	}

	// no supercede, continue to call original func
	return (ret < RH_SUPERCEDE);
}

template <typename ...t_args>
inline bool callForward_Post(int func, t_args... args)
{
	auto hook = hooklist[func];
	register int ret = RH_UNSET;
	for (auto it = hook->post.begin(), end = hook->post.end(); it != end; ++it)
	{
		if ((*it)->GetState() == FSTATE_OK)
		{
			g_currentHookChain = (*it);
			ret = g_amxxapi.ExecuteForward((*it)->GetForwardID(), args...);
		}
	}

	// no override
	return (ret < RH_OVERRIDE);
}

// rehlds functions
void SV_StartSound(IRehldsHook_SV_StartSound *chain, int recipients, edict_t *entity, int channel, const char *sample, int volume, float attenuation, int fFlags, int pitch);
void SV_DropClient(IRehldsHook_SV_DropClient *chain, IGameClient *cl, bool crash, const char *fmt);
void SV_ActivateServer(IRehldsHook_SV_ActivateServer *chain, int runPhysics);
void Cvar_DirectSet(IRehldsHook_Cvar_DirectSet *chain, cvar_t *var, const char *value);

// regamedll functions
int GetForceCamera(IReGameHook_GetForceCamera *chain, CBasePlayer *pObserver);

// regamedll functions - player
void CBasePlayer_Spawn(IReGameHook_CBasePlayer_Spawn *chain, CBasePlayer *pthis);
void CBasePlayer_Precache(IReGameHook_CBasePlayer_Precache *chain, CBasePlayer *pthis);
int CBasePlayer_ObjectCaps(IReGameHook_CBasePlayer_ObjectCaps *chain, CBasePlayer *pthis);
int CBasePlayer_Classify(IReGameHook_CBasePlayer_Classify *chain, CBasePlayer *pthis);
void CBasePlayer_TraceAttack(IReGameHook_CBasePlayer_TraceAttack *chain, CBasePlayer *pthis, entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
int CBasePlayer_TakeDamage(IReGameHook_CBasePlayer_TakeDamage *chain, CBasePlayer *pthis, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
int CBasePlayer_TakeHealth(IReGameHook_CBasePlayer_TakeHealth *chain, CBasePlayer *pthis, float flHealth, int bitsDamageType);
void CBasePlayer_Killed(IReGameHook_CBasePlayer_Killed *chain, CBasePlayer *pthis, entvars_t *pevAttacker, int iGib);
void CBasePlayer_AddPoints(IReGameHook_CBasePlayer_AddPoints *chain, CBasePlayer *pthis, int score, BOOL bAllowNegativeScore);
void CBasePlayer_AddPointsToTeam(IReGameHook_CBasePlayer_AddPointsToTeam *chain, CBasePlayer *pthis, int score, BOOL bAllowNegativeScore);
BOOL CBasePlayer_AddPlayerItem(IReGameHook_CBasePlayer_AddPlayerItem *chain, CBasePlayer *pthis, CBasePlayerItem *pItem);
BOOL CBasePlayer_RemovePlayerItem(IReGameHook_CBasePlayer_RemovePlayerItem *chain, CBasePlayer *pthis, CBasePlayerItem *pItem);
int CBasePlayer_GiveAmmo(IReGameHook_CBasePlayer_GiveAmmo *chain, CBasePlayer *pthis, int iAmount, char *szName, int iMax);
void CBasePlayer_ResetMaxSpeed(IReGameHook_CBasePlayer_ResetMaxSpeed *chain, CBasePlayer *pthis);
void CBasePlayer_Jump(IReGameHook_CBasePlayer_Jump *chain, CBasePlayer *pthis);
void CBasePlayer_Duck(IReGameHook_CBasePlayer_Duck *chain, CBasePlayer *pthis);
void CBasePlayer_PreThink(IReGameHook_CBasePlayer_PreThink *chain, CBasePlayer *pthis);
void CBasePlayer_PostThink(IReGameHook_CBasePlayer_PostThink *chain, CBasePlayer *pthis);
void CBasePlayer_UpdateClientData(IReGameHook_CBasePlayer_UpdateClientData *chain, CBasePlayer *pthis);
void CBasePlayer_ImpulseCommands(IReGameHook_CBasePlayer_ImpulseCommands *chain, CBasePlayer *pthis);
void CBasePlayer_RoundRespawn(IReGameHook_CBasePlayer_RoundRespawn *chain, CBasePlayer *pthis);
void CBasePlayer_Blind(IReGameHook_CBasePlayer_Blind *chain, CBasePlayer *pthis, float flUntilTime, float flHoldTime, float flFadeTime, int iAlpha);
CBaseEntity *CBasePlayer_Observer_IsValidTarget(IReGameHook_CBasePlayer_Observer_IsValidTarget *chain, CBasePlayer *pthis, int iPlayerIndex, bool bSameTeam);
