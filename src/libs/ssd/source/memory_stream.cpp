#include <string.h>

#include "ssd/ssd_debug.h"
#include "ssd/ssd_io_stream.h"
#include "types.h"

namespace ssd {

bool MemoryStream::IsOpen() const { return unknown20 != nullptr; }

long MemoryStream::GetSize(u64 *size) const {
  if (size == nullptr) {
    log_message(u"Assert : \"%s\" = nullptr, %s:%d", u"fileSize", get_logfilename(u"D:/ssd/ssd51/ssd/sources/io/memory_stream.cpp"), 0x76);
    abort();
  }
  *size = unknown28;
  return 0;
}

long MemoryStream::Open(void *data, u64 size, OpenMode mode) {
  if (mode != OPEN_MODE_READ) {
    return -1;
  }
  this->unknown20 = static_cast<u8 *>(data);
  this->unknown28 = size;
  unknown30 = 0;
  return 0;
}

long MemoryStream::Close() {
  unknown20 = nullptr;
  return 0;
}

long MemoryStream::Read(u64 size, void *buffer, u64 *readSize) {
  u64 accessSize = CheckAccessSize(size);
  if (accessSize != 0) {
    memcpy(buffer, &unknown20[unknown30], accessSize);
    unknown30 += accessSize;
  }
  if (readSize != nullptr) {
    *readSize = unknown30;
  }
  return 0;
}

long MemoryStream::Write(u64 size, const void *buffer, u64 *writeSize) { return -1; }

long MemoryStream::Seek(SeekMode mode, u64 offset, u64 *position) {
  if (mode == SEEK_MODE_CURRENT) {
    this->unknown30 += CheckAccessSize(offset);
  } else if (mode == SEEK_MODE_BEGIN) {
    this->unknown30 = CheckAccessSize(offset);
  } else if (mode == SEEK_MODE_END) {
    u64 accessSize = CheckAccessSize(offset);
    this->unknown30 = unknown28 - accessSize;
  }
  if (position != nullptr) {
    *position = this->unknown30;
  }
  return 0;
}

long MemoryStream::Tell(u64 *position) {
  *position = this->unknown30;
  return 0;
}

long MemoryStream::GetPosition(u64 *position) const {
  *position = this->unknown30;
  return 0;
}

u64 MemoryStream::CheckAccessSize(u64 size) {
  if (!IsOpen()) {
    return 0;
  }
  if (this->unknown28 != 0) {
    if (unknown30 + size >= this->unknown28) {
      return this->unknown28 - unknown30;
    }
  }
  return size;
}

} // namespace ssd
