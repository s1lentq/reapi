#include "precompiled.h"

hookctx_t* g_hookCtx = nullptr;
CTempStrings hookctx_t::s_temp_strings;

/*
* ReHLDS functions
*/
void SV_StartSound(IRehldsHook_SV_StartSound *chain, int recipients, edict_t *entity, int channel, const char *sample, int volume, float attenuation, int fFlags, int pitch)
{
	auto original = [chain](int _recipients, int _entity, int _channel, const char *_sample, int _volume, float _attenuation, int _fFlags, int _pitch)
	{
		chain->callNext(_recipients, edictByIndexAmx(_entity), _channel, _sample, _volume, _attenuation, _fFlags, _pitch);
	};

	callVoidForward(RH_SV_StartSound, original, recipients, indexOfEdict(entity), channel, sample, volume, attenuation, fFlags, pitch);
}

void SV_DropClient(IRehldsHook_SV_DropClient *chain, IGameClient *cl, bool crash, const char *fmt)
{
	auto original = [chain](int _cl, bool _crash, const char *_fmt)
	{
		chain->callNext(g_RehldsSvs->GetClient(_cl - 1), _crash, _fmt);
	};

	callVoidForward(RH_SV_DropClient, original, cl->GetId() + 1, crash, fmt);
}

void SV_ActivateServer(IRehldsHook_SV_ActivateServer *chain, int runPhysics)
{
	auto original = [chain](int _runPhysics)
	{
		chain->callNext(_runPhysics);
	};

	callVoidForward(RH_SV_ActivateServer, original, runPhysics);
}

void Cvar_DirectSet(IRehldsHook_Cvar_DirectSet *chain, cvar_t *var, const char *value)
{
	auto original = [chain](cvar_t *_var, const char *_value)
	{
		chain->callNext(_var, _value);
	};

	callVoidForward(RH_Cvar_DirectSet, original, var, value);
}

/*
* ReGameDLL functions
*/
void CBasePlayer_Spawn(IReGameHook_CBasePlayer_Spawn *chain, CBasePlayer *pthis)
{
	auto original = [chain](int _pthis)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis));
	};

	callVoidForward(RG_CBasePlayer_Spawn, original, indexOfEdict(pthis->pev));
}

void CBasePlayer_Precache(IReGameHook_CBasePlayer_Precache *chain, CBasePlayer *pthis)
{
	auto original = [chain](int _pthis)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis));
	};

	callVoidForward(RG_CBasePlayer_Precache, original, indexOfEdict(pthis->pev));
}

int CBasePlayer_ObjectCaps(IReGameHook_CBasePlayer_ObjectCaps *chain, CBasePlayer *pthis)
{
	auto original = [chain](int _pthis)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pthis));
	};

	return callForward<int>(RG_CBasePlayer_ObjectCaps, original, indexOfEdict(pthis->pev));
}

int CBasePlayer_Classify(IReGameHook_CBasePlayer_Classify *chain, CBasePlayer *pthis)
{
	auto original = [chain](int _pthis)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pthis));
	};

	return callForward<int>(RG_CBasePlayer_Classify, original, indexOfEdict(pthis->pev));
}

void CBasePlayer_TraceAttack(IReGameHook_CBasePlayer_TraceAttack *chain, CBasePlayer *pthis, entvars_t *pevAttacker, float flDamage, Vector& vecDir, TraceResult *ptr, int bitsDamageType)
{
	Vector vecDirCopy(vecDir);

	auto original = [chain, &vecDirCopy](int _pthis, int _pevAttacker, float _flDamage, cell _vecDir, TraceResult *_ptr, int _bitsDamageType)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis), PEV(_pevAttacker), _flDamage, vecDirCopy, _ptr, _bitsDamageType);
	};

	callVoidForward(RG_CBasePlayer_TraceAttack, original, indexOfEdict(pthis->pev), indexOfEdict(pevAttacker), flDamage, g_amxxapi.PrepareCellArrayA(reinterpret_cast<cell *>(&vecDirCopy), 3, true), ptr, bitsDamageType);
}

int CBasePlayer_TakeDamage(IReGameHook_CBasePlayer_TakeDamage *chain, CBasePlayer *pthis, entvars_t *pevInflictor, entvars_t *pevAttacker, float& flDamage, int bitsDamageType)
{
	auto original = [chain](int _pthis, int _pevInflictor, int _pevAttacker, volatile float& _flDamage, int _bitsDamageType)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pthis), PEV(_pevInflictor), PEV(_pevAttacker), const_cast<float&>(_flDamage), _bitsDamageType);
	};

	return callForward<int>(RG_CBasePlayer_TakeDamage, original, indexOfEdict(pthis->pev), indexOfEdict(pevInflictor), indexOfEdict(pevAttacker), flDamage, bitsDamageType);
}

int CBasePlayer_TakeHealth(IReGameHook_CBasePlayer_TakeHealth *chain, CBasePlayer *pthis, float flHealth, int bitsDamageType)
{
	auto original = [chain](int _pthis, float _flHealth, int _bitsDamageType)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pthis), _flHealth, _bitsDamageType);
	};

	return callForward<int>(RG_CBasePlayer_TakeHealth, original, indexOfEdict(pthis->pev), flHealth, bitsDamageType);
}

void CBasePlayer_Killed(IReGameHook_CBasePlayer_Killed *chain, CBasePlayer *pthis, entvars_t *pevAttacker, int iGib)
{
	auto original = [chain](int _pthis, int _pevAttacker, int _iGib)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis), PEV(_pevAttacker), _iGib);
	};

	callVoidForward(RG_CBasePlayer_Killed, original, indexOfEdict(pthis->pev), indexOfEdict(pevAttacker), iGib);
}

void CBasePlayer_AddPoints(IReGameHook_CBasePlayer_AddPoints *chain, CBasePlayer *pthis, int score, BOOL bAllowNegativeScore)
{
	auto original = [chain](int _pthis, int _score, BOOL _bAllowNegativeScore)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis), _score, _bAllowNegativeScore);
	};

	callVoidForward(RG_CBasePlayer_AddPoints, original, indexOfEdict(pthis->pev), score, bAllowNegativeScore);
}

void CBasePlayer_AddPointsToTeam(IReGameHook_CBasePlayer_AddPointsToTeam *chain, CBasePlayer *pthis, int score, BOOL bAllowNegativeScore)
{
	auto original = [chain](int _pthis, int _score, BOOL _bAllowNegativeScore)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis), _score, _bAllowNegativeScore);
	};

	callVoidForward(RG_CBasePlayer_AddPointsToTeam, original, indexOfEdict(pthis->pev), score, bAllowNegativeScore);
}

BOOL CBasePlayer_AddPlayerItem(IReGameHook_CBasePlayer_AddPlayerItem *chain, CBasePlayer *pthis, CBasePlayerItem *pItem)
{
	auto original = [chain](int _pthis, int _pItem)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pthis), getPrivate<CBasePlayerItem>(_pItem));
	};

	return callForward<BOOL>(RG_CBasePlayer_AddPlayerItem, original, indexOfEdict(pthis->pev), indexOfEdict(pItem->pev));
}

BOOL CBasePlayer_RemovePlayerItem(IReGameHook_CBasePlayer_RemovePlayerItem *chain, CBasePlayer *pthis, CBasePlayerItem *pItem)
{
	auto original = [chain](int _pthis, int _pItem)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pthis), getPrivate<CBasePlayerItem>(_pItem));
	};

	return callForward<BOOL>(RG_CBasePlayer_RemovePlayerItem, original, indexOfEdict(pthis->pev), indexOfEdict(pItem->pev));
}

int CBasePlayer_GiveAmmo(IReGameHook_CBasePlayer_GiveAmmo *chain, CBasePlayer *pthis, int iAmount, char *szName, int iMax)
{
	auto original = [chain](int _pthis, int _iAmount, char *_szName, int _iMax)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pthis), _iAmount, _szName, _iMax);
	};

	return callForward<int>(RG_CBasePlayer_GiveAmmo, original, indexOfEdict(pthis->pev), iAmount, szName, iMax);
}

void CBasePlayer_ResetMaxSpeed(IReGameHook_CBasePlayer_ResetMaxSpeed *chain, CBasePlayer *pthis)
{
	auto original = [chain](int _pthis)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis));
	};

	callVoidForward(RG_CBasePlayer_ResetMaxSpeed, original, indexOfEdict(pthis->pev));
}

void CBasePlayer_Jump(IReGameHook_CBasePlayer_Jump *chain, CBasePlayer *pthis)
{
	auto original = [chain](int _pthis)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis));
	};

	callVoidForward(RG_CBasePlayer_Jump, original, indexOfEdict(pthis->pev));
}

void CBasePlayer_Duck(IReGameHook_CBasePlayer_Duck *chain, CBasePlayer *pthis)
{
	auto original = [chain](int _pthis)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis));
	};

	callVoidForward(RG_CBasePlayer_Duck, original, indexOfEdict(pthis->pev));
}

void CBasePlayer_PreThink(IReGameHook_CBasePlayer_PreThink *chain, CBasePlayer *pthis)
{
	auto original = [chain](int _pthis)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis));
	};

	callVoidForward(RG_CBasePlayer_PreThink, original, indexOfEdict(pthis->pev));
}

void CBasePlayer_PostThink(IReGameHook_CBasePlayer_PostThink *chain, CBasePlayer *pthis)
{
	auto original = [chain](int _pthis)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis));
	};

	callVoidForward(RG_CBasePlayer_PostThink, original, indexOfEdict(pthis->pev));
}

void CBasePlayer_UpdateClientData(IReGameHook_CBasePlayer_UpdateClientData *chain, CBasePlayer *pthis)
{
	auto original = [chain](int _pthis)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis));
	};

	callVoidForward(RG_CBasePlayer_UpdateClientData, original, indexOfEdict(pthis->pev));
}

void CBasePlayer_ImpulseCommands(IReGameHook_CBasePlayer_ImpulseCommands *chain, CBasePlayer *pthis)
{
	auto original = [chain](int _pthis)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis));
	};

	callVoidForward(RG_CBasePlayer_ImpulseCommands, original, indexOfEdict(pthis->pev));
}

void CBasePlayer_RoundRespawn(IReGameHook_CBasePlayer_RoundRespawn *chain, CBasePlayer *pthis)
{
	auto original = [chain](int _pthis)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis));
	};

	callVoidForward(RG_CBasePlayer_RoundRespawn, original, indexOfEdict(pthis->pev));
}

void CBasePlayer_Blind(IReGameHook_CBasePlayer_Blind *chain, CBasePlayer *pthis, float flUntilTime, float flHoldTime, float flFadeTime, int iAlpha)
{
	auto original = [chain](int _pthis, float _flUntilTime, float _flHoldTime, float _flFadeTime, int _iAlpha)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis), _flUntilTime, _flHoldTime, _flFadeTime, _iAlpha);
	};

	callVoidForward(RG_CBasePlayer_Blind, original, indexOfEdict(pthis->pev), flUntilTime, flHoldTime, flFadeTime, iAlpha);
}

CBasePlayer *CBasePlayer_Observer_IsValidTarget(IReGameHook_CBasePlayer_Observer_IsValidTarget *chain, CBasePlayer *pthis, int iPlayerIndex, bool bSameTeam)
{
	auto original = [chain](int _pthis, int _iPlayerIndex, bool _bSameTeam)
	{
		return indexOfPDataAmx(chain->callNext(getPrivate<CBasePlayer>(_pthis), _iPlayerIndex, _bSameTeam));
	};

	return getPrivate<CBasePlayer>(callForward<size_t>(RG_CBasePlayer_Observer_IsValidTarget, original, indexOfEdict(pthis->pev), iPlayerIndex, bSameTeam));
}

void CBasePlayer_SetAnimation(IReGameHook_CBasePlayer_SetAnimation *chain, CBasePlayer *pthis, PLAYER_ANIM playerAnim)
{
	auto original = [chain](int _pthis, PLAYER_ANIM _playerAnim)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis), _playerAnim);
	};

	callVoidForward(RG_CBasePlayer_SetAnimation, original, indexOfEdict(pthis->pev), playerAnim);
}

void CBasePlayer_GiveDefaultItems(IReGameHook_CBasePlayer_GiveDefaultItems *chain, CBasePlayer *pthis)
{
	auto original = [chain](int _pthis)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis));
	};

	callVoidForward(RG_CBasePlayer_GiveDefaultItems, original, indexOfEdict(pthis->pev));
}

CBaseEntity *CBasePlayer_GiveNamedItem(IReGameHook_CBasePlayer_GiveNamedItem *chain, CBasePlayer *pthis, const char *pszName)
{
	auto original = [chain](int _pthis, const char *_pszName)
	{
		return indexOfPDataAmx(chain->callNext(getPrivate<CBasePlayer>(_pthis), _pszName));
	};

	return getPrivate<CBaseEntity>(callForward<size_t>(RG_CBasePlayer_GiveNamedItem, original, indexOfEdict(pthis->pev), pszName));
}

void CBasePlayer_AddAccount(IReGameHook_CBasePlayer_AddAccount *chain, CBasePlayer *pthis, int amount, RewardType type, bool bTrackChange)
{
	auto original = [chain](int _pthis, int _amount, RewardType _type, bool _bTrackChange)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis), _amount, _type, _bTrackChange);
	};

	callVoidForward(RG_CBasePlayer_AddAccount, original, indexOfEdict(pthis->pev), amount, type, bTrackChange);
}

void CBasePlayer_GiveShield(IReGameHook_CBasePlayer_GiveShield *chain, CBasePlayer *pthis, bool bDeploy)
{
	auto original = [chain](int _pthis, bool _bDeploy)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis), _bDeploy);
	};

	callVoidForward(RG_CBasePlayer_GiveShield, original, indexOfEdict(pthis->pev), bDeploy);
}

void CBasePlayer_SetClientUserInfoModel(IReGameHook_CBasePlayer_SetClientUserInfoModel *chain, CBasePlayer *pthis, char *infobuffer, char *szNewModel)
{
	auto original = [chain](int _pthis, char *_infobuffer, char *_szNewModel)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis), _infobuffer, _szNewModel);
	};

	callVoidForward(RG_CBasePlayer_SetClientUserInfoModel, original, indexOfEdict(pthis->pev), infobuffer, szNewModel);
}

bool CBasePlayer_SetClientUserInfoName(IReGameHook_CBasePlayer_SetClientUserInfoName *chain, CBasePlayer *pthis, char *infobuffer, char *szNewName)
{
	auto original = [chain](int _pthis, char *_infobuffer, char *_szNewName)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pthis), _infobuffer, _szNewName);
	};

	return callForward<bool>(RG_CBasePlayer_SetClientUserInfoName, original, indexOfEdict(pthis->pev), infobuffer, szNewName);
}

bool CBasePlayer_HasRestrictItem(IReGameHook_CBasePlayer_HasRestrictItem *chain, CBasePlayer *pthis, ItemID item, ItemRestType type)
{
	auto original = [chain](int _pthis, ItemID _item, ItemRestType _type)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pthis), _item, _type);
	};

	return callForward<bool>(RG_CBasePlayer_HasRestrictItem, original, indexOfEdict(pthis->pev), item, type);
}

void CBasePlayer_DropPlayerItem(IReGameHook_CBasePlayer_DropPlayerItem *chain, CBasePlayer *pthis, const char *pszItemName)
{
	auto original = [chain](int _pthis, const char *_pszItemName)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis), _pszItemName);
	};

	callVoidForward(RG_CBasePlayer_DropPlayerItem, original, indexOfEdict(pthis->pev), pszItemName);
}

void CBaseAnimating_ResetSequenceInfo(IReGameHook_CBaseAnimating_ResetSequenceInfo *chain, CBaseAnimating *pthis)
{
	auto original = [chain](int _pthis)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pthis));
	};

	callVoidForward(RG_CBaseAnimating_ResetSequenceInfo, original, indexOfEdict(pthis->pev));
}

int GetForceCamera(IReGameHook_GetForceCamera *chain, CBasePlayer *pObserver)
{
	auto original = [chain](int _pObserver)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pObserver));
	};

	return callForward<int>(RG_GetForceCamera, original, indexOfEdict(pObserver->pev));
}

void PlayerBlind(IReGameHook_PlayerBlind *chain, CBasePlayer *pPlayer, entvars_t *pevInflictor, entvars_t *pevAttacker, float fadeTime, float fadeHold, int alpha, Vector& color)
{
	Vector colorCopy(color);

	auto original = [chain, &colorCopy](int _pPlayer, int _pevInflictor, int _pevAttacker, float _fadeTime, float _fadeHold, int _alpha, cell _color)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pPlayer), PEV(_pevInflictor), PEV(_pevAttacker), _fadeTime, _fadeHold, _alpha, colorCopy);
	};

	callVoidForward(RG_PlayerBlind, original, indexOfEdict(pPlayer->pev), indexOfEdict(pevInflictor), indexOfEdict(pevAttacker), fadeTime, fadeHold, alpha, g_amxxapi.PrepareCellArrayA(reinterpret_cast<cell *>(&colorCopy), 3, true));
}

void RadiusFlash_TraceLine(IReGameHook_RadiusFlash_TraceLine *chain, CBasePlayer *pPlayer, entvars_t *pevInflictor, entvars_t *pevAttacker, Vector& vecSrc, Vector& vecSpot, TraceResult *ptr)
{
	Vector vecSrcCopy(vecSrc), vecSpotCopy(vecSpot);

	auto original = [chain, &vecSrcCopy, &vecSpotCopy](int _pPlayer, int _pevInflictor, int _pevAttacker, cell _vecSrc, cell _vecSpot, TraceResult *_ptr)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pPlayer), PEV(_pevInflictor), PEV(_pevAttacker), vecSrcCopy, vecSpotCopy, _ptr);
	};

	callVoidForward(RG_RadiusFlash_TraceLine, original, indexOfEdict(pPlayer->pev), indexOfEdict(pevInflictor), indexOfEdict(pevAttacker), g_amxxapi.PrepareCellArrayA(reinterpret_cast<cell *>(&vecSrcCopy), 3, true), g_amxxapi.PrepareCellArrayA(reinterpret_cast<cell *>(&vecSpotCopy), 3, true), ptr);
}

bool RoundEnd(IReGameHook_RoundEnd *chain, int winStatus, ScenarioEventEndRound event, float tmDelay)
{
	auto original = [chain](int _winStatus, ScenarioEventEndRound _event, float _tmDelay)
	{
		return chain->callNext(_winStatus, _event, _tmDelay);
	};

	return callForward<bool>(RG_RoundEnd, original, winStatus, event, tmDelay);
}

void PM_Move(IReGameHook_PM_Move *chain, playermove_t *ppmove, int server)
{
	auto original = [chain](playermove_t *_ppmove, int _server)
	{
		chain->callNext(_ppmove, _server);
	};

	callVoidForward(RG_PM_Move, original, ppmove, server);
}

void PM_AirMove(IReGameHook_PM_AirMove *chain, int playerIndex)
{
	auto original = [chain](int _playerIndex)
	{
		chain->callNext(_playerIndex);
	};

	callVoidForward(RG_PM_AirMove, original, playerIndex);
}

BOOL CSGameRules_FShouldSwitchWeapon(IReGameHook_CSGameRules_FShouldSwitchWeapon *chain, CBasePlayer *pPlayer, CBasePlayerItem *pWeapon)
{
	auto original = [chain](int _pPlayer, int _pWeapon)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pPlayer), getPrivate<CBasePlayerItem>(_pWeapon));
	};

	return callForward<BOOL>(RG_CSGameRules_FShouldSwitchWeapon, original, indexOfEdict(pPlayer->pev), indexOfEdict(pWeapon->pev));
}

BOOL CSGameRules_GetNextBestWeapon(IReGameHook_CSGameRules_GetNextBestWeapon *chain, CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon)
{
	auto original = [chain](int _pPlayer, int _pCurrentWeapon)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pPlayer), getPrivate<CBasePlayerItem>(_pCurrentWeapon));
	};

	return callForward<BOOL>(RG_CSGameRules_GetNextBestWeapon, original, indexOfEdict(pPlayer->pev), indexOfEdict(pCurrentWeapon->pev));
}

float CSGameRules_FlPlayerFallDamage(IReGameHook_CSGameRules_FlPlayerFallDamage *chain, CBasePlayer *pPlayer)
{
	auto original = [chain](int _pPlayer)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pPlayer));
	};

	return callForward<float>(RG_CSGameRules_FlPlayerFallDamage, original, indexOfEdict(pPlayer->pev));
}

BOOL CSGameRules_FPlayerCanTakeDamage(IReGameHook_CSGameRules_FPlayerCanTakeDamage *chain, CBasePlayer *pPlayer, CBaseEntity *pAttacker)
{
	auto original = [chain](int _pPlayer, int _pAttacker)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pPlayer), getPrivate<CBaseEntity>(_pAttacker));
	};

	return callForward<BOOL>(RG_CSGameRules_FPlayerCanTakeDamage, original, indexOfEdict(pPlayer->pev), indexOfEdict(pAttacker->pev));
}

void CSGameRules_PlayerSpawn(IReGameHook_CSGameRules_PlayerSpawn *chain, CBasePlayer *pPlayer)
{
	auto original = [chain](int _pPlayer)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pPlayer));
	};

	callVoidForward(RG_CSGameRules_PlayerSpawn, original, indexOfEdict(pPlayer->pev));
}

BOOL CSGameRules_FPlayerCanRespawn(IReGameHook_CSGameRules_FPlayerCanRespawn *chain, CBasePlayer *pPlayer)
{
	auto original = [chain](int _pPlayer)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pPlayer));
	};

	return callForward<BOOL>(RG_CSGameRules_FPlayerCanRespawn, original, indexOfEdict(pPlayer->pev));
}

edict_t *CSGameRules_GetPlayerSpawnSpot(IReGameHook_CSGameRules_GetPlayerSpawnSpot *chain, CBasePlayer *pPlayer)
{
	auto original = [chain](int _pPlayer)
	{
		return indexOfEdict(chain->callNext(getPrivate<CBasePlayer>(_pPlayer)));
	};

	return edictByIndexAmx(callForward<size_t>(RG_CSGameRules_GetPlayerSpawnSpot, original, indexOfEdict(pPlayer->pev)));
}

void CSGameRules_ClientUserInfoChanged(IReGameHook_CSGameRules_ClientUserInfoChanged *chain, CBasePlayer *pPlayer, char *infobuffer)
{
	auto original = [chain](int _pPlayer, char *_infobuffer)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pPlayer), _infobuffer);
	};

	callVoidForward(RG_CSGameRules_ClientUserInfoChanged, original, indexOfEdict(pPlayer->pev), infobuffer);
}

void CSGameRules_PlayerKilled(IReGameHook_CSGameRules_PlayerKilled *chain, CBasePlayer *pVictim, entvars_t *pevKiller, entvars_t *pevInflictor)
{
	auto original = [chain](int _pVictim, int _pevKiller, int _pevInflictor)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pVictim), PEV(_pevKiller), PEV(_pevInflictor));
	};

	callVoidForward(RG_CSGameRules_PlayerKilled, original, indexOfEdict(pVictim->pev), indexOfEdict(pevKiller), indexOfEdictAmx(pevInflictor));
}

void CSGameRules_DeathNotice(IReGameHook_CSGameRules_DeathNotice *chain, CBasePlayer *pVictim, entvars_t *pevKiller, entvars_t *pevInflictor)
{
	auto original = [chain](int _pVictim, int _pevKiller, int _pevInflictor)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pVictim), PEV(_pevKiller), PEV(_pevInflictor));
	};

	callVoidForward(RG_CSGameRules_DeathNotice, original, indexOfEdict(pVictim->pev), indexOfEdict(pevKiller), indexOfEdictAmx(pevInflictor));
}

int CSGameRules_CanHavePlayerItem(IReGameHook_CSGameRules_CanHavePlayerItem *chain, CBasePlayer *pPlayer, CBasePlayerItem *pItem)
{
	auto original = [chain](int _pPlayer, int _pItem)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pPlayer), getPrivate<CBasePlayerItem>(_pItem));
	};

	return callForward<int>(RG_CSGameRules_CanHavePlayerItem, original, indexOfEdict(pPlayer->pev), indexOfEdict(pItem->pev));
}

int CSGameRules_DeadPlayerWeapons(IReGameHook_CSGameRules_DeadPlayerWeapons *chain, CBasePlayer *pPlayer)
{
	auto original = [chain](int _pPlayer)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pPlayer));
	};

	return callForward<int>(RG_CSGameRules_DeadPlayerWeapons, original, indexOfEdict(pPlayer->pev));
}

void CSGameRules_ServerDeactivate(IReGameHook_CSGameRules_ServerDeactivate *chain)
{
	auto original = [chain]()
	{
		chain->callNext();
	};

	callVoidForward(RG_CSGameRules_ServerDeactivate, original);
}

void CSGameRules_CheckMapConditions(IReGameHook_CSGameRules_CheckMapConditions *chain)
{
	auto original = [chain]()
	{
		chain->callNext();
	};

	callVoidForward(RG_CSGameRules_CheckMapConditions, original);
}

void CSGameRules_CleanUpMap(IReGameHook_CSGameRules_CleanUpMap *chain)
{
	auto original = [chain]()
	{
		chain->callNext();
	};

	callVoidForward(RG_CSGameRules_CleanUpMap, original);
}

void CSGameRules_RestartRound(IReGameHook_CSGameRules_RestartRound *chain)
{
	auto original = [chain]()
	{
		chain->callNext();
	};

	callVoidForward(RG_CSGameRules_RestartRound, original);
}

void CSGameRules_CheckWinConditions(IReGameHook_CSGameRules_CheckWinConditions *chain)
{
	auto original = [chain]()
	{
		chain->callNext();
	};

	callVoidForward(RG_CSGameRules_CheckWinConditions, original);
}

void CSGameRules_RemoveGuns(IReGameHook_CSGameRules_RemoveGuns *chain)
{
	auto original = [chain]()
	{
		chain->callNext();
	};

	callVoidForward(RG_CSGameRules_RemoveGuns, original);
}

void CSGameRules_GiveC4(IReGameHook_CSGameRules_GiveC4 *chain)
{
	auto original = [chain]()
	{
		chain->callNext();
	};

	callVoidForward(RG_CSGameRules_GiveC4, original);
}

void CSGameRules_ChangeLevel(IReGameHook_CSGameRules_ChangeLevel *chain)
{
	auto original = [chain]()
	{
		chain->callNext();
	};

	callVoidForward(RG_CSGameRules_ChangeLevel, original);
}

void CSGameRules_GoToIntermission(IReGameHook_CSGameRules_GoToIntermission *chain)
{
	auto original = [chain]()
	{
		chain->callNext();
	};

	callVoidForward(RG_CSGameRules_GoToIntermission, original);
}

void CSGameRules_BalanceTeams(IReGameHook_CSGameRules_BalanceTeams *chain)
{
	auto original = [chain]()
	{
		chain->callNext();
	};

	callVoidForward(RG_CSGameRules_BalanceTeams, original);
}

void HandleMenu_ChooseAppearance(IReGameHook_HandleMenu_ChooseAppearance *chain, CBasePlayer *pPlayer, int slot)
{
	auto original = [chain](int _pPlayer, int _slot)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pPlayer), _slot);
	};

	callVoidForward(RG_HandleMenu_ChooseAppearance, original, indexOfEdict(pPlayer->pev), slot);
}

BOOL HandleMenu_ChooseTeam(IReGameHook_HandleMenu_ChooseTeam *chain, CBasePlayer *pPlayer, int slot)
{
	auto original = [chain](int _pPlayer, int _slot)
	{
		return chain->callNext(getPrivate<CBasePlayer>(_pPlayer), _slot);
	};

	return callForward<BOOL>(RG_HandleMenu_ChooseTeam, original, indexOfEdict(pPlayer->pev), slot);
}

void ShowMenu(IReGameHook_ShowMenu *chain, CBasePlayer *pPlayer, int bitsValidSlots, int nDisplayTime, BOOL fNeedMore, char *pszText)
{
	auto original = [chain](int _pPlayer, int _bitsValidSlots, int _nDisplayTime, BOOL _fNeedMore, char *_pszText)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pPlayer), _bitsValidSlots, _nDisplayTime, _fNeedMore, _pszText);
	};

	callVoidForward(RG_ShowMenu, original, indexOfEdict(pPlayer->pev), bitsValidSlots, nDisplayTime, fNeedMore, pszText);
}

void ShowVGUIMenu(IReGameHook_ShowVGUIMenu *chain, CBasePlayer *pPlayer, int MenuType, int BitMask, char *szOldMenu)
{
	auto original = [chain](int _pPlayer, int _MenuType, int _BitMask, char *_szOldMenu)
	{
		chain->callNext(getPrivate<CBasePlayer>(_pPlayer), _MenuType, _BitMask, _szOldMenu);
	};

	callVoidForward(RG_ShowVGUIMenu, original, indexOfEdict(pPlayer->pev), MenuType, BitMask, szOldMenu);
}

int g_iClientStartSpeak, g_iClientStopSpeak;

void ClientStartSpeak(size_t clientIndex)
{
	g_amxxapi.ExecuteForward(g_iClientStartSpeak, clientIndex);
}

void ClientStopSpeak(size_t clientIndex)
{
	g_amxxapi.ExecuteForward(g_iClientStopSpeak, clientIndex);
}
