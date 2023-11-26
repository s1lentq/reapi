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
* Returns usercmd data from an entity.
* Use the ucmd_* UCmd enum
*/
native any:get_ucmd(const ucmd, const UCmd:var, any:...);

/*
* Sets a NetAdr var.
*
* @param var        The specified mvar, look at the enum NetAdrVars
*
* @return           1 on success.
*/
native set_netadr(const adr, const NetAdrVars:var, any:...);

/*
* Returns a NetAdr var
*
* @param var        The specified mvar, look at the enum NetAdrVars
*
* @return           If an integer or boolean or one byte, array or everything else is passed via the 3rd argument and more, look at the argument list for the specified mvar
*/
native any:get_netadr(const adr, const NetAdrVars:var, any:...);

/*
* Gets value for key in buffer
*
* @param pbuffer    Pointer to buffer
* @param key        Key string
* @param value      Buffer to copy value to
* @param maxlen     Maximum size of the buffer
*
* @return           Number of cells written to buffer
* @error            If invalid buffer handler provided, an error will be thrown.
*/
native get_key_value(const pbuffer, const key[], const value[], const maxlen);

/*
* Sets value for key in buffer
*
* @param pbuffer    Pointer to buffer
* @param key        Key string
* @param value      Value to set
*
* @noreturn
* @error            If invalid buffer handler provided, an error will be thrown.
*/
native set_key_value(const pbuffer, const key[], const value[]);

/*
* Gets an AMXX string buffer from a infobuffer pointer
*
* @param buffer     Info string pointer
* @param value      String to copy value to
* @param maxlen     Maximum size of the output buffer
*
* @return           Returns a string buffer on infobuffer pointer
*/
native get_key_value_buffer(const pbuffer, const output[], const maxlen);

/*
* Sets value string to entire buffer
*
* @param buffer     Pointer to buffer
* @param value      Value to set
* @param maxlen     Maximum size of the value buffer to set, -1 means copy all characters
*
* @return           1 on success, 0 otherwise
*/
native set_key_value_buffer(const pbuffer, const value[], const maxlen = -1);

/*
* Gets the position of the bone
*
* @param entity     Entity index
* @param bone       Number of the bone
* @param vecOrigin  Array to store origin in
* @param vecAngles  Array to store angles in
*
* @return           1 on success, 0 otherwise
* @error            If the index is not within the range of 1 to maxEntities or
*                   the entity is not valid, an error will be thrown.
*/
native GetBonePosition(const entity, const bone, Float:vecOrigin[3], Float:vecAngles[3] = {0.0, 0.0, 0.0});

/*
* Gets the position of the attachment
*
* @param entity     Entity index
* @param attachment Number of the attachment
* @param vecOrigin  Array to store origin in
* @param vecAngles  Array to store angles in
*
* @return           1 on success, 0 otherwise
* @error            If the index is not within the range of 1 to maxEntities or
*                   the entity is not valid, an error will be thrown.
*/
native GetAttachment(const entity, const attachment, Float:vecOrigin[3], Float:vecAngles[3] = {0.0, 0.0, 0.0});

/*
* Sets body group value based on entity's model group
*
* @param entity     Entity index
* @param group      Number of entity's model group index
* @param value      Value to assign
*
* @return           1 on success, 0 otherwise
* @error            If the index is not within the range of 1 to maxEntities or
*                   the entity is not valid, an error will be thrown.
*      
*/      
native SetBodygroup(const entity, const group, const value);

/*
* Gets body group value based on entity's model group
*
* @param entity     Entity index
* @param group      Number of entity's model group index
*
* @return           Body group value
* @error            If the index is not within the range of 1 to maxEntities or
*                   the entity is not valid, an error will be thrown.
*      
*/ 
native GetBodygroup(const entity, const group);

/*
* Gets sequence information based on entity's model current sequence index
*
* @param entity             Entity index
* @param piFlags            Sequence flags (1 = sequence loops)
* @param pflFrameRate       Sequence framerate
* @param pflGroundSpeed     Sequence ground speed
*
* @return                   True on success, false otherwise
* @error                    If the index is not within the range of 1 to maxEntities or
*                           the entity is not valid, an error will be thrown.
*      
*/ 
native bool:GetSequenceInfo(const entity, &piFlags, &Float:pflFrameRate, &Float:pflGroundSpeed);

/*
* Sets the name of the map.
*
* @param mapname     New map name.
*
* @noreturn
*/
native rh_set_mapname(const mapname[]);

/*
* Gets the name of the map.
*
* @param output     Buffer to copy map name to
* @param len        Maximum buffer size
* @param type       MNT_SET will return the name of the current map
*                   MNT_TRUE will return the original map name independant of the name set with via rh_set_mapname
*
* @noreturn
*/
native rh_get_mapname(output[], len, MapNameType:type = MNT_SET);

/*
* Reverts back the original map name.
*
* @noreturn
*/
native rh_reset_mapname();

/*
* Emits a sound from an entity from the engine.
*
* @param entity     Entity index or use 0 to emit from worldspawn at the specified position
* @param recipient  Recipient index or use 0 to make all clients hear it
* @param channel    Channel to emit from
* @param sample     Sound file to emit
* @param vol        Volume in percents
* @param attn       Sound attenuation
* @param flags      Emit flags
* @param pitch      Sound pitch
* @param emitFlags  Additional Emit2 flags, look at the defines like SND_EMIT2_*
* @param origin     Specify origin and only on "param" entity worldspawn that is 0
*
* @return           true if the emission was successfull, false otherwise
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

/*
* Kicks a client from server with message
*
* @param index     Client index
* @param message   Message that will be sent to client when it is deleted from server
*
* @noreturn
*
*/
native rh_drop_client(const index, const message[] = "");

/*
* -
*
* @param output     Buffer to copy the ip address
* @param len        Maximum buffer size
*
* @noreturn
*
*/
native rh_get_net_from(output[], len);

/*
* Returns client's netchan playing time in seconds.
*
* @param index     Client index
*
* @return          Netchan connection time in seconds or 0 if client index is invalid or client is not connected
*/
native rh_get_client_connect_time(const index);
