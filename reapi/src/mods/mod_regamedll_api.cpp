#include "precompiled.h"

IReGameApi *g_ReGameApi;
const ReGameFuncs_t *g_ReGameFuncs;
IReGameHookchains *g_ReGameHookchains;
CGameRules *g_pGameRules = nullptr;

bool RegamedllApi_Init()
{
	const char *szGameDLLModule = GET_GAME_INFO(PLID, GINFO_DLL_FULLPATH);
	if (!szGameDLLModule)
		return false;

	CSysModule *gameModule = Sys_LoadModule(szGameDLLModule);
	if (!gameModule)
		return false;

	CreateInterfaceFn ifaceFactory = Sys_GetFactory(gameModule);
	if (!ifaceFactory)
		return false;

	int retCode = 0;
	g_ReGameApi = (IReGameApi *)ifaceFactory(VRE_GAMEDLL_API_VERSION, &retCode);
	if (!g_ReGameApi)
	{
		return false;
	}

	int majorVersion = g_ReGameApi->GetMajorVersion();
	int minorVersion = g_ReGameApi->GetMinorVersion();

	if (majorVersion != REGAMEDLL_API_VERSION_MAJOR)
	{
		UTIL_ServerPrint("[%s]: ReGameDLL API major version mismatch; expected %d, real %d\n", Plugin_info.logtag, REGAMEDLL_API_VERSION_MAJOR, majorVersion);

		// need to notify that it is necessary to update the ReGameDLL.
		if (majorVersion < REGAMEDLL_API_VERSION_MAJOR)
		{
			UTIL_ServerPrint("[%s]: Please update the ReGameDLL up to a major version API >= %d\n", Plugin_info.logtag, REGAMEDLL_API_VERSION_MAJOR);
		}

		// need to notify that it is necessary to update the module.
		else if (majorVersion > REGAMEDLL_API_VERSION_MAJOR)
		{
			UTIL_ServerPrint("[%s]: Please update the %s up to a major version API >= %d\n", Plugin_info.logtag, Plugin_info.logtag, majorVersion);
		}

		return false;
	}

	if (minorVersion < REGAMEDLL_API_VERSION_MINOR)
	{
		UTIL_ServerPrint("[%s]: ReGameDLL API minor version mismatch; expected at least %d, real %d\n", Plugin_info.logtag, REGAMEDLL_API_VERSION_MINOR, minorVersion);
		UTIL_ServerPrint("[%s]: Please update the ReGameDLL up to a minor version API >= %d\n", Plugin_info.logtag, REGAMEDLL_API_VERSION_MINOR);
		return false;
	}

	g_ReGameFuncs = g_ReGameApi->GetFuncs();
	g_ReGameHookchains = g_ReGameApi->GetHookchains();

	return true;
}