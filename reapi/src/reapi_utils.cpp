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
