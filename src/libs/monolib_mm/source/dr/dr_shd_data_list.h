#pragma once
#include <stddef.h>

#include "dr/dr_res_fetch.h"
#include "dr/dr_shd_data_obj.h"
#include "grlib/cglib_shd_list.h"
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
class FileResTh;
class DrResShdMpf;
class DrResShdObjMot;
class DrResShdPrePass;
class DrResShdShw;
class DrResShdStreamOut;

class DrShdDataList {
public:
  DrShdDataList(DrMan *drMan);
  ~DrShdDataList();
  void createWork();
  void createShader();
  void createAlphaTestBlock();
  void releaseShader();
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

  FileResTh *unknown00;                              // Inferred role: shader file resource; original member name unknown.
  DrMan *unknown08;                                  // Inferred role: dr man; original member name unknown.
  void *unknown10;                                   // Inferred role: shader object work memory; original member name unknown.
  DrShdDataObj *unknown18[10];                       // Inferred role: shd objs; original member name unknown.
  DrResFetch unknown68[91];                          // Inferred role: fetches; original member name unknown.
  grlib::CGLibShdListBase<DrShdDataObj> *unknown618; // Inferred role: shader list; original member name unknown.
  DrResShdMpf *unknown620;                           // Inferred role: mpf objs; original member name unknown.
  DrResShdPrePass *unknown628;                       // Inferred role: pre pass objs; original member name unknown.
  DrResShdShw *unknown630;                           // Inferred role: shw objs; original member name unknown.
  // Evidence for the arrays: ~DrShdDataList releases each vertex and index and destroys them with addresses recomputed
  // per element (array destruction), while the two stream outputs are constructed, created and destroyed one by one.
  grlib::CGLibVtxVertex
      unknown638[12]; // Inferred role: vertices (shd, quads tex, triangle, triangle tex, box, sphere, cylinder, spot, rain drop, eff, depth check, plane); original member name unknown.
  grlib::CGLibVtxIndex unknown818[8];                               // Inferred role: indices (quads, triangle, box, sphere, cylinder, spot, rain drop, eff); original member name unknown.
  grlib::CGLibVtxStmOut unknown958;                                 // Inferred role: stm out; original member name unknown.
  grlib::CGLibVtxStmOut unknown980;                                 // Inferred role: stm out; original member name unknown.
  grlib::CGLibUniformArray<grlib::CGLibOneUniformBlock> unknown9a8; // Inferred role: alpha test uniforms; original member name unknown.
  DrResShdStreamOut *unknown9d0;                                    // Inferred role: stm out objs; original member name unknown.
  DrResShdObjMot *unknown9d8;                                       // Inferred role: object mot blur objs; original member name unknown.
};

static_assert(offsetof(DrShdDataList, unknown08) == 0x008, "");
static_assert(offsetof(DrShdDataList, unknown18) == 0x018, "");
static_assert(offsetof(DrShdDataList, unknown68) == 0x068, "");
static_assert(offsetof(DrShdDataList, unknown620) == 0x620, "");
static_assert(offsetof(DrShdDataList, unknown638) == 0x638, "");
static_assert(offsetof(DrShdDataList, unknown818) == 0x818, "");
static_assert(offsetof(DrShdDataList, unknown958) == 0x958, "");
static_assert(offsetof(DrShdDataList, unknown980) == 0x980, "");
static_assert(offsetof(DrShdDataList, unknown9a8) == 0x9a8, "");
static_assert(offsetof(DrShdDataList, unknown9d0) == 0x9d0, "");
static_assert(offsetof(DrShdDataList, unknown9d8) == 0x9d8, "");

} // namespace ml
