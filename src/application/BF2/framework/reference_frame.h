#pragma once
#include <stddef.h>

#include "fw/fw_transform.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace fw {

class ReferenceFrame : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNode<ReferenceFrame> {
public:
  static const u32 FLAG_LOCAL_SYNCED = 1 << 0;
  static const u32 FLAG_WORLD_SYNCED = 1 << 1;
  static const u32 FLAG_MATRIX_SYNCED = 1 << 2;

  ReferenceFrame();
  ~ReferenceFrame() override;
  void addChild(ReferenceFrame &child);
  void removeChild(ReferenceFrame &child);
  void syncLocalTransform();
  const Transform &getSyncedWorldTransform() {
    syncWorldTransform();
    return worldTransform;
  }

  void syncWorldTransform();
  static void unlinkParent(ReferenceFrame &frame);
  static void unlinkChild(ReferenceFrame &frame);
  const mm::Mat44 &getSyncedWorldMatrix();

  Transform localTransform;
  Transform worldTransform;
  mm::Mat44 worldMatrix;
  u32 flags;
  ReferenceFrame *parent;
  mm::mtl::IntrusiveList<ReferenceFrame> children;
  void *_c8;
  void *_d0;
};

static_assert(offsetof(ReferenceFrame, localTransform) == 0x20, "");
static_assert(offsetof(ReferenceFrame, worldMatrix) == 0x60, "");
static_assert(offsetof(ReferenceFrame, flags) == 0xa0, "");
static_assert(offsetof(ReferenceFrame, children) == 0xb0, "");
static_assert(sizeof(ReferenceFrame) == 0xe0, "");

class TransformUpdater : public mm::mtl::IntrusiveListNode<TransformUpdater> {
public:
  void resolveWorldTrasform();

  mm::mtl::Vector<mm::mtl::IntrusivePtr<ReferenceFrame>> frames;
  mm::mtl::Vector<mm::mtl::IntrusivePtr<ReferenceFrame>> afterFrames;
};

static_assert(offsetof(TransformUpdater, frames) == 0x10, "");
static_assert(offsetof(TransformUpdater, afterFrames) == 0x38, "");
static_assert(sizeof(TransformUpdater) == 0x60, "");

class TransformManager : public mm::mtl::PtrSingleton<TransformManager> {
public:
  static const u32 LAYER_MAX = 32;

  void update(u32 layerMask);

  mm::mtl::IntrusiveList<TransformUpdater> groups[LAYER_MAX];
};

static_assert(offsetof(TransformManager, groups) == 0x08, "");

} // namespace fw
