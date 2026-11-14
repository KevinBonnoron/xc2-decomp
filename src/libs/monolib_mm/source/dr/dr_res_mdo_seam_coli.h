#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrResMdoSeamMemObj;

struct MdsSeamColiData {
  u8 _00[0x38];
  u32 unknown38; // Inferred role: collision memory size; original member name unknown.
  u8 _3c[0x54 - 0x3c];
  u32 unknown54; // Inferred role: collision flags; original member name unknown.
};

static_assert(offsetof(MdsSeamColiData, unknown38) == 0x38, "");
static_assert(offsetof(MdsSeamColiData, unknown54) == 0x54, "");

class DrResMdoSeamColi {
public:
  DrResMdoSeamColi(int index);
  virtual ~DrResMdoSeamColi();
  void createColi(const void *data, const MdsSeamColiData *coliData);
  void release();
  void setCache(DrResMdoSeamMemObj *cache);

  DrResMdoSeamColi *unknown08; // Inferred role: next; original member name unknown.
  DrResMdoSeamColi *unknown10; // Inferred role: prev; original member name unknown.
  DrResMdoSeamMemObj *m_cache;
  const MdsSeamColiData *unknown20; // Inferred role: collision data; original member name unknown.
  const void *unknown28;            // Inferred role: collision resource; original member name unknown.
  u8 _30[0x38 - 0x30];
  u32 unknown38; // Inferred role: memory size; original member name unknown.
  u16 unknown3c; // Inferred role: index; original member name unknown.
  s16 unknown3e; // Inferred role: wait count; original member name unknown.
  u16 unknown40; // Inferred role: seam idx; original member name unknown.
  u16 unknown42; // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamColi, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoSeamColi, unknown28) == 0x28, "");
static_assert(offsetof(DrResMdoSeamColi, unknown38) == 0x38, "");
static_assert(offsetof(DrResMdoSeamColi, unknown42) == 0x42, "");
static_assert(sizeof(DrResMdoSeamColi) == 0x48, "");

} // namespace ml
