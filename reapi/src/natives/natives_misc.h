#pragma once

enum GiveType
{
	GT_APPEND,          // Just give item
	GT_REPLACE,         // Give the item and remove all other weapons from the slot
	GT_DROP_AND_REPLACE // Give the item and drop all other weapons from the slot
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
	WI_SLOT,
};

void RegisterNatives_Misc();
