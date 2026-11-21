#include "event/outsider_field.h"

#include "event/cam_hands.h"
#include "event/cam_motion.h"
#include "event/cam_obj.h"
#include "event/group_manager.h"
#include "event/object_camera.h"
#include "event/object_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

OutsiderField::OutsiderField() { clear(); }

void OutsiderField::clear() {
  unknown00 = TYPE_UNKNOWN_1;
  unknown10 = mm::Vec3::zero;
  unknown20 = 0.0f;
  unknown30 = mm::Vec3::zero;
  unknown40 = 0.0f;
}

void OutsiderField::update() {
  switch (unknown00) {
  case TYPE_UNKNOWN_0:
    unknown30 = mm::Vec3::zero;
    unknown40 = 0.0f;
    break;
  case TYPE_UNKNOWN_1:
    unknown30 = mm::mtl::Singleton<GroupManager>::getPtr()->unknown001();
    unknown40 = 0.0f;
    if (0.0f < mm::mtl::Singleton<GroupManager>::getPtr()->unknown002()) {
      unknown40 = mm::mtl::Singleton<GroupManager>::getPtr()->unknown002() + 2.5f;
    }
    break;
  case TYPE_UNKNOWN_2:
    unknown30 = mm::mtl::Singleton<GroupManager>::getPtr()->unknown001();
    unknown40 = unknown20;
    break;
  case TYPE_UNKNOWN_3:
    unknown30 = unknown10;
    unknown40 = unknown20;
    break;
  case TYPE_UNKNOWN_4: {
    if (mm::mtl::Singleton<ObjectManager>::getPtr()->getCameraCount() == 0) {
      return;
    }
    // The game stores the group position (0x71000e6c4c) and overwrites it with the camera position below (statement the code holds).
    unknown30 = mm::mtl::Singleton<GroupManager>::getPtr()->unknown001();
    if ((mm::mtl::Singleton<ObjectManager>::getPtr()->getCamera(0)->getCamObj()->unknown005()->unknown001() & CamMotion::FLAG_UNKNOWN_1) != 0) {
      unknown30 = mm::mtl::Singleton<ObjectManager>::getPtr()->getCamera(0)->getCamObj()->unknown005()->getPos();
    } else {
      unknown30 = mm::mtl::Singleton<ObjectManager>::getPtr()->getCamera(0)->getCamObj()->getHands()->getPos();
    }
    unknown40 = unknown20;
    break;
  }
  }
}

void OutsiderField::setField(TYPE type, const mm::Vec3 &pos, f32 radius) {
  unknown00 = type;
  unknown10 = pos;
  unknown20 = radius;
}

bool OutsiderField::isInside(const mm::Vec3 &pos) const {
  if (unknown00 < TYPE_UNKNOWN_1) {
    return false;
  }
  if (unknown40 <= 0.0f) {
    return false;
  }
  f32 distanceX = unknown30.x - pos.x;
  f32 distanceZ = unknown30.z - pos.z;
  f32 squaredX = distanceX * distanceX;
  f32 squaredZ = distanceZ * distanceZ;
  f32 squaredRadius = unknown40 * unknown40;
  return squaredX + squaredZ < squaredRadius;
}

} // namespace event
