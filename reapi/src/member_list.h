#pragma once

#define BEGIN_MEMBER_REGION(x)			(MAX_REGION_RANGE * memberlist_t::members_tables_e::ht_##x)

// member types
enum MType
{
	MEMBER_FLOAT = 0,		// Any floating point value
	MEMBER_DOUBLE,			// double value
	MEMBER_ENTITY,			// An entity offset (EOFFSET)
	MEMBER_CLASSPTR,		// CBaseEntity *
	MEMBER_EHANDLE,			// Entity handle
	MEMBER_EVARS,			// EVARS *
	MEMBER_EDICT,			// edict_t *, or edict_t *  (same thing)
	MEMBER_VECTOR,			// Any vector
	MEMBER_CHAR_POINTER,		// char *
	MEMBER_CHAR_ARRAY,		// char []
	MEMBER_INTEGER,			// Any integer or enum
	MEMBER_SHORT,			// 2 byte integer
	MEMBER_BYTE,			// a byte
	MEMBER_BOOL,			// a bool
	MEMBER_SIGNALS,			// class CUnifiedSignals
	MEBMER_REBUYSTRUCT,		// struct RebuyStruct
};

struct member_t
{
	uint16 size;
	uint16 max_size;
	uint32 offset;
	MType type;
};

struct memberlist_t
{
	member_t *operator[](size_t members) const;

	enum members_tables_e
	{
		ht_gamerules,
		ht_base,
		ht_animating,
		ht_player
	};
};

extern memberlist_t memberlist;

// CSGameRules
enum CSGameRules_Members
{
	m_bFreezePeriod = BEGIN_MEMBER_REGION(gamerules),
	m_bBombDropped,

	// m_VoiceGameMgr -> CVoiceGameMgr
	m_msgPlayerVoiceMask,
	m_msgRequestState,
	m_nMaxPlayers,
	m_UpdateInterval,

	m_fTeamCount,				// m_flRestartRoundTime, the global time when the round is supposed to end, if this is not 0
	m_flCheckWinConditions,
	m_fRoundCount,
	m_iRoundTime,				// (From mp_roundtime) - How many seconds long this round is.
	m_iRoundTimeSecs,
	m_iIntroRoundTime,			// (From mp_freezetime) - How many seconds long the intro round (when players are frozen) is.
	m_fIntroRoundCount,			// The global time when the intro round ends and the real one starts
						// wrote the original "m_flRoundTime" comment for this variable).
	m_iAccountTerrorist,
	m_iAccountCT,
	m_iNumTerrorist,			// The number of terrorists on the team (this is generated at the end of a round)
	m_iNumCT,				// The number of CTs on the team (this is generated at the end of a round)
	m_iNumSpawnableTerrorist,
	m_iNumSpawnableCT,
	m_iSpawnPointCount_Terrorist,		// Number of Terrorist spawn points
	m_iSpawnPointCount_CT,			// Number of CT spawn points
	m_iHostagesRescued,
	m_iHostagesTouched,
	m_iRoundWinStatus,			// 1 == CT's won last round, 2 == Terrorists did, 3 == Draw, no winner
	m_iNumCTWins,
	m_iNumTerroristWins,
	m_bTargetBombed,			// whether or not the bomb has been bombed
	m_bBombDefused,				// whether or not the bomb has been defused
	m_bMapHasBombTarget,
	m_bMapHasBombZone,
	m_bMapHasBuyZone,
	m_bMapHasRescueZone,
	m_bMapHasEscapeZone,
	m_iMapHasVIPSafetyZone,			// 0 = uninitialized,   1 = has VIP safety zone,   2 = DOES not have VIP safetyzone
	m_bMapHasCameras,
	m_iC4Timer,
	m_iC4Guy,				// The current Terrorist who has the C4.
	m_iLoserBonus,				// the amount of money the losing team gets. This scales up as they lose more rounds in a row
	m_iNumConsecutiveCTLoses,		// the number of rounds the CTs have lost in a row.
	m_iNumConsecutiveTerroristLoses,	// the number of rounds the Terrorists have lost in a row.
	m_fMaxIdlePeriod,			// For the idle kick functionality. This is tha max amount of time that the player has to be idle before being kicked
	m_iLimitTeams,
	m_bLevelInitialized,
	m_bRoundTerminating,
	m_bCompleteReset,			// Set to TRUE to have the scores reset next time round restarts
	m_flRequiredEscapeRatio,
	m_iNumEscapers,
	m_iHaveEscaped,
	m_bCTCantBuy,
	m_bTCantBuy,				// Who can and can't buy.
	m_flBombRadius,
	m_iConsecutiveVIP,
	m_iTotalGunCount,
	m_iTotalGrenadeCount,
	m_iTotalArmourCount,
	m_iUnBalancedRounds,			// keeps track of the # of consecutive rounds that have gone by where one team outnumbers the other team by more than 2
	m_iNumEscapeRounds,			// keeps track of the # of consecutive rounds of escape played.. Teams will be swapped after 8 rounds
	m_iMapVotes,
	m_iLastPick,
	m_iMaxMapTime,
	m_iMaxRounds,
	m_iTotalRoundsPlayed,
	m_iMaxRoundsWon,
	m_iStoredSpectValue,
	m_flForceCameraValue,
	m_flForceChaseCamValue,
	m_flFadeToBlackValue,
	m_pVIP,
	VIPQueue,
	m_flIntermissionEndTime,
	m_flIntermissionStartTime,
	m_iEndIntermissionButtonHit,
	m_tmNextPeriodicThink,
	m_bFirstConnected,
	m_bInCareerGame,
	m_fCareerRoundMenuTime,
	m_iCareerMatchWins,
	m_iRoundWinDifference,
	m_fCareerMatchMenuTime,
	m_bSkipSpawn
};

// CBasePlayer
enum CBaseEntity_Members
{
	currentammo = BEGIN_MEMBER_REGION(base),
	maxammo_buckshot,
	ammo_buckshot,
	maxammo_9mm,
	ammo_9mm,
	maxammo_556nato,
	ammo_556nato,
	maxammo_556natobox,
	ammo_556natobox,
	maxammo_762nato,
	ammo_762nato,
	maxammo_45acp,
	ammo_45acp,
	maxammo_50ae,
	ammo_50ae,
	maxammo_338mag,
	ammo_338mag,
	maxammo_57mm,
	ammo_57mm,
	maxammo_357sig,
	ammo_357sig,
	m_flStartThrow,
	m_flReleaseThrow,
	m_iSwing,
	has_disconnected,
};

// CBaseAnimating
enum CBaseAnimating_Members
{
	m_flFrameRate = BEGIN_MEMBER_REGION(animating),
	m_flGroundSpeed,
	m_flLastEventCheck,
	m_fSequenceFinished,
	m_fSequenceLoops,
};

// CBasePlayer
enum CBasePlayer_Members
{
	random_seed = BEGIN_MEMBER_REGION(player),
	m_usPlayerBleed,
	m_hObserverTarget,
	m_flNextObserverInput,
	m_iObserverWeapon,
	m_iObserverC4State,
	m_bObserverHasDefuser,
	m_iObserverLastMode,
	m_flFlinchTime,
	m_flAnimTime,
	m_bHighDamage,
	m_flVelocityModifier,
	m_iLastZoom,
	m_bResumeZoom,
	m_flEjectBrass,
	m_iKevlar,
	m_bNotKilled,
	m_iTeam,
	m_iAccount,
	m_bHasPrimary,
	m_flDeathThrowTime,
	m_iThrowDirection,
	m_flLastTalk,
	m_bJustConnected,
	m_bContextHelp,
	m_iJoiningState,
	m_pIntroCamera,
	m_fIntroCamTime,
	m_fLastMovement,
	m_bMissionBriefing,
	m_bTeamChanged,
	m_iModelName,
	m_iTeamKills,
	m_iIgnoreGlobalChat,
	m_bHasNightVision,
	m_bNightVisionOn,
	m_vRecentPath,
	m_flIdleCheckTime,
	m_flRadioTime,
	m_iRadioMessages,
	m_bIgnoreRadio,
	m_bHasC4,
	m_bHasDefuser,
	m_bKilledByBomb,
	m_vBlastVector,
	m_bKilledByGrenade,
	//m_hintMessageQueue,
	m_flDisplayHistory,
	m_iMenu,
	m_iChaseTarget,
	m_pChaseTarget,
	m_fCamSwitch,
	m_bEscaped,
	m_bIsVIP,
	m_tmNextRadarUpdate,
	m_vLastOrigin,
	m_iCurrentKickVote,
	m_flNextVoteTime,
	m_bJustKilledTeammate,
	m_iHostagesKilled,
	m_iMapVote,
	m_bCanShoot,
	m_flLastFired,
	m_flLastAttackedTeammate,
	m_bHeadshotKilled,
	m_bPunishedForTK,
	m_bReceivesNoMoneyNextRound,
	m_iTimeCheckAllowed,
	m_bHasChangedName,
	m_szNewName,
	m_bIsDefusing,
	m_tmHandleSignals,
	m_signals,
	m_pentCurBombTarget,
	m_iPlayerSound,
	m_iTargetVolume,
	m_iWeaponVolume,
	m_iExtraSoundTypes,
	m_iWeaponFlash,
	m_flStopExtraSoundTime,
	m_flFlashLightTime,
	m_iFlashBattery,
	m_afButtonLast,
	m_afButtonPressed,
	m_afButtonReleased,
	m_pentSndLast,
	m_flSndRoomtype,
	m_flSndRange,
	m_flFallVelocity,
	m_rgItems,
	m_fNewAmmo,
	m_afPhysicsFlags,
	m_fNextSuicideTime,
	m_flTimeStepSound,
	m_flTimeWeaponIdle,
	m_flSwimTime,
	m_flDuckTime,
	m_flWallJumpTime,
	m_flSuitUpdate,
	m_rgSuitPlayList,
	m_iSuitPlayNext,
	m_rgiSuitNoRepeat,
	m_rgflSuitNoRepeatTime,
	m_lastDamageAmount,
	m_tbdPrev,
	m_flgeigerRange,
	m_flgeigerDelay,
	m_igeigerRangePrev,
	m_iStepLeft,
	m_szTextureName,
	m_chTextureType,
	m_idrowndmg,
	m_idrownrestored,
	m_bitsHUDDamage,
	m_fInitHUD,
	m_fGameHUDInitialized,
	m_iTrain,
	m_fWeapon,
	m_pTank,
	m_fDeadTime,
	m_fNoPlayerSound,
	m_fLongJump,
	m_tSneaking,
	m_iUpdateTime,
	m_iClientHealth,
	m_iClientBattery,
	m_iHideHUD,
	m_iClientHideHUD,
	m_iFOV,
	m_iClientFOV,
	m_iNumSpawns,
	m_pObserver,
	m_rgpPlayerItems,
	m_pActiveItem,
	m_pClientActiveItem,
	m_pLastItem,
	m_rgAmmo,
	m_rgAmmoLast,
	m_vecAutoAim,
	m_fOnTarget,
	m_iDeaths,
	m_izSBarState,
	m_flNextSBarUpdateTime,
	m_flStatusBarDisappearDelay,
	m_SbarString0,
	m_lastx,
	m_lasty,
	m_nCustomSprayFrames,
	m_flNextDecalTime,
	m_szTeamName,
	m_modelIndexPlayer,
	m_szAnimExtention,
	m_iGaitsequence,
	m_flGaitframe,
	m_flGaityaw,
	m_prevgaitorigin,
	m_flPitch,
	m_flYaw,
	m_flGaitMovement,
	m_iAutoWepSwitch,
	m_bVGUIMenus,
	m_bShowHints,
	m_bShieldDrawn,
	m_bOwnsShield,
	m_bWasFollowing,
	m_flNextFollowTime,
	m_flYawModifier,
	m_blindUntilTime,
	m_blindStartTime,
	m_blindHoldTime,
	m_blindFadeTime,
	m_blindAlpha,
	m_allowAutoFollowTime,
	m_autoBuyString,
	m_rebuyString,
	m_rebuyStruct,
	m_bIsInRebuy,
	m_flLastUpdateTime,
	m_lastLocation,
	m_progressStart,
	m_progressEnd,
	m_bObserverAutoDirector,
	m_canSwitchObserverModes,
	m_heartBeatTime,
	m_intenseTimestamp,
	m_silentTimestamp,
	m_musicState,
	m_flLastCommandTime
};
