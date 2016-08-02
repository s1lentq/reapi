#include "precompiled.h"

void Broadcast(const char *sentence)
{
	char text[128];
	snprintf(text, sizeof text, "%!MRAD_%s", sentence);

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
