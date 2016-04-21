#include "precompiled.h"

CHookManager g_hookManager;

int CHookManager::addHandler(AMX* amx, int func, int forward, bool post) const
{
	if (!m_hooklist[func]->post.size() && !m_hooklist[func]->pre.size())
	{
		// API hookchain
		m_hooklist[func]->registerHookchain();
	}

	auto& dest = post ? m_hooklist[func]->post : m_hooklist[func]->pre;
	dest.push_back(new CAmxxHook(amx, forward));
	int id = func * MAX_HOOK_FORWARDS + dest.size();
	return post ? -id : id; // use unsigned ids for post hooks
}

AMX* CAmxxHook::GetAmx() const
{
	return m_amx;
}

int CAmxxHook::GetIndex() const
{
	return m_index;
}

fwdstate CAmxxHook::GetState() const
{
	return m_state;
}

void CAmxxHook::SetState(fwdstate st)
{
	m_state = st;
}

void CHookManager::clearHandlers() const
{
#define CLEAR_HOOKLIST(__END__, __START__)\
	for (size_t i = BEGIN_FUNC_REGION(__START__); i < RH_##__END__##_End; ++i) {\
		if (m_hooklist[i] == nullptr)\
			continue;\
		m_hooklist[i]->pre.clear();\
		m_hooklist[i]->post.clear();\
		m_hooklist[i]->unregisterHookchain();\
	}

	CLEAR_HOOKLIST(EngineFunc, engine);
	CLEAR_HOOKLIST(GameDLL, gamedll);
	CLEAR_HOOKLIST(CBasePlayer, player);
}

hook_t* CHookManager::getHook(size_t func) const
{
	return m_hooklist.getHookSafe(func);
}

CAmxxHook* CHookManager::getAmxxHook(cell handle) const
{
	bool post = false;

	if (handle < 0) // post
	{
		handle = ~handle;
		post = true;
	}
	else handle--;

	const size_t func = handle / MAX_HOOK_FORWARDS;
	const size_t id = handle & (MAX_HOOK_FORWARDS - 1);
	auto hook = m_hooklist[func];

	if (hook)
	{
		auto& forwards = post ? hook->post : hook->pre;
		if (id < forwards.size())
			return forwards[id];
	}

	return nullptr;
}
