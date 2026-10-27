#include "gf/object/component/behavior/plugin/gf_foot_ik_controller_plugin.h"

#include "framework/anim/anim_manager.h"
#include "framework/ik/ik_placement_ground_solver.h"
#include "framework/ik/ik_slope_ground_solver.h"
#include "framework/ik/ik_two_chara_ground_solver.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/gf_com_ik.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

namespace fw {
class IkSolver;
} // namespace fw

namespace gf {

template <typename T> static T *castSolver(const mm::mtl::IntrusivePtr<fw::IkSolver> &solver) {
  if (solver.get() == nullptr) {
    return nullptr;
  }
  return mm::mtl::dynamicCast<T>(solver.get());
}

constexpr u32 IK_SOLVER_SLOPE = 0;
constexpr u32 IK_SOLVER_GROUND = 2;

FootIkControllerPlugin::FootIkControllerPlugin() : unknown10(nullptr), unknown18(MODE_UNKNOWN_0), unknown1c(false), unknown1d(false), unknown1e(0), unknown1f(true), unknown20(false) {}

bool FootIkControllerPlugin::setup(GfComBehavior &behavior) {
  unknown10 = &behavior;
  const GfComIK *ik = behavior.unknown08->getComponent<GfComIK>();
  if (ik != nullptr) {
    const mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::IkSolver>> &solvers = ik->unknown10.unknown10;
    fw::PlacementGroundSolver *placement = castSolver<fw::PlacementGroundSolver>(solvers[IK_SOLVER_GROUND]);
    if (castSolver<fw::SlopeGroundSolver>(solvers[IK_SOLVER_SLOPE]) != nullptr) {
      unknown18 = MODE_UNKNOWN_2;
      if (placement != nullptr) {
        unknown1c = true;
      }
    } else if (placement != nullptr) {
      unknown18 = MODE_UNKNOWN_1;
    }
    if (castSolver<fw::TwoCharaGroundSolver>(solvers[IK_SOLVER_GROUND]) != nullptr) {
      unknown18 = MODE_UNKNOWN_3;
    }
  }

  bool enable = false;
  if ((getASMStateAttribute(behavior) & 1) != 0) {
    enable = unknown1f;
  }
  setGroundPlacement(enable);
  return true;
}

u64 FootIkControllerPlugin::getASMStateAttribute(GfComBehavior &behavior) const {
  GfComAsm *comAsm = behavior.unknown08->getComponent<GfComAsm>();
  if (comAsm != nullptr) {
    return comAsm->getAttribute(static_cast<AsmCategory>(0), ANIM_LAYER_BASE);
  }
  return 0;
}

void FootIkControllerPlugin::setGroundPlacement(bool enable) {
  if (unknown10 == nullptr) {
    return;
  }

  const GfComIK *ik = unknown10->unknown08->getComponent<GfComIK>();
  if (ik != nullptr) {
    const mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::IkSolver>> &solvers = ik->unknown10.unknown10;
    if (unknown18 == MODE_UNKNOWN_1) {
      fw::PlacementGroundSolver *solver = castSolver<fw::PlacementGroundSolver>(solvers[IK_SOLVER_GROUND]);
      if (solver != nullptr) {
        solver->setEnablePlacement(enable);
      }
    } else if (unknown18 == MODE_UNKNOWN_2) {
      fw::SlopeGroundSolver *solver = castSolver<fw::SlopeGroundSolver>(solvers[IK_SOLVER_SLOPE]);
      if (solver != nullptr) {
        solver->setEnablePlacement(enable);
        solver->unknown88 = enable;
      }
    } else if (unknown18 == MODE_UNKNOWN_3) {
      fw::TwoCharaGroundSolver *solver = castSolver<fw::TwoCharaGroundSolver>(solvers[IK_SOLVER_GROUND]);
      if (solver != nullptr) {
        solver->setEnablePlacement(enable);
      }
    }
  }
  unknown1d = enable;
}

void FootIkControllerPlugin::cleanup(GfComBehavior &) { unknown10 = nullptr; }

void FootIkControllerPlugin::onActivate() {}

void FootIkControllerPlugin::onDeactivate() {}

void FootIkControllerPlugin::update(GfComBehavior &behavior, const fw::UpdateInfo &) {
  u64 attribute = getASMStateAttribute(behavior);
  bool enable = false;
  if ((attribute & 1) != 0) {
    enable = unknown1f;
  }
  setGroundPlacement(enable);

  bool isFit = false;
  if (unknown1d) {
    isFit = ((static_cast<u32>(unknown18) | 2) == 3) & (unknown1e != 0 || (attribute & 8) != 0);
  }

  const GfComIK *ik = behavior.unknown08->getComponent<GfComIK>();
  if (ik != nullptr) {
    const mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::IkSolver>> &solvers = ik->unknown10.unknown10;
    fw::PlacementGroundSolver *placement = castSolver<fw::PlacementGroundSolver>(solvers[IK_SOLVER_GROUND]);
    if (placement != nullptr) {
      placement->unknown65 = isFit;
    }
    fw::TwoCharaGroundSolver *twoChara = castSolver<fw::TwoCharaGroundSolver>(solvers[IK_SOLVER_GROUND]);
    if (twoChara != nullptr) {
      twoChara->unknownb9 = isFit;
    }
  }

  if (unknown18 == MODE_UNKNOWN_3) {
    ik = behavior.unknown08->getComponent<GfComIK>();
    if (ik != nullptr) {
      const mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::IkSolver>> &solvers = ik->unknown10.unknown10;
      fw::TwoCharaGroundSolver *twoChara = castSolver<fw::TwoCharaGroundSolver>(solvers[IK_SOLVER_GROUND]);
      if (twoChara != nullptr) {
        if ((attribute & 2) == 0 && !unknown20) {
          twoChara->unknowna8 = 0;
        } else {
          twoChara->unknowna8 = 1;
        }
      }
    }
  }
}

void FootIkControllerPlugin::switchMode(Mode mode) {
  if (unknown1c && unknown18 != mode) {
    unknown1e = 0;
    setGroundPlacement(false);
    unknown18 = mode;
  }
}

} // namespace gf
