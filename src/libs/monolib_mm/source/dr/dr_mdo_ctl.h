#pragma once
#include <stddef.h>

#include "dr/dr_mdo_setup.h"
#include "types.h"

namespace mm {
struct Mat44;
struct Vec3;
} // namespace mm

namespace grlib {
class CGLibVtxInstans;
} // namespace grlib

namespace ml {

class MdoWrkMatRes;
class DrMdoCtlMpfWork;
class DrResChkList;
class DrResMdoAlpTbl;
class DrResMdoMat;
class DrResMdoPos;
struct MdsMatInfoHeader;
struct MdsMatShaderTbl;
struct MdsMdlInfoHeader;
struct MdsMdlTopHeader;

// Inferred role: render pass id of each render type, shared by the DrMdoCtl subclasses of the unit; original name unknown.
static const u16 unknown098[] = {0, 7, 8, 4, 1, 1};

// Name from the game symbol _ZN2ml8DrMdoCtl22partsInstanceDefRenderERKNS_18MdoInstanceDrawArgE. Size: DrMdoCtlPos::callPosRender (0x71008172bc) fills
// 0x30 bytes of it on the stack; the members are the ones partsInstanceDefRender (0x71007f1ed4) reads. It draws consecutive ranges of the instances
// that start at unknown08: unknown14 instances (0x71007f2248, 0x71007f2904), unknown10 - unknown18 then unknown18 - unknown1c instances when
// unknown18 is not 0 (0x71007f22ac, 0x71007f230c) and the last unknown1c instances (0x71007f2c58). The roles below are inferred from these reads.
struct MdoInstanceDrawArg {
  const MdsMdlInfoHeader *unknown00; // Inferred role: mdl info of the draw; original member name unknown.
  s32 unknown08;                     // Inferred role: vertex offset of the instances; original member name unknown.
  s32 unknown0c;                     // Inferred role: vertex stride of the instances; original member name unknown.
  s32 unknown10;                     // Inferred role: instance count of the draw; original member name unknown.
  s32 unknown14;                     // Inferred role: instance count of the leading range, drawn from the first instance; original member name unknown.
  s32 unknown18;                     // Inferred role: instance count of the ranges after the leading unknown10 - unknown18 ones; original member name unknown.
  s32 unknown1c;                     // Inferred role: instance count of the last range, drawn with a setup material of its own; original member name unknown.
  s32 unknown20;                     // Inferred role: etc uniform index offset; original member name unknown.
  s32 unknown24;                     // Inferred role: etc uniform index of the node animation; original member name unknown.
  s32 unknown28;                     // Inferred role: depth stencil mode; original member name unknown.
  s32 unknown2c;                     // Inferred role: storage buffer index; original member name unknown.
};

static_assert(offsetof(MdoInstanceDrawArg, unknown08) == 0x08, "");
static_assert(offsetof(MdoInstanceDrawArg, unknown10) == 0x10, "");
static_assert(offsetof(MdoInstanceDrawArg, unknown14) == 0x14, "");
static_assert(offsetof(MdoInstanceDrawArg, unknown1c) == 0x1c, "");
static_assert(offsetof(MdoInstanceDrawArg, unknown20) == 0x20, "");
static_assert(offsetof(MdoInstanceDrawArg, unknown28) == 0x28, "");
static_assert(offsetof(MdoInstanceDrawArg, unknown2c) == 0x2c, "");
static_assert(sizeof(MdoInstanceDrawArg) == 0x30, "");

// Name from the game symbol _ZN2ml8DrMdoCtl27partsInstanceZPrepassRenderERKNS_21MdoInstancePrePassArgE. Size: DrMdoCtlSeamInstMap::createInstZPrePassDisplayList (0x710081d8c4) fills 0x28 bytes of it
// on the stack; the members are the ones partsInstanceZPrepassRender (0x71007f2fd4) reads. It draws consecutive ranges of the instances that start at unknown08: unknown10 instances,
// unknown14 - unknown18 instances, then the last unknown18 instances (drawn with the depth stencil of setupPartsMaterial mode 3). The roles below are inferred from these reads.
struct MdoInstancePrePassArg {
  const MdsMdlInfoHeader *unknown00; // Inferred role: mdl info of the draw; original member name unknown.
  s32 unknown08;                     // Inferred role: vertex offset of the instances; original member name unknown.
  s32 unknown0c;                     // Inferred role: vertex stride of the instances; original member name unknown.
  s32 unknown10;                     // Inferred role: instance count of the leading range; original member name unknown.
  s32 unknown14;                     // Inferred role: instance count of the second and last ranges together; original member name unknown.
  s32 unknown18;                     // Inferred role: instance count of the last range, drawn with a setup material of its own; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  u8 unknown20; // Inferred role: sets up the depth stencil of the draw; original member name unknown.
  u8 unknown21; // Inferred role: first thickness pass, read by partsInstanceThicknessRender (0x71007f3a14); original member name unknown.
};

static_assert(offsetof(MdoInstancePrePassArg, unknown08) == 0x08, "");
static_assert(offsetof(MdoInstancePrePassArg, unknown10) == 0x10, "");
static_assert(offsetof(MdoInstancePrePassArg, unknown14) == 0x14, "");
static_assert(offsetof(MdoInstancePrePassArg, unknown18) == 0x18, "");
static_assert(offsetof(MdoInstancePrePassArg, unknown20) == 0x20, "");
static_assert(offsetof(MdoInstancePrePassArg, unknown21) == 0x21, "");
static_assert(sizeof(MdoInstancePrePassArg) == 0x28, "");

class DrMdoCtl : public DrMdoSetup {
public:
  DrMdoCtl(int viewNum);
  void bindShader(int index);
  u32 getShdIdx(u32 &uniformIndex, const MdsMatShaderTbl *table, int count);
  void beginSetup();
  void beginSeamSetup();
  void changeSeamBaseMapMdlInfo();
  DrResChkList *stockRenderList(DrResChkList *&head, DrResChkList *prev, u32 mdlIndex);
  void updateMdl();
  void partsBaseMdlRender(const MdsMdlInfoHeader *header);
  void partsMaterialSetup(const MdsMdlInfoHeader *header);
  void partsDefRender(const MdsMdlInfoHeader *header, int shaderParam0, int shaderParam1, bool isDepthStencil);
  void setMatrix(const mm::Mat44 &matrix);
  void setOffsetPos(const mm::Vec3 &position);
  const mm::Mat44 &getMatrix() const;
  void partsInstanceThicknessBillRender(const MdoInstancePrePassArg &arg);
  void createMaterialDisplaList(const MdsMatInfoHeader *header, DrResMdoMat *mat);
  void createMaterialDisplayList(u8 **table, int count, MdoWrkMatRes *matRes);
  void createMaterialOneDisplayList(MdoWrkMatRes *matRes, int index);
  void createMaterialLgtPrePassDisplaList(const MdsMatInfoHeader *header, DrResMdoMat *mat);
  void createInstBillMate(const MdsMatInfoHeader *header, int index);
  void createInstBillPrepass(const MdsMatInfoHeader *header, int index);
  void createBaseBillMate(const MdsMatInfoHeader *header, int index);
  void createBaseBillPrepass(const MdsMatInfoHeader *header, int index);
  void createOccMate(const MdsMatInfoHeader *header, int index);
  void createNodeAnm(const MdsMatInfoHeader *header, int index);
  void createInstanceDefRender(const MdsMdlInfoHeader *header, grlib::CGLibVtxInstans *instans, u32 offset, u32 stride, u32 instanceCount);
  void partsInstanceDefRender(const MdoInstanceDrawArg &arg);
  void partsZPrePassRender(const MdsMdlInfoHeader *header, int shaderParam0, int shaderParam1, DrResMdoAlpTbl *alpTbl, u32 alpIndex);
  void partsShadowRender(const MdsMdlInfoHeader *header, int shaderParam0, int shaderParam1, int shaderParam2);
  void partsShadowBaseRender(const MdsMdlTopHeader *top);
  void partsShadowNukiBaseRender(const MdsMdlTopHeader *top);
  void partsPosShadowRender(const MdsMdlTopHeader *top);
  void partsPosNukiShadowRender(const MdsMdlTopHeader *top);
  void partsPosNoamShadowRender(const MdsMdlTopHeader *top, grlib::CGLibVtxInstans *instans, u32 offset, u32 stride, u32 instanceCount);
  void partsInstanceZPrepassRender(const MdoInstancePrePassArg &arg);
  void partsInstanceZPrepassBillRender(const MdoInstancePrePassArg &arg);
  void partsInstanceThicknessRender(const MdoInstancePrePassArg &arg);
  void createInstanceOccBuff(const MdsMdlTopHeader *top, int count, DrResMdoPos *pos0, DrResMdoPos *pos1);
  void mpfZPrePassRender(int index, const MdsMdlInfoHeader *header, DrMdoCtlMpfWork *work, grlib::CGLibVtxInstans *instans);
  void mpfDrawRender(int index, const MdsMdlInfoHeader *header, DrMdoCtlMpfWork *work, grlib::CGLibVtxInstans *instans);
  void partsShadowDirRender(const MdsMdlInfoHeader *header, int shaderParam0, int shaderParam1);
  void partsThicknessRender(const MdsMdlInfoHeader *header, int shaderParam0, int shaderParam1, DrResMdoAlpTbl *alpTbl, u32 alpIndex, bool isFirst);
  void createWeightVtx(int renderType, u32 alphaFlags, u32 lodFlags, bool isPrePass);
  void setFrameSpd(f32 speed) { unknowndc = speed; }
  // Inferred role: selects the shader extension table of a technique, the lookup repeated by the shader and uniform block functions; original name unknown.
  void unknown004(int index);
  // Inferred role: renders a mdl info with its render index or its mesh parts render index, repeated by the shadow render functions; original name unknown.
  void unknown005(const MdsMdlInfoHeader *info);
  static void waitWeightVtx();
  static void waitBeginWeightVtx();

  // Inferred role: render list per mdl and render type, a flat table of 8 types per mdl: DrMdoCtlMpf::defMpfZPreRender addresses it with a 32-bit i * 8 (0x71007faa5c);
  // original member name unknown.
  DrResChkList **unknown190;
  DrResChkList *unknown198; // Inferred role: render list entries; original member name unknown.
  s32 unknown1a0;           // Inferred role: render list entry count; original member name unknown.
};

static_assert(offsetof(DrMdoCtl, unknown190) == 0x190, "");
static_assert(offsetof(DrMdoCtl, unknown198) == 0x198, "");
static_assert(offsetof(DrMdoCtl, unknown1a0) == 0x1a0, "");
static_assert(sizeof(DrMdoCtl) == 0x1b0, "");

} // namespace ml
