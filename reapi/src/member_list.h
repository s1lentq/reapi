#pragma once

#define BEGIN_MEMBER_REGION(x)			(MAX_REGION_RANGE * memberlist_t::members_tables_e::mt_##x)

// member types
enum MType
{
	MEMBER_NONE = 0,
	MEMBER_FLOAT,			// Any floating point value
	MEMBER_DOUBLE,			// double value
	MEMBER_ENTITY,			// An entity offset (EOFFSET)
	MEMBER_CLASSPTR,		// CBaseEntity *
	MEMBER_EHANDLE,			// Entity handle
	MEMBER_EVARS,			// EVARS *
	MEMBER_EDICT,			// edict_t *, or edict_t *  (same thing)
	MEMBER_VECTOR,			// Any vector
	MEMBER_STRING,			// char *, char []
	MEMBER_QSTRING,			// quake string, like string_t
	MEMBER_RSTRING,			// reverse of qstring to string
	MEMBER_INTEGER,			// Any integer or enum
	MEMBER_SHORT,			// 2 byte integer
	MEMBER_BYTE,			// a byte
	MEMBER_BOOL,			// a bool
	MEMBER_SIGNALS,			// class CUnifiedSignals
	MEBMER_REBUYSTRUCT,		// struct RebuyStruct
	MEMBER_PMTRACE,			// struct pmtrace_t
	MEBMER_USERCMD,			// struct usercmd_s
	MEMBER_TRACERESULT,		// struct TraceResult
};

struct memberlist_t
{
	struct member_t *operator[](size_t members) const;

	enum members_tables_e
	{
		mt_gamerules,
		mt_base,
		mt_animating,
		mt_basemonster,
		mt_player,
		mt_entvars,
		mt_playermove,
		mt_movevars,
		mt_usercmd,
		mt_pmtrace,
		mt_csplayer,
		mt_baseitem,
		mt_baseweapon,
		mt_weaponbox,
		mt_armoury,
		mt_grenade,
		mt_p228,
		mt_scout,
		mt_hegrenade,
		mt_xm1014,
		mt_c4,
		mt_mac10,
		mt_aug,
		mt_smokegrenade,
		mt_elite,
		mt_fiveseven,
		mt_ump45,
		mt_sg550,
		mt_galil,
		mt_famas,
		mt_usp,
		mt_glock18,
		mt_awp,
		mt_mp5n,
		mt_m249,
		mt_m3,
		mt_m4a1,
		mt_tmp,
		mt_g3sg1,
		mt_deagle,
		mt_sg552,
		mt_ak47,
		mt_knife,
		mt_p90,
		mt_shield,
		mt_rebuystruct,
		mt_mapinfo,
		mt_csplayerweapon,
		mt_gib,
		mt_netadr,
		mt_csentity
	};
};

struct member_t
{
	bool isTypeReturnable() const;

	size_t size;
	size_t max_size;
	size_t offset;
	const char *name;
	MType type;
	bool (*pfnIsRefsToClass)(void *pEntity);

	inline static const char *getTypeString(MType memberType)
	{
		switch (memberType)
		{
		case MEMBER_FLOAT:       return "Float";
		case MEMBER_DOUBLE:      return "Double";
		case MEMBER_ENTITY:      return "Entity";
		case MEMBER_CLASSPTR:    return "ClassPtr";
		case MEMBER_EHANDLE:     return "EHANDLE";
		case MEMBER_EVARS:       return "entvars";
		case MEMBER_EDICT:       return "edict";
		case MEMBER_VECTOR:      return "Vector";
		case MEMBER_STRING:      return "String";
		case MEMBER_QSTRING:     return "QStirng";
		case MEMBER_INTEGER:     return "Integer";
		case MEMBER_SHORT:       return "Short";
		case MEMBER_BYTE:        return "Byte";
		case MEMBER_BOOL:        return "Bool";
		case MEMBER_SIGNALS:     return "Signals";
		case MEBMER_REBUYSTRUCT: return "RebuyStruct";
		case MEMBER_PMTRACE:     return "pmtrace";
		case MEBMER_USERCMD:     return "usercmd";
		case MEMBER_TRACERESULT: return "TraceResult";
		default:
		{
			static char string[16];
			Q_snprintf(string, sizeof(string), "%d", memberType);
			return string;
		}
		}

		return ""; // shut up compiler
	}

};

inline bool member_t::isTypeReturnable() const
{
	switch (type) {
	case MEMBER_FLOAT:
	case MEMBER_DOUBLE:
	case MEMBER_ENTITY:
	case MEMBER_CLASSPTR:
	case MEMBER_EDICT:
	case MEMBER_INTEGER:
	case MEMBER_SHORT:
	case MEMBER_BYTE:
	case MEMBER_BOOL:
	case MEMBER_EVARS:
	case MEMBER_PMTRACE:
	case MEBMER_USERCMD:
		return true;

	default:
		return false;
	}
}

extern memberlist_t memberlist;

// CSGameRules
enum CSGameRules_Members
{
	m_bFreezePeriod = BEGIN_MEMBER_REGION(gamerules),
	m_bBombDropped,
	m_GameDesc,

	// m_VoiceGameMgr -> CVoiceGameMgr
	m_msgPlayerVoiceMask,
	m_msgRequestState,
	m_nMaxPlayers,
	m_UpdateInterval,

	m_flRestartRoundTime,		// The global time when the round is supposed to end, if this is not 0 (deprecated name m_fTeamCount)
	m_flCheckWinConditions,
	m_fRoundStartTime,			// Time round has started (deprecated name m_fRoundCount)
	m_iRoundTime,				// (From mp_roundtime) - How many seconds long this round is.
	m_iRoundTimeSecs,
	m_iIntroRoundTime,			// (From mp_freezetime) - How many seconds long the intro round (when players are frozen) is.
	m_fRoundStartTimeReal,		// The global time when the intro round ends and the real one starts
								// wrote the original "m_flRoundTime" comment for this variable).
	m_iAccountTerrorist,
	m_iAccountCT,
	m_iNumTerrorist,			// The number of terrorists on the team (this is generated at the end of a round)
	m_iNumCT,					// The number of CTs on the team (this is generated at the end of a round)
	m_iNumSpawnableTerrorist,
	m_iNumSpawnableCT,
	m_iSpawnPointCount_Terrorist,	// Number of Terrorist spawn points
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
	m_bMapHasVIPSafetyZone,			// 0 = uninitialized,   1 = has VIP safety zone,   2 = DOES not have VIP safetyzone
	m_bMapHasCameras,
	m_iC4Timer,
	m_iC4Guy,							// The current Terrorist who has the C4.
	m_iLoserBonus,						// the amount of money the losing team gets. This scales up as they lose more rounds in a row
	m_iNumConsecutiveCTLoses,			// the number of rounds the CTs have lost in a row.
	m_iNumConsecutiveTerroristLoses,	// the number of rounds the Terrorists have lost in a row.
	m_fMaxIdlePeriod,					// For the idle kick functionality. This is tha max amount of time that the player has to be idle before being kicked
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
	m_iUnBalancedRounds,		// keeps track of the # of consecutive rounds that have gone by where one team outnumbers the other team by more than 2
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
	m_pVIPQueue,
	m_flIntermissionEndTime,
	m_flIntermissionStartTime,
	m_iEndIntermissionButtonHit,
	m_tmNextPeriodicThink,
	m_bGameStarted,
	m_bInCareerGame,
	m_fCareerRoundMenuTime,
	m_iCareerMatchWins,
	m_iRoundWinDifference,
	m_fCareerMatchMenuTime,
	m_bSkipSpawn,
	m_bSkipShowMenu,
	m_bNeededPlayers,
	m_flEscapeRatio,
	m_flTimeLimit,
	m_flGameStartTime,
	m_bTeamBalanced,
};

// CBaseEntity
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

// CBaseMonster
enum CBaseMonster_Members
{
	m_Activity = BEGIN_MEMBER_REGION(basemonster),
	m_IdealActivity,
	m_LastHitGroup,
	m_bitsDamageType,
	m_rgbTimeBasedDamage,
	m_MonsterState,
	m_IdealMonsterState,
	m_afConditions,
	m_afMemory,
	m_flNextAttack,
	m_hEnemy,
	m_hTargetEnt,
	m_flFieldOfView,
	m_bloodColor,
	m_HackedGunPos,
	m_vecEnemyLKP,
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
	m_flLastCommandTime,
	m_iLastAccount,
	m_iLastClientHealth,
	m_tmNextAccountHealthUpdate,
};

// entvars
enum EntVars
{
	var_classname = BEGIN_MEMBER_REGION(entvars),
	var_globalname,
	var_origin,
	var_oldorigin,
	var_velocity,
	var_basevelocity,
	var_clbasevelocity,
	var_movedir,
	var_angles,
	var_avelocity,
	var_punchangle,
	var_v_angle,
	var_endpos,
	var_startpos,
	var_impacttime,
	var_starttime,
	var_fixangle,
	var_idealpitch,
	var_pitch_speed,
	var_ideal_yaw,
	var_yaw_speed,
	var_modelindex,
	var_model,
	var_viewmodel,
	var_weaponmodel,
	var_absmin,
	var_absmax,
	var_mins,
	var_maxs,
	var_size,
	var_ltime,
	var_nextthink,
	var_movetype,
	var_solid,
	var_skin,
	var_body,
	var_effects,
	var_gravity,
	var_friction,
	var_light_level,
	var_sequence,
	var_gaitsequence,
	var_frame,
	var_animtime,
	var_framerate,
	var_controller,
	var_blending,
	var_scale,
	var_rendermode,
	var_renderamt,
	var_rendercolor,
	var_renderfx,
	var_health,
	var_frags,
	var_weapons,
	var_takedamage,
	var_deadflag,
	var_view_ofs,
	var_button,
	var_impulse,
	var_chain,
	var_dmg_inflictor,
	var_enemy,
	var_aiment,
	var_owner,
	var_groundentity,
	var_spawnflags,
	var_flags,
	var_colormap,
	var_team,
	var_max_health,
	var_teleport_time,
	var_armortype,
	var_armorvalue,
	var_waterlevel,
	var_watertype,
	var_target,
	var_targetname,
	var_netname,
	var_message,
	var_dmg_take,
	var_dmg_save,
	var_dmg,
	var_dmgtime,
	var_noise,
	var_noise1,
	var_noise2,
	var_noise3,
	var_speed,
	var_air_finished,
	var_pain_finished,
	var_radsuit_finished,
	var_pContainingEntity,
	var_playerclass,
	var_maxspeed,
	var_fov,
	var_weaponanim,
	var_pushmsec,
	var_bInDuck,
	var_flTimeStepSound,
	var_flSwimTime,
	var_flDuckTime,
	var_iStepLeft,
	var_flFallVelocity,
	var_gamestate,
	var_oldbuttons,
	var_groupinfo,
	var_iuser1,
	var_iuser2,
	var_iuser3,
	var_iuser4,
	var_fuser1,
	var_fuser2,
	var_fuser3,
	var_fuser4,
	var_vuser1,
	var_vuser2,
	var_vuser3,
	var_vuser4,
	var_euser1,
	var_euser2,
	var_euser3,
	var_euser4
};

enum PlayerMove
{
	pm_player_index = BEGIN_MEMBER_REGION(playermove),
	pm_server,
	pm_multiplayer,
	pm_time,
	pm_frametime,
	pm_forward,
	pm_right,
	pm_up,
	pm_origin,
	pm_angles,
	pm_oldangles,
	pm_velocity,
	pm_movedir,
	pm_basevelocity,
	pm_view_ofs,
	pm_flDuckTime,
	pm_bInDuck,
	pm_flTimeStepSound,
	pm_iStepLeft,
	pm_flFallVelocity,
	pm_punchangle,
	pm_flSwimTime,
	pm_flNextPrimaryAttack,
	pm_effects,
	pm_flags,
	pm_usehull,
	pm_gravity,
	pm_friction,
	pm_oldbuttons,
	pm_waterjumptime,
	pm_dead,
	pm_deadflag,
	pm_spectator,
	pm_movetype,
	pm_onground,
	pm_waterlevel,
	pm_watertype,
	pm_oldwaterlevel,
	pm_sztexturename,
	pm_chtexturetype,
	pm_maxspeed,
	pm_clientmaxspeed,
	pm_iuser1,
	pm_iuser2,
	pm_iuser3,
	pm_iuser4,
	pm_fuser1,
	pm_fuser2,
	pm_fuser3,
	pm_fuser4,
	pm_vuser1,
	pm_vuser2,
	pm_vuser3,
	pm_vuser4,
	pm_numphysent,
	pm_cmd,
	pm_numtouch,
	pm_physinfo,
	pm_player_mins,
	pm_player_maxs,

	// TODO: Impl me!
	//pm_physents,
	//pm_nummoveent,
	//pm_moveents,
	//pm_numvisent
	//pm_visents,
	//pm_touchindex,
	//pm_movevars,
};

enum MoveVars
{
	mv_gravity = BEGIN_MEMBER_REGION(movevars),
	mv_stopspeed,
	mv_maxspeed,
	mv_spectatormaxspeed,
	mv_accelerate,
	mv_airaccelerate,
	mv_wateraccelerate,
	mv_friction,
	mv_edgefriction,
	mv_waterfriction,
	mv_entgravity,
	mv_bounce,
	mv_stepsize,
	mv_maxvelocity,
	mv_zmax,
	mv_waveHeight,
	mv_footsteps,
	mv_skyName,
	mv_rollangle,
	mv_rollspeed,
	mv_skycolor_r,
	mv_skycolor_g,
	mv_skycolor_b,
	mv_skyvec_x,
	mv_skyvec_y,
	mv_skyvec_z
};

enum UserCmd
{
	ucmd_lerp_msec = BEGIN_MEMBER_REGION(usercmd),
	ucmd_msec,
	ucmd_viewangles,
	ucmd_forwardmove,
	ucmd_sidemove,
	ucmd_upmove,
	ucmd_lightlevel,
	ucmd_buttons,
	ucmd_impulse,
	ucmd_weaponselect,
	ucmd_impact_index,
	ucmd_impact_position
};

enum PMTrace
{
	pmt_allsolid = BEGIN_MEMBER_REGION(pmtrace),
	pmt_startsolid,
	pmt_inopen,
	pmt_inwater,
	pmt_fraction,
	pmt_endpos,
	pmt_ent,
	pmt_deltavelocity,
	pmt_hitgroup
};

enum NetAdr
{
	netadr_type = BEGIN_MEMBER_REGION(netadr),
	netadr_ip,
	netadr_port
};

// CCSPlayer
enum CSPlayer_Members
{
	m_szModel = BEGIN_MEMBER_REGION(csplayer),
	m_bForceShowMenu,
	m_flRespawnPending,
	m_flSpawnProtectionEndTime,
	m_vecOldvAngle,
	m_iWeaponInfiniteAmmo,
	m_iWeaponInfiniteIds,
	m_bCanShootOverride,
	m_bGameForcingRespawn,
	m_bAutoBunnyHopping,
	m_bMegaBunnyJumping,
	m_bPlantC4Anywhere,
	m_bSpawnProtectionEffects,
	m_flJumpHeight,
	m_flLongJumpHeight,
	m_flLongJumpForce,
	m_flDuckSpeedMultiplier,
	m_iNumKilledByUnanswered,
	m_bPlayerDominated,
};

enum CBasePlayerItem_Members
{
	m_pPlayer = BEGIN_MEMBER_REGION(baseitem),
	m_pNext,
	m_iId,
};

enum CBasePlayerWeapon_Members
{
	m_Weapon_iPlayEmptySound = BEGIN_MEMBER_REGION(baseweapon),
	m_Weapon_fFireOnEmpty,
	m_Weapon_flNextPrimaryAttack,
	m_Weapon_flNextSecondaryAttack,
	m_Weapon_flTimeWeaponIdle,
	m_Weapon_iPrimaryAmmoType,
	m_Weapon_iSecondaryAmmoType,
	m_Weapon_iClip,
	m_Weapon_iClientClip,
	m_Weapon_iClientWeaponState,
	m_Weapon_fInReload,
	m_Weapon_fInSpecialReload,
	m_Weapon_iDefaultAmmo,
	m_Weapon_iShellId,
	m_Weapon_fMaxSpeed,
	m_Weapon_bDelayFire,
	m_Weapon_iDirection,
	m_Weapon_bSecondarySilencerOn,
	m_Weapon_flAccuracy,
	m_Weapon_flLastFire,
	m_Weapon_iShotsFired,
	//m_Weapon_vVecAiming,
	//m_Weapon_model_name,
	m_Weapon_flGlock18Shoot,
	m_Weapon_iGlock18ShotsFired,
	m_Weapon_flFamasShoot,
	m_Weapon_iFamasShotsFired,
	m_Weapon_fBurstSpread,
	m_Weapon_iWeaponState,
	m_Weapon_flNextReload,
	m_Weapon_flDecreaseShotsFired,
	m_Weapon_usFireGlock18,
	m_Weapon_usFireFamas,
	m_Weapon_flPrevPrimaryAttack,
	m_Weapon_flLastFireTime,
};

enum CWeaponBox_Members
{
	m_WeaponBox_rgpPlayerItems = BEGIN_MEMBER_REGION(weaponbox),
	m_WeaponBox_rgiszAmmo,
	m_WeaponBox_rgAmmo,
	m_WeaponBox_cAmmoTypes,
	m_WeaponBox_bIsBomb,
};

enum CArmoury_Members
{
	m_Armoury_iItem = BEGIN_MEMBER_REGION(armoury),
	m_Armoury_iCount,
	m_Armoury_iInitialCount,
	m_Armoury_bAlreadyCounted,
};

enum CGrenade_Members
{
	m_Grenade_bStartDefuse = BEGIN_MEMBER_REGION(grenade),
	m_Grenade_bIsC4,
	m_Grenade_pBombDefuser,
	m_Grenade_flDefuseCountDown,
	m_Grenade_flC4Blow,
	m_Grenade_flNextFreqInterval,
	m_Grenade_flNextBeep,
	m_Grenade_flNextFreq,
	m_Grenade_sBeepName,
	m_Grenade_fAttenu,
	m_Grenade_flNextBlink,
	m_Grenade_fNextDefuse,
	m_Grenade_bJustBlew,
	m_Grenade_iTeam,
	m_Grenade_iCurWave,
	m_Grenade_pentCurBombTarget,
	m_Grenade_SGSmoke,
	m_Grenade_angle,
	m_Grenade_usEvent,
	m_Grenade_bLightSmoke,
	m_Grenade_bDetonated,
	m_Grenade_vSmokeDetonate,
	m_Grenade_iBounceCount,
	m_Grenade_fRegisteredSound,
};

enum CP228_Members
{
	m_P228_iShell = BEGIN_MEMBER_REGION(p228),
	m_P228_usFire,
};

enum CSCOUT_Members
{
	m_SCOUT_iShell = BEGIN_MEMBER_REGION(scout),
	m_SCOUT_usFire,
};

enum CHEGrenade_Members
{
	m_HEGrenade_usCreate = BEGIN_MEMBER_REGION(hegrenade),
};

enum CXM1014_Members
{
	m_XM1014_iShell = BEGIN_MEMBER_REGION(xm1014),
	m_XM1014_flPumpTime,
	m_XM1014_usFire,
};

enum CC4_Members
{
	m_C4_bStartedArming = BEGIN_MEMBER_REGION(c4),
	m_C4_bBombPlacedAnimation,
	m_C4_fArmedTime,
	m_C4_bHasShield,
};

enum CMAC10_Members
{
	m_MAC10_iShell = BEGIN_MEMBER_REGION(mac10),
	m_MAC10_iShellOn,
	m_MAC10_usFire,
};

enum CAUG_Members
{
	m_AUG_iShell = BEGIN_MEMBER_REGION(aug),
	m_AUG_iShellOn,
	m_AUG_usFire,
};

enum CSmokeGrenade_Members
{
	m_SmokeGrenade_usCreate = BEGIN_MEMBER_REGION(smokegrenade),
};

enum CELITE_Members
{
	m_ELITE_iShell = BEGIN_MEMBER_REGION(elite),
	m_ELITE_usFire_LEFT,
	m_ELITE_usFire_RIGHT,
};

enum CFiveSeven_Members
{
	m_FiveSeven_iShell = BEGIN_MEMBER_REGION(fiveseven),
	m_FiveSeven_usFire,
};

enum CUMP45_Members
{
	m_UMP45_iShell = BEGIN_MEMBER_REGION(ump45),
	m_UMP45_iShellOn,
	m_UMP45_usFire,
};

enum CSG550_Members
{
	m_SG550_iShell = BEGIN_MEMBER_REGION(sg550),
	m_SG550_usFire,
};

enum CGalil_Members
{
	m_Galil_iShell = BEGIN_MEMBER_REGION(galil),
	m_Galil_iShellOn,
	m_Galil_usFire,
};

enum CFamas_Members
{
	m_Famas_iShell = BEGIN_MEMBER_REGION(famas),
	m_Famas_iShellOn,
	m_Famas_flBaseDamageBurst,
};

enum CUSP_Members
{
	m_USP_iShell = BEGIN_MEMBER_REGION(usp),
	m_USP_usFire,
	m_USP_flBaseDamageSil,
};

enum CGLOCK18_Members
{
	m_GLOCK18_iShell = BEGIN_MEMBER_REGION(glock18),
	m_GLOCK18_bBurstFire,
};

enum CAWP_Members
{
	m_AWP_iShell = BEGIN_MEMBER_REGION(awp),
	m_AWP_usFire,
};

enum CMP5N_Members
{
	m_MP5N_iShell = BEGIN_MEMBER_REGION(mp5n),
	m_MP5N_iShellOn,
	m_MP5N_usFire,
};

enum CM249_Members
{
	m_M249_iShell = BEGIN_MEMBER_REGION(m249),
	m_M249_iShellOn,
	m_M249_usFire,
};

enum CM3_Members
{
	m_M3_iShell = BEGIN_MEMBER_REGION(m3),
	m_M3_flPumpTime,
	m_M3_usFire,
};

enum CM4A1_Members
{
	m_M4A1_iShell = BEGIN_MEMBER_REGION(m4a1),
	m_M4A1_iShellOn,
	m_M4A1_usFire,
	m_M4A1_flBaseDamageSil,
};

enum CTMP_Members
{
	m_TMP_iShell = BEGIN_MEMBER_REGION(tmp),
	m_TMP_iShellOn,
	m_TMP_usFire,
};

enum CG3SG1_Members
{
	m_G3SG1_iShell = BEGIN_MEMBER_REGION(g3sg1),
	m_G3SG1_usFire,
};

enum CDEAGLE_Members
{
	m_DEAGLE_iShell = BEGIN_MEMBER_REGION(deagle),
	m_DEAGLE_usFire,
};

enum CSG552_Members
{
	m_SG552_iShell = BEGIN_MEMBER_REGION(sg552),
	m_SG552_iShellOn,
	m_SG552_usFire,
};

enum CAK47_Members
{
	m_AK47_iShell = BEGIN_MEMBER_REGION(ak47),
	m_AK47_iShellOn,
	m_AK47_usFire,
};

enum CKnife_Members
{
	m_Knife_trHit = BEGIN_MEMBER_REGION(knife),
	m_Knife_usKnife,
	m_Knife_flStabBaseDamage,
	m_Knife_flSwingBaseDamage,
	m_Knife_flSwingBaseDamage_Fast,
	m_Knife_flStabDistance,
	m_Knife_flSwingDistance,
	m_Knife_flBackStabMultiplier,
};

enum CP90_Members
{
	m_P90_iShell = BEGIN_MEMBER_REGION(p90),
	m_P90_iShellOn,
	m_P90_usFire,
};

enum CShield_Members
{
	m_Shield_hEntToIgnoreTouchesFrom = BEGIN_MEMBER_REGION(shield),
	m_Shield_flTimeToIgnoreTouches,
};

enum RebuyStruct_Members
{
	m_primaryWeapon = BEGIN_MEMBER_REGION(rebuystruct),
	m_primaryAmmo,
	m_secondaryWeapon,
	m_secondaryAmmo,
	m_heGrenade,
	m_flashbang,
	m_smokeGrenade,
	m_defuser,
	m_nightVision,
	m_armor,
};

enum MapInfo_Members
{
	m_MapInfo_iBuyingStatus = BEGIN_MEMBER_REGION(mapinfo),
	m_MapInfo_flBombRadius,
};

enum CSPlayerWeapon_Members
{
	m_Weapon_iStateSecondaryAttack = BEGIN_MEMBER_REGION(csplayerweapon),
	m_Weapon_flBaseDamage,
};

enum CGib_Members
{
	m_Gib_bloodColor = BEGIN_MEMBER_REGION(gib),
	m_Gib_cBloodDecals,
	m_Gib_material,
	m_Gib_lifeTime,
};

enum CSEntity_Members
{
	m_ucDmgPenetrationLevel = BEGIN_MEMBER_REGION(csentity),
	m_pevLastInflictor,
};
