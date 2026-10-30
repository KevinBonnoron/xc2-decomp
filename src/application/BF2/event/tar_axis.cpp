#include "event/tar_axis.h"

#include "event/chara_obj.h"
#include "event/data_manager.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "event/text_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

TarAxis::TarAxis() : unknown08(1), unknown10(mm::Vec3::zero) {}

TarAxis::TarAxis(u32 axis, f32 x, f32 y, f32 z) : unknown08(axis), unknown10(x, y, z) {}

TarAxis::TarAxis(u32 axis, const mm::Vec3 &tar) : unknown08(axis), unknown10(tar) {}

void TarAxis::set(u32 axis, f32 x, f32 y, f32 z) {
  unknown08 = axis;
  unknown10.x = x;
  unknown10.y = y;
  unknown10.z = z;
}

void TarAxis::set(u32 axis, const mm::Vec3 &tar) {
  unknown08 = axis;
  unknown10 = tar;
}

mm::Vec3 TarAxis::calcTar(const mm::Vec3 &pos) const { return mm::mtl::Singleton<DataManager>::getPtr()->axis2tar(unknown08, unknown10.x, unknown10.y, unknown10.z, pos); }

mm::Vec3 DataManager::axis2tar(u32 axis, f32 x, f32 y, f32 z, const mm::Vec3 &pos) {
  if (axis < TarAxis::AXIS_CHARA) {
    switch (axis) {
    case TarAxis::AXIS_ANGLE:
      return unknown003(x, unknown120->unknown110.y + y, pos);
    case TarAxis::AXIS_ANGLE_GLOBAL:
      return unknown003(x, unknown120->unknown160.y + y, pos);
    default:
      return unknown002(getTarAxis(axis), x, y, z);
    }
  }
  if (axis < getCharaNum() + TarAxis::AXIS_CHARA) {
    return unknown002(getTarAxis(axis), x, y, z);
  }
  return mm::Vec3(x, y, z);
}

mm::Mat44 TarAxis::calcOrigMat() const { return mm::mtl::Singleton<DataManager>::getPtr()->getTarAxis(unknown08); }

mm::Mat44 DataManager::getTarAxis(u32 axis) {
  if (axis < TarAxis::AXIS_CHARA) {
    mm::Mat44 mat = mm::Mat44::identity;
    switch (axis) {
    case TarAxis::AXIS_NONE:
      mat = mm::Mat44::identity;
      break;
    case TarAxis::AXIS_POS:
      mat = unknown120->unknownd0;
      break;
    case TarAxis::AXIS_POS_GLOBAL:
      mat = unknown120->unknown120;
      break;
    case TarAxis::AXIS_SAY:
      if (mm::mtl::Singleton<TextManager>::getPtr()->getTalker() != nullptr) {
        ObjectChara *chara = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByHandle(mm::mtl::Singleton<TextManager>::getPtr()->getTalker()->getHandle());
        if (chara != nullptr) {
          mat.setRotXYZ(chara->getRot());
          mat.setTrans(chara->getPos());
        }
      }
      break;
    case TarAxis::AXIS_ANGLE:
      mat.setRotY(unknown120->unknown110.y);
      break;
    case TarAxis::AXIS_ANGLE_GLOBAL:
      mat.setRotY(unknown120->unknown160.y);
      break;
    }
    return mat;
  }
  if (axis < getCharaNum() + TarAxis::AXIS_CHARA) {
    ObjectChara *chara = mm::mtl::Singleton<ObjectManager>::getPtr()->getChara(axis - TarAxis::AXIS_CHARA);
    mm::Mat44 mat;
    mat.setRotXYZ(chara->getRot());
    mat.setTrans(chara->getPos() + mm::Vec3(0.0f, chara->getEyeOffset(), 0.0f));
    return mat;
  }
  return mm::Mat44::identity;
}

const char *TarAxis::getOrigName() const { return mm::mtl::Singleton<DataManager>::getPtr()->getTarName(unknown08); }

inline const char *DataManager::getTarName(u32 axis) {
  if (axis < TarAxis::AXIS_CHARA) {
    switch (axis) {
    case TarAxis::AXIS_NONE:
      return "";
    case TarAxis::AXIS_POS:
      return "POS";
    case TarAxis::AXIS_POS_GLOBAL:
      return "POS_G";
    case TarAxis::AXIS_SAY:
      return "SAY";
    case TarAxis::AXIS_ANGLE:
      return "ANG";
    case TarAxis::AXIS_ANGLE_GLOBAL:
      return "ANG_G";
    }
  }
  if (axis < getCharaNum() + TarAxis::AXIS_CHARA) {
    return mm::mtl::Singleton<ObjectManager>::getPtr()->getChara(axis - TarAxis::AXIS_CHARA)->getName();
  }
  return "";
}

} // namespace event
