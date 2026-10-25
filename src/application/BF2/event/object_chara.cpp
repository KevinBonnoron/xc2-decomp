#include "event/object_chara.h"

#include "mm_math/mm_math.h"

#include "event/frame_manager.h"
#include "event/memory_manager.h"
#include "mm_math/mm_mat44.h"
#include "mtl/alloc_handle.h"

namespace event {

mm::Vec3 ObjectChara::getPos() const { return unknown70->getPos(); }

void ObjectChara::resetTar() { unknown70->resetTar(); }

ObjectChara::ObjectChara(const char *name) : Object(OBJTYPE_CHARA, name), unknown68(0), unknown70(nullptr) {}

ObjectChara::~ObjectChara() {
  if (unknown70 != nullptr) {
    delete unknown70;
    unknown70 = nullptr;
  }
}

void ObjectChara::createGfObj(gf::GF_OBJ_HANDLE *handle) {
  unknown70 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  unknown70->createGfObj(handle);
  unknown68 |= FLAG_CREATED;
}

void ObjectChara::createGfObj(CHARA_TYPE type, u32 id, u32 param3, u32 param4) {
  unknown70 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  unknown70->createGfObj(type, id, param3, param4);
  unknown68 |= FLAG_CREATED;
}

void ObjectChara::createModel(const char *model, u32 param2, u32 param3) {
  unknown70 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  unknown70->createModel(model, param2, param3);
  unknown68 &= ~FLAG_CREATED;
}

void ObjectChara::createGhost() {
  unknown70 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  unknown70->createGhost();
  unknown68 |= FLAG_CREATED;
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

void ObjectChara::OnManiSetRot(IManiCallback::SetParam &param) {
  mm::Vec3 euler = mm::matrixToEuler(param.matrix);
  RotAxis axis = unknowna0;
  mm::Vec3 pos = unknown70->getPos();
  f32 ofs = mm::mtl::Singleton<DataManager>::getPtr()->getRotOfsY(axis.getAxis(), pos);
  axis.set(axis.getAxis(), 0.0f, euler.y - ofs, 0.0f);
  setRotAxis(axis);
}

} // namespace event
