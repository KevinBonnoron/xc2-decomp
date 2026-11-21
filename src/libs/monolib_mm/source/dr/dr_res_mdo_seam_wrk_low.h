#pragma once
#include <stddef.h>

#include "dr/dr_res_mdo_seam_res.h"
#include "types.h"

namespace grlib {
class CGLibTriUniformArray;
} // namespace grlib

namespace mm {
struct Vec3;
} // namespace mm

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {
class DrCalcViewWork;
class DrResMdoAlpTbl;
struct unknown504;
struct MdoWrkMatRes;

// Inferred layout of the low map resource header (game symbol MdsSeamLowMapHead, members unknown); offsets are relative to the header.
struct MdsSeamLowMapHead {
  u8 _00[0x08];
  u32 unknown08; // Inferred role: model data offset; original member name unknown.
  u32 unknown0c; // Inferred role: material data offset; original member name unknown.
  u32 unknown10; // Inferred role: fixed animation data offset, 0 when there is none; original member name unknown.
  u8 _14[0x18 - 0x14];
  u32 unknown18; // Inferred role: vertex data offset; original member name unknown.
  u32 unknown1c; // Inferred role: texture data offset; original member name unknown.
  u32 unknown20; // Inferred role: shader data offset; original member name unknown.
};

static_assert(offsetof(MdsSeamLowMapHead, unknown08) == 0x08, "");
static_assert(offsetof(MdsSeamLowMapHead, unknown10) == 0x10, "");
static_assert(offsetof(MdsSeamLowMapHead, unknown20) == 0x20, "");

// Inferred layout of the low map data (game symbol MdsSeamLowData, members unknown); also the entry of the low map table of the seam
// resource (stride 0x48, read by DrMdoCtlSeamRead::callLowMdlStream at 0x71008261bc and DrMdoCtlSeamLowMap::readLowMapCheck).
struct MdsSeamLowData {
  f32 unknown00[3]; // Inferred role: maximum position of the area; original member name unknown.
  f32 unknown0c[3]; // Inferred role: minimum position of the area; original member name unknown.
  u8 _18[0x28 - 0x18];
  u32 unknown28; // Inferred role: data offset in the seam file; original member name unknown.
  u32 unknown2c; // Inferred role: memory size; original member name unknown.
  u16 unknown30; // Inferred role: global index that hides the map, zero for none; original member name unknown.
  u8 _32[0x48 - 0x32];
};

static_assert(offsetof(MdsSeamLowData, unknown0c) == 0x0c, "");
static_assert(offsetof(MdsSeamLowData, unknown28) == 0x28, "");
static_assert(offsetof(MdsSeamLowData, unknown2c) == 0x2c, "");
static_assert(offsetof(MdsSeamLowData, unknown30) == 0x30, "");
static_assert(sizeof(MdsSeamLowData) == 0x48, "");

class DrResMdoSeamWrkLow : public unknown133<DrResMdoSeamWrkLow> {
public:
  DrResMdoSeamWrkLow();
  virtual ~DrResMdoSeamWrkLow();
  void release();
  void changeMemCall();
  void setupWork(MdoWrkMatRes *matRes, grlib::CGLibTriUniformArray *uniforms, mtl::ALLOC_HANDLE handle, const MdsSeamLowMapHead *head, const MdsSeamLowData *data, u32 max);
  bool update(DrCalcViewWork *view, const mm::Vec3 &position, const u32 *hideBits, bool isOpen);

  static f32 SEAM_LOWEMAP_READ_CHECK;

  const MdsSeamLowMapHead *unknown18; // Inferred role: low map header; original member name unknown.
  u8 _20[0x28 - 0x20];
  MdoWrkMatRes *unknown28;       // Inferred role: material work; original member name unknown.
  DrResMdoSeamMemObj *unknown30; // Inferred role: memory object; original member name unknown.
  unknown504 *unknown38;         // Inferred role: render entries; original member name unknown.
  DrResMdoAlpTbl *unknown40;     // Inferred role: alpha table; original member name unknown.
  u8 _48[0x58 - 0x48];
  unknown504 **unknown58; // Inferred role: first alpha render entries per material and kind; original member name unknown.
  u8 _60[0x78 - 0x60];
  s32 *unknown78; // Inferred role: alpha render entry num per kind; original member name unknown.
  u8 _80[0x88 - 0x80];
  void *unknown88; // Inferred role: allocated buffer; original member name unknown.
  u8 _90[0x9c - 0x90];
  u32 unknown9c; // Inferred role: state flags; original member name unknown.
  u32 unknowna0; // Inferred role: low map index; original member name unknown.
  u32 unknowna4; // Inferred role: unknown, cleared by the constructor; original member name unknown.
  u32 unknowna8; // Inferred role: unknown, cleared by the constructor; original member name unknown.
  u32 unknownac; // Inferred role: unknown, cleared by the constructor; original member name unknown.
  s32 unknownb0; // Inferred role: memory size; original member name unknown.
  u32 unknownb4; // Inferred role: unknown, cleared by the constructor; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamWrkLow, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown28) == 0x28, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown30) == 0x30, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown38) == 0x38, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown40) == 0x40, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown58) == 0x58, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown78) == 0x78, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown88) == 0x88, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown9c) == 0x9c, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknowna0) == 0xa0, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknownb0) == 0xb0, "");
static_assert(sizeof(DrResMdoSeamWrkLow) == 0xb8, "");

} // namespace ml
