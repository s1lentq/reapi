#include "precompiled.h"

/*
* Get client protocol
*
* @param index  Client index
*
* @return       Client protocol
*
* native REU_GetProtocol(const index);
*/
cell AMX_NATIVE_CALL REU_GetProtocol(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };

	CHECK_ISPLAYER(arg_index);

	return g_ReunionApi->GetClientProtocol(params[arg_index] - 1);
}

/*
* Get client auth type
*
* @param index  Client index
*
* @return       Client auth type
*
* native REU_GetAuthtype(const index);
*/
cell AMX_NATIVE_CALL REU_GetAuthtype(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };

	CHECK_ISPLAYER(arg_index);

	return g_ReunionApi->GetClientAuthtype(params[arg_index] - 1);
}

/*
* Get client authkey
*
* @param index  Client index
* @param index  Buffer to copy the authkey
* @param index  Maximum buffer size
*
* @return       Number of cells copied to buffer
*
* native REU_GetAuthKey(const index, dest[], maxlen);
*/
cell AMX_NATIVE_CALL REU_GetAuthKey(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_output, arg_maxlen };

	CHECK_ISPLAYER(arg_index);

	int clientId = params[arg_index] - 1;

	char buffer[256];
	size_t size = g_ReunionApi->GetClientAuthdata(clientId, buffer, sizeof buffer);
	if (size <= 0)
		return 0;

	size_t numToCopy = min<size_t>(size, params[arg_maxlen]);
	cell *dest = getAmxAddr(amx, params[arg_output]);
	setAmxString(dest, buffer, numToCopy);
	return numToCopy;
}

/*
* Check if the client is running RevEmu with limited user rights.
*
* @param index  Client index
*
* @return       1/0
*
* native REU_IsRevemuWithoutAdminRights(const index);
*/
cell AMX_NATIVE_CALL REU_IsRevemuWithoutAdminRights(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index };

	CHECK_ISPLAYER(arg_index);

	int clientId = params[arg_index] - 1;
	if (g_ReunionApi->GetClientAuthtype(clientId) != DP_AUTH_REVEMU)
		return FALSE;

	char buffer[256];
	size_t size = g_ReunionApi->GetClientAuthdata(clientId, buffer, sizeof buffer);

	for (size_t i = 0; i < size; i++) {
		if (!isdigit(buffer[i]))
			return FALSE;
	}

	return TRUE;
}

AMX_NATIVE_INFO Reunion_Natives[] =
{
	{ "REU_GetProtocol",                REU_GetProtocol                },
	{ "REU_GetAuthtype",                REU_GetAuthtype                },
	{ "REU_GetAuthKey",                 REU_GetAuthKey                 },
	{ "REU_IsRevemuWithoutAdminRights", REU_IsRevemuWithoutAdminRights },

	{ nullptr, nullptr }
};

void RegisterNatives_Reunion()
{
	if (!api_cfg.hasReunion())
		fillNatives(Reunion_Natives, [](AMX *amx, cell *params) -> cell { AMXX_LogError(amx, AMX_ERR_NATIVE, "%s: isn't available", "Reunion"); return FALSE; });

	g_amxxapi.AddNatives(Reunion_Natives);
}
