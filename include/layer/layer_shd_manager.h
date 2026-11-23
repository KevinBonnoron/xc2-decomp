#pragma once
#include <stddef.h>

#include "grlib/cglib_sampler.h"
#include "grlib/cglib_shd_list.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_vtx_fetch.h"
#include "grlib/cglib_vtx_index.h"
#include "grlib/cglib_vtx_vertex.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_top_mask_obj.h"
#include "layer/layer_view_port.h"
#include "ml/work_event.h"
#include "mm_math/mm_mat44.h"
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
  void createShader();
  bool setupUpdate();
  void createRenderWork();
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
  grlib::CGLibDecShader *setupShader();
  grlib::CGLibDecShader *setupShader(grlib::CGLibDblUniformBlock *uniform);
  void setShaderMaskMode(const LayerObjTopMaskObj *mask);
  void selectViewPort(const LayerViewPort &viewPort);
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

  static void (LayerShdManager::*s_CallSetup[])(u32 index);
  static grlib::CGLibDecShader *(LayerShdManager::*s_CallSelect[])();
  static const u32 s_eFetchTbl[];
  static void (*s_CallBlend[])();
  static const u32 s_resDefBlend[];
  static const u32 s_resSwfBlend[];
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

  // Inferred helper repeated by the render functions of the layer objects: sets the mask mode of a visible mask
  // object, otherwise the view port; returns false when the mask is clipped. Original name unknown.
  bool unknown002(const LayerObjTopMaskObj *mask, LayerResViewPortInfo *const &viewPort) {
    if (mask == nullptr || (mask->unknowna8 & 0x90000) != 0) {
      if (viewPort == nullptr) {
        setShaderMaskOff();
        resetViewPort();
      } else {
        setViewPort(viewPort);
      }
    } else {
      if (mask->isClip()) {
        return false;
      }
      setShaderMaskMode(mask);
    }
    return true;
  }

  // Inferred helper: calls the blend setup of a blend type when it changes; original name unknown.
  void unknown003(u32 blend) {
    if (unknown52c != blend) {
      s_CallBlend[blend]();
      unknown52c = blend;
    }
  }

  // Inferred helper: selects the depth mode from the flags of a layer object; original name unknown.
  void unknown004(const LayerObj *layer) {
    if (!(layer->unknowna8 & 0x400)) {
      setDepthBufferCheckOff();
    } else if (!(layer->unknowna8 & 0x800)) {
      setDepthBufferCheckOn();
    } else {
      set3DSpaceMode(layer->unknown238);
    }
  }

  void *unknown08; // Inferred role: shader binary data; original member name unknown.
  void *unknown10; // Inferred role: shader resource data; original member name unknown.
  u32 unknown18;   // Inferred role: shader resource size; original member name unknown.
  u8 _01c[0x020 - 0x01c];
  LayerManager *m_layerManager;                   // Inferred role: manager, the constructor argument; original member name unknown.
  ml::FileHandleTh *unknown28;                    // Inferred role: pending shader binary file; original member name unknown.
  ml::FileHandleTh *unknown30;                    // Inferred role: pending shader resource file; original member name unknown.
  LayerVertexMan *m_layerVertexMan;               // Inferred role: vertex manager; original member name unknown.
  LayerTextureMan *m_layerTextureMan;             // Inferred role: texture manager; original member name unknown.
  unknown001 *unknown48;                          // Inferred role: declaration offsets per shader; original member name unknown.
  const LayerObjTopMaskObj *m_layerObjTopMaskObj; // Inferred role: mask object; original member name unknown.
  grlib::CGLibTextureBuffer *unknown58;           // Inferred role: second texture; original member name unknown.
  grlib::CGLibDblUniformBlock *unknown60;         // Inferred role: second texture uniform; original member name unknown.
  bool unknown68;                                 // Inferred role: render work created; original member name unknown.
  u8 _069[0x070 - 0x069];
  grlib::CGLibVtxFetch unknown70[5];
  grlib::CGLibSampler unknownc0[9];           // Inferred role: samplers; original member name unknown.
  grlib::CGLibShdListData m_cGLibShdListData; // Inferred role: shaders; original member name unknown.
  grlib::CGLibVtxVertex unknown238[5];        // Inferred role: vertices; original member name unknown.
  grlib::CGLibVtxIndex unknown300;            // Inferred role: quads index; original member name unknown.
  grlib::CGLibVtxIndex unknown328;            // Inferred role: line quads index; original member name unknown.
  grlib::CGLibDblUniformBlock *unknown350;    // Inferred role: 3d space uniform; original member name unknown.
  grlib::CGLibDblUniformBlock *unknown358;    // Inferred role: view port uniform; original member name unknown.
  grlib::CGLibRenderTarget *unknown360;       // Inferred role: def render target; original member name unknown.
  grlib::CGLibTextureBuffer unknown368;       // Inferred role: resource texture; original member name unknown.
  u8 _3d8[0x4a0 - 0x3d8];
  mm::Mat44 unknown4a0; // Inferred role: view projection matrix; original member name unknown.
  u8 _4e0[0x4f0 - 0x4e0];
  s16 unknown4f0;                // Inferred role: shader index; original member name unknown.
  s16 unknown4f2;                // Inferred role: shader parameter; original member name unknown.
  s16 unknown4f4;                // Inferred role: depth mode; original member name unknown.
  s16 unknown4f6;                // Inferred role: shader parameter; original member name unknown.
  s16 unknown4f8;                // Inferred role: shader parameter; original member name unknown.
  s16 unknown4fa;                // Inferred role: mask mode; original member name unknown.
  s16 unknown4fc;                // Inferred role: second texture mode; original member name unknown.
  s16 unknown4fe;                // Inferred role: selected shader index; original member name unknown.
  s16 unknown500;                // Inferred role: selected shader parameter; original member name unknown.
  s16 unknown502;                // Inferred role: selected depth mode; original member name unknown.
  s16 unknown504;                // Inferred role: selected shader parameter; original member name unknown.
  s16 unknown506;                // Inferred role: selected shader parameter; original member name unknown.
  s16 unknown508;                // Inferred role: selected mask mode; original member name unknown.
  s16 unknown50a;                // Inferred role: selected second texture mode; original member name unknown.
  LayerViewPort m_layerViewPort; // Inferred role: view port; original member name unknown.
  u8 _51c[0x528 - 0x51c];
  bool unknown528; // Inferred role: view port changed; original member name unknown.
  bool unknown529; // Inferred role: depth check; original member name unknown.
  bool unknown52a; // Inferred role: render target view port; original member name unknown.
  u8 _52b[0x52c - 0x52b];
  u32 unknown52c;            // Inferred role: current blend type; original member name unknown.
  f32 m_screenWidth;         // Inferred role: screen width; named after the game accessor layer::LayerManager::getScreenWidth.
  f32 m_screenHeight;        // Inferred role: screen height; named after the game accessor layer::LayerManager::getScreenHeight.
  f32 m_screenDivWidth;      // Inferred role: screen div width; named after the game accessor layer::LayerManager::getScreenDivWidth.
  f32 m_screenDivHeight;     // Inferred role: screen div height; named after the game accessor layer::LayerManager::getScreenDivHeight.
  f32 m_screenCalcPosWidth;  // Inferred role: screen calc pos width; named after the game accessor layer::LayerManager::getScreenCalcPosWidth.
  f32 m_screenCalcPosHeight; // Inferred role: screen calc pos height; named after the game accessor layer::LayerManager::getScreenCalcPosHeight.
  f32 m_screenCalcSclWidth;  // Inferred role: screen calc scl width; named after the game accessor layer::LayerManager::getScreenCalcSclWidth.
  f32 m_screenCalcSclHeight; // Inferred role: screen calc scl height; named after the game accessor layer::LayerManager::getScreenCalcSclHeight.
  f32 unknown550;            // Inferred role: screen org width; original member name unknown.
  f32 unknown554;            // Inferred role: screen org height; original member name unknown.
  f32 unknown558;            // Inferred role: screen scale; original member name unknown.
  f32 unknown55c;            // Inferred role: screen scale width; original member name unknown.
  f32 unknown560;            // Inferred role: screen scale height; original member name unknown.
  u8 _564[0x574 - 0x564];
  f32 m_screenRatioHeight; // Inferred role: screen ratio height; named after the game accessor layer::LayerManager::getScreenRatioHeight.
  f32 m_gamma;             // Inferred role: gamma; named after the game accessor layer::LayerAccManager::getGamma.
};

static_assert(offsetof(LayerShdManager, unknown08) == 0x008, "");
static_assert(offsetof(LayerShdManager, unknown10) == 0x010, "");
static_assert(offsetof(LayerShdManager, unknown28) == 0x028, "");
static_assert(offsetof(LayerShdManager, unknown30) == 0x030, "");
static_assert(offsetof(LayerShdManager, unknown18) == 0x018, "");
static_assert(offsetof(LayerShdManager, m_layerVertexMan) == 0x038, "");
static_assert(offsetof(LayerShdManager, m_layerTextureMan) == 0x040, "");
static_assert(offsetof(LayerShdManager, m_layerObjTopMaskObj) == 0x050, "");
static_assert(offsetof(LayerShdManager, unknown58) == 0x058, "");
static_assert(offsetof(LayerShdManager, unknown60) == 0x060, "");
static_assert(offsetof(LayerShdManager, unknownc0) == 0x0c0, "");
static_assert(offsetof(LayerShdManager, m_cGLibShdListData) == 0x1e0, "");
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
static_assert(offsetof(LayerShdManager, m_layerViewPort) == 0x50c, "");
static_assert(offsetof(LayerShdManager, unknown528) == 0x528, "");
static_assert(offsetof(LayerShdManager, unknown529) == 0x529, "");
static_assert(offsetof(LayerShdManager, unknown52a) == 0x52a, "");
static_assert(offsetof(LayerShdManager, unknown558) == 0x558, "");
static_assert(offsetof(LayerShdManager, unknown55c) == 0x55c, "");
static_assert(offsetof(LayerShdManager, unknown52c) == 0x52c, "");
static_assert(offsetof(LayerShdManager, m_screenWidth) == 0x530, "");
static_assert(offsetof(LayerShdManager, unknown550) == 0x550, "");
static_assert(offsetof(LayerShdManager, m_gamma) == 0x578, "");

} // namespace layer
