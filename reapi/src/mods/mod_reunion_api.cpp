#include "precompiled.h"

IReunionApi* g_ReunionApi;

bool ReunionApi_Init()
{
	if (!g_RehldsApi)
		return false;

	g_ReunionApi = (IReunionApi *)g_RehldsApi->GetFuncs()->GetPluginApi("reunion");

	if (!g_ReunionApi)
		return false;

	if (g_ReunionApi->version_major != REUNION_API_VERSION_MAJOR) {
		UTIL_ServerPrint("[%s]: Reunion Api major version mismatch; expected %d, real %d\n", Plugin_info.logtag, REUNION_API_VERSION_MAJOR, g_ReunionApi->version_major);
		return false;
	}

	if (g_ReunionApi->version_minor < REUNION_API_VERSION_MINOR) {
		UTIL_ServerPrint("[%s]: Reunion Api minor version mismatch; expected at least %d, real %d\n", Plugin_info.logtag, REUNION_API_VERSION_MINOR, g_ReunionApi->version_minor);
		return false;
	}

	return true;
}
