#include "precompiled.h"

#if _MSC_VER >= 1900
#pragma warning(disable:4573)
#endif

#if _MSC_VER <= 1800 && __INTEL_COMPILER < 1500
	// BUG BUG
	// http://connect.microsoft.com/VisualStudio/feedbackdetail/view/797682/c-decltype-of-class-member-access-incompletely-implemented
	#define decltypefx(cx, pref, mx) decltype(std::declval<cx>().pref##mx)
	#define decltypefxdot(cx, pref, mx) decltype(std::declval<cx>().pref.mx)
#else
	#define decltypefx(cx, pref, mx) decltype(cx::pref##mx)
	#define decltypefxdot(cx, pref, mx) decltype(cx::pref.mx)
#endif

#define STRUCT_MEMBERS(cx, mx, postf)           ((!(postf & (MAX_REGION_RANGE - 1)) ? regmember::current_cell = 1, true : false) || (postf & (MAX_REGION_RANGE - 1)) == regmember::current_cell++) ? regmember([](member_t* ptr){ decltypefx(cx, , mx) f = {};ptr->size = getTypeSize(f);ptr->max_size = sizeof(f);ptr->offset = offsetof(cx, mx);ptr->type = getMemberType(f);ptr->name = #postf;}) : regmember(#mx)
#define CLASS_MEMBERS(cx, mx, postf)            ((!(postf & (MAX_REGION_RANGE - 1)) ? regmember::current_cell = 1, true : false) || (postf & (MAX_REGION_RANGE - 1)) == regmember::current_cell++) ? regmember([](member_t* ptr){ decltypefx(cx, , mx) f = {};ptr->size = getTypeSize(f);ptr->max_size = sizeof(f);ptr->offset = offsetof(cx, mx);ptr->type = getMemberType(f);ptr->name = #postf;ptr->pfnIsRefsToClass = [](void *pEntity){ return dynamic_cast<cx *>((cx::BaseClass *)pEntity) != nullptr;};}) : regmember(#mx)
#define CLASS_MEMBERS_PREF(cx, mx, postf, pref) ((!(postf & (MAX_REGION_RANGE - 1)) ? regmember::current_cell = 1, true : false) || (postf & (MAX_REGION_RANGE - 1)) == regmember::current_cell++) ? regmember([](member_t* ptr){ decltypefx(cx, pref, mx) f = {};ptr->size = getTypeSize(f);ptr->max_size = sizeof(f);ptr->offset = offsetof(cx, pref##mx);ptr->type = getMemberType(f);ptr->name = #postf;ptr->pfnIsRefsToClass = [](void *pEntity){ return dynamic_cast<cx *>((cx::BaseClass *)pEntity) != nullptr;};}) : regmember(#pref#mx)
#define CLASS_MEMBERS_DOT(cx, mx, postf, pref)  ((!(postf & (MAX_REGION_RANGE - 1)) ? regmember::current_cell = 1, true : false) || (postf & (MAX_REGION_RANGE - 1)) == regmember::current_cell++) ? regmember([](member_t* ptr){ decltypefxdot(cx, pref, mx) f = {};ptr->size = getTypeSize(f);ptr->max_size = sizeof(f);ptr->offset = offsetof(cx, pref.mx);ptr->type = getMemberType(f);ptr->name = #postf;ptr->pfnIsRefsToClass = [](void *pEntity){ return dynamic_cast<cx *>((cx::BaseClass *)pEntity) != nullptr;};}) : regmember(#pref"."#mx)

#define GM_MEMBERS(mx)           CLASS_MEMBERS(CHalfLifeMultiplay, mx, mx)
#define GM_VOICE_MEMBERS(mx)     CLASS_MEMBERS_DOT(CHalfLifeMultiplay, mx, mx, m_VoiceGameMgr)
#define BASE_MEMBERS(mx)         CLASS_MEMBERS(CBaseEntity, mx, mx)
#define ANIM_MEMBERS(mx)         CLASS_MEMBERS(CBaseAnimating, mx, mx)
#define MONST_MEMBERS(mx)        CLASS_MEMBERS(CBaseMonster, mx, mx)
#define PL_MEMBERS(mx)           CLASS_MEMBERS(CBasePlayer, mx, mx)
#define EVAR_MEMBERS(mx)         STRUCT_MEMBERS(com_entvars, mx, var_##mx)
#define PMOVE_MEMBERS(mx)        STRUCT_MEMBERS(com_playermove, mx, pm_##mx)
#define MOVEVAR_MEMBERS(mx)      STRUCT_MEMBERS(movevars_t, mx, mv_##mx)
#define UCMD_MEMBERS(mx)         STRUCT_MEMBERS(usercmd_s, mx, ucmd_##mx)
#define NETCHAN_MEMBERS(mx)      STRUCT_MEMBERS(netchan_t, mx, net_##mx)
#define PMTRACE_MEMBERS(mx)      STRUCT_MEMBERS(pmtrace_s, mx, pmt_##mx)
#define NETADR_MEMBERS(mx)       STRUCT_MEMBERS(netadr_t, mx, netadr_##mx)
#define CSPL_MEMBERS(mx)         CLASS_MEMBERS(CCSPlayer, mx, mx)
#define BASEITEM_MEMBERS(mx)     CLASS_MEMBERS(CBasePlayerItem, mx, mx)
#define BASEWPN_MEMBERS(mx)      CLASS_MEMBERS_PREF(CBasePlayerWeapon, mx, m_Weapon_##mx, m_)
#define WPNBOX_MEMBERS(mx)       CLASS_MEMBERS_PREF(CWeaponBox, mx, m_WeaponBox_##mx, m_)
#define ARMOURY_MEMBERS(mx)      CLASS_MEMBERS_PREF(CArmoury, mx, m_Armoury_##mx, m_)
#define GRENADE_MEMBERS(mx)      CLASS_MEMBERS_PREF(CGrenade, mx, m_Grenade_##mx, m_)
#define P228_MEMBERS(mx)         CLASS_MEMBERS_PREF(CP228, mx, m_P228_##mx, m_)
#define SCOUT_MEMBERS(mx)        CLASS_MEMBERS_PREF(CSCOUT, mx, m_SCOUT_##mx, m_)
#define HEGREN_MEMBERS(mx)       CLASS_MEMBERS_PREF(CHEGrenade, mx, m_HEGrenade_##mx, m_)
#define XM1014_MEMBERS(mx)       CLASS_MEMBERS_PREF(CXM1014, mx, m_XM1014_##mx, m_)
#define C4_MEMBERS(mx)           CLASS_MEMBERS_PREF(CC4, mx, m_C4_##mx, m_)
#define MAC10_MEMBERS(mx)        CLASS_MEMBERS_PREF(CMAC10, mx, m_MAC10_##mx, m_)
#define AUG_MEMBERS(mx)          CLASS_MEMBERS_PREF(CAUG, mx, m_AUG_##mx, m_)
#define SMOKEGREN_MEMBERS(mx)    CLASS_MEMBERS_PREF(CSmokeGrenade, mx, m_SmokeGrenade_##mx, m_)
#define ELITE_MEMBERS(mx)        CLASS_MEMBERS_PREF(CELITE, mx, m_ELITE_##mx, m_)
#define FIVESEVEN_MEMBERS(mx)    CLASS_MEMBERS_PREF(CFiveSeven, mx, m_FiveSeven_##mx, m_)
#define UMP45_MEMBERS(mx)        CLASS_MEMBERS_PREF(CUMP45, mx, m_UMP45_##mx, m_)
#define SG550_MEMBERS(mx)        CLASS_MEMBERS_PREF(CSG550, mx, m_SG550_##mx, m_)
#define GALIL_MEMBERS(mx)        CLASS_MEMBERS_PREF(CGalil, mx, m_Galil_##mx, m_)
#define FAMAS_MEMBERS(mx)        CLASS_MEMBERS_PREF(CFamas, mx, m_Famas_##mx, m_)
#define USP_MEMBERS(mx)          CLASS_MEMBERS_PREF(CUSP, mx, m_USP_##mx, m_)
#define GLOCK18_MEMBERS(mx)      CLASS_MEMBERS_PREF(CGLOCK18, mx, m_GLOCK18_##mx, m_)
#define AWP_MEMBERS(mx)          CLASS_MEMBERS_PREF(CAWP, mx, m_AWP_##mx, m_)
#define MP5N_MEMBERS(mx)         CLASS_MEMBERS_PREF(CMP5N, mx, m_MP5N_##mx, m_)
#define M249_MEMBERS(mx)         CLASS_MEMBERS_PREF(CM249, mx, m_M249_##mx, m_)
#define M3_MEMBERS(mx)           CLASS_MEMBERS_PREF(CM3, mx, m_M3_##mx, m_)
#define M4A1_MEMBERS(mx)         CLASS_MEMBERS_PREF(CM4A1, mx, m_M4A1_##mx, m_)
#define TMP_MEMBERS(mx)          CLASS_MEMBERS_PREF(CTMP, mx, m_TMP_##mx, m_)
#define G3SG1_MEMBERS(mx)        CLASS_MEMBERS_PREF(CG3SG1, mx, m_G3SG1_##mx, m_)
#define DEAGLE_MEMBERS(mx)       CLASS_MEMBERS_PREF(CDEAGLE, mx, m_DEAGLE_##mx, m_)
#define SG552_MEMBERS(mx)        CLASS_MEMBERS_PREF(CSG552, mx, m_SG552_##mx, m_)
#define AK47_MEMBERS(mx)         CLASS_MEMBERS_PREF(CAK47, mx, m_AK47_##mx, m_)
#define KNIFE_MEMBERS(mx)        CLASS_MEMBERS_PREF(CKnife, mx, m_Knife_##mx, m_)
#define P90_MEMBERS(mx)          CLASS_MEMBERS_PREF(CP90, mx, m_P90_##mx, m_)
#define SHIELD_MEMBERS(mx)       CLASS_MEMBERS_PREF(CWShield, mx, m_Shield_##mx, m_)
#define REBUYSTRUCT_MEMBERS(mx)  STRUCT_MEMBERS(RebuyStruct, mx, mx)
#define MAPINFO_MEMBERS(mx)      CLASS_MEMBERS_PREF(CMapInfo, mx, m_MapInfo_##mx, m_)
#define CSPLWPN_MEMBERS(mx)      CLASS_MEMBERS_PREF(CCSPlayerWeapon, mx, m_Weapon_##mx, m_)
#define GIB_MEMBERS(mx)          CLASS_MEMBERS_PREF(CGib, mx, m_Gib_##mx, m_)
#define CSENT_MEMBERS(mx)        CLASS_MEMBERS(CCSEntity, mx, mx)

inline MType getMemberType(float*)              { return MEMBER_FLOAT; }
inline MType getMemberType(float)               { return MEMBER_FLOAT; }

inline MType getMemberType(double)              { return MEMBER_DOUBLE; }

inline MType getMemberType(CBasePlayer**)       { return MEMBER_CLASSPTR; }
inline MType getMemberType(CBasePlayer*)        { return MEMBER_CLASSPTR; }
inline MType getMemberType(CBasePlayerItem**)   { return MEMBER_CLASSPTR; }
inline MType getMemberType(CBasePlayerItem*)    { return MEMBER_CLASSPTR; }
inline MType getMemberType(CBaseEntity*)        { return MEMBER_CLASSPTR; }

inline MType getMemberType(EHANDLE)             { return MEMBER_EHANDLE; }
inline MType getMemberType(entvars_t*)          { return MEMBER_EVARS; }
inline MType getMemberType(edict_t*)            { return MEMBER_EDICT; }

inline MType getMemberType(Vector*)             { return MEMBER_VECTOR; }
inline MType getMemberType(Vector)              { return MEMBER_VECTOR; }

inline MType getMemberType(char*)               { return MEMBER_STRING; }
inline MType getMemberType(string_t)            { return MEMBER_QSTRING; }
inline MType getMemberType(string_t*)           { return MEMBER_QSTRING; }
inline MType getMemberType(qstring_t)           { return MEMBER_QSTRING; }
inline MType getMemberType(qstring_t*)          { return MEMBER_QSTRING; }

inline MType getMemberType(char)                { return MEMBER_BYTE; }
inline MType getMemberType(byte)                { return MEMBER_BYTE; }
inline MType getMemberType(byte*)               { return MEMBER_BYTE; }

inline MType getMemberType(int*)                { return MEMBER_INTEGER; }
inline MType getMemberType(int)                 { return MEMBER_INTEGER; }
inline MType getMemberType(unsigned)            { return MEMBER_INTEGER; }
inline MType getMemberType(TeamName)            { return MEMBER_INTEGER; }
inline MType getMemberType(JoinState)           { return MEMBER_INTEGER; }
inline MType getMemberType(ModelName)           { return MEMBER_INTEGER; }
inline MType getMemberType(_Menu)               { return MEMBER_INTEGER; }
inline MType getMemberType(MusicState)          { return MEMBER_INTEGER; }
inline MType getMemberType(Activity)            { return MEMBER_INTEGER; }
inline MType getMemberType(MONSTERSTATE)        { return MEMBER_INTEGER; }
inline MType getMemberType(ArmorType)           { return MEMBER_INTEGER; }
inline MType getMemberType(ArmouryItemPack)     { return MEMBER_INTEGER; }
inline MType getMemberType(InfoMapBuyParam)     { return MEMBER_INTEGER; }
inline MType getMemberType(SecondaryAtkState)   { return MEMBER_INTEGER; }
inline MType getMemberType(netadrtype_t)        { return MEMBER_INTEGER; }
inline MType getMemberType(netsrc_t)            { return MEMBER_INTEGER; }
inline MType getMemberType(netadr_t)            { return MEMBER_NETADR; }

inline MType getMemberType(TraceResult)         { return MEMBER_TRACERESULT; }

inline MType getMemberType(short)               { return MEMBER_SHORT; }
inline MType getMemberType(unsigned short)      { return MEMBER_SHORT; }

inline MType getMemberType(bool)                { return MEMBER_BOOL; }
inline MType getMemberType(bool*)               { return MEMBER_BOOL; }
inline MType getMemberType(CUnifiedSignals)     { return MEMBER_SIGNALS; }
inline MType getMemberType(RebuyStruct)         { return MEBMER_REBUYSTRUCT; }

inline MType getMemberType(pmtrace_t)           { return MEMBER_PMTRACE; }
inline MType getMemberType(usercmd_s)           { return MEBMER_USERCMD; }

template<typename T> struct always_false: std::false_type {};

template<typename T>
inline MType getMemberType(T) { static_assert(always_false<T>::value, "Not implemented overload"); return MEMBER_NONE; }

template<typename T, size_t size>
inline size_t getTypeSize(T type[size]) { return sizeof(T); }

template<typename T>
inline size_t getTypeSize(T& type) { return sizeof(T); }

struct regmember
{
	template<typename T>
	regmember(T lambdaFunc) { lambdaFunc(&member); }

	regmember(const char *name) { UTIL_SysError("%s doesn't match member definition", name); }	// to cause a amxx module failure.
	operator member_t() const { return member; }
	member_t member;

	static int current_cell;				// the counter of cells
};

int regmember::current_cell = 1;

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-offsetof"
#endif // #ifdef __GNUC__

member_t memberlist_gamerules[] = {
	GM_MEMBERS(m_bFreezePeriod),
	GM_MEMBERS(m_bBombDropped),
	GM_MEMBERS(m_GameDesc),
	// m_VoiceGameMgr ->
		GM_VOICE_MEMBERS(m_msgPlayerVoiceMask),
		GM_VOICE_MEMBERS(m_msgRequestState),
		GM_VOICE_MEMBERS(m_nMaxPlayers),
		GM_VOICE_MEMBERS(m_UpdateInterval),
	GM_MEMBERS(m_flRestartRoundTime),
	GM_MEMBERS(m_flCheckWinConditions),
	GM_MEMBERS(m_fRoundStartTime),
	GM_MEMBERS(m_iRoundTime),
	GM_MEMBERS(m_iRoundTimeSecs),
	GM_MEMBERS(m_iIntroRoundTime),
	GM_MEMBERS(m_fRoundStartTimeReal),
	GM_MEMBERS(m_iAccountTerrorist),
	GM_MEMBERS(m_iAccountCT),
	GM_MEMBERS(m_iNumTerrorist),
	GM_MEMBERS(m_iNumCT),
	GM_MEMBERS(m_iNumSpawnableTerrorist),
	GM_MEMBERS(m_iNumSpawnableCT),
	GM_MEMBERS(m_iSpawnPointCount_Terrorist),
	GM_MEMBERS(m_iSpawnPointCount_CT),
	GM_MEMBERS(m_iHostagesRescued),
	GM_MEMBERS(m_iHostagesTouched),
	GM_MEMBERS(m_iRoundWinStatus),
	GM_MEMBERS(m_iNumCTWins),
	GM_MEMBERS(m_iNumTerroristWins),
	GM_MEMBERS(m_bTargetBombed),
	GM_MEMBERS(m_bBombDefused),
	GM_MEMBERS(m_bMapHasBombTarget),
	GM_MEMBERS(m_bMapHasBombZone),
	GM_MEMBERS(m_bMapHasBuyZone),
	GM_MEMBERS(m_bMapHasRescueZone),
	GM_MEMBERS(m_bMapHasEscapeZone),
	GM_MEMBERS(m_bMapHasVIPSafetyZone),
	GM_MEMBERS(m_bMapHasCameras),
	GM_MEMBERS(m_iC4Timer),
	GM_MEMBERS(m_iC4Guy),
	GM_MEMBERS(m_iLoserBonus),
	GM_MEMBERS(m_iNumConsecutiveCTLoses),
	GM_MEMBERS(m_iNumConsecutiveTerroristLoses),
	GM_MEMBERS(m_fMaxIdlePeriod),
	GM_MEMBERS(m_iLimitTeams),
	GM_MEMBERS(m_bLevelInitialized),
	GM_MEMBERS(m_bRoundTerminating),
	GM_MEMBERS(m_bCompleteReset),
	GM_MEMBERS(m_flRequiredEscapeRatio),
	GM_MEMBERS(m_iNumEscapers),
	GM_MEMBERS(m_iHaveEscaped),
	GM_MEMBERS(m_bCTCantBuy),
	GM_MEMBERS(m_bTCantBuy),
	GM_MEMBERS(m_flBombRadius),
	GM_MEMBERS(m_iConsecutiveVIP),
	GM_MEMBERS(m_iTotalGunCount),
	GM_MEMBERS(m_iTotalGrenadeCount),
	GM_MEMBERS(m_iTotalArmourCount),
	GM_MEMBERS(m_iUnBalancedRounds),
	GM_MEMBERS(m_iNumEscapeRounds),
	GM_MEMBERS(m_iMapVotes),
	GM_MEMBERS(m_iLastPick),
	GM_MEMBERS(m_iMaxMapTime),
	GM_MEMBERS(m_iMaxRounds),
	GM_MEMBERS(m_iTotalRoundsPlayed),
	GM_MEMBERS(m_iMaxRoundsWon),
	GM_MEMBERS(m_iStoredSpectValue),
	GM_MEMBERS(m_flForceCameraValue),
	GM_MEMBERS(m_flForceChaseCamValue),
	GM_MEMBERS(m_flFadeToBlackValue),
	GM_MEMBERS(m_pVIP),
	GM_MEMBERS(m_pVIPQueue),
	GM_MEMBERS(m_flIntermissionEndTime),
	GM_MEMBERS(m_flIntermissionStartTime),
	GM_MEMBERS(m_iEndIntermissionButtonHit),
	GM_MEMBERS(m_tmNextPeriodicThink),
	GM_MEMBERS(m_bGameStarted),
	GM_MEMBERS(m_bInCareerGame),
	GM_MEMBERS(m_fCareerRoundMenuTime),
	GM_MEMBERS(m_iCareerMatchWins),
	GM_MEMBERS(m_iRoundWinDifference),
	GM_MEMBERS(m_fCareerMatchMenuTime),
	GM_MEMBERS(m_bSkipSpawn),
	GM_MEMBERS(m_bSkipShowMenu),
	GM_MEMBERS(m_bNeededPlayers),
	GM_MEMBERS(m_flEscapeRatio),
	GM_MEMBERS(m_flTimeLimit),
	GM_MEMBERS(m_flGameStartTime),
	GM_MEMBERS(m_bTeamBalanced),
};

member_t memberlist_base[] = {
	BASE_MEMBERS(currentammo),
	BASE_MEMBERS(maxammo_buckshot),
	BASE_MEMBERS(ammo_buckshot),
	BASE_MEMBERS(maxammo_9mm),
	BASE_MEMBERS(ammo_9mm),
	BASE_MEMBERS(maxammo_556nato),
	BASE_MEMBERS(ammo_556nato),
	BASE_MEMBERS(maxammo_556natobox),
	BASE_MEMBERS(ammo_556natobox),
	BASE_MEMBERS(maxammo_762nato),
	BASE_MEMBERS(ammo_762nato),
	BASE_MEMBERS(maxammo_45acp),
	BASE_MEMBERS(ammo_45acp),
	BASE_MEMBERS(maxammo_50ae),
	BASE_MEMBERS(ammo_50ae),
	BASE_MEMBERS(maxammo_338mag),
	BASE_MEMBERS(ammo_338mag),
	BASE_MEMBERS(maxammo_57mm),
	BASE_MEMBERS(ammo_57mm),
	BASE_MEMBERS(maxammo_357sig),
	BASE_MEMBERS(ammo_357sig),
	BASE_MEMBERS(m_flStartThrow),
	BASE_MEMBERS(m_flReleaseThrow),
	BASE_MEMBERS(m_iSwing),
	BASE_MEMBERS(has_disconnected),
};

member_t memberlist_animating[] = {
	ANIM_MEMBERS(m_flFrameRate),
	ANIM_MEMBERS(m_flGroundSpeed),
	ANIM_MEMBERS(m_flLastEventCheck),
	ANIM_MEMBERS(m_fSequenceFinished),
	ANIM_MEMBERS(m_fSequenceLoops),
};

member_t memberlist_basemonster[] = {
	MONST_MEMBERS(m_Activity),
	MONST_MEMBERS(m_IdealActivity),
	MONST_MEMBERS(m_LastHitGroup),
	MONST_MEMBERS(m_bitsDamageType),
	MONST_MEMBERS(m_rgbTimeBasedDamage),
	MONST_MEMBERS(m_MonsterState),
	MONST_MEMBERS(m_IdealMonsterState),
	MONST_MEMBERS(m_afConditions),
	MONST_MEMBERS(m_afMemory),
	MONST_MEMBERS(m_flNextAttack),
	MONST_MEMBERS(m_hEnemy),
	MONST_MEMBERS(m_hTargetEnt),
	MONST_MEMBERS(m_flFieldOfView),
	MONST_MEMBERS(m_bloodColor),
	MONST_MEMBERS(m_HackedGunPos),
	MONST_MEMBERS(m_vecEnemyLKP),
};

member_t memberlist_player[] = {
	PL_MEMBERS(random_seed),
	PL_MEMBERS(m_usPlayerBleed),
	PL_MEMBERS(m_hObserverTarget),
	PL_MEMBERS(m_flNextObserverInput),
	PL_MEMBERS(m_iObserverWeapon),
	PL_MEMBERS(m_iObserverC4State),
	PL_MEMBERS(m_bObserverHasDefuser),
	PL_MEMBERS(m_iObserverLastMode),
	PL_MEMBERS(m_flFlinchTime),
	PL_MEMBERS(m_flAnimTime),
	PL_MEMBERS(m_bHighDamage),
	PL_MEMBERS(m_flVelocityModifier),
	PL_MEMBERS(m_iLastZoom),
	PL_MEMBERS(m_bResumeZoom),
	PL_MEMBERS(m_flEjectBrass),
	PL_MEMBERS(m_iKevlar),
	PL_MEMBERS(m_bNotKilled),
	PL_MEMBERS(m_iTeam),
	PL_MEMBERS(m_iAccount),
	PL_MEMBERS(m_bHasPrimary),
	PL_MEMBERS(m_flDeathThrowTime),
	PL_MEMBERS(m_iThrowDirection),
	PL_MEMBERS(m_flLastTalk),
	PL_MEMBERS(m_bJustConnected),
	PL_MEMBERS(m_bContextHelp),
	PL_MEMBERS(m_iJoiningState),
	PL_MEMBERS(m_pIntroCamera),
	PL_MEMBERS(m_fIntroCamTime),
	PL_MEMBERS(m_fLastMovement),
	PL_MEMBERS(m_bMissionBriefing),
	PL_MEMBERS(m_bTeamChanged),
	PL_MEMBERS(m_iModelName),
	PL_MEMBERS(m_iTeamKills),
	PL_MEMBERS(m_iIgnoreGlobalChat),
	PL_MEMBERS(m_bHasNightVision),
	PL_MEMBERS(m_bNightVisionOn),
	PL_MEMBERS(m_vRecentPath),
	PL_MEMBERS(m_flIdleCheckTime),
	PL_MEMBERS(m_flRadioTime),
	PL_MEMBERS(m_iRadioMessages),
	PL_MEMBERS(m_bIgnoreRadio),
	PL_MEMBERS(m_bHasC4),
	PL_MEMBERS(m_bHasDefuser),
	PL_MEMBERS(m_bKilledByBomb),
	PL_MEMBERS(m_vBlastVector),
	PL_MEMBERS(m_bKilledByGrenade),
	//PL_MEMBERS(m_hintMessageQueue),
	PL_MEMBERS(m_flDisplayHistory),
	PL_MEMBERS(m_iMenu),
	PL_MEMBERS(m_iChaseTarget),
	PL_MEMBERS(m_pChaseTarget),
	PL_MEMBERS(m_fCamSwitch),
	PL_MEMBERS(m_bEscaped),
	PL_MEMBERS(m_bIsVIP),
	PL_MEMBERS(m_tmNextRadarUpdate),
	PL_MEMBERS(m_vLastOrigin),
	PL_MEMBERS(m_iCurrentKickVote),
	PL_MEMBERS(m_flNextVoteTime),
	PL_MEMBERS(m_bJustKilledTeammate),
	PL_MEMBERS(m_iHostagesKilled),
	PL_MEMBERS(m_iMapVote),
	PL_MEMBERS(m_bCanShoot),
	PL_MEMBERS(m_flLastFired),
	PL_MEMBERS(m_flLastAttackedTeammate),
	PL_MEMBERS(m_bHeadshotKilled),
	PL_MEMBERS(m_bPunishedForTK),
	PL_MEMBERS(m_bReceivesNoMoneyNextRound),
	PL_MEMBERS(m_iTimeCheckAllowed),
	PL_MEMBERS(m_bHasChangedName),
	PL_MEMBERS(m_szNewName),
	PL_MEMBERS(m_bIsDefusing),
	PL_MEMBERS(m_tmHandleSignals),
	PL_MEMBERS(m_signals),
	PL_MEMBERS(m_pentCurBombTarget),
	PL_MEMBERS(m_iPlayerSound),
	PL_MEMBERS(m_iTargetVolume),
	PL_MEMBERS(m_iWeaponVolume),
	PL_MEMBERS(m_iExtraSoundTypes),
	PL_MEMBERS(m_iWeaponFlash),
	PL_MEMBERS(m_flStopExtraSoundTime),
	PL_MEMBERS(m_flFlashLightTime),
	PL_MEMBERS(m_iFlashBattery),
	PL_MEMBERS(m_afButtonLast),
	PL_MEMBERS(m_afButtonPressed),
	PL_MEMBERS(m_afButtonReleased),
	PL_MEMBERS(m_pentSndLast),
	PL_MEMBERS(m_flSndRoomtype),
	PL_MEMBERS(m_flSndRange),
	PL_MEMBERS(m_flFallVelocity),
	PL_MEMBERS(m_rgItems),
	PL_MEMBERS(m_fNewAmmo),
	PL_MEMBERS(m_afPhysicsFlags),
	PL_MEMBERS(m_fNextSuicideTime),
	PL_MEMBERS(m_flTimeStepSound),
	PL_MEMBERS(m_flTimeWeaponIdle),
	PL_MEMBERS(m_flSwimTime),
	PL_MEMBERS(m_flDuckTime),
	PL_MEMBERS(m_flWallJumpTime),
	PL_MEMBERS(m_flSuitUpdate),
	PL_MEMBERS(m_rgSuitPlayList),
	PL_MEMBERS(m_iSuitPlayNext),
	PL_MEMBERS(m_rgiSuitNoRepeat),
	PL_MEMBERS(m_rgflSuitNoRepeatTime),
	PL_MEMBERS(m_lastDamageAmount),
	PL_MEMBERS(m_tbdPrev),
	PL_MEMBERS(m_flgeigerRange),
	PL_MEMBERS(m_flgeigerDelay),
	PL_MEMBERS(m_igeigerRangePrev),
	PL_MEMBERS(m_iStepLeft),
	PL_MEMBERS(m_szTextureName),
	PL_MEMBERS(m_chTextureType),
	PL_MEMBERS(m_idrowndmg),
	PL_MEMBERS(m_idrownrestored),
	PL_MEMBERS(m_bitsHUDDamage),
	PL_MEMBERS(m_fInitHUD),
	PL_MEMBERS(m_fGameHUDInitialized),
	PL_MEMBERS(m_iTrain),
	PL_MEMBERS(m_fWeapon),
	PL_MEMBERS(m_pTank),
	PL_MEMBERS(m_fDeadTime),
	PL_MEMBERS(m_fNoPlayerSound),
	PL_MEMBERS(m_fLongJump),
	PL_MEMBERS(m_tSneaking),
	PL_MEMBERS(m_iUpdateTime),
	PL_MEMBERS(m_iClientHealth),
	PL_MEMBERS(m_iClientBattery),
	PL_MEMBERS(m_iHideHUD),
	PL_MEMBERS(m_iClientHideHUD),
	PL_MEMBERS(m_iFOV),
	PL_MEMBERS(m_iClientFOV),
	PL_MEMBERS(m_iNumSpawns),
	PL_MEMBERS(m_pObserver),
	PL_MEMBERS(m_rgpPlayerItems),
	PL_MEMBERS(m_pActiveItem),
	PL_MEMBERS(m_pClientActiveItem),
	PL_MEMBERS(m_pLastItem),
	PL_MEMBERS(m_rgAmmo),
	PL_MEMBERS(m_rgAmmoLast),
	PL_MEMBERS(m_vecAutoAim),
	PL_MEMBERS(m_fOnTarget),
	PL_MEMBERS(m_iDeaths),
	PL_MEMBERS(m_izSBarState),
	PL_MEMBERS(m_flNextSBarUpdateTime),
	PL_MEMBERS(m_flStatusBarDisappearDelay),
	PL_MEMBERS(m_SbarString0),
	PL_MEMBERS(m_lastx),
	PL_MEMBERS(m_lasty),
	PL_MEMBERS(m_nCustomSprayFrames),
	PL_MEMBERS(m_flNextDecalTime),
	PL_MEMBERS(m_szTeamName),
	PL_MEMBERS(m_modelIndexPlayer),
	PL_MEMBERS(m_szAnimExtention),
	PL_MEMBERS(m_iGaitsequence),
	PL_MEMBERS(m_flGaitframe),
	PL_MEMBERS(m_flGaityaw),
	PL_MEMBERS(m_prevgaitorigin),
	PL_MEMBERS(m_flPitch),
	PL_MEMBERS(m_flYaw),
	PL_MEMBERS(m_flGaitMovement),
	PL_MEMBERS(m_iAutoWepSwitch),
	PL_MEMBERS(m_bVGUIMenus),
	PL_MEMBERS(m_bShowHints),
	PL_MEMBERS(m_bShieldDrawn),
	PL_MEMBERS(m_bOwnsShield),
	PL_MEMBERS(m_bWasFollowing),
	PL_MEMBERS(m_flNextFollowTime),
	PL_MEMBERS(m_flYawModifier),
	PL_MEMBERS(m_blindUntilTime),
	PL_MEMBERS(m_blindStartTime),
	PL_MEMBERS(m_blindHoldTime),
	PL_MEMBERS(m_blindFadeTime),
	PL_MEMBERS(m_blindAlpha),
	PL_MEMBERS(m_allowAutoFollowTime),
	PL_MEMBERS(m_autoBuyString),
	PL_MEMBERS(m_rebuyString),
	PL_MEMBERS(m_rebuyStruct),
	PL_MEMBERS(m_bIsInRebuy),
	PL_MEMBERS(m_flLastUpdateTime),
	PL_MEMBERS(m_lastLocation),
	PL_MEMBERS(m_progressStart),
	PL_MEMBERS(m_progressEnd),
	PL_MEMBERS(m_bObserverAutoDirector),
	PL_MEMBERS(m_canSwitchObserverModes),
	PL_MEMBERS(m_heartBeatTime),
	PL_MEMBERS(m_intenseTimestamp),
	PL_MEMBERS(m_silentTimestamp),
	PL_MEMBERS(m_musicState),
	PL_MEMBERS(m_flLastCommandTime),
	PL_MEMBERS(m_iLastAccount),
	PL_MEMBERS(m_iLastClientHealth),
	PL_MEMBERS(m_tmNextAccountHealthUpdate),
};

member_t memberlist_entvars[] = {
	EVAR_MEMBERS(classname),
	EVAR_MEMBERS(globalname),
	EVAR_MEMBERS(origin),
	EVAR_MEMBERS(oldorigin),
	EVAR_MEMBERS(velocity),
	EVAR_MEMBERS(basevelocity),
	EVAR_MEMBERS(clbasevelocity),
	EVAR_MEMBERS(movedir),
	EVAR_MEMBERS(angles),
	EVAR_MEMBERS(avelocity),
	EVAR_MEMBERS(punchangle),
	EVAR_MEMBERS(v_angle),
	EVAR_MEMBERS(endpos),
	EVAR_MEMBERS(startpos),
	EVAR_MEMBERS(impacttime),
	EVAR_MEMBERS(starttime),
	EVAR_MEMBERS(fixangle),
	EVAR_MEMBERS(idealpitch),
	EVAR_MEMBERS(pitch_speed),
	EVAR_MEMBERS(ideal_yaw),
	EVAR_MEMBERS(yaw_speed),
	EVAR_MEMBERS(modelindex),
	EVAR_MEMBERS(model),
	EVAR_MEMBERS(viewmodel),
	EVAR_MEMBERS(weaponmodel),
	EVAR_MEMBERS(absmin),
	EVAR_MEMBERS(absmax),
	EVAR_MEMBERS(mins),
	EVAR_MEMBERS(maxs),
	EVAR_MEMBERS(size),
	EVAR_MEMBERS(ltime),
	EVAR_MEMBERS(nextthink),
	EVAR_MEMBERS(movetype),
	EVAR_MEMBERS(solid),
	EVAR_MEMBERS(skin),
	EVAR_MEMBERS(body),
	EVAR_MEMBERS(effects),
	EVAR_MEMBERS(gravity),
	EVAR_MEMBERS(friction),
	EVAR_MEMBERS(light_level),
	EVAR_MEMBERS(sequence),
	EVAR_MEMBERS(gaitsequence),
	EVAR_MEMBERS(frame),
	EVAR_MEMBERS(animtime),
	EVAR_MEMBERS(framerate),
	EVAR_MEMBERS(controller),
	EVAR_MEMBERS(blending),
	EVAR_MEMBERS(scale),
	EVAR_MEMBERS(rendermode),
	EVAR_MEMBERS(renderamt),
	EVAR_MEMBERS(rendercolor),
	EVAR_MEMBERS(renderfx),
	EVAR_MEMBERS(health),
	EVAR_MEMBERS(frags),
	EVAR_MEMBERS(weapons),
	EVAR_MEMBERS(takedamage),
	EVAR_MEMBERS(deadflag),
	EVAR_MEMBERS(view_ofs),
	EVAR_MEMBERS(button),
	EVAR_MEMBERS(impulse),
	EVAR_MEMBERS(chain),
	EVAR_MEMBERS(dmg_inflictor),
	EVAR_MEMBERS(enemy),
	EVAR_MEMBERS(aiment),
	EVAR_MEMBERS(owner),
	EVAR_MEMBERS(groundentity),
	EVAR_MEMBERS(spawnflags),
	EVAR_MEMBERS(flags),
	EVAR_MEMBERS(colormap),
	EVAR_MEMBERS(team),
	EVAR_MEMBERS(max_health),
	EVAR_MEMBERS(teleport_time),
	EVAR_MEMBERS(armortype),
	EVAR_MEMBERS(armorvalue),
	EVAR_MEMBERS(waterlevel),
	EVAR_MEMBERS(watertype),
	EVAR_MEMBERS(target),
	EVAR_MEMBERS(targetname),
	EVAR_MEMBERS(netname),
	EVAR_MEMBERS(message),
	EVAR_MEMBERS(dmg_take),
	EVAR_MEMBERS(dmg_save),
	EVAR_MEMBERS(dmg),
	EVAR_MEMBERS(dmgtime),
	EVAR_MEMBERS(noise),
	EVAR_MEMBERS(noise1),
	EVAR_MEMBERS(noise2),
	EVAR_MEMBERS(noise3),
	EVAR_MEMBERS(speed),
	EVAR_MEMBERS(air_finished),
	EVAR_MEMBERS(pain_finished),
	EVAR_MEMBERS(radsuit_finished),
	EVAR_MEMBERS(pContainingEntity),
	EVAR_MEMBERS(playerclass),
	EVAR_MEMBERS(maxspeed),
	EVAR_MEMBERS(fov),
	EVAR_MEMBERS(weaponanim),
	EVAR_MEMBERS(pushmsec),
	EVAR_MEMBERS(bInDuck),
	EVAR_MEMBERS(flTimeStepSound),
	EVAR_MEMBERS(flSwimTime),
	EVAR_MEMBERS(flDuckTime),
	EVAR_MEMBERS(iStepLeft),
	EVAR_MEMBERS(flFallVelocity),
	EVAR_MEMBERS(gamestate),
	EVAR_MEMBERS(oldbuttons),
	EVAR_MEMBERS(groupinfo),
	EVAR_MEMBERS(iuser1),
	EVAR_MEMBERS(iuser2),
	EVAR_MEMBERS(iuser3),
	EVAR_MEMBERS(iuser4),
	EVAR_MEMBERS(fuser1),
	EVAR_MEMBERS(fuser2),
	EVAR_MEMBERS(fuser3),
	EVAR_MEMBERS(fuser4),
	EVAR_MEMBERS(vuser1),
	EVAR_MEMBERS(vuser2),
	EVAR_MEMBERS(vuser3),
	EVAR_MEMBERS(vuser4),
	EVAR_MEMBERS(euser1),
	EVAR_MEMBERS(euser2),
	EVAR_MEMBERS(euser3),
	EVAR_MEMBERS(euser4),
};

member_t memberlist_playermove[] = {
	PMOVE_MEMBERS(player_index),
	PMOVE_MEMBERS(server),
	PMOVE_MEMBERS(multiplayer),
	PMOVE_MEMBERS(time),
	PMOVE_MEMBERS(frametime),
	PMOVE_MEMBERS(forward),
	PMOVE_MEMBERS(right),
	PMOVE_MEMBERS(up),
	PMOVE_MEMBERS(origin),
	PMOVE_MEMBERS(angles),
	PMOVE_MEMBERS(oldangles),
	PMOVE_MEMBERS(velocity),
	PMOVE_MEMBERS(movedir),
	PMOVE_MEMBERS(basevelocity),
	PMOVE_MEMBERS(view_ofs),
	PMOVE_MEMBERS(flDuckTime),
	PMOVE_MEMBERS(bInDuck),
	PMOVE_MEMBERS(flTimeStepSound),
	PMOVE_MEMBERS(iStepLeft),
	PMOVE_MEMBERS(flFallVelocity),
	PMOVE_MEMBERS(punchangle),
	PMOVE_MEMBERS(flSwimTime),
	PMOVE_MEMBERS(flNextPrimaryAttack),
	PMOVE_MEMBERS(effects),
	PMOVE_MEMBERS(flags),
	PMOVE_MEMBERS(usehull),
	PMOVE_MEMBERS(gravity),
	PMOVE_MEMBERS(friction),
	PMOVE_MEMBERS(oldbuttons),
	PMOVE_MEMBERS(waterjumptime),
	PMOVE_MEMBERS(dead),
	PMOVE_MEMBERS(deadflag),
	PMOVE_MEMBERS(spectator),
	PMOVE_MEMBERS(movetype),
	PMOVE_MEMBERS(onground),
	PMOVE_MEMBERS(waterlevel),
	PMOVE_MEMBERS(watertype),
	PMOVE_MEMBERS(oldwaterlevel),
	PMOVE_MEMBERS(sztexturename),
	PMOVE_MEMBERS(chtexturetype),
	PMOVE_MEMBERS(maxspeed),
	PMOVE_MEMBERS(clientmaxspeed),
	PMOVE_MEMBERS(iuser1),
	PMOVE_MEMBERS(iuser2),
	PMOVE_MEMBERS(iuser3),
	PMOVE_MEMBERS(iuser4),
	PMOVE_MEMBERS(fuser1),
	PMOVE_MEMBERS(fuser2),
	PMOVE_MEMBERS(fuser3),
	PMOVE_MEMBERS(fuser4),
	PMOVE_MEMBERS(vuser1),
	PMOVE_MEMBERS(vuser2),
	PMOVE_MEMBERS(vuser3),
	PMOVE_MEMBERS(vuser4),
	PMOVE_MEMBERS(numphysent),
	PMOVE_MEMBERS(cmd),
	PMOVE_MEMBERS(numtouch),
	PMOVE_MEMBERS(physinfo),
	PMOVE_MEMBERS(player_mins),
	PMOVE_MEMBERS(player_maxs),

	// TODO: Impl me!
	//PMOVE_MEMBERS(physents),
	//PMOVE_MEMBERS(nummoveent),
	//PMOVE_MEMBERS(moveents),
	//PMOVE_MEMBERS(numvisent),
	//PMOVE_MEMBERS(visents),
	//PMOVE_MEMBERS(touchindex),
	//PMOVE_MEMBERS(movevars),
};

member_t memberlist_movevars[] = {
	MOVEVAR_MEMBERS(gravity),
	MOVEVAR_MEMBERS(stopspeed),
	MOVEVAR_MEMBERS(maxspeed),
	MOVEVAR_MEMBERS(spectatormaxspeed),
	MOVEVAR_MEMBERS(accelerate),
	MOVEVAR_MEMBERS(airaccelerate),
	MOVEVAR_MEMBERS(wateraccelerate),
	MOVEVAR_MEMBERS(friction),
	MOVEVAR_MEMBERS(edgefriction),
	MOVEVAR_MEMBERS(waterfriction),
	MOVEVAR_MEMBERS(entgravity),
	MOVEVAR_MEMBERS(bounce),
	MOVEVAR_MEMBERS(stepsize),
	MOVEVAR_MEMBERS(maxvelocity),
	MOVEVAR_MEMBERS(zmax),
	MOVEVAR_MEMBERS(waveHeight),
	MOVEVAR_MEMBERS(footsteps),
	MOVEVAR_MEMBERS(skyName),
	MOVEVAR_MEMBERS(rollangle),
	MOVEVAR_MEMBERS(rollspeed),
	MOVEVAR_MEMBERS(skycolor_r),
	MOVEVAR_MEMBERS(skycolor_g),
	MOVEVAR_MEMBERS(skycolor_b),
	MOVEVAR_MEMBERS(skyvec_x),
	MOVEVAR_MEMBERS(skyvec_y),
	MOVEVAR_MEMBERS(skyvec_z),
};

member_t memberlist_usercmd[] = {
	UCMD_MEMBERS(lerp_msec),
	UCMD_MEMBERS(msec),
	UCMD_MEMBERS(viewangles),
	UCMD_MEMBERS(forwardmove),
	UCMD_MEMBERS(sidemove),
	UCMD_MEMBERS(upmove),
	UCMD_MEMBERS(lightlevel),
	UCMD_MEMBERS(buttons),
	UCMD_MEMBERS(impulse),
	UCMD_MEMBERS(weaponselect),
	UCMD_MEMBERS(impact_index),
	UCMD_MEMBERS(impact_position),
};

member_t memberlist_pmtrace[] = {
	PMTRACE_MEMBERS(allsolid),
	PMTRACE_MEMBERS(startsolid),
	PMTRACE_MEMBERS(inopen),
	PMTRACE_MEMBERS(inwater),
	PMTRACE_MEMBERS(fraction),
	PMTRACE_MEMBERS(endpos),
	PMTRACE_MEMBERS(ent),
	PMTRACE_MEMBERS(deltavelocity),
	PMTRACE_MEMBERS(hitgroup),
};

member_t memberlist_netchan[] = {
	NETCHAN_MEMBERS(sock),
	NETCHAN_MEMBERS(remote_address),
	NETCHAN_MEMBERS(player_slot),
	NETCHAN_MEMBERS(last_received),
	NETCHAN_MEMBERS(connect_time),
	NETCHAN_MEMBERS(rate),
	NETCHAN_MEMBERS(cleartime),
	NETCHAN_MEMBERS(incoming_sequence),
	NETCHAN_MEMBERS(incoming_acknowledged),
	NETCHAN_MEMBERS(incoming_reliable_acknowledged),
	NETCHAN_MEMBERS(incoming_reliable_sequence),
	NETCHAN_MEMBERS(outgoing_sequence),
	NETCHAN_MEMBERS(reliable_sequence),
	NETCHAN_MEMBERS(last_reliable_sequence)
};

member_t memberlist_csplayer[] = {
	CSPL_MEMBERS(m_szModel),
	CSPL_MEMBERS(m_bForceShowMenu),
	CSPL_MEMBERS(m_flRespawnPending),
	CSPL_MEMBERS(m_flSpawnProtectionEndTime),
	CSPL_MEMBERS(m_vecOldvAngle),
	CSPL_MEMBERS(m_iWeaponInfiniteAmmo),
	CSPL_MEMBERS(m_iWeaponInfiniteIds),
	CSPL_MEMBERS(m_bCanShootOverride),
	CSPL_MEMBERS(m_bGameForcingRespawn),
	CSPL_MEMBERS(m_bAutoBunnyHopping),
	CSPL_MEMBERS(m_bMegaBunnyJumping),
	CSPL_MEMBERS(m_bPlantC4Anywhere),
	CSPL_MEMBERS(m_bSpawnProtectionEffects),
	CSPL_MEMBERS(m_flJumpHeight),
	CSPL_MEMBERS(m_flLongJumpHeight),
	CSPL_MEMBERS(m_flLongJumpForce),
	CSPL_MEMBERS(m_flDuckSpeedMultiplier),
	CSPL_MEMBERS(m_iNumKilledByUnanswered),
	CSPL_MEMBERS(m_bPlayerDominated),
};

member_t memberlist_baseitem[] = {
	BASEITEM_MEMBERS(m_pPlayer),
	BASEITEM_MEMBERS(m_pNext),
	BASEITEM_MEMBERS(m_iId),
};

member_t memberlist_baseweapon[] = {
	BASEWPN_MEMBERS(iPlayEmptySound),
	BASEWPN_MEMBERS(fFireOnEmpty),
	BASEWPN_MEMBERS(flNextPrimaryAttack),
	BASEWPN_MEMBERS(flNextSecondaryAttack),
	BASEWPN_MEMBERS(flTimeWeaponIdle),		// FIXME: conflict with CBasePlayer::m_flTimeWeaponIdle
	BASEWPN_MEMBERS(iPrimaryAmmoType),
	BASEWPN_MEMBERS(iSecondaryAmmoType),
	BASEWPN_MEMBERS(iClip),
	BASEWPN_MEMBERS(iClientClip),
	BASEWPN_MEMBERS(iClientWeaponState),
	BASEWPN_MEMBERS(fInReload),
	BASEWPN_MEMBERS(fInSpecialReload),
	BASEWPN_MEMBERS(iDefaultAmmo),
	BASEWPN_MEMBERS(iShellId),
	BASEWPN_MEMBERS(fMaxSpeed),
	BASEWPN_MEMBERS(bDelayFire),
	BASEWPN_MEMBERS(iDirection),
	BASEWPN_MEMBERS(bSecondarySilencerOn),
	BASEWPN_MEMBERS(flAccuracy),
	BASEWPN_MEMBERS(flLastFire),
	BASEWPN_MEMBERS(iShotsFired),
	//BASEWPN_MEMBERS(vVecAiming),
	//BASEWPN_MEMBERS(model_name),
	BASEWPN_MEMBERS(flGlock18Shoot),
	BASEWPN_MEMBERS(iGlock18ShotsFired),
	BASEWPN_MEMBERS(flFamasShoot),
	BASEWPN_MEMBERS(iFamasShotsFired),
	BASEWPN_MEMBERS(fBurstSpread),
	BASEWPN_MEMBERS(iWeaponState),
	BASEWPN_MEMBERS(flNextReload),
	BASEWPN_MEMBERS(flDecreaseShotsFired),
	BASEWPN_MEMBERS(usFireGlock18),
	BASEWPN_MEMBERS(usFireFamas),
	BASEWPN_MEMBERS(flPrevPrimaryAttack),
	BASEWPN_MEMBERS(flLastFireTime),
};

member_t memberlist_weaponbox[] = {
	WPNBOX_MEMBERS(rgpPlayerItems),
	WPNBOX_MEMBERS(rgiszAmmo),
	WPNBOX_MEMBERS(rgAmmo),
	WPNBOX_MEMBERS(cAmmoTypes),
	WPNBOX_MEMBERS(bIsBomb),
};

member_t memberlist_armoury[] = {
	ARMOURY_MEMBERS(iItem),
	ARMOURY_MEMBERS(iCount),
	ARMOURY_MEMBERS(iInitialCount),
	ARMOURY_MEMBERS(bAlreadyCounted),
};

member_t memberlist_grenade[] = {
	GRENADE_MEMBERS(bStartDefuse),
	GRENADE_MEMBERS(bIsC4),
	GRENADE_MEMBERS(pBombDefuser),
	GRENADE_MEMBERS(flDefuseCountDown),
	GRENADE_MEMBERS(flC4Blow),
	GRENADE_MEMBERS(flNextFreqInterval),
	GRENADE_MEMBERS(flNextBeep),
	GRENADE_MEMBERS(flNextFreq),
	GRENADE_MEMBERS(sBeepName),
	GRENADE_MEMBERS(fAttenu),
	GRENADE_MEMBERS(flNextBlink),
	GRENADE_MEMBERS(fNextDefuse),
	GRENADE_MEMBERS(bJustBlew),
	GRENADE_MEMBERS(iTeam),
	GRENADE_MEMBERS(iCurWave),
	GRENADE_MEMBERS(pentCurBombTarget),
	GRENADE_MEMBERS(SGSmoke),
	GRENADE_MEMBERS(angle),
	GRENADE_MEMBERS(usEvent),
	GRENADE_MEMBERS(bLightSmoke),
	GRENADE_MEMBERS(bDetonated),
	GRENADE_MEMBERS(vSmokeDetonate),
	GRENADE_MEMBERS(iBounceCount),
	GRENADE_MEMBERS(fRegisteredSound),
};

member_t memberlist_p228[] = {
	P228_MEMBERS(iShell),
	P228_MEMBERS(usFire),
};

member_t memberlist_scout[] = {
	SCOUT_MEMBERS(iShell),
	SCOUT_MEMBERS(usFire),
};

member_t memberlist_hegrenade[] = {
	HEGREN_MEMBERS(usCreate),
};

member_t memberlist_xm1014[] = {
	XM1014_MEMBERS(iShell),
	XM1014_MEMBERS(flPumpTime),
	XM1014_MEMBERS(usFire),
};

member_t memberlist_c4[] = {
	C4_MEMBERS(bStartedArming),
	C4_MEMBERS(bBombPlacedAnimation),
	C4_MEMBERS(fArmedTime),
	C4_MEMBERS(bHasShield),
};

member_t memberlist_mac10[] = {
	MAC10_MEMBERS(iShell),
	MAC10_MEMBERS(iShellOn),
	MAC10_MEMBERS(usFire),
};

member_t memberlist_aug[] = {
	AUG_MEMBERS(iShell),
	AUG_MEMBERS(iShellOn),
	AUG_MEMBERS(usFire),
};

member_t memberlist_smokegrenade[] = {
	SMOKEGREN_MEMBERS(usCreate),
};

member_t memberlist_elite[] = {
	ELITE_MEMBERS(iShell),
	ELITE_MEMBERS(usFire_LEFT),
	ELITE_MEMBERS(usFire_RIGHT),
};

member_t memberlist_fiveseven[] = {
	FIVESEVEN_MEMBERS(iShell),
	FIVESEVEN_MEMBERS(usFire),
};

member_t memberlist_ump45[] = {
	UMP45_MEMBERS(iShell),
	UMP45_MEMBERS(iShellOn),
	UMP45_MEMBERS(usFire),
};

member_t memberlist_sg550[] = {
	SG550_MEMBERS(iShell),
	SG550_MEMBERS(usFire),
};

member_t memberlist_galil[] = {
	GALIL_MEMBERS(iShell),
	GALIL_MEMBERS(iShellOn),
	GALIL_MEMBERS(usFire),
};

member_t memberlist_famas[] = {
	FAMAS_MEMBERS(iShell),
	FAMAS_MEMBERS(iShellOn),
	FAMAS_MEMBERS(flBaseDamageBurst),
};

member_t memberlist_usp[] = {
	USP_MEMBERS(iShell),
	USP_MEMBERS(usFire),
	USP_MEMBERS(flBaseDamageSil),
};

member_t memberlist_glock18[] = {
	GLOCK18_MEMBERS(iShell),
	GLOCK18_MEMBERS(bBurstFire),
};

member_t memberlist_awp[] = {
	AWP_MEMBERS(iShell),
	AWP_MEMBERS(usFire),
};

member_t memberlist_mp5n[] = {
	MP5N_MEMBERS(iShell),
	MP5N_MEMBERS(iShellOn),
	MP5N_MEMBERS(usFire),
};

member_t memberlist_m249[] = {
	M249_MEMBERS(iShell),
	M249_MEMBERS(iShellOn),
	M249_MEMBERS(usFire),
};

member_t memberlist_m3[] = {
	M3_MEMBERS(iShell),
	M3_MEMBERS(flPumpTime),
	M3_MEMBERS(usFire),
};

member_t memberlist_m4a1[] = {
	M4A1_MEMBERS(iShell),
	M4A1_MEMBERS(iShellOn),
	M4A1_MEMBERS(usFire),
	M4A1_MEMBERS(flBaseDamageSil),
};

member_t memberlist_tmp[] = {
	TMP_MEMBERS(iShell),
	TMP_MEMBERS(iShellOn),
	TMP_MEMBERS(usFire),
};

member_t memberlist_g3sg1[] = {
	G3SG1_MEMBERS(iShell),
	G3SG1_MEMBERS(usFire),
};

member_t memberlist_deagle[] = {
	DEAGLE_MEMBERS(iShell),
	DEAGLE_MEMBERS(usFire),
};

member_t memberlist_sg552[] = {
	SG552_MEMBERS(iShell),
	SG552_MEMBERS(iShellOn),
	SG552_MEMBERS(usFire),
};

member_t memberlist_ak47[] = {
	AK47_MEMBERS(iShell),
	AK47_MEMBERS(iShellOn),
	AK47_MEMBERS(usFire),
};

member_t memberlist_knife[] = {
	KNIFE_MEMBERS(trHit),
	KNIFE_MEMBERS(usKnife),
	KNIFE_MEMBERS(flStabBaseDamage),
	KNIFE_MEMBERS(flSwingBaseDamage),
	KNIFE_MEMBERS(flSwingBaseDamage_Fast),
	KNIFE_MEMBERS(flStabDistance),
	KNIFE_MEMBERS(flSwingDistance),
	KNIFE_MEMBERS(flBackStabMultiplier),
};

member_t memberlist_p90[] = {
	P90_MEMBERS(iShell),
	P90_MEMBERS(iShellOn),
	P90_MEMBERS(usFire),
};

member_t memberlist_shield[] = {
	SHIELD_MEMBERS(hEntToIgnoreTouchesFrom),
	SHIELD_MEMBERS(flTimeToIgnoreTouches),
};

member_t memberlist_rebuystruct[] = {
	REBUYSTRUCT_MEMBERS(m_primaryWeapon),
	REBUYSTRUCT_MEMBERS(m_primaryAmmo),
	REBUYSTRUCT_MEMBERS(m_secondaryWeapon),
	REBUYSTRUCT_MEMBERS(m_secondaryAmmo),
	REBUYSTRUCT_MEMBERS(m_heGrenade),
	REBUYSTRUCT_MEMBERS(m_flashbang),
	REBUYSTRUCT_MEMBERS(m_smokeGrenade),
	REBUYSTRUCT_MEMBERS(m_defuser),
	REBUYSTRUCT_MEMBERS(m_nightVision),
	REBUYSTRUCT_MEMBERS(m_armor),
};

member_t memberlist_mapinfo[] = {
	MAPINFO_MEMBERS(iBuyingStatus),
	MAPINFO_MEMBERS(flBombRadius),
};

member_t memberlist_csplayerweapon[] = {
	CSPLWPN_MEMBERS(iStateSecondaryAttack),
	CSPLWPN_MEMBERS(flBaseDamage),
};

member_t memberlist_gib[] = {
	GIB_MEMBERS(bloodColor),
	GIB_MEMBERS(cBloodDecals),
	GIB_MEMBERS(material),
	GIB_MEMBERS(lifeTime),
};

member_t memberlist_netadr[] = {
	NETADR_MEMBERS(type),
	NETADR_MEMBERS(ip),
	NETADR_MEMBERS(port)
};

member_t memberlist_csentity[] = {
	CSENT_MEMBERS(m_ucDmgPenetrationLevel),
	CSENT_MEMBERS(m_pevLastInflictor),
};

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif // #ifdef __GNUC__

memberlist_t memberlist;

member_t *memberlist_t::operator[](size_t members) const
{
	#define CASE(h)	case mt_##h: if (likely(index < arraysize(memberlist_##h))) return &memberlist_##h[index]; else break;

	const auto table = members_tables_e(members / MAX_REGION_RANGE);
	const auto index = members & (MAX_REGION_RANGE - 1);

	switch (table) {
		CASE(gamerules)
		CASE(base)
		CASE(animating)
		CASE(basemonster)
		CASE(player)
		CASE(entvars)
		CASE(playermove)
		CASE(movevars)
		CASE(usercmd)
		CASE(pmtrace)
		CASE(netchan)
		CASE(csplayer)
		CASE(baseitem)
		CASE(baseweapon)
		CASE(weaponbox)
		CASE(armoury)
		CASE(grenade)
		CASE(p228)
		CASE(scout)
		CASE(hegrenade)
		CASE(xm1014)
		CASE(c4)
		CASE(mac10)
		CASE(aug)
		CASE(smokegrenade)
		CASE(elite)
		CASE(fiveseven)
		CASE(ump45)
		CASE(sg550)
		CASE(galil)
		CASE(famas)
		CASE(usp)
		CASE(glock18)
		CASE(awp)
		CASE(mp5n)
		CASE(m249)
		CASE(m3)
		CASE(m4a1)
		CASE(tmp)
		CASE(g3sg1)
		CASE(deagle)
		CASE(sg552)
		CASE(ak47)
		CASE(knife)
		CASE(p90)
		CASE(shield)
		CASE(rebuystruct)
		CASE(mapinfo)
		CASE(csplayerweapon)
		CASE(gib)
		CASE(netadr)
		CASE(csentity)
	}

	#undef CASE
	return nullptr;
}
