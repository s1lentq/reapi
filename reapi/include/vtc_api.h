#pragma once

#define VOICETRANSCODER_API_VERSION_MAJOR 1
#define VOICETRANSCODER_API_VERSION_MINOR 0

template <typename ...t_args>
class IVoidCallbackRegistry {
public:
	virtual ~IVoidCallbackRegistry() {}

	typedef void (*callback_t)(t_args...);

	virtual void registerCallback(callback_t func) = 0;
	virtual void unregisterCallback(callback_t func) = 0;
};

typedef IVoidCallbackRegistry<size_t> ICallbackRegistry_ClientStartSpeak;
typedef IVoidCallbackRegistry<size_t> ICallbackRegistry_ClientStopSpeak;

class IVoiceTranscoderAPI {
public:
	virtual ~IVoiceTranscoderAPI() {}

	virtual size_t GetMajorVersion() = 0;
	virtual size_t GetMinorVersion() = 0;

	virtual bool IsClientSpeaking(size_t clientIndex) = 0;

	virtual ICallbackRegistry_ClientStartSpeak *ClientStartSpeak() = 0;
	virtual ICallbackRegistry_ClientStopSpeak *ClientStopSpeak() = 0;

	virtual void MuteClient(size_t clientIndex) = 0;
	virtual void UnmuteClient(size_t clientIndex) = 0;
};
