#include "layer/layer_act_def.h"

#include <stddef.h>

#include "layer/layer_act_base.h"

namespace layer {

namespace {

struct unknown004 {
  u8 _00[0x02];
  u16 unknown02; // Inferred role: icon number; original member name unknown.
};

struct unknown006 {
  u8 _00[0x04];
  u16 unknown04; // Inferred role: start frame; original member name unknown.
  u16 unknown06; // Inferred role: end frame; original member name unknown.
};

struct unknown007 {
  u8 _00[0x28];
  s32 unknown28; // Inferred role: frame param count; original member name unknown.
};

static_assert(offsetof(unknown007, unknown28) == 0x28, "");
static_assert(offsetof(unknown004, unknown02) == 0x02, "");
static_assert(offsetof(unknown006, unknown06) == 0x06, "");

} // namespace

u32 LayerActDef::calcDefActionWorkSize(const u8 *data) { return sizeof(LayerActWork) + reinterpret_cast<const LyrActionHeader *>(data)->actionNum * sizeof(u32); }

void LayerActDef::setupDefAction(u8 *work, const u8 *data) { setupAction(work, data); }

bool LayerActDef::actcmd_iconnum(const u8 *&cmd) {
  unknown2a4 = reinterpret_cast<const unknown004 *>(cmd)->unknown02;
  cmd += 4;
  return false;
}

bool LayerActDef::actcmd_animdef(const u8 *&cmd) {
  s32 count = reinterpret_cast<const unknown007 *>(unknownb8)->unknown28;
  for (s32 i = 0; i < count; i++) {
    unknown2b0[i].unknown00 = 0.0f;
    unknown2b0[i].unknown04 = 0.0f;
  }
  unknown298->unknown80 = unknown298->unknown00->unknown18;
  unknown298->unknown84 = 0.0f;
  unknown2b8 = 0;
  cmd += 4;
  return false;
}

bool LayerActDef::actcmd_animfrm(const u8 *&cmd) {
  if (unknown250->unknown24 & 1) {
    const unknown006 *data = reinterpret_cast<const unknown006 *>(cmd);
    unknown298->unknown84 = data->unknown04;
    unknown298->unknown80 = data->unknown06;
    unknown2b0->unknown00 = unknown298->unknown84;
  }
  unknown2b0->unknown00 = unknown298->unknown84 + unknown250->unknown14 * unknown298->unknown00->unknown1c;
  cmd += 8;
  if (unknown298->unknown80 <= unknown2b0->unknown00) {
    return false;
  }
  return true;
}

} // namespace layer
