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
