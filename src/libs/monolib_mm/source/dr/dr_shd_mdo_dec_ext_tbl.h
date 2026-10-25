#pragma once
#include <stddef.h>

#include "grlib/cglib_dec_shd_ext_tbl.h"
#include "types.h"

namespace ml {
class DrShdMdoDecRes;

class DrShdMdoDecExtTbl : public grlib::CGLibDecShdExtTbl {
public:
  u32 getValGlobalParam(int index);
  void bindShader();

  DrShdMdoDecRes *unknown18; // Inferred role: dec res; original member name unknown.
  u8 _20[0x28 - 0x20];
  u32 *unknown28; // Inferred role: global params; original member name unknown.
};

static_assert(offsetof(DrShdMdoDecExtTbl, unknown18) == 0x18, "");
static_assert(offsetof(DrShdMdoDecExtTbl, unknown28) == 0x28, "");

} // namespace ml
