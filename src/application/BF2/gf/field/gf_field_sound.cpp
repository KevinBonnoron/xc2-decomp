// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/field/gf_field_sound.cpp.
#include "gf/field/gf_field_sound.h"

#include "framework/resource/sound_resource.h"
#include "framework/sound/sound_manager.h"
#include "gf/data/gf_data_sound.h"
#include "gf/field/gf_field_bgm.h"
#include "gf/field/gf_field_mapse.h"
#include "gf/gf_manager.h"
#include "gf/sound/gf_sound.h"
#include "mm_mtl/reference_object.h"

namespace fw {
enum SoundCategory : int;
} // namespace fw

template mm::mtl::PtrSingleton<gf::GfFieldSound>::~PtrSingleton();

namespace gf {

// Inferred role: sound categories faded by an event; original name unknown.
static const fw::SoundCategory unknown001[6] = {CATEGORY_PLAYER_VOICE, CATEGORY_BATTLE_SE, CATEGORY_CHARACTER_SE, CATEGORY_NO_SLOW_SE, CATEGORY_ENEMY_VOICE, CATEGORY_NARE_VOICE};

// Inferred role: sound categories faded by a map jump; original name unknown.
static const fw::SoundCategory unknown002[9] = {
    CATEGORY_PLAYER_VOICE, CATEGORY_BATTLE_SE, CATEGORY_FIELD_SE, CATEGORY_GIMMICK_SE, CATEGORY_GAME_ENV, CATEGORY_CHARACTER_SE, CATEGORY_NO_SLOW_SE, CATEGORY_ENEMY_VOICE, CATEGORY_NARE_VOICE};

// Inferred role: sound categories destroyed after a map jump; original name unknown.
static const fw::SoundCategory unknown003[7] = {CATEGORY_FIELD_SE, CATEGORY_GIMMICK_SE, CATEGORY_GAME_ENV, CATEGORY_CHARACTER_SE, CATEGORY_NO_SLOW_SE, CATEGORY_ENEMY_VOICE, CATEGORY_NARE_VOICE};

GfFieldSound::~GfFieldSound() {}

void GfFieldSound::destroyCommonSound() {
  m_commonPack = nullptr;
  mm::mtl::safeRelease(unknown20);
}

void GfFieldSound::getMapSeFile(mm::mtl::FixStr<128> &path, const char *name) {
  mm::mtl::FixStr<64> file;
  file.format("se_fld_%s", name);
  GfDataSound::getFullPath(path, file.c_str());
}

void GfFieldSound::update(const fw::UpdateInfo &info) {
  if (unknown10 != nullptr) {
    unknown10->update(info);
  }
  if (unknown18 != nullptr) {
    unknown18->update(info);
  }
}

void GfFieldSound::postUpdate(const fw::UpdateInfo &info) {
  if (unknown18 != nullptr) {
    unknown18->postUpdate(info);
  }
}

void GfFieldSound::clear() {
  if (unknown10 != nullptr) {
    unknown10->destroy();
  }
  if (unknown18 != nullptr) {
    unknown18->destroy();
  }
}

void GfFieldSound::gevGameMapModel(GF_OBJ_HANDLE *handle, bool isEnter) {
  if (unknown18 != nullptr) {
    unknown18->gevGameMapModel(handle, isEnter);
  }
}

void GfFieldSound::gevPlayEvent(GEV event, u32 value) {
  if (unknown10 != nullptr) {
    unknown10->gevPlayEvent(event, value);
  }
}

void GfFieldSound::gevBattleEnd() {
  if (unknown10 != nullptr) {
    unknown10->gevBattleEnd();
  }
}

void GfFieldSound::gevMapjump(GEV event, const MapjumpCallbackInfo &info) {
  if (GfFieldBgm::get() != nullptr) {
    GfFieldBgm::get()->gevMapjump(event, info);
  }
}

void GfFieldSound::gevPause(u32 resumeBits, u32 pauseBits) {
  if (unknown10 != nullptr) {
    unknown10->gevPause(resumeBits, pauseBits);
  }
  if (unknown18 != nullptr) {
    unknown18->gevPause(resumeBits, pauseBits);
  }
}

void GfFieldSound::setCategorySeFadeoutForEvent(f32 volume) {
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    for (u32 i = 0; i < 6; i++) {
      sound->setCategoryVolume(unknown118, unknown001[i], volume, 0.0f);
    }
  }
}

void GfFieldSound::setCategorySeFadeoutForMapjump(f32 fadeTime) {
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    for (u32 i = 0; i < 9; i++) {
      sound->setCategoryVolume(unknown110, unknown002[i], 0.0f, fadeTime);
    }
  }
}

void GfFieldSound::setCategorySeFadeinForMapjump(f32 fadeTime) {
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    for (u32 i = 0; i < 9; i++) {
      sound->setCategoryVolume(unknown110, unknown002[i], 1.0f, fadeTime);
    }
  }
}

void GfFieldSound::destroyCategorySeForMapjump() {
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    for (u32 i = 0; i < 7; i++) {
      sound->destroyCategorySe(unknown003[i]);
    }
  }
}

void GfFieldSound::destroyMapSound() {
  m_mapPack = nullptr;
  mm::mtl::safeRelease(unknown30);
  unknown40.clear();
  unknownc4.clear();
}

void GfFieldSound::waitLoadMapSound() {
  if (unknown30 != nullptr) {
    while (!unknown30->valid()) {
      GfSleep(1);
    }
    if (fw::SoundManager::get() != nullptr) {
      m_mapPack = fw::SoundManager::get()->findPack(unknownc4.c_str(), nullptr);
    }
  }
}

fw::SoundPack *GfFieldSound::getCommonPack() { return m_commonPack; }

fw::SoundPack *GfFieldSound::getMapPack() { return m_mapPack; }

} // namespace gf
