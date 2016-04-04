#include "precompiled.h"

CHookManager g_hookManager;

CHook *CHookManager::addHandler(int func, int forward, bool post)
{
	if (!hooklist[func]->post.size() && !hooklist[func]->pre.size())
	{
		// register API hookchain
		hooklist[func]->registerHookchain();
	}

	CHook *hook = new CHook(forward);
	if (post)
	{
		hooklist[func]->post.push_back(hook);
	}
	else
	{
		hooklist[func]->pre.push_back(hook);
	}

	return hook;
}

void CHookManager::clearHandlers()
{
#define CLEAR_HOOKLIST(__END__, __START__)\
	for (size_t i = BEGIN_FUNC_REGION(__START__); i < RH_##__END__##_End; ++i) {\
		if (hooklist[i] == nullptr)\
			continue;\
		hooklist[i]->pre.clear();\
		hooklist[i]->post.clear();\
		hooklist[i]->unregisterHookchain();\
	}
	
	CLEAR_HOOKLIST(EngineFunc, engine);
	CLEAR_HOOKLIST(GameDLL, gamedll);
	CLEAR_HOOKLIST(CBasePlayer, player);
}
