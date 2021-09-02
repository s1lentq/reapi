#if defined _reapi_gamedll_included
	#endinput
#endif

#define _reapi_gamedll_included

#include <reapi_gamedll_const>

/*
* Sets Think callback for entity
*
* @param entity     Entity index
* @param callback   The forward to call
* @param params     Optional set of data to pass through to callback
* @param len        Optional size of data
*
* @note Use "" to reset callback
* @note Callback should be contains passing arguments as "public Think_Callback(const ent)"
*
* @noreturn
*/
native SetThink(const ent, const callback[], const params[] = "", const len = 0);

/*
* Sets Touch callback for entity
*
* @param entity     Entity index
* @param callback   The forward to call
* @param params     Optional set of data to pass through to callback
* @param len        Optional size of data
*
* @note Use "" to reset callback
* @note Callback should be contains passing arguments as "public Touch_Callback(const ent, const other)"
*
* @noreturn
*/
native SetTouch(const ent, const callback[], const params[] = "", const len = 0);

/*
* Sets Use callback for entity
*
* @param entity     Entity index
* @param callback   The forward to call
* @param params     Optional set of data to pass through to callback
* @param len        Optional size of data
*
* @note Use "" to reset callback
* @note Callback should be contains passing arguments as "public Use_Callback(const ent, const activator, const caller, USE_TYPE:useType, Float:value)"
*
* @noreturn
*/
native SetUse(const ent, const callback[], const params[] = "", const len = 0);

/*
* Sets Blocked callback for entity
*
* @param entity     Entity index
* @param callback   The forward to call
* @param params     Optional set of data to pass through to callback
* @param len        Optional size of data
*
* @note Use "" to reset callback
* @note Callback should be contains passing arguments as "public Blocked_Callback(const ent, const other)"
*
* @noreturn
*/
native SetBlocked(const ent, const callback[], const params[] = "", const len = 0);

/*
* Sets MoveDone callback for entity
*
* @param entity     Entity index
* @param callback   The forward to call
* @param params     Optional set of data to pass through to callback
* @param len        Optional size of data
*
* @note Use "" to reset callback
* @note Entity should be inherited from CBaseToggle, otherwise server can crash
* @note Callback should be contains passing arguments as "public MoveDone_Callback(const ent)"
*
* @noreturn
*/
native SetMoveDone(const ent, const callback[], const params[] = "", const len = 0);

/*
* Sets a value to CSGameRules_Members members.
*
* @param member     The specified member, look at the enums with name CSGameRules_Members
*
* @return           1 on success.
*/
native set_member_game(CSGameRules_Members:member, any:...);

/*
* Returns a value from CSGameRules_Members members
*
* @param member     The specified member, look at the enums with name CSGameRules_Members
*
* @return           If an integer or boolean or one byte, array or everything else is passed via the 3rd argument and more, look at the argument list for the specified member
*/
native any:get_member_game(CSGameRules_Members:member, any:...);

/*
* Sets a value to an entity's member.
*
* @param index      Entity index
* @param member     The specified member, look at the enums with name *_Members
*
* @return           1 on success.
*/
native set_member(const index, any:member, any:...);

/*
* Returns a value from an entity's member.
*
* @param index      Entity index
* @param member     The specified member, look at the enums with name *_Members
*
* @return           If an integer or boolean or one byte, array or everything else is passed via the 3rd argument and more, look at the argument list for the specified member
*/
native any:get_member(const index, any:member, any:...);

/*
* Sets a value to an entity's member.
* Safe version, can guarantee that the present member is refers to derived class of the entity.
*
* @param index      Entity index
* @param member     The specified member, look at the enums with name *_Members
*
* @return           1 on success.
*/
native set_member_s(const index, any:member, any:...);

/*
* Returns a value from an entity's member.
* Safe version, can guarantee that the present member is refers to derived class of the entity.
*
* @param index      Entity index
* @param member     The specified member, look at the enums with name *_Members
*
* @return           If an integer or boolean or one byte, array or everything else is passed via the 3rd argument and more, look at the argument list for the specified member
*/
native any:get_member_s(const index, any:member, any:...);

/*
* Sets playermove var.
*
* @param var        The specified playermove, look at the enum PlayerMove
*
* @return           1 on success.
*/
native set_pmove(const PlayerMove:var, any:...);

/*
* Returns a playermove var.
*
* @param var        The specified playermove var, look at the enums PlayerMove
*
* @return           If an integer or boolean or one byte, array or everything else is passed via the 3rd argument and more, look at the argument list for the specified mvar
*/
native any:get_pmove(const PlayerMove:var, any:...);

/*
* Sets a movevar value to a playermove.
*
* @param var        The specified mvar, look at the enum MoveVars
*
* @return           1 on success.
*/
native set_movevar(const MoveVars:var, any:...);

/*
* Returns a movevar value from a playermove.
*
* @param var        The specified mvar, look at the enum MoveVars
*
* @return           If an integer or boolean or one byte, array or everything else is passed via the 3rd argument and more, look at the argument list for the specified mvar
*/
native any:get_movevar(const MoveVars:var, any:...);

/*
* Sets a pmtrace var.
*
* @param var        The specified mvar, look at the enum PMTrace
*
* @return           1 on success.
*/
native set_pmtrace(const tracehandle, const PMTrace:var, any:...);

/*
* Returns a pmtrace var
*
* @param var        The specified mvar, look at the enum PMTrace
*
* @return           If an integer or boolean or one byte, array or everything else is passed via the 3rd argument and more, look at the argument list for the specified mvar
*/
native any:get_pmtrace(const tracehandle, const PMTrace:var, any:...);

/*
* Sets a RebuyStruct member.
*
* @param var        The specified RebuyStruct, look at the enum RebuyStruct
*
* @return           1 on success.
*/
native set_rebuy(const RebuyHandle:rebuyhandle, const RebuyStruct:member, any:value);

/*
* Returns a RebuyStruct member
*
* @param var        The specified RebuyStruct, look at the enum RebuyStruct
*
* @return           If an integer or boolean or one byte, array or everything else is passed via the 3rd argument and more, look at the argument list for the specified RebuyStruct
*/
native any:get_rebuy(const RebuyHandle:rebuyhandle, RebuyStruct:member);

/*
* Assign the number of the player's animation.
*
* @param index          Client index
* @param playerAnim     Specific animation number
*
* @noreturn
*/
native rg_set_animation(const index, PLAYER_ANIM:playerAnim);

/*
* Adds money to player's account.
*
* @param index          Client index
* @param amount         The amount of money
* @param bTrackChange   If bTrackChange is 1, the amount of money added will also be displayed.
*
* @noreturn
*/
native rg_add_account(const index, amount, AccountSet:typeSet = AS_ADD, const bool:bTrackChange = true);

/*
* Gives the player an item.
*
* @param index      Client index
* @param pszName    Item classname
* @param type       Look at the enums with name GiveType
*
* @return           Index of entity if successfull, -1 otherwise
*/
native rg_give_item(const index, const pszName[], GiveType:type = GT_APPEND);

/*
* Gives the player an custom item, this means that don't handled API things.
*
* @example rg_give_custom_item(id, "weapon_c4"); doesn't sets the member m_bHasC4 to true, as the rg_give_item does.
*
* @param index      Client index
* @param pszName    Item classname
* @param type       Look at the enums with name GiveType
* @param uid        Sets a unique index for the entity
*
* @return           Index of entity if successfull, -1 otherwise
*
*/
native rg_give_custom_item(const index, const pszName[], GiveType:type = GT_APPEND, const uid = 0);

/*
* Give the default items to a player.
*
* @param index      Client index
*
* @noreturn
*/
native rg_give_default_items(const index);

/*
* Gives the player a shield
*
* @param index          Client index
* @param bDeploy        To deploy the shield
*
* @noreturn
*/
native rg_give_shield(const index, const bool:bDeploy = true);

/*
* Inflicts damage in a radius from the source position.
*
* @param vecSrc             The source position
* @param inflictor          Inflictor is the entity that caused the damage (such as a gun)
* @param attacker           Attacker is the entity that triggered the damage (such as the gun's owner)
* @param flDamage           The amount of damage
* @param flRadius           Damage radius
* @param iClassIgnore       To specify classes that are immune to damage
* @param bitsDamageType     Damage type DMG_*
*
* @noreturn
*/
native rg_dmg_radius(Float:vecSrc[3], const inflictor, const attacker, const Float:flDamage, const Float:flRadius, const iClassIgnore, const bitsDamageType);

/*
* Resets the global multi damage accumulator.
*
* @noreturn
*/
native rg_multidmg_clear();

/*
* Inflicts contents of global multi damage registered on victim.
*
* @param inflictor      Inflictor is the entity that caused the damage (such as a gun)
* @param attacker       Attacker is the entity that triggered the damage (such as the gun's owner)
*
* @noreturn
*/
native rg_multidmg_apply(const inflictor, const attacker);

/*
* Adds damage to the accumulator.
*
* @param inflictor          Inflictor is the entity that caused the damage (such as a gun)
* @param victim             The victim that takes damage
* @param flDamage           The amount of damage
* @param bitsDamageType     Damage type DMG_*
*
* @noreturn
*/
native rg_multidmg_add(const inflictor, const victim, const Float:flDamage, const bitsDamageType);

/*
* Fires bullets from entity.
*
* @param inflictor          Inflictor is the entity that caused the damage (such as a gun)
* @param attacker           Attacker is the entity that triggered the damage (such as the gun's owner)
* @param shots              The number of shots
* @param vecSrc             The source position of the barrel
* @param vecDirShooting     Shooting direction
* @param vecSpread          Spread
* @param flDistance         Max shot distance
* @param iBulletType        Bullet type, look at the enum with name Bullet in cssdk_const.inc
* @param iTracerFreq        Tracer frequency
* @param iDamage            Damage amount
*
* @noreturn
*/
native rg_fire_bullets(const inflictor, const attacker, const shots, Float:vecSrc[3], Float:vecDirShooting[3], Float:vecSpread[3], const Float:flDistance, const Bullet:iBulletType, const iTracerFreq, const iDamage);

/*
* Fires buckshots from entity.
*
* @param inflictor          Inflictor is the entity that caused the damage (such as a gun)
* @param attacker           Attacker is the entity that triggered the damage (such as the gun's owner)
* @param shots              The number of shots
* @param vecSrc             The source position of the barrel
* @param vecDirShooting     Shooting direction
* @param vecSpread          Spread
* @param flDistance         Max shot distance
* @param iTracerFreq        Tracer frequency
* @param iDamage            Damage amount
*
* @noreturn
*/
native rg_fire_buckshots(const inflictor, const attacker, const shots, Float:vecSrc[3], Float:vecDirShooting[3], Float:vecSpread[3], const Float:flDistance, const iTracerFreq, const iDamage);

/*
* Fires bullets from player's weapon.
*
* @param inflictor          Inflictor is the entity that caused the damage (such as a gun)
* @param attacker           Attacker is the entity that triggered the damage (such as the gun's owner)
* @param vecSrc             The source position of the barrel
* @param vecDirShooting     Shooting direction
* @param vecSpread          Spread
* @param flDistance         Max shot distance
* @param iPenetration       The amount of penetration
* @param iBulletType        Bullet type, look at the enum with name Bullet in cssdk_const.inc
* @param iDamage            Damage amount
* @param flRangeModifier    Damage range modifier
* @param bPistol            Pistol shot
* @param shared_rand        Use player's random seed, get circular gaussian spread
*
* @return Float:[3]         The spread result
*/
native Float:[3] rg_fire_bullets3(const inflictor, const attacker, Float:vecSrc[3], Float:vecDirShooting[3], const Float:vecSpread, const Float:flDistance, const iPenetration, const Bullet:iBulletType, const iDamage, const Float:flRangeModifier, const bool:bPistol, const shared_rand);

/*
* Forces the round to end.
*
* @param tmDelay    Delay before the onset of a new round
* @param st         Which team won
* @param event      The event is the end of the round
* @param message    The message on round end
* @param sentence   The sound at the end of the round
* @param trigger    This will trigger to all hooks on that function
*                   Be very careful about recursion!
*
* @return           1 on success, 0 otherwise
*/
native rg_round_end(const Float:tmDelay, const WinStatus:st, const ScenarioEventEndRound:event = ROUND_NONE, const message[] = "default", const sentence[] = "default", const bool:trigger = false);

/*
* Updates current scores.
*
* @param iCtsWins   The amount of wins for counter-terrorists
* @param iTsWins    The amount of wins for terrorists
* @param bAdd       Adds the score to the current amount
*
* @noreturn
*/
native rg_update_teamscores(const iCtsWins = 0, const iTsWins = 0, const bool:bAdd = true);

/*
* Creates an entity using Counter-Strike's custom CreateNamedEntity wrapper.
*
* @param classname      Entity classname
* @param useHashTable   Use this only for known game entities
*
* @note: Do not use this if you use a custom classname
*
* @return               Index of the created entity or 0 otherwise
*/
native rg_create_entity(const classname[], const bool:useHashTable = false);

/*
* Finds an entity in the world using Counter-Strike's custom FindEntityByString wrapper.
*
* @param start_index        Entity index to start searching from. -1 to start from the first entity
* @param classname          Classname to search for
* @param useHashTable       Use this only for known game entities
*
* @note: Do not use this if you use a custom classname
*
* @return                   Entity index > 0 if found, 0 otherwise
*/
native rg_find_ent_by_class(start_index, const classname[], const bool:useHashTable = false);

/*
* Finds an entity in the world using Counter-Strike's custom FindEntityByString wrapper, matching by owner.
*
* @param start_index    Entity index to start searching from. -1 to start from the first entity
* @param classname      Classname to search for
*
* @return               1 if found, 0 otherwise
*/
native rg_find_ent_by_owner(&start_index, const classname[], owner);

/*
* Finds the weapon by name in the player's inventory.
*
* @param index      Client index
* @param weapon     Weapon name
*
* @return           Weapon's entity index, 0 otherwise
*/
native rg_find_weapon_bpack_by_name(const index, const weapon[]);

/*
* Checks if the player has the item.
*
* @param index      Client index
* @param item       Item name
*
* @return           true if he does, false otherwise
*/
native bool:rg_has_item_by_name(const index, const item[]);

/*
* Returns specific information about the weapon.
*
* @param weapon name or id      Weapon id, see WEAPON_* constants, WeaponIdType or weapon_* name
* @param WpnInfo:type           Info type, see WI_* constants
*
* @return                       Weapon information
* @error                        If weapon_id or type are out of bounds, an error will be thrown
*/
native any:rg_get_weapon_info(any:...);

/*
* Sets specific weapon info values.
*
* @param weapon_id      Weapon id, see WEAPON_* constants
* @param type           Info type, see WI_* constants
*
* @return               1 on success, 0 otherwise
*/
native rg_set_weapon_info(const {WeaponIdType,_}:weapon_id, WpnInfo:type, any:...);

/*
* Remove all the player's stuff in a specific slot.
*
* @param index  Client index
* @param slot   The slot that will be emptied
*
* @return       1 on success, 0 otherwise
*/
native rg_remove_items_by_slot(const index, const InventorySlotType:slot);

/*
* Drop to floor all the player's stuff by specific slot.
*
* @param index      Client index
* @param slot       Specific slot for remove of each item.
*
* @return           1 on success, 0 otherwise
*/
native rg_drop_items_by_slot(const index, const InventorySlotType:slot);

/*
* Remove all of the player's items.
*
* @param index      Client index
* @param removeSuit Remove suit
*
* @return           1 on success, 0 otherwise
*/
native rg_remove_all_items(const index, const bool:removeSuit = false);

/*
* Forces the player to drop the specified item classname.
*
* @param index      Client index
* @param item_name  Item classname
*
* @return           1 on success, 0 otherwise
*
*/
native rg_drop_item(const index, const item_name[]);

/*
* Executes a client command on the gamedll side.
*
* @param index      Client index
* @param command    Client command to execute
* @param arg        Optional command arguments
*
* @return           1 on success, 0 otherwise
*/
native rg_internal_cmd(const index, const cmd[], const arg[] = "");

/*
* Removes the specified item classname from the player
*
* @param index      Client index
* @param item_name  Item classname
* @param removeAmmo Remove ammunition
*
* @return           1 if found and remove, 0 otherwise
*/
native rg_remove_item(const index, const item_name[], const bool:removeAmmo = false);

/*
* Sets the amount of ammo in the client's backpack for a specific weapon.
*
* @param index      Client index
* @param weapon     Weapon id
* @param amount     New backpack ammo amount to set
*
* @noreturn
*/
native rg_set_user_bpammo(const index, WeaponIdType:weapon, amount);

/*
* Returns the amount of ammo in the client's backpack for a specific weapon.
*
* @param index      Client index
* @param weapon     Weapon id
*
* @return           Amount of ammo in backpack
*/
native rg_get_user_bpammo(const index, WeaponIdType:weapon);

/*
* Sets the amount of clip ammo for a specific weapon.
*
* @param index      Client index
* @param weapon     Weapon id
* @param amount     New clip ammo amount to set
*
* @noreturn
*/
native rg_set_user_ammo(const index, WeaponIdType:weapon, amount);

/*
* Returns the amount of clip ammo for a specific weapon.
*
* @param index      Client index
* @param weapon     Weapon id
*
* @return           Amount of clip ammo
*/
native rg_get_user_ammo(const index, WeaponIdType:weapon);

/*
* Sets the client's defusekit status and allows to set a custom HUD icon and color.
*
* @param index      Client index
* @param defusekit  If nonzero the client will have a defusekit, otherwise it will be removed
* @param color      Color RGB
* @param icon       HUD sprite to use as an icon
* @param flash      If nonzero the icon will flash red
*
* @noreturn
*/
native rg_give_defusekit(const index, const bool:bDefusekit = true, const Float:color[] = {0.0, 160.0, 0.0}, const icon[] = "defuser", const bool:bFlash = false);

/*
* Returns the client's armor value and retrieves the type of armor.
*
* @param index        Client index
* @param armortype    Variable to store armor type in
*
* @return             Amount of armor, 0 if the client has no armor
*/
native rg_get_user_armor(const index, &ArmorType:armortype = ARMOR_NONE);

/*
* Sets the client's armor value and the type of armor.
*
* @param index          Client index
* @param armorvalue     Amount of armor to set
* @param armortype      Armor type to set
*
* @noreturn
*/
native rg_set_user_armor(const index, armorvalue, ArmorType:armortype);

/*
* Sets the client's team without killing the player and sets the client's model.
* @note To obtain a TeamName use the following:
*       new TeamName:team = get_member(id, m_iTeam);
*
* @param index          Client index
* @param team           Team id
* @param model          Internal model, use MODEL_AUTO for a random appearance or MODEL_UNASSIGNED to not update it
*
* @param send_teaminfo          If true, a TeamInfo message will be sent
* @param check_win_conditions   If true, a CheckWinConditions will be call
*
* @return               1 on success, 0 otherwise
*/
native rg_set_user_team(const index, {TeamName,_}:team, {ModelName,_}:model = MODEL_AUTO, const bool:send_teaminfo = true, const bool:check_win_conditions = false);

/*
* Sets the client's player model.
*
* @param index          Client index
* @param model          Model name
* @param update_index   If true, the modelindex is updated as well
*
* @return               1 on success, 0 otherwise
*/
native rg_set_user_model(const index, const model[], const bool:update_index = false);

/*
* Resets the client's model.
*
* @param index          Client index
* @param update_index   If true, the modelindex is reset as well
*
* @return               1 on success, 0 otherwise
*/
native rg_reset_user_model(const index, const bool:update_index = false);

/*
* Enable/Disable player's footsteps.
*
* @param index      Client index
* @param silent     To enable silent footsteps
*
* @return           1 on success, 0 otherwise
*/
native rg_set_user_footsteps(const index, bool:silent = false);

/*
* Get the current footsteps state of the player.
*
* @param index      Client index
*
* @return           1 if the player has silent footsteps, 0 otherwise
*/
native rg_get_user_footsteps(const index);

/*
* Transfers C4 from one player to another.
*
* @param index      Client index
* @param receiver   Receiver index, if 0 it will transfer to a random player
*
* @return           1 on success, 0 otherwise
*/
native rg_transfer_c4(const index, const receiver = 0);

/*
* Instantly reload client's weapons.
*
* @param index      Client index
* @param weapon     Weapon entity-index, if 0 then all weapons will be reloaded
*
* @return           1 on success, 0 otherwise
*/
native rg_instant_reload_weapons(const index, const weapon = 0);

/*
* Plant a bomb.
*
* @param index      Owner index or 0 for worldspawn.
* @param origin     The origin of the bomb where it will be planted.
* @param angles     The angles of the planted bomb.
*
* @return           Index of bomb entity or AMX_NULLENT (-1) otherwise
*/
native rg_plant_bomb(const index, Float:vecOrigin[3], Float:vecAngles[3] = {0.0,0.0,0.0});

/*
* Sets the amount of reward in the game account for all players.
*
* @param rules_index    Look at the enum with name RewardRules
* @param amount         The money amount
*
* @noreturn
*/
native rg_set_account_rules(const RewardRules:rules_index, const amount);

/*
* Gets the specified reward rule's money amount.
*
* @param rules_index    Look at the enum with name RewardRules
*
* @return               The amount of reward
*
*/
native rg_get_account_rules(const RewardRules:rules_index);

/*
* Checks if the bomb is planted.
*
* @return           true if the bomb is planted, false otherwise
*/
native bool:rg_is_bomb_planted();

/*
* Forces a player to join a team.
*
* @param index      Client index
* @param team       Team id
*
* @return           1 on success, 0 otherwise
*/
native rg_join_team(const index, const TeamName:team);

/*
* Instantly balances the teams.
*
* @noreturn
*/
native rg_balance_teams();

/*
* Swaps players' teams without reseting frags, deaths and wins.
*
* @noreturn
*/
native rg_swap_all_players();

/*
* Instantly switches the player to his opposite team.
* @note Switch from CT to TERRORIST is also opposite.
*
* @param index      Client index
*
* @noreturn
*/
native rg_switch_team(const index);

/*
* Forces the player to switch to a specific weapon.
*
* @param index      Client index
* @param weapon     Weapon entity-index
*
* @return           1 on success, 0 otherwise
*/
native rg_switch_weapon(const index, const weapon);

/*
* Gets which team has a higher join priority.
*
* @return           Returns the Team Name
*/
native TeamName:rg_get_join_team_priority();

/*
* Checks whether the player can take damage from the attacker.
*
* @param index      Client index
* @param attacker   Attacker index
*
* @return           true if player can take damage, false otherwise
*/
native bool:rg_is_player_can_takedamage(const index, const attacker);

/*
* Checks whether the player can respawn.
*
* @param index      Client index
*
* @return           true if player can respawn, false otherwise
*/
native bool:rg_is_player_can_respawn(const index);

/*
* Gets WeaponIdType from weaponbox
*
* @param entity     Weaponbox entity
*
* @return           return enum of WeaponIdType
*/
native WeaponIdType:rg_get_weaponbox_id(const entity);

/*
* Respawn on round for players/bots.
*
* @param index      Client index
*
* @noreturn
*/
native rg_round_respawn(const index);

/*
* Resets player's maxspeed.
*
* @param index      Client index
*
* @noreturn
*/
native rg_reset_maxspeed(const index);

/*
* Draws a HUD progress bar which fills from 0% to 100% for the time duration in seconds.
* @note: Set the duration to 0 to hide the bar.
*
* @param index      Client index
* @param time       Duration
* @param observer   Send for everyone who is observing the player
*
* @noreturn
*/
native rg_send_bartime(const index, const duration, const bool:observer = true);

/*
* Same as BarTime, but StartPercent specifies how much of the bar is (already) filled.
*
* @param index          Client index
* @param time           Duration
* @param startPercent   Start percent
* @param observer       Send for everyone who is observing the player
*
* @noreturn
*/
native rg_send_bartime2(const index, const duration, const startPercent, const bool:observer = true);

/*
* Sends the SendAudio message - plays the specified audio.
*
* @param index      Receiver index or use 0 for everyone
* @param sample     Sound file to play
* @param pitch      Sound pitch
*
* @noreturn
*/
native rg_send_audio(const index, const sample[], const pitch = PITCH_NORM);

/**
* Sets a parameter of the member CSPlayerItem::m_ItemInfo
*
* @param entity Entity index
* @param type   Item info type. See ItemInfo constants.
*
*/
native rg_set_iteminfo(const entity, ItemInfo:type, any:...);

/**
* Gets a parameter of the member CSPlayerItem::m_ItemInfo
*
* @param entity Entity index
* @param type   Item info type. See ItemInfo constants.
*
*/
native rg_get_iteminfo(const ent, ItemInfo:type, any:...);

/*
* Adds hint message to the queue.
*
* @param index                 Client index
* @param message               The message hint
* @param duration              The time duration in seconds stays on screen
* @param bDisplayIfPlayerDead  Whether to print hint for dead players?
* @param bOverride             Whether to override previous messages?
*
* @return                      true if prints, false otherwise
*/
native bool:rg_hint_message(const index, const message[], Float:duration = 6.0, bool:bDisplayIfPlayerDead = false, bool:bOverride = false);

/*
* Instantly restart round.
*
* @noreturn
*/
native rg_restart_round();

/*
* Instantly check win conditions.
*
* @noreturn
*/
native rg_check_win_conditions();

/*
* Instantly initialize player counts.
*
* @param num_alive_terrorist   Count alive terrorists
* @param num_alive_ct          Count alive counter-terrorists
* @param num_dead_terrorist    Count dead terrorists
* @param num_dead_ct           Count dead counter-terrorists
*
* @noreturn
*/
native rg_initialize_player_counts(&num_alive_terrorist = 0, &num_alive_ct = 0, &num_dead_terrorist = 0, &num_dead_ct = 0);

/*
* Reset if player can hear another player.
*
* @param index                 Player id
* @noreturn
*/
native rg_reset_can_hear_player(const index);

/*
* Set if player can hear another player
*
* @param listener              Listener player id
* @param sender                Sender player id
* @param can_hear              Can listener hear sender
*
* @noreturn
*/
native rg_set_can_hear_player(const listener, const sender, const bool:can_hear);

/*
* Get if player can hear another player
*
* @param listener              Listener player id
* @param sender                Sender player id
*
* @return boolean
*/
native bool:rg_get_can_hear_player(const listener, const sender);

/*
* Spawn a head gib
*
* @param index                 Entity id
*
* @return                      Index of head gib entity or AMX_NULLENT (-1) otherwise
*/
native rg_spawn_head_gib(const index);

/*
* Spawn random gibs
*
* @param index                 Entity id
* @param cGibs                 Count gibs
* @param bHuman                Set gibs of a human or alien
*
* @noreturn
*/
native rg_spawn_random_gibs(const index, const cGibs, const bool:bHuman = true);
