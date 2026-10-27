#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

struct MdsSeamEnvMapHead;

class DrResMdoSeamWrkEnv {
public:
  void setDispState();
  u32 chkDispState();
  u8 *getDisplayWrk();
  int getDisplayWrkSize();
  void setDisplayWrk(u8 *work, int size);
  void changeMemCall(const MdsSeamEnvMapHead *head);
  void setInfo(const mm::Vec3 &position, const mm::Vec3 &scale, bool isEnable, u32 flags);

  u8 _00[0x08];
  DrResMdoSeamWrkEnv *unknown08; // Inferred role: next object; original member name unknown.
  u8 _10[0x18 - 0x10];
  const MdsSeamEnvMapHead *unknown18; // Inferred role: env map header; original member name unknown.
  u8 _20[0x38 - 0x20];
  u8 *unknown38[2]; // Inferred role: display work per buffer; original member name unknown.
  int unknown48[2]; // Inferred role: display work size per buffer; original member name unknown.
  u8 _50[0x58 - 0x50];
  u8 _58[0x68 - 0x58];
  u32 unknown68; // Inferred role: info flags; original member name unknown.
  u32 unknown6c; // Inferred role: state flags; original member name unknown.
  u8 _70[0x74 - 0x70];
  bool unknown74; // Inferred role: enable; original member name unknown.
  u8 _75[0x80 - 0x75];
  mm::Vec3 unknown80; // Inferred role: position; original member name unknown.
  mm::Vec3 unknown90; // Inferred role: scale; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamWrkEnv, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown38) == 0x38, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown48) == 0x48, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown68) == 0x68, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown6c) == 0x6c, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown74) == 0x74, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown80) == 0x80, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown90) == 0x90, "");

} // namespace ml
