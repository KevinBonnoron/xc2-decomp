#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibVtxInstans;
} // namespace grlib

namespace ml {
class DrResMdoSeamMemObj;
struct MdsSeamLowMapHead;

class DrResMdoSeamWrkLow {
public:
  virtual ~DrResMdoSeamWrkLow();
  void release();
  void changeMemCall();

  u8 _08[0x18 - 0x08];
  const MdsSeamLowMapHead *unknown18; // Inferred role: low map header; original member name unknown.
  u8 _20[0x28 - 0x20];
  void *unknown28;               // Inferred role: allocated work; original member name unknown.
  DrResMdoSeamMemObj *unknown30; // Inferred role: memory object; original member name unknown.
  u8 _38[0x40 - 0x38];
  grlib::CGLibVtxInstans *unknown40; // Inferred role: instance vertex; original member name unknown.
  u8 _48[0x88 - 0x48];
  void *unknown88; // Inferred role: allocated buffer; original member name unknown.
  u8 _90[0x9c - 0x90];
  u32 unknown9c; // Inferred role: state flags; original member name unknown.
  u8 _a0[0xb8 - 0xa0];
};

static_assert(offsetof(DrResMdoSeamWrkLow, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown28) == 0x28, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown30) == 0x30, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown40) == 0x40, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown88) == 0x88, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown9c) == 0x9c, "");
static_assert(sizeof(DrResMdoSeamWrkLow) == 0xb8, "");

} // namespace ml
