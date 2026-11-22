#include "dr/dr_res_shd.h"

#include "dr/dr_shd_data_obj.h"
#include "grlib/cglib_shader.h"

namespace ml {

namespace _drrsm {

const char *c_DeclOfsNames[2] = {"MODE_UMATE_ON", "DECL_DITHER"};

} // namespace _drrsm

DrResShdMpf::DrResShdMpf(DrShdDataObj *dataObj, int type) : m_drShdDataObj(dataObj) {
  for (int i = 0; i < 8; i++) {
    unknown08[i] = -1;
  }
  unknown28 = 1;
  unknown2a = type;
  unknown2c[0] = m_drShdDataObj->getDeclarationOfs(_drrsm::c_DeclOfsNames[0]);
  unknown2c[1] = m_drShdDataObj->getDeclarationOfs(_drrsm::c_DeclOfsNames[1]);
  setShaderParam();
}

void DrResShdMpf::setShaderParam() {
  unknown08[2] = 1;
  unknown08[0] = 0;
  unknown08[1] = 1;
  unknown08[3] = (m_drShdDataObj->unknown38 + m_drShdDataObj->unknown58)->getUniformBlockOfs("U_MpfWet");
  unknown08[4] = (m_drShdDataObj->unknown38 + m_drShdDataObj->unknown58)->getUniformBlockOfs("U_MpfOld");
  unknown08[5] = 1;
  unknown08[6] = 0;
  unknown08[7] = 2;
  unknown28 &= ~1;
}

void DrResShdMpf::setupShader(u32 mode) {
  m_drShdDataObj->setDeclarationIdx(unknown2c[0], 2 - (mode & 1));
  m_drShdDataObj->setDeclarationIdx(unknown2c[1], 2 - ((mode >> 1) & 1));
  m_drShdDataObj->setupShader((mode >> 1) & 1);
}

DrResShdPrePass::DrResShdPrePass(DrShdDataObj *dataObj, int type) : m_drShdDataObj(dataObj) {
  for (int i = 0; i < 11; i++) {
    unknown08[i] = -1;
  }
  unknown3a = type;
  unknown38 = 1;
  unknown34 = m_drShdDataObj->getDeclarationOfs("DECL_PASS_TYPE");
  setShaderParam();
}

void DrResShdPrePass::setShaderParam() {
  (this->*s_callShdSet[unknown3a])();
  unknown38 &= ~1;
}

void DrResShdPrePass::setupShader(u32 index, u32 passType) {
  m_drShdDataObj->setDeclarationIdx(unknown34, passType);
  m_drShdDataObj->setupShader(index);
}

void DrResShdPrePass::preshdset_Obj() { unknown08[5] = 2; }

void DrResShdPrePass::preshdset_ObjT() {
  unknown08[5] = 2;
  unknown08[8] = 1;
  unknown08[0] = 0;
}

void DrResShdPrePass::preshdset_ObjT_Al() {
  unknown08[5] = 2;
  unknown08[6] = 0;
  unknown08[9] = 4;
  unknown08[8] = 1;
  unknown08[0] = 0;
  unknown08[1] = 1;
}

void DrResShdPrePass::preshdset_Mot() { unknown08[6] = 0; }

void DrResShdPrePass::preshdset_MotT() {
  unknown08[6] = 0;
  unknown08[0] = 0;
  unknown08[8] = 1;
}

void DrResShdPrePass::preshdset_MotT_Al() {
  unknown08[5] = 2;
  unknown08[6] = 0;
  unknown08[9] = 4;
  unknown08[8] = 1;
  unknown08[0] = 0;
  unknown08[1] = 1;
}

void DrResShdPrePass::preshdset_Inst() { unknown08[6] = 0; }

void DrResShdPrePass::preshdset_InstT() {
  unknown08[6] = 0;
  unknown08[0] = 0;
  unknown08[8] = 1;
}

void DrResShdPrePass::preshdset_Obj_Al() {
  unknown08[5] = 2;
  unknown08[6] = 0;
  unknown08[9] = 4;
  unknown08[1] = 1;
  unknown08[8] = 1;
}

void DrResShdPrePass::preshdset_Mot_Al() {
  unknown08[5] = 2;
  unknown08[6] = 0;
  unknown08[9] = 4;
  unknown08[1] = 1;
  unknown08[8] = 1;
}

void DrResShdPrePass::preshdset_Inst_Al() {
  unknown08[6] = 0;
  unknown08[9] = 4;
  unknown08[1] = 1;
  unknown08[8] = 1;
}

void DrResShdPrePass::preshdset_InstT_Al() {
  unknown08[6] = 0;
  unknown08[9] = 4;
  unknown08[8] = 1;
  unknown08[0] = 0;
  unknown08[1] = 1;
}

void DrResShdPrePass::preshdset_Inst_Bill_Al() {
  unknown08[5] = 3;
  unknown08[6] = 0;
  unknown08[9] = 4;
  unknown08[1] = 1;
  unknown08[8] = 1;
}

void DrResShdPrePass::preshdset_InstT_Bill_Al() {
  unknown08[5] = 3;
  unknown08[6] = 0;
  unknown08[9] = 4;
  unknown08[8] = 1;
  unknown08[0] = 0;
  unknown08[1] = 1;
}

void DrResShdPrePass::preshdset_Fw() {
  unknown08[5] = 2;
  unknown08[10] = 3;
  unknown08[3] = 3;
  unknown08[4] = 4;
}

void DrResShdPrePass::preshdset_FwT() {
  unknown08[3] = 3;
  unknown08[5] = 2;
  unknown08[8] = 1;
  unknown08[0] = 0;
  unknown08[10] = 3;
  unknown08[4] = 4;
}

void DrResShdPrePass::preshdset_Fw_Al() {
  unknown08[5] = 2;
  unknown08[6] = 0;
  unknown08[9] = 4;
  unknown08[3] = 3;
  unknown08[1] = 1;
  unknown08[10] = 3;
  unknown08[8] = 1;
  unknown08[4] = 4;
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

DrResShdShw::DrResShdShw(DrShdDataObj *dataObj, int type) : m_drShdDataObj(dataObj) {
  for (int i = 0; i < 7; i++) {
    unknown08[i] = -1;
  }
  unknown28 = 1;
  unknown2a = type;
  unknown24 = m_drShdDataObj->getDeclarationOfs("TEX_TYPE");
  unknown26 = m_drShdDataObj->getDeclarationOfs("SPT_TYPE");
  setShaderParam();
}

void DrResShdShw::setShaderParam() {
  (this->*s_callShwSet[unknown2a])();
  unknown28 &= ~1;
}

void DrResShdShw::setupShader(DrResFetch *fetch) { m_drShdDataObj->setupShader(fetch); }

void DrResShdShw::setDecAType(u32 index) { m_drShdDataObj->setDeclarationIdx(unknown24, index); }

void DrResShdShw::setDecBType(u32 index) { m_drShdDataObj->setDeclarationIdx(unknown26, index); }

void DrResShdShw::shwShdset_DefObj() {
  unknown08[2] = 1;
  unknown08[0] = 0;
  unknown08[3] = 2;
  unknown08[1] = 0;
}

void DrResShdShw::shwShdset_Inst() {
  unknown08[2] = 1;
  unknown08[0] = 0;
  unknown08[3] = 2;
  unknown08[1] = 0;
}

void DrResShdShw::shwShdset_Mot() {
  unknown08[2] = 1;
  unknown08[0] = 0;
  unknown08[3] = 2;
  unknown08[1] = 0;
}

void DrResShdShw::shwShdset_InstMot() {
  unknown08[2] = 1;
  unknown08[0] = 0;
  unknown08[3] = 2;
  unknown08[1] = 0;
}

void DrResShdShw::shwShdset_Fw() {
  unknown08[1] = 0;
  unknown08[2] = 1;
  unknown08[3] = 2;
  unknown08[0] = 0;
  unknown08[4] = 3;
  unknown08[5] = 1;
  unknown08[6] = 2;
}

void (DrResShdShw::*DrResShdShw::s_callShwSet[])() = {
    &DrResShdShw::shwShdset_DefObj,
    &DrResShdShw::shwShdset_Inst,
    &DrResShdShw::shwShdset_Mot,
    &DrResShdShw::shwShdset_InstMot,
    &DrResShdShw::shwShdset_Fw,
};

DrResShdStreamOut::DrResShdStreamOut(DrShdDataObj *dataObj, int type) : m_drShdDataObj(dataObj) {
  unknown08[0] = -1;
  unknown08[1] = -1;
  unknown08[2] = -1;
  unknown14 = type;
  unknown16 = 0;
  setShaderParam();
}

void DrResShdStreamOut::setupStreamShader(u32 index) { m_drShdDataObj->setupShader(index); }

void DrResShdStreamOut::setShaderParam() { (this->*s_callStmOuSet[unknown14])(); }

void DrResShdStreamOut::setDecNum(u32 num) { m_drShdDataObj->setDeclarationIdx(unknown16, num); }

void DrResShdStreamOut::stmShdset_Weight() {
  unknown08[0] = 1;
  unknown08[1] = 0;
}

void DrResShdStreamOut::stmShdset_WetVtx() {
  unknown08[0] = 1;
  unknown08[1] = 0;
  // The game stores {1, 0} as one 64-bit store and the 2 as a separate word (0x710088f6f0, 0x710088f6fc): a load between
  // the stores keeps the third one out of the merge, so m_drShdDataObj is read here.
  DrShdDataObj *dataObj = m_drShdDataObj;
  unknown08[2] = 2;
  unknown16 = dataObj->getDeclarationOfs("WET_NUM");
}

void DrResShdStreamOut::stmShdset_MofSet() {
  unknown08[0] = 0;
  unknown08[1] = 0;
}

void DrResShdStreamOut::stmShdset_MeshVtxSet() {
  unknown08[0] = 0;
  unknown08[1] = 1;
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

DrResShdObjMot::DrResShdObjMot(DrShdDataObj *dataObj, int type) : m_drShdDataObj(dataObj) {
  for (int i = 0; i < 5; i++) {
    unknown08[i] = -1;
  }
  unknown1c = 1;
  unknown1e = type;
  setShaderParam();
}

void DrResShdObjMot::setShaderParam() {
  (this->*s_callMotObjSet[unknown1e])();
  unknown1c &= ~1;
}

void DrResShdObjMot::setupShader() { m_drShdDataObj->setupShader(0u); }

void DrResShdObjMot::motblur_motObj() {
  unknown08[0] = 0;
  unknown08[1] = 1;
  unknown08[2] = (m_drShdDataObj->unknown38 + m_drShdDataObj->unknown58)->getUniformBlockOfs("U_VPam");
  unknown08[3] = (m_drShdDataObj->unknown38 + m_drShdDataObj->unknown58)->getUniformBlockOfs("U_VPam");
}

void DrResShdObjMot::motblur_motObjTex() {
  unknown08[0] = 0;
  unknown08[1] = 1;
  unknown08[2] = (m_drShdDataObj->unknown38 + m_drShdDataObj->unknown58)->getUniformBlockOfs("U_VPam");
  unknown08[3] = (m_drShdDataObj->unknown38 + m_drShdDataObj->unknown58)->getUniformBlockOfs("U_VPam");
  unknown08[4] = (m_drShdDataObj->unknown38 + m_drShdDataObj->unknown58)->getTextureLocation("tex");
}

void DrResShdObjMot::motblur_notObj() {
  unknown08[0] = (m_drShdDataObj->unknown38 + m_drShdDataObj->unknown58)->getUniformBlockOfs("U_MDL1");
  unknown08[1] = (m_drShdDataObj->unknown38 + m_drShdDataObj->unknown58)->getUniformBlockOfs("U_MDL2");
  unknown08[2] = (m_drShdDataObj->unknown38 + m_drShdDataObj->unknown58)->getUniformBlockOfs("U_VPam");
  unknown08[3] = (m_drShdDataObj->unknown38 + m_drShdDataObj->unknown58)->getUniformBlockOfs("U_VPam");
}

void DrResShdObjMot::motblur_notObjTex() {
  unknown08[0] = (m_drShdDataObj->unknown38 + m_drShdDataObj->unknown58)->getUniformBlockOfs("U_MDL1");
  unknown08[1] = (m_drShdDataObj->unknown38 + m_drShdDataObj->unknown58)->getUniformBlockOfs("U_MDL2");
  unknown08[2] = (m_drShdDataObj->unknown38 + m_drShdDataObj->unknown58)->getUniformBlockOfs("U_VPam");
  unknown08[3] = (m_drShdDataObj->unknown38 + m_drShdDataObj->unknown58)->getUniformBlockOfs("U_VPam");
  unknown08[4] = (m_drShdDataObj->unknown38 + m_drShdDataObj->unknown58)->getTextureLocation("tex");
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
