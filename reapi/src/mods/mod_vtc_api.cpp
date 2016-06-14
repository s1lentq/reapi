#include "precompiled.h"

IVoiceTranscoderAPI *g_pVoiceTranscoderApi;

bool VTC_Api_Init()
{
	if (!g_RehldsApi)
		return false;

	g_pVoiceTranscoderApi = (IVoiceTranscoderAPI *)g_RehldsApi->GetFuncs()->GetPluginApi("VoiceTranscoder");

	if (!g_pVoiceTranscoderApi)
		return false;

	int majorVersion = g_pVoiceTranscoderApi->GetMajorVersion();
	int minorVersion = g_pVoiceTranscoderApi->GetMinorVersion();

	if (majorVersion != VOICETRANSCODER_API_VERSION_MAJOR) {
		UTIL_ServerPrint("[%s]: VTC Api major version mismatch; expected %d, real %d\n", Plugin_info.logtag, VOICETRANSCODER_API_VERSION_MAJOR, majorVersion);
		return false;
	}

	if (minorVersion < VOICETRANSCODER_API_VERSION_MINOR) {
		UTIL_ServerPrint("[%s]: VTC Api minor version mismatch; expected at least %d, real %d\n", Plugin_info.logtag, VOICETRANSCODER_API_VERSION_MINOR, minorVersion);
		return false;
	}

	g_pVoiceTranscoderApi->ClientStartSpeak()->registerCallback(&ClientStartSpeak);
	g_pVoiceTranscoderApi->ClientStopSpeak()->registerCallback(&ClientStopSpeak);

	return true;
}
