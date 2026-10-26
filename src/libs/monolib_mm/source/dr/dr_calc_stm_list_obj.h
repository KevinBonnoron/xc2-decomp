#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

struct DrCalcStmRes {
  const u8 *unknown00; // Inferred role: data; original member name unknown.
  u8 _08[0x10 - 0x08];
  u8 unknown10; // Inferred role: flags; original member name unknown.
  u8 _11[0x18 - 0x11];
};

static_assert(offsetof(DrCalcStmRes, unknown10) == 0x10, "");
static_assert(sizeof(DrCalcStmRes) == 0x18, "");

class DrCalcStmListObj {
public:
  enum DrTexUseMode {
    DR_TEX_USE_MODE_NONE,
    DR_TEX_USE_MODE_LOW,
    DR_TEX_USE_MODE_MIDDLE,
  };

  void release();
  bool isResSafe() const;
  DrCalcStmRes *getResObj(u32 index);
  DrCalcStmRes *getResVertexObj();
  DrCalcStmRes *getResShaderObj();
  bool isResChange() const;
  bool isResSub() const;
  bool isResTex() const;
  void setUseMode(DrTexUseMode mode);
  grlib::CGLibTextureBuffer *getTexObj(u32 index);
  u32 getAdder();
  u32 texstm_size_Wait();

  u8 _00[0x30];
  DrCalcStmRes *unknown30[2]; // Inferred role: res; original member name unknown.
  u8 _40[0x74 - 0x40];
  u16 unknown74; // Inferred role: vertex res index; original member name unknown.
  u16 unknown76; // Inferred role: shader res index; original member name unknown.
  u8 _78[0x80 - 0x78];
  u32 unknown80; // Inferred role: state flags; original member name unknown.
  u8 _84[0x88 - 0x84];
  u32 unknown88; // Inferred role: wait state; original member name unknown.
  u8 _8c[0xb0 - 0x8c];
  grlib::CGLibTextureBuffer *unknownb0; // Inferred role: textures; original member name unknown.
  u8 _b8[0xcc - 0xb8];
  s32 unknowncc[2]; // Inferred role: use mode per buffer; original member name unknown.
};

static_assert(offsetof(DrCalcStmListObj, unknown30) == 0x30, "");
static_assert(offsetof(DrCalcStmListObj, unknown74) == 0x74, "");
static_assert(offsetof(DrCalcStmListObj, unknown76) == 0x76, "");
static_assert(offsetof(DrCalcStmListObj, unknown80) == 0x80, "");
static_assert(offsetof(DrCalcStmListObj, unknown88) == 0x88, "");
static_assert(offsetof(DrCalcStmListObj, unknownb0) == 0xb0, "");
static_assert(offsetof(DrCalcStmListObj, unknowncc) == 0xcc, "");

} // namespace ml
