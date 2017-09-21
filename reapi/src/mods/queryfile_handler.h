#pragma once

class CQueryFileManager
{
public:
	int Add(AMX *amx, const char *filename, const char *funcname, ResourceType_e flag, uint32 hash);
	void Clear();
	bool Remove(int index);
	void FireCallback(IGameClient *pClient, uint32 hash, int uniqueId);

private:
	class CQueryFileHandler
	{
	public:
		CQueryFileHandler(AMX *amx, const char *funcname);
		~CQueryFileHandler();

		const int GetAmxxID()   const { return m_amxId;    };
		const int GetUniqueID() const { return m_uniqueId; };

	private:
		int m_amxId;
		int m_uniqueId;
	};

	std::vector<CQueryFileHandler *> m_hooklist;
};

extern CQueryFileManager g_queryFileManager;

void QueryFileHandler_Callback(IGameClient *pClient, uint32 hash, int uniqueId);
