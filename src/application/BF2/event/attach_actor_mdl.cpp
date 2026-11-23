#include "event/attach_actor_mdl.h"

#include "event/attach_util.h"
#include "event/model_obj.h"
#include "mm_math/mm_mat44.h"

namespace event {

AttachActorMdl::AttachActorMdl(const char *name, ModelObj *model) : AttachActorBase(name, model->getHandle()), m_modelObj(model) {}

AttachActorMdl::~AttachActorMdl() {}

void AttachActorMdl::render() { AttachActorBase::render(); }

void AttachActorMdl::setEffectCaster(bool isSet, u32 effect) {
  if (isSet) {
    AttachUtil::setCaster(true, m_modelObj->getHandle(), effect);
  } else {
    AttachUtil::setCaster(false, m_modelObj->getHandle(), effect);
  }
}

void AttachActorMdl::setEffectMount(bool isSet, u32 effect, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type) {
  if (isSet) {
    AttachUtil::setMount(true, m_modelObj->getHandle(), effect, bone, offset, isRotate, type);
  } else {
    AttachUtil::setMount(false, m_modelObj->getHandle(), effect, bone, offset, isRotate, type);
  }
}

bool AttachActorMdl::getMtpMat(mm::Mat44 &mat, const char *name) const {
  mat = mm::Mat44::identity;
  return false;
}

bool AttachActorMdl::getEfpMat(mm::Mat44 &mat, const char *name) const {
  mat = mm::Mat44::identity;
  if (*name == '\0') {
    return false;
  }
  return m_modelObj->getEfpMat(mat, name);
}

bool AttachActorMdl::getBoneMat(mm::Mat44 &mat, const char *name) const {
  mat = mm::Mat44::identity;
  if (*name == '\0') {
    return false;
  }
  return m_modelObj->getBoneMat(mat, name);
}

void AttachActorMdl::setTransform(const mm::Mat44 &transform) { unknown60 = transform; }

} // namespace event
