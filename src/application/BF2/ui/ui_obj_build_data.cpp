#include "ui/ui_obj_build_data.h"

#include <string.h>

namespace ui {

UIObjBuildData::UIObjBuildData(mm::mtl::IAllocator *allocator) : unknown58(allocator) {
  if (allocator != nullptr) {
    unknown08.setAllocator(allocator);
    unknown30.setAllocator(unknown58);
  }
}

UIObjBuildData::~UIObjBuildData() { clear(); }

void UIObjBuildData::clear() {
  for (u32 i = 0; i < unknown08.size(); i++) {
    if (unknown08[i].unknown00.capacity() != 0) {
      unknown08[i].unknown00.destroy();
    }
  }
  if (unknown08.capacity() != 0) {
    unknown08.destroy();
  }
  if (unknown30.capacity() != 0) {
    unknown30.destroy();
  }
}

u32 UIObjBuildData::getObjectNum() const { return unknown08.size(); }

u32 UIObjBuildData::searchObject(const char *name) {
  for (u32 i = 0; i < unknown08.size(); i++) {
    if (unknown08[i].unknown28 < static_cast<u32>(unknown30.size())) {
      if (strcmp(unknown30[unknown08[i].unknown28], name) == 0) {
        return i;
      }
    }
  }
  return static_cast<u32>(-1);
}

} // namespace ui
