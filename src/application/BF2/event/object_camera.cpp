#include "event/object_camera.h"

#include "event/cam_hands.h"
#include "event/cam_manager.h"
#include "event/cam_motion.h"
#include "event/cam_obj.h"
#include "mm_mtl/singleton.h"

namespace event {

ObjectCamera::~ObjectCamera() {
  mm::mtl::Singleton<CamManager>::getPtr()->destroyCam(unknown68);
  unknown68 = nullptr;
}

const char *ObjectCamera::getCutName() const { return m_cutName.c_str(); }

void ObjectCamera::start() {}

void ObjectCamera::end() {
  if (unknown68 != nullptr)
    unknown68->end();
}

void ObjectCamera::tail() { unknown68->tail(); }

void ObjectCamera::playMotion(const char *name, const mm::Vec3 &offset) { unknown68->activateMotion()->play(name, offset); }

void ObjectCamera::stopMotion() { unknown68->activateMotion()->stop(); }

void ObjectCamera::setPosAxis(const PosAxis &axis, CV_TYPE cv) {
  unknown80 = axis;
  unknowna0.clear();
  unknowna0.push_back(axis);
  unknown68->activateHands()->setPos(axis, cv);
}

void ObjectCamera::movePosAxis(const PosAxis &axis, f32 frame, CV_TYPE cv) {
  unknowna0.push_back(axis);
  unknown68->activateHands()->addAnmPos(frame, axis, cv);
}

mm::Vec3 ObjectCamera::getPos() const { return unknown68->getPos(); }

void ObjectCamera::setTarAxis(const TarAxis &axis, CV_TYPE cv) {
  unknown2b0 = axis;
  unknown2d0.clear();
  unknown2d0.push_back(axis);
  unknown68->activateHands()->setTar(axis, cv);
}

void ObjectCamera::moveTarAxis(const TarAxis &axis, f32 frame, CV_TYPE cv) {
  unknown2d0.push_back(axis);
  unknown68->activateHands()->addAnmTar(frame, axis, cv);
}

mm::Vec3 ObjectCamera::getTar() const { return unknown68->getTarget(); }

void ObjectCamera::setFov(f32 fov, CV_TYPE cv) { unknown68->activateHands()->setFov(fov, cv); }

void ObjectCamera::moveFov(f32 fov, f32 frame, CV_TYPE cv) { unknown68->activateHands()->addAnmFov(frame, fov, cv); }

f32 ObjectCamera::getFov() const { return unknown68->getFov(); }

void ObjectCamera::setRotZ(f32 rotZ, CV_TYPE cv) { unknown68->activateHands()->setRotZ(rotZ, cv); }

void ObjectCamera::moveRotZ(f32 rotZ, f32 frame, CV_TYPE cv) { unknown68->activateHands()->addAnmRotZ(frame, rotZ, cv); }

f32 ObjectCamera::getRotZ() const { return unknown68->getRoll(); }

void ObjectCamera::setCutName(const char *name) { m_cutName = name; }

void ObjectCamera::followPos(bool isFollow) { unknown68->activateHands()->followPos(isFollow); }

bool ObjectCamera::isFollowPos() const { return unknown68->activateHands()->isFollowPos(); }

void ObjectCamera::followTar(bool isFollow) { unknown68->activateHands()->followTar(isFollow); }

bool ObjectCamera::isFollowTar() const { return unknown68->activateHands()->isFollowTar(); }

bool ObjectCamera::OnBouRectSelect(const IBouCallback::SelectParam &param) { return false; }

} // namespace event
