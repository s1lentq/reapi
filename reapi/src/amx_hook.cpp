#include "precompiled.h"

CAmxxHookBase::CAmxxHookBase(AMX *amx, const char *funcname, int forwardIndex, int index) :
	m_fwdindex(forwardIndex),
	m_index(index),
	m_state(FSTATE_ENABLED),
	m_amx(amx)
{
	Q_strlcpy(m_CallbackName, funcname);
}

CAmxxHookBase::~CAmxxHookBase()
{
	if (m_fwdindex != -1)
	{
		g_amxxapi.UnregisterSPForward(m_fwdindex);
		m_fwdindex = -1;
	}
}

void CAmxxHookBase::Error(int error, const char *fmt, ...)
{
	va_list argptr;
	static char string[1024];
	va_start(argptr, fmt);
	vsprintf(string, fmt, argptr);
	va_end(argptr);

	auto scriptName = g_amxxapi.GetAmxScriptName(g_amxxapi.FindAmxScriptByAmx(m_amx));
	if (scriptName)
	{
		if ((scriptName = strrchr(scriptName, CORRECT_PATH_SEPARATOR)))
			scriptName++;
	}

	g_amxxapi.Log("Run time error %d (plugin \"%s\") (forward \"%s\")", error, scriptName, m_CallbackName);
	g_amxxapi.Log("%s", string);
}
