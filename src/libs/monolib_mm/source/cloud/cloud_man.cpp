#include "cloud/cloud_man.h"

#include "cloud/cloud_calc_params.h"
#include "cloud/cloud_data_man.h"
#include "cloud/cloud_obj_man.h"
#include "cloud/cloud_obj_reduction.h"
#include "cloud/cloud_shader_man.h"
#include "cloud/cloud_texture_man.h"
#include "cloud/cloud_vertex_man.h"
#include "dr/dr_draw_work_info.h"
#include "dr/dr_man.h"
#include "dr/dr_mdo_zsort.h"
#include "dr/dr_res_mdo_sort.h"
#include "mm_math/mm_col3.h"
#include "mtl/mem_manager.h"

namespace cloud {

CloudMan::CloudMan(ml::Scn *scn, mtl::ALLOC_HANDLE handle, u32 size) : m_scn(scn), _28(0) {
  s_nDblDfIdx = 0;
  s_nDblStIdx = 1;
  m_memTop = mtl::ALLOC_HANDLE();
  m_memData = mtl::ALLOC_HANDLE();
  m_memWork = mtl::ALLOC_HANDLE();
  m_memTop = mtl::MemManager::create(handle, size + 0x1000, "CloudTop", false);
  m_memData = mtl::MemManager::create(m_memTop, 0x380000, "CloudData", false);
  u32 workSize = size - 0x380000;
  m_memWork = mtl::MemManager::create(m_memTop, workSize, "CloudWork", false);
  m_isSetupRequest = true;
  m_sortCloud = nullptr;
  m_textureMan = nullptr;
  m_shaderMan = nullptr;
  m_vertexMan = nullptr;
  m_speed = 1.0f;
  _64 = 1.0f;
  m_dataMan = new (m_memWork) CloudDataMan();
  m_objMan = new (m_memWork) CloudObjMan();
  m_sortCloud = new (m_memWork) ml::DrResMdoSortCloud(this);
}

CloudMan::~CloudMan() {
  if (m_sortCloud != nullptr) {
    delete m_sortCloud;
    m_sortCloud = nullptr;
  }

  if (m_objMan != nullptr) {
    delete m_objMan;
    m_objMan = nullptr;
  }

  if (m_vertexMan != nullptr) {
    delete m_vertexMan;
    m_vertexMan = nullptr;
  }

  if (m_textureMan != nullptr) {
    delete m_textureMan;
    m_textureMan = nullptr;
  }

  if (m_shaderMan != nullptr) {
    delete m_shaderMan;
    m_shaderMan = nullptr;
  }

  if (m_dataMan != nullptr) {
    delete m_dataMan;
    m_dataMan = nullptr;
  }

  if (m_memData.isValid()) {
    mtl::MemManager::erase(m_memData);
    m_memData = mtl::ALLOC_HANDLE();
  }

  if (m_memWork.isValid()) {
    mtl::MemManager::erase(m_memWork);
    m_memWork = mtl::ALLOC_HANDLE();
  }

  if (m_memTop.isValid()) {
    mtl::MemManager::erase(m_memTop);
    m_memTop = mtl::ALLOC_HANDLE();
  }
}

void CloudMan::dispOn(bool isOn) { m_objMan->m_isDisp = isOn; }

void CloudMan::planeOn(bool isOn) { m_objMan->m_isPlane = isOn; }

void CloudMan::planeSideOn(bool isOn) { m_objMan->m_isPlaneSide = isOn; }

void CloudMan::skyOn(bool isOn) { m_objMan->m_isSky = isOn; }

void CloudMan::mdlOn(bool isOn) { m_objMan->m_isMdl = isOn; }

void CloudMan::setHeight(f32 height) { m_objMan->m_calcParams->m_height = height; }

f32 CloudMan::getHeight() const { return m_objMan->m_calcParams->m_height; }

bool CloudMan::isHole() const { return m_objMan->m_isHole; }

void CloudMan::setCldNum(u32 cldNum) {
  if (cldNum < 2) {
    m_objMan->m_calcParams->m_cldNum = cldNum;
  }
}

u32 CloudMan::getCldNum() const { return m_objMan->m_calcParams->m_cldNum; }

void CloudMan::beginSetup() {
  if (!m_dataMan->isReadOk()) {
    return;
  }

  m_isSetupRequest = false;
  m_vertexMan = new (m_memWork) CloudVertexMan();
  m_textureMan = new (m_memWork) CloudTextureMan();
  m_shaderMan = new (m_memWork) CloudShaderMan();
  m_shaderMan->createShader();
  m_textureMan->createTexture();
  m_objMan->creataFastSetup();
}

void CloudMan::begin(f32 speed) {
  m_speed = speed;
  if (m_isSetupRequest) {
    beginSetup();
  } else {
    m_shaderMan->update();
  }
}

void CloudMan::end() {}

void CloudMan::apply(const ml::IDrDrawWorkInfo *workInfo, ml::DrMdoZSortMan *sortMan) {
  if (!m_isSetupRequest && workInfo->m_loop == 0 && m_objMan->update(workInfo) && m_objMan->isRender()) {
    sortMan->setViewCloud(m_sortCloud);
  }
}

void CloudMan::alphaRender(const ml::IDrDrawWorkInfo *workInfo) {
  m_objMan->alphaRender(workInfo);
  ml::DrMan::getIns()->setAlphaRenderTarget();
}

void CloudMan::finalRender(const ml::IDrDrawWorkInfo *workInfo) {
  if (!m_isSetupRequest) {
    m_objMan->isRender();
  }
}

void CloudMan::tail() {
  s_nDblDfIdx = 1 - s_nDblDfIdx;
  s_nDblStIdx = 1 - s_nDblStIdx;
}

void CloudMan::getPixelMem(u32 &size, u32 width, u32 height) { CloudObjReduction::getPixelMem(size, width, height); }

const mm::Col3 &CloudMan::getPlaneCol(u32 index) const {
  if (index == 0) {
    return m_objMan->m_calcParams->m_planeCols[0];
  }

  return m_objMan->m_calcParams->m_planeCols[1];
}

void CloudMan::openDebugWindow(ml::WinProc *window) {}

} // namespace cloud
