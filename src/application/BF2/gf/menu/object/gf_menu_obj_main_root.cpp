#include "gf/menu/object/gf_menu_obj_main_root.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

constexpr u32 SCREEN_MAIN_ROOT = 2;

GfMenuObjMainRoot::GfMenuObjMainRoot(u32 handle) : GfMenuObject(handle) {}

GfMenuObjMainRoot::~GfMenuObjMainRoot() { ; }

void GfMenuObjMainRoot::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(GfMenuFullScreen::getScreenLayerID(SCREEN_MAIN_ROOT), layerParam);
}

void GfMenuObjMainRoot::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (!main.isValid()) {
    return;
  }
// __LINE__ must be 54 as in the original file: it is the line argument of operator new.
#line 54
  MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.handle, listener);
  if (listener != nullptr) {
    listener->release();
  }
  GfMenuTypes::Param param;
  u32 menu = getFSLayerParam(unknown20, param) ? param.get<OpenParam>().unknown00 : 1;
  u16 menuLayer = getMenuLayerID(menu);
  changeFSSubLayer(main.handle, 1, menuLayer, true);
  main.setDispChild(true, "IMG_bg_black");
  setFSShadowLayer(unknown20, true);
  disableInput(main.handle);
  GfMenuObject::initialize();
}

void GfMenuObjMainRoot::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMainRoot::update() { GfMenuObject::update(); }

void GfMenuObjMainRoot::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.type) {
  case 1:
    break;
  case 8:
    if (event.param1 == 3) {
      closeFSLayer(acc.handle, true, true);
    }
    break;
  case 0x43:
    closeFSLayer(acc.handle, true, true);
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
  }
}

} // namespace gf
