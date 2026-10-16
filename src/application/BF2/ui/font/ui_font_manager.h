#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ui {

class UIFontManager : public mm::mtl::PtrSingleton<UIFontManager> {
public:
  bool findFacePattern(const char *name, u32 &index);
};

} // namespace ui
