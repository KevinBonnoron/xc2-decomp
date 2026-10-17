#include "event/object_effect.h"

#include "event/data_manager.h"
#include "event/effect_obj.h"
#include "mm_mtl/singleton.h"

namespace event {

ObjectEffect::~ObjectEffect() {
  if (mEffectObj != nullptr) {
    delete mEffectObj;
    mEffectObj = nullptr;
  }
}

void ObjectEffect::start() {}

void ObjectEffect::end() {
  if (mEffectObj != nullptr) {
    mEffectObj->end();
  }
}

mm::Vec3 ObjectEffect::getPos() const { return mEffectObj->getPos(); }

mm::Vec3 ObjectEffect::getRot() const { return mEffectObj->getRot(); }

void ObjectEffect::tail() { mEffectObj->tail(); }

void ObjectEffect::setPosAxis(const PosAxis &axis) {
  posAxis = axis;
  mEffectObj->setPos(mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(axis.getAxis(), axis.getPos().x, axis.getPos().y, axis.getPos().z));
}

void ObjectEffect::setRotAxis(const RotAxis &axis) {
  rotAxis = axis;
  const mm::Vec3 &pos = mEffectObj->getPos();
  mEffectObj->setRot(mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(axis.getAxis(), axis.getRot().x, axis.getRot().y, axis.getRot().z, pos));
}

void ObjectEffect::play(const char *name, f32 life, f32 speed, f32 skip, int prio, int offscrId) {
  mEffectObj->play(name, life, speed, skip, prio, offscrId);
  resetAttach();
}

void ObjectEffect::stop() { mEffectObj->stop(); }

void ObjectEffect::linerPosAxis(const PosAxis &axis, f32 frame, CV_TYPE cv) {
  posAxis = axis;
  mEffectObj->moveTo(
      mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(axis.getAxis(), axis.getPos().x, axis.getPos().y, axis.getPos().z), frame, cv);
}

void ObjectEffect::linerRotAxis(const RotAxis &axis, f32 frame, CV_TYPE cv) {
  rotAxis = axis;
  const mm::Vec3 &pos = mEffectObj->getPos();
  mEffectObj->turnTo(
      mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(axis.getAxis(), axis.getRot().x, axis.getRot().y, axis.getRot().z, pos), frame, cv);
}

void ObjectEffect::setScale(const mm::Vec3 &scale) { mEffectObj->setScale(scale); }

mm::Vec3 ObjectEffect::getScale() const { return mEffectObj->getScale(); }

void ObjectEffect::setColor(const mm::Col4 &color) { mEffectObj->setColor(color); }

void ObjectEffect::linerColor(const mm::Col4 &color, f32 frame, CV_TYPE cv) { mEffectObj->colorTo(color, frame, cv); }

mm::Col4 ObjectEffect::getColor() const { return mEffectObj->getColor(); }

void ObjectEffect::setCaster(IAttachActor *caster) {
  mEffectObj->setCaster(caster);
  this->caster = caster;
  mount = nullptr;
}

void ObjectEffect::setMount(IAttachActor *mount, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type) {
  mEffectObj->setMount(mount, bone, offset, isRotate, type);
  caster = nullptr;
  this->mount = mount;
  mountBone = bone;
  mountOffset = offset;
  isMountRotate = isRotate;
  attachType = type;
}

size_t ObjectEffect::getEffCount() const { return mEffectObj->getEffCount(); }

} // namespace event
