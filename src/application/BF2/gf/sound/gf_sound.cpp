#include "gf/sound/gf_sound.h"

#include <new>

#include "arc/arc_data.h"
#include "framework/resource/common_resource.h"
#include "framework/sound/sound_manager.h"
#include "framework/sound/sound_pack.h"
#include "framework/sound/sound_res_source_manager.h"
#include "fw/fw_update_info.h"
#include "gf/asset/gf_asset_resource.h"
#include "gf/data/gf_bdat_bgm.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_option.h"
#include "gf/field/gf_field_sound.h"
#include "gf/gf_allocator.h"
#include "gf/gf_pause.h"
#include "gf/gf_static_res.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "ml/fixed_size_alloc.h"
#include "mm_mtl/fixed_vector.h"

namespace fw {
enum SoundVolumeType : int;
} // namespace fw

namespace gf {

namespace {

const u32 INVALID_UNKNOWN_65535 = 0xffff; // Inferred role: invalid se param; original name unknown.

constexpr fw::SoundVolumeType VOLUME_TYPE_UNKNOWN_0 = static_cast<fw::SoundVolumeType>(0); // Inferred role: volume type current; original name unknown.

u32 getCategoryIndex(GF_SE_CATEGORY_HANDLE *handle) { return reinterpret_cast<u64>(handle) & 0xff; }

// Inferred role: tests the categories of the game se; original name unknown.
bool unknown001(u8 category) {
  switch (category) {
  case CATEGORY_BATTLE:
  case CATEGORY_FIELD:
  case CATEGORY_GIMMICK:
  case CATEGORY_CH_SE:
  case CATEGORY_CH_SE_NS:
  case CATEGORY_ENE_VO:
  case CATEGORY_NAREVO:
    return true;
  default:
    return false;
  }
}

// Inferred role: tests the categories of the event se; original name unknown.
bool unknown002(u8 category) {
  switch (category) {
  case CATEGORY_BGM:
  case CATEGORY_EVT_CS:
  case CATEGORY_EVT_VOICE:
  case CATEGORY_EVT_SE:
    return true;
  default:
    return false;
  }
}

} // namespace

// Named as the game's symbol gf::SS_NAME_TABLE.
const char *const SS_NAME_TABLE[] = {"/sound/tag/source/field.ssp", "/sound/tag/source/battle.ssp", "/sound/tag/source/event.ssp"};

u32 getSoundSourceCount() { return 3; }

const char *getSoundSourceFileName(u32 index) { return SS_NAME_TABLE[index]; }

void registerSSPack(arc::CArcData &archive, fw::SoundResSourceManager *manager) {
  u32 count = archive.getFiles();
  for (u32 i = 0; i < count; i++) {
    manager->pushResource(fw::SoundResSourceImporter::importBinary(archive.getFileAdr(i)));
  }
}

void bindGFSoundSource() {
  if (fw::SoundResSourceManager::get() != nullptr) {
    fw::SoundResSourceManager::beginPush(getSoundSourceCount(), getAllocator(ALLOCATOR_UNKNOWN_0));
    for (u32 i = 0; i < getSoundSourceCount(); i++) {
      fw::CommonResource *resource = GfStaticRes::search(getSoundSourceFileName(i));
      if (resource != nullptr) {
        arc::CArcData archive(resource->getAssetData());
        registerSSPack(archive, fw::SoundResSourceManager::get());
      }
    }
    fw::SoundResSourceManager::endPush();
  }
}

void unrbindGFSoundSource() {
  if (fw::SoundResSourceManager::get() != nullptr) {
    fw::SoundResSourceManager::clearAll();
  }
}

void reloadGFSoundSource() {
  unrbindGFSoundSource();
  for (u32 i = 0; i < getSoundSourceCount(); i++) {
    GfStaticRes::reloadRequestForDebug(getSoundSourceFileName(i));
  }
  bindGFSoundSource();
}

void SoundParam::clear() {
  unknown28 = 1.0f;
  unknown00 = 0;
  unknown04.clear();
  unknown38 = 0;
  unknown39 = SOUND_TRANSFORM_UNKNOWN_0;
  unknown3a = SEINFO_UNKNOWN_0;
  unknown30 = unknown020;
}

void SoundParam::setupTransformGlobal(const mm::Vec3 &position) {
  unknown39 = SOUND_TRANSFORM_UNKNOWN_1;
  this->unknown40 = position;
}

void SoundParam::setupTransformObj(GF_OBJ_HANDLE *handle, const mm::Vec3 &offset) {
  unknown39 = SOUND_TRANSFORM_UNKNOWN_2;
  this->unknown30 = handle;
  unknown40 = offset;
}

void SoundParam::setupTransformBone(GF_OBJ_HANDLE *handle, const char *bone, const mm::Vec3 &offset) {
  unknown39 = SOUND_TRANSFORM_UNKNOWN_3;
  this->unknown30 = handle;
  unknown40 = offset;
  this->unknown50 = bone;
}

void GfSound::SeParam::clear() {
  unknown00 = SEINFO_UNKNOWN_0;
  unknown01 = 0;
  unknown02 = false;
  unknown03 = 0;
  unknown08 = unknown020;
  unknown10.clear();
}

void SoundHandle::clear() {
  unknown00 = 0;
  unknown04 = INVALID_UNKNOWN_65535;
}

SoundHandle::SoundHandle() { clear(); }

SoundHandle::SoundHandle(u32 handle) : unknown00(handle), unknown04(INVALID_UNKNOWN_65535) {}

bool SoundHandle::isValid() const { return unknown00 != 0; }

GfSound::GfSound(const GfSetupParam &param) : unknown10(false), unknown11(false), unknown18(0), unknown66d0(unknown019) { initialize(param); }

void GfSound::initialize(const GfSetupParam &) {
  GfEvent::addEventCallback(this);
  unknown6690.initialize();
  unknown66d0 = createCategoryHandle();
  unknown10 = true;
}

GfSound::~GfSound() {}

void GfSound::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, 166, 8) GfSound(param); }

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

GF_SE_CATEGORY_HANDLE *GfSound::createCategoryHandle() {
  for (u32 i = 0; i < CATEGORY_UNKNOWN_32; i++) {
    if (!unknown20[i].unknown001()) {
      int index = i;
      CategoryVolume &categoryVolume = unknown20[index];
      for (CategoryVolume::Volume &volume : categoryVolume.unknown00) {
        volume.clear();
      }
      categoryVolume.unknown16c = true;
      categoryVolume.unknown168 = index;
      GF_SE_CATEGORY_HANDLE *handle = reinterpret_cast<GF_SE_CATEGORY_HANDLE *>(i | unknown18 << 8);
      unknown18++;
      return handle;
    }
  }
  return unknown019;
}

void GfSound::releaseCategoryHandle(GF_SE_CATEGORY_HANDLE *&handle) {
  if (handle != unknown019) {
    CategoryVolume &categoryVolume = unknown20[getCategoryIndex(handle)];
    for (CategoryVolume::Volume &volume : categoryVolume.unknown00) {
      volume.clear();
    }
    categoryVolume.unknown16c = true;
    categoryVolume.unknown168 = -1;
    unknown11 = true;
    handle = unknown019;
  }
}

void GfMasterVolume::finalize() {
  if (GfSound::get() != nullptr) {
    GfSound::get()->releaseCategoryHandle(unknown00);
  }
}

void GfSound::update(const fw::UpdateInfo &info) {
  calcCategoryVolume(info);
  updateSeParamList(info);
  unknown11 = false;
}

void GfSound::updateSeParamList(const fw::UpdateInfo &) {
  fw::SoundManager *soundManager = fw::SoundManager::get();
  if (soundManager == nullptr) {
    return;
  }
  for (mm::mtl::FixedList<u16, 512>::iterator it = unknown5278.begin(); it != unknown5278.end();) {
    if (!soundManager->isValid(getSeParam(*it)->unknown10.unknown00)) {
      deAllocateSeParam(*it);
      it = unknown5278.erase(it);
    } else {
      ++it;
    }
  }
}

bool GfSound::calcCategoryVolume(const fw::UpdateInfo &info) {
  for (CategoryVolume &categoryVolume : unknown20) {
    if (categoryVolume.unknown001()) {
      categoryVolume.unknown16c = false;
      for (CategoryVolume::Volume &volume : categoryVolume.unknown00) {
        if (volume.unknown10 == 0.0f) {
          if (volume.unknown00 != volume.unknown04) {
            volume.unknown00 = volume.unknown04;
            categoryVolume.unknown16c = true;
          }
        } else {
          volume.unknown10 -= info.unknown04;
          if (volume.unknown10 > 0.0f) {
            f32 rate = volume.unknown10 / volume.unknown0c;
            volume.unknown00 = volume.unknown04 * (1.0f - rate) + rate * volume.unknown08;
          } else {
            volume.unknown0c = 0.0f;
            volume.unknown10 = 0.0f;
            volume.unknown00 = volume.unknown04;
          }
          categoryVolume.unknown16c = true;
        }
      }
    }
  }

  if (!isNeedUpdateCategoryVolume()) {
    return false;
  }

  f32 volumes[CATEGORY_UNKNOWN_18];
  for (u32 category = 1; category < CATEGORY_UNKNOWN_18; category++) {
    volumes[category] = 1.0f;
  }

  for (u32 i = 0; i < CATEGORY_UNKNOWN_32; i++) {
    if (unknown20[i].unknown001()) {
      for (u32 category = 1; category < CATEGORY_UNKNOWN_18; category++) {
        volumes[category] *= unknown20[i].unknown00[category].unknown00;
      }
    }
  }

  fw::SoundManager *soundManager = fw::SoundManager::get();
  if (soundManager != nullptr) {
    for (u32 category = 1; category < CATEGORY_UNKNOWN_18; category++) {
      soundManager->setCategoryVolume(static_cast<fw::SoundCategory>(category), volumes[category], 0.0f);
    }
  }

  return true;
}

void GfSound::setupGame() { unknown6690.setupGame(); }

void GfMasterVolume::setupGame() {
  const SDataOption *option = GfDataManager::getDataOption();
  setEventVoiceVolume(getFloatVolume(option->unknown4c.unknown00));
  setEventCsVolume(getFloatVolume(option->unknown4c.unknown02));
  setEventBgmVolume(getFloatVolume(option->unknown4c.unknown04));
  setEventSeVolume(getFloatVolume(option->unknown4c.unknown06));
  setGameBgmVolume(getFloatVolume(option->unknown4c.unknown08));
  setGameEnvVolume(getFloatVolume(option->unknown4c.unknown0a));
  setGameWeatherVolume(getFloatVolume(option->unknown4c.unknown0c));
  setGameSeVolume(getFloatVolume(option->unknown4c.unknown0e));
  setPlayerVoiceVolume(getFloatVolume(option->unknown4c.unknown10));
  setEnemyVoiceVolume(getFloatVolume(option->unknown4c.unknown12));
  setNareVoiceVolume(getFloatVolume(option->unknown4c.unknown14));
  setSystemVolume(getFloatVolume(option->unknown4c.unknown16));
  setMenuBgmVolume(getFloatVolume(option->unknown4c.unknown18));
}

void GfSound::setCategoryVolume(GF_SE_CATEGORY_HANDLE *handle, fw::SoundCategory category, f32 volume, f32 fadeTime) {
  unknown20[getCategoryIndex(handle)].unknown00[static_cast<u32>(category)].set(volume, fadeTime);
}

GfSound::CategoryVolume *GfSound::getCategoryVolume(GF_SE_CATEGORY_HANDLE *handle) { return &unknown20[getCategoryIndex(handle)]; }

f32 GfSound::getCategoryVolume(GF_SE_CATEGORY_HANDLE *handle, fw::SoundCategory category) const { return unknown20[getCategoryIndex(handle)].unknown00[static_cast<u32>(category)].unknown00; }

const GfSound::CategoryVolume *GfSound::getCategoryVolume(GF_SE_CATEGORY_HANDLE *handle) const { return &unknown20[getCategoryIndex(handle)]; }

bool GfSound::isNeedUpdateCategoryVolume() const {
  if (unknown11) {
    return true;
  }

  for (const CategoryVolume &volume : unknown20) {
    if (!volume.unknown001()) {
      continue;
    }

    if (volume.unknown16c) {
      return true;
    }
  }

  return false;
}

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

SoundHandle GfSound::playBgm(const char *name, f32 volume, bool ignorePause, int loopCount, fw::SoundCategory category) {
  SoundHandle handle;
  fw::SoundManager *soundManager = fw::SoundManager::get();
  if (soundManager != nullptr) {
    handle.unknown00 = soundManager->playBgm(name, volume, ignorePause, loopCount, category);
    if (handle.unknown00 != 0) {
      handle.unknown04 = allocateSeParam();
      SeParam *seParam = getSeParam(handle.unknown04);
      if (seParam != nullptr) {
        seParam->unknown00 = SEINFO_UNKNOWN_0;
        seParam->unknown10 = handle;
        seParam->unknown02 = soundManager->isLoop(handle.unknown00);
        seParam->unknown08 = unknown020;
        seParam->unknown01 = category;
        seParam->unknown03 = 0;
        unknown5278.push_back(handle.unknown04);
      }
    }
  }
  return handle;
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
    if (param.unknown3a == SEINFO_UNKNOWN_0) {
      if (GfObjUtil::getSePackAll(packs, param.unknown30)) {
        handle = playSeWithPack(param, packs, SEINFO_UNKNOWN_4);
        if (handle.isValid()) {
          return handle;
        }
      }
      if (soundManager->getCommonPack() != nullptr) {
        packs.clear();
        packs.push_back(soundManager->getCommonPack());
        handle = playSeWithPack(param, packs, SEINFO_UNKNOWN_1);
        if (handle.isValid()) {
          return handle;
        }
      }
      GfFieldSound *fieldSound = GfFieldSound::get();
      if (fieldSound != nullptr) {
        if (fieldSound->getCommonPack() != nullptr) {
          packs.clear();
          packs.push_back(fieldSound->getCommonPack());
          handle = playSeWithPack(param, packs, SEINFO_UNKNOWN_2);
          if (handle.isValid()) {
            return handle;
          }
        }
        if (fieldSound->getMapPack() != nullptr) {
          packs.clear();
          packs.push_back(fieldSound->getMapPack());
          handle = playSeWithPack(param, packs, SEINFO_UNKNOWN_3);
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
  case SEINFO_UNKNOWN_1:
    if (fw::SoundManager::get() == nullptr) {
      break;
    }
    pack = fw::SoundManager::get()->getCommonPack();
    if (pack != nullptr) {
      packs.push_back(pack);
    }
    break;
  case SEINFO_UNKNOWN_2:
    if (GfFieldSound::get() == nullptr) {
      break;
    }
    pack = GfFieldSound::get()->getCommonPack();
    if (pack != nullptr) {
      packs.push_back(pack);
    }
    break;
  case SEINFO_UNKNOWN_3:
    if (GfFieldSound::get() == nullptr) {
      break;
    }
    pack = GfFieldSound::get()->getMapPack();
    if (pack != nullptr) {
      packs.push_back(pack);
    }
    break;
  case SEINFO_UNKNOWN_4:
    GfObjUtil::getSePackAll(packs, param.unknown30);
    break;
  }
  return !packs.empty();
}

SoundHandle GfSound::playSeWithPack(const SoundParam &param, mm::mtl::FixedVector<fw::SoundPack *, 4> &packs, SEINFO seInfo) {
  fw::SoundManager *soundManager = fw::SoundManager::get();
  u32 id = 0;
  if (param.unknown04.empty()) {
    for (fw::SoundPack *&pack : packs) {
      id = soundManager->playSe(param.unknown00, pack, param.unknown28, static_cast<fw::SoundCategory>(param.unknown38));
      if (id != 0) {
        break;
      }
    }
  } else {
    for (fw::SoundPack *&pack : packs) {
      id = soundManager->playSe(param.unknown04.c_str(), pack, param.unknown28, static_cast<fw::SoundCategory>(param.unknown38));
      if (id != 0) {
        break;
      }
    }
  }
  SoundHandle handle(id);
  if (id != 0) {
    handle.unknown04 = allocateSeParam();
    SeParam *seParam = getSeParam(handle.unknown04);
    if (seParam != nullptr) {
      seParam->unknown00 = seInfo;
      seParam->unknown10 = handle;
      seParam->unknown02 = soundManager->isLoop(id);
      seParam->unknown01 = param.unknown38;
      seParam->unknown08 = param.unknown30;
      seParam->unknown03 = 0;
      unknown5278.push_back(handle.unknown04);
    }
    if (param.unknown39 == SOUND_TRANSFORM_UNKNOWN_1) {
      soundManager->setPos(id, param.unknown40);
    }
  }
  return handle;
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
  return playSeWithPack(param, packs, SEINFO_UNKNOWN_5);
}

void GfSound::stopSe(SoundHandle handle, f32 fadeTime) {
  if (fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->stopSe(handle.unknown00, fadeTime);
  }
}

void GfSound::destroyCategorySe(fw::SoundCategory category) {
  fw::SoundManager *soundManager = fw::SoundManager::get();
  if (soundManager == nullptr) {
    return;
  }
  for (u16 id : unknown5278) {
    SeParam *seParam = getSeParam(id);
    if (seParam->unknown01 == category) {
      soundManager->stopSe(seParam->unknown10.unknown00, 0.0f);
    }
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
    return fw::SoundManager::get()->getVolume(handle.unknown00, VOLUME_TYPE_UNKNOWN_0);
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

fw::SoundPack *GfSound::createObjSePack(GfAssetResource *resource) {
  if (resource == nullptr || !resource->isValidData()) {
    return nullptr;
  }
  fw::SoundPack::SetupInfo info;
  info.unknown84 = CATEGORY_CH_SE;
  info.unknowna4 = 8;
  info.unknown00 = resource->getAssetName();
  info.unknown90 = resource->getAssetName();
  info.unknown98 = resource->getAssetData();
  info.unknowna0 = resource->getAssetSize();
  return fw::SoundPack::create(info);
}

void GfSound::destroyObjSePack(fw::SoundPack *&pack) {
  if (pack != nullptr) {
    pack->release();
    pack = nullptr;
  }
}

void GfSound::gevPause(u32 resumeBits, u32 pauseBits) {
  if (pauseBits & PAUSE_BIT_UNKNOWN_3) {
    setPauseGameSe(true);
    setPauseGameWeatherSe(true);
  }
  if (pauseBits & PAUSE_BIT_UNKNOWN_2) {
    setPauseEventSe(true);
  }
  if (resumeBits & PAUSE_BIT_UNKNOWN_3) {
    setPauseGameSe(false);
    setPauseGameWeatherSe(false);
  }
  if (resumeBits & PAUSE_BIT_UNKNOWN_2) {
    setPauseEventSe(false);
  }
}

void GfSound::setPauseGameSe(bool isPause) {
  f32 volume = isPause ? 0.0f : 1.0f;
  setCategoryVolume(unknown66d0, CATEGORY_BATTLE, volume, 0.0f);
  setCategoryVolume(unknown66d0, CATEGORY_FIELD, volume, 0.0f);
  setCategoryVolume(unknown66d0, CATEGORY_GIMMICK, volume, 0.0f);
  setCategoryVolume(unknown66d0, CATEGORY_CH_SE, volume, 0.0f);
  setCategoryVolume(unknown66d0, CATEGORY_CH_SE_NS, volume, 0.0f);
  setCategoryVolume(unknown66d0, CATEGORY_ENE_VO, volume, 0.0f);
  setCategoryVolume(unknown66d0, CATEGORY_NAREVO, volume, 0.0f);
  for (u16 id : unknown5278) {
    SeParam *seParam = getSeParam(id);
    if (unknown001(seParam->unknown01)) {
      setPauseType(seParam->unknown10, isPause, 0.0f, 2);
    }
  }
}

void GfSound::setPauseGameWeatherSe(bool isPause) {
  f32 volume = isPause ? 0.0f : 1.0f;
  setCategoryVolume(unknown66d0, CATEGORY_ENV, volume, 0.0f);
  setCategoryVolume(unknown66d0, CATEGORY_WEATHER, volume, 0.0f);
  for (u16 id : unknown5278) {
    SeParam *seParam = getSeParam(id);
    switch (seParam->unknown01) {
    case CATEGORY_ENV:
    case CATEGORY_WEATHER:
      setPauseType(seParam->unknown10, isPause, 0.0f, 2);
      break;
    }
  }
}

void GfSound::setPauseEventSe(bool isPause) {
  for (u16 id : unknown5278) {
    SeParam *seParam = getSeParam(id);
    if (unknown002(seParam->unknown01)) {
      setPauseType(seParam->unknown10, isPause, 0.0f, 4);
    }
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
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_EVT_VOICE, volume, 0.0f);
  }
}

f32 GfMasterVolume::getFloatVolume(u16 volume) {
  if (volume == 0xff) {
    return 1.0f;
  }
  return volume / unknown005;
}

void GfMasterVolume::setEventCsVolume(f32 volume) {
  unknown0c = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_EVT_CS, volume, 0.0f);
  }
}

void GfMasterVolume::setEventBgmVolume(f32 volume) {
  unknown10 = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_EVT_BGM, volume, 0.0f);
  }
}

void GfMasterVolume::setEventSeVolume(f32 volume) {
  unknown14 = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_EVT_SE, volume, 0.0f);
  }
}

void GfMasterVolume::setGameBgmVolume(f32 volume) {
  unknown18 = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_BGM, volume, 0.0f);
  }
}

void GfMasterVolume::setGameEnvVolume(f32 volume) {
  unknown1c = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_ENV, volume, 0.0f);
  }
}

void GfMasterVolume::setGameWeatherVolume(f32 volume) {
  unknown20 = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_WEATHER, volume, 0.0f);
  }
}

void GfMasterVolume::setGameSeVolume(f32 volume) {
  unknown24 = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_BATTLE, volume, 0.0f);
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_FIELD, volume, 0.0f);
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_GIMMICK, volume, 0.0f);
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_CH_SE, volume, 0.0f);
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_CH_SE_NS, volume, 0.0f);
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_ENE_VO, volume, 0.0f);
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_NAREVO, volume, 0.0f);
  }
}

void GfMasterVolume::setPlayerVoiceVolume(f32 volume) {
  unknown28 = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_VOICE, volume, 0.0f);
  }
}

void GfMasterVolume::setEnemyVoiceVolume(f32 volume) {
  unknown2c = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_ENE_VO, volume, 0.0f);
  }
}

void GfMasterVolume::setNareVoiceVolume(f32 volume) {
  unknown30 = volume;
  if (GfSound::get() != nullptr) {
    GfSound::get()->setCategoryVolume(unknown00, CATEGORY_NAREVO, volume, 0.0f);
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

u16 GfMasterVolume::getU16Volume(f32 volume) {
  if (volume >= 1.0f) {
    return 0xff;
  }
  return static_cast<u8>(volume * unknown005);
}

void GfSound::setCategory(SoundHandle handle, fw::SoundCategory category) {
  SeParam *param = getSeParam(static_cast<u16>(handle.unknown04));
  if (param != nullptr && fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->setCategory(handle.unknown00, category);
  }
}

void GfSound::setPauseType(SoundHandle handle, bool isPause, f32 fadeTime, u8 type) {
  SeParam *param = getSeParam(static_cast<u16>(handle.unknown04));
  if (param != nullptr) {
    u8 oldBits = param->unknown03;
    u8 newBits;
    if (isPause) {
      newBits = oldBits | type;
    } else {
      newBits = oldBits & ~type;
    }
    param->unknown03 = newBits;
    if ((oldBits == 0) != (newBits == 0) && fw::SoundManager::get() != nullptr) {
      fw::SoundManager::get()->pause(handle.unknown00, isPause, fadeTime);
    }
  }
}

void GfSound::deAllocateSeParam(u16 id) {
  if (id != INVALID_UNKNOWN_65535) {
    unknown2e20.unknown011(id);
  }
}

u16 GfSound::allocateSeParam() {
  u32 index;
  SeParam *param = new (unknown2e20.unknown003(&index)) SeParam;
  if (param == nullptr) {
    return INVALID_UNKNOWN_65535;
  }
  return index;
}

GfSound::SeParam *GfSound::getSeParam(u16 id) {
  if (id == 0xffff) {
    return nullptr;
  }
  return &unknown2e20.unknown007[id];
}

} // namespace gf

template class ml::fixed_size_alloc_inside<gf::GfSound::SeParam, 384>;

template mm::mtl::PtrSingleton<gf::GfSound>::~PtrSingleton();
