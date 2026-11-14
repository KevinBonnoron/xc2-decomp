#include "event/object_camera.h"

#include <math.h>

#include "event/cam_hands.h"
#include "event/cam_manager.h"
#include "event/cam_motion.h"
#include "event/cam_obj.h"
#include "event/debug_manager.h"
#include "event/frame_manager.h"
#include "event/object_util.h"
#include "event/seq_info.h"
#include "event/seq_manager.h"
#include "ml/dev_graph.h"
#include "mm_mtl/singleton.h"

namespace event {

ObjectCamera::ObjectCamera(const char *name, u32 id) : Object(OBJTYPE_UNKNOWN_3, name), unknown68(nullptr), unknown70(id), unknown4e0(0), unknown4e4(0) {
  unknown68 = mm::mtl::Singleton<CamManager>::getPtr()->createCam(id);
  unknown80 = PosAxis(PosAxis::AXIS_UNKNOWN_1, unknown68->getPos());
  unknown2b0 = TarAxis(TarAxis::AXIS_UNKNOWN_1, unknown68->getTarget());
}

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

void ObjectCamera::update() {
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  unknown68->update(info);
  if (unknown70 == 0 && mm::mtl::Singleton<DebugManager>::getPtr()->isSyncFreeCam() && mm::mtl::Singleton<CamManager>::getPtr()->isFreeCam()) {
    updateSyncFreeCam();
  }
}

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

void ObjectCamera::render(const mm::Col4 &color) { mm::mtl::Singleton<SeqManager>::getPtr(); }

void ObjectCamera::OnManiRender(IManiCallback::RenderParam &param) { mm::mtl::Singleton<SeqManager>::getPtr(); }

bool ObjectCamera::isFollowTar() const { return unknown68->activateHands()->isFollowTar(); }

bool ObjectCamera::OnBouRectSelect(const IBouCallback::SelectParam &param) { return false; }

void ObjectCamera::OnBouRender(const IBouCallback::RenderParam &param) {
  if (static_cast<int>(mm::mtl::Singleton<SeqManager>::getPtr()->unknown001().unknown54) < 3 && unknown70 == 0) {
    int x = ml::DevGraph::getRootWidth() - 415;
    const mm::Vec3 &pos = unknown68->getPos();
    const mm::Vec3 &target = unknown68->getTarget();
    mm::Vec3 rot = unknown68->getRot();
    ObjectUtil::drawCameraInfo(x, 120, pos, target, rot, unknown68->getFov(), unknown68->isFocal());
  }
}

mm::Vec3 ObjectCamera::calcRot() const {
  mm::Vec3 tar = getTar();
  mm::Vec3 pos = getPos();
  f32 dx = tar.x - pos.x;
  f32 dy = tar.y - pos.y;
  f32 dz = tar.z - pos.z;
  mm::Vec3 rot;
  rot.y = -atan2f(dx, -dz);
  rot.x = atan2f(dy, sqrtf(dx * dx + dz * dz));
  rot.z = unknown68->getRoll();
  return rot;
}

} // namespace event
