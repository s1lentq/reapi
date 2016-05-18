#include "precompiled.h"

edict_t* g_pEdicts;
int gmsgSendAudio, gmsgTeamScore, gmsgStatusIcon, gmsgArmorType;

void OnAmxxAttach()
{
	// initialize API
	api_cfg.Init();
}

bool OnMetaAttach()
{
	return true;
}

void OnMetaDetach()
{
	// clear all hooks?
	g_hookManager.clearHandlers();

	if (api_cfg.hasVTC()) {
		g_pVoiceTranscoderApi->ClientStartSpeak()->unregisterCallback(&ClientStartSpeak);
		g_pVoiceTranscoderApi->ClientStopSpeak()->unregisterCallback(&ClientStopSpeak);
	}

	if (api_cfg.hasReGameDLL()) {
		g_ReGameHookchains->InstallGameRules()->unregisterHook(&InstallGameRules);
	}
}

void ServerActivate_Post(edict_t *pEdictList, int edictCount, int clientMax)
{
	gmsgSendAudio = GET_USER_MSG_ID(PLID, "SendAudio", NULL);
	gmsgTeamScore = GET_USER_MSG_ID(PLID, "TeamScore", NULL);
	gmsgStatusIcon = GET_USER_MSG_ID(PLID, "StatusIcon", NULL);
	gmsgArmorType = GET_USER_MSG_ID(PLID, "ArmorType", NULL);

	SET_META_RESULT(MRES_IGNORED);
}

void ServerDeactivate_Post()
{
	api_cfg.ServerDeactivate();
	g_hookManager.clearHandlers();
	g_pFunctionTable->pfnSpawn = Spawn;

	SET_META_RESULT(MRES_IGNORED);
}

CGameRules *InstallGameRules(IReGameHook_InstallGameRules *chain)
{
	return g_pGameRules = chain->callNext();
}

int Spawn(edict_t* pEntity)
{
	g_pEdicts = g_engfuncs.pfnPEntityOfEntIndex(0);
	g_pFunctionTable->pfnSpawn = nullptr;

	RETURN_META_VALUE(MRES_IGNORED, 0);
}
