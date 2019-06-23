#include "precompiled.h"

CHookManager g_hookManager;

int CHookManager::addHandler(AMX *amx, int func, const char *funcname, int forward, bool post) const
{
	auto hook = m_hooklist.getHookSafe(func);

	if (!hook->post.size() && !hook->pre.size())
	{
		// API hookchain
		hook->registerHookchain();
	}

	auto& dest = post ? hook->post : hook->pre;
	dest.push_back(new CAmxxHookBase(amx, funcname, forward));
	int id = func * MAX_HOOK_FORWARDS + dest.size();
	return post ? -id : id; // use unsigned ids for post hooks
}

void CHookManager::Clear() const
{
	m_hooklist.clear();
}

hook_t *CHookManager::getHook(size_t func) const
{
	return m_hooklist.getHookSafe(func);
}

CAmxxHookBase *CHookManager::getAmxxHook(cell handle) const
{
	bool post = handle < 0;

	if (post)
		handle = ~handle;
	else
		handle--;

	const size_t func = handle / MAX_HOOK_FORWARDS;
	const size_t id = handle & (MAX_HOOK_FORWARDS - 1);
	auto hook = m_hooklist.getHookSafe(func);

	if (hook)
	{
		auto& forwards = post ? hook->post : hook->pre;
		if (id < forwards.size())
			return forwards[id];
	}

	return nullptr;
}
