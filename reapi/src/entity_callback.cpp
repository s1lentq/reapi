#include "precompiled.h"

CEntityCallback g_entCallback;

void CEntityCallback::PurgeCallbacks(CBaseEntity *pEntity, CallbackType_e type)
{
	auto it = m_callbacks.begin();
	while (it != m_callbacks.end())
	{
		EntityCallback_t data = (*it)->GetUnique();

		// this callback was already sets, need to unregister the current forward
		if (data.m_callbackType == type && data.m_entity == pEntity) {
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
			EntityCallback_t data = (*it)->GetUnique();
			if (data.m_entity == pEntity) {
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

bool CEntityCallback::SetThink(AMX *amx, CBaseEntity *pEntity, const char *pszCallback)
{
	PurgeCallbacks(pEntity, CType_Think);

	int fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_DONE);
	if (fwdid == -1) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: failed to register forward.", __FUNCTION__);
		return false;
	}

	EntityCallback_t entry(pEntity, CType_Think);
	m_callbacks.push_back(new CAmxxHook<EntityCallback_t>(amx, pszCallback, fwdid, entry));
	pEntity->SetThink(&CBaseEntity::SUB_Think);
	return true;
}

bool CEntityCallback::SetTouch(AMX *amx, CBaseEntity *pEntity, const char *pszCallback)
{
	PurgeCallbacks(pEntity, CType_Touch);

	int fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_CELL, FP_DONE);
	if (fwdid == -1) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: failed to register forward.", __FUNCTION__);
		return false;
	}

	EntityCallback_t entry(pEntity, CType_Touch);
	m_callbacks.push_back(new CAmxxHook<EntityCallback_t>(amx, pszCallback, fwdid, entry));
	pEntity->SetTouch(&CBaseEntity::SUB_Touch);
	return true;
}

bool CEntityCallback::SetUse(AMX *amx, CBaseEntity *pEntity, const char *pszCallback)
{
	PurgeCallbacks(pEntity, CType_Use);

	int fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_CELL, FP_CELL, FP_CELL, FP_FLOAT, FP_DONE);
	if (fwdid == -1) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: failed to register forward.", __FUNCTION__);
		return false;
	}

	EntityCallback_t entry(pEntity, CType_Use);
	m_callbacks.push_back(new CAmxxHook<EntityCallback_t>(amx, pszCallback, fwdid, entry));
	pEntity->SetUse(&CBaseEntity::SUB_Use);
	return true;
}

bool CEntityCallback::SetBlocked(AMX *amx, CBaseEntity *pEntity, const char *pszCallback)
{
	PurgeCallbacks(pEntity, CType_Blocked);

	int fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_CELL, FP_DONE);
	if (fwdid == -1) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: failed to register forward.", __FUNCTION__);
		return false;
	}

	EntityCallback_t entry(pEntity, CType_Blocked);
	m_callbacks.push_back(new CAmxxHook<EntityCallback_t>(amx, pszCallback, fwdid, entry));
	pEntity->SetTouch(&CBaseEntity::SUB_Blocked);
	return true;
}

bool CEntityCallback::SetMoveDone(AMX *amx, CBaseEntity *pEntity, const char *pszCallback)
{
	PurgeCallbacks(pEntity, CType_MoveDone);

	int fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_DONE);
	if (fwdid == -1) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: failed to register forward.", __FUNCTION__);
		return false;
	}

	EntityCallback_t entry(pEntity, CType_MoveDone);
	m_callbacks.push_back(new CAmxxHook<EntityCallback_t>(amx, pszCallback, fwdid, entry));

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
