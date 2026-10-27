#include "framework/reference_frame.h"

#include "anm/anm_qs_transform.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec4.h"

namespace fw {

ReferenceFrame::ReferenceFrame() : unknowna0(0), unknowna8(nullptr) {
  unknown20.unknown00 = mm::Vec3::zero;
  unknown20.unknown10 = mm::Quat::identity;
  unknown40.unknown00 = mm::Vec3::zero;
  unknown40.unknown10 = mm::Quat::identity;
  unknown60 = mm::Mat44::identity;
  unknowna0 |= FLAG_LOCAL_SYNCED | FLAG_WORLD_SYNCED | FLAG_MATRIX_SYNCED;
  unknownc8 = 0.0f;
  unknowncc = 0.0f;
  unknownd0 = 0.0f;
  unknownd4 = 0.0f;
}

ReferenceFrame::~ReferenceFrame() { ; }

void ReferenceFrame::addChild(ReferenceFrame &child) {
  unknownb0.push_back(&child);
  child.unknowna8 = this;
}

void ReferenceFrame::removeChild(ReferenceFrame &child) {
  unknownb0.erase(&child);
  child.unknowna8 = nullptr;
}

static void toLocalTransform(const Transform &parentWorld, const Transform &world, Transform *local) {
  Transform inverse;
  Transform::invert(parentWorld, &inverse);
  Transform::mul(inverse, world, local);
}

void ReferenceFrame::syncLocalTransform() {
  if ((unknowna0 & FLAG_LOCAL_SYNCED) == 0) {
    if (unknowna8 != nullptr) {
      toLocalTransform(unknowna8->getSyncedWorldTransform(), unknown40, &unknown20);
    } else {
      unknown20 = unknown40;
    }

    unknowna0 |= FLAG_LOCAL_SYNCED;
  }
}

void ReferenceFrame::syncWorldTransform() {
  if ((unknowna0 & FLAG_WORLD_SYNCED) == 0) {
    if (unknowna8 != nullptr) {
      Transform::mul(unknowna8->getSyncedWorldTransform(), unknown20, &unknown40);
    } else {
      unknown40 = unknown20;
    }

    unknowna0 = (unknowna0 & ~(FLAG_WORLD_SYNCED | FLAG_MATRIX_SYNCED)) | FLAG_WORLD_SYNCED;
  }
}

void Transform::mul(const Transform &transform, const Transform &other, Transform *result) {
  result->unknown00 = transform.unknown00 + transform.unknown10.rotate(other.unknown00);
  result->unknown10 = mm::Quat::mul(other.unknown10, transform.unknown10);
}

void TransformUtil::mul(const Transform &transform, const anm::QsTransform &other, f32 scale, Transform *result) {
  mm::Vec3 translation(other.unknown00.x, other.unknown00.y, other.unknown00.z);
  result->unknown00 = transform.unknown00 + transform.unknown10.rotate(translation) * scale;
  result->unknown10 = mm::Quat::mul(other.unknown10, transform.unknown10);
}

void ReferenceFrame::unlinkParent(ReferenceFrame &frame) {
  if (frame.unknowna8 != nullptr) {
    frame.unknowna8->removeChild(frame);
  }
}

void TransformManager::update(u32 layerMask) {
  for (u32 layer = 0; layer < LAYER_MAX; layer++) {
    if ((1 << layer & layerMask) != 0) {
      for (mm::mtl::IntrusiveList<TransformUpdater>::iterator it = unknown08[layer].begin(); it != unknown08[layer].end(); ++it) {
        (*it).resolveWorldTrasform();
      }
    }
  }
}

} // namespace fw

template mm::mtl::PtrSingleton<fw::TransformManager>::~PtrSingleton();
