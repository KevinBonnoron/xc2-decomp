#include "event/attach_actor_base.h"

#include "gf/object/gf_obj_handle.h"

namespace event {

AttachActorBase::AttachActorBase(const char *name) : unknown8(name), unknown50(gf::INVALID_HANDLE), unknown60(mm::Mat44::identity) {}

AttachActorBase::AttachActorBase(const char *name, gf::GF_OBJ_HANDLE *actor) : unknown8(name), unknown50(actor), unknown60(mm::Mat44::identity) {}

void AttachActorBase::setActor(gf::GF_OBJ_HANDLE *actor) { unknown50 = actor; }

const char *AttachActorBase::getName() const { return unknown8.c_str(); }

bool AttachActorBase::getMat(mm::Mat44 &mat) const {
  mat = unknown60;
  return true;
}

bool AttachActorBase::hasMtp(const char *name) const {
  mm::Mat44 mat;
  return getMtpMat(mat, name);
}

bool AttachActorBase::hasEfp(const char *name) const {
  mm::Mat44 mat;
  return getEfpMat(mat, name);
}

bool AttachActorBase::hasBone(const char *name) const {
  mm::Mat44 mat;
  return getBoneMat(mat, name);
}

void AttachActorBase::setTransform(const mm::Mat44 &transform) { unknown60 = transform; }

} // namespace event
