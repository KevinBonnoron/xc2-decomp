#include "gf/menu/object/gf_menu_obj_drop_item.h"

#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_util.h"

namespace gf {

// Inferred role: call id of the drop item object; original name unknown.
constexpr u32 unknown001 = 0x2b;

// Inferred role: names and fit margin of the objects the item text of each drop type is fitted to; original type name unknown.
struct unknown002 {
  const char *unknown00; // Inferred role: item text; original member name unknown.
  const char *unknown08; // Inferred role: item text background; original member name unknown.
  int unknown10;         // Inferred role: horizontal margin of the fit; original member name unknown.
};

// Inferred role: fit parameters of each drop type (gold, heal, get, sell); original name unknown.
static const unknown002 unknown003[4] = {
    {"TXT_item_gold", "IMG_item_gold_bg", 0x28},
    {"TXT_item_heal", "IMG_item_heal_bg", 0x10},
    {"TXT_item_get", "IMG_item_get_bg", 0x20},
    {"TXT_item_sell", "IMG_item_sell_bg", 0x10},
};

GfMenuObjDropItem::GfMenuObjDropItem(u32 handle) : GfMenuObject(handle) {}

GfMenuObjDropItem::~GfMenuObjDropItem() { GfMenuManyObjects::destroy<DropItemInfo>(GfMenuManyObjects::unknown001_3); }

void GfMenuObjDropItem::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDropItem::update() { GfMenuObject::update(); }

void GfMenuObjDropItem::removeObject(ui::UIObjectAcc acc) {
  GfMenuManyObjects::remove<DropItemInfo>(GfMenuManyObjects::unknown001_3, acc.unknown10);
  acc.setDisp(false);
  acc.setTerm();
}

void GfMenuObjDropItem::setupPlugin(u32 handle, u32 type) {
  if (type < 4) {
    u32 text = ui::UIUtil::searchChild(handle, unknown003[type].unknown00);
    if (ui::UIUtil::isValid(text)) {
      u32 background = ui::UIUtil::searchChild(handle, unknown003[type].unknown08);
      if (ui::UIUtil::isValid(background)) {
        GfMenuObjUtil::FitOption option;
        option.unknown04.x = -20;
        GfMenuObjUtil::createFitPlugin(background, text, unknown003[type].unknown10, 0, option);
      }
    }
  }
}

void GfMenuObjDropItem::close(u32 handle) {
  ui::UIObjectAcc root(getAttachedObject(unknown001));
  if (root.isValid() && !root.isTerm()) {
    ui::UIObjectAcc acc(handle);
    if (acc.isValid() && acc.isDuplicate()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_34;
      event.unknown08_u16 = acc.getDuplicateIndex();
      sendEvent(root.unknown10, event, 0.0f);
    }
  }
}

void GfMenuObjDropItem::closeAll() {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      GfMenuManyObjects::closeAll<DropItemInfo>(GfMenuManyObjects::unknown001_3, close);
    }
  }
}

} // namespace gf

template void gf::GfMenuManyObjects::remove<gf::GfMenuObjDropItem::DropItemInfo>(u32, u32);
template void mm::mtl::Queue<gf::GfMenuObjDropItem::DropItemInfo>::push_back(const gf::GfMenuObjDropItem::DropItemInfo &);
template void mm::mtl::Queue<gf::GfMenuObjDropItem::DropItemInfo>::expand(size_t, size_t);
