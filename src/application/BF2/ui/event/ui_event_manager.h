#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ui {

class UIEventCondition;

class UIEventManager : public mm::mtl::PtrSingleton<UIEventManager> {
public:
  void removeObjectListener(u32 handle);
  void addCondition(u32 handle, UIEventCondition *condition);
};

} // namespace ui
