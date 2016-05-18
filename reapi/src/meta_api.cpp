#include "precompiled.h"
#include "appversion.h"

meta_globals_t *gpMetaGlobals;
gamedll_funcs_t *gpGamedllFuncs;
mutil_funcs_t *gpMetaUtilFuncs;
enginefuncs_t *g_pengfuncsTable;

plugin_info_t Plugin_info =
{
	META_INTERFACE_VERSION,			// ifvers
	"ReAPI",				// name
	APP_VERSION_STRD,					// version
	APP_VERSION_YMD_STR,				// date
	"Asmodai & s1lent",				// author
	"https://github.com/s1lentq/reapi/",	// url
	"ReAPI",				// logtag, all caps please
	PT_ANYTIME,				// (when) loadable
	PT_NEVER,				// (when) unloadable
};

C_DLLEXPORT int Meta_Query(char *interfaceVersion, plugin_info_t* *plinfo, mutil_funcs_t *pMetaUtilFuncs)
{
	*plinfo = &Plugin_info;
	gpMetaUtilFuncs = pMetaUtilFuncs;
	return TRUE;
}

// Must provide at least one of these..
META_FUNCTIONS gMetaFunctionTable =
{
	NULL,			// pfnGetEntityAPI		HL SDK; called before game DLL
	NULL,			// pfnGetEntityAPI_Post		META; called after game DLL
	GetEntityAPI2,			// pfnGetEntityAPI2		HL SDK2; called before game DLL
	GetEntityAPI2_Post,			// pfnGetEntityAPI2_Post	META; called after game DLL
	NULL,			// pfnGetNewDLLFunctions	HL SDK2; called before game DLL
	NULL,			// pfnGetNewDLLFunctions_Post	META; called after game DLL
	NULL,			// pfnGetEngineFunctions	META; called before HL engine
	NULL,			// pfnGetEngineFunctions_Post	META; called after HL engine
};

C_DLLEXPORT int Meta_Attach(PLUG_LOADTIME now, META_FUNCTIONS *pFunctionTable, meta_globals_t *pMGlobals, gamedll_funcs_t *pGamedllFuncs)
{
	gpMetaGlobals = pMGlobals;
	gpGamedllFuncs = pGamedllFuncs;

	if (!OnMetaAttach())
	{
		return FALSE;
	}

	GET_HOOK_TABLES(PLID, &g_pengfuncsTable, nullptr, nullptr);
	memcpy(pFunctionTable, &gMetaFunctionTable, sizeof(META_FUNCTIONS));
	return TRUE;
}

C_DLLEXPORT int Meta_Detach(PLUG_LOADTIME now, PL_UNLOAD_REASON reason)
{
	OnMetaDetach();
	return TRUE;
}
