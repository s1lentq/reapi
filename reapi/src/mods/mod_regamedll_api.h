#pragma once

extern IReGameApi *g_ReGameApi;
extern const ReGameFuncs_t *g_ReGameFuncs;
extern IReGameHookchains *g_ReGameHookchains;
extern CHalfLifeMultiplay **g_pCSGameRules;

extern bool RegamedllApi_Init();
