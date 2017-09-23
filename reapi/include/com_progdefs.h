#pragma once

#include "event_flags.h"
#include "event_args.h"

typedef struct event_info_s
{
	unsigned short index;	// 0 implies not in use
	short packet_index;		// Use data from state info for entity in delta_packet.
							// -1 implies separate info based on event parameter signature

	short entity_index;		// The edict this event is associated with
	float fire_time;		// if non-zero, the time when the event should be fired ( fixed up on the client )
	event_args_t args;

// CLIENT ONLY
	int flags;			// Reliable or not, etc.
} event_info_t;

// 16 simultaneous events, max
const int MAX_EVENT_QUEUE = 64;

typedef struct event_state_s
{
	struct event_info_s ei[MAX_EVENT_QUEUE];
} event_state_t;

struct qstring_t { unsigned int str; };
struct rstring_t { const char *str; };

struct com_globalvars
{
	float time;
	float frametime;
	float force_retouch;
	qstring_t mapname;
	qstring_t startspot;
	float deathmatch;
	float coop;
	float teamplay;
	float serverflags;
	float found_secrets;
	vec3_t v_forward;
	vec3_t v_up;
	vec3_t v_right;
	float trace_allsolid;
	float trace_startsolid;
	float trace_fraction;
	vec3_t trace_endpos;
	vec3_t trace_plane_normal;
	float trace_plane_dist;
	edict_t *trace_ent;
	float trace_inopen;
	float trace_inwater;
	int trace_hitgroup;
	int trace_flags;
	int msg_entity;
	int cdAudioTrack;
	int maxClients;
	int maxEntities;
	rstring_t pStringBase;
	void *pSaveData;
	vec3_t vecLandmarkOffset;
};

struct com_entvars
{
	qstring_t classname;
	qstring_t globalname;

	vec3_t origin;
	vec3_t oldorigin;
	vec3_t velocity;
	vec3_t basevelocity;
	vec3_t clbasevelocity;	// Base velocity that was passed in to server physics so
							// client can predict conveyors correctly. Server zeroes it, so we need to store here, too.
	vec3_t movedir;

	vec3_t angles;			// Model angles
	vec3_t avelocity;		// angle velocity (degrees per second)
	vec3_t punchangle;		// auto-decaying view angle adjustment
	vec3_t v_angle;			// Viewing angle (player only)

	// For parametric entities
	vec3_t endpos;
	vec3_t startpos;
	float impacttime;
	float starttime;

	int fixangle;			// 0:nothing, 1:force view angles, 2:add avelocity
	float idealpitch;
	float pitch_speed;
	float ideal_yaw;
	float yaw_speed;

	int modelindex;
	qstring_t model;

	qstring_t viewmodel;	// player's viewmodel
	qstring_t weaponmodel;	// what other players see

	vec3_t absmin;			// BB max translated to world coord
	vec3_t absmax;			// BB max translated to world coord
	vec3_t mins;			// local BB min
	vec3_t maxs;			// local BB max
 	vec3_t size;			// maxs - mins

	float ltime;
	float nextthink;

	int movetype;
	int solid;

	int skin;
	int body;				// sub-model selection for studiomodels
	int effects;

	float gravity;			// % of "normal" gravity
	float friction;			// inverse elasticity of MOVETYPE_BOUNCE

	int light_level;

	int sequence;			// animation sequence
	int gaitsequence;		// movement animation sequence for player (0 for none)
	float frame;			// % playback position in animation sequences (0..255)
	float animtime;			// world time when frame was set
	float framerate;		// animation playback rate (-8x to 8x)
	byte controller[4];		// bone controller setting (0..255)
	byte blending[2];		// blending amount between sub-sequences (0..255)

	float scale;			// sprite rendering scale (0..255)

	int rendermode;
	float renderamt;
	vec3_t rendercolor;
	int renderfx;

	float health;
	float frags;
	int weapons;  			// bit mask for available weapons
	float takedamage;

	int deadflag;
	vec3_t view_ofs;		// eye position

	int button;
	int impulse;

	edict_t *chain;			// Entity pointer when linked into a linked list
	edict_t *dmg_inflictor;
	edict_t *enemy;
	edict_t *aiment;		// entity pointer when MOVETYPE_FOLLOW
	edict_t *owner;
	edict_t *groundentity;

	int spawnflags;
	int flags;

	int colormap;			// lowbyte topcolor, highbyte bottomcolor
	int team;

	float max_health;
	float teleport_time;
	float armortype;
	float armorvalue;
	int waterlevel;
	int watertype;

	qstring_t target;
	qstring_t targetname;
	qstring_t netname;
	qstring_t message;

	float dmg_take;
	float dmg_save;
	float dmg;
	float dmgtime;

	qstring_t noise;
	qstring_t noise1;
	qstring_t noise2;
	qstring_t noise3;

	float speed;
	float air_finished;
	float pain_finished;
	float radsuit_finished;

	edict_t *pContainingEntity;

	int playerclass;
	float maxspeed;

	float fov;
	int weaponanim;

	int pushmsec;

	int bInDuck;
	int flTimeStepSound;
	int flSwimTime;
	int flDuckTime;
	int iStepLeft;
	float flFallVelocity;

	int gamestate;
	int oldbuttons;
	int groupinfo;

	// For mods
	int iuser1;
	int iuser2;
	int iuser3;
	int iuser4;

	float fuser1;
	float fuser2;
	float fuser3;
	float fuser4;

	vec3_t vuser1;
	vec3_t vuser2;
	vec3_t vuser3;
	vec3_t vuser4;

	edict_t *euser1;
	edict_t *euser2;
	edict_t *euser3;
	edict_t *euser4;
};

struct com_playermove
{
	int player_index;				// So we don't try to run the PM_CheckStuck nudging too quickly.
	qboolean server;				// For debugging, are we running physics code on server side?
	qboolean multiplayer;			// 1 == multiplayer server
	float time;						// realtime on host, for reckoning duck timing
	float frametime;				// Duration of this frame
	vec3_t forward, right, up;		// Vectors for angles
	vec3_t origin;					// Movement origin.
	vec3_t angles;					// Movement view angles.
	vec3_t oldangles;				// Angles before movement view angles were looked at.
	vec3_t velocity;				// Current movement direction.
	vec3_t movedir;					// For waterjumping, a forced forward velocity so we can fly over lip of ledge.
	vec3_t basevelocity;			// Velocity of the conveyor we are standing, e.g.
	vec3_t view_ofs;				// For ducking/dead
	// Our eye position.
	float flDuckTime;				// Time we started duck
	qboolean bInDuck;				// In process of ducking or ducked already?
	int flTimeStepSound;			// For walking/falling
	// Next time we can play a step sound
	int iStepLeft;
	float flFallVelocity;
	vec3_t punchangle;
	float flSwimTime;
	float flNextPrimaryAttack;
	int effects;					// MUZZLE FLASH, e.g.
	int flags;						// FL_ONGROUND, FL_DUCKING, etc.
	int usehull;					// 0 = regular player hull, 1 = ducked player hull, 2 = point hull
	float gravity;					// Our current gravity and friction.
	float friction;
	int oldbuttons;					// Buttons last usercmd
	float waterjumptime;			// Amount of time left in jumping out of water cycle.
	qboolean dead;					// Are we a dead player?
	int deadflag;
	int spectator;					// Should we use spectator physics model?
	int movetype;					// Our movement type, NOCLIP, WALK, FLY
	int onground;					// -1 = in air, else pmove entity number
	int waterlevel;
	int watertype;
	int oldwaterlevel;
	char sztexturename[256];
	char chtexturetype;
	float maxspeed;
	float clientmaxspeed;
	int iuser1;
	int iuser2;
	int iuser3;
	int iuser4;
	float fuser1;
	float fuser2;
	float fuser3;
	float fuser4;
	vec3_t vuser1;
	vec3_t vuser2;
	vec3_t vuser3;
	vec3_t vuser4;
	int numphysent;						// world state
	// Number of entities to clip against.
	physent_t physents[MAX_PHYSENTS];
	int nummoveent;						// Number of momvement entities (ladders)
	physent_t moveents[MAX_MOVEENTS];	// just a list of ladders
	int numvisent;						// All things being rendered, for tracing against things you don't actually collide with
	physent_t visents[MAX_PHYSENTS];
	usercmd_t cmd;						// input to run through physics.
	int numtouch;						// Trace results for objects we collided with.
	pmtrace_t touchindex[MAX_PHYSENTS];
	char physinfo[MAX_PHYSINFO_STRING];	// Physics info string
	struct movevars_s *movevars;
	Vector player_mins[4];
	Vector player_maxs[4];

	const char *(*PM_Info_ValueForKey)(const char *s, const char *key);
	void(*PM_Particle)(float *origin, int color, float life, int zpos, int zvel);
	int(*PM_TestPlayerPosition)(float *pos, pmtrace_t *ptrace);
	void(*Con_NPrintf)(int idx, char *fmt, ...);
	void(*Con_DPrintf)(char *fmt, ...);
	void(*Con_Printf)(char *fmt, ...);
	double(*Sys_FloatTime)();
	void(*PM_StuckTouch)(int hitent, pmtrace_t *ptraceresult);
	int(*PM_PointContents)(float *p, int *truecontents);
	int(*PM_TruePointContents)(float *p);
	int(*PM_HullPointContents)(struct hull_s *hull, int num, float *p);
	pmtrace_t(*PM_PlayerTrace)(float *start, float *end, int traceFlags, int ignore_pe);
	struct pmtrace_s *(*PM_TraceLine)(float *start, float *end, int flags, int usehulll, int ignore_pe);
	int32(*RandomLong)(int32 lLow, int32 lHigh);
	float(*RandomFloat)(float flLow, float flHigh);
	int(*PM_GetModelType)(struct model_s *mod);
	void(*PM_GetModelBounds)(struct model_s *mod, float *mins, float *maxs);
	void *(*PM_HullForBsp)(physent_t *pe, float *offset);
	float(*PM_TraceModel)(physent_t *pEnt, float *start, float *end, trace_t *trace);
	int(*COM_FileSize)(char *filename);
	byte *(*COM_LoadFile)(char *path, int usehunk, int *pLength);
	void(*COM_FreeFile)(void *buffer);
	char *(*memfgets)(byte *pMemFile, int fileSize, int *pFilePos, char *pBuffer, int bufferSize);
	qboolean runfuncs;
	void(*PM_PlaySound)(int channel, const char *sample, float volume, float attenuation, int fFlags, int pitch);
	const char *(*PM_TraceTexture)(int ground, float *vstart, float *vend);
	void(*PM_PlaybackEventFull)(int flags, int clientindex, unsigned short eventindex, float delay, float *origin, float *angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2);

	pmtrace_t (*PM_PlayerTraceEx)(float *start, float *end, int traceFlags, int (*pfnIgnore)(physent_t *pe));
	int (*PM_TestPlayerPositionEx)(float *pos, pmtrace_t *ptrace, int (*pfnIgnore)(physent_t *pe));
	struct pmtrace_s *(*PM_TraceLineEx)(float *start, float *end, int flags, int usehulll, int (*pfnIgnore)(physent_t *pe));
};
