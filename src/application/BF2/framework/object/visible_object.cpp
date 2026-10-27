#include "framework/object/visible_object.h"

#include "fw/fw_transform.h"
#include "scn/scn_obj_acc.h"

namespace fw {

void VisibleObject::update() {
  if (unknown30 != nullptr && unknown28.get() != nullptr) {
    mm::Vec3 position = unknown28->unknown40.unknown00;
    position += unknown40;
    ml::ScnObjAccGpuCheck gpuCheck(unknown30);
    gpuCheck.setPos(position, 10.0f);
  }
}

bool VisibleObject::isRender() const {
  if (unknown30 != nullptr) {
    ml::ScnObjAccGpuCheck gpuCheck(unknown30);
    return gpuCheck.isRender();
  }

  return false;
}

} // namespace fw
