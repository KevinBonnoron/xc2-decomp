#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ui {

class UITimerManager : public mm::mtl::PtrSingleton<UITimerManager> {
public:
  u32 getTimerHandle(u32 object);
  void setTimerSpeedFactor(u32 timer, f32 speedFactor);
};

} // namespace ui
