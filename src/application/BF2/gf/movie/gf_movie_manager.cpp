#include "gf/movie/gf_movie_manager.h"

#include "framework/movie/movie_manager.h"
#include "gf/gf_allocator.h"
#include "gf/menu/object/gf_menu_obj_movie_layer.h"
#include "ui/object/ui_screen_object.h"

namespace gf {

GfMovieManager::GfMovieManager() {}

void GfMovieManager::build(const GfSetupParam &) {
  // __LINE__ must be 31 as in the original file: its value changes the instruction order.
#line 31
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfMovieManager();
}

void GfMovieManager::destroy() {
  GfMovieManager *movieManager = get();
  movieManager->close();
  delete movieManager;
}

void GfMovieManager::close() { fw::MovieManager::get()->close(); }

void GfMovieManager::open(mm::mtl::IAllocator *allocator, u32 layer) { fw::MovieManager::get()->open(allocator, layer); }

void GfMovieManager::open(mm::mtl::IAllocator *allocator) {
  u32 layer = GfMenuObjMovieLayer::createMovieLayer(0x500, 0x2d0, ui::UIScreenObject::OnMemoryInfo{0, 3});
  if (layer != 0) {
    fw::MovieManager::get()->open(allocator, layer);
  }
}

void GfMovieManager::open(mm::mtl::IAllocator *allocator, int width, int height) {
  u32 layer = GfMenuObjMovieLayer::createMovieLayer(width, height, ui::UIScreenObject::OnMemoryInfo{1, 3});
  if (layer != 0) {
    fw::MovieManager::get()->open(allocator, width, height, layer);
  }
}

bool GfMovieManager::set_file(const char *path) { return fw::MovieManager::get()->set_file(path); }

f32 GfMovieManager::get_length() { return fw::MovieManager::get()->get_length(); }

f32 GfMovieManager::pos() { return fw::MovieManager::get()->pos(); }

void GfMovieManager::play() { fw::MovieManager::get()->play(); }

void GfMovieManager::pause() { fw::MovieManager::get()->pause(); }

void GfMovieManager::stop() { fw::MovieManager::get()->stop(); }

bool GfMovieManager::isstandby() { return fw::MovieManager::get()->isstandby(); }

bool GfMovieManager::ispause() { return fw::MovieManager::get()->ispause(); }

bool GfMovieManager::isplaying() { return fw::MovieManager::get()->isplaying(); }

} // namespace gf
