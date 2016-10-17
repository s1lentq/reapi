#pragma once

template <typename T, size_t N>
char(&ArraySizeHelper(T(&array)[N]))[N];
#define arraysize(array) (sizeof(ArraySizeHelper(array)))

#define INDEXENT edictByIndex
#define ENTINDEX indexOfEdict

extern enginefuncs_t* g_pengfuncsTable;
extern DLL_FUNCTIONS *g_pFunctionTable;

inline void EMESSAGE_BEGIN(int msg_dest, int msg_type, const float *pOrigin = nullptr, edict_t *ed = nullptr) { (*g_pengfuncsTable->pfnMessageBegin)(msg_dest, msg_type, pOrigin, ed); }
inline void EMESSAGE_END() { (*g_pengfuncsTable->pfnMessageEnd)(); }
inline void EWRITE_BYTE(int iValue) { (*g_pengfuncsTable->pfnWriteByte)(iValue); }
inline void EWRITE_CHAR(int iValue) { (*g_pengfuncsTable->pfnWriteChar)(iValue); }
inline void EWRITE_SHORT(int iValue) { (*g_pengfuncsTable->pfnWriteShort)(iValue); }
inline void EWRITE_LONG(int iValue) { (*g_pengfuncsTable->pfnWriteLong)(iValue); }
inline void EWRITE_ANGLE(float flValue) { (*g_pengfuncsTable->pfnWriteAngle)(flValue); }
inline void EWRITE_COORD(float flValue) { (*g_pengfuncsTable->pfnWriteCoord)(flValue); }
inline void EWRITE_STRING(const char *sz) { (*g_pengfuncsTable->pfnWriteString)(sz); }
inline void EWRITE_ENTITY(int iValue) { (*g_pengfuncsTable->pfnWriteEntity)(iValue); }

#ifndef _WIN32
#define _strlwr(p) for (int i = 0; p[i] != 0; i++) p[i] = tolower(p[i]);
#endif

inline size_t indexOfEdict(edict_t* ed)
{
	return ed - g_pEdicts;
}

inline size_t indexOfEdict(entvars_t* pev)
{
	return indexOfEdict(pev->pContainingEntity);
}

// safe to index -1
inline edict_t* edictByIndexAmx(int index)
{
	auto ed = g_pEdicts + index;
	if (unlikely(index < 0))
		ed = nullptr;
	return ed;
}

// fast
inline edict_t* edictByIndex(int index)
{
	return g_pEdicts + index;
}

template<typename T>
inline T* getPrivate(int index)
{
	T* pdata = nullptr;
	if (likely(index >= 0))
		pdata = (T *)g_pEdicts[index].pvPrivateData;
	return pdata;
}

inline entvars_t* PEV(int index)
{
	entvars_t* pvars = nullptr;
	if (likely(index >= 0))
		pvars = &g_pEdicts[index].v;
	return pvars;
}

// HLTypeConversion.h -> AMXModX
template <typename T>
inline T &ref_member(void *ptr, int offset, int element = 0)
{
	return *reinterpret_cast<T *>((reinterpret_cast<int8 *>(ptr) + offset + (element * sizeof(T))));
}

template <typename T>
inline T &get_member(void *ptr, int offset, int element = 0)
{
	return ref_member<T>(ptr, offset, element);
}

template <typename T>
inline T &get_member(edict_t *pEntity, int offset, int element = 0)
{
	return get_member<T>(pEntity->pvPrivateData, offset, element);
}

template <typename T>
inline void set_member(void *ptr, int offset, T value, int element = 0)
{
	ref_member<T>(ptr, offset, element) = value;
}

template <typename T>
inline void set_member(edict_t *pEntity, int offset, T value, int element = 0)
{
	set_member<T>(pEntity->pvPrivateData, offset, value, element);
}

template <typename T>
inline T* get_member_direct(void *ptr, int offset, int element = 0, int size = sizeof(T))
{
	return reinterpret_cast<T *>(reinterpret_cast<int8 *>(ptr) + offset + (element * size));
}

template <typename T>
inline T get_member_direct(edict_t *pEntity, int offset, int element = 0, int size = 0)
{
	return get_member_direct<T>(pEntity->pvPrivateData, offset, element, size);
}

inline bool GetWeaponInfoRange(WeaponIdType wpnid)
{
	if (wpnid == WEAPON_SHIELDGUN)
		return true;

	if (wpnid > WEAPON_NONE && wpnid != WEAPON_C4 && wpnid != WEAPON_KNIFE && wpnid <= WEAPON_P90)
		return true;

	return false;
}

inline const char *GetTeamName(TeamName team)
{
	switch (team)
	{
	case CT:
		return "CT";
	case TERRORIST:
		return "TERRORIST";
	case SPECTATOR:
		return "SPECTATOR";
	default:
		return "UNASSIGNED";
	}
}

void Broadcast(const char *sentence);
void UpdateTeamScores();
ModelName GetModelAuto(TeamName team);
void UTIL_ServerPrint(const char *fmt, ...);

extern void __declspec(noreturn) UTIL_SysError(const char *fmt, ...);

class CTempStrings
{
public:
	CTempStrings();
	char* push(AMX* amx);
	void pop(size_t count);

	enum
	{
		STRINGS_MAX = 16,
		STRING_SIZE = 1024,
		STRING_LEN = STRING_SIZE - 1
	};

private:
	size_t m_current;
	char m_strings[STRINGS_MAX][STRING_SIZE];
};
