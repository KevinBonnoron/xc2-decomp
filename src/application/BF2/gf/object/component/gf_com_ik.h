#pragma once
#include <stddef.h>

#include "framework/anim/anim_manager.h"
#include "gf/object/component/gf_component.h"
#include "mm_mtl/unique_ptr.h"
#include "types.h"

namespace fw {
class IKGroundInterface;
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

enum IK_SOLVER_INDEX {
  IK_SOLVER_INDEX_UNKNOWN_0,
  IK_SOLVER_INDEX_UNKNOWN_1,
  IK_SOLVER_INDEX_UNKNOWN_2,
  IK_SOLVER_INDEX_UNKNOWN_3,
  IK_SOLVER_INDEX_UNKNOWN_4,
  IK_SOLVER_INDEX_UNKNOWN_5,
  IK_SOLVER_INDEX_UNKNOWN_6,
  IK_SOLVER_INDEX_UNKNOWN_7,
  IK_SOLVER_INDEX_UNKNOWN_8,
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

  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  GfComIK();
  ~GfComIK() override;
  void cleanup();
  fw::RotateIkSolver *createRotateBodyIK(const char *boneName);
  fw::SpineIkSolver *createSpineIK(const fw::ParamAdapter &param, const char *boneName, const char *endBoneName);
  fw::LookAtIkSolver *createLookAtIK(const fw::ParamAdapter &param, const char *boneName);
  fw::SphericalCoordinatesIkSolver *createSphericalCoordinatesIkSolver(const fw::ParamAdapter &param, const char *boneName);
  fw::SpineRotateIKSolver *createSpineRotateIkSolver(const fw::ParamAdapter &param, const char *boneName, const char *endBoneName);
  fw::TransLocalIkSolver *createTransEyeIkSolver(u32 index, const char *boneName);
  fw::RotateLocalIkSolver *createRotateEyeIkSolver(u32 index, const char *boneName);
  void changeLayer(u32 oldLayer, u32 newLayer) override;
  const mm::mtl::RTTI *getRTTI() const override;

  fw::IkResolver unknown10;                            // Inferred role: ik resolver; original member name unknown.
  mm::mtl::UniquePtr<fw::IKGroundInterface> unknown48; // Inferred role: ground; original member name unknown.
  u32 unknown50;                                       // Inferred role: foot count; original member name unknown.
  ViewerListener unknown58;                            // Inferred role: viewer listener; original member name unknown.
  void *unknown68;                                     // Inferred role: viewer; original member name unknown.
};

static_assert(offsetof(GfComIK, unknown10) == 0x10, "");
static_assert(offsetof(GfComIK, unknown48) == 0x48, "");
static_assert(offsetof(GfComIK, unknown50) == 0x50, "");
static_assert(offsetof(GfComIK, unknown58) == 0x58, "");
static_assert(offsetof(GfComIK, unknown68) == 0x68, "");
static_assert(sizeof(GfComIK) == 0x70, "");

} // namespace gf
