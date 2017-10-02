#pragma once

#include "amx_hook.h"

class CEntityCallback
{
public:
	void Clear(CBaseEntity *pEntity = nullptr);

	bool SetThink   (AMX *amx, CBaseEntity *pEntity, const char *pszCallback);
	bool SetTouch   (AMX *amx, CBaseEntity *pEntity, const char *pszCallback);
	bool SetUse     (AMX *amx, CBaseEntity *pEntity, const char *pszCallback);
	bool SetBlocked (AMX *amx, CBaseEntity *pEntity, const char *pszCallback);
	bool SetMoveDone(AMX *amx, CBaseEntity *pEntity, const char *pszCallback);

	enum CallbackType_e
	{
		CType_Think,
		CType_Touch,
		CType_Use,
		CType_Blocked,
		CType_MoveDone,
	};

	template <typename ...f_args>
	void FireCallbacks(CBaseEntity *pEntity, CallbackType_e type, volatile f_args... args)
	{
		for (auto fwd : m_callbacks) {
			if (fwd->GetUnique().m_entity == pEntity && fwd->GetUnique().m_callbackType == type) {
				g_amxxapi.ExecuteForward(fwd->GetIndex(), args...);
			}
		}
	}

private:
	void PurgeCallbacks(CBaseEntity *pEntity, CallbackType_e type);
	struct EntityCallback_t
	{
		EntityCallback_t(CBaseEntity *pEntity, CallbackType_e type) :
			m_entity(pEntity), m_callbackType(type) {};

		CBaseEntity *m_entity;
		CallbackType_e m_callbackType;
	};

	std::vector<CAmxxHook<EntityCallback_t> *> m_callbacks;
};

extern CEntityCallback g_entCallback;
