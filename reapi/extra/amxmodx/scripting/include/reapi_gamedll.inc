#if defined _reapi_gamedll_included
	#endinput
#endif

#define _reapi_gamedll_included

#include <reapi_gamedll_const>

/*
* Sets a value to an CSGameRules_Members members
*
* @param member		The specified member, look at the enum's with name CSGameRules_Members
*
* @return		1 on success.
*/
native set_member_game(CSGameRules_Members:member, any:...);

/*
* Returns a value from an CSGameRules_Members members
*
* @param member		The specified member, look at the enum's with name CSGameRules_Members
*
* @return		If an integer or boolean or one byte, array or everything else is passed via 3rd argument and more, look at argument list for specified member
*
*/
native any:get_member_game(CSGameRules_Members:member, any:...);

/*
* Sets a value to an entity's member
*
* @param index		Entity index
* @param member		The specified member, look at the enum's with name *_Members
*
* @return		1 on success.
*/
native set_member(const index, {CBaseEntity_Members, CBaseAnimating_Members, CBaseMonster_Members,
	CBasePlayer_Members, CCSPlayer_Members, CBasePlayerItem_Members, CBasePlayerWeapon_Members,
	CWeaponBox_Members, CArmoury_Members}:member, any:...);

/*
* Returns a value from an entity's member
*
* @param index		Entity index
* @param member		The specified member, look at the enum's with name *_Members
*
* @return		If an integer or boolean or one byte, array or everything else is passed via 3rd argument and more, look at argument list for specified member
*/
native any:get_member(const index, {CBaseEntity_Members, CBaseAnimating_Members, CBaseMonster_Members,
	CBasePlayer_Members, CCSPlayer_Members, CBasePlayerItem_Members, CBasePlayerWeapon_Members,
	CWeaponBox_Members, CArmoury_Members}:member, any:...);

/*
* Sets a playermove vars
*
* @param var		The specified playermove, look at the enum's PlayerMove
*
* @return		1 on success.
*/
native set_pmove(const PlayerMove:var, any:...);

/*
* Returns a playermove vars
*
* @param var		The specified playermove var, look at the enum's PlayerMove
*
* @return		If an integer or boolean or one byte, array or everything else is passed via 3rd argument and more, look at argument list for specified mvar
*/
native any:get_pmove(const PlayerMove:var, any:...);

/*
* Sets a movevars value to an playermove
*
* @param var		The specified mvar, look at the enum's MoveVars
*
* @return		1 on success.
*/
native set_movevar(const MoveVars:var, any:...);

/*
* Returns a movevars value from an playermove
*
* @param var		The specified mvar, look at the enum's MoveVars
*
* @return		If an integer or boolean or one byte, array or everything else is passed via 3rd argument and more, look at argument list for specified mvar
*/
native any:get_movevar(const MoveVars:var, any:...);

/*
* Sets a pmtrace vars
*
* @param var		The specified mvar, look at the enum's PMTrace
*
* @return		1 on success.
*/
native set_pmtrace(const tracehandle, const PMTrace:var, any:...);

/*
* Returns a pmtrace vars
*
* @param var		The specified mvar, look at the enum's PMTrace
*
* @return		If an integer or boolean or one byte, array or everything else is passed via 3rd argument and more, look at argument list for specified mvar
*/
native any:get_pmtrace(const tracehandle, const PMTrace:var, any:...);

/*
* Assign the number of the player animations.
*
* @param index		Client index
* @param playerAnim	Specific the number animation
*
* @noreturn
*/
native rg_set_animation(const index, PLAYER_ANIM:playerAnim);

/*
* Adds money to player's account.
*
* @param index		Client index
* @param amount		The amount of money
* @param bTrackChange	If the bTrackChange is 1, the amount of money added will also be displayed.
*
* @noreturn
*/
native rg_add_account(const index, amount, AccountSet:typeSet = AS_ADD, const bool:bTrackChange = true);

/*
* Gives item to player
*
* @param index		Client index
* @param pszName	Classname item
* @param type		Look at the enum's with name GiveType
*
* @return		Index of entity if successfully, -1 otherwise
*/
native rg_give_item(const index, const pszName[], GiveType:type = GT_APPEND);

/*
* Give the player default items
*
* @param index		Client index
*
* @noreturn
*/
native rg_give_default_items(const index);

/*
* Give the player shield
*
* @param index		Client index
* @param bDeploy	to get shield from holster
*
* @noreturn
*/
native rg_give_shield(const index, const bool:bDeploy = true);

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
*/
native rg_dmg_radius(Float:vecSrc[3], const inflictor, const attacker, const Float:flDamage, const Float:flRadius, const iClassIgnore, const bitsDamageType);

/*
* Resets the global multi damage accumulator
*
* @noreturn
*/
native rg_multidmg_clear();

/*
* Inflicts contents of global multi damage register on victim
*
* @param inflictor	Inflictor is the entity that caused the damage (such as a gun)
* @param attacker	Attacker is the entity that tirggered the damage (such as the gun's owner).
*
* @noreturn
*/
native rg_multidmg_apply(const inflictor, const attacker);

/*
* Adds damage the accumulator
*
* @param inflictor	Inflictor is the entity that caused the damage (such as a gun)
* @param victim		A victim that takes damage
* @param flDamage	The amount of damage
* @param bitsDamageType	Damage type DMG_*
*
* @noreturn
*/
native rg_multidmg_add(const inflictor, const victim, const Float:flDamage, const bitsDamageType);

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
* @param iBulletType		Bullet type, look at the enum's with name Bullet cssdk_const.inc
* @param iTracerFreq		Tracer frequancy
* @param iDamage		Damage amount
*
* @noreturn
*/
native rg_fire_bullets(const inflictor, const attacker, const shots, Float:vecSrc[3], Float:vecDirShooting[3], Float:vecSpread[3], const Float:flDistance, const Bullet:iBulletType, const iTracerFreq, const iDamage);

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
* @param iBulletType		Bullet type, look at the enum's with name Bullet cssdk_const.inc
* @param iDamage		Damage amount
* @param flRangeModifier	Damage range modifier
* @param bPistol		Pistol shot
* @param shared_rand		Use player's random seed, get circular gaussian spread
*
* @return Float:[3]		The result spread
*/
native Float:[3] rg_fire_bullets3(const inflictor, const attacker, Float:vecSrc[3], Float:vecDirShooting[3], const Float:vecSpread, const Float:flDistance, const iPenetration, const Bullet:iBulletType, const iDamage, const Float:flRangeModifier, const bool:bPistol, const shared_rand);

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
*/
native rg_round_end(const Float:tmDelay, const WinStatus:st, const ScenarioEventEndRound:event = ROUND_NONE, const message[] = "default", const sentence[] = "default");

/*
* Update current scores
*
* @param iCtsWins		The amount of wins to won
* @param iTsWins		The amount of wins to won
* @param bAdd			Adds the score to the current amount wins.
*
* @noreturn
*/
native rg_update_teamscores(const iCtsWins = 0, const iTsWins = 0, const bool:bAdd = true);

/*
* Creates an entity using Counter-Strike's custom CreateNamedEntity wrapper.
*
* @param classname		Entity classname
* @param useHashTable		Use this only for known game entities.
*				NOTE: Do not use this if you use a custom classname.
*
* @return			Index of the created entity or 0 otherwise
*
*/
native rg_create_entity(const classname[], const bool:useHashTable = false);

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
*/
native rg_find_ent_by_class(start_index, const classname[], const bool:useHashTable = false);

/*
* Finds an entity in the world using Counter-Strike's custom FindEntityByString wrapper, matching by owner.
*
* @param start_index		Entity index to start searching from. -1 to start from the first entity
* @param classname		Classname to search for
*
* @return			1 if found, 0 otherwise
*
*/
native rg_find_ent_by_owner(&start_index, const classname[], owner);

/*
* Find the weapon by name in the player's inventory.
*
* @param index			Client index
* @param weapon			Weapon name
*
* @return			Entity-index of weapon, 0 otherwise
*
*/
native rg_find_weapon_bpack_by_name(const index, const weapon[]);

/*
* Check if the player already have this item.
*
* @param index			Client index
* @param item			Item name
*
* @return			1 if successfully, 0 otherwise
*
*/
native bool:rg_has_item_by_name(const index, const item[]);

/*
* Returns some information about a weapon.
*
* @param weapon name or id	Weapon id, see WEAPON_* constants WeaponIdType or weapon_* name
* @param WpnInfo:type		Info type, see WI_* constants
*
* @return			Weapon information value
* @error			If weapon_id and type are out of bound, an error will be thrown.
*
*/
native any:rg_get_weapon_info(any:...);

/*
* Sets specific values of weapons info.
*
* @param weapon_id	Weapon id, see WEAPON_* constants
* @param type		Info type, see WI_* constants
*
* @return		1 if successfully, 0 otherwise
*
*/
native rg_set_weapon_info(const {WeaponIdType,_}:weapon_id, WpnInfo:type, any:...);

/*
* Remove all the player's stuff by specific slot.
*
* @param index		Client index
* @param slot		Specific slot for remove of each item.
*
* @return		1 if successfully, 0 otherwise
*
*/
native rg_remove_items_by_slot(const index, const InventorySlotType:slot);

/*
* Drop to floor all the player's stuff by specific slot.
*
* @param index		Client index
* @param slot		Specific slot for remove of each item.
*
* @return		1 if successfully, 0 otherwise
*
*/
native rg_drop_items_by_slot(const index, const InventorySlotType:slot);

/*
* Remove all the player's stuff.
*
* @param index		Client index
* @param removeSuit	Remove suit
*
* @return		1 if successfully, 0 otherwise
*
*/
native rg_remove_all_items(const index, const bool:removeSuit = false);

/*
* Drop specifed the player's item by classname.
*
* @param index		Client index
* @param item_name	Classname of item
*
* @return		1 if successfully, 0 otherwise
*
*/
native rg_drop_item(const index, const item_name[]);

/*
* Execute a client command on the gamedll side.
*
* @param index		Client index
* @param command	Client command to execute on
* @param arg		Optional command arguments
*
* @return		1 if successfully, 0 otherwise
*
*/
native rg_internal_cmd(const index, const cmd[], const arg[] = "");

/*
* Remove specifed the player's item by classname
*
* @param index		Client index
* @param item_name	Classname of item
*
* @return		1 if found and remove, 0 otherwise
*
*/
native rg_remove_item(const index, const item_name[]);

/*
* Returns amount of ammo in the client's backpack for a specific weapon.
*
* @param index		Client index
* @param weapon		Weapon id
*
* @return		Amount of ammo in backpack
*
*/
native rg_get_user_bpammo(const index, WeaponIdType:weapon);

/*
* Sets amount of ammo in the client's backpack for a specific weapon.
*
* @param index		Client index
* @param weapon		Weapon id
* @param amount		New backpack ammo amount to set
*
* @noreturn
*
*/
native rg_set_user_bpammo(const index, WeaponIdType:weapon, amount);

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
*/
native rg_give_defusekit(const index, const bool:bDefusekit = true, const Float:color[] = {0.0, 160.0, 0.0}, const icon[] = "defuser", const bool:bFlash = false);

/*
* Returns the client's armor value and retrieves the type of armor.
*
* @param index		Client index
* @param armortype	Variable to store armor type in
*
* @return		Amount of armor, 0 if client has no armor
*
*/
native rg_get_user_armor(const index, &ArmorType:armortype);

/*
* Sets the client's armor value the type of armor.
*
* @param index		Client index
* @param armorvalue	Amount of armor to set
* @param armortype	Armor type
*
* @noreturn
*
*/
native rg_set_user_armor(const index, armorvalue, ArmorType:armortype);

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
*/
native rg_set_user_team(const index, {TeamName,_}:team, {ModelName,_}:model = MODEL_AUTO, const bool:send_teaminfo = true);

/*
* Sets the client's player model.
*
* @param index		Client index
* @param model		Model name
* @param update_index	If true, the modelindex is updated as well
*
* @return		1 if successfully, 0 otherwise
*
*/
native rg_set_user_model(const index, const model[], const bool:update_index = false);

/*
* Reset model user
*
* @param index		Client index
* @param update_index	If true, the modelindex is reseted as well
*
* @return		1 if successfully, 0 otherwise
*
*/
native rg_reset_user_model(const index, const bool:update_index = false);

/*
* Enable/Disable footsteps of the player.
*
* @param index		Client index
* @param silent		To enable silent footsteps of player's
*
* @return		1 if successfully, 0 otherwise
*
*/
native rg_set_user_footsteps(const index, bool:silent = false);

/*
* Get the current state footsteps of the player.
*
* @param index		Client index
*
* @return		1 if have silent footsteps, 0 otherwise
*
*/
native rg_get_user_footsteps(const index);

/*
* Transfer C4 to player
*
* @param index		Client index
* @param receiver	Receiver index, if 0 so will transfer a random to player
*
* @return		1 if successfully, 0 otherwise
*
*/
native rg_transfer_c4(const index, const receiver = 0);

/*
* Instant reload weapons
*
* @param index		Client index
* @param weapon		Weapon entity-index, if 0 then all the weapons
*
* @return		1 if successfully, 0 otherwise
*
*/
native rg_instant_reload_weapons(const index, const weapon = 0);

/*
* Sets the amount of reward in the game account for all players.
*
* @param rules_index	Look at the enum's with name RewardRules
* @param amount		The amount money
*
* @noreturn
*
*/
native rg_set_account_rules(const RewardRules:rules_index, const amount);

/*
* Get the amount of reward from account
*
* @param rules_index	Look at the enum's with name RewardRules
*
* @return		The amount of reward from account
*
*/
native rg_get_account_rules(const RewardRules:rules_index);

/*
* If the bomb is planted
*
* @return		true if bomb is planted, false otherwise
*
*/
native bool:rg_is_bomb_planted();

/*
* Join team
*
* @param index		Client index
* @param team		Team id
*
* @return		1 if successfully joined the team, 0 otherwise
*
*/
native rg_join_team(const index, const TeamName:team);

/*
* Instantly balances the team.
*
* @noreturn
*
*/
native rg_balance_teams();

/*
* To swap players, without reset frags/deaths and the amount wins.
*
* @noreturn
*
*/
native rg_swap_all_players();

/*
* Instantly switches to the opposite team for one player.
* @note Switch from CT to TERRORIST also opposite.
*
* @param index		Client index
*
* @noreturn
*
*/
native rg_switch_team(const index);

/*
* Switch to specific weapon
*
* @param index		Client index
* @param weapon		Weapon entity-index
*
* @return		1 if successfully switched, 0 otherwise
*
*/
native rg_switch_weapon(const index, const weapon);

/*
* To get which team has a high priority to join.
*
* @return		Returns the Team Name
*
*/
native TeamName:rg_get_join_team_priority();

/*
* Can this player take damage from this attacker?
*
* @param index		Client index
* @param attacker	Attacker index
*
* @return		true if can take a damage, false otherwise
*
*/
native bool:rg_is_player_can_takedamage(const index, const attacker);

/*
* To get WeaponIdType from weaponbox
*
* @param entity		Weaponbox entity
*
* @return		return enum's of WeaponIdType
*
*/
native WeaponIdType:rg_get_weaponbox_id(const entity);

/*
* Respawn on round for players/bots
*
* @param index		Client index
*
* @noreturn
*
*/
native rg_round_respawn(const index);

/*
* Reset player maxspeed
*
* @param index		Client index
*
* @noreturn
*
*/
native rg_reset_maxspeed(const index);

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
*/
native rg_send_bartime(const index, const duration, const bool:observer = true);

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
*/
native rg_send_bartime2(const index, const duration, const startPercent, const bool:observer = true);

/*
* Sends the message SendAudio - plays the specified audio
*
* @param index		Receiver index or use 0 for everyone
* @param sample		Sound file to play
* @param pitch		Sound pitch
*
* @noreturn
*
*/
native rg_send_audio(const index, const sample[], const pitch = PITCH_NORM);
