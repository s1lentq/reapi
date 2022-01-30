#if defined _reapi_reunion_included
	#endinput
#endif
#define _reapi_reunion_included

enum client_auth_type
{
	CA_TYPE_NONE = 0,
	CA_TYPE_DPROTO,
	CA_TYPE_STEAM,
	CA_TYPE_STEAMEMU,
	CA_TYPE_REVEMU,
	CA_TYPE_OLDREVEMU,
	CA_TYPE_HLTV,
	CA_TYPE_SC2009,
	CA_TYPE_AVSMP,
	CA_TYPE_SXEI,
	CA_TYPE_REVEMU2013,
	CA_TYPE_SSE3,
};

#define is_user_steam(%0) (REU_GetAuthtype(%0) == CA_TYPE_STEAM)

/*
* Gets client protocol.
*
* @param index  Client index
*
* @return       Client protocol
*/
native REU_GetProtocol(const index);

/*
* Gets client auth type.
*
* @param index  Client index
*
* @return       Client auth type
*/
native client_auth_type:REU_GetAuthtype(const index);

/*
* Get client authkey
*
* @param index  Client index
* @param index  Buffer to copy the authkey
* @param index  Maximum buffer size
*
* @return       Number of cells copied to buffer
*
*/
native REU_GetAuthKey(const index, dest[], maxlen);

/*
* Check if the client is running RevEmu with limited user rights.
*
* @param index  Client index
*
* @return       1/0
*/
native bool:REU_IsRevemuWithoutAdminRights(const index);
