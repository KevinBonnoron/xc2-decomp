#include "gf/menu/gf_menu_sound_manager.h"

#include "bdat.h"
#include "gf/data/gf_bdat_bgm.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_manager.h"
#include "mm_mtl/fixstr.h"

namespace gf {

GfMenuSoundManager::GfMenuSoundManager(const GfSetupParam &param) : unknown08(false), unknown78(unknown019) { initialize(param); }

void GfMenuSoundManager::initialize(const GfSetupParam &) {
  unknown08 = true;
  if (GfSound::get() != nullptr) {
    unknown78 = GfSound::get()->createCategoryHandle();
  }
  unknown10.clear();
}

GfMenuSoundManager::~GfMenuSoundManager() {}

void GfMenuSoundManager::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfMenuSoundManager(param); }

void GfMenuSoundManager::destroy() {
  GfMenuSoundManager *manager = get();
  manager->finalize();
  delete manager;
}

void GfMenuSoundManager::finalize() {
  unknown08 = false;
  if (GfSound::get() != nullptr) {
    GfSound::get()->releaseCategoryHandle(unknown78);
  }
}

bool GfMenuSoundManager::isInitialized() {
  GfMenuSoundManager *manager = get();
  if (manager != nullptr) {
    return manager->unknown08;
  }
  return false;
}

void GfMenuSoundManager::postUpdate(const fw::UpdateInfo &info) {
  GfMenuSoundManager *manager = get();
  if (manager == nullptr) {
    return;
  }
  GfSound *sound = GfSound::get();
  if (sound == nullptr) {
    return;
  }
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SOUND_BGM);
  for (unknown001 *it = manager->unknown10.begin(); it != manager->unknown10.end();) {
    f32 time = Bdat::getVal(bdat, "time", it->unknown08).valueF32;
    f32 playTime = 0.0f;
    sound->getPlayTime(it->unknown00, playTime);
    if (playTime > time || !sound->isPlaying(it->unknown00)) {
      u32 id = it->unknown08;
      it = manager->unknown10.erase(it);
      if (manager->unknown10.size() == 0 && !manager->isSpecOutJingle(id) && !GfMenuManager::isOpenFullScreen()) {
        fadeFieldBgm(1.0f, 1.0f);
      }
    } else {
      it++;
    }
  }
}

bool GfMenuSoundManager::isSpecInJingle(u32 id) {
  switch (id) {
  case 0xc:
  case 0xd:
  case 0x12:
    return true;
  default:
    return false;
  }
}

void GfMenuSoundManager::fadeInFieldBgm(f32 time) { fadeFieldBgm(time, 1.0f); }

SoundHandle GfMenuSoundManager::playJingle(u32 id) {
  GfMenuSoundManager *manager = get();
  if (manager != nullptr && manager->unknown10.size() != manager->unknown10.capacity()) {
    GfSound *sound = GfSound::get();
    if (sound != nullptr) {
      u16 resource = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_SOUND_BGM), "resource", id).valueU16;
      if (resource != 0) {
        const char *name = GfBdatBgm::get()->getBgmListfilename(resource);
        if (name == nullptr || name[0] == '\0') {
          return SoundHandle(0);
        }
        mm::mtl::FixStr<128> path;
        path.format("stream/bgm/%s", name);
        SoundHandle handle = sound->playVoice(path.c_str(), 1.0f, false, CATEGORY_SYSTEM);
        if (manager->unknown10.size() == 0 && !manager->isSpecInJingle(id) && !GfMenuManager::isOpenFullScreen()) {
          fadeFieldBgm(0.5f, 0.5f);
        }
        unknown001 jingle;
        jingle.unknown00 = handle;
        jingle.unknown08 = id;
        manager->unknown10.push_back(jingle);
        return handle;
      }
    }
  }
  return SoundHandle(0);
}

bool GfMenuSoundManager::isSpecOutJingle(u32 id) {
  switch (id) {
  case 0xc:
  case 0xd:
  case 0x12:
    return true;
  default:
    return false;
  }
}

void GfMenuSoundManager::fadeFieldBgm(f32 time, f32 volume) {
  GfMenuSoundManager *manager = get();
  if (manager == nullptr) {
    return;
  }
  GfSound *sound = GfSound::get();
  if (sound == nullptr) {
    return;
  }
  sound->setCategoryVolume(manager->unknown78, CATEGORY_BGM, volume, time);
  sound->setCategoryVolume(manager->unknown78, CATEGORY_ENV, volume, time);
  sound->setCategoryVolume(manager->unknown78, CATEGORY_WEATHER, volume, time);
}

void GfMenuSoundManager::fadeOutFieldBgm(f32 time) { fadeFieldBgm(time, 0.0f); }

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfMenuSoundManager>::~PtrSingleton();
