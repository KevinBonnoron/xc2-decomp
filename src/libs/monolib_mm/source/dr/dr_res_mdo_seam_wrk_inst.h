#pragma once
#include <stddef.h>

#include "dr/dr_mdo_ctl_pos.h"
#include "dr/dr_res_mdo_seam_res.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace grlib {
class CGLibTriUniformArray;
} // namespace grlib

namespace ml {
class DrMdoCtlSeamInstMap;
class DrPixlShadowCacheObj;
class DrPixlShadowObj;
class DrResMdoPntAlphaMan;
class DrResMdoPos;
class DrResMdoSeamParmRead;
struct MdoArgSeamUpdate;
struct MdoWrkMatRes;
struct unknown721;
class DrResMdoVertex;
class DrResMdoInstAnmObj;
class DrResMdoSeamWrkPosInst;
struct unknown404;

struct MdsSeamInstMapHead {
  u8 unknown00; // Inferred role: flags; original member name unknown.
  u8 _01[0x0c - 0x01];
  u32 unknown0c; // Inferred role: offset of the model data; original member name unknown.
  u32 unknown10; // Inferred role: offset of the material data; original member name unknown.
  u32 unknown14; // Inferred role: offset of the fixed animation data; original member name unknown.
  u32 unknown18; // Inferred role: offset of the position data; original member name unknown.
  u32 unknown1c; // Inferred role: offset of the vertex data; original member name unknown.
  u32 unknown20; // Inferred role: offset of the texture entries; original member name unknown.
  s32 unknown24; // Inferred role: texture entry count; original member name unknown.
  u8 _28[0x2c - 0x28];
  s32 unknown2c; // Inferred role: model count; original member name unknown.
  u8 _30[0x38 - 0x30];
  u32 unknown38; // Inferred role: offset of the etc position entries; original member name unknown.
  s32 unknown3c; // Inferred role: etc position entry count; original member name unknown.
  u8 _40[0x44 - 0x40];
  u32 unknown44; // Inferred role: offset of the shader data; original member name unknown.
  u8 _48[0x58 - 0x48];
};

static_assert(offsetof(MdsSeamInstMapHead, unknown18) == 0x18, "");
static_assert(offsetof(MdsSeamInstMapHead, unknown0c) == 0x0c, "");
static_assert(offsetof(MdsSeamInstMapHead, unknown14) == 0x14, "");
static_assert(offsetof(MdsSeamInstMapHead, unknown44) == 0x44, "");
static_assert(offsetof(MdsSeamInstMapHead, unknown24) == 0x24, "");
static_assert(offsetof(MdsSeamInstMapHead, unknown2c) == 0x2c, "");
static_assert(offsetof(MdsSeamInstMapHead, unknown38) == 0x38, "");
static_assert(offsetof(MdsSeamInstMapHead, unknown3c) == 0x3c, "");

// Inferred role: etc position entry of the instance map; original type name unknown.
struct unknown400 {
  s32 unknown00; // Inferred role: etc position id; original member name unknown.
  u8 _04[0x20 - 0x04];
};

static_assert(sizeof(unknown400) == 0x20, "");

// Inferred role: texture entry of the instance map; original type name unknown.
struct unknown401 {
  u8 _00[0x02 - 0x00];
  u16 unknown02; // Inferred role: texture list index; original member name unknown.
  u16 unknown04; // Inferred role: seam texture index; original member name unknown.
  u16 unknown06; // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(unknown401, unknown02) == 0x02, "");
static_assert(offsetof(unknown401, unknown04) == 0x04, "");
static_assert(offsetof(unknown401, unknown06) == 0x06, "");
static_assert(sizeof(unknown401) == 0x08, "");

struct MdoArgSeamInst {
  s32 unknown00; // Inferred role: alpha; original member name unknown.
  u8 _04[0x10 - 0x04];
  DrResMdoInstAnmObj *unknown10; // Inferred role: inst anm object; original member name unknown.
  u8 _18[0x20 - 0x18];
};

static_assert(offsetof(MdoArgSeamInst, unknown10) == 0x10, "");
static_assert(sizeof(MdoArgSeamInst) == 0x20, "");

class DrResMdoSeamWrkInst : public unknown133<DrResMdoSeamWrkInst> {
public:
  // Inferred role: model info of the instance map; original type name unknown.
  struct unknown002 {
    u8 _00[0x20];
  };

  DrResMdoSeamWrkInst();
  virtual ~DrResMdoSeamWrkInst();
  void release();
  void releaseCache(DrMdoCtlSeamInstMap *ctl);
  void setupWork(MdoWrkMatRes *matRes, grlib::CGLibTriUniformArray *uniforms, mtl::ALLOC_HANDLE handle, DrMdoCtlSeamInstMap *ctl, const MdsSeamInstMapHead *head, const u32 *hideBits, u32 max,
                 const DrResMdoInstAnmObj *anm);
  void changeMemCall();
  bool update(const DrResMdoSeamParmRead *parmRead, bool isOpen, u32 flags);
  void calcEtcInstPos(DrMdoCtlSeamInstMap *ctl);
  void calcEtcInstPosUpdate(DrMdoCtlSeamInstMap *ctl);
  bool callReadOffColiTest(const mm::Vec3 &position, const DrResMdoSeamParmRead *parmRead);
  bool callReadColiTest(const mm::Vec3 &position, bool isFirst);
  void calcCacheInfo();
  void beginRenderList(u16 *textureFlags);
  void seachRenderMdlList(MdoArgSeamUpdate &update);
  void seachReadMdlList(u16 *vertexTbl, u16 *textureTbl, DrResMdoSeamVertex *seamVertex, DrResMdoSeamTexture *seamTexture, DrMdoCtlSeamInstMap *ctl);
  void seachCheckStreamList(u16 *textureFlags, DrResMdoSeamTexture *textures);
  void seachShadowCheck(DrResMdoInstAnmObj *anm);
  u32 isSubMdl(u32 index);
  bool chankRenderMdl(const MdsPosRangeTreeData *tree, MdoArgSeamInst &arg);
  bool objPartsRenderMdl(const MdsPosKeepData *keep, DrResMdoPos *pos, const MdoArgSeamInst &arg);
  bool clipRenderMdl(const MdsPosRangeTreeData *tree, MdoArgSeamInst &arg);
  void linkRenderMdlList(u32 index, MdoArgSeamInst &arg);
  void linkReadMdl();
  bool linkShadowRenderMdl(u32 index, DrPixlShadowCacheObj &cache, DrMdoCtlSeamInstMap *ctl, f32 range);
  bool seachShadowInstMapRenderChild(DrPixlShadowCacheObj &cache, DrMdoCtlSeamInstMap *ctl, const MdsPosRangeTreeData *tree);
  void linkDefShadowRenderMdl(u32 index, DrPixlShadowObj *shadow, DrMdoCtlSeamInstMap *ctl);
  void seachDefShadowInstMapRenderChild(DrPixlShadowObj *shadow, DrMdoCtlSeamInstMap *ctl, const MdsPosRangeTreeData *tree);
  void linkReadMdl(u32 index);
  bool setEtcPosCache(mtl::ALLOC_HANDLE handle, int index, DrResMdoSeamMemObj *memObj, const DrResMdoInstAnmObj *anm);
  void beginMdl();
  unknown002 *getMdlInfo();
  void callShadowCacheInstUpdate(u64 mask);
  bool seachShadowInstMapRender(DrPixlShadowCacheObj &cache, DrMdoCtlSeamInstMap *ctl);
  void seachDefShadowInstMapRender(DrPixlShadowObj *shadow, DrMdoCtlSeamInstMap *ctl);
  void occRender();

  const unknown721 *unknown18;              // Inferred role: instance map entry; original member name unknown.
  const MdsSeamInstMapHead *unknown20;      // Inferred role: instance map header; original member name unknown.
  const unknown404 *unknown28;              // Inferred role: position data; original member name unknown.
  const DrMdoCtlPos::unknown018 *unknown30; // Inferred role: lod range per position; original member name unknown.
  const DrMdoCtlPos::unknown019 *unknown38; // Inferred role: lod entries; original member name unknown.
  const u32 *unknown40;                     // Inferred role: gbl id hiding bits; original member name unknown.
  u32 *unknown48;                           // Inferred role: shadow bit table; original member name unknown.
  MdoWrkMatRes *unknown50;                  // Inferred role: material work; original member name unknown.
  void *unknown58;                          // Inferred role: allocated work; original member name unknown.
  DrResMdoVertex *unknown60;                // Inferred role: vertex; original member name unknown.
  u32 unknown68;                            // Inferred role: inst map index; original member name unknown.
  u8 _6c[0x70 - 0x6c];
  u32 unknown70; // Inferred role: position model count; original member name unknown.
  u32 unknown74; // Inferred role: render count; original member name unknown.
  u8 _78[0x80 - 0x78];
  f32 unknown80; // Inferred role: shadow check range; original member name unknown.
  s32 unknown84; // Inferred role: memory size; original member name unknown.
  s16 unknown88; // Inferred role: read count; original member name unknown.
  u16 unknown8a; // Inferred role: state flags; original member name unknown.
  u8 _8c[0x90 - 0x8c];
  void **unknown90; // Inferred role: render buffers; original member name unknown.
  s32 unknown98;    // Inferred role: render buffer count; original member name unknown.
  u8 _9c[0xc8 - 0x9c];
  u32 *unknownc8; // Inferred role: read model bit table; original member name unknown.
  u32 *unknownd0; // Inferred role: sub model bit table; original member name unknown.
  u32 *unknownd8; // Inferred role: bit table; original member name unknown.
  u8 _e0[0xe8 - 0xe0];
  u32 *unknowne8; // Inferred role: etc position bit table; original member name unknown.
  u8 _f0[0x108 - 0xf0];
  DrResMdoSeamMemObj *unknown108;      // Inferred role: memory object; original member name unknown.
  DrResMdoSeamTexList **unknown110;    // Inferred role: texture lists; original member name unknown.
  DrResMdoSeamWrkPosInst *unknown118;  // Inferred role: position objects; original member name unknown.
  DrResMdoSeamWrkPosInst **unknown120; // Inferred role: used position objects; original member name unknown.
  DrResMdoSeamWrkPosInst *unknown128;  // Inferred role: current position object; original member name unknown.
  DrResMdoSeamWrkInst *unknown130;     // Inferred role: linked inst map; original member name unknown.
  u8 _138[0x140 - 0x138];
  s32 unknown140; // Inferred role: position object count; original member name unknown.
  s32 unknown144; // Inferred role: render object count; original member name unknown.
  u8 _148[0x14c - 0x148];
  s32 unknown14c; // Inferred role: model info count; original member name unknown.
  u16 unknown150; // Inferred role: model info index; original member name unknown.
  u8 _152[0x156 - 0x152];
  u16 unknown156; // Inferred role: shadow flags; original member name unknown.
  u32 unknown158; // Inferred role: shadow cache flags; original member name unknown.
  u8 _15c[0x198 - 0x15c];
  DrResMdoPntAlphaMan *unknown198; // Inferred role: point alpha manager; original member name unknown.
  unknown002 *unknown1a0;          // Inferred role: model infos; original member name unknown.
  u8 _1a8[0x1b0 - 0x1a8];
  void *unknown1b0; // Inferred role: unknown work, cleared by the constructor; original member name unknown.
  void *unknown1b8; // Inferred role: unknown work, cleared by the constructor; original member name unknown.
  u8 _1c0[0x1c8 - 0x1c0];
};

static_assert(offsetof(DrResMdoSeamWrkInst, unknown20) == 0x20, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown28) == 0x28, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown30) == 0x30, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown38) == 0x38, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown40) == 0x40, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown48) == 0x48, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown50) == 0x50, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown68) == 0x68, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown70) == 0x70, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown80) == 0x80, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown84) == 0x84, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown88) == 0x88, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown90) == 0x90, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown98) == 0x98, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknownc8) == 0xc8, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknownd0) == 0xd0, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknowne8) == 0xe8, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown108) == 0x108, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown110) == 0x110, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown118) == 0x118, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown120) == 0x120, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown128) == 0x128, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown130) == 0x130, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown140) == 0x140, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown14c) == 0x14c, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown150) == 0x150, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown156) == 0x156, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown198) == 0x198, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown1a0) == 0x1a0, "");
static_assert(sizeof(DrResMdoSeamWrkInst::unknown002) == 0x20, "");
static_assert(sizeof(DrResMdoSeamWrkInst) == 0x1c8, "");

} // namespace ml
