#pragma once
#include <stddef.h>

#include "framework/dynamics/dynamics_manager.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace skd {
class CollisionObject;
class Dynamics;
} // namespace skd

namespace fw {

class DynamicsDrawer;

class DynamicsUpdater : public DynamicsUpdaterInterface {
public:
  DynamicsUpdater();
  ~DynamicsUpdater() override;
  void unbind();
  void bind(skd::Dynamics *dynamics, mm::mtl::IntrusivePtr<ReferenceFrame> frame);
  void cacheTransform();
  void setEnable(bool enable);
  void setEnableMovement(bool enable);
  void update(const UpdateInfo &info) override;
  void drawDebug() override;

  skd::Dynamics *dynamics;
  mm::mtl::IntrusivePtr<ReferenceFrame> referenceFrame;
  Transform cachedTransform;
  Transform offsetTransform;
  bool isEnable;
  bool isEnableMovement;
  bool isResetRequested;
  mm::mtl::Delegate<void()> preUpdateCallback;
  f32 speed;
  DynamicsDrawer *drawer;
};

static_assert(offsetof(DynamicsUpdater, dynamics) == 0x18, "");
static_assert(offsetof(DynamicsUpdater, cachedTransform) == 0x30, "");
static_assert(offsetof(DynamicsUpdater, isEnable) == 0x70, "");
static_assert(offsetof(DynamicsUpdater, preUpdateCallback) == 0x78, "");
static_assert(offsetof(DynamicsUpdater, speed) == 0x98, "");
static_assert(offsetof(DynamicsUpdater, drawer) == 0xa0, "");

class DynamicsColObjUpdater : public DynamicsColObjUpdaterInterface {
public:
  DynamicsColObjUpdater();
  ~DynamicsColObjUpdater() override;
  void unbind();
  void bind(skd::CollisionObject *collisionObject);
  void update() override;

  skd::CollisionObject *collisionObject;
};

static_assert(offsetof(DynamicsColObjUpdater, collisionObject) == 0x18, "");

} // namespace fw
