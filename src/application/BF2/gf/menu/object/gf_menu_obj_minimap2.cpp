#include "gf/menu/object/gf_menu_obj_minimap2.h"

#include "gf/menu/gf_menu_flag.h"
#include "gf/menu/gf_menu_map_info.h"
#include "gf/menu/gf_menu_types.h"
#include "mm_math/mm_pnt.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x80;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x100;

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

} // namespace gf
