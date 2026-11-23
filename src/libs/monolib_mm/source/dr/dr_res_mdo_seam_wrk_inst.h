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
class DrCalcViewWork;
class DrMdoCtlSeamInstMap;
class DrPixlShadowCacheObj;
class DrPixlShadowObj;
class DrResMdoPntAlphaMan;
class DrResMdoPos;
class DrResMdoSeamParmRead;
struct MdoArgSeamUpdate;
struct MdsSeamOfsTexTblData;
struct MdoWrkMatRes;
struct unknown721;
class DrResMdoVertex;
class DrResMdoInstAnmObj;
class DrResMdoSeamWrkPosInst;
struct unknown404;
class DrResMdoPosAddList;

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
  u32 unknown48; // Inferred role: offset of the texture list indices (u16); original member name unknown.
  s32 unknown4c; // Inferred role: texture list index count; original member name unknown.
  u8 _50[0x58 - 0x50];
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
  u8 _04[0x08 - 0x04];
  f32 unknown08; // Inferred role: box maximum x; original member name unknown.
  f32 unknown0c; // Inferred role: box maximum y; original member name unknown.
  f32 unknown10; // Inferred role: box maximum z; original member name unknown.
  f32 unknown14; // Inferred role: box minimum x; original member name unknown.
  f32 unknown18; // Inferred role: box minimum y; original member name unknown.
  f32 unknown1c; // Inferred role: box minimum z; original member name unknown.
};

static_assert(sizeof(unknown400) == 0x20, "");

// Inferred role: texture entry of the instance map; original type name unknown.
struct unknown401 {
  u16 unknown00; // Inferred role: texture index in the texture list; original member name unknown.
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
  DrResMdoInstAnmObj *m_drResMdoInstAnmObj; // Inferred role: inst anm object; original member name unknown.
  u8 _18[0x20 - 0x18];
};

static_assert(offsetof(MdoArgSeamInst, m_drResMdoInstAnmObj) == 0x10, "");
static_assert(sizeof(MdoArgSeamInst) == 0x20, "");

class DrResMdoSeamWrkInst : public unknown133<DrResMdoSeamWrkInst> {
public:
  // Inferred role: model info of the instance map; original type name unknown.
  struct unknown002 {
    u16 unknown00; // Inferred role: instance count of the model info; original member name unknown.
    u16 unknown02; // Inferred role: first instance of the range that is drawn, the instances before it are skipped; original member name unknown.
    u16 unknown04; // Inferred role: instance count of the last ranges; original member name unknown.
    u16 unknown06; // Inferred role: instance count of the last range; original member name unknown.
    u16 unknown08; // Inferred role: flags, bit 0 sets up the depth stencil of the z pre pass; original member name unknown.
    u8 _0a[0x0c - 0x0a];
    u16 unknown0c; // Inferred role: mdl entry index; original member name unknown.
    u16 unknown0e; // Inferred role: vertex index, 0xffff for the vertex of the instance map; original member name unknown.
    u8 _10[0x14 - 0x10];
    u32 unknown14;         // Inferred role: vertex offset of the instances; original member name unknown.
    unknown002 *unknown18; // Inferred role: next model info of the occlusion list; original member name unknown.
  };

  DrResMdoSeamWrkInst();
  virtual ~DrResMdoSeamWrkInst();
  void release();
  void releaseCache(DrMdoCtlSeamInstMap *ctl);
  void setupWork(MdoWrkMatRes *matRes, grlib::CGLibTriUniformArray *uniforms, mtl::ALLOC_HANDLE handle, DrMdoCtlSeamInstMap *ctl, const MdsSeamInstMapHead *head, const u32 *hideBits, u32 max,
                 const DrResMdoInstAnmObj *anm);
  void changeMemCall();
  bool update(const DrResMdoSeamParmRead *parmRead, bool isOpen, u32 flags);
  u32 updateRenderList(MdoArgSeamUpdate &arg);
  void calcEtcInstPos(DrMdoCtlSeamInstMap *ctl);
  void calcEtcInstPosUpdate(DrMdoCtlSeamInstMap *ctl);
  bool callReadOffColiTest(const mm::Vec3 &position, const DrResMdoSeamParmRead *parmRead);
  bool callReadColiTest(const mm::Vec3 &position, bool isFirst);
  bool callTexReadUpdate(u16 *textureListFlags, DrResMdoSeamTexList *texLists, DrMdoCtlSeamInstMap *ctl, bool isRelease);
  void calcCacheInfo();
  void beginRenderList(u16 *textureFlags);
  void seachRenderMdlList(MdoArgSeamUpdate &update);
  void seachReadMdlList(u16 *vertexTbl, u16 *textureTbl, DrResMdoSeamVertex *seamVertex, DrResMdoSeamTexture *seamTexture, DrMdoCtlSeamInstMap *ctl);
  void seachNewStreamList(u16 *vertexTbl, DrResMdoSeamVertex *seamVertex, u16 *textureTbl, DrResMdoSeamTexture *seamTexture, DrResMdoSeamParmRead *parmRead, const MdsSeamOfsTexTblData *table,
                          bool isHeight);
  void seachCheckStreamList(u16 *textureFlags, DrResMdoSeamTexture *textures);
  void seachEtcInstPos(DrResMdoSeamParmRead *parmRead, DrMdoCtlSeamInstMap *ctl, bool isFirst);
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

  const unknown721 *unknown18;                    // Inferred role: instance map entry; original member name unknown.
  const MdsSeamInstMapHead *m_mdsSeamInstMapHead; // Inferred role: instance map header; original member name unknown.
  const unknown404 *unknown28;                    // Inferred role: position data; original member name unknown.
  const DrMdoCtlPos::unknown018 *unknown30;       // Inferred role: lod range per position; original member name unknown.
  const DrMdoCtlPos::unknown019 *unknown38;       // Inferred role: lod entries; original member name unknown.
  const u32 *unknown40;                           // Inferred role: gbl id hiding bits; original member name unknown.
  u32 *unknown48;                                 // Inferred role: shadow bit table; original member name unknown.
  MdoWrkMatRes *m_mdoWrkMatRes;                   // Inferred role: material work; original member name unknown.
  u8 *unknown58;                                  // Inferred role: allocated work; original member name unknown.
  DrResMdoVertex *m_drResMdoVertex;               // Inferred role: vertex; original member name unknown.
  u32 unknown68;                                  // Inferred role: inst map index; original member name unknown.
  u8 _6c[0x70 - 0x6c];
  u32 unknown70; // Inferred role: position model count; original member name unknown.
  u32 unknown74; // Inferred role: render count; original member name unknown.
  u32 unknown78; // Inferred role: unknown, cleared by setupWork; original member name unknown.
  u32 unknown7c; // Inferred role: size of the bit tables part of the allocated work; original member name unknown.
  f32 unknown80; // Inferred role: shadow check range; original member name unknown.
  s32 unknown84; // Inferred role: memory size; original member name unknown.
  s16 unknown88; // Inferred role: read count; original member name unknown.
  u16 unknown8a; // Inferred role: state flags; original member name unknown.
  u8 _8c[0x90 - 0x8c];
  void **unknown90; // Inferred role: render buffers; original member name unknown.
  s32 unknown98;    // Inferred role: render buffer count; original member name unknown.
  u8 _9c[0xa0 - 0x9c];
  u32 *unknowna0; // Inferred role: material bit table, the bits i and i + the material count, also the material update flags; original member name unknown.
  u32 *unknowna8; // Inferred role: material bit table of the materials with a texture that is not read yet; original member name unknown.
  u32 *unknownb0; // Inferred role: mdl bit table, the bits i and i + the mdl entry count; original member name unknown.
  u32 *unknownb8; // Inferred role: mdl bit table of the mdl entries with a texture that is not read yet; original member name unknown.
  u32 *unknownc0; // Inferred role: texture bit table of the height textures to read; original member name unknown.
  u32 *unknownc8; // Inferred role: read model bit table; original member name unknown.
  u32 *unknownd0; // Inferred role: sub model bit table; original member name unknown.
  u32 *unknownd8; // Inferred role: bit table; original member name unknown.
  u32 *unknowne0; // Inferred role: texture bit table, the bits i and i + the entry count; original member name unknown.
  u32 *unknowne8; // Inferred role: etc position bit table; original member name unknown.
  u8 _f0[0xf8 - 0xf0];
  u32 *unknownf8;                             // Inferred role: allocated bit table of 0x40 bytes; original member name unknown.
  u32 *unknown100;                            // Inferred role: allocated bit table of 0x40 bytes; original member name unknown.
  DrResMdoSeamMemObj *m_drResMdoSeamMemObj;   // Inferred role: memory object; original member name unknown.
  DrResMdoSeamTexList **unknown110;           // Inferred role: texture lists; original member name unknown.
  DrResMdoSeamWrkPosInst *unknown118;         // Inferred role: position objects; original member name unknown.
  DrResMdoSeamWrkPosInst **unknown120;        // Inferred role: used position objects; original member name unknown.
  DrResMdoSeamWrkPosInst *unknown128;         // Inferred role: current position object; original member name unknown.
  DrResMdoSeamWrkInst *m_drResMdoSeamWrkInst; // Inferred role: linked inst map; original member name unknown.
  DrResMdoPosAddList *unknown138;             // Inferred role: position add list of the ctl, set by setupWork; original member name unknown.
  s32 unknown140;                             // Inferred role: position object count; original member name unknown.
  s32 unknown144;                             // Inferred role: render object count; original member name unknown.
  s32 unknown148;                             // Inferred role: render count; original member name unknown.
  s32 unknown14c;                             // Inferred role: model info count; original member name unknown.
  u16 unknown150;                             // Inferred role: model info index; original member name unknown.
  u16 unknown152;                             // Inferred role: model info count of the render type; original member name unknown.
  u16 unknown154;                             // Inferred role: unknown flags; original member name unknown.
  u16 unknown156;                             // Inferred role: shadow flags; original member name unknown.
  u32 unknown158;                             // Inferred role: shadow cache flags; original member name unknown.
  u8 _15c[0x160 - 0x15c];
  DrResMdoPos **unknown160[3];                // Inferred role: render list heads per mdl entry, one list per render type; original member name unknown.
  DrResMdoPos **unknown178;                   // Inferred role: allocated array per mdl entry, same kind as unknown160; original member name unknown.
  DrResMdoPos **unknown180;                   // Inferred role: allocated array per mdl entry, same kind as unknown160; original member name unknown.
  DrResMdoPos **unknown188;                   // Inferred role: allocated array per mdl entry, same kind as unknown160; original member name unknown.
  u16 *unknown190;                            // Inferred role: allocated array of 2 bytes per mdl entry; original member name unknown.
  DrResMdoPntAlphaMan *m_drResMdoPntAlphaMan; // Inferred role: point alpha manager; original member name unknown.
  unknown002 *unknown1a0;                     // Inferred role: model infos; original member name unknown.
  void *unknown1a8;                           // Inferred role: allocated array of 8 bytes per mdl entry; original member name unknown.
  unknown002 *unknown1b0;                     // Inferred role: head of the occlusion model info list, cleared by the constructor; original member name unknown.
  unknown002 *unknown1b8;                     // Inferred role: tail of the occlusion model info list, cleared by the constructor; original member name unknown.
  DrCalcViewWork *unknown1c0;                 // Inferred role: view work of the calc man, set by setupWork; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamWrkInst, m_mdsSeamInstMapHead) == 0x20, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown7c) == 0x7c, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknownf8) == 0xf8, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown138) == 0x138, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown178) == 0x178, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown190) == 0x190, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown1a8) == 0x1a8, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown1c0) == 0x1c0, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown28) == 0x28, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown30) == 0x30, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown38) == 0x38, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown40) == 0x40, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown48) == 0x48, "");
static_assert(offsetof(DrResMdoSeamWrkInst, m_mdoWrkMatRes) == 0x50, "");
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
static_assert(offsetof(DrResMdoSeamWrkInst, m_drResMdoSeamMemObj) == 0x108, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown110) == 0x110, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown118) == 0x118, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown120) == 0x120, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown128) == 0x128, "");
static_assert(offsetof(DrResMdoSeamWrkInst, m_drResMdoSeamWrkInst) == 0x130, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown140) == 0x140, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown14c) == 0x14c, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown150) == 0x150, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown152) == 0x152, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown156) == 0x156, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown160) == 0x160, "");
static_assert(offsetof(DrResMdoSeamWrkInst, m_drResMdoPntAlphaMan) == 0x198, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown1a0) == 0x1a0, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown1b0) == 0x1b0, "");
static_assert(offsetof(DrResMdoSeamWrkInst::unknown002, unknown02) == 0x02, "");
static_assert(offsetof(DrResMdoSeamWrkInst::unknown002, unknown04) == 0x04, "");
static_assert(offsetof(DrResMdoSeamWrkInst::unknown002, unknown06) == 0x06, "");
static_assert(offsetof(DrResMdoSeamWrkInst::unknown002, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoSeamWrkInst::unknown002, unknown0c) == 0x0c, "");
static_assert(offsetof(DrResMdoSeamWrkInst::unknown002, unknown0e) == 0x0e, "");
static_assert(offsetof(DrResMdoSeamWrkInst::unknown002, unknown14) == 0x14, "");
static_assert(offsetof(DrResMdoSeamWrkInst::unknown002, unknown18) == 0x18, "");
static_assert(sizeof(DrResMdoSeamWrkInst::unknown002) == 0x20, "");
static_assert(sizeof(DrResMdoSeamWrkInst) == 0x1c8, "");

} // namespace ml
