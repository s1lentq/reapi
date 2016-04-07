#pragma once

// hookchain return type
enum HookChainState
{
	HC_CONTINUE = 0,
	HC_OVERRIDE,
	HC_SUPERCEDE,
	HC_BREAK
};

// api types
enum AType : uint8
{
	ATYPE_INTEGER = 0,
	ATYPE_FLOAT,
	ATYPE_STRING,
	ATYPE_CLASSPTR
};

struct retval_t
{
	bool set;
	AType type;

	union
	{
		char*			_string;
		float			_float;
		int				_interger;
		CBaseEntity*	_classptr;
	};
};

inline AType getApiType(int)			{ return ATYPE_INTEGER; }
inline AType getApiType(unsigned)		{ return ATYPE_INTEGER; }
inline AType getApiType(cvar_s *)		{ return ATYPE_INTEGER; }
inline AType getApiType(float)			{ return ATYPE_FLOAT; }
inline AType getApiType(const char *)	{ return ATYPE_STRING; }
inline AType getApiType(CBaseEntity *)	{ return ATYPE_CLASSPTR; }

template<size_t current>
void setupArgTypes(AType args_type[])
{

}

#define MAX_ARGS 10u

template<size_t current = 0, typename T, typename ...t_args>
void setupArgTypes(AType args_type[MAX_ARGS], T arg, t_args... args)
{
	args_type[current] = getApiType(arg);
	if (sizeof...(args) && current + 1 < MAX_ARGS)
		setupArgTypes<current + 1>(args_type, args...);
}

struct hookctx_t
{
	template<typename ...t_args>
	hookctx_t(size_t count, size_t ptr, t_args... args)
	{
		args_count = min(count, MAX_ARGS);
		args_ptr = ptr;
		setupArgTypes(args_type, args...);
	}

	retval_t retVal;
	size_t args_count;
	size_t args_ptr;
	AType args_type[MAX_ARGS];
};

extern hookctx_t* g_hookCtx;

template <typename original_t, typename ...f_args>
void callVoidForward(int func, original_t original, f_args... args)
{
	hookctx_t hookCtx(sizeof...(args), size_t(&original) + sizeof(original), args...);
	hookCtx.retVal.set = false;
	g_hookCtx = &hookCtx;

	int hc_state = HC_CONTINUE;
	auto hook = g_hookManager.getHook(func);

	for (auto& fwd : hook->pre)
	{
		if (fwd->GetState() == FSTATE_ENABLED)
		{
			auto ret = g_amxxapi.ExecuteForward(fwd->m_forward, args...);

			if (ret == HC_BREAK) {
				g_hookCtx = nullptr;
				return;
			}

			if (ret > hc_state)
				hc_state = ret;
		}
	}

	if (hc_state != HC_SUPERCEDE)
		original(args...);

	for (auto& fwd : hook->post)
	{
		if (fwd->GetState() == FSTATE_ENABLED)
		{
			auto ret = g_amxxapi.ExecuteForward(fwd->m_forward, args...);

			if (ret == HC_BREAK)
				break;
		}
	}

	g_hookCtx = nullptr;
}

template <typename R, typename original_t, typename ...f_args>
R callForward(int func, original_t original, f_args... args)
{
	hookctx_t hookCtx(sizeof...(args), size_t(&original) + sizeof(original), args...);
	hookCtx.retVal.set = false;
	hookCtx.retVal.type = getApiType(R());
	g_hookCtx = &hookCtx;

	int hc_state = HC_CONTINUE;
	auto hook = g_hookManager.getHook(func);

	for (auto& fwd : hook->pre)
	{
		if (fwd->GetState() == FSTATE_ENABLED)
		{
			auto ret = g_amxxapi.ExecuteForward(fwd->m_forward, args...);

			if (ret == HC_CONTINUE)
				continue;

			if (!hookCtx.retVal.set)
			{
				g_amxxapi.LogError(fwd->GetAmx(), AMX_ERR_CALLBACK, "%s", "can't suppress original function call without new return value set");
				continue;
			}

			if (ret == HC_BREAK) {
				g_hookCtx = nullptr;
				return (R)hookCtx.retVal._interger;
			}

			if (ret > hc_state)
				hc_state = ret;
		}
	}

	if (hc_state != HC_SUPERCEDE)
	{
		auto retVal = original(args...);

		if (hc_state != HC_OVERRIDE)
			hookCtx.retVal._interger = *(int *)&retVal;
	}

	for (auto& fwd : hook->post) {
		if (fwd->GetState() == FSTATE_ENABLED) {
			auto ret = g_amxxapi.ExecuteForward(fwd->m_forward, args...);

			if (ret == HC_BREAK)
				break;
		}
	}

	g_hookCtx = nullptr;
	return (R)hookCtx.retVal._interger;
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
void CBasePlayer_TraceAttack(IReGameHook_CBasePlayer_TraceAttack *chain, CBasePlayer *pthis, entvars_t *pevAttacker, float flDamage, Vector& vecDir, TraceResult *ptr, int bitsDamageType);
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
