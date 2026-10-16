#pragma once
#include "mm_mtl/singleton.h"

namespace ui {

class UITagParser : public mm::mtl::PtrSingleton<UITagParser> {
public:
  bool parseTag(const char *text, const char *tag);
};

} // namespace ui
