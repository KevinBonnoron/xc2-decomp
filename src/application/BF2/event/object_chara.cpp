#include "event/object_chara.h"

#include "mm_math/mm_math.h"

#include "event/frame_manager.h"
#include "event/memory_manager.h"
#include "mm_math/mm_mat44.h"
#include "mtl/alloc_handle.h"

namespace event {

mm::Vec3 ObjectChara::getPos() const { return mCharaObj->getPos(); }

void ObjectChara::resetTar() { mCharaObj->resetTar(); }

ObjectChara::ObjectChara(const char *name) : Object(OBJTYPE_CHARA, name), flags(0), mCharaObj(nullptr) {}

ObjectChara::~ObjectChara() {
  if (mCharaObj != nullptr) {
    delete mCharaObj;
    mCharaObj = nullptr;
  }
}

void ObjectChara::createGfObj(gf::GF_OBJ_HANDLE *handle) {
  mCharaObj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  mCharaObj->createGfObj(handle);
  flags |= FLAG_CREATED;
}

void ObjectChara::createGfObj(CHARA_TYPE type, u32 id, u32 param3, u32 param4) {
  mCharaObj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  mCharaObj->createGfObj(type, id, param3, param4);
  flags |= FLAG_CREATED;
}

void ObjectChara::createModel(const char *model, u32 param2, u32 param3) {
  mCharaObj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  mCharaObj->createModel(model, param2, param3);
  flags &= ~FLAG_CREATED;
}

void ObjectChara::createGhost() {
  mCharaObj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  mCharaObj->createGhost();
  flags |= FLAG_CREATED;
}

void ObjectChara::clear() {
  if (mCharaObj != nullptr) {
    mCharaObj->clear();
  }
}

void ObjectChara::start() {
  if (mCharaObj != nullptr) {
    mCharaObj->start();
  }
}

void ObjectChara::end() {
  if (mCharaObj != nullptr) {
    mCharaObj->end();
  }
}

void ObjectChara::update() {
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  if (mCharaObj != nullptr) {
    mCharaObj->update(info);
  }
}

bool ObjectChara::isTar() const { return mCharaObj->isTar(); }

void ObjectChara::tail() {
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  if (mCharaObj != nullptr) {
    mCharaObj->tail(info);
  }
}

bool ObjectChara::isLoading() const { return !mCharaObj->isReady(); }

void ObjectChara::linerPosAxis(const PosAxis &axis, bool isWalk, f32 frame, CV_TYPE cv) {
  posAxis = axis;
  mCharaObj->linerPos(
      mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(axis.getAxis(), axis.getPos().x, axis.getPos().y, axis.getPos().z), isWalk, frame, cv);
  mCharaObj->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
}

void ObjectChara::turnRotAxis(const RotAxis &axis, EVT_rotcvtype cv, f32 frame) {
  rotAxis = axis;
  const mm::Vec3 &pos = mCharaObj->getPosTo();
  mCharaObj->turnRot(
      mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(axis.getAxis(), axis.getRot().x, axis.getRot().y, axis.getRot().z, pos), cv, frame);
  mCharaObj->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
}

void ObjectChara::linerRotAxis(const RotAxis &axis, f32 frame, CV_TYPE cv) {
  rotAxis = axis;
  const mm::Vec3 &pos = mCharaObj->getPosTo();
  mCharaObj->linerRot(
      mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(axis.getAxis(), axis.getRot().x, axis.getRot().y, axis.getRot().z, pos), frame, cv);
  mCharaObj->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
}

mm::Vec3 ObjectChara::getTar() const { return mCharaObj->getTar(); }

f32 ObjectChara::getEyeOffset() const { return mCharaObj->getEyeOffset(); }

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
  RotAxis axis = rotAxis;
  mm::Vec3 pos = mCharaObj->getPos();
  f32 ofs = mm::mtl::Singleton<DataManager>::getPtr()->getRotOfsY(axis.getAxis(), pos);
  axis.set(axis.getAxis(), 0.0f, euler.y - ofs, 0.0f);
  setRotAxis(axis);
}

} // namespace event
