#include "framework/ik/ik_placement_ground_solver.h"

#include "anm/anm_pose.h"
#include "anm/anm_qs_transform.h"
#include "framework/ik/ik_foot_placement_solver.h"
#include "framework/ik/ik_raycaster.h"
#include "framework/reference_frame.h"
#include "fw/fw_param_manager.h"
#include "fw/fw_transform.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec4.h"

namespace fw {

PlacementGroundSolver::PlacementGroundSolver() : unknown58(0.3f), unknown5c(2), unknown60(0.0f), unknown64(false), unknown65(false), unknown68(nullptr) {}

PlacementGroundSolver::~PlacementGroundSolver() {}

FootPlacementIKSolver *PlacementGroundSolver::createFootPlacementIK(IKFootIndex index, ParamAdapter &param, const char *footName, const char *kneeName, const char *hipName, bool isMirror) {
  if (index >= unknown20.size()) {
    return nullptr;
  }

  FootPlacementIKSolver::Description description;
  description.unknown00 = footName;
  description.unknown08 = kneeName;
  description.unknown10 = hipName;
  description.unknown25 = isMirror;
  description.unknown28 = param;
  IKFootGroundInterface *ground = unknown68 != nullptr ? unknown68->getFootGround(index) : nullptr;
  FootPlacementIKSolver *solver = FootPlacementIKSolver::create(description, unknown10, *unknown18, ground);
  unknown20[index] = solver;
  if (solver != nullptr) {
    solver->release();
  }
  return solver;
}

void PlacementGroundSolver::solve(const UpdateInfo &info) {
  if (unknown68 == nullptr) {
    return;
  }

  bool isChanged = true;
  if (!unknown65) {
    isChanged = unknown60 < 0.0f;
    if (!unknown64 && !isChanged) {
      return;
    }
  }

  const Transform &transform = unknown10->unknown40;
  f32 lowest = transform.unknown00.y;
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      IKFootGroundInterface *ground = unknown68->getFootGround(static_cast<IKFootIndex>(i));
      if (ground != nullptr) {
        const mm::Vec3 *hitPos = ground->getHitPos();
        if (hitPos != nullptr) {
          lowest = lowest < hitPos->y ? lowest : hitPos->y;
        }
      }
    }
  }

  if (isChanged) {
    f32 offset;
    if (!unknown65) {
      offset = 0.0f;
    } else {
      offset = mm::clamp<f32>(lowest - transform.unknown00.y, -unknown58, 0.0f);
    }
    if (offset > unknown60) {
      f32 limit = unknown60 + 0.05f;
      offset = offset < limit ? offset : limit;
    } else {
      f32 limit = unknown60 - 0.03f;
      offset = offset > limit ? offset : limit;
    }
    if (offset < 0.0f) {
      anm::QsTransform transform = unknown18->getBoneModelSpace(0);
      transform.unknown00.y += offset;
      unknown18->setBoneModelSpace(0, transform, anm::Pose::PROPAGATE_TYPE_UNKNOWN_1);
    }
    unknown60 = offset;
  }

  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->solve(info);
    }
  }
}

void PlacementGroundSolver::setEnablePlacement(bool enable) {
  unknown64 = enable;
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->unknown003(enable);
    }
  }
}

void PlacementGroundSolver::overwriteRaycastUp(f32 distance) {
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->unknown001(distance);
    }
  }
}

void PlacementGroundSolver::resetRaycastUp() {
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->unknowna0 &= ~4;
    }
  }
}

void PlacementGroundSolver::overwriteRaycastDown(f32 distance) {
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->unknown002(distance);
    }
  }
}

void PlacementGroundSolver::resetRaycastDown() {
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->unknowna0 &= ~8;
    }
  }
}

void PlacementGroundSolver::setGroundAngle(const mm::Vec3 &angle) {
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->setGroundAngle(angle);
    }
  }
}

const mm::mtl::RTTI *PlacementGroundSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
