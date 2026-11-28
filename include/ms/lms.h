#pragma once
#include <stddef.h>

#include "types.h"

struct LMSColor;

// C interface of the message library the game links, as ms::MsWrapper sees it: declared from the symbols LMS_* of the
// executable and from the calls of ms::MsWrapper. The project is an opaque handle here. The wrapper passes 32-bit
// values and tail calls the functions (`b LMS_GetTagNum`, 0x710069c968), while the library itself takes u16 group, tag
// and parameter numbers and returns u16 counts: a u16 prototype in the wrapper's unit would add a zero extension, so
// the library's own prototypes (src/libs/monolib_mm/source/lms/lms_impl.h) differ and the two declarations are never
// seen by one unit. LMS_InitProject receives the message project binary already loaded in memory (the library stores
// the pointer and reads its header), not a path.
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
