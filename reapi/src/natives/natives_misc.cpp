#include "precompiled.h"

/*
* Assign the number of the player animations.
*
* @param index		Client index
* @param playerAnim	Specific the number animation
*
* @noreturn
*
* native rg_set_animation(index, PLAYER_ANIM:playerAnim);
*/
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

/*
* Adds money to player's account.
*
* @param index		Client index
* @param amount		The amount of money
* @param bTrackChange	If the bTrackChange is 1, the amount of money added will also be displayed.
*
* @noreturn
*
* native rg_add_account(index, amount, bool:bTrackChange = true);
*/
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

/*
* Gives item to player
*
* @param index		Client index
* @param pszName	Classname item
*
* @noreturn
*
* native rg_give_item(index, const pszName[]);
*/
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

/*
* Give the player default items
*
* @param index		Client index
*
* @noreturn
*
* native rg_give_default_items(index);
*/
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

/*
* Give the player shield
*
* @param index		Client index
* @param bDeploy	to get shield from holster
*
* @noreturn
*
* native rg_give_shield(index, bool:bDeploy = true);
*/
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

/*
* Inflicts in a radius from the source position.
*
* @param vecSrc		The source position
* @param inflictor	Inflictor is the entity that caused the damage (such as a gun)
* @param attacker	Attacker is the entity that tirggered the damage (such as the gun's owner).
* @param flDamage	The amount of damage
* @param flRadius	Radius damage
* @param iClassIgnore	To specify classes that are immune to damage.
* @param bitsDamageType	Damage type DMG_*
*
* @noreturn
*
* native rg_dmg_radius(Float:vecSrc[3], inflictor, attacker, Float:flDamage, Float:flRadius, iClassIgnore, bitsDamageType);
*/
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

/*
* Resets the global multi damage accumulator
*
* @noreturn
*
* native rg_multidmg_clear();
*/
static cell AMX_NATIVE_CALL rg_multidmg_clear(AMX *amx, cell *params)
{
	g_ReGameFuncs->ClearMultiDamage();
	return TRUE;
}

/*
* inflicts contents of global multi damage register on victim
*
* @param inflictor	Inflictor is the entity that caused the damage (such as a gun)
* @param attacker	Attacker is the entity that tirggered the damage (such as the gun's owner).
*
* @noreturn
*
* native rg_multidmg_apply(inflictor, attacker);
*/
static cell AMX_NATIVE_CALL rg_multidmg_apply(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_inflictor, arg_attacker };

	entvars_t *pevInflictor = VARS(INDEXENT(params[arg_inflictor]));
	entvars_t *pevAttacker = VARS(INDEXENT(params[arg_attacker]));

	g_ReGameFuncs->ApplyMultiDamage(pevInflictor, pevAttacker);
	return TRUE;
}

/*
* Adds damage the accumulator
*
* @param inflictor	Inflictor is the entity that caused the damage (such as a gun)
* @param victim		A victim that takes damage
* @param flDamage	The amount of damage
* @param bitsDamageType	Damage type DMG_*
*
* @noreturn
*
* native rg_multidmg_add(inflictor, victim, Float:flDamage, bitsDamageType);
*/
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

/*
* Fire bullets from entity
*
* @param inflictor		Inflictor is the entity that caused the damage (such as a gun)
* @param attacker		Attacker is the entity that tirggered the damage (such as the gun's owner).
* @param shots			The number of shots
* @param vecSrc			The source position of the barrel
* @param vecDirShooting		Direction shooting
* @param vecSpread		Spread
* @param flDistance		Max shot distance
* @param iBulletType		Bullet type
* @param iTracerFreq		Tracer frequancy
* @param iDamage		Damage amount
*
* @noreturn
*
* native rg_fire_bullets(inflictor, attacker, shots, Float:vecSrc[3], Float:vecDirShooting[3], Float::vecSpread[3], Float:flDistance, iBulletType, iTracerFreq, iDamage);
*/
static cell AMX_NATIVE_CALL rg_fire_bullets(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_inflictor, arg_attacker, arg_shots, arg_vecSrc, arg_dir, arg_spread, arg_dist, arg_bullet_type, arg_tracefrq, arg_dmg };

	ICSEntity *pInflictor = g_ReGameFuncs->INDEX_TO_CSENTITY(params[arg_inflictor]);

	cell *pSrc = getAmxAddr(amx, params[arg_vecSrc]);
	cell *pDir = getAmxAddr(amx, params[arg_dir]);
	cell *pSpread = getAmxAddr(amx, params[arg_spread]);

	Vector vecSrc(*(float *)&pSrc[0], *(float *)&pSrc[1], *(float *)&pSrc[2]);
	Vector vecDirShooting(*(float *)&pDir[0], *(float *)&pDir[1], *(float *)&pDir[2]);
	Vector vecSpread(*(float *)&pSpread[0], *(float *)&pSpread[1], *(float *)&pSpread[2]);

	entvars_t *pevAttacker = VARS(INDEXENT(params[arg_attacker]));

	pInflictor->FireBullets
	(
		params[arg_shots],
		vecSrc,
		vecDirShooting,
		vecSpread,
		*(float *)&params[arg_dist],
		params[arg_bullet_type],
		params[arg_tracefrq],
		params[arg_dmg],
		pevAttacker
	);

	return TRUE;
}

/*
* Fire bullets from player's weapon
*
* @param inflictor		Inflictor is the entity that caused the damage (such as a gun)
* @param attacker		Attacker is the entity that tirggered the damage (such as the gun's owner).
* @param vecSrc			The source position of the barrel
* @param vecDirShooting		Direction shooting
* @param vecSpread		Spread
* @param flDistance		Max shot distance
* @param iPenetration		The number of penetration
* @param iBulletType		Bullet type
* @param iDamage		Damage amount
* @param flRangeModifier	Damage range modifier
* @param bPistol		Pistol shot
* @param shared_rand		Use player's random seed, get circular gaussian spread
*
* @return Float:[3]		The result spread
*
* native Float:[3] rg_fire_bullets3(inflictor, attacker, Float:vecSrc[3], Float:vecDirShooting[3], Float:vecSpread, Float:flDistance, iPenetration, iBulletType, iDamage, Float:flRangeModifier, bool:bPistol, shared_rand);
*/
static cell AMX_NATIVE_CALL rg_fire_bullets3(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_inflictor, arg_attacker, arg_vecSrc, arg_dir, arg_spread, arg_dist, arg_penetration, arg_bullet_type, arg_dmg, arg_range_mod, arg_pistol, arg_rand, arg_out };

	ICSEntity *pInflictor = g_ReGameFuncs->INDEX_TO_CSENTITY(params[arg_inflictor]);

	cell *pSrc = getAmxAddr(amx, params[arg_vecSrc]);
	cell *pDir = getAmxAddr(amx, params[arg_dir]);

	Vector vecSrc(*(float *)&pSrc[0], *(float *)&pSrc[1], *(float *)&pSrc[2]);
	Vector vecDirShooting(*(float *)&pDir[0], *(float *)&pDir[1], *(float *)&pDir[2]);

	entvars_t *pevAttacker = VARS(INDEXENT(params[arg_attacker]));

	Vector *pOut = (Vector *)getAmxAddr(amx, params[arg_out]);

	*pOut = pInflictor->FireBullets3
	(
		vecSrc,
		vecDirShooting,
		*(float *)&params[arg_spread],
		*(float *)&params[arg_dist],
		params[arg_penetration],
		params[arg_bullet_type],
		params[arg_dmg],
		*(float *)&params[arg_range_mod],
		pevAttacker,
		params[arg_pistol] != 0,
		params[arg_rand]
	);

	return TRUE;
}

struct {
	const char *msg;
	const char *sentence;
	size_t status;
} msg_sentence_list[] = {
	{ "", "" },									// ROUND_NONE
	{ "#Target_Bombed",                     "terwin",     WINSTATUS_TERRORISTS  },	// ROUND_TARGET_BOMB
	{ "#VIP_Escaped",                       "ctwin",      WINSTATUS_CTS         },	// ROUND_VIP_ESCAPED
	{ "#VIP_Assassinated",                  "terwin",     WINSTATUS_TERRORISTS  },	// ROUND_VIP_ASSASSINATED
	{ "#Terrorists_Escaped",                "terwin",     WINSTATUS_TERRORISTS  },	// ROUND_TERRORISTS_ESCAPED
	{ "#CTs_PreventEscape",                 "ctwin",      WINSTATUS_CTS         },	// ROUND_CTS_PREVENT_ESCAPE
	{ "#Escaping_Terrorists_Neutralized",   "ctwin",      WINSTATUS_CTS         },	// ROUND_ESCAPING_TERRORISTS_NEUTRALIZED
	{ "#Bomb_Defused",                      "ctwin",      WINSTATUS_CTS         },	// ROUND_BOMB_DEFUSED
	{ "#CTs_Win",                           "ctwin",      WINSTATUS_CTS         },	// ROUND_CTS_WIN
	{ "#Terrorists_Win",                    "terwin",     WINSTATUS_TERRORISTS  },	// ROUND_TERRORISTS_WIN
	{ "#Round_Draw",                        "rounddraw",  WINSTATUS_DRAW        },	// ROUND_END_DRAW
	{ "#All_Hostages_Rescued",              "ctwin",      WINSTATUS_CTS         },	// ROUND_ALL_HOSTAGES_RESCUED
	{ "#Target_Saved",                      "ctwin",      WINSTATUS_CTS         },	// ROUND_TARGET_SAVED
	{ "#Hostages_Not_Rescued",              "terwin",     WINSTATUS_TERRORISTS  },	// ROUND_HOSTAGE_NOT_RESCUED
	{ "#Terrorists_Not_Escaped",            "ctwin",      WINSTATUS_CTS         },	// ROUND_TERRORISTS_NOT_ESCAPED
	{ "#VIP_Not_Escaped",                   "terwin",     WINSTATUS_TERRORISTS  },	// ROUND_VIP_NOT_ESCAPED
	{ "#Game_Commencing",                   "",           WINSTATUS_DRAW        },	// ROUND_GAME_COMMENCE
};

/*
* Complete the round
*
* @param tmDelay		Delay before the onset of a new round.
* @param st			Which team won
* @param event			The event is the end of the round
* @param message		The message on round end
* @param sentence		The sound at the end of the round
*
* @noreturn
*
* native rg_round_end(Float:tmDelay, WinStatus:st, ScenarioEventEndRound:event = ROUND_NONE, const message[] = "default", const sentence[] = "default");
*/
static cell AMX_NATIVE_CALL rg_round_end(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_delay, arg_win, arg_event, arg_message, arg_sentence, arg_silent };

	size_t winstatus = params[arg_win];
	if (winstatus <= 0) {
		MF_LogError(amx, AMX_ERR_NATIVE, "rg_round_end: unknown win-status %i", winstatus);
		return FALSE;
	}

	const char *_sentence, *_message;
	ScenarioEventEndRound event = static_cast<ScenarioEventEndRound>(params[arg_event]);

	_sentence = getAmxString(amx, params[arg_sentence]);
	_message = getAmxString(amx, params[arg_message]);

	if (event != ROUND_NONE) {
		auto& lst = msg_sentence_list[event];
		if (strcmp(_sentence, "default") == 0)
			_sentence = lst.sentence;
		if (strcmp(_message, "default") == 0)
			_message = lst.msg;
	}

	if (_sentence[0])
		Broadcast(_sentence);

	if (_message[0])
		g_ReGameFuncs->EndRoundMessage(_message, event);

	(*g_pCSGameRules)->TerminateRound(*(float *)&params[arg_delay], winstatus);
	return TRUE;
}

/*
* Update current scores
*
* @param iCtsWins		The amount of wins to won
* @param iTsWins		The amount of wins to won
* @param bAdd			Adds the score to the current amount wins.
*
* @noreturn
*
* native rg_update_teamscores(iCtsWins = 0, iTsWins = 0, bool:bAdd = true);
*/
static cell AMX_NATIVE_CALL rg_update_teamscores(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_cts, arg_ts, arg_add };

	(*g_pCSGameRules)->m_iNumCTWins = ((params[arg_add] != 0) ? (*g_pCSGameRules)->m_iNumCTWins : 0) + params[arg_cts];
	(*g_pCSGameRules)->m_iNumTerroristWins = ((params[arg_add] != 0) ? (*g_pCSGameRules)->m_iNumTerroristWins : 0) + params[arg_ts];
	UpdateTeamScores();

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

	{ "rg_round_end", rg_round_end },
	{ "rg_update_teamscores", rg_update_teamscores },

	{ nullptr, nullptr }
};

void RegisterNatives_Misc()
{
	g_amxxapi.AddNatives(Misc_Natives);
}
