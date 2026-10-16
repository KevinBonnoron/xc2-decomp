#pragma once
#include "fw/fw_update_info.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_curve.h"
#include "ui/ctrl/ui_ctrl_manager.h"

namespace ui {

template <int N> class UICtrlSimple {
public:
  struct Range {
    Range() : from(0.0f), to(0.0f) {}

    f32 from;
    f32 to;
  };

  UICtrlSimple() : curve(nullptr), time(0.0f), duration(0.0f), speedFactor(1.0f), loop(false), pause(false) {
    for (int i = 0; i < N; i++) {
      values[i] = 0.0f;
    }
  }

  void update(f32 deltaTime) {
    if (deltaTime == 0.0f) {
      return;
    }
    if (time == duration || pause) {
      return;
    }

    time += speedFactor * deltaTime;
    if (time >= duration) {
      if (loop) {
        time -= duration;
      } else {
        time = duration;
      }
    }
    f32 rate = curve != nullptr ? curve->calc(time, 0.0f, 1.0f, duration) : time / duration;
    for (int i = 0; i < N; i++) {
      values[i] = ranges[i].from + rate * (ranges[i].to - ranges[i].from);
    }
  }

  bool isBusy() const { return time != duration; }

  Range ranges[N];
  f32 values[N];
  const UICtrlCurve *curve;
  f32 time;
  f32 duration;
  f32 speedFactor;
  bool loop;
  bool pause;
};

template <typename T> class UICtrlSimpleUpdater : public IUICtrlUpdater {
public:
  UICtrlSimpleUpdater() : ctrl(nullptr) {}

  virtual bool updateCtrl(const fw::UpdateInfo &info) {
    if (ctrl == nullptr) {
      return false;
    }
    ctrl->update(info.deltaTime);
    return ctrl->isBusy();
  }

  T *ctrl;
};

} // namespace ui
