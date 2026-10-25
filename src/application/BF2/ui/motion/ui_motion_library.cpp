#include "ui/motion/ui_motion_library.h"

#include "framework/resource/common_resource.h"
#include "mm_mtl/hash.h"
#include "ui/motion/ui_motion_data.h"

namespace ui {

UIMotionLibrary::UIMotionLibrary() {}

UIMotionLibrary::~UIMotionLibrary() { reset(); }

UIMotionData *UIMotionLibrary::find(const char *name) {
  u32 hash = mm::mtl::hashStrCrc(name);
  for (MotionInfo *it = unknown08.begin(); it != unknown08.end(); ++it) {
    if (it->unknown00 == hash) {
      return it->unknown10;
    }
  }
  return nullptr;
}

void UIMotionLibrary::reset() {
  if (unknown08.capacity() != 0) {
    for (MotionInfo *it = unknown08.begin(); it != unknown08.end(); ++it) {
      if (it->unknown10 != nullptr) {
        delete it->unknown10;
        it->unknown10 = nullptr;
      }
      if (it->unknown08 != nullptr) {
        it->unknown08->release();
        it->unknown08 = nullptr;
      }
    }
    unknown08.destroy();
  }
}

bool UIMotionLibrary::isLoading() const {
  for (const MotionInfo *it = unknown08.begin(); it != unknown08.end(); ++it) {
    if (it->unknown10 == nullptr) {
      return true;
    }
  }
  return false;
}

} // namespace ui
