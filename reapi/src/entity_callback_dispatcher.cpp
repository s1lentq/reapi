#include "precompiled.h"

// Deletes all registered callbacks for the specified entity, or all entities if pEntity is nullptr
void CEntityCallbackDispatcher::DeleteExistingCallbacks(CBaseEntity *pEntity, CallbackType type)
{
	for (std::list<EntityCallback *>::const_iterator it = m_callbacks.begin();
		it != m_callbacks.end(); )
	{
		EntityCallback *callback = (*it);

		// This callback was already sets, need to unregister the current forward
		if (!pEntity || (callback->m_pEntity == pEntity && (callback->m_callbackType == type || None == type)))
		{
			// Are we in the middle of processing callbacks?
			if (IsProcessingCallbacks())
			{
				// Sets the mark for the object to be deleted later
				const std::list<EntityCallback *>::const_iterator callbackIt =
					std::find(m_callbacksMarkForDeletion.begin(), m_callbacksMarkForDeletion.end(), callback);

				if (callbackIt == m_callbacksMarkForDeletion.end())
					m_callbacksMarkForDeletion.push_back(callback);

				it++;
			}
			else
			{
				it = m_callbacks.erase(it);
				delete callback;
			}
		}
		else
		{
			it++;
		}
	}

	if (!pEntity && !IsProcessingCallbacks())
		m_callbacks.clear();
}

// Deletes all registered callbacks
void CEntityCallbackDispatcher::DeleteAllCallbacks()
{
	DeleteExistingCallbacks(nullptr);
}

bool CEntityCallbackDispatcher::SetThink(AMX *amx, CBaseEntity *pEntity, const char *pszCallback, const cell *pParams, size_t iParamsLen)
{
	DeleteExistingCallbacks(pEntity, Think);

	int fwdid;
	if (iParamsLen > 0)
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_ARRAY, FP_DONE);
	else
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_DONE);

	if (fwdid == -1)
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: failed to register forward.", __FUNCTION__);
		return false;
	}

	m_callbacks.push_back(new EntityCallback(amx, pszCallback, fwdid, pEntity, pParams, iParamsLen, Think));
	pEntity->SetThink(&CBaseEntity::SUB_Think);
	return true;
}

bool CEntityCallbackDispatcher::SetTouch(AMX *amx, CBaseEntity *pEntity, const char *pszCallback, const cell *pParams, size_t iParamsLen)
{
	DeleteExistingCallbacks(pEntity, Touch);

	int fwdid;
	if (iParamsLen > 0)
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_CELL, FP_ARRAY, FP_DONE);
	else
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_CELL, FP_DONE);

	if (fwdid == -1)
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: failed to register forward.", __FUNCTION__);
		return false;
	}

	m_callbacks.push_back(new EntityCallback(amx, pszCallback, fwdid, pEntity, pParams, iParamsLen, Touch));
	pEntity->SetTouch(&CBaseEntity::SUB_Touch);
	return true;
}

bool CEntityCallbackDispatcher::SetUse(AMX *amx, CBaseEntity *pEntity, const char *pszCallback, const cell *pParams, size_t iParamsLen)
{
	DeleteExistingCallbacks(pEntity, Use);

	int fwdid;
	if (iParamsLen > 0)
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_CELL, FP_CELL, FP_CELL, FP_FLOAT, FP_ARRAY, FP_DONE);
	else
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_CELL, FP_CELL, FP_CELL, FP_FLOAT, FP_DONE);

	if (fwdid == -1)
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: failed to register forward.", __FUNCTION__);
		return false;
	}

	m_callbacks.push_back(new EntityCallback(amx, pszCallback, fwdid, pEntity, pParams, iParamsLen, Use));
	pEntity->SetUse(&CBaseEntity::SUB_Use);
	return true;
}

bool CEntityCallbackDispatcher::SetBlocked(AMX *amx, CBaseEntity *pEntity, const char *pszCallback, const cell *pParams, size_t iParamsLen)
{
	DeleteExistingCallbacks(pEntity, Blocked);

	int fwdid;
	if (iParamsLen > 0)
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_CELL, FP_ARRAY, FP_DONE);
	else
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_CELL, FP_DONE);

	if (fwdid == -1)
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: failed to register forward.", __FUNCTION__);
		return false;
	}

	m_callbacks.push_back(new EntityCallback(amx, pszCallback, fwdid, pEntity, pParams, iParamsLen, Blocked));
	pEntity->SetBlocked(&CBaseEntity::SUB_Blocked);
	return true;
}

bool CEntityCallbackDispatcher::SetMoveDone(AMX *amx, CBaseEntity *pEntity, const char *pszCallback, const cell *pParams, size_t iParamsLen)
{
	DeleteExistingCallbacks(pEntity, MoveDone);

	int fwdid;
	if (iParamsLen > 0)
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_ARRAY, FP_DONE);
	else
		fwdid = g_amxxapi.RegisterSPForwardByName(amx, pszCallback, FP_CELL, FP_DONE);

	if (fwdid == -1)
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: failed to register forward.", __FUNCTION__);
		return false;
	}

	// Make sure that the entity actually inherited from CBaseToggle
	CBaseToggle *pEntityToggle = dynamic_cast<CBaseToggle *>(pEntity);
	if (!pEntityToggle)
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: '%s' has no refs to the base class of an entity 'CBaseToggle'", __FUNCTION__, STRING(pEntity->pev->classname));
		return false;
	}

	m_callbacks.push_back(new EntityCallback(amx, pszCallback, fwdid, pEntity, pParams, iParamsLen, MoveDone));
	pEntityToggle->SetMoveDone(&CBaseToggle::SUB_MoveDone);
	return true;
}

void CEntityCallbackDispatcher::UnsetThink(AMX *amx, CBaseEntity *pEntity)
{
	pEntity->SetThink(nullptr);
	DeleteExistingCallbacks(pEntity, Think);
}

void CEntityCallbackDispatcher::UnsetTouch(AMX *amx, CBaseEntity *pEntity)
{
	pEntity->SetTouch(nullptr);
	DeleteExistingCallbacks(pEntity, Touch);
}

void CEntityCallbackDispatcher::UnsetUse(AMX *amx, CBaseEntity *pEntity)
{
	pEntity->SetUse(nullptr);
	DeleteExistingCallbacks(pEntity, Use);
}

void CEntityCallbackDispatcher::UnsetBlocked(AMX *amx, CBaseEntity *pEntity)
{
	pEntity->SetBlocked(nullptr);
	DeleteExistingCallbacks(pEntity, Blocked);
}

void CEntityCallbackDispatcher::UnsetMoveDone(AMX *amx, CBaseEntity *pEntity)
{
	// Make sure that the entity actually inherited from CBaseToggle
	CBaseToggle *pEntityToggle = dynamic_cast<CBaseToggle *>(pEntity);
	if (!pEntityToggle)
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: '%s' has no refs to the base class of an entity 'CBaseToggle'", __FUNCTION__, STRING(pEntity->pev->classname));
		return;
	}

	pEntityToggle->SetMoveDone(nullptr);
	DeleteExistingCallbacks(pEntity, MoveDone);
}

// Fundamental callbacks
void CBaseEntity::SUB_Think()
{
	EntityCallbackDispatcher().DispatchCallbacks(this, CEntityCallbackDispatcher::Think, indexOfEdict(pev));
}

void CBaseEntity::SUB_Touch(CBaseEntity *pOther)
{
	EntityCallbackDispatcher().DispatchCallbacks(this, CEntityCallbackDispatcher::Touch, indexOfEdict(pev), indexOfEdict(pOther->pev));
}

void CBaseEntity::SUB_Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	EntityCallbackDispatcher().DispatchCallbacks(this, CEntityCallbackDispatcher::Use, indexOfEdict(pev), indexOfEdict(pActivator->pev), indexOfEdict(pCaller->pev), useType, value);
}

void CBaseEntity::SUB_Blocked(CBaseEntity *pOther)
{
	EntityCallbackDispatcher().DispatchCallbacks(this, CEntityCallbackDispatcher::Blocked, indexOfEdict(pev), indexOfEdict(pOther->pev));
}

void CBaseToggle::SUB_MoveDone()
{
	EntityCallbackDispatcher().DispatchCallbacks(this, CEntityCallbackDispatcher::MoveDone, indexOfEdict(pev));
}

// Instance of the callback dispatcher
static CEntityCallbackDispatcher s_EntityCallbackDispatcher = {};

// Returns the instance of the callback dispatcher
CEntityCallbackDispatcher &EntityCallbackDispatcher()
{
	return s_EntityCallbackDispatcher;
}
