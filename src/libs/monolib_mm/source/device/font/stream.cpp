#include "font/stream.h"

#include "font/file.h"
#include "types.h"

Stream::Stream(File *file) : unknown00(file) {
  unknown08 = 0;
  unknown09 = 0;
}

Stream::~Stream() {}

float Stream::read_fixed() {
  unknown09 = 0;
  int value = unknown00->read_le32();
  return value / 65536.0f;
}

void Stream::align() {
  unknown08 = 0;
  unknown09 = 0;
}

u8 Stream::read_u8() {
  align();
  return unknown00->read_byte();
}

u16 Stream::read_u16() {
  align();
  return unknown00->read_le16();
}

u32 Stream::read_u32() {
  align();
  return unknown00->read_le32();
}

u8 Stream::read_s8() {
  align();
  return unknown00->read_byte();
}

u16 Stream::read_s16() {
  align();
  return unknown00->read_le16();
}

u32 Stream::read_s32() {
  align();
  return unknown00->read_le32();
}

u64 Stream::pos() { return unknown00->pos(); }

u64 Stream::pos(u64 position) {
  align();
  return unknown00->pos(position);
}
