#include "dr/dr_shd_lgt_global_ibl.h"

#include "dr/dr_light_obj_global_ibl.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/shd_util.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep
#include "types.h"
#include <string.h>

namespace ml {

namespace _dr_shd_lgt_glb_ibl {

bool CompareByPriority(const DrLightObjGlobalIBL *a, const DrLightObjGlobalIBL *b) {
  u32 priorityA = a->getPriority();
  u32 priorityB = b->getPriority();
  return priorityA > priorityB;
}

} // namespace _dr_shd_lgt_glb_ibl

DrShdLgtGlobalIBL::~DrShdLgtGlobalIBL() {
  for (int i = 0; i < 4; i++) {
    unknown001 &view = unknown10[i];
    if (view.unknown2048 != nullptr) {
      delete view.unknown2048;
      view.unknown2048 = nullptr;
    }
    view.unknown00.unknown001();
  }
}

void DrShdLgtGlobalIBL::delViewInfo(int viewNum) {}

void DrShdLgtGlobalIBL::resetColorBuff(int index) {
  if (unknown00->unknown120[index]->unknownfe4 == 3) {
    unknown10[index].unknown2050 = true;
  }
}

bool DrShdLgtGlobalIBL::isEnable() const { return unknown10[unknown00->unknown1c98].unknown00.size() > 0; }

void DrShdLgtGlobalIBL::setUniformBlock(u32 index) const { unknown10[unknown00->unknown1c98].unknown2048->setUniformBlock(index); }

void DrShdLgtGlobalIBL::setStorageBuffer(u32 index) const { unknown10[unknown00->unknown1c98].unknown2048->setStorageBuffer(index); }

const mm::Mat44 &DrShdLgtGlobalIBL::getSHMatrix(u32 row, u32 column) const {
  const unknown001 &view = unknown10[unknown00->unknown1c98];
  return view.unknown340[row * 3 + column];
}

void DrShdLgtGlobalIBL::updateUB_ShMatrixList(u8 *work, int viewNum) { grlib::ShdMat44TransposeMat44Array(reinterpret_cast<f32 *>(work), unknown10[viewNum].unknown340, 0x60); }

void DrShdLgtGlobalIBL::updateUB_ToProxySpace(u8 *work, int viewNum) {
  unknown001 &view = unknown10[viewNum];
  for (int i = 0; i < 32; i++) {
    const DrLightObjGlobalIBL *obj = view.unknown40[i].unknown10;
    grlib::ShdMat44TransposeMat44(reinterpret_cast<f32 *>(work), obj == nullptr ? mm::Mat44::identity : obj->unknown3d0);
    work += sizeof(mm::Mat44);
  }
}

void DrShdLgtGlobalIBL::getSHAverage(mm::Vec3 &average, u32 index) const {
  const unknown001 &view = unknown10[unknown00->unknown1c98];
  average.x = view.unknown340[index * 3].rows[3][3];
  average.y = view.unknown340[index * 3 + 1].rows[3][3];
  average.z = view.unknown340[index * 3 + 2].rows[3][3];
  if (average.isError()) {
    average = mm::Vec3::zero;
  }
}

void DrShdLgtGlobalIBL::update(int viewNum) {
  if (viewNum == 0 || (viewNum > 0 && unknown00->unknown059(viewNum))) {
    updateView(viewNum);
  }
}

void DrShdLgtGlobalIBL::updateUniformBlock(int viewNum) { updateUniformBlockImpl(viewNum); }

void DrShdLgtGlobalIBL::getLowestPrioritySH(mm::Mat44 &red, mm::Mat44 &green, mm::Mat44 &blue) const {
  const unknown001 &view = unknown10[unknown00->unknown1c98];
  int index = -1;
  for (DrLightObjGlobalIBL *const *it = view.unknown1b40.end(); it != view.unknown1b40.begin(); --it) {
    const unknown002 &slot = view.unknown40[0];
    if (slot.unknown10 == nullptr) {
      break;
    }
    if (slot.unknown10 == it[-1] && slot.unknown04[(slot.unknown08 + 2) % 3] != 3 && (slot.unknown04[0] == 2 || slot.unknown04[1] == 2 || slot.unknown04[2] == 2)) {
      index = slot.unknown00;
    }
  }
  if (index != -1) {
    red = view.unknown340[index * 3];
    green = view.unknown340[index * 3 + 1];
    blue = view.unknown340[index * 3 + 2];
  } else {
    memset(&red, 0, sizeof(mm::Mat44));
    memset(&green, 0, sizeof(mm::Mat44));
    memset(&blue, 0, sizeof(mm::Mat44));
  }
}

void DrShdLgtGlobalIBL::addObj(DrLightObjGlobalIBL *obj, int viewNum) { unknown10[viewNum].unknown00.push_back(obj); }

} // namespace ml

template mm::mtl::FixedList<ml::DrShdLgtGlobalIBL::SlotCandidate, 32>::iterator
    mm::mtl::FixedList<ml::DrShdLgtGlobalIBL::SlotCandidate, 32>::erase(mm::mtl::FixedList<ml::DrShdLgtGlobalIBL::SlotCandidate, 32>::iterator);
