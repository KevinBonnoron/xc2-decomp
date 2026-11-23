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

// Inferred layout of the animicon action command header, followed by its u16 icon numbers; original type and member names unknown.
struct unknown024 {
  u8 _00[0x02];
  u16 unknown02; // Inferred role: icon count; original member name unknown.
  f32 unknown04; // Inferred role: end sec; original member name unknown.
  f32 unknown08; // Inferred role: icons per sec; original member name unknown.
};

static_assert(offsetof(unknown007, unknown28) == 0x28, "");
static_assert(offsetof(unknown004, unknown02) == 0x02, "");
static_assert(offsetof(unknown006, unknown06) == 0x06, "");
static_assert(sizeof(unknown024) == 0x0c, "");

} // namespace

LayerActDef::LayerActDef() {}

void LayerActDef::updatePartsAction(const LyrActionData *action) {
  const u8 *cmd = unknown250->unknown00 + action->unknown0c;
  bool isCmdEnd = false;
  for (s32 i = 0; i < action->unknown10; i++) {
    isCmdEnd |= (this->*s_pCallActCmd[*reinterpret_cast<const u16 *>(cmd)])(cmd);
  }
  checkActionEnd(action, isCmdEnd);
}

u32 LayerActDef::calcDefActionWorkSize(const u8 *data) { return sizeof(unknown084) + reinterpret_cast<const unknown083 *>(data)->actionNum * sizeof(u32); }

void LayerActDef::setupDefAction(u8 *work, const u8 *data) { setupAction(work, data); }

bool LayerActDef::actcmd_iconnum(const u8 *&cmd) {
  unknown2a4 = reinterpret_cast<const unknown004 *>(cmd)->unknown02;
  cmd += 4;
  return false;
}

bool LayerActDef::actcmd_animicon(const u8 *&cmd) {
  const unknown024 *data = reinterpret_cast<const unknown024 *>(cmd);
  const u16 *icons = reinterpret_cast<const u16 *>(data + 1);
  bool result;
  if (data->unknown04 <= unknown250->unknown14) {
    unknown2a4 = icons[data->unknown02 - 1];
    result = false;
  } else {
    unknown2a4 = icons[static_cast<u32>(unknown250->unknown14 * data->unknown08)];
    result = true;
  }
  cmd = cmd + sizeof(unknown024) + data->unknown02 * sizeof(u16);
  return result;
}

bool LayerActDef::actcmd_animdef(const u8 *&cmd) {
  s32 count = reinterpret_cast<const unknown007 *>(m_resData)->unknown28;
  for (s32 i = 0; i < count; i++) {
    unknown2b0[i].m_second = 0.0f;
    unknown2b0[i].unknown04 = 0;
  }
  unknown298->unknown80 = unknown298->unknown00->unknown18;
  unknown298->unknown84 = 0.0f;
  unknown2b8 = 0.0f;
  cmd += 4;
  return false;
}

bool LayerActDef::actcmd_animfrm(const u8 *&cmd) {
  if (unknown250->unknown24 & 1) {
    const unknown006 *data = reinterpret_cast<const unknown006 *>(cmd);
    unknown298->unknown84 = data->unknown04;
    unknown298->unknown80 = data->unknown06;
    unknown2b0->m_second = unknown298->unknown84;
  }
  unknown2b0->m_second = unknown298->unknown84 + unknown250->unknown14 * unknown298->unknown00->unknown1c;
  cmd += 8;
  if (unknown298->unknown80 <= unknown2b0->m_second) {
    return false;
  }
  return true;
}

} // namespace layer
