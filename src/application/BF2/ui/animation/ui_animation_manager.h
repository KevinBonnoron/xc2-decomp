#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ui {

class UIAnimationManager : public mm::mtl::PtrSingleton<UIAnimationManager> {
public:
  void changeEventHandleObject(u32 object, u32 handler);
};

} // namespace ui
