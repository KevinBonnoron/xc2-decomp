#pragma once
#include <stddef.h>

#include "types.h"

class Stream;

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

class FontSys {
public:
  // Layout evidence: FontSys::Header::read 0x710078ec0c and the constructor of the font header in FontSys::construct.
  struct Header {
    void read(Stream *stream);

    u32 m_signature;
    u32 unknown04; // Inferred role: header field read right after the signature; original member name unknown.
    u16 unknown08; // Inferred role: glyph count; original member name unknown.
    u8 unknown0a;  // Inferred role: stream position of the glyph data; original member name unknown.
    float m_font_size;
    float m_origin_width;
    float m_origin_height;
    bool m_cmp;
  };

  // Inferred role: glyph metrics and texture coordinates; original type name unknown.
  struct unknown001 {
    u16 unknown00; // Inferred role: character code; original member name unknown.
    float unknown04;
    float unknown08;
    float unknown0c;
    float unknown10;
    float unknown14;
    float unknown18;
  };

  // Inferred role: node of a hash table bucket chain; original type name unknown.
  struct unknown002 {
    unknown002 *unknown00; // Inferred role: next node of the chain; original member name unknown.
    u16 unknown08;         // Inferred role: character code; original member name unknown.
    unknown001 *unknown10; // Inferred role: glyph of the character; original member name unknown.
  };

  static const int HASH_UNKNOWN_101 = 101; // Inferred role: hash table size; original name unknown.

  FontSys();
  ~FontSys();
  void construct(void *data, int size);
  void *destroy();
  float get_font_size() const;
  float get_origin_width() const;
  float get_origin_height() const;
  void get_texture(u16 code);
  grlib::CGLibTextureBuffer *get_texobj();
  float get_width() const;
  float get_height() const;
  float get_ux() const;
  float get_vy() const;
  float get_uw() const;
  float get_vh() const;

  Header *m_head;
  unknown002 *unknown08[HASH_UNKNOWN_101]; // Inferred role: hash table of the glyphs by character code; original member name unknown.
  void *m_data;
  float m_width;
  float m_height;
  float m_ux;
  float m_vy;
  float m_uw;
  float m_vh;
  grlib::CGLibTextureBuffer *m_texobj;
};

static_assert(offsetof(FontSys::Header, m_font_size) == 0x0c, "");
static_assert(offsetof(FontSys::Header, m_cmp) == 0x18, "");
static_assert(sizeof(FontSys::Header) == 0x1c, "");
static_assert(sizeof(FontSys::unknown001) == 0x1c, "");
static_assert(sizeof(FontSys::unknown002) == 0x18, "");
static_assert(offsetof(FontSys, m_data) == 0x330, "");
static_assert(offsetof(FontSys, m_width) == 0x338, "");
static_assert(offsetof(FontSys, m_texobj) == 0x350, "");
static_assert(sizeof(FontSys) == 0x358, "");
