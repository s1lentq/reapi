#include "precompiled.h"

CHook *g_currentHookChain = nullptr;

/*
* ReHLDS functions
*/
void SV_StartSound(IRehldsHook_SV_StartSound *chain, int recipients, edict_t *entity, int channel, const char *sample, int volume, float attenuation, int fFlags, int pitch)
{
	if (callVoidForward_Pre(RH_SV_StartSound, recipients, ENTINDEX(entity), channel, sample, volume, attenuation, fFlags, pitch)) {
		chain->callNext(recipients, entity, channel, sample, volume, attenuation, fFlags, pitch);
	}

	callVoidForward_Post(RH_SV_StartSound, recipients, ENTINDEX(entity), channel, sample, volume, attenuation, fFlags, pitch);
}

void SV_DropClient(IRehldsHook_SV_DropClient *chain, IGameClient *cl, bool crash, const char *fmt)
{
	if (callVoidForward_Pre(RH_SV_DropClient, cl->GetId(), crash, fmt)) {
		chain->callNext(cl, crash, fmt);
	}

	callVoidForward_Post(RH_SV_DropClient, cl->GetId(), crash, fmt);
}

void SV_ActivateServer(IRehldsHook_SV_ActivateServer *chain, int runPhysics)
{
	callVoidForward(chain, RH_SV_ActivateServer, runPhysics);
}

void Cvar_DirectSet(IRehldsHook_Cvar_DirectSet *chain, cvar_t *var, const char *value)
{
	callVoidForward(chain, RH_Cvar_DirectSet, var, value);
}

/*
* ReGameDLL functions
*/
void CBasePlayer_Spawn(IReGameHook_CBasePlayer_Spawn *chain, CBasePlayer *pthis)
{
	if (callVoidForward_Pre(RH_CBasePlayer_Spawn, pthis->entindex())) {
		chain->callNext();
	}

	callVoidForward_Post(RH_CBasePlayer_Spawn, pthis->entindex());
}

void CBasePlayer_Precache(IReGameHook_CBasePlayer_Precache *chain, CBasePlayer *pthis)
{
	if (callVoidForward_Pre(RH_CBasePlayer_Precache, pthis->entindex())) {
		chain->callNext();
	}

	callVoidForward_Post(RH_CBasePlayer_Precache, pthis->entindex());
}

int CBasePlayer_ObjectCaps(IReGameHook_CBasePlayer_ObjectCaps *chain, CBasePlayer *pthis)
{
	int ownresult = 0;		// return own for OVERRIDE
	int origresult = 0;		// return by call original function

	if (callForward_Pre(RH_CBasePlayer_ObjectCaps, pthis->entindex())) {
		origresult = chain->callNext();
	}

	if (callForward_Post(RH_CBasePlayer_ObjectCaps, pthis->entindex())) {
		// return original
		return origresult;
	}

	// return from override
	return g_currentHookChain->m_data.m_interger;
}

int CBasePlayer_Classify(IReGameHook_CBasePlayer_Classify *chain, CBasePlayer *pthis)
{
	//int ownresult = 0;		// return own for OVERRIDE
	int origresult = 0;		// return by call original function

	if (callForward_Pre(RH_CBasePlayer_Classify, pthis->entindex())) {
		origresult = chain->callNext();
	}

	if (callForward_Post(RH_CBasePlayer_Classify, pthis->entindex())) {
		// return original
		return origresult;
	}

	// return from override
	return g_currentHookChain->m_data.m_interger;
}

void CBasePlayer_TraceAttack(IReGameHook_CBasePlayer_TraceAttack *chain, CBasePlayer *pthis, entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType)
{
	if (callVoidForward_Pre(RH_CBasePlayer_TraceAttack, pthis->entindex(), ENTINDEX(pevAttacker), flDamage,	g_amxxapi.PrepareCellArrayA(reinterpret_cast<cell *>(&vecDir), 3, false), ptr, bitsDamageType)) {
		chain->callNext(pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
	}

	callVoidForward_Post(RH_CBasePlayer_TraceAttack, pthis->entindex(), ENTINDEX(pevAttacker), flDamage,	g_amxxapi.PrepareCellArrayA(reinterpret_cast<cell *>(&vecDir), 3, false), ptr, bitsDamageType);
}

int CBasePlayer_TakeDamage(IReGameHook_CBasePlayer_TakeDamage *chain, CBasePlayer *pthis, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	//int ownresult = 0;		// return own for OVERRIDE
	int origresult = 0;		// return by call original function

	if (callForward_Pre(RH_CBasePlayer_TakeDamage, pthis->entindex(), ENTINDEX(pevInflictor), ENTINDEX(pevAttacker), flDamage, bitsDamageType)) {
		origresult = chain->callNext(pevInflictor, pevAttacker, flDamage, bitsDamageType);
	}

	if (callForward_Post(RH_CBasePlayer_TakeDamage, pthis->entindex(), ENTINDEX(pevInflictor), ENTINDEX(pevAttacker), flDamage, bitsDamageType)) {
		// return original
		return origresult;
	}

	// return from override
	return g_currentHookChain->m_data.m_interger;
}

int CBasePlayer_TakeHealth(IReGameHook_CBasePlayer_TakeHealth *chain, CBasePlayer *pthis, float flHealth, int bitsDamageType)
{
	//int ownresult = 0;		// return own for OVERRIDE
	int origresult = 0;		// return by call original function

	if (callForward_Pre(RH_CBasePlayer_TakeHealth, pthis->entindex(), flHealth, bitsDamageType)) {
		origresult = chain->callNext(flHealth, bitsDamageType);
	}

	if (callForward_Post(RH_CBasePlayer_TakeHealth, pthis->entindex(), flHealth, bitsDamageType)) {
		// return original
		return origresult;
	}

	// return from override
	return g_currentHookChain->m_data.m_interger;
}

void CBasePlayer_Killed(IReGameHook_CBasePlayer_Killed *chain, CBasePlayer *pthis, entvars_t *pevAttacker, int iGib)
{
	if (callVoidForward_Pre(RH_CBasePlayer_Killed, pthis->entindex(), ENTINDEX(pevAttacker), iGib)) {
		chain->callNext(pevAttacker, iGib);
	}

	callVoidForward_Post(RH_CBasePlayer_Killed, pthis->entindex(), ENTINDEX(pevAttacker), iGib);
}

void CBasePlayer_AddPoints(IReGameHook_CBasePlayer_AddPoints *chain, CBasePlayer *pthis, int score, BOOL bAllowNegativeScore)
{
	if (callVoidForward_Pre(RH_CBasePlayer_AddPoints, pthis->entindex(), score, bAllowNegativeScore)) {
		chain->callNext(score, bAllowNegativeScore);
	}

	callVoidForward_Post(RH_CBasePlayer_AddPoints, pthis->entindex(), score, bAllowNegativeScore);
}

void CBasePlayer_AddPointsToTeam(IReGameHook_CBasePlayer_AddPointsToTeam *chain, CBasePlayer *pthis, int score, BOOL bAllowNegativeScore)
{
	if (callVoidForward_Pre(RH_CBasePlayer_AddPointsToTeam, pthis->entindex(), score, bAllowNegativeScore)) {
		chain->callNext(score, bAllowNegativeScore);
	}

	callVoidForward_Post(RH_CBasePlayer_AddPointsToTeam, pthis->entindex(), score, bAllowNegativeScore);
}

BOOL CBasePlayer_AddPlayerItem(IReGameHook_CBasePlayer_AddPlayerItem *chain, CBasePlayer *pthis, CBasePlayerItem *pItem)
{
	//BOOL ownresult = 0;		// return own for OVERRIDE
	BOOL origresult = 0;		// return by call original function

	if (callForward_Pre(RH_CBasePlayer_AddPlayerItem, pthis->entindex(), pItem->entindex())) {
		origresult = chain->callNext(pItem);
	}

	if (callForward_Post(RH_CBasePlayer_AddPlayerItem, pthis->entindex(), pItem->entindex())) {
		// return original
		return origresult;
	}

	// return from override
	return (BOOL)g_currentHookChain->m_data.m_interger;
}

BOOL CBasePlayer_RemovePlayerItem(IReGameHook_CBasePlayer_RemovePlayerItem *chain, CBasePlayer *pthis, CBasePlayerItem *pItem)
{
	//BOOL ownresult = 0;		// return own for OVERRIDE
	BOOL origresult = 0;		// return by call original function

	if (callForward_Pre(RH_CBasePlayer_RemovePlayerItem, pthis->entindex(), pItem->entindex())) {
		origresult = chain->callNext(pItem);
	}

	if (callForward_Post(RH_CBasePlayer_RemovePlayerItem, pthis->entindex(), pItem->entindex())) {
		// return original
		return origresult;
	}

	// return from override
	return (BOOL)g_currentHookChain->m_data.m_interger;
}

int CBasePlayer_GiveAmmo(IReGameHook_CBasePlayer_GiveAmmo *chain, CBasePlayer *pthis, int iAmount, char *szName, int iMax)
{
	//int ownresult = 0;		// return own for OVERRIDE
	int origresult = 0;		// return by call original function

	if (callForward_Pre(RH_CBasePlayer_GiveAmmo, pthis->entindex(), iAmount, szName, iMax)) {
		origresult = chain->callNext(iAmount, szName, iMax);
	}

	if (callForward_Post(RH_CBasePlayer_GiveAmmo, pthis->entindex(), iAmount, szName, iMax)) {
		// return original
		return origresult;
	}

	// return from override
	return g_currentHookChain->m_data.m_interger;
}

void CBasePlayer_ResetMaxSpeed(IReGameHook_CBasePlayer_ResetMaxSpeed *chain, CBasePlayer *pthis)
{
	if (callVoidForward_Pre(RH_CBasePlayer_ResetMaxSpeed, pthis->entindex())) {
		chain->callNext();
	}

	callVoidForward_Post(RH_CBasePlayer_ResetMaxSpeed, pthis->entindex());
}

void CBasePlayer_Jump(IReGameHook_CBasePlayer_Jump *chain, CBasePlayer *pthis)
{
	if (callVoidForward_Pre(RH_CBasePlayer_Jump, pthis->entindex())) {
		chain->callNext();
	}

	callVoidForward_Post(RH_CBasePlayer_Jump, pthis->entindex());
}

void CBasePlayer_Duck(IReGameHook_CBasePlayer_Duck *chain, CBasePlayer *pthis)
{
	if (callVoidForward_Pre(RH_CBasePlayer_Duck, pthis->entindex())) {
		chain->callNext();
	}

	callVoidForward_Post(RH_CBasePlayer_Duck, pthis->entindex());
}

void CBasePlayer_PreThink(IReGameHook_CBasePlayer_PreThink *chain, CBasePlayer *pthis)
{
	if (callVoidForward_Pre(RH_CBasePlayer_PreThink, pthis->entindex())) {
		chain->callNext();
	}

	callVoidForward_Post(RH_CBasePlayer_PreThink, pthis->entindex());
}

void CBasePlayer_PostThink(IReGameHook_CBasePlayer_PostThink *chain, CBasePlayer *pthis)
{
	if (callVoidForward_Pre(RH_CBasePlayer_PostThink, pthis->entindex())) {
		chain->callNext();
	}

	callVoidForward_Post(RH_CBasePlayer_PostThink, pthis->entindex());
}

void CBasePlayer_UpdateClientData(IReGameHook_CBasePlayer_UpdateClientData *chain, CBasePlayer *pthis)
{
	if (callVoidForward_Pre(RH_CBasePlayer_UpdateClientData, pthis->entindex())) {
		chain->callNext();
	}

	callVoidForward_Post(RH_CBasePlayer_UpdateClientData, pthis->entindex());
}

void CBasePlayer_ImpulseCommands(IReGameHook_CBasePlayer_ImpulseCommands *chain, CBasePlayer *pthis)
{
	if (callVoidForward_Pre(RH_CBasePlayer_ImpulseCommands, pthis->entindex())) {
		chain->callNext();
	}

	callVoidForward_Post(RH_CBasePlayer_ImpulseCommands, pthis->entindex());
}

void CBasePlayer_RoundRespawn(IReGameHook_CBasePlayer_RoundRespawn *chain, CBasePlayer *pthis)
{
	if (callVoidForward_Pre(RH_CBasePlayer_RoundRespawn, pthis->entindex())) {
		chain->callNext();
	}

	callVoidForward_Post(RH_CBasePlayer_RoundRespawn, pthis->entindex());
}

void CBasePlayer_Blind(IReGameHook_CBasePlayer_Blind *chain, CBasePlayer *pthis, float flUntilTime, float flHoldTime, float flFadeTime, int iAlpha)
{
	if (callVoidForward_Pre(RH_CBasePlayer_Blind, pthis->entindex(), flUntilTime, flHoldTime, flFadeTime, iAlpha)) {
		chain->callNext(flUntilTime, flHoldTime, flFadeTime, iAlpha);
	}

	callVoidForward_Post(RH_CBasePlayer_Blind, pthis->entindex(), flUntilTime, flHoldTime, flFadeTime, iAlpha);
}

CBaseEntity *CBasePlayer_Observer_IsValidTarget(IReGameHook_CBasePlayer_Observer_IsValidTarget *chain, CBasePlayer *pthis, int iPlayerIndex, bool bSameTeam)
{
	//CBaseEntity *ownresult = nullptr;		// return own for OVERRIDE
	CBaseEntity *origresult = nullptr;		// return by call original function

	if (callForward_Pre(RH_CBasePlayer_Observer_IsValidTarget, pthis->entindex(), iPlayerIndex, bSameTeam)) {
		origresult = chain->callNext(iPlayerIndex, bSameTeam);
	}

	if (callForward_Post(RH_CBasePlayer_Observer_IsValidTarget, pthis->entindex(), iPlayerIndex, bSameTeam)) {
		// return original
		return origresult;
	}

	// return from override
	return g_currentHookChain->m_data.m_classptr;
}

int GetForceCamera(IReGameHook_GetForceCamera *chain, CBasePlayer *pObserver)
{
	//int ownresult = 0;		// return own for OVERRIDE
	int origresult = 0;		// return by call original function

	if (callForward_Pre(RH_GetForceCamera, pObserver->entindex())) {
		origresult = chain->callNext(pObserver);
	}

	if (callForward_Post(RH_GetForceCamera, pObserver->entindex())) {
		// return original
		return origresult;
	}

	// return from override
	return g_currentHookChain->m_data.m_interger;
}
