#include "precompiled.h"

// native set_member(_index, any:_member, any:...);
cell AMX_NATIVE_CALL set_member(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_member, arg_value, arg_elem };
	member_t *member = memberlist[params[arg_member]];

	if (member == nullptr) {
		MF_LogError(amx, AMX_ERR_NATIVE, "set_member: unknown member id %i", params[arg_member]);
		return FALSE;
	}

	edict_t *pEdict = INDEXENT(params[arg_index]);
	if (pEdict == nullptr || pEdict->pvPrivateData == nullptr) {
		MF_LogError(amx, AMX_ERR_NATIVE, "set_member: invalid or uninitialized entity");
		return FALSE;
	}
	
	cell* value = getAmxAddr(amx, params[arg_value]);
	size_t element = (PARAMS_COUNT == 4) ? *getAmxAddr(amx, params[arg_elem]) : 0;

	return set_member(pEdict->pvPrivateData, member, element, value);
}

// native any:get_member(_index, any:_member, any:...);
cell AMX_NATIVE_CALL get_member(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_index, arg_member, arg_3, arg_4 };
	member_t *member = memberlist[params[arg_member]];

	if (member == nullptr) {
		MF_LogError(amx, AMX_ERR_NATIVE, "get_member: unknown member id %i", params[arg_member]);
		return FALSE;
	}

	edict_t *pEdict = INDEXENT(params[arg_index]);
	if (pEdict == nullptr || pEdict->pvPrivateData == nullptr) {
		MF_LogError(amx, AMX_ERR_NATIVE, "get_member: invalid or uninitialized entity");
		return FALSE;
	}

	cell* dest;
	size_t element;

	if (PARAMS_COUNT == 4) {
		dest = getAmxAddr(amx, params[arg_3]);
		element = *getAmxAddr(amx, params[arg_4]);
	}
	else if (PARAMS_COUNT == 3) {
		cell* arg3 = getAmxAddr(amx, params[arg_3]);

		if (isTypeReturnable(member->type)) {
			dest = nullptr;
			element = *arg3;
		}
		else {
			dest = arg3;
			element = 0;
		}
	}
	else {
		dest = nullptr;
		element = 0;
	}

	return get_member(pEdict->pvPrivateData, member, element, dest);
}

// native set_member_game(any:_member, any:...);
cell AMX_NATIVE_CALL set_member_game(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_member, arg_value, arg_elem };
	member_t *member = memberlist[params[arg_member]];

	if (member == nullptr) {
		MF_LogError(amx, AMX_ERR_NATIVE, "set_member_game: unknown member id %i", params[arg_member]);
		return FALSE;
	}

	if (g_pCSGameRules == nullptr || *g_pCSGameRules == nullptr) {
		MF_LogError(amx, AMX_ERR_NATIVE, "get_member_game: gamerules not initialized");
		return FALSE;
	}

	cell* value = getAmxAddr(amx, params[arg_value]);
	size_t element = (PARAMS_COUNT == 4) ? *getAmxAddr(amx, params[arg_elem]) : 0;

	return set_member(*g_pCSGameRules, member, element, value);
}

// native get_member_game(any:_member, any:...);
cell AMX_NATIVE_CALL get_member_game(AMX *amx, cell *params)
{
	enum args_e { arg_count, arg_member, arg_3, arg_4 };
	member_t *member = memberlist[params[arg_member]];

	if (member == nullptr) {
		MF_LogError(amx, AMX_ERR_NATIVE, "get_member_game: unknown member id %i", params[arg_member]);
		return FALSE;
	}

	if (g_pCSGameRules == nullptr || *g_pCSGameRules == nullptr) {
		MF_LogError(amx, AMX_ERR_NATIVE, "get_member_game: gamerules not initialized");
		return FALSE;
	}

	cell* dest;
	size_t element;
	
	if (PARAMS_COUNT == 4) {
		dest = getAmxAddr(amx, params[arg_3]);
		element = *getAmxAddr(amx, params[arg_4]);
	}
	else if (PARAMS_COUNT == 3) {
		cell* arg3 = getAmxAddr(amx, params[arg_3]);

		if (isTypeReturnable(member->type)) {
			dest = nullptr;
			element = *arg3;
		}
		else {
			dest = arg3;
			element = 0;
		}
	}
	else {
		dest = nullptr;
		element = 0;
	}

	return get_member(*g_pCSGameRules, member, element, dest);
}

AMX_NATIVE_INFO Member_Natives[] =
{
	{ "set_member", set_member },
	{ "get_member", get_member },
	
	{ "set_member_game", set_member_game },
	{ "get_member_game", get_member_game },

	{ nullptr, nullptr }
};

void RegisterNatives_Members()
{
	if (api_cfg.hasReGameDLL())
		g_amxxapi.AddNatives(Member_Natives);
}

BOOL set_member(void* pdata, const member_t *member, size_t element, cell* value)
{
	switch (member->type) {
	case MEMBER_CLASSPTR:
		{
			// native set_member(_index, any:_member, _value, _elem);
			CBaseEntity *pEntity = CBaseEntity::Instance(INDEXENT(*value));
			set_member<CBaseEntity *>(pdata, member->offset, pEntity, element);
			return TRUE;
		}
	case MEMBER_EHANDLE:
		{
			// native set_member(_index, any:_member, _value, _elem);
			EHANDLE& ehandle = get_member<EHANDLE>(pdata, member->offset, element);
			edict_t *pEdictValue = INDEXENT(*value);
			ehandle.Set(pEdictValue);
			return TRUE;
		}
	case MEMBER_EDICT:
		{
			// native set_member(_index, any:_member, _value, _elem);
			edict_t *pEdictValue = INDEXENT(*value);
			set_member<edict_t *>(pdata, member->offset, pEdictValue, element);
			return TRUE;
		}
	case MEMBER_VECTOR:
		{
			// native set_member(_index, any:_member, Float:_value[3], _elem);
			Vector *pSource = (Vector *)value;
			set_member<Vector>(pdata, member->offset, *pSource, element);
			return TRUE;
		}
	case MEMBER_STRING:
		{
			// native set_member(_index, any:_member, const source[]);
			if (member->max_size > sizeof(char*)) {
				// char []
				char *source = getAmxString(value);
				char *dest = get_member_direct<char *>(pdata, member->offset);
				strncpy(dest, source, member->max_size - 1);
				dest[member->max_size - 1] = '\0';

			} else {
				// char *
				char *source = getAmxString(value);
				char *&dest = get_member<char *>(pdata, member->offset);
				g_ReGameFuncs->ChangeString(dest, source);
			}

			return TRUE;
		}
	case MEMBER_FLOAT:
	case MEMBER_INTEGER:
		{
			// native set_member(_index, any:_member, any:_value, _elem);
			set_member<int>(pdata, member->offset, *value, element);
			return TRUE;
		}
	case MEMBER_SHORT:
		{
			// native set_member(_index, any:_member, _value, _elem);
			set_member<short>(pdata, member->offset, *value, element);
			return TRUE;
		}
	case MEMBER_BYTE:
		{
			// native set_member(_index, any:_member, _value, _elem);
			set_member<byte>(pdata, member->offset, *value, element);
			return TRUE;
		}
	case MEMBER_BOOL:
		{
			// native set_member(_index, any:_member, bool:_value, _elem);
			set_member<bool>(pdata, member->offset, *value != 0, element);
			return TRUE;
		}
	case MEMBER_SIGNALS:
		{
			// native set_member(_index, any:_member, _value);
			CUnifiedSignals& signal = get_member<CUnifiedSignals>(pdata, member->offset, element);
			signal.Signal(*value);
			return TRUE;
		}
	case MEMBER_DOUBLE:
		{
			// native set_member(_index, any:_member, any:_value, _elem);
			set_member<double>(pdata, member->offset, *(float *)value, element);
			return TRUE;
		}

	case MEMBER_ENTITY:
	case MEMBER_EVARS:
	case MEBMER_REBUYSTRUCT:
		return FALSE;
	}

	return FALSE;
}

cell get_member(void* pdata, const member_t *member, size_t element, cell* dest)
{
	switch (member->type)
	{
	case MEMBER_CLASSPTR:
		// native any:get_member(_index, any:_member, element);
		return get_member<CBaseEntity *>(pdata, member->offset, element)->entindex();
	case MEMBER_EHANDLE:
		{
			// native any:get_member(_index, any:_member, element);
			EHANDLE ehandle = get_member<EHANDLE>(pdata, member->offset, element);
			edict_t *pEntity = ehandle.Get();
			if (pEntity != nullptr) {
				return ENTINDEX(pEntity);
			}
			return -1;
		}
	case MEMBER_EDICT:
		{
			// native any:get_member(_index, any:_member, element);
			edict_t *pEntity = get_member<edict_t *>(pdata, member->offset, element);
			if (pEntity != nullptr) {
				return ENTINDEX(pEntity);
			}

			return -1;
		}
	case MEMBER_VECTOR:
		{
			// native any:get_member(_index, any:_member, any:output[], element);
			if (!dest)
				return 0;

			cell* vecSrc = get_member_direct<cell *>(pdata, member->offset, element);

			dest[0] = vecSrc[0];
			dest[1] = vecSrc[1];
			dest[2] = vecSrc[2];
			return 1;
		}
	case MEMBER_STRING:
		{
			// native any:get_member(_index, any:_member, any:output[], maxlength);
			if (!dest)
				return 0;

			if (member->max_size > sizeof(char*)) {
				// char []
				const char *src = get_member_direct<const char *>(pdata, member->offset);
				setAmxString(dest, src, element);
			} else {
				// char *
				const char *src = get_member<const char *>(pdata, member->offset);
				if (src == nullptr) {
					setAmxString(dest, "", 1);
					return 0;
				}
				setAmxString(dest, src, element);
			}

			return 1;
		}
	case MEMBER_FLOAT:
	case MEMBER_INTEGER:
		// native any:get_member(_index, any:_member, element);
		return get_member<int>(pdata, member->offset, element);
	case MEMBER_SHORT:
		// native any:get_member(_index, any:_member, element);
		return get_member<short>(pdata, member->offset, element);
	case MEMBER_BYTE:
		// native any:get_member(_index, any:_member, element);
		return get_member<byte>(pdata, member->offset, element);
	case MEMBER_BOOL:
		// native any:get_member(_index, any:_member, element);
		return get_member<bool>(pdata, member->offset, element);
	case MEMBER_DOUBLE:
		// native any:get_member(_index, any:_member, element);
		return get_member<double>(pdata, member->offset, element);
	case MEMBER_SIGNALS:
		{
			enum {_Signal, _State};

			// native any:get_member(_index, any:_member, signals[2]);
			if (!dest)
				return 0;

			CUnifiedSignals& signal = get_member<CUnifiedSignals>(pdata, member->offset);

			int *pSignals = dest;
			pSignals[_Signal] = signal.GetSignal();
			pSignals[_State] = signal.GetState();
			return 1;
		}

	case MEMBER_ENTITY:
	case MEMBER_EVARS:
	case MEBMER_REBUYSTRUCT:
		return 0;
	}

	return 0;
}

bool isTypeReturnable(MType type)
{
	switch (type) {
	case MEMBER_FLOAT:
	case MEMBER_DOUBLE:
	case MEMBER_ENTITY:
	case MEMBER_CLASSPTR:
	case MEMBER_EDICT:
	case MEMBER_INTEGER:
	case MEMBER_SHORT:
	case MEMBER_BYTE:
	case MEMBER_BOOL:
		return true;

	default:
		return false;
	}
}
