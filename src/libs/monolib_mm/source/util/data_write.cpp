#include "ml/data_write.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "ml/dev_file_th.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

void DataWrite::init(mtl::ALLOC_HANDLE handle, u64 capacity) {
  if (m_buffer != nullptr) {
    mtl::MemManager::deallocate(m_buffer, 0, false);
    m_buffer = nullptr;
  }
  m_buffer = static_cast<u8 *>(mtl::MemManager::allocate(handle, capacity, 0x80, false, "no name", 0));
  m_size = 0;
  m_capacity = capacity;
}

void *DataWrite::write(const void *data, u64 size) {
  u8 *destination = m_buffer + m_size;
  memcpy(destination, data, size);
  m_size += size;
  return destination;
}

void *DataWrite::writeFormat(const char *format, ...) {
  char text[0x200];
  va_list args;
  va_start(args, format);
  int length = vsnprintf(text, sizeof(text), format, args);
  va_end(args);
  u8 *destination = m_buffer + m_size;
  memcpy(destination, text, length);
  m_size += length;
  m_buffer[m_size] = '\r';
  m_buffer[m_size + 1] = '\n';
  m_size += 2;
  return destination;
}

void DataWrite::align(u64 alignment) {
  u64 remainder = m_size % alignment;
  if (remainder != 0) {
    u64 padding = alignment - remainder;
    memset(m_buffer + m_size, 0, padding);
    m_size += padding;
  }
}

int DataWrite::writeFile(const char *path) {
  DevFileTh::writeFileBlock(path, m_buffer, m_size, 0);
  return 0;
}

} // namespace ml
