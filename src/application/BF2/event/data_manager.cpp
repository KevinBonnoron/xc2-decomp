#include "event/data_manager.h"

#include <stddef.h>

#include "event/manager.h"
#include "event/memory_manager.h"
#include "event/object_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

DataManager::OfsInfo::OfsInfo(const char *name) : unknown00(name) {
  unknown50 = mm::Mat44::identity;
  unknown90 = mm::Mat44::identity;
  unknownd0 = mm::Mat44::identity;
  unknown110 = mm::Vec3::zero;
  unknown120 = mm::Mat44::identity;
  unknown160 = mm::Vec3::zero;
}

DataManager::DataManager() : unknown98("default"), unknown120(nullptr) {}

DataManager::~DataManager() { clear(); }

void DataManager::clear() {
  for (size_t i = 0; i < unknown10.size(); i++) {
    if (unknown10[i]) {
      delete unknown10[i];
      unknown10[i] = nullptr;
    }
  }
  unknown10.clear();
  unknown98 = "default";
  unknowndc = "";
  unknown120 = nullptr;
}

void DataManager::setupScene() {
  unknown98 = Manager::get()->getSceneName();
  updateCurrent();
}

void DataManager::updateCurrent() {
  if (__builtin_strcmp(unknown98.c_str(), unknowndc.c_str()) == 0) {
    return;
  }
  unknown120 = searchScene(unknown98.c_str());
  if (!unknown120) {
    unknown120 = createScene(unknown98.c_str());
  }
  if (unknown120) {
    unknowndc = unknown98.c_str();
  }
}

void DataManager::startScene() {
  unknown98 = Manager::get()->getSceneName();
  updateCurrent();
}

DataManager::OfsInfo *DataManager::getCurrent() {
  updateCurrent();
  return unknown120;
}

DataManager::OfsInfo *DataManager::searchScene(const char *name) const {
  for (size_t i = 0; i < unknown10.size(); i++) {
    if (__builtin_strcmp(unknown10[i]->unknown00.c_str(), name) == 0) {
      return unknown10[i];
    }
  }
  return nullptr;
}

DataManager::OfsInfo *DataManager::createScene(const char *name) {
  OfsInfo *info = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) OfsInfo(name);
  unknown10.push_back(info);
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

void DataManager::setOffsetSrc(const mm::Vec3 &pos, f32 rotY, bool isKeep) {
  unknown120->unknown50.setRotY(-rotY);
  unknown120->unknown50.setTrans(mm::Vec3(-pos.x, -pos.y, -pos.z));
  unknown120->unknownd0 = unknown120->unknown50 * unknown120->unknown90;
  if (isKeep) {
    unknown120->unknown120 = unknown120->unknownd0;
  }
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
