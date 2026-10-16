#include "dr/dr_shd_data_list.h"

#include "dr/dr_res_shd.h"
#include "dr/dr_shd_data_obj.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_one_uniform_block.h"

namespace ml {

void DrShdDataList::reloadShader(int type) { createShader(); }

DrShdDataObj *DrShdDataList::getDebugShdObj(int index) { return &m_shdObjs[0][index]; }

DrShdDataObj *DrShdDataList::getSelectShdObj(int index) { return &m_shdObjs[1][index]; }

DrShdDataObj *DrShdDataList::getShadowShdObj(int index) { return &m_shdObjs[2][index]; }

DrShdDataObj *DrShdDataList::getPostShdObj(int index) { return &m_shdObjs[3][index]; }

DrShdDataObj *DrShdDataList::getSteamShdObj(int index) { return &m_shdObjs[4][index]; }

DrShdDataObj *DrShdDataList::getMpfShdObj(int index) { return &m_shdObjs[5][index]; }

DrShdDataObj *DrShdDataList::getPreShdObj(int index) { return &m_shdObjs[6][index]; }

DrShdDataObj *DrShdDataList::getComputeObj(int index) { return &m_shdObjs[9][index]; }

DrShdDataObj *DrShdDataList::getCateShdObj(int category, int index) { return &m_shdObjs[category][index]; }

DrResShdMpf *DrShdDataList::getMpfObj(int index) { return &m_mpfObjs[index]; }

DrResShdPrePass *DrShdDataList::getPrePassObj(int index) { return &m_prePassObjs[index]; }

DrResShdShw *DrShdDataList::getShwObj(int index) { return &m_shwObjs[index]; }

DrResShdStreamOut *DrShdDataList::getStmOutObj(int index) { return &m_stmOutObjs[index]; }

DrResShdObjMot *DrShdDataList::getObjMotBlurObj(int index) { return &m_objMotBlurObjs[index]; }

void DrShdDataList::bindShdVertex() { grlib::CGLibCtlVertex::setVertex(m_shdVertex); }

void DrShdDataList::bindShdSphereVertex() { grlib::CGLibCtlVertex::setVertex(m_sphereVertex); }

void DrShdDataList::bindShdSpotVertex() { grlib::CGLibCtlVertex::setVertex(m_spotVertex); }

void DrShdDataList::bindQuadsTex() { grlib::CGLibCtlVertex::setVertex(m_quadsTexVertex); }

void DrShdDataList::bindTriangle() { grlib::CGLibCtlVertex::setVertex(m_triangleVertex); }

void DrShdDataList::bindTriangleTex() { grlib::CGLibCtlVertex::setVertex(m_triangleTexVertex); }

void DrShdDataList::bindShdBoxVertex() { grlib::CGLibCtlVertex::setVertex(m_boxVertex); }

void DrShdDataList::bindShdCylinderVertex() { grlib::CGLibCtlVertex::setVertex(m_cylinderVertex); }

void DrShdDataList::bindShdRainDropVertex() { grlib::CGLibCtlVertex::setVertex(m_rainDropVertex); }

void DrShdDataList::bindShdEffVtx() { grlib::CGLibCtlVertex::setVertex(m_effVertex); }

void DrShdDataList::bindShdDepthCheck() { grlib::CGLibCtlVertex::setVertex(m_depthCheckVertex); }

void DrShdDataList::bindPlaneVertex() { grlib::CGLibCtlVertex::setVertex(m_planeVertex); }

void DrShdDataList::renderQuads() { m_quadsIndex.drawIndex(); }

void DrShdDataList::renderInstQuads(int instanceCount) { m_quadsIndex.drawInsIndex(instanceCount); }

void DrShdDataList::renderTriangle() { m_triangleIndex.drawIndex(); }

void DrShdDataList::renderSphere() { m_sphereIndex.drawIndex(); }

void DrShdDataList::renderSpotMdl() { m_spotIndex.drawIndex(); }

void DrShdDataList::renderBox() { m_boxIndex.drawIndex(); }

void DrShdDataList::renderCylinder() { m_cylinderIndex.drawIndex(); }

void DrShdDataList::renderRainDrop() { m_rainDropIndex.drawIndex(); }

void DrShdDataList::renderEffVtx(int instanceCount) { m_effIndex.drawInsIndex(instanceCount); }

void DrShdDataList::renderPoint(int count) { grlib::CGLibCtlVertex::renderVertex(GRL_PRIMITIVE_POINTS, count); }

void DrShdDataList::renderPoint(int count, int instanceCount) {
  grlib::CGLibCtlVertex::renderInstanceVertex(GRL_PRIMITIVE_POINTS, count, instanceCount);
}

DrResFetch *DrShdDataList::getFetchShader(int index) { return &m_fetches[index]; }

DrResFetch *DrShdDataList::getSubFetchShader(int index) {
  u8 next = s_etcNextVertex[index];
  return next == 0xff ? nullptr : &m_fetches[next];
}

grlib::CGLibOneUniformBlock *DrShdDataList::getAlphaTestUniform(f32 alphaRef) {
  u32 index = static_cast<s32>(alphaRef * 10.0f);
  if (index > 10) {
    index = 10;
  }
  return &m_alphaTestUniforms.m_items[index];
}

} // namespace ml
