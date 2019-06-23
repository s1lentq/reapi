#pragma once

#include "amx_hook.h"

class CEntityCallback
{
public:
	void Clear(CBaseEntity *pEntity = nullptr);

	bool SetThink   (AMX *amx, CBaseEntity *pEntity, const char *pszCallback, const cell *pParams, size_t iParamsLen);
	bool SetTouch   (AMX *amx, CBaseEntity *pEntity, const char *pszCallback, const cell *pParams, size_t iParamsLen);
	bool SetUse     (AMX *amx, CBaseEntity *pEntity, const char *pszCallback, const cell *pParams, size_t iParamsLen);
	bool SetBlocked (AMX *amx, CBaseEntity *pEntity, const char *pszCallback, const cell *pParams, size_t iParamsLen);
	bool SetMoveDone(AMX *amx, CBaseEntity *pEntity, const char *pszCallback, const cell *pParams, size_t iParamsLen);

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
			auto data = fwd->GetUnique();
			if (data->m_entity == pEntity && data->m_callbackType == type)
			{
				if (data->m_iParamLen > 0) {
					g_amxxapi.ExecuteForward(fwd->GetIndex(), args..., g_amxxapi.PrepareCellArrayA(data->m_pParams, data->m_iParamLen, true));
				} else {
					g_amxxapi.ExecuteForward(fwd->GetIndex(), args...);
				}
			}
		}
	}

private:
	void PurgeCallbacks(CBaseEntity *pEntity, CallbackType_e type);
	struct eCallback_t
	{
		eCallback_t(CBaseEntity *pEntity, const cell *pParams, size_t iParamsLen, CallbackType_e type) :
			m_entity(pEntity), m_callbackType(type)
		{
			if (iParamsLen > 0) {
				m_iParamLen = iParamsLen + 1;
				m_pParams = new cell[m_iParamLen];
				Q_memcpy(m_pParams, pParams, sizeof(cell) * iParamsLen);
				m_pParams[iParamsLen] = 0;
			} else {
				m_iParamLen = 0;
				m_pParams = nullptr;
			}
		};

		~eCallback_t()
		{
			if (m_pParams) {
				delete[] m_pParams;
				m_pParams = nullptr;
			}

			m_iParamLen = 0;
		}

		CBaseEntity *m_entity;
		CallbackType_e m_callbackType;
		cell *m_pParams;
		size_t m_iParamLen;
	};

	std::vector<CAmxxHookUnique<eCallback_t> *> m_callbacks;
};

extern CEntityCallback g_entCallback;
