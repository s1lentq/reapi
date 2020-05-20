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
		AMXX_LogError(amx, AMX_ERR_NATIVE, "temp strings limit exceeded, contact reapi authors");
		return nullptr;
	}

	return m_strings[m_current++];
}

void CTempStrings::pop(size_t count)
{
	m_current -= count;
}

CBaseEntity *GiveNamedItemInternal(AMX *amx, CBasePlayer *pPlayer, const char *pszItemName, const size_t uid)
{
	edict_t *pEdict = CREATE_NAMED_ENTITY(ALLOC_STRING(pszItemName));
	if (FNullEnt(pEdict))
	{
		AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: Item \"%s\" failed to create!\n", __FUNCTION__, pszItemName);
		return nullptr;
	}

	pEdict->v.origin = pPlayer->pev->origin;
	pEdict->v.spawnflags |= SF_NORESPAWN;

	// In some cases, we must to sets unique id
	// for the entity before it will triggered a spawn.
	pEdict->v.impulse = uid;

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

void StudioFrameAdvanceEnt(edict_t *pEdict)
{
	float flInterval = gpGlobals->time - pEdict->v.animtime;
	if (flInterval <= 0.001f) {
		pEdict->v.animtime = gpGlobals->time;
		return;
	}

	if (pEdict->v.animtime == 0.0f) {
		flInterval = 0.0f;
	}

	studiohdr_t *pstudiohdr = static_cast<studiohdr_t *>(GET_MODEL_PTR(pEdict));
	if (!pstudiohdr) {
		return;
	}

	if (pEdict->v.sequence >= pstudiohdr->numseq || pEdict->v.sequence < 0) {
		return;
	}

	float flFrameRate = 256.0f;
	mstudioseqdesc_t *pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex) + int(pEdict->v.sequence);
	if (pseqdesc->numframes > 1)
	{
		flFrameRate = pseqdesc->fps * 256.0f / (pseqdesc->numframes - 1);
	}

	pEdict->v.frame += flInterval * flFrameRate * pEdict->v.framerate;
	pEdict->v.animtime = gpGlobals->time;

	if (pEdict->v.frame < 0.0f || pEdict->v.frame >= 256.0f)
	{
		// true if the sequence loops
		if (pseqdesc->flags & STUDIO_LOOPING)
			pEdict->v.frame -= int(pEdict->v.frame / 256.0f) * 256.0f;
		else
			pEdict->v.frame = (pEdict->v.frame < 0.0f) ? 0.0f : 255.0f;
	}
}

void FixupAngles(edict_t *pEdict, Vector &vecSrc)
{
	vecSrc.x -= pEdict->v.origin.x;
	vecSrc.y -= pEdict->v.origin.y;

	float x = vecSrc.x;
	float y = vecSrc.y;
	float c = cos((pEdict->v.angles.y * M_PI / 180.0));
	float s = sin((pEdict->v.angles.y * M_PI / 180.0));

	vecSrc.x = x * c - y * s;
	vecSrc.y = y * c + x * s;

	vecSrc.x += pEdict->v.origin.x;
	vecSrc.y += pEdict->v.origin.y;
}

void GetBonePosition(CBaseEntity *pEntity, int iBone, Vector *pVecOrigin, Vector *pVecAngles)
{
	Vector vecOrigin, vecAngles;
	edict_t *pEdict = pEntity->edict();

	pEntity->pev->angles.x = -pEntity->pev->angles.x;
	GET_BONE_POSITION(pEdict, iBone, vecOrigin, vecAngles);
	pEntity->pev->angles.x = -pEntity->pev->angles.x;

	if (!pEntity->IsPlayer()) {
		FixupAngles(pEdict, vecOrigin);
	}

	if (pVecOrigin) {
		*pVecOrigin = vecOrigin;
	}

	if (pVecAngles) {
		*pVecAngles = vecAngles;
	}
}

void GetAttachment(CBaseEntity *pEntity, int iBone, Vector *pVecOrigin, Vector *pVecAngles)
{
	Vector vecOrigin, vecAngles;
	edict_t *pEdict = pEntity->edict();

	// force to update frame
	StudioFrameAdvanceEnt(pEdict);

	GET_ATTACHMENT(pEdict, iBone, vecOrigin, vecAngles);

	if (!pEntity->IsPlayer()) {
		FixupAngles(pEdict, vecOrigin);
	}

	if (pVecOrigin) {
		*pVecOrigin = vecOrigin;
	}

	if (pVecAngles) {
		*pVecAngles = vecAngles;
	}
}

void RemoveOrDropItem(CBasePlayer *pPlayer, CBasePlayerItem *pItem, GiveType type)
{
	switch (type)
	{
	case GT_DROP_AND_REPLACE:
		pPlayer->CSPlayer()->DropPlayerItem(STRING(pItem->pev->classname));
		break;
	case GT_REPLACE:
		pPlayer->pev->weapons &= ~(1 << pItem->m_iId);
		pPlayer->RemovePlayerItem(pItem);
		pItem->Kill();
		break;
	case GT_APPEND:
	default:
		break;
	}
}

const char *getATypeStr(AType type)
{
	static constexpr const char *s_ATypes[]
	{
		"ATYPE_INTEGER",
		"ATYPE_FLOAT",
		"ATYPE_STRING",
		"ATYPE_CLASSPTR",
		"ATYPE_EDICT",
		"ATYPE_EVARS",
		"ATYPE_BOOL"
	};

	if (type >= arraysize(s_ATypes))
		return "";

	return s_ATypes[type];
}
