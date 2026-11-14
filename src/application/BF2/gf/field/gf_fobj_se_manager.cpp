#include "gf/field/gf_fobj_se_manager.h"

#include "framework/sound/sound_manager.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/vector.h" // IWYU pragma: keep

namespace gf {

GfFobjSeManager::GfFobjSeManager(const CreateInfo *info) : unknown08(nullptr) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfFobjSeManager::create(const CreateInfo &info) {
  dispose();
  unknown00 = info;
  unknown08 = fw::SoundManager::get()->findPack("se_fld_allmap", nullptr);
  if (unknown08 == nullptr) {
    dispose();
    return;
  }
  unknown10.setAllocator(getAllocator(ALLOCATOR_UNKNOWN_0));
  unknown10.reserve(info.unknown04);
  unknown38.setAllocator(getAllocator(ALLOCATOR_UNKNOWN_0));
}

void GfFobjSeManager::dispose() {
  if (!unknown10.empty()) {
    if (fw::SoundManager::get() != nullptr) {
      for (SeInfo &info : unknown10) {
        fw::SoundManager::get()->stopSe(info.unknown04, 0.5f);
      }
    }
    unknown10.destroy();
  }
  unknown00 = CreateInfo();
}

void GfFobjSeManager::update(f32 deltaTime) {
  if (unknown00.unknown04 == 0) {
    return;
  }

  for (SeInfo *it = unknown10.begin(); it != unknown10.end(); ++it) {
    if (!fw::SoundManager::get()->isPlaying(it->unknown04)) {
      it = unknown10.erase(it);
      --it;
    }
  }
  for (mm::mtl::Map<u16, f32>::iterator it = unknown38.begin(); it != unknown38.end(); ++it) {
    it->second += deltaTime;
  }
}

} // namespace gf

template gf::GfFobjSeManager::SeInfo *mm::mtl::Vector<gf::GfFobjSeManager::SeInfo>::erase(gf::GfFobjSeManager::SeInfo *);
template void mm::mtl::Vector<gf::GfFobjSeManager::SeInfo>::expand(size_t, size_t);
