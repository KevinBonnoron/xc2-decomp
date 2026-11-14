#include "gf/menu/object/gf_menu_obj_item_list2.h"

#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_item.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/gf_menu_flag.h"
#include "gf/menu/gf_menu_item_util.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_sort.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: item type of each filter, 0 for every type; original name unknown.
static const ItemType::Type unknown001[13] = {
    ItemType::ITEM_TYPE_UNKNOWN_0,
    ItemType::ITEM_TYPE_UNKNOWN_12,
    ItemType::ITEM_TYPE_UNKNOWN_7,
    ItemType::ITEM_TYPE_UNKNOWN_11,
    ItemType::ITEM_TYPE_UNKNOWN_10,
    ItemType::ITEM_TYPE_UNKNOWN_14,
    ItemType::ITEM_TYPE_UNKNOWN_9,
    ItemType::ITEM_TYPE_UNKNOWN_3,
    ItemType::ITEM_TYPE_UNKNOWN_2,
    ItemType::ITEM_TYPE_UNKNOWN_1,
    ItemType::ITEM_TYPE_UNKNOWN_6,
    ItemType::ITEM_TYPE_UNKNOWN_5,
    ItemType::ITEM_TYPE_UNKNOWN_8,
};

// Inferred role: sort type of each filter; original name unknown.
static const u32 unknown002[13] = {11, 3, 4, 5, 6, 7, 8, 9, 2, 10, 11, 12, 13};

GfMenuObjItemList2::GfMenuObjItemList2(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown98(0), unknown9c(0), unknowna0(true) {}

GfMenuObjItemList2::~GfMenuObjItemList2() {
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
}

void GfMenuObjItemList2::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 162 as in the original file: it is the line argument of operator new.
#line 162
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(0x6f, main);
  u32 window = acc.searchChild("LAY_mainwindow");
// __LINE__ must be 168 as in the original file: it is the line argument of operator new.
#line 168
  ItemListListener *itemListListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ItemListListener(this);
  itemListListener->addRef();
  ui::UIEventManager::get()->registObjectListener(window, itemListListener);
  if (itemListListener != nullptr) {
    itemListListener->release();
  }
  u32 filterHandle = acc.searchChild("LAY_filter");
// __LINE__ must be 172 as in the original file: it is the line argument of operator new.
#line 172
  FilterListener *filterListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) FilterListener(this);
  filterListener->addRef();
  ui::UIEventManager::get()->registObjectListener(filterHandle, filterListener);
  if (filterListener != nullptr) {
    filterListener->release();
  }
  unknown28 = GfMenuItemList::create();
  ui::UISelectObjList::CreateParam createParam;
  createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
  unknown30 = ui::UISelectObjList::create(createParam);
  {
    ui::UIObjectAcc filter(acc.unknown10, "LAY_filter");
    mm::mtl::FixStr<32> name;
    unknown38.clear();
    for (u32 i = 0; i < 13; i++) {
      ItemType::Type type = unknown001[i];
      if (i == 0 || GfMenuFlag::get1(type + 0x3a) == 1) {
        u32 number = 0;
        name.format("IMG_ficon@%02d", unknown38.size() + 1);
        ui::UIObjectAcc icon(filter.unknown10, name.c_str());
        unknown38.push_back(i);
        if (i == 0) {
          number = 0xe;
        } else {
          GfMenuItemUtil::getIconNumber(type, 0, number, true);
        }
        icon.setImageIndex(number);
        icon.setDisp(true);
      }
    }
    u32 count = filter.countChild("LAY_icon@%02d", 1);
    for (u32 i = unknown38.size(); i < count; i++) {
      name.format("IMG_ficon@%02d", i + 1);
      ui::UIObjectAcc icon(filter.unknown10, name.c_str());
      icon.setDisp(false);
    }
    mm::Rect<s16> rect;
    filter.getLayoutRect("all_item", rect);
    mm::Rect<s16> range;
    filter.getLayoutRect("all_item_range", range);
    GfMenuObjUtil::placeObjectH(filter.unknown10, "LAY_icon@%02d", unknown38.size(), mm::Pnt<s16>(rect.x + rect.width / 2, rect.y + rect.height / 2), range.x - rect.x);
  }
  GfMenuObject::initialize();
}

void GfMenuObjItemList2::setupItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *selectList) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < selectList->getSize(); i++) {
    name.format("IMG_itemicon@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 2, list, i, false);
    name.format("TXT_itemname@%02d", i + 1);
    GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 0, list, i, false);
    name.format("LAY_listtag@%02d", i + 1);
    adapter->unknown24 = acc.searchChild(name.c_str());
    name.format("IMG_reaicon@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 7, list, i, false);
    name.format("TXT_pricenum@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 6, list, i, false);
    name.format("TXT_stc_num@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 3, list, i, false);
    name.format("TXT_stc_maxnum@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 4, list, i, false);
  }
  GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(acc.searchChild("TXT_infotxt"), 9, list, -1, false);
  if (adapter != nullptr) {
    adapter->unknown24 = acc.searchChild("LAY_info_text");
  }
  name.format("TXT_getarea@%02d", 1);
  adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 0xb, list, -1, false);
  if (adapter != nullptr) {
    adapter->unknown24 = acc.searchChild("LAY_getinfo");
  }
  adapter->unknown70 = 0;
  name.format("TXT_getarea@%02d", 2);
  adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 0xb, list, -1, false);
  adapter->unknown70 = 1;
  for (u32 i = 0; i < 3; i++) {
    name.format("TXT_iteminfo_pouch_eff@%02d", i + 1);
    adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 0xe, list, -1, false);
    if (adapter != nullptr) {
      adapter->unknown70 = i;
    }
  }
  GfMenuItemAdapter::createFromList(acc.searchChild("TXT_iteminfo_pouch_time"), 0xd, list, -1, false);
}

void GfMenuObjItemList2::updateItemList(GfMenuItemList *list, ui::UISelectObjList *selectList, u32 filter, u32 sort) {
  GfMenuItemList::ItemBoxSetup setup;
  setup.unknown00.unknown08 = selectList->getSize();
  setup.unknown00.unknown10 = true;
  setup.unknown28 = false;
  setup.unknown29 = false;
  if (filter == 0) {
    list->setup(getAllocator(ALLOCATOR_UNKNOWN_0), setup.unknown00);
    for (u32 i = 1; i < 13; i++) {
      setup.unknown14 = unknown001[i];
      list->addListFromBox(setup);
    }
  } else {
    setup.unknown14 = unknown001[filter];
    list->setupFromBox(setup);
  }
  list->sort(1, false);
  list->setIndex(0);
}

void GfMenuObjItemList2::refreshItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *selectList) {
  if (list != nullptr && selectList != nullptr) {
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < selectList->getSize(); i++) {
      MenuItemInfo &info = list->getContents(list->getPageIndex(i));
      name.format("IMG_tagsellect@%02d", i + 1);
      GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), list->getIndex(true) == i);
      name.format("LAY_stock@%02d", i + 1);
      GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), GfMenuItemUtil::canCountStack(info.unknown00));
    }
  }
}

void GfMenuObjItemList2::setupFilter(ui::UIObjectAcc &acc, u32 index) {
  ui::UIStr text;
  getFilterText(index, text);
  ui::UIObjectAcc label(acc.searchChild("TXT_filterlabel"));
  label.setText(text);
}

void GfMenuObjItemList2::refreshFilterIcon() {
  ui::UIObjectAcc filter(unknown18, "LAY_filter");
  mm::mtl::FixStr<32> name;
  if (unknown38.size() != 0) {
    u32 i = 0;
    do {
      u32 selected = unknown98;
      name.format("IMG_ficon@%02d", i + 1);
      ui::UIObjectAcc icon(filter.searchChild(name.c_str()));
      if (i == selected) {
        icon.setMulColor("sys_select");
      } else {
        icon.loadDefColor();
      }
      i++;
    } while (i < unknown38.size());
  }
}

void GfMenuObjItemList2::getFilterText(u32 index, ui::UIStr &text) {
  text.copy(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_FILTER_CATEGORY), GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_ITEM_LIST_FILTER, index + 1)));
}

void GfMenuObjItemList2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjItemList2::update() { GfMenuObject::update(); }

void GfMenuObjItemList2::setFadeOutSub(u32 handle) { GfMenuObjUtil::setCommonFadeOut(handle, 2, 0); }

void GfMenuObjItemList2::sendEvent(u32 handle, u32 type, u32 param, u32 delay) {
  ui::EventData event;
  // Store order from the copy the game inlines in FilterListener::reciveEvent (1.0.0: 0x710047cce4), which matches only with unknown08 last; sendEvent itself matches with
  // either order.
  event.unknown0c = 0;
  event.unknown00 = type;
  event.unknown08 = param;
  ui::UIManager::get()->requestObjectEvent(handle, event, static_cast<f32>(delay) * 0.033333335f);
}

int GfMenuObjItemList2::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjItemList2::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjItemList2::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObjOperationInfo::setGuideText(3, 0);
    setFadeIn(handle);
    break;
  case 2:
    unknown163(handle, GfMenuTypes::unknown003_34, 0);
    break;
  case 3:
    if (event.unknown08 == 1) {
      unknown163(acc.searchChild("LAY_mainwindow"), GfMenuTypes::unknown003_257, 0);
      unknown163(acc.searchChild("LAY_filter"), GfMenuTypes::unknown003_257, 0);
      GfMenuObjMainMenu2::setSystemKeyEnable(true);
      GfMenuObjOperationInfo::add(acc.searchChild("LAY_mainwindow"), 0, 0, 0);
    } else if (event.unknown08 == 2) {
      GfMenuObjOperationInfo::remove(acc.searchChild("LAY_mainwindow"), 0, 0, 0);
      acc.setDisp(false);
      acc.setTerm();
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    if (!unknown20->unknowna0) {
      unknown163(handle, 3, 2);
    } else {
      setFadeOut(handle);
    }
    break;
  case 0x24:
    GfMenuObject::disableInput(acc.searchChild("LAY_mainwindow"));
    setFadeOutSub(handle);
    unknown20->unknowna0 = false;
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjItemList2::ItemListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown20->unknown98 = 0;
    unknown20->unknown30->clear();
    unknown20->unknown30->pickupObject(acc.unknown10, "LAY_listtag@%02d", 1);
    setupItemList(acc, unknown20->unknown28, unknown20->unknown30);
    GfMenuObjUtil::createVScrollBarPlugin(acc.searchChild("IMG_scroll_point"), unknown20->unknown28, "IMG_scroll_line", true);
    updateItemList(unknown20->unknown28, unknown20->unknown30, unknown20->unknown98, unknown0c);
    refreshItemList(acc, unknown20->unknown28, unknown20->unknown30);
    setupFilter(acc, 0);
    GfMenuObjSort::setSortLabelText(GfMenuObjSort::getSortID(unknown002[0], 0), acc.searchChild("TXT_sort_label"));
    unknown164(handle, GfMenuTypes::unknown003_257);
    unknown0c = 0;
    break;
  case 6: {
    u32 index = event.unknown08;
    u32 previous = event.unknown0c;
    if (index != 0xffffffff) {
      unknown20->unknown28->setIndex(index);
      unknown20->unknown28->getContents(index);
      refreshItemList(acc, unknown20->unknown28, unknown20->unknown30);
    }
    if (previous != 0xffffffff && index != previous) {
      GfMenuObjUtil::playSECommonCursor();
    }
    break;
  }
  case 8:
    switch (event.unknown0c) {
    case 2:
      unknown164(handle, GfMenuTypes::unknown003_258);
      unknown163(owner.searchChild("LAY_main"), GfMenuTypes::unknown003_34, 0);
      break;
    case 9: {
      u32 filter = unknown20->unknown38[unknown20->unknown98];
      GfMenuObjSort::open(acc.unknown10, acc.searchChild("TXT_sort_label"), unknown002[filter], unknown0c);
      GfMenuObject::disableInput(handle);
      GfMenuObjOperationInfo::remove(owner.searchChild("LAY_mainwindow"), 0, 0, 0);
      unknown164(owner.searchChild("LAY_filter"), GfMenuTypes::unknown003_258);
      break;
    }
    }
    break;
  case GfMenuTypes::unknown003_257:
    GfMenuObject::setupInputSelectionFromList(handle, *unknown20->unknown28);
    GfMenuObject::enableInput(handle);
    break;
  case GfMenuTypes::unknown003_258:
    GfMenuObject::disableInput(handle);
    break;
  case GfMenuTypes::unknown003_259: {
    u32 filter = unknown20->unknown38[unknown20->unknown98];
    // The original source repeats the statements of setupFilter() here instead of calling it, where event 1 above
    // calls it (bl at 0x710047c314, its only reference): the game holds them at 0x710047c158-0x710047c1cc, and
    // both destructors run before getSortID. With setupFilter(acc, filter) the function is 361 instructions against
    // the game's 389; neither call is inlined (costs 430 and 435 against 412), and a higher inline threshold
    // inlines the constant call of event 1 first, which the game keeps.
    {
      ui::UIStr text;
      getFilterText(filter, text);
      ui::UIObjectAcc label(acc.searchChild("TXT_filterlabel"));
      label.setText(text);
    }
    GfMenuObjSort::setSortLabelText(GfMenuObjSort::getSortID(unknown002[filter], 0), acc.searchChild("TXT_sort_label"));
    unknown0c = 0;
    updateItemList(unknown20->unknown28, unknown20->unknown30, filter, unknown0c);
    unknown20->unknown28->setIndex(0);
    unknown20->unknown28->getSize();
    acc.setDispChild(filter != 4, "LAY_iteminfo_normal");
    acc.setDispChild(filter == 4, "LAY_iteminfo_pouch");
    break;
  }
  case GfMenuTypes::unknown003_260:
    GfMenuObject::resetInputSelection(handle);
    GfMenuObject::setupInputSelectionFromList(handle, *unknown20->unknown28);
    break;
  case 0x148:
    GfMenuObject::enableInput(handle);
    GfMenuObjOperationInfo::add(owner.searchChild("LAY_mainwindow"), 0, 0, 0);
    unknown164(owner.searchChild("LAY_filter"), GfMenuTypes::unknown003_257);
    if (unknown0c != event.unknown08) {
      u16 sort = GfMenuObjSort::getSortID(unknown002[unknown20->unknown38[unknown20->unknown98]], event.unknown08);
      unknown20->unknown28->sort(sort, false);
      unknown0c = event.unknown08;
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjItemList2::FilterListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    break;
  case 6: {
    u32 index = event.unknown08;
    u32 previous = event.unknown0c;
    if (unknown20->unknown98 != index) {
      unknown20->unknown98 = index;
      unknown20->refreshFilterIcon();
      unknown164(acc.getParentHandle(), GfMenuTypes::unknown003_259);
      sendEvent(acc.getParentHandle(), GfMenuTypes::unknown003_260, 0, 1);
    }
    if (previous != 0xffffffff && index != previous) {
      GfMenuObjUtil::playSECommonTab();
    }
    break;
  }
  case GfMenuTypes::unknown003_257:
    GfMenuObject::resetInputSelection(handle);
    GfMenuObject::setupInputSelection(handle, unknown20->unknown98, unknown20->unknown38.size());
    GfMenuObject::enableInput(handle);
    unknown20->refreshFilterIcon();
    break;
  case GfMenuTypes::unknown003_258:
    GfMenuObject::disableInput(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}
} // namespace gf
