#include "event/pos_axis.h"

#include "event/chara_obj.h"
#include "event/data_manager.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "event/text_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

PosAxis::PosAxis() : unknown08(1), unknown10(mm::Vec3::zero) {}

PosAxis::PosAxis(u32 axis, f32 x, f32 y, f32 z) : unknown08(axis), unknown10(x, y, z) {}

PosAxis::PosAxis(u32 axis, const mm::Vec3 &pos) : unknown08(axis), unknown10(pos) {}

void PosAxis::set(u32 axis, f32 x, f32 y, f32 z) {
  unknown08 = axis;
  unknown10.x = x;
  unknown10.y = y;
  unknown10.z = z;
}

void PosAxis::set(u32 axis, const mm::Vec3 &pos) {
  unknown08 = axis;
  unknown10 = pos;
}

mm::Vec3 PosAxis::calcPos() const { return mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(unknown08, unknown10.x, unknown10.y, unknown10.z); }

mm::Vec3 DataManager::axis2pos(u32 axis, f32 x, f32 y, f32 z) {
  if (axis < PosAxis::AXIS_CHARA) {
    return unknown002(getPosAxis(axis), x, y, z);
  }
  if (axis < getCharaNum() + PosAxis::AXIS_CHARA) {
    return unknown002(getPosAxis(axis), x, y, z);
  }
  return mm::Vec3(x, y, z);
}

mm::Mat44 PosAxis::calcOrigMat() const { return mm::mtl::Singleton<DataManager>::getPtr()->getPosAxis(unknown08); }

mm::Mat44 DataManager::getPosAxis(u32 axis) {
  if (axis < PosAxis::AXIS_CHARA) {
    mm::Mat44 mat = mm::Mat44::identity;
    switch (axis) {
    case PosAxis::AXIS_NONE:
      mat = unknown120->unknownd0;
      break;
    case PosAxis::AXIS_POS:
      mat = unknown120->unknownd0;
      break;
    case PosAxis::AXIS_POS_GLOBAL:
      mat = unknown120->unknown120;
      break;
    case PosAxis::AXIS_SAY:
      if (mm::mtl::Singleton<TextManager>::getPtr()->getTalker() != nullptr) {
        ObjectChara *chara = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByHandle(mm::mtl::Singleton<TextManager>::getPtr()->getTalker()->getHandle());
        if (chara != nullptr) {
          mat.setRotXYZ(chara->getRot());
          mat.setTrans(chara->getPos());
        }
      }
      break;
    }
    return mat;
  }
  if (axis < getCharaNum() + PosAxis::AXIS_CHARA) {
    ObjectChara *chara = mm::mtl::Singleton<ObjectManager>::getPtr()->getChara(axis - PosAxis::AXIS_CHARA);
    mm::Mat44 mat;
    mat.setRotXYZ(chara->getRot());
    mat.setTrans(chara->getPos());
    return mat;
  }
  return mm::Mat44::identity;
}

const char *PosAxis::getOrigName() const { return mm::mtl::Singleton<DataManager>::getPtr()->getPosName(unknown08); }

inline const char *DataManager::getPosName(u32 axis) {
  if (axis < PosAxis::AXIS_CHARA) {
    switch (axis) {
    case PosAxis::AXIS_NONE:
      return "";
    case PosAxis::AXIS_POS:
      return "POS";
    case PosAxis::AXIS_POS_GLOBAL:
      return "POS_G";
    case PosAxis::AXIS_SAY:
      return "SAY";
    }
  }
  if (axis < getCharaNum() + PosAxis::AXIS_CHARA) {
    return mm::mtl::Singleton<ObjectManager>::getPtr()->getChara(axis - PosAxis::AXIS_CHARA)->getName();
  }
  return "";
}

} // namespace event
