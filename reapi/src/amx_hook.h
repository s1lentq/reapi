#pragma once

enum fwdstate
{
	FSTATE_INVALID = 0,
	FSTATE_ENABLED,
	FSTATE_PAUSED,
	FSTATE_STOPPED
};

class CAmxxHookBase
{
public:
	~CAmxxHookBase()
	{
		if (m_index != -1) {
			g_amxxapi.UnregisterSPForward(m_index);
			m_index = -1;
		}
	}

	CAmxxHookBase(AMX *amx, const char *funcname, int index) :
		m_index(index),
		m_state(FSTATE_ENABLED),
		m_amx(amx)
	{
		Q_strlcpy(m_CallbackName, funcname);
	}

	int GetIndex()                const { return m_index; }
	fwdstate GetState()           const { return m_state; }
	AMX *GetAmx()                 const { return m_amx; }
	const char *GetCallbackName() const { return m_CallbackName; }

	void SetState(fwdstate st) { m_state = st; }

private:
	int m_index;
	char m_CallbackName[64];
	fwdstate m_state;
	AMX *m_amx;
};

template <typename T>
class CAmxxHookUnique: public CAmxxHookBase
{
public:
	~CAmxxHookUnique()
	{
		if (m_uniqueData)
		{
			delete m_uniqueData;
			m_uniqueData = nullptr;
		}
	}

	CAmxxHookUnique(AMX *amx, const char *funcname, int index, T *data = nullptr) :
		CAmxxHookBase(amx, funcname, index),
		m_uniqueData(data)
	{

	}

	T *GetUnique() const { return m_uniqueData; }

private:
	T *m_uniqueData;
};
