#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ui {

class UIEventManager : public mm::mtl::PtrSingleton<UIEventManager> {
public:
  void removeObjectListener(u32 handle);
};

} // namespace ui
