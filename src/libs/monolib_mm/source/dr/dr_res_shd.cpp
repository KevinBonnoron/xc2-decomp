#include "dr/dr_res_shd.h"

#include "dr/dr_shd_data_obj.h"
#include "grlib/cglib_shader.h"

namespace ml {

void DrResShdMpf::setupShader(u32 mode) {
  m_dataObj->setDeclarationIdx(m_declOfs[0], 2 - (mode & 1));
  m_dataObj->setDeclarationIdx(m_declOfs[1], 2 - ((mode >> 1) & 1));
  m_dataObj->setupShader((mode >> 1) & 1);
}

DrResShdPrePass::DrResShdPrePass(DrShdDataObj *dataObj, int type) : m_dataObj(dataObj) {
  for (int i = 0; i < 11; i++) {
    m_locations[i] = -1;
  }
  m_type = type;
  m_flags = 1;
  m_passTypeOfs = m_dataObj->getDeclarationOfs("DECL_PASS_TYPE");
  setShaderParam();
}

void DrResShdPrePass::setShaderParam() {
  (this->*s_callShdSet[m_type])();
  m_flags &= ~1;
}

void DrResShdPrePass::setupShader(u32 index, u32 passType) {
  m_dataObj->setDeclarationIdx(m_passTypeOfs, passType);
  m_dataObj->setupShader(index);
}

void DrResShdPrePass::preshdset_Obj() { m_locations[5] = 2; }

void DrResShdPrePass::preshdset_ObjT() {
  m_locations[5] = 2;
  m_locations[8] = 1;
  m_locations[0] = 0;
}

void DrResShdPrePass::preshdset_ObjT_Al() {
  m_locations[5] = 2;
  m_locations[6] = 0;
  m_locations[9] = 4;
  m_locations[8] = 1;
  m_locations[0] = 0;
  m_locations[1] = 1;
}

void DrResShdPrePass::preshdset_Mot() { m_locations[6] = 0; }

void DrResShdPrePass::preshdset_MotT() {
  m_locations[6] = 0;
  m_locations[0] = 0;
  m_locations[8] = 1;
}

void DrResShdPrePass::preshdset_MotT_Al() {
  m_locations[5] = 2;
  m_locations[6] = 0;
  m_locations[9] = 4;
  m_locations[8] = 1;
  m_locations[0] = 0;
  m_locations[1] = 1;
}

void DrResShdPrePass::preshdset_Inst() { m_locations[6] = 0; }

void DrResShdPrePass::preshdset_InstT() {
  m_locations[6] = 0;
  m_locations[0] = 0;
  m_locations[8] = 1;
}

void DrResShdPrePass::preshdset_Obj_Al() {
  m_locations[5] = 2;
  m_locations[6] = 0;
  m_locations[9] = 4;
  m_locations[1] = 1;
  m_locations[8] = 1;
}

void DrResShdPrePass::preshdset_Mot_Al() {
  m_locations[5] = 2;
  m_locations[6] = 0;
  m_locations[9] = 4;
  m_locations[1] = 1;
  m_locations[8] = 1;
}

void DrResShdPrePass::preshdset_Inst_Al() {
  m_locations[6] = 0;
  m_locations[9] = 4;
  m_locations[1] = 1;
  m_locations[8] = 1;
}

void DrResShdPrePass::preshdset_InstT_Al() {
  m_locations[6] = 0;
  m_locations[9] = 4;
  m_locations[8] = 1;
  m_locations[0] = 0;
  m_locations[1] = 1;
}

void DrResShdPrePass::preshdset_Inst_Bill_Al() {
  m_locations[5] = 3;
  m_locations[6] = 0;
  m_locations[9] = 4;
  m_locations[1] = 1;
  m_locations[8] = 1;
}

void DrResShdPrePass::preshdset_InstT_Bill_Al() {
  m_locations[5] = 3;
  m_locations[6] = 0;
  m_locations[9] = 4;
  m_locations[8] = 1;
  m_locations[0] = 0;
  m_locations[1] = 1;
}

void DrResShdPrePass::preshdset_Fw() {
  m_locations[5] = 2;
  m_locations[10] = 3;
  m_locations[3] = 3;
  m_locations[4] = 4;
}

void DrResShdPrePass::preshdset_FwT() {
  m_locations[3] = 3;
  m_locations[5] = 2;
  m_locations[8] = 1;
  m_locations[0] = 0;
  m_locations[10] = 3;
  m_locations[4] = 4;
}

void DrResShdPrePass::preshdset_Fw_Al() {
  m_locations[5] = 2;
  m_locations[6] = 0;
  m_locations[9] = 4;
  m_locations[3] = 3;
  m_locations[1] = 1;
  m_locations[10] = 3;
  m_locations[8] = 1;
  m_locations[4] = 4;
}

void (DrResShdPrePass::*DrResShdPrePass::s_callShdSet[])() = {
    &DrResShdPrePass::preshdset_Obj,           &DrResShdPrePass::preshdset_ObjT,          &DrResShdPrePass::preshdset_ObjT,
    &DrResShdPrePass::preshdset_ObjT_Al,       &DrResShdPrePass::preshdset_ObjT_Al,       &DrResShdPrePass::preshdset_Mot,
    &DrResShdPrePass::preshdset_MotT,          &DrResShdPrePass::preshdset_MotT,          &DrResShdPrePass::preshdset_MotT_Al,
    &DrResShdPrePass::preshdset_MotT_Al,       &DrResShdPrePass::preshdset_Inst,          &DrResShdPrePass::preshdset_InstT,
    &DrResShdPrePass::preshdset_InstT,         &DrResShdPrePass::preshdset_Obj_Al,        &DrResShdPrePass::preshdset_ObjT_Al,
    &DrResShdPrePass::preshdset_ObjT_Al,       &DrResShdPrePass::preshdset_ObjT_Al_Fs,    &DrResShdPrePass::preshdset_ObjT_Al_Fs,
    &DrResShdPrePass::preshdset_Mot_Al,        &DrResShdPrePass::preshdset_MotT_Al,       &DrResShdPrePass::preshdset_MotT_Al,
    &DrResShdPrePass::preshdset_MotT_Al_Fs,    &DrResShdPrePass::preshdset_MotT_Al_Fs,    &DrResShdPrePass::preshdset_Inst_Al,
    &DrResShdPrePass::preshdset_InstT_Al,      &DrResShdPrePass::preshdset_InstT_Al,      &DrResShdPrePass::preshdset_Inst_Bill_Al,
    &DrResShdPrePass::preshdset_InstT_Bill_Al, &DrResShdPrePass::preshdset_InstT_Bill_Al, &DrResShdPrePass::preshdset_Inst_Bill_Al,
    &DrResShdPrePass::preshdset_InstT_Bill_Al, &DrResShdPrePass::preshdset_InstT_Bill_Al, &DrResShdPrePass::preshdset_Fw,
    &DrResShdPrePass::preshdset_FwT,           &DrResShdPrePass::preshdset_FwT,           &DrResShdPrePass::preshdset_FwT_Al,
    &DrResShdPrePass::preshdset_FwT_Al,        &DrResShdPrePass::preshdset_Fw_Al,         &DrResShdPrePass::preshdset_FwT_Al,
    &DrResShdPrePass::preshdset_FwT_Al,        &DrResShdPrePass::preshdset_FwT_Al_Fs,     &DrResShdPrePass::preshdset_FwT_Al_Fs,
};

DrResShdShw::DrResShdShw(DrShdDataObj *dataObj, int type) : m_dataObj(dataObj) {
  for (int i = 0; i < 7; i++) {
    m_locations[i] = -1;
  }
  m_flags = 1;
  m_type = type;
  m_texTypeOfs = m_dataObj->getDeclarationOfs("TEX_TYPE");
  m_sptTypeOfs = m_dataObj->getDeclarationOfs("SPT_TYPE");
  setShaderParam();
}

void DrResShdShw::setShaderParam() {
  (this->*s_callShwSet[m_type])();
  m_flags &= ~1;
}

void DrResShdShw::setupShader(DrResFetch *fetch) { m_dataObj->setupShader(fetch); }

void DrResShdShw::setDecAType(u32 index) { m_dataObj->setDeclarationIdx(m_texTypeOfs, index); }

void DrResShdShw::setDecBType(u32 index) { m_dataObj->setDeclarationIdx(m_sptTypeOfs, index); }

void DrResShdShw::shwShdset_DefObj() {
  m_locations[2] = 1;
  m_locations[0] = 0;
  m_locations[3] = 2;
  m_locations[1] = 0;
}

void DrResShdShw::shwShdset_Inst() {
  m_locations[2] = 1;
  m_locations[0] = 0;
  m_locations[3] = 2;
  m_locations[1] = 0;
}

void DrResShdShw::shwShdset_Mot() {
  m_locations[2] = 1;
  m_locations[0] = 0;
  m_locations[3] = 2;
  m_locations[1] = 0;
}

void DrResShdShw::shwShdset_InstMot() {
  m_locations[2] = 1;
  m_locations[0] = 0;
  m_locations[3] = 2;
  m_locations[1] = 0;
}

void DrResShdShw::shwShdset_Fw() {
  m_locations[1] = 0;
  m_locations[2] = 1;
  m_locations[3] = 2;
  m_locations[0] = 0;
  m_locations[4] = 3;
  m_locations[5] = 1;
  m_locations[6] = 2;
}

void (DrResShdShw::*DrResShdShw::s_callShwSet[])() = {
    &DrResShdShw::shwShdset_DefObj,
    &DrResShdShw::shwShdset_Inst,
    &DrResShdShw::shwShdset_Mot,
    &DrResShdShw::shwShdset_InstMot,
    &DrResShdShw::shwShdset_Fw,
};

void DrResShdStreamOut::setShaderParam() { (this->*s_callStmOuSet[m_type])(); }

void DrResShdStreamOut::setDecNum(u32 num) { m_dataObj->setDeclarationIdx(m_wetNumOfs, num); }

void DrResShdStreamOut::stmShdset_Weight() {
  m_locations[0] = 1;
  m_locations[1] = 0;
}

void DrResShdStreamOut::stmShdset_MofSet() {
  m_locations[0] = 0;
  m_locations[1] = 0;
}

void DrResShdStreamOut::stmShdset_MeshVtxSet() {
  m_locations[0] = 0;
  m_locations[1] = 1;
}

void (DrResShdStreamOut::*DrResShdStreamOut::s_callStmOuSet[])() = {
    &DrResShdStreamOut::stmShdset_Weight,
    &DrResShdStreamOut::stmShdset_Weight,
    &DrResShdStreamOut::stmShdset_Weight,
    &DrResShdStreamOut::stmShdset_Weight,
    &DrResShdStreamOut::stmShdset_WetVtx,
    &DrResShdStreamOut::stmShdset_MofSet,
    &DrResShdStreamOut::stmShdset_MofSet,
    &DrResShdStreamOut::stmShdset_MeshVtxSet,
    &DrResShdStreamOut::stmShdset_MofSet,
};

DrResShdObjMot::DrResShdObjMot(DrShdDataObj *dataObj, int type) : m_dataObj(dataObj) {
  for (int i = 0; i < 5; i++) {
    m_locations[i] = -1;
  }
  m_flags = 1;
  m_type = type;
  setShaderParam();
}

void DrResShdObjMot::setShaderParam() {
  (this->*s_callMotObjSet[m_type])();
  m_flags &= ~1;
}

void DrResShdObjMot::setupShader() { m_dataObj->setupShader(0u); }

void DrResShdObjMot::motblur_motObj() {
  m_locations[0] = 0;
  m_locations[1] = 1;
  m_locations[2] = (m_dataObj->m_shaders + m_dataObj->m_shaderIdx)->getUniformBlockOfs("U_VPam");
  m_locations[3] = (m_dataObj->m_shaders + m_dataObj->m_shaderIdx)->getUniformBlockOfs("U_VPam");
}

void DrResShdObjMot::motblur_motObjTex() {
  m_locations[0] = 0;
  m_locations[1] = 1;
  m_locations[2] = (m_dataObj->m_shaders + m_dataObj->m_shaderIdx)->getUniformBlockOfs("U_VPam");
  m_locations[3] = (m_dataObj->m_shaders + m_dataObj->m_shaderIdx)->getUniformBlockOfs("U_VPam");
  m_locations[4] = (m_dataObj->m_shaders + m_dataObj->m_shaderIdx)->getTextureLocation("tex");
}

void DrResShdObjMot::motblur_notObj() {
  m_locations[0] = (m_dataObj->m_shaders + m_dataObj->m_shaderIdx)->getUniformBlockOfs("U_MDL1");
  m_locations[1] = (m_dataObj->m_shaders + m_dataObj->m_shaderIdx)->getUniformBlockOfs("U_MDL2");
  m_locations[2] = (m_dataObj->m_shaders + m_dataObj->m_shaderIdx)->getUniformBlockOfs("U_VPam");
  m_locations[3] = (m_dataObj->m_shaders + m_dataObj->m_shaderIdx)->getUniformBlockOfs("U_VPam");
}

void DrResShdObjMot::motblur_notObjTex() {
  m_locations[0] = (m_dataObj->m_shaders + m_dataObj->m_shaderIdx)->getUniformBlockOfs("U_MDL1");
  m_locations[1] = (m_dataObj->m_shaders + m_dataObj->m_shaderIdx)->getUniformBlockOfs("U_MDL2");
  m_locations[2] = (m_dataObj->m_shaders + m_dataObj->m_shaderIdx)->getUniformBlockOfs("U_VPam");
  m_locations[3] = (m_dataObj->m_shaders + m_dataObj->m_shaderIdx)->getUniformBlockOfs("U_VPam");
  m_locations[4] = (m_dataObj->m_shaders + m_dataObj->m_shaderIdx)->getTextureLocation("tex");
}

void (DrResShdObjMot::*DrResShdObjMot::s_callMotObjSet[])() = {
    &DrResShdObjMot::motblur_motObj,
    &DrResShdObjMot::motblur_motObjTex,
    &DrResShdObjMot::motblur_motObjTex,
    &DrResShdObjMot::motblur_notObj,
    &DrResShdObjMot::motblur_notObjTex,
    &DrResShdObjMot::motblur_notObjTex,
};

} // namespace ml
