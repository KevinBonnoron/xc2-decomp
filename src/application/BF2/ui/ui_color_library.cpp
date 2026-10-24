#include "ui/ui_color_library.h"

#include "ui/ui_util.h"

namespace ui {

UIColorLibrary::UIColorLibrary() {
  unknown08.setAllocator(UIUtil::getProgAllocator());
  unknown08.reserve(8);
}

UIColorLibrary::~UIColorLibrary() { reset(); }

void UIColorLibrary::reset() {
  unknown08.clear();
  if (unknown08.capacity() != 0) {
    unknown08.destroy();
  }
}

} // namespace ui
