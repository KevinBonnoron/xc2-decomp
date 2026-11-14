#include "font/file.h"

#include "types.h"

File::File() : unknown00(nullptr), m_err(0) {}

File::File(void *data, u64 size) : unknown00(data), m_err(1), m_pos(0), m_size(size) {
  if (data == nullptr) {
    m_err = 0;
  }
}

File::~File() {
  if (unknown00 != nullptr) {
    unknown00 = nullptr;
  }
}

u8 File::read_byte() {
  u8 value = *unknown001<u8>(unknown00, m_pos);
  m_pos += 1;
  return value;
}

u8 File::read8() {
  u8 value = *unknown001<u8>(unknown00, m_pos);
  m_pos += 1;
  return value;
}

u16 File::read_le16() {
  u16 value = *unknown001<u16>(unknown00, m_pos);
  m_pos += 2;
  return value;
}

u16 File::read16() {
  u16 value = *unknown001<u16>(unknown00, m_pos);
  m_pos += 2;
  return value;
}

u32 File::read_le32() {
  u32 value = *unknown001<u32>(unknown00, m_pos);
  m_pos += 4;
  return value;
}

u32 File::read32() {
  u32 value = *unknown001<u32>(unknown00, m_pos);
  m_pos += 4;
  return value;
}

u64 File::read_le64() {
  u64 value = *(static_cast<u64 *>(unknown00) + m_pos);
  m_pos += 8;
  return value;
}

u64 File::read64() {
  u64 value = *(static_cast<u64 *>(unknown00) + m_pos);
  m_pos += 8;
  return value;
}

u16 File::read_be16() {
  u16 value = *unknown001<u16>(unknown00, m_pos);
  m_pos += 2;
  return value >> 8 | value << 8;
}

u64 File::read_be64() {
  u64 value = *(static_cast<u64 *>(unknown00) + m_pos);
  m_pos += 8;
  value = (value & 0xff00ff00ff00ff00) >> 8 | (value & 0x00ff00ff00ff00ff) << 8;
  value = (value & 0xffff0000ffff0000) >> 16 | (value & 0x0000ffff0000ffff) << 16;
  return value >> 32 | value << 32;
}

float File::read_float32() {
  float value = *unknown001<float>(unknown00, m_pos);
  m_pos += 4;
  return value;
}

double File::read_double64() {
  double value = *(static_cast<double *>(unknown00) + m_pos);
  m_pos += 8;
  return value;
}

int File::read_bytes(void *destination, int size) {
  void *data = unknown00;
  switch (size) {
  case 1:
    *static_cast<u8 *>(destination) = *unknown001<u8>(data, m_pos);
    m_pos += 1;
    break;
  case 2:
    *static_cast<u16 *>(destination) = *unknown001<u16>(data, m_pos);
    m_pos += 2;
    break;
  case 4:
    *static_cast<u32 *>(destination) = *unknown001<u32>(data, m_pos);
    m_pos += 4;
    break;
  case 8:
    *static_cast<u64 *>(destination) = *(static_cast<u64 *>(data) + m_pos);
    m_pos += 8;
    break;
  default:
    for (int i = 0; i < size; i++) {
      *static_cast<u8 *>(destination) = *unknown001<u8>(data, m_pos);
      m_pos += 1;
    }
    break;
  }
  return 0;
}

int File::read(void *destination, int size, void *source) {
  switch (size) {
  case 1:
    *static_cast<u8 *>(destination) = *unknown001<u8>(source, m_pos);
    m_pos += 1;
    break;
  case 2:
    *static_cast<u16 *>(destination) = *unknown001<u16>(source, m_pos);
    m_pos += 2;
    break;
  case 4:
    *static_cast<u32 *>(destination) = *unknown001<u32>(source, m_pos);
    m_pos += 4;
    break;
  case 8:
    *static_cast<u64 *>(destination) = *(static_cast<u64 *>(source) + m_pos);
    m_pos += 8;
    break;
  default:
    for (int i = 0; i < size; i++) {
      *static_cast<u8 *>(destination) = *unknown001<u8>(source, m_pos);
      m_pos += 1;
    }
    break;
  }
  return 0;
}

u64 File::size() { return m_size; }

u64 File::pos() { return m_pos; }

int File::go_to_end() {
  m_pos = m_size;
  return 0;
}

u64 File::pos(u64 position) {
  m_pos = position;
  return 0;
}

bool File::is_eof() { return m_pos >= m_size; }

int File::err() { return m_err; }
