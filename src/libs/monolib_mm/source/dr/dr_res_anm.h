#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

// Inferred type: animation key of an _AOM_DataHead; original type name unknown.
struct unknown001 {
  f32 unknown00; // Inferred role: frame; original member name unknown.
  f32 unknown04; // Inferred role: value; original member name unknown.
};

static_assert(sizeof(unknown001) == 0x08, "");

// Name from the game symbol of ml::DrResAnm::calcAnm. The keys (unknown001) follow the header.
struct _AOM_DataHead {
  f32 unknown00; // Inferred role: start frame; original member name unknown.
  f32 unknown04; // Inferred role: end frame; original member name unknown.
  s32 unknown08; // Inferred role: key count; original member name unknown.
  u8 _0c[0x10 - 0x0c];
};

static_assert(offsetof(_AOM_DataHead, unknown08) == 0x08, "");
static_assert(sizeof(_AOM_DataHead) == 0x10, "");

class DrResAnm {
public:
  virtual ~DrResAnm();

  f32 calcAnm(f32 frame, const _AOM_DataHead *head);
  f32 calcAnmLiner(f32 frame, const _AOM_DataHead *head);
  f32 calcAnmRot(f32 *values, f32 frame, const _AOM_DataHead *head);
};

} // namespace ml
