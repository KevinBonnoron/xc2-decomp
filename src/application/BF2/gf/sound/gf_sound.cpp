#include "gf/sound/gf_sound.h"

#include "framework/sound/sound_manager.h"
#include "gf/data/gf_bdat_bgm.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_option.h"
#include "gf/field/gf_field_sound.h"
#include "gf/gf_allocator.h"
#include "gf/gf_pause.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/fixed_vector.h"

namespace fw {
enum SoundVolumeType : int;
} // namespace fw

namespace gf {

namespace {

const u32 INVALID_SE_PARAM = 0xffff;

constexpr fw::SoundVolumeType VOLUME_TYPE_CURRENT = static_cast<fw::SoundVolumeType>(0);

u32 getCategoryIndex(GF_SE_CATEGORY_HANDLE *handle) { return reinterpret_cast<u64>(handle) & 0xff; }

} // namespace

void SoundParam::clear() {
  volume = 1.0f;
  id = 0;
  name.clear();
  category = 0;
  transform = SOUND_TRANSFORM_NONE;
  seInfo = SEINFO_SEARCH;
  handle = INVALID_HANDLE;
}

void SoundParam::setupTransformGlobal(const mm::Vec3 &position) {
  transform = SOUND_TRANSFORM_GLOBAL;
  this->position = position;
}

void SoundParam::setupTransformObj(GF_OBJ_HANDLE *handle, const mm::Vec3 &offset) {
  transform = SOUND_TRANSFORM_OBJ;
  this->handle = handle;
  position = offset;
}

void SoundParam::setupTransformBone(GF_OBJ_HANDLE *handle, const char *bone, const mm::Vec3 &offset) {
  transform = SOUND_TRANSFORM_BONE;
  this->handle = handle;
  position = offset;
  this->bone = bone;
}

void GfSound::SeParam::clear() {
  seInfo = SEINFO_SEARCH;
  category = 0;
  isLoop = false;
  pauseBits = 0;
  handle = INVALID_HANDLE;
  soundHandle.clear();
}

void SoundHandle::clear() {
  handle = 0;
  seParam = INVALID_SE_PARAM;
}

SoundHandle::SoundHandle() { clear(); }

SoundHandle::SoundHandle(u32 handle) : handle(handle), seParam(INVALID_SE_PARAM) {}

bool SoundHandle::isValid() const { return handle != 0; }

void GfSound::initialize(const GfSetupParam &) {
  GfEvent::addEventCallback(this);
  masterVolume.initialize();
  categoryHandle = createCategoryHandle();
  initialized = true;
}

void GfSound::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, 166, 8) GfSound(param); }

void GfSound::destroy() {
  GfSound *sound = get();
  sound->finalize();
  delete sound;
}

void GfSound::finalize() {
  releaseCategoryHandle(categoryHandle);
  masterVolume.finalize();
  GfEvent::removeEventCallback(this);
  initialized = false;
}

void GfMasterVolume::initialize() {
  if (GfSound::get() != nullptr) {
    categoryHandle = GfSound::get()->createCategoryHandle();
  }
}

void GfSound::releaseCategoryHandle(GF_SE_CATEGORY_HANDLE *&handle) {
  if (handle != INVALID_CATEGORY_HANDLE) {
    CategoryVolume &categoryVolume = categoryVolumes[getCategoryIndex(handle)];
    for (CategoryVolume::Volume &volume : categoryVolume.volumes) {
      volume.clear();
    }
    categoryVolume.isChanged = true;
    categoryVolume.index = -1;
    isReleased = true;
    handle = INVALID_CATEGORY_HANDLE;
  }
}

void GfMasterVolume::finalize() {
  if (GfSound::get() != nullptr) {
    GfSound::get()->releaseCategoryHandle(categoryHandle);
  }
}

void GfSound::setupGame() { masterVolume.setupGame(); }

void GfMasterVolume::setupGame() {
  const SDataOption *option = GfDataManager::getDataOption();
  setEventVoiceVolume(getFloatVolume(option->eventVoiceVolume));
  setEventCsVolume(getFloatVolume(option->eventCsVolume));
  setEventBgmVolume(getFloatVolume(option->eventBgmVolume));
  setEventSeVolume(getFloatVolume(option->eventSeVolume));
  setGameBgmVolume(getFloatVolume(option->gameBgmVolume));
  setGameEnvVolume(getFloatVolume(option->gameEnvVolume));
  setGameWeatherVolume(getFloatVolume(option->gameWeatherVolume));
  setGameSeVolume(getFloatVolume(option->gameSeVolume));
  setPlayerVoiceVolume(getFloatVolume(option->playerVoiceVolume));
  setEnemyVoiceVolume(getFloatVolume(option->enemyVoiceVolume));
  setNareVoiceVolume(getFloatVolume(option->nareVoiceVolume));
  setSystemVolume(getFloatVolume(option->systemVolume));
  setMenuBgmVolume(getFloatVolume(option->menuBgmVolume));
}

void GfSound::setCategoryVolume(GF_SE_CATEGORY_HANDLE *handle, fw::SoundCategory category, f32 volume, f32 fadeTime) {
  categoryVolumes[getCategoryIndex(handle)].volumes[static_cast<u32>(category)].set(volume, fadeTime);
}

GfSound::CategoryVolume *GfSound::getCategoryVolume(GF_SE_CATEGORY_HANDLE *handle) { return &categoryVolumes[getCategoryIndex(handle)]; }

f32 GfSound::getCategoryVolume(GF_SE_CATEGORY_HANDLE *handle, fw::SoundCategory category) const { return categoryVolumes[getCategoryIndex(handle)].volumes[static_cast<u32>(category)].current; }

const GfSound::CategoryVolume *GfSound::getCategoryVolume(GF_SE_CATEGORY_HANDLE *handle) const { return &categoryVolumes[getCategoryIndex(handle)]; }

void GfSound::setCategoryPitch(fw::SoundCategory category, f32 pitch, f32 fadeTime) {
  if (fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->setCategoryPitch(category, pitch, fadeTime);
  }
}

SoundHandle GfSound::playBgm(u32 bgm, f32 volume, bool ignorePause, int loopCount, fw::SoundCategory category) {
  const char *name = GfBdatBgm::get()->getBgmListfilename(bgm);
  if (name == nullptr || name[0] == '\0') {
    return SoundHandle();
  }
  mm::mtl::FixStr<128> path;
  path.format("stream/bgm/%s", name);
  return playBgm(path.c_str(), volume, ignorePause, loopCount, category);
}

void GfSound::startBgm(SoundHandle handle) {
  if (fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->startBgm(handle.handle);
  }
}

void GfSound::stopBgm(SoundHandle handle, f32 fadeTime) {
  if (fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->stopBgm(handle.handle, fadeTime);
  }
}

SoundHandle GfSound::playVoice(const char *name, f32 volume, bool ignorePause, fw::SoundCategory category) {
  if (fw::SoundManager::get() != nullptr) {
    return SoundHandle(fw::SoundManager::get()->playVoice(name, volume, ignorePause, category));
  }
  return SoundHandle();
}

void GfSound::startVoice(SoundHandle handle) {
  if (fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->startVoice(handle.handle);
  }
}

void GfSound::stopVoice(SoundHandle handle, f32 fadeTime) {
  if (fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->stopVoice(handle.handle, fadeTime);
  }
}

SoundHandle GfSound::playSe(const SoundParam &param) {
  fw::SoundManager *soundManager = fw::SoundManager::get();
  if (soundManager != nullptr) {
    mm::mtl::FixedVector<fw::SoundPack *, 4> packs;
    SoundHandle handle;
    if (param.seInfo == SEINFO_SEARCH) {
      if (GfObjUtil::getSePackAll(packs, param.handle)) {
        handle = playSeWithPack(param, packs, SEINFO_OBJ_PACK);
        if (handle.isValid()) {
          return handle;
        }
      }
      if (soundManager->getCommonPack() != nullptr) {
        packs.clear();
        packs.push_back(soundManager->getCommonPack());
        handle = playSeWithPack(param, packs, SEINFO_COMMON_PACK);
        if (handle.isValid()) {
          return handle;
        }
      }
      GfFieldSound *fieldSound = GfFieldSound::get();
      if (fieldSound != nullptr) {
        if (fieldSound->getCommonPack() != nullptr) {
          packs.clear();
          packs.push_back(fieldSound->getCommonPack());
          handle = playSeWithPack(param, packs, SEINFO_FIELD_COMMON_PACK);
          if (handle.isValid()) {
            return handle;
          }
        }
        if (fieldSound->getMapPack() != nullptr) {
          packs.clear();
          packs.push_back(fieldSound->getMapPack());
          handle = playSeWithPack(param, packs, SEINFO_FIELD_MAP_PACK);
          if (handle.isValid()) {
            return handle;
          }
        }
      }
    } else {
      if (!getSePack(packs, param)) {
        return SoundHandle();
      }
      return playSeWithPack(param, packs, static_cast<SEINFO>(param.seInfo));
    }
  }
  return SoundHandle();
}

bool GfSound::getSePack(mm::mtl::FixedVector<fw::SoundPack *, 4> &packs, const SoundParam &param) {
  fw::SoundPack *pack;
  switch (param.seInfo) {
  case SEINFO_COMMON_PACK:
    if (fw::SoundManager::get() == nullptr) {
      break;
    }
    pack = fw::SoundManager::get()->getCommonPack();
    if (pack != nullptr) {
      packs.push_back(pack);
    }
    break;
  case SEINFO_FIELD_COMMON_PACK:
    if (GfFieldSound::get() == nullptr) {
      break;
    }
    pack = GfFieldSound::get()->getCommonPack();
    if (pack != nullptr) {
      packs.push_back(pack);
    }
    break;
  case SEINFO_FIELD_MAP_PACK:
    if (GfFieldSound::get() == nullptr) {
      break;
    }
    pack = GfFieldSound::get()->getMapPack();
    if (pack != nullptr) {
      packs.push_back(pack);
    }
    break;
  case SEINFO_OBJ_PACK:
    GfObjUtil::getSePackAll(packs, param.handle);
    break;
  }
  return !packs.empty();
}

SoundHandle GfSound::playSe(const char *name, fw::SoundCategory category) {
  if (fw::SoundManager::get() == nullptr) {
    return SoundHandle();
  }
  mm::mtl::FixedVector<fw::SoundPack *, 4> packs;
  packs.push_back(nullptr);
  SoundParam param;
  param.name = name;
  param.category = category;
  return playSeWithPack(param, packs, SEINFO_NAME);
}

void GfSound::stopSe(SoundHandle handle, f32 fadeTime) {
  if (fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->stopSe(handle.handle, fadeTime);
  }
}

void GfSound::setPan(SoundHandle handle, f32 pan, f32 fadeTime) {
  if (fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->setPan(handle.handle, pan, fadeTime);
  }
}

void GfSound::setPlayTime(SoundHandle handle, f32 time) {
  if (fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->setPlayTime(handle.handle, time);
  }
}

bool GfSound::getPlayTime(SoundHandle handle, f32 &time) const {
  if (fw::SoundManager::get() != nullptr) {
    return fw::SoundManager::get()->getPlayTime(handle.handle, time);
  }
  return false;
}

bool GfSound::getTotalTime(SoundHandle handle, f32 &time) const {
  if (fw::SoundManager::get() != nullptr) {
    return fw::SoundManager::get()->getTotalTime(handle.handle, time);
  }
  return false;
}

bool GfSound::isLoop(SoundHandle handle) const {
  if (fw::SoundManager::get() != nullptr) {
    return fw::SoundManager::get()->isLoop(handle.handle);
  }
  return false;
}

void GfSound::setVolume(SoundHandle handle, f32 volume, f32 fadeTime) {
  if (fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->setVolume(handle.handle, volume, fadeTime);
  }
}

f32 GfSound::getVolume(SoundHandle handle) {
  if (fw::SoundManager::get() != nullptr) {
    return fw::SoundManager::get()->getVolume(handle.handle, VOLUME_TYPE_CURRENT);
  }
  return 0.0f;
}

bool GfSound::isPlaying(SoundHandle handle) const {
  if (fw::SoundManager::get() != nullptr) {
    return fw::SoundManager::get()->isPlaying(handle.handle);
  }
  return false;
}

bool GfSound::isPreparing(SoundHandle handle) const {
  if (fw::SoundManager::get() != nullptr) {
    return fw::SoundManager::get()->isPreparing(handle.handle);
  }
  return false;
}

void GfSound::gevPause(u32 resumeBits, u32 pauseBits) {
  if (pauseBits & PAUSE_BIT_GAME_SOUND) {
    setPauseGameSe(true);
    setPauseGameWeatherSe(true);
  }
  if (pauseBits & PAUSE_BIT_EVENT_SOUND) {
    setPauseEventSe(true);
  }
  if (resumeBits & PAUSE_BIT_GAME_SOUND) {
    setPauseGameSe(false);
    setPauseGameWeatherSe(false);
  }
  if (resumeBits & PAUSE_BIT_EVENT_SOUND) {
    setPauseEventSe(false);
  }
}

void GfSound::gevLayerPause(u32, bool) {}

GfMasterVolume::GfMasterVolume()
    : eventVoiceVolume(0.7f), eventCsVolume(0.8f), eventBgmVolume(0.6f), eventSeVolume(0.7f), gameBgmVolume(0.6f), gameEnvVolume(0.4f), gameWeatherVolume(0.4f), gameSeVolume(0.6f),
      playerVoiceVolume(0.8f), enemyVoiceVolume(0.8f), nareVoiceVolume(0.8f), systemVolume(0.5f), menuBgmVolume(0.5f) {}

GfMasterVolume::~GfMasterVolume() {}

void GfMasterVolume::setEventVoiceVolume(f32 volume) {
  eventVoiceVolume = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_EVENT_VOICE, volume, 0.0f);
  }
}

f32 GfMasterVolume::getFloatVolume(u16 volume) {
  if (volume == 0xff) {
    return 1.0f;
  }
  return volume / VOLUME_SCALE;
}

void GfMasterVolume::setEventCsVolume(f32 volume) {
  eventCsVolume = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_EVENT_CS, volume, 0.0f);
  }
}

void GfMasterVolume::setEventBgmVolume(f32 volume) {
  eventBgmVolume = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_EVENT_BGM, volume, 0.0f);
  }
}

void GfMasterVolume::setEventSeVolume(f32 volume) {
  eventSeVolume = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_EVENT_SE, volume, 0.0f);
  }
}

void GfMasterVolume::setGameBgmVolume(f32 volume) {
  gameBgmVolume = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_GAME_BGM, volume, 0.0f);
  }
}

void GfMasterVolume::setGameEnvVolume(f32 volume) {
  gameEnvVolume = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_GAME_ENV, volume, 0.0f);
  }
}

void GfMasterVolume::setGameWeatherVolume(f32 volume) {
  gameWeatherVolume = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_GAME_WEATHER, volume, 0.0f);
  }
}

void GfMasterVolume::setGameSeVolume(f32 volume) {
  gameSeVolume = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_BATTLE_SE, volume, 0.0f);
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_FIELD_SE, volume, 0.0f);
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_GIMMICK_SE, volume, 0.0f);
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_CHARACTER_SE, volume, 0.0f);
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_NO_SLOW_SE, volume, 0.0f);
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_ENEMY_VOICE, volume, 0.0f);
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_NARE_VOICE, volume, 0.0f);
  }
}

void GfMasterVolume::setPlayerVoiceVolume(f32 volume) {
  playerVoiceVolume = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_PLAYER_VOICE, volume, 0.0f);
  }
}

void GfMasterVolume::setEnemyVoiceVolume(f32 volume) {
  enemyVoiceVolume = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_ENEMY_VOICE, volume, 0.0f);
  }
}

void GfMasterVolume::setNareVoiceVolume(f32 volume) {
  nareVoiceVolume = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_NARE_VOICE, volume, 0.0f);
  }
}

void GfMasterVolume::setSystemVolume(f32 volume) {
  systemVolume = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_SYSTEM, volume, 0.0f);
  }
}

void GfMasterVolume::setMenuBgmVolume(f32 volume) {
  menuBgmVolume = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(categoryHandle, CATEGORY_MENU_BGM, volume, 0.0f);
  }
}

} // namespace gf
