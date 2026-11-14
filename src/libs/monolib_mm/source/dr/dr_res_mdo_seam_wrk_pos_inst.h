#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {
class DrResMdoInstAnmObj;
class DrResMdoPos;
class DrResMdoSeamMemObj;
class DrResMdoSeamParmRead;
class DrResMdoSeamTexture;
class DrResMdoSeamVertex;
struct MdsPosKeepData;
struct MdsPosRangeTreeData;

struct MdsPosReadTreeData {
  u8 _00[0x2a - 0x00];
  u16 unknown2a; // Inferred role: read flags; original member name unknown.
  u8 _2c[0x30 - 0x2c];
};

static_assert(offsetof(MdsPosReadTreeData, unknown2a) == 0x2a, "");
static_assert(sizeof(MdsPosReadTreeData) == 0x30, "");

// Inferred role: header of the base position data of an instance map; original type name unknown.
struct unknown404 {
  u8 _00[0x08];
  u32 unknown08; // Inferred role: offset of the lod range table; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  u32 unknown10; // Inferred role: offset of the lod entries; original member name unknown.
  u8 _14[0x18 - 0x14];
  u32 unknown18; // Inferred role: position keep data offset; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  u32 unknown20; // Inferred role: lod tree index table offset; original member name unknown.
  u8 _24[0x28 - 0x24];
  s32 unknown28; // Inferred role: range tree offset; original member name unknown.
  s32 unknown2c; // Inferred role: root range tree num; original member name unknown.
  u8 _30[0x4c - 0x30];
  u32 unknown4c; // Inferred role: read table offsets offset; original member name unknown.
  u8 _50[0x54 - 0x50];
  u32 unknown54; // Inferred role: tree work offset; original member name unknown.
};

static_assert(offsetof(unknown404, unknown08) == 0x08, "");
static_assert(offsetof(unknown404, unknown10) == 0x10, "");
static_assert(offsetof(unknown404, unknown18) == 0x18, "");
static_assert(offsetof(unknown404, unknown20) == 0x20, "");
static_assert(offsetof(unknown404, unknown28) == 0x28, "");
static_assert(offsetof(unknown404, unknown2c) == 0x2c, "");
static_assert(offsetof(unknown404, unknown4c) == 0x4c, "");
static_assert(offsetof(unknown404, unknown54) == 0x54, "");

// Inferred role: header of the etc position data of an instance map; original type name unknown.
struct unknown405 {
  u8 _00[0x04 - 0x00];
  u32 unknown04; // Inferred role: position keep data offset; original member name unknown.
  u8 _08[0x0c - 0x08];
  u32 unknown0c; // Inferred role: lod tree index table offset; original member name unknown.
  u8 _10[0x14 - 0x10];
  s32 unknown14; // Inferred role: range tree offset; original member name unknown.
  s32 unknown18; // Inferred role: root range tree num; original member name unknown.
  u8 _1c[0x2c - 0x1c];
  u32 unknown2c; // Inferred role: read table offsets offset; original member name unknown.
  u8 _30[0x34 - 0x30];
  u32 unknown34; // Inferred role: tree work offset; original member name unknown.
};

static_assert(offsetof(unknown405, unknown04) == 0x04, "");
static_assert(offsetof(unknown405, unknown0c) == 0x0c, "");
static_assert(offsetof(unknown405, unknown14) == 0x14, "");
static_assert(offsetof(unknown405, unknown18) == 0x18, "");
static_assert(offsetof(unknown405, unknown2c) == 0x2c, "");
static_assert(offsetof(unknown405, unknown34) == 0x34, "");

class DrResMdoSeamWrkPosInst {
public:
  // Inferred role: shared work of the position tree; original type name unknown.
  struct unknown001 {
    const u8 *unknown00; // Inferred role: position data; original member name unknown.
    const u8 *unknown08; // Inferred role: tree; original member name unknown.
    s32 unknown10;       // Inferred role: tree num; original member name unknown.
    s32 unknown14;       // Inferred role: bit table size; original member name unknown.
    u32 *unknown18;      // Inferred role: bit table; original member name unknown.
  };

  // Inferred role: offsets of the position read tables; original type name unknown.
  struct unknown003 {
    u32 unknown00; // Inferred role: vertex index table offset; original member name unknown.
    u8 _04[0x08 - 0x04];
    u32 unknown08; // Inferred role: texture index table offset; original member name unknown.
    u8 _0c[0x10 - 0x0c];
    u32 unknown10; // Inferred role: read tree offset; original member name unknown.
    u8 _14[0x18 - 0x14];
    s32 unknown18; // Inferred role: read tree num; original member name unknown.
  };

  DrResMdoSeamWrkPosInst();
  ~DrResMdoSeamWrkPosInst();
  void releaseBaseInstPos();
  void setupBaseInstPos(const u8 *data, mtl::ALLOC_HANDLE handle, const DrResMdoInstAnmObj *anm);
  void changeMemBaseInstPos(const u8 *data);
  static void seachCalcTbl(u16 *vertexTbl, u16 *textureTbl, DrResMdoSeamVertex *seamVertex, DrResMdoSeamTexture *seamTexture, DrResMdoSeamParmRead *parmRead);
  void seachReadTreeMdl(u32 flags);
  void delCall();
  void changeMemEtcInstPos();
  void update();
  u32 getDataSize() const;
  u32 clipCheck(u32 index);
  u32 *getShwBitTbl(u32 index);
  void setupEtcInstPos(int index, DrResMdoSeamMemObj *memObj, mtl::ALLOC_HANDLE handle, const DrResMdoInstAnmObj *anm);
  void clearShwBitTbl(u32 index);
  void clearAllShwBitTbl();
  void chankReadTreeMdl(const MdsPosReadTreeData *tree, const mm::Vec3 &position);
  void chankReadTreeTextureOnly(const MdsPosReadTreeData *tree, const mm::Vec3 &position);
  void chankReadTreeMdlOnly(const MdsPosReadTreeData *tree, const mm::Vec3 &position);
  void chankReadTreeMdlRangeOnly(const MdsPosReadTreeData *tree, const mm::Vec3 &position, f32 range);
  void chankReadTreeTextureRangeOnly(const MdsPosReadTreeData *tree, const mm::Vec3 &position, f32 range);

  static u16 *s_pVertexTbl;
  static u16 *s_pTextureTbl;
  static DrResMdoSeamVertex *s_pSeamVertex;
  static DrResMdoSeamTexture *s_pSeamTexture;
  static DrResMdoSeamParmRead *s_pParmRead;

  const u8 *unknown00;                  // Inferred role: position data; original member name unknown.
  const MdsPosKeepData *unknown08;      // Inferred role: position keep data; original member name unknown.
  const u32 *unknown10;                 // Inferred role: range tree indices of the lod trees; original member name unknown.
  const MdsPosRangeTreeData *unknown18; // Inferred role: range trees; original member name unknown.
  const unknown003 *unknown20;          // Inferred role: read table offsets; original member name unknown.
  const MdsPosReadTreeData *unknown28;  // Inferred role: read trees; original member name unknown.
  const u16 *unknown30;                 // Inferred role: vertex index table; original member name unknown.
  const u16 *unknown38;                 // Inferred role: texture index table; original member name unknown.
  unknown001 *unknown40;
  DrResMdoPos *unknown48;        // Inferred role: positions; original member name unknown.
  DrResMdoSeamMemObj *unknown50; // Inferred role: memory object; original member name unknown.
  u32 **unknown58;               // Inferred role: shadow bit tables; original member name unknown.
  u32 unknown60;                 // Inferred role: shadow bit table size; original member name unknown.
  u32 unknown64;                 // Inferred role: first inst anm object index; original member name unknown.
  s32 unknown68;                 // Inferred role: inst anm object num; original member name unknown.
  s32 unknown6c;                 // Inferred role: position num; original member name unknown.
  u8 _70[0x74 - 0x70];
  u32 unknown74;   // Inferred role: state flags; original member name unknown.
  void *unknown78; // Inferred role: allocated work; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown40) == 0x40, "");
static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown48) == 0x48, "");
static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown50) == 0x50, "");
static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown58) == 0x58, "");
static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown60) == 0x60, "");
static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown64) == 0x64, "");
static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown68) == 0x68, "");
static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown6c) == 0x6c, "");
static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown74) == 0x74, "");
static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown78) == 0x78, "");
static_assert(sizeof(DrResMdoSeamWrkPosInst) == 0x80, "");

} // namespace ml
