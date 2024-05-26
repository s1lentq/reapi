#pragma once

#include <array>

// Class managing hooks for game messages
class MessageHookManager
{
public:
	// Adds a hook for a game message
	cell addHook(AMX *amx, int msg_id, const char *funcname, bool post);

	// Removes a hook with the given handle
	bool removeHook(AMX *amx, cell handle);

	// Clears all hooks
	void Clear();

	// Get the AMXX hook with the given handle
	CAmxxHookBase *getAmxxHook(cell handle);

private:
	class MessageHook
	{
	public:
		// Clears all hooks associated with this message
		void clear()
		{
			if (post.size() || pre.size()) {
				for (CAmxxHookBase *h : post)
					delete h;
				post.clear();

				for (CAmxxHookBase *h : pre)
					delete h;
				pre.clear();

				// Unregister the message hook
				if (g_RehldsMessageManager)
					g_RehldsMessageManager->unregisterHook(id, RoutineMessageCallbacks);
			}
		}

		int id;
		std::vector<CAmxxHookBase *> pre, post;
	};

	// Dispatches the callbacks for the message hooks
	void DispatchCallbacks(IVoidHookChain<IMessage *> *chain, IMessage *message);

	// Routine function for dispatching message callbacks
	static void RoutineMessageCallbacks(IVoidHookChain<IMessage *> *chain, IMessage *message);

	// Getter the message hook by ID
	MessageHook *getHook(size_t id);

	// Array of message hooks
	std::array<MessageHook, MAX_USERMESSAGES> hooks;
};

// Global instance of the message hook manager
extern MessageHookManager g_messageHookManager;

// Pointer to the message context within an active hook
extern IMessage *g_activeMessageContext;
