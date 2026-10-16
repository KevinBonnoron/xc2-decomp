#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ui {

class UIPadRead;

class UIManager : public mm::mtl::PtrSingleton<UIManager> {
public:
  UIManager(const UIPadRead *padRead, mtl::ALLOC_HANDLE handle);

  u8 _08[0x3d8 - 0x08];
  const UIPadRead *padRead;
};

static_assert(offsetof(UIManager, padRead) == 0x3d8, "");

} // namespace ui
