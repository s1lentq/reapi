#pragma once

#define PARAMS_COUNT			(params[0] / sizeof(cell))
#define PARAMS_REQUIRE(x)		if (params[0] != x * sizeof(cell)) { MF_LogError(amx, AMX_ERR_NATIVE, "Invalid parameters count in %s", __FUNCTION__); return nullptr; }
#define NATIVE_MEMBER_REQUIRE(a,x)	if (!api_cfg.has##x()) { MF_LogError(amx, AMX_ERR_NATIVE, "Member (%s) is not available, required %s", memberlist[a]->member_name, #x); return 0; }

extern AMX_NATIVE_INFO Member_Natives[];

void RegisterNatives();
