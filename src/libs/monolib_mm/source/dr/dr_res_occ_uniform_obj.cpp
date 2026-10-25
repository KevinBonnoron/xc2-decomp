#include "dr/dr_res_occ_uniform_obj.h"

#include "dr/dr_man.h"
#include "mm_math/mm_mat44.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

DrResOccUniformObj::DrResOccUniformObj(DrMan *drMan, int max) : unknown00(max), unknown04(0), m_buffer(nullptr) {
  int size = max * sizeof(mm::Mat44);
  m_buffer = mtl::MemManager::allocate(drMan->unknown14, size, 0x10, false, "no name", 0);
  unknown10 = static_cast<mm::Mat44 *>(m_buffer);
}

DrResOccUniformObj::~DrResOccUniformObj() {
  if (m_buffer != nullptr) {
    mtl::MemManager::deallocate(m_buffer, 0, false);
    m_buffer = nullptr;
  }
}

void DrResOccUniformObj::begin() { unknown04 = 0; }

void DrResOccUniformObj::end() {}

mm::Mat44 *DrResOccUniformObj::getMatTbl(int index) { return unknown10 + index; }

mm::Mat44 *DrResOccUniformObj::getMatTbl() {
  if (unknown00 > unknown04) {
    return &unknown10[unknown04++];
  }
  return nullptr;
}

} // namespace ml
