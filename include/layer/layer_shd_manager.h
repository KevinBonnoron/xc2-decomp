#pragma once
#include <stddef.h>

#include "grlib/cglib_sampler.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_vtx_index.h"
#include "grlib/cglib_vtx_vertex.h"
#include "mm_math/mm_mat44.h"
#include "types.h"

namespace grlib {
class CGLibDblUniformBlock;
class CGLibRenderTarget;
class CGLibVtxInstans;
class CGLibVtxOneInstans;
} // namespace grlib

namespace ml {
class IDrDrawWorkInfo;
} // namespace ml

namespace layer {
class LayerObjTopMaskObj;
class LayerResSecTexture;
class LayerTextureMan;
class LayerVertexMan;
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
  void createResWork();
  void setSecTexture(LayerResSecTexture *secTexture);

  u8 _008[0x010 - 0x008];
  const void *unknown10; // Inferred role: shader resource data; original member name unknown.
  u32 unknown18;         // Inferred role: shader resource size; original member name unknown.
  u8 _01c[0x038 - 0x01c];
  LayerVertexMan *unknown38;  // Inferred role: vertex manager; original member name unknown.
  LayerTextureMan *unknown40; // Inferred role: texture manager; original member name unknown.
  u8 _048[0x050 - 0x048];
  const LayerObjTopMaskObj *unknown50;    // Inferred role: mask object; original member name unknown.
  grlib::CGLibTextureBuffer *unknown58;   // Inferred role: second texture; original member name unknown.
  grlib::CGLibDblUniformBlock *unknown60; // Inferred role: second texture uniform; original member name unknown.
  u8 _068[0x0c0 - 0x068];
  grlib::CGLibSampler unknownc0[11]; // Inferred role: samplers; original member name unknown.
  u8 _220[0x238 - 0x220];
  grlib::CGLibVtxVertex unknown238[5];     // Inferred role: vertices; original member name unknown.
  grlib::CGLibVtxIndex unknown300;         // Inferred role: quads index; original member name unknown.
  grlib::CGLibVtxIndex unknown328;         // Inferred role: line quads index; original member name unknown.
  grlib::CGLibDblUniformBlock *unknown350; // Inferred role: 3d space uniform; original member name unknown.
  grlib::CGLibDblUniformBlock *unknown358; // Inferred role: view port uniform; original member name unknown.
  grlib::CGLibRenderTarget *unknown360;    // Inferred role: def render target; original member name unknown.
  grlib::CGLibTextureBuffer unknown368;    // Inferred role: resource texture; original member name unknown.
  u8 _3d8[0x4a0 - 0x3d8];
  mm::Mat44 unknown4a0; // Inferred role: view projection matrix; original member name unknown.
  u8 _4e0[0x4f4 - 0x4e0];
  s16 unknown4f4; // Inferred role: depth mode; original member name unknown.
  u8 _4f6[0x4fa - 0x4f6];
  s16 unknown4fa; // Inferred role: mask mode; original member name unknown.
  s16 unknown4fc; // Inferred role: second texture mode; original member name unknown.
  u8 _4fe[0x529 - 0x4fe];
  bool unknown529; // Inferred role: depth check; original member name unknown.
  u8 _52a[0x530 - 0x52a];
  f32 unknown530; // Inferred role: screen width; original member name unknown.
  f32 unknown534; // Inferred role: screen height; original member name unknown.
  f32 unknown538; // Inferred role: screen div width; original member name unknown.
  f32 unknown53c; // Inferred role: screen div height; original member name unknown.
  f32 unknown540; // Inferred role: screen calc pos width; original member name unknown.
  f32 unknown544; // Inferred role: screen calc pos height; original member name unknown.
  f32 unknown548; // Inferred role: screen calc scl width; original member name unknown.
  f32 unknown54c; // Inferred role: screen calc scl height; original member name unknown.
  f32 unknown550; // Inferred role: screen org width; original member name unknown.
  f32 unknown554; // Inferred role: screen org height; original member name unknown.
  u8 _558[0x574 - 0x558];
  f32 unknown574; // Inferred role: screen ratio height; original member name unknown.
  f32 unknown578; // Inferred role: gamma; original member name unknown.
};

static_assert(offsetof(LayerShdManager, unknown10) == 0x010, "");
static_assert(offsetof(LayerShdManager, unknown18) == 0x018, "");
static_assert(offsetof(LayerShdManager, unknown38) == 0x038, "");
static_assert(offsetof(LayerShdManager, unknown40) == 0x040, "");
static_assert(offsetof(LayerShdManager, unknown50) == 0x050, "");
static_assert(offsetof(LayerShdManager, unknown58) == 0x058, "");
static_assert(offsetof(LayerShdManager, unknown60) == 0x060, "");
static_assert(offsetof(LayerShdManager, unknownc0) == 0x0c0, "");
static_assert(offsetof(LayerShdManager, unknown238) == 0x238, "");
static_assert(offsetof(LayerShdManager, unknown300) == 0x300, "");
static_assert(offsetof(LayerShdManager, unknown328) == 0x328, "");
static_assert(offsetof(LayerShdManager, unknown350) == 0x350, "");
static_assert(offsetof(LayerShdManager, unknown360) == 0x360, "");
static_assert(offsetof(LayerShdManager, unknown368) == 0x368, "");
static_assert(offsetof(LayerShdManager, unknown4a0) == 0x4a0, "");
static_assert(offsetof(LayerShdManager, unknown4f4) == 0x4f4, "");
static_assert(offsetof(LayerShdManager, unknown4fa) == 0x4fa, "");
static_assert(offsetof(LayerShdManager, unknown4fc) == 0x4fc, "");
static_assert(offsetof(LayerShdManager, unknown529) == 0x529, "");
static_assert(offsetof(LayerShdManager, unknown530) == 0x530, "");
static_assert(offsetof(LayerShdManager, unknown550) == 0x550, "");
static_assert(offsetof(LayerShdManager, unknown578) == 0x578, "");

} // namespace layer
