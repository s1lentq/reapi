#include "precompiled.h"

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

void ServerDeactivate_Post()
{
	g_hookManager.clearHandlers();
}
