#include "framework/sound/sound_manager.h"

#include <strings.h>

#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "framework/resource/resource_object.h"
#include "framework/resource/sound_resource.h"
#include "framework/sound/sound_driver.h"
#include "framework/sound/sound_pack.h"
#include "framework/sound/sound_ssd_drv.h"
#include "fw/fw_update_info.h"
#include "ml/path_util.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace fw {
enum SoundCategory : int;

SoundManager::~SoundManager() {
  mm::mtl::safeRelease(unknowne0);
  mm::mtl::safeRelease(unknowne8[1]);
  mm::mtl::safeRelease(unknowne8[2]);
  mm::mtl::safeRelease(unknowne8[0]);
  if (m_iSoundDriver != nullptr) {
    delete m_iSoundDriver;
    m_iSoundDriver = nullptr;
  }
}

bool SoundManager::finalize() {
  mm::mtl::safeRelease(unknowne8[2]);
  mm::mtl::safeRelease(unknowne8[1]);
  mm::mtl::safeRelease(unknowne8[0]);
  mm::mtl::safeRelease(unknowne0);
  if (m_iSoundDriver != nullptr) {
    if (unknown94 > 0) {
      do {
        pauseAll(false, 0.0f);
      } while (unknown94 > 0);
    }

    for (size_t i = 0; i < unknown20.size(); i++) {
      if (unknown20[i] != nullptr) {
        unknown20[i]->release();
        unknown20[i] = nullptr;
      }
    }
    unknown20.clear();

    if (!m_iSoundDriver->finalize()) {
      return false;
    }

    if (m_iSoundDriver != nullptr) {
      delete m_iSoundDriver;
      m_iSoundDriver = nullptr;
    }
  }

  return true;
}

SoundManager::SoundManager(mm::mtl::IAllocator *allocator) : m_iSoundDriver(nullptr), unknown68(0), unknown94(0), unknown98(false), unknowne0(nullptr), unknowne8() {}

void SoundManager::attachPoolMemory(void *memory, u32 size) {
  if (get() != nullptr && m_iSoundDriver != nullptr && unknown98) {
    m_iSoundDriver->attachPoolMemory(memory, size);
  }
}

void SoundManager::addCategory(SoundCategory category, f32 volume, const char *name) {
  if (m_iSoundDriver != nullptr) {
    mm::mtl::FixStr<128> categoryName;
    categoryName.format("%s(%d)", name, category);
    m_iSoundDriver->addCategory(category, volume, categoryName.c_str());
  }
}

void SoundManager::pauseAll(bool isPause, f32 time) {
  if (get() == nullptr || m_iSoundDriver == nullptr || !unknown98) {
    return;
  }

  if (isPause) {
    if (unknown94 == 0) {
      m_iSoundDriver->pauseAll(true, time);
    }
    unknown94++;
  } else if (unknown94 > 0) {
    unknown94--;
    if (unknown94 == 0) {
      m_iSoundDriver->pauseAll(false, time);
    }
  }
}

void SoundManager::update(const UpdateInfo &info) {
  if (isFinalized()) {
    return;
  }

  if (m_iSoundDriver == nullptr) {
    return;
  }

  f32 previousVolume = getMasterVolume();
  m_masterVolumeOrg.update(info.unknown04);
  unknown80.update(info.unknown04);
  f32 volume = getMasterVolume();
  if (__builtin_fabsf(volume - previousVolume) > 0.000001f) {
    m_iSoundDriver->setMasterVolume(volume);
  }

  m_iSoundDriver->update(info);
}

f32 SoundManager::getMasterVolume() const { return m_masterVolumeOrg.m_masterVolumeOrg * unknown80.m_masterVolumeOrg; }

void SoundManager::tail(const UpdateInfo &info) {
  if (isFinalized()) {
    return;
  }
}

mm::mtl::IAllocator *SoundManager::getProcAllocator() { return FrameworkMemory::getAllocator(7); }

u32 SoundManager::getUniqueID(SoundCategory category) { return m_uniqueID.unknown001() | category << 24; }

void SoundManager::setListeningPoint(const mm::Mat44 &matrix) {
  if (m_iSoundDriver != nullptr) {
    m_iSoundDriver->setListeningPoint(matrix);
  }
}

const mm::Mat44 &SoundManager::getListeningPoint() const {
  if (m_iSoundDriver != nullptr) {
    return m_iSoundDriver->getListeningPoint();
  }

  return mm::Mat44::identity;
}

void SoundManager::setOutputMode(SoundOutputType type) {
  if (m_iSoundDriver != nullptr) {
    m_iSoundDriver->setOutputMode(type);
  }
}

void SoundManager::removeCategory(SoundCategory category) {
  if (m_iSoundDriver != nullptr) {
    m_iSoundDriver->removeCategory(category);
  }
}

void SoundManager::setCategoryVolume(SoundCategory category, f32 volume, f32 time) {
  if (m_iSoundDriver != nullptr) {
    m_iSoundDriver->setCategoryVolume(category, volume, time);
  }
}

f32 SoundManager::getCategoryVolume(SoundCategory category) const {
  if (m_iSoundDriver != nullptr) {
    return m_iSoundDriver->getCategoryVolume(category);
  }

  return 0.0f;
}

void SoundManager::setCategoryMute(SoundCategory category, bool isMute, f32 time) {
  if (m_iSoundDriver != nullptr) {
    m_iSoundDriver->setCategoryMute(category, isMute, time);
  }
}

void SoundManager::setCategoryPitch(SoundCategory category, f32 pitch, f32 time) {
  if (m_iSoundDriver != nullptr) {
    m_iSoundDriver->setCategoryPitch(category, pitch, time);
  }
}

bool SoundManager::isSoundEbable() const {
  if (get() == nullptr) {
    return false;
  }

  if (m_iSoundDriver == nullptr) {
    return false;
  }

  return unknown98;
}

u32 SoundManager::playBgm(const char *name, f32 volume, bool ignorePause, int loopCount, SoundCategory category) {
  if (!isSoundEbable()) {
    return 0;
  }

  u32 handle = m_iSoundDriver->playBgm(name, volume, ignorePause, loopCount, category);
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
    return m_iSoundDriver->startBgm(handle);
  }

  return false;
}

void SoundManager::stopBgm(u32 handle, f32 time) {
  if (isSoundEbable() && handle != 0) {
    m_iSoundDriver->stopBgm(handle, time);
  }
}

u32 SoundManager::playVoice(const char *name, f32 volume, bool ignorePause, SoundCategory category) {
  if (!isSoundEbable()) {
    return 0;
  }

  u32 handle = m_iSoundDriver->playVoice(name, volume, ignorePause, category);
  if (handle != 0 && !ignorePause && isPauseAll()) {
    pause(handle, true, 0.0f);
  }

  return handle;
}

bool SoundManager::startVoice(u32 handle) {
  if (isSoundEbable() && handle != 0) {
    return m_iSoundDriver->startVoice(handle);
  }

  return false;
}

void SoundManager::stopVoice(u32 handle, f32 time) {
  if (isSoundEbable() && handle != 0) {
    m_iSoundDriver->stopVoice(handle, time);
  }
}

SoundPack *SoundManager::getCommonPack() { return findPack("common", nullptr); }

SoundPack *SoundManager::findPack(const char *name, mm::mtl::IAllocator *allocator) {
  mm::mtl::FixStr<256> path(name);
  mm::mtl::FixStr<64> packName = ml::PathUtil::getNoPathExtName(path.c_str());
  if (packName.length() == path.length()) {
    for (mm::mtl::List<SoundPack *>::iterator it = unknowna0.begin(); it != unknowna0.end(); ++it) {
      SoundPack *pack = *it;
      if (strcasecmp(pack->unknown12c.c_str(), packName.c_str()) == 0 && (allocator == nullptr || pack->unknown10 == allocator)) {
        return pack;
      }
    }
  } else {
    for (mm::mtl::List<SoundPack *>::iterator it = unknowna0.begin(); it != unknowna0.end(); ++it) {
      SoundPack *pack = *it;
      if (strcasecmp(pack->unknown24.c_str(), name) == 0 && (allocator == nullptr || pack->unknown10 == allocator)) {
        return pack;
      }
    }
  }

  return nullptr;
}

u32 SoundManager::playSe(u32 id, SoundPack *pack, f32 volume, SoundCategory category) {
  if (!isSoundEbable()) {
    return 0;
  }

  if (pack == nullptr) {
    pack = getCommonPack();
  } else if (!isRegistPack(pack)) {
    return 0;
  }

  u32 handle = m_iSoundDriver->playSe(id, pack, volume, category);
  if (handle != 0 && isPauseAll()) {
    pause(handle, true, 0.0f);
  }

  return handle;
}

u32 SoundManager::playSeEx(const SoundPlayInfo &info, SoundResult &result) {
  result.unknown00 = 0;
  result.unknown04 = 3;
  SoundPlayInfo playInfo = info;
  if (!isSoundEbable()) {
    return 0;
  }

  if (playInfo.m_soundPack == nullptr) {
    playInfo.m_soundPack = findPack("common", nullptr);
    if (playInfo.m_soundPack == nullptr) {
      return 0;
    }
  }

  if (!isRegistPack(playInfo.m_soundPack)) {
    return 0;
  }

  u32 handle = m_iSoundDriver->playSeEx(playInfo, result);
  if (handle != 0 && isPauseAll()) {
    pause(handle, true, 0.0f);
  }

  return handle;
}

void SoundManager::stopSe(u32 handle, f32 time) {
  if (isSoundEbable() && handle != 0) {
    m_iSoundDriver->stopSe(handle, time);
  }
}

u32 SoundManager::findSe(const char *name) const {
  if (!isSoundEbable()) {
    return 0;
  }

  return m_iSoundDriver->findSe(name);
}

u32 SoundManager::getSoundType(u32 handle) const { return handle >> 24; }

bool SoundManager::isValid(u32 handle) const {
  if (isSoundEbable() && handle != 0) {
    return m_iSoundDriver->isValid(handle);
  }

  return false;
}

bool SoundManager::isPlaying(u32 handle) const {
  if (!isSoundEbable() || handle == 0) {
    return false;
  }

  return m_iSoundDriver->isPreparing(handle) || m_iSoundDriver->isReady(handle) || m_iSoundDriver->isPlaying(handle) || m_iSoundDriver->isPause(handle);
}

bool SoundManager::isPause(u32 handle) const {
  if (isSoundEbable() && handle != 0) {
    return m_iSoundDriver->isPause(handle);
  }

  return false;
}

bool SoundManager::isPreparing(u32 handle) const {
  if (isSoundEbable() && handle != 0) {
    return m_iSoundDriver->isPreparing(handle);
  }

  return false;
}

bool SoundManager::isPrepared(u32 handle) const {
  if (isSoundEbable() && handle != 0) {
    return m_iSoundDriver->isReady(handle);
  }

  return false;
}

void SoundManager::setCategory(u32 handle, SoundCategory category) {
  if (isSoundEbable() && handle != 0) {
    m_iSoundDriver->setCategory(handle, category);
  }
}

void SoundManager::setVolume(u32 handle, f32 volume, f32 time) {
  if (isSoundEbable() && handle != 0) {
    m_iSoundDriver->setVolume(handle, volume, time);
  }
}

f32 SoundManager::getVolume(u32 handle, SoundVolumeType type) {
  if (isSoundEbable() && handle != 0) {
    return m_iSoundDriver->getVolume(handle, type);
  }

  return 0.0f;
}

void SoundManager::setPitch(u32 handle, f32 pitch, f32 time) {
  if (isSoundEbable() && handle != 0) {
    m_iSoundDriver->setPitch(handle, pitch, time);
  }
}

void SoundManager::setPan(u32 handle, f32 pan, f32 time) {
  if (isSoundEbable() && handle != 0) {
    m_iSoundDriver->setPan(handle, pan, time);
  }
}

void SoundManager::setPos(u32 handle, const mm::Vec3 &position) {
  if (isSoundEbable() && handle != 0) {
    m_iSoundDriver->setPos(handle, position);
  }
}

bool SoundManager::setPlayTime(u32 handle, f32 time) {
  if (isSoundEbable() && handle != 0) {
    return m_iSoundDriver->setPlayTime(handle, time);
  }

  return false;
}

bool SoundManager::getPlayTime(u32 handle, f32 &time) {
  if (isSoundEbable() && handle != 0) {
    return m_iSoundDriver->getPlayTime(handle, time);
  }

  return false;
}

bool SoundManager::getTotalTime(u32 handle, f32 &time) {
  if (isSoundEbable() && handle != 0) {
    return m_iSoundDriver->getTotalTime(handle, time);
  }

  return false;
}

bool SoundManager::isLoop(u32 handle) {
  if (isSoundEbable() && handle != 0) {
    return m_iSoundDriver->isLoop(handle);
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

  return m_iSoundDriver->isLoop(id, pack);
}

bool SoundManager::setRemainLoopCount(u32 handle, int count) {
  if (isSoundEbable() && handle != 0) {
    return m_iSoundDriver->setRemainLoopCount(handle, count);
  }

  return false;
}

bool SoundManager::getRemainLoopCount(u32 handle, int &count) {
  if (isSoundEbable() && handle != 0) {
    return m_iSoundDriver->getRemainLoopCount(handle, count);
  }

  return false;
}

void SoundManager::pause(u32 handle, bool isPause, f32 time) {
  if (isSoundEbable()) {
    m_iSoundDriver->pause(handle, isPause, time);
  }
}

void SoundManager::pauseCategory(SoundCategory category, bool isPause, f32 time) {
  if (isSoundEbable()) {
    m_iSoundDriver->pauseCategory(category, isPause, time);
  }
}

void SoundManager::stopAll() {
  if (isSoundEbable()) {
    m_iSoundDriver->stopAll();
  }
}

void SoundManager::stopVoiceAll() {
  if (isSoundEbable()) {
    m_iSoundDriver->stopVoiceAll();
  }
}

void SoundManager::stopBgmAll() {
  if (isSoundEbable()) {
    m_iSoundDriver->stopBgmAll();
  }
}

void SoundManager::stopSeAll() {
  if (isSoundEbable()) {
    m_iSoundDriver->stopSeAll();
  }
}

void SoundManager::registPack(SoundPack *pack) { unknowna0.push_back(pack); }

void SoundManager::removePack(SoundPack *pack) {
  mm::mtl::List<SoundPack *>::iterator end = unknowna0.end();
  for (mm::mtl::List<SoundPack *>::iterator it = unknowna0.begin(); it != end;) {
    mm::mtl::List<SoundPack *>::iterator cur = it;
    ++it;
    if (*cur == pack) {
      unknowna0.erase(cur);
    }
  }
}

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
  for (u32 i = 0; i < BATTLE_RESOURCE_UNKNOWN_3; i++) {
    if (unknowne8[i] != nullptr && !unknowne8[i]->valid()) {
      return false;
    }
  }

  return true;
}

void SoundManager::detachPoolMemory(void *memory, u32 size) {
  if (isSoundEbable()) {
    m_iSoundDriver->detachPoolMemory(memory, size);
  }
}

void SoundManager::setMasterVolume(f32 volume, f32 time) {
  if (m_iSoundDriver == nullptr) {
    return;
  }

  m_masterVolumeOrg.start(volume, time);
  m_iSoundDriver->setMasterVolume(getMasterVolume());
}

f32 SoundManager::getMasterVolumeOrg() const { return m_masterVolumeOrg.m_masterVolumeOrg; }

void SoundManager::setMasterMute(bool isMute, f32 time) {
  if (isMute) {
    unknown80.start(0.0f, time);
  } else {
    unknown80.start(1.0f, time);
  }

  if (m_iSoundDriver != nullptr) {
    m_iSoundDriver->setMasterVolume(getMasterVolume());
  }
}

const char *SoundManager::getName() const { return "SoundManager"; }

} // namespace fw

template mm::mtl::PtrSingleton<fw::SoundManager>::~PtrSingleton();

namespace fw {

bool SoundManager::initialize() {
  if (m_iSoundDriver == nullptr) {
    // __LINE__ must be 555 of sound_manager.h as in the original: it is the line argument of operator new.
#line 555 "framework/sound/sound_manager.h"
    m_iSoundDriver = new (Framework::getAllocator(), 16, __FILE__, __LINE__) SoundSsdDriver(FrameworkMemory::getAllocator(7), 0x400);
    unknown98 = m_iSoundDriver->isDeviceEnable();

    {
      mtl::ALLOC_HANDLE handle = FrameworkMemory::getMem(6);
      attachPoolMemory(reinterpret_cast<void *>(mtl::MemManager::getTopAdr(handle)), mtl::MemManager::getTotalSize(handle));
    }
    {
      mtl::ALLOC_HANDLE handle = FrameworkMemory::getMem(8);
      attachPoolMemory(reinterpret_cast<void *>(mtl::MemManager::getTopAdr(handle)), mtl::MemManager::getTotalSize(handle));
    }

    m_uniqueID.unknown08 = 0xffffff;
    unknowna0.setAllocator(FrameworkMemory::getAllocator(5));
    unknowna0.reserve(0x400);

    addCategory(static_cast<SoundCategory>(1), 1.0f, "BGM");
    addCategory(static_cast<SoundCategory>(2), 1.0f, "VOICE");
    addCategory(static_cast<SoundCategory>(3), 1.0f, "SYSTEM");
    addCategory(static_cast<SoundCategory>(4), 1.0f, "BATTLE");
    addCategory(static_cast<SoundCategory>(5), 1.0f, "FIELD");
    addCategory(static_cast<SoundCategory>(6), 1.0f, "GIMMICK");
    addCategory(static_cast<SoundCategory>(7), 1.0f, "ENV");
    addCategory(static_cast<SoundCategory>(8), 1.0f, "WEATHER");
    addCategory(static_cast<SoundCategory>(9), 1.0f, "EVT_CS");
    addCategory(static_cast<SoundCategory>(10), 1.0f, "EVT_BGM");
    addCategory(static_cast<SoundCategory>(11), 1.0f, "EVT_VOICE");
    addCategory(static_cast<SoundCategory>(12), 1.0f, "EVT_SE");
    addCategory(static_cast<SoundCategory>(13), 1.0f, "CH_SE");
    addCategory(static_cast<SoundCategory>(14), 1.0f, "CH_SE NS");
    addCategory(static_cast<SoundCategory>(15), 1.0f, "ENE_VO");
    addCategory(static_cast<SoundCategory>(16), 1.0f, "NAREVO");
    addCategory(static_cast<SoundCategory>(17), 1.0f, "MENU_BGM");

    unknown20.clear();
    unknown20.push_back(SoundSsdBank::create("SystemBgmBank", static_cast<SoundCategory>(1), 4));
    unknown20.push_back(SoundSsdBank::create("SystemVoiceBank", static_cast<SoundCategory>(2), 8));
    unknown20.push_back(SoundSsdBank::create("SystemSystemBank", static_cast<SoundCategory>(3), 0x40));
    loadCommonSe();
    loadBattleSe();
  }

  return true;
}

} // namespace fw
