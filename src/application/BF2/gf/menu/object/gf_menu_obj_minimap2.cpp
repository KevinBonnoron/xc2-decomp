#include "gf/menu/object/gf_menu_obj_minimap2.h"

#include "gf/menu/gf_menu_flag.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_map_info.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec2.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x80;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x100;
// Inferred role: preset control and map size mode when the map is set up; original name unknown.
// Decision 2026-11-14 #20: the pair is stored as a unit (str wzr, [x19, #0xc]; str x8, [x19, #0x10] at 0x710049ed74), not merged with 0x0c, which is the evidence of a sub-object (as in
// GfMenuObjArtsPalette and the compass).
static const GfMenuObjMinimap2::MainListener::unknown003 unknown004 = {-1, 0};

GfMenuObjMinimap2::GfMenuObjMinimap2(u32 handle) : GfMenuObject(handle), unknown24(false), unknown240(false) {}

GfMenuObjMinimap2::~GfMenuObjMinimap2() {}

void GfMenuObjMinimap2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMinimap2::enable() { GfMenuFlag::set1(0x1f, 0); }

void GfMenuObjMinimap2::disable() { GfMenuFlag::set1(0x1f, 1); }

void GfMenuObjMinimap2::changeMap() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown00 = unknown002;
    GfMenuObject::sendEvent(acc.searchChild("LAY_map"), event, 0.0f);
  }
}

void GfMenuObjMinimap2::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjMinimap2::open() { unknown143(unknown001, GfMenuTypes::unknown003_33); }

void GfMenuObjMinimap2::dispOffIconTable(u32 index, mm::mtl::FixedVector<u32, 128> &table) {
  if (index < table.size()) {
    ui::UIObjectAcc acc(table[index]);
    if (acc.isValid()) {
      acc.setDisp(false);
    }
  }
}

void GfMenuObjMinimap2::setupIconTable(u32 index, mm::mtl::FixedVector<u32, 128> &table, u32 image, mm::Pnt<s16> pos) {
  if (index < table.size()) {
    ui::UIObjectAcc acc(table[index]);
    if (acc.isValid()) {
      acc.setDisp(true);
      acc.setSuspend(false);
      acc.setPosCenter(pos);
      acc.setImageIndex(image);
    }
  }
}

void GfMenuObjMinimap2::destroyIconTable(mm::mtl::FixedVector<u32, 128> &table) {
  for (u32 *it = table.begin(); it != table.end(); it++) {
    ui::UIObjectAcc acc(*it);
    if (acc.isValid() && !acc.isTerm()) {
      acc.setTerm();
    }
  }
  table.clear();
}

void GfMenuObjMinimap2::createIconTable(ui::UIObjectAcc &acc, mm::mtl::FixedVector<u32, 128> &table) {
  ui::UIObjectAcc icons(acc.searchChild("LAY_icon"));
  ui::UIObjectAcc mask(acc.searchChild("IMG_map_mask"));
  for (int i = 0; i < 128; i++) {
    u32 handle = icons.duplicateChild("IMG_icon");
    ui::UIObjectAcc icon(handle);
    if (icon.isValid()) {
      icon.setDisp(false);
      icon.setSuspend(true);
      icon.setIgnoreSize(true);
      icon.setMaskObject(mask.unknown10);
      table.push_back(handle);
    }
  }
}

bool GfMenuObjMinimap2::refreshMapPosition() {
  ui::UIObjectAcc map(unknown18, "LAY_map_image");
  mm::Pnt<s16> offset;
  if (!GfMenuMapInfo::getMapSegImageOffs(offset)) {
    return false;
  }
  offset.x = -offset.x;
  offset.y = -offset.y;
  mm::Pnt<s16> center;
  map.getDisplayOffsCenter(center);
  if (unknown240 == 1) {
    offset.x = offset.x * 2;
    offset.y = offset.y * 2;
  }
  map.setPosCenter(mm::Pnt<s16>(offset.x + center.x, offset.y + center.y));
  return true;
}

void GfMenuObjMinimap2::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    acc.setDisp(false);
    unknown0c = 0;
    unknown10 = unknown004;
    GfMenuObject::disableInput(acc.unknown10);
    GfMenuObjMinimap2::createIconTable(acc, unknown20->unknown28);
    acc.getLayoutRect("mini_map", unknown20->unknown230);
    ui::UIObjectAcc dummy(acc.unknown10, "IMG_dummy");
    dummy.getRect(unknown20->unknown238, 0);
    break;
  }
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
    }
    break;
  case 0x21:
    if (GfMenuFlag::get1(0x1f) == 0 && unknown0c == 0) {
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown00 = 6;
      param.unknown04 = 0;
      param.unknown0d = true;
      param.unknown08 = unknown10.unknown00;
      param.unknown10 = 1;
      unknown10.unknown00 = GfMenuObjUtil::startPresetCtrl(handle, param);
      unknown0c = 1;
    }
    break;
  case 0x22:
    if (unknown0c == 1) {
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown10 = 0;
      param.unknown00 = 6;
      param.unknown04 = 1;
      param.unknown0d = true;
      param.unknown08 = unknown10.unknown00;
      unknown10.unknown00 = GfMenuObjUtil::startPresetCtrl(handle, param);
      unknown0c = 0;
      GfMenuObject::disableInput(acc.unknown10);
    }
    break;
  case 8:
    if (event.unknown0c == 9 && GfMenuFlag::get1(0x20) == 0 && GfMenuManager::isFieldHudInputEnable()) {
      int mode = unknown10.unknown04;
      if (mode == 0) {
        acc.setDispChild(false, "IMG_map_frame");
        acc.setDispChild(false, "IMG_map_base");
        acc.setDispChild(false, "IMG_map_mask");
        acc.setDispChild(false, "LAY_icon_base");
        ui::UIObjectAcc center(acc.unknown10, "IMG_map_image_center");
        GfMenuObjUtil::setDockPos(center.unknown10, acc.searchChild("IMG_map_center"), 0, true);
        acc.getLayoutRect("mini_map2", unknown20->unknown230);
        mode = 1;
      } else if (mode == 1) {
        acc.setDispChild(true, "IMG_map_frame");
        acc.setDispChild(true, "IMG_map_base");
        acc.setDispChild(true, "IMG_map_mask");
        acc.setDispChild(false, "LAY_map");
        mode = 2;
      } else if (mode == 2) {
        acc.setDispChild(true, "LAY_map");
        acc.setDispChild(false, "LAY_icon_base");
        ui::UIObjectAcc center(acc.unknown10, "IMG_map_image_center");
        GfMenuObjUtil::setDockPos(center.unknown10, acc.searchChild("IMG_map_frame"), 0, true);
        acc.getLayoutRect("mini_map", unknown20->unknown230);
        mode = 0;
      }
      unknown10.unknown04 = mode;
      unknown20->unknown240 = mode;
      ui::UIObjectAcc map(acc.unknown10, "LAY_map_image");
      if (mode == 1) {
        mm::Vec2 scale(2.0f, 2.0f);
        map.setScale(scale);
      } else {
        mm::Vec2 scale(1.0f, 1.0f);
        map.setScale(scale);
      }
      unknown20->refreshMapPosition();
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
