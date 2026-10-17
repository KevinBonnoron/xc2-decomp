#include "framework/ik/ik_solver.h"

#include "anm/anm_pose.h"
#include "framework/reference_frame.h"
#include "fw/fw_update_info.h"

namespace fw {

IkSolver::IkSolver() : pose(nullptr) {}

void IkSolver::unbind() {
  referenceFrame = nullptr;
  if (pose != nullptr) {
    pose->release();
    pose = nullptr;
  }
}

IkSolver::~IkSolver() { unbind(); }

void IkSolver::bind(mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose) {
  referenceFrame = frame;
  this->pose = &pose;
  pose.addRef();
}

IkFadeSolver::IkFadeSolver() : weight(0.0f), fadeState(FADE_STATE_NONE), fadeTime(0.0f), fadeElapsed(0.0f), fadeStartWeight(0.0f) {}

void IkFadeSolver::solve(const UpdateInfo &info) {
  switch (fadeState) {
  case FADE_STATE_IN: {
    fadeElapsed += info.deltaTime;
    f32 rate = fadeElapsed / fadeTime;
    if (rate >= 1.0f) {
      weight = 1.0f;
      fadeState = FADE_STATE_NONE;
    } else {
      weight = calcBezier(rate, fadeStartWeight, 1.0f);
    }
    break;
  }
  case FADE_STATE_OUT: {
    fadeElapsed += info.deltaTime;
    f32 rate = fadeElapsed / fadeTime;
    if (rate >= 1.0f) {
      weight = 0.0f;
      fadeState = FADE_STATE_NONE;
      onDisable();
    } else {
      weight = calcBezier(rate, fadeStartWeight, 0.0f);
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
  f32 prevWeight = weight;
  if (time > 0.0f) {
    fadeTime = time;
    fadeStartWeight = weight;
    fadeState = FADE_STATE_IN;
  } else {
    weight = 1.0f;
    fadeStartWeight = 0.0f;
    fadeTime = 0.0f;
    fadeState = FADE_STATE_NONE;
  }

  fadeElapsed = 0.0f;
  if (prevWeight == 0.0f) {
    onEnable();
  }
}

void IkFadeSolver::fadeOut(f32 time) {
  if (time > 0.0f) {
    fadeStartWeight = weight;
    fadeTime = time;
    fadeState = FADE_STATE_OUT;
  } else {
    fadeTime = 0.0f;
    fadeStartWeight = 0.0f;
    weight = 0.0f;
    fadeState = FADE_STATE_NONE;
    onDisable();
  }

  fadeElapsed = 0.0f;
}

const mm::mtl::RTTI *IkSolver::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *IkFadeSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
