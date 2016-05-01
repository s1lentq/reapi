#if defined _reapi_misc_included
	#endinput
#endif
#define _reapi_misc_included

enum client_auth
{
	/**
	 * Description:		-
	 * Return type:		int
	 * Params:		get_client_data(const index, CA_PROTOCOL)
	 */
	CA_PROTOCOL,

	/**
	 * Description:		-
	 * Return type:		client_auth_type
	 * Params:		get_client_data(const index, CA_TYPE)
	 */
	CA_TYPE,

	/**
	 * Description:		-
	 * Return type:		-
	 * Params:		get_client_data(const index, CA_STRING, output[], maxlength)
	 */
	CA_STRING,
};

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

/*
* Checks whether the player is talking at this moment
*
* @param index		Client index
* @return		1 if client is speaking, 0 otherwise
*
*/
native VTC_IsClientSpeaking(index);

/*
* Mutes this player
*
* @param index		Client index
* @noreturn
*/
native VTC_MuteClient(index);

/*
* Unmutes this player
*
* @param index		Client index
* @noreturn
*/
native VTC_UnmuteClient(index);

/*
* Called when player started talking
*
* @param index		Client index
* @noreturn
*/
forward VTC_OnClientStartSpeak(index);

/*
* Called when player stopped talking
*
* @param index		Client index
* @noreturn
*/
forward VTC_OnClientStopSpeak(index);

/*
* Get out information of the client
*
* @param index		Client index
* @type			to look enum client_auth
*/
native get_client_data(const index, client_auth:type, any:...);
