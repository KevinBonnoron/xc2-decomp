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
#include "ml/fixed_size_alloc.h"
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

u32 getSoundSourceCount() { return 3; }

const char *getSoundSourceFileName(u32 index) { return SS_NAME_TABLE[index]; }

void SoundParam::clear() {
  unknown28 = 1.0f;
  unknown00 = 0;
  unknown04.clear();
  unknown38 = 0;
  unknown39 = SOUND_TRANSFORM_NONE;
  unknown3a = SEINFO_SEARCH;
  unknown30 = INVALID_HANDLE;
}

void SoundParam::setupTransformGlobal(const mm::Vec3 &position) {
  unknown39 = SOUND_TRANSFORM_GLOBAL;
  this->unknown40 = position;
}

void SoundParam::setupTransformObj(GF_OBJ_HANDLE *handle, const mm::Vec3 &offset) {
  unknown39 = SOUND_TRANSFORM_OBJ;
  this->unknown30 = handle;
  unknown40 = offset;
}

void SoundParam::setupTransformBone(GF_OBJ_HANDLE *handle, const char *bone, const mm::Vec3 &offset) {
  unknown39 = SOUND_TRANSFORM_BONE;
  this->unknown30 = handle;
  unknown40 = offset;
  this->unknown50 = bone;
}

void GfSound::SeParam::clear() {
  unknown00 = SEINFO_SEARCH;
  unknown01 = 0;
  unknown02 = false;
  unknown03 = 0;
  unknown08 = INVALID_HANDLE;
  unknown10.clear();
}

void SoundHandle::clear() {
  unknown00 = 0;
  unknown04 = INVALID_SE_PARAM;
}

SoundHandle::SoundHandle() { clear(); }

SoundHandle::SoundHandle(u32 handle) : unknown00(handle), unknown04(INVALID_SE_PARAM) {}

bool SoundHandle::isValid() const { return unknown00 != 0; }

void GfSound::initialize(const GfSetupParam &) {
  GfEvent::addEventCallback(this);
  unknown6690.initialize();
  unknown66d0 = createCategoryHandle();
  unknown10 = true;
}

void GfSound::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, 166, 8) GfSound(param); }

void GfSound::destroy() {
  GfSound *sound = get();
  sound->finalize();
  delete sound;
}

void GfSound::finalize() {
  releaseCategoryHandle(unknown66d0);
  unknown6690.finalize();
  GfEvent::removeEventCallback(this);
  unknown10 = false;
}

void GfMasterVolume::initialize() {
  if (GfSound::get() != nullptr) {
    unknown00 = GfSound::get()->createCategoryHandle();
  }
}

void GfSound::releaseCategoryHandle(GF_SE_CATEGORY_HANDLE *&handle) {
  if (handle != INVALID_CATEGORY_HANDLE) {
    CategoryVolume &categoryVolume = unknown20[getCategoryIndex(handle)];
    for (CategoryVolume::Volume &volume : categoryVolume.unknown00) {
      volume.clear();
    }
    categoryVolume.unknown16c = true;
    categoryVolume.unknown168 = -1;
    unknown11 = true;
    handle = INVALID_CATEGORY_HANDLE;
  }
}

void GfMasterVolume::finalize() {
  if (GfSound::get() != nullptr) {
    GfSound::get()->releaseCategoryHandle(unknown00);
  }
}

void GfSound::setupGame() { unknown6690.setupGame(); }

void GfMasterVolume::setupGame() {
  const SDataOption *option = GfDataManager::getDataOption();
  setEventVoiceVolume(getFloatVolume(option->unknown4c));
  setEventCsVolume(getFloatVolume(option->unknown4e));
  setEventBgmVolume(getFloatVolume(option->unknown50));
  setEventSeVolume(getFloatVolume(option->unknown52));
  setGameBgmVolume(getFloatVolume(option->unknown54));
  setGameEnvVolume(getFloatVolume(option->unknown56));
  setGameWeatherVolume(getFloatVolume(option->unknown58));
  setGameSeVolume(getFloatVolume(option->unknown5a));
  setPlayerVoiceVolume(getFloatVolume(option->unknown5c));
  setEnemyVoiceVolume(getFloatVolume(option->unknown5e));
  setNareVoiceVolume(getFloatVolume(option->unknown60));
  setSystemVolume(getFloatVolume(option->unknown62));
  setMenuBgmVolume(getFloatVolume(option->unknown64));
}

void GfSound::setCategoryVolume(GF_SE_CATEGORY_HANDLE *handle, fw::SoundCategory category, f32 volume, f32 fadeTime) {
  unknown20[getCategoryIndex(handle)].unknown00[static_cast<u32>(category)].set(volume, fadeTime);
}

GfSound::CategoryVolume *GfSound::getCategoryVolume(GF_SE_CATEGORY_HANDLE *handle) { return &unknown20[getCategoryIndex(handle)]; }

f32 GfSound::getCategoryVolume(GF_SE_CATEGORY_HANDLE *handle, fw::SoundCategory category) const { return unknown20[getCategoryIndex(handle)].unknown00[static_cast<u32>(category)].unknown00; }

const GfSound::CategoryVolume *GfSound::getCategoryVolume(GF_SE_CATEGORY_HANDLE *handle) const { return &unknown20[getCategoryIndex(handle)]; }

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
    fw::SoundManager::get()->startBgm(handle.unknown00);
  }
}

void GfSound::stopBgm(SoundHandle handle, f32 fadeTime) {
  if (fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->stopBgm(handle.unknown00, fadeTime);
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
    fw::SoundManager::get()->startVoice(handle.unknown00);
  }
}

void GfSound::stopVoice(SoundHandle handle, f32 fadeTime) {
  if (fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->stopVoice(handle.unknown00, fadeTime);
  }
}

SoundHandle GfSound::playSe(const SoundParam &param) {
  fw::SoundManager *soundManager = fw::SoundManager::get();
  if (soundManager != nullptr) {
    mm::mtl::FixedVector<fw::SoundPack *, 4> packs;
    SoundHandle handle;
    if (param.unknown3a == SEINFO_SEARCH) {
      if (GfObjUtil::getSePackAll(packs, param.unknown30)) {
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
      return playSeWithPack(param, packs, static_cast<SEINFO>(param.unknown3a));
    }
  }
  return SoundHandle();
}

bool GfSound::getSePack(mm::mtl::FixedVector<fw::SoundPack *, 4> &packs, const SoundParam &param) {
  fw::SoundPack *pack;
  switch (param.unknown3a) {
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
    GfObjUtil::getSePackAll(packs, param.unknown30);
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
  param.unknown04 = name;
  param.unknown38 = category;
  return playSeWithPack(param, packs, SEINFO_NAME);
}

void GfSound::stopSe(SoundHandle handle, f32 fadeTime) {
  if (fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->stopSe(handle.unknown00, fadeTime);
  }
}

void GfSound::setPan(SoundHandle handle, f32 pan, f32 fadeTime) {
  if (fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->setPan(handle.unknown00, pan, fadeTime);
  }
}

void GfSound::setPlayTime(SoundHandle handle, f32 time) {
  if (fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->setPlayTime(handle.unknown00, time);
  }
}

bool GfSound::getPlayTime(SoundHandle handle, f32 &time) const {
  if (fw::SoundManager::get() != nullptr) {
    return fw::SoundManager::get()->getPlayTime(handle.unknown00, time);
  }
  return false;
}

bool GfSound::getTotalTime(SoundHandle handle, f32 &time) const {
  if (fw::SoundManager::get() != nullptr) {
    return fw::SoundManager::get()->getTotalTime(handle.unknown00, time);
  }
  return false;
}

bool GfSound::isLoop(SoundHandle handle) const {
  if (fw::SoundManager::get() != nullptr) {
    return fw::SoundManager::get()->isLoop(handle.unknown00);
  }
  return false;
}

void GfSound::setVolume(SoundHandle handle, f32 volume, f32 fadeTime) {
  if (fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->setVolume(handle.unknown00, volume, fadeTime);
  }
}

f32 GfSound::getVolume(SoundHandle handle) {
  if (fw::SoundManager::get() != nullptr) {
    return fw::SoundManager::get()->getVolume(handle.unknown00, VOLUME_TYPE_CURRENT);
  }
  return 0.0f;
}

bool GfSound::isPlaying(SoundHandle handle) const {
  if (fw::SoundManager::get() != nullptr) {
    return fw::SoundManager::get()->isPlaying(handle.unknown00);
  }
  return false;
}

bool GfSound::isPreparing(SoundHandle handle) const {
  if (fw::SoundManager::get() != nullptr) {
    return fw::SoundManager::get()->isPreparing(handle.unknown00);
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
    : unknown08(0.7f), unknown0c(0.8f), unknown10(0.6f), unknown14(0.7f), unknown18(0.6f), unknown1c(0.4f), unknown20(0.4f), unknown24(0.6f), unknown28(0.8f), unknown2c(0.8f), unknown30(0.8f),
      unknown34(0.5f), unknown38(0.5f) {}

GfMasterVolume::~GfMasterVolume() {}

void GfMasterVolume::setEventVoiceVolume(f32 volume) {
  unknown08 = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_EVENT_VOICE, volume, 0.0f);
  }
}

f32 GfMasterVolume::getFloatVolume(u16 volume) {
  if (volume == 0xff) {
    return 1.0f;
  }
  return volume / VOLUME_SCALE;
}

void GfMasterVolume::setEventCsVolume(f32 volume) {
  unknown0c = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_EVENT_CS, volume, 0.0f);
  }
}

void GfMasterVolume::setEventBgmVolume(f32 volume) {
  unknown10 = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_EVENT_BGM, volume, 0.0f);
  }
}

void GfMasterVolume::setEventSeVolume(f32 volume) {
  unknown14 = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_EVENT_SE, volume, 0.0f);
  }
}

void GfMasterVolume::setGameBgmVolume(f32 volume) {
  unknown18 = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_GAME_BGM, volume, 0.0f);
  }
}

void GfMasterVolume::setGameEnvVolume(f32 volume) {
  unknown1c = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_GAME_ENV, volume, 0.0f);
  }
}

void GfMasterVolume::setGameWeatherVolume(f32 volume) {
  unknown20 = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_GAME_WEATHER, volume, 0.0f);
  }
}

void GfMasterVolume::setGameSeVolume(f32 volume) {
  unknown24 = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_BATTLE_SE, volume, 0.0f);
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_FIELD_SE, volume, 0.0f);
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_GIMMICK_SE, volume, 0.0f);
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_CHARACTER_SE, volume, 0.0f);
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_NO_SLOW_SE, volume, 0.0f);
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_ENEMY_VOICE, volume, 0.0f);
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_NARE_VOICE, volume, 0.0f);
  }
}

void GfMasterVolume::setPlayerVoiceVolume(f32 volume) {
  unknown28 = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_PLAYER_VOICE, volume, 0.0f);
  }
}

void GfMasterVolume::setEnemyVoiceVolume(f32 volume) {
  unknown2c = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_ENEMY_VOICE, volume, 0.0f);
  }
}

void GfMasterVolume::setNareVoiceVolume(f32 volume) {
  unknown30 = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_NARE_VOICE, volume, 0.0f);
  }
}

void GfMasterVolume::setSystemVolume(f32 volume) {
  unknown34 = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_SYSTEM, volume, 0.0f);
  }
}

void GfMasterVolume::setMenuBgmVolume(f32 volume) {
  unknown38 = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_MENU_BGM, volume, 0.0f);
  }
}

GfSound::SeParam *GfSound::getSeParam(u16 id) {
  if (id == 0xffff) {
    return nullptr;
  }
  return &unknown5268[id];
}

} // namespace gf

template class ml::fixed_size_alloc_inside<gf::GfSound::SeParam, 384>;

template mm::mtl::PtrSingleton<gf::GfSound>::~PtrSingleton();
