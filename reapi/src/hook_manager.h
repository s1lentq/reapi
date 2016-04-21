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
	CAmxxHook(AMX* amx, int index) : m_index(index), m_state(FSTATE_ENABLED), m_amx(amx) {};
	
	int GetIndex() const;
	fwdstate GetState() const;
	AMX* GetAmx() const;
	void SetState(fwdstate st);

private:
	int m_index;
	fwdstate m_state;
	AMX* m_amx;
};

class CHookManager
{
public:
	void clearHandlers() const;
	cell addHandler(AMX* amx, int func, int forward, bool post) const;
	hook_t* getHook(size_t func) const;
	CAmxxHook* getAmxxHook(cell hook) const;

	hook_t* getHookFast(size_t func) const {
		return m_hooklist[func];
	}

private:
	hooklist_t m_hooklist;
};

extern CHookManager g_hookManager;
