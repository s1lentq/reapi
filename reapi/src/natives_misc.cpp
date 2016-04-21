#include "precompiled.h"

// native rg_set_animation(index, PLAYER_ANIM:playerAnim);
static cell AMX_NATIVE_CALL rg_set_animation(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_anim };

	ICSPlayer *pPlayer = g_ReGameFuncs->INDEX_TO_CSPLAYER(params[arg_index]);
	if (pPlayer == nullptr || !pPlayer->IsConnected()) {
		return FALSE;
	}

	pPlayer->SetAnimation(static_cast<PLAYER_ANIM>(params[arg_anim]));
	return TRUE;
}

// native rg_add_account(index, amount, bool:bTrackChange = true);
static cell AMX_NATIVE_CALL rg_add_account(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_amount, arg_track_change };

	ICSPlayer *pPlayer = g_ReGameFuncs->INDEX_TO_CSPLAYER(params[arg_index]);
	if (pPlayer == nullptr || !pPlayer->IsConnected()) {
		return FALSE;
	}

	pPlayer->AddAccount(params[arg_amount], params[arg_track_change] != 0);
	return TRUE;
}

// native rg_give_item(index, const pszName[]);
static cell AMX_NATIVE_CALL rg_give_item(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_item };

	ICSPlayer *pPlayer = g_ReGameFuncs->INDEX_TO_CSPLAYER(params[arg_index]);

	if (pPlayer == nullptr || !pPlayer->IsConnected()) {
		return FALSE;
	}

	const char *itemName = getAmxString(amx, params[arg_item]);
	pPlayer->GiveNamedItem(itemName);
	return TRUE;
}

// native rg_give_default_items(index);
static cell AMX_NATIVE_CALL rg_give_default_items(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };

	ICSPlayer *pPlayer = g_ReGameFuncs->INDEX_TO_CSPLAYER(params[arg_index]);
	if (pPlayer == nullptr || !pPlayer->IsConnected()) {
		return FALSE;
	}

	pPlayer->GiveDefaultItems();
	return TRUE;
}

// native rg_give_shield(index, bool:bDeploy = true);
static cell AMX_NATIVE_CALL rg_give_shield(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_deploy };

	ICSPlayer *pPlayer = g_ReGameFuncs->INDEX_TO_CSPLAYER(params[arg_index]);
	if (pPlayer == nullptr || !pPlayer->IsConnected()) {
		return FALSE;
	}

	pPlayer->GiveShield(params[arg_deploy] != 0);
	return TRUE;
}

// native rg_dmg_radius(Float:vecSrc[3], inflictor, attacker, Float:flDamage, Float:flRadius, iClassIgnore, bitsDamageType);
static cell AMX_NATIVE_CALL rg_dmg_radius(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_vec, arg_inflictor, arg_attacker, arg_damage, arg_radius, arg_ignore_class, arg_dmg_type };

	cell *pSrc = getAmxAddr(amx, params[arg_vec]);

	entvars_t *pevInflictor = VARS(INDEXENT(params[arg_inflictor]));
	entvars_t *pevAttacker = VARS(INDEXENT(params[arg_attacker]));

	Vector vecSrc(*(float *)&pSrc[0], *(float *)&pSrc[1], *(float *)&pSrc[2]);
	g_ReGameFuncs->RadiusDamage(vecSrc, pevInflictor, pevAttacker, *(float *)&params[arg_damage], *(float *)&params[arg_radius], params[arg_ignore_class], params[arg_dmg_type]);
	return TRUE;
}

// native rg_multidmg_clear();
static cell AMX_NATIVE_CALL rg_multidmg_clear(AMX *amx, cell *params)
{
	g_ReGameFuncs->ClearMultiDamage();
	return TRUE;
}

// native rg_multidmg_apply(inflictor, attacker);
static cell AMX_NATIVE_CALL rg_multidmg_apply(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_inflictor, arg_attacker };

	entvars_t *pevInflictor = VARS(INDEXENT(params[arg_inflictor]));
	entvars_t *pevAttacker = VARS(INDEXENT(params[arg_attacker]));

	g_ReGameFuncs->ApplyMultiDamage(pevInflictor, pevAttacker);
	return TRUE;
}

// native rg_multidmg_add(inflictor, victim, Float:flDamage, bitsDamageType);
static cell AMX_NATIVE_CALL rg_multidmg_add(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_inflictor, arg_victim, arg_damage, arg_dmg_type };

	entvars_t *pevInflictor = VARS(INDEXENT(params[arg_inflictor]));
	CBaseEntity *pVictim = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_inflictor]);

	if (pVictim == nullptr) {
		return FALSE;
	}

	g_ReGameFuncs->AddMultiDamage(pevInflictor, pVictim, *(float *)&params[arg_damage], params[arg_dmg_type]);
	return TRUE;
}

// native rg_fire_bullets(inflictor, attacker, shots, Float:vecSrc[3], Float:vecDirShooting[3], Float::vecSpread[3], Float:flDistance, iBulletType, iTracerFreq, iDamage);
static cell AMX_NATIVE_CALL rg_fire_bullets(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_inflictor, arg_attacker, arg_shots, arg_vecSrc, arg_dir, arg_spread, arg_dist, arg_bullet_type, arg_tracefrq, arg_dmg };

	ICSEntity *pInflictor = g_ReGameFuncs->INDEX_TO_CSENTITY(params[arg_inflictor]);

	cell *pSrc = getAmxAddr(amx, params[arg_vecSrc]);
	Vector vecSrc(*(float *)&pSrc[0], *(float *)&pSrc[1], *(float *)&pSrc[2]);

	cell *pDir = getAmxAddr(amx, params[arg_dir]);
	Vector vecDirShooting(*(float *)&pDir[0], *(float *)&pDir[1], *(float *)&pDir[2]);

	cell *pSpread = getAmxAddr(amx, params[arg_spread]);
	Vector vecSpread(*(float *)&pSpread[0], *(float *)&pSpread[1], *(float *)&pSpread[2]);

	entvars_t *pevAttacker = VARS(INDEXENT(params[arg_attacker]));
	pInflictor->FireBullets(params[arg_shots], vecSrc, vecDirShooting, vecSpread, *(float *)&params[arg_dist], params[arg_bullet_type], params[arg_tracefrq], params[arg_dmg], pevAttacker);
	return TRUE;
}

// native Float:[3] rg_fire_bullets3(inflictor, attacker, Float:vecSrc[3], Float:vecDirShooting[3], Float:vecSpread, Float:flDistance, iPenetration, iBulletType, iDamage, Float:flRangeModifier, bool:bPistol, shared_rand);
static cell AMX_NATIVE_CALL rg_fire_bullets3(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_inflictor, arg_attacker, arg_vecSrc, arg_dir, arg_spread, arg_dist, arg_penetration, arg_bullet_type, arg_dmg, arg_range_mod, arg_pistol, arg_rand, arg_out };

	ICSEntity *pInflictor = g_ReGameFuncs->INDEX_TO_CSENTITY(params[arg_inflictor]);

	cell *pSrc = getAmxAddr(amx, params[arg_vecSrc]);
	Vector vecSrc(*(float *)&pSrc[0], *(float *)&pSrc[1], *(float *)&pSrc[2]);

	cell *pDir = getAmxAddr(amx, params[arg_dir]);
	Vector vecDirShooting(*(float *)&pDir[0], *(float *)&pDir[1], *(float *)&pDir[2]);

	entvars_t *pevAttacker = VARS(INDEXENT(params[arg_attacker]));

	Vector *pOut = (Vector *)getAmxAddr(amx, params[arg_out]);
	*pOut = pInflictor->FireBullets3(vecSrc, vecDirShooting, *(float *)&params[arg_spread], *(float *)&params[arg_dist], params[arg_penetration], params[arg_bullet_type], params[arg_dmg], *(float *)&params[arg_range_mod], pevAttacker, params[arg_pistol] != 0, params[arg_rand]);

	return TRUE;
}

AMX_NATIVE_INFO Misc_Natives[] =
{
	{ "rg_set_animation", rg_set_animation },
	{ "rg_add_account", rg_add_account },
	{ "rg_give_item", rg_give_item },
	{ "rg_give_default_items", rg_give_default_items },
	{ "rg_give_shield", rg_give_shield },

	{ "rg_dmg_radius", rg_dmg_radius },
	{ "rg_multidmg_clear", rg_multidmg_clear },
	{ "rg_multidmg_apply", rg_multidmg_apply },
	{ "rg_multidmg_add", rg_multidmg_add },

	{ "rg_fire_bullets", rg_fire_bullets },
	{ "rg_fire_bullets3", rg_fire_bullets3 },

	{ nullptr, nullptr }
};

void RegisterNatives_Misc()
{
	g_amxxapi.AddNatives(Misc_Natives);
}
