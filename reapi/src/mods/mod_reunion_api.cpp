#include "precompiled.h"

IReunionApi* g_ReunionApi;

bool ReunionApi_Init()
{
	if (g_RehldsApi == nullptr)
		return false;

	g_ReunionApi = (IReunionApi *)g_RehldsApi->GetFuncs()->GetPluginApi("reunion");

	if (g_ReunionApi == nullptr) {
		return false;
	}

	if (g_ReunionApi->version_major != REUNION_API_VERSION_MAJOR) {
		UTIL_LogPrintf("[%s]: Reunion Api major version mismatch; expected %d, real %d\n", Plugin_info.logtag, REUNION_API_VERSION_MAJOR, g_ReunionApi->version_major);
		return false;
	}

	if (g_ReunionApi->version_minor < REUNION_API_VERSION_MINOR) {
		UTIL_LogPrintf("[%s]: Reunion Api minor version mismatch; expected at least %d, real %d\n", Plugin_info.logtag, REUNION_API_VERSION_MINOR, g_ReunionApi->version_minor);
		return false;
	}

	return true;
}
