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
	~CAmxxHookBase();
	CAmxxHookBase(AMX *amx, const char *funcname, int forwardIndex, int index);

	int GetFwdIndex()             const { return m_fwdindex; }
	int GetIndex()                const { return m_index; }
	fwdstate GetState()           const { return m_state; }
	AMX *GetAmx()                 const { return m_amx; }
	const char *GetCallbackName() const { return m_CallbackName; }

	void SetState(fwdstate st) { m_state = st; }
	void Error(int error, const char *fmt, ...);

private:
	int m_fwdindex, m_index;
	char m_CallbackName[64];
	fwdstate m_state;
	AMX *m_amx;
};
