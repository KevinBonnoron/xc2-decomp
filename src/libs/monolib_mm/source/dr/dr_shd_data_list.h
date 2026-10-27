#pragma once
#include <stddef.h>

#include "dr/dr_res_fetch.h"
#include "dr/dr_shd_data_obj.h"
#include "grlib/cglib_uniform_array.h"
#include "grlib/cglib_vtx_index.h"
#include "grlib/cglib_vtx_stm_out.h"
#include "grlib/cglib_vtx_vertex.h"
#include "types.h"

namespace grlib {
class CGLibOneUniformBlock;
} // namespace grlib

namespace ml {
class DrMan;
class DrResShdMpf;
class DrResShdObjMot;
class DrResShdPrePass;
class DrResShdShw;
class DrResShdStreamOut;

class DrShdDataList {
public:
  void createShader();
  void reloadShader(int type);
  DrShdDataObj *getDebugShdObj(int index);
  DrShdDataObj *getSelectShdObj(int index);

  // Inferred role: binds the quad vertices and sets the shader up; original name unknown.
  void unknown002(DrShdDataObj *shader) {
    bindQuadsTex();
    shader->setupShader(0u);
  }

  // Inferred role: select shader for a single render target quad; original name unknown.
  DrShdDataObj *unknown001() {
    DrShdDataObj *shader = getSelectShdObj(1);
    shader->setDeclarationIdx(shader->getDeclarationOfs("PIXL_TYPE"), 1);
    shader->setDeclarationIdx(shader->getDeclarationOfs("MRT_NUM"), 1);
    return shader;
  }

  DrShdDataObj *getShadowShdObj(int index);
  DrShdDataObj *getPostShdObj(int index);
  DrShdDataObj *getSteamShdObj(int index);
  DrShdDataObj *getMpfShdObj(int index);
  DrShdDataObj *getPreShdObj(int index);
  DrShdDataObj *getComputeObj(int index);
  DrShdDataObj *getCateShdObj(int category, int index);
  DrResShdMpf *getMpfObj(int index);
  DrResShdPrePass *getPrePassObj(int index);
  DrResShdShw *getShwObj(int index);
  DrResShdStreamOut *getStmOutObj(int index);
  DrResShdObjMot *getObjMotBlurObj(int index);
  void bindShdVertex();
  void bindShdSphereVertex();
  void bindShdSpotVertex();
  void bindQuadsTex();
  void bindTriangle();
  void bindTriangleTex();
  void bindShdBoxVertex();
  void bindShdCylinderVertex();
  void bindShdRainDropVertex();
  void bindShdEffVtx();
  void bindShdDepthCheck();
  void bindPlaneVertex();
  void renderQuads();
  void renderInstQuads(int instanceCount);
  void renderTriangle();
  void renderSphere();
  void renderSpotMdl();
  void renderBox();
  void renderCylinder();
  void renderRainDrop();
  void renderEffVtx(int instanceCount);
  void renderPoint(int count);
  void renderPoint(int count, int instanceCount);
  DrResFetch *getFetchShader(int index);
  DrResFetch *getSubFetchShader(int index);
  grlib::CGLibOneUniformBlock *getAlphaTestUniform(f32 alphaRef);

  static u8 s_etcNextVertex[];

  u8 _000[0x008 - 0x000];
  DrMan *unknown08; // Inferred role: dr man; original member name unknown.
  u8 _010[0x018 - 0x010];
  DrShdDataObj *unknown18[10]; // Inferred role: shd objs; original member name unknown.
  DrResFetch unknown68[91];    // Inferred role: fetches; original member name unknown.
  u8 _618[0x620 - 0x618];
  DrResShdMpf *unknown620;                                          // Inferred role: mpf objs; original member name unknown.
  DrResShdPrePass *unknown628;                                      // Inferred role: pre pass objs; original member name unknown.
  DrResShdShw *unknown630;                                          // Inferred role: shw objs; original member name unknown.
  grlib::CGLibVtxVertex unknown638;                                 // Inferred role: shd vertex; original member name unknown.
  grlib::CGLibVtxVertex unknown660;                                 // Inferred role: quads tex vertex; original member name unknown.
  grlib::CGLibVtxVertex unknown688;                                 // Inferred role: triangle vertex; original member name unknown.
  grlib::CGLibVtxVertex unknown6b0;                                 // Inferred role: triangle tex vertex; original member name unknown.
  grlib::CGLibVtxVertex unknown6d8;                                 // Inferred role: box vertex; original member name unknown.
  grlib::CGLibVtxVertex unknown700;                                 // Inferred role: sphere vertex; original member name unknown.
  grlib::CGLibVtxVertex unknown728;                                 // Inferred role: cylinder vertex; original member name unknown.
  grlib::CGLibVtxVertex unknown750;                                 // Inferred role: spot vertex; original member name unknown.
  grlib::CGLibVtxVertex unknown778;                                 // Inferred role: rain drop vertex; original member name unknown.
  grlib::CGLibVtxVertex unknown7a0;                                 // Inferred role: eff vertex; original member name unknown.
  grlib::CGLibVtxVertex unknown7c8;                                 // Inferred role: depth check vertex; original member name unknown.
  grlib::CGLibVtxVertex unknown7f0;                                 // Inferred role: plane vertex; original member name unknown.
  grlib::CGLibVtxIndex unknown818;                                  // Inferred role: quads index; original member name unknown.
  grlib::CGLibVtxIndex unknown840;                                  // Inferred role: triangle index; original member name unknown.
  grlib::CGLibVtxIndex unknown868;                                  // Inferred role: box index; original member name unknown.
  grlib::CGLibVtxIndex unknown890;                                  // Inferred role: sphere index; original member name unknown.
  grlib::CGLibVtxIndex unknown8b8;                                  // Inferred role: cylinder index; original member name unknown.
  grlib::CGLibVtxIndex unknown8e0;                                  // Inferred role: spot index; original member name unknown.
  grlib::CGLibVtxIndex unknown908;                                  // Inferred role: rain drop index; original member name unknown.
  grlib::CGLibVtxIndex unknown930;                                  // Inferred role: eff index; original member name unknown.
  grlib::CGLibVtxStmOut unknown958[2];                              // Inferred role: stm outs; original member name unknown.
  grlib::CGLibUniformArray<grlib::CGLibOneUniformBlock> unknown9a8; // Inferred role: alpha test uniforms; original member name unknown.
  u8 _9b0[0x9d0 - 0x9b0];
  DrResShdStreamOut *unknown9d0; // Inferred role: stm out objs; original member name unknown.
  DrResShdObjMot *unknown9d8;    // Inferred role: object mot blur objs; original member name unknown.
};

static_assert(offsetof(DrShdDataList, unknown08) == 0x008, "");
static_assert(offsetof(DrShdDataList, unknown18) == 0x018, "");
static_assert(offsetof(DrShdDataList, unknown68) == 0x068, "");
static_assert(offsetof(DrShdDataList, unknown620) == 0x620, "");
static_assert(offsetof(DrShdDataList, unknown638) == 0x638, "");
static_assert(offsetof(DrShdDataList, unknown818) == 0x818, "");
static_assert(offsetof(DrShdDataList, unknown958) == 0x958, "");
static_assert(offsetof(DrShdDataList, unknown9a8) == 0x9a8, "");
static_assert(offsetof(DrShdDataList, unknown9d0) == 0x9d0, "");
static_assert(offsetof(DrShdDataList, unknown9d8) == 0x9d8, "");

} // namespace ml
