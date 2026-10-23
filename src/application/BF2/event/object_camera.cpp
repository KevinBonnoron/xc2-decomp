#include "event/object_camera.h"

#include "event/cam_hands.h"
#include "event/cam_motion.h"
#include "event/cam_obj.h"

namespace event {

const char *ObjectCamera::getCutName() const { return mCutName.c_str(); }

void ObjectCamera::start() {}

void ObjectCamera::end() {
  if (mCamObj != nullptr)
    mCamObj->end();
}

void ObjectCamera::tail() { mCamObj->tail(); }

void ObjectCamera::playMotion(const char *name, const mm::Vec3 &offset) { mCamObj->activateMotion()->play(name, offset); }

void ObjectCamera::stopMotion() { mCamObj->activateMotion()->stop(); }

void ObjectCamera::setPosAxis(const PosAxis &axis, CV_TYPE cv) {
  posAxis = axis;
  posAxes.clear();
  posAxes.push_back(axis);
  mCamObj->activateHands()->setPos(axis, cv);
}

void ObjectCamera::movePosAxis(const PosAxis &axis, f32 frame, CV_TYPE cv) {
  posAxes.push_back(axis);
  mCamObj->activateHands()->addAnmPos(frame, axis, cv);
}

mm::Vec3 ObjectCamera::getPos() const { return mCamObj->getPos(); }

void ObjectCamera::setTarAxis(const TarAxis &axis, CV_TYPE cv) {
  tarAxis = axis;
  tarAxes.clear();
  tarAxes.push_back(axis);
  mCamObj->activateHands()->setTar(axis, cv);
}

void ObjectCamera::moveTarAxis(const TarAxis &axis, f32 frame, CV_TYPE cv) {
  tarAxes.push_back(axis);
  mCamObj->activateHands()->addAnmTar(frame, axis, cv);
}

mm::Vec3 ObjectCamera::getTar() const { return mCamObj->getTarget(); }

void ObjectCamera::setFov(f32 fov, CV_TYPE cv) { mCamObj->activateHands()->setFov(fov, cv); }

void ObjectCamera::moveFov(f32 fov, f32 frame, CV_TYPE cv) { mCamObj->activateHands()->addAnmFov(frame, fov, cv); }

f32 ObjectCamera::getFov() const { return mCamObj->getFov(); }

void ObjectCamera::setRotZ(f32 rotZ, CV_TYPE cv) { mCamObj->activateHands()->setRotZ(rotZ, cv); }

void ObjectCamera::moveRotZ(f32 rotZ, f32 frame, CV_TYPE cv) { mCamObj->activateHands()->addAnmRotZ(frame, rotZ, cv); }

f32 ObjectCamera::getRotZ() const { return mCamObj->getRoll(); }

void ObjectCamera::setCutName(const char *name) { mCutName = name; }

void ObjectCamera::followPos(bool isFollow) { mCamObj->activateHands()->followPos(isFollow); }

bool ObjectCamera::isFollowPos() const { return mCamObj->activateHands()->isFollowPos(); }

void ObjectCamera::followTar(bool isFollow) { mCamObj->activateHands()->followTar(isFollow); }

bool ObjectCamera::isFollowTar() const { return mCamObj->activateHands()->isFollowTar(); }

bool ObjectCamera::OnBouRectSelect(const IBouCallback::SelectParam &param) { return false; }

} // namespace event
