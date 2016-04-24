#pragma once

// hookchain return type
enum HookChainState
{
	HC_CONTINUE = 0,	// plugin didn't take any action
	HC_OVERRIDE,		// call real function, but use my return value
	HC_SUPERCEDE,		// skip real function, use my return value
	HC_BREAK		// skip all forwards and real function, use my return value
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

#define MAX_ARGS 12u

template<size_t current>
void setupArgTypes(AType args_type[MAX_ARGS])
{
}

template<size_t current = 0, typename T, typename ...t_args>
void setupArgTypes(AType args_type[MAX_ARGS], T, t_args... args)
{
	args_type[current] = getApiType(T());
	if (sizeof...(args) && current + 1 < MAX_ARGS)
		setupArgTypes<current + 1>(args_type, args...);
}

struct hookctx_t
{
	template<typename ...t_args>
	hookctx_t(size_t arg_count, t_args... args) : args_ptr()
	{
		args_count = min(arg_count, MAX_ARGS);
		setupArgTypes(args_type, args...);
	}

	void reset(size_t arg_ptr, AType ret_type = ATYPE_INTEGER)
	{
		retVal.set = false;
		retVal.type = ret_type;
		args_ptr = arg_ptr;
	}

	retval_t retVal;
	size_t args_count;
	size_t args_ptr;
	AType args_type[MAX_ARGS];
};

extern hookctx_t* g_hookCtx;

template <typename original_t, typename ...f_args>
NOINLINE void DLLEXPORT _callVoidForward(const hook_t* hook, original_t original, volatile f_args... args)
{
	g_hookCtx->reset(size_t(&original) + sizeof(original));
	int hc_state = HC_CONTINUE;

	for (auto& fwd : hook->pre)
	{
		if (fwd->GetState() == FSTATE_ENABLED)
		{
			auto ret = g_amxxapi.ExecuteForward(fwd->GetIndex(), args...);

			if (ret == HC_BREAK) {
				return;
			}

			if (ret > hc_state)
				hc_state = ret;
		}
	}

	if (hc_state != HC_SUPERCEDE)
		original(args...);

	for (auto& fwd : hook->post) {
		if (fwd->GetState() == FSTATE_ENABLED) {
			auto ret = g_amxxapi.ExecuteForward(fwd->GetIndex(), args...);

			if (ret == HC_BREAK)
				break;
		}
	}
}

template <typename original_t, typename ...f_args>
void callVoidForward(size_t func, original_t original, f_args... args)
{
#ifndef _WIN32
	static
#endif
	hookctx_t hookCtx(sizeof...(args), args...);

	g_hookCtx = &hookCtx;
	_callVoidForward(g_hookManager.getHookFast(func), original, args...);
	g_hookCtx = nullptr;
}

template <typename R, typename original_t, typename ...f_args>
NOINLINE R DLLEXPORT _callForward(const hook_t* hook, original_t original, volatile f_args... args)
{
	auto& hookCtx = *g_hookCtx;
	hookCtx.reset(size_t(&original) + sizeof(original), getApiType(R()));
	int hc_state = HC_CONTINUE;

	for (auto& fwd : hook->pre)
	{
		if (fwd->GetState() == FSTATE_ENABLED)
		{
			auto ret = g_amxxapi.ExecuteForward(fwd->GetIndex(), args...);

			if (ret == HC_CONTINUE)
				continue;

			if (!hookCtx.retVal.set) {
				g_amxxapi.LogError(fwd->GetAmx(), AMX_ERR_CALLBACK, "%s", "can't suppress original function call without new return value set");
				continue;
			}

			if (ret == HC_BREAK) {
				return *(R *)&hookCtx.retVal._interger;
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
			auto ret = g_amxxapi.ExecuteForward(fwd->GetIndex(), args...);

			if (ret == HC_BREAK)
				break;
		}
	}

	return *(R *)&hookCtx.retVal._interger;
}

template <typename R, typename original_t, typename ...f_args>
R callForward(size_t func, original_t original, f_args... args)
{
#ifndef _WIN32
	static
#endif
	hookctx_t hookCtx(sizeof...(args), args...);

	g_hookCtx = &hookCtx;
	auto ret = _callForward<R>(g_hookManager.getHookFast(func), original, args...);
	g_hookCtx = nullptr;

	return ret;
}

// rehlds functions
void SV_StartSound(IRehldsHook_SV_StartSound *chain, int recipients, edict_t *entity, int channel, const char *sample, int volume, float attenuation, int fFlags, int pitch);
void SV_DropClient(IRehldsHook_SV_DropClient *chain, IGameClient *cl, bool crash, const char *fmt);
void SV_ActivateServer(IRehldsHook_SV_ActivateServer *chain, int runPhysics);
void Cvar_DirectSet(IRehldsHook_Cvar_DirectSet *chain, cvar_t *var, const char *value);

// regamedll functions
int GetForceCamera(IReGameHook_GetForceCamera *chain, CBasePlayer *pObserver);
void PlayerBlind(IReGameHook_PlayerBlind *chain, CBasePlayer *pPlayer, entvars_t *pevInflictor, entvars_t *pevAttacker, float fadeTime, float fadeHold, int alpha, Vector& color);
void RadiusFlash_TraceLine(IReGameHook_RadiusFlash_TraceLine *chain, CBasePlayer *pPlayer, entvars_t *pevInflictor, entvars_t *pevAttacker, Vector& vecSrc, Vector& vecSpot, TraceResult *ptr);
bool RoundEnd(IReGameHook_RoundEnd *chain, int winStatus, ScenarionEventEndRound event, float tmDelay);

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
void CBasePlayer_SetAnimation(IReGameHook_CBasePlayer_SetAnimation *chain, CBasePlayer *pthis, PLAYER_ANIM playerAnim);
void CBasePlayer_GiveDefaultItems(IReGameHook_CBasePlayer_GiveDefaultItems *chain, CBasePlayer *pthis);
void CBasePlayer_GiveNamedItem(IReGameHook_CBasePlayer_GiveNamedItem *chain, CBasePlayer *pthis, const char *pszName);
void CBasePlayer_AddAccount(IReGameHook_CBasePlayer_AddAccount *chain, CBasePlayer *pthis, int amount, bool bTrackChange);
void CBasePlayer_GiveShield(IReGameHook_CBasePlayer_GiveShield *chain, CBasePlayer *pthis, bool bDeploy);

void CBaseAnimating_ResetSequenceInfo(IReGameHook_CBaseAnimating_ResetSequenceInfo *chain, CBaseAnimating *pthis);
