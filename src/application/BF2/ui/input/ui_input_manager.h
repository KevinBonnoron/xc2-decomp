#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ui {

class UIInputManager : public mm::mtl::PtrSingleton<UIInputManager> {
public:
  u32 searchInputHandle(u32 handle);
  void migrateInput(u32 input, u32 handle);
};

} // namespace ui
