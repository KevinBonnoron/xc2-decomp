#pragma once
#include <stddef.h>

#include "ssd/ssd_io_stream.h"
#include "types.h"

namespace ssd {

class TextRef;

class FileStream : public IoStreamBase {
public:
  FileStream();
  long Close() override;
  static void Initialize();
  static void Finalize();
  static long Delete(const TextRef &path);
  void Clear();
  bool IsOpen() const override;
  long Open(const TextRef &path, OpenMode mode) override;
  long GetSize(u64 *size) const override;
  long Read(u64 size, void *buffer, u64 *readSize) override;
  long Write(u64 size, const void *buffer, u64 *writeSize) override;
  long Seek(SeekMode mode, u64 offset, u64 *position) override;
  long GetPosition(u64 *position) const override;
  long Tell(u64 *position) override;
  u64 CheckAccessSize(u64 size) override;

  u64 unknown18; // Inferred role: cleared by the constructor; original member name unknown.
  u64 unknown20; // Inferred role: position; original member name unknown.
  u64 unknown28; // Inferred role: size; original member name unknown.
  u64 unknown30; // Inferred role: file handle; original member name unknown.
};

static_assert(offsetof(FileStream, unknown20) == 0x20, "");
static_assert(offsetof(FileStream, unknown30) == 0x30, "");
static_assert(sizeof(FileStream) == 0x38, "");

} // namespace ssd
