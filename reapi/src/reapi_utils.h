#pragma once

template <typename T, size_t N>
char(&ArraySizeHelper(T(&array)[N]))[N];
#define arraysize(array) (sizeof(ArraySizeHelper(array)))

#define INDEXENT edictByIndex
#define ENTINDEX indexOfEdict

extern edict_t* g_pEdicts;
extern enginefuncs_t* g_pengfuncsTable;

inline size_t indexOfEdict(edict_t* ed)
{
	return ed - g_pEdicts;
}

inline size_t indexOfEdict(entvars_t* pev)
{
	return indexOfEdict(pev->pContainingEntity);
}

inline edict_t* edictByIndex(size_t index)
{
	return g_pEdicts + index;
}

template<typename T>
T* getPrivate(int index)
{
	return (T *)edictByIndex(index)->pvPrivateData;
}

inline entvars_t* PEV(int index)
{
	return &edictByIndex(index)->v;
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
inline T get_member_direct(void *ptr, int offset, int element = 0, int size = 0)
{
	return reinterpret_cast<T>(reinterpret_cast<int8 *>(ptr) + offset + (element * size));
}

template <typename T>
inline T get_member_direct(edict_t *pEntity, int offset, int element = 0, int size = 0)
{
	return get_member_direct<T>(pEntity->pvPrivateData, offset, element, size);
}

void Broadcast(const char *sentence);
void UpdateTeamScores();

extern void __declspec(noreturn) UTIL_SysError(const char *fmt, ...);
