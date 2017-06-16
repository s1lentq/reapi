#pragma once

enum
{
	MAX_KV_LEN = 127,
	MAX_INFO_STRING = 256
};

enum WpnInfo
{
	WI_ID,
	WI_COST,
	WI_CLIP_COST,
	WI_BUY_CLIP_SIZE,
	WI_GUN_CLIP_SIZE,
	WI_MAX_ROUNDS,
	WI_AMMO_TYPE,
	WI_AMMO_NAME,
	WI_NAME,
};

void RegisterNatives_Misc();
