#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/ui_object.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIScreenObject : public UIObject {
public:
  enum Mode {
    MODE_RENDER_VIEW = 0,
    MODE_ON_MEMORY = 1,
  };

  static mm::mtl::RTTI m_rtti;

  u32 getOnMemoryPixelSize() const;
  void *getOnMemoryBuffer() const;
  void swapOnMemoryBuffer();

  u32 mode;
  u8 _10c[0x110 - 0x10c];
  u32 renderIndex;
};

static_assert(offsetof(UIScreenObject, mode) == 0x108, "");
static_assert(offsetof(UIScreenObject, renderIndex) == 0x110, "");

} // namespace ui
