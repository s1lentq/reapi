#pragma once

#define CHECK_ISPLAYER(x)	if (params[x] <= 0 || params[x] > gpGlobals->maxClients) { MF_LogError(amx, AMX_ERR_NATIVE, "%s: invalid player index %i [%s]", __FUNCTION__, params[x], #x); return FALSE; }
#define CHECK_ISENTITY(x)	if (params[x] > gpGlobals->maxEntities) { MF_LogError(amx, AMX_ERR_NATIVE, "%s: invalid entity index %i [%s]", __FUNCTION__, params[x], #x); return FALSE; }

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
		return g_ReGameFuncs->UTIL_PlayerByIndex(m_value);
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

inline void fillNatives(AMX_NATIVE_INFO* table, cell (AMX_NATIVE_CALL with)(AMX *, cell *))
{
	for (size_t i = 0; table[i].name; i++)
		table[i].func = with;
}
