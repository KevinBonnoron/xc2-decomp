#pragma once
#include "mm_mtl/singleton.h"

namespace ui {

class UIMotionData;

class UIMotionLibrary : public mm::mtl::PtrSingleton<UIMotionLibrary> {
public:
  UIMotionData *find(const char *name);
};

} // namespace ui
