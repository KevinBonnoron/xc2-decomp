#include "framework/ik/ik_two_chara_ground_solver.h"

#include "anm/anm_pose.h"
#include "framework/ik/ik_foot_placement_solver.h"
#include "framework/reference_frame.h"
#include "fw/fw_param_manager.h"
#include "fw/fw_transform.h"

namespace anm {
struct QsTransform;
} // namespace anm
namespace mm {
struct Vec3;
} // namespace mm

namespace fw {
class IKFootGroundInterface;
struct UpdateInfo;

TwoCharaGroundSolver::TwoCharaGroundSolver()
    : unknown90(0.3f), unknown94(4), unknown98(0), unknowna0(0), unknowna8(0), unknownac(0.0f), unknownb0(0.0f), unknownb4(0xffff), unknownb6(0xffff), unknownb8(false), unknownb9(false),
      unknownba(true), unknownbb(true), unknownc0(nullptr) {}

TwoCharaGroundSolver::~TwoCharaGroundSolver() {}

FootPlacementIKSolver *TwoCharaGroundSolver::createFootPlacementIKMain(IKFootIndex index, ParamAdapter param, const char *footName, const char *kneeName, const char *hipName, bool isMirror) {
  if (index >= unknown20.size()) {
    return nullptr;
  }

  FootPlacementIKSolver::Description description;
  description.unknown00 = footName;
  description.unknown08 = kneeName;
  description.unknown10 = hipName;
  description.unknown25 = isMirror;
  description.unknown28 = param;
  IKFootGroundInterface *ground = unknownc0 != nullptr ? unknownc0->getFootGround(index) : nullptr;
  FootPlacementIKSolver *solver = FootPlacementIKSolver::create(description, unknown10, *unknown18, ground);
  unknown20[index] = solver;
  if (solver != nullptr) {
    solver->release();
  }
  return solver;
}

FootPlacementIKSolver *TwoCharaGroundSolver::createFootPlacementIKSub(IKFootIndex index, ParamAdapter param, const char *footName, const char *kneeName, const char *hipName, bool isMirror) {
  if (index >= unknown58.size()) {
    return nullptr;
  }

  FootPlacementIKSolver::Description description;
  description.unknown00 = footName;
  description.unknown08 = kneeName;
  description.unknown10 = hipName;
  description.unknown25 = isMirror;
  description.unknown28 = param;
  IKFootGroundInterface *ground = unknownc0 != nullptr ? unknownc0->getFootGround(index) : nullptr;
  FootPlacementIKSolver *solver = FootPlacementIKSolver::create(description, unknown10, *unknown18, ground);
  unknown58[index] = solver;
  if (solver != nullptr) {
    solver->release();
  }
  return solver;
}

void TwoCharaGroundSolver::doPlacementFoot(const UpdateInfo &info) {
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      if (unknowna8 == 1) {
        unknown20[i]->unknowna0 &= ~1;
      }
      unknown20[i]->solve(info);
    }
  }
  for (u32 i = 0; i < unknown58.size(); i++) {
    if (unknown58[i].get() != nullptr) {
      unknown58[i]->solve(info);
    }
  }
}

void TwoCharaGroundSolver::calcMainBodyTransform(Transform *result) {
  const anm::QsTransform &bone = unknown18->getBoneModelSpace(unknownb4);
  TransformUtil::mul(unknown10->unknown40, bone, 1.0f, result);
}

void TwoCharaGroundSolver::calcSubBodyTransform(Transform *result) {
  const anm::QsTransform &bone = unknown18->getBoneModelSpace(unknownb6);
  TransformUtil::mul(unknown10->unknown40, bone, 1.0f, result);
}

void TwoCharaGroundSolver::setEnablePlacement(bool enable) {
  unknownb8 = enable;
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->unknown003(enable && unknownba);
    }
  }
  for (u32 i = 0; i < unknown58.size(); i++) {
    if (unknown58[i].get() != nullptr) {
      unknown58[i]->unknown003(enable && unknownbb);
    }
  }
}

void TwoCharaGroundSolver::setGroundAngle(const mm::Vec3 &angle) {
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->setGroundAngle(angle);
    }
  }
  for (u32 i = 0; i < unknown58.size(); i++) {
    if (unknown58[i].get() != nullptr) {
      unknown58[i]->setGroundAngle(angle);
    }
  }
}

void TwoCharaGroundSolver::overwriteRaycastUp(f32 distance) {
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->unknown001(distance);
    }
  }
  for (u32 i = 0; i < unknown58.size(); i++) {
    if (unknown58[i].get() != nullptr) {
      unknown58[i]->unknown001(distance);
    }
  }
}

void TwoCharaGroundSolver::resetRaycastUp() {
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->unknowna0 &= ~4;
    }
  }
  for (u32 i = 0; i < unknown58.size(); i++) {
    if (unknown58[i].get() != nullptr) {
      unknown58[i]->unknowna0 &= ~4;
    }
  }
}

void TwoCharaGroundSolver::overwriteRaycastDown(f32 distance) {
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->unknown002(distance);
    }
  }
  for (u32 i = 0; i < unknown58.size(); i++) {
    if (unknown58[i].get() != nullptr) {
      unknown58[i]->unknown002(distance);
    }
  }
}

void TwoCharaGroundSolver::resetRaycastDown() {
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->unknowna0 &= ~8;
    }
  }
  for (u32 i = 0; i < unknown58.size(); i++) {
    if (unknown58[i].get() != nullptr) {
      unknown58[i]->unknowna0 &= ~8;
    }
  }
}

const mm::mtl::RTTI *TwoCharaGroundSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
