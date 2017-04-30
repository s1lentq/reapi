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
* Sets the name of the map.
*
* @param mapname	New map name.
*
* @noreturn
*
*/
native rh_set_mapname(const mapname[]);

/*
* Gets the name of the map.
*
* @param output		Buffer to copy map name to
* @param len		Maximum buffer size
* @param type		MNT_SET will return the name of the current map
*			MNT_TRUE will return the original map name independant of the name set with via rh_set_mapname
*
* @noreturn
*
*/
native rh_get_mapname(output[], len, MapNameType:type = MNT_SET);

/*
* Reverts back the original map name.
*
* @noreturn
*
*/
native rh_reset_mapname();

/*
* Emits a sound from an entity from the engine.
*
* @param entity		Entity index or use 0 to emit from worldspawn at the specified position
* @param recipient	Recipient index or use 0 to make all clients hear it
* @param channel	Channel to emit from
* @param sample		Sound file to emit
* @param vol		Volume in percents
* @param attn		Sound attenuation
* @param flags		Emit flags
* @param pitch		Sound pitch
* @param emitFlags	Additional Emit2 flags, look at the defines like SND_EMIT2_*
* @param origin		Specify origin and only on "param" entity worldspawn that is 0
*
* @return		true if the emission was successfull, false otherwise
*
*/
native bool:rh_emit_sound2(const entity, const recipient, const channel, const sample[], Float:vol = VOL_NORM, Float:attn = ATTN_NORM, const flags = 0, const pitch = PITCH_NORM, emitFlags = 0, const Float:origin[3] = {0.0,0.0,0.0});

/*
* Forces an userinfo update.
*
* @param playerEntIndex    Player entity index (starts from 1)
*
* @noreturn
*/
native rh_update_user_info(playerEntIndex);