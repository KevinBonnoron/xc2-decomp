#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "mm_mtl/map.h"
#include "types.h"

namespace fw {

// Layout evidence: the constructor (1.0.0: 0x71001acbfc) stores the root of the tree at 0x00, zeroes the count at 0x08 and stores the
// process allocator at 0x10; the tree is a mm::mtl::Map<mm::mtl::FixStr<64>, int> (the destructor frees its nodes) and gf::GfComSound
// places its next member 0x20 bytes after the table.
class SoundVariableTable {
public:
  SoundVariableTable();
  ~SoundVariableTable();
  void setVariable(const char *name, int value);

  mm::mtl::Map<mm::mtl::FixStr<64>, int> unknown00; // Inferred role: variables by name; original member name unknown.
  u8 _18[0x20 - 0x18];
};

static_assert(offsetof(SoundVariableTable, unknown00) == 0x00, "");
static_assert(sizeof(SoundVariableTable) == 0x20, "");

} // namespace fw
