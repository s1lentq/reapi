#pragma once

// Key + value + 2 x slash + NULL
const int MAX_INFO_STRING = 256;
const int MAX_KV_LEN = 127;
const int INFO_MAX_BUFFER_VALUES = 4;

const char *Info_ValueForKey(const char *s, const char *key);
void Info_RemoveKey(char *s, const char *key);
void Info_SetValueForStarKey(char *s, const char *key, const char *value, int maxsize);
