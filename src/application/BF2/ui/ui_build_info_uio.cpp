#include "ui/ui_build_info_uio.h"

#include "framework/resource/common_resource.h"
#include "mm_mtl/fixstr.h"
#include "ui/ui_util.h"

namespace ui {

UIBuildInfoUIO::UIBuildInfoUIO(const char *name) : m_name(name), unknown10(nullptr) {
  mm::mtl::FixStr<128> fileName;
  UIUtil::makeMenuUIOFileName(fileName, name);
  fw::CommonResource *resource = fw::CommonResource::request(UIUtil::getResourceAllocator(), fileName.c_str(), 10, false);
  if (resource != nullptr) {
    unknown10 = resource;
  }
  unknown18.setAllocator(UIUtil::getProgAllocator());
}

UIBuildInfoUIO::~UIBuildInfoUIO() {
  if (unknown10 != nullptr) {
    unknown10->release();
    unknown10 = nullptr;
  }
}

const char *UIBuildInfoUIO::getName() const { return m_name; }

u32 UIBuildInfoUIO::getObjectNum() const { return isReady() ? static_cast<u32>(unknown18.size()) : 0; }

void UIBuildInfoUIO::getObjectData(u32 index, ObjectData &data) const {
  if (!isReady()) {
    return;
  }
  data = unknown18[index];
}

bool UIBuildInfoUIO::isReady() const { return unknown18.size() != 0; }

bool UIBuildInfoUIO::isValid() const { return unknown10 != nullptr; }

} // namespace ui
