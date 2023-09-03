#include "precompiled.h"

edict_t* g_pEdicts;
playermove_t* g_pMove;
char g_szMapName[32] = "";
int gmsgSendAudio, gmsgStatusIcon, gmsgArmorType, gmsgItemStatus, gmsgBarTime, gmsgBarTime2;

struct
{
	const char* pszName;
	int& id;
} g_RegUserMsg[] = {
	{ "SendAudio",  gmsgSendAudio },
	{ "StatusIcon", gmsgStatusIcon },
	{ "ArmorType",  gmsgArmorType },
	{ "ItemStatus", gmsgItemStatus },
	{ "BarTime",    gmsgBarTime },
	{ "BarTime2",   gmsgBarTime2 },
};

void OnAmxxAttach()
{
	// initialize API
	api_cfg.Init();
	g_pEdicts = g_engfuncs.pfnPEntityOfEntIndex(0);

	// If AMXX_Attach been called in a first the event Spawn
	if (g_pEdicts)
	{
		// save true mapname
		strncpy(g_szMapName, STRING(gpGlobals->mapname), sizeof(g_szMapName) - 1);
		g_szMapName[sizeof(g_szMapName) - 1] = '\0';
	}
}

bool OnMetaAttach()
{
	return true;
}

void OnMetaDetach()
{
	// clear all hooks?
	g_hookManager.Clear();
	g_queryFileManager.Clear();

	if (api_cfg.hasVTC()) {
		g_pVoiceTranscoderApi->OnClientStartSpeak() -= OnClientStartSpeak;
		g_pVoiceTranscoderApi->OnClientStopSpeak() -= OnClientStopSpeak;
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
	g_pEdicts = nullptr;
	api_cfg.ServerDeactivate();
	g_hookManager.Clear();
	g_queryFileManager.Clear();
	EntityCallbackDispatcher().DeleteAllCallbacks();

	g_pFunctionTable->pfnSpawn = DispatchSpawn;
	g_pFunctionTable->pfnKeyValue = KeyValue;

	SET_META_RESULT(MRES_IGNORED);
}

void KeyValue(edict_t *pentKeyvalue, KeyValueData *pkvd)
{
	// get the first edict worldspawn
	if (FClassnameIs(pentKeyvalue, "worldspawn"))
	{
		// save true mapname
		strncpy(g_szMapName, STRING(gpGlobals->mapname), sizeof(g_szMapName) - 1);
		g_szMapName[sizeof(g_szMapName) - 1] = '\0';

		g_pEdicts = pentKeyvalue;
		g_pFunctionTable->pfnKeyValue = nullptr;
	}

	SET_META_RESULT(MRES_IGNORED);
}

CGameRules *InstallGameRules(IReGameHook_InstallGameRules *chain)
{
	auto gamerules = chain->callNext();

	// Safe check CGameRules API interface version
	if (!g_ReGameApi->BGetIGameRules(GAMERULES_API_INTERFACE_VERSION))
	{
		api_cfg.FailedReGameDllAPI();
		UTIL_ServerPrint("[%s]: Interface CGameRules API version '%s' not found.\n", Plugin_info.logtag, GAMERULES_API_INTERFACE_VERSION);
	}
	else
	{
		g_pGameRules = gamerules;
	}

	return gamerules;
}

int DispatchSpawn(edict_t *pEntity)
{
	g_pEdicts = g_engfuncs.pfnPEntityOfEntIndex(0);
	if (api_cfg.hasReGameDLL()) {
		g_pMove = g_ReGameApi->GetPlayerMove();
	}

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

void OnFreeEntPrivateData(edict_t *pEdict)
{
	CBaseEntity *pEntity = getPrivate<CBaseEntity>(pEdict);
	if (!pEntity){
		return;
	}

	EntityCallbackDispatcher().DeleteExistingCallbacks(pEntity);
	SET_META_RESULT(MRES_IGNORED);
}
