#pragma once

#define PARAMS_COUNT            (params[0] / sizeof(cell))

#define CHECK_ISPLAYER(x)       if (unlikely(params[x] <= 0 || params[x] > gpGlobals->maxClients)) { MF_LogError(amx, AMX_ERR_NATIVE, "%s: invalid player index %i [%s]", __FUNCTION__, params[x], #x); return FALSE; }
#define CHECK_ISENTITY(x)       if (unlikely(params[x] < 0 || params[x] > gpGlobals->maxEntities)) { MF_LogError(amx, AMX_ERR_NATIVE, "%s: invalid entity index %i [%s]", __FUNCTION__, params[x], #x); return FALSE; }
#define CHECK_GAMERULES()       if (unlikely(!g_pGameRules)) { MF_LogError(amx, AMX_ERR_NATIVE, "%s: gamerules not initialized", __FUNCTION__); return FALSE; }
#define CHECK_CONNECTED(x, y)   if (unlikely(x == nullptr || x->has_disconnected)) { MF_LogError(amx, AMX_ERR_NATIVE, "%s: player %i is not connected", __FUNCTION__, params[y]); return FALSE; }

class CAmxArg
{
public:
	CAmxArg(AMX* amx, cell value) : m_amx(amx), m_value(value) {}
	operator float() const
	{
		return *(float *)&m_value;
	}
	operator Vector&() const
	{
		return *(Vector *)getAmxAddr(m_amx, m_value);
	}
	operator entvars_s*() const
	{
		auto pev = PEV(m_value); // faster
		return m_value < 0 ? nullptr : pev;
	}
	operator int() const
	{
		return m_value;
	}
	operator size_t() const
	{
		return size_t(m_value);
	}
	operator bool() const
	{
		return m_value != 0;
	}
	operator CBaseEntity*() const
	{
		if (m_value < 0)
			return nullptr;
		return getPrivate<CBaseEntity>(m_value);
	}
	operator CBasePlayer*() const
	{
		if (m_value < 0)
			return nullptr;
		return UTIL_PlayerByIndex(m_value);
	}
	operator IGameClient *() const
	{
		if (m_value <= 0)
			return nullptr;
		return g_RehldsSvs->GetClient(m_value - 1); // id: 0 - 31
	}
	operator edict_t *() const
	{
		return edictByIndexAmx(m_value);
	}
	operator const float *() const
	{
		return (float *)getAmxAddr(m_amx, m_value);
	}
	operator TeamName() const
	{
		return static_cast<TeamName>(m_value);
	}
	operator ModelName() const
	{
		return static_cast<ModelName>(m_value);
	}
	operator PLAYER_ANIM() const
	{
		return static_cast<PLAYER_ANIM>(m_value);
	}
	Vector& vector() const
	{
		return operator Vector&();
	}

private:
	AMX*	m_amx;
	cell	m_value;
};

class CAmxArgs
{
public:
	CAmxArgs(AMX* amx, cell* params) : m_amx(amx), m_params(params) {}
	CAmxArg operator[](size_t index) const
	{
		return CAmxArg(m_amx, m_params[index]);
	}

private:
	AMX*	m_amx;
	cell*	m_params;
};

struct getAmxString
{
	getAmxString(cell* src, size_t* len = nullptr)
	{
		getAmxStringTemp(src, temp, sizeof temp - 1, len);
	}

	getAmxString(AMX* amx, cell addr, size_t* len = nullptr)
	{
		getAmxStringTemp(getAmxAddr(amx, addr), temp, sizeof temp - 1, len);
	}

	operator char *()
	{
		return temp;
	}

	char temp[1024];
};

inline void fillNatives(AMX_NATIVE_INFO* table, cell (AMX_NATIVE_CALL with)(AMX *, cell *))
{
	for (size_t i = 0; table[i].name; i++)
		table[i].func = with;
}
