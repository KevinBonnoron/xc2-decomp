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

  skd::Dynamics *unknown18;                        // Inferred role: dynamics; original member name unknown.
  mm::mtl::IntrusivePtr<ReferenceFrame> unknown20; // Inferred role: reference frame; original member name unknown.
  Transform unknown30;                             // Inferred role: cached transform; original member name unknown.
  Transform unknown50;                             // Inferred role: offset transform; original member name unknown.
  bool unknown70;                                  // Inferred role: enable; original member name unknown.
  bool unknown71;                                  // Inferred role: enable movement; original member name unknown.
  bool unknown72;                                  // Inferred role: reset requested; original member name unknown.
  mm::mtl::Delegate<void()> unknown78;             // Inferred role: pre update callback; original member name unknown.
  f32 unknown98;                                   // Inferred role: speed; original member name unknown.
  DynamicsDrawer *unknowna0;                       // Inferred role: drawer; original member name unknown.
};

static_assert(offsetof(DynamicsUpdater, unknown18) == 0x18, "");
static_assert(offsetof(DynamicsUpdater, unknown30) == 0x30, "");
static_assert(offsetof(DynamicsUpdater, unknown70) == 0x70, "");
static_assert(offsetof(DynamicsUpdater, unknown78) == 0x78, "");
static_assert(offsetof(DynamicsUpdater, unknown98) == 0x98, "");
static_assert(offsetof(DynamicsUpdater, unknowna0) == 0xa0, "");

class DynamicsColObjUpdater : public DynamicsColObjUpdaterInterface {
public:
  DynamicsColObjUpdater();
  ~DynamicsColObjUpdater() override;
  void unbind();
  void bind(skd::CollisionObject *collisionObject);
  void update() override;

  skd::CollisionObject *unknown18; // Inferred role: collision object; original member name unknown.
};

static_assert(offsetof(DynamicsColObjUpdater, unknown18) == 0x18, "");

} // namespace fw
