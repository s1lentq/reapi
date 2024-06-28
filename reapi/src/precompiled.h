#pragma once

// C
#include <string.h>			// for strncpy(), etc
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

// C++
#include <vector>				// std::vector
#include <list>					// std::list

// platform defs
#include "platform.h"

// cssdk
#include <extdll.h>
#include <eiface.h>

// rewrite on own custom preprocessor definitions INDEXENT and ENTINDEX from cbase.h
#include "type_conversion.h"

#include <pm_defs.h>
#include <pm_movevars.h>
#include <com_progdefs.h>

// metamod SDK
#include <meta_api.h>

// regamedll API
#include <regamedll_api.h>
#include "mod_regamedll_api.h"
#include <mapinfo.h>
#include <studio.h>

// rehlds API
#include <rehlds_api.h>
#include "mod_rehlds_api.h"

// VTC API
#include <vtc_api.h>
#include "mod_vtc_api.h"

// Reunion API
#include <reunion_api.h>
#include "mod_reunion_api.h"

// rechecker API
#include <rechecker_api.h>
#include "mod_rechecker_api.h"

// AmxModX API
#include "amxxmodule.h"

#include "info.h"
#include "com_client.h"

// reapi main
#include "main.h"
#include "api_config.h"
#include "hook_manager.h"
#include "hook_message_manager.h"
#include "hook_callback.h"
#include "entity_callback_dispatcher.h"
#include "member_list.h"

// natives
#include "natives_hookchains.h"
#include "natives_hookmessage.h"
#include "natives_members.h"
#include "natives_misc.h"
#include "natives_common.h"
#include "natives_helper.h"

// addons
#include "natives_vtc.h"
#include "natives_reunion.h"
#include "natives_rechecker.h"

#include "reapi_utils.h"
