#include "precompiled.h"

IRehldsApi* g_RehldsApi;
const RehldsFuncs_t* g_RehldsFuncs;
IRehldsServerData* g_RehldsData;
IRehldsHookchains* g_RehldsHookchains;
IRehldsServerStatic* g_RehldsSvs;

bool RehldsApi_Init()
{
#ifdef WIN32
	CSysModule* engineModule = Sys_LoadModule("swds.dll");
#else
	CSysModule* engineModule = Sys_LoadModule("engine_i486.so");
#endif

	if (!engineModule)
		return false;

	CreateInterfaceFn ifaceFactory = Sys_GetFactory(engineModule);
	if (!ifaceFactory)
		return false;

	int retCode = 0;
	g_RehldsApi = (IRehldsApi*)ifaceFactory(VREHLDS_HLDS_API_VERSION, &retCode);

	if (!g_RehldsApi)
		return false;

	int majorVersion = g_RehldsApi->GetMajorVersion();
	int minorVersion = g_RehldsApi->GetMinorVersion();

	if (majorVersion != REHLDS_API_VERSION_MAJOR)
	{
		UTIL_ServerPrint("[%s]: ReHLDS Api major version mismatch; expected %d, real %d\n", Plugin_info.logtag, REHLDS_API_VERSION_MAJOR, majorVersion);
		return false;
	}

	if (minorVersion < REHLDS_API_VERSION_MINOR)
	{
		UTIL_ServerPrint("[%s]: ReHLDS Api minor version mismatch; expected at least %d, real %d\n", Plugin_info.logtag, REHLDS_API_VERSION_MINOR, minorVersion);
		return false;
	}

	g_RehldsFuncs = g_RehldsApi->GetFuncs();
	g_RehldsData = g_RehldsApi->GetServerData();
	g_RehldsHookchains = g_RehldsApi->GetHookchains();
	g_RehldsSvs = g_RehldsApi->GetServerStatic();

	return true;
}
