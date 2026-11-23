#include "dr/dr_shd_lgt_man.h"

#include "dr/dr_ap_gx_type.h"
#include "dr/dr_light_obj.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_shd_lgt_clustered.h"
#include "dr/dr_shd_lgt_global_ibl.h"
#include "dr/dr_shd_lgt_hybrid.h"
#include "dr/dr_shd_lgt_obj.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_shd_list.h"
#include "ml/file_res_th.h"
#include "ml/scn.h"
#include "ml/work_util.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrShdLgtMan::DrShdLgtMan(DrMan *drMan) : m_drMan(drMan), m_fileResTh(nullptr), m_hybridLight(nullptr), m_drShdLgtClustered(nullptr) {
  unknown10 = new (m_drMan->unknown0c) grlib::CGLibShdListBase<DrShdLgtObj>();
  m_drResFetch.setLgtVertexParam();
  releaseLightShader();
  reloadShader(0);
  m_hybridLight = new (drMan->unknown0c) DrShdLgtHybrid(drMan);
  m_drShdLgtGlobalIBL = new (drMan->unknown0c) DrShdLgtGlobalIBL(drMan);
  m_drShdLgtClustered = new (drMan->unknown0c) DrShdLgtClustered(drMan, true);
}

void DrShdLgtMan::releaseLightShader() {
  unknown10->release();
  if (m_fileResTh != nullptr) {
    m_fileResTh->Release();
    m_fileResTh = nullptr;
  }
}

void DrShdLgtMan::reloadShader(int) {
  Scn *scn = Scn::get();
  if (scn != nullptr) {
    m_fileResTh = scn->allocEntryRes("/monolib/shader/shd_lgt.wishp");
  }
  if (m_fileResTh == nullptr) {
    m_fileResTh = new (WorkUtil::getWorkMem()) FileResTh();
    m_fileResTh->loadBlock(m_drMan->unknown1c, "/monolib/shader/shd_lgt.wishp", 0x1000, 0);
  }
  createLightShader();
}

DrShdLgtMan::~DrShdLgtMan() {
  releaseLightShader();
  m_drResFetch.clearWork();
  if (m_hybridLight != nullptr) {
    delete m_hybridLight;
    m_hybridLight = nullptr;
  }
  if (m_drShdLgtGlobalIBL != nullptr) {
    delete m_drShdLgtGlobalIBL;
    m_drShdLgtGlobalIBL = nullptr;
  }
  if (m_drShdLgtClustered != nullptr) {
    delete m_drShdLgtClustered;
    m_drShdLgtClustered = nullptr;
  }
  if (unknown10 != nullptr) {
    delete unknown10;
    unknown10 = nullptr;
  }
}

DrShdLgtHybrid *DrShdLgtMan::getHybridLight() { return m_hybridLight; }

const char *DrShdLgtMan::getDeclarationName(DECLARATION type) const { return s_DeclarationNames[type]; }

void DrShdLgtMan::renderBegin() {
  unknown42 = 0xffff;
  unknown44 = 0xffff;
  unknown48 = 0xffffffff;
  unknown40 = 1;
}

void DrShdLgtMan::beforeUpdateCate(int viewNum) { m_drShdLgtGlobalIBL->update(viewNum); }

void DrShdLgtMan::resetColorBuff(int index) {
  DrShdLgtGlobalIBL *globalIBL = m_drShdLgtGlobalIBL;
  if (globalIBL != nullptr) {
    globalIBL->resetColorBuff(index);
  }
}

void DrShdLgtMan::setupLocalIBLShader(DrShdLgtObj *obj) { grlib::CGLibCtlShader::setShader(*obj, m_drResFetch); }

void DrShdLgtMan::setupGlobalIBLShader(DrShdLgtObj *obj) { grlib::CGLibCtlShader::setShader(*obj, m_drResFetch); }

DrShdLgtObj *DrShdLgtMan::getGlobalIBLShader(GIBL_SHADER_TYPE type) { return &unknown18[1][type]; }

DrShdLgtObj *DrShdLgtMan::getComputeShader(COMP_SHADER_TYPE type) { return &unknown18[2][type]; }

void DrShdLgtMan::stockBegin() {
  m_hybridLight->stockBegin();
  m_drShdLgtClustered->stockBegin();
}

void DrShdLgtMan::stockEnd() {
  m_hybridLight->stockEnd();
  m_drShdLgtClustered->stockEnd();
}

void DrShdLgtMan::updateCate(int cate) {
  m_hybridLight->update();
  m_drShdLgtClustered->update();
}

void DrShdLgtMan::setupCate(int cate) {
  m_hybridLight->setupCate(cate);
  m_drShdLgtClustered->setupCate(cate);
}

void DrShdLgtMan::addViewInfo(int cate) {
  m_hybridLight->addViewInfo(cate);
  m_drShdLgtClustered->addViewInfo(cate);
}

void DrShdLgtMan::delViewInfo(int cate) {
  m_hybridLight->delViewInfo(cate);
  m_drShdLgtClustered->delViewInfo(cate);
  m_drShdLgtGlobalIBL->delViewInfo(cate);
}

bool DrShdLgtMan::createLightShader() {
  if (unknown10->createPacShader(m_fileResTh->m_glassBreakage, 0x3f3, true)) {
    for (s32 i = 0; i < unknown10->unknown54; i++) {
      unknown18[i] = unknown10->unknown004(i);
    }
    return true;
  }
  return false;
}

void DrShdLgtMan::setupLgtBuff() {
  if (unknown48 != 0) {
    unknown48 = 0;
    DrAPGxType::setupCullingOff();
    DrAPGxType::setupBlend(7);
    m_drMan->m_drPixlMan->selectLightRenderTarget();
  }
}

void DrShdLgtMan::renderDebugPnt(DrLightObjPnt *light) { renderDebug(RENDER_DEBUG_TYPE_UNKNOWN_0, light->m_pos, mm::Quat::identity, mm::Vec3::unit * light->unknownb4[0], light->unknown90); }

} // namespace ml
