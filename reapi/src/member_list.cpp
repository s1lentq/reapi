#include "precompiled.h"

#define CLASS_MEMBERS(cx, mx) ((!(mx & (MAX_REGION_RANGE - 1)) ? regmember::current_cell = 1, true : false) || (mx & (MAX_REGION_RANGE - 1)) == regmember::current_cell++) ? regmember([](member_t* ptr){ decltype(##cx::##mx) f = {};ptr->size = getTypeSize(f);ptr->max_size = sizeof(f);ptr->offset = offsetof(##cx, ##mx);ptr->type = getMemberType(f);}) : regmember(#mx)

#define GM_MEMBERS(mx) CLASS_MEMBERS(CHalfLifeMultiplay, mx)
#define GM_VOICE_MEMBERS(mx) CLASS_MEMBERS(CVoiceGameMgr, mx)
#define BASE_MEMBERS(mx) CLASS_MEMBERS(CBaseEntity, mx)
#define ANIM_MEMBERS(mx) CLASS_MEMBERS(CBaseAnimating, mx)
#define PL_MEMBERS(mx) CLASS_MEMBERS(CBasePlayer, mx)
#define EVAR_MEMBERS(mx) CLASS_MEMBERS(com_entvars, mx)

inline MType getMemberType(float*)			{ return MEMBER_FLOAT; }
inline MType getMemberType(float)			{ return MEMBER_FLOAT; }

inline MType getMemberType(double)			{ return MEMBER_DOUBLE; }

inline MType getMemberType(CBasePlayer**)		{ return MEMBER_CLASSPTR; }
inline MType getMemberType(CBasePlayer*)		{ return MEMBER_CLASSPTR; }
inline MType getMemberType(CBasePlayerItem**)		{ return MEMBER_CLASSPTR; }
inline MType getMemberType(CBasePlayerItem*)		{ return MEMBER_CLASSPTR; }
inline MType getMemberType(CBaseEntity*)		{ return MEMBER_CLASSPTR; }

inline MType getMemberType(EHANDLE)			{ return MEMBER_EHANDLE; }
inline MType getMemberType(entvars_t*)			{ return MEMBER_EVARS; }
inline MType getMemberType(edict_t*)			{ return MEMBER_EDICT; }

inline MType getMemberType(Vector*)			{ return MEMBER_VECTOR; }
inline MType getMemberType(Vector)			{ return MEMBER_VECTOR; }

inline MType getMemberType(char*)			{ return MEMBER_STRING; }
inline MType getMemberType(qstring_t)		{ return MEMBER_QSTRING; }

inline MType getMemberType(char)			{ return MEMBER_BYTE; }
inline MType getMemberType(byte)			{ return MEMBER_BYTE; }
inline MType getMemberType(byte*)			{ return MEMBER_BYTE; }

inline MType getMemberType(int*)			{ return MEMBER_INTEGER; }
inline MType getMemberType(int)				{ return MEMBER_INTEGER; }
inline MType getMemberType(unsigned)			{ return MEMBER_INTEGER; }
inline MType getMemberType(TeamName)			{ return MEMBER_INTEGER; }
inline MType getMemberType(JoinState)			{ return MEMBER_INTEGER; }
inline MType getMemberType(ModelName)			{ return MEMBER_INTEGER; }
inline MType getMemberType(_Menu)			{ return MEMBER_INTEGER; }
inline MType getMemberType(MusicState)			{ return MEMBER_INTEGER; }

inline MType getMemberType(short)			{ return MEMBER_SHORT; }
inline MType getMemberType(unsigned short)		{ return MEMBER_SHORT; }

inline MType getMemberType(bool)			{ return MEMBER_BOOL; }
inline MType getMemberType(CUnifiedSignals)		{ return MEMBER_SIGNALS; }
inline MType getMemberType(RebuyStruct)			{ return MEBMER_REBUYSTRUCT; }

template<typename T>
inline MType getMemberType(T) { static_assert(false, "Not implemented overload"); }

template<typename T>
inline size_t getTypeSize(T type[]) { return sizeof(T); }

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

member_t memberlist_gamerules[] = {
	GM_MEMBERS(m_bFreezePeriod),
	GM_MEMBERS(m_bBombDropped),
	// m_VoiceGameMgr ->
		GM_VOICE_MEMBERS(m_msgPlayerVoiceMask),
		GM_VOICE_MEMBERS(m_msgRequestState),
		GM_VOICE_MEMBERS(m_nMaxPlayers),
		GM_VOICE_MEMBERS(m_UpdateInterval),
	GM_MEMBERS(m_fTeamCount),
	GM_MEMBERS(m_flCheckWinConditions),
	GM_MEMBERS(m_fRoundCount),
	GM_MEMBERS(m_iRoundTime),
	GM_MEMBERS(m_iRoundTimeSecs),
	GM_MEMBERS(m_iIntroRoundTime),
	GM_MEMBERS(m_fIntroRoundCount),
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
	GM_MEMBERS(m_iMapHasVIPSafetyZone),
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
	GM_MEMBERS(VIPQueue),
	GM_MEMBERS(m_flIntermissionEndTime),
	GM_MEMBERS(m_flIntermissionStartTime),
	GM_MEMBERS(m_iEndIntermissionButtonHit),
	GM_MEMBERS(m_tmNextPeriodicThink),
	GM_MEMBERS(m_bFirstConnected),
	GM_MEMBERS(m_bInCareerGame),
	GM_MEMBERS(m_fCareerRoundMenuTime),
	GM_MEMBERS(m_iCareerMatchWins),
	GM_MEMBERS(m_iRoundWinDifference),
	GM_MEMBERS(m_fCareerMatchMenuTime),
	GM_MEMBERS(m_bSkipSpawn),
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
	EVAR_MEMBERS(euser4)
};


memberlist_t memberlist;

member_t *memberlist_t::operator[](size_t members) const
{
	#define CASE(h)	case ht_##h: if (index < arraysize(memberlist_##h)) return &memberlist_##h[index]; else break;

	const auto table = members_tables_e(members / MAX_REGION_RANGE);
	const auto index = members & (MAX_REGION_RANGE - 1);

	switch (table) {
		CASE(gamerules)
		CASE(base)
		CASE(animating)
		CASE(player)
		CASE(entvars)
	}

	return nullptr;
}
