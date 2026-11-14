#include "ms/ms_wrapper.h"

#include "ms/lms.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ms {

void *MsWrapper::m_pProj;
mtl::ALLOC_HANDLE MsWrapper::m_allocHandle;

void MsWrapper::init(mtl::ALLOC_HANDLE handle) {
  m_pProj = nullptr;
  m_allocHandle = handle;
  LMS_SetMemFuncs(myAlloc, myFree);
}

void *MsWrapper::myAlloc(size_t size) { return mtl::MemManager::allocate(m_allocHandle, size, 4, false, "no name", 0); }

void MsWrapper::myFree(void *pointer) { mtl::MemManager::deallocate(pointer, 0, false); }

void MsWrapper::regist(const char *path) { m_pProj = LMS_InitProject(path); }

void MsWrapper::unregist() {
  LMS_CloseProject(m_pProj);
  m_pProj = nullptr;
}

u32 MsWrapper::getColorNum() { return LMS_GetColorNum(m_pProj); }

bool MsWrapper::getColor(const char *name, LMSColor *color) { return LMS_GetColorByName(m_pProj, name, color) == 0; }

bool MsWrapper::getColor(u32 index, LMSColor *color) { return LMS_GetColor(m_pProj, index, color) == 0; }

s32 MsWrapper::getTagGroupNum() { return LMS_GetTagGroupNum(m_pProj); }

s32 MsWrapper::getTagNum(s32 group) { return LMS_GetTagNum(m_pProj, group); }

s32 MsWrapper::getTagParamNum(s32 group, s32 tag) { return LMS_GetTagParamNum(m_pProj, group, tag); }

s32 MsWrapper::getTagParamListItemNum(s32 group, s32 tag, s32 param) { return LMS_GetTagListItemNum(m_pProj, group, tag, param); }

const char *MsWrapper::getTagGroupName(s32 group) { return LMS_GetTagGroupName(m_pProj, group); }

const char *MsWrapper::getTagName(s32 group, s32 tag) { return LMS_GetTagName(m_pProj, group, tag); }

const char *MsWrapper::getTagParamName(s32 group, s32 tag, s32 param) { return LMS_GetTagParamName(m_pProj, group, tag, param); }

const char *MsWrapper::getTagParamListItemName(s32 group, s32 tag, s32 param, s32 item) { return LMS_GetTagListItemName(m_pProj, group, tag, param, item); }

s32 MsWrapper::getTagParamType(s32 group, s32 tag, s32 param) { return LMS_GetTagParamType(m_pProj, group, tag, param); }

} // namespace ms
