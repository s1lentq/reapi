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
native set_member(index, any:member, any:...);

/*
* Returns a value from an entity's member
*
* @param index		Entity index
* @param member		The specified member, look at the enum's with name *_Members
*
* @return		If an integer or boolean or one byte, array or everything else is passed via 3rd argument and more, look at argument list for specified member
*
* An integer:		new iTeam = get_member(id, m_iTeam);
*
* String array:		new szName[32];
*			get_member(id, m_szNewName, charsmax(m_szNewName));
*
* An int array:		new iAmmoIndex = get_member(id, m_rgAmmo, 5); // number of the element
*
*/
native any:get_member(index, any:member, any:...);

native rg_set_animation(index, PLAYER_ANIM:playerAnim);
native rg_add_account(index, amount, bool:bTrackChange = true);
native rg_give_item(index, const pszName[]);
native rg_give_default_items(index);
native rg_give_shield(index, bool:bDeploy = true);
native rg_dmg_radius(Float:vecSrc[3], inflictor, attacker, Float:flDamage, Float:flRadius, iClassIgnore, bitsDamageType);
native rg_multidmg_clear();
native rg_multidmg_apply(inflictor, attacker);
native rg_multidmg_add(inflictor, victim, Float:flDamage, bitsDamageType);

native rg_fire_bullets(inflictor, attacker, shots, Float:vecSrc[3], Float:vecDirShooting[3], Float:vecSpread[3], Float:flDistance, iBulletType, iTracerFreq, iDamage);
native Float:[3] rg_fire_bullets3(inflictor, attacker, Float:vecSrc[3], Float:vecDirShooting[3], Float:vecSpread, Float:flDistance, iPenetration, iBulletType, iDamage, Float:flRangeModifier, bool:bPistol, shared_rand);

native rg_round_end(Float:tmDelay, WinStatus:st, ScenarionEventEndRound:event = ROUND_NONE, const message[] = "default", const sentence[] = "default");
native rg_update_teamscores(iCtsWins = 0, iTsWins = 0, bool:bAdd = true);
