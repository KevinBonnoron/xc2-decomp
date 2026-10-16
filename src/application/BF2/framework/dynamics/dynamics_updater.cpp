#include "framework/dynamics/dynamics_updater.h"

#include "anm/anm_pose.h"
#include "fw/fw_update_info.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "skd/skd_collision_object.h"
#include "skd/skd_dynamics.h"

namespace fw {

DynamicsUpdater::DynamicsUpdater()
    : dynamics(nullptr), referenceFrame(), isEnable(true), isEnableMovement(true), isResetRequested(false), preUpdateCallback(), speed(1.0f),
      drawer(nullptr) {
  cachedTransform.position = mm::Vec3::zero;
  cachedTransform.rotation = mm::Quat::identity;
  offsetTransform.position = mm::Vec3::zero;
  offsetTransform.rotation = mm::Quat::identity;
}

DynamicsUpdater::~DynamicsUpdater() { unbind(); }

void DynamicsUpdater::unbind() {
  if (dynamics != nullptr) {
    dynamics->release();
    dynamics = nullptr;
  }

  referenceFrame = nullptr;
}

void DynamicsUpdater::bind(skd::Dynamics *dynamics, mm::mtl::IntrusivePtr<ReferenceFrame> frame) {
  unbind();
  this->dynamics = dynamics;
  dynamics->addRef();
  referenceFrame = frame;
  cacheTransform();
}

void DynamicsUpdater::cacheTransform() {
  if (referenceFrame.get() != nullptr) {
    cachedTransform = referenceFrame->getSyncedWorldTransform();
  }
}

void DynamicsUpdater::setEnable(bool enable) {
  isEnable = enable;
  if (dynamics != nullptr) {
    dynamics->resetDynamics();
  }

  if (isEnableMovement) {
    cacheTransform();
  }
}

void DynamicsUpdater::setEnableMovement(bool enable) {
  if (enable != isEnableMovement) {
    isEnableMovement = enable;
    if (enable) {
      cacheTransform();
    }
  }
}

void DynamicsUpdater::update(const UpdateInfo &info) {
  if (!isEnable) {
    return;
  }

  if (preUpdateCallback.isValid()) {
    preUpdateCallback();
  }

  if (isResetRequested) {
    dynamics->resetDynamics();
    isResetRequested = false;
  } else if (isEnableMovement) {
    const Transform &world = referenceFrame->getSyncedWorldTransform();
    dynamics->notifyMovement(world.position,
                             world.rotation,
                             cachedTransform.position + offsetTransform.position,
                             mm::Quat::mul(cachedTransform.rotation, offsetTransform.rotation));
    cachedTransform = world;
  }

  dynamics->update(info.deltaTime * speed);
  anm::Pose *pose = dynamics->pose;
  pose->syncLocalSpace();
  pose->syncModelSpace();
}

DynamicsColObjUpdater::DynamicsColObjUpdater() : collisionObject(nullptr) {}

DynamicsColObjUpdater::~DynamicsColObjUpdater() { unbind(); }

void DynamicsColObjUpdater::unbind() {
  if (collisionObject != nullptr) {
    collisionObject->release();
    collisionObject = nullptr;
  }
}

void DynamicsColObjUpdater::bind(skd::CollisionObject *collisionObject) {
  unbind();
  this->collisionObject = collisionObject;
  collisionObject->addRef();
}

void DynamicsColObjUpdater::update() { collisionObject->update(); }

} // namespace fw
