#if defined _reapi_engine_included
	#endinput
#endif

#define _reapi_engine_included

#include <reapi_engine_const>

/*
* Sets entvars data for an entity.
* Use the var_* EntVars enum
*/
native set_entvar(const index, const EntVars:var, any:...);

/*
* Returns entvar data from an entity.
* Use the var_* EntVars enum
*/
native any:get_entvar(const index, const EntVars:var, any:...);

/*
* Sets usercmd data.
* Use the ucmd_* UCmd enum
*/
native set_ucmd(const ucmd, const UCmd:var, any:...);

/*
* Returns entvar data from an entity.
* Use the ucmd_* UCmd enum
*/
native any:get_ucmd(const ucmd, const UCmd:var, any:...);

/*
* Set name of the map
*
* @param mapname	Change the name of the map.
*
* @noreturn
*
*/
native rh_set_mapname(const mapname[]);

/*
* Get name of the map
*
* @param output		Buffer to copy mapname to
* @param len		Maximum buffer size
* @param type		MNT_SET return the name of the current map
*			MNT_TRUE return true the name of the current map independently of the set via rh_set_mapname
*
* @noreturn
*
*/
native rh_get_mapname(output[], len, MapNameType:type = MNT_SET);

/*
* Reset to true map name
*
* @noreturn
*
*/
native rh_reset_mapname();

/*
* Emits a sound from an entity from the engine.
*
* @param entity		Entity index or use 0 to emit from worldspawn at the specified position
* @param recipient	Recipient index or use 0 to heard for all clients
* @param channel	Channel to emit from
* @param sample		Sound file to emit
* @param vol		Volume in percent
* @param attn		Sound attenuation
* @param flags		Emit flags
* @param pitch		Sound pitch
* @param emitFlags	Additional Emit2 flags, look at the defines like SND_EMIT2_*
* @param origin		Specify origin and only on "param" entity worldspawn that is 0
*
* @return		true if successfully sounds are emitted, false otherwise
*
*/
native bool:rh_emit_sound2(const entity, const recipient, const channel, const sample[], Float:vol = VOL_NORM, Float:attn = ATTN_NORM, const flags = 0, const pitch = PITCH_NORM, emitFlags = 0, const Float:origin[3] = {0.0,0.0,0.0});

/*
* Forces an userinfo update
*
* @param playerEntIndex    Player entity index (starts from 1)
*
* @noreturn
*/
native rh_update_user_info(playerEntIndex);