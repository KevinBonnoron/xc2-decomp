#include "dr/dr_shd_lgt_global_ibl.h"

#include "dr/dr_light_obj_global_ibl.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/shd_util.h"
#include "types.h"

namespace ml {

namespace _dr_shd_lgt_glb_ibl {

bool CompareByPriority(const DrLightObjGlobalIBL *a, const DrLightObjGlobalIBL *b) {
  u32 priorityA = a->getPriority();
  u32 priorityB = b->getPriority();
  return priorityA > priorityB;
}

} // namespace _dr_shd_lgt_glb_ibl

void DrShdLgtGlobalIBL::delViewInfo(int viewNum) {}

void DrShdLgtGlobalIBL::resetColorBuff(int index) {
  if (unknown00->unknown120[index]->unknownfe4 == 3) {
    unknown10[index].unknown2050 = true;
  }
}

bool DrShdLgtGlobalIBL::isEnable() const { return unknown10[unknown00->unknown1c98].unknown2c > 0; }

void DrShdLgtGlobalIBL::setUniformBlock(u32 index) const { unknown10[unknown00->unknown1c98].unknown2048->setUniformBlock(index); }

void DrShdLgtGlobalIBL::setStorageBuffer(u32 index) const { unknown10[unknown00->unknown1c98].unknown2048->setStorageBuffer(index); }

const mm::Mat44 &DrShdLgtGlobalIBL::getSHMatrix(u32 row, u32 column) const {
  const unknown001 &view = unknown10[unknown00->unknown1c98];
  return view.unknown340[row * 3 + column];
}

void DrShdLgtGlobalIBL::updateUB_ShMatrixList(u8 *work, int viewNum) { grlib::ShdMat44TransposeMat44Array(reinterpret_cast<f32 *>(work), unknown10[viewNum].unknown340, 0x60); }

} // namespace ml
