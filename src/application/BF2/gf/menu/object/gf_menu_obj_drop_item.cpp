#include "gf/menu/object/gf_menu_obj_drop_item.h"

#include "gf/data/gf_data_item.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
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

void GfMenuObjDropItem::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
    attachExternalCall(unknown001, main);
// __LINE__ must be 94 as in the original file: it is the line argument of operator new.
#line 94
    ListListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
  }
  ui::UIObjectAcc(unknown18).setTerm();
  GfMenuObject::initialize();
  GfMenuManyObjects::unknown002<DropItemInfo>(GfMenuManyObjects::unknown001_3, 64);
}

void GfMenuObjDropItem::removeObject(ui::UIObjectAcc acc) {
  GfMenuManyObjects::remove<DropItemInfo>(GfMenuManyObjects::unknown001_3, acc.unknown10);
  acc.setDisp(false);
  acc.setTerm();
}

void GfMenuObjDropItem::setupScreen(u32 handle, int type, int number, int item) {
  switch (type) {
  case 0:
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_gold", true);
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_heal", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_get", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_sell", false);
    {
      u32 text = ui::UIUtil::searchChild(handle, "TXT_item_gold");
      if (ui::UIUtil::isValid(text)) {
        GfMenuObjUtil::createNumberPlugin(text, number);
      }
    }
    break;
  case 1:
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_gold", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_heal", true);
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_get", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_sell", false);
    {
      u32 text = ui::UIUtil::searchChild(handle, "TXT_item_heal");
      if (ui::UIUtil::isValid(text)) {
        GfMenuObjUtil::createNumberPlugin(text, number);
      }
    }
    break;
  case 2: {
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_gold", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_heal", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_get", true);
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_sell", false);
    GfMenuObjUtil::setChildText(handle, "TXT_item_get", number);
    MenuItemInfo info;
    info.unknown00 = GfDataItem::getItemType(item);
    info.unknown04 = item;
    ui::UIObjectAcc acc(handle);
    GfMenuItemAdapter::create(acc.searchChild("IMG_item_get_icon"), 2, info, false);
    break;
  }
  case 3: {
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_gold", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_heal", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_get", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_item_sell", true);
    GfMenuObjUtil::setChildText(handle, "TXT_item_sell_name", number);
    u32 price = ui::UIUtil::searchChild(handle, "TXT_item_sell_price");
    if (ui::UIUtil::isValid(price)) {
      GfMenuObjUtil::createNumberPlugin(price, item);
    }
    break;
  }
  }
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

void GfMenuObjDropItem::ListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case 0x21: {
    ui::UIObjectAcc item(acc.searchDuplicatedChild("LAY_item_root", event.unknown14_u16));
    if (item.isValid()) {
      item.setDisp(true);
      item.setDispChild(true, "LAY_item");
      setupScreen(item.unknown10, event.unknown08, event.unknown0c, event.unknown10);
      GfMenuObjUtil::CtrlParam ctrl;
      ctrl.unknown08 = 0x10000000;
      ctrl.unknown50 = "getitem";
      ctrl.unknown58 = "fadein";
      ctrl.unknown04 = (item.getDuplicateIndex() << 16) | 0x200;
      int id = GfMenuObjUtil::startCtrl(item.unknown10, ctrl, nullptr);
      if (id == -1) {
        removeObject(item);
      } else {
        hookCtrlEvent(acc.unknown10, id);
      }
    }
    break;
  }
  case 0x22: {
    ui::UIObjectAcc item(acc.searchDuplicatedChild("LAY_item_root", event.unknown08_u16));
    if (item.isValid()) {
      removeObject(item);
    }
    break;
  }
  case 3: {
    u32 param = event.unknown08;
    if (param == 0) {
      break;
    }
    ui::UIObjectAcc item(acc.searchDuplicatedChild("LAY_item_root", param >> 16));
    if ((param & 0xff00) == 0x200 && item.isValid()) {
      removeObject(item);
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template void gf::GfMenuManyObjects::remove<gf::GfMenuObjDropItem::DropItemInfo>(u32, u32);
template void mm::mtl::Queue<gf::GfMenuObjDropItem::DropItemInfo>::push_back(const gf::GfMenuObjDropItem::DropItemInfo &);
template void mm::mtl::Queue<gf::GfMenuObjDropItem::DropItemInfo>::expand(size_t, size_t);
