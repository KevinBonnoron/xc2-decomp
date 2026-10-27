#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "types.h"

namespace ml {

class DrMan;

class DrResEtcUniformObj {
public:
  // Inferred type: uniform block range; the original type name is unknown.
  struct unknown001 {
    s32 unknown00; // Inferred role: offset; original member name unknown.
    s32 unknown04; // Inferred role: size; original member name unknown.
  };

  DrResEtcUniformObj(DrMan *drMan, int max, int size, int bufferSize);
  ~DrResEtcUniformObj();
  void begin();
  void end();
  void setUniformBlock(s16 index, u32 binding);

  s32 unknown00; // Inferred role: block size; original member name unknown.
  s32 unknown04; // Inferred role: range max; original member name unknown.
  s32 unknown08; // Inferred role: range count; original member name unknown.
  s32 unknown0c; // Inferred role: used size; original member name unknown.
  s32 unknown10; // Inferred role: buffer size; original member name unknown.
  u8 _14[0x18 - 0x14];
  void *unknown18;                       // Inferred role: buffer end; original member name unknown.
  void *unknown20;                       // Inferred role: allocation; original member name unknown.
  unknown001 *unknown28;                 // Inferred role: ranges; original member name unknown.
  grlib::CGLibDblUniformBlock unknown30; // Inferred role: uniform block; original member name unknown.
};

static_assert(offsetof(DrResEtcUniformObj, unknown10) == 0x10, "");
static_assert(offsetof(DrResEtcUniformObj, unknown18) == 0x18, "");
static_assert(offsetof(DrResEtcUniformObj, unknown28) == 0x28, "");
static_assert(offsetof(DrResEtcUniformObj, unknown30) == 0x30, "");

} // namespace ml
