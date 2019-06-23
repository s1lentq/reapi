#include "precompiled.h"

CEntityCallback g_entCallback;

void CEntityCallback::PurgeCallbacks(CBaseEntity *pEntity, CallbackType_e type)
{
	auto it = m_callbacks.begin();
	while (it != m_callbacks.end())
	{
		eCallback_t *pUnique = (*it)->GetUnique();

		// this callback was already sets, need to unregister the current forward
		if (pUnique->m_callbackType == type && pUnique->m_entity == pEntity) {
			delete (*it);
			it = m_callbacks.erase(it);
		} else {
			it++;
		}
	}
}

void CEntityCallback::Clear(CBaseEntity *pEntity)
{
	if (pEntity)
	{
		auto it = m_callbacks.begin();
		while (it != m_callbacks.end())
		{
			eCallback_t *pUnique = (*it)->GetUnique();
			if (pUnique->m_entity == pEntity) {
				delete (*it);
				it = m_callbacks.erase(it);
			} else {
				it++;
			}
		}
	}
	else
	{
		for (auto h : m_callbacks) {
			delete h;
		}

		m_callbacks.clear();
	}
}

bool CEntityCallback::SetThink(AMX *amx, CBaseEntity *pEntity, const char *pszCallback, const cell *pParams, size_t iParamsLen)
{
	PurgeCallbacks(pEntity, CType_Think);

	int fwdid;
	if (iParamsLen > 0) {
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_ARRAY, FP_DONE);
	} else {
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_DONE);
	}

	if (fwdid == -1) {
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: failed to register forward.", __FUNCTION__);
		return false;
	}

	m_callbacks.push_back(new CAmxxHookUnique<eCallback_t>(amx, pszCallback, fwdid, new eCallback_t(pEntity, pParams, iParamsLen, CType_Think)));
	pEntity->SetThink(&CBaseEntity::SUB_Think);
	return true;
}

bool CEntityCallback::SetTouch(AMX *amx, CBaseEntity *pEntity, const char *pszCallback, const cell *pParams, size_t iParamsLen)
{
	PurgeCallbacks(pEntity, CType_Touch);

	int fwdid;
	if (iParamsLen > 0) {
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_CELL, FP_ARRAY, FP_DONE);
	} else {
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_CELL, FP_DONE);
	}

	if (fwdid == -1) {
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: failed to register forward.", __FUNCTION__);
		return false;
	}

	m_callbacks.push_back(new CAmxxHookUnique<eCallback_t>(amx, pszCallback, fwdid, new eCallback_t(pEntity, pParams, iParamsLen, CType_Touch)));
	pEntity->SetTouch(&CBaseEntity::SUB_Touch);
	return true;
}

bool CEntityCallback::SetUse(AMX *amx, CBaseEntity *pEntity, const char *pszCallback, const cell *pParams, size_t iParamsLen)
{
	PurgeCallbacks(pEntity, CType_Use);

	int fwdid;
	if (iParamsLen > 0) {
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_CELL, FP_CELL, FP_CELL, FP_FLOAT, FP_ARRAY, FP_DONE);
	} else {
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_CELL, FP_CELL, FP_CELL, FP_FLOAT, FP_DONE);
	}

	if (fwdid == -1) {
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: failed to register forward.", __FUNCTION__);
		return false;
	}

	m_callbacks.push_back(new CAmxxHookUnique<eCallback_t>(amx, pszCallback, fwdid, new eCallback_t(pEntity, pParams, iParamsLen, CType_Use)));
	pEntity->SetUse(&CBaseEntity::SUB_Use);
	return true;
}

bool CEntityCallback::SetBlocked(AMX *amx, CBaseEntity *pEntity, const char *pszCallback, const cell *pParams, size_t iParamsLen)
{
	PurgeCallbacks(pEntity, CType_Blocked);

	int fwdid;
	if (iParamsLen > 0) {
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_CELL, FP_ARRAY, FP_DONE);
	} else {
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_CELL, FP_DONE);
	}

	if (fwdid == -1) {
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: failed to register forward.", __FUNCTION__);
		return false;
	}

	m_callbacks.push_back(new CAmxxHookUnique<eCallback_t>(amx, pszCallback, fwdid, new eCallback_t(pEntity, pParams, iParamsLen, CType_Blocked)));
	pEntity->SetBlocked(&CBaseEntity::SUB_Blocked);
	return true;
}

bool CEntityCallback::SetMoveDone(AMX *amx, CBaseEntity *pEntity, const char *pszCallback, const cell *pParams, size_t iParamsLen)
{
	PurgeCallbacks(pEntity, CType_MoveDone);

	int fwdid;
	if (iParamsLen > 0) {
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_ARRAY, FP_DONE);
	} else {
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_DONE);
	}

	if (fwdid == -1) {
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: failed to register forward.", __FUNCTION__);
		return false;
	}

	m_callbacks.push_back(new CAmxxHookUnique<eCallback_t>(amx, pszCallback, fwdid, new eCallback_t(pEntity, pParams, iParamsLen, CType_MoveDone)));

	// TODO: Make sure that the entity actually inherited from CBaseToggle
	((CBaseToggle *)pEntity)->SetMoveDone(&CBaseToggle::SUB_MoveDone);
	return true;
}

// Fundamental callbacks
void CBaseEntity::SUB_Think()
{
	g_entCallback.FireCallbacks(this, CEntityCallback::CType_Think, indexOfEdict(pev));
}

void CBaseEntity::SUB_Touch(CBaseEntity *pOther)
{
	g_entCallback.FireCallbacks(this, CEntityCallback::CType_Touch, indexOfEdict(pev), indexOfEdict(pOther->pev));
}

void CBaseEntity::SUB_Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	g_entCallback.FireCallbacks(this, CEntityCallback::CType_Use, indexOfEdict(pev), indexOfEdict(pActivator->pev), indexOfEdict(pCaller->pev), useType, value);
}

void CBaseEntity::SUB_Blocked(CBaseEntity *pOther)
{
	g_entCallback.FireCallbacks(this, CEntityCallback::CType_Blocked, indexOfEdict(pev), indexOfEdict(pOther->pev));
}

void CBaseToggle::SUB_MoveDone()
{
	g_entCallback.FireCallbacks(this, CEntityCallback::CType_MoveDone, indexOfEdict(pev));
}
