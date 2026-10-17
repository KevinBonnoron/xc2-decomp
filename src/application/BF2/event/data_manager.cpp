#include "event/data_manager.h"

#include <stddef.h>

#include "event/manager.h"
#include "event/memory_manager.h"
#include "event/object_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

DataManager::OfsInfo::OfsInfo(const char *name) : name(name) {
  srcMatrix = mm::Mat44::identity;
  desMatrix = mm::Mat44::identity;
  offsetMatrix = mm::Mat44::identity;
  offsetVector = mm::Vec3::zero;
  keepMatrix = mm::Mat44::identity;
  keepVector = mm::Vec3::zero;
}

DataManager::DataManager() : mSceneName("default"), mCurrent(nullptr) {}

DataManager::~DataManager() { clear(); }

void DataManager::clear() {
  for (size_t i = 0; i < mScenes.size(); i++) {
    if (mScenes[i]) {
      delete mScenes[i];
      mScenes[i] = nullptr;
    }
  }
  mScenes.clear();
  mSceneName = "default";
  mCurrentSceneName = "";
  mCurrent = nullptr;
}

void DataManager::setupScene() {
  mSceneName = Manager::get()->getSceneName();
  updateCurrent();
}

void DataManager::updateCurrent() {
  if (__builtin_strcmp(mSceneName.c_str(), mCurrentSceneName.c_str()) == 0) {
    return;
  }
  mCurrent = searchScene(mSceneName.c_str());
  if (!mCurrent) {
    mCurrent = createScene(mSceneName.c_str());
  }
  if (mCurrent) {
    mCurrentSceneName = mSceneName.c_str();
  }
}

void DataManager::startScene() {
  mSceneName = Manager::get()->getSceneName();
  updateCurrent();
}

DataManager::OfsInfo *DataManager::getCurrent() {
  updateCurrent();
  return mCurrent;
}

DataManager::OfsInfo *DataManager::searchScene(const char *name) const {
  for (size_t i = 0; i < mScenes.size(); i++) {
    if (__builtin_strcmp(mScenes[i]->name.c_str(), name) == 0) {
      return mScenes[i];
    }
  }
  return nullptr;
}

DataManager::OfsInfo *DataManager::createScene(const char *name) {
  OfsInfo *info = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) OfsInfo(name);
  mScenes.push_back(info);
  return info;
}

size_t DataManager::getCharaNum() const { return mm::mtl::Singleton<ObjectManager>::getPtr()->getCharaCount(); }

bool DataManager::checkRadianTar(u32 axis) {
  if (axis < 6) {
    switch (axis) {
    case 4:
    case 5:
      return true;
    default:
      return false;
    }
  }
  if (axis < getCharaNum() + 6) {
    return false;
  }
  return false;
}

void DataManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    clear();
    break;
  case MSG_TYPE_SETUP_SCENE:
    setupScene();
    break;
  case MSG_TYPE_START_SCENE:
    startScene();
    break;
  case MSG_TYPE_CLEAR:
    clear();
    break;
  default:
    break;
  }
}

} // namespace event
