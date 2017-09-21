#pragma once
#include "hook_list.h"

enum fwdstate
{
	FSTATE_INVALID = 0,
	FSTATE_ENABLED,
	FSTATE_PAUSED,
	FSTATE_STOPPED
};

class CAmxxHook
{
public:
	CAmxxHook(AMX* amx, const char *funcname, int index) : m_index(index), m_state(FSTATE_ENABLED), m_amx(amx)
	{
		strncpy(m_CallbackName, funcname, sizeof(m_CallbackName) - 1);
		m_CallbackName[sizeof(m_CallbackName) - 1] = '\0';
	};

	int GetIndex() const;
	fwdstate GetState() const;
	AMX* GetAmx() const;
	const char *GetCallbackName() const;

	void SetState(fwdstate st);

private:
	int m_index;
	char m_CallbackName[64];
	fwdstate m_state;
	AMX* m_amx;
};

class CHookManager
{
public:
	void Clear() const;
	cell addHandler(AMX* amx, int func, const char *funcname, int forward, bool post) const;
	hook_t* getHook(size_t func) const;
	CAmxxHook* getAmxxHook(cell hook) const;

	hook_t* getHookFast(size_t func) const {
		return m_hooklist[func];
	}

private:
	hooklist_t m_hooklist;
};

extern CHookManager g_hookManager;
