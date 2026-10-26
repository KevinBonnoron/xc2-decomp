#include "ui/motion/ui_motion_library.h"

#include "framework/resource/common_resource.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/hash.h"
#include "ui/motion/ui_motion_data.h"
#include "ui/ui_util.h"

namespace ui {

UIMotionLibrary::UIMotionLibrary() {}

UIMotionLibrary::~UIMotionLibrary() { reset(); }

bool UIMotionLibrary::add(const char *name) {
  u32 hash = mm::mtl::hashStrCrc(name);
  if (unknown08.capacity() != 0) {
    for (MotionInfo *it = unknown08.begin(); it != unknown08.end(); ++it) {
      if (it->unknown00 == hash) {
        return true;
      }
    }
  } else {
    unknown08.setAllocator(UIUtil::getProgAllocator());
    unknown08.reserve(8);
  }

  mm::mtl::FixStr<128> fileName;
  UIUtil::makeMenuUIMFileName(fileName, name);
  u32 storedHash = mm::mtl::hashStrCrc(name);
  fw::CommonResource *resource = fw::CommonResource::request(UIUtil::getResourceAllocator(), fileName.c_str(), 10, false);
  if (resource != nullptr) {
    MotionInfo info;
    info.unknown00 = storedHash;
    info.unknown08 = resource;
    info.unknown10 = nullptr;
    unknown08.push_back(info);
  }
  return true;
}

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
