#pragma once
#include <stddef.h>

#include "dr/dr_res_mdo_seam_res.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace grlib {
class CGLibTriUniformArray;
} // namespace grlib

namespace ml {

struct MdoWrkMatRes;

// Inferred layout of the env map resource header; offsets are relative to the header.
struct MdsSeamEnvMapHead {
  u32 unknown00; // Inferred role: model data offset; original member name unknown.
  u32 unknown04; // Inferred role: material data offset; original member name unknown.
  u32 unknown08; // Inferred role: fixed animation data offset, 0 when there is none; original member name unknown.
  u32 unknown0c; // Inferred role: vertex data offset; original member name unknown.
  u32 unknown10; // Inferred role: texture data offset; original member name unknown.
  u8 _14[0x18 - 0x14];
  u32 unknown18; // Inferred role: shader data offset; original member name unknown.
};

static_assert(offsetof(MdsSeamEnvMapHead, unknown08) == 0x08, "");
static_assert(offsetof(MdsSeamEnvMapHead, unknown18) == 0x18, "");

// Inferred layout of the env map data; offsets are relative to the data.
struct MdsSeamEnvMapData {
  u8 _00[0x38];
  u32 unknown38; // Inferred role: memory size; original member name unknown.
};

static_assert(offsetof(MdsSeamEnvMapData, unknown38) == 0x38, "");

class DrResMdoSeamWrkEnv : public unknown133<DrResMdoSeamWrkEnv> {
public:
  DrResMdoSeamWrkEnv();
  virtual ~DrResMdoSeamWrkEnv();
  void setDispState();
  u32 chkDispState();
  bool update(const mm::Vec3 &position, bool isOpen);
  u8 *getDisplayWrk();
  int getDisplayWrkSize();
  void setDisplayWrk(u8 *work, int size);
  void changeMemCall(const MdsSeamEnvMapHead *head);
  void setInfo(const mm::Vec3 &position, const mm::Vec3 &scale, bool isEnable, u32 flags);
  void release();
  void setupWork(MdoWrkMatRes *matRes, grlib::CGLibTriUniformArray *uniforms, mtl::ALLOC_HANDLE handle, const MdsSeamEnvMapHead *head, const MdsSeamEnvMapData *data);

  const MdsSeamEnvMapHead *unknown18; // Inferred role: env map header; original member name unknown.
  const MdsSeamEnvMapData *unknown20; // Inferred role: env map data; original member name unknown.
  void *unknown28;                    // Inferred role: allocated bit table; original member name unknown.
  u32 *unknown30;                     // Inferred role: render bit table; original member name unknown.
  u8 *m_displayWrk[2];
  int m_displayWrkSize[2];
  u32 unknown50; // Inferred role: env map index; original member name unknown.
  u8 _54[0x58 - 0x54];
  MdoWrkMatRes *unknown58;       // Inferred role: material work; original member name unknown.
  DrResMdoSeamMemObj *unknown60; // Inferred role: memory object; original member name unknown.
  u32 unknown68;                 // Inferred role: info flags; original member name unknown.
  u32 unknown6c;                 // Inferred role: state flags; original member name unknown.
  s32 unknown70;                 // Inferred role: memory size; original member name unknown.
  bool unknown74;                // Inferred role: enable; original member name unknown.
  u8 _75[0x80 - 0x75];
  mm::Vec3 unknown80; // Inferred role: position; original member name unknown.
  mm::Vec3 unknown90; // Inferred role: scale; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamWrkEnv, unknown28) == 0x28, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown20) == 0x20, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown30) == 0x30, "");

static_assert(offsetof(DrResMdoSeamWrkEnv, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, m_displayWrk) == 0x38, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, m_displayWrkSize) == 0x48, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown68) == 0x68, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown50) == 0x50, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown58) == 0x58, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown70) == 0x70, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown6c) == 0x6c, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown74) == 0x74, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown80) == 0x80, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown90) == 0x90, "");

} // namespace ml
