#include "ssd/ssd_debug.h"
#include "ssd/ssd_file_stream.h"
#include "types.h"

namespace ssd {
class TextRef;

FileStream::FileStream() : unknown18(0), unknown20(0), unknown28(0), unknown30(0) {}

void FileStream::Initialize() {}

void FileStream::Finalize() {}

long FileStream::Delete(const TextRef &path) { return 0; }

void FileStream::Clear() {
  unknown20 = 0;
  unknown28 = 0;
}

bool FileStream::IsOpen() const { return unknown30 != 0; }

long FileStream::Write(u64 size, const void *buffer, u64 *writeSize) {
  IsOpen();
  return -1;
}

long FileStream::GetSize(u64 *size) const {
  if (!IsOpen()) {
    return -1;
  }
  if (size == nullptr) {
    log_message(u"Assert : \"%s\" = nullptr, %s:%d", u"fileSize", get_logfilename(u"D:/ssd/ssd51/ssd/sources/io/file_stream.cpp"), 0x1a8);
    abort();
  }
  *size = unknown28;
  return 0;
}

long FileStream::Tell(u64 *position) {
  if (!IsOpen()) {
    return -1;
  }
  *position = unknown28;
  return 0;
}

long FileStream::GetPosition(u64 *position) const {
  *position = unknown20;
  return 0;
}

u64 FileStream::CheckAccessSize(u64 size) {
  if (!IsOpen()) {
    return 0;
  }
  u64 fileSize = unknown28;
  if (fileSize != 0 && unknown20 + size >= fileSize) {
    return fileSize - unknown20;
  }
  return size;
}

} // namespace ssd
