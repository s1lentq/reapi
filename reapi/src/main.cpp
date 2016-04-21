#include "precompiled.h"

edict_t* g_pEdicts;

bool OnMetaAttach()
{
	// initialize API
	if (!api_cfg.Init())
		return false;

	return true;
}

void OnMetaDetach()
{
	// clear all hooks?
	g_hookManager.clearHandlers();
}

void ServerActivate(edict_t *pEdictList, int edictCount, int clientMax)
{
	g_pEdicts = pEdictList;
	api_cfg.ServerActivate();

	SET_META_RESULT(MRES_IGNORED);
}

void ServerDeactivate_Post()
{
	api_cfg.ServerActivate();
	g_hookManager.clearHandlers();

	SET_META_RESULT(MRES_IGNORED);
}
