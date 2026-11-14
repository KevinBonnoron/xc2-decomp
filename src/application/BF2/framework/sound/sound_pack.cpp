#include "framework/sound/sound_pack.h"

#include <string.h>

#include "framework/memory/framework_memory.h"
#include "framework/sound/sound_manager.h"
#include "framework/sound/sound_ssd_drv.h"
#include "ml/path_util.h"
#include "mm_mtl/hash.h"

namespace fw {

SoundPack *SoundPack::createFromStream(mm::mtl::IAllocator *allocator, const SetupInfo &info) {
  SoundPack *pack = SoundManager::get()->findPack(info.unknown00.c_str(), allocator);
  if (pack != nullptr) {
    pack->addRef();
    return pack;
  }

  // __LINE__ must be 171 as in the original file: it is the line argument of operator new.
#line 171
  pack = new (FrameworkMemory::getAllocator(5), 8, __FILE__, __LINE__) SoundPack(info.unknown84, allocator, info.unknown00.c_str(), info.unknown88);
  pack->addRef();
  mm::mtl::FixStr<256> bankName;
  bankName.format("%s_%p", info.unknown00.c_str(), allocator);
  pack->unknown178 = SoundSsdBank::create(bankName.c_str(), info.unknown84, info.unknowna4);
  pack->unknown178->setMaxSound(info.unknowna4);
  pack->registSource(info.unknown98, info.unknowna0);
  SoundManager::get()->registPack(pack);
  return pack;
}

SoundPack *SoundPack::create(const SetupInfo &info) {
  SoundPack *pack = SoundManager::get()->findPack(info.unknown00.c_str(), nullptr);
  if (pack != nullptr) {
    pack->addRef();
    return pack;
  }

  // __LINE__ must be 210 as in the original file: it is the line argument of operator new.
#line 210
  pack = new (FrameworkMemory::getAllocator(5), 8, __FILE__, __LINE__) SoundPack(info.unknown84, nullptr, info.unknown00.c_str(), info.unknown88);
  pack->addRef();
  mm::mtl::FixStr<256> bankName;
  bankName.format("%s_%p", info.unknown00.c_str(), nullptr);
  pack->unknown178 = SoundSsdBank::create(bankName.c_str(), info.unknown84, info.unknowna4);
  pack->unknown178->setMaxSound(info.unknowna4);
  pack->registSource(info.unknown98, info.unknowna0);
  SoundManager::get()->registPack(pack);
  return pack;
}

SoundPack::SoundPack(SoundCategory category, mm::mtl::IAllocator *allocator, const char *name, SoundPriority priority) : unknown0c(category), unknown10(allocator), unknown170(priority) {
  unknown24 = name;
  unknown128 = mm::mtl::hashStrCrc(name);
  unknown12c = ml::PathUtil::getNoPathExtName(name);
}

SoundPack::~SoundPack() {
  stopAll();
  m_source.clear();
  unknown988.clear();
  mm::mtl::safeRelease(unknown178);
  SoundManager::get()->removePack(this);
}

void SoundPack::stopAll() {
  if (unknown178 != nullptr) {
    unknown178->stopAll();
  }
}

bool SoundPack::canRelease() const {
  if (unknown178 != nullptr) {
    return unknown178->canRelease();
  }

  return true;
}

mm::mtl::IntrusivePtr<SoundSsdSource> SoundPack::getSource(u32 index) const { return m_source[index]; }

mm::mtl::IntrusivePtr<SoundSsdSource> SoundPack::findSourceFromID(u32 id) const {
  for (u32 i = 0; i < unknown988.size(); i++) {
    if (unknown988[i].unknown00 == id) {
      return m_source[i];
    }
  }

  return nullptr;
}

mm::mtl::IntrusivePtr<SoundSsdSource> SoundPack::findSource(const char *name) const {
  u32 hash = mm::mtl::hashStrCrc(name);
  for (u32 i = 0; i < unknown988.size(); i++) {
    if (unknown988[i].unknown04 == hash) {
      if (strcmp(m_source[i]->unknown134.c_str(), name) == 0) {
        return m_source[i];
      }
    }
  }

  return nullptr;
}

bool SoundPack::isLoopSource(const char *name) const {
  mm::mtl::IntrusivePtr<SoundSsdSource> source = findSource(name);
  if (source.get() == nullptr) {
    return false;
  }

  return source->isLoop();
}

bool SoundPack::isLoopSource(u32 id) const {
  for (u32 i = 0; i < unknown988.size(); i++) {
    if (unknown988[i].unknown00 == id) {
      SoundSsdSource *source = m_source[i].get();
      if (source == nullptr) {
        return false;
      }

      mm::mtl::IntrusivePtr<SoundSsdSource> hold(source);
      return source->isLoop();
    }
  }

  return false;
}

} // namespace fw
