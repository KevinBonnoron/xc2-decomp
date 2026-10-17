#pragma once
#include <stddef.h>

#include "dr/dr_res_fetch.h"
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
class DrShdDataObj;

class DrShdDataList {
public:
  void createShader();
  void reloadShader(int type);
  DrShdDataObj *getDebugShdObj(int index);
  DrShdDataObj *getSelectShdObj(int index);
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
  DrMan *m_drMan;
  u8 _010[0x018 - 0x010];
  DrShdDataObj *m_shdObjs[10];
  DrResFetch m_fetches[91];
  u8 _618[0x620 - 0x618];
  DrResShdMpf *m_mpfObjs;
  DrResShdPrePass *m_prePassObjs;
  DrResShdShw *m_shwObjs;
  grlib::CGLibVtxVertex m_shdVertex;
  grlib::CGLibVtxVertex m_quadsTexVertex;
  grlib::CGLibVtxVertex m_triangleVertex;
  grlib::CGLibVtxVertex m_triangleTexVertex;
  grlib::CGLibVtxVertex m_boxVertex;
  grlib::CGLibVtxVertex m_sphereVertex;
  grlib::CGLibVtxVertex m_cylinderVertex;
  grlib::CGLibVtxVertex m_spotVertex;
  grlib::CGLibVtxVertex m_rainDropVertex;
  grlib::CGLibVtxVertex m_effVertex;
  grlib::CGLibVtxVertex m_depthCheckVertex;
  grlib::CGLibVtxVertex m_planeVertex;
  grlib::CGLibVtxIndex m_quadsIndex;
  grlib::CGLibVtxIndex m_triangleIndex;
  grlib::CGLibVtxIndex m_boxIndex;
  grlib::CGLibVtxIndex m_sphereIndex;
  grlib::CGLibVtxIndex m_cylinderIndex;
  grlib::CGLibVtxIndex m_spotIndex;
  grlib::CGLibVtxIndex m_rainDropIndex;
  grlib::CGLibVtxIndex m_effIndex;
  grlib::CGLibVtxStmOut m_stmOuts[2];
  grlib::CGLibUniformArray<grlib::CGLibOneUniformBlock> m_alphaTestUniforms;
  u8 _9b0[0x9d0 - 0x9b0];
  DrResShdStreamOut *m_stmOutObjs;
  DrResShdObjMot *m_objMotBlurObjs;
};

static_assert(offsetof(DrShdDataList, m_drMan) == 0x008, "");
static_assert(offsetof(DrShdDataList, m_shdObjs) == 0x018, "");
static_assert(offsetof(DrShdDataList, m_fetches) == 0x068, "");
static_assert(offsetof(DrShdDataList, m_mpfObjs) == 0x620, "");
static_assert(offsetof(DrShdDataList, m_shdVertex) == 0x638, "");
static_assert(offsetof(DrShdDataList, m_quadsIndex) == 0x818, "");
static_assert(offsetof(DrShdDataList, m_stmOuts) == 0x958, "");
static_assert(offsetof(DrShdDataList, m_alphaTestUniforms) == 0x9a8, "");
static_assert(offsetof(DrShdDataList, m_stmOutObjs) == 0x9d0, "");
static_assert(offsetof(DrShdDataList, m_objMotBlurObjs) == 0x9d8, "");

} // namespace ml
