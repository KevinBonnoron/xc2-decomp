#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"

namespace ml {

class IniParser {
public:
  struct KeyParam {
    mm::mtl::FixStr<128> unknown00; // Inferred role: key name; original member name unknown.
    mm::mtl::FixStr<128> unknown84; // Inferred role: value; original member name unknown.
    mm::mtl::FixStr<32> unknown108; // Inferred role: section name; original member name unknown.
  };

  const char *getKeyValue(const char *section, const char *key) const;

  mm::mtl::FixedVector<KeyParam, 128> unknown0000; // Inferred role: parsed key parameters; original member name unknown.
};

static_assert(sizeof(IniParser::KeyParam) == 0x12c, "");
static_assert(offsetof(IniParser::KeyParam, unknown84) == 0x84, "");
static_assert(offsetof(IniParser::KeyParam, unknown108) == 0x108, "");

} // namespace ml
