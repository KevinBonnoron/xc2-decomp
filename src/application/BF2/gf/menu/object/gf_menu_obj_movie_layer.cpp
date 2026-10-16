#include "gf/menu/object/gf_menu_obj_movie_layer.h"

#include "gf/movie/gf_movie_manager.h"

namespace gf {

constexpr u32 CALL_MOVIE_LAYER = 126;

GfMenuObjMovieLayer::GfMenuObjMovieLayer(u32 handle) : GfMenuObject(handle) {}

GfMenuObjMovieLayer::~GfMenuObjMovieLayer() { ; }

void GfMenuObjMovieLayer::initialize() {
  attachExternalCall(CALL_MOVIE_LAYER, handle);
  GfMenuObject::initialize();
}

void GfMenuObjMovieLayer::finalize() {
  GfMovieManager::get()->close();
  GfMenuObject::finalize();
}

void GfMenuObjMovieLayer::update() { GfMenuObject::update(); }

u32 GfMenuObjMovieLayer::getMovieLayerObject() { return getAttachedObject(CALL_MOVIE_LAYER); }

} // namespace gf
