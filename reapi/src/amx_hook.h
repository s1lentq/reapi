#pragma once

enum fwdstate
{
	FSTATE_INVALID = 0,
	FSTATE_ENABLED,
	FSTATE_PAUSED,
	FSTATE_STOPPED
};

template <typename T = void>
class CAmxxHook
{
public:
	~CAmxxHook()
	{
		if (m_index != -1) {
			g_amxxapi.UnregisterSPForward(m_index);
			m_index = -1;
		}

		delete m_uniqueData;
	}

	CAmxxHook(AMX *amx, const char *funcname, int index, T *data = nullptr) :
		m_index(index),
		m_state(FSTATE_ENABLED),
		m_amx(amx),
		m_uniqueData(data)
	{
		Q_strlcpy(m_CallbackName, funcname);
	};

	T *GetUnique()                 const;
	int GetIndex()                const;
	fwdstate GetState()           const;
	AMX *GetAmx()                 const;
	const char *GetCallbackName() const;

	void SetState(fwdstate st);

private:
	T *m_uniqueData;
	int m_index;
	char m_CallbackName[64];
	fwdstate m_state;
	AMX *m_amx;
};

// Inlines
template <typename T>
inline T *CAmxxHook<T>::GetUnique() const
{
	return m_uniqueData;
}

template <typename T>
inline AMX *CAmxxHook<T>::GetAmx() const
{
	return m_amx;
}

template <typename T>
inline const char *CAmxxHook<T>::GetCallbackName() const
{
	return m_CallbackName;
}

template <typename T>
inline int CAmxxHook<T>::GetIndex() const
{
	return m_index;
}

template <typename T>
inline fwdstate CAmxxHook<T>::GetState() const
{
	return m_state;
}

template <typename T>
inline void CAmxxHook<T>::SetState(fwdstate st)
{
	m_state = st;
}
