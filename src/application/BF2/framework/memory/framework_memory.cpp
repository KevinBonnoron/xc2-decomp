#include "framework/memory/framework_memory.h"

#include "ml/ml_mem.h"
#include "ml/work_root.h"
#include "mm_mtl/hash.h"
#include "mtl/mem_manager.h"

namespace fw {

MemorySectionInfo::MemorySectionInfo() : unknown00(0), unknown08(0), unknown10(0x20), unknown14(true), unknown5c(mtl::ALLOCATOR_TYPE_PROGRAM) {}

FrameworkMemory::FrameworkMemory() : unknown20(false) {}

mtl::ALLOC_HANDLE FrameworkMemory::createSection(const MemorySectionInfo &info) {
  SectionRegistInfo &section = unknown08[info.unknown00];
  if (section.unknown60.isValid()) {
    return mtl::ALLOC_HANDLE();
  }
  mtl::ALLOC_HANDLE handle;
  if (info.unknown14) {
    handle = mtl::MemManager::create(info.unknown04, info.unknown08, info.unknown18.c_str(), true, info.unknown5c, info.unknown10);
  } else {
    handle = mtl::MemManager::create(info.unknown04, info.unknown08, info.unknown18.c_str(), false, info.unknown5c, info.unknown10);
  }
  if (handle.isValid()) {
    static_cast<MemorySectionInfo &>(section) = info;
    section.unknown60 = handle;
    section.unknown64 = mm::mtl::hashStrCrc(info.unknown18.c_str());
    section.unknown68.setMemHandle(handle);
  }
  return handle;
}

void FrameworkMemory::initialize(mtl::ALLOC_HANDLE handle, u32 sectionMax) {
  FrameworkMemory &memory = get();
  if (!memory.unknown20) {
    memory.unknown20 = true;
    memory.unknown28.setMemHandle(handle);
    memory.unknown08.setAllocator(&memory.unknown28);
    memory.unknown08.reserve(sectionMax);
  }
}

void FrameworkMemory::finalize() {
  FrameworkMemory &memory = get();
  if (memory.unknown20) {
    for (size_t i = 0; i < memory.unknown08.size(); i++) {
      if (memory.unknown08[i].unknown60.isValid()) {
        memory.removeSection(memory.unknown08[i].unknown60);
      }
    }
    memory.unknown08.destroy();
    memory.unknown20 = false;
  }
}

void FrameworkMemory::removeSection(mtl::ALLOC_HANDLE handle) {
  if (unknown20 && handle.isValid()) {
    for (size_t i = 0; i < unknown08.size(); i++) {
      if (unknown08[i].unknown60 == handle) {
        removeChildSection(handle);
        if (unknown08[i].unknown60.isValid()) {
          mtl::MemManager::erase(unknown08[i].unknown60);
          unknown08[i].unknown60 = mtl::ALLOC_HANDLE();
        }
        unknown08[i].unknown001();
        return;
      }
    }
  }
}

void FrameworkMemory::removeChildSection(mtl::ALLOC_HANDLE handle) {
  if (unknown20 && handle.isValid()) {
    for (size_t i = 0; i < unknown08.size(); i++) {
      if (unknown08[i].unknown60.isValid() && unknown08[i].unknown04 == handle) {
        removeChildSection(unknown08[i].unknown60);
        if (unknown08[i].unknown60.isValid()) {
          mtl::MemManager::erase(unknown08[i].unknown60);
          unknown08[i].unknown60 = mtl::ALLOC_HANDLE();
        }
        unknown08[i].unknown001();
        return;
      }
    }
  }
}

mtl::ALLOC_HANDLE FrameworkMemory::getMem(u32 section) {
  if (section == 1) {
    return ml::MlMem::getProductMem();
  }
  if (section == 2) {
    return ml::MlMem::getDebugMem();
  }
  if (section == 3) {
    return ml::WorkRoot::getMemTMP();
  }
  FrameworkMemory &memory = get();
  if (!memory.unknown20) {
    return mtl::ALLOC_HANDLE();
  }
  return memory.unknown08[section].unknown60;
}

mm::mtl::IAllocator *FrameworkMemory::getAllocator(u32 section) {
  if (section == 1) {
    return Allocator::getSysAllocator();
  }
  if (section == 2) {
    return Allocator::getDebAllocator();
  }
  if (section == 3) {
    return Allocator::getTmpAllocator();
  }
  FrameworkMemory &memory = get();
  if (!memory.unknown20) {
    return nullptr;
  }
  return &memory.unknown08[section].unknown68;
}

} // namespace fw
