#if defined _reapi_gamedll_const_included
	#endinput
#endif

#define _reapi_gamedll_const_included

// flags for CUnifiedSignals m_signals
#define SIGNAL_BUY		(1<<0)
#define SIGNAL_BOMB		(1<<1)
#define SIGNAL_RESCUE		(1<<2)
#define SIGNAL_ESCAPE		(1<<3)
#define SIGNAL_VIPSAFETY	(1<<4)

enum WinStatus
{
	WINSTATUS_CTS = 1,
	WINSTATUS_TERRORISTS,
	WINSTATUS_DRAW,
};

// used for EndRoundMessage() logged messages
enum ScenarionEventEndRound
{
	ROUND_NONE,
	ROUND_TARGET_BOMB,
	ROUND_VIP_ESCAPED,
	ROUND_VIP_ASSASSINATED,
	ROUND_TERRORISTS_ESCAPED,
	ROUND_CTS_PREVENT_ESCAPE,
	ROUND_ESCAPING_TERRORISTS_NEUTRALIZED,
	ROUND_BOMB_DEFUSED,
	ROUND_CTS_WIN,
	ROUND_TERRORISTS_WIN,
	ROUND_END_DRAW,
	ROUND_ALL_HOSTAGES_RESCUED,
	ROUND_TARGET_SAVED,
	ROUND_HOSTAGE_NOT_RESCUED,
	ROUND_TERRORISTS_NOT_ESCAPED,
	ROUND_VIP_NOT_ESCAPED,
	ROUND_GAME_COMMENCE,
};

enum PLAYER_ANIM
{
	PLAYER_IDLE,
	PLAYER_WALK,
	PLAYER_JUMP,
	PLAYER_SUPERJUMP,
	PLAYER_DIE,
	PLAYER_ATTACK1,
	PLAYER_ATTACK2,
	PLAYER_FLINCH,
	PLAYER_LARGE_FLINCH,
	PLAYER_RELOAD,
	PLAYER_HOLDBOMB
};

enum GamedllFunc
{
	/**
	 * Description:		-
	 * Return type:		int
	 * Params:		(const pObserver)
	 */
	RG_GetForceCamera = 1024,

	/**
	 * Description:		-
	 * Params:		(const index, const inflictor, const attacker, const Float:fadeTime, const Float:fadeHold, const alpha, Float:color[3])
	 */
	RG_PlayerBlind,

	/**
	 * Description:		-
	 * Params:		(const index, inflictor, attacker, Float:vecSrc[3], Float:vecSpot[3], tracehandle)
	 */
	RG_RadiusFlash_TraceLine,

	/**
	 * Description:		-
	 * Params:		(WinStatus:status, ScenarionEventEndRound:event, Float:tmDelay)
	 */
	RG_RoundEnd,

	// [...]
	RG_End
};

enum GamedllFunc_CBaseAnimating
{
	/**
	 * Description:		-
	 * Params:		(const this)
	 */
	RG_CBaseAnimating_ResetSequenceInfo = 2048,

	// [...]
	RG_CBaseAnimating_End
};

enum GamedllFunc_CBasePlayer
{
	/**
	 * Description:		-
	 * Params:		(const this)
	 */
	RG_CBasePlayer_Spawn = 3072,

	/**
	 * Description:		-
	 * Params:		(const this)
	 */
	RG_CBasePlayer_Precache,

	/**
	 * Description:		-
	 * Return type:		int
	 * Params:		(const this)
	 */
	RG_CBasePlayer_ObjectCaps,


	/**
	 * Description:		-
	 * Return type:		int
	 * Params:		(const this)
	 */
	RG_CBasePlayer_Classify,

	/**
	 * Description:		-
	 * Params:		(const this, pevAttacker, Float:flDamage, Float:vecDir[3], tracehandle, bitsDamageType)
	 */
	RG_CBasePlayer_TraceAttack,

	/**
	 * Description:		-
	 * Return type:		int
	 * Params:		(const this, pevInflictor, pevAttacker, Float:flDamage, bitsDamageType)
	 */
	RG_CBasePlayer_TakeDamage,

	/**
	 * Description:		-
	 * Params:		(const this, Float:flHealth, bitsDamageType)
	 */
	RG_CBasePlayer_TakeHealth,

	/**
	 * Description:		-
	 * Params:		(const this, pevAttacker, iGib)
	 */
	RG_CBasePlayer_Killed,

	/**
	 * Description:		-
	 * Params:		(const this, score, bAllowNegativeScore)
	 */
	RG_CBasePlayer_AddPoints,

	/**
	 * Description:		-
	 * Params:		(const this, score, bAllowNegativeScore)
	 */
	RG_CBasePlayer_AddPointsToTeam,

	/**
	 * Description:		-
	 * Return type:		BOOL
	 * Params:		(const this, const pItem)
	 */
	RG_CBasePlayer_AddPlayerItem,

	/**
	 * Description:		-
	 * Return type:		BOOL
	 * Params:		(const this, const pItem)
	 */
	RG_CBasePlayer_RemovePlayerItem,

	/**
	 * Description:		-
	 * Return type:		int
	 * Params:		(const this, iAmount, szName[], iMax)
	 */
	RG_CBasePlayer_GiveAmmo,

	/**
	 * Description:		-
	 * Params:		(const this)
	 */
	RG_CBasePlayer_ResetMaxSpeed,

	/**
	 * Description:		-
	 * Params:		(const this)
	 */
	RG_CBasePlayer_Jump,

	/**
	 * Description:		-
	 * Params:		(const this)
	 */
	RG_CBasePlayer_Duck,

	/**
	 * Description:		-
	 * Params:		(const this)
	 */
	RG_CBasePlayer_PreThink,

	/**
	 * Description:		-
	 * Params:		(const this)
	 */
	RG_CBasePlayer_PostThink,

	/**
	 * Description:		-
	 * Params:		(const this)
	 */
	RG_CBasePlayer_UpdateClientData,

	/**
	 * Description:		-
	 * Params:		(const this)
	 */
	RG_CBasePlayer_ImpulseCommands,

	/**
	 * Description:		-
	 * Params:		(const this)
	 */
	RG_CBasePlayer_RoundRespawn,

	/**
	 * Description:		-
	 * Params:		(const this, Float:flUntilTime, Float:flHoldTime, Float:flFadeTime, iAlpha)
	 */
	RG_CBasePlayer_Blind,

	/**
	 * Description:		-
	 * Params:		(const this, iPlayerIndex, bool:bSameTeam)
	 */
	RG_CBasePlayer_Observer_IsValidTarget,

	// [...]
	RG_CBasePlayer_End
};

// CSGameRules
enum CSGameRules_Members
{
	/**
	 * Description:		-
	 * Member type:		BOOL
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_bFreezePeriod = 0,

	/**
	 * Description:		-
	 * Member type:		BOOL
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_bBombDropped,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_msgPlayerVoiceMask,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_msgRequestState,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_nMaxPlayers,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member_game(member);
	 * Set params:		set_member_game(member, Float:value);
	 */
	m_UpdateInterval,

	/**
	 * Description:		The global time when the round is supposed to end, if this is not 0
	 * Member type:		float
	 * Get params:		Float:get_member_game(member);
	 * Set params:		set_member_game(member, Float:value);
	 */
	m_fTeamCount,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member_game(member);
	 * Set params:		set_member_game(member, Float:value);
	 */
	m_flCheckWinConditions,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member_game(member);
	 * Set params:		set_member_game(member, Float:value);
	 */
	m_fRoundCount,

	/**
	 * Description:		How many seconds long this round is.
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iRoundTime,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iRoundTimeSecs,

	/**
	 * Description:		(From mp_freezetime) - How many seconds long the intro round (when players are frozen) is.
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iIntroRoundTime,

	/**
	 * Description:		The global time when the intro round ends
	 * Member type:		float
	 * Get params:		Float:get_member_game(member);
	 * Set params:		set_member_game(member, Float:value);
	 */
	m_fIntroRoundCount,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iAccountTerrorist,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iAccountCT,

	/**
	 * Description:		The number of terrorists on the team (this is generated at the end of a round)
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iNumTerrorist,

	/**
	 * Description:		The number of CTs on the team (this is generated at the end of a round)
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iNumCT,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iNumSpawnableTerrorist,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iNumSpawnableCT,

	/**
	 * Description:		Number of Terrorist spawn points
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iSpawnPointCount_Terrorist,

	/**
	 * Description:		Number of CT spawn points
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iSpawnPointCount_CT,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iHostagesRescued,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iHostagesTouched,

	/**
	 * Description:		1 == CT's won last round, 2 == Terrorists did, 3 == Draw, no winner
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iRoundWinStatus,

	/**
	 * Description:		-
	 * Member type:		short
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iNumCTWins,

	/**
	 * Description:		-
	 * Member type:		short
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iNumTerroristWins,

	/**
	 * Description:		whether or not the bomb has been bombed
	 * Member type:		bool
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, bool:value);
	 */
	m_bTargetBombed,

	/**
	 * Description:		whether or not the bomb has been defused
	 * Member type:		bool
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_bBombDefused,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_bMapHasBombTarget,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_bMapHasBombZone,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_bMapHasBuyZone,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_bMapHasRescueZone,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_bMapHasEscapeZone,

	/**
	 * Description:		0 = uninitialized,   1 = has VIP safety zone,   2 = DOES not have VIP safetyzone
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iMapHasVIPSafetyZone,

	/**
	 * Description:		-
	 * Member type:		BOOL
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_bMapHasCameras,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iC4Timer,

	/**
	 * Description:		The current Terrorist who has the C4.
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iC4Guy,

	/**
	 * Description:		the amount of money the losing team gets. This scales up as they lose more rounds in a row
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iLoserBonus,

	/**
	 * Description:		the number of rounds the CTs have lost in a row.
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iNumConsecutiveCTLoses,

	/**
	 * Description:		the number of rounds the Terrorists have lost in a row.
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iNumConsecutiveTerroristLoses,

	/**
	 * Description:		For the idle kick functionality. This is tha max amount of time that the player has to be idle before being kicked
	 * Member type:		float
	 * Get params:		Float:get_member_game(member);
	 * Set params:		set_member_game(member, Float:value);
	 */
	m_fMaxIdlePeriod,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iLimitTeams,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_bLevelInitialized,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_bRoundTerminating,

	/**
	 * Description:		Set to TRUE to have the scores reset next time round restarts
	 * Member type:		bool
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_bCompleteReset,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member_game(member);
	 * Set params:		set_member_game(member, Float:value);
	 */
	m_flRequiredEscapeRatio,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iNumEscapers,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iHaveEscaped,

	/**
	 * Description:		Who can and can't buy.
	 * Member type:		bool
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_bCTCantBuy,

	/**
	 * Description:		Who can and can't buy.
	 * Member type:		bool
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_bTCantBuy,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member_game(member);
	 * Set params:		set_member_game(member, Float:value);
	 */
	m_flBombRadius,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iConsecutiveVIP,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iTotalGunCount,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iTotalGrenadeCount,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iTotalArmourCount,

	/**
	 * Description:		keeps track of the # of consecutive rounds that have gone by where one team outnumbers the other team by more than 2
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iUnBalancedRounds,

	/**
	 * Description:		keeps track of the # of consecutive rounds of escape played.. Teams will be swapped after 8 rounds
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iNumEscapeRounds,

	/**
	 * Description:		-
	 * Member type:		int [100]
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value, element);
	 */
	m_iMapVotes,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iLastPick,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iMaxMapTime,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iMaxRounds,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iTotalRoundsPlayed,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iMaxRoundsWon,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iStoredSpectValue,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member_game(member);
	 * Set params:		set_member_game(member, Float:value);
	 */
	m_flForceCameraValue,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member_game(member);
	 * Set params:		set_member_game(member, Float:value);
	 */
	m_flForceChaseCamValue,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member_game(member);
	 * Set params:		set_member_game(member, Float:value);
	 */
	m_flFadeToBlackValue,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_pVIP,

	/**
	 * Description:		-
	 * Member type:		int [5]
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value, element);
	 */
	m_pVIPQueue,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member_game(member);
	 * Set params:		set_member_game(member, Float:value);
	 */
	m_flIntermissionEndTime,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member_game(member);
	 * Set params:		set_member_game(member, Float:value);
	 */
	m_flIntermissionStartTime,


	/**
	 * Description:		-
	 * Member type:		BOOL
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iEndIntermissionButtonHit,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member_game(member);
	 * Set params:		set_member_game(member, Float:value);
	 */
	m_tmNextPeriodicThink,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_bFirstConnected,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_bInCareerGame,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member_game(member);
	 * Set params:		set_member_game(member, Float:value);
	 */
	m_fCareerRoundMenuTime,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iCareerMatchWins,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_iRoundWinDifference,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member_game(member);
	 * Set params:		set_member_game(member, Float:value);
	 */
	m_fCareerMatchMenuTime,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member_game(member);
	 * Set params:		set_member_game(member, value);
	 */
	m_bSkipSpawn
};

// CBaseEntity
enum CBaseEntity_Members
{
	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	currentammo = 1024,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	maxammo_buckshot,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	ammo_buckshot,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	maxammo_9mm,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	ammo_9mm,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	maxammo_556nato,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	ammo_556nato,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	maxammo_556natobox,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	ammo_556natobox,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	maxammo_762nato,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	ammo_762nato,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	maxammo_45acp,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	ammo_45acp,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	maxammo_50ae,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	ammo_50ae,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	maxammo_338mag,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	ammo_338mag,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	maxammo_57mm,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	ammo_57mm,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	maxammo_357sig,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	ammo_357sig,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flStartThrow,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flReleaseThrow,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iSwing,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	has_disconnected,
};

// CBaseAnimating
enum CBaseAnimating_Members
{
	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flFrameRate = 2048,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flGroundSpeed,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flLastEventCheck,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_fSequenceFinished,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_fSequenceLoops,
};

// CBasePlayer
enum CBasePlayer_Members
{
	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	random_seed = 3072,

	/**
	 * Description:		-
	 * Member type:		unsigned short
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_usPlayerBleed,

	/**
	 * Description:		-
	 * Member type:		class EHANDLE
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_hObserverTarget,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flNextObserverInput,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iObserverWeapon,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iObserverC4State,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bObserverHasDefuser,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iObserverLastMode,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flFlinchTime,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flAnimTime,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bHighDamage,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flVelocityModifier,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iLastZoom,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bResumeZoom,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flEjectBrass,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iKevlar,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bNotKilled,

	/**
	 * Description:		-
	 * Member type:		enum TeamName
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iTeam,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iAccount,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bHasPrimary,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flDeathThrowTime,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iThrowDirection,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flLastTalk,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bJustConnected,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bContextHelp,

	/**
	 * Description:		-
	 * Member type:		enum JoinState
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iJoiningState,

	/**
	 * Description:		-
	 * Member type:		class CBaseEntity *
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_pIntroCamera,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_fIntroCamTime,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_fLastMovement,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bMissionBriefing,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bTeamChanged,

	/**
	 * Description:		-
	 * Member type:		enum ModelName
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iModelName,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iTeamKills,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iIgnoreGlobalChat,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bHasNightVision,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bNightVisionOn,

	/**
	 * Description:		-
	 * Member type:		class Vector [20]
	 * Get params:		get_member(index, member, Float:output[3], element);
	 * Set params:		set_member(index, member, Float:dest[3], element);
	 */
	m_vRecentPath,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flIdleCheckTime,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flRadioTime,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iRadioMessages,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bIgnoreRadio,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bHasC4,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bHasDefuser,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bKilledByBomb,

	/**
	 * Description:		-
	 * Member type:		class Vector
	 * Get params:		get_member(index, member, Float:output[3]);
	 * Set params:		set_member(index, member, Float:dest[3]);
	 */
	m_vBlastVector,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bKilledByGrenade,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_flDisplayHistory,

	/**
	 * Description:		-
	 * Member type:		enum _Menu
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iMenu,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iChaseTarget,

	/**
	 * Description:		-
	 * Member type:		class CBaseEntity *
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_pChaseTarget,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_fCamSwitch,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bEscaped,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bIsVIP,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_tmNextRadarUpdate,

	/**
	 * Description:		-
	 * Member type:		class Vector
	 * Get params:		get_member(index, member, Float:output[3]);
	 * Set params:		set_member(index, member, Float:dest[3]);
	 */
	m_vLastOrigin,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iCurrentKickVote,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flNextVoteTime,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bJustKilledTeammate,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iHostagesKilled,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iMapVote,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bCanShoot,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flLastFired,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flLastAttackedTeammate,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bHeadshotKilled,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bPunishedForTK,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bReceivesNoMoneyNextRound,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iTimeCheckAllowed,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bHasChangedName,

	/**
	 * Description:		-
	 * Member type:		char [32]
	 * Get params:		get_member(index, member, dest[], const lenght);
	 * Set params:		set_member(index, member, const source[]);
	 */
	m_szNewName,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bIsDefusing,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_tmHandleSignals,

	/**
	 * Description:		-
	 * Member type:		class CUnifiedSignals
	 * Get params:		get_member(index, member, signals[2]); (0 - signal, 1 - state)
	 * Set params:		set_member(index, member, value);
	 */
	m_signals,

	/**
	 * Description:		-
	 * Member type:		struct edict_s *
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_pentCurBombTarget,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iPlayerSound,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iTargetVolume,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iWeaponVolume,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iExtraSoundTypes,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iWeaponFlash,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flStopExtraSoundTime,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flFlashLightTime,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iFlashBattery,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_afButtonLast,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_afButtonPressed,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_afButtonReleased,

	/**
	 * Description:		-
	 * Member type:		struct edict_s *
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_pentSndLast,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flSndRoomtype,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flSndRange,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flFallVelocity,

	/**
	 * Description:		-
	 * Member type:		int [4]
	 * Get params:		get_member(index, member, element);
	 * Set params:		set_member(index, member, value, element);
	 */
	m_rgItems,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_fNewAmmo,

	/**
	 * Description:		-
	 * Member type:		unsigned int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_afPhysicsFlags,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_fNextSuicideTime,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flTimeStepSound,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flTimeWeaponIdle,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flSwimTime,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flDuckTime,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flWallJumpTime,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flSuitUpdate,

	/**
	 * Description:		-
	 * Member type:		int [4]
	 * Get params:		get_member(index, member, element);
	 * Set params:		set_member(index, member, value, element);
	 */
	m_rgSuitPlayList,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iSuitPlayNext,

	/**
	 * Description:		-
	 * Member type:		int [32]
	 * Get params:		get_member(index, member, element);
	 * Set params:		set_member(index, member, value, element);
	 */
	m_rgiSuitNoRepeat,

	/**
	 * Description:		-
	 * Member type:		float [32]
	 * Get params:		Float:get_member(index, member, element);
	 * Set params:		set_member(index, member, Float:value, element);
	 */
	m_rgflSuitNoRepeatTime,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_lastDamageAmount,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_tbdPrev,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flgeigerRange,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flgeigerDelay,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_igeigerRangePrev,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iStepLeft,

	/**
	 * Description:		-
	 * Member type:		char [17]
	 * Get params:		get_member(index, member, dest[], const lenght);
	 * Set params:		set_member(index, member, const source[]);
	 */
	m_szTextureName,

	/**
	 * Description:		-
	 * Member type:		char
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_chTextureType,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_idrowndmg,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_idrownrestored,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bitsHUDDamage,

	/**
	 * Description:		-
	 * Member type:		BOOL
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_fInitHUD,

	/**
	 * Description:		-
	 * Member type:		BOOL
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_fGameHUDInitialized,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iTrain,

	/**
	 * Description:		-
	 * Member type:		BOOL
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_fWeapon,

	/**
	 * Description:		-
	 * Member type:		class EHANDLE
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_pTank,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_fDeadTime,

	/**
	 * Description:		-
	 * Member type:		BOOL
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_fNoPlayerSound,

	/**
	 * Description:		-
	 * Member type:		BOOL
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_fLongJump,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_tSneaking,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iUpdateTime,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iClientHealth,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iClientBattery,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iHideHUD,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iClientHideHUD,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iFOV,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iClientFOV,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iNumSpawns,

	/**
	 * Description:		-
	 * Member type:		class CBaseEntity *
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_pObserver,

	/**
	 * Description:		-
	 * Member type:		class CBasePlayerItem *[6]
	 * Get params:		get_member(index, member, element);
	 * Set params:		set_member(index, member, value, element);
	 */
	m_rgpPlayerItems,

	/**
	 * Description:		-
	 * Member type:		class CBasePlayerItem *
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_pActiveItem,

	/**
	 * Description:		-
	 * Member type:		class CBasePlayerItem *
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_pClientActiveItem,

	/**
	 * Description:		-
	 * Member type:		class CBasePlayerItem *
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_pLastItem,

	/**
	 * Description:		-
	 * Member type:		int [32]
	 * Get params:		get_member(index, member, element);
	 * Set params:		set_member(index, member, value, element);
	 */
	m_rgAmmo,

	/**
	 * Description:		-
	 * Member type:		int [32]
	 * Get params:		get_member(index, member, element);
	 * Set params:		set_member(index, member, value, element);
	 */
	m_rgAmmoLast,

	/**
	 * Description:		-
	 * Member type:		class Vector
	 * Get params:		get_member(index, member, element);
	 * Set params:		set_member(index, member, value, element);
	 */
	m_vecAutoAim,

	/**
	 * Description:		-
	 * Member type:		BOOL
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_fOnTarget,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iDeaths,

	/**
	 * Description:		-
	 * Member type:		int [4]
	 * Get params:		get_member(index, member, element);
	 * Set params:		set_member(index, member, value, element);
	 */
	m_izSBarState,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flNextSBarUpdateTime,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flStatusBarDisappearDelay,

	/**
	 * Description:		-
	 * Member type:		char [128]
	 * Get params:		get_member(index, member, dest[], const lenght);
	 * Set params:		set_member(index, member, const source[]);
	 */
	m_SbarString0,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_lastx,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_lasty,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_nCustomSprayFrames,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flNextDecalTime,

	/**
	 * Description:		-
	 * Member type:		char [16]
	 * Get params:		get_member(index, member, dest[], const lenght);
	 * Set params:		set_member(index, member, const source[]);
	 */
	m_szTeamName,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_modelIndexPlayer,

	/**
	 * Description:		-
	 * Member type:		char [32]
	 * Get params:		get_member(index, member, dest[], const lenght);
	 * Set params:		set_member(index, member, const source[]);
	 */
	m_szAnimExtention,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iGaitsequence,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flGaitframe,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flGaityaw,

	/**
	 * Description:		-
	 * Member type:		class Vector
	 * Get params:		get_member(index, member, element);
	 * Set params:		set_member(index, member, value, element);
	 */
	m_prevgaitorigin,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flPitch,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flYaw,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flGaitMovement,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_iAutoWepSwitch,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bVGUIMenus,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bShowHints,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bShieldDrawn,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bOwnsShield,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bWasFollowing,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flNextFollowTime,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flYawModifier,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_blindUntilTime,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_blindStartTime,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_blindHoldTime,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_blindFadeTime,

	/**
	 * Description:		-
	 * Member type:		int
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_blindAlpha,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_allowAutoFollowTime,

	/**
	 * Description:		-
	 * Member type:		char [256]
	 * Get params:		get_member(index, member, dest[], const lenght);
	 * Set params:		set_member(index, member, const source[]);
	 */
	m_autoBuyString,

	/**
	 * Description:		-
	 * Member type:		char *
	 * Get params:		get_member(index, member, dest[], const lenght);
	 * Set params:		set_member(index, member, const source[]);
	 */
	m_rebuyString,

	/**
	 * Description:		-
	 * Member type:		struct RebuyStruct
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_rebuyStruct,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bIsInRebuy,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_flLastUpdateTime,

	/**
	 * Description:		-
	 * Member type:		char [32]
	 * Get params:		get_member(index, member, dest[], const lenght);
	 * Set params:		set_member(index, member, const source[]);
	 */
	m_lastLocation,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_progressStart,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_progressEnd,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_bObserverAutoDirector,

	/**
	 * Description:		-
	 * Member type:		bool
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_canSwitchObserverModes,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_heartBeatTime,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_intenseTimestamp,

	/**
	 * Description:		-
	 * Member type:		float
	 * Get params:		Float:get_member(index, member);
	 * Set params:		set_member(index, member, Float:value);
	 */
	m_silentTimestamp,

	/**
	 * Description:		-
	 * Member type:		enum MusicState
	 * Get params:		get_member(index, member);
	 * Set params:		set_member(index, member, value);
	 */
	m_musicState,

	/**
	 * Description:		-
	 * Member type:		float [8]
	 * Get params:		Float:get_member(index, member, element);
	 * Set params:		set_member(index, member, Float:value, element);
	 */
	m_flLastCommandTime
};
