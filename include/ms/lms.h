#pragma once
#include <stddef.h>

#include "types.h"

struct LMSColor;

// C interface of the message library the game links, declared from the symbols LMS_* of the executable and from the
// calls of ms::MsWrapper. The project is an opaque handle here: its type name is unknown.
extern "C" {
void LMS_SetMemFuncs(void *(*allocate)(size_t size), void (*deallocate)(void *pointer));
void *LMS_InitProject(const char *path);
void LMS_CloseProject(void *project);
u32 LMS_GetColorNum(void *project);
int LMS_GetColorByName(void *project, const char *name, LMSColor *color);
int LMS_GetColor(void *project, u32 index, LMSColor *color);
s32 LMS_GetTagGroupNum(void *project);
s32 LMS_GetTagNum(void *project, s32 group);
s32 LMS_GetTagParamNum(void *project, s32 group, s32 tag);
s32 LMS_GetTagListItemNum(void *project, s32 group, s32 tag, s32 param);
const char *LMS_GetTagGroupName(void *project, s32 group);
const char *LMS_GetTagName(void *project, s32 group, s32 tag);
const char *LMS_GetTagParamName(void *project, s32 group, s32 tag, s32 param);
const char *LMS_GetTagListItemName(void *project, s32 group, s32 tag, s32 param, s32 item);
s32 LMS_GetTagParamType(void *project, s32 group, s32 tag, s32 param);
}
