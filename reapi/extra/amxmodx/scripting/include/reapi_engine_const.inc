#if defined _reapi_engine_const_included
	#endinput
#endif

#define _reapi_engine_const_included

/**
* For native rh_get_mapname
*/
enum MapNameType
{
	MNT_TRUE,   // return the original map name independant of the name set with via rh_set_mapname
	MNT_SET     // return the name of the current map
};

/**
* rh_emit_sound2 flags
*/
#define SND_EMIT2_NOPAS   BIT(0) // Never to check PAS
#define SND_EMIT2_INVOKER BIT(1) // Do not send to the client invoker

/**
* enum EngineFunc
*/
enum EngineFunc
{
	/*
	* Description:  -
	* Params:       (const recipients, const entity, const channel, const sample[], const volume, Float:attenuation, const fFlags, const pitch)
	*/
	RH_SV_StartSound = BEGIN_FUNC_REGION(engine),

	/*
	* Description:  -
	* Params:       (const client, bool:crash, const fmt[])
	*/
	RH_SV_DropClient,

	/*
	* Description:  -
	* Params:       (const runPhysics)
	*/
	RH_SV_ActivateServer,

	/*
	* Description:  -
	* Params:       (pcvar, const value[])
	*/
	RH_Cvar_DirectSet,

	/*
	* Description:  Receiver is player index or 0 when update will be sended to all.
	* Params:       (const client, buffer, const receiver)
	*/
	RH_SV_WriteFullClientUpdate,

	/*
	* Description:  -
	* Params:       (const classname[])
	*/
	RH_GetEntityInit,

	/*
	* Description:  Called after processing a client connection request.
	* Params:       (const client)
	*/
	RH_ClientConnected,

	/*
	* Description:  Called when processing a 'connect' client connectionless packet.
	* Params:       ()
	*/
	RH_SV_ConnectClient,

	/*
	* Description:  Called when client it's in the scoreboard
	* Params:       (const this)
	*/
	RH_SV_EmitPings,
	/*
	* Description:  Called when an entity is created.
	* Return type:  Edict * (Entity index)
	* Params:       ()
	*/
	RH_ED_Alloc,

	/*
	* Description:  Called when an entity is removed (freed from server).
	* Params:       (const entity)
	*/
	RH_ED_Free,

	/*
	* Description:  -
	* Params:       (const string[])
	*/
	RH_Con_Printf,
};

/**
* enum EntVars
*/
enum EntVars
{
	/*
	* Description:      -
	* Member type:      string_t
	* Get params:       get_entvar(index, EntVars:var, dest[], const lenght);
	* Set params:       set_entvar(index, EntVars:var, const source[]);
	*/
	var_classname = BEGIN_MEMBER_REGION(entvars),

	/*
	* Description:      -
	* Member type:      string_t
	* Get params:       get_entvar(index, EntVars:var, dest[], const lenght);
	* Set params:       set_entvar(index, EntVars:var, const source[]);
	*/
	var_globalname,

	/*
	* Description:      -
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_origin,

	/*
	* Description:      -
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_oldorigin,

	/*
	* Description:      -
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_velocity,

	/*
	* Description:      -
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_basevelocity,

	/*
	* Description:      Base velocity that was passed in to server physics so client can predict conveyors correctly. Server zeroes it, so we need to it store here, too.
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_clbasevelocity,

	/*
	* Description:      -
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_movedir,

	/*
	* Description:      Angles model.
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_angles,

	/*
	* Description:      Angle velocity (degrees per second).
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_avelocity,

	/*
	* Description:      Auto-decaying view angle adjustment.
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_punchangle,

	/*
	* Description:      View angle (player only).
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_v_angle,

	/*
	* Description:      -
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_endpos,

	/*
	* Description:      -
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_startpos,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_impacttime,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_starttime,

	/*
	* Description:      0:nothing, 1:force view angles, 2:add avelocity
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_fixangle,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_idealpitch,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_pitch_speed,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_ideal_yaw,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_yaw_speed,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_modelindex,

	/*
	* Description:      -
	* Member type:      string_t
	* Get params:       get_entvar(index, EntVars:var, dest[], const lenght);
	* Set params:       set_entvar(index, EntVars:var, const source[]);
	*/
	var_model,

	/*
	* Description:      Player's viewmodel.
	* Member type:      string_t
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, const source[]);
	*/
	var_viewmodel,

	/*
	* Description:      The model that other players see.
	* Member type:      string_t
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, const source[]);
	*/
	var_weaponmodel,

	/*
	* Description:      BB min translated to world coord.
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_absmin,

	/*
	* Description:      BB max translated to world coord.
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_absmax,

	/*
	* Description:      Local BB min.
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_mins,

	/*
	* Description:      Local BB max.
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_maxs,

	/*
	* Description:      maxs - mins
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_size,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_ltime,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_nextthink,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_movetype,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_solid,

	/*
	* Description:      Skin selection for studio models.
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_skin,

	/*
	* Description:      Sub-model selection for studio models.
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_body,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_effects,

	/*
	* Description:      % of "normal" gravity.
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_gravity,

	/*
	* Description:      Inverse elasticity of MOVETYPE_BOUNCE
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_friction,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_light_level,

	/*
	* Description:      Animation sequence.
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_sequence,

	/*
	* Description:      Movement animation sequence for player (0 for none)
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_gaitsequence,

	/*
	* Description:      % playback position in animation sequences (0..255)
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_frame,

	/*
	* Description:      World time when frame was set.
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_animtime,

	/*
	* Description:      Animation playback rate (-8x to 8x)
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_framerate,

	/*
	* Description:      Bone controller setting (0..255)
	* Member type:      byte [4]
	* Get params:       get_entvar(index, EntVars:var, element);
	* Set params:       set_entvar(index, EntVars:var, value, element);
	*/
	var_controller,

	/*
	* Description:      Blending amount between sub-sequences (0..255)
	* Member type:      byte [2]
	* Get params:       get_entvar(index, EntVars:var, element);
	* Set params:       set_entvar(index, EntVars:var, value, element);
	*/
	var_blending,

	/*
	* Description:      Sprite rendering scale (0..255)
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_scale,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_rendermode,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_renderamt,

	/*
	* Description:      -
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_rendercolor,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_renderfx,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_health,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_frags,

	/*
	* Description:      bit mask for available weapons
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_weapons,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_takedamage,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_deadflag,

	/*
	* Description:      eye position
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_view_ofs,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_button,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_impulse,

	/*
	* Description:      Entity pointer when linked into a linked list.
	* Member type:      struct edict_s *
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_chain,

	/*
	* Description:      -
	* Member type:      struct edict_s *
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_dmg_inflictor,

	/*
	* Description:      -
	* Member type:      struct edict_s *
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_enemy,

	/*
	* Description:      Entity pointer when MOVETYPE_FOLLOW
	* Member type:      struct edict_s *
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_aiment,

	/*
	* Description:      -
	* Member type:      struct edict_s *
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_owner,

	/*
	* Description:      -
	* Member type:      struct edict_s *
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_groundentity,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_spawnflags,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_flags,

	/*
	* Description:      lowbyte topcolor, highbyte bottomcolor
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_colormap,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_team,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_max_health,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_teleport_time,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_armortype,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_armorvalue,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_waterlevel,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_watertype,

	/*
	* Description:      -
	* Member type:      string_t
	* Get params:       get_entvar(index, EntVars:var, dest[], const lenght);
	* Set params:       set_entvar(index, EntVars:var, const source[]);
	*/
	var_target,

	/*
	* Description:      -
	* Member type:      string_t
	* Get params:       get_entvar(index, EntVars:var, dest[], const lenght);
	* Set params:       set_entvar(index, EntVars:var, const source[]);
	*/
	var_targetname,

	/*
	* Description:      -
	* Member type:      string_t
	* Get params:       get_entvar(index, EntVars:var, dest[], const lenght);
	* Set params:       set_entvar(index, EntVars:var, const source[]);
	*/
	var_netname,

	/*
	* Description:      -
	* Member type:      string_t
	* Get params:       get_entvar(index, EntVars:var, dest[], const lenght);
	* Set params:       set_entvar(index, EntVars:var, const source[]);
	*/
	var_message,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_dmg_take,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_dmg_save,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_dmg,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_dmgtime,

	/*
	* Description:      -
	* Member type:      string_t
	* Get params:       get_entvar(index, EntVars:var, dest[], const lenght);
	* Set params:       set_entvar(index, EntVars:var, const source[]);
	*/
	var_noise,

	/*
	* Description:      -
	* Member type:      string_t
	* Get params:       get_entvar(index, EntVars:var, dest[], const lenght);
	* Set params:       set_entvar(index, EntVars:var, const source[]);
	*/
	var_noise1,

	/*
	* Description:      -
	* Member type:      string_t
	* Get params:       get_entvar(index, EntVars:var, dest[], const lenght);
	* Set params:       set_entvar(index, EntVars:var, const source[]);
	*/
	var_noise2,

	/*
	* Description:      -
	* Member type:      string_t
	* Get params:       get_entvar(index, EntVars:var, dest[], const lenght);
	* Set params:       set_entvar(index, EntVars:var, const source[]);
	*/
	var_noise3,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_speed,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_air_finished,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_pain_finished,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_radsuit_finished,

	/*
	* Description:      -
	* Member type:      struct edict_s *
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_pContainingEntity,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_playerclass,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_maxspeed,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_fov,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_weaponanim,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_pushmsec,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_bInDuck,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_flTimeStepSound,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_flSwimTime,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_flDuckTime,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_iStepLeft,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_flFallVelocity,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_gamestate,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_oldbuttons,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_groupinfo,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_iuser1,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_iuser2,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_iuser3,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_iuser4,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_fuser1,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_fuser2,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_fuser3,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, Float:value);
	*/
	var_fuser4,

	/*
	* Description:      -
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_vuser1,

	/*
	* Description:      -
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_vuser2,

	/*
	* Description:      -
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_vuser3,

	/*
	* Description:      -
	* Member type:      class Vector
	* Get params:       get_entvar(index, EntVars:var, Float:output[3]);
	* Set params:       set_entvar(index, EntVars:var, Float:dest[3]);
	*/
	var_vuser4,

	/*
	* Description:      -
	* Member type:      struct edict_s *
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_euser1,

	/*
	* Description:      -
	* Member type:      struct edict_s *
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_euser2,

	/*
	* Description:      -
	* Member type:      struct edict_s *
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_euser3,

	/*
	* Description:      -
	* Member type:      struct edict_s *
	* Get params:       get_entvar(index, EntVars:var);
	* Set params:       set_entvar(index, EntVars:var, value);
	*/
	var_euser4
};

/**
* enum UCmd
*/
enum UCmd
{
	/*
	* Description:      -
	* Member type:      short
	* Get params:       get_ucmd(const ucmd, UserCmd:var);
	* Set params:       set_ucmd(const ucmd, UserCmd:var, value);
	*/
	ucmd_lerp_msec = BEGIN_MEMBER_REGION(usercmd),

	/*
	* Description:      -
	* Member type:      byte
	* Get params:       get_ucmd(const ucmd, UserCmd:var);
	* Set params:       set_ucmd(const ucmd, UserCmd:var, value);
	*/
	ucmd_msec,

	/*
	* Description:      -
	* Member type:      vec3_t
	* Get params:       get_ucmd(const ucmd, UserCmd:var, Float:output[3]);
	* Set params:       set_ucmd(const ucmd, UserCmd:var, Float:dest[3]);
	*/
	ucmd_viewangles,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_ucmd(const ucmd, UserCmd:var);
	* Set params:       set_ucmd(const ucmd, UserCmd:var, Float:value);
	*/
	ucmd_forwardmove,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_ucmd(const ucmd, UserCmd:var);
	* Set params:       set_ucmd(const ucmd, UserCmd:var, Float:value);
	*/
	ucmd_sidemove,

	/*
	* Description:      -
	* Member type:      float
	* Get params:       Float:get_ucmd(const ucmd, UserCmd:var);
	* Set params:       set_ucmd(const ucmd, UserCmd:var, Float:value);
	*/
	ucmd_upmove,

	/*
	* Description:      -
	* Member type:      byte
	* Get params:       get_ucmd(const ucmd, UserCmd:var);
	* Set params:       set_ucmd(const ucmd, UserCmd:var, value);
	*/
	ucmd_lightlevel,

	/*
	* Description:      -
	* Member type:      unsigned short
	* Get params:       get_ucmd(const ucmd, UserCmd:var);
	* Set params:       set_ucmd(const ucmd, UserCmd:var, value);
	*/
	ucmd_buttons,

	/*
	* Description:      -
	* Member type:      byte
	* Get params:       get_ucmd(const ucmd, UserCmd:var);
	* Set params:       set_ucmd(const ucmd, UserCmd:var, value);
	*/
	ucmd_impulse,

	/*
	* Description:      -
	* Member type:      byte
	* Get params:       get_ucmd(const ucmd, UserCmd:var);
	* Set params:       set_ucmd(const ucmd, UserCmd:var, value);
	*/
	ucmd_weaponselect,

	/*
	* Description:      -
	* Member type:      int
	* Get params:       get_ucmd(const ucmd, UserCmd:var);
	* Set params:       set_ucmd(const ucmd, UserCmd:var, value);
	*/
	ucmd_impact_index,

	/*
	* Description:      -
	* Member type:      vec3_t
	* Get params:       get_ucmd(const ucmd, UserCmd:var, Float:output[3]);
	* Set params:       set_ucmd(const ucmd, UserCmd:var, Float:dest[3]);
	*/
	ucmd_impact_position
};
