#include "precompiled.h"

/*
* Compares the entity to specified a classname.
* @note This native also checks the validity of an entity.
*
* @return		true/false
*
* native bool:FClassnameIs(const entityIndex, const className[]);
*/
cell AMX_NATIVE_CALL amx_FClassnameIs(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_classname };

	int nEntityIndex = params[arg_index];
	if (nEntityIndex < 0 || nEntityIndex > gpGlobals->maxEntities) {
		return FALSE;
	}

	edict_t *pEdict = edictByIndex(nEntityIndex);
	if (pEdict && FClassnameIs(pEdict, getAmxString(amx, params[arg_classname]))) {
		return TRUE;
	}

	return FALSE;
}

AMX_NATIVE_INFO Natives_Common[] =
{
	{ "FClassnameIs", amx_FClassnameIs },

	{ nullptr, nullptr }
};

/*
* Check if the entity is valid
*
* @return		true/false
*
* native bool:is_entity(const entityIndex);
*/
cell AMX_NATIVE_CALL is_entity(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };

	int nIndex = params[arg_index];
	if (nIndex < 0 || nIndex > gpGlobals->maxEntities) {
		return FALSE;
	}

	auto pEntity = getPrivate<CBaseEntity>(nIndex);
	if (!pEntity) {
		return FALSE;
	}

	// if it is the index of the player
	if (pEntity->IsPlayer() && pEntity->has_disconnected) {
		return FALSE;
	}

	return TRUE;
}

/*
* Check if the rehlds is available
*
* @return		true/false
*
* native bool:is_rehlds();
*/
cell AMX_NATIVE_CALL is_rehlds(AMX *amx, cell *params)
{
	return (cell)api_cfg.hasReHLDS();
}

/*
* Check if the regamedll is available
*
* @return		true/false
*
* native bool:is_regamedll();
*/
cell AMX_NATIVE_CALL is_regamedll(AMX *amx, cell *params)
{
	return (cell)api_cfg.hasReGameDLL();
}

/*
* Check if the reunion is available
*
* @return		true/false
*
* native bool:is_has_reunion();
*/
cell AMX_NATIVE_CALL has_reunion(AMX *amx, cell *params)
{
	return (cell)api_cfg.hasReunion();
}

/*
* Check if the vtc is available
*
* @return		true/false
*
* native bool:is_has_vtc();
*/
cell AMX_NATIVE_CALL has_vtc(AMX *amx, cell *params)
{
	return (cell)api_cfg.hasVTC();
}

AMX_NATIVE_INFO Natives_Checks[] =
{
	{ "is_entity", is_entity },
	{ "is_rehlds", is_rehlds },
	{ "is_regamedll", is_regamedll },
	{ "has_reunion", has_reunion },
	{ "has_vtc", has_vtc }
};

void RegisterNatives_Common()
{
	g_amxxapi.AddNatives(Natives_Common);
	g_amxxapi.AddNatives(Natives_Checks);
}
