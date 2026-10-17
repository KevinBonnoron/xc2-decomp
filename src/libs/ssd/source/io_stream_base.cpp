#include "ssd/ssd_io_stream.h"
#include "types.h"

namespace ssd {
class TextRef;

bool IoStreamBase::IsOpen() const { return false; }

long IoStreamBase::Open(const TextRef &path, OpenMode mode) { return -1; }

long IoStreamBase::Open(void *data, u64 size, OpenMode mode) { return -1; }

long IoStreamBase::Close() { return -1; }

long IoStreamBase::Read(u64 size, void *buffer, u64 *readSize) { return -1; }

long IoStreamBase::Write(u64 size, const void *buffer, u64 *writeSize) { return -1; }

long IoStreamBase::Seek(SeekMode mode, u64 offset, u64 *position) { return -1; }

long IoStreamBase::GetData(u64 offset, u64 size, void *buffer, u64 *readSize) {
  long result = Seek(SEEK_MODE_BEGIN, offset, nullptr);
  if (result < 0) {
    return result;
  }
  return Read(size, buffer, readSize);
}

long IoStreamBase::GetSize(u64 *size) const { return -1; }

long IoStreamBase::GetPosition(u64 *position) const { return -1; }

long IoStreamBase::Tell(u64 *position) { return -1; }

u64 IoStreamBase::CheckAccessSize(u64 size) { return 0; }

} // namespace ssd
