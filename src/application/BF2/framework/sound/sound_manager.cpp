#include "framework/sound/sound_manager.h"

#include "framework/memory/framework_memory.h"
#include "framework/resource/resource_object.h"
#include "framework/resource/sound_resource.h"
#include "framework/sound/sound_driver.h"
#include "fw/fw_update_info.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"

namespace fw {
enum SoundCategory : int;

void SoundManager::attachPoolMemory(void *memory, u32 size) {
  if (get() != nullptr && unknown18 != nullptr && unknown98) {
    unknown18->attachPoolMemory(memory, size);
  }
}

void SoundManager::addCategory(SoundCategory category, f32 volume, const char *name) {
  if (unknown18 != nullptr) {
    mm::mtl::FixStr<128> categoryName;
    categoryName.format("%s(%d)", name, category);
    unknown18->addCategory(category, volume, categoryName.c_str());
  }
}

void SoundManager::pauseAll(bool isPause, f32 time) {
  if (get() == nullptr || unknown18 == nullptr || !unknown98) {
    return;
  }

  if (isPause) {
    if (unknown94 == 0) {
      unknown18->pauseAll(true, time);
    }
    unknown94++;
  } else if (unknown94 > 0) {
    unknown94--;
    if (unknown94 == 0) {
      unknown18->pauseAll(false, time);
    }
  }
}

void SoundManager::update(const UpdateInfo &info) {
  if (isFinalized()) {
    return;
  }

  if (unknown18 == nullptr) {
    return;
  }

  f32 previousVolume = getMasterVolume();
  m_masterVolumeOrg.update(info.unknown04);
  unknown80.update(info.unknown04);
  f32 volume = getMasterVolume();
  if (__builtin_fabsf(volume - previousVolume) > 0.000001f) {
    unknown18->setMasterVolume(volume);
  }

  unknown18->update(info);
}

f32 SoundManager::getMasterVolume() const { return m_masterVolumeOrg.unknown00 * unknown80.unknown00; }

void SoundManager::tail(const UpdateInfo &info) {
  if (isFinalized()) {
    return;
  }
}

mm::mtl::IAllocator *SoundManager::getProcAllocator() { return FrameworkMemory::getAllocator(7); }

u32 SoundManager::getUniqueID(SoundCategory category) {
  m_uniqueID.unknown00++;
  if (m_uniqueID.unknown00 > m_uniqueID.unknown08) {
    m_uniqueID.unknown00 = m_uniqueID.unknown04;
  } else if (m_uniqueID.unknown00 < m_uniqueID.unknown04) {
    m_uniqueID.unknown00 = m_uniqueID.unknown04;
  }

  return m_uniqueID.unknown00 | category << 24;
}

void SoundManager::setListeningPoint(const mm::Mat44 &matrix) {
  if (unknown18 != nullptr) {
    unknown18->setListeningPoint(matrix);
  }
}

const mm::Mat44 &SoundManager::getListeningPoint() const {
  if (unknown18 != nullptr) {
    return unknown18->getListeningPoint();
  }

  return mm::Mat44::identity;
}

void SoundManager::setOutputMode(SoundOutputType type) {
  if (unknown18 != nullptr) {
    unknown18->setOutputMode(type);
  }
}

void SoundManager::removeCategory(SoundCategory category) {
  if (unknown18 != nullptr) {
    unknown18->removeCategory(category);
  }
}

void SoundManager::setCategoryVolume(SoundCategory category, f32 volume, f32 time) {
  if (unknown18 != nullptr) {
    unknown18->setCategoryVolume(category, volume, time);
  }
}

f32 SoundManager::getCategoryVolume(SoundCategory category) const {
  if (unknown18 != nullptr) {
    return unknown18->getCategoryVolume(category);
  }

  return 0.0f;
}

void SoundManager::setCategoryMute(SoundCategory category, bool isMute, f32 time) {
  if (unknown18 != nullptr) {
    unknown18->setCategoryMute(category, isMute, time);
  }
}

void SoundManager::setCategoryPitch(SoundCategory category, f32 pitch, f32 time) {
  if (unknown18 != nullptr) {
    unknown18->setCategoryPitch(category, pitch, time);
  }
}

bool SoundManager::isSoundEbable() const {
  if (get() == nullptr) {
    return false;
  }

  if (unknown18 == nullptr) {
    return false;
  }

  return unknown98;
}

u32 SoundManager::playBgm(const char *name, f32 volume, bool ignorePause, int loopCount, SoundCategory category) {
  if (!isSoundEbable()) {
    return 0;
  }

  u32 handle = unknown18->playBgm(name, volume, ignorePause, loopCount, category);
  if (handle != 0 && !ignorePause && isPauseAll()) {
    pause(handle, true, 0.0f);
  }

  return handle;
}

bool SoundManager::isPauseAll() const {
  if (!isSoundEbable()) {
    return false;
  }

  return unknown94 != 0;
}

bool SoundManager::startBgm(u32 handle) {
  if (isSoundEbable() && handle != 0) {
    return unknown18->startBgm(handle);
  }

  return false;
}

void SoundManager::stopBgm(u32 handle, f32 time) {
  if (isSoundEbable() && handle != 0) {
    unknown18->stopBgm(handle, time);
  }
}

u32 SoundManager::playVoice(const char *name, f32 volume, bool ignorePause, SoundCategory category) {
  if (!isSoundEbable()) {
    return 0;
  }

  u32 handle = unknown18->playVoice(name, volume, ignorePause, category);
  if (handle != 0 && !ignorePause && isPauseAll()) {
    pause(handle, true, 0.0f);
  }

  return handle;
}

bool SoundManager::startVoice(u32 handle) {
  if (isSoundEbable() && handle != 0) {
    return unknown18->startVoice(handle);
  }

  return false;
}

void SoundManager::stopVoice(u32 handle, f32 time) {
  if (isSoundEbable() && handle != 0) {
    unknown18->stopVoice(handle, time);
  }
}

SoundPack *SoundManager::getCommonPack() { return findPack("common", nullptr); }

u32 SoundManager::playSe(u32 id, SoundPack *pack, f32 volume, SoundCategory category) {
  if (!isSoundEbable()) {
    return 0;
  }

  if (pack == nullptr) {
    pack = getCommonPack();
  } else if (!isRegistPack(pack)) {
    return 0;
  }

  u32 handle = unknown18->playSe(id, pack, volume, category);
  if (handle != 0 && isPauseAll()) {
    pause(handle, true, 0.0f);
  }

  return handle;
}

void SoundManager::stopSe(u32 handle, f32 time) {
  if (isSoundEbable() && handle != 0) {
    unknown18->stopSe(handle, time);
  }
}

u32 SoundManager::findSe(const char *name) const {
  if (!isSoundEbable()) {
    return 0;
  }

  return unknown18->findSe(name);
}

u32 SoundManager::getSoundType(u32 handle) const { return handle >> 24; }

bool SoundManager::isValid(u32 handle) const {
  if (isSoundEbable() && handle != 0) {
    return unknown18->isValid(handle);
  }

  return false;
}

bool SoundManager::isPlaying(u32 handle) const {
  if (!isSoundEbable() || handle == 0) {
    return false;
  }

  return unknown18->isPreparing(handle) || unknown18->isReady(handle) || unknown18->isPlaying(handle) || unknown18->isPause(handle);
}

bool SoundManager::isPause(u32 handle) const {
  if (isSoundEbable() && handle != 0) {
    return unknown18->isPause(handle);
  }

  return false;
}

bool SoundManager::isPreparing(u32 handle) const {
  if (isSoundEbable() && handle != 0) {
    return unknown18->isPreparing(handle);
  }

  return false;
}

bool SoundManager::isPrepared(u32 handle) const {
  if (isSoundEbable() && handle != 0) {
    return unknown18->isReady(handle);
  }

  return false;
}

void SoundManager::setCategory(u32 handle, SoundCategory category) {
  if (isSoundEbable() && handle != 0) {
    unknown18->setCategory(handle, category);
  }
}

void SoundManager::setVolume(u32 handle, f32 volume, f32 time) {
  if (isSoundEbable() && handle != 0) {
    unknown18->setVolume(handle, volume, time);
  }
}

f32 SoundManager::getVolume(u32 handle, SoundVolumeType type) {
  if (isSoundEbable() && handle != 0) {
    return unknown18->getVolume(handle, type);
  }

  return 0.0f;
}

void SoundManager::setPitch(u32 handle, f32 pitch, f32 time) {
  if (isSoundEbable() && handle != 0) {
    unknown18->setPitch(handle, pitch, time);
  }
}

void SoundManager::setPan(u32 handle, f32 pan, f32 time) {
  if (isSoundEbable() && handle != 0) {
    unknown18->setPan(handle, pan, time);
  }
}

void SoundManager::setPos(u32 handle, const mm::Vec3 &position) {
  if (isSoundEbable() && handle != 0) {
    unknown18->setPos(handle, position);
  }
}

bool SoundManager::setPlayTime(u32 handle, f32 time) {
  if (isSoundEbable() && handle != 0) {
    return unknown18->setPlayTime(handle, time);
  }

  return false;
}

bool SoundManager::getPlayTime(u32 handle, f32 &time) {
  if (isSoundEbable() && handle != 0) {
    return unknown18->getPlayTime(handle, time);
  }

  return false;
}

bool SoundManager::getTotalTime(u32 handle, f32 &time) {
  if (isSoundEbable() && handle != 0) {
    return unknown18->getTotalTime(handle, time);
  }

  return false;
}

bool SoundManager::isLoop(u32 handle) {
  if (isSoundEbable() && handle != 0) {
    return unknown18->isLoop(handle);
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

  return unknown18->isLoop(id, pack);
}

bool SoundManager::setRemainLoopCount(u32 handle, int count) {
  if (isSoundEbable() && handle != 0) {
    return unknown18->setRemainLoopCount(handle, count);
  }

  return false;
}

bool SoundManager::getRemainLoopCount(u32 handle, int &count) {
  if (isSoundEbable() && handle != 0) {
    return unknown18->getRemainLoopCount(handle, count);
  }

  return false;
}

void SoundManager::pause(u32 handle, bool isPause, f32 time) {
  if (isSoundEbable()) {
    unknown18->pause(handle, isPause, time);
  }
}

void SoundManager::pauseCategory(SoundCategory category, bool isPause, f32 time) {
  if (isSoundEbable()) {
    unknown18->pauseCategory(category, isPause, time);
  }
}

void SoundManager::stopAll() {
  if (isSoundEbable()) {
    unknown18->stopAll();
  }
}

void SoundManager::stopVoiceAll() {
  if (isSoundEbable()) {
    unknown18->stopVoiceAll();
  }
}

void SoundManager::stopBgmAll() {
  if (isSoundEbable()) {
    unknown18->stopBgmAll();
  }
}

void SoundManager::stopSeAll() {
  if (isSoundEbable()) {
    unknown18->stopSeAll();
  }
}

void SoundManager::registPack(SoundPack *pack) { unknowna0.push_back(pack); }

void SoundManager::loadCommonSe() {
  mm::mtl::safeRelease(unknowne0);
  SoundResource::SetupInfo info;
  info.unknown08 = 0x20;
  unknowne0 = SoundResource::request(FrameworkMemory::getAllocator(6), "/sound/se/common.xsp", info, static_cast<LOAD_PRIO>(10));
}

void SoundManager::loadBattleSe() {
  mm::mtl::safeRelease(unknowne8[2]);
  mm::mtl::safeRelease(unknowne8[1]);
  mm::mtl::safeRelease(unknowne8[0]);
  SoundResource::SetupInfo info;
  info.unknown08 = 0x20;
  unknowne8[0] = SoundResource::request(FrameworkMemory::getAllocator(6), "/sound/se/se_btl_system.xsp", info, static_cast<LOAD_PRIO>(10));
  info.unknown08 = 8;
  unknowne8[1] = SoundResource::request(FrameworkMemory::getAllocator(6), "/sound/se/se_btl_elem.xsp", info, static_cast<LOAD_PRIO>(10));
  info.unknown08 = 8;
  unknowne8[2] = SoundResource::request(FrameworkMemory::getAllocator(6), "/sound/se/se_btl_weapon.xsp", info, static_cast<LOAD_PRIO>(10));
}

bool SoundManager::isRegistPack(SoundPack *pack) const {
  if (pack == nullptr) {
    return false;
  }

  mm::mtl::List<SoundPack *>::const_iterator it = unknowna0.begin();
  for (; it != unknowna0.end(); ++it) {
    if (*it == pack) {
      break;
    }
  }

  return it != unknowna0.end();
}

bool SoundManager::isCommonLoaded() const {
  if (unknowne0 != nullptr) {
    return unknowne0->valid();
  }

  return true;
}

SoundPack *SoundManager::getBattlePack() { return findPack("se_btl_system", nullptr); }

bool SoundManager::isBattleLoaded() const {
  for (u32 i = 0; i < BATTLE_RESOURCE_MAX; i++) {
    if (unknowne8[i] != nullptr && !unknowne8[i]->valid()) {
      return false;
    }
  }

  return true;
}

void SoundManager::detachPoolMemory(void *memory, u32 size) {
  if (isSoundEbable()) {
    unknown18->detachPoolMemory(memory, size);
  }
}

void SoundManager::setMasterVolume(f32 volume, f32 time) {
  if (unknown18 == nullptr) {
    return;
  }

  m_masterVolumeOrg.start(volume, time);
  unknown18->setMasterVolume(getMasterVolume());
}

f32 SoundManager::getMasterVolumeOrg() const { return m_masterVolumeOrg.unknown00; }

void SoundManager::setMasterMute(bool isMute, f32 time) {
  if (isMute) {
    unknown80.start(0.0f, time);
  } else {
    unknown80.start(1.0f, time);
  }

  if (unknown18 != nullptr) {
    unknown18->setMasterVolume(getMasterVolume());
  }
}

const char *SoundManager::getName() const { return "SoundManager"; }

} // namespace fw

template mm::mtl::PtrSingleton<fw::SoundManager>::~PtrSingleton();
