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
	ATYPE_CLASSPTR,
	ATYPE_EDICT,
	ATYPE_EVARS
};

struct retval_t
{
	bool set;
	AType type;

	union
	{
		char*			_string;
		float			_float;
		int			_integer;
		CBaseEntity*		_classptr;
		edict_t*		_edict;
		entvars_t*		_pev;
	};
};

inline AType getApiType(int)			{ return ATYPE_INTEGER; }
inline AType getApiType(unsigned)		{ return ATYPE_INTEGER; }
inline AType getApiType(float)			{ return ATYPE_FLOAT; }
inline AType getApiType(const char *)		{ return ATYPE_STRING; }
inline AType getApiType(char[])			{ return ATYPE_STRING; }
inline AType getApiType(CBaseEntity *)		{ return ATYPE_CLASSPTR; }
inline AType getApiType(edict_t *)		{ return ATYPE_EDICT; }
inline AType getApiType(entvars_t *)		{ return ATYPE_EVARS; }

template<typename T>
inline AType getApiType(T *) { return ATYPE_INTEGER; }

inline bool hasStringArgs() { return false; }

template <typename T, typename ...f_args>
bool hasStringArgs(T, f_args... args)
{
	if (getApiType(T()) == ATYPE_STRING) return true;
	return hasStringArgs(args...);
}

#define MAX_HOOKCHAIN_ARGS 12u

template<size_t current = 0, typename T1, typename T2, typename T3, typename T4, typename ...t_args>
void setupArgTypes(AType args_type[], T1, T2, T3, T4, t_args... args)
{
	if (current + 4 <= MAX_HOOKCHAIN_ARGS)
		*(uint32 *)&args_type[current] = getApiType(T1()) | (getApiType(T2()) << 8) | (getApiType(T3()) << 16) | (getApiType(T4()) << 24);
	if (sizeof...(args) && current + 4 < MAX_HOOKCHAIN_ARGS)
		setupArgTypes<current + 4>(args_type, args...);
}

template<size_t current = 0, typename T1, typename T2, typename T3>
void setupArgTypes(AType args_type[], T1, T2, T3)
{
	if (current + 3 <= MAX_HOOKCHAIN_ARGS)
		*(uint32 *)&args_type[current] = getApiType(T1()) | (getApiType(T2()) << 8) | (getApiType(T3()) << 16);
	else
		setupArgTypes(args_type, T1(), T2());
}

template<size_t current = 0, typename T1, typename T2>
void setupArgTypes(AType args_type[], T1, T2)
{
	if (current + 2 <= MAX_HOOKCHAIN_ARGS)
		*(uint16 *)&args_type[current] = getApiType(T1()) | (getApiType(T2()) << 8);
	else
		setupArgTypes(args_type, T1());
}

template<size_t current = 0, typename T>
void setupArgTypes(AType args_type[], T)
{
	if (current + 1 <= MAX_HOOKCHAIN_ARGS)
		args_type[current] = getApiType(T());
}

template<size_t current = 0>
void setupArgTypes(AType args_type[])
{
}

struct hookctx_t
{
	template<typename ...t_args>
	hookctx_t(size_t arg_count, t_args... args)
	{
		args_count = min(arg_count, MAX_HOOKCHAIN_ARGS);
		
		if (hasStringArgs(args...)) {
			tempstrings_used = 0;
		}

		setupArgTypes(args_type, args...);
	}

	void reset(size_t arg_ptr, AType ret_type = ATYPE_INTEGER)
	{
		retVal.set = false;
		retVal.type = ret_type;
		args_ptr = arg_ptr;
	}

	char* get_temp_string(AMX* amx)
	{
		auto ptr = s_temp_strings.push(amx);
		if (likely(ptr)) {
			tempstrings_used++;
			return ptr;
		}
		return "<reapi error>";
	}

	void clear_temp_strings() const
	{
		s_temp_strings.pop(tempstrings_used);
	}

	retval_t retVal;
	size_t args_count;
	size_t args_ptr;
	size_t tempstrings_used;
	AType args_type[MAX_HOOKCHAIN_ARGS];

	static CTempStrings s_temp_strings;
};

extern hookctx_t* g_hookCtx;

template <typename original_t, typename ...f_args>
NOINLINE void DLLEXPORT _callVoidForward(const hook_t* hook, original_t original, volatile f_args... args)
{
	auto hookCtx = g_hookCtx;
	hookCtx->reset(size_t(&original) + sizeof(original));
	int hc_state = HC_CONTINUE;

	for (auto fwd : hook->pre)
	{
		if (likely(fwd->GetState() == FSTATE_ENABLED))
		{
			auto ret = g_amxxapi.ExecuteForward(fwd->GetIndex(), args...);

			if (unlikely(ret == HC_BREAK)) {
				return;
			}

			if (unlikely(ret > hc_state))
				hc_state = ret;
		}
	}

	if (hc_state != HC_SUPERCEDE) {
		g_hookCtx = nullptr;
		original(args...);
		g_hookCtx = hookCtx;
	}

	for (auto fwd : hook->post) {
		if (likely(fwd->GetState() == FSTATE_ENABLED)) {
			auto ret = g_amxxapi.ExecuteForward(fwd->GetIndex(), args...);

			if (unlikely(ret == HC_BREAK))
				break;
		}
	}
}

template <typename original_t, typename ...f_args>
void callVoidForward(size_t func, original_t original, f_args... args)
{
	hookctx_t hookCtx(sizeof...(args), args...);
	hookctx_t* save = g_hookCtx;

	g_hookCtx = &hookCtx;
	_callVoidForward(g_hookManager.getHookFast(func), original, args...);
	g_hookCtx = save;

	if (hasStringArgs(args...)) {
		hookCtx.clear_temp_strings();
	}
}

template <typename R, typename original_t, typename ...f_args>
NOINLINE R DLLEXPORT _callForward(const hook_t* hook, original_t original, volatile f_args... args)
{
	auto hookCtx = g_hookCtx;
	hookCtx->reset(size_t(&original) + sizeof(original), getApiType(R()));
	int hc_state = HC_CONTINUE;

	for (auto fwd : hook->pre)
	{
		if (likely(fwd->GetState() == FSTATE_ENABLED))
		{
			auto ret = g_amxxapi.ExecuteForward(fwd->GetIndex(), args...);

			if (likely(ret == HC_CONTINUE)) {
				continue;
			}

			if (unlikely(!hookCtx->retVal.set)) {
				g_amxxapi.LogError(fwd->GetAmx(), AMX_ERR_CALLBACK, "can't suppress original function call without new return value set");
				continue;
			}

			if (unlikely(ret == HC_BREAK)) {
				return *(R *)&hookCtx->retVal._integer;
			}

			if (unlikely(ret > hc_state))
				hc_state = ret;
		}
	}

	if (likely(hc_state != HC_SUPERCEDE))
	{
		g_hookCtx = nullptr;
		auto retVal = original(args...);
		g_hookCtx = hookCtx;

		if (likely(hc_state != HC_OVERRIDE))
			hookCtx->retVal._integer = *(int *)&retVal;

		hookCtx->retVal.set = true;
	}

	for (auto fwd : hook->post) {
		if (likely(fwd->GetState() == FSTATE_ENABLED)) {
			auto ret = g_amxxapi.ExecuteForward(fwd->GetIndex(), args...);

			if (unlikely(ret == HC_BREAK))
				break;
		}
	}

	return *(R *)&hookCtx->retVal._integer;
}

template <typename R, typename original_t, typename ...f_args>
R callForward(size_t func, original_t original, f_args... args)
{
	if (sizeof(R) > sizeof(int)) {
		UTIL_SysError("%s: invalid return type size (%i)", __FUNCTION__, sizeof(R));
	}

	hookctx_t hookCtx(sizeof...(args), args...);
	hookctx_t* save = g_hookCtx;

	g_hookCtx = &hookCtx;
	auto ret = _callForward<R>(g_hookManager.getHookFast(func), original, args...);
	g_hookCtx = save;

	if (hasStringArgs(args...)) {
		hookCtx.clear_temp_strings();
	}

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
bool RoundEnd(IReGameHook_RoundEnd *chain, int winStatus, ScenarioEventEndRound event, float tmDelay);
void PM_Move(IReGameHook_PM_Move *chain, playermove_t *ppmove, int server);
void PM_AirMove(IReGameHook_PM_AirMove *chain, int playerIndex);
void HandleMenu_ChooseAppearance(IReGameHook_HandleMenu_ChooseAppearance *chain, CBasePlayer *pPlayer, int slot);
BOOL HandleMenu_ChooseTeam(IReGameHook_HandleMenu_ChooseTeam *chain, CBasePlayer *pPlayer, int slot);
void ShowMenu(IReGameHook_ShowMenu *chain, CBasePlayer *pPlayer, int bitsValidSlots, int nDisplayTime, BOOL fNeedMore, char *pszText);
void ShowVGUIMenu(IReGameHook_ShowVGUIMenu *chain, CBasePlayer *pPlayer, int MenuType, int BitMask, char *szOldMenu);

// regamedll functions - player
void CBasePlayer_Spawn(IReGameHook_CBasePlayer_Spawn *chain, CBasePlayer *pthis);
void CBasePlayer_Precache(IReGameHook_CBasePlayer_Precache *chain, CBasePlayer *pthis);
int CBasePlayer_ObjectCaps(IReGameHook_CBasePlayer_ObjectCaps *chain, CBasePlayer *pthis);
int CBasePlayer_Classify(IReGameHook_CBasePlayer_Classify *chain, CBasePlayer *pthis);
void CBasePlayer_TraceAttack(IReGameHook_CBasePlayer_TraceAttack *chain, CBasePlayer *pthis, entvars_t *pevAttacker, float flDamage, Vector& vecDir, TraceResult *ptr, int bitsDamageType);
int CBasePlayer_TakeDamage(IReGameHook_CBasePlayer_TakeDamage *chain, CBasePlayer *pthis, entvars_t *pevInflictor, entvars_t *pevAttacker, float& flDamage, int bitsDamageType);
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

CBasePlayer *CBasePlayer_Observer_IsValidTarget(IReGameHook_CBasePlayer_Observer_IsValidTarget *chain, CBasePlayer *pthis, int iPlayerIndex, bool bSameTeam);
void CBasePlayer_SetAnimation(IReGameHook_CBasePlayer_SetAnimation *chain, CBasePlayer *pthis, PLAYER_ANIM playerAnim);
void CBasePlayer_GiveDefaultItems(IReGameHook_CBasePlayer_GiveDefaultItems *chain, CBasePlayer *pthis);
void CBasePlayer_GiveNamedItem(IReGameHook_CBasePlayer_GiveNamedItem *chain, CBasePlayer *pthis, const char *pszName);
void CBasePlayer_AddAccount(IReGameHook_CBasePlayer_AddAccount *chain, CBasePlayer *pthis, int amount, RewardType type, bool bTrackChange);
void CBasePlayer_GiveShield(IReGameHook_CBasePlayer_GiveShield *chain, CBasePlayer *pthis, bool bDeploy);
void CBasePlayer_SetClientUserInfoModel(IReGameHook_CBasePlayer_SetClientUserInfoModel *chain, CBasePlayer *pthis, char *infobuffer, char *szNewModel);
void CBasePlayer_SetClientUserInfoName(IReGameHook_CBasePlayer_SetClientUserInfoName *chain, CBasePlayer *pthis, char *infobuffer, char *szNewName);
bool CBasePlayer_HasRestrictItem(IReGameHook_CBasePlayer_HasRestrictItem *chain, CBasePlayer *pthis, ItemID item, ItemRestType type);
void CBasePlayer_DropPlayerItem(IReGameHook_CBasePlayer_DropPlayerItem *chain, CBasePlayer *pthis, const char *pszItemName);

void CBaseAnimating_ResetSequenceInfo(IReGameHook_CBaseAnimating_ResetSequenceInfo *chain, CBaseAnimating *pthis);

BOOL CSGameRules_FShouldSwitchWeapon(IReGameHook_CSGameRules_FShouldSwitchWeapon *chain, CBasePlayer *pPlayer, CBasePlayerItem *pWeapon);
BOOL CSGameRules_GetNextBestWeapon(IReGameHook_CSGameRules_GetNextBestWeapon *chain, CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon);
float CSGameRules_FlPlayerFallDamage(IReGameHook_CSGameRules_FlPlayerFallDamage *chain, CBasePlayer *pPlayer);
BOOL CSGameRules_FPlayerCanTakeDamage(IReGameHook_CSGameRules_FPlayerCanTakeDamage *chain, CBasePlayer *pPlayer, CBaseEntity *pAttacker);
void CSGameRules_PlayerSpawn(IReGameHook_CSGameRules_PlayerSpawn *chain, CBasePlayer *pPlayer);
BOOL CSGameRules_FPlayerCanRespawn(IReGameHook_CSGameRules_FPlayerCanRespawn *chain, CBasePlayer *pPlayer);
edict_t *CSGameRules_GetPlayerSpawnSpot(IReGameHook_CSGameRules_GetPlayerSpawnSpot *chain, CBasePlayer *pPlayer);
void CSGameRules_ClientUserInfoChanged(IReGameHook_CSGameRules_ClientUserInfoChanged *chain, CBasePlayer *pPlayer, char *infobuffer);
void CSGameRules_PlayerKilled(IReGameHook_CSGameRules_PlayerKilled *chain, CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor);
void CSGameRules_DeathNotice(IReGameHook_CSGameRules_DeathNotice *chain, CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pevInflictor);
int CSGameRules_CanHavePlayerItem(IReGameHook_CSGameRules_CanHavePlayerItem *chain, CBasePlayer *pPlayer, CBasePlayerItem *pItem);
int CSGameRules_DeadPlayerWeapons(IReGameHook_CSGameRules_DeadPlayerWeapons *chain, CBasePlayer *pPlayer);
void CSGameRules_ServerDeactivate(IReGameHook_CSGameRules_ServerDeactivate *chain);
void CSGameRules_CheckMapConditions(IReGameHook_CSGameRules_CheckMapConditions *chain);
void CSGameRules_CleanUpMap(IReGameHook_CSGameRules_CleanUpMap *chain);
void CSGameRules_RestartRound(IReGameHook_CSGameRules_RestartRound *chain);
void CSGameRules_CheckWinConditions(IReGameHook_CSGameRules_CheckWinConditions *chain);
void CSGameRules_RemoveGuns(IReGameHook_CSGameRules_RemoveGuns *chain);
void CSGameRules_GiveC4(IReGameHook_CSGameRules_GiveC4 *chain);
void CSGameRules_ChangeLevel(IReGameHook_CSGameRules_ChangeLevel *chain);
void CSGameRules_GoToIntermission(IReGameHook_CSGameRules_GoToIntermission *chain);
void CSGameRules_BalanceTeams(IReGameHook_CSGameRules_BalanceTeams *chain);

extern int g_iClientStartSpeak;
extern int g_iClientStopSpeak;

void ClientStartSpeak(size_t clientIndex);
void ClientStopSpeak(size_t clientIndex);
