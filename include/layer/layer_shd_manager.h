#pragma once
#include <stddef.h>

#include "grlib/cglib_sampler.h"
#include "grlib/cglib_vtx_index.h"
#include "grlib/cglib_vtx_vertex.h"
#include "mm_math/mm_mat44.h"
#include "types.h"

namespace grlib {
class CGLibDblUniformBlock;
class CGLibRenderTarget;
class CGLibTextureBuffer;
class CGLibVtxInstans;
class CGLibVtxOneInstans;
} // namespace grlib

namespace ml {
class IDrDrawWorkInfo;
} // namespace ml

namespace layer {
class LayerObjTopMaskObj;
class LayerVertexObj;

enum LayerSamplerType {};
enum LayerDefVertType {};

class LayerShdManager {
public:
  virtual ~LayerShdManager();
  void allRelease();
  void shaderRelease();
  void readShader();
  bool setupUpdate();
  void beginShader(const ml::IDrDrawWorkInfo *info);
  void endShader(const ml::IDrDrawWorkInfo *info);
  void setupMainRenderTarget();
  void setShaderMaskOff();
  void setDepthBufferCheckOn();
  void setDepthBufferCheckOff();
  void set3DSpaceMode(grlib::CGLibDblUniformBlock *uniform);
  void setupTexture(const grlib::CGLibTextureBuffer &texture, LayerSamplerType type, u32 location);
  grlib::CGLibRenderTarget *getDefRenderTarget();
  void setupVertex(LayerVertexObj *vertex, u32 index);
  void setupVertex(LayerDefVertType type);
  void setupInstaceVertex(grlib::CGLibVtxInstans &instance, u32 stride, u32 offset);
  void setupInstaceVertex(grlib::CGLibVtxOneInstans &instance, u32 stride, u32 offset);
  void renderQuadsIndex();
  void renderInstaceQuadsIndex(u32 instanceCount);
  void renderLineQuadsIndex();
  void setupBlendDef();
  void setupBlendSwf();
  void setupBlendNo();
  void setupBlendAdd();
  void setupBlendAddSwf();
  void setupBlendSub();
  void setupBlendSubSwf();
  void setupBlendMul();
  void initFlowMap(u32 index);
  void initGamma(u32 index);

  u8 _008[0x050 - 0x008];
  const LayerObjTopMaskObj *m_maskObj;
  u8 _058[0x0c0 - 0x058];
  grlib::CGLibSampler m_samplers[11];
  u8 _220[0x238 - 0x220];
  grlib::CGLibVtxVertex m_vertices[5];
  grlib::CGLibVtxIndex m_quadsIndex;
  grlib::CGLibVtxIndex m_lineQuadsIndex;
  grlib::CGLibDblUniformBlock *m_3DSpaceUniform;
  grlib::CGLibDblUniformBlock *m_viewPortUniform;
  grlib::CGLibRenderTarget *m_defRenderTarget;
  u8 _368[0x4a0 - 0x368];
  mm::Mat44 m_viewProjectionMatrix;
  u8 _4e0[0x4f4 - 0x4e0];
  s16 m_depthMode;
  u8 _4f6[0x4fa - 0x4f6];
  s16 m_maskMode;
  u8 _4fc[0x529 - 0x4fc];
  bool m_isDepthCheck;
  u8 _52a[0x530 - 0x52a];
  f32 m_screenWidth;
  f32 m_screenHeight;
  f32 m_screenDivWidth;
  f32 m_screenDivHeight;
  f32 m_screenCalcPosWidth;
  f32 m_screenCalcPosHeight;
  f32 m_screenCalcSclWidth;
  f32 m_screenCalcSclHeight;
  f32 m_screenOrgWidth;
  f32 m_screenOrgHeight;
  u8 _558[0x574 - 0x558];
  f32 m_screenRatioHeight;
  f32 m_gamma;
};

static_assert(offsetof(LayerShdManager, m_maskObj) == 0x050, "");
static_assert(offsetof(LayerShdManager, m_samplers) == 0x0c0, "");
static_assert(offsetof(LayerShdManager, m_vertices) == 0x238, "");
static_assert(offsetof(LayerShdManager, m_quadsIndex) == 0x300, "");
static_assert(offsetof(LayerShdManager, m_lineQuadsIndex) == 0x328, "");
static_assert(offsetof(LayerShdManager, m_3DSpaceUniform) == 0x350, "");
static_assert(offsetof(LayerShdManager, m_defRenderTarget) == 0x360, "");
static_assert(offsetof(LayerShdManager, m_viewProjectionMatrix) == 0x4a0, "");
static_assert(offsetof(LayerShdManager, m_depthMode) == 0x4f4, "");
static_assert(offsetof(LayerShdManager, m_maskMode) == 0x4fa, "");
static_assert(offsetof(LayerShdManager, m_isDepthCheck) == 0x529, "");
static_assert(offsetof(LayerShdManager, m_screenWidth) == 0x530, "");
static_assert(offsetof(LayerShdManager, m_screenOrgWidth) == 0x550, "");
static_assert(offsetof(LayerShdManager, m_gamma) == 0x578, "");

} // namespace layer
