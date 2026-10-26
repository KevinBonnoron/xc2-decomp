#include "ml/file_handle_th.h"

namespace ml {

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
