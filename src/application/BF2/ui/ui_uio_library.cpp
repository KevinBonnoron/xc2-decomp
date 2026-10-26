#include "ui/ui_uio_library.h"

#include "framework/resource/common_resource.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/hash.h"
#include "ui/ui_util.h"

namespace ui {

UIUioLibrary::UIUioLibrary() {}

UIUioLibrary::~UIUioLibrary() { reset(); }

void UIUioLibrary::reset() {
  if (unknown08.capacity() != 0) {
    for (UioInfo *it = unknown08.begin(); it != unknown08.end(); ++it) {
      if (it->unknown08 != nullptr) {
        it->unknown08->release();
        it->unknown08 = nullptr;
      }
    }
    unknown08.destroy();
  }
}

bool UIUioLibrary::isLoading() const {
  for (const UioInfo *it = unknown08.begin(); it != unknown08.end(); ++it) {
    if (it->unknown08 != nullptr && !it->unknown08->valid()) {
      return true;
    }
  }
  return false;
}

bool UIUioLibrary::add(const char *name) {
  u32 hash = mm::mtl::hashStrCrc(name);
  if (unknown08.capacity() != 0) {
    for (UioInfo *it = unknown08.begin(); it != unknown08.end(); ++it) {
      if (it->unknown00 == hash) {
        return true;
      }
    }
  } else {
    unknown08.setAllocator(UIUtil::getProgAllocator());
    unknown08.reserve(8);
  }

  mm::mtl::FixStr<128> fileName;
  UIUtil::makeMenuUIOFileName(fileName, name);
  u32 storedHash = mm::mtl::hashStrCrc(name);
  fw::CommonResource *resource = fw::CommonResource::request(UIUtil::getResourceAllocator(), fileName.c_str(), 10, false);
  if (resource != nullptr) {
    UioInfo info;
    info.unknown00 = storedHash;
    info.unknown08 = resource;
    unknown08.push_back(info);
  }
  return true;
}

} // namespace ui
