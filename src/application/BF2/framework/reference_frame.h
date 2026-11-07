#pragma once
#include <stddef.h>

#include "fw/fw_transform.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixed_array.h"
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
  static const u32 FLAG_ALL_SYNCED = FLAG_LOCAL_SYNCED | FLAG_WORLD_SYNCED | FLAG_MATRIX_SYNCED;

  ReferenceFrame();
  ~ReferenceFrame() override;
  void invalidateLocal() { unknowna0 = (unknowna0 & ~FLAG_ALL_SYNCED) | FLAG_WORLD_SYNCED; }
  void invalidateWorld() { unknowna0 = (unknowna0 & ~FLAG_ALL_SYNCED) | FLAG_LOCAL_SYNCED; }
  // Inferred role: marks the local transform as outdated and keeps the matrix flag; original name unknown.
  void unknown001() { unknowna0 = (unknowna0 & ~(FLAG_LOCAL_SYNCED | FLAG_WORLD_SYNCED)) | FLAG_WORLD_SYNCED; }
  // Inferred role: marks the world transform as outdated and returns the local transform for writing; original name unknown.
  Transform &unknown002() {
    invalidateWorld();
    return unknown20;
  }
  // Inferred role: marks the local transform as outdated and returns the world transform for writing; original name unknown.
  Transform &unknown003() {
    invalidateLocal();
    return unknown40;
  }
  void addChild(ReferenceFrame &child);
  void removeChild(ReferenceFrame &child);
  void syncLocalTransform();
  const Transform &getSyncedWorldTransform() {
    syncWorldTransform();
    return unknown40;
  }

  void syncWorldTransform();
  void syncWorldMatrix() {
    if ((unknowna0 & FLAG_MATRIX_SYNCED) == 0) {
      syncWorldTransform();
      unknown40.unknown001(unknown60);
      unknowna0 |= FLAG_MATRIX_SYNCED;
    }
  }
  static void unlinkParent(ReferenceFrame &frame);
  static void unlinkChild(ReferenceFrame &frame);
  const mm::Mat44 &getSyncedWorldMatrix() {
    syncWorldMatrix();
    return unknown60;
  }

  Transform unknown20;                              // Inferred role: local transform; original member name unknown.
  Transform unknown40;                              // Inferred role: world transform; original member name unknown.
  mm::Mat44 unknown60;                              // Inferred role: world matrix; original member name unknown.
  u32 unknowna0;                                    // Inferred role: flags; original member name unknown.
  ReferenceFrame *unknowna8;                        // Inferred role: parent; original member name unknown.
  mm::mtl::IntrusiveList<ReferenceFrame> unknownb0; // Inferred role: children; original member name unknown.
  f32 unknownc8;                                    // Inferred role: scale x; original member name unknown.
  f32 unknowncc;                                    // Inferred role: scale y; original member name unknown.
  f32 unknownd0;                                    // Inferred role: scale z; original member name unknown.
  f32 unknownd4;
};

static_assert(offsetof(ReferenceFrame, unknown20) == 0x20, "");
static_assert(offsetof(ReferenceFrame, unknown60) == 0x60, "");
static_assert(offsetof(ReferenceFrame, unknowna0) == 0xa0, "");
static_assert(offsetof(ReferenceFrame, unknownb0) == 0xb0, "");
static_assert(offsetof(ReferenceFrame, unknownc8) == 0xc8, "");
static_assert(offsetof(ReferenceFrame, unknownd0) == 0xd0, "");
static_assert(sizeof(ReferenceFrame) == 0xe0, "");

class TransformUpdater : public mm::mtl::IntrusiveListNode<TransformUpdater> {
public:
  void resolveWorldTrasform();

  mm::mtl::Vector<mm::mtl::IntrusivePtr<ReferenceFrame>> unknown10; // Inferred role: frames; original member name unknown.
  mm::mtl::Vector<mm::mtl::IntrusivePtr<ReferenceFrame>> unknown38; // Inferred role: after frames; original member name unknown.
};

static_assert(offsetof(TransformUpdater, unknown10) == 0x10, "");
static_assert(offsetof(TransformUpdater, unknown38) == 0x38, "");
static_assert(sizeof(TransformUpdater) == 0x60, "");

class TransformManager : public mm::mtl::PtrSingleton<TransformManager> {
public:
  static const u32 LAYER_MAX = 32;

  struct Group {
    mm::mtl::IntrusiveList<TransformUpdater> unknown00; // Inferred role: updaters; original member name unknown.
  };

  void update(u32 layerMask);
  void addUpdater(u32 layer, TransformUpdater &updater) { unknown08[layer].unknown00.push_back(&updater); }
  void removeUpdater(u32 layer, TransformUpdater &updater) { unknown08[layer].unknown00.erase(&updater); }

  mm::mtl::FixedArray<Group, LAYER_MAX> unknown08; // Inferred role: groups; original member name unknown.
};

static_assert(sizeof(TransformManager::Group) == 0x18, "");
static_assert(offsetof(TransformManager, unknown08) == 0x08, "");
static_assert(sizeof(TransformManager) == 0x308, "");

} // namespace fw
