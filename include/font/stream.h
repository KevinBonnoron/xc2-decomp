#pragma once
#include <stddef.h>

#include "types.h"

class File;

// Layout evidence: Stream::Stream(File*) 0x710078efc0 and Stream::read_uint 0x710078f084 (bit buffer: the byte being
// consumed and the number of bits left in it).
class Stream {
public:
  Stream(File *file);
  ~Stream();
  bool read_bool();
  u32 read_uint(int bits);
  u32 read_sint(int bits);
  float read_fixed();
  float read_float16();
  float read_float();
  double read_double();
  void align();
  u8 read_u8();
  u16 read_u16();
  u32 read_u32();
  u8 read_s8();
  u16 read_s16();
  u32 read_s32();
  u64 pos();
  u64 pos(u64 position);

private:
  File *unknown00; // Inferred role: file; original member name unknown.
  u8 unknown08;    // Inferred role: byte being consumed; original member name unknown.
  u8 unknown09;    // Inferred role: number of bits left in the byte being consumed; original member name unknown.

  friend struct StreamLayout;
};

struct StreamLayout {
  static_assert(offsetof(Stream, unknown08) == 0x08, "");
  static_assert(offsetof(Stream, unknown09) == 0x09, "");
  static_assert(sizeof(Stream) == 0x10, "");
};
