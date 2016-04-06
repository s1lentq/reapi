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

void ServerActivate_Post(edict_t *pEdictList, int edictCount, int clientMax)
{
	g_pEdicts = pEdictList;
	RETURN_META(MRES_IGNORED);
}

void ServerDeactivate_Post()
{
	g_hookManager.clearHandlers();
	RETURN_META(MRES_IGNORED);
}
