#pragma once
#include <stddef.h>

#include "ssd/ssd_hash.h"
#include "types.h"

namespace ssd {

enum TextEncodeType : u8 {
  TEXT_ENCODE_NONE = 0,
  TEXT_ENCODE_UTF8 = 2,
  TEXT_ENCODE_UTF16 = 3,
};

class TextRef {
public:
  TextRef(const TextRef &text);
  TextRef(const char *text);
  TextRef(const char16_t *text);
  void Clear();
  void InitImpl(const char *text);
  void InitImpl(const char16_t *text);
  virtual void Set(const TextRef &text);
  virtual void Set(const char *text);
  virtual void Set(const char16_t *text);

  static const char16_t *EmptyText;

  Hash unknown08;           // Inferred role: hash; original member name unknown.
  const void *unknown10;    // Inferred role: text; original member name unknown.
  TextEncodeType unknown18; // Inferred role: encode type; original member name unknown.
};

static_assert(offsetof(TextRef, unknown08) == 0x8, "");
static_assert(offsetof(TextRef, unknown18) == 0x18, "");

} // namespace ssd
