#include "precompiled.h"

void Broadcast(const char *sentence)
{
	char text[32];

	strcpy(text, "%!MRAD_");
	strcat(text, UTIL_VarArgs("%s", sentence));

	static int gmsgSendAudio = 0;
	if (gmsgSendAudio == 0 && !(gmsgSendAudio = REG_USER_MSG("SendAudio", -1)))
		return;

	g_pengfuncsTable->pfnMessageBegin(MSG_BROADCAST, REG_USER_MSG("SendAudio", -1), NULL, NULL);
	g_pengfuncsTable->pfnWriteByte(0);
	g_pengfuncsTable->pfnWriteString(text);
	g_pengfuncsTable->pfnWriteShort(100);
	g_pengfuncsTable->pfnMessageEnd();
}

void UpdateTeamScores()
{
	static int gmsgTeamScore = 0;
	if (gmsgTeamScore == 0 && !(gmsgTeamScore = REG_USER_MSG("TeamScore", -1)))
		return;

	g_pengfuncsTable->pfnMessageBegin(MSG_ALL, gmsgTeamScore, NULL, NULL);
	g_pengfuncsTable->pfnWriteString("CT");
	g_pengfuncsTable->pfnWriteShort((*g_pCSGameRules)->m_iNumCTWins);
	g_pengfuncsTable->pfnMessageEnd();

	g_pengfuncsTable->pfnMessageBegin(MSG_ALL, gmsgTeamScore, NULL, NULL);
	g_pengfuncsTable->pfnWriteString("TERRORIST");
	g_pengfuncsTable->pfnWriteShort((*g_pCSGameRules)->m_iNumTerroristWins);
	g_pengfuncsTable->pfnMessageEnd();
}
