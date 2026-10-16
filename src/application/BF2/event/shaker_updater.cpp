#include "event/shaker_updater.h"

#include "event/cmd_param.h"
#include "event/cmd_variable.h"
#include "mm_math/mm_vec3.h"

namespace event {

ShakerUpdater::ShakerUpdater() {}

void ShakerUpdater::clear() { queue.clear(); }

void ShakerUpdater::update() { queue.update(); }

void ShakerUpdater::reserve(const mm::Vec3 &pos, const mm::Vec3 &rot) {
  CmdParam param;
  param.val(0).setF32(pos.x);
  param.val(1).setF32(pos.y);
  param.val(2).setF32(pos.z);
  param.val(3).setF32(rot.x);
  param.val(4).setF32(rot.y);
  param.val(5).setF32(rot.z);
  queue.push_back(&cmd, param);
}

} // namespace event
