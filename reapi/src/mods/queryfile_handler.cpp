#include "precompiled.h"

CQueryFileManager g_queryFileManager;

void CQueryFileManager::Clear()
{
	for (auto query : m_hooklist) {
		delete query;
	}

	m_hooklist.clear();
}

int CQueryFileManager::Add(AMX *amx, const char *filename, const char *funcname, ResourceType_e flag, uint32 hash)
{
	auto handler = new CQueryFileHandler(amx, funcname);
	m_hooklist.push_back(handler);
	g_RecheckerFuncs->AddQueryFile(filename, flag, hash, &QueryFileHandler_Callback, handler->GetUniqueID());
	return handler->GetAmxxID();
}

bool CQueryFileManager::Remove(int index)
{
	auto iter = m_hooklist.begin();
	while (iter != m_hooklist.end())
	{
		if ((*iter)->GetAmxxID() == index) {
			delete (*iter);
			iter = m_hooklist.erase(iter);
			return true;
		}
		else
			iter++;
	}

	return false;
}

void CQueryFileManager::FireCallback(IGameClient *pClient, uint32 hash, int uniqueId)
{
	for (auto query : m_hooklist)
	{
		if (query->GetUniqueID() != uniqueId) {
			continue;
		}

		if (g_RecheckerFuncs->GetResource()->GetPrevHash() == hash) {
			hash = 0;
		}

		g_amxxapi.ExecuteForward(query->GetAmxxID(), pClient->GetId() + 1, hash);
	}
}

CQueryFileManager::CQueryFileHandler::CQueryFileHandler(AMX *amx, const char *funcname)
{
	m_amxId = g_amxxapi.RegisterSPForwardByName(amx, funcname, FP_CELL, FP_CELL, FP_DONE);
	m_uniqueId = MAKE_REQUESTID(PLID);
}

CQueryFileManager::CQueryFileHandler::~CQueryFileHandler()
{
	if (m_amxId != -1) {
		g_amxxapi.UnregisterSPForward(m_amxId);
	}

	g_RecheckerFuncs->RemoveQueryFile(m_uniqueId);
}

void QueryFileHandler_Callback(IGameClient *pClient, uint32 hash, int uniqueId)
{
	g_queryFileManager.FireCallback(pClient, hash, uniqueId);
}
