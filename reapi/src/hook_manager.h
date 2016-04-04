#pragma once
#include "hook_list.h"

//#define MAX_RANGE_HOOKS		RH_EngineFunc_End + RH_GameDLL_End + RH_CBasePlayer_End

enum fwdstate
{
	FSTATE_INVALID = 0,
	FSTATE_OK,
	FSTATE_PAUSE,
	FSTATE_STOP
};

class CHook
{
public:
	CHook(int forward_index) : m_forward(forward_index), m_state(FSTATE_OK) {};
	
	int GetForwardID() const { return m_forward; }
	fwdstate GetState() const { return m_state; }

public:
	int m_forward;
	fwdstate m_state;

	struct data_return_t
	{
		char*		m_string;
		float		m_float;
		int		m_interger;
		CBaseEntity*	m_classptr;
	};
	data_return_t m_data;
};

class CHookManager
{
public:
	void clearHandlers();
	CHook *addHandler(int func, int forward, bool post);
};

extern CHookManager g_hookManager;
