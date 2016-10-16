#pragma once

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>			// for strncpy(), etc
#include <vector>				// std::vector

#include <extdll.h>
#include <eiface.h>
#include <meta_api.h>

#include <cbase.h>
#include <pm_defs.h>
#include <pm_defs.h>
#include <pm_movevars.h>
#include <com_progdefs.h>

#include <osdep.h>			// win32 vsnprintf, etc
#include <osconfig.h>
#include <sdk_util.h>
#include <platform.h>

// regamedll API
#include "gamerules.h"
#include "regamedll_api.h"
#include "mod_regamedll_api.h"

// rehlds API
#include "rehlds_api.h"
#include "mod_rehlds_api.h"

// VTC API
#include "vtc_api.h"
#include "mod_vtc_api.h"

// Reunion API
#include "reunion_api.h"
#include "mod_reunion_api.h"

// AmxModX API
#include "amxxmodule.h"

#include "main.h"
#include "reapi_utils.h"
#include "api_config.h"
#include "hook_manager.h"
#include "hook_callback.h"
#include "member_list.h"

#include "natives_hookchains.h"
#include "natives_members.h"
#include "natives_misc.h"
#include "natives_addons.h"
#include "natives_helper.h"
