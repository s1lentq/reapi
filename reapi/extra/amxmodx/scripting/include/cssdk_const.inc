#if defined _cssdk_const_included
#endinput
#endif
#define _cssdk_const_included

#define BIT(%0)                         (1<<(%0))

#define NULLENT                         -1

#define MAX_WEAPONS                     32
#define MAX_CLIENTS                     32                  // Max # of clients allowed in a server.
#define MAX_ITEM_TYPES                  6                   // hud item selection slots

#define MAX_EDICT_BITS                  11                  // How many bits to use to encode an edict. # of bits needed to represent max edicts
#define MAX_EDICTS                      BIT(MAX_EDICT_BITS) // Max # of edicts in a level (2048)

/**
* get_entvar(entity, var_button) or get_entvar(entity, var_oldbuttons) values
*/
#define IN_ATTACK                       BIT(0)
#define IN_JUMP                         BIT(1)
#define IN_DUCK                         BIT(2)
#define IN_FORWARD                      BIT(3)
#define IN_BACK                         BIT(4)
#define IN_USE                          BIT(5)
#define IN_CANCEL                       BIT(6)
#define IN_LEFT                         BIT(7)
#define IN_RIGHT                        BIT(8)
#define IN_MOVELEFT                     BIT(9)
#define IN_MOVERIGHT                    BIT(10)
#define IN_ATTACK2                      BIT(11)
#define IN_RUN                          BIT(12)
#define IN_RELOAD                       BIT(13)
#define IN_ALT1                         BIT(14)
#define IN_SCORE                        BIT(15) // Used by client.dll for when scoreboard is held down

/**
* get_entvar(entity, var_flags) values
*/
#define FL_FLY                          BIT(0)  // Changes the SV_Movestep() behavior to not need to be on ground
#define FL_SWIM                         BIT(1)  // Changes the SV_Movestep() behavior to not need to be on ground (but stay in water)
#define FL_CONVEYOR                     BIT(2)
#define FL_CLIENT                       BIT(3)
#define FL_INWATER                      BIT(4)
#define FL_MONSTER                      BIT(5)
#define FL_GODMODE                      BIT(6)
#define FL_NOTARGET                     BIT(7)
#define FL_SKIPLOCALHOST                BIT(8)  // Don't send entity to local host, it's predicting this entity itself
#define FL_ONGROUND                     BIT(9)  // At rest / on the ground
#define FL_PARTIALGROUND                BIT(10) // Not all corners are valid
#define FL_WATERJUMP                    BIT(11) // Player jumping out of water
#define FL_FROZEN                       BIT(12) // Player is frozen for 3rd person camera
#define FL_FAKECLIENT                   BIT(13) // JAC: fake client, simulated server side; don't send network messages to them
#define FL_DUCKING                      BIT(14) // Player flag -- Player is fully crouched
#define FL_FLOAT                        BIT(15) // Apply floating force to this entity when in water
#define FL_GRAPHED                      BIT(16) // Worldgraph has this ent listed as something that blocks a connection
#define FL_IMMUNE_WATER                 BIT(17)
#define FL_IMMUNE_SLIME                 BIT(18)
#define FL_IMMUNE_LAVA                  BIT(19)
#define FL_PROXY                        BIT(20) // This is a spectator proxy
#define FL_ALWAYSTHINK                  BIT(21) // Brush model flag -- call think every frame regardless of nextthink - ltime (for constantly changing velocity/path)
#define FL_BASEVELOCITY                 BIT(22) // Base velocity has been applied this frame (used to convert base velocity into momentum)
#define FL_MONSTERCLIP                  BIT(23) // Only collide in with monsters who have FL_MONSTERCLIP set
#define FL_ONTRAIN                      BIT(24) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_WORLDBRUSH                   BIT(25) // Not moveable/removeable brush entity (really part of the world, but represented as an entity for transparency or something)
#define FL_SPECTATOR                    BIT(26) // This client is a spectator, don't run touch functions, etc.
#define FL_CUSTOMENTITY                 BIT(29) // This is a custom entity
#define FL_KILLME                       BIT(30) // This entity is marked for death -- This allows the engine to kill ents at the appropriate time
#define FL_DORMANT                      BIT(31) // Entity is dormant, no updates to client

/**
* get_entvar(entity, var_movetype) values
*/
#define MOVETYPE_NONE                   0  // Never moves
#define MOVETYPE_WALK                   3  // Player only - moving on the ground
#define MOVETYPE_STEP                   4  // Gravity, special edge handling -- monsters use this
#define MOVETYPE_FLY                    5  // No gravity, but still collides with stuff
#define MOVETYPE_TOSS                   6  // Gravity/Collisions
#define MOVETYPE_PUSH                   7  // No clip to world, push and crush
#define MOVETYPE_NOCLIP                 8  // No gravity, no collisions, still do velocity/avelocity
#define MOVETYPE_FLYMISSILE             9  // Extra size to monsters
#define MOVETYPE_BOUNCE                 10 // Just like Toss, but reflect velocity when contacting surfaces
#define MOVETYPE_BOUNCEMISSILE          11 // Bounce w/o gravity
#define MOVETYPE_FOLLOW                 12 // Track movement of aiment
#define MOVETYPE_PUSHSTEP               13 // BSP model that needs physics/world collisions (uses nearest hull for world collision)

/**
* get_entvar(entity, var_solid) values
*
* @note Some movetypes will cause collisions independent of SOLID_NOT and
* SOLID_TRIGGER when the entity moves. SOLID only effects OTHER entities
* colliding with this one when they move - UGH!
*/
#define SOLID_NOT                       0 // No interaction with other objects
#define SOLID_TRIGGER                   1 // Touch on edge, but not blocking
#define SOLID_BBOX                      2 // Touch on edge, block
#define SOLID_SLIDEBOX                  3 // Touch on edge, but not an onground
#define SOLID_BSP                       4 // BSP clip, touch on edge, block

/**
* get_entvar(entity, var_deadflag) values
*/
#define DEAD_NO                         0 // Alive
#define DEAD_DYING                      1 // Playing death animation or still falling off of a ledge waiting to hit ground
#define DEAD_DEAD                       2 // Dead, lying still
#define DEAD_RESPAWNABLE                3
#define DEAD_DISCARDBODY                4

/**
* new Float:takedamage;
* get_entvar(entity, var_takedamage, takedamage) values
* or
* new Float:takedamage = Float:get_entvar(entity, var_takedamage) values
*/
#define DAMAGE_NO                       0.0
#define DAMAGE_YES                      1.0
#define DAMAGE_AIM                      2.0

/**
* get_entvar(entity, var_effects) values
*/
#define EF_BRIGHTFIELD                  1   // Swirling cloud of particles
#define EF_MUZZLEFLASH                  2   // Single frame ELIGHT on entity attachment 0
#define EF_BRIGHTLIGHT                  4   // DLIGHT centered at entity origin
#define EF_DIMLIGHT                     8   // Player flashlight
#define EF_INVLIGHT                     16  // Get lighting from ceiling
#define EF_NOINTERP                     32  // Don't interpolate the next frame
#define EF_LIGHT                        64  // Rocket flare glow sprite
#define EF_NODRAW                       128 // Don't draw entity

// Break Model Defines
#define BREAK_TYPEMASK                  0x4F
#define BREAK_GLASS                     0x01
#define BREAK_METAL                     0x02
#define BREAK_FLESH                     0x04
#define BREAK_WOOD                      0x08

#define BREAK_SMOKE                     0x10
#define BREAK_TRANS                     0x20
#define BREAK_CONCRETE                  0x40
#define BREAK_2                         0x80

// Colliding temp entity sounds
#define BOUNCE_GLASS                    BREAK_GLASS
#define BOUNCE_METAL                    BREAK_METAL
#define BOUNCE_FLESH                    BREAK_FLESH
#define BOUNCE_WOOD                     BREAK_WOOD
#define BOUNCE_SHRAP                    0x10
#define BOUNCE_SHELL                    0x20
#define BOUNCE_CONCRETE                 BREAK_CONCRETE
#define BOUNCE_SHOTSHELL                0x80

// Temp entity bounce sound types
#define TE_BOUNCE_NULL                  0
#define TE_BOUNCE_SHELL                 1
#define TE_BOUNCE_SHOTSHELL             2

/**
* Spectating camera mode constants
*
* @note These constants are linked to different camera modes available when you
*   are spectating (either dead or when in spectator team). Usually this is
*   stored in the var_iuser1 field in Counter-Strike game.
*/
#define OBS_NONE                        0
#define OBS_CHASE_LOCKED                1 // Locked Chase Cam
#define OBS_CHASE_FREE                  2 // Free Chase Cam
#define OBS_ROAMING                     3 // Free Look
#define OBS_IN_EYE                      4 // First Person
#define OBS_MAP_FREE                    5 // Free Overview
#define OBS_MAP_CHASE                   6 // Chase Overview

/**
* Instant damage values for use with the 3rd parameter of the "Damage" client
* message.
*/
#define DMG_GENERIC                     0           // Generic damage was done
#define DMG_CRUSH                       BIT(0)      // Crushed by falling or moving object
#define DMG_BULLET                      BIT(1)      // Shot
#define DMG_SLASH                       BIT(2)      // Cut, clawed, stabbed
#define DMG_BURN                        BIT(3)      // Heat burned
#define DMG_FREEZE                      BIT(4)      // Frozen
#define DMG_FALL                        BIT(5)      // Fell too far
#define DMG_BLAST                       BIT(6)      // Explosive blast damage
#define DMG_CLUB                        BIT(7)      // Crowbar, punch, headbutt
#define DMG_SHOCK                       BIT(8)      // Electric shock
#define DMG_SONIC                       BIT(9)      // Sound pulse shockwave
#define DMG_ENERGYBEAM                  BIT(10)     // Laser or other high energy beam
#define DMG_NEVERGIB                    BIT(12)     // With this bit OR'd in, no damage type will be able to gib victims upon death
#define DMG_ALWAYSGIB                   BIT(13)     // With this bit OR'd in, any damage type can be made to gib victims upon death.
#define DMG_DROWN                       BIT(14)     // Drowning
#define DMG_PARALYZE                    BIT(15)     // Slows affected creature down
#define DMG_NERVEGAS                    BIT(16)     // Nerve toxins, very bad
#define DMG_POISON                      BIT(17)     // Blood poisioning
#define DMG_RADIATION                   BIT(18)     // Radiation exposure
#define DMG_DROWNRECOVER                BIT(19)     // Drowning recovery
#define DMG_ACID                        BIT(20)     // Toxic chemicals or acid burns
#define DMG_SLOWBURN                    BIT(21)     // In an oven
#define DMG_SLOWFREEZE                  BIT(22)     // In a subzero freezer
#define DMG_MORTAR                      BIT(23)     // Hit by air raid (done to distinguish grenade from mortar)
#define DMG_GRENADE                     BIT(24)     // Counter-Strike only - Hit by HE grenade
#define DMG_TIMEBASED                   (~(0x3fff)) // Mask for time-based damage

// These are the damage types that are allowed to gib corpses
#define DMG_GIB_CORPSE                  (DMG_CRUSH | DMG_FALL | DMG_BLAST | DMG_SONIC | DMG_CLUB)

// These are the damage types that have client hud art
#define DMG_SHOWNHUD                    (DMG_POISON | DMG_ACID | DMG_FREEZE | DMG_SLOWFREEZE | DMG_DROWN | DMG_BURN | DMG_SLOWBURN | DMG_NERVEGAS | DMG_RADIATION | DMG_SHOCK)

// When calling KILLED(), a value that governs gib behavior is expected to be
// one of these three values
#define GIB_NORMAL                      0 // Gib if entity was overkilled
#define GIB_NEVER                       1 // Never gib, no matter how much death damage is done ( freezing, etc )
#define GIB_ALWAYS                      2 // Always gib ( Houndeye Shock, Barnacle Bite )

// Player physics flags bits
// CBasePlayer::m_afPhysicsFlags
#define PFLAG_ONLADDER                  BIT(0)
#define PFLAG_ONSWING                   BIT(0)
#define PFLAG_ONTRAIN                   BIT(1)
#define PFLAG_ONBARNACLE                BIT(2)
#define PFLAG_DUCKING                   BIT(3) // In the process of ducking, but totally squatted yet
#define PFLAG_USING                     BIT(4) // Using a continuous entity
#define PFLAG_OBSERVER                  BIT(5) // Player is locked in stationary cam mode. Spectators can move, observers can't.

/**
* @section get_entvar(entity, var_spawnflags) values
*/

/**
* func_train
*/
#define SF_TRAIN_WAIT_RETRIGGER         BIT(0)
#define SF_TRAIN_START_ON               BIT(2) // Train is initially moving
#define SF_TRAIN_PASSABLE               BIT(3) // Train is not solid -- used to make water trains

/**
* func_wall_toggle
*/
#define SF_WALL_TOOGLE_START_OFF        BIT(0)
#define SF_WALL_TOOGLE_NOTSOLID         BIT(3)

/**
* func_converyor
*/
#define SF_CONVEYOR_VISUAL              BIT(0)
#define SF_CONVEYOR_NOTSOLID            BIT(1)

/**
* func_button
*/
#define SF_BUTTON_DONTMOVE              BIT(0)
#define SF_BUTTON_TOGGLE                BIT(5) // Button stays pushed until reactivated
#define SF_BUTTON_SPARK_IF_OFF          BIT(6) // Button sparks in OFF state
#define SF_BUTTON_TOUCH_ONLY            BIT(8) // Button only fires as a result of USE key.

/**
* func_rot_button
*/
#define SF_ROTBUTTON_NOTSOLID           BIT(0)
#define SF_ROTBUTTON_BACKWARDS          BIT(1)

/**
* env_global
*/
#define SF_GLOBAL_SET                   BIT(0) // Set global state to initial state on spawn

/**
* multisource
*/
#define MAX_MS_TARGETS                  32 // maximum number of targets a single multisource entity may be assigned.
#define SF_MULTI_INIT                   BIT(0)

/**
* momentary_rot_button
*/
#define SF_MOMENTARY_DOOR               BIT(0) // Make this button behave like a door (HACKHACK)
                                               // This will disable use and make the button solid
                                               // rotating buttons were made SOLID_NOT by default since their were some
                                               // collision problems with them...

/**
* button_target
*/
#define SF_BTARGET_USE                  BIT(0)
#define SF_BTARGET_ON                   BIT(1)

/**
* func_door, func_water, func_door_rotating, momementary_door
*/
#define SF_DOOR_START_OPEN              BIT(0)
#define SF_DOOR_PASSABLE                BIT(3)
#define SF_DOOR_NO_AUTO_RETURN          BIT(5)
#define SF_DOOR_USE_ONLY                BIT(8)  // door must be opened by player's use button.
#define SF_DOOR_TOUCH_ONLY_CLIENTS      BIT(10) // Only clients can touch
#define SF_DOOR_ACTUALLY_WATER          BIT(31) // This bit marks that func_door are actually func_water

/**
* gibshooter
*/
#define SF_GIBSHOOTER_REPEATABLE        BIT(0) // Allows a gibshooter to be refired

/**
* env_funnel
*/
#define SF_FUNNEL_REVERSE               BIT(0) // Funnel effect repels particles instead of attracting them

/**
* env_bubbles
*/
#define SF_BUBBLES_STARTOFF             BIT(0)

/**
* env_blood
*/
#define SF_BLOOD_RANDOM                 BIT(0)
#define SF_BLOOD_STREAM                 BIT(1)
#define SF_BLOOD_PLAYER                 BIT(2)
#define SF_BLOOD_DECAL                  BIT(3)

/**
* env_shake
*/
#define SF_SHAKE_EVERYONE               BIT(0) // Don't check radius
#define SF_SHAKE_DISRUPT                BIT(1) // Disrupt controls
#define SF_SHAKE_INAIR                  BIT(2) // Shake players in air

/**
* env_fade
*/
#define SF_FADE_IN                      BIT(0) // Fade in, not out
#define SF_FADE_MODULATE                BIT(1) // Modulate, don't blend
#define SF_FADE_ONLYONE                 BIT(2)

/**
* env_beam, env_lightning
*/
#define SF_BEAM_STARTON                 BIT(0)
#define SF_BEAM_TOGGLE                  BIT(1)
#define SF_BEAM_RANDOM                  BIT(2)
#define SF_BEAM_RING                    BIT(3)
#define SF_BEAM_SPARKSTART              BIT(4)
#define SF_BEAM_SPARKEND                BIT(5)
#define SF_BEAM_DECALS                  BIT(6)
#define SF_BEAM_SHADEIN                 BIT(7)
#define SF_BEAM_SHADEOUT                BIT(8)
#define SF_BEAM_TEMPORARY               BIT(15)

/**
* env_sprite
*/
#define SF_SPRITE_STARTON               BIT(0)
#define SF_SPRITE_ONCE                  BIT(1)
#define SF_SPRITE_TEMPORARY             BIT(15)

/**
* env_message
*/
#define SF_MESSAGE_ONCE                 BIT(0) // Fade in, not out
#define SF_MESSAGE_ALL                  BIT(1) // Send to all clients

/**
* env_explosion
*/
#define SF_ENVEXPLOSION_NODAMAGE        BIT(0) // When set, ENV_EXPLOSION will not actually inflict damage
#define SF_ENVEXPLOSION_REPEATABLE      BIT(1) // Can this entity be refired?
#define SF_ENVEXPLOSION_NOFIREBALL      BIT(2) // Don't draw the fireball
#define SF_ENVEXPLOSION_NOSMOKE         BIT(3) // Don't draw the smoke
#define SF_ENVEXPLOSION_NODECAL         BIT(4) // Don't make a scorch mark
#define SF_ENVEXPLOSION_NOSPARKS        BIT(5) // Don't make a scorch mark

/**
* func_tank
*/
#define SF_TANK_ACTIVE                  BIT(0)
#define SF_TANK_PLAYER                  BIT(1)
#define SF_TANK_HUMANS                  BIT(2)
#define SF_TANK_ALIENS                  BIT(3)
#define SF_TANK_LINEOFSIGHT             BIT(4)
#define SF_TANK_CANCONTROL              BIT(5)
#define SF_TANK_SOUNDON                 BIT(15)

/**
* grenade
*/
#define SF_DETONATE                     BIT(0) // Grenades flagged with this will be triggered when the owner calls detonateSatchelCharges

/**
* game_score
*/
#define SF_SCORE_NEGATIVE               BIT(0) // Allow negative scores
#define SF_SCORE_TEAM                   BIT(1) // Award points to team in teamplay

/**
* game_text
*/
#define SF_ENVTEXT_ALLPLAYERS           BIT(0) // Message will be displayed to all players instead of just the activator.

/**
* game_team_master
*/
#define SF_TEAMMASTER_FIREONCE          BIT(0) // Remove on Fire
#define SF_TEAMMASTER_ANYTEAM           BIT(1) // Any team until set? -- Any team can use this until the team is set (otherwise no teams can use it)

/**
* game_team_set
*/
#define SF_TEAMSET_FIREONCE             BIT(0) // Remove entity after firing.
#define SF_TEAMSET_CLEARTEAM            BIT(1) // Clear team -- Sets the team to "NONE" instead of activator

/**
* game_player_hurt
*/
#define SF_PKILL_FIREONCE               BIT(0) // Remove entity after firing.

/**
* game_counter
*/
#define SF_GAMECOUNT_FIREONCE           BIT(0) // Remove entity after firing.
#define SF_GAMECOUNT_RESET              BIT(1) // Reset entity Initial value after fired.
#define SF_GAMECOUNT_OVER_LIMIT         BIT(2) // Fire a target when initial value is higher than limit value.

/**
* game_player_equip
*/
#define MAX_EQUIP                       32
#define SF_PLAYEREQUIP_USEONLY          BIT(0) // If set, the game_player_equip entity will not equip respawning players,
                                               // but only react to direct triggering, equipping its activator. This makes its master obsolete.

/**
* game_player_team
*/
#define SF_PTEAM_FIREONCE               BIT(0) // Remove entity after firing.
#define SF_PTEAM_KILL                   BIT(1) // Kill Player.
#define SF_PTEAM_GIB                    BIT(2) // Gib Player.

/**
* func_plat
*/
#define SF_PLAT_TOGGLE                  BIT(0) // The lift is no more automatically called from top and activated by stepping on it.
                                               // It required trigger to do so.

/**
* func_trackchange
*/
#define SF_TRACK_ACTIVATETRAIN          BIT(0)
#define SF_TRACK_RELINK                 BIT(1)
#define SF_TRACK_ROTMOVE                BIT(2)
#define SF_TRACK_STARTBOTTOM            BIT(3)
#define SF_TRACK_DONT_MOVE              BIT(4)

/**
* func_tracktrain
*/
#define SF_TRACKTRAIN_NOPITCH           BIT(0)
#define SF_TRACKTRAIN_NOCONTROL         BIT(1)
#define SF_TRACKTRAIN_FORWARDONLY       BIT(2)
#define SF_TRACKTRAIN_PASSABLE          BIT(3)

/**
* path_track
*/
#define SF_PATH_DISABLED                BIT(0)
#define SF_PATH_FIREONCE                BIT(1)
#define SF_PATH_ALTREVERSE              BIT(2)
#define SF_PATH_DISABLE_TRAIN           BIT(3)
#define SF_PATH_ALTERNATE               BIT(15)

/**
* path_corner
*/
#define SF_CORNER_WAITFORTRIG           BIT(0)
#define SF_CORNER_TELEPORT              BIT(1)
#define SF_CORNER_FIREONCE              BIT(2)

/**
* trigger_push
*/
#define SF_TRIGGER_PUSH_ONCE            BIT(0)
#define SF_TRIGGER_PUSH_START_OFF       BIT(1) // Spawnflag that makes trigger_push spawn turned OFF
/**
* trigger_hurt
*/
#define SF_TRIGGER_HURT_TARGETONCE      BIT(0) // Only fire hurt target once
#define SF_TRIGGER_HURT_START_OFF       BIT(1) // Spawnflag that makes trigger_push spawn turned OFF
#define SF_TRIGGER_HURT_NO_CLIENTS      BIT(3) // Spawnflag that makes trigger_push spawn turned OFF
#define SF_TRIGGER_HURT_CLIENTONLYFIRE  BIT(4) // Trigger hurt will only fire its target if it is hurting a client
#define SF_TRIGGER_HURT_CLIENTONLYTOUCH BIT(5) // Only clients may touch this trigger.

/**
* trigger_auto
*/
#define SF_AUTO_FIREONCE                BIT(0)
#define SF_AUTO_NORESET                 BIT(1)

/**
* trigger_relay
*/
#define SF_RELAY_FIREONCE               BIT(0)

/**
* multi_manager
*/
#define SF_MULTIMAN_THREAD              BIT(0)
#define SF_MULTIMAN_CLONE               BIT(31)

/**
* env_render
* @note These are flags to indicate masking off various render parameters that
* are usually copied to the targets
*/
#define SF_RENDER_MASKFX                BIT(0)
#define SF_RENDER_MASKAMT               BIT(1)
#define SF_RENDER_MASKMODE              BIT(2)
#define SF_RENDER_MASKCOLOR             BIT(3)

/**
* trigger_changelevel
*/
#define SF_CHANGELEVEL_USEONLY          BIT(1)

/**
* trigger_endsection
*/
#define SF_ENDSECTION_USEONLY           BIT(0)

/**
* trigger_camera
*/
#define SF_CAMERA_PLAYER_POSITION       BIT(0)
#define SF_CAMERA_PLAYER_TARGET         BIT(1)
#define SF_CAMERA_PLAYER_TAKECONTROL    BIT(2)

/**
* func_rotating
*/
#define SF_BRUSH_ROTATE_START_ON        BIT(0)
#define SF_BRUSH_ROTATE_BACKWARDS       BIT(1)
#define SF_BRUSH_ROTATE_Z_AXIS          BIT(2)
#define SF_BRUSH_ROTATE_X_AXIS          BIT(3)
#define SF_BRUSH_ACCDCC                 BIT(4) // Brush should accelerate and decelerate when toggled
#define SF_BRUSH_HURT                   BIT(5) // Rotating brush that inflicts pain based on rotation speed
#define SF_BRUSH_ROTATE_NOT_SOLID       BIT(6) // Some special rotating objects are not solid.
#define SF_BRUSH_ROTATE_SMALLRADIUS     BIT(7)
#define SF_BRUSH_ROTATE_MEDIUMRADIUS    BIT(8)
#define SF_BRUSH_ROTATE_LARGERADIUS     BIT(9)

/**
* triggers
*/
#define SF_TRIGGER_ALLOWMONSTERS        BIT(0) // Monsters allowed to fire this trigger
#define SF_TRIGGER_NOCLIENTS            BIT(1) // Players not allowed to fire this trigger
#define SF_TRIGGER_PUSHABLES            BIT(2) // Only pushables can fire this trigger
#define SF_TRIGGER_NORESET              BIT(6) // It is not allowed to be resetting on a new round

/**
* trigger_multiple
*/
#define SF_TRIGGER_MULTIPLE_NOTOUCH     BIT(0)

/**
* trigger_counter
*/
#define SF_TRIGGER_COUNTER_NOMESSAGE    BIT(0)

/**
* func_breakable
*/
#define SF_BREAK_TRIGGER_ONLY           BIT(0) // May only be broken by trigger
#define SF_BREAK_TOUCH                  BIT(1) // Can be 'crashed through' by running player (plate glass)
#define SF_BREAK_PRESSURE               BIT(2) // Can be broken by a player standing on it
#define SF_BREAK_CROWBAR                BIT(8) // Instant break if hit with crowbar

/**
* func_pushable (also func_breakable, so don't collide with those flags)
*/
#define SF_PUSH_BREAKABLE               BIT(7)

/**
* light_spawn
*/
#define SF_LIGHT_START_OFF              BIT(0)

/**
* info_decal
*/
#define SF_DECAL_NOTINDEATHMATCH        BIT(11)

/**
* worldspawn
*/
#define SF_WORLD_DARK                   BIT(0) // Fade from black at startup
#define SF_WORLD_TITLE                  BIT(1) // Display game title at startup
#define SF_WORLD_FORCETEAM              BIT(2) // Force teams

/**
* Set this bit on guns and stuff that should never respawn
*/
#define SF_NORESPAWN                    BIT(30)

/**
* @endsection
*/

/**
* Train status values
*/
#define TRAIN_ACTIVE                    0x80
#define TRAIN_NEW                       0xc0

#define TRAIN_OFF                       0x00
#define TRAIN_NEUTRAL                   0x01
#define TRAIN_SLOW                      0x02
#define TRAIN_MEDIUM                    0x03
#define TRAIN_FAST                      0x04
#define TRAIN_BACK                      0x05

#define FEV_NOTHOST                     BIT(0) // Skip local host for event send.
#define FEV_RELIABLE                    BIT(1) // Send the event reliably. You must specify the origin and angles
                                               // for this to work correctly on the server for anything
                                               // that depends on the event origin/angles. I.e., the origin/angles are not
                                               // taken from the invoking edict for reliable events.

#define FEV_GLOBAL                      BIT(2) // Don't restrict to PAS/PVS, send this event to _everybody_ on the server ( useful for stopping CHAN_STATIC
                                               // sounds started by client event when client is not in PVS anymore ( hwguy in TFC e.g. ).

#define FEV_UPDATE                      BIT(3) // If this client already has one of these events in its queue, just update the event instead of sending it as a duplicate
#define FEV_HOSTONLY                    BIT(4) // Only send to entity specified as the invoker
#define FEV_SERVER                      BIT(5) // Only send if the event was created on the server.
#define FEV_CLIENT                      BIT(6) // Only issue event client side ( from shared code )

/**
* Cap bits to indicate what an object's capabilities are, currently used for
* save/restore and level transitions.
*/
#define FCAP_CUSTOMSAVE                 BIT(0)
#define FCAP_ACROSS_TRANSITION          BIT(1)  // Should transfer between transitions
#define FCAP_MUST_SPAWN                 BIT(2)  // Spawn after restore
#define FCAP_IMPULSE_USE                BIT(3)  // Can be used by the player
#define FCAP_CONTINUOUS_USE             BIT(4)  // Can be used by the player
#define FCAP_ONOFF_USE                  BIT(5)  // Can be used by the player
#define FCAP_DIRECTIONAL_USE            BIT(6)  // Player sends +/- 1 when using (currently only tracktrains)
#define FCAP_MASTER                     BIT(7)  // Can be used to "master" other entities (like multisource)
#define FCAP_DONT_SAVE                  BIT(31) // Don't save this

// UNDONE: This will ignore transition volumes (trigger_transition), but not the PVS!!!
#define FCAP_FORCE_TRANSITION           BIT(7)  // ALWAYS goes across transitions

// All monsters need this data
#define DONT_BLEED                      -1
#define BLOOD_COLOR_RED                 247
#define BLOOD_COLOR_YELLOW              195
#define BLOOD_COLOR_GREEN               BLOOD_COLOR_YELLOW

// CBasePlayer::m_iIgnoreGlobalChat
enum
{
	IGNOREMSG_NONE,  // Nothing to do
	IGNOREMSG_ENEMY, // To ignore any chat messages from the enemy
	IGNOREMSG_TEAM   // Same as IGNOREMSG_ENEMY but ignore teammates
}

enum HitBoxGroup
{
	HITGROUP_GENERIC = 0,
	HITGROUP_HEAD,
	HITGROUP_CHEST,
	HITGROUP_STOMACH,
	HITGROUP_LEFTARM,
	HITGROUP_RIGHTARM,
	HITGROUP_LEFTLEG,
	HITGROUP_RIGHTLEG,
	HITGROUP_SHIELD
};

enum ArmorType
{
	ARMOR_NONE,     // No armor
	ARMOR_KEVLAR,   // Body vest only
	ARMOR_VESTHELM, // Vest and helmet
};

// For CArmoury::m_Armoury_iItem
enum ArmouryItemPack
{
	ARMOURY_MP5NAVY,
	ARMOURY_TMP,
	ARMOURY_P90,
	ARMOURY_MAC10,
	ARMOURY_AK47,
	ARMOURY_SG552,
	ARMOURY_M4A1,
	ARMOURY_AUG,
	ARMOURY_SCOUT,
	ARMOURY_G3SG1,
	ARMOURY_AWP,
	ARMOURY_M3,
	ARMOURY_XM1014,
	ARMOURY_M249,
	ARMOURY_FLASHBANG,
	ARMOURY_HEGRENADE,
	ARMOURY_KEVLAR,
	ARMOURY_ASSAULT,
	ARMOURY_SMOKEGRENADE
};

enum RewardType
{
	RT_NONE,
	RT_ROUND_BONUS,
	RT_PLAYER_RESET,
	RT_PLAYER_JOIN,
	RT_PLAYER_SPEC_JOIN,
	RT_PLAYER_BOUGHT_SOMETHING,
	RT_HOSTAGE_TOOK,
	RT_HOSTAGE_RESCUED,
	RT_HOSTAGE_DAMAGED,
	RT_HOSTAGE_KILLED,
	RT_TEAMMATES_KILLED,
	RT_ENEMY_KILLED,
	RT_INTO_GAME,
	RT_VIP_KILLED,
	RT_VIP_RESCUED_MYSELF
};

enum TeamName
{
	TEAM_UNASSIGNED,
	TEAM_TERRORIST,
	TEAM_CT,
	TEAM_SPECTATOR
};

enum ModelName
{
	MODEL_UNASSIGNED,
	MODEL_CT_URBAN,
	MODEL_T_TERROR,
	MODEL_T_LEET,
	MODEL_T_ARCTIC,
	MODEL_CT_GSG9,
	MODEL_CT_GIGN,
	MODEL_CT_SAS,
	MODEL_T_GUERILLA,
	MODEL_CT_VIP,
	MODEL_T_MILITIA,
	MODEL_CT_SPETSNAZ,
	MODEL_AUTO
};

enum
{
	GR_NONE = 0,
	GR_WEAPON_RESPAWN_YES,
	GR_WEAPON_RESPAWN_NO,
	GR_AMMO_RESPAWN_YES,
	GR_AMMO_RESPAWN_NO,
	GR_ITEM_RESPAWN_YES,
	GR_ITEM_RESPAWN_NO,
	GR_PLR_DROP_GUN_ALL,
	GR_PLR_DROP_GUN_ACTIVE,
	GR_PLR_DROP_GUN_NO,
	GR_PLR_DROP_AMMO_ALL,
	GR_PLR_DROP_AMMO_ACTIVE,
	GR_PLR_DROP_AMMO_NO
};

enum WeaponIdType
{
	WEAPON_NONE,
	WEAPON_P228,
	WEAPON_GLOCK,
	WEAPON_SCOUT,
	WEAPON_HEGRENADE,
	WEAPON_XM1014,
	WEAPON_C4,
	WEAPON_MAC10,
	WEAPON_AUG,
	WEAPON_SMOKEGRENADE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_UMP45,
	WEAPON_SG550,
	WEAPON_GALIL,
	WEAPON_FAMAS,
	WEAPON_USP,
	WEAPON_GLOCK18,
	WEAPON_AWP,
	WEAPON_MP5N,
	WEAPON_M249,
	WEAPON_M3,
	WEAPON_M4A1,
	WEAPON_TMP,
	WEAPON_G3SG1,
	WEAPON_FLASHBANG,
	WEAPON_DEAGLE,
	WEAPON_SG552,
	WEAPON_AK47,
	WEAPON_KNIFE,
	WEAPON_P90,
	WEAPON_SHIELDGUN = 99
};

// For member CBaseMonster::m_rgbTimeBasedDamage
enum TimeBasedDamage
{
	ITDB_PRALYZE,
	ITDB_NERVEGAS,
	ITDB_POISON,
	ITDB_RADIATION,
	ITDB_DROWNRECOVER,
	ITDB_ACID,
	ITDB_SLOWBURN,
	ITDB_SLOWFREEZE
};

enum Activity
{
	ACT_INVALID = -1,
	ACT_RESET, // Set m_Activity to this invalid value to force a reset to m_IdealActivity
	ACT_IDLE,
	ACT_GUARD,
	ACT_WALK,
	ACT_RUN,
	ACT_FLY,
	ACT_SWIM,
	ACT_HOP,
	ACT_LEAP,
	ACT_FALL,
	ACT_LAND,
	ACT_STRAFE_LEFT,
	ACT_STRAFE_RIGHT,
	ACT_ROLL_LEFT,
	ACT_ROLL_RIGHT,
	ACT_TURN_LEFT,
	ACT_TURN_RIGHT,
	ACT_CROUCH,
	ACT_CROUCHIDLE,
	ACT_STAND,
	ACT_USE,
	ACT_SIGNAL1,
	ACT_SIGNAL2,
	ACT_SIGNAL3,
	ACT_TWITCH,
	ACT_COWER,
	ACT_SMALL_FLINCH,
	ACT_BIG_FLINCH,
	ACT_RANGE_ATTACK1,
	ACT_RANGE_ATTACK2,
	ACT_MELEE_ATTACK1,
	ACT_MELEE_ATTACK2,
	ACT_RELOAD,
	ACT_ARM,
	ACT_DISARM,
	ACT_EAT,
	ACT_DIESIMPLE,
	ACT_DIEBACKWARD,
	ACT_DIEFORWARD,
	ACT_DIEVIOLENT,
	ACT_BARNACLE_HIT,
	ACT_BARNACLE_PULL,
	ACT_BARNACLE_CHOMP,
	ACT_BARNACLE_CHEW,
	ACT_SLEEP,
	ACT_INSPECT_FLOOR,
	ACT_INSPECT_WALL,
	ACT_IDLE_ANGRY,
	ACT_WALK_HURT,
	ACT_RUN_HURT,
	ACT_HOVER,
	ACT_GLIDE,
	ACT_FLY_LEFT,
	ACT_FLY_RIGHT,
	ACT_DETECT_SCENT,
	ACT_SNIFF,
	ACT_BITE,
	ACT_THREAT_DISPLAY,
	ACT_FEAR_DISPLAY,
	ACT_EXCITED,
	ACT_SPECIAL_ATTACK1,
	ACT_SPECIAL_ATTACK2,
	ACT_COMBAT_IDLE,
	ACT_WALK_SCARED,
	ACT_RUN_SCARED,
	ACT_VICTORY_DANCE,
	ACT_DIE_HEADSHOT,
	ACT_DIE_CHESTSHOT,
	ACT_DIE_GUTSHOT,
	ACT_DIE_BACKSHOT,
	ACT_FLINCH_HEAD,
	ACT_FLINCH_CHEST,
	ACT_FLINCH_STOMACH,
	ACT_FLINCH_LEFTARM,
	ACT_FLINCH_RIGHTARM,
	ACT_FLINCH_LEFTLEG,
	ACT_FLINCH_RIGHTLEG,
	ACT_FLINCH,
	ACT_LARGE_FLINCH,
	ACT_HOLDBOMB,
	ACT_IDLE_FIDGET,
	ACT_IDLE_SCARED,
	ACT_IDLE_SCARED_FIDGET,
	ACT_FOLLOW_IDLE,
	ACT_FOLLOW_IDLE_FIDGET,
	ACT_FOLLOW_IDLE_SCARED,
	ACT_FOLLOW_IDLE_SCARED_FIDGET,
	ACT_CROUCH_IDLE,
	ACT_CROUCH_IDLE_FIDGET,
	ACT_CROUCH_IDLE_SCARED,
	ACT_CROUCH_IDLE_SCARED_FIDGET,
	ACT_CROUCH_WALK,
	ACT_CROUCH_WALK_SCARED,
	ACT_CROUCH_DIE,
	ACT_WALK_BACK,
	ACT_IDLE_SNEAKY,
	ACT_IDLE_SNEAKY_FIDGET,
	ACT_WALK_SNEAKY,
	ACT_WAVE,
	ACT_YES,
	ACT_NO
};

enum WinStatus
{
	WINSTATUS_CTS = 1,
	WINSTATUS_TERRORISTS,
	WINSTATUS_DRAW,
};

// Bypass warning: 200 on amxmodx 1.8.2
#if AMXX_VERSION_NUM < 183
	#define ROUND_ESCAPING_TERRORISTS_NEUTRALIZED ROUND_ESCAPING_TERRORISTS_NEUTR
	#define RR_ESCAPING_TERRORISTS_NEUTRALIZED RR_ESCAPING_TERRORISTS_NEUTR
#endif

// Used for EndRoundMessage() logged messages
enum ScenarioEventEndRound
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
	ROUND_GAME_RESTART,
	ROUND_GAME_OVER
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

// CBasePlayer::m_iJoiningState
enum JoinState { JOINED, SHOWLTEXT, READINGLTEXT, SHOWTEAMSELECT, PICKINGTEAM, GETINTOGAME };

// CBasePlayer::m_iMenu
enum _Menu
{
	Menu_OFF,
	Menu_ChooseTeam,
	Menu_IGChooseTeam,
	Menu_ChooseAppearance,
	Menu_Buy,
	Menu_BuyPistol,
	Menu_BuyRifle,
	Menu_BuyMachineGun,
	Menu_BuyShotgun,
	Menu_BuySubMachineGun,
	Menu_BuyItem,
	Menu_Radio1,
	Menu_Radio2,
	Menu_Radio3,
	Menu_ClientBuy
};

// CBasePlayer::m_flLastCommandTime[8]
enum TrackCommands
{
	CMD_SAY,
	CMD_SAYTEAM,
	CMD_FULLUPDATE,
	CMD_VOTE,
	CMD_VOTEMAP,
	CMD_LISTMAPS,
	CMD_LISTPLAYERS,
	CMD_NIGHTVISION,
	COMMANDS_TO_TRACK,
};

// CBasePlayer::m_rgpPlayerItems[6]
enum InventorySlotType
{
	NONE_SLOT,
	PRIMARY_WEAPON_SLOT,
	PISTOL_SLOT,
	KNIFE_SLOT,
	GRENADE_SLOT,
	C4_SLOT,
};

// Sets animation for weapon_shield of SendWeaponAnim
enum shieldgren_e
{
	SHIELDREN_IDLE = 4,
	SHIELDREN_UP,
	SHIELDREN_DOWN
};

enum shieldgun_e
{
	SHIELDGUN_IDLE,
	SHIELDGUN_SHOOT1,
	SHIELDGUN_SHOOT2,
	SHIELDGUN_SHOOT_EMPTY,
	SHIELDGUN_RELOAD,
	SHIELDGUN_DRAW,
	SHIELDGUN_DRAWN_IDLE,
	SHIELDGUN_UP,
	SHIELDGUN_DOWN,
};

// Flags for CUnifiedSignals m_signals
enum SignalState
{
	SIGNAL_BUY       = BIT(0),
	SIGNAL_BOMB      = BIT(1),
	SIGNAL_RESCUE    = BIT(2),
	SIGNAL_ESCAPE    = BIT(3),
	SIGNAL_VIPSAFETY = BIT(4),
};

// Weapon states of the following weapons: usp, elite, glock18, famas and m4a1.
enum WeaponState
{
	WPNSTATE_USP_SILENCED       = BIT(0),
	WPNSTATE_GLOCK18_BURST_MODE = BIT(1),
	WPNSTATE_M4A1_SILENCED      = BIT(2),
	WPNSTATE_ELITE_LEFT         = BIT(3),
	WPNSTATE_FAMAS_BURST_MODE   = BIT(4),
	WPNSTATE_SHIELD_DRAWN       = BIT(5),
};

enum Bullet
{
	BULLET_NONE,
	BULLET_PLAYER_9MM,
	BULLET_PLAYER_MP5,
	BULLET_PLAYER_357,
	BULLET_PLAYER_BUCKSHOT,
	BULLET_PLAYER_CROWBAR,
	BULLET_MONSTER_9MM,
	BULLET_MONSTER_MP5,
	BULLET_MONSTER_12MM,
	BULLET_PLAYER_45ACP,
	BULLET_PLAYER_338MAG,
	BULLET_PLAYER_762MM,
	BULLET_PLAYER_556MM,
	BULLET_PLAYER_50AE,
	BULLET_PLAYER_57MM,
	BULLET_PLAYER_357SIG,
};

enum RewardRules
{
	RR_CTS_WIN,
	RR_TERRORISTS_WIN,
	RR_TARGET_BOMB,
	RR_VIP_ESCAPED,
	RR_VIP_ASSASSINATED,
	RR_TERRORISTS_ESCAPED,
	RR_CTS_PREVENT_ESCAPE,
	RR_ESCAPING_TERRORISTS_NEUTRALIZED,
	RR_BOMB_DEFUSED,
	RR_BOMB_PLANTED,
	RR_BOMB_EXPLODED,
	RR_ALL_HOSTAGES_RESCUED,
	RR_TARGET_BOMB_SAVED,
	RR_HOSTAGE_NOT_RESCUED,
	RR_VIP_NOT_ESCAPED,
	RR_LOSER_BONUS_DEFAULT,
	RR_LOSER_BONUS_MIN,
	RR_LOSER_BONUS_MAX,
	RR_LOSER_BONUS_ADD,
	RR_RESCUED_HOSTAGE,
	RR_TOOK_HOSTAGE_ACC,
	RR_TOOK_HOSTAGE,
	RR_END
};

enum ItemRestType
{
	ITEM_TYPE_BUYING,  // When a player is buying items
	ITEM_TYPE_TOUCHED, // When the player touches a weaponbox or armoury_entity
	ITEM_TYPE_EQUIPPED // When an entity game_player_equip gives item to player or default items on player spawn
};

// Constant items
enum ItemID
{
	ITEM_NONE = -1,
	ITEM_SHIELDGUN,
	ITEM_P228,
	ITEM_GLOCK,
	ITEM_SCOUT,
	ITEM_HEGRENADE,
	ITEM_XM1014,
	ITEM_C4,
	ITEM_MAC10,
	ITEM_AUG,
	ITEM_SMOKEGRENADE,
	ITEM_ELITE,
	ITEM_FIVESEVEN,
	ITEM_UMP45,
	ITEM_SG550,
	ITEM_GALIL,
	ITEM_FAMAS,
	ITEM_USP,
	ITEM_GLOCK18,
	ITEM_AWP,
	ITEM_MP5N,
	ITEM_M249,
	ITEM_M3,
	ITEM_M4A1,
	ITEM_TMP,
	ITEM_G3SG1,
	ITEM_FLASHBANG,
	ITEM_DEAGLE,
	ITEM_SG552,
	ITEM_AK47,
	ITEM_KNIFE,
	ITEM_P90,
	ITEM_NVG,
	ITEM_DEFUSEKIT,
	ITEM_KEVLAR,
	ITEM_ASSAULT,
	ITEM_LONGJUMP,
	ITEM_SODACAN,
	ITEM_HEALTHKIT,
	ITEM_ANTIDOTE,
	ITEM_BATTERY
};
