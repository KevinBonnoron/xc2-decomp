#include "event/rot_axis.h"

#include <math.h>

#include "event/chara_obj.h"
#include "event/data_manager.h"
#include "event/object_chara.h"
#include "event/object_list.h"
#include "event/object_manager.h"
#include "event/text_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

RotAxis::RotAxis() : unknown08(1), unknown10(mm::Vec3::zero) {}

RotAxis::RotAxis(u32 axis, f32 x, f32 y, f32 z) : unknown08(axis), unknown10(x, y, z) {}

RotAxis::RotAxis(u32 axis, const mm::Vec3 &rot) : unknown08(axis), unknown10(rot) {}

void RotAxis::set(u32 axis, f32 x, f32 y, f32 z) {
  unknown08 = axis;
  unknown10.x = x;
  unknown10.y = y;
  unknown10.z = z;
}

void RotAxis::set(u32 axis, const mm::Vec3 &rot) {
  unknown08 = axis;
  unknown10 = rot;
}

mm::Vec3 RotAxis::calcRot(const mm::Vec3 &pos) const { return mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(unknown08, unknown10.x, unknown10.y, unknown10.z, pos); }

mm::Vec3 DataManager::axis2rot(u32 axis, f32 x, f32 y, f32 z, const mm::Vec3 &pos) {
  if (axis < RotAxis::AXIS_CHARA) {
    return mm::Vec3(x, getRotOfsY(axis, pos) + y, z);
  }
  if (axis < getCharaNum() + RotAxis::AXIS_CHARA) {
    return mm::Vec3(x, getRotOfsY(axis, pos) + y, z);
  }
  return mm::Vec3(x, y, z);
}

f32 RotAxis::calcOrigRot(const mm::Vec3 &pos) const { return mm::mtl::Singleton<DataManager>::getPtr()->getRotOfsY(unknown08, pos); }

f32 DataManager::getRotOfsY(u32 axis, const mm::Vec3 &pos) {
  if (axis < RotAxis::AXIS_CHARA) {
    f32 rotY = 0.0f;
    switch (axis) {
    case RotAxis::AXIS_NONE:
      rotY = unknown120->unknown110.y;
      break;
    case RotAxis::AXIS_ANGLE:
      rotY = unknown120->unknown110.y;
      break;
    case RotAxis::AXIS_ANGLE_GLOBAL:
      rotY = unknown120->unknown160.y;
      break;
    case RotAxis::AXIS_SAY:
      if (mm::mtl::Singleton<TextManager>::getPtr()->getTalker() != nullptr) {
        ObjectChara *chara = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByHandle(mm::mtl::Singleton<TextManager>::getPtr()->getTalker()->getHandle());
        if (chara != nullptr) {
          rotY = chara->getRot().y;
        }
      }
      break;
    }
    return rotY;
  }
  if (axis < getCharaNum() + RotAxis::AXIS_CHARA) {
    u32 index = axis - RotAxis::AXIS_CHARA;
    ObjectChara *chara = static_cast<ObjectChara *>(mm::mtl::Singleton<ObjectManager>::getPtr()->getCurrent()->getCharaObject(index));
    mm::Vec3 charaPos = chara->getPos();
    if (charaPos.x != pos.x || charaPos.z != pos.z) {
      return atan2f(charaPos.x - pos.x, charaPos.z - pos.z);
    }
  }
  return 0.0f;
}

const char *RotAxis::getOrigName() const { return mm::mtl::Singleton<DataManager>::getPtr()->getRotName(unknown08); }

inline const char *DataManager::getRotName(u32 axis) {
  if (axis < RotAxis::AXIS_CHARA) {
    const char *name;
    switch (axis) {
    case RotAxis::AXIS_NONE:
      name = "";
      break;
    case RotAxis::AXIS_ANGLE:
      name = "ANG";
      break;
    case RotAxis::AXIS_ANGLE_GLOBAL:
      name = "ANG_G";
      break;
    case RotAxis::AXIS_SAY:
      name = "SAY";
      break;
    }
    return name;
  }
  if (axis < getCharaNum() + RotAxis::AXIS_CHARA) {
    return mm::mtl::Singleton<ObjectManager>::getPtr()->getChara(axis - RotAxis::AXIS_CHARA)->getName();
  }
  return "";
}

} // namespace event
