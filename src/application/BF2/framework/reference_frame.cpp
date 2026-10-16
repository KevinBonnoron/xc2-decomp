#include "framework/reference_frame.h"

#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace fw {

ReferenceFrame::ReferenceFrame() : flags(0), parent(nullptr) {
  localTransform.position = mm::Vec3::zero;
  localTransform.rotation = mm::Quat::identity;
  worldTransform.position = mm::Vec3::zero;
  worldTransform.rotation = mm::Quat::identity;
  worldMatrix = mm::Mat44::identity;
  flags |= FLAG_LOCAL_SYNCED | FLAG_WORLD_SYNCED | FLAG_MATRIX_SYNCED;
  _c8 = nullptr;
  _d0 = nullptr;
}

void ReferenceFrame::addChild(ReferenceFrame &child) {
  children.push_back(&child);
  child.parent = this;
}

void ReferenceFrame::removeChild(ReferenceFrame &child) {
  children.erase(&child);
  child.parent = nullptr;
}

static void toLocalTransform(const Transform &parentWorld, const Transform &world, Transform *local) {
  Transform inverse;
  Transform::invert(parentWorld, &inverse);
  Transform::mul(inverse, world, local);
}

void ReferenceFrame::syncLocalTransform() {
  if ((flags & FLAG_LOCAL_SYNCED) == 0) {
    if (parent != nullptr) {
      toLocalTransform(parent->getSyncedWorldTransform(), worldTransform, &localTransform);
    } else {
      localTransform = worldTransform;
    }

    flags |= FLAG_LOCAL_SYNCED;
  }
}

void ReferenceFrame::syncWorldTransform() {
  if ((flags & FLAG_WORLD_SYNCED) == 0) {
    if (parent != nullptr) {
      Transform::mul(parent->getSyncedWorldTransform(), localTransform, &worldTransform);
    } else {
      worldTransform = localTransform;
    }

    flags = (flags & ~(FLAG_WORLD_SYNCED | FLAG_MATRIX_SYNCED)) | FLAG_WORLD_SYNCED;
  }
}

void Transform::mul(const Transform &transform, const Transform &other, Transform *result) {
  result->position = transform.position + transform.rotation.rotate(other.position);
  result->rotation = mm::Quat::mul(other.rotation, transform.rotation);
}

void ReferenceFrame::unlinkParent(ReferenceFrame &frame) {
  if (frame.parent != nullptr) {
    frame.parent->removeChild(frame);
  }
}

void TransformManager::update(u32 layerMask) {
  for (u32 layer = 0; layer < LAYER_MAX; layer++) {
    if ((1 << layer & layerMask) != 0) {
      for (mm::mtl::IntrusiveList<TransformUpdater>::iterator it = groups[layer].begin(); it != groups[layer].end(); ++it) {
        (*it).resolveWorldTrasform();
      }
    }
  }
}

} // namespace fw
