#include "event/attach_actor_gf.h"

#include "event/attach_util.h"
#include "fw/fw_transform.h"
#include "gf/object/component/effect/gf_com_effect_caster.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"

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

bool AttachActorGf::getEfpMat(mm::Mat44 &mat, const char *name) const {
  mat = mm::Mat44::identity;
  gf::GfObj *actor = gf::GfObjUtil::getObj(unknowna0);
  gf::GfComTransform *transform = actor->getComponent<gf::GfComTransform>();
  if (!transform) {
    return false;
  }
  gf::GfComEffectCaster *caster = actor->getComponent<gf::GfComEffectCaster>();
  if (!caster || !caster->getEfpMatrix(name, mat)) {
    return false;
  }
  mm::Vec3 rotation = mm::quatToEuler(transform->getRotation());
  mm::Vec3 position = transform->getPosition();
  mm::Mat44 world;
  world.setRotXYZ(rotation);
  world.setTrans(position);
  mat = mat * world.unknown003();
  return true;
}

bool AttachActorGf::getBoneMat(mm::Mat44 &mat, const char *name) const {
  mat = mm::Mat44::identity;
  if (*name == '\0') {
    return false;
  }
  gf::GfObjAcc actor(unknowna0);
  int bone = actor.getBoneIdx(name);
  if (bone < 0) {
    return false;
  }
  fw::Transform boneTransform;
  if (!actor.getBoneTransform(boneTransform, bone)) {
    return false;
  }
  boneTransform.unknown001(mat);
  gf::GfComTransform *transform = gf::GfObjUtil::getObj(unknowna0)->getComponent<gf::GfComTransform>();
  mm::Vec3 rotation = mm::quatToEuler(transform->getRotation());
  mm::Vec3 position = transform->getPosition();
  mm::Mat44 world;
  world.setRotXYZ(rotation);
  world.setTrans(position);
  mat = mat * world.unknown003();
  return true;
}

void AttachActorGf::setTransform(const mm::Mat44 &transform) { unknown60 = transform; }

} // namespace event
