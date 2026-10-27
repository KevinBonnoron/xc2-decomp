#include "gf/game/gf_game_arts_movie.h"

#include "gf/asset/gf_asset_def.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/asset/gf_slot.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/gf_allocator.h"
#include "gf/movie/gf_movie_manager.h"
#include "mm_mtl/fixstr.h"

namespace gf {

constexpr size_t MOVIE_SLOT_SIZE = 0x500000;

GfArtsMovie::GfArtsMovie() : unknown10(INVALID_SLOT_HANDLE), unknown18(nullptr), unknown20(0), m_state(0) { unknown28.clear(); }

GfArtsMovie::~GfArtsMovie() {}

void GfArtsMovie::startSetup(const char *name) {
  unknown10 = GfAssetManager::allocateFromAssetTypeSlot(ASSET_TYPE_TEMPORARY, MOVIE_SLOT_SIZE);
  if (unknown10 != INVALID_SLOT_HANDLE) {
    size_t size;
    {
      void *buffer;
      GfAssetManager::getSlotInfo(unknown18, buffer, size, unknown10);
    }
    mm::mtl::FixStr<128> path;
    path.format("/stream/movie/%s.webm", name);
    GfMovieManager::get()->open(unknown18);
    GfMovieManager::get()->set_file(path.c_str());
    GfMovieManager::get()->play();
    m_state = 1;
    unknown28.bind(this, &GfArtsMovie::updateForSetup);
  }
}

void GfArtsMovie::updateForSetup(const fw::UpdateInfo &) {
  if (GfMovieManager::get()->isstandby() && !GfMovieManager::get()->isplaying()) {
    return;
  }
  m_state = 2;
  unknown28.bind(this, &GfArtsMovie::updateForPlay);
}

void GfArtsMovie::updateForPlay(const fw::UpdateInfo &) {
  if (!GfMovieManager::get()->isplaying()) {
    unknown28.bind(this, &GfArtsMovie::updateForMemorySafe);
  }
}

void GfArtsMovie::updateForMemorySafe(const fw::UpdateInfo &) {
  GfMovieManager::get()->close();
  GfAssetManager::releaseSlotHandle(unknown10);
  unknown10 = INVALID_SLOT_HANDLE;
  unknown18 = nullptr;
  m_state = 3;
  unknown28.clear();
}

void GfArtsMovie::update(const fw::UpdateInfo &info) {
  if (unknown28.isValid()) {
    unknown28(info);
  }
}

GfArtsMovie *GfArtsMovie::createSiren() {
  if (!GfPlayFactory::createArtsMovie("bf99000001")) {
    return nullptr;
  }
  GfArtsMovie *artsMovie = get();
  if (artsMovie == nullptr) {
#line 127
    artsMovie = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfArtsMovie();
  }
  return artsMovie;
}

void GfArtsMovie::destroy() {
  GfArtsMovie *artsMovie = get();
  if (artsMovie != nullptr) {
    delete artsMovie;
  }
}

s32 GfArtsMovie::getState() const { return m_state; }

void GfArtsMovie::gevPause(u32, u32) {}

} // namespace gf
