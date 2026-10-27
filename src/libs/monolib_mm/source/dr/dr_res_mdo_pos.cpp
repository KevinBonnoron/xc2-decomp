#include "dr/dr_res_mdo_pos.h"

#include "dr/dr_calc_clip_work_view_plane.h"
#include <new>

#include "dr/dr_calc_view_work.h"
#include "dr/dr_res_mdo_pos_add_list.h"
#include "mm_math/mm_vec3.h"

namespace ml {

DrResMdoPos::DrResMdoPos() : unknown00(nullptr), unknown08(nullptr), unknown1e(0), unknown21(0), unknown22(0xff) {}

DrResMdoPos::DrResMdoPos(const MdsPosKeepData *keepData) : unknown00(nullptr), unknown08(keepData), unknown1e(0), unknown21(0), unknown22(0xff) {}

void DrResMdoPos::copy(DrResMdoPos *source) {
  unknown1e = 0;
  unknown18 = source->unknown18;
  unknown08 = source->unknown08;
  unknown21 = source->unknown21;
  unknown22 = source->unknown22;
}

DrResMdoPos::~DrResMdoPos() {
  if (unknown00 != nullptr) {
    unknown00->unknown28 = nullptr;
    unknown00 = nullptr;
  }
}

void DrResMdoPos::release() {
  if (unknown00 != nullptr) {
    unknown00->unknown28 = nullptr;
    unknown00 = nullptr;
  }
}

bool DrResMdoPos::clipTest(DrCalcViewWork *viewWork, const mm::Vec3 &position, f32 radius) {
  const mm::Vec3 &viewPos = viewWork->unknown400;
  f32 dx = viewPos.x - position.x;
  f32 dy = viewPos.y - position.y;
  f32 dz = viewPos.z - position.z;
  if (dx * dx + dy * dy + dz * dz > radius * radius && !viewWork->unknown4e0.clipTest(position, radius)) {
    return false;
  }
  return true;
}

void DrResMdoPos::setAddAlphaCnt(int count) {
  int value = unknown21 + count;
  if (value > 0xff) {
    value = -1;
  }
  unknown21 = value;
}

bool DrResMdoPos::setSubAlphaCnt(int count) {
  int value = unknown21 - count;
  int clamped = value > 0 ? value : 0;
  bool result = value >= 0;
  unknown21 = clamped;
  return result;
}

int DrResMdoPosAddList::createBuffSize() { return 4000; }

int DrResMdoPosAddList::setupBuff(u8 *buffer) {
  unknown00 = reinterpret_cast<DrResMdoPos *>(buffer);
  unknown08 = 0;
  for (int i = 0; i < 100; i++) {
    new (&unknown00[i]) DrResMdoPos();
  }
  return 4000;
}

void DrResMdoPosAddList::release() {
  for (int i = 0; i < 100; i++) {
    unknown00[i].release();
  }
}

void DrResMdoPosAddList::begin() { unknown08 = 0; }

DrResMdoPos *DrResMdoPosAddList::createAdd() {
  if (unknown08 >= 100) {
    return nullptr;
  }
  return &unknown00[unknown08++];
}

} // namespace ml
