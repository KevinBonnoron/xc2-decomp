#include "dr/dr_shd_data_list.h"

#include "dr/dr_res_shd.h"
#include "dr/dr_shd_data_obj.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_shd_list.h"

namespace ml {

void DrShdDataObj::createShader(DrShdDataList *list, int type, int index) {
  if (type == 2) {
    return;
  }
  unknown68[0] = &list->unknown68[index];
  u8 next = DrShdDataList::s_etcNextVertex[index];
  unknown68[1] = next == 0xff ? nullptr : &list->unknown68[next];
}

void DrShdDataList::reloadShader(int type) { createShader(); }

DrShdDataObj *DrShdDataList::getDebugShdObj(int index) { return &unknown18[0][index]; }

DrShdDataObj *DrShdDataList::getSelectShdObj(int index) { return &unknown18[1][index]; }

DrShdDataObj *DrShdDataList::getShadowShdObj(int index) { return &unknown18[2][index]; }

DrShdDataObj *DrShdDataList::getPostShdObj(int index) { return &unknown18[3][index]; }

DrShdDataObj *DrShdDataList::getSteamShdObj(int index) { return &unknown18[4][index]; }

DrShdDataObj *DrShdDataList::getMpfShdObj(int index) { return &unknown18[5][index]; }

DrShdDataObj *DrShdDataList::getPreShdObj(int index) { return &unknown18[6][index]; }

DrShdDataObj *DrShdDataList::getComputeObj(int index) { return &unknown18[9][index]; }

DrShdDataObj *DrShdDataList::getCateShdObj(int category, int index) { return &unknown18[category][index]; }

DrResShdMpf *DrShdDataList::getMpfObj(int index) { return &unknown620[index]; }

DrResShdPrePass *DrShdDataList::getPrePassObj(int index) { return &unknown628[index]; }

DrResShdShw *DrShdDataList::getShwObj(int index) { return &unknown630[index]; }

DrResShdStreamOut *DrShdDataList::getStmOutObj(int index) { return &unknown9d0[index]; }

DrResShdObjMot *DrShdDataList::getObjMotBlurObj(int index) { return &unknown9d8[index]; }

void DrShdDataList::bindShdVertex() { grlib::CGLibCtlVertex::setVertex(unknown638); }

void DrShdDataList::bindShdSphereVertex() { grlib::CGLibCtlVertex::setVertex(unknown700); }

void DrShdDataList::bindShdSpotVertex() { grlib::CGLibCtlVertex::setVertex(unknown750); }

void DrShdDataList::bindQuadsTex() { grlib::CGLibCtlVertex::setVertex(unknown660); }

void DrShdDataList::bindTriangle() { grlib::CGLibCtlVertex::setVertex(unknown688); }

void DrShdDataList::bindTriangleTex() { grlib::CGLibCtlVertex::setVertex(unknown6b0); }

void DrShdDataList::bindShdBoxVertex() { grlib::CGLibCtlVertex::setVertex(unknown6d8); }

void DrShdDataList::bindShdCylinderVertex() { grlib::CGLibCtlVertex::setVertex(unknown728); }

void DrShdDataList::bindShdRainDropVertex() { grlib::CGLibCtlVertex::setVertex(unknown778); }

void DrShdDataList::bindShdEffVtx() { grlib::CGLibCtlVertex::setVertex(unknown7a0); }

void DrShdDataList::bindShdDepthCheck() { grlib::CGLibCtlVertex::setVertex(unknown7c8); }

void DrShdDataList::bindPlaneVertex() { grlib::CGLibCtlVertex::setVertex(unknown7f0); }

void DrShdDataList::renderQuads() { unknown818.drawIndex(); }

void DrShdDataList::renderInstQuads(int instanceCount) { unknown818.drawInsIndex(instanceCount); }

void DrShdDataList::renderTriangle() { unknown840.drawIndex(); }

void DrShdDataList::renderSphere() { unknown890.drawIndex(); }

void DrShdDataList::renderSpotMdl() { unknown8e0.drawIndex(); }

void DrShdDataList::renderBox() { unknown868.drawIndex(); }

void DrShdDataList::renderCylinder() { unknown8b8.drawIndex(); }

void DrShdDataList::renderRainDrop() { unknown908.drawIndex(); }

void DrShdDataList::renderEffVtx(int instanceCount) { unknown930.drawInsIndex(instanceCount); }

void DrShdDataList::renderPoint(int count) { grlib::CGLibCtlVertex::renderVertex(GRL_PRIMITIVE_POINTS, count); }

void DrShdDataList::renderPoint(int count, int instanceCount) { grlib::CGLibCtlVertex::renderInstanceVertex(GRL_PRIMITIVE_POINTS, count, instanceCount); }

DrResFetch *DrShdDataList::getFetchShader(int index) { return &unknown68[index]; }

DrResFetch *DrShdDataList::getSubFetchShader(int index) {
  u8 next = s_etcNextVertex[index];
  return next == 0xff ? nullptr : &unknown68[next];
}

grlib::CGLibOneUniformBlock *DrShdDataList::getAlphaTestUniform(f32 alphaRef) {
  u32 index = static_cast<s32>(alphaRef * 10.0f);
  if (index > 10) {
    index = 10;
  }
  return &unknown9a8.m_items[index];
}

DrShdDataObj::DrShdDataObj() {
  unknown68[0] = nullptr;
  unknown68[1] = nullptr;
}

DrShdDataObj::~DrShdDataObj() {}

void DrShdDataObj::release() {}

void DrShdDataObj::setupShader(u32 index) { grlib::CGLibCtlShader::setShader(*this, *unknown68[index]); }

void DrShdDataObj::setupShader(DrResFetch *fetch) { grlib::CGLibCtlShader::setShader(*this, *fetch); }

void DrShdDataObj::setupComputeShader() { grlib::CGLibCtlShader::setComputeShader(*this); }

} // namespace ml

template class grlib::CGLibShdListBase<ml::DrShdDataObj>;

// clang-format off
#include "dr_shd_fetch_man.cpp"
#include "dr_shd_fetch_obj.cpp"
#include "dr_shd_lgt_man.cpp"
#include "dr_shd_lgt_obj.cpp"
#include "dr_shd_lgt_tile_based_dr.cpp"
#include "dr_shd_man.cpp"
#include "dr_shd_mdo_man.cpp"
#include "dr_shd_mdo_ext_tbl_obj.cpp"
#include "dr_shd_mdo_dec_ext_tbl.cpp"
#include "dr_shd_mdo_dec_res.cpp"
// clang-format on
