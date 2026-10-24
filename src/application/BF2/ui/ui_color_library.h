#pragma once
#include <stddef.h>

#include "mm_math/mm_col4.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace ui {

class UIColorLibrary : public mm::mtl::PtrSingleton<UIColorLibrary> {
public:
  struct ColorInfo {
    u32 unknown00;      // Inferred role: hash; original member name unknown.
    mm::Col4 unknown04; // Inferred role: color; original member name unknown.
  };

  UIColorLibrary();
  virtual ~UIColorLibrary();
  void reset();
  bool add(const char *name, const mm::Col4 &color);
  bool find(const char *name, mm::Col4 &color);

  mm::mtl::Vector<ColorInfo> unknown08; // Inferred role: colors; original member name unknown.
};

static_assert(sizeof(UIColorLibrary::ColorInfo) == 0x14, "");
static_assert(offsetof(UIColorLibrary, unknown08) == 0x08, "");
static_assert(sizeof(UIColorLibrary) == 0x30, "");

} // namespace ui
