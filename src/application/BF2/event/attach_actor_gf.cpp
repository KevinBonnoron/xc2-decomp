#include "event/attach_actor_gf.h"

#include "event/attach_util.h"

namespace event {

AttachActorGf::AttachActorGf(const char *name, gf::GF_OBJ_HANDLE *handle) : AttachActorBase(name, handle), unknowna0(handle) {}

AttachActorGf::~AttachActorGf() {}

void AttachActorGf::render() { AttachActorBase::render(); }

void AttachActorGf::setEffectCaster(bool isSet, u32 effect) {
  if (isSet) {
    AttachUtil::setCaster(true, unknowna0, effect);
  } else {
    AttachUtil::setCaster(false, unknowna0, effect);
  }
}

void AttachActorGf::setEffectMount(bool isSet, u32 effect, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type) {
  if (isSet) {
    AttachUtil::setMount(true, unknowna0, effect, bone, offset, isRotate, type);
  } else {
    AttachUtil::setMount(false, unknowna0, effect, bone, offset, isRotate, type);
  }
}

bool AttachActorGf::getMtpMat(mm::Mat44 &mat, const char *name) const {
  mat = mm::Mat44::identity;
  return false;
}

void AttachActorGf::setTransform(const mm::Mat44 &transform) { unknown60 = transform; }

} // namespace event
