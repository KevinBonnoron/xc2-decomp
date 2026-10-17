#include "event/pos_axis.h"

#include "event/chara_obj.h"
#include "event/data_manager.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "event/text_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

PosAxis::PosAxis() : mAxis(1), mPos(mm::Vec3::zero) {}

PosAxis::PosAxis(u32 axis, f32 x, f32 y, f32 z) : mAxis(axis), mPos(x, y, z) {}

PosAxis::PosAxis(u32 axis, const mm::Vec3 &pos) : mAxis(axis), mPos(pos) {}

void PosAxis::set(u32 axis, f32 x, f32 y, f32 z) {
  mAxis = axis;
  mPos.x = x;
  mPos.y = y;
  mPos.z = z;
}

void PosAxis::set(u32 axis, const mm::Vec3 &pos) {
  mAxis = axis;
  mPos = pos;
}

mm::Vec3 PosAxis::calcPos() const { return mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(mAxis, mPos.x, mPos.y, mPos.z); }

mm::Vec3 DataManager::axis2pos(u32 axis, f32 x, f32 y, f32 z) {
  if (axis < PosAxis::AXIS_CHARA) {
    return transformPos(getPosAxis(axis), x, y, z);
  }
  if (axis < getCharaNum() + PosAxis::AXIS_CHARA) {
    return transformPos(getPosAxis(axis), x, y, z);
  }
  return mm::Vec3(x, y, z);
}

mm::Mat44 PosAxis::calcOrigMat() const { return mm::mtl::Singleton<DataManager>::getPtr()->getPosAxis(mAxis); }

mm::Mat44 DataManager::getPosAxis(u32 axis) {
  if (axis < PosAxis::AXIS_CHARA) {
    mm::Mat44 mat = mm::Mat44::identity;
    switch (axis) {
    case PosAxis::AXIS_NONE:
      mat = mCurrent->offsetMatrix;
      break;
    case PosAxis::AXIS_POS:
      mat = mCurrent->offsetMatrix;
      break;
    case PosAxis::AXIS_POS_GLOBAL:
      mat = mCurrent->keepMatrix;
      break;
    case PosAxis::AXIS_SAY:
      if (mm::mtl::Singleton<TextManager>::getPtr()->getTalker() != nullptr) {
        ObjectChara *chara =
            mm::mtl::Singleton<ObjectManager>::getPtr()->searchByHandle(mm::mtl::Singleton<TextManager>::getPtr()->getTalker()->getHandle());
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

const char *PosAxis::getOrigName() const { return mm::mtl::Singleton<DataManager>::getPtr()->getPosName(mAxis); }

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
