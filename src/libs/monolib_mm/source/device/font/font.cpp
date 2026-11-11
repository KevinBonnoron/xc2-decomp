#include <assert.h>

#include "font/font_sys.h"
#include "font/stream.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

FontSys::FontSys() : m_head(nullptr), m_data(nullptr), m_width(0.0f), m_height(0.0f), m_ux(0.0f), m_vy(0.0f), m_uw(0.0f), m_vh(0.0f), m_texobj(nullptr) {
  for (int i = 0; i < HASH_SIZE; i++) {
    unknown08[i] = nullptr;
  }
}

void FontSys::Header::read(Stream *stream) {
  m_signature = stream->read_u32();
  m_cmp = m_signature == 0x43544e46;
#line 31
  assert(m_signature == 0x00544e46 || m_cmp);
  unknown04 = stream->read_u32();
  unknown08 = stream->read_u16();
  unknown0a = stream->read_u8();
  m_font_size = stream->read_u8();
  m_origin_width = stream->read_u8();
  m_origin_height = stream->read_u8();
}

FontSys::~FontSys() {}

float FontSys::get_font_size() const {
#line 239
  assert(m_head);
  return m_head->m_font_size;
}

float FontSys::get_origin_width() const {
#line 249
  assert(m_head);
  return m_head->m_origin_width;
}

float FontSys::get_origin_height() const {
#line 259
  assert(m_head);
  return m_head->m_origin_height;
}

void FontSys::get_texture(u16 code) {
  if ((code & 0xff00) == 0xff00) {
    code &= 0xff;
  }
  for (unknown002 *node = unknown08[((code >> 8) * 0x1003f + (code & 0xff) + 0x59bbe285) % HASH_SIZE]; node != nullptr; node = node->unknown00) {
    if (node->unknown08 == code) {
      const unknown001 *glyph = node->unknown10;
      m_width = glyph->unknown04;
      m_height = glyph->unknown08;
      m_ux = glyph->unknown0c;
      m_vy = glyph->unknown10;
      m_uw = glyph->unknown14;
      m_vh = glyph->unknown18;
      return;
    }
  }
  m_width = 0.0f;
  m_height = 0.0f;
  m_ux = 0.0f;
  m_vy = 0.0f;
  m_uw = 0.0f;
  m_vh = 0.0f;
}

grlib::CGLibTextureBuffer *FontSys::get_texobj() { return m_texobj; }

float FontSys::get_width() const { return m_width; }

float FontSys::get_height() const { return m_height; }

float FontSys::get_ux() const { return m_ux; }

float FontSys::get_vy() const { return m_vy; }

float FontSys::get_uw() const { return m_uw; }

float FontSys::get_vh() const { return m_vh; }
