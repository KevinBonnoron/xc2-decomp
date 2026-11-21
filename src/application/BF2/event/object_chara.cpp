#include "event/object_chara.h"

#include <math.h>

#include "mm_math/mm_math.h"

#include "event/bou_rect.h"
#include "event/frame_manager.h"
#include "event/mani_manager.h"
#include "event/memory_manager.h"
#include "event/object_manager.h"
#include "mm_math/mm_mat44.h"
#include "mtl/alloc_handle.h"

namespace event {

mm::Vec3 ObjectChara::getPos() const { return unknown70->getPos(); }

mm::Vec3 ObjectChara::getRot() const { return unknown70->getRotTo(); }

void ObjectChara::resetTar() { unknown70->resetTar(); }

bool ObjectChara::OnBouRectSelect(const IBouCallback::SelectParam &param) {
  const BouRect *rect = param.rect;
  mm::Vec3 pos = unknown70->getPos();
  if (rect->isInside(pos)) {
    mm::mtl::Singleton<ManiManager>::getPtr()->addManipulate(this, static_cast<MANI_TYPE>(0));
    return true;
  }
  mm::mtl::Singleton<ManiManager>::getPtr()->removeManipulate(this);
  return false;
}

ObjectChara::ObjectChara(const char *name) : Object(OBJTYPE_UNKNOWN_2, name), unknown68(0), unknown70(nullptr) {}

ObjectChara::~ObjectChara() {
  if (unknown70 != nullptr) {
    delete unknown70;
    unknown70 = nullptr;
  }
}

void ObjectChara::createGfObj(gf::GF_OBJ_HANDLE *handle) {
  unknown70 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  unknown70->createGfObj(handle);
  unknown68 |= FLAG_UNKNOWN_0;
}

void ObjectChara::createGfObj(CHARA_TYPE type, u32 id, u32 param3, u32 param4) {
  unknown70 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  unknown70->createGfObj(type, id, param3, param4);
  unknown68 |= FLAG_UNKNOWN_0;
}

void ObjectChara::createModel(const char *model, u32 param2, u32 param3) {
  unknown70 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  unknown70->createModel(model, param2, param3);
  unknown68 &= ~FLAG_UNKNOWN_0;
}

void ObjectChara::createGhost() {
  unknown70 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  unknown70->createGhost();
  unknown68 |= FLAG_UNKNOWN_0;
}

void ObjectChara::clear() {
  if (unknown70 != nullptr) {
    unknown70->clear();
  }
}

void ObjectChara::start() {
  if (unknown70 != nullptr) {
    unknown70->start();
  }
}

void ObjectChara::end() {
  if (unknown70 != nullptr) {
    unknown70->end();
  }
}

void ObjectChara::update() {
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  if (unknown70 != nullptr) {
    unknown70->update(info);
  }
}

void ObjectChara::setTar(const TarAxis &axis, f32 frame, EVT_tarcvtype cv, EVT_aimtype aim, f32 weight, f32 speed) {
  unknownc0 = axis;
  unknown70->setTar(axis, frame, cv, aim, weight, speed);
}

bool ObjectChara::isTar() const { return unknown70->isTar(); }

void ObjectChara::tail() {
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  if (unknown70 != nullptr) {
    unknown70->tail(info);
  }
}

bool ObjectChara::isLoading() const { return !unknown70->isReady(); }

// The game (0x710011114c) ends with a tail call to CharaObj::mount (b at 0x710011127c), as linerPosAxis does. Without
// CharaObj::walkPos defined earlier in this unit (chara_obj.cpp) the tail call is lost (78 instructions instead of 77):
// LLVM only infers nocapture on the position argument, and so can mark the call tail, from a definition.
void ObjectChara::walkPosAxis(const PosAxis &axis, EVT_poscvtype cv, bool isRun) {
  unknown80 = axis;
  unknown70->walkPos(mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(axis.getAxis(), axis.getPos().x, axis.getPos().y, axis.getPos().z), cv, isRun);
  unknown70->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
}

void ObjectChara::linerPosAxis(const PosAxis &axis, bool isWalk, f32 frame, CV_TYPE cv) {
  unknown80 = axis;
  unknown70->linerPos(mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(axis.getAxis(), axis.getPos().x, axis.getPos().y, axis.getPos().z), isWalk, frame, cv);
  unknown70->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
}

void ObjectChara::turnRotAxis(const RotAxis &axis, EVT_rotcvtype cv, f32 frame) {
  unknowna0 = axis;
  const mm::Vec3 &pos = unknown70->getPosTo();
  unknown70->turnRot(mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(axis.getAxis(), axis.getRot().x, axis.getRot().y, axis.getRot().z, pos), cv, frame);
  unknown70->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
}

void ObjectChara::linerRotAxis(const RotAxis &axis, f32 frame, CV_TYPE cv) {
  unknowna0 = axis;
  const mm::Vec3 &pos = unknown70->getPosTo();
  unknown70->linerRot(mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(axis.getAxis(), axis.getRot().x, axis.getRot().y, axis.getRot().z, pos), frame, cv);
  unknown70->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
}

mm::Vec3 ObjectChara::getTar() const { return unknown70->getTar(); }

f32 ObjectChara::getEyeOffset() const { return unknown70->getEyeOffset(); }

mm::Mat44 ObjectChara::getMat() {
  mm::Mat44 mat;
  mat.setRotXYZ(getRot());
  mat.setTrans(getPos());
  return mat;
}

mm::Mat44 ObjectChara::getEyeMat() {
  mm::Mat44 mat;
  mat.setRotXYZ(getRot());
  mat.setTrans(getEyePos());
  return mat;
}

void ObjectChara::OnManiSetPos(IManiCallback::SetParam &param) {
  mm::Vec3 pos = param.matrix.unknown004();
  PosAxis axis = unknown80;
  pos = DataManager::unknown001(axis.calcOrigMatInv(), pos.x, pos.y, pos.z);
  axis.set(axis.getAxis(), pos);
  setPosAxis(axis);
}

void ObjectChara::OnManiSetRot(IManiCallback::SetParam &param) {
  mm::Vec3 euler = mm::matrixToEuler(param.matrix);
  RotAxis axis = unknowna0;
  mm::Vec3 pos = unknown70->getPos();
  f32 ofs = mm::mtl::Singleton<DataManager>::getPtr()->getRotOfsY(axis.getAxis(), pos);
  axis.set(axis.getAxis(), 0.0f, euler.y - ofs, 0.0f);
  setRotAxis(axis);
}

bool ObjectChara::OnManiStartRot(IManiCallback::StartParam &param) {
  mm::Vec3 pos = unknown70->getPos();
  f32 ofs = mm::mtl::Singleton<DataManager>::getPtr()->getRotOfsY(unknowna0.getAxis(), pos);
  mm::Mat44 start;
  start.setRotY(ofs);
  start.setTrans(unknown70->getPos());
  mm::Mat44 rot;
  rot.setRotY(unknown70->getRotTo().y - ofs);
  param.unknown00 = start;
  param.unknown40 = rot;
  return true;
}

// Measured forms (1.0.0: 0x71001132cc, 239 instructions): TarAxis::calcOrigMatInv is defined in this unit, so LLVM infers readonly and nocapture on its this and forwards the local axis from registers
// (a declaration only gives 238 instructions). DataManager::unknown002 takes the matrix by value: the game keeps the inverse of each branch in its own stack slot (0x80, 0x40, 0), while a const
// reference parameter or a named local matrix lets the compiler share one slot (200 instructions). The angle branch copies the axis, then writes y and x of the local axis through a non-const
// getTar(): the game stores the copied axis index and z before the calls and the two angles afterwards one field at a time (building a Vec3 and calling set() gives 240 instructions). Each branch ends
// with its own setTar (the game stores unknownc0 and loads unknown70 per branch).
void ObjectChara::OnManiSetTar(IManiCallback::SetParam &param) {
  TarAxis axis;
  u32 type = unknownc0.getAxis();
  if (type < TarAxis::AXIS_UNKNOWN_4) {
    mm::Vec3 pos = param.matrix.unknown004();
    axis = unknownc0;
    pos = DataManager::unknown002(axis.calcOrigMatInv(), pos.x, pos.y, pos.z);
    axis.set(axis.getAxis(), pos);
    setTar(axis, -1.0f, static_cast<EVT_tarcvtype>(0), static_cast<EVT_aimtype>(0), -1.0f, -1.0f);
  } else if (type < TarAxis::AXIS_UNKNOWN_6) {
    mm::Vec3 pos = param.matrix.unknown004();
    axis = unknownc0;
    pos = pos - getEyePos();
    mm::Mat44 mat = unknownc0.calcOrigMatInv();
    f32 x = mat.rows[0][0] * pos.x + mat.rows[1][0] * pos.y + mat.rows[2][0] * pos.z;
    f32 y = mat.rows[0][1] * pos.x + mat.rows[1][1] * pos.y + mat.rows[2][1] * pos.z;
    f32 z = mat.rows[0][2] * pos.x + mat.rows[1][2] * pos.y + mat.rows[2][2] * pos.z;
    axis.getTar().y = -atan2f(x, -z);
    axis.getTar().x = atan2f(y, sqrtf(x * x + z * z));
    setTar(axis, -1.0f, static_cast<EVT_tarcvtype>(0), static_cast<EVT_aimtype>(0), -1.0f, -1.0f);
  } else if (type < mm::mtl::Singleton<ObjectManager>::getPtr()->getCharaCount() + TarAxis::AXIS_UNKNOWN_6) {
    mm::Vec3 pos = param.matrix.unknown004();
    axis = unknownc0;
    pos = DataManager::unknown002(axis.calcOrigMatInv(), pos.x, pos.y, pos.z);
    axis.set(axis.getAxis(), pos);
    setTar(axis, -1.0f, static_cast<EVT_tarcvtype>(0), static_cast<EVT_aimtype>(0), -1.0f, -1.0f);
  }
}

} // namespace event
