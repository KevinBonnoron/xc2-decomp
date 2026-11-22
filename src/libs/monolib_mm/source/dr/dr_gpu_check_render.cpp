#include "dr/dr_gpu_check_render.h"

#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_vertex_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_vtx_instans.h"
#include "grlib/shd_util.h"
#include "mm_math/mm_mat44.h"

namespace ml {

DrGpuCheckRender::DrGpuCheckRender() { m_cGLibDblUniformBlock.setup(0x80); }

DrGpuCheckRender::~DrGpuCheckRender() {}

void DrGpuCheckRender::beginUpdate() {
  m_drCalcViewWork = DrMan::get()->m_drCalcMan->m_drCalcViewWork;
  unknown10 = DrMan::get()->m_drMdlMan->m_drMdoVertexMan->unknown10;
  unknown50 = unknown10->getNextInstansBuff();
  s32 offset = unknown10->unknown08;
  unknown58 = offset;
  unknown5c = offset;
  unknown64 = 1;
}

void DrGpuCheckRender::endUpdate() {
  if (unknown58 != unknown5c) {
    unknown10->unknown08 = unknown58 - unknown5c + unknown10->unknown08;
  }
}

void DrGpuCheckRender::beginRender(bool isDblDepth) {
  DrMan::get()->m_drPixlMan->depCheckBegin(isDblDepth);
  m_drCalcViewWork = DrMan::get()->m_drCalcMan->m_drCalcViewWork;
  m_drShdDataList = DrMan::get()->m_drShdMan->m_drShdDataList;
  DrShdDataObj *shader = m_drShdDataList->getSelectShdObj(8);
  unknown60 = shader->getDeclarationOfs("EFFMODE");
  m_drShdDataList->bindShdDepthCheck();
  shader->setDeclarationIdx(unknown60, 1);
  unknown64 = 1;
  shader->setupShader(0u);
  u32 staticOfs = (shader->unknown38 + shader->unknown58)->getUniformBlockOfs("U_Static");
  m_drCalcViewWork->unknown7b0.setUniformBlock(staticOfs);
  f32 *buff = static_cast<f32 *>(m_cGLibDblUniformBlock.getBuff());
  grlib::ShdMat44TransposeMat34(buff, m_drCalcViewWork->unknown40);
  grlib::ShdMat44TransposeMat44(buff + 12, m_drCalcViewWork->unknown180);
  f32 width = DrMan::get()->unknown5b8->unknown28;
  f32 height = DrMan::get()->unknown5b8->unknown2c;
  f32 invX = 1.0f / m_drCalcViewWork->unknown180.rows[0][0];
  f32 invY = 1.0f / m_drCalcViewWork->unknown180.rows[1][1];
  buff[28] = invX / width * 0.5f;
  buff[29] = invY / height * 0.5f;
  buff[30] = 0.0f;
  buff[31] = 0.0f;
  m_cGLibDblUniformBlock.updateData();
  m_cGLibDblUniformBlock.setUniformBlock((shader->unknown38 + shader->unknown58)->getUniformBlockOfs("U_Sub"));
}

void DrGpuCheckRender::endRender() { DrMan::get()->m_drPixlMan->depCheckEnd(); }

void DrGpuCheckRender::render(u32 offset, int mode) {
  if (unknown64 != mode) {
    DrShdDataObj *shader = m_drShdDataList->getSelectShdObj(8);
    shader->setDeclarationIdx(unknown60, mode);
    shader->setupShader(0u);
    if (mode == 1) {
      m_drShdDataList->bindShdDepthCheck();
    } else {
      m_drShdDataList->bindShdBoxVertex();
    }
    unknown64 = mode;
  }
  grlib::CGLibCtlVertex::setInstanceVertex(*unknown10, 16, offset, 1, 1);
  if (mode == 1) {
    m_drShdDataList->renderQuads();
  } else {
    m_drShdDataList->renderBox();
  }
}

} // namespace ml
