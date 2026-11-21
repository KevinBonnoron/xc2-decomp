#include "font/write_str.h"

#include "font/file.h"
#include "font/font_sys.h"
#include "font/stream.h"
#include <string.h>

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

float WriteStr::calc_string_width(const char *string) {
  File file(const_cast<char *>(string), strlen(string));
  Stream stream(&file);
  float width = 0.0f;
  float maxWidth = 0.0f;
  while (!file.is_eof()) {
    u8 byte = stream.read_u8();
    u16 code = is_byte_code(&byte) ? byte : (byte << 8) | stream.read_u8();
    get_font()->get_texture(code);
    width += (is_fixed_width() ? get_fixed_width() : get_font()->get_width()) * get_scale_h();
    maxWidth = width > maxWidth ? width : maxWidth;
    if (m_limit_width != 0.0f && width >= m_limit_width) {
      width = 0.0f;
    }
  }
  return maxWidth;
}

float WriteStr::calc_string_width_to_new_line(File *file) {
  Stream stream(file);
  u64 position = stream.pos();
  float width = 0.0f;
  float maxWidth = 0.0f;
  while (!file->is_eof()) {
    u8 byte = stream.read_u8();
    u16 code = is_byte_code(&byte) ? byte : (byte << 8) | stream.read_u8();
    get_font()->get_texture(code);
    width += (is_fixed_width() ? get_fixed_width() : get_font()->get_width()) * get_scale_h();
    maxWidth = width > maxWidth ? width : maxWidth;
    if (m_limit_width != 0.0f && width >= m_limit_width) {
      break;
    }
  }
  stream.pos(position);
  return maxWidth;
}

void WriteStr::set_limit_width(float width) { m_limit_width = width; }

float WriteStr::get_limit_width() const { return m_limit_width; }

void WriteStr::reset_limit_width() { m_limit_width = 0.0f; }

void WriteStr::set_draw_flag(u32 flag) { m_draw_flag = flag; }

u32 WriteStr::get_draw_flag() const { return m_draw_flag; }
