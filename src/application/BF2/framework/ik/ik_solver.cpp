#include "framework/ik/ik_solver.h"

#include "anm/anm_pose.h"
#include "framework/reference_frame.h"
#include "fw/fw_update_info.h"
#include "mm_mtl/intrusive_ptr.h" // IWYU pragma: keep
#include "mm_mtl/vector.h"        // IWYU pragma: keep

namespace fw {

IkSolver::IkSolver() : unknown18(nullptr) {}

void IkSolver::unbind() {
  unknown10 = nullptr;
  if (unknown18 != nullptr) {
    unknown18->release();
    unknown18 = nullptr;
  }
}

IkSolver::~IkSolver() { unbind(); }

void IkSolver::bind(mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose) {
  unknown10 = frame;
  this->unknown18 = &pose;
  pose.addRef();
}

IkFadeSolver::IkFadeSolver() : unknown20(0.0f), unknown24(FADE_STATE_NONE), unknown28(0.0f), unknown2c(0.0f), unknown30(0.0f) {}

void IkFadeSolver::solve(const UpdateInfo &info) {
  switch (unknown24) {
  case FADE_STATE_IN: {
    unknown2c += info.unknown04;
    f32 rate = unknown2c / unknown28;
    if (rate >= 1.0f) {
      unknown20 = 1.0f;
      unknown24 = FADE_STATE_NONE;
    } else {
      unknown20 = calcBezier(rate, unknown30, 1.0f);
    }
    break;
  }
  case FADE_STATE_OUT: {
    unknown2c += info.unknown04;
    f32 rate = unknown2c / unknown28;
    if (rate >= 1.0f) {
      unknown20 = 0.0f;
      unknown24 = FADE_STATE_NONE;
      onDisable();
    } else {
      unknown20 = calcBezier(rate, unknown30, 0.0f);
    }
    break;
  }
  default:
    break;
  }

  if (isEnable()) {
    calcIK(info);
  }
}

f32 IkFadeSolver::calcBezier(f32 t, f32 start, f32 end) {
  f32 u = 1.0f - t;
  f32 tt = t * t;
  return start * (u * u * u + u * u * 3.0f * t) + end * (tt * (u * 3.0f) + tt * t);
}

void IkFadeSolver::fadeIn(f32 time) {
  f32 prevWeight = unknown20;
  if (time > 0.0f) {
    unknown28 = time;
    unknown30 = unknown20;
    unknown24 = FADE_STATE_IN;
  } else {
    unknown20 = 1.0f;
    unknown30 = 0.0f;
    unknown28 = 0.0f;
    unknown24 = FADE_STATE_NONE;
  }

  unknown2c = 0.0f;
  if (prevWeight == 0.0f) {
    onEnable();
  }
}

void IkFadeSolver::fadeOut(f32 time) {
  if (time > 0.0f) {
    unknown30 = unknown20;
    unknown28 = time;
    unknown24 = FADE_STATE_OUT;
  } else {
    unknown28 = 0.0f;
    unknown30 = 0.0f;
    unknown20 = 0.0f;
    unknown24 = FADE_STATE_NONE;
    onDisable();
  }

  unknown2c = 0.0f;
}

const mm::mtl::RTTI *IkSolver::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *IkFadeSolver::getRTTI() const { return &m_rtti; }

} // namespace fw

template void mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::IkSolver>>::destroy();
template void mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::IkSolver>>::expand(size_t, size_t);
template void mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::IkSolver>>::push_back(mm::mtl::IntrusivePtr<fw::IkSolver> const &);
