#include <stddef.h>

#include "nn/fs.h"
#include "nn/result.h"
#include "ssd/ssd_allocator.h"
#include "ssd/ssd_debug.h"
#include "ssd/ssd_file_stream.h"
#include "ssd/ssd_text.h"
#include "types.h"

namespace ssd {
enum Result : long;

FileStream::FileStream() : unknown18(0), unknown20(0), unknown28(0), unknown30() {}

void FileStream::Initialize() {}

void FileStream::Finalize() {}

long FileStream::Delete(const TextRef &path) { return 0; }

void FileStream::Clear() {
  unknown20 = 0;
  unknown28 = 0;
}

bool FileStream::IsOpen() const { return unknown30.handle != nullptr; }

long FileStream::Open(const TextRef &path, OpenMode mode) {
  unknown20 = 0;
  MemoryBlock text = {nullptr, 0};
  path.GetText(&text, TEXT_ENCODE_UTF8);
  nn::Result result = nn::fs::OpenFile(&unknown30, static_cast<const char *>(text.unknown00), 1);
  void *address = text.unknown00;
  Allocator *allocator = SoundMemory::allocator_;
  allocator->DeleteBufferImpl(allocator->GetMemoryBlock(address));
  text.unknown00 = nullptr;
  text.unknown08 = 0;
  if (!result.IsSuccess()) {
    log_error(static_cast<Result>(-65), static_cast<Debug::LogFlag::Type>(0x30), u"ファイルが開けませんでした。: file=\"%s\"", path.unknown10);
    return -65;
  }
  long size;
  nn::fs::GetFileSize(&size, unknown30);
  unknown28 = size;
  return 0;
}

long FileStream::Read(u64 size, void *buffer, u64 *readSize) {
  size_t read;
  nn::fs::ReadFile(&read, unknown30, unknown20, buffer, size);
  unknown20 += read;
  if (readSize != nullptr) {
    *readSize = read;
  }
  return 0;
}

long FileStream::Close() {
  if (IsOpen()) {
    nn::fs::CloseFile(unknown30);
    unknown30.handle = nullptr;
  }
  return 0;
}

long FileStream::Write(u64 size, const void *buffer, u64 *writeSize) {
  IsOpen();
  return -1;
}

long FileStream::GetSize(u64 *size) const {
  if (!IsOpen()) {
    return -1;
  }
  SSD_ASSERT(size != nullptr, u"Assert : \"%s\" = nullptr, %s:%d", u"fileSize", u"D:/ssd/ssd51/ssd/sources/io/file_stream.cpp", 0x1a8);
  *size = unknown28;
  return 0;
}

long FileStream::Seek(SeekMode mode, u64 offset, u64 *position) {
  if (!IsOpen()) {
    return -1;
  }
  if (mode == SEEK_MODE_CURRENT) {
    unknown20 += offset;
  } else if (mode == SEEK_MODE_BEGIN) {
    unknown20 = offset;
  } else if (mode == SEEK_MODE_END) {
    unknown20 = unknown28 - offset;
  }
  if (position != nullptr) {
    *position = unknown20;
  }
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
