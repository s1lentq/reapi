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
