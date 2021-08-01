#pragma once

#define PARAMS_REQUIRE(x)		if (params[0] != x * sizeof(cell)) { AMXX_LogError(amx, AMX_ERR_NATIVE, "Invalid parameters count in %s", __FUNCTION__); return nullptr; }
#define NATIVE_MEMBER_REQUIRE(a,x)	if (!api_cfg.has##x()) { AMXX_LogError(amx, AMX_ERR_NATIVE, "Member (%s) is not available, required %s", memberlist[a]->member_name, #x); return 0; }

void RegisterNatives_HookChains();

template <typename T, size_t BUF_MAX, size_t BUF_SIZE = 1>
class CTempAnyData
{
public:
	T *Alloc()
	{
		m_current = (m_current + 1) % BUF_MAX;
		return m_data[m_current];
	}

private:
	size_t m_current = 0;
	T m_data[BUF_MAX][BUF_SIZE];
};
