#include "ml/file_res_th.h"

#include "ml/dev_file_th.h"
#include "ml/file_handle_th.h"
#include "ml/path_util.h"
#include "mm_mtl/allocator.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

FileResTh::FileResTh() {
  unknownd0 = -1;
  m_fileHandleTh = nullptr;
  m_glassBreakage = nullptr;
  unknownf0 = true;
  unknownf4 = 0;
  unknownf8 = nullptr;
  unknowne0 = 0;
}

FileResTh::~FileResTh() { release(); }

bool FileResTh::isExist() const { return m_glassBreakage != nullptr; }

bool FileResTh::load(mtl::ALLOC_HANDLE handle, const char *path, u32 option, FILE_PRIO priority) {
  release();
  DevFileParamTh param;
  param._08 = handle;
  param.unknown00 = path;
  param.unknown60 = this;
  param._54 = option;
  param.unknown68 = priority;
  param._6d = true;
  SetName(PathUtil::getFilePtrFromPath(path));
  m_fileHandleTh = DevFileTh::readFile(param);
  if (m_fileHandleTh != nullptr) {
    unknownf4 = 1;
  } else {
    unknownd0 = -2;
    unknownf4 = 3;
  }
  return m_fileHandleTh != nullptr;
}

bool FileResTh::load(mm::mtl::IAllocator *allocator, const char *path, u32 option, FILE_PRIO priority) {
  release();
  DevFileParamTh param;
  param._10 = allocator;
  param.unknown00 = path;
  param.unknown60 = this;
  param._54 = option;
  param.unknown68 = priority;
  param._6d = true;
  SetName(PathUtil::getFilePtrFromPath(path));
  m_fileHandleTh = DevFileTh::readFile(param);
  if (m_fileHandleTh != nullptr) {
    unknownf4 = 1;
  } else {
    unknownd0 = -2;
    unknownf4 = 3;
  }
  return m_fileHandleTh != nullptr;
}

void FileResTh::release() {
  if (m_fileHandleTh != nullptr) {
    m_fileHandleTh->m_iWorkEvent = nullptr;
    if (m_fileHandleTh != nullptr) {
      DevFileTh::cancel(m_fileHandleTh, false);
      m_fileHandleTh = nullptr;
    }
  }
  if (unknownf0 && m_glassBreakage != nullptr) {
    if (unknownf8 != nullptr) {
      unknownf8->deallocate(m_glassBreakage);
      m_glassBreakage = nullptr;
      unknownf8 = nullptr;
    } else {
      mtl::MemManager::deallocate(m_glassBreakage, 0, false);
      m_glassBreakage = nullptr;
    }
  }
  unknownd0 = -1;
  unknownf4 = 0;
  unknowne0 = 0;
}

void FileResTh::setMem(void *buffer, int size, const char *name, bool isBufferOwner) {
  unknownf0 = isBufferOwner;
  m_glassBreakage = buffer;
  unknownd0 = size;
  SetName(PathUtil::getFilePtrFromPath(name));
}

bool FileResTh::OnFileEvent(EventFileTh *event) {
  if (event->type == EventFileTh::TYPE_UNKNOWN_2) {
    void *buffer = m_fileHandleTh->unknown08;
    m_fileHandleTh->unknown08 = nullptr;
    m_glassBreakage = buffer;
    unknownd0 = m_fileHandleTh->unknown18;
    unknowne8 = m_fileHandleTh->unknown1c8;
    unknowne0 = m_fileHandleTh->m_time;
    unknownf8 = static_cast<mm::mtl::IAllocator *>(m_fileHandleTh->unknown30);
    unknownf4 = 2;
  } else {
    unknownd0 = -2;
    unknownf4 = 3;
  }
  m_fileHandleTh = nullptr;
  return true;
}

} // namespace ml
