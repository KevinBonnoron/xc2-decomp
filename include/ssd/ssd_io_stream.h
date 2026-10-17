#pragma once
#include <stddef.h>

#include "ssd/ssd_sound.h"
#include "types.h"

namespace ssd {

class TextRef;

class IoStreamBase : public Object {
public:
  enum OpenMode : u8 {
    OPEN_MODE_READ = 1,
  };

  enum SeekMode : u8 {
    SEEK_MODE_BEGIN = 1,
    SEEK_MODE_CURRENT = 2,
    SEEK_MODE_END = 3,
  };

  virtual bool IsOpen() const;
  virtual long Open(const TextRef &path, OpenMode mode);
  virtual long Open(void *data, u64 size, OpenMode mode);
  virtual long Close();
  virtual long GetSize(u64 *size) const;
  virtual long Read(u64 size, void *buffer, u64 *readSize);
  virtual long Write(u64 size, const void *buffer, u64 *writeSize);
  virtual long Seek(SeekMode mode, u64 offset, u64 *position);
  virtual long GetPosition(u64 *position) const;
  virtual long Tell(u64 *position);
  virtual u64 CheckAccessSize(u64 size);
  long GetData(u64 offset, u64 size, void *buffer, u64 *readSize);
};

class MemoryStream : public IoStreamBase {
public:
  bool IsOpen() const override;
  long Open(void *data, u64 size, OpenMode mode) override;
  long Close() override;
  long Read(u64 size, void *buffer, u64 *readSize) override;
  long Write(u64 size, const void *buffer, u64 *writeSize) override;
  long Seek(SeekMode mode, u64 offset, u64 *position) override;
  long Tell(u64 *position) override;
  long GetSize(u64 *size) const override;
  long GetPosition(u64 *position) const override;
  u64 CheckAccessSize(u64 size) override;

  u8 _18[0x20 - 0x18];
  u8 *data;
  u64 size;
  u64 position;
};

static_assert(offsetof(MemoryStream, data) == 0x20, "");
static_assert(offsetof(MemoryStream, position) == 0x30, "");

} // namespace ssd
