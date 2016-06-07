#pragma once

extern char g_szMapName[32];
extern edict_t* g_pEdicts;
extern playermove_t* g_pMove;
extern int gmsgSendAudio;
extern int gmsgTeamScore;
extern int gmsgStatusIcon;
extern int gmsgArmorType;
extern int gmsgTeamInfo;
extern int gmsgItemStatus;

void OnAmxxAttach();
bool OnMetaAttach();
void OnMetaDetach();

void ServerActivate_Post(edict_t *pEdictList, int edictCount, int clientMax);
void ServerDeactivate_Post();
int DispatchSpawn(edict_t* pEntity);
void ResetGlobalState();

CGameRules *InstallGameRules(IReGameHook_InstallGameRules *chain);
