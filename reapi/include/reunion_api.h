#ifndef REUNION_API_H
#define REUNION_API_H

#define REUNION_API_VERSION_MAJOR		1
#define REUNION_API_VERSION_MINOR		1

enum dp_authkind_e
{
	DP_AUTH_NONE = 0,
	DP_AUTH_DPROTO = 1,
	DP_AUTH_STEAM = 2,
	DP_AUTH_STEAMEMU = 3,
	DP_AUTH_REVEMU = 4,
	DP_AUTH_OLDREVEMU = 5,
	DP_AUTH_HLTV = 6,
	DP_AUTH_SC2009 = 7,
	DP_AUTH_AVSMP = 8,
	DP_AUTH_SXEI = 9,
	DP_AUTH_REVEMU2013 = 10,
	DP_AUTH_SSE3 = 11,
};

class IReunionApi
{
public:
	int version_major;
	int version_minor;

	virtual int GetClientProtocol(int index) = 0; // index: 0-31
	virtual dp_authkind_e GetClientAuthtype(int index) = 0; // index: 0-31

	virtual size_t GetClientAuthdata(int index, void *data, int maxlen) = 0; // get auth data as binary. index: 0-31
	virtual const char *GetClientAuthdataString(int index, char *data, int maxlen) = 0; // get auth data as string. index: 0-31
};

#endif // REUNION_API_H
