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
struct MdoInstancePrePassArg;
struct MdsMatInfoHeader;
struct MdsMatShaderTbl;
struct MdsMdlInfoHeader;
struct MdsMdlTopHeader;

// Inferred role: render pass id of each render type, shared by the DrMdoCtl subclasses of the unit; original name unknown.
static const u16 unknown098[] = {0, 7, 8, 4, 1, 1};

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

  DrResChkList *(*unknown190)[8]; // Inferred role: render list per mdl and render type; original member name unknown.
  DrResChkList *unknown198;       // Inferred role: render list entries; original member name unknown.
  s32 unknown1a0;                 // Inferred role: render list entry count; original member name unknown.
};

static_assert(offsetof(DrMdoCtl, unknown190) == 0x190, "");
static_assert(offsetof(DrMdoCtl, unknown198) == 0x198, "");
static_assert(offsetof(DrMdoCtl, unknown1a0) == 0x1a0, "");
static_assert(sizeof(DrMdoCtl) == 0x1b0, "");

} // namespace ml
