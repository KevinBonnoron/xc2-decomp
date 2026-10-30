#include "ml/file_handle_th.h"

#include "ml/dev_file_th.h"
#include "ml/work_event.h"

namespace ml {

bool FileHandleTh::call(CBM cbm) {
  if (cbm == CBM_UNKNOWN_4 || cbm == CBM_UNKNOWN_6) {
    if (unknown70 != nullptr) {
      *unknown70 = nullptr;
    }
    if (unknown78 != nullptr) {
      *unknown78 = -1;
    }
  } else if (cbm == CBM_UNKNOWN_5 || cbm == CBM_UNKNOWN_2) {
    if (unknown70 != nullptr) {
      *unknown70 = unknown08;
    }
    if (unknown78 != nullptr) {
      *unknown78 = unknown18;
    }
  }
  if (unknown60 != nullptr) {
    EventFileTh event(cbm, this);
    return unknown60->OnFileEvent(&event);
  }
  return false;
}

bool FileHandleTh::addCurrentPtr(int offset) {
  m_currentPtr += offset;
  return true;
}

bool FileHandleTh::setCurrentPtr(int offset) {
  m_currentPtr = offset;
  return true;
}

void FileHandleTh::setReadAdr(int size, void *buffer, int alignedSize) {
  unknown18 = size;
  unknown08 = buffer;
  unknown10 = alignedSize;
}

void FileHandleTh::setTime(u64 time) { m_time = time; }

} // namespace ml
