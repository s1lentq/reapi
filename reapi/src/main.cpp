#include "precompiled.h"

edict_t* g_pEdicts;
char g_szMapName[32];
int gmsgSendAudio, gmsgTeamScore, gmsgStatusIcon, gmsgArmorType, gmsgTeamInfo, gmsgItemStatus;

struct
{
	const char* pszName;
	int& id;
} g_RegUserMsg[] = {
	{ "SendAudio",  gmsgSendAudio },
	{ "TeamScore",  gmsgTeamScore },
	{ "StatusIcon", gmsgStatusIcon },
	{ "ArmorType",  gmsgArmorType },
	{ "TeamInfo",   gmsgTeamInfo },
	{ "ItemStatus", gmsgItemStatus },
};

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
	for (auto& msg : g_RegUserMsg) {
		msg.id = GET_USER_MSG_ID(PLID, msg.pszName, NULL);
	}

	SET_META_RESULT(MRES_IGNORED);
}

void ServerDeactivate_Post()
{
	api_cfg.ServerDeactivate();
	g_hookManager.clearHandlers();
	g_pFunctionTable->pfnSpawn = DispatchSpawn;

	SET_META_RESULT(MRES_IGNORED);
}

CGameRules *InstallGameRules(IReGameHook_InstallGameRules *chain)
{
	return g_pGameRules = chain->callNext();
}

int DispatchSpawn(edict_t* pEntity)
{
	// save true mapname
	strncpy(g_szMapName, STRING(gpGlobals->mapname), sizeof(g_szMapName) - 1);
	g_szMapName[sizeof(g_szMapName) - 1] = '\0';

	g_pEdicts = g_engfuncs.pfnPEntityOfEntIndex(0);
	g_pFunctionTable->pfnSpawn = nullptr;
	RETURN_META_VALUE(MRES_IGNORED, 0);
}

void ResetGlobalState()
{
	// restore mapname
	if (strcmp(g_RehldsData->GetName(), g_szMapName) != 0) {
		g_RehldsData->SetName(g_szMapName);
		g_pFunctionTable->pfnResetGlobalState = nullptr;
	}

	SET_META_RESULT(MRES_IGNORED);
}
