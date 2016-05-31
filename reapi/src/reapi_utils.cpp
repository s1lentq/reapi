#include "precompiled.h"

void Broadcast(const char *sentence)
{
	char text[128];
	snprintf(text, sizeof text, "%!MRAD_%s", sentence);

	g_pengfuncsTable->pfnMessageBegin(MSG_BROADCAST, gmsgSendAudio, NULL, NULL);
	g_pengfuncsTable->pfnWriteByte(0);
	g_pengfuncsTable->pfnWriteString(text);
	g_pengfuncsTable->pfnWriteShort(100);
	g_pengfuncsTable->pfnMessageEnd();
}

void UpdateTeamScores()
{
	g_pengfuncsTable->pfnMessageBegin(MSG_ALL, gmsgTeamScore, NULL, NULL);
	g_pengfuncsTable->pfnWriteString("CT");
	g_pengfuncsTable->pfnWriteShort(CSGameRules()->m_iNumCTWins);
	g_pengfuncsTable->pfnMessageEnd();

	g_pengfuncsTable->pfnMessageBegin(MSG_ALL, gmsgTeamScore, NULL, NULL);
	g_pengfuncsTable->pfnWriteString("TERRORIST");
	g_pengfuncsTable->pfnWriteShort(CSGameRules()->m_iNumTerroristWins);
	g_pengfuncsTable->pfnMessageEnd();
}

bool RemovePlayerItem(CBasePlayer *pPlayer, const char* szItemName)
{
	for (auto pItem : pPlayer->m_rgpPlayerItems) {
		while (pItem != nullptr)
		{
			if (FClassnameIs(pItem->pev, szItemName))
			{
				CBasePlayerWeapon *pWeapon = static_cast<CBasePlayerWeapon *>(pItem);
				if (pWeapon->IsWeapon()) {
					pWeapon->RetireWeapon();
				}

				pPlayer->pev->weapons &= ~(1 << pItem->m_iId);
				pPlayer->RemovePlayerItem(pItem);
				pItem->Kill();
				return true;
			}

			pItem = pItem->m_pNext;
		}
	}

	return false;
}

void SendItemStatus(CBasePlayer *pPlayer)
{
	int itemStatus = 0;
	if (pPlayer->m_bHasNightVision)
		itemStatus |= ITEM_STATUS_NIGHTVISION;

	if (pPlayer->m_bHasDefuser)
		itemStatus |= ITEM_STATUS_DEFUSER;

	MESSAGE_BEGIN(MSG_ONE, gmsgItemStatus, NULL, pPlayer->pev);
		WRITE_BYTE(itemStatus);
	MESSAGE_END();
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
