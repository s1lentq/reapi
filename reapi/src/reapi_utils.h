#pragma once

template <typename T, size_t N>
char(&ArraySizeHelper(T(&array)[N]))[N];
#define arraysize(array) (sizeof(ArraySizeHelper(array)))

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

inline bool GetWeaponInfoRange(WeaponIdType wpnid, bool set_info = false)
{
	if (wpnid == WEAPON_SHIELDGUN)
		return true;

	if (set_info && (wpnid == WEAPON_KNIFE || wpnid == WEAPON_C4))
		return false;

	if (WEAPON_NONE < wpnid && wpnid <= WEAPON_P90)
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
CBaseEntity *GiveNamedItemInternal(AMX *amx, CBasePlayer *pPlayer, const char *pszItemName, const size_t uid = 0);

void GetBonePosition(CBaseEntity *pEntity, int iBone, Vector *pVecOrigin, Vector *pVecAngles);
void GetAttachment(CBaseEntity *pEntity, int iAttachment, Vector *pVecOrigin, Vector *pVecAngles);
void SetBodygroup(CBaseEntity *pEntity, int iGroup, int iValue);
int GetBodygroup(CBaseEntity *pEntity, int iGroup);
bool GetSequenceInfo2(CBaseEntity *pEntity, int *piFlags, float *pflFrameRate, float *pflGroundSpeed);
void RemoveOrDropItem(CBasePlayer *pPlayer, CBasePlayerItem *pItem, GiveType type);

const char *getATypeStr(AType type);

const char *NET_AdrToString(const netadr_t &a, bool onlyBase = false);

extern void NORETURN UTIL_SysError(const char *fmt, ...);
