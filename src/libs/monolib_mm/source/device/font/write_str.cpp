#include "font/write_str.h"

#include "types.h"

WriteStr::WriteStr() {
  m_limit_width = 0.0f;
  m_draw_flag = 0x111;
}

WriteStr::~WriteStr() {}

bool WriteStr::is_byte_code(const u8 *code) {
  u8 byte = *code;
  if (byte > 0x80 && byte < 0xa0) {
    return false;
  }
  if (byte >= 0xe0 && byte <= 0xef) {
    return false;
  }
  return true;
}

void WriteStr::set_limit_width(float width) { m_limit_width = width; }

float WriteStr::get_limit_width() const { return m_limit_width; }

void WriteStr::reset_limit_width() { m_limit_width = 0.0f; }

void WriteStr::set_draw_flag(u32 flag) { m_draw_flag = flag; }

u32 WriteStr::get_draw_flag() const { return m_draw_flag; }
