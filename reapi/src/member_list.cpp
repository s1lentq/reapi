#include "precompiled.h"

struct regmember
{
	template<typename T>
	regmember(T& type, size_t maxsize, size_t offset, enum_membertypes member_type)
	{
		member.size = sizeof(T);
		member.max_size = sizeof(T);
		member.offset = offset;
		member.type = member_type;
	}
	template<typename T>
	regmember(T type[], size_t maxsize, size_t offset, enum_membertypes member_type)
	{
		member.size = sizeof(T);
		member.max_size = maxsize;
		member.offset = offset;
		member.type = member_type;
	}

	regmember(const char *error)
	{
		UTIL_SysError("%s", error);
	}	// to cause a amxx module failure.
	operator member_t() const { return member; }
	member_t member;

	static int current_cell;				// the counter of cells
};

static char mem_dummy[0xffff];
int regmember::current_cell = 1;

#define GM_MEMBERS(mx, mtype) ((!(mx & 1023) ? regmember::current_cell = 1, true : false) || (mx & 1023) == regmember::current_cell++) ? regmember(((CHalfLifeMultiplay *)&mem_dummy)->##mx, sizeof(((CHalfLifeMultiplay *)&mem_dummy)->##mx), offsetof(CHalfLifeMultiplay, mx), mtype) : regmember(#mx " doesn't match hook definition")
#define GM_VOICE_MEMBERS(mx, mtype) ((!(mx & 1023) ? regmember::current_cell = 1, true : false) || (mx & 1023) == regmember::current_cell++) ? regmember(((CVoiceGameMgr *)&mem_dummy)->##mx, sizeof(((CVoiceGameMgr *)&mem_dummy)->##mx), offsetof(CVoiceGameMgr, mx), mtype) : regmember(#mx " doesn't match hook definition")

member_t memberlist_gamerules[] = {	
	GM_MEMBERS(m_bFreezePeriod, MEMBER_INTEGER),
	GM_MEMBERS(m_bBombDropped, MEMBER_INTEGER),
	// m_VoiceGameMgr ->
		GM_VOICE_MEMBERS(m_msgPlayerVoiceMask, MEMBER_INTEGER),
		GM_VOICE_MEMBERS(m_msgRequestState, MEMBER_INTEGER),
		GM_VOICE_MEMBERS(m_nMaxPlayers, MEMBER_INTEGER),
		GM_VOICE_MEMBERS(m_UpdateInterval, MEMBER_DOUBLE),
	GM_MEMBERS(m_fTeamCount, MEMBER_FLOAT),
	GM_MEMBERS(m_flCheckWinConditions, MEMBER_FLOAT),
	GM_MEMBERS(m_fRoundCount, MEMBER_FLOAT),
	GM_MEMBERS(m_iRoundTime, MEMBER_INTEGER),
	GM_MEMBERS(m_iRoundTimeSecs, MEMBER_INTEGER),
	GM_MEMBERS(m_iIntroRoundTime, MEMBER_INTEGER),
	GM_MEMBERS(m_fIntroRoundCount, MEMBER_FLOAT),
	GM_MEMBERS(m_iAccountTerrorist, MEMBER_INTEGER),
	GM_MEMBERS(m_iAccountCT, MEMBER_INTEGER),
	GM_MEMBERS(m_iNumTerrorist, MEMBER_INTEGER),
	GM_MEMBERS(m_iNumCT, MEMBER_INTEGER),
	GM_MEMBERS(m_iNumSpawnableTerrorist, MEMBER_INTEGER),
	GM_MEMBERS(m_iNumSpawnableCT, MEMBER_INTEGER),
	GM_MEMBERS(m_iSpawnPointCount_Terrorist, MEMBER_INTEGER),
	GM_MEMBERS(m_iSpawnPointCount_CT, MEMBER_INTEGER),
	GM_MEMBERS(m_iHostagesRescued, MEMBER_INTEGER),
	GM_MEMBERS(m_iHostagesTouched, MEMBER_INTEGER),
	GM_MEMBERS(m_iRoundWinStatus, MEMBER_INTEGER),
	GM_MEMBERS(m_iNumCTWins, MEMBER_SHORT),
	GM_MEMBERS(m_iNumTerroristWins, MEMBER_SHORT),
	GM_MEMBERS(m_bTargetBombed, MEMBER_BOOL),
	GM_MEMBERS(m_bBombDefused, MEMBER_BOOL),
	GM_MEMBERS(m_bMapHasBombTarget, MEMBER_BOOL),
	GM_MEMBERS(m_bMapHasBombZone, MEMBER_BOOL),
	GM_MEMBERS(m_bMapHasBuyZone, MEMBER_BOOL),
	GM_MEMBERS(m_bMapHasRescueZone, MEMBER_BOOL),
	GM_MEMBERS(m_bMapHasEscapeZone, MEMBER_BOOL),
	GM_MEMBERS(m_iMapHasVIPSafetyZone, MEMBER_INTEGER),
	GM_MEMBERS(m_bMapHasCameras, MEMBER_INTEGER),
	GM_MEMBERS(m_iC4Timer, MEMBER_INTEGER),
	GM_MEMBERS(m_iC4Guy, MEMBER_INTEGER),
	GM_MEMBERS(m_iLoserBonus, MEMBER_INTEGER),
	GM_MEMBERS(m_iNumConsecutiveCTLoses, MEMBER_INTEGER),
	GM_MEMBERS(m_iNumConsecutiveTerroristLoses, MEMBER_INTEGER),
	GM_MEMBERS(m_fMaxIdlePeriod, MEMBER_FLOAT),
	GM_MEMBERS(m_iLimitTeams, MEMBER_INTEGER),
	GM_MEMBERS(m_bLevelInitialized, MEMBER_BOOL),
	GM_MEMBERS(m_bRoundTerminating, MEMBER_BOOL),
	GM_MEMBERS(m_bCompleteReset, MEMBER_BOOL),
	GM_MEMBERS(m_flRequiredEscapeRatio, MEMBER_FLOAT),
	GM_MEMBERS(m_iNumEscapers, MEMBER_INTEGER),
	GM_MEMBERS(m_iHaveEscaped, MEMBER_INTEGER),
	GM_MEMBERS(m_bCTCantBuy, MEMBER_BOOL),
	GM_MEMBERS(m_bTCantBuy, MEMBER_BOOL),
	GM_MEMBERS(m_flBombRadius, MEMBER_FLOAT),
	GM_MEMBERS(m_iConsecutiveVIP, MEMBER_INTEGER),
	GM_MEMBERS(m_iTotalGunCount, MEMBER_INTEGER),
	GM_MEMBERS(m_iTotalGrenadeCount, MEMBER_INTEGER),
	GM_MEMBERS(m_iTotalArmourCount, MEMBER_INTEGER),
	GM_MEMBERS(m_iUnBalancedRounds, MEMBER_INTEGER),
	GM_MEMBERS(m_iNumEscapeRounds, MEMBER_INTEGER),
	GM_MEMBERS(m_iMapVotes, MEMBER_INTEGER),			// ARRAY 100
	GM_MEMBERS(m_iLastPick, MEMBER_INTEGER),
	GM_MEMBERS(m_iMaxMapTime, MEMBER_INTEGER),
	GM_MEMBERS(m_iMaxRounds, MEMBER_INTEGER),
	GM_MEMBERS(m_iTotalRoundsPlayed, MEMBER_INTEGER),
	GM_MEMBERS(m_iMaxRoundsWon, MEMBER_INTEGER),
	GM_MEMBERS(m_iStoredSpectValue, MEMBER_INTEGER),
	GM_MEMBERS(m_flForceCameraValue, MEMBER_FLOAT),
	GM_MEMBERS(m_flForceChaseCamValue, MEMBER_FLOAT),
	GM_MEMBERS(m_flFadeToBlackValue, MEMBER_FLOAT),
	GM_MEMBERS(m_pVIP, MEMBER_CLASSPTR),
	GM_MEMBERS(VIPQueue, MEMBER_CLASSPTR),				// ARRAY [5]
	GM_MEMBERS(m_flIntermissionEndTime, MEMBER_FLOAT),
	GM_MEMBERS(m_flIntermissionStartTime, MEMBER_FLOAT),
	GM_MEMBERS(m_iEndIntermissionButtonHit, MEMBER_INTEGER),
	GM_MEMBERS(m_tmNextPeriodicThink, MEMBER_FLOAT),
	GM_MEMBERS(m_bFirstConnected, MEMBER_BOOL),
	GM_MEMBERS(m_bInCareerGame, MEMBER_BOOL),
	GM_MEMBERS(m_fCareerRoundMenuTime, MEMBER_FLOAT),
	GM_MEMBERS(m_iCareerMatchWins, MEMBER_INTEGER),
	GM_MEMBERS(m_iRoundWinDifference, MEMBER_INTEGER),
	GM_MEMBERS(m_fCareerMatchMenuTime, MEMBER_FLOAT),
	GM_MEMBERS(m_bSkipSpawn, MEMBER_BOOL),
};

#define PL_MEMBERS(mx, mtype) ((!(mx & 1023) ? regmember::current_cell = 1, true : false) || (mx & 1023) == regmember::current_cell++) ? regmember(((CBasePlayer *)&mem_dummy)->##mx, sizeof(((CBasePlayer *)&mem_dummy)->##mx), offsetof(CBasePlayer, mx), mtype) : regmember(#mx " doesn't match hook definition")

member_t memberlist_player[] = {
	PL_MEMBERS(random_seed, MEMBER_INTEGER),
	PL_MEMBERS(m_usPlayerBleed, MEMBER_SHORT),
	PL_MEMBERS(m_hObserverTarget, MEMBER_EHANDLE),
	PL_MEMBERS(m_flNextObserverInput, MEMBER_FLOAT),
	PL_MEMBERS(m_iObserverWeapon, MEMBER_INTEGER),
	PL_MEMBERS(m_iObserverC4State, MEMBER_INTEGER),
	PL_MEMBERS(m_bObserverHasDefuser, MEMBER_BOOL),
	PL_MEMBERS(m_iObserverLastMode, MEMBER_INTEGER),
	PL_MEMBERS(m_flFlinchTime, MEMBER_FLOAT),
	PL_MEMBERS(m_flAnimTime, MEMBER_FLOAT),
	PL_MEMBERS(m_bHighDamage, MEMBER_BOOL),
	PL_MEMBERS(m_flVelocityModifier, MEMBER_FLOAT),
	PL_MEMBERS(m_iLastZoom, MEMBER_INTEGER),
	PL_MEMBERS(m_bResumeZoom, MEMBER_BOOL),
	PL_MEMBERS(m_flEjectBrass, MEMBER_FLOAT),
	PL_MEMBERS(m_iKevlar, MEMBER_INTEGER),
	PL_MEMBERS(m_bNotKilled, MEMBER_BOOL),
	PL_MEMBERS(m_iTeam, MEMBER_INTEGER),
	PL_MEMBERS(m_iAccount, MEMBER_INTEGER),
	PL_MEMBERS(m_bHasPrimary, MEMBER_BOOL),
	PL_MEMBERS(m_flDeathThrowTime, MEMBER_FLOAT),
	PL_MEMBERS(m_iThrowDirection, MEMBER_INTEGER),
	PL_MEMBERS(m_flLastTalk, MEMBER_FLOAT),
	PL_MEMBERS(m_bJustConnected, MEMBER_BOOL),
	PL_MEMBERS(m_bContextHelp, MEMBER_BOOL),
	PL_MEMBERS(m_iJoiningState, MEMBER_INTEGER),
	PL_MEMBERS(m_pIntroCamera, MEMBER_CLASSPTR),
	PL_MEMBERS(m_fIntroCamTime, MEMBER_FLOAT),
	PL_MEMBERS(m_fLastMovement, MEMBER_FLOAT),
	PL_MEMBERS(m_bMissionBriefing, MEMBER_BOOL),
	PL_MEMBERS(m_bTeamChanged, MEMBER_BOOL),
	PL_MEMBERS(m_iModelName, MEMBER_INTEGER),
	PL_MEMBERS(m_iTeamKills, MEMBER_INTEGER),
	PL_MEMBERS(m_iIgnoreGlobalChat, MEMBER_INTEGER),
	PL_MEMBERS(m_bHasNightVision, MEMBER_BOOL),
	PL_MEMBERS(m_bNightVisionOn, MEMBER_BOOL),
	PL_MEMBERS(m_vRecentPath, MEMBER_VECTOR),			// ARRAY [20]
	PL_MEMBERS(m_flIdleCheckTime, MEMBER_FLOAT),
	PL_MEMBERS(m_flRadioTime, MEMBER_FLOAT),
	PL_MEMBERS(m_iRadioMessages, MEMBER_INTEGER),
	PL_MEMBERS(m_bIgnoreRadio, MEMBER_BOOL),
	PL_MEMBERS(m_bHasC4, MEMBER_BOOL),
	PL_MEMBERS(m_bHasDefuser, MEMBER_BOOL),
	PL_MEMBERS(m_bKilledByBomb, MEMBER_BOOL),
	PL_MEMBERS(m_vBlastVector, MEMBER_VECTOR),
	PL_MEMBERS(m_bKilledByGrenade, MEMBER_BOOL),
	//PL_MEMBERS(m_hintMessageQueue),
	PL_MEMBERS(m_flDisplayHistory, MEMBER_INTEGER),
	PL_MEMBERS(m_iMenu, MEMBER_INTEGER),
	PL_MEMBERS(m_iChaseTarget, MEMBER_INTEGER),
	PL_MEMBERS(m_pChaseTarget, MEMBER_CLASSPTR),
	PL_MEMBERS(m_fCamSwitch, MEMBER_FLOAT),
	PL_MEMBERS(m_bEscaped, MEMBER_BOOL),
	PL_MEMBERS(m_bIsVIP, MEMBER_BOOL),
	PL_MEMBERS(m_tmNextRadarUpdate, MEMBER_FLOAT),
	PL_MEMBERS(m_vLastOrigin, MEMBER_VECTOR),
	PL_MEMBERS(m_iCurrentKickVote, MEMBER_INTEGER),
	PL_MEMBERS(m_flNextVoteTime, MEMBER_FLOAT),
	PL_MEMBERS(m_bJustKilledTeammate, MEMBER_BOOL),
	PL_MEMBERS(m_iHostagesKilled, MEMBER_INTEGER),
	PL_MEMBERS(m_iMapVote, MEMBER_INTEGER),
	PL_MEMBERS(m_bCanShoot, MEMBER_BOOL),
	PL_MEMBERS(m_flLastFired, MEMBER_FLOAT),
	PL_MEMBERS(m_flLastAttackedTeammate, MEMBER_FLOAT),
	PL_MEMBERS(m_bHeadshotKilled, MEMBER_BOOL),
	PL_MEMBERS(m_bPunishedForTK, MEMBER_BOOL),
	PL_MEMBERS(m_bReceivesNoMoneyNextRound, MEMBER_BOOL),
	PL_MEMBERS(m_iTimeCheckAllowed, MEMBER_INTEGER),
	PL_MEMBERS(m_bHasChangedName, MEMBER_BOOL),
	PL_MEMBERS(m_szNewName, MEMBER_CHAR_ARRAY),			// ARRAY [32]
	PL_MEMBERS(m_bIsDefusing, MEMBER_BOOL),
	PL_MEMBERS(m_tmHandleSignals, MEMBER_FLOAT),
	PL_MEMBERS(m_signals, MEMBER_SIGNALS),
	PL_MEMBERS(m_pentCurBombTarget, MEMBER_EDICT),
	PL_MEMBERS(m_iPlayerSound, MEMBER_INTEGER),
	PL_MEMBERS(m_iTargetVolume, MEMBER_INTEGER),
	PL_MEMBERS(m_iWeaponVolume, MEMBER_INTEGER),
	PL_MEMBERS(m_iExtraSoundTypes, MEMBER_INTEGER),
	PL_MEMBERS(m_iWeaponFlash, MEMBER_INTEGER),
	PL_MEMBERS(m_flStopExtraSoundTime, MEMBER_FLOAT),
	PL_MEMBERS(m_flFlashLightTime, MEMBER_FLOAT),
	PL_MEMBERS(m_iFlashBattery, MEMBER_INTEGER),
	PL_MEMBERS(m_afButtonLast, MEMBER_INTEGER),
	PL_MEMBERS(m_afButtonPressed, MEMBER_INTEGER),
	PL_MEMBERS(m_afButtonReleased, MEMBER_INTEGER),
	PL_MEMBERS(m_pentSndLast, MEMBER_EDICT),
	PL_MEMBERS(m_flSndRoomtype, MEMBER_FLOAT),
	PL_MEMBERS(m_flSndRange, MEMBER_FLOAT),
	PL_MEMBERS(m_flFallVelocity, MEMBER_FLOAT),
	PL_MEMBERS(m_rgItems, MEMBER_INTEGER),				// ARRAY [4]
	PL_MEMBERS(m_fNewAmmo, MEMBER_INTEGER),
	PL_MEMBERS(m_afPhysicsFlags, MEMBER_INTEGER),
	PL_MEMBERS(m_fNextSuicideTime, MEMBER_FLOAT),
	PL_MEMBERS(m_flTimeStepSound, MEMBER_FLOAT),
	PL_MEMBERS(m_flTimeWeaponIdle, MEMBER_FLOAT),
	PL_MEMBERS(m_flSwimTime, MEMBER_FLOAT),
	PL_MEMBERS(m_flDuckTime, MEMBER_FLOAT),
	PL_MEMBERS(m_flWallJumpTime, MEMBER_FLOAT),
	PL_MEMBERS(m_flSuitUpdate, MEMBER_FLOAT),
	PL_MEMBERS(m_rgSuitPlayList, MEMBER_INTEGER),			// ARRAY [4]
	PL_MEMBERS(m_iSuitPlayNext, MEMBER_INTEGER),
	PL_MEMBERS(m_rgiSuitNoRepeat, MEMBER_INTEGER),			// ARRAY [32]
	PL_MEMBERS(m_rgflSuitNoRepeatTime, MEMBER_FLOAT),		// ARRAY [32]
	PL_MEMBERS(m_lastDamageAmount, MEMBER_INTEGER),
	PL_MEMBERS(m_tbdPrev, MEMBER_FLOAT),
	PL_MEMBERS(m_flgeigerRange, MEMBER_FLOAT),
	PL_MEMBERS(m_flgeigerDelay, MEMBER_FLOAT),
	PL_MEMBERS(m_igeigerRangePrev, MEMBER_INTEGER),
	PL_MEMBERS(m_iStepLeft, MEMBER_INTEGER),
	PL_MEMBERS(m_szTextureName, MEMBER_CHAR_ARRAY),			// ARRAY [17]
	PL_MEMBERS(m_chTextureType, MEMBER_BYTE),
	PL_MEMBERS(m_idrowndmg, MEMBER_INTEGER),
	PL_MEMBERS(m_idrownrestored, MEMBER_INTEGER),
	PL_MEMBERS(m_bitsHUDDamage, MEMBER_INTEGER),
	PL_MEMBERS(m_fInitHUD, MEMBER_INTEGER),
	PL_MEMBERS(m_fGameHUDInitialized, MEMBER_INTEGER),
	PL_MEMBERS(m_iTrain, MEMBER_INTEGER),
	PL_MEMBERS(m_fWeapon, MEMBER_INTEGER),
	PL_MEMBERS(m_pTank, MEMBER_EHANDLE),
	PL_MEMBERS(m_fDeadTime, MEMBER_FLOAT),
	PL_MEMBERS(m_fNoPlayerSound, MEMBER_INTEGER),
	PL_MEMBERS(m_fLongJump, MEMBER_INTEGER),
	PL_MEMBERS(m_tSneaking, MEMBER_FLOAT),
	PL_MEMBERS(m_iUpdateTime, MEMBER_INTEGER),
	PL_MEMBERS(m_iClientHealth, MEMBER_INTEGER),
	PL_MEMBERS(m_iClientBattery, MEMBER_INTEGER),
	PL_MEMBERS(m_iHideHUD, MEMBER_INTEGER),
	PL_MEMBERS(m_iClientHideHUD, MEMBER_INTEGER),
	PL_MEMBERS(m_iFOV, MEMBER_INTEGER),
	PL_MEMBERS(m_iClientFOV, MEMBER_INTEGER),
	PL_MEMBERS(m_iNumSpawns, MEMBER_INTEGER),
	PL_MEMBERS(m_pObserver, MEMBER_CLASSPTR),
	PL_MEMBERS(m_rgpPlayerItems, MEMBER_CLASSPTR),
	PL_MEMBERS(m_pActiveItem, MEMBER_CLASSPTR),
	PL_MEMBERS(m_pClientActiveItem, MEMBER_CLASSPTR),
	PL_MEMBERS(m_pLastItem, MEMBER_CLASSPTR),
	PL_MEMBERS(m_rgAmmo, MEMBER_INTEGER),				// ARRAY [32]
	PL_MEMBERS(m_rgAmmoLast, MEMBER_INTEGER),			// ARRAY [32]
	PL_MEMBERS(m_vecAutoAim, MEMBER_VECTOR),
	PL_MEMBERS(m_fOnTarget, MEMBER_INTEGER),
	PL_MEMBERS(m_iDeaths, MEMBER_INTEGER),
	PL_MEMBERS(m_izSBarState, MEMBER_INTEGER),			// ARRAY [4]
	PL_MEMBERS(m_flNextSBarUpdateTime, MEMBER_FLOAT),
	PL_MEMBERS(m_flStatusBarDisappearDelay, MEMBER_FLOAT),
	PL_MEMBERS(m_SbarString0, MEMBER_CHAR_ARRAY),			// ARRAY [128]
	PL_MEMBERS(m_lastx, MEMBER_INTEGER),
	PL_MEMBERS(m_lasty, MEMBER_INTEGER),
	PL_MEMBERS(m_nCustomSprayFrames, MEMBER_INTEGER),
	PL_MEMBERS(m_flNextDecalTime, MEMBER_FLOAT),
	PL_MEMBERS(m_szTeamName, MEMBER_CHAR_ARRAY),			// ARRAY [16]
	PL_MEMBERS(m_modelIndexPlayer, MEMBER_INTEGER),
	PL_MEMBERS(m_szAnimExtention, MEMBER_CHAR_ARRAY),		// ARRAY [32]
	PL_MEMBERS(m_iGaitsequence, MEMBER_INTEGER),
	PL_MEMBERS(m_flGaitframe, MEMBER_FLOAT),
	PL_MEMBERS(m_flGaityaw, MEMBER_FLOAT),
	PL_MEMBERS(m_prevgaitorigin, MEMBER_VECTOR),
	PL_MEMBERS(m_flPitch, MEMBER_FLOAT),
	PL_MEMBERS(m_flYaw, MEMBER_FLOAT),
	PL_MEMBERS(m_flGaitMovement, MEMBER_FLOAT),
	PL_MEMBERS(m_iAutoWepSwitch, MEMBER_INTEGER),
	PL_MEMBERS(m_bVGUIMenus, MEMBER_BOOL),
	PL_MEMBERS(m_bShowHints, MEMBER_BOOL),
	PL_MEMBERS(m_bShieldDrawn, MEMBER_BOOL),
	PL_MEMBERS(m_bOwnsShield, MEMBER_BOOL),
	PL_MEMBERS(m_bWasFollowing, MEMBER_BOOL),
	PL_MEMBERS(m_flNextFollowTime, MEMBER_FLOAT),
	PL_MEMBERS(m_flYawModifier, MEMBER_FLOAT),
	PL_MEMBERS(m_blindUntilTime, MEMBER_FLOAT),
	PL_MEMBERS(m_blindStartTime, MEMBER_FLOAT),
	PL_MEMBERS(m_blindHoldTime, MEMBER_FLOAT),
	PL_MEMBERS(m_blindFadeTime, MEMBER_FLOAT),
	PL_MEMBERS(m_blindAlpha, MEMBER_INTEGER),
	PL_MEMBERS(m_allowAutoFollowTime, MEMBER_FLOAT),
	PL_MEMBERS(m_autoBuyString, MEMBER_CHAR_ARRAY),			// ARRAY 256
	PL_MEMBERS(m_rebuyString, MEMBER_CHAR_POINTER),
	PL_MEMBERS(m_rebuyStruct, MEBMER_REBUYSTRUCT),
	PL_MEMBERS(m_bIsInRebuy, MEMBER_BOOL),
	PL_MEMBERS(m_flLastUpdateTime, MEMBER_FLOAT),
	PL_MEMBERS(m_lastLocation, MEMBER_CHAR_ARRAY),			// ARRAY [32]
	PL_MEMBERS(m_progressStart, MEMBER_FLOAT),
	PL_MEMBERS(m_progressEnd, MEMBER_FLOAT),
	PL_MEMBERS(m_bObserverAutoDirector, MEMBER_BOOL),
	PL_MEMBERS(m_canSwitchObserverModes, MEMBER_BOOL),
	PL_MEMBERS(m_heartBeatTime, MEMBER_FLOAT),
	PL_MEMBERS(m_intenseTimestamp, MEMBER_FLOAT),
	PL_MEMBERS(m_silentTimestamp, MEMBER_FLOAT),
	PL_MEMBERS(m_musicState, MEMBER_INTEGER),
	PL_MEMBERS(m_flLastCommandTime, MEMBER_FLOAT),			// ARRAY [8]
};

memberlist_t memberlist;

member_t *memberlist_t::operator[](size_t members) const
{	
	#define CASE(h)	case ht_##h: if (index < arraysize(memberlist_##h)) return &memberlist_##h[index]; else break;

	const auto table = members_tables_e(members / MAX_REGION_RANGE);
	const auto index = members & (MAX_REGION_RANGE - 1);

	switch (table) {
		CASE(gamerules)
		CASE(player)
	}

	return nullptr;
}
