#pragma once

#include <string.h>
#include <new>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>			// for strncpy(), etc

#include <vector>				// std::vector

#include <extdll.h>
#include "reapi_utils.h"
#include <cbase.h>

#include "osdep.h"			// win32 vsnprintf, etc
#include "sdk_util.h"

#include <eiface.h>
#include <meta_api.h>
#include "amxxmodule.h"
#include "osconfig.h"

// gamedll
#include "gamerules.h"

// regamedll API
#include "regamedll_api.h"
#include "mod_regamedll_api.h"

// rehlds API
#include "rehlds_api.h"
#include "mod_rehlds_api.h"

#include "api_config.h"
#include "hook_manager.h"
#include "hook_callback.h"
#include "member_list.h"
#include "natives_hookchains.h"
#include "natives_members.h"

#undef DLLEXPORT
#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#define NOINLINE __declspec(noinline)
#else
#define DLLEXPORT __attribute__((visibility("default")))
#define NOINLINE __attribute__((noinline))
#define WINAPI		/* */
#endif
