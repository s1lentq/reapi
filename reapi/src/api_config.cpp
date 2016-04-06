#include "precompiled.h"

CAPI_Config api_cfg;

CAPI_Config::CAPI_Config() : m_api_rehlds(false), m_api_regame(false)
{

}

bool CAPI_Config::Init()
{
	m_api_rehlds = RehldsApi_Init();
	m_api_regame = RegamedllApi_Init();

	return true;
}
