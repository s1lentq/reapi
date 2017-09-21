#include "precompiled.h"

/*
* Checks whether the player is talking at this moment
*
* @param index		Client index
* @return		true if client is speaking, false otherwise
*
* native bool:VTC_IsClientSpeaking(const index);
*/
cell AMX_NATIVE_CALL VTC_IsClientSpeaking(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };

	CHECK_ISPLAYER(arg_index);

	return (cell)g_pVoiceTranscoderApi->IsClientSpeaking((size_t)params[arg_index]);
}

/*
* Mutes this player
*
* @param index		Client index
* @noreturn
*
* native VTC_MuteClient(const index);
*/
cell AMX_NATIVE_CALL VTC_MuteClient(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };

	CHECK_ISPLAYER(arg_index);

	g_pVoiceTranscoderApi->MuteClient((size_t)params[arg_index]);
	return TRUE;
}

/*
* Unmutes this player
*
* @param index		Client index
* @noreturn
*
* native VTC_UnmuteClient(const index);
*/
cell AMX_NATIVE_CALL VTC_UnmuteClient(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };

	CHECK_ISPLAYER(arg_index);

	g_pVoiceTranscoderApi->UnmuteClient((size_t)params[arg_index]);
	return TRUE;
}

/*
* Checks whether the player is muted at this moment
*
* @param index          Client index
* @return               true if client is muted, false otherwise
*
* native bool:VTC_IsClientMuted(const index);
*/
cell AMX_NATIVE_CALL VTC_IsClientMuted(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };

	CHECK_ISPLAYER(arg_index);

	return (cell)g_pVoiceTranscoderApi->IsClientMuted((size_t)params[arg_index]);
}

/*
* To play the audio file via the voice stream.
*
* @param receiver       Receiver index
* @param soundFilePath  The path to the sound file.
*
* @note Usage example:
*       VTC_PlaySound(id, "sound/ambience/Opera.wav");
*
* @noreturn
*
* native VTC_PlaySound(const receiver, const soundFilePath[]);
*/
cell AMX_NATIVE_CALL VTC_PlaySound(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_audio_pathfile };

	CHECK_ISPLAYER(arg_index);

	g_pVoiceTranscoderApi->PlaySound((size_t)params[arg_index], getAmxString(amx, params[arg_audio_pathfile]));
	return TRUE;
}

AMX_NATIVE_INFO VTC_Natives[] =
{
	{ "VTC_IsClientSpeaking", VTC_IsClientSpeaking },
	{ "VTC_MuteClient",       VTC_MuteClient       },
	{ "VTC_UnmuteClient",     VTC_UnmuteClient     },
	{ "VTC_IsClientMuted",    VTC_IsClientMuted    },
	{ "VTC_PlaySound",        VTC_PlaySound        },

	{ nullptr, nullptr }
};

void RegisterNatives_VTC()
{
	if (!api_cfg.hasVTC())
		fillNatives(VTC_Natives, [](AMX *amx, cell *params) -> cell { MF_LogError(amx, AMX_ERR_NATIVE, "%s: isn't available", "VTC"); return FALSE; });

	g_amxxapi.AddNatives(VTC_Natives);
}
