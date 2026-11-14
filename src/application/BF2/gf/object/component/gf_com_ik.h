#pragma once
#include <stddef.h>

#include "framework/anim/anim_manager.h"
#include "framework/ik/ik_ground_interface.h"
#include "framework/ik/ik_raycaster.h"
#include "gf/object/component/gf_component.h"
#include "gf/object/component/property/gf_env_property.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/unique_ptr.h"
#include "types.h"

namespace fw {
class BlowRotateIkSolver;
class LookIkSolver;
class PlacementGroundSolver;
class SlopeGroundSolver;
class TwoCharaGroundSolver;
class MessageObject;
class ParamAdapter;
class RotateIkSolver;
class SpineIkSolver;
class LookAtIkSolver;
class SphericalCoordinatesIkSolver;
class SpineRotateIKSolver;
class TransLocalIkSolver;
class RotateLocalIkSolver;
} // namespace fw

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

// Inferred role: slot indices of the IK solver vector, from the size asserts; original name unknown.
enum unknown002 {
  unknown002_0,
  unknown002_1,
  unknown002_2,
  unknown002_3,
  unknown002_4,
  unknown002_5,
  unknown002_6,
  unknown002_7,
  unknown002_8,
};

// Evidence: component slot 3 (access offset 0x50 in GfObjFactory), IkResolver at 0x10 (add/removeIkResolver with this + 0x10), vtables and sizes from the constructor.
class GfComIK : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 3;

  class ViewerListener {
  public:
    ViewerListener() : unknown08(nullptr) {}
    virtual void onWkStandbyLogout() {
      if (unknown08 != nullptr) {
        unknown08->unknown68 = nullptr;
      }
    }

    GfComIK *unknown08; // Inferred role: owner; original member name unknown.
  };
  struct SetupInfo {};

  // Layout evidence: the vtable (getPlane, getHitPos, then the destructor called by Ground::~Ground) and the 0x28 byte elements of Ground.
  class FootGround : public fw::IKFootGroundInterface {
  public:
    FootGround() : unknown18(nullptr), unknown20(0) {}
    virtual ~FootGround() {}
    const mm::Plane *getPlane() const override;
    const mm::Vec3 *getHitPos() const override;

    // Inferred helper: ground sample of this foot, null without a valid one; original name unknown.
    const GfEnvProperty::unknown002 *unknown001() const {
      if (unknown18 == nullptr) {
        return nullptr;
      }
      return unknown18->unknown004(unknown20);
    }

    GfEnvProperty *unknown18; // Inferred role: environment property; original member name unknown.
    int unknown20;            // Inferred role: foot index; original member name unknown.
  };

  // Layout evidence: operator new of 0x108 bytes in GfComIK::setup.
  class Ground : public fw::IKGroundInterface {
  public:
    fw::IKFootGroundInterface *getFootGround(fw::IKFootIndex index) override;
    const mm::Plane *getPlane() const override;
    const mm::Vec3 *getHitPos() const override;
    const mm::Plane *getPlaneSub() const override;
    const mm::Vec3 *getHitPosSub() const override;

    // Inferred helper: binds the environment property and sizes the foot grounds; original name unknown.
    void unknown001(GfEnvProperty *env, u32 footCount) {
      unknown08 = env;
      unknown10.resize(footCount, FootGround());
      for (u32 i = 0; i < footCount; i++) {
        FootGround &ground = unknown10[i];
        ground.unknown18 = env;
        ground.unknown20 = i + 1;
      }
    }

    // Inferred helper: ground sample, null without a valid one; original name unknown.
    const GfEnvProperty::unknown002 *unknown002(GfEnvProperty::GROUND_INDEX index) const {
      if (unknown08 == nullptr) {
        return nullptr;
      }
      if (!unknown08->unknown2d4) {
        return nullptr;
      }
      return unknown08->unknown004(index);
    }

    GfEnvProperty *unknown08;                      // Inferred role: environment property; original member name unknown.
    mm::mtl::FixedVector<FootGround, 6> unknown10; // Inferred role: foot grounds; original member name unknown.
  };

  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  GfComIK();
  void setup(const SetupInfo &info);
  ~GfComIK() override;
  void cleanup();
  fw::RotateIkSolver *createRotateBodyIK(const char *boneName);
  fw::SpineIkSolver *createSpineIK(const fw::ParamAdapter &param, const char *boneName, const char *endBoneName);
  fw::LookAtIkSolver *createLookAtIK(const fw::ParamAdapter &param, const char *boneName);
  fw::SphericalCoordinatesIkSolver *createSphericalCoordinatesIkSolver(const fw::ParamAdapter &param, const char *boneName);
  fw::SpineRotateIKSolver *createSpineRotateIkSolver(const fw::ParamAdapter &param, const char *boneName, const char *endBoneName);
  fw::TransLocalIkSolver *createTransEyeIkSolver(u32 index, const char *boneName);
  fw::RotateLocalIkSolver *createRotateEyeIkSolver(u32 index, const char *boneName);
  fw::LookIkSolver *createLookIK(f32 fadeInTime, f32 fadeOutTime);
  fw::PlacementGroundSolver *createPlacementGroundIK(f32 value);
  fw::TwoCharaGroundSolver *createTwoCharaGroundIK(f32 value, const char *boneName, const char *endBoneName);
  fw::SlopeGroundSolver *createSlopeGroundIK(f32 first, f32 second);
  fw::BlowRotateIkSolver *createBlowRotateIkSolver(const char *boneName);
  void changeLayer(u32 oldLayer, u32 newLayer) override;
  const mm::mtl::RTTI *getRTTI() const override;

  fw::IkResolver unknown10;             // Inferred role: ik resolver; original member name unknown.
  mm::mtl::UniquePtr<Ground> unknown48; // Inferred role: ground; original member name unknown.
  u32 unknown50;                        // Inferred role: foot count; original member name unknown.
  ViewerListener unknown58;             // Inferred role: viewer listener; original member name unknown.
  void *unknown68;                      // Inferred role: viewer; original member name unknown.
};

static_assert(offsetof(GfComIK::FootGround, unknown08) == 0x08, "");
static_assert(offsetof(GfComIK::FootGround, unknown18) == 0x18, "");
static_assert(offsetof(GfComIK::FootGround, unknown20) == 0x20, "");
static_assert(sizeof(GfComIK::FootGround) == 0x28, "");
static_assert(offsetof(GfComIK::Ground, unknown08) == 0x08, "");
static_assert(offsetof(GfComIK::Ground, unknown10) == 0x10, "");
static_assert(sizeof(GfComIK::Ground) == 0x108, "");

static_assert(offsetof(GfComIK, unknown10) == 0x10, "");
static_assert(offsetof(GfComIK, unknown48) == 0x48, "");
static_assert(offsetof(GfComIK, unknown50) == 0x50, "");
static_assert(offsetof(GfComIK, unknown58) == 0x58, "");
static_assert(offsetof(GfComIK, unknown68) == 0x68, "");
static_assert(sizeof(GfComIK) == 0x70, "");

} // namespace gf
