#include "precompiled.h"

void Broadcast(const char *sentence)
{
	char text[128];
	snprintf(text, sizeof text, "%%!MRAD_%s", sentence);

	EMESSAGE_BEGIN(MSG_BROADCAST, gmsgSendAudio);
		EWRITE_BYTE(0);
		EWRITE_STRING(text);
		EWRITE_SHORT(100);
	EMESSAGE_END();
}

struct {
	TeamName team;
	ModelName model;

} modelStruct[] = {
	{ TERRORIST, MODEL_TERROR },
	{ TERRORIST, MODEL_LEET },
	{ TERRORIST, MODEL_ARCTIC },
	{ TERRORIST, MODEL_GUERILLA },
	{ CT, MODEL_URBAN },
	{ CT, MODEL_GSG9 },
	{ CT, MODEL_GIGN },
	{ CT, MODEL_SAS },
};

ModelName GetModelAuto(TeamName team)
{
	int cur = 0;
	const int numSkin = 4;
	for (auto& it : modelStruct) {
		if (it.team != team) {
			++cur;
			continue;
		}

		return modelStruct[RANDOM_LONG(cur, cur + numSkin - 1)].model;
	}

	return MODEL_UNASSIGNED;
}

CTempStrings::CTempStrings()
{
	m_current = 0;
}


char* CTempStrings::push(AMX* amx)
{
	if (m_current == STRINGS_MAX) {
		MF_LogError(amx, AMX_ERR_NATIVE, "temp strings limit exceeded, contact reapi authors");
		return nullptr;
	}

	return m_strings[m_current++];
}

void CTempStrings::pop(size_t count)
{
	m_current -= count;
}

CBaseEntity *GiveNamedItemInternal(AMX *amx, CBasePlayer *pPlayer, const char *pszItemName)
{
	edict_t *pEdict = CREATE_NAMED_ENTITY(ALLOC_STRING(pszItemName));
	if (FNullEnt(pEdict))
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: Item \"%s\" failed to create!\n", __FUNCTION__, pszItemName);
		return nullptr;
	}

	pEdict->v.origin = pPlayer->pev->origin;
	pEdict->v.spawnflags |= SF_NORESPAWN;

	MDLL_Spawn(pEdict);
	MDLL_Touch(pEdict, ENT(pPlayer->pev));

	CBaseEntity *pEntity = getPrivate<CBaseEntity>(pEdict);

	// not allow the item to fall to the ground.
	if (FNullEnt(pEntity->pev->owner) || pEntity->pev->owner != pPlayer->edict())
	{
		pEntity->pev->targetname = iStringNull;
		pEntity->pev->flags |= FL_KILLME;

		return nullptr;
	}

	return pEntity;
}
