#ifdef UNFINISHED

// mhook.h - class and types to describe hooks and hooklists

/*
 * Copyright (c) 2001-2003 Will Day <willday@hpgx.net>
 *
 *    This file is part of Metamod.
 *
 *    Metamod is free software; you can redistribute it and/or modify it
 *    under the terms of the GNU General Public License as published by the
 *    Free Software Foundation; either version 2 of the License, or (at
 *    your option) any later version.
 *
 *    Metamod is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Metamod; if not, write to the Free Software Foundation,
 *    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *    In addition, as a special exception, the author gives permission to
 *    link the code of this program with the Half-Life Game Engine ("HL
 *    Engine") and Modified Game Libraries ("MODs") developed by Valve,
 *    L.L.C ("Valve").  You must obey the GNU General Public License in all
 *    respects for all of the code used other than the HL Engine and MODs
 *    from Valve.  If you modify this file, you may extend this exception
 *    to your version of the file, but you are not obligated to do so.  If
 *    you do not wish to do so, delete this exception statement from your
 *    version.
 *
 */

#ifndef MHOOK_H
#define MHOOK_H

#include "plinfo.h"			// plid_t, etc
#include "types_meta.h"		// mBOOL
#include "osdep.h"			// MUTEX_T, etc

#define MAX_HOOKS	100

// Particular game events that we detect, though whatever means we can best
// find.
typedef enum {
	EV_NONE = 0,			// no event here...
	// non-log detected
	EV_PLAYER_CONNECT,		// ie ClientConnect
	EV_PLAYER_ENTER,		// ie ClientPutInServer
	EV_PLAYER_LEAVE,		// ie ClientDisconnect (opposite PutInServer)
	EV_PLAYER_SPAWN,		// deadflag change to DEAD_NO
	EV_PLAYER_DEATH,		// deadflag change to DEAD_DEAD
	EV_PLAYER_CHANGE_NAME,	// netname change in ClientUserInfoChanged
	// log detected
	EV_PLAYER_JOIN_TEAM,	// ie "Joe<15><785><>" joined team "CT"
	EV_PLAYER_SUICIDE,		// ie "Joe<15><785><CT>" committed suicide ...
	EV_PLAYER_CHANGE_ROLE,	// TFC: ie "Joe<15><785><Red>" changed role to "Pyro"
	EV_TEAM_KILL,			// ie "Joe<15><785><CT>" killed "Bob<16><342><CT>" ...
	EV_WEAPON_KILL,			// ie "Joe<15><785><CT>" killed "Sam<17><197><TERRORIST>" with "sg552"
	EV_TEAM_SCORE,			// ie Team "CT" scored "7" with "2" players
} game_event_t;

// Info corresponding to a player, in particular the info found in the logline.
typedef struct {
	char *name;
	int userid;
	int wonid;
	char *team;
} event_player_t;

// Info for an event, mostly corresponding to info from a logline.
typedef struct {
	game_event_t evtype;	// specific event, if identified.
	char *buf;				// copy of the logmsg, with embedded NULLs
	event_player_t *player;	
	char *action;			// "triggered" string, or a generic action string
	event_player_t *target;
	char *with;
} event_args_t;

// Types for callback functions to be called for requested event/logline.
typedef		void (*event_func_t)	(game_event_t event, event_args_t *args, 
		const char *logline);
typedef		void (*logmatch_func_t)	(const char *pattern, event_args_t *args, 
		const char *logline);

// The 4 types of hook requests we accept.
typedef enum {
	H_NONE = 0,
	H_EVENT,				// Specific event, from a short list.
	H_TRIGGER,				// A given "triggered" string.
	H_STRING,				// Any substring of logline.
	H_REGEX,				// A regular expression matching of logline.
} hook_t;


// Class for individual hook function, as registered by a plugin.
class MHook {
	friend class MHookList;
	friend class MFuncQueue;
	private:
	// data:
		int index;
		hook_t type;			// EVENT, TRIGGER, etc
		plid_t plid;
		int pl_index;			// index of matching plugin
		void *pfnHandle;
		game_event_t event;		// if type is H_EVENT
		const char *match;		// if type is TRIGGER, STRING, or REGEX
	// Copy/Assignment constructors, to satisfy -Weffc++.
	// Note however, we declare them private and don't define them, since
	// we don't ever want to copy or assign instances of the class.
	// (thanks to O'Reilly "C++: The Core Language", page 113)
		MHook(const MHook &src);
		void operator=(const MHook &src);
	// constructors:
		MHook(void);
		MHook(int idx, plid_t pid, game_event_t evt, event_func_t pfn);
		MHook(int idx, plid_t pid, hook_t tp, const char *cp, logmatch_func_t pfn);
	// functions:
		mBOOL call(event_args_t *args, const char *logline);
		mBOOL enqueue(MFuncQueue *mfq, event_args_t *args, const char *logline);
	public:
		// no public interfaces; everything done from friend MHookList.
};


// Class for list of registered hook functions.
class MHookList {
	private:
	// data:
		MHook *hlist[MAX_HOOKS];
		int size;			// set to MAX_HOOKS in constructor
		int endlist;
		MUTEX_T mx_hlist;
		int MXlock(void) { return(MUTEX_LOCK(&mx_hlist)); };
		int MXunlock(void) { return(MUTEX_UNLOCK(&mx_hlist)); };
	public:
	// constructor:
		MHookList(void);
	// functions:
		int add(plid_t plid, game_event_t event, event_func_t pfnHandle);
		int add(plid_t plid, hook_t type, const char *match, 
				logmatch_func_t pfnHandle);
		mBOOL remove(plid_t plid, int hindex);
		int remove_all(plid_t plid);
		mBOOL call(event_args_t *args, const char *logline);
		mBOOL enqueue(MFuncQueue *mfq, hook_t htype, event_args_t *evargs, 
				const char *logline);
		char *str_htype(hook_t htype);
};

#endif /* MHOOK_H */

#endif /* UNFINISHED */
