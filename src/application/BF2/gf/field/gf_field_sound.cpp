// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/field/gf_field_sound.cpp.
#include "gf/field/gf_field_sound.h"

#include "framework/memory/framework_memory.h"
#include "framework/resource/sound_resource.h"
#include "framework/sound/sound_manager.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_sound.h"
#include "gf/field/gf_field_bgm.h"
#include "gf/field/gf_field_mapse.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/sound/gf_sound.h"
#include "gf/util/gf_util.h"
#include "mm_mtl/reference_object.h"

namespace fw {
enum SoundCategory : int;
enum LOAD_PRIO : int;
} // namespace fw

namespace gf {
namespace _gffsn {
extern const char *s_szCommonName;
} // namespace _gffsn
} // namespace gf

template mm::mtl::PtrSingleton<gf::GfFieldSound>::~PtrSingleton();

namespace gf {

// Inferred role: sound categories faded by an event; original name unknown.
static const fw::SoundCategory unknown001[6] = {CATEGORY_VOICE, CATEGORY_BATTLE, CATEGORY_CH_SE, CATEGORY_CH_SE_NS, CATEGORY_ENE_VO, CATEGORY_NAREVO};

// Inferred role: sound categories faded by a map jump; original name unknown.
static const fw::SoundCategory unknown002[9] = {CATEGORY_VOICE, CATEGORY_BATTLE, CATEGORY_FIELD, CATEGORY_GIMMICK, CATEGORY_ENV, CATEGORY_CH_SE, CATEGORY_CH_SE_NS, CATEGORY_ENE_VO, CATEGORY_NAREVO};

// Inferred role: sound categories destroyed after a map jump; original name unknown.
static const fw::SoundCategory unknown003[7] = {CATEGORY_FIELD, CATEGORY_GIMMICK, CATEGORY_ENV, CATEGORY_CH_SE, CATEGORY_CH_SE_NS, CATEGORY_ENE_VO, CATEGORY_NAREVO};

GfFieldSound::GfFieldSound(const GfSetupParam &param)
    : unknown08(false), unknown10(nullptr), unknown18(nullptr), unknown20(nullptr), m_commonPack(nullptr), unknown30(nullptr), m_mapPack(nullptr), unknown108(unknown019), unknown110(unknown019),
      unknown118(unknown019) {
  initialize(param);
}

void GfFieldSound::build(const GfSetupParam &param) {
// __LINE__ of the operator new call is 0x75 in the game.
#line 117
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfFieldSound(param);
}

void GfFieldSound::initialize(const GfSetupParam &) {
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    unknown108 = sound->createCategoryHandle();
    unknown110 = sound->createCategoryHandle();
    unknown118 = sound->createCategoryHandle();
  }
// __LINE__ of the first operator new call is 0x92 in the game.
#line 146
  unknown10 = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfFieldBgm();
#line 149
  unknown18 = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfFieldMapSe();
  createCommonSound();
  unknown08 = true;
}

GfFieldSound::~GfFieldSound() {}

void GfFieldSound::destroy() {
  GfFieldSound *sound = get();
  sound->finalize();
  delete sound;
}

void GfFieldSound::finalize() {
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
  if (unknown10 != nullptr) {
    delete unknown10;
    unknown10 = nullptr;
  }
  m_commonPack = nullptr;
  m_mapPack = nullptr;
  mm::mtl::safeRelease(unknown20);
  mm::mtl::safeRelease(unknown30);
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    sound->releaseCategoryHandle(unknown108);
    sound->releaseCategoryHandle(unknown110);
    sound->releaseCategoryHandle(unknown118);
  }
  unknown08 = false;
}

void GfFieldSound::createCommonSound() {
  fw::SoundResource::SetupInfo info;
  info.unknown00 = CATEGORY_FIELD;
  mm::mtl::FixStr<128> path;
  GfDataSound::getFullPath(path, _gffsn::s_szCommonName);
  unknown20 = fw::SoundResource::request(fw::FrameworkMemory::getAllocator(8), path.c_str(), info, static_cast<fw::LOAD_PRIO>(10));
  while (!unknown20->valid()) {
    GfSleep(1);
  }
  m_commonPack = fw::SoundManager::get()->findPack(_gffsn::s_szCommonName, nullptr);
}

void GfFieldSound::createMapSound() {
  destroyMapSound();
  const char *name = GfDataMap::getMapResourceName(GfGameManager::getMapJumpID());
  if (name != nullptr) {
    fw::SoundResource::SetupInfo info;
    info.unknown00 = CATEGORY_FIELD;
    getMapSeFile(unknown40, name);
    unknownc4 = util::getNoPathExtName(unknown40.c_str());
    unknown30 = fw::SoundResource::request(fw::FrameworkMemory::getAllocator(8), unknown40.c_str(), info, static_cast<fw::LOAD_PRIO>(10));
  }
}

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
