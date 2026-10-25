#include "gf/menu/object/gf_menu_obj_movie_layer.h"

#include "gf/movie/gf_movie_manager.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"
#include "ui/object/ui_layout_object.h"
#include "ui/ui_object.h"
#include "ui/ui_util.h"

namespace gf {

constexpr u32 CALL_MOVIE_LAYER = 126;

u32 GfMenuObjMovieLayer::m_CreatedCount;

GfMenuObjMovieLayer::GfMenuObjMovieLayer(u32 handle) : GfMenuObject(handle) {}

GfMenuObjMovieLayer::~GfMenuObjMovieLayer() { ; }

void GfMenuObjMovieLayer::initialize() {
  attachExternalCall(CALL_MOVIE_LAYER, unknown18);
  GfMenuObject::initialize();
}

void GfMenuObjMovieLayer::finalize() {
  GfMovieManager::get()->close();
  GfMenuObject::finalize();
}

void GfMenuObjMovieLayer::update() { GfMenuObject::update(); }

u32 GfMenuObjMovieLayer::getMovieLayerObject() { return getAttachedObject(CALL_MOVIE_LAYER); }

u32 GfMenuObjMovieLayer::createMovieLayer(u32 width, u32 height, const ui::UIScreenObject::OnMemoryInfo &info) {
  if (getAttachedObject(CALL_MOVIE_LAYER) == 0) {
    return 0;
  }

  ui::UIObject *object = ui::UIUtil::getObject(getAttachedObject(CALL_MOVIE_LAYER));
  ui::UILayoutObject *layout = nullptr;
  if (object != nullptr) {
    layout = mm::mtl::dynamicCast<ui::UILayoutObject>(object);
  }
  mm::mtl::FixStr<32> name;
  name.format("SCR_movie%02d", m_CreatedCount % 100);
  m_CreatedCount++;
  ui::UIObject *created = ui::UIScreenObject::createOnMemory(layout, width, height, name, ui::UIUtil::getProgAllocator(), info);
  u32 handle = 0;
  if (created != nullptr) {
    ui::UIObject::importDisplayInfo(created->unknown50, created->unknownc8);
    handle = ui::UIUtil::registObject(created);
    if (handle != 0) {
      layout->addChild(handle, created);
      created->unknown98.set(4);
    }
  }

  return handle;
}

} // namespace gf
