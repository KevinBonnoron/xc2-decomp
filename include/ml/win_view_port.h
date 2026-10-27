#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"

namespace ml {

class WinViewPort {
public:
  WinViewPort();
  void setWorkSize(const mm::Pnt<int> &size);

  mm::Pnt<int> unknown00; // Inferred role: size; original member name unknown.
  mm::Pnt<int> unknown08; // Inferred role: work size; original member name unknown.
  mm::Pnt<int> unknown10; // Inferred role: scroll; original member name unknown.
  mm::Pnt<int> unknown18; // Inferred role: scroll range; original member name unknown.
  mm::Pnt<int> unknown20; // Inferred role: scroll range; original member name unknown.
};

static_assert(offsetof(WinViewPort, unknown08) == 0x08, "");
static_assert(offsetof(WinViewPort, unknown10) == 0x10, "");
static_assert(offsetof(WinViewPort, unknown18) == 0x18, "");
static_assert(offsetof(WinViewPort, unknown20) == 0x20, "");
static_assert(sizeof(WinViewPort) == 0x28, "");

} // namespace ml
