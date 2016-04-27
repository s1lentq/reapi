#include "precompiled.h"

edict_t* g_pEdicts;
int gmsgSendAudio;
int gmsgTeamScore;

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
}

void ServerActivate_Post(edict_t *pEdictList, int edictCount, int clientMax)
{
	g_pEdicts = pEdictList;
	gmsgSendAudio = GET_USER_MSG_ID(PLID, "SendAudio", NULL);
	gmsgTeamScore = GET_USER_MSG_ID(PLID, "TeamScore", NULL);
	api_cfg.ServerActivate();

	SET_META_RESULT(MRES_IGNORED);
}

void ServerDeactivate_Post()
{
	api_cfg.ServerActivate();
	g_hookManager.clearHandlers();

	SET_META_RESULT(MRES_IGNORED);
}
