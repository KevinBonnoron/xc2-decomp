#pragma once
#include "mm_mtl/singleton.h"

namespace mm {
struct Col4;
}

namespace ui {

class UIColorLibrary : public mm::mtl::PtrSingleton<UIColorLibrary> {
public:
  bool find(const char *name, mm::Col4 &color);
};

} // namespace ui
