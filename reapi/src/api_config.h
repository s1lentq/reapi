#pragma once

// reapi version
#include "reapi_version.inc"

class CAPI_Config {
public:
	CAPI_Config();
	void Init();

	bool hasReHLDS() const { return m_api_rehlds; }
	bool hasReGameDLL() const { return m_api_regame; }
	bool hasVTC() const { return m_api_vtc; }
	bool hasReunion() const { return m_api_reunion; }

	void ServerDeactivate() const;

private:
	// to provide API functions
	bool m_api_rehlds;		// some useful functions
	bool m_api_regame;		// some useful functions #2

	// future plans?
	bool m_api_vtc;			// for gag
	bool m_api_reunion;		// for information about authorization client

	//bool m_api_revoice;		// for gag #2
	//bool m_api_rechecker;		// for detection when checking and adding few files
};

extern CAPI_Config api_cfg;
