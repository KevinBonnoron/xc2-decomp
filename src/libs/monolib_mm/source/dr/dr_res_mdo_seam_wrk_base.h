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
struct MdsSeamBaseMapHead {
  u32 unknown00; // Inferred role: flags; original member name unknown.
  u8 _04[0x38 - 0x04];
};

// Inferred role: render list entry of the base map; original type name unknown.
struct unknown504 {
  u32 unknown00; // Inferred role: mdl entry index; original member name unknown.
  u16 unknown04; // Inferred role: index of the next entry plus one; original member name unknown.
  u16 unknown06; // Inferred role: vertex index; original member name unknown.
  u16 unknown08; // Inferred role: unknown, set by the render list call; original member name unknown.
  u8 _0a[0x0c - 0x0a];
};

static_assert(offsetof(unknown504, unknown04) == 0x04, "");
static_assert(offsetof(unknown504, unknown06) == 0x06, "");
static_assert(offsetof(unknown504, unknown08) == 0x08, "");
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
  void beginBaseMapRenderList();
  void callShadowCacheBaseUpdate(u64 mask);
  void beginRender();
  void endRender();
  void setVertexCache(u32 index, DrResMdoSeamMemObj *memObj, int size, DrMdoCtlSeamBaseMap *ctl);
  void selectVertex(int index);
  void releaseCache(DrMdoCtlSeamBaseMap *ctl);
  bool seachShadowBaseMapRender(DrPixlShadowCacheObj &cache, DrMdoCtlSeamBaseMap *ctl);
  void seachDefShadowBaseMapRender(DrPixlShadowObj *shadow, DrMdoCtlSeamBaseMap *ctl);
  void stockRenderListBaseMap(int base, u32 kind, u32 index, u32 vertex, bool isAlpha, int unknown);

  const unknown700 *unknown18;         // Inferred role: base map entry; original member name unknown.
  const MdsSeamBaseMapHead *unknown20; // Inferred role: base map header; original member name unknown.
  u8 _28[0x38 - 0x28];
  const MdsSeamBaMpTreeData *unknown38; // Inferred role: tree data; original member name unknown.
  u8 _40[0x68 - 0x40];
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
  u8 _fc[0x110 - 0xfc];
  unknown504 **unknown110; // Inferred role: first render entries per material; original member name unknown.
  unknown504 **unknown118; // Inferred role: first alpha render entries per material; original member name unknown.
  unknown504 **unknown120; // Inferred role: last render entry per material and kind; original member name unknown.
  unknown504 **unknown128; // Inferred role: last alpha render entry per material and kind; original member name unknown.
  s32 *unknown130;         // Inferred role: render entry num per kind; original member name unknown.
  s32 *unknown138;         // Inferred role: alpha render entry num per kind; original member name unknown.
  u8 _140[0x150 - 0x140];
  unknown504 *unknown150;         // Inferred role: render entries; original member name unknown.
  DrResMdoSeamMemObj *unknown158; // Inferred role: memory object; original member name unknown.
  u8 _160[0x168 - 0x160];
  DrResMdoAlpTbl *unknown168; // Inferred role: alpha table; original member name unknown.
  s32 unknown170;             // Inferred role: render list num; original member name unknown.
  s32 unknown174;             // Inferred role: render list size; original member name unknown.
  s16 unknown178;             // Inferred role: selected vertex; original member name unknown.
  s16 unknown17a;             // Inferred role: unknown, cleared by the constructor; original member name unknown.
  s16 unknown17c;             // Inferred role: unknown, cleared by the constructor; original member name unknown.
  s16 unknown17e;             // Inferred role: vertex count; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamWrkBase, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown20) == 0x20, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown38) == 0x38, "");
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
static_assert(offsetof(DrResMdoSeamWrkBase, unknown170) == 0x170, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown178) == 0x178, "");
static_assert(sizeof(DrResMdoSeamWrkBase) == 0x180, "");

} // namespace ml
