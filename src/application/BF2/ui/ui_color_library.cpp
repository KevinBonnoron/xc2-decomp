#include "ui/ui_color_library.h"

#include "ui/ui_util.h"

namespace ui {

UIColorLibrary::UIColorLibrary() {
  colors.setAllocator(UIUtil::getProgAllocator());
  colors.reserve(8);
}

UIColorLibrary::~UIColorLibrary() { reset(); }

void UIColorLibrary::reset() {
  colors.clear();
  if (colors.capacity() != 0) {
    colors.release();
  }
}

} // namespace ui
