#include "framework/resource/resource_manager.h"

#include <string.h>

#include "framework/framework.h"
#include "framework/resource/resource_object.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/hash.h"
#include "mm_mtl/reference_object.h"

namespace fw {

mtl::ALLOC_HANDLE ResourceManager::getMemSYS() { return Framework::getMemHandle(); }

mtl::ALLOC_HANDLE ResourceManager::getMemTMP() { return m_hMemoryTemp; }

void ResourceManager::setMemTMP(mtl::ALLOC_HANDLE handle) { m_hMemoryTemp = handle; }

u32 ResourceManager::getHash(const char *name) { return mm::mtl::hashStrCrc(name); }

ResourceManager::ResourceManager(mm::mtl::IAllocator *allocator, u32 capacity) : unknown518(allocator), unknown520(0), unknown524(0), unknown528(0), unknown52c(0), unknown530(false) {
  for (int type = 0; type < 32; type++) {
    unknown18[type].setAllocator(allocator);
    unknown18[type].reserve(capacity);
  }
}

void ResourceManager::enterFinalizeApplet() {
  unknown530 = true;
  unknown52c = 2;
}

void ResourceManager::addDelayReleaseExtention(const char *extension) {
  ResourceManager *manager = get();
  if (manager == nullptr) {
    return;
  }
  if (extension[0] == '.') {
    extension++;
  }
  if (mm::mtl::find(manager->unknown8548.begin(), manager->unknown8548.end(), extension) == manager->unknown8548.end()) {
    manager->unknown8548.push_back(extension);
  }
}

void ResourceManager::update(const UpdateInfo &info) {
  updateSafeReleaseList(false);
  unknown520 = 0;
  for (int type = 0; type < 32; type++) {
    for (u32 i = 0; i < unknown18[type].size(); i++) {
      if (unknown18[type][i] != nullptr) {
        unknown18[type][i]->update();
      }
    }
  }
}

bool ResourceManager::isLoaded() {
  for (int type = 0; type < 32; type++) {
    for (u32 i = 0; i < unknown18[type].size(); i++) {
      if (unknown18[type][i] != nullptr && !unknown18[type][i]->valid()) {
        return false;
      }
    }
  }
  return true;
}

void ResourceManager::updateSafeReleaseList(bool isForce) {
  unknown001 *it = unknown4540.begin();
  while (it != unknown4540.end()) {
    it->unknown08--;
    if (isForce || it->unknown08 < 1) {
      mm::mtl::safeRelease(it->unknown00);
      it = unknown4540.erase(it);
    } else {
      it++;
    }
  }
}

void ResourceManager::addResource(ResourceObject *resource) {
  mm::mtl::Vector<ResourceObject *> &resources = unknown18[resource->unknown0c];
  ResourceObject **it = resources.begin();
  while (it != resources.end() && resource->unknown28 >= (*it)->unknown28) {
    it++;
  }
  if (it == resources.end()) {
    resources.push_back(resource);
  } else {
    resources.insert(it, resource);
  }
}

void ResourceManager::removeResource(ResourceObject *resource) {
  mm::mtl::Vector<ResourceObject *> &resources = unknown18[resource->unknown0c];
  ResourceObject **it = mm::mtl::find(resources.begin(), resources.end(), resource);
  if (it != resources.end()) {
    resources.erase(it);
  }
}

ResourceObject *ResourceManager::searchResource(u32 type, mtl::ALLOC_HANDLE handle, const char *path) {
  u32 hash = mm::mtl::hashStrCrc(path);
  for (u32 i = 0; i < unknown18[type].size(); i++) {
    if (unknown18[type][i] != nullptr && unknown18[type][i]->unknown10 == handle && unknown18[type][i]->unknown20 == hash && strcmp(unknown18[type][i]->unknown2c.c_str(), path) == 0) {
      return unknown18[type][i];
    }
  }
  return nullptr;
}

ResourceObject *ResourceManager::searchResource(u32 type, mm::mtl::IAllocator *allocator, const char *path) {
  u32 hash = mm::mtl::hashStrCrc(path);
  for (u32 i = 0; i < unknown18[type].size(); i++) {
    if (unknown18[type][i] != nullptr && unknown18[type][i]->unknown18 == allocator && unknown18[type][i]->unknown20 == hash && strcmp(unknown18[type][i]->unknown2c.c_str(), path) == 0) {
      return unknown18[type][i];
    }
  }
  return nullptr;
}

void ResourceManager::addSafeObject(mm::mtl::ReferenceObject *object, eResourceType type) {
  unknown001 *it = unknown538.begin();
  while (it != unknown538.end()) {
    if (it->unknown00 == object) {
      it->unknown08++;
      break;
    }
    it++;
  }
  if (it == unknown538.end()) {
    object->addRef();
    unknown001 safeObject;
    safeObject.unknown00 = object;
    safeObject.unknown08 = 1;
    safeObject.unknown0c = type;
    unknown538.push_back(safeObject);
  }
}

} // namespace fw
