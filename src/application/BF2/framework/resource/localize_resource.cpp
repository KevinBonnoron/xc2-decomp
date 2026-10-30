#include "framework/resource/localize_resource.h"

#include "framework/lang_util.h"
#include "framework/resource/resource_manager.h"
#include "ml/dev_file_th.h"
#include "mtl/alloc_handle.h"

namespace fw {
enum LOAD_PRIO : int;

LocalizeResource::LocalizeResource(mtl::ALLOC_HANDLE handle, LOAD_PRIO priority) : CommonResource(handle, priority, 0, 0), unknown154(unknown001_0) {}

LocalizeResource::LocalizeResource(mm::mtl::IAllocator *allocator, LOAD_PRIO priority) : CommonResource(allocator, priority, 0, 0), unknown154(unknown001_0) {}

LocalizeResource::~LocalizeResource() { ; }

LocalizeResource *LocalizeResource::request(mtl::ALLOC_HANDLE handle, const char *path, int priority, bool isSafe) {
  LocalizeResource *resource = static_cast<LocalizeResource *>(CommonResource::search(handle, path));
  if (resource != nullptr) {
    resource->addRef();
    return resource;
  }

  resource = new (ResourceManager::getMemSYS()) LocalizeResource(handle, static_cast<LOAD_PRIO>(priority));
  if (resource != nullptr) {
    resource->unknownd0 = path;
    resource->setPath(path);
    resource->addRef();
    resource->update();
  }

  return resource;
}

LocalizeResource *LocalizeResource::request(mm::mtl::IAllocator *allocator, const char *path, int priority, bool isSafe) {
  LocalizeResource *resource = static_cast<LocalizeResource *>(CommonResource::search(allocator, path));
  if (resource != nullptr) {
    resource->addRef();
    return resource;
  }

  resource = new (ResourceManager::getMemSYS()) LocalizeResource(allocator, static_cast<LOAD_PRIO>(priority));
  if (resource != nullptr) {
    resource->unknownd0 = path;
    resource->setPath(path);
    resource->addRef();
    resource->update();
  }

  return resource;
}

const char *LocalizeResource::getAssetName() const { return unknownd0.empty() ? nullptr : unknownd0.c_str(); }

void LocalizeResource::update() {
  if (unknown154 == unknown001_4) {
    bool wasValid = valid();
    CommonResource::update();
    if (!unknownd0.empty() && wasValid != valid()) {
      unknown2c = unknownd0;
    }

    return;
  }

  if (LangUtil::getLangType() == 0) {
    unknown154 = unknown001_4;
    return;
  }

  mm::mtl::FixStr<128> filePath;
  switch (unknown154) {
  case unknown001_0:
    makeLocalizeFilePath(filePath, LangUtil::getLangFolder());
    ml::DevFileTh::checkValidFile(filePath.c_str(), this);
    unknown154 = unknown001_2;
    break;
  case unknown001_1:
    makeLocalizeFilePath(filePath, mm::mtl::FixStr<16>("us"));
    ml::DevFileTh::checkValidFile(filePath.c_str(), this);
    unknown154 = unknown001_3;
    break;
  default:
    break;
  }
}

bool LocalizeResource::OnFileEvent(ml::EventFileTh *event) {
  if (event == nullptr) {
    return false;
  }

  if (event->type == ml::EventFileTh::TYPE_VALID) {
    mm::mtl::FixStr<128> filePath;
    switch (unknown154) {
    case unknown001_2:
      makeLocalizeFilePath(filePath, LangUtil::getLangFolder());
      break;
    case unknown001_3:
      makeLocalizeFilePath(filePath, mm::mtl::FixStr<16>("us"));
      break;
    default:
      break;
    }

    unknown2c = filePath;
  } else if (unknown154 == unknown001_2 && LangUtil::getLangType() != 1 && LangUtil::getLangType() != 6 && LangUtil::getLangType() != 11) {
    unknown154 = unknown001_1;
    return true;
  }

  unknown154 = unknown001_4;
  return true;
}

} // namespace fw
