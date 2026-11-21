#pragma once
#include <stddef.h>

#include "dr/dr_res_mdo_seam_res.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace grlib {
class CGLibTriUniformArray;
} // namespace grlib

namespace ml {
class DrCalcClipMan;
class DrCalcViewWork;
class DrMdoCtlSeamBaseMap;
class DrPixlShadowCacheObj;
class DrPixlShadowObj;
class DrResMdoAlpTbl;
class DrResMdoSeamWrkBaseVertex;
struct MdoWrkMatRes;
struct MdsSeamBaMpTreeData;
struct MdsSeamOfsTexTblData;
class DrResMdoSeamParmRead;
struct unknown700;

// Inferred role: base map header of the resource data; the original type name is MdsSeamBaseMapHead (game symbols), the members are unknown.
// Offsets are relative to the header; DrMdoCtlSeamBaseMap::initBaseMapParts (1.0.0: 0x710081fc10) reads unknown0c to unknown2c.
struct MdsSeamBaseMapHead {
  u32 unknown00; // Inferred role: flags; original member name unknown.
  u8 _04[0x0c - 0x04];
  u32 unknown0c; // Inferred role: model data offset; original member name unknown.
  u32 unknown10; // Inferred role: material data offset; original member name unknown.
  u32 unknown14; // Inferred role: fixed animation data offset, 0 when there is none; original member name unknown.
  u32 unknown18; // Inferred role: tree resource offset; original member name unknown.
  u32 unknown1c; // Inferred role: offset of the texture entries; original member name unknown.
  s32 unknown20; // Inferred role: texture entry count; original member name unknown.
  u32 unknown24; // Inferred role: vertex data offset, 0 when there is none; original member name unknown.
  u8 _28[0x2c - 0x28];
  u32 unknown2c; // Inferred role: shader data offset; original member name unknown.
  u32 unknown30; // Inferred role: offset of the texture list indices (u16); original member name unknown.
  s32 unknown34; // Inferred role: texture list index count; original member name unknown.
  u32 unknown38; // Inferred role: offset of the resource that unknown50 of the work points at; original member name unknown.
};

// Inferred role: header of the tree resource at MdsSeamBaseMapHead::unknown18; the offsets are relative to it; original type name unknown.
struct unknown780 {
  u8 _00[0x04];
  u32 unknown04; // Inferred role: offset of the data of unknown30 of the work; original member name unknown.
  u8 _08[0x0c - 0x08];
  u32 unknown0c; // Inferred role: offset of the tree data; original member name unknown.
  u8 _10[0x14 - 0x10];
  u32 unknown14; // Inferred role: offset of the data of unknown40 of the work; original member name unknown.
  u8 _18[0x1c - 0x18];
  u32 unknown1c; // Inferred role: offset of the data of unknown48 of the work; original member name unknown.
};

// Inferred role: header of the model resource at MdsSeamBaseMapHead::unknown0c; original type name unknown.
struct unknown781 {
  u8 _00[0x24];
  u32 unknown24; // Inferred role: offset of the data of unknown60 of the work, 0 when there is none; original member name unknown.
};

// Inferred role: header of the resource at MdsSeamBaseMapHead::unknown38; original type name unknown.
struct unknown782 {
  u8 _00[0x04];
  s32 unknown04; // Inferred role: bit count; calcCacheInfo (1.0.0: 0x710087d2ac) reads the bits i and i + this count of unknowne0 of the work; original member name unknown.
  u32 unknown08; // Inferred role: offset of the data of unknown58 of the work; original member name unknown.
};

// Inferred role: list at the offset unknown24 of the model resource, which unknown60 of the work points at. Layout evidence: updateRenderList (1.0.0: 0x710087ccac)
// and calcCheckClipInfo (0x710087d720) load a u32 offset of the entries (pairs of u16) at +0x00, a signed entry count at +0x04 and a u32 offset of the u16 index data
// at +0x08; original type name unknown.
struct unknown783 {
  u32 unknown00; // Inferred role: offset of the entries; original member name unknown.
  s32 unknown04; // Inferred role: entry count; original member name unknown.
  u32 unknown08; // Inferred role: offset of the index data; original member name unknown.
};

static_assert(offsetof(unknown783, unknown04) == 0x04, "");
static_assert(offsetof(unknown783, unknown08) == 0x08, "");

static_assert(offsetof(MdsSeamBaseMapHead, unknown0c) == 0x0c, "");
static_assert(offsetof(MdsSeamBaseMapHead, unknown10) == 0x10, "");
static_assert(offsetof(MdsSeamBaseMapHead, unknown14) == 0x14, "");
static_assert(offsetof(MdsSeamBaseMapHead, unknown1c) == 0x1c, "");
static_assert(offsetof(MdsSeamBaseMapHead, unknown20) == 0x20, "");
static_assert(offsetof(MdsSeamBaseMapHead, unknown24) == 0x24, "");
static_assert(offsetof(MdsSeamBaseMapHead, unknown2c) == 0x2c, "");
static_assert(offsetof(MdsSeamBaseMapHead, unknown30) == 0x30, "");
static_assert(offsetof(MdsSeamBaseMapHead, unknown34) == 0x34, "");
static_assert(offsetof(MdsSeamBaseMapHead, unknown18) == 0x18, "");
static_assert(offsetof(MdsSeamBaseMapHead, unknown38) == 0x38, "");
static_assert(sizeof(MdsSeamBaseMapHead) == 0x3c, "");
static_assert(offsetof(unknown780, unknown04) == 0x04, "");
static_assert(offsetof(unknown780, unknown0c) == 0x0c, "");
static_assert(offsetof(unknown780, unknown14) == 0x14, "");
static_assert(offsetof(unknown780, unknown1c) == 0x1c, "");
static_assert(offsetof(unknown781, unknown24) == 0x24, "");
static_assert(offsetof(unknown782, unknown04) == 0x04, "");
static_assert(offsetof(unknown782, unknown08) == 0x08, "");

// Inferred role: texture entry of the base map header at MdsSeamBaseMapHead::unknown1c; original type name unknown.
struct unknown785 {
  u16 unknown00; // Inferred role: texture index in the texture list; original member name unknown.
  u16 unknown02; // Inferred role: texture list index; original member name unknown.
  u8 _04[0x06 - 0x04];
  u8 unknown06; // Inferred role: flags, bit 0 is set when the texture is read; original member name unknown.
  u8 _07[0x08 - 0x07];
};

static_assert(offsetof(unknown785, unknown02) == 0x02, "");
static_assert(offsetof(unknown785, unknown06) == 0x06, "");
static_assert(sizeof(unknown785) == 0x08, "");

// Inferred role: render list entry of the base map; original type name unknown.
struct unknown504 {
  u32 unknown00; // Inferred role: mdl entry index; original member name unknown.
  u16 unknown04; // Inferred role: index of the next entry plus one; original member name unknown.
  u16 unknown06; // Inferred role: vertex index; original member name unknown.
  u16 unknown08; // Inferred role: unknown, set by the render list call; original member name unknown.
  u16 unknown0a; // Inferred role: flags, bit 1 selects the dither of the z pre pass; original member name unknown.
};

static_assert(offsetof(unknown504, unknown04) == 0x04, "");
static_assert(offsetof(unknown504, unknown06) == 0x06, "");
static_assert(offsetof(unknown504, unknown08) == 0x08, "");
static_assert(offsetof(unknown504, unknown0a) == 0x0a, "");
static_assert(sizeof(unknown504) == 0x0c, "");

class DrResMdoSeamWrkBase : public unknown133<DrResMdoSeamWrkBase> {
public:
  DrResMdoSeamWrkBase();
  virtual ~DrResMdoSeamWrkBase();
  void seachDefShadowBaseMapRenderChild(DrPixlShadowObj *shadow, DrMdoCtlSeamBaseMap *ctl, const MdsSeamBaMpTreeData *tree);
  void release();
  bool update(DrCalcViewWork *view, const DrResMdoSeamParmRead *parmRead, bool isOpen, u32 flags);
  u32 updateRenderList(DrCalcViewWork *view, DrCalcClipMan *clip, u16 *textureFlags, DrResMdoSeamTexture *textures, u16 *texListFlags, DrResMdoSeamTexList *texLists, DrMdoCtlSeamBaseMap *ctl,
                       const MdsSeamOfsTexTblData *table, u32 flags);
  void setupWork(MdoWrkMatRes *matRes, grlib::CGLibTriUniformArray *uniforms, mtl::ALLOC_HANDLE handle, DrMdoCtlSeamBaseMap *ctl, const MdsSeamBaseMapHead *head, u32 max);
  void setupHeader();
  void changeMemCall();
  void beginBaseMapRenderList();
  bool callTexReadUpdate(u16 *textureListFlags, DrResMdoSeamTexList *texLists, DrMdoCtlSeamBaseMap *ctl);
  void callReleaseReadList(DrMdoCtlSeamBaseMap *ctl, DrResMdoSeamTexList *texLists, const u16 *textureListFlags);
  void callShadowCacheBaseUpdate(u64 mask);
  void beginRender();
  void endRender();
  void setVertexCache(u32 index, DrResMdoSeamMemObj *memObj, int size, DrMdoCtlSeamBaseMap *ctl);
  void selectVertex(int index);
  void releaseCache(DrMdoCtlSeamBaseMap *ctl);
  void calcCacheInfo();
  bool seachShadowBaseMapRender(DrPixlShadowCacheObj &cache, DrMdoCtlSeamBaseMap *ctl);
  bool seachShadowBaseMapRenderChild(DrPixlShadowCacheObj &cache, DrMdoCtlSeamBaseMap *ctl, const MdsSeamBaMpTreeData *tree);
  void seachDefShadowBaseMapRender(DrPixlShadowObj *shadow, DrMdoCtlSeamBaseMap *ctl);
  void stockRenderListBaseMap(int base, u32 kind, u32 index, u32 vertex, bool isAlpha, int unknown);

  // Names from the game symbols _ZN2ml19DrResMdoSeamWrkBase23SEAM_BASEMAP_READ_CHECKE (0x71011b5738), ...26SEAM_BASEMAP_READ_IN_CHECKE (0x71011b573c),
  // ...25SEAM_BASEMAP_VERTEX_CHECKE (0x71011b5740) and ...26SEAM_BASEMAP_VERTEX_MIDDLEE (0x71011b5744); writable data, initial values read from the
  // game's .data (4200.0f, 10.0f, 4000.0f, 4000.0f), written by DrMdoCtlSeamBaseMap::readBaseMapCheck.
  static f32 SEAM_BASEMAP_READ_CHECK;
  static f32 SEAM_BASEMAP_READ_IN_CHECK;
  static f32 SEAM_BASEMAP_VERTEX_CHECK;
  static f32 SEAM_BASEMAP_VERTEX_MIDDLE;

  const unknown700 *unknown18;          // Inferred role: base map entry; original member name unknown.
  const MdsSeamBaseMapHead *unknown20;  // Inferred role: base map header; original member name unknown.
  const unknown780 *unknown28;          // Inferred role: tree resource; original member name unknown.
  const u8 *unknown30;                  // Inferred role: tree resource data; original member name unknown.
  const MdsSeamBaMpTreeData *unknown38; // Inferred role: tree data; original member name unknown.
  const u8 *unknown40;                  // Inferred role: tree resource data; original member name unknown.
  const u8 *unknown48;                  // Inferred role: tree resource data; original member name unknown.
  const unknown782 *unknown50;          // Inferred role: resource at MdsSeamBaseMapHead::unknown38; original member name unknown.
  const u8 *unknown58;                  // Inferred role: data of unknown50; original member name unknown.
  const unknown783 *unknown60;          // Inferred role: list at the offset unknown24 of the model resource, null when there is none; original member name unknown.
  MdoWrkMatRes *unknown68;              // Inferred role: material work; original member name unknown.
  void *unknown70;                      // Inferred role: allocated buffer; original member name unknown.
  DrResMdoSeamWrkBaseVertex *unknown78; // Inferred role: vertices; original member name unknown.
  u8 _80[0x84 - 0x80];
  u32 unknown84; // Inferred role: base map index; original member name unknown.
  u8 _88[0x8c - 0x88];
  u32 unknown8c; // Inferred role: render count; original member name unknown.
  u32 unknown90; // Inferred role: render count; original member name unknown.
  u32 unknown94; // Inferred role: render count; original member name unknown.
  u64 unknown98; // Inferred role: shadow cache update mask; original member name unknown.
  s32 unknowna0; // Inferred role: state flags, cleared by the constructor; original member name unknown.
  u8 _a4[0xa8 - 0xa4];
  void **unknowna8; // Inferred role: allocated buffers; original member name unknown.
  s32 unknownb0;    // Inferred role: allocated buffer count; original member name unknown.
  s32 unknownb4;    // Inferred role: memory size; original member name unknown.
  u8 _b8[0xe0 - 0xb8];
  u32 *unknowne0;  // Inferred role: unknown, cleared by the constructor; original member name unknown.
  u32 *unknowne8;  // Inferred role: unknown, cleared by the constructor; original member name unknown.
  u32 **unknownf0; // Inferred role: shadow bit tables; original member name unknown.
  u32 unknownf8;   // Inferred role: shadow bit table size; original member name unknown.
  u8 _fc[0x100 - 0xfc];
  u32 *unknown100; // Inferred role: shadow bit table of the shadow cache being searched; original member name unknown.
  u8 _108[0x110 - 0x108];
  unknown504 **unknown110; // Inferred role: first render entries per material; original member name unknown.
  unknown504 **unknown118; // Inferred role: first alpha render entries per material; original member name unknown.
  unknown504 **unknown120; // Inferred role: last render entry per material and kind; original member name unknown.
  unknown504 **unknown128; // Inferred role: last alpha render entry per material and kind; original member name unknown.
  s32 *unknown130;         // Inferred role: render entry num per kind; original member name unknown.
  s32 *unknown138;         // Inferred role: alpha render entry num per kind; original member name unknown.
  u8 _140[0x150 - 0x140];
  unknown504 *unknown150;           // Inferred role: render entries; original member name unknown.
  DrResMdoSeamMemObj *unknown158;   // Inferred role: memory object; original member name unknown.
  DrResMdoSeamTexList **unknown160; // Inferred role: texture lists of the header texture entries; original member name unknown.
  DrResMdoAlpTbl *unknown168;       // Inferred role: alpha table; original member name unknown.
  s32 unknown170;                   // Inferred role: render list num; original member name unknown.
  s32 unknown174;                   // Inferred role: render list size; original member name unknown.
  s16 unknown178;                   // Inferred role: selected vertex; original member name unknown.
  s16 unknown17a;                   // Inferred role: unknown, cleared by the constructor; original member name unknown.
  s16 unknown17c;                   // Inferred role: unknown, cleared by the constructor; original member name unknown.
  s16 unknown17e;                   // Inferred role: vertex count; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamWrkBase, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown20) == 0x20, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown28) == 0x28, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown30) == 0x30, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown38) == 0x38, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown40) == 0x40, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown48) == 0x48, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown50) == 0x50, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown58) == 0x58, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown60) == 0x60, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown68) == 0x68, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown78) == 0x78, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown84) == 0x84, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown8c) == 0x8c, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown98) == 0x98, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknowna8) == 0xa8, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknownb4) == 0xb4, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown110) == 0x110, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown130) == 0x130, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown138) == 0x138, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown150) == 0x150, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown158) == 0x158, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknownf0) == 0xf0, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown100) == 0x100, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown170) == 0x170, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown178) == 0x178, "");
static_assert(sizeof(DrResMdoSeamWrkBase) == 0x180, "");

} // namespace ml
