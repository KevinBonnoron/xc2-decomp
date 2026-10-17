#pragma once
#include <stddef.h>

#include "framework/dynamics/dynamics_updater.h"
#include "gf/object/component/gf_component.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace fw {
class ForceCalculator;
class MessageObject;
} // namespace fw
namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm
namespace skd {
class CollisionObject;
struct ResDynamics;
} // namespace skd

namespace gf {

class GfComDynamics : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 8;
  static const u32 ITERATION_COUNT_DEFAULT = 6;
  static const u32 ITERATION_COUNT_MAX = 30;

  enum {
    ASM_ATTRIBUTE_LIMIT_MOVEMENT = 1 << 2,
    ASM_ATTRIBUTE_MAX_ITERATION = 1 << 6,
  };

  struct SetupInfo {
    const skd::ResDynamics *resDynamics;
    skd::CollisionObject *collisionObject;
    fw::ForceCalculator *forceCalculator;
    u32 iterationCount;
  };

  class ViewerListener {
  public:
    virtual void onWkStandbyLogout() {
      if (owner != nullptr) {
        owner->viewer = nullptr;
      }
    }

    GfComDynamics *owner;
  };

  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  GfComDynamics();
  ~GfComDynamics() override;
  void setup(const SetupInfo &info);
  void applyAttribute();
  void cleanup();
  void changeLayer(u32 oldLayer, u32 newLayer) override;
  void resetMovement();
  u32 getSolverCount() const;
  const char *getSolverName(u32 index) const;
  u32 getSolverID(const char *name) const;
  void setSolverBlendWeight(u32 index, f32 weight);
  f32 getSolverBlendWeight(u32 index) const;
  const mm::mtl::RTTI *getRTTI() const override;

  fw::DynamicsUpdater updater;
  fw::DynamicsColObjUpdater colObjUpdater;
  mm::mtl::IntrusivePtr<fw::ForceCalculator> forceCalculator;
  u32 iterationCount;
  bool isMaxIteration;
  ViewerListener viewerListener;
  void *viewer;
};

static_assert(offsetof(GfComDynamics, updater) == 0x10, "");
static_assert(offsetof(GfComDynamics, colObjUpdater) == 0xc0, "");
static_assert(offsetof(GfComDynamics, forceCalculator) == 0xe0, "");
static_assert(offsetof(GfComDynamics, iterationCount) == 0xe8, "");
static_assert(offsetof(GfComDynamics, isMaxIteration) == 0xec, "");
static_assert(offsetof(GfComDynamics, viewerListener) == 0xf0, "");
static_assert(offsetof(GfComDynamics, viewer) == 0x100, "");

} // namespace gf
