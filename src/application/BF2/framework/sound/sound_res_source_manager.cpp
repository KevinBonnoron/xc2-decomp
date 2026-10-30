#include "framework/sound/sound_res_source_manager.h"

#include "anm/anm_array.h"
#include "anm/anm_string_ptr.h"
#include "framework/sound/sound_manager.h"

namespace fw {

SoundResSourceManager::SoundResSourceManager() : unknown48(false) {}

SoundResSourceManager::~SoundResSourceManager() { clearAll(); }

void SoundResSourceManager::clearAll() {
  SoundResSourceManager *manager = get();
  if (manager != nullptr) {
    manager->unknown08.clear();
    manager->unknown08.setAllocator(nullptr);
    manager->unknown20.clear();
    manager->unknown20.setAllocator(nullptr);
  }
}

void SoundResSourceManager::beginPush(u32 count, mm::mtl::IAllocator *allocator) {
  SoundResSourceManager *manager = get();
  if (manager != nullptr) {
    manager->unknown08.setAllocator(allocator);
    manager->unknown20.setAllocator(allocator);
    manager->unknown20.reserve(count);
  }
}

void SoundResSourceManager::endPush() {
  SoundResSourceManager *manager = get();
  if (manager != nullptr) {
    for (const ResSoundSource *resource : manager->unknown20) {
      for (const ResSoundSourceBase &source : resource->unknown00) {
        manager->unknown08.insert(mm::mtl::MapPair<anm::StringPtr, const ResSoundSourceBase *>(source.unknown00, &source));
      }
      for (const ResComplexSoundSource &source : resource->unknown10) {
        manager->unknown08.insert(mm::mtl::MapPair<anm::StringPtr, const ResSoundSourceBase *>(source.unknown00, &source));
      }
    }
  }
}

void SoundResSourceManager::pushResource(const ResSoundSource *source) {
  if (source != nullptr) {
    SoundResSourceManager *manager = get();
    if (manager != nullptr) {
      manager->unknown20.push_back(source);
    }
  }
}

void SoundResSourceManager::stopSe(u32 handle, f32 time) {
  if (SoundManager::get() != nullptr) {
    SoundManager::get()->stopSe(handle, time);
  }
}

} // namespace fw

template mm::mtl::PtrSingleton<fw::SoundResSourceManager>::~PtrSingleton();
