#include "event/attach_actor_base.h"

#include "anm/anm_array-inl.h"
#include "anm/anm_pose.h"
#include "anm/anm_skeleton.h"
#include "event/manager.h"
#include "framework/reference_frame.h"
#include "fw/fw_debug.h"
#include "fw/fw_transform.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "ml/scn.h"
#include "ml/scn_cam_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace event {

AttachActorBase::AttachActorBase(const char *name) : unknown8(name), unknown50(gf::INVALID_HANDLE), unknown60(mm::Mat44::identity) {}

AttachActorBase::AttachActorBase(const char *name, gf::GF_OBJ_HANDLE *actor) : unknown8(name), unknown50(actor), unknown60(mm::Mat44::identity) {}

void AttachActorBase::setActor(gf::GF_OBJ_HANDLE *actor) { unknown50 = actor; }

void AttachActorBase::render() {
  ml::ScnObjCam *camera = Manager::get()->getScn()->getCam(-1);
  gf::GfObj *actor = gf::GfObjUtil::getObj(unknown50);
  if (!actor) {
    return;
  }
  gf::GfComTransform *transform = actor->getComponent<gf::GfComTransform>();
  gf::GfComModel *model = actor->getComponent<gf::GfComModel>();
  if (!transform && !model) {
    return;
  }
  const anm::Skeleton *skeleton = model->skeleton;
  anm::Pose *pose = model->pose;
  if (!skeleton && !pose) {
    return;
  }
  u32 count = skeleton->bones.size();
  for (u32 i = 0; i < count; ++i) {
    const char *name = skeleton->bones[static_cast<u16>(i)].name;
    mm::Mat44 matrix;
    fw::Transform world;
    fw::TransformUtil::mul(transform->frame->getSyncedWorldTransform(), pose->getBoneModelSpace(i), 1.0f, &world);
    world.unknown001(matrix);
    mm::Vec3 screen;
    if (ml::ScnCamUtil::getScreenPos(screen, camera, matrix.unknown004())) {
      fw::debug::drawAxis(matrix, 0.1f);
      fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
      fw::debug::drawFont(static_cast<int>(screen.x), static_cast<int>(screen.y), name);
    }
  }
}

const char *AttachActorBase::getName() const { return unknown8.c_str(); }

bool AttachActorBase::getMat(mm::Mat44 &mat) const {
  mat = unknown60;
  return true;
}

bool AttachActorBase::getMtpMatGlobal(mm::Mat44 &mat, const char *name) const {
  mm::Mat44 local;
  if (!getMtpMat(local, name)) {
    mat = unknown60;
    return false;
  }
  mat = local * unknown60;
  return true;
}

bool AttachActorBase::hasMtp(const char *name) const {
  mm::Mat44 mat;
  return getMtpMat(mat, name);
}

bool AttachActorBase::getEfpMatGlobal(mm::Mat44 &mat, const char *name) const {
  mm::Mat44 local;
  if (!getEfpMat(local, name)) {
    mat = unknown60;
    return false;
  }
  mat = local * unknown60;
  return true;
}

bool AttachActorBase::hasEfp(const char *name) const {
  mm::Mat44 mat;
  return getEfpMat(mat, name);
}

bool AttachActorBase::getBoneMatGlobal(mm::Mat44 &mat, const char *name) const {
  mm::Mat44 local;
  if (!getBoneMat(local, name)) {
    mat = unknown60;
    return false;
  }
  mat = local * unknown60;
  return true;
}

bool AttachActorBase::hasBone(const char *name) const {
  mm::Mat44 mat;
  return getBoneMat(mat, name);
}

void AttachActorBase::setTransform(const mm::Mat44 &transform) { unknown60 = transform; }

} // namespace event
