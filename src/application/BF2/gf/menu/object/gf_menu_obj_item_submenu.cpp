#include "gf/menu/object/gf_menu_obj_item_submenu.h"

#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x6e;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;

GfMenuObjItemSubmenu::GfMenuObjItemSubmenu(u32 handle) : GfMenuObject(handle), unknown2c(0) {}

GfMenuObjItemSubmenu::~GfMenuObjItemSubmenu() { ; }

void GfMenuObjItemSubmenu::finalize() { GfMenuObject::finalize(); }

void GfMenuObjItemSubmenu::update() { GfMenuObject::update(); }

void GfMenuObjItemSubmenu::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjItemSubmenu::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::unknown002(handle);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjItemSubmenu::setFadeOut(u32 handle, bool unknown) {
  GfMenuObjUtil::PresetCtrlParam param;
  param.unknown00 = 6;
  param.unknown04 = 1;
  param.unknown10 = 1;
  if (unknown) {
    param.unknown0c = true;
  }
  int ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjItemSubmenu::returnItemSubMenu() { GF_MENU_REQUEST_EVENT(unknown001, unknown002); }

} // namespace gf
