#include "precompiled.h"

IRecheckerApi *g_RecheckerApi;
IRecheckerHookchains *g_RecheckerHookchains;
const RecheckerFuncs_t *g_RecheckerFuncs;

bool RecheckerApi_Init()
{
	if (!g_RehldsApi)
		return false;

	g_RecheckerApi = (IRecheckerApi *)g_RehldsApi->GetFuncs()->GetPluginApi("rechecker");

	if (!g_RecheckerApi)
		return false;

	if (g_RecheckerApi->GetMajorVersion() != RECHECKER_API_VERSION_MAJOR)
	{
		UTIL_ServerPrint("[%s]: Rechecker API major version mismatch; expected %d, real %d\n", Plugin_info.logtag, RECHECKER_API_VERSION_MAJOR, g_RecheckerApi->GetMajorVersion());

		// need to notify that it is necessary to update the Rechecker.
		if (g_RecheckerApi->GetMajorVersion() < RECHECKER_API_VERSION_MAJOR)
		{
			UTIL_ServerPrint("[%s]: Please update the Rechecker up to a major version API >= %d\n", Plugin_info.logtag, RECHECKER_API_VERSION_MAJOR);
		}

		// need to notify that it is necessary to update the module.
		else if (g_RecheckerApi->GetMajorVersion() > RECHECKER_API_VERSION_MAJOR)
		{
			UTIL_ServerPrint("[%s]: Please update the %s up to a major version API >= %d\n", Plugin_info.logtag, Plugin_info.logtag, g_RecheckerApi->GetMajorVersion());
		}

		return false;
	}

	if (g_RecheckerApi->GetMinorVersion() < RECHECKER_API_VERSION_MINOR)
	{
		UTIL_ServerPrint("[%s]: Rechecker API minor version mismatch; expected at least %d, real %d\n", Plugin_info.logtag, RECHECKER_API_VERSION_MINOR, g_RecheckerApi->GetMinorVersion());
		UTIL_ServerPrint("[%s]: Please update the Rechecker up to a minor version API >= %d\n", Plugin_info.logtag, RECHECKER_API_VERSION_MINOR);
		return false;
	}

	g_RecheckerFuncs = g_RecheckerApi->GetFuncs();
	g_RecheckerHookchains = g_RecheckerApi->GetHookchains();

	return true;
}
