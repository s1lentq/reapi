/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
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
#pragma once

#include "hookchains.h"
#include "interface.h"

#define RECHECKER_API_VERSION_MAJOR 2
#define RECHECKER_API_VERSION_MINOR 1

enum ResourceType_e
{
	RES_TYPE_NONE = 0,
	RES_TYPE_EXISTS,		// to comparison with the specified hash value
	RES_TYPE_MISSING,		// check it missing file on client
	RES_TYPE_IGNORE,		// ignore the specified hash value
	RES_TYPE_HASH_ANY,		// any file with any the hash value
};

class IResourceBuffer;

// FileConsistencyProcess hook
typedef IVoidHookChain<IGameClient *, IResourceBuffer *, ResourceType_e, uint32> IRecheckerHook_FileConsistencyProcess;
typedef IVoidHookChainRegistry<IGameClient *, IResourceBuffer *, ResourceType_e, uint32> IRecheckerHookRegistry_FileConsistencyProcess;

// CmdExec hook
typedef IVoidHookChain<IGameClient *, IResourceBuffer *, char *, uint32> IRecheckerHook_CmdExec;
typedef IVoidHookChainRegistry<IGameClient *, IResourceBuffer *, char *, uint32> IRecheckerHookRegistry_CmdExec;

// FileConsistencyFinal hook
typedef IVoidHookChain<IGameClient *> IRecheckerHook_FileConsistencyFinal;
typedef IVoidHookChainRegistry<IGameClient *> IRecheckerHookRegistry_FileConsistencyFinal;

class IRecheckerHookchains {
protected:
	virtual ~IRecheckerHookchains() {}

public:
	virtual IRecheckerHookRegistry_FileConsistencyProcess *FileConsistencyProcess() = 0;
	virtual IRecheckerHookRegistry_CmdExec *CmdExec() = 0;
	virtual IRecheckerHookRegistry_FileConsistencyFinal *FileConsistencyFinal() = 0;
};

class IResourceBuffer {
protected:
	virtual ~IResourceBuffer() {}

public:
	virtual uint32 GetFileHash() const = 0;
	virtual ResourceType_e GetFileFlag() const = 0;

	virtual const char *GetFileName() const = 0;
	virtual const char *GetCmdExec() const = 0;
	virtual int GetLine() const = 0;

	virtual bool IsBreak() const = 0;			// is have do not check a next files
	virtual bool IsDuplicate() const = 0;		// it is already have in resourcelist
	virtual bool IsAddEx() const = 0;			// if it added via API
};

class IResponseBuffer {
protected:
	virtual ~IResponseBuffer() {}

public:
	virtual int GetUserID() const = 0;
	virtual IGameClient *GetGameClient() const = 0;
	virtual const char *GetFileName() const = 0;
	virtual uint32 GetClientHash() const = 0;
	virtual uint32 GetPrevHash() const = 0;
};

class IResourceFile {
protected:
	virtual ~IResourceFile() {}

public:
	virtual const char *FindFilenameOfHash(uint32 hash) = 0;
	virtual int GetConsistencyNum() const = 0;
	virtual uint32 GetPrevHash() const = 0;
};

#undef FindResource

using query_func_t = void (*)(IGameClient *pClient, uint32 hash, int uniqueId);

struct RecheckerFuncs_t {
	IResourceBuffer *(*AddResource)(const char *filename, char *cmdExec, ResourceType_e flag, uint32 hash, bool bBreak);
	IResourceBuffer *(*AddQueryFile)(const char *filename, ResourceType_e flag, uint32 hash, query_func_t callback, int uniqueId);
	void (*RemoveQueryFile)(int uniqueId);
	void (*ClearQueryFiles)();
	IResourceBuffer *(*FindResource)(const char *filename);
	IResourceFile *(*GetResource)();
	IResponseBuffer *(*GetResponseFile)(IGameClient *pClient, const char *filename);
	bool (*IsResourceExists)(IGameClient *pClient, const char *filename, uint32 &hash);
};

class IRecheckerApi {
protected:
	virtual ~IRecheckerApi() { }

public:
	virtual int GetMajorVersion() = 0;
	virtual int GetMinorVersion() = 0;
	virtual const RecheckerFuncs_t *GetFuncs() = 0;
	virtual IRecheckerHookchains *GetHookchains() = 0;
};
