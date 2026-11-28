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
#include "mm_math/mm_mat44.h"
#include "mm_mtl/singleton.h"

namespace event {

ObjectCamera::ObjectCamera(const char *name, u32 id) : Object(OBJTYPE_UNKNOWN_3, name), m_camObj(nullptr), unknown70(id), unknown4e0(0), unknown4e4(0) {
  m_camObj = mm::mtl::Singleton<CamManager>::getPtr()->createCam(id);
  m_posAxis = PosAxis(PosAxis::AXIS_UNKNOWN_1, m_camObj->getPos());
  m_tarAxis = TarAxis(TarAxis::AXIS_UNKNOWN_1, m_camObj->getTarget());
}

ObjectCamera::~ObjectCamera() {
  mm::mtl::Singleton<CamManager>::getPtr()->destroyCam(m_camObj);
  m_camObj = nullptr;
}

const char *ObjectCamera::getCutName() const { return m_cutName.c_str(); }

void ObjectCamera::start() {}

void ObjectCamera::end() {
  if (m_camObj != nullptr)
    m_camObj->end();
}

void ObjectCamera::tail() { m_camObj->tail(); }

void ObjectCamera::update() {
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  m_camObj->update(info);
  if (unknown70 == 0 && mm::mtl::Singleton<DebugManager>::getPtr()->isSyncFreeCam() && mm::mtl::Singleton<CamManager>::getPtr()->isFreeCam()) {
    updateSyncFreeCam();
  }
}

void ObjectCamera::playMotion(const char *name, const mm::Vec3 &offset) { m_camObj->activateMotion()->play(name, offset); }

void ObjectCamera::stopMotion() { m_camObj->activateMotion()->stop(); }

void ObjectCamera::setPosAxis(const PosAxis &axis, CV_TYPE cv) {
  m_posAxis = axis;
  unknowna0.clear();
  unknowna0.push_back(axis);
  m_camObj->activateHands()->setPos(axis, cv);
}

void ObjectCamera::movePosAxis(const PosAxis &axis, f32 frame, CV_TYPE cv) {
  unknowna0.push_back(axis);
  m_camObj->activateHands()->addAnmPos(frame, axis, cv);
}

mm::Vec3 ObjectCamera::getPos() const { return m_camObj->getPos(); }

void ObjectCamera::setTarAxis(const TarAxis &axis, CV_TYPE cv) {
  m_tarAxis = axis;
  unknown2d0.clear();
  unknown2d0.push_back(axis);
  m_camObj->activateHands()->setTar(axis, cv);
}

void ObjectCamera::moveTarAxis(const TarAxis &axis, f32 frame, CV_TYPE cv) {
  unknown2d0.push_back(axis);
  m_camObj->activateHands()->addAnmTar(frame, axis, cv);
}

mm::Vec3 ObjectCamera::getTar() const { return m_camObj->getTarget(); }

void ObjectCamera::setFov(f32 fov, CV_TYPE cv) { m_camObj->activateHands()->setFov(fov, cv); }

void ObjectCamera::moveFov(f32 fov, f32 frame, CV_TYPE cv) { m_camObj->activateHands()->addAnmFov(frame, fov, cv); }

f32 ObjectCamera::getFov() const { return m_camObj->getFov(); }

void ObjectCamera::setRotZ(f32 rotZ, CV_TYPE cv) { m_camObj->activateHands()->setRotZ(rotZ, cv); }

void ObjectCamera::moveRotZ(f32 rotZ, f32 frame, CV_TYPE cv) { m_camObj->activateHands()->addAnmRotZ(frame, rotZ, cv); }

f32 ObjectCamera::getRotZ() const { return m_camObj->getRoll(); }

void ObjectCamera::setCutName(const char *name) { m_cutName = name; }

void ObjectCamera::followPos(bool isFollow) { m_camObj->activateHands()->followPos(isFollow); }

bool ObjectCamera::isFollowPos() const { return m_camObj->activateHands()->isFollowPos(); }

void ObjectCamera::followTar(bool isFollow) { m_camObj->activateHands()->followTar(isFollow); }

void ObjectCamera::render(const mm::Col4 &color) { mm::mtl::Singleton<SeqManager>::getPtr(); }

void ObjectCamera::OnManiRender(IManiCallback::RenderParam &param) { mm::mtl::Singleton<SeqManager>::getPtr(); }

bool ObjectCamera::isFollowTar() const { return m_camObj->activateHands()->isFollowTar(); }

bool ObjectCamera::OnBouRectSelect(const IBouCallback::SelectParam &param) { return false; }

void ObjectCamera::OnBouRender(const IBouCallback::RenderParam &param) {
  if (mm::mtl::Singleton<SeqManager>::getPtr()->unknown001().unknown54 < 3 && unknown70 == 0) {
    int x = ml::DevGraph::getRootWidth() - 415;
    const mm::Vec3 &pos = m_camObj->getPos();
    const mm::Vec3 &target = m_camObj->getTarget();
    mm::Vec3 rot = m_camObj->getRot();
    ObjectUtil::drawCameraInfo(x, 120, pos, target, rot, m_camObj->getFov(), m_camObj->isFocal());
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
  rot.z = m_camObj->getRoll();
  return rot;
}

// 0x71001158c4, 108 instructions. The point is transformed by the products written out: through DataManager::unknown001 (as ObjectChara::OnManiSetPos does)
// the two integer copies of the position come before the first product and the registers of x and y swap (ldp w21, w22 against the game's ldp w22, w21).
void ObjectCamera::OnManiSetPos(IManiCallback::SetParam &param) {
  if (mm::mtl::Singleton<SeqManager>::getPtr()->unknown001().unknown54 < 3) {
    mm::Vec3 pos = param.matrix.unknown004();
    PosAxis axis = unknowna0[unknown4e0];
    mm::Mat44 inverse = axis.calcOrigMatInv();
    f32 x = pos.x * inverse.rows[0][0] + pos.y * inverse.rows[1][0] + pos.z * inverse.rows[2][0] + inverse.rows[3][0];
    f32 y = pos.x * inverse.rows[0][1] + pos.y * inverse.rows[1][1] + pos.z * inverse.rows[2][1] + inverse.rows[3][1];
    f32 z = pos.x * inverse.rows[0][2] + pos.y * inverse.rows[1][2] + pos.z * inverse.rows[2][2] + inverse.rows[3][2];
    axis.set(axis.getAxis(), x, y, z);
    if (unknown4e0 == 0) {
      m_posAxis = axis;
    }
    unknowna0[unknown4e0] = axis;
    m_camObj->getHands()->insertAnmPos(unknown4e0, axis);
  }
}

} // namespace event
