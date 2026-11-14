#pragma once
#include <stddef.h>

#include "types.h"

// Layout evidence: File::File(void*, unsigned long) 0x71007906b0 and the accessors File::err 0x7100790a58, File::pos
// 0x7100790a24 and File::size 0x7100790a1c.
class File {
public:
  File();
  File(void *data, u64 size);
  ~File();
  u8 read_byte();
  u8 read8();
  u16 read_le16();
  u16 read16();
  u32 read_le32();
  u32 read32();
  u64 read_le64();
  u64 read64();
  u16 read_be16();
  u32 read_be32();
  u64 read_be64();
  float read_float32();
  double read_double64();
  int read_bytes(void *destination, int size);
  int read(void *destination, int size, void *source);
  u64 size();
  u64 pos();
  int go_to_end();
  u64 pos(u64 position);
  bool is_eof();
  int err();

private:
  // Inferred helper: address of the value that lies the given number of bytes after the start of a buffer; original
  // name unknown.
  template <typename T> static T *unknown001(void *base, u64 offset) { return static_cast<T *>(static_cast<void *>(static_cast<u8 *>(base) + offset)); }

  void *unknown00; // Inferred role: data; original member name unknown.
  int m_err;
  u64 m_pos;
  u64 m_size;

  friend struct FileLayout;
};

struct FileLayout {
  static_assert(offsetof(File, m_err) == 0x08, "");
  static_assert(offsetof(File, m_pos) == 0x10, "");
  static_assert(offsetof(File, m_size) == 0x18, "");
  static_assert(sizeof(File) == 0x20, "");
};
