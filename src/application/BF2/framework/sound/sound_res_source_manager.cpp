#include "framework/sound/sound_res_source_manager.h"

#include "anm/anm_array.h"
#include "anm/anm_string_ptr.h"
#include "framework/sound/sound_manager.h"
#include "framework/sound/sound_variable_table.h"
#include "mm_mtl/delegate.h"

namespace fw {
class SoundPack;

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
      for (const ResSoundSource::unknown001 &source : resource->unknown00) {
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

int findComplexIndex(const SoundVariableTable &table, const ResComplexSoundSource *source) {
  int values[8];
  u32 count = 0;
  for (const char *name : source->unknown10) {
    if (!table.getVariable(name, &values[count])) {
      return -1;
    }
    count++;
  }
  for (u32 i = 0; i < source->unknown20.size(); i++) {
    for (u32 j = 0; true; j++) {
      if (j >= source->unknown20[i].unknown10.size()) {
        return i;
      }
      if (source->unknown20[i].unknown10[j] >= 0 && source->unknown20[i].unknown10[j] != values[j]) {
        break;
      }
    }
  }
  return -1;
}

u32 SoundResSourceManager::playSe(const char *name, f32 volume, const SoundVariableTable &table, SoundCategory category, const mm::mtl::Delegate<void(const ResSoundData &, CustomInfo *)> &callback) {
  SoundResSourceManager *manager = get();
  SoundManager *soundManager = SoundManager::get();
  if (manager != nullptr && soundManager != nullptr) {
    mm::mtl::Map<anm::StringPtr, const ResSoundSourceBase *>::iterator it = manager->unknown08.find(name);
    if (it != manager->unknown08.end()) {
      const ResSoundSourceBase *source = it->second;
      switch (source->unknown08) {
      case 0: {
        const ResSoundData &sound = static_cast<const ResSoundSource::unknown001 *>(source)->unknown10;
        SoundPack *pack = soundManager->findPack(sound.unknown00, nullptr);
        if (pack == nullptr) {
          return 0;
        }
        if (callback.isValid()) {
          CustomInfo info;
          info.unknown00 = 1.0f;
          callback(sound, &info);
          volume *= info.unknown00;
        }
        return soundManager->playSe(sound.unknown08, pack, volume, category);
      }
      case 1: {
        const ResComplexSoundSource *complex = static_cast<const ResComplexSoundSource *>(source);
        int index = findComplexIndex(table, complex);
        if (index == -1) {
          return 0;
        }
        const ResSoundData &sound = complex->unknown20[index].unknown00;
        SoundPack *pack = soundManager->findPack(sound.unknown00, nullptr);
        if (pack == nullptr) {
          return 0;
        }
        if (callback.isValid()) {
          CustomInfo info;
          info.unknown00 = 1.0f;
          callback(sound, &info);
          volume *= info.unknown00;
        }
        return soundManager->playSe(sound.unknown08, pack, volume, category);
      }
      }
    }
  }
  return 0;
}

void SoundResSourceManager::stopSe(u32 handle, f32 time) {
  if (SoundManager::get() != nullptr) {
    SoundManager::get()->stopSe(handle, time);
  }
}

} // namespace fw

template mm::mtl::PtrSingleton<fw::SoundResSourceManager>::~PtrSingleton();
