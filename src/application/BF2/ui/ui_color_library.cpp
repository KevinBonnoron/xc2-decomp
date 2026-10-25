#include "ui/ui_color_library.h"

#include "mm_mtl/hash.h"
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

bool UIColorLibrary::add(const char *name, const mm::Col4 &color) {
  u32 hash = mm::mtl::hashStrCrc(name);
  for (ColorInfo *it = unknown08.begin(); it != unknown08.end(); ++it) {
    if (it->unknown00 == hash) {
      it->unknown04 = color;
      return true;
    }
  }

  ColorInfo info;
  info.unknown00 = hash;
  info.unknown04 = color;
  unknown08.push_back(info);
  return true;
}

bool UIColorLibrary::find(const char *name, mm::Col4 &color) {
  u32 hash = mm::mtl::hashStrCrc(name);
  color = mm::Col4::white;
  for (ColorInfo *it = unknown08.begin(); it != unknown08.end(); ++it) {
    if (it->unknown00 == hash) {
      color = it->unknown04;
      return true;
    }
  }
  return false;
}

} // namespace ui
