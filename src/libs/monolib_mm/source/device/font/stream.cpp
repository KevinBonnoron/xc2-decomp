#include "font/stream.h"

#include <string.h>

#include "font/file.h"
#include "types.h"

Stream::Stream(File *file) : m_file(file) {
  unknown08 = 0;
  unknown09 = 0;
}

Stream::~Stream() {}

float Stream::read_fixed() {
  unknown09 = 0;
  int value = m_file->read_le32();
  return value / 65536.0f;
}

// The game returns the assembled bits in a float register (fmov s0, w8); memcpy copies them without changing the value.
float Stream::read_float16() {
  unknown09 = 0;
  u32 half = m_file->read_le16();
  u32 bits = (half & 0x8000) << 16;
  u32 exponent = half >> 10 & 0x1f;
  if (exponent != 0) {
    bits = (exponent * 0x800000 + 0x37800000) | bits;
  }
  bits |= (half & 0x3ff) << 13;
  float value;
  memcpy(&value, &bits, sizeof(value));
  return value;
}

float Stream::read_float() {
  unknown09 = 0;
  u32 bits = m_file->read_le32();
  float value;
  memcpy(&value, &bits, sizeof(value));
  return value;
}

double Stream::read_double() {
  unknown09 = 0;
  u64 bits = m_file->read_le64();
  double value;
  memcpy(&value, &bits, sizeof(value));
  return value;
}

void Stream::align() {
  unknown08 = 0;
  unknown09 = 0;
}

u8 Stream::read_u8() {
  align();
  return m_file->read_byte();
}

u16 Stream::read_u16() {
  align();
  return m_file->read_le16();
}

u32 Stream::read_u32() {
  align();
  return m_file->read_le32();
}

u8 Stream::read_s8() {
  align();
  return m_file->read_byte();
}

u16 Stream::read_s16() {
  align();
  return m_file->read_le16();
}

u32 Stream::read_s32() {
  align();
  return m_file->read_le32();
}

u64 Stream::pos() { return m_file->pos(); }

u64 Stream::pos(u64 position) {
  align();
  return m_file->pos(position);
}
