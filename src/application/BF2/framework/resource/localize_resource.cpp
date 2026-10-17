#include "framework/resource/localize_resource.h"

#include "framework/lang_util.h"
#include "framework/resource/resource_manager.h"
#include "ml/dev_file_th.h"
#include "mtl/alloc_handle.h"

namespace fw {
enum LOAD_PRIO : int;

LocalizeResource::LocalizeResource(mtl::ALLOC_HANDLE handle, LOAD_PRIO priority)
    : CommonResource(handle, priority, 0, 0), checkState(CHECK_STATE_NONE) {}

LocalizeResource::LocalizeResource(mm::mtl::IAllocator *allocator, LOAD_PRIO priority)
    : CommonResource(allocator, priority, 0, 0), checkState(CHECK_STATE_NONE) {}

LocalizeResource::~LocalizeResource() { ; }

LocalizeResource *LocalizeResource::request(mtl::ALLOC_HANDLE handle, const char *path, int priority, bool isSafe) {
  LocalizeResource *resource = static_cast<LocalizeResource *>(CommonResource::search(handle, path));
  if (resource != nullptr) {
    resource->addRef();
    return resource;
  }

  resource = new (ResourceManager::getMemSYS()) LocalizeResource(handle, static_cast<LOAD_PRIO>(priority));
  if (resource != nullptr) {
    resource->localizedPath = path;
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
    resource->localizedPath = path;
    resource->setPath(path);
    resource->addRef();
    resource->update();
  }

  return resource;
}

const char *LocalizeResource::getAssetName() const { return localizedPath.empty() ? nullptr : localizedPath.c_str(); }

void LocalizeResource::update() {
  if (checkState == CHECK_STATE_DONE) {
    bool wasValid = valid();
    CommonResource::update();
    if (!localizedPath.empty() && wasValid != valid()) {
      path = localizedPath;
    }

    return;
  }

  if (LangUtil::getLangType() == 0) {
    checkState = CHECK_STATE_DONE;
    return;
  }

  mm::mtl::FixStr<128> filePath;
  switch (checkState) {
  case CHECK_STATE_NONE:
    makeLocalizeFilePath(filePath, LangUtil::getLangFolder());
    ml::DevFileTh::checkValidFile(filePath.c_str(), this);
    checkState = CHECK_STATE_LANG;
    break;
  case CHECK_STATE_RETRY:
    makeLocalizeFilePath(filePath, mm::mtl::FixStr<16>("us"));
    ml::DevFileTh::checkValidFile(filePath.c_str(), this);
    checkState = CHECK_STATE_DEFAULT;
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
    switch (checkState) {
    case CHECK_STATE_LANG:
      makeLocalizeFilePath(filePath, LangUtil::getLangFolder());
      break;
    case CHECK_STATE_DEFAULT:
      makeLocalizeFilePath(filePath, mm::mtl::FixStr<16>("us"));
      break;
    default:
      break;
    }

    path = filePath;
  } else if (checkState == CHECK_STATE_LANG && LangUtil::getLangType() != 1 && LangUtil::getLangType() != 6 && LangUtil::getLangType() != 11) {
    checkState = CHECK_STATE_RETRY;
    return true;
  }

  checkState = CHECK_STATE_DONE;
  return true;
}

} // namespace fw
