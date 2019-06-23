#pragma once

#include "amx_hook.h"
#include "hook_list.h"

class CHookManager
{
public:
	void Clear() const;
	cell addHandler(AMX *amx, int func, const char *funcname, int forward, bool post) const;
	hook_t *getHook(size_t func) const;
	CAmxxHookBase *getAmxxHook(cell hook) const;

	hook_t *getHookFast(size_t func) const {
		return m_hooklist[func];
	}

private:
	hooklist_t m_hooklist;
};

extern CHookManager g_hookManager;
