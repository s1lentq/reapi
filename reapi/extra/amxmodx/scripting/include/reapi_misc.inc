#if defined _reapi_misc_included
	#endinput
#endif
#define _reapi_misc_included

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
