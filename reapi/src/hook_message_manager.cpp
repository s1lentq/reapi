#include "precompiled.h"

// Global instance of the message hook manager
MessageHookManager g_messageHookManager;

// Pointer to the message context within an active hook
IMessage *g_activeMessageContext = nullptr;

/**
* @brief Dispatches the callbacks associated with the given message
*
* This function executes the hooks associated with the given message type,
* allowing modifications or interception of the message's behavior
*
* @param chain     Pointer to the hook chain for the message
* @param message   Pointer to the message parameters
*/
void MessageHookManager::DispatchCallbacks(IVoidHookChain<IMessage *> *chain, IMessage *message)
{
	// Get the hook associated with the given message type
	MessageHook *msg = getHook(message->getId());

	// If somehow no hook is found, just continue hookchain
	if (!msg) {
		chain->callNext(message);
		return;
	}

	// Save the current message context and set the new one
	IMessage *savedContext = g_activeMessageContext;
	g_activeMessageContext = message;

	int hookState = HC_CONTINUE;

	// Execute pre-hooks
	for (const CAmxxHookBase *fwd : msg->pre)
	{
		if (likely(fwd->GetState() == FSTATE_ENABLED))
		{
			int ret = g_amxxapi.ExecuteForward(fwd->GetFwdIndex(), message->getId(), message->getDest(), indexOfEdictAmx(message->getEdict(), 0 /* most friendly to use 0 as invalid index for message */));
			if (unlikely(ret == HC_BREAK)) {
				g_activeMessageContext = savedContext;
				return;
			}

			if (unlikely(ret > hookState))
				hookState = ret;
		}
	}

	// If the hook state is not superseded, continue hookchain
	if (hookState != HC_SUPERCEDE) {
		g_activeMessageContext = nullptr;
		chain->callNext(message);
		g_activeMessageContext = message;
	}

	// Execute post-hooks
	for (const CAmxxHookBase *fwd : msg->post)
	{
		if (likely(fwd->GetState() == FSTATE_ENABLED))
		{
			int ret = g_amxxapi.ExecuteForward(fwd->GetFwdIndex(), message->getId(), message->getDest(), indexOfEdictAmx(message->getEdict(), 0 /* most friendly to use 0 as invalid index for message */));
			if (unlikely(ret == HC_BREAK))
				break;
		}
	}

	// Restore the original message context
	g_activeMessageContext = savedContext;
}

/**
* @brief Adds a hook for the specified message ID
*
* This function registers a new hook for the specified message ID and associates it with the provided function
*
* @param msg_id    ID of the message to hook
* @param funcname  Name of the function to call when the hook is triggered
* @param post      Indicates whether the hook should be executed after the default behavior (true) or before (false)
*
* @return Returns a handle to the registered hook, or 0 if the registration fails
*/
cell MessageHookManager::addHook(AMX *amx, int msg_id, const char *funcname, bool post)
{
	int fwid = g_amxxapi.RegisterSPForwardByName(amx, funcname, FP_CELL, FP_CELL, FP_CELL, FP_DONE);
	if (unlikely(fwid == -1)) {
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: register forward failed.", __FUNCTION__);
		return 0;
	}

	// Get the message hook associated with the ID
	MessageHook &msg = hooks[msg_id];

	// If it's the first hook for this message, register it with message manager
	if (!msg.post.size() && !msg.pre.size())
	{
		msg.id = msg_id;
		g_RehldsMessageManager->registerHook(msg_id, RoutineMessageCallbacks);
	}

	// Determine whether to add the hook to the pre or post vector
	std::vector<CAmxxHookBase *> &dest = post ? msg.post : msg.pre;

	// Pack msg_id and forward ID into the handle value
	cell handle = (msg_id * MAX_USERMESSAGES) + dest.size() + 1;

	dest.emplace_back(new CAmxxHookBase(amx, funcname, fwid, -1));

	return post ? -handle : handle;
}

/**
* @brief Removes a hook associated with the specified handle
*
* This function removes the hook associated with the given handle from the hook manager
*
* @param handle    Handle to the hook to be removed
*
* @return Returns  true if the hook is successfully removed, false otherwise
*/
bool MessageHookManager::removeHook(AMX *amx, cell handle)
{
	// Determine whether the hook is a post-hook
	bool post = handle < 0;
	if (post)
		handle = ~handle;
	else
		handle--;

	// Unpack the message ID and forward ID from the handle
	const size_t id = handle / MAX_USERMESSAGES;
	const size_t fwid = handle & (MAX_USERMESSAGES - 1);

	// Get the message hook by ID, returns nullptr if the ID is invalid
	MessageHook *msg = getHook(id);
	if (msg)
	{
		// Get the appropriate vector of hooks (pre or post)
		std::vector<CAmxxHookBase *> &forwards = post ? msg->post : msg->pre;

		// Check if the forward ID is within the vector bounds
		if (fwid < forwards.size())
		{
			// Delete the hook and erase it from the vector
			delete forwards[fwid];
			forwards.erase(forwards.begin() + fwid);
			return true;
		}
	}

	return false;
}

/**
* @brief Retrieves the AMXX hook associated with the specified handle
*
* This function returns the AMXX hook associated with the provided handle
*
* @param           handle Handle of the hook to retrieve
*
* @return Pointer to the AMXX hook if found, nullptr otherwise
*/
CAmxxHookBase *MessageHookManager::getAmxxHook(cell handle)
{
	// Determine whether the hook is a post-hook
	bool post = handle < 0;
	if (post)
		handle = ~handle;
	else
		handle--;

	// Unpack the message ID and forward ID from the handle
	const size_t id = handle / MAX_USERMESSAGES;
	const size_t fwid = handle & (MAX_USERMESSAGES - 1);

	// Get the message hook by ID, returns nullptr if the ID is invalid
	MessageHook *msg = getHook(id);
	if (msg)
	{
		// Get the appropriate vector of hooks (pre or post)
		std::vector<CAmxxHookBase *> &forwards = post ? msg->post : msg->pre;

		// Check if the forward ID is within the vector bounds
		if (fwid < forwards.size())
			return forwards[fwid];
	}

	return nullptr;
}

/**
* @brief Get the message hook by ID.
*
* This function safely retrieves the message hook associated with the provided ID.
*
* @param id        ID of the message hook to retrieve.
*
* @return Pointer to the message hook if found, nullptr otherwise.
*/
MessageHookManager::MessageHook *MessageHookManager::getHook(size_t id)
{
	if (id <= 0 || id >= MAX_USERMESSAGES)
		return nullptr;

	return &hooks[id];
}

/**
* @brief Clears all registered message hooks
*
* This function clears all registered message hooks from the hook manager
*/
void MessageHookManager::Clear()
{
	for (auto &h : hooks)
		h.clear();
}

/**
* @brief Dispatches the message callbacks as a routine
*/
void MessageHookManager::RoutineMessageCallbacks(IVoidHookChain<IMessage *> *chain, IMessage *message)
{
	g_messageHookManager.DispatchCallbacks(chain, message);
}
