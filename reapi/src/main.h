#pragma once

extern edict_t* g_pEdicts;
extern int gmsgSendAudio;
extern int gmsgTeamScore;

void OnAmxxAttach();
bool OnMetaAttach();
void OnMetaDetach();

void ServerActivate_Post(edict_t *pEdictList, int edictCount, int clientMax);
void ServerDeactivate_Post();
