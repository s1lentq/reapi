#if defined _reapi_gamedll_included
	#endinput
#endif

#define _reapi_gamedll_included

#include <reapi_gamedll_const.inc>

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
native set_member(const index, any:member, any:...);

/*
* Returns a value from an entity's member
*
* @param index		Entity index
* @param member		The specified member, look at the enum's with name *_Members
*
* @return		If an integer or boolean or one byte, array or everything else is passed via 3rd argument and more, look at argument list for specified member
*/
native any:get_member(const index, any:member, any:...);

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
native rg_add_account(const index, amount, bool:bTrackChange = true);

/*
* Gives item to player
*
* @param index		Client index
* @param pszName	Classname item
*
* @noreturn
*/
native rg_give_item(index, const pszName[], GiveType:type = GT_APPEND);

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
native rg_give_shield(const index, bool:bDeploy = true);

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
* inflicts contents of global multi damage register on victim
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
* @param iBulletType		Bullet type
* @param iTracerFreq		Tracer frequancy
* @param iDamage		Damage amount
*
* @noreturn
*/
native rg_fire_bullets(const inflictor, const attacker, const shots, Float:vecSrc[3], Float:vecDirShooting[3], Float:vecSpread[3], const Float:flDistance, const iBulletType, const iTracerFreq, const iDamage);

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
*/
native Float:[3] rg_fire_bullets3(const inflictor, const attacker, Float:vecSrc[3], Float:vecDirShooting[3], const Float:vecSpread, const Float:flDistance, const iPenetration, const iBulletType, const iDamage, const Float:flRangeModifier, const bool:bPistol, const shared_rand);

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
* @param classname		Entity class name
*
* @return			Index of the created entity or 0 otherwise
*
*/
native rg_create_entity(const classname[]);

/*
* Finds an entity in the world using Counter-Strike's custom FindEntityByString wrapper.
*
* @param start_index		Entity index to start searching from. -1 to start from the first entity
* @param classname		Classname to search for
*
* @return			Entity index > 0 if found, 0 otherwise
*
*/
native rg_find_ent_by_class(start_index, const classname[]);

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
* Remove all the player's stuff
*
* @param index		Client index
*
* @noreturn
*
*/
native rg_remove_all_items(const index, bool:bRemoveSuit);

/*
* Remove specifed the player's item by class name
*
* @param index		Client index
* @param item_name	Class name item
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
native rg_give_defusekit(const index, bool:bDefusekit = true, Float:color[] = {0.0, 160.0, 0.0}, const icon[] = "defuser", bool:bFlash = false);

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
