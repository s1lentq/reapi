#include "precompiled.h"

/*
* Checks whether the player is talking at this moment
*
* @param index		Client index
* @return		1 if client is speaking, 0 otherwise
*
* native VTC_IsClientSpeaking(index);
*/
cell AMX_NATIVE_CALL VTC_IsClientSpeaking(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };
	return g_pVoiceTranscoderApi->IsClientSpeaking((size_t)params[arg_index]);
}

/*
* Mutes this player
*
* @param index		Client index
* @noreturn
*
* native VTC_MuteClient(index);
*/
cell AMX_NATIVE_CALL VTC_MuteClient(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };
	g_pVoiceTranscoderApi->MuteClient((size_t)params[arg_index]);

	return FALSE;
}

/*
* Unmutes this player
*
* @param index		Client index
* @noreturn
*
* native VTC_UnmuteClient(index);
*/
cell AMX_NATIVE_CALL VTC_UnmuteClient(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };
	g_pVoiceTranscoderApi->UnmuteClient((size_t)params[arg_index]);

	return FALSE;
}

AMX_NATIVE_INFO Vtc_Natives[] =
{
	{ "VTC_IsClientSpeaking", VTC_IsClientSpeaking },
	{ "VTC_MuteClient", VTC_MuteClient },
	{ "VTC_UnmuteClient", VTC_UnmuteClient },

	{ nullptr, nullptr }
};

/*
* Get client protocol
*
* @param index		Client index
*
* native REU_GetProtocol(const index);
*/
cell AMX_NATIVE_CALL REU_GetProtocol(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };

	CHECK_ISPLAYER(params[arg_index]);

	return g_ReunionApi->GetClientProtocol(params[arg_index] - 1);
}

/*
* Get client auth type
*
* @param index		Client index
*
* native REU_GetAuthtype(const index);
*/
cell AMX_NATIVE_CALL REU_GetAuthtype(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };

	CHECK_ISPLAYER(params[arg_index]);

	return g_ReunionApi->GetClientAuthtype(params[arg_index] - 1);
}

AMX_NATIVE_INFO Reunion_Natives[] =
{
	{ "REU_GetProtocol", REU_GetProtocol },
	{ "REU_GetAuthtype", REU_GetAuthtype },

	{ nullptr, nullptr }
};

void RegisterNatives_Addons()
{
	if (api_cfg.hasVTC())
		g_amxxapi.AddNatives(Vtc_Natives);
	if (api_cfg.hasReunion())
		g_amxxapi.AddNatives(Reunion_Natives);
}
