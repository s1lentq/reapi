#include "precompiled.h"

int regfunc::current_cell = 1;

#define ENG(h) { {}, {}, #h, "ReHLDS", [](){ return api_cfg.hasReHLDS(); }, ((!(RH_##h & (MAX_REGION_RANGE - 1)) ? regfunc::current_cell = 1, true : false) || (RH_##h & (MAX_REGION_RANGE - 1)) == regfunc::current_cell++) ? regfunc(h) : regfunc(#h " doesn't match hook definition"), [](){ g_RehldsHookchains->##h##()->registerHook(&##h); }, [](){ g_RehldsHookchains->##h##()->unregisterHook(&##h); }}
hook_t hooklist_engine[] = {
	ENG(SV_StartSound),
	ENG(SV_DropClient),
	ENG(SV_ActivateServer),
	ENG(Cvar_DirectSet)
};

#define DLL(h) { {}, {}, #h, "ReGameDLL", [](){ return api_cfg.hasReGameDLL(); }, ((!(RH_##h & (MAX_REGION_RANGE - 1)) ? regfunc::current_cell = 1, true : false) || (RH_##h & (MAX_REGION_RANGE - 1)) == regfunc::current_cell++) ? regfunc(h) : regfunc(#h " doesn't match hook definition"), [](){ g_ReGameHookchains->##h##()->registerHook(&##h); }, [](){ g_ReGameHookchains->##h##()->unregisterHook(&##h); }}
hook_t hooklist_gamedll[] = {
	DLL(GetForceCamera),
	DLL(PlayerBlind),
	DLL(RadiusFlash_TraceLine)
};

hook_t hooklist_animating[] = {
	DLL(CBaseAnimating_ResetSequenceInfo)
};

hook_t hooklist_player[] = {
	DLL(CBasePlayer_Spawn),
	DLL(CBasePlayer_Precache),
	DLL(CBasePlayer_ObjectCaps),
	DLL(CBasePlayer_Classify),
	DLL(CBasePlayer_TraceAttack),
	DLL(CBasePlayer_TakeDamage),
	DLL(CBasePlayer_TakeHealth),
	DLL(CBasePlayer_Killed),
	DLL(CBasePlayer_AddPoints),
	DLL(CBasePlayer_AddPointsToTeam),
	DLL(CBasePlayer_AddPlayerItem),
	DLL(CBasePlayer_RemovePlayerItem),
	DLL(CBasePlayer_GiveAmmo),
	DLL(CBasePlayer_ResetMaxSpeed),
	DLL(CBasePlayer_Jump),
	DLL(CBasePlayer_Duck),
	DLL(CBasePlayer_PreThink),
	DLL(CBasePlayer_PostThink),
	DLL(CBasePlayer_UpdateClientData),
	DLL(CBasePlayer_ImpulseCommands),
	DLL(CBasePlayer_RoundRespawn),
	DLL(CBasePlayer_Blind),

	DLL(CBasePlayer_Observer_IsValidTarget),
	DLL(CBasePlayer_SetAnimation),
	DLL(CBasePlayer_GiveDefaultItems),
	DLL(CBasePlayer_GiveNamedItem),
	DLL(CBasePlayer_AddAccount),
	DLL(CBasePlayer_GiveShield),
};

hook_t* hooklist_t::getHookSafe(size_t hook)
{
	#define CASE(h)	case ht_##h: if (index < arraysize(hooklist_##h)) return &hooklist_##h[index]; else break;

	const auto table = hooks_tables_e(hook / MAX_REGION_RANGE);
	const auto index = hook & (MAX_REGION_RANGE - 1);

	switch (table) {
		CASE(engine)
		CASE(gamedll)
		CASE(animating)
		CASE(player)
	}

	return nullptr;
}
