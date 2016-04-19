#pragma once
#include "hook_list.h"

//#define MAX_RANGE_HOOKS		RH_EngineFunc_End + RH_GameDLL_End + RH_CBasePlayer_End

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
	CAmxxHook(AMX* amx, int forward_index) : m_forward(forward_index), m_state(FSTATE_ENABLED), m_amx(amx) {};
	
	int GetForwardID() const { return m_forward; }
	fwdstate GetState() const { return m_state; }
	AMX* GetAmx() const;

public:
	int m_forward;
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
