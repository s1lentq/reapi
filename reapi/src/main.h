#pragma once

extern edict_t* g_pEdicts;
extern int gmsgSendAudio;
extern int gmsgTeamScore;
extern int gmsgStatusIcon;
extern int gmsgArmorType;

void OnAmxxAttach();
bool OnMetaAttach();
void OnMetaDetach();

void ServerActivate_Post(edict_t *pEdictList, int edictCount, int clientMax);
void ServerDeactivate_Post();
int Spawn(edict_t* pEntity);

CGameRules *InstallGameRules(IReGameHook_InstallGameRules *chain);
