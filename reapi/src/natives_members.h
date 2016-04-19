#pragma once

void RegisterNatives_Members();

BOOL set_member(void* pdata, const member_t *member, size_t element, cell* value);
cell get_member(void* pdata, const member_t *member, size_t element, cell* dest);

bool isTypeReturnable(MType type);
