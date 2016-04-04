#include "precompiled.h"

CAPI_Config api_cfg;

bool CAPI_Config::Init()
{
	m_api_rehlds = RehldsApi_Init();
	m_api_regame = RegamedllApi_Init();

	return true;
}
