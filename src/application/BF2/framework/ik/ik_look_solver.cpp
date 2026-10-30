#include "framework/ik/ik_look_solver.h"

#include "framework/ik/ik_look_at_solver.h"
#include "framework/ik/ik_spine_solver.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/reference_object.h"

namespace fw {

LookIkSolver *LookIkSolver::create(const Description &description, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose) {
  // __LINE__ of the game: it is the line argument of operator new.
#line 26
  LookIkSolver *solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) LookIkSolver();
  solver->addRef();
  solver->createImpl(description, frame, pose);
  return solver;
}

bool LookIkSolver::createImpl(const Description &description, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose) {
  bind(frame, pose);
  unknown30 = description;
  return true;
}

LookIkSolver::LookIkSolver() : unknown30(0.5f, 0.5f), unknown38(true) {}

LookIkSolver::~LookIkSolver() {}

LookAtIkSolver *LookIkSolver::createLookAtIK(const ParamAdapter &param, const char *boneName) {
  LookAtIkSolver *solver = LookAtIkSolver::create(param, boneName, unknown10, *unknown18);
  unknown28 = solver;
  mm::mtl::safeRelease(solver);
  return unknown28.get();
}

SpineIkSolver *LookIkSolver::createSpineIK(const ParamAdapter &param, const char *boneName, const char *endBoneName) {
  SpineIkSolver *solver = SpineIkSolver::create(param, boneName, endBoneName, unknown10, *unknown18);
  unknown20 = solver;
  mm::mtl::safeRelease(solver);
  return unknown20.get();
}

void LookIkSolver::fadeIn(f32 time) {
  if (unknown20.get() != nullptr && unknown38) {
    unknown20.get()->fadeIn(time);
  }

  if (unknown28.get() != nullptr) {
    unknown28.get()->fadeIn(time);
  }
}

void LookIkSolver::fadeOut(f32 time) {
  if (unknown20.get() != nullptr && unknown38) {
    unknown20.get()->fadeOut(time);
  }

  if (unknown28.get() != nullptr) {
    unknown28.get()->fadeOut(time);
  }
}

void LookIkSolver::setTarget(const mm::Vec3 &target) {
  if (unknown20.get() != nullptr && unknown38) {
    unknown20.get()->unknown50 = target;
  }

  if (unknown28.get() != nullptr) {
    unknown28.get()->unknowna0 = target;
  }
}

void LookIkSolver::startTargetFade(f32 time) {
  if (unknown20.get() != nullptr && unknown38) {
    unknown20.get()->startTargetFade(time);
  }

  if (unknown28.get() != nullptr) {
    unknown28.get()->startTargetFade(time);
  }
}

void LookIkSolver::setEnableSpine(bool enable) {
  if (unknown20.get() == nullptr) {
    return;
  }

  if (unknown38 == enable) {
    return;
  }

  bool isSpineEnable = unknown20->isEnable();
  if (enable) {
    if (!isSpineEnable && unknown28->isEnable()) {
      unknown20->fadeIn(unknown30.unknown04);
    }
  } else if (isSpineEnable || unknown20->unknown24 == IkFadeSolver::unknown002_1) {
    unknown20->fadeOut(unknown30.unknown00);
  }

  unknown38 = enable;
}

void LookIkSolver::setFrontMS(const mm::Vec3 &front) {
  if (unknown20.get() != nullptr) {
    unknown20.get()->unknown70 = front;
  }

  if (unknown28.get() != nullptr) {
    unknown28.get()->unknown60 = front;
  }
}

void LookIkSolver::setTargetUpRatio(f32 ratio) {
  if (unknown28.get() != nullptr) {
    unknown28.get()->unknowncc = ratio;
  }
}

void LookIkSolver::setTargetDownRatio(f32 ratio) {
  if (unknown28.get() != nullptr) {
    unknown28.get()->unknownd0 = ratio;
  }
}

void LookIkSolver::solve(const UpdateInfo &info) {
  if (unknown20.get() != nullptr) {
    unknown20.get()->solve(info);
  }

  if (unknown28.get() != nullptr) {
    unknown28.get()->solve(info);
  }
}

const mm::mtl::RTTI *LookIkSolver::getRTTI() const { return &m_rtti; }

bool LookIkSolver::isEnable() const {
  if (unknown28.get() != nullptr && unknown28.get()->isEnable()) {
    return true;
  }

  if (unknown20.get() != nullptr && unknown20.get()->isEnable()) {
    return true;
  }

  return false;
}

} // namespace fw
