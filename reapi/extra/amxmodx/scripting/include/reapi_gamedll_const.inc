#if defined _reapi_gamedll_const_included
	#endinput
#endif

#define _reapi_gamedll_const_included

// Returns 1 if round ended by expired time
// NOTE: Use this for hookchain RG_RoundEnd with the parameter ScenarioEventEndRound:event
#define HadRoundExpired(event)	(1<<_:event) & (1<<_:ROUND_TARGET_SAVED) | (1<<_:ROUND_HOSTAGE_NOT_RESCUED) | (1<<_:ROUND_TERRORISTS_NOT_ESCAPED) | (1<<_:ROUND_VIP_NOT_ESCAPED)

// suppress warning: 200 on amxmodx 1.8.2
#if AMXX_VERSION_NUM < 183
	#define RG_CBaseAnimating_ResetSequenceInfo RG_CBaseAnimating_ResetSequence
	#define RG_CBasePlayer_Observer_IsValidTarget RG_CBasePlayer_Observer_IsValid
	#define RG_CSGameRules_FShouldSwitchWeapon RG_CSGameRules_ShouldSwitchWpn
	#define RG_CSGameRules_GetNextBestWeapon RG_CSGameRules_GetNextBestWpn
	#define RG_CSGameRules_FlPlayerFallDamage RG_CSGameRules_PlayerFallDmg
	#define RG_CSGameRules_FPlayerCanTakeDamage RG_CSGameRules_PlayerCanTakeDmg
	#define RG_CSGameRules_FPlayerCanRespawn RG_CSGameRules_PlayerCanRespawn
	#define RG_CSGameRules_GetPlayerSpawnSpot RG_CSGameRules_PlayerSpawnSpot
	#define RG_CSGameRules_ClientUserInfoChanged RG_CSGameRules_UserInfoChanged
	#define RG_CSGameRules_CanHavePlayerItem RG_CSGameRules_CanPlayerItem
	#define RG_CSGameRules_DeadPlayerWeapons RG_CSGameRules_DeadPlayerWpn
	#define RG_CSGameRules_CheckMapConditions RG_CSGameRules_CheckMapCond
	#define RG_CSGameRules_CheckWinConditions RG_CSGameRules_CheckWinCond
	#define RG_CBasePlayer_SetClientUserInfoModel RG_CBasePlayer_SetUserInfoModel
	#define RG_CBasePlayer_SetClientUserInfoName RG_CBasePlayer_SetUserInfoName
#endif

enum UnifiedSignals
{
	US_Signal,
	US_State
};

enum AccountSet
{
	AS_SET,	// Setts the value of the account
	AS_ADD	// Adds a value to the account
};

// Weapon info types for use with rg_get_weapon_info()
enum WpnInfo
{
	/*
	* Description:		-
	* Return type:		enum WeaponIdType
	* Get params:		rg_get_weapon_info(const weapon_name[], WI_ID);
	* Set params:		-
	*/
	WI_ID,

	/*
	* Description:		-
	* Return type:		int
	* Get params:		rg_get_weapon_info(const weapon_id, WI_COST);
	* Set params:		rg_set_weapon_info(const weapon_id, WI_COST, const value);
	*/
	WI_COST,

	/*
	* Description:		-
	* Return type:		int
	* Get params:		rg_get_weapon_info(const weapon_id, WI_CLIP_COST);
	* Set params:		rg_set_weapon_info(const weapon_id, WI_CLIP_COST, const value);
	*/
	WI_CLIP_COST,

	/*
	* Description:		-
	* Return type:		int
	* Get params:		rg_get_weapon_info(const weapon_id, WI_BUY_CLIP_SIZE);
	* Set params:		-
	*/
	WI_BUY_CLIP_SIZE,

	/*
	* Description:		-
	* Return type:		int
	* Get params:		rg_get_weapon_info(const weapon_id, WI_GUN_CLIP_SIZE);
	* Set params:		-
	*/
	WI_GUN_CLIP_SIZE,

	/*
	* Description:		-
	* Return type:		int
	* Get params:		rg_get_weapon_info(const weapon_id, WI_MAX_ROUNDS);
	* Set params:		-
	*/
	WI_MAX_ROUNDS,

	/*
	* Description:		-
	* Return type:		int
	* Get params:		rg_get_weapon_info(const weapon_id, WI_AMMO_TYPE);
	* Set params:		-
	*/
	WI_AMMO_TYPE,

	/*
	* Description:		-
	* Return type:		-
	* Get params:		rg_get_weapon_info(const weapon_id, WI_AMMO_NAME, const output[], maxlenght);
	* Set params:		-
	*/
	WI_AMMO_NAME,

	/*
	* Description:		-
	* Return type:		-
	* Get params:		rg_get_weapon_info(const weapon_id, WI_NAME, const output[], maxlenght);
	* Set params:		-
	*/
	WI_NAME
};

// Use with rg_give_item
enum GiveType
{
	GT_APPEND,		// Just give item
	GT_REPLACE,		// Give the item and remove all other weapons from the slot
	GT_DROP_AND_REPLACE	// Give the item and drop all other weapons from the slot
};

enum MenuChooseTeam
{
	MenuChoose_T = 1,
	MenuChoose_CT,
	MenuChoose_VIP,

	MenuChoose_AutoSelect = 5,
	MenuChoose_Spec,
};

enum VGUIMenu
{
	VGUI_Menu_Team = 2,
	VGUI_Menu_MapBriefing = 4,

	VGUI_Menu_Class_T = 26,
	VGUI_Menu_Class_CT,
	VGUI_Menu_Buy,
	VGUI_Menu_Buy_Pistol,
	VGUI_Menu_Buy_ShotGun,
	VGUI_Menu_Buy_Rifle,
	VGUI_Menu_Buy_SubMachineGun,
	VGUI_Menu_Buy_MachineGun,
	VGUI_Menu_Buy_Item,
};

enum GamedllFunc
{
	/*
	* Description:		-
	* Return type:		int
	* Params:		(const pObserver)
	*/
	RG_GetForceCamera = BEGIN_FUNC_REGION(gamedll),

	/*
	* Description:		-
	* Params:		(const index, const inflictor, const attacker, const Float:fadeTime, const Float:fadeHold, const alpha, Float:color[3])
	*/
	RG_PlayerBlind,

	/*
	* Description:		-
	* Params:		(const index, inflictor, attacker, Float:vecSrc[3], Float:vecSpot[3], tracehandle)
	*/
	RG_RadiusFlash_TraceLine,

	/*
	* Description:		-
	* Params:		(WinStatus:status, ScenarioEventEndRound:event, Float:tmDelay)
	*/
	RG_RoundEnd,

	/*
	* Description:		-
	* Params:		(const PlayerMove:ppmove, const server)
	*/
	RG_PM_Move,

	/*
	* Description:		-
	* Params:		(const playerIndex)
	*/
	RG_PM_AirMove,

	/*
	* Description:		-
	* Params:		(const index, const slot)
	*/
	RG_HandleMenu_ChooseAppearance,

	/*
	* Description:		-
	* Params:		(const index, const MenuChooseTeam:slot)
	*/
	RG_HandleMenu_ChooseTeam,

	/*
	* Description:		-
	* Params:		(const index, const bitsSlots, const iDisplayTime, const iNeedMore, pszText[])
	*/
	RG_ShowMenu,

	/*
	* Description:		-
	* Params:		(const index, VGUIMenu:menuType, const bitsSlots, szOldMenu[])
	*/
	RG_ShowVGUIMenu,

	/*
	* Description:		The player buys ammo.
	* Return type:		bool
	* Params:		(const index, const weapon_entity, const bool:blinkMoney)
	*/
	RG_BuyGunAmmo,

	/*
	* Description:		-
	* Return type:		CBaseEntity * (Entity index of weapon)
	* Params:		(const index, const WeaponIdType:weaponID)
	*/
	RG_BuyWeaponByWeaponID
};

enum GamedllFunc_CBaseAnimating
{
	/*
	* Description:		-
	* Params:		(const this)
	*/
	RG_CBaseAnimating_ResetSequenceInfo = BEGIN_FUNC_REGION(animating)
};

enum GamedllFunc_CBasePlayer
{
	/*
	* Description:		-
	* Params:		(const this)
	*/
	RG_CBasePlayer_Spawn = BEGIN_FUNC_REGION(player),

	/*
	* Description:		-
	* Params:		(const this)
	*/
	RG_CBasePlayer_Precache,

	/*
	* Description:		-
	* Return type:		int
	* Params:		(const this)
	*/
	RG_CBasePlayer_ObjectCaps,

	/*
	* Description:		-
	* Return type:		int
	* Params:		(const this)
	*/
	RG_CBasePlayer_Classify,

	/*
	* Description:		-
	* Params:		(const this, pevAttacker, Float:flDamage, Float:vecDir[3], tracehandle, bitsDamageType)
	*/
	RG_CBasePlayer_TraceAttack,

	/*
	* Description:		-
	* Return type:		int
	* Params:		(const this, pevInflictor, pevAttacker, Float:flDamage, bitsDamageType)
	*/
	RG_CBasePlayer_TakeDamage,

	/*
	* Description:		-
	* Params:		(const this, Float:flHealth, bitsDamageType)
	*/
	RG_CBasePlayer_TakeHealth,

	/*
	* Description:		-
	* Params:		(const this, pevAttacker, iGib)
	*/
	RG_CBasePlayer_Killed,

	/*
	* Description:		-
	* Params:		(const this, score, bAllowNegativeScore)
	*/
	RG_CBasePlayer_AddPoints,

	/*
	* Description:		-
	* Params:		(const this, score, bAllowNegativeScore)
	*/
	RG_CBasePlayer_AddPointsToTeam,

	/*
	* Description:		-
	* Return type:		BOOL
	* Params:		(const this, const pItem)
	*/
	RG_CBasePlayer_AddPlayerItem,

	/*
	* Description:		-
	* Return type:		BOOL
	* Params:		(const this, const pItem)
	*/
	RG_CBasePlayer_RemovePlayerItem,

	/*
	* Description:		-
	* Return type:		int
	* Params:		(const this, iAmount, szName[], iMax)
	*/
	RG_CBasePlayer_GiveAmmo,

	/*
	* Description:		-
	* Params:		(const this)
	*/
	RG_CBasePlayer_ResetMaxSpeed,

	/*
	* Description:		-
	* Params:		(const this)
	*/
	RG_CBasePlayer_Jump,

	/*
	* Description:		-
	* Params:		(const this)
	*/
	RG_CBasePlayer_Duck,

	/*
	* Description:		-
	* Params:		(const this)
	*/
	RG_CBasePlayer_PreThink,

	/*
	* Description:		-
	* Params:		(const this)
	*/
	RG_CBasePlayer_PostThink,

	/*
	* Description:		-
	* Params:		(const this)
	*/
	RG_CBasePlayer_UpdateClientData,

	/*
	* Description:		-
	* Params:		(const this)
	*/
	RG_CBasePlayer_ImpulseCommands,

	/*
	* Description:		-
	* Params:		(const this)
	*/
	RG_CBasePlayer_RoundRespawn,

	/*
	* Description:		-
	* Params:		(const this, Float:flUntilTime, Float:flHoldTime, Float:flFadeTime, iAlpha)
	*/
	RG_CBasePlayer_Blind,

	/*
	* Description:		-
	* Params:		(const this, infobuffer[], szNewModel[])
	*/
	RG_CBasePlayer_SetClientUserInfoModel,

	/*
	* Description:		-
	* Params:		(const this, infobuffer[], szNewName[])
	*/
	RG_CBasePlayer_SetClientUserInfoName,

	/*
	* Description:		-
	* Params:		(const this, iPlayerIndex, bool:bSameTeam)
	*/
	RG_CBasePlayer_Observer_IsValidTarget,

	/*
	* Description:		-
	* Params:		(const this, PLAYER_ANIM:playerAnim)
	*/
	RG_CBasePlayer_SetAnimation,

	/*
	* Description:		-
	* Params:		(const this)
	*/
	RG_CBasePlayer_GiveDefaultItems,

	/*
	* Description:		-
	* Return type:		CBaseEntity * (Entity index of item)
	* Params:		(const this, const pszName[])
	*/
	RG_CBasePlayer_GiveNamedItem,

	/*
	* Description:		-
	* Params:		(const this, amount, RewardType:type, bool:bTrackChange)
	*/
	RG_CBasePlayer_AddAccount,

	/*
	* Description:		-
	* Params:		(const this, bool:bDeploy)
	*/
	RG_CBasePlayer_GiveShield,

	/*
	* Description:		-
	* Params:		(const this, const pszItemName[])
	*/
	RG_CBasePlayer_DropPlayerItem,

	/*
	* Description:		-
	* Params:		(const this, ItemID:item, ItemRestType:type)
	*/
	RG_CBasePlayer_HasRestrictItem,

	/*
	* Description:		Called when a player throws the shield on the ground.
	* Params:		(const this, bool:deploy)
	*/
	RG_CBasePlayer_DropShield,

	/*
	* Description:		Called on spawn, the attempt to equip a player.
	* Params:		(const this, bool addDefault, bool equipGame)
	*/
	RG_CBasePlayer_OnSpawnEquip,

	/*
	* Description:		The player uses a radio message.
	*			Called on self-radio uses, throwing grenades or on freeze time end.
	* Params:		(const this, const msg_id[], const msg_verbose[], pitch, bool:showIcon)
	*/
	RG_CBasePlayer_Radio,

	/*
	* Description:		VIP player got to the point of rescue.
	* Params:		(const this)
	*/
	RG_CBasePlayer_Disappear,

	/*
	* Description:		Makes a random player the VIP.
	* Params:		(const this)
	*/
	RG_CBasePlayer_MakeVIP,

	/*
	* Description:		Makes a random player the bomber.
	* Return type:		bool
	* Params:		(const this)
	*/
	RG_CBasePlayer_MakeBomber,

	/*
	* Description:		The player goes into observer mode.
	* Params:		(const this, Float:vecPosition[3], Float:vecViewAngle[3])
	*/
	RG_CBasePlayer_StartObserver,

	/*
	* Description:		Called when a player enters the game.
	* Return type:		bool
	* Params:		(const this)
	*/
	RG_CBasePlayer_GetIntoGame

};

enum GamedllFunc_CSGameRules
{
	/*
	* Description:		Should the player switch to this weapon?
	* Params:		(const index, const weapon)
	*/
	RG_CSGameRules_FShouldSwitchWeapon = BEGIN_FUNC_REGION(gamerules),

	/*
	* Description:		I can't use this weapon anymore, get me the next best one.
	* Params:		(const index, const currentWeapon)
	*/
	RG_CSGameRules_GetNextBestWeapon,

	/*
	* Description:		-
	* Params:		(const index)
	*/
	RG_CSGameRules_FlPlayerFallDamage,

	/*
	* Description:		Can this player take damage from this attacker?
	* Params:		(const index, const attacker)
	*/
	RG_CSGameRules_FPlayerCanTakeDamage,

	/*
	* Description:		Called by CBasePlayer::Spawn just before releasing the player into the game.
	* Params:		(const index)
	*/
	RG_CSGameRules_PlayerSpawn,

	/*
	* Description:		Is this player allowed to respawn now?
	* Params:		(const index)
	*/
	RG_CSGameRules_FPlayerCanRespawn,

	/*
	* Description:		Place this player on his spawnspot and face him in the proper direction.
	* Params:		(const index)
	*/
	RG_CSGameRules_GetPlayerSpawnSpot,

	/*
	* Description:		The player has changed userinfo; can change it now.
	* Params:		(const index, infobuffer[])
	*/
	RG_CSGameRules_ClientUserInfoChanged,

	/*
	* Description:		Called each time a player dies.
	* Params:		(const victim, const killer, const inflictor)
	*/
	RG_CSGameRules_PlayerKilled,

	/*
	* Description:		Call this from within a GameRules class to report an obituary.
	* Params:		(const victim, const killer, const inflictor)
	*/
	RG_CSGameRules_DeathNotice,

	/*
	* Description:		The player is touching a CBasePlayerItem, do I give it to him?
	* Params:		(const index, const item)
	*/
	RG_CSGameRules_CanHavePlayerItem,

	/*
	* Description:		What do I do with player's weapons when he's killed?
	* Params:		(const index)
	*/
	RG_CSGameRules_DeadPlayerWeapons,

	/*
	* Description:		-
	* Params:		()
	*/
	RG_CSGameRules_ServerDeactivate,

	/*
	* Description:		-
	* Params:		()
	*/
	RG_CSGameRules_CheckMapConditions,

	/*
	* Description:		Recreate all the map entities from the map data (preserving their indices),
	*			then remove everything else except the players.
	*			Also get rid of all world decals.
	* Params:		()
	*/
	RG_CSGameRules_CleanUpMap,

	/*
	* Description:		Call this on a new round or restart round with member m_bCompleteReset is TRUE
	* Params:		()
	*/
	RG_CSGameRules_RestartRound,

	/*
	* Description:		Check if the scenario has been won/lost.
	* Params:		()
	*/
	RG_CSGameRules_CheckWinConditions,

	/*
	* Description:		-
	* Params:		()
	*/
	RG_CSGameRules_RemoveGuns,

	/*
	* Description:		-
	* Params:		()
	*/
	RG_CSGameRules_GiveC4,

	/*
	* Description:		-
	* Params:		()
	*/
	RG_CSGameRules_ChangeLevel,

	/*
	* Description:		-
	* Params:		()
	*/
	RG_CSGameRules_GoToIntermission,

	/*
	* Description:		-
	* Params:		()
	*/
	RG_CSGameRules_BalanceTeams,

	/*
	* Description:		It's called when the freeze time ends.
	* Params:		()
	*/
	RG_CSGameRules_OnRoundFreezeEnd
};

// CSGameRules
enum CSGameRules_Members
{
	/*
	* Description:		-
	* Member type:		BOOL
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bFreezePeriod = BEGIN_MEMBER_REGION(gamerules),

	/*
	* Description:		-
	* Member type:		BOOL
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bBombDropped,

	/*
	* Description:		-
	* Member type:		char *
	* Get params:		get_member_game(member, dest[], const lenght);
	* Set params:		set_member_game(member, const source[]);
	*/
	m_GameDesc,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_msgPlayerVoiceMask,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_msgRequestState,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_nMaxPlayers,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member_game(member);
	* Set params:		set_member_game(member, Float:value);
	*/
	m_UpdateInterval,

	/*
	* Description:		The global time when the round is supposed to end, if this is not 0.
	* Member type:		float
	* Get params:		Float:get_member_game(member);
	* Set params:		set_member_game(member, Float:value);
	*/
	m_flRestartRoundTime,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member_game(member);
	* Set params:		set_member_game(member, Float:value);
	*/
	m_flCheckWinConditions,

	/*
	* Description:		Time round has started.
	* Member type:		float
	* Get params:		Float:get_member_game(member);
	* Set params:		set_member_game(member, Float:value);
	*/
	m_fRoundStartTime,

	/*
	* Description:		How many seconds long this round is.
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iRoundTime,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iRoundTimeSecs,

	/*
	* Description:		(From mp_freezetime) - How many seconds long the intro round (when players are frozen) is.
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iIntroRoundTime,

	/*
	* Description:		The global time when the intro round ends and the real one starts (wrote the original "m_flRoundTime" comment for this variable).
	* Member type:		float
	* Get params:		Float:get_member_game(member);
	* Set params:		set_member_game(member, Float:value);
	*/
	m_fRoundStartTimeReal,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iAccountTerrorist,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iAccountCT,

	/*
	* Description:		The number of terrorists on the team (this is generated at the end of a round).
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iNumTerrorist,

	/*
	* Description:		The number of CTs on the team (this is generated at the end of a round).
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iNumCT,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iNumSpawnableTerrorist,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iNumSpawnableCT,

	/*
	* Description:		Number of Terrorist spawn points.
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iSpawnPointCount_Terrorist,

	/*
	* Description:		Number of CT spawn points.
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iSpawnPointCount_CT,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iHostagesRescued,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iHostagesTouched,

	/*
	* Description:		1 == CTs won last round, 2 == Terrorists did, 3 == Draw, no winner
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iRoundWinStatus,

	/*
	* Description:		-
	* Member type:		short
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iNumCTWins,

	/*
	* Description:		-
	* Member type:		short
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iNumTerroristWins,

	/*
	* Description:		Whether or not the bomb target has been bombed.
	* Member type:		bool
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, bool:value);
	*/
	m_bTargetBombed,

	/*
	* Description:		Whether or not the bomb has been defused.
	* Member type:		bool
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bBombDefused,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bMapHasBombTarget,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bMapHasBombZone,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bMapHasBuyZone,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bMapHasRescueZone,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bMapHasEscapeZone,

	/*
	* Description:		0 = uninitialized, 1 = has VIP safety zone, 2 = DOES not have VIP safetyzone
	* Member type:		qboolean
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bMapHasVIPSafetyZone,

	/*
	* Description:		-
	* Member type:		BOOL
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bMapHasCameras,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iC4Timer,

	/*
	* Description:		The current Terrorist who has the C4.
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iC4Guy,

	/*
	* Description:		The amount of money the losing team gets. This scales up as they lose more rounds in a row.
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iLoserBonus,

	/*
	* Description:		The number of rounds the CTs have lost in a row.
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iNumConsecutiveCTLoses,

	/*
	* Description:		The number of rounds the Terrorists have lost in a row.
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iNumConsecutiveTerroristLoses,

	/*
	* Description:		For the idle kick functionality. This is the max amount of time that the player has to be idle before being kicked.
	* Member type:		float
	* Get params:		Float:get_member_game(member);
	* Set params:		set_member_game(member, Float:value);
	*/
	m_fMaxIdlePeriod,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iLimitTeams,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bLevelInitialized,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bRoundTerminating,

	/*
	* Description:		Set to TRUE to have the scores reset next time round restarts.
	* Member type:		bool
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bCompleteReset,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member_game(member);
	* Set params:		set_member_game(member, Float:value);
	*/
	m_flRequiredEscapeRatio,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iNumEscapers,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iHaveEscaped,

	/*
	* Description:		Who can and can't buy.
	* Member type:		bool
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bCTCantBuy,

	/*
	* Description:		Who can and can't buy.
	* Member type:		bool
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bTCantBuy,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member_game(member);
	* Set params:		set_member_game(member, Float:value);
	*/
	m_flBombRadius,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iConsecutiveVIP,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iTotalGunCount,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iTotalGrenadeCount,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iTotalArmourCount,

	/*
	* Description:		Keeps track of the # of consecutive rounds that have gone by where one team outnumbers the other team by more than 2.
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iUnBalancedRounds,

	/*
	* Description:		Keeps track of the # of consecutive rounds of escape played. Teams will be swapped after 8 rounds.
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iNumEscapeRounds,

	/*
	* Description:		-
	* Member type:		int [100]
	* Get params:		get_member_game(member, element);
	* Set params:		set_member_game(member, value, element);
	*/
	m_iMapVotes,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iLastPick,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iMaxMapTime,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iMaxRounds,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iTotalRoundsPlayed,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iMaxRoundsWon,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iStoredSpectValue,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member_game(member);
	* Set params:		set_member_game(member, Float:value);
	*/
	m_flForceCameraValue,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member_game(member);
	* Set params:		set_member_game(member, Float:value);
	*/
	m_flForceChaseCamValue,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member_game(member);
	* Set params:		set_member_game(member, Float:value);
	*/
	m_flFadeToBlackValue,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_pVIP,

	/*
	* Description:		-
	* Member type:		int [5]
	* Get params:		get_member_game(member, element);
	* Set params:		set_member_game(member, value, element);
	*/
	m_pVIPQueue,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member_game(member);
	* Set params:		set_member_game(member, Float:value);
	*/
	m_flIntermissionEndTime,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member_game(member);
	* Set params:		set_member_game(member, Float:value);
	*/
	m_flIntermissionStartTime,


	/*
	* Description:		-
	* Member type:		BOOL
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iEndIntermissionButtonHit,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member_game(member);
	* Set params:		set_member_game(member, Float:value);
	*/
	m_tmNextPeriodicThink,

	/*
	* Description:		TRUE = the game commencing when there is at least one CT and T, FALSE = scoring will not start until both teams have players (deprecated name m_bFirstConnected)
	* Member type:		bool
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bGameStarted,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bInCareerGame,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member_game(member);
	* Set params:		set_member_game(member, Float:value);
	*/
	m_fCareerRoundMenuTime,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iCareerMatchWins,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_iRoundWinDifference,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member_game(member);
	* Set params:		set_member_game(member, Float:value);
	*/
	m_fCareerMatchMenuTime,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bSkipSpawn,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bSkipShowMenu,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value);
	*/
	m_bNeededPlayers,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member_game(member);
	* Set params:		set_member_game(member, Float:value);
	*/
	m_flEscapeRatio
};

// CBaseEntity
enum CBaseEntity_Members
{
	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	currentammo = BEGIN_MEMBER_REGION(base),

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	maxammo_buckshot,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	ammo_buckshot,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	maxammo_9mm,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	ammo_9mm,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	maxammo_556nato,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	ammo_556nato,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	maxammo_556natobox,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	ammo_556natobox,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	maxammo_762nato,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	ammo_762nato,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	maxammo_45acp,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	ammo_45acp,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	maxammo_50ae,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	ammo_50ae,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	maxammo_338mag,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	ammo_338mag,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	maxammo_57mm,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	ammo_57mm,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	maxammo_357sig,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	ammo_357sig,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flStartThrow,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flReleaseThrow,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iSwing,

	/*
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
	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flFrameRate = BEGIN_MEMBER_REGION(animating),

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flGroundSpeed,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flLastEventCheck,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_fSequenceFinished,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_fSequenceLoops,
};

// CBaseMonster
enum CBaseMonster_Members
{
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Activity = BEGIN_MEMBER_REGION(basemonster),

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_IdealActivity,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_LastHitGroup,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bitsDamageType,

	/*
	* Description:		-
	* Member type:		usigned char [5]
	* Get params:		get_member_game(member);
	* Set params:		set_member_game(member, value, element);
	*/
	m_rgbTimeBasedDamage,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_MonsterState,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_IdealMonsterState,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_afConditions,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_afMemory,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flNextAttack,

	/*
	* Description:		-
	* Member type:		class EHANDLE
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_hEnemy,

	/*
	* Description:		-
	* Member type:		class EHANDLE
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_hTargetEnt,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flFieldOfView,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bloodColor,

	/*
	* Description:		-
	* Member type:		class Vector
	* Get params:		get_member(index, member, Float:output[3]);
	* Set params:		set_member(index, member, Float:dest[3]);
	*/
	m_HackedGunPos,

	/*
	* Description:		-
	* Member type:		class Vector
	* Get params:		get_member(index, member, Float:output[3]);
	* Set params:		set_member(index, member, Float:dest[3]);
	*/
	m_vecEnemyLKP,
};

// CBasePlayer
enum CBasePlayer_Members
{
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	random_seed = BEGIN_MEMBER_REGION(player),

	/*
	* Description:		-
	* Member type:		unsigned short
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_usPlayerBleed,

	/*
	* Description:		-
	* Member type:		class EHANDLE
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_hObserverTarget,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flNextObserverInput,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iObserverWeapon,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iObserverC4State,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bObserverHasDefuser,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iObserverLastMode,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flFlinchTime,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flAnimTime,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bHighDamage,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flVelocityModifier,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iLastZoom,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bResumeZoom,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flEjectBrass,

	/*
	* Description:		-
	* Member type:		enum ArmorType
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iKevlar,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bNotKilled,

	/*
	* Description:		-
	* Member type:		enum TeamName
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iTeam,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iAccount,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bHasPrimary,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flDeathThrowTime,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iThrowDirection,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flLastTalk,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bJustConnected,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bContextHelp,

	/*
	* Description:		-
	* Member type:		enum JoinState
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iJoiningState,

	/*
	* Description:		-
	* Member type:		class CBaseEntity *
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_pIntroCamera,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_fIntroCamTime,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_fLastMovement,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bMissionBriefing,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bTeamChanged,

	/*
	* Description:		-
	* Member type:		enum ModelName
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iModelName,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iTeamKills,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iIgnoreGlobalChat,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bHasNightVision,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bNightVisionOn,

	/*
	* Description:		-
	* Member type:		class Vector [20]
	* Get params:		get_member(index, member, Float:output[3], element);
	* Set params:		set_member(index, member, Float:dest[3], element);
	*/
	m_vRecentPath,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flIdleCheckTime,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flRadioTime,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iRadioMessages,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bIgnoreRadio,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bHasC4,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bHasDefuser,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bKilledByBomb,

	/*
	* Description:		-
	* Member type:		class Vector
	* Get params:		get_member(index, member, Float:output[3]);
	* Set params:		set_member(index, member, Float:dest[3]);
	*/
	m_vBlastVector,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bKilledByGrenade,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_flDisplayHistory,

	/*
	* Description:		-
	* Member type:		enum _Menu
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iMenu,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iChaseTarget,

	/*
	* Description:		-
	* Member type:		class CBaseEntity *
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_pChaseTarget,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_fCamSwitch,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bEscaped,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bIsVIP,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_tmNextRadarUpdate,

	/*
	* Description:		-
	* Member type:		class Vector
	* Get params:		get_member(index, member, Float:output[3]);
	* Set params:		set_member(index, member, Float:dest[3]);
	*/
	m_vLastOrigin,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iCurrentKickVote,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flNextVoteTime,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bJustKilledTeammate,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iHostagesKilled,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iMapVote,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bCanShoot,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flLastFired,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flLastAttackedTeammate,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bHeadshotKilled,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bPunishedForTK,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bReceivesNoMoneyNextRound,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iTimeCheckAllowed,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bHasChangedName,

	/*
	* Description:		-
	* Member type:		char [32]
	* Get params:		get_member(index, member, dest[], const lenght);
	* Set params:		set_member(index, member, const source[]);
	*/
	m_szNewName,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bIsDefusing,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_tmHandleSignals,

	/*
	* Description:		(0 - signal, 1 - state)
	* Member type:		class CUnifiedSignals
	* Get params:		get_member(index, member, signals[UnifiedSignals]);
	* Set params:		set_member(index, member, signals[UnifiedSignals]);
	*/
	m_signals,

	/*
	* Description:		-
	* Member type:		struct edict_s *
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_pentCurBombTarget,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iPlayerSound,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iTargetVolume,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iWeaponVolume,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iExtraSoundTypes,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iWeaponFlash,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flStopExtraSoundTime,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flFlashLightTime,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iFlashBattery,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_afButtonLast,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_afButtonPressed,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_afButtonReleased,

	/*
	* Description:		-
	* Member type:		struct edict_s *
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_pentSndLast,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flSndRoomtype,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flSndRange,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flFallVelocity,

	/*
	* Description:		-
	* Member type:		int [4]
	* Get params:		get_member(index, member, element);
	* Set params:		set_member(index, member, value, element);
	*/
	m_rgItems,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_fNewAmmo,

	/*
	* Description:		-
	* Member type:		unsigned int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_afPhysicsFlags,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_fNextSuicideTime,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flTimeStepSound,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flTimeWeaponIdle,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flSwimTime,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flDuckTime,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flWallJumpTime,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flSuitUpdate,

	/*
	* Description:		-
	* Member type:		int [4]
	* Get params:		get_member(index, member, element);
	* Set params:		set_member(index, member, value, element);
	*/
	m_rgSuitPlayList,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iSuitPlayNext,

	/*
	* Description:		-
	* Member type:		int [32]
	* Get params:		get_member(index, member, element);
	* Set params:		set_member(index, member, value, element);
	*/
	m_rgiSuitNoRepeat,

	/*
	* Description:		-
	* Member type:		float [32]
	* Get params:		Float:get_member(index, member, element);
	* Set params:		set_member(index, member, Float:value, element);
	*/
	m_rgflSuitNoRepeatTime,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_lastDamageAmount,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_tbdPrev,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flgeigerRange,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flgeigerDelay,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_igeigerRangePrev,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iStepLeft,

	/*
	* Description:		-
	* Member type:		char [17]
	* Get params:		get_member(index, member, dest[], const lenght);
	* Set params:		set_member(index, member, const source[]);
	*/
	m_szTextureName,

	/*
	* Description:		-
	* Member type:		char
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_chTextureType,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_idrowndmg,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_idrownrestored,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bitsHUDDamage,

	/*
	* Description:		-
	* Member type:		BOOL
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_fInitHUD,

	/*
	* Description:		-
	* Member type:		BOOL
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_fGameHUDInitialized,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iTrain,

	/*
	* Description:		-
	* Member type:		BOOL
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_fWeapon,

	/*
	* Description:		-
	* Member type:		class EHANDLE
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_pTank,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_fDeadTime,

	/*
	* Description:		-
	* Member type:		BOOL
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_fNoPlayerSound,

	/*
	* Description:		-
	* Member type:		BOOL
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_fLongJump,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_tSneaking,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iUpdateTime,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iClientHealth,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iClientBattery,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iHideHUD,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iClientHideHUD,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iFOV,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iClientFOV,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iNumSpawns,

	/*
	* Description:		-
	* Member type:		class CBaseEntity *
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_pObserver,

	/*
	* Description:		-
	* Member type:		class CBasePlayerItem *[6]
	* Get params:		get_member(index, member, element);
	* Set params:		set_member(index, member, value, element);
	*/
	m_rgpPlayerItems,

	/*
	* Description:		-
	* Member type:		class CBasePlayerItem *
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_pActiveItem,

	/*
	* Description:		-
	* Member type:		class CBasePlayerItem *
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_pClientActiveItem,

	/*
	* Description:		-
	* Member type:		class CBasePlayerItem *
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_pLastItem,

	/*
	* Description:		-
	* Member type:		int [32]
	* Get params:		get_member(index, member, element);
	* Set params:		set_member(index, member, value, element);
	*/
	m_rgAmmo,

	/*
	* Description:		-
	* Member type:		int [32]
	* Get params:		get_member(index, member, element);
	* Set params:		set_member(index, member, value, element);
	*/
	m_rgAmmoLast,

	/*
	* Description:		-
	* Member type:		class Vector
	* Get params:		get_member(index, member, element);
	* Set params:		set_member(index, member, value, element);
	*/
	m_vecAutoAim,

	/*
	* Description:		-
	* Member type:		BOOL
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_fOnTarget,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iDeaths,

	/*
	* Description:		-
	* Member type:		int [4]
	* Get params:		get_member(index, member, element);
	* Set params:		set_member(index, member, value, element);
	*/
	m_izSBarState,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flNextSBarUpdateTime,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flStatusBarDisappearDelay,

	/*
	* Description:		-
	* Member type:		char [128]
	* Get params:		get_member(index, member, dest[], const lenght);
	* Set params:		set_member(index, member, const source[]);
	*/
	m_SbarString0,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_lastx,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_lasty,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_nCustomSprayFrames,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flNextDecalTime,

	/*
	* Description:		-
	* Member type:		char [16]
	* Get params:		get_member(index, member, dest[], const lenght);
	* Set params:		set_member(index, member, const source[]);
	*/
	m_szTeamName,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_modelIndexPlayer,

	/*
	* Description:		-
	* Member type:		char [32]
	* Get params:		get_member(index, member, dest[], const lenght);
	* Set params:		set_member(index, member, const source[]);
	*/
	m_szAnimExtention,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iGaitsequence,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flGaitframe,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flGaityaw,

	/*
	* Description:		-
	* Member type:		class Vector
	* Get params:		get_member(index, member, element);
	* Set params:		set_member(index, member, value, element);
	*/
	m_prevgaitorigin,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flPitch,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flYaw,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flGaitMovement,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iAutoWepSwitch,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bVGUIMenus,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bShowHints,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bShieldDrawn,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bOwnsShield,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bWasFollowing,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flNextFollowTime,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flYawModifier,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_blindUntilTime,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_blindStartTime,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_blindHoldTime,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_blindFadeTime,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_blindAlpha,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_allowAutoFollowTime,

	/*
	* Description:		-
	* Member type:		char [256]
	* Get params:		get_member(index, member, dest[], const lenght);
	* Set params:		set_member(index, member, const source[]);
	*/
	m_autoBuyString,

	/*
	* Description:		-
	* Member type:		char *
	* Get params:		get_member(index, member, dest[], const lenght);
	* Set params:		set_member(index, member, const source[]);
	*/
	m_rebuyString,

	/*
	* Description:		-
	* Member type:		struct RebuyStruct
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_rebuyStruct,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bIsInRebuy,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_flLastUpdateTime,

	/*
	* Description:		-
	* Member type:		char [32]
	* Get params:		get_member(index, member, dest[], const lenght);
	* Set params:		set_member(index, member, const source[]);
	*/
	m_lastLocation,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_progressStart,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_progressEnd,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bObserverAutoDirector,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_canSwitchObserverModes,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_heartBeatTime,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_intenseTimestamp,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_silentTimestamp,

	/*
	* Description:		-
	* Member type:		enum MusicState
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_musicState,

	/*
	* Description:		-
	* Member type:		float [8]
	* Get params:		Float:get_member(index, member, element);
	* Set params:		set_member(index, member, Float:value, element);
	*/
	m_flLastCommandTime
};

enum PlayerMove
{
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_player_index = BEGIN_MEMBER_REGION(playermove),

	/*
	* Description:		-
	* Member type:		qboolean
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_server,

	/*
	* Description:		-
	* Member type:		qboolean
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_multiplayer,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_pmove(const MoveVars:var);
	* Set params:		set_pmove(const MoveVars:var, Float:value);
	*/
	pm_time,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_pmove(const MoveVars:var);
	* Set params:		set_pmove(const MoveVars:var, Float:value);
	*/
	pm_frametime,

	/*
	* Description:		-
	* Member type:		vec3_t
	* Get params:		get_pmove(const PlayerMove:var, Float:output[3]);
	* Set params:		set_pmove(const PlayerMove:var, Float:dest[3]);
	*/
	pm_forward,

	/*
	* Description:		-
	* Member type:		vec3_t
	* Get params:		get_pmove(const PlayerMove:var, Float:output[3]);
	* Set params:		set_pmove(const PlayerMove:var, Float:dest[3]);
	*/
	pm_right,

	/*
	* Description:		-
	* Member type:		vec3_t
	* Get params:		get_pmove(const PlayerMove:var, Float:output[3]);
	* Set params:		set_pmove(const PlayerMove:var, Float:dest[3]);
	*/
	pm_up,

	/*
	* Description:		-
	* Member type:		vec3_t
	* Get params:		get_pmove(const PlayerMove:var, Float:output[3]);
	* Set params:		set_pmove(const PlayerMove:var, Float:dest[3]);
	*/
	pm_origin,

	/*
	* Description:		-
	* Member type:		vec3_t
	* Get params:		get_pmove(const PlayerMove:var, Float:output[3]);
	* Set params:		set_pmove(const PlayerMove:var, Float:dest[3]);
	*/
	pm_angles,

	/*
	* Description:		-
	* Member type:		vec3_t
	* Get params:		get_pmove(const PlayerMove:var, Float:output[3]);
	* Set params:		set_pmove(const PlayerMove:var, Float:dest[3]);
	*/
	pm_oldangles,

	/*
	* Description:		-
	* Member type:		vec3_t
	* Get params:		get_pmove(const PlayerMove:var, Float:output[3]);
	* Set params:		set_pmove(const PlayerMove:var, Float:dest[3]);
	*/
	pm_velocity,

	/*
	* Description:		-
	* Member type:		vec3_t
	* Get params:		get_pmove(const PlayerMove:var, Float:output[3]);
	* Set params:		set_pmove(const PlayerMove:var, Float:dest[3]);
	*/
	pm_movedir,

	/*
	* Description:		-
	* Member type:		vec3_t
	* Get params:		get_pmove(const PlayerMove:var, Float:output[3]);
	* Set params:		set_pmove(const PlayerMove:var, Float:dest[3]);
	*/
	pm_basevelocity,

	/*
	* Description:		-
	* Member type:		vec3_t
	* Get params:		get_pmove(const PlayerMove:var, Float:output[3]);
	* Set params:		set_pmove(const PlayerMove:var, Float:dest[3]);
	*/
	pm_view_ofs,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, Float:value);
	*/
	pm_flDuckTime,

	/*
	* Description:		-
	* Member type:		qboolean
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_bInDuck,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_flTimeStepSound,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_iStepLeft,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, Float:value);
	*/
	pm_flFallVelocity,

	/*
	* Description:		-
	* Member type:		vec3_t
	* Get params:		get_pmove(const PlayerMove:var, Float:output[3]);
	* Set params:		set_pmove(const PlayerMove:var, Float:dest[3]);
	*/
	pm_punchangle,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, Float:value);
	*/
	pm_flSwimTime,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, Float:value);
	*/
	pm_flNextPrimaryAttack,
	
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_effects,
	
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_flags,
	
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_usehull,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, Float:value);
	*/
	pm_gravity,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, Float:value);
	*/
	pm_friction,
	
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_oldbuttons,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, Float:value);
	*/
	pm_waterjumptime,
	
	/*
	* Description:		-
	* Member type:		qboolean
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_dead,
	
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_deadflag,
	
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_spectator,
	
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_movetype,
	
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_onground,
	
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_waterlevel,
	
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_watertype,
	
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_oldwaterlevel,

	/*
	* Description:		-
	* Member type:		char [256]
	* Get params:		get_member(const PlayerMove:var, dest[], const lenght);
	* Set params:		set_member(const PlayerMove:var, const source[]);
	*/
	pm_sztexturename,

	/*
	* Description:		-
	* Member type:		char
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_chtexturetype,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, Float:value);
	*/
	pm_maxspeed,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, Float:value);
	*/
	pm_clientmaxspeed,
	
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_iuser1,
	
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_iuser2,
	
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_iuser3,
	
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_iuser4,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, Float:value);
	*/
	pm_fuser1,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, Float:value);
	*/
	pm_fuser2,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, Float:value);
	*/
	pm_fuser3,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, Float:value);
	*/
	pm_fuser4,

	/*
	* Description:		-
	* Member type:		vec3_t
	* Get params:		get_pmove(const PlayerMove:var, Float:output[3]);
	* Set params:		set_pmove(const PlayerMove:var, Float:dest[3]);
	*/
	pm_vuser1,

	/*
	* Description:		-
	* Member type:		vec3_t
	* Get params:		get_pmove(const PlayerMove:var, Float:output[3]);
	* Set params:		set_pmove(const PlayerMove:var, Float:dest[3]);
	*/
	pm_vuser2,

	/*
	* Description:		-
	* Member type:		vec3_t
	* Get params:		get_pmove(const PlayerMove:var, Float:output[3]);
	* Set params:		set_pmove(const PlayerMove:var, Float:dest[3]);
	*/
	pm_vuser3,

	/*
	* Description:		-
	* Member type:		vec3_t
	* Get params:		get_pmove(const PlayerMove:var, Float:output[3]);
	* Set params:		set_pmove(const PlayerMove:var, Float:dest[3]);
	*/
	pm_vuser4,
	
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_numphysent,
	
	/*
	* Description:		-
	* Member type:		struct usercmd_s *
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_cmd,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmove(member);
	* Set params:		set_pmove(const PlayerMove:var, value);
	*/
	pm_numtouch,

	/*
	* Description:		-
	* Member type:		char [256]
	* Get params:		get_member(const PlayerMove:var, dest[], const lenght);
	* Set params:		set_member(const PlayerMove:var, const source[]);
	*/
	pm_physinfo,

	/*
	* Description:		-
	* Member type:		vec3_t [4]
	* Get params:		get_pmove(const PlayerMove:var, Float:output[3], element);
	* Set params:		set_pmove(const PlayerMove:var, Float:dest[3], element);
	*/
	pm_player_mins,

	/*
	* Description:		-
	* Member type:		vec3_t [4]
	* Get params:		get_pmove(const PlayerMove:var, Float:output[3], element);
	* Set params:		set_pmove(const PlayerMove:var, Float:dest[3], element);
	*/
	pm_player_maxs
};

enum MoveVars
{
	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_gravity = BEGIN_MEMBER_REGION(movevars),

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_stopspeed,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_maxspeed,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_spectatormaxspeed,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_accelerate,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_airaccelerate,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_wateraccelerate,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_friction,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_edgefriction,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_waterfriction,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_entgravity,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_bounce,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_stepsize,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_maxvelocity,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_zmax,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_waveHeight,

	/*
	* Description:		-
	* Member type:		BOOL
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_footsteps,

	/*
	* Description:		-
	* Member type:		char [32]
	* Get params:		Float:get_movevar(const MoveVars:var, dest[], const lenght);
	* Set params:		set_movevar(const MoveVars:var, const source[]);
	*/
	mv_skyName,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_rollangle,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_rollspeed,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_skycolor_r,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_skycolor_g,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_skycolor_b,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_skyvec_x,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_skyvec_y,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_movevar(const MoveVars:var);
	* Set params:		set_movevar(const MoveVars:var, Float:value);
	*/
	mv_skyvec_z
};

enum PMTrace
{
	/*
	* Description:		-
	* Member type:		qboolean
	* Get params:		get_pmtrace(const tr, const PMTrace:var);
	* Set params:		set_pmtrace(const tr, const PMTrace:var, value);
	*/
	pmt_allsolid = BEGIN_MEMBER_REGION(pmtrace),

	/*
	* Description:		-
	* Member type:		qboolean
	* Get params:		get_pmtrace(const tr, const PMTrace:var);
	* Set params:		set_pmtrace(const tr, const PMTrace:var, value);
	*/
	pmt_startsolid,

	/*
	* Description:		-
	* Member type:		qboolean
	* Get params:		get_pmtrace(const tr, const PMTrace:var);
	* Set params:		set_pmtrace(const tr, const PMTrace:var, value);
	*/
	pmt_inopen,

	/*
	* Description:		-
	* Member type:		qboolean
	* Get params:		get_pmtrace(const tr, const PMTrace:var);
	* Set params:		set_pmtrace(const tr, const PMTrace:var, value);
	*/
	pmt_inwater,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_pmtrace(const tr, const PMTrace:var);
	* Set params:		set_pmtrace(const tr, const PMTrace:var, Float:value);
	*/
	pmt_fraction,

	/*
	* Description:		-
	* Member type:		vec3_t
	* Get params:		get_pmtrace(const tr, const PMTrace:var, Float:output[3]);
	* Set params:		set_pmtrace(const tr, const PMTrace:var, Float:dest[3]);
	*/
	pmt_endpos,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmtrace(const tr, const PMTrace:var);
	* Set params:		set_pmtrace(const tr, const PMTrace:var, value);
	*/
	pmt_ent,

	/*
	* Description:		-
	* Member type:		vec3_t
	* Get params:		get_pmtrace(const tr, const PMTrace:var, Float:output[3]);
	* Set params:		set_pmtrace(const tr, const PMTrace:var, Float:dest[3]);
	*/
	pmt_deltavelocity,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_pmtrace(const tr, const PMTrace:var);
	* Set params:		set_pmtrace(const tr, const PMTrace:var, value);
	*/
	pmt_hitgroup
};

// CCSPlayer
enum CCSPlayer_Members
{
	/*
	* Description:		-
	* Member type:		char [32]
	* Get params:		get_member(index, member, dest[], const lenght);
	* Set params:		set_member(index, member, const source[]);
	*/
	m_szModel = BEGIN_MEMBER_REGION(csplayer),

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_bForceShowMenu,
};

// CBasePlayerItem
enum CBasePlayerItem_Members
{
	/*
	* Description:		-
	* Member type:		class CBasePlayer *
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_pPlayer = BEGIN_MEMBER_REGION(baseitem),

	/*
	* Description:		-
	* Member type:		class CBasePlayerItem *
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_pNext,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_iId,
};

// CBasePlayerWeapon
enum CBasePlayerWeapon_Members
{
	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_iPlayEmptySound = BEGIN_MEMBER_REGION(baseweapon),

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_fFireOnEmpty,

	/*
	* Description:		Soonest time ItemPostFrame will call PrimaryAttack.
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_Weapon_flNextPrimaryAttack,

	/*
	* Description:		Soonest time ItemPostFrame will call SecondaryAttack.
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_Weapon_flNextSecondaryAttack,

	/*
	* Description:		Soonest time ItemPostFrame will call WeaponIdle.
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_Weapon_flTimeWeaponIdle,

	/*
	* Description:		"primary" ammo index into player's m_rgAmmo[]
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_iPrimaryAmmoType,

	/*
	* Description:		"secondary" ammo index into player's m_rgAmmo[]
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_iSecondaryAmmoType,

	/*
	* Description:		Number of shots left in the primary weapon clip, -1 if not used.
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_iClip,

	/*
	* Description:		The last version of m_Weapon_iClip sent to hud dll.
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_iClientClip,

	/*
	* Description:		The last version of the weapon state sent to hud dll (is current weapon, is on target).
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_iClientWeaponState,

	/*
	* Description:		Are we in the middle of a reload?
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_fInReload,

	/*
	* Description:		Are we in the middle of a reload for the shotguns?
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_fInSpecialReload,

	/*
	* Description:		How much ammo you get when you pick up this weapon as placed by a level designer.
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_iDefaultAmmo,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_iShellId,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_Weapon_fMaxSpeed,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_bDelayFire,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_iDirection,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_bSecondarySilencerOn,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_Weapon_flAccuracy,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_Weapon_flLastFire,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_iShotsFired,

	/*
	* Description:		Time to shoot the remaining bullets of the glock18 burst fire.
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_Weapon_flGlock18Shoot,

	/*
	* Description:		Used to keep track of the shots fired during the Glock18 burst fire mode.
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_iGlock18ShotsFired,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_Weapon_flFamasShoot,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_iFamasShotsFired,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_Weapon_fBurstSpread,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_iWeaponState,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_Weapon_flNextReload,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_Weapon_flDecreaseShotsFired,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_usFireGlock18,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Weapon_usFireFamas,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_Weapon_flPrevPrimaryAttack,

	/*
	* Description:		-
	* Member type:		float
	* Get params:		Float:get_member(index, member);
	* Set params:		set_member(index, member, Float:value);
	*/
	m_Weapon_flLastFireTime
};

// CWeaponBox
enum CWeaponBox_Members
{
	/*
	* Description:		-
	* Member type:		class CBasePlayerItem *[6]
	* Get params:		get_member(index, member, element);
	* Set params:		set_member(index, member, value, element);
	*/
	m_WeaponBox_rgpPlayerItems = BEGIN_MEMBER_REGION(weaponbox),

	/*
	* Description:		-
	* Member type:		string_t [32]
	* Get params:		get_member(index, member, dest[], const lenght);
	* Set params:		set_member(index, member, const source[]);
	*/
	m_WeaponBox_rgiszAmmo,

	/*
	* Description:		-
	* Member type:		int [32]
	* Get params:		get_member(index, member, element);
	* Set params:		set_member(index, member, value, element);
	*/
	m_WeaponBox_rgAmmo,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_WeaponBox_cAmmoTypes,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_WeaponBox_bIsBomb,
};

// CArmoury
enum CArmoury_Members
{
	/*
	* Description:		-
	* Member type:		enum ArmouryItemPack
	* Get params:		ArmouryItemPack:get_member(index, member);
	* Set params:		set_member(index, member, ArmouryItemPack:value);
	*/
	m_Armoury_iItem = BEGIN_MEMBER_REGION(armoury),

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Armoury_iCount,

	/*
	* Description:		-
	* Member type:		int
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Armoury_iInitialCount,

	/*
	* Description:		-
	* Member type:		bool
	* Get params:		get_member(index, member);
	* Set params:		set_member(index, member, value);
	*/
	m_Armoury_bAlreadyCounted,
};
