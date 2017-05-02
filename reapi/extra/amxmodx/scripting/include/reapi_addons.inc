#if defined _reapi_addons_included
	#endinput
#endif
#define _reapi_addons_included

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
* Checks whether the player is talking at the moment.
*
* @param index		Client index
* @return		true if client is speaking, false otherwise
*
*/
native bool:VTC_IsClientSpeaking(const index);

/*
* Mutes the player.
*
* @param index		Client index
* @noreturn
*/
native VTC_MuteClient(const index);

/*
* Unmutes the player.
*
* @param index		Client index
* @noreturn
*/
native VTC_UnmuteClient(const index);

/*
* Checks whether the player is muted at the moment.
*
* @param index          Client index
* @return               true if client is muted, false otherwise
*
*/
native bool:VTC_IsClientMuted(const index);

/*
* Play the audio file via the voice stream.
*
* @param receiver       Receiver index
* @param soundFilePath  The path to the sound file
*
* @note Usage example:
*       VTC_PlaySound(id, "sound/ambience/Opera.wav");
*
* @noreturn
*
*/
native VTC_PlaySound(const receiver, const soundFilePath[]);

/*
* Called when the player started talking.
*
* @param index		Client index
* @noreturn
*/
forward VTC_OnClientStartSpeak(const index);

/*
* Called when the player stopped talking.
*
* @param index		Client index
* @noreturn
*/
forward VTC_OnClientStopSpeak(const index);

/*
* Gets client protocol.
*
* @param index		Client index
* @return		Client protocol
*/
native REU_GetProtocol(const index);

/*
* Gets client auth type.
*
* @param index		Client index
* @return		Client auth type
*/
native client_auth_type:REU_GetAuthtype(const index);

/*
* Check if the client is running RevEmu with limited user rights.
*
* @param index		Client index
* @return		1/0
*
*/
native bool:REU_IsRevemuWithoutAdminRights(const index);
