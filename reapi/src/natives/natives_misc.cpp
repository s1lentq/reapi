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
cell AMX_NATIVE_CALL rg_set_animation(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_anim };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	pPlayer->CSPlayer()->SetAnimation(CAmxArg(amx, params[arg_anim]));
	return TRUE;
}

enum AccountSet { AS_SET, AS_ADD };

/*
* Adds money to player's account.
*
* @param index		Client index
* @param amount		The amount of money
* @param bTrackChange	If the bTrackChange is 1, the amount of money added will also be displayed.
*
* @noreturn
*
* native rg_add_account(index, amount, AccountSet:typeSet = AS_ADD, const bool:bTrackChange = true);
*/
cell AMX_NATIVE_CALL rg_add_account(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_amount, arg_typeSet, arg_track_change };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	if (static_cast<AccountSet>(params[arg_typeSet]) == AS_SET) {
		pPlayer->m_iAccount = 0;
	}

	pPlayer->CSPlayer()->AddAccount(params[arg_amount], RT_NONE, params[arg_track_change] != 0);
	return TRUE;
}

enum GiveType { GT_APPEND, GT_REPLACE, GT_DROP_AND_REPLACE };

/*
* Gives item to player
*
* @param index		Client index
* @param pszName	Classname item
* @param type		Look at the enum's with name GiveType
*
* @return		1 if successfully, 0 otherwise
*
* native rg_give_item(index, const pszName[], GiveType:type = GT_APPEND);
*/
cell AMX_NATIVE_CALL rg_give_item(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_item, arg_type };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	GiveType type = static_cast<GiveType>(params[arg_type]);
	const char *itemName = getAmxString(amx, params[arg_item]);

	if (type > GT_APPEND) {

		auto pInfo = g_ReGameApi->GetWeaponSlot(itemName);
		if (pInfo != nullptr)
		{
			auto pItem = pPlayer->m_rgpPlayerItems[ pInfo->slot ];
			while (pItem != nullptr) {
				if (pItem->m_iId == pInfo->id) {
					pItem = pItem->m_pNext;
					continue;
				}

				switch (type)
				{
				case GT_DROP_AND_REPLACE:
					pPlayer->CSPlayer()->DropPlayerItem(STRING(pItem->pev->classname));
					break;
				case GT_REPLACE:
					pPlayer->pev->weapons &= ~(1 << pItem->m_iId);
					pPlayer->RemovePlayerItem(pItem);
					pItem->Kill();
					break;
				case GT_APPEND: break;
				default: break;
				}

				pItem = pItem->m_pNext;
			}
		}
	}

	pPlayer->CSPlayer()->GiveNamedItemEx(itemName);
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
cell AMX_NATIVE_CALL rg_give_default_items(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	pPlayer->CSPlayer()->GiveDefaultItems();
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
* native rg_give_shield(index, const bool:bDeploy = true);
*/
cell AMX_NATIVE_CALL rg_give_shield(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_deploy };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	pPlayer->CSPlayer()->GiveShield(params[arg_deploy] != 0);
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
cell AMX_NATIVE_CALL rg_dmg_radius(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_vec, arg_inflictor, arg_attacker, arg_damage, arg_radius, arg_ignore_class, arg_dmg_type };

	CHECK_ISENTITY(arg_inflictor);
	CHECK_ISENTITY(arg_attacker);

	CAmxArgs args(amx, params);
	g_ReGameFuncs->RadiusDamage(args[arg_vec], args[arg_inflictor], args[arg_attacker], args[arg_damage], args[arg_radius], args[arg_ignore_class], args[arg_dmg_type]);

	return TRUE;
}

/*
* Resets the global multi damage accumulator
*
* @noreturn
*
* native rg_multidmg_clear();
*/
cell AMX_NATIVE_CALL rg_multidmg_clear(AMX *amx, cell *params)
{
	g_ReGameFuncs->ClearMultiDamage();
	return TRUE;
}

/*
* Inflicts contents of global multi damage register on victim
*
* @param inflictor	Inflictor is the entity that caused the damage (such as a gun)
* @param attacker	Attacker is the entity that tirggered the damage (such as the gun's owner).
*
* @noreturn
*
* native rg_multidmg_apply(inflictor, attacker);
*/
cell AMX_NATIVE_CALL rg_multidmg_apply(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_inflictor, arg_attacker };

	CHECK_ISENTITY(arg_inflictor);
	CHECK_ISENTITY(arg_attacker);

	CAmxArgs args(amx, params);
	g_ReGameFuncs->ApplyMultiDamage(args[arg_inflictor], args[arg_attacker]);

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
cell AMX_NATIVE_CALL rg_multidmg_add(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_inflictor, arg_victim, arg_damage, arg_dmg_type };

	CHECK_ISENTITY(arg_inflictor);
	CHECK_ISENTITY(arg_victim);

	if (params[arg_victim] < 0) { // null
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: victim == null", __FUNCTION__);
		return FALSE;
	}

	CAmxArgs args(amx, params);
	g_ReGameFuncs->AddMultiDamage(args[arg_inflictor], args[arg_victim], args[arg_damage], args[arg_dmg_type]);

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
cell AMX_NATIVE_CALL rg_fire_bullets(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_inflictor, arg_attacker, arg_shots, arg_vecSrc, arg_dir, arg_spread, arg_dist, arg_bullet_type, arg_tracefrq, arg_dmg };

	CHECK_ISENTITY(arg_inflictor);
	CHECK_ISENTITY(arg_attacker);

	CAmxArgs args(amx, params);
	CBaseEntity *pInflictor = args[arg_inflictor];

	pInflictor->m_pEntity->FireBullets
	(
		args[arg_shots],
		args[arg_vecSrc],
		args[arg_dir],
		args[arg_spread],
		args[arg_dist],
		args[arg_bullet_type],
		args[arg_tracefrq],
		args[arg_dmg],
		args[arg_attacker]
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
* native Float:[3] rg_fire_bullets3(const inflictor, const attacker, Float:vecSrc[3], Float:vecDirShooting[3], const Float:vecSpread, const Float:flDistance, const iPenetration, const Bullet:iBulletType, const iDamage, const Float:flRangeModifier, const bool:bPistol, const shared_rand);
*/
cell AMX_NATIVE_CALL rg_fire_bullets3(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_inflictor, arg_attacker, arg_vecSrc, arg_dir, arg_spread, arg_dist, arg_penetration, arg_bullet_type, arg_dmg, arg_range_mod, arg_pistol, arg_rand, arg_out };

	CHECK_ISENTITY(arg_inflictor);
	CHECK_ISENTITY(arg_attacker);

	CAmxArgs args(amx, params);
	CBaseEntity *pInflictor = args[arg_inflictor];
	entvars_t *pAttacker = args[arg_attacker];

	args[arg_out].vector() = pInflictor->m_pEntity->FireBullets3
	(
		args[arg_vecSrc],
		args[arg_dir],
		args[arg_spread],
		args[arg_dist],
		args[arg_penetration],
		args[arg_bullet_type],
		args[arg_dmg],
		args[arg_range_mod],
		pAttacker, // icc fix
		args[arg_pistol],
		args[arg_rand]
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
cell AMX_NATIVE_CALL rg_round_end(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_delay, arg_win, arg_event, arg_message, arg_sentence, arg_silent };

	CHECK_GAMERULES();

	size_t winstatus = params[arg_win];
	if (winstatus <= 0) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: unknown win status %i", __FUNCTION__, winstatus);
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
		CSGameRules()->EndRoundMessage(_message, event);

	CSGameRules()->TerminateRound(CAmxArg(amx, params[arg_delay]), winstatus);
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
* native rg_update_teamscores(const iCtsWins = 0, const iTsWins = 0, const bool:bAdd = true);
*/
cell AMX_NATIVE_CALL rg_update_teamscores(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_cts, arg_ts, arg_add };

	CHECK_GAMERULES();

	CSGameRules()->m_iNumCTWins = ((params[arg_add] != 0) ? CSGameRules()->m_iNumCTWins : 0) + params[arg_cts];
	CSGameRules()->m_iNumTerroristWins = ((params[arg_add] != 0) ? CSGameRules()->m_iNumTerroristWins : 0) + params[arg_ts];
	CSGameRules()->UpdateTeamScores();

	return TRUE;
}

/*
* Creates an entity using Counter-Strike's custom CreateNamedEntity wrapper.
*
* @param classname		Entity class name
* @param useHashTable		Use this only for known game entities.
*				NOTE: Do not use this if you use a custom classname.
*
* @return			Index of the created entity or 0 otherwise
*
* native rg_create_entity(const classname[], const bool:useHashTable = false);
*/
cell AMX_NATIVE_CALL rg_create_entity(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_classname, arg_hashtable };

	string_t iClass = g_engfuncs.pfnAllocString(getAmxString(amx, params[arg_classname]));

	edict_t	*pEntity;
	if (params[arg_hashtable] != 0)
		pEntity = g_ReGameFuncs->CREATE_NAMED_ENTITY2(iClass);
	else
		pEntity = CREATE_NAMED_ENTITY(iClass);

	if (pEntity) {
		return indexOfEdict(pEntity);
	}

	return 0;
}

/*
* Finds an entity in the world using Counter-Strike's custom FindEntityByString wrapper.
*
* @param start_index		Entity index to start searching from. -1 to start from the first entity
* @param classname		Classname to search for
* @param useHashTable		Use this only for known game entities.
*				NOTE: Do not use this if you use a custom classname.
*
* @return			Entity index > 0 if found, 0 otherwise
*
* native rg_find_ent_by_class(start_index, const classname[], const bool:useHashTable = false);
*/
cell AMX_NATIVE_CALL rg_find_ent_by_class(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_start_index, arg_classname, arg_hashtable };

	const char* value = getAmxString(amx, params[arg_classname]);

	if (params[arg_hashtable] != 0)
	{
		auto pStartEntity = getPrivate<CBaseEntity>(params[arg_start_index]);
		auto pEntity = g_ReGameFuncs->UTIL_FindEntityByString(pStartEntity, "classname", value);
		if (pEntity) {
			return indexOfEdict(pEntity->pev);
		}

		return 0;
	}

	auto pStartEntity = edictByIndexAmx(params[arg_start_index]);
	auto pEdict = FIND_ENTITY_BY_STRING(pStartEntity, "classname", value);
	if (pEdict) {
		return indexOfEdict(pEdict);
	}

	return 0;
}

/*
* Finds an entity in the world using Counter-Strike's custom FindEntityByString wrapper, matching by owner.
*
* @param start_index		Entity index to start searching from. -1 to start from the first entity
* @param classname		Classname to search for
*
* @return			1 if found, 0 otherwise
*
* native rg_find_ent_by_owner(&start_index, const classname[], owner);
*/
cell AMX_NATIVE_CALL rg_find_ent_by_owner(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_start_index, arg_classname, arg_onwer };

	CHECK_ISENTITY(arg_onwer);

	cell& startIndex = *getAmxAddr(amx, params[arg_start_index]);
	const char* value = getAmxString(amx, params[arg_classname]);
	edict_t* pOwner = edictByIndexAmx(params[arg_onwer]);
	edict_t* pEntity = g_pEdicts + startIndex;

	for (int i = startIndex; i < gpGlobals->maxEntities; i++, pEntity++)
	{
		if (pEntity->v.owner != pOwner)
			continue;

		// yet not allocated
		if (!pEntity->pvPrivateData || pEntity->free)
			continue;

		if (FClassnameIs(pEntity, value))
		{
			startIndex = i;
			return TRUE;
		}
	}

	return FALSE;
}

/*
* Find the weapon by name in the player's inventory.
*
* @param index			Client index
* @param weapon			Weapon name
*
* @return			Entity-index of weapon, 0 otherwise
*
* native rg_find_weapon_bpack_by_name(const index, const weapon[]);
*/
cell AMX_NATIVE_CALL rg_find_weapon_bpack_by_name(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_weapon };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	const char *pszWeaponName = getAmxString(amx, params[arg_weapon]);
	auto pInfo = g_ReGameApi->GetWeaponSlot(pszWeaponName);
	if (pInfo != nullptr)
	{
		auto pItem = pPlayer->m_rgpPlayerItems[ pInfo->slot ];
		while (pItem)
		{
			if (FClassnameIs(pItem->pev, pszWeaponName)) {
				return indexOfEdict(pItem->pev);
			}

			pItem = pItem->m_pNext;
		}
	}

	return FALSE;
}

struct {
	const char* pszItemName;
	bool(*hasItem)(CBasePlayer* pl);
} itemInfoStruct[] = {
	{ "item_thighpack",		[](CBasePlayer* pl) -> bool { return pl->m_bHasDefuser; } },
	{ "item_longjump",		[](CBasePlayer* pl) -> bool { return pl->m_fLongJump == TRUE; } },
	{ "item_assaultsuit",		[](CBasePlayer* pl) -> bool { return pl->m_iKevlar == ARMOR_VESTHELM; } },
	{ "item_kevlar",		[](CBasePlayer* pl) -> bool { return pl->m_iKevlar == ARMOR_KEVLAR; } },
	{ "weapon_shield",		[](CBasePlayer* pl) -> bool { return pl->m_bOwnsShield; } },
};

/*
* Check if the player already have this item.
*
* @param index			Client index
* @param item			Item name
*
* @return			1 if successfully, 0 otherwise
*
* native bool:rg_has_item_by_name(const index, const item[]);
*/
cell AMX_NATIVE_CALL rg_has_item_by_name(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_item };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	const char *pszItemName = getAmxString(amx, params[arg_item]);
	// item_* and weapon_shield
	for (auto& inf : itemInfoStruct) {
		if (FStrEq(inf.pszItemName, pszItemName)) {
			return (cell)inf.hasItem(pPlayer);
		}
	}

	// weapon_*
	auto pInfo = g_ReGameApi->GetWeaponSlot(pszItemName);
	if (pInfo != nullptr)
	{
		auto pItem = pPlayer->m_rgpPlayerItems[ pInfo->slot ];
		while (pItem)
		{
			if (FClassnameIs(pItem->pev, pszItemName)) {
				return TRUE;
			}

			pItem = pItem->m_pNext;
		}
	}

	return FALSE;
}

/*
* Returns some information about a weapon.
*
* @param weapon name or id	Weapon id, see WEAPON_* constants or weapon_* name
* @param WpnInfo:type		Info type, see WI_* constants
*
* @return			Weapon information value
* @error			If weapon_id and type are out of bound, an error will be thrown.
*
* native any:rg_get_weapon_info(any:...);
*/
cell AMX_NATIVE_CALL rg_get_weapon_info(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_weapon_id, arg_type, arg_3, arg_4 };

	WeaponIdType weaponID = static_cast<WeaponIdType>(*getAmxAddr(amx, params[arg_weapon_id]));
	WpnInfo info_type = static_cast<WpnInfo>(*getAmxAddr(amx, params[arg_type]));

	if (!GetWeaponInfoRange(weaponID) && info_type != WI_ID)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: invalid weapon id %i", __FUNCTION__, weaponID);
		return 0;
	}

	WeaponInfoStruct* info = g_ReGameApi->GetWeaponInfo(weaponID);
	char* szWeaponName = getAmxString(amx, params[arg_weapon_id]);

	switch (info_type)
	{
	case WI_ID:
		if (szWeaponName != nullptr) {
			auto infoName = g_ReGameApi->GetWeaponInfo(szWeaponName);
			if (infoName != nullptr) {
				return infoName->id;
			}
		}

		return WEAPON_NONE;
	case WI_COST:
		return info->cost;
	case WI_CLIP_COST:
		return info->clipCost;
	case WI_BUY_CLIP_SIZE:
		return info->buyClipSize;
	case WI_GUN_CLIP_SIZE:
		return info->gunClipSize;
	case WI_MAX_ROUNDS:
		return info->maxRounds;
	case WI_AMMO_TYPE:
		return info->ammoType;
	case WI_AMMO_NAME:
		{
			if (PARAMS_COUNT != arg_4) {
				MF_LogError(amx, AMX_ERR_NATIVE, "%s: bad parameter count, got %i, expected %i", __FUNCTION__, PARAMS_COUNT, arg_4);
				return -1;
			}

			// native rg_get_weapon_info(id, WI_AMMO_NAME, output[], maxlength);
			cell* dest = getAmxAddr(amx, params[arg_3]);
			size_t length = *getAmxAddr(amx, params[arg_4]);

			if (info->ammoName == nullptr) {
				setAmxString(dest, "", 1);
				return 0;
			}

			setAmxString(dest, info->ammoName, length);
			return 1;
		}
	case WI_NAME:
		{
			if (PARAMS_COUNT != arg_4) {
				MF_LogError(amx, AMX_ERR_NATIVE, "%s: bad parameter count, got %i, expected %i", __FUNCTION__, PARAMS_COUNT, arg_4);
				return -1;
			}

			// native rg_get_weapon_info(id, WI_NAME, output[], maxlength);
			cell* dest = getAmxAddr(amx, params[arg_3]);
			size_t length = *getAmxAddr(amx, params[arg_4]);

			if (info->entityName == nullptr) {
				setAmxString(dest, "", 1);
				return 0;
			}

			setAmxString(dest, info->entityName, length);
			return 1;
		}
	default:
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: unknown type statement %i, params count %i", __FUNCTION__, info_type, PARAMS_COUNT);
		return -1;
	}
}

/*
* Sets specific values of weapons info.
*
* @param weapon_id	Weapon id, see WEAPON_* constants
* @param type		Info type, see WI_* constants
*
* @return		1 if successfully, 0 otherwise
*
* native rg_set_weapon_info(const {WeaponIdType,_}:weapon_id, WpnInfo:type, any:...);
*/
cell AMX_NATIVE_CALL rg_set_weapon_info(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_weapon_id, arg_type, arg_value };

	WeaponIdType weaponID = static_cast<WeaponIdType>(params[arg_weapon_id]);
	if (!GetWeaponInfoRange(weaponID))
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: invalid weapon id %i", __FUNCTION__, weaponID);
		return 0;
	}

	cell* value = getAmxAddr(amx, params[arg_value]);
	WeaponInfoStruct *info = g_ReGameApi->GetWeaponInfo(weaponID);
	WpnInfo info_type = static_cast<WpnInfo>(params[arg_type]);

	switch (info_type)
	{
	case WI_COST:
		info->cost = *value;
		break;
	case WI_CLIP_COST:
		info->clipCost = *value;
		break;
	case WI_BUY_CLIP_SIZE:
	case WI_GUN_CLIP_SIZE:
	case WI_MAX_ROUNDS:
	case WI_AMMO_TYPE:
	case WI_AMMO_NAME:
	case WI_NAME:
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: this change will have no effect, type statement %i", __FUNCTION__, info_type);
		return 0;
	default:
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: unknown type statement %i, params count %i", __FUNCTION__, info_type, PARAMS_COUNT);
		return 0;
	}

	return 1;
}

/*
* Remove all the player's stuff
*
* @param index		Client index
*
* @noreturn
*
* native rg_remove_all_items(const index, const bool:bRemoveSuit);
*/
cell AMX_NATIVE_CALL rg_remove_all_items(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_suit };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	pPlayer->CSPlayer()->RemoveAllItems(params[arg_suit] != 0);
	return TRUE;
}

/*
* Remove specifed the player's item by class name
*
* @param index		Client index
* @param item_name	Class name item
*
* @noreturn
*
* native rg_remove_item(const index, const item_name[]);
*/
cell AMX_NATIVE_CALL rg_remove_item(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_item_name };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	const char* szItemName = getAmxString(amx, params[arg_item_name]);
	if (pPlayer->CSPlayer()->RemovePlayerItem(szItemName)) {
		return TRUE;
	}

	return FALSE;
}

/*
* Returns amount of ammo in the client's backpack for a specific weapon.
*
* @param index		Client index
* @param weapon		Weapon id
*
* @return		Amount of ammo in backpack
*
* native rg_get_user_bpammo(const index, WeaponIdType:weapon);
*/
cell AMX_NATIVE_CALL rg_get_user_bpammo(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_weapon };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	WeaponIdType weaponId = static_cast<WeaponIdType>(params[arg_weapon]);
	if (weaponId < WEAPON_P228 || weaponId > WEAPON_P90 || weaponId == WEAPON_KNIFE)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Invalid weapon id %d", params[arg_weapon]);
		return FALSE;
	}

	for (auto pItem : pPlayer->m_rgpPlayerItems)
	{
		while (pItem != nullptr)
		{
			if (pItem->m_iId == weaponId) {
				return pPlayer->m_rgAmmo[ static_cast<CBasePlayerWeapon *>(pItem)->m_iPrimaryAmmoType ];
			}

			pItem = pItem->m_pNext;
		}
	}

	return FALSE;
}

/*
* Sets amount of ammo in the client's backpack for a specific weapon.
*
* @param index		Client index
* @param weapon		Weapon id
* @param amount		New backpack ammo amount to set
*
* @noreturn
*
* native rg_set_user_bpammo(const index, WeaponIdType:weapon, amount);
*/
cell AMX_NATIVE_CALL rg_set_user_bpammo(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_weapon, arg_amount };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	WeaponIdType weaponId = static_cast<WeaponIdType>(params[arg_weapon]);
	if (weaponId < WEAPON_P228 || weaponId > WEAPON_P90 || weaponId == WEAPON_KNIFE)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Invalid weapon id %d", params[arg_weapon]);
		return FALSE;
	}

	for (auto pItem : pPlayer->m_rgpPlayerItems)
	{
		while (pItem != nullptr)
		{
			if (pItem->m_iId == weaponId) {
				pPlayer->m_rgAmmo[ static_cast<CBasePlayerWeapon *>(pItem)->m_iPrimaryAmmoType ] = params[arg_amount];
				return TRUE;
			}

			pItem = pItem->m_pNext;
		}
	}

	return FALSE;
}

/*
* Sets the client's defusekit status and allows to set a custom HUD icon and color.
*
* @param index		Client index
* @param defusekit	If nonzero the client will have a defusekit, otherwise it will be removed
* @param color		Color RGB
* @param icon		HUD sprite to use as icon
* @param flash		If nonzero the icon will flash red
*
* @noreturn
*
* native rg_give_defusekit(const index, const bool:bDefusekit = true, const Float:color[] = {0.0, 160.0, 0.0}, const icon[] = "defuser", const bool:bFlash = false);
*/
cell AMX_NATIVE_CALL rg_give_defusekit(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_def, arg_color, arg_icon, arg_flash };

	CHECK_GAMERULES();
	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	// on the map there is not bomb places
	if (CSGameRules() != nullptr && !CSGameRules()->m_bMapHasBombTarget && !CSGameRules()->m_bMapHasBombZone) {
		return FALSE;
	}

	pPlayer->m_bHasDefuser =
		pPlayer->pev->body = params[arg_def] != 0;

	if (params[arg_def] != 0)
	{
		Vector* color = (Vector *)getAmxAddr(amx, params[arg_color]);
		const char* icon = getAmxString(amx, params[arg_icon]);

		MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pPlayer->pev);
			WRITE_BYTE(params[arg_flash] != 0 ? STATUSICON_FLASH : STATUSICON_SHOW);
			WRITE_STRING(icon);
			WRITE_BYTE(color->x);
			WRITE_BYTE(color->y);
			WRITE_BYTE(color->z);
		MESSAGE_END();
	}
	else
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pPlayer->pev);
			WRITE_BYTE(STATUSICON_HIDE);
			WRITE_STRING("defuser");
		MESSAGE_END();
	}

	return TRUE;
}

/*
* Returns the client's armor value and retrieves the type of armor.
*
* @param index		Client index
* @param armortype	Variable to store armor type in
*
* @return		Amount of armor, 0 if client has no armor
*
* native rg_get_user_armor(const index, &ArmorType:armortype);
*/
cell AMX_NATIVE_CALL rg_get_user_armor(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_armortype };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	*getAmxAddr(amx, params[arg_armortype]) = pPlayer->m_iKevlar;
	return static_cast<cell>(pPlayer->pev->armorvalue);
}

/*
* Sets the client's armor value the type of armor.
*
* @param index		Client index
* @param armorvalue	Amount of armor to set
* @param armortype	Armor type
*
* @noreturn
*
* native rg_set_user_armor(const index, armorvalue, ArmorType:armortype);
*/
cell AMX_NATIVE_CALL rg_set_user_armor(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_armorvalue, arg_armortype };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	ArmorType armorType = static_cast<ArmorType>(params[arg_armortype]);

	pPlayer->pev->armorvalue = params[arg_armorvalue];
	pPlayer->m_iKevlar = armorType;

	if (armorType == ARMOR_KEVLAR || armorType == ARMOR_VESTHELM) {
		MESSAGE_BEGIN(MSG_ONE, gmsgArmorType, nullptr, pPlayer->pev);
			WRITE_BYTE(armorType == ARMOR_VESTHELM ? 1 : 0);
		MESSAGE_END();
	}

	return TRUE;
}

/*
* Sets the client's team without killing the player, and sets the client model.
* @note To obtain of TeamName use the following:
*	new TeamName:team = get_member(id, m_iTeam);
*
* @param index		Client index
* @param team		Team id
* @param model		Internal model, use MODEL_AUTO for a random appearance or if MODEL_UNASSIGNED not update it.
*
* @param send_teaminfo	If true, a TeamInfo message will be sent
*
* @return		1 if successfully, 0 otherwise
*
* native rg_set_user_team(const index, {TeamName,_}:team, {ModelName,_}:model = MODEL_AUTO, const bool:send_teaminfo = true);
*/
cell AMX_NATIVE_CALL rg_set_user_team(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_team, arg_model, arg_sendinfo };

	CHECK_GAMERULES();
	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	CAmxArgs args(amx, params);

	TeamName prevTeam = pPlayer->m_iTeam;
	pPlayer->m_iTeam = args[arg_team];

	if (prevTeam != args[arg_team]) {
		// next team
		switch (pPlayer->m_iTeam) {
		case TERRORIST:
			CSGameRules()->m_iNumTerrorist++;
			break;
		case CT:
			CSGameRules()->m_iNumCT++;
			break;
		}

		// previous team
		switch (prevTeam) {
		case TERRORIST:
			CSGameRules()->m_iNumTerrorist--;
			if (pPlayer->m_bHasC4 && !CSGameRules()->m_fTeamCount && CSGameRules()->m_bMapHasBombTarget)
			{
				if (CSGameRules()->m_iNumTerrorist > 0 && pPlayer->CSPlayer()->RemovePlayerItem("weapon_c4")) {
					pPlayer->m_bHasC4 = false;
					pPlayer->pev->body = 0;
					pPlayer->CSPlayer()->SetBombIcon();
					pPlayer->CSPlayer()->SetProgressBarTime(0);
					CSGameRules()->GiveC4();
				} else if (pPlayer->IsAlive()) {// are still alive
					pPlayer->CSPlayer()->DropPlayerItem("weapon_c4");
				}
			}
			break;
		case CT:
			CSGameRules()->m_iNumCT--;
			if (pPlayer->m_bHasDefuser) {
				pPlayer->m_bHasDefuser = false;
				pPlayer->pev->body = 0;

				MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pPlayer->pev);
					WRITE_BYTE(STATUSICON_HIDE);
					WRITE_STRING("defuser");
				MESSAGE_END();

				pPlayer->CSPlayer()->SendItemStatus();
			}
			break;
		}
	}

	if (args[arg_model] > MODEL_UNASSIGNED) {
		if (args[arg_model] != MODEL_AUTO) {
			pPlayer->m_iModelName = args[arg_model];
		} else {
			pPlayer->m_iModelName = GetModelAuto(pPlayer->m_iTeam);
		}

		pPlayer->CSPlayer()->SetPlayerModel(pPlayer->m_bHasC4);
	}

	if (params[arg_sendinfo] != 0) {
		pPlayer->CSPlayer()->TeamChangeUpdate();
	}

	g_amxxapi.SetPlayerTeamInfo(args[arg_index], args[arg_team], GetTeamName(args[arg_team]));
	return TRUE;
}

/*
* Sets the client's player model.
*
* @param index		Client index
* @param model		Model name
* @param update_index	If true, the modelindex is updated as well
*
* @return		1 if successfully, 0 otherwise
*
* native rg_set_user_model(const index, const model[], const bool:update_index = false);
*/
cell AMX_NATIVE_CALL rg_set_user_model(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_model, arg_update };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	const char* newModel = getAmxString(amx, params[arg_model]);
	if (*newModel == '\0') {
		MF_LogError(amx, AMX_ERR_NATIVE, "Model can not be empty");
		return FALSE;
	}

	pPlayer->CSPlayer()->SetPlayerModelEx(newModel);
	pPlayer->CSPlayer()->SetPlayerModel(pPlayer->m_bHasC4);

	if (params[arg_update] != 0)
	{
		char model[260];
		snprintf(model, sizeof(model), "models/player/%s/%s.mdl", newModel, newModel);
		pPlayer->CSPlayer()->SetNewPlayerModel(model);
	}

	return TRUE;
}

/*
* Reset model user
*
* @param index		Client index
*
* @return		1 if successfully, 0 otherwise
*
* native rg_reset_user_model(const index);
*/
cell AMX_NATIVE_CALL rg_reset_user_model(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_team, arg_model };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	pPlayer->CSPlayer()->SetPlayerModelEx("");
	pPlayer->CSPlayer()->SetPlayerModel(pPlayer->m_bHasC4);
	return TRUE;
}

/*
* Transfer C4 to player
*
* @param index		Client index
* @param receiver	Receiver index, if 0 so will transfer a random to player
*
* @return		1 if successfully, 0 otherwise
*
* native rg_transfer_c4(const index, const receiver = 0);
*/
cell AMX_NATIVE_CALL rg_transfer_c4(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_receiver };

	CHECK_GAMERULES();
	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	if (!pPlayer->m_bHasC4 || !pPlayer->CSPlayer()->RemovePlayerItem("weapon_c4"))
		return FALSE;

	pPlayer->pev->body = 0;
	pPlayer->m_bHasC4 = false;
	pPlayer->CSPlayer()->SetBombIcon();
	pPlayer->CSPlayer()->SetProgressBarTime(0);

	if (params[arg_receiver] != 0 && params[arg_receiver] <= gpGlobals->maxClients) {
		CBasePlayer *pReceiver = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_receiver]);
		if (pReceiver == nullptr || pReceiver->has_disconnected) {
			MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_receiver]);
			return FALSE;
		}

		pReceiver->m_bHasC4 = true;
		pReceiver->CSPlayer()->GiveNamedItemEx("weapon_c4");
		pReceiver->CSPlayer()->SetBombIcon();
		pReceiver->pev->body = 1;
	} else {
		auto flags = pPlayer->pev->flags;
		pPlayer->pev->flags |= FL_DORMANT;
		CSGameRules()->GiveC4();
		pPlayer->pev->flags = flags;
	}

	return TRUE;
}

/*
* Instant reload weapons
*
* @param index		Client index
* @param weapon		Weapon entity-index, if 0 then all the weapons
*
* @return		1 if successfully, 0 otherwise
*
* native rg_instant_reload_weapons(const index, const weapon = 0);
*/
cell AMX_NATIVE_CALL rg_instant_reload_weapons(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_weapon, arg_force_reload, arg_force_refill };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	CBasePlayerWeapon *pWeapon = nullptr;
	if (params[arg_weapon] != 0)
	{
		pWeapon = getPrivate<CBasePlayerWeapon>(params[arg_weapon]);
		if (pWeapon == nullptr || !pWeapon->IsWeapon()) {
			MF_LogError(amx, AMX_ERR_NATIVE, "%s: Invalid entity weapon", __FUNCTION__);
			return FALSE;
		}
	}

	pPlayer->CSPlayer()->ReloadWeapons(pWeapon, true, true);
	return TRUE;
}

/*
* Sets the amount of reward in the game account for all players.
*
* @param rules_index	Look at the enum's with name RewardRules
* @param amount		The amount money
*
* @noreturn
*
* native rg_set_account_rules(const RewardRules:rules_index, const amount);
*/
cell AMX_NATIVE_CALL rg_set_account_rules(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_rules_index, arg_amount };

	CHECK_GAMERULES();

	CSGameRules()->SetAccountRules(static_cast<RewardRules>(params[arg_rules_index]), params[arg_amount]);
	return TRUE;
}

/*
* Get the amount of reward from account
*
* @param rules_index	Look at the enum's with name RewardRules
*
* @return		The amount of reward from account
*
* native rg_get_account_rules(const RewardRules:rules_index);
*/
cell AMX_NATIVE_CALL rg_get_account_rules(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_rules_index };

	CHECK_GAMERULES();

	return (cell)CSGameRules()->GetAccountRules(static_cast<RewardRules>(params[arg_rules_index]));
}

/*
* If the bomb is planted
*
* @return		true if bomb is planted, false otherwise
*
* native bool:rg_is_bomb_planted();
*/
cell AMX_NATIVE_CALL rg_is_bomb_planted(AMX *amx, cell *params)
{
	CHECK_GAMERULES();

	return (cell)CSGameRules()->IsBombPlanted();
}

/*
* Join team
*
* @param index		Client index
* @param team		Team id
*
* @return		1 if successfully joined the team, 0 otherwise
*
* native rg_join_team(const index, const TeamName:team);
*/
cell AMX_NATIVE_CALL rg_join_team(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_team };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	return (cell)pPlayer->CSPlayer()->JoinTeam(static_cast<TeamName>(params[arg_team]));
}

/*
* Instantly balances the team.
*
* @noreturn
*
* native rg_balance_teams();
*/
cell AMX_NATIVE_CALL rg_balance_teams(AMX *amx, cell *params)
{
	CHECK_GAMERULES();

	CSGameRules()->BalanceTeams();
	return TRUE;
}

/*
* To swap players, without reset frags/deaths and the amount wins.
*
* @noreturn
*
* native rg_swap_all_players();
*/
cell AMX_NATIVE_CALL rg_swap_all_players(AMX *amx, cell *params)
{
	CHECK_GAMERULES();

	CSGameRules()->SwapAllPlayers();
	return TRUE;
}

/*
* Instantly switches to the opposite team for one player.
* @note Switch from CT to TERRORIST also opposite.
*
* @param index		Client index
*
* @noreturn
*
* native rg_switch_team(const index);
*/
cell AMX_NATIVE_CALL rg_switch_team(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	pPlayer->CSPlayer()->SwitchTeam();
	return TRUE;
}

/*
* Switch to specific weapon
*
* @param index		Client index
* @param weapon		Weapon entity-index
*
* @return		1 if successfully switched, 0 otherwise
*
* native rg_switch_weapon(const index, const weapon);
*/
cell AMX_NATIVE_CALL rg_switch_weapon(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_weapon };

	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	auto pWeapon = getPrivate<CBasePlayerWeapon>(params[arg_weapon]);
	if (pWeapon == nullptr || !pWeapon->IsWeapon()) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: Invalid entity weapon", __FUNCTION__);
		return FALSE;
	}

	return (cell)pPlayer->CSPlayer()->SwitchWeapon(pWeapon);
}

/*
* To get which team has a high priority to join.
*
* @return		Returns the Team Name
*
* native TeamName:rg_get_join_team_priority();
*/
cell AMX_NATIVE_CALL rg_get_join_team_priority(AMX *amx, cell *params)
{
	CHECK_GAMERULES();

	return CSGameRules()->SelectDefaultTeam();
}

/*
* Can this player take damage from this attacker?
*
* @param index		Client index
* @param attacker	Attacker index
*
* @return		true if can take a damage, false otherwise
*
* native bool:rg_is_player_can_takedamage(const index, const attacker);
*/
cell AMX_NATIVE_CALL rg_is_player_can_takedamage(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_attacker };

	CHECK_GAMERULES();
	CHECK_ISPLAYER(arg_index);

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	CBaseEntity *pAttacker = getPrivate<CBaseEntity>(params[arg_attacker]);
	if (!pAttacker) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: Invalid entity attacker", __FUNCTION__);
		return FALSE;
	}

	return CSGameRules()->FPlayerCanTakeDamage(pPlayer, pAttacker);
}

/*
* To get WeaponIdType from weaponbox
*
* @param entity		Weaponbox entity
*
* @return		return enum's of WeaponIdType
*
* native WeaponIdType:rg_get_weaponbox_id(const entity);
*/
cell AMX_NATIVE_CALL rg_get_weaponbox_id(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_entity };

	CHECK_ISENTITY(arg_entity);

	CWeaponBox *pEntityBox = getPrivate<CWeaponBox>(params[arg_entity]);
	if (pEntityBox == nullptr) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: Invalid entity weaponbox", __FUNCTION__);
		return FALSE;
	}

	for (auto item : pEntityBox->m_rgpPlayerItems) {
		if (item) {
			return item->m_iId;
		}
	}

	return WEAPON_NONE;
}

/*
* Respawn on round for players/bots
*
* @param index		Client index
*
* @noreturn
*
* native rg_round_respawn(const index);
*/
cell AMX_NATIVE_CALL rg_round_respawn(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	pPlayer->RoundRespawn();
	return TRUE;
}

/*
* Draws a HUD progress bar which is fills from 0% to 100% for the time duration seconds.
* NOTE: Set Duration to 0 to hide the bar.
*
* @param index		Client index
* @param time		Duration
* @param observer	Send for everyone observer player
*
* @noreturn
*
* native rg_send_bartime(const index, const Float:duration, const bool:observer = true);
*/
cell AMX_NATIVE_CALL rg_send_bartime(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_time, arg_observer };

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	CAmxArgs args(amx, params);
	if (!args[arg_observer]) {
		EMESSAGE_BEGIN(MSG_ONE_UNRELIABLE, gmsgBarTime, nullptr, pPlayer->edict());
			EWRITE_SHORT(args[arg_time]);
		EMESSAGE_END();
		return TRUE;
	}

	pPlayer->CSPlayer()->SetProgressBarTime(args[arg_time]);
	return TRUE;
}

/*
* Same as BarTime, but StartPercent specifies how much of the bar is (already) filled.
*
* @param index		Client index
* @param time		Duration
* @param startPercent	Start percent
* @param observer	Send for everyone observer player
*
* @noreturn
*
* native rg_send_bartime2(const index, const Float:duration, const Float:startPercent, const bool:observer = true);
*/
cell AMX_NATIVE_CALL rg_send_bartime2(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_time, arg_start_percent, arg_observer };

	CBasePlayer *pPlayer = g_ReGameFuncs->UTIL_PlayerByIndex(params[arg_index]);
	if (pPlayer == nullptr || pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_index]);
		return FALSE;
	}

	CAmxArgs args(amx, params);
	if (!args[arg_observer]) {
		EMESSAGE_BEGIN(MSG_ONE_UNRELIABLE, gmsgBarTime2, nullptr, pPlayer->edict());
			EWRITE_SHORT(args[arg_time]);
			EWRITE_SHORT(args[arg_start_percent]);
		EMESSAGE_END();
		return TRUE;
	}

	pPlayer->CSPlayer()->SetProgressBarTime2(args[arg_time], args[arg_start_percent]);
	return TRUE;
}

/*
* Sends the message SendAudio - plays the specified audio
*
* @param index		Receiver index or use 0 for everyone
* @param sample		Sound file to play
* @param pitch		Sound pitch
*
* @noreturn
*
* native rg_send_audio(const index, const sample[], const pitch = PITCH_NORM);
*/
cell AMX_NATIVE_CALL rg_send_audio(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_sample, arg_pitch };

	int nIndex = params[arg_index];
	if (nIndex < 0)
		nIndex = 0;

	const char *szSample = getAmxString(amx, params[arg_sample]);
	auto pEdict = (nIndex == 0) ? nullptr : edictByIndexAmx(nIndex);

	EMESSAGE_BEGIN(nIndex ? MSG_ONE_UNRELIABLE : MSG_BROADCAST, gmsgSendAudio, nullptr, pEdict);
		EWRITE_BYTE(nIndex);
		EWRITE_STRING(szSample);
		EWRITE_SHORT(params[arg_pitch]);
	EMESSAGE_END();

	return TRUE;
}

AMX_NATIVE_INFO Misc_Natives_RG[] =
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

	{ "rg_create_entity", rg_create_entity },
	{ "rg_find_ent_by_class", rg_find_ent_by_class },
	{ "rg_find_ent_by_owner", rg_find_ent_by_owner },
	{ "rg_find_weapon_bpack_by_name", rg_find_weapon_bpack_by_name },
	{ "rg_has_item_by_name", rg_has_item_by_name },

	{ "rg_get_weapon_info", rg_get_weapon_info },
	{ "rg_set_weapon_info", rg_set_weapon_info },

	{ "rg_remove_all_items", rg_remove_all_items },
	{ "rg_remove_item", rg_remove_item },

	{ "rg_get_user_bpammo", rg_get_user_bpammo },
	{ "rg_set_user_bpammo", rg_set_user_bpammo },

	{ "rg_give_defusekit", rg_give_defusekit },

	{ "rg_get_user_armor", rg_get_user_armor },
	{ "rg_set_user_armor", rg_set_user_armor },

	{ "rg_set_user_team", rg_set_user_team },

	{ "rg_set_user_model", rg_set_user_model },
	{ "rg_reset_user_model", rg_reset_user_model },

	{ "rg_transfer_c4", rg_transfer_c4 },
	{ "rg_instant_reload_weapons", rg_instant_reload_weapons },

	{ "rg_set_account_rules", rg_set_account_rules },
	{ "rg_get_account_rules", rg_get_account_rules },

	{ "rg_is_bomb_planted", rg_is_bomb_planted },
	{ "rg_join_team", rg_join_team },
	{ "rg_balance_teams", rg_balance_teams },
	{ "rg_swap_all_players", rg_swap_all_players },
	{ "rg_switch_team", rg_switch_team },
	{ "rg_switch_weapon", rg_switch_weapon },
	{ "rg_get_join_team_priority", rg_get_join_team_priority },
	{ "rg_is_player_can_takedamage", rg_is_player_can_takedamage },
	{ "rg_get_weaponbox_id", rg_get_weaponbox_id },
	{ "rg_round_respawn", rg_round_respawn },

	{ "rg_send_bartime", rg_send_bartime },
	{ "rg_send_bartime2", rg_send_bartime2 },
	{ "rg_send_audio", rg_send_audio },

	{ nullptr, nullptr }
};

/*
* Set name of the map
*
* @param mapname	Change the name of the map.
*
* @noreturn
*
* native rh_set_mapname(const mapname[]);
*/
cell AMX_NATIVE_CALL rh_set_mapname(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_mapname };

	const char *mapname = getAmxString(amx, params[arg_mapname]);
	g_RehldsData->SetName(mapname);
	g_pFunctionTable->pfnResetGlobalState = ResetGlobalState;
	return TRUE;
}

enum MapNameType { MNT_TRUE, MNT_SET };

/*
* Get name of the map
*
* @param output		Buffer to copy mapname to
* @param len		Maximum buffer size
* @param type		MNT_SET return the name of the current map
*			MNT_TRUE return true the name of the current map independently of the set via rh_set_mapname
*
* @noreturn
*
* native rh_get_mapname(output[], len, MapNameType:type = MNT_SET);
*/
cell AMX_NATIVE_CALL rh_get_mapname(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_output, arg_len, arg_type };

	cell* dest = getAmxAddr(amx, params[arg_output]);
	size_t length = *getAmxAddr(amx, params[arg_len]);

	switch ((MapNameType)params[arg_type])
	{
	case MNT_TRUE:
		setAmxString(dest, g_szMapName, length);
		break;
	case MNT_SET:
		setAmxString(dest, g_RehldsData->GetName(), length);
		break;
	}

	return TRUE;
}

/*
* Reset to true map name
*
* @noreturn
*
* native rh_reset_mapname();
*/
cell AMX_NATIVE_CALL rh_reset_mapname(AMX *amx, cell *params)
{
	g_RehldsData->SetName(g_szMapName);
	g_pFunctionTable->pfnResetGlobalState = nullptr;
	return TRUE;
}

/*
* Emits a sound from an entity from the engine.
*
* @param entity		Entity index or use 0 to emit from worldspawn at the specified position
* @param recipients	Recipient index or use 0 to heard for all clients
* @param channel	Channel to emit from
* @param sample		Sound file to emit
* @param vol		Volume in percent
* @param attn		Sound attenuation
* @param flags		Emit flags
* @param pitch		Sound pitch
* @param emitFlags	Additional Emit2 flags, look at the defines like SND_EMIT2_*
* @param origin		Specify origin and only on "param" entity worldspawn that is 0
*
* @return		1 if successfully sounds are emitted, 0 otherwise
*
* native rh_emit_sound2(const entity, const recipient, const channel, const sample[], Float:vol = VOL_NORM, Float:attn = ATTN_NORM, const flags = 0, const pitch = PITCH_NORM, emitFlags = 0, const Float:origin[3] = {0.0,0.0,0.0});
*/
cell AMX_NATIVE_CALL rh_emit_sound2(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_entity, arg_recipient, arg_channel, arg_sample, arg_vol, arg_attn, arg_flags, arg_pitch, arg_emitFlags, arg_origin };

	CBaseEntity *pRecipient = getPrivate<CBaseEntity>(params[arg_recipient]);
	if (pRecipient && pRecipient->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_recipient]);
		return FALSE;
	}

	// ignore recipient of non-player
	if (params[arg_recipient] != 0 && pRecipient && !pRecipient->IsNetClient()) {
		return FALSE;
	}

	CAmxArgs args(amx, params);
	const char *sample = getAmxString(amx, params[arg_sample]);

	return (cell)g_RehldsFuncs->SV_EmitSound2
	(
		args[arg_entity],	// entity
		args[arg_recipient],	// recipient
		args[arg_channel],	// channel
		sample,			// sample
		args[arg_vol],		// volume
		args[arg_attn],		// attn
		args[arg_flags],	// flags
		args[arg_pitch],	// pitch
		args[arg_emitFlags],	// emitFlags
		args[arg_origin]	// pOrigin
	);
}

// TODO: should we duplicate documentation for native here and in include?
cell AMX_NATIVE_CALL rh_update_user_info(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_playerEntIndex };

	CBasePlayer *pPlayer = getPrivate<CBasePlayer>(params[arg_playerEntIndex]);
	if (pPlayer != nullptr && pPlayer->has_disconnected) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[arg_playerEntIndex]);
		return FALSE;
	}

	CAmxArgs args(amx, params);
	g_RehldsFuncs->SV_UpdateUserInfo(args[arg_playerEntIndex]);

	return TRUE;
}

AMX_NATIVE_INFO Misc_Natives_RH[] =
{
	{ "rh_set_mapname", rh_set_mapname },
	{ "rh_get_mapname", rh_get_mapname },
	{ "rh_reset_mapname", rh_reset_mapname },
	{ "rh_emit_sound2", rh_emit_sound2 },
	{ "rh_update_user_info", rh_update_user_info },

	{ nullptr, nullptr }
};

/*
* Check if the entity is valid
*
* @return		true/false
*
* native bool:is_entity(const entityIndex);
*/
cell AMX_NATIVE_CALL is_entity(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };

	int nIndex = params[arg_index];
	if (nIndex < 0 || nIndex > gpGlobals->maxEntities) {
		return FALSE;
	}

	auto pEntity = getPrivate<CBaseEntity>(nIndex);
	if (!pEntity) {
		return FALSE;
	}

	// if it is the index of the player
	if (pEntity->IsPlayer() && pEntity->has_disconnected) {
		return FALSE;
	}

	return TRUE;
}

/*
* Check if the rehlds is available
*
* @return		true/false
*
* native bool:is_rehlds();
*/
cell AMX_NATIVE_CALL is_rehlds(AMX *amx, cell *params)
{
	return (cell)api_cfg.hasReHLDS();
}

/*
* Check if the regamedll is available
*
* @return		true/false
*
* native bool:is_regamedll();
*/
cell AMX_NATIVE_CALL is_regamedll(AMX *amx, cell *params)
{
	return (cell)api_cfg.hasReGameDLL();
}

/*
* Check if the reunion is available
*
* @return		true/false
*
* native bool:is_has_reunion();
*/
cell AMX_NATIVE_CALL has_reunion(AMX *amx, cell *params)
{
	return (cell)api_cfg.hasReunion();
}

/*
* Check if the vtc is available
*
* @return		true/false
*
* native bool:is_has_vtc();
*/
cell AMX_NATIVE_CALL has_vtc(AMX *amx, cell *params)
{
	return (cell)api_cfg.hasVTC();
}

AMX_NATIVE_INFO Misc_Natives_Checks[] =
{
	{ "is_entity", is_entity },
	{ "is_rehlds", is_rehlds },
	{ "is_regamedll", is_regamedll },
	{ "has_reunion", has_reunion },
	{ "has_vtc", has_vtc }
};

void RegisterNatives_Misc()
{
	if (!api_cfg.hasReGameDLL())
		fillNatives(Misc_Natives_RG, [](AMX *amx, cell *params) -> cell { MF_LogError(amx, AMX_ERR_NATIVE, "%s: isn't available", "ReGameDll"); return FALSE; });

	if (!api_cfg.hasReHLDS())
		fillNatives(Misc_Natives_RH, [](AMX *amx, cell *params) -> cell { MF_LogError(amx, AMX_ERR_NATIVE, "%s: isn't available", "ReHlds"); return FALSE; });

	g_amxxapi.AddNatives(Misc_Natives_RG);
	g_amxxapi.AddNatives(Misc_Natives_RH);
	g_amxxapi.AddNatives(Misc_Natives_Checks);
}
