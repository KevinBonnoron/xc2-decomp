#include "framework/sound/sound_manager.h"

#include "framework/memory/framework_memory.h"
#include "framework/resource/resource_object.h"
#include "framework/sound/sound_driver.h"
#include "fw/fw_update_info.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixstr.h"

namespace fw {
enum SoundCategory : int;

void SoundManager::attachPoolMemory(void *memory, u32 size) {
  if (get() != nullptr && driver != nullptr && soundEnable) {
    driver->attachPoolMemory(memory, size);
  }
}

void SoundManager::addCategory(SoundCategory category, f32 volume, const char *name) {
  if (driver != nullptr) {
    mm::mtl::FixStr<128> categoryName;
    categoryName.format("%s(%d)", name, category);
    driver->addCategory(category, volume, categoryName.c_str());
  }
}

void SoundManager::pauseAll(bool isPause, f32 time) {
  if (get() == nullptr || driver == nullptr || !soundEnable) {
    return;
  }

  if (isPause) {
    if (pauseCount == 0) {
      driver->pauseAll(true, time);
    }
    pauseCount++;
  } else if (pauseCount > 0) {
    pauseCount--;
    if (pauseCount == 0) {
      driver->pauseAll(false, time);
    }
  }
}

void SoundManager::update(const UpdateInfo &info) {
  if (isFinalized()) {
    return;
  }

  if (driver == nullptr) {
    return;
  }

  f32 previousVolume = getMasterVolume();
  masterFade.update(info.deltaTime);
  muteFade.update(info.deltaTime);
  f32 volume = getMasterVolume();
  if (__builtin_fabsf(volume - previousVolume) > 0.000001f) {
    driver->setMasterVolume(volume);
  }

  driver->update(info);
}

f32 SoundManager::getMasterVolume() const { return masterFade.volume * muteFade.volume; }

void SoundManager::tail(const UpdateInfo &info) {
  if (isFinalized()) {
    return;
  }
}

mm::mtl::IAllocator *SoundManager::getProcAllocator() { return FrameworkMemory::getAllocator(7); }

u32 SoundManager::getUniqueID(SoundCategory category) {
  m_uniqueID.current++;
  if (m_uniqueID.current > m_uniqueID.max) {
    m_uniqueID.current = m_uniqueID.min;
  } else if (m_uniqueID.current < m_uniqueID.min) {
    m_uniqueID.current = m_uniqueID.min;
  }

  return m_uniqueID.current | category << 24;
}

void SoundManager::setListeningPoint(const mm::Mat44 &matrix) {
  if (driver != nullptr) {
    driver->setListeningPoint(matrix);
  }
}

const mm::Mat44 &SoundManager::getListeningPoint() const {
  if (driver != nullptr) {
    return driver->getListeningPoint();
  }

  return mm::Mat44::identity;
}

void SoundManager::setOutputMode(SoundOutputType type) {
  if (driver != nullptr) {
    driver->setOutputMode(type);
  }
}

void SoundManager::removeCategory(SoundCategory category) {
  if (driver != nullptr) {
    driver->removeCategory(category);
  }
}

void SoundManager::setCategoryVolume(SoundCategory category, f32 volume, f32 time) {
  if (driver != nullptr) {
    driver->setCategoryVolume(category, volume, time);
  }
}

f32 SoundManager::getCategoryVolume(SoundCategory category) const {
  if (driver != nullptr) {
    return driver->getCategoryVolume(category);
  }

  return 0.0f;
}

void SoundManager::setCategoryMute(SoundCategory category, bool isMute, f32 time) {
  if (driver != nullptr) {
    driver->setCategoryMute(category, isMute, time);
  }
}

void SoundManager::setCategoryPitch(SoundCategory category, f32 pitch, f32 time) {
  if (driver != nullptr) {
    driver->setCategoryPitch(category, pitch, time);
  }
}

bool SoundManager::isSoundEbable() const {
  if (get() == nullptr) {
    return false;
  }

  if (driver == nullptr) {
    return false;
  }

  return soundEnable;
}

u32 SoundManager::playBgm(const char *name, f32 volume, bool ignorePause, int loopCount, SoundCategory category) {
  if (!isSoundEbable()) {
    return 0;
  }

  u32 handle = driver->playBgm(name, volume, ignorePause, loopCount, category);
  if (handle != 0 && !ignorePause && isPauseAll()) {
    pause(handle, true, 0.0f);
  }

  return handle;
}

bool SoundManager::isPauseAll() const {
  if (!isSoundEbable()) {
    return false;
  }

  return pauseCount != 0;
}

bool SoundManager::startBgm(u32 handle) {
  if (isSoundEbable() && handle != 0) {
    return driver->startBgm(handle);
  }

  return false;
}

void SoundManager::stopBgm(u32 handle, f32 time) {
  if (isSoundEbable() && handle != 0) {
    driver->stopBgm(handle, time);
  }
}

u32 SoundManager::playVoice(const char *name, f32 volume, bool ignorePause, SoundCategory category) {
  if (!isSoundEbable()) {
    return 0;
  }

  u32 handle = driver->playVoice(name, volume, ignorePause, category);
  if (handle != 0 && !ignorePause && isPauseAll()) {
    pause(handle, true, 0.0f);
  }

  return handle;
}

bool SoundManager::startVoice(u32 handle) {
  if (isSoundEbable() && handle != 0) {
    return driver->startVoice(handle);
  }

  return false;
}

void SoundManager::stopVoice(u32 handle, f32 time) {
  if (isSoundEbable() && handle != 0) {
    driver->stopVoice(handle, time);
  }
}

SoundPack *SoundManager::getCommonPack() { return findPack("common", nullptr); }

void SoundManager::stopSe(u32 handle, f32 time) {
  if (isSoundEbable() && handle != 0) {
    driver->stopSe(handle, time);
  }
}

u32 SoundManager::findSe(const char *name) const {
  if (!isSoundEbable()) {
    return 0;
  }

  return driver->findSe(name);
}

u32 SoundManager::getSoundType(u32 handle) const { return handle >> 24; }

bool SoundManager::isValid(u32 handle) const {
  if (isSoundEbable() && handle != 0) {
    return driver->isValid(handle);
  }

  return false;
}

bool SoundManager::isPlaying(u32 handle) const {
  if (!isSoundEbable() || handle == 0) {
    return false;
  }

  return driver->isPreparing(handle) || driver->isReady(handle) || driver->isPlaying(handle) || driver->isPause(handle);
}

bool SoundManager::isPause(u32 handle) const {
  if (isSoundEbable() && handle != 0) {
    return driver->isPause(handle);
  }

  return false;
}

bool SoundManager::isPreparing(u32 handle) const {
  if (isSoundEbable() && handle != 0) {
    return driver->isPreparing(handle);
  }

  return false;
}

bool SoundManager::isPrepared(u32 handle) const {
  if (isSoundEbable() && handle != 0) {
    return driver->isReady(handle);
  }

  return false;
}

void SoundManager::setCategory(u32 handle, SoundCategory category) {
  if (isSoundEbable() && handle != 0) {
    driver->setCategory(handle, category);
  }
}

void SoundManager::setVolume(u32 handle, f32 volume, f32 time) {
  if (isSoundEbable() && handle != 0) {
    driver->setVolume(handle, volume, time);
  }
}

f32 SoundManager::getVolume(u32 handle, SoundVolumeType type) {
  if (isSoundEbable() && handle != 0) {
    return driver->getVolume(handle, type);
  }

  return 0.0f;
}

void SoundManager::setPitch(u32 handle, f32 pitch, f32 time) {
  if (isSoundEbable() && handle != 0) {
    driver->setPitch(handle, pitch, time);
  }
}

void SoundManager::setPan(u32 handle, f32 pan, f32 time) {
  if (isSoundEbable() && handle != 0) {
    driver->setPan(handle, pan, time);
  }
}

void SoundManager::setPos(u32 handle, const mm::Vec3 &position) {
  if (isSoundEbable() && handle != 0) {
    driver->setPos(handle, position);
  }
}

bool SoundManager::setPlayTime(u32 handle, f32 time) {
  if (isSoundEbable() && handle != 0) {
    return driver->setPlayTime(handle, time);
  }

  return false;
}

bool SoundManager::getPlayTime(u32 handle, f32 &time) {
  if (isSoundEbable() && handle != 0) {
    return driver->getPlayTime(handle, time);
  }

  return false;
}

bool SoundManager::getTotalTime(u32 handle, f32 &time) {
  if (isSoundEbable() && handle != 0) {
    return driver->getTotalTime(handle, time);
  }

  return false;
}

bool SoundManager::isLoop(u32 handle) {
  if (isSoundEbable() && handle != 0) {
    return driver->isLoop(handle);
  }

  return false;
}

bool SoundManager::isLoop(u32 id, SoundPack *pack) {
  if (!isSoundEbable()) {
    return false;
  }

  if (pack == nullptr) {
    pack = getCommonPack();
  }

  return driver->isLoop(id, pack);
}

bool SoundManager::setRemainLoopCount(u32 handle, int count) {
  if (isSoundEbable() && handle != 0) {
    return driver->setRemainLoopCount(handle, count);
  }

  return false;
}

bool SoundManager::getRemainLoopCount(u32 handle, int &count) {
  if (isSoundEbable() && handle != 0) {
    return driver->getRemainLoopCount(handle, count);
  }

  return false;
}

void SoundManager::pause(u32 handle, bool isPause, f32 time) {
  if (isSoundEbable()) {
    driver->pause(handle, isPause, time);
  }
}

void SoundManager::pauseCategory(SoundCategory category, bool isPause, f32 time) {
  if (isSoundEbable()) {
    driver->pauseCategory(category, isPause, time);
  }
}

void SoundManager::stopAll() {
  if (isSoundEbable()) {
    driver->stopAll();
  }
}

void SoundManager::stopVoiceAll() {
  if (isSoundEbable()) {
    driver->stopVoiceAll();
  }
}

void SoundManager::stopBgmAll() {
  if (isSoundEbable()) {
    driver->stopBgmAll();
  }
}

void SoundManager::stopSeAll() {
  if (isSoundEbable()) {
    driver->stopSeAll();
  }
}

void SoundManager::registPack(SoundPack *pack) { packs.push_back(pack); }

bool SoundManager::isCommonLoaded() const {
  if (commonResource != nullptr) {
    return commonResource->valid();
  }

  return true;
}

SoundPack *SoundManager::getBattlePack() { return findPack("se_btl_system", nullptr); }

bool SoundManager::isBattleLoaded() const {
  for (u32 i = 0; i < BATTLE_RESOURCE_MAX; i++) {
    if (battleResources[i] != nullptr && !battleResources[i]->valid()) {
      return false;
    }
  }

  return true;
}

void SoundManager::detachPoolMemory(void *memory, u32 size) {
  if (isSoundEbable()) {
    driver->detachPoolMemory(memory, size);
  }
}

void SoundManager::setMasterVolume(f32 volume, f32 time) {
  if (driver == nullptr) {
    return;
  }

  masterFade.start(volume, time);
  driver->setMasterVolume(getMasterVolume());
}

f32 SoundManager::getMasterVolumeOrg() const { return masterFade.volume; }

void SoundManager::setMasterMute(bool isMute, f32 time) {
  if (isMute) {
    muteFade.start(0.0f, time);
  } else {
    muteFade.start(1.0f, time);
  }

  if (driver != nullptr) {
    driver->setMasterVolume(getMasterVolume());
  }
}

const char *SoundManager::getName() const { return "SoundManager"; }

} // namespace fw
