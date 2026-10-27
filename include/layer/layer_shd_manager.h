#pragma once
#include <stddef.h>

#include "grlib/cglib_sampler.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_vtx_fetch.h"
#include "grlib/cglib_vtx_index.h"
#include "grlib/cglib_vtx_vertex.h"
#include "ml/work_event.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_rect.h"
#include "types.h"

namespace grlib {
class CGLibDblUniformBlock;
class CGLibDecShader;
class CGLibRenderTarget;
class CGLibVtxInstans;
class CGLibVtxOneInstans;
} // namespace grlib

namespace ml {
class FileHandleTh;
class IDrDrawWorkInfo;
} // namespace ml

namespace layer {
class LayerManager;
class LayerObjTopMaskObj;
struct LayerResViewPortInfo;
class LayerResSecTexture;
class LayerTextureMan;
class LayerVertexMan;
class LayerVertexObj;

enum LayerSamplerType {};
enum LayerDefVertType {};

class LayerShdManager : public ml::IWorkEvent {
public:
  // Inferred layout of the declaration offsets of one shader; original type and member names unknown.
  struct unknown001 {
    u16 unknown00; // Inferred role: offset of MENU_GAUGE_TYPE; original member name unknown.
    u16 unknown02; // Inferred role: offset of MENU_WORLD_TYPE; original member name unknown.
    u16 unknown04; // Inferred role: offset of MENU_ICON_TYPE; original member name unknown.
    u16 unknown06; // Inferred role: offset of MENU_USE_TEX, MENU_DECODE_TYPE or MENU_FILBLEND_TYPE; original member name unknown.
    u16 unknown08; // Inferred role: offset of MENU_MASKOBJ_TYPE; original member name unknown.
    u16 unknown0a; // Inferred role: offset of MENU_SECTEX_TYPE; original member name unknown.
  };

  LayerShdManager(LayerManager *manager);
  virtual ~LayerShdManager();
  bool OnFileEvent(ml::EventFileTh *event) override;
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
  void setupShader();
  void setupShader(grlib::CGLibDblUniformBlock *uniform);
  void setShaderMaskMode(const LayerObjTopMaskObj *mask);
  void setViewPort(LayerResViewPortInfo *viewPort);
  grlib::CGLibDecShader *selectGamma();
  grlib::CGLibDecShader *selectFlowMap();
  grlib::CGLibDecShader *selectGsBlur();
  grlib::CGLibDecShader *selectTest();
  grlib::CGLibDecShader *selectMemWrite();
  grlib::CGLibDecShader *selectDebug();
  grlib::CGLibDecShader *selectFont();
  grlib::CGLibDecShader *selectNumber();
  grlib::CGLibDecShader *selectPoly();
  grlib::CGLibDecShader *selectWin();
  grlib::CGLibDecShader *selectIcon();
  grlib::CGLibDecShader *selectColor();
  grlib::CGLibDecShader *selectTex();

  static grlib::CGLibDecShader *(LayerShdManager::*s_CallSelect[])();
  static const u32 s_eFetchTbl[];
  static void (*s_CallBlend[])();
  void initColor(u32 index);
  void initTex(u32 index);
  void initFont(u32 index);
  void initWin(u32 index);
  void initNumber(u32 index);
  void initPoly(u32 index);
  void initMemWrite(u32 index);
  void initDebug(u32 index);
  void initGsBlur(u32 index);
  void initTest(u32 index);
  void resetViewPort();

  void *unknown08;       // Inferred role: shader binary data; original member name unknown.
  const void *unknown10; // Inferred role: shader resource data; original member name unknown.
  u32 unknown18;         // Inferred role: shader resource size; original member name unknown.
  u8 _01c[0x028 - 0x01c];
  ml::FileHandleTh *unknown28;            // Inferred role: pending shader binary file; original member name unknown.
  ml::FileHandleTh *unknown30;            // Inferred role: pending shader resource file; original member name unknown.
  LayerVertexMan *unknown38;              // Inferred role: vertex manager; original member name unknown.
  LayerTextureMan *unknown40;             // Inferred role: texture manager; original member name unknown.
  unknown001 *unknown48;                  // Inferred role: declaration offsets per shader; original member name unknown.
  const LayerObjTopMaskObj *unknown50;    // Inferred role: mask object; original member name unknown.
  grlib::CGLibTextureBuffer *unknown58;   // Inferred role: second texture; original member name unknown.
  grlib::CGLibDblUniformBlock *unknown60; // Inferred role: second texture uniform; original member name unknown.
  u8 _068[0x070 - 0x068];
  grlib::CGLibVtxFetch unknown70[5];
  grlib::CGLibSampler unknownc0[11]; // Inferred role: samplers; original member name unknown.
  grlib::CGLibDecShader *unknown220; // Inferred role: shaders; original member name unknown.
  u8 _228[0x238 - 0x228];
  grlib::CGLibVtxVertex unknown238[5];     // Inferred role: vertices; original member name unknown.
  grlib::CGLibVtxIndex unknown300;         // Inferred role: quads index; original member name unknown.
  grlib::CGLibVtxIndex unknown328;         // Inferred role: line quads index; original member name unknown.
  grlib::CGLibDblUniformBlock *unknown350; // Inferred role: 3d space uniform; original member name unknown.
  grlib::CGLibDblUniformBlock *unknown358; // Inferred role: view port uniform; original member name unknown.
  grlib::CGLibRenderTarget *unknown360;    // Inferred role: def render target; original member name unknown.
  grlib::CGLibTextureBuffer unknown368;    // Inferred role: resource texture; original member name unknown.
  u8 _3d8[0x4a0 - 0x3d8];
  mm::Mat44 unknown4a0; // Inferred role: view projection matrix; original member name unknown.
  u8 _4e0[0x4f0 - 0x4e0];
  s16 unknown4f0;           // Inferred role: shader index; original member name unknown.
  s16 unknown4f2;           // Inferred role: shader parameter; original member name unknown.
  s16 unknown4f4;           // Inferred role: depth mode; original member name unknown.
  s16 unknown4f6;           // Inferred role: shader parameter; original member name unknown.
  s16 unknown4f8;           // Inferred role: shader parameter; original member name unknown.
  s16 unknown4fa;           // Inferred role: mask mode; original member name unknown.
  s16 unknown4fc;           // Inferred role: second texture mode; original member name unknown.
  s16 unknown4fe;           // Inferred role: selected shader index; original member name unknown.
  s16 unknown500;           // Inferred role: selected shader parameter; original member name unknown.
  s16 unknown502;           // Inferred role: selected depth mode; original member name unknown.
  s16 unknown504;           // Inferred role: selected shader parameter; original member name unknown.
  s16 unknown506;           // Inferred role: selected shader parameter; original member name unknown.
  s16 unknown508;           // Inferred role: selected mask mode; original member name unknown.
  s16 unknown50a;           // Inferred role: selected second texture mode; original member name unknown.
  mm::Rect<f32> unknown50c; // Inferred role: view port; original member name unknown.
  u8 _51c[0x528 - 0x51c];
  bool unknown528; // Inferred role: view port changed; original member name unknown.
  bool unknown529; // Inferred role: depth check; original member name unknown.
  bool unknown52a; // Inferred role: render target view port; original member name unknown.
  u8 _52b[0x52c - 0x52b];
  u32 unknown52c; // Inferred role: current blend type; original member name unknown.
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
  f32 unknown558; // Inferred role: screen scale; original member name unknown.
  f32 unknown55c; // Inferred role: screen scale width; original member name unknown.
  f32 unknown560; // Inferred role: screen scale height; original member name unknown.
  u8 _564[0x574 - 0x564];
  f32 unknown574; // Inferred role: screen ratio height; original member name unknown.
  f32 unknown578; // Inferred role: gamma; original member name unknown.
};

static_assert(offsetof(LayerShdManager, unknown08) == 0x008, "");
static_assert(offsetof(LayerShdManager, unknown10) == 0x010, "");
static_assert(offsetof(LayerShdManager, unknown28) == 0x028, "");
static_assert(offsetof(LayerShdManager, unknown30) == 0x030, "");
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
static_assert(offsetof(LayerShdManager, unknown50c) == 0x50c, "");
static_assert(offsetof(LayerShdManager, unknown528) == 0x528, "");
static_assert(offsetof(LayerShdManager, unknown529) == 0x529, "");
static_assert(offsetof(LayerShdManager, unknown52a) == 0x52a, "");
static_assert(offsetof(LayerShdManager, unknown558) == 0x558, "");
static_assert(offsetof(LayerShdManager, unknown55c) == 0x55c, "");
static_assert(offsetof(LayerShdManager, unknown52c) == 0x52c, "");
static_assert(offsetof(LayerShdManager, unknown530) == 0x530, "");
static_assert(offsetof(LayerShdManager, unknown550) == 0x550, "");
static_assert(offsetof(LayerShdManager, unknown578) == 0x578, "");

} // namespace layer
