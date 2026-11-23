#include "dr/dr_calc_stm_work.h"

#include <new>

#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_vertex_man.h"
#include "grlib/cglib_texture_buffer.h"

namespace ml {

DrCalcStmWork::DrCalcStmWork() : m_texObj(nullptr), unknown08(0), m_drResMdoVertex(nullptr) {}

DrCalcStmWork::~DrCalcStmWork() { workRelease(); }

void DrCalcStmWork::workRelease() {
  texRelease();
  unknown08 = 0;
  if (m_drResMdoVertex != nullptr) {
    DrMan::get()->m_drMdlMan->m_drMdoVertexMan->releaseVertexObj(m_drResMdoVertex);
    m_drResMdoVertex = nullptr;
  }
}

int DrCalcStmWork::getWorkSize(u32 count) { return count * sizeof(grlib::CGLibTextureBuffer); }

int DrCalcStmWork::createWork(u8 *work, u32 count) {
  unknown08 = count;
  m_texObj = reinterpret_cast<grlib::CGLibTextureBuffer *>(work);
  for (int i = 0; i < unknown08; i++) {
    new (&m_texObj[i]) grlib::CGLibTextureBuffer;
  }
  return getWorkSize(count);
}

grlib::CGLibTextureBuffer *DrCalcStmWork::getTexObj(u32 index) { return &m_texObj[index]; }

void DrCalcStmWork::texRelease() {
  for (int i = 0; i < unknown08; i++) {
    m_texObj[i].release();
  }
}

} // namespace ml
