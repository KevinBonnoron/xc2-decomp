#pragma once
#include <stddef.h>

#include "mm_mtl/array.h"
#include "types.h"

namespace ui {

class UIInputSwitcher {
public:
  UIInputSwitcher(u32 size);
  virtual ~UIInputSwitcher();

  void clearInputObject();
  bool setInputObject(u32 index, u32 handle);
  u32 getInputHandle(u32 handle) const;
  u32 getInputObject(u32 index);
  void disable();
  void enable(u32 index);
  bool isActive(u32 unused);

  mm::mtl::Array<u32> unknown08; // Inferred role: input object handles; original member name unknown.
  s32 unknown20;                 // Inferred role: enabled index; original member name unknown.
};

static_assert(offsetof(UIInputSwitcher, unknown08) == 0x08, "");
static_assert(offsetof(UIInputSwitcher, unknown20) == 0x20, "");
static_assert(sizeof(UIInputSwitcher) == 0x28, "");

} // namespace ui
