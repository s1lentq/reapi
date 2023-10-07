#include "precompiled.h"

// NOTE: This file contains a lot of fixes that are not covered by REHLDS_FIXES define.
// TODO: Most of the Info_ functions can be speedup via removing unneded copy of key and values.

// Searches the string for the given
// key and returns the associated value, or an empty string.
const char *Info_ValueForKey(const char *s, const char *key)
{
	// use few (two?) buffers so compares work without stomping on each other
	static char value[INFO_MAX_BUFFER_VALUES][MAX_KV_LEN];
	static int valueindex;
	char pkey[MAX_KV_LEN];
	char *c;
	int nCount;

	while (*s)
	{
		if (*s == '\\')
		{
			s++;	// skip the slash
		}

		// Copy a key
		nCount = 0;
		c = pkey;
		while (*s != '\\')
		{
			if (!*s)
			{
				// key should end with a \, not a NULL, but suppose its value as absent
				return "";
			}

			if (nCount >= MAX_KV_LEN)
			{
				s++;
				continue;	// skip oversized key chars till the slash or EOL
			}
			*c++ = *s++;
			nCount++;
		}
		*c = 0;
		s++;	// skip the slash

		// Copy a value
		nCount = 0;
		c = value[valueindex];
		while (*s != '\\')
		{
			if (!*s)
			{
				break;		// allow value to be ended with NULL
			}

			if (nCount >= MAX_KV_LEN)
			{
				s++;
				continue;	// skip oversized value chars till the slash or EOL
			}

			*c++ = *s++;
			nCount++;
		}
		*c = 0;

		if (!Q_strcmp(key, pkey))
		{
			c = value[valueindex];
			valueindex = (valueindex + 1) % INFO_MAX_BUFFER_VALUES;
			return c;
		}
	}

	return "";
}

void Info_RemoveKey(char *s, const char *key)
{
	char pkey[MAX_KV_LEN];
	char value[MAX_KV_LEN];
	char *start;
	char *c;
	int cmpsize;
	int nCount;

	if (Q_strstr(key, "\\"))
	{
		UTIL_ServerPrint("Can't use a key with a \\\n");
		return;
	}

	cmpsize = Q_strlen(key);
	if (cmpsize > MAX_KV_LEN - 1)
		cmpsize = MAX_KV_LEN - 1;

	while (*s)
	{
		start = s;

		if (*s == '\\')
		{
			s++; // skip the slash
		}

		// Copy a key
		nCount = 0;
		c = pkey;
		while (*s != '\\')
		{
			if (!*s)
			{
				break;		// key should end with a \, not a NULL, but allow to remove it
			}
			if (nCount >= MAX_KV_LEN)
			{
				s++;
				continue;	// skip oversized key chars till the slash or EOL
			}
			*c++ = *s++;
			nCount++;
		}
		*c = 0;
		if (*s)
			s++;	// skip the slash

		// Copy a value
		nCount = 0;
		c = value;
		while (*s != '\\')
		{
			if (!*s)
			{
				break;		// allow value to be ended with NULL
			}

			if (nCount >= MAX_KV_LEN)
			{
				s++;
				continue;	// skip oversized value chars till the slash or EOL
			}

			*c++ = *s++;
			nCount++;
		}
		*c = 0;

		// Compare keys
		if (!Q_strncmp(key, pkey, cmpsize))
		{
			Q_strcpy_s(start, s);	// remove this part
			s = start;				// continue searching
		}
	}
}

qboolean Info_IsKeyImportant(const char *key)
{
	if (key[0] == '*')
		return true;
	if (!strcmp(key, "name"))
		return true;
	if (!strcmp(key, "model"))
		return true;
	if (!strcmp(key, "rate"))
		return true;
	if (!strcmp(key, "topcolor"))
		return true;
	if (!strcmp(key, "bottomcolor"))
		return true;
	if (!strcmp(key, "cl_updaterate"))
		return true;
	if (!strcmp(key, "cl_lw"))
		return true;
	if (!strcmp(key, "cl_lc"))
		return true;

	return false;
}

char *Info_FindLargestKey(char *s, int maxsize)
{
	static char largest_key[MAX_KV_LEN];
	char key[MAX_KV_LEN];
	char value[MAX_KV_LEN];
	char *c;
	int nCount;
	int largest_size = 0;

	largest_key[0] = 0;

	while (*s)
	{
		if (*s == '\\')
		{
			s++; // skip the slash
		}

		// Copy a key
		nCount = 0;
		c = key;
		while (*s != '\\')
		{
			// key should end with a \, not a NULL, return this key, so it will be deleted as wrong
			if (!*s)
			{
				*c = 0;
				strcpy(largest_key, key);
				return largest_key;
			}

			// oversized key, return this key, so it will be deleted as wrong
			if (nCount >= MAX_KV_LEN)
			{
				*c = 0;
				strcpy(largest_key, key);
				return largest_key;
			}
			*c++ = *s++;
			nCount++;
		}
		*c = 0;
		s++;	// skip the slash

		// Get length
		int size = c - key;

		// Copy a value
		nCount = 0;
		c = value;
		while (*s != '\\')
		{
			if (!*s)
			{
				break;					// allow value to be ended with NULL
			}
			if (nCount >= MAX_KV_LEN)	// oversized value, return this key, so it will be deleted as wrong
			{
				*c = 0;
				strcpy(largest_key, key);
				return largest_key;
			}
			*c++ = *s++;
			nCount++;
		}
		*c = 0;

		// Add length
		size += c - value;

		if (size > largest_size && !Info_IsKeyImportant(key))
		{
			largest_size = size;
			strcpy(largest_key, key);
		}
	}

	return largest_key;
}

void Info_SetValueForStarKey(char *s, const char *key, const char *value, int maxsize)
{
	char newArray[MAX_INFO_STRING];
	char *v;
	int c;

	if (!key || !value)
	{
		UTIL_ServerPrint("Keys and values can't be null\n");
		return;
	}

	if (key[0] == 0)
	{
		UTIL_ServerPrint("Keys can't be an empty string\n");
		return;
	}

	if (Q_strstr(key, "\\") || Q_strstr(value, "\\"))
	{
		UTIL_ServerPrint("Can't use keys or values with a \\\n");
		return;
	}

	if (Q_strstr(key, "..") || (Q_strcmp(key, "name") != 0 && Q_strstr(value, "..")))
	{
		// TODO: Why silently return?
		//UTIL_ServerPrint("Can't use keys or values with a ..\n");
		return;
	}

	if (Q_strstr(key, "\"") || Q_strstr(value, "\""))
	{
		UTIL_ServerPrint("Can't use keys or values with a \"\n");
		return;
	}

	int keyLen = Q_strlen(key);
	int valueLan = Q_strlen(value);

	if (keyLen >= MAX_KV_LEN || valueLan >= MAX_KV_LEN)
	{
		UTIL_ServerPrint("Keys and values must be < %i characters\n", MAX_KV_LEN);
		return;
	}

	/*if (!Q_UnicodeValidate(key) || !Q_UnicodeValidate(value))
	{
		UTIL_ServerPrint("Keys and values must be valid utf8 text\n");
		return;
	}*/

	// Remove current key/value and return if we doesn't specified to set a value
	Info_RemoveKey(s, key);
	if (value[0] == 0)
	{
		return;
	}

	// Create key/value pair
	Q_snprintf(newArray, MAX_INFO_STRING - 1, "\\%s\\%s", key, value);
	newArray[MAX_INFO_STRING - 1] = 0;

	int neededLength = Q_strlen(newArray);
	if ((int)Q_strlen(s) + neededLength >= maxsize)
	{
		// no more room in the buffer to add key/value
		if (!Info_IsKeyImportant(key))
		{
			// no room to add setting
			UTIL_ServerPrint("Info string length exceeded\n");
			return;
		}

		// keep removing the largest key/values until we have a room
		char *largekey;
		do
		{
			largekey = Info_FindLargestKey(s, maxsize);
			if (largekey[0] == 0)
			{
				// no room to add setting
				UTIL_ServerPrint("Info string length exceeded\n");
				return;
			}
			Info_RemoveKey(s, largekey);
		} while ((int)Q_strlen(s) + neededLength >= maxsize);
	}

	// auto lowercase team
	bool lowerCaseValue = _stricmp(key, "team") == 0;
	s += Q_strlen(s);
	v = newArray;
	while (*v)
	{
		c = (unsigned char)*v++;
		if (lowerCaseValue)
		{
			c = tolower(c);
		}
		*s++ = c;
	}
	*s = 0;
}
