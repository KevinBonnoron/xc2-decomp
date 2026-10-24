#include "gf/game/salvage/gf_salvage_cam.h"

#include "fw/fw_transform.h"
#include "gf/object/gf_obj_acc.h"
#include "mm_math/mm_vec3.h"

namespace fw {
enum CAMERA_PRIO : int;
} // namespace fw

namespace gf {

static constexpr fw::CAMERA_PRIO CAMERA_PRIO_SALVAGE = static_cast<fw::CAMERA_PRIO>(55);

GfSalvageCam::GfSalvageCam(GF_OBJ_HANDLE *target) : fw::Camera(CAMERA_PRIO_SALVAGE), unknowna8(target) {}

GfSalvageCam::~GfSalvageCam() {}

void GfSalvageCam::onPush() {}

void GfSalvageCam::onPop() {}

void GfSalvageCam::onActivate() {}

void GfSalvageCam::onDeactivate() {}

void GfSalvageCam::update(const fw::UpdateInfo &info) {
  GfObjAcc acc(unknowna8);
  const mm::Vec3 &position = acc.getWorldTransform().position;
  setLookAt(position + mm::Vec3(0.0f, 10.0f, 10.0f), position, 0.0f);
}

const mm::mtl::RTTI *GfSalvageCam::getRTTI() const { return &m_rtti; }

const char *GfSalvageCam::getName() const { return "GfSalvageCam"; }

} // namespace gf
