#pragma once
#include <stddef.h>

#include "dr/dr_mdl_obj.h"
#include "dr/dr_res_mdo_inst_anm_obj.h"
#include "mm_math/mm_mat44.h"
#include "types.h"

namespace grlib {
class CGLibVtxInstans;
} // namespace grlib

namespace ml {

class DrCalcClipMan;
class DrCalcCpPlaneObj;
class DrCalcViewWork;
class DrMan;
class DrPixlShadowObj;
class DrResMdoInstMdlInfo;
class DrResMdoPntAlphaMan;
class DrResMdoPosAddList;
class DrResMdoSortPos;
class DrResWrkClipList;
struct _MdoInstanceWork;
struct MdsMdlInfoHeader;
class DrPixlShadowCacheObj;
class DrResMdoPos;

struct MdsPosRangeTreeData {
  f32 unknown00[3]; // Inferred role: center; original member name unknown.
  f32 unknown0c;    // Inferred role: radius; original member name unknown.
  f32 unknown10;    // Inferred role: squared render distance; original member name unknown.
  u32 unknown14;    // Inferred role: offset of the child tree indices; original member name unknown.
  u32 unknown18;    // Inferred role: offset of the position indices; original member name unknown.
  u16 unknown1c;    // Inferred role: child tree count; original member name unknown.
  u16 unknown1e;    // Inferred role: position count; original member name unknown.
};

static_assert(offsetof(MdsPosRangeTreeData, unknown0c) == 0x0c, "");
static_assert(offsetof(MdsPosRangeTreeData, unknown10) == 0x10, "");
static_assert(offsetof(MdsPosRangeTreeData, unknown14) == 0x14, "");
static_assert(offsetof(MdsPosRangeTreeData, unknown1c) == 0x1c, "");
static_assert(offsetof(MdsPosRangeTreeData, unknown1e) == 0x1e, "");
static_assert(sizeof(MdsPosRangeTreeData) == 0x20, "");

struct MdsPosKeepData {
  mm::Mat44 unknown00; // Inferred role: matrix; original member name unknown.
  u8 _40[0x4c - 0x40];
  f32 unknown4c;    // Inferred role: clip radius; original member name unknown.
  f32 unknown50[3]; // Inferred role: clip center; original member name unknown.
  u32 unknown5c;    // Inferred role: lod range index; original member name unknown.
  u16 unknown60;    // Inferred role: range tree index of the lod trees; original member name unknown.
  u16 unknown62;    // Inferred role: gbl id hiding the position; original member name unknown.
  u8 _64[0x66 - 0x64];
  u16 unknown66; // Inferred role: clip list index plus one; original member name unknown.
  u8 _68[0x70 - 0x68];
};

static_assert(offsetof(MdsPosKeepData, unknown4c) == 0x4c, "");
static_assert(offsetof(MdsPosKeepData, unknown50) == 0x50, "");
static_assert(offsetof(MdsPosKeepData, unknown5c) == 0x5c, "");
static_assert(offsetof(MdsPosKeepData, unknown60) == 0x60, "");
static_assert(offsetof(MdsPosKeepData, unknown62) == 0x62, "");
static_assert(offsetof(MdsPosKeepData, unknown66) == 0x66, "");
static_assert(sizeof(MdsPosKeepData) == 0x70, "");

struct MdoArgInst {
  s32 unknown00;  // Inferred role: alpha; original member name unknown.
  bool unknown04; // Inferred role: lod tree render; original member name unknown.
  f32 unknown08;  // Inferred role: lod distance; original member name unknown.
  f32 unknown0c;  // Inferred role: squared far render distance; original member name unknown.
};

static_assert(offsetof(MdoArgInst, unknown04) == 0x04, "");
static_assert(offsetof(MdoArgInst, unknown08) == 0x08, "");
static_assert(offsetof(MdoArgInst, unknown0c) == 0x0c, "");
static_assert(sizeof(MdoArgInst) == 0x10, "");

class DrMdoCtlPos : public DrMdlObj {
public:
  DrMdoCtlPos(const void *data, const char *path, DrMan *drMan, int viewNum);
  // Inferred role: position resource header; original type name unknown.
  struct unknown017 {
    u8 _00[0x28 - 0x00];
    u32 unknown28; // Inferred role: offset of the range trees; original member name unknown.
    s32 unknown2c; // Inferred role: range tree count; original member name unknown.
  };

  // Inferred role: lod range of a position; original type name unknown.
  struct unknown018 {
    u32 unknown00; // Inferred role: first lod entry index in the low 28 bits; original member name unknown.
    s32 unknown04; // Inferred role: lod entry count; original member name unknown.
  };

  // Inferred role: lod entry; original type name unknown.
  struct unknown019 {
    u8 _00[0x04 - 0x00];
    f32 unknown04; // Inferred role: lod distance; original member name unknown.
    u32 unknown08; // Inferred role: render list index, bit 31 marks a range tree lod; original member name unknown.
  };

  static const int INS_RENDERBUFF_SIZE = 0xbd000; // Name from the game symbol _ZN2ml11DrMdoCtlPos19INS_RENDERBUFF_SIZEE; also in torna and xc1de.

  ~DrMdoCtlPos() override;
  void update() override;
  void dispOffUpdate() override;
  void resourceInit() override;
  void shadowRender() override;
  bool shadowCacheRender(DrPixlShadowCacheObj &cache) override;
  void shadowCacheAddRender(int index) override;
  void callShadowCacheUpdate(u64 flags) override;
  void occRender() override;
  void setDeleteCall(int deleteCall) override;
  void releasePos();
  void updatePos();
  void createMdlList();
  void beginRenderListPos();
  bool chankRenderMdl(const MdsPosRangeTreeData *tree, MdoArgInst &arg);
  bool objPartsRenderMdl(const MdsPosKeepData *keep, DrResMdoPos *pos, const MdoArgInst &arg);
  bool clipRenderMdl(const MdsPosRangeTreeData *tree, MdoArgInst &arg);
  void chankShadowRenderMdl(const MdsPosRangeTreeData *tree, DrPixlShadowCacheObj &cache);
  void clipShadowRenderMdl(const MdsPosRangeTreeData *tree, DrPixlShadowCacheObj &cache);
  void nomTreeShadowRenderMdl(const MdsPosRangeTreeData *tree, DrPixlShadowObj *shadow);
  void createRenderDisplayList(const MdsMdlInfoHeader *header, int index, _MdoInstanceWork *work, grlib::CGLibVtxInstans *instans, int count);
  void callDisplistPrePsssRender(int param);
  void callDisplistRender(int param);
  void callZpreePassRenderPosAll();
  void callRenderPosAll();
  void callRefractionRenderPosAll();
  void callThicknessRenderFirstPosAll();
  void callThicknessRenderSecondPosAll();
  void callGBuffRenderPosAll();
  void callLightPrePassRenderPosAll();
  void callAlphaRenderPosAll();
  void callSpAlphaRenderPosAll();
  void createThicknessRenderFirstDisplayList();
  void createThicknessRenderSecondDisplayList();
  void createThicknessRenderDisplayListSub(bool isFirst);
  void createZBuffRenderDisplayList();
  void callPosRender(u32 renderType);
  void updateInstPosDispCall(const u32 *flags);
  void createInstUniformBlock(const u32 *flags);
  void nomTreeListShadowRenderMdl(const MdsPosRangeTreeData *tree, DrPixlShadowObj *shadow);

  const unknown017 *unknown1a8;          // Inferred role: position resource header; original member name unknown.
  const unknown018 *unknown1b0;          // Inferred role: lod range per position; original member name unknown.
  const unknown019 *unknown1b8;          // Inferred role: lod entries; original member name unknown.
  const u32 *unknown1c0;                 // Inferred role: range tree indices of the lod trees; original member name unknown.
  const MdsPosRangeTreeData *unknown1c8; // Inferred role: range trees; original member name unknown.
  const MdsPosKeepData *unknown1d0;      // Inferred role: position keep data; original member name unknown.
  s32 unknown1d8;                        // Inferred role: position count; original member name unknown.
  u8 _1dc[0x1e0 - 0x1dc];
  DrResMdoPos *unknown1e0;       // Inferred role: positions; original member name unknown.
  DrResMdoInstAnmObj unknown1e8; // Inferred role: inst anm object; original member name unknown.
  DrResWrkClipList *unknown218;  // Inferred role: clip list; original member name unknown.
  void *unknown220;              // Inferred role: work memory; original member name unknown.
  void **unknown228;             // Inferred role: allocated buffers; original member name unknown.
  void *unknown230;              // Inferred role: allocated memory; original member name unknown.
  s32 unknown238;                // Inferred role: allocated buffer count; original member name unknown.
  u8 _23c[0x240 - 0x23c];
  u32 *unknown240;                 // Inferred role: display call flags of the positions; original member name unknown.
  s32 unknown248;                  // Inferred role: render buffer offset; original member name unknown.
  s32 unknown24c;                  // Inferred role: unknown, cleared by resourceInit; original member name unknown.
  DrResMdoPosAddList *unknown250;  // Inferred role: add list; original member name unknown.
  DrResMdoInstMdlInfo *unknown258; // Inferred role: inst mdl info; original member name unknown.
  u16 unknown260;                  // Inferred role: render list count; original member name unknown.
  u16 unknown262;                  // Inferred role: second render list count; original member name unknown.
  u8 _264[0x268 - 0x264];
  DrResMdoSortPos *unknown268;     // Inferred role: z sort object; original member name unknown.
  DrResMdoPos **unknown270[3];     // Inferred role: render list heads; original member name unknown.
  DrResMdoPos **unknown288[3];     // Inferred role: render list tails; original member name unknown.
  u16 *unknown2a0;                 // Inferred role: render list counts; original member name unknown.
  DrResMdoPntAlphaMan *unknown2a8; // Inferred role: pnt alpha man; original member name unknown.
  u8 _2b0[0x2c0 - 0x2b0];
  void *unknown2c0; // Inferred role: first render list entry; original member name unknown.
  u8 _2c8[0x2d8 - 0x2c8];
  u32 unknown2d8; // Inferred role: render list size; original member name unknown.
  u8 _2dc[0x2e0 - 0x2dc];
  u64 unknown2e0[6]; // Inferred role: render list values cleared every frame; original member name unknown.
  u8 _310[0x340 - 0x310];
  u64 unknown340;               // Inferred role: render list value cleared every frame; original member name unknown.
  DrCalcViewWork *unknown348;   // Inferred role: view work; original member name unknown.
  DrCalcClipMan *unknown350;    // Inferred role: clip man; original member name unknown.
  DrCalcCpPlaneObj *unknown358; // Inferred role: clip plane object; original member name unknown.
  u32 unknown360;               // Inferred role: render count; original member name unknown.
  u8 _364[0x368 - 0x364];
  u64 unknown368; // Inferred role: shadow cache mask; original member name unknown.
  u64 unknown370; // Inferred role: shadow cache render mask; original member name unknown.
  u32 unknown378; // Inferred role: shadow cache render count; original member name unknown.
  u8 _37c[0x420 - 0x37c];
};

static_assert(offsetof(DrMdoCtlPos, unknown1a0) == 0x1a0, "");
static_assert(offsetof(DrMdoCtlPos, unknown1a8) == 0x1a8, "");
static_assert(offsetof(DrMdoCtlPos, unknown1b0) == 0x1b0, "");
static_assert(offsetof(DrMdoCtlPos, unknown1b8) == 0x1b8, "");
static_assert(offsetof(DrMdoCtlPos, unknown1c0) == 0x1c0, "");
static_assert(offsetof(DrMdoCtlPos, unknown1c8) == 0x1c8, "");
static_assert(offsetof(DrMdoCtlPos, unknown1d0) == 0x1d0, "");
static_assert(offsetof(DrMdoCtlPos, unknown1d8) == 0x1d8, "");
static_assert(offsetof(DrMdoCtlPos, unknown1e0) == 0x1e0, "");
static_assert(offsetof(DrMdoCtlPos, unknown1e8) == 0x1e8, "");
static_assert(offsetof(DrMdoCtlPos, unknown218) == 0x218, "");
static_assert(offsetof(DrMdoCtlPos, unknown238) == 0x238, "");
static_assert(offsetof(DrMdoCtlPos, unknown240) == 0x240, "");
static_assert(offsetof(DrMdoCtlPos, unknown248) == 0x248, "");
static_assert(offsetof(DrMdoCtlPos, unknown24c) == 0x24c, "");
static_assert(offsetof(DrMdoCtlPos, unknown250) == 0x250, "");
static_assert(offsetof(DrMdoCtlPos, unknown258) == 0x258, "");
static_assert(offsetof(DrMdoCtlPos, unknown260) == 0x260, "");
static_assert(offsetof(DrMdoCtlPos, unknown268) == 0x268, "");
static_assert(offsetof(DrMdoCtlPos, unknown270) == 0x270, "");
static_assert(offsetof(DrMdoCtlPos, unknown288) == 0x288, "");
static_assert(offsetof(DrMdoCtlPos, unknown2a0) == 0x2a0, "");
static_assert(offsetof(DrMdoCtlPos, unknown2a8) == 0x2a8, "");
static_assert(offsetof(DrMdoCtlPos, unknown2c0) == 0x2c0, "");
static_assert(offsetof(DrMdoCtlPos, unknown2d8) == 0x2d8, "");
static_assert(offsetof(DrMdoCtlPos, unknown2e0) == 0x2e0, "");
static_assert(offsetof(DrMdoCtlPos, unknown340) == 0x340, "");
static_assert(offsetof(DrMdoCtlPos, unknown348) == 0x348, "");
static_assert(offsetof(DrMdoCtlPos, unknown350) == 0x350, "");
static_assert(offsetof(DrMdoCtlPos, unknown358) == 0x358, "");
static_assert(offsetof(DrMdoCtlPos, unknown360) == 0x360, "");
static_assert(offsetof(DrMdoCtlPos, unknown368) == 0x368, "");
static_assert(offsetof(DrMdoCtlPos, unknown370) == 0x370, "");
static_assert(offsetof(DrMdoCtlPos, unknown378) == 0x378, "");
static_assert(sizeof(DrMdoCtlPos) == 0x420, "");
static_assert(sizeof(DrMdoCtlPos::unknown018) == 0x08, "");
static_assert(offsetof(DrMdoCtlPos::unknown019, unknown04) == 0x04, "");
static_assert(offsetof(DrMdoCtlPos::unknown019, unknown08) == 0x08, "");
static_assert(sizeof(DrMdoCtlPos::unknown019) == 0x0c, "");

} // namespace ml
