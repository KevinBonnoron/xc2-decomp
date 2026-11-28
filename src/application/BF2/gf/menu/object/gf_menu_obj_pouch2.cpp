#include "gf/menu/object/gf_menu_obj_pouch2.h"

#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_voice.h"
#include "gf/game/item/gf_pouch_util.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/adapter/gf_menu_pouch_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_item_util.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_char_select.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_sort.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: favorite category of each item filter; original name unknown.
static const u32 unknown002[13] = {0, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};

// Inferred role: call id passed to attachExternalCall in initialize(); taken from the game disassembly, original name unknown.
constexpr u32 unknown005 = 0x70;

// Inferred helper: requests an event with its type and first two parameters on a UI object; original name unknown.
static inline void unknown001(u32 handle, u16 type, u32 param0, u32 param1) {
  ui::EventData event;
  event.unknown10_u64 = 0;
  event.unknown0c = param1;
  event.unknown00 = type;
  event.unknown08 = param0;
  ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

GfMenuObjPouch2::GfMenuObjPouch2(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown5c(0), unknown60(0), unknown64(0), unknown68(nullptr),
      unknown70(), unknownd0(), unknown130(this), unknown3c9(false), m_GAME_VOICE_HANDLE(nullptr), unknown3d8(0), m_menuBladeList(nullptr), unknown3e8(false) {}

GfMenuObjPouch2::~GfMenuObjPouch2() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown68);
  mm::mtl::safeRelease(m_menuBladeList);
  unknown38 = nullptr;
}

void GfMenuObjPouch2::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 185 as in the original file: it is the line argument of operator new.
#line 185
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(unknown005, main);
  u32 slot = acc.searchChild("LAY_eqp_fevitem");
#line 191
  SlotListener *slotListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SlotListener(this);
  slotListener->addRef();
  ui::UIEventManager::get()->registObjectListener(slot, slotListener);
  if (slotListener != nullptr) {
    slotListener->release();
  }
  u32 itemList = acc.searchChild("LAY_fvstock_fevitem");
#line 195
  ItemListListener *itemListListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ItemListListener(this);
  itemListListener->addRef();
  ui::UIEventManager::get()->registObjectListener(itemList, itemListListener);
  if (itemListListener != nullptr) {
    itemListListener->release();
  }
  u32 filter = acc.searchChild("LAY_stock_filter2");
#line 209
  FilterListener2 *filterListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) FilterListener2(this);
  filterListener->addRef();
  ui::UIEventManager::get()->registObjectListener(filter, filterListener);
  if (filterListener != nullptr) {
    filterListener->release();
  }
  u32 partyInfo = acc.searchChild("LAY_chr_fevinfo");
#line 213
  PartyInfoListener *partyInfoListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) PartyInfoListener(this);
  partyInfoListener->addRef();
  ui::UIEventManager::get()->registObjectListener(partyInfo, partyInfoListener);
  if (partyInfoListener != nullptr) {
    partyInfoListener->release();
  }
  u32 result = acc.searchChild("LAY_result");
#line 217
  ResultListener *resultListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ResultListener(this);
  resultListener->addRef();
  ui::UIEventManager::get()->registObjectListener(result, resultListener);
  if (resultListener != nullptr) {
    resultListener->release();
  }
  unknown28 = GfMenuItemList::create();
  ui::UIListInfoBase::SetupParam param;
  param.unknown08 = 3;
  unknown28->setup(getAllocator(ALLOCATOR_UNKNOWN_0), param);
  ui::UISelectObjList::CreateParam createParam;
  createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
  unknown48 = ui::UISelectObjList::create(createParam);
  unknown40 = GfMenuItemList::create();
  unknown38 = unknown160();
  unknown50 = GfMenuCallContext::create();
  unknown68 = GfMenuCallContext::create();
  m_menuBladeList = GfMenuBladeList::create();
  ui::UIObjectAcc slotAcc(acc.searchChild("LAY_eqp_fevitem"));
  disableInput(slotAcc.unknown10);
  ui::UIObjectAcc itemListAcc(acc.searchChild("LAY_fvstock_fevitem"));
  disableInput(itemListAcc.unknown10);
  GfMenuObject::initialize();
}

void GfMenuObjPouch2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPouch2::update() {
  unknown130.unknown003();
  GfMenuObject::update();
}

void GfMenuObjPouch2::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjPouch2::setFadeIn(u32 handle, u32 type) {
  int ctrl = -1;
  switch (type) {
  case 0:
    ctrl = GfMenuObjUtil::unknown002(handle);
    break;
  case 1: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_l_early");
    param.unknown04 = 1;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_r_early");
    param.unknown04 = 1;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  }
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjPouch2::setFadeOut(u32 handle, u32 type) {
  int ctrl = -1;
  switch (type) {
  case 0:
    ctrl = GfMenuObjUtil::unknown003(handle);
    break;
  case 1: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_l_early");
    param.unknown14 = 10;
    param.unknown04 = 2;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_r_early");
    param.unknown14 = 10;
    param.unknown04 = 2;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  }
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjPouch2::setupSlot(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber>) {
  mm::mtl::FixStr<32> name;
  for (u32 slot = 1; slot != 4; slot++) {
    u32 index = slot - 1;
    name.format("IMG_eqpouch_slicon@%02d", slot);
    GfMenuItemAdapter::createFromPouchReferenceDriver(acc.searchChild(name.c_str()), 2, index, 0, false);
    name.format("TXT_eqpouch_efftime@%02d", slot);
    ui::UIObjectAcc time(acc.searchChild(name.c_str()));
    GfMenuPouchAdapter *adapter = GfMenuPouchAdapter::createFromReferenceDriver(acc.searchChild(name.c_str()), 0, index, 0, false);
    name.format("IMG_eqpouch_efftime_bg@%02d", slot);
    ui::UIObjectAcc background(acc.searchChild(name.c_str()));
    if (adapter != nullptr) {
      adapter->unknown24 = background.unknown10;
    }
    GfMenuObjUtil::FitOption option;
    GfMenuObjUtil::createFitPlugin(background.unknown10, time.unknown10, 8, 8, option);
    name.format("TXT_eqpouch_name@%02d", slot);
    GfMenuItemAdapter::createFromPouchReferenceDriver(acc.searchChild(name.c_str()), 0, index, 0, false);
  }
}

void GfMenuObjPouch2::getFilterText(u32 filter, ui::UIStr &text) {
  ui::UIStr filterText(GfDataBdat::getFP(BDAT_MENU_FILTER_CATEGORY), GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_POUCH_FILTER, filter + 1));
  text.copy(filterText);
}

void GfMenuObjPouch2::updateItemList(GfMenuItemList *list, ui::UISelectObjList *, u32 filter, u32 sort) {
  list->clear();
  GfMenuItemList::ItemBoxSetup setup;
  setup.unknown14 = ItemType::ITEM_TYPE_UNKNOWN_10;
  setup.m_setupParam.unknown08 = 8;
  setup.m_setupParam.unknown10 = true;
  setup.unknown28 = false;
  setup.unknown29 = false;
  // The game keeps this function (0x71004b81d4) out of line at the callers with a variable filter (ItemListListener::reciveEvent event 0x101, FilterListener2) and
  // inlines it at the constant site of event 1. With `setupFromBox` called once after the `if`, the inline cost at a variable site is 270 against the threshold 275 (measured
  // with -Rpass-analysis=inline) and the callers inline it (929 instructions for ItemListListener::reciveEvent against the game's 895, 338 against 268 for FilterListener2);
  // written in both arms the cost is 310, the two calls tail merge back into the game's single call and the constant site is still inlined (threshold 412, cost 235).
  if (filter != 0) {
    GfMenuItemList::FiltertInfo info;
    info.unknown00 = 8;
    info.unknown06 = unknown002[filter];
    setup.m_filtertInfo = &info;
    list->setupFromBox(setup);
  } else {
    list->setupFromBox(setup);
  }
  list->sort(GfMenuObjSort::getSortID(0x10, sort), false);
  list->setIndex(0);
}

void GfMenuObjPouch2::refreshItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *selectList, u32 item) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < selectList->getSize(); i++) {
    // The game compares the list item (cset after the getContents load), then calls getSize and combines both
    // (and) before the name format (0x71004b8508); the single-use locals place that compare, that call and that
    // computation (rulings 2026-11-13 #1 and #2, P2). Two locals give 110 insns (compare after the format).
    bool isSelected = list->getContents(list->getPageIndex(i)).unknown04 == item;
    bool isInList = i < list->getSize();
    bool isDisp = isSelected && isInList;
    name.format("IMG_fvstock_tagsellct@%02d", i + 1);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), isDisp);
    name.format("TXT_fvstock_itname@%02d", i + 1);
    ui::UIObjectAcc text(acc.searchChild(name.c_str()));
    GfMenuObjUtil::setColMulandAdd(text.unknown10, "txt_normal2");
    name.format("IMG_fvstock_eqicon@%02d", i + 1);
    ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
    icon.setDisp(false);
  }
}

void GfMenuObjPouch2::refreshSlot(ui::UIObjectAcc &acc, u32 index) {
  u32 driver = GfMenuReference::getReferenceDriverID(0);
  u32 openCount = GfPouchUtil::getOpenCount(driver);
  mm::mtl::FixStr<32> name;
  for (u32 slot = 0; slot < 3; slot++) {
    SDataPouch &pouch = GfPouchUtil::getPouch(driver, slot);
    if (slot < openCount) {
      mm::mtl::FixStr<32> slotName;
      slotName.format("IMG_eqpouch_slbase@%02d", slot + 1);
      ui::UIObjectAcc base(acc.searchChild(slotName.c_str()));
      base.startAnimation(pouch.unknown04 == 0 ? "porch1_idle" : "porch_full", false);
      slotName.format("TXT_eqpouch_no@%02d", slot + 1);
      ui::UIObjectAcc number(acc.searchChild(slotName.c_str()));
      number.setDisp(pouch.unknown04 == 0);
    }
  }
  SDataPouch &pouch = GfPouchUtil::getPouch(driver, index);
  ui::UIObjectAcc cursor(acc.searchChild("IMG_slotcursor"));
  cursor.setImageIndex(pouch.unknown04 != 0);
  for (u32 slot = 0; slot < 3; slot++) {
    name.format("LAY_eqpouch_slot@%02d", slot + 1);
    ui::UIObjectAcc layout(acc.searchChild(name.c_str()));
    if (slot < openCount) {
      layout.setDisp(true);
    } else {
      layout.setDisp(false);
    }
  }
  ui::UISelectObjList::CreateParam param;
  param.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
  ui::UISelectObjList *list = ui::UISelectObjList::create(param);
  for (u32 slot = 0; slot < openCount; slot++) {
    mm::mtl::FixStr<32> slotName;
    slotName.format("LAY_eqpouch_slot@%02d", slot + 1);
    list->addContents(acc.searchChild(slotName.c_str()));
  }
  mm::Rect<s16> rect;
  acc.getLayoutRect("fev_slot02", rect);
  mm::Rect<s16> next;
  acc.getLayoutRect("fev_slot03", next);
  GfMenuObjUtil::placeObjectH(list, mm::Pnt<s16>(rect.x + rect.width / 2, rect.y + rect.height / 2), next.x - 1 - rect.x);
  mm::mtl::safeRelease(list);
}

void GfMenuObjPouch2::setupResult(ui::UIObjectAcc &acc) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 3; i++) {
    u32 number = i + 1;
    name.format("TXT_res_item_name@%02d", number);
    GfMenuItemAdapter::createFromPouchReferenceDriver(acc.searchChild(name.c_str()), 0, i, 0, false);
    name.format("IMG_res_item_icon@%02d", number);
    GfMenuItemAdapter::createFromPouchReferenceDriver(acc.searchChild(name.c_str()), 2, i, 0, false);
    name.format("TXT_res_time@%02d", number);
    GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromPouchReferenceDriver(acc.searchChild(name.c_str()), 0xd, i, 0, false);
    if (adapter != nullptr) {
      name.format("IMG_res_time_bg@%02d", number);
      adapter->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("IMG_res_time_bg@%02d", number);
    ui::UIObjectAcc timeBackground(acc.searchChild(name.c_str()));
    name.format("TXT_res_time@%02d", number);
    ui::UIObjectAcc time(acc.searchChild(name.c_str()));
    GfMenuObjUtil::createFitPlugin(timeBackground.unknown10, time.unknown10, 8, 8, GfMenuObjUtil::FitOption());
    name.format("TXT_res_empty@%02d", number);
    ui::UIObjectAcc empty(acc.searchChild(name.c_str()));
    name.format("IMG_res_empty_bg@%02d", number);
    ui::UIObjectAcc emptyBackground(acc.searchChild(name.c_str()));
    GfMenuObjUtil::createFitPlugin(emptyBackground.unknown10, empty.unknown10, 8, 8, GfMenuObjUtil::FitOption());
    for (u32 effect = 0; effect < 3; effect++) {
      name.format("TXT_res_eff%1d@%02d", effect + 1, number);
      adapter = GfMenuItemAdapter::createFromPouchReferenceDriver(acc.searchChild(name.c_str()), 0xe, i, 0, false);
      if (adapter != nullptr) {
        adapter->unknown70 = effect;
        name.format("IMG_res_eff%1d_bg@%02d", effect + 1, number);
        adapter->unknown24 = acc.searchChild(name.c_str());
      }
    }
    name.format("IMG_res_char_icon1@%02d", number);
    GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild(name.c_str()), 3, 0, false);
    for (int slot = 0; slot < 4; slot++) {
      name.format("IMG_res_char_icon%1d@%02d", slot + 2, number);
      GfMenuCharDataAdapter *charAdapter = GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.c_str()), 3, 0, slot, false);
      if (charAdapter != nullptr) {
        name.format("LAY_res_char_icon%1d@%02d", slot + 2, number);
        charAdapter->unknown24 = acc.searchChild(name.c_str());
      }
    }
  }
}

void GfMenuObjPouch2::setupPartyInfo(ui::UIObjectAcc &acc) {
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_chr_fiface@01"), 3, 0, false);
  GfMenuCharDataAdapter *adapter = GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_chr_fvicon01@01"), 10, 0, true);
  if (adapter != nullptr) {
    adapter->unknown80 = 0;
  }
  adapter = GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_chr_fvicon02@01"), 10, 0, true);
  if (adapter != nullptr) {
    adapter->unknown80 = 1;
  }
  adapter = GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_chr_fviconit@01"), 0xc, 0, true);
  if (adapter != nullptr) {
    adapter->unknown80 = 0;
  }
  adapter = GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_chr_fvitnameit@01"), 0xb, 0, true);
  if (adapter != nullptr) {
    adapter->unknown80 = 0;
  }
  adapter = GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_chr_fviconit2@01"), 0xc, 0, true);
  if (adapter != nullptr) {
    adapter->unknown80 = 1;
  }
  adapter = GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_chr_fvitnameit2@01"), 0xb, 0, true);
  if (adapter != nullptr) {
    adapter->unknown80 = 1;
  }
  mm::mtl::FixStr<32> name;
  for (int slot = 0; slot < 3; slot++) {
    name.format("IMG_chr_fiface@%02d", slot + 2);
    adapter = GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.c_str()), 3, 0, slot, false);
    if (adapter != nullptr) {
      name.format("LAY_chr_fi@%02d", slot + 2);
      adapter->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("IMG_chr_fvicon01@%02d", slot + 2);
    adapter = GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.c_str()), 10, 0, slot, true);
    if (adapter != nullptr) {
      adapter->unknown80 = 0;
    }
    name.format("IMG_chr_fvicon02@%02d", slot + 2);
    adapter = GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.c_str()), 10, 0, slot, true);
    if (adapter != nullptr) {
      adapter->unknown80 = 1;
    }
    name.format("IMG_chr_fviconit@%02d", slot + 2);
    adapter = GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.c_str()), 0xc, 0, slot, true);
    if (adapter != nullptr) {
      adapter->unknown80 = 0;
    }
    name.format("TXT_chr_fvitnameit@%02d", slot + 2);
    adapter = GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.c_str()), 0xb, 0, slot, true);
    if (adapter != nullptr) {
      adapter->unknown80 = 0;
    }
    name.format("IMG_chr_fviconit2@%02d", slot + 2);
    adapter = GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.c_str()), 0xc, 0, slot, true);
    if (adapter != nullptr) {
      adapter->unknown80 = 1;
    }
    name.format("TXT_chr_fvitnameit2@%02d", slot + 2);
    adapter = GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.c_str()), 0xb, 0, slot, true);
    if (adapter != nullptr) {
      adapter->unknown80 = 1;
    }
  }
}

void GfMenuObjPouch2::setupFilter(ui::UIObjectAcc &acc, u32 filter) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 13; i++) {
    name.format("IMG_ficon@%02d", i + 1);
    ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
    if (icon.isValid()) {
      u32 number = 0;
      if (i == 0) {
        number = 14;
      } else {
        GfMenuItemUtil::getIconNumber(ItemType::ITEM_TYPE_UNKNOWN_10, unknown002[i], number, false);
      }
      icon.setImageIndex(number);
    }
  }
  {
    mm::Rect<s16> rect;
    acc.getLayoutRect("all_item", rect);
    mm::Rect<s16> range;
    acc.getLayoutRect("all_item_range", range);
    GfMenuObjUtil::placeObjectH(acc.unknown10, "LAY_icon@%02d", 13, mm::Pnt<s16>(rect.x + rect.width / 2, rect.y + rect.height / 2), range.x - rect.x);
  }
  ui::UIStr text;
  getFilterText(filter, text);
  ui::UIObjectAcc label(acc.searchChild("TXT_fvstock_index"));
  label.setText(text);
}

void GfMenuObjPouch2::setupItemList(ui::UIObjectAcc &acc, GfMenuItemList *list) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 8; i++) {
    name.format("IMG_fvstock_iticon@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 2, list, i, false);
    name.format("TXT_fvstock_itname@%02d", i + 1);
    GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 0, list, i, false);
    name.format("LAY_fvstock_listtag@%02d", i + 1);
    if (adapter != nullptr) {
      adapter->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("IMG_fvstock_reaicon@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 7, list, i, false);
    name.format("TXT_fvstock_stcknum@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 3, list, i, false);
    name.format("IMG_fvstock_tagsellct@%02d", i + 1);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
  }
  for (u32 i = 0; i < 3; i++) {
    name.format("TXT_fvstock_info_eff@%02d", i + 1);
    GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 0xe, list, -1, false);
    if (adapter != nullptr) {
      adapter->unknown70 = i;
    }
  }
  GfMenuItemAdapter::createFromList(acc.searchChild("TXT_fvstock_info_time_num"), 0xd, list, -1, false);
}

bool GfMenuObjPouch2::seqFavOpen() {
  unknown3c8 = false;
  unknown3c0 = 0;
  unknown3c4 = 0;
  return true;
}

GAME_VOICE_HANDLE *GfMenuObjPouch2::procFavFlag(ui::UIObjectAcc &acc, FavoriteFlag &flag, u32 index, u32 favorite) {
  // Inferred role: effect image names of the favorite flag icons; original name unknown.
  static const char *const unknown006[] = {"IMG_chr_fvicon01eff@%02d", "IMG_chr_fvicon02eff@%02d", "IMG_chr_fviconit01eff@%02d", "IMG_chr_fviconit02eff@%02d"};
  // Inferred role: animation image names of the favorite flag icons; original name unknown.
  static const char *const unknown007[] = {"IMG_chr_fvicon01anm@%02d", "IMG_chr_fvicon02anm@%02d", "IMG_chr_fviconit01anm@%02d", "IMG_chr_fviconit02anm@%02d"};
  mm::mtl::FixStr<32> name;
  name.format(unknown006[favorite], index + 1);
  ui::UIObjectAcc effect(acc.searchChild(name.c_str()));
  effect.startAnimation("flash", false);
  name.format(unknown007[favorite], index + 1);
  ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 0x10000000;
  param.unknown50 = "mnu070_heart";
  param.unknown58 = "fadein_a";
  param.unknown04 = 1;
  GfMenuObjUtil::startCtrl(icon.unknown10, param, nullptr);
  return SCOM_FIELD_VOICE::createFavorite(flag.unknown00, static_cast<FAVORITE>(favorite));
}

void GfMenuObjPouch2::setFavFlag(u32 driver, u32 item, mm::mtl::FixedArray<FavoriteFlag, 4> &flags, const GfMenuBladeList *list) {
  flags[0].unknown00 = driver;
  flags[0].unknown04 = item;
  flags[0].unknown08[0] = GfMenuObjUtil::getFavoriteStat(OBJECT_TYPE_PC, driver, FAVORITE_UNKNOWN_0);
  flags[0].unknown08[1] = GfMenuObjUtil::getFavoriteStat(OBJECT_TYPE_PC, driver, FAVORITE_UNKNOWN_1);
  flags[0].unknown08[2] = GfMenuObjUtil::getFavoriteStat(OBJECT_TYPE_PC, driver, FAVORITE_UNKNOWN_2);
  flags[0].unknown08[3] = GfMenuObjUtil::getFavoriteStat(OBJECT_TYPE_PC, driver, FAVORITE_UNKNOWN_3);
  DataParamAcc acc(OBJECT_TYPE_PC, driver, GIMMICK_TYPE_UNKNOWN_0);
  for (u32 i = 0; i < 3; i++) {
    if (i < list->getSize()) {
      u32 blade = list->getContents(i).unknown00;
      flags[i + 1].unknown00 = blade;
      flags[i + 1].unknown04 = item;
      if (blade != 0) {
        flags[i + 1].unknown08[0] = GfMenuObjUtil::getFavoriteStat(OBJECT_TYPE_BLADE, blade, FAVORITE_UNKNOWN_0);
        flags[i + 1].unknown08[1] = GfMenuObjUtil::getFavoriteStat(OBJECT_TYPE_BLADE, blade, FAVORITE_UNKNOWN_1);
        flags[i + 1].unknown08[2] = GfMenuObjUtil::getFavoriteStat(OBJECT_TYPE_BLADE, blade, FAVORITE_UNKNOWN_2);
        flags[i + 1].unknown08[3] = GfMenuObjUtil::getFavoriteStat(OBJECT_TYPE_BLADE, blade, FAVORITE_UNKNOWN_3);
      }
    } else {
      flags[i + 1].unknown00 = 0;
      flags[i + 1].unknown04 = item;
    }
  }
}

bool GfMenuObjPouch2::seqFavLoop() {
  ui::UIObjectAcc acc(unknown18);
  if (!unknown3c8) {
    for (; unknown3c0 < 4; unknown3c0++) {
      for (; unknown3c4 < 4; unknown3c4++) {
        if (unknown70[unknown3c0].unknown08[unknown3c4] != unknownd0[unknown3c0].unknown08[unknown3c4] && unknownd0[unknown3c0].unknown08[unknown3c4] == 0) {
          GAME_VOICE_HANDLE *voice = procFavFlag(acc, unknownd0[unknown3c0], unknown3c0, unknown3c4);
          unknown3c8 = true;
          m_GAME_VOICE_HANDLE = voice;
          unknown3c4++;
          return false;
        }
        u32 favorite;
        if (unknown3c0 == 0) {
          favorite = GfDataDriver::getFavorite(unknownd0[unknown3c0].unknown00, static_cast<FAVORITE>(unknown3c4));
        } else {
          favorite = GfDataBlade::getFavorite(unknownd0[unknown3c0].unknown00, static_cast<FAVORITE>(unknown3c4));
        }
        if (unknown3c4 < 2) {
          if (favorite == GfDataItem::getCategory(unknownd0[unknown3c0].unknown04)) {
            GAME_VOICE_HANDLE *voice = SCOM_FIELD_VOICE::createFavorite(unknownd0[unknown3c0].unknown00, static_cast<FAVORITE>(unknown3c4));
            unknown3c8 = true;
            m_GAME_VOICE_HANDLE = voice;
            unknown3c4++;
            return false;
          }
        } else if (favorite == unknownd0[unknown3c0].unknown04) {
          GAME_VOICE_HANDLE *voice = SCOM_FIELD_VOICE::createFavorite(unknownd0[unknown3c0].unknown00, static_cast<FAVORITE>(unknown3c4));
          unknown3c8 = true;
          m_GAME_VOICE_HANDLE = voice;
          unknown3c4++;
          return false;
        }
      }
      unknown3c4 = 0;
    }
    return true;
  }
  int result = GfGameVoice::getResult(m_GAME_VOICE_HANDLE);
  if (result == 1 || result == 2) {
    return false;
  }
  unknown3c8 = false;
  return false;
}

void GfMenuObjPouch2::updateSlotList(GfMenuItemList *list) {
  u32 driver = GfMenuReference::getReferenceDriverID(0);
  list->clear();
  for (u32 slot = 0; slot < 3; slot++) {
    SDataPouch &pouch = GfPouchUtil::getPouch(driver, slot);
    if (pouch._06 != 0) {
      MenuItemInfo info;
      info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_10;
      info.unknown04 = pouch.unknown04;
      info.unknown08 = info.unknown04 != 0;
      list->addContents(info);
    }
  }
}

bool GfMenuObjPouch2::seqFavPouchIn() {
  ui::UIObjectAcc acc(unknown18);
  u32 slot = unknown38->unknown0c + 1;
  mm::mtl::FixStr<32> name;
  name.format("IMG_eqpouch_slbase@%02d", slot);
  ui::UIObjectAcc base(acc.searchChild(name.c_str()));
  name.format("IMG_eqpouch_slicon@%02d", slot);
  ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
  bool isEnd = true;
  unknown3c9 = true;
  switch (unknown3c0) {
  case 0: {
    name.format("TXT_eqpouch_no@%02d", slot);
    ui::UIObjectAcc number(acc.searchChild(name.c_str()));
    number.setDisp(false);
    if (unknown3c4 < 5) {
      unknown3c4++;
    } else {
      unknown3c0++;
    }
    isEnd = false;
    break;
  }
  case 1: {
    base.startAnimation("porch1_itemin", false);
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "mnu070_item";
    param.unknown58 = "item_throw";
    param.unknown11 = true;
    param.unknown14 = 8;
    GfMenuObjUtil::startCtrl(icon.unknown10, param, nullptr);
    GfMenuObjUtil::playSE(0x39);
    unknown3c0++;
    isEnd = false;
    break;
  }
  case 2:
    if (!base.isPlayingAnimation()) {
      u32 layout = acc.searchChild("LAY_eqp_fevitem");
      GfMenuObjMainMenu2::openCharChange(layout, 0, false);
      ui::UIObjectAcc favorite(acc.searchChild("LAY_eqp_fevitem"));
      refreshSlot(favorite, unknown28->getIndex(false));
      GfMenuObject::enableInput(layout);
      unknown3c9 = false;
      unknown30->setAlpha(1.0f);
      unknown30->setDisp(true);
    } else {
      isEnd = false;
    }
    break;
  }
  return isEnd;
}

bool GfMenuObjPouch2::seqFavClose() {
  ui::UIObjectAcc acc(unknown18);
  sendEvent(acc.searchChild("LAY_fvstock_fevitem"), 0x22, 0);
  unknown001(acc.searchChild("LAY_stock_filter2"), 0x22, 0, 0);
  unknown001(acc.searchChild("LAY_chr_fevinfo"), 0x102, 0, 0);
  unknown001(acc.searchChild("LAY_eqp_fevitem"), 0x101, 1, 0);
  unknown3c0 = 0;
  unknown3c4 = 0;
  return true;
}

// Inferred role: plays the cursor sound when the selection moved from a valid previous index; original name unknown.
static void unknown009(u32 index, u32 previous) {
  if (previous != 0xffffffff && index != previous) {
    GfMenuObjUtil::playSECommonCursor();
  }
}

void GfMenuObjPouch2::SlotListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(m_menuObjPouch2->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    setupSlot(acc, m_menuObjPouch2->unknown38);
    updateSlotList(m_menuObjPouch2->unknown28);
    refreshSlot(acc, 0);
    // Written out like the cursor setup of GfMenuObjCharSelect::SubMenuListener and GfMenuObjHanaSubmenu::SubmenuListener (ruling 8): a helper taking the
    // cursor and format names gives a 240 byte frame against the game's 256 (the parameter has its own slot). The two stores after the search of
    // IMG_slotcursor are the game's (P3): the constructor already cleared the cursor type at offset 0x1a and the dock type at 0x38 is 1 by default
    // (0x71004b6990 and 0x71004b6994: strh wzr).
    GfMenuObjUtil::CursorParam param;
    param.unknown00 = ui::UIObjectAcc(handle).getParentHandle();
    param.unknown04 = acc.searchChild("IMG_slotcursor");
    param.unknown1a = 0;
    param.m_cursorSetting.unknown18 = 0;
    param.unknown08 = "IMG_eqpouch_slbase@%02d";
    m_menuObjPouch2->unknown30 = GfMenuObjUtil::createCursor(param);
    m_menuObjPouch2->unknown30->open(0);
    GfMenuObject::setupInputSelection(handle, 0, m_menuObjPouch2->unknown28->getSize());
    GfMenuObject::disableInput(handle);
    unknown164(handle, GfMenuTypes::unknown003_257);
    break;
  }
  case 0x101:
    GfMenuObjOperationInfo::setGuideText(0x20, 0);
    GfMenuObjOperationInfo::add(handle, 0, 0, 0);
    GfMenuObjMainMenu2::setSubIndexText(0x16);
    GfMenuObjUtil::setChildDisp(handle, "IMG_eqpouch_sellect", true);
    m_menuObjPouch2->unknown30->setDisp(false);
    setFadeIn(handle, 1);
    m_menuObjPouch2->unknown3e8 = event.unknown08 == 0;
    break;
  case 0x140:
    GfMenuReference::setReferenceDriverID(0, event.unknown08);
    updateSlotList(m_menuObjPouch2->unknown28);
    refreshSlot(acc, m_menuObjPouch2->unknown28->getIndex(false));
    GfMenuObject::resetInputSelection(handle);
    GfMenuObject::setupInputSelection(handle, 0, m_menuObjPouch2->unknown28->getSize());
    GfMenuObjCharSelect::execCharPosScale(0);
    break;
  case 3:
    if (event.unknown08 == 1) {
      if (!m_menuObjPouch2->unknown3c9) {
        m_menuObjPouch2->unknown30->setDisp(true);
      }
      if (m_menuObjPouch2->unknown3e8) {
        GfMenuObjMainMenu2::openCharChange(acc.unknown10, 0, false);
        GfMenuObject::enableInput(handle);
      }
    }
    break;
  case 6: {
    u32 index = event.unknown08;
    u32 previous = event.unknown0c;
    u32 driver = GfMenuReference::getReferenceDriverID(0);
    if (m_menuObjPouch2->unknown30->inputChange(index)) {
      m_menuObjPouch2->unknown38->unknown0c = index;
      SDataPouch &pouch = GfPouchUtil::getPouch(driver, index);
      ui::UIObjectAcc cursor(acc.searchChild("IMG_slotcursor"));
      cursor.setImageIndex(pouch.unknown04 != 0);
    }
    unknown009(index, previous);
    break;
  }
  case 8:
    if (GfMenuObjCharSelect::getCharBusy()) {
      break;
    }
    switch (event.unknown0c) {
    case 1:
      if (m_menuObjPouch2->unknown40->getSize() != 0) {
        GfMenuBladeList::DriverSetup setup;
        setup.unknown18 = GfMenuReference::getReferenceDriverID(0);
        setup.unknown14 = 1;
        m_menuObjPouch2->m_menuBladeList->setupFromDriver(setup);
        unknown164(handle, GfMenuTypes::unknown003_258);
        unknown001(owner.searchChild("LAY_chr_fevinfo"), GfMenuTypes::unknown003_257, 0, 0);
        unknown001(owner.searchChild("LAY_fvstock_fevitem"), GfMenuTypes::unknown003_33, 0, 0);
        unknown001(owner.searchChild("LAY_stock_filter2"), GfMenuTypes::unknown003_33, 0, 0);
        GfMenuObjMainMenu2::closeCharChange();
        GfMenuObjUtil::playSECommonDecide();
      } else {
        GfMenuObjCommonText::openError(m_menuObjPouch2->unknown50, 0x15, 0);
        GfMenuObjUtil::playSECommon(2);
      }
      break;
    case 2:
      unknown164(owner.searchChild("LAY_main"), GfMenuTypes::unknown003_34);
      unknown001(handle, GfMenuTypes::unknown003_258, 0, 0);
      GfMenuObjMainMenu2::disableCharChange();
      GfMenuObjUtil::playSECommonCancel();
      break;
    case 9: {
      u32 driver = GfMenuReference::getReferenceDriverID(0);
      u8 first = GfDataDriver::getPouchData(driver, 0)._06;
      u8 second = GfDataDriver::getPouchData(driver, 1)._06;
      if (first == 0 || second == 0) {
        if (GfPouchUtil::isExistOpenItem()) {
          m_menuObjPouch2->unknown58 = 0x48;
          GfMenuObjCommonText::open(m_menuObjPouch2->unknown50, m_menuObjPouch2->unknown58, 0);
          GfMenuObject::setCallContextEventHandler(m_menuObjPouch2->unknown50, handle);
        } else {
          GfMenuObjCommonText::openError(m_menuObjPouch2->unknown50, 0x13, 0);
          GfMenuObjUtil::playSECommon(2);
        }
      } else {
        GfMenuObjCommonText::openError(m_menuObjPouch2->unknown50, 0x14, 0);
        GfMenuObjUtil::playSECommon(2);
      }
      break;
    }
    case 10: {
      GfMenuBladeList::DriverSetup setup;
      setup.unknown18 = GfMenuReference::getReferenceDriverID(0);
      setup.unknown14 = 1;
      m_menuObjPouch2->m_menuBladeList->setupFromDriver(setup);
      unknown164(handle, GfMenuTypes::unknown003_258);
      unknown001(owner.searchChild("LAY_result"), GfMenuTypes::unknown003_257, 0, 0);
      GfMenuObjCharSelect::dispOffChar(0);
      m_menuObjPouch2->unknown64 = 0;
      GfMenuObjMainMenu2::closeCharChange();
      GfMenuObjUtil::playSECommonOpenSubMenu();
      break;
    }
    }
    break;
  case 0x41:
    if (m_menuObjPouch2->unknown50 != nullptr && m_menuObjPouch2->unknown50->unknown0c == event.unknown08) {
      u16 result = event.unknown10_u16;
      u32 driver = GfMenuReference::getReferenceDriverID(0);
      if (result == 0 && m_menuObjPouch2->unknown58 == 0x48) {
        GfPouchUtil::execOpen(driver);
        updateSlotList(m_menuObjPouch2->unknown28);
        refreshSlot(acc, m_menuObjPouch2->unknown28->getIndex(false));
        GfMenuObject::resetInputSelection(handle);
        GfMenuObject::setupInputSelection(handle, 0, m_menuObjPouch2->unknown28->getSize());
      }
    }
    break;
  case 0x102:
    GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
    GfMenuObjUtil::setChildDisp(handle, "IMG_eqpouch_sellect", false);
    GfMenuObject::disableInput(handle);
    setFadeOut(handle, 1);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

// Ruling 8: the prologue (the owner and handle accessors, then the switch on the event) is written out in every listener of this class; a file-local struct that builds both accessors in its
// constructor gives 899 instructions against the game's 895 here (482 lines differ from +0x8, 0x71004b73e0).
void GfMenuObjPouch2::ItemListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(m_menuObjPouch2->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    updateItemList(m_menuObjPouch2->unknown40, m_menuObjPouch2->unknown48, 0, 0);
    setupItemList(acc, m_menuObjPouch2->unknown40);
    m_menuObjPouch2->unknown48->pickupObject(handle, "LAY_fvstock_listtag@%02d", 1);
    GfMenuObjUtil::createVScrollBarPlugin(acc.searchChild("IMG_fvstock_scpoint"), m_menuObjPouch2->unknown40, "IMG_fvstock_scline", true);
    // The game reloads the list and the select list for the call after the getContents asserts (0x71004b7c60); written as the argument of
    // refreshItemList the item is read after both pointers, which are then loaded together before the asserts (ldp x21, x22 at the top of the case).
    u32 item = m_menuObjPouch2->unknown40->getContents(0).unknown04;
    refreshItemList(acc, m_menuObjPouch2->unknown40, m_menuObjPouch2->unknown48, item);
    GfMenuObject::disableInput(handle);
    acc.setDisp(false);
    GfMenuObjSort::setSortLabelText(GfMenuObjSort::getSortID(0x10, 0), owner.searchChild("TXT_item_sort_label"));
    m_menuObjPouch2->unknown3d8 = 0;
    break;
  }
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(handle);
    }
    break;
  case 6: {
    u32 index = event.unknown08;
    u32 previous = event.unknown0c;
    m_menuObjPouch2->unknown40->setIndex(index);
    u32 item = m_menuObjPouch2->unknown40->getContents(index).unknown04;
    refreshItemList(acc, m_menuObjPouch2->unknown40, m_menuObjPouch2->unknown48, item);
    unknown001(owner.searchChild("LAY_chr_fevinfo"), 0x103, item, 0);
    unknown009(index, previous);
    break;
  }
  case 8:
    switch (event.unknown0c) {
    case 1: {
      u32 driver = GfMenuReference::getReferenceDriverID(0);
      u32 slot = m_menuObjPouch2->unknown38->unknown0c;
      // Bare call: the game calls getPouch (0x71004b7774) and never reads the result.
      GfPouchUtil::getPouch(driver, slot);
      if (m_menuObjPouch2->unknown40->getSize() != 0) {
        u32 item = m_menuObjPouch2->unknown40->getContents(m_menuObjPouch2->unknown40->getIndex(false)).unknown04;
        m_menuObjPouch2->unknown50->reset();
        if (GfPouchUtil::isEnableSetItem(driver, slot, item)) {
          // Inferred role: common text id of each pouch slot, written to unknown58 (0x7100f722a8; the result event compares the same ids); original name unknown.
          static const u32 unknown008[] = {0x17, 0xa1, 0xa2};
          m_menuObjPouch2->unknown58 = unknown008[slot];
          GfMenuObjCommonText::open(m_menuObjPouch2->unknown50, m_menuObjPouch2->unknown58, 0);
          GfMenuObject::setCallContextEventHandler(m_menuObjPouch2->unknown50, handle);
          break;
        }
        m_menuObjPouch2->unknown58 = 0x18;
        GfMenuObjCommonText::openError(m_menuObjPouch2->unknown50, m_menuObjPouch2->unknown58, 0);
      }
      GfMenuObjUtil::playSECommon(2);
      break;
    }
    case 2:
      sendEvent(handle, 0x22, 0);
      unknown001(owner.searchChild("LAY_stock_filter2"), 0x22, 0, 0);
      unknown001(owner.searchChild("LAY_chr_fevinfo"), 0x102, 0, 0);
      unknown001(owner.searchChild("LAY_eqp_fevitem"), 0x101, 0, 0);
      GfMenuObjUtil::playSECommonCancel();
      break;
    case 10:
      sendEvent(handle, 0x102, 0);
      unknown001(owner.searchChild("LAY_result"), 0x101, 0, 0);
      setFadeOut(handle, 1);
      setFadeOut(owner.searchChild("LAY_chr_fevinfo"), 2);
      m_menuObjPouch2->unknown64 = 1;
      GfMenuObjUtil::playSECommonOpenSubMenu();
      break;
    case 12:
      GfMenuObjSort::open(acc.unknown10, owner.searchChild("TXT_item_sort_label"), 0x10, m_menuObjPouch2->unknown3d8);
      GfMenuObject::disableInput(handle);
      GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
      break;
    }
    break;
  case 0x21:
    GfMenuObjCharSelect::dispOffChar(0);
    setFadeIn(handle, 1);
    unknown001(handle, 0x101, 0, 0);
    GfMenuObject::disableInput(handle);
    break;
  case 0x22:
    GfMenuObjCharSelect::dispOnChar(0);
    setFadeOut(handle, 1);
    unknown001(handle, 0x102, 0, 0);
    break;
  case 0x41:
    if (m_menuObjPouch2->unknown50 != nullptr && m_menuObjPouch2->unknown50->unknown0c == event.unknown08) {
      // The game loads the result (ldrh) before the compares of the call context id (0x71004b7968): the local places that load, and the switch keeps
      // it there (`id == 0xa1 || id == 0xa2 || id == 0x17 && result == 0` and `event.unknown10_u16 == 0` in the case body both load it after the
      // compares: 6 differing instructions, same count).
      u16 result = event.unknown10_u16;
      switch (m_menuObjPouch2->unknown58) {
      case 0x17:
      case 0xa1:
      case 0xa2:
        if (result == 0) {
          u32 driver = GfMenuReference::getReferenceDriverID(0);
          u32 slot = m_menuObjPouch2->unknown38->unknown0c;
          SDataPouch pouch = GfPouchUtil::getPouch(driver, slot);
          u32 item = m_menuObjPouch2->unknown40->getContents(m_menuObjPouch2->unknown40->getIndex(false)).unknown04;
          setFavFlag(driver, item, m_menuObjPouch2->unknown70, m_menuObjPouch2->m_menuBladeList);
          pouch.unknown04 = item;
          GfPouchUtil::setPouch(driver, slot, pouch);
          GfDataDriver::setUsedFavoriteItemForPouch(driver, item);
          setFavFlag(driver, item, m_menuObjPouch2->unknownd0, m_menuObjPouch2->m_menuBladeList);
          m_menuObjPouch2->unknown130.unknown005();
          m_menuObjPouch2->unknown130.unknown002(&GfMenuObjPouch2::seqFavOpen);
          m_menuObjPouch2->unknown130.unknown002(&GfMenuObjPouch2::seqFavLoop);
          m_menuObjPouch2->unknown130.unknown002(&GfMenuObjPouch2::seqFavClose);
          m_menuObjPouch2->unknown130.unknown002(&GfMenuObjPouch2::seqFavPouchIn);
          GfMenuObject::disableInput(handle);
          m_menuObjPouch2->unknown30->setAlpha(0.0f);
        }
        break;
      }
    }
    break;
  case 0x101:
    GfMenuObjOperationInfo::setGuideText(0x17, 0);
    GfMenuObjOperationInfo::add(handle, 0, 0, 0);
    m_menuObjPouch2->unknown5c = 0;
    m_menuObjPouch2->unknown3d8 = 0;
    sendEvent(owner.searchChild("LAY_stock_filter2"), 0x101, 0);
    unknown001(handle, 0x104, 0, 0);
    GfMenuObjSort::setSortLabelText(GfMenuObjSort::getSortID(0x10, m_menuObjPouch2->unknown3d8), owner.searchChild("TXT_item_sort_label"));
    // The select list is the game's erased argument: x1 is not set at 0x71004b7b18 (the parameter is never read).
    updateItemList(m_menuObjPouch2->unknown40, m_menuObjPouch2->unknown48, m_menuObjPouch2->unknown5c, m_menuObjPouch2->unknown3d8);
    break;
  case 0x102:
    GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
    unknown001(owner.searchChild("LAY_stock_filter2"), 0x102, 0, 0);
    refreshItemList(acc, m_menuObjPouch2->unknown40, m_menuObjPouch2->unknown48, 0);
    GfMenuObject::disableInput(handle);
    break;
  case 0x104: {
    m_menuObjPouch2->unknown40->setIndex(0);
    // Reloads of the list and of the select list after the index load (0x71004b7c2c); the call form with the item as an argument loads them before it and the
    // function has an ldp of both pointers at the top of the case instead.
    u32 item = m_menuObjPouch2->unknown40->getContents(m_menuObjPouch2->unknown40->getIndex(false)).unknown04;
    refreshItemList(acc, m_menuObjPouch2->unknown40, m_menuObjPouch2->unknown48, item);
    GfMenuObject::resetInputSelection(handle);
    GfMenuObject::setupInputSelectionFromList(handle, *m_menuObjPouch2->unknown40);
    break;
  }
  case 0x148:
    GfMenuObject::enableInput(handle);
    GfMenuObjOperationInfo::add(handle, 0, 0, 0);
    if (m_menuObjPouch2->unknown3d8 != event.unknown08) {
      // The game calls getSortID (0x71004b7634) before the discarded getIndex of the slot list (0x71004b7648, result unused) and the sort, which the local places.
      u16 sort = GfMenuObjSort::getSortID(0x10, event.unknown08);
      m_menuObjPouch2->unknown28->getIndex(true);
      m_menuObjPouch2->unknown40->sort(sort, false);
      m_menuObjPouch2->unknown3d8 = event.unknown08;
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

// Ruling 8: same prologue as ItemListListener; the accessor struct gives 270 instructions against the game's 268 (185 lines differ from +0x0, 0x71004b9f10).
void GfMenuObjPouch2::FilterListener2::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(m_menuObjPouch2->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupFilter(acc, m_menuObjPouch2->unknown5c);
    GfMenuObject::disableInput(handle);
    acc.setDisp(false);
    break;
  case 6: {
    int index = event.unknown08;
    int previous = event.unknown0c;
    mm::mtl::FixStr<32> name;
    if (previous >= 0) {
      name.format("IMG_ficon@%02d", previous + 1);
      ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
      icon.loadDefColor();
    }
    if (index >= 0) {
      name.format("IMG_ficon@%02d", index + 1);
      ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
      icon.setMulColor("sys_select");
    }
    ui::UIStr text;
    getFilterText(index, text);
    ui::UIObjectAcc label(acc.searchChild("TXT_fvstock_index"));
    label.setText(text);
    m_menuObjPouch2->unknown5c = index;
    updateItemList(m_menuObjPouch2->unknown40, m_menuObjPouch2->unknown48, m_menuObjPouch2->unknown5c, m_menuObjPouch2->unknown3d8);
    u32 item = m_menuObjPouch2->unknown40->getContents(m_menuObjPouch2->unknown40->getIndex(false)).unknown04;
    unknown001(owner.searchChild("LAY_chr_fevinfo"), 0x103, item, 0);
    unknown001(owner.searchChild("LAY_fvstock_fevitem"), 0x104, 0, 0);
    if (previous != -1 && index != previous) {
      GfMenuObjUtil::playSECommonTab();
    }
    break;
  }
  case 0x21:
    acc.setDisp(true);
    break;
  case 0x22:
    acc.setDisp(false);
    GfMenuObject::disableInput(handle);
    m_menuObjPouch2->unknown5c = 0;
    updateItemList(m_menuObjPouch2->unknown40, m_menuObjPouch2->unknown48, m_menuObjPouch2->unknown5c, m_menuObjPouch2->unknown3d8);
    break;
  case 0x101: {
    m_menuObjPouch2->unknown5c = 0;
    m_menuObjPouch2->unknown60 = m_menuObjPouch2->unknown5c;
    u32 list = acc.searchChild("LAY_iconlist");
    GfMenuObject::hookCtrlEvent(list, GfMenuObjUtil::unknown002(list));
    GfMenuObject::setupInputSelection(handle, m_menuObjPouch2->unknown5c, 13);
    GfMenuObject::enableInput(handle);
    break;
  }
  case 0x102: {
    u32 list = acc.searchChild("LAY_iconlist");
    GfMenuObject::hookCtrlEvent(list, GfMenuObjUtil::unknown003(list));
    GfMenuObject::disableInput(handle);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

// Inferred role: shows a favorite icon with the image index `imageIndex` when `isFavorite`, hides it otherwise; original name unknown. The `like` accessor is the caller's: a helper that builds
// its own gives 575 instructions with 148 differing lines from +0x24 (0x71004ba5a0: the inlined copies get three `like` stack slots where the game has two), and a plain `static` one is not
// inlined (413 instructions). The favorite test stays in the caller: a helper that takes the compared value and calls getFavoriteStat/getFavorite itself (one per driver and blade) gives 575
// instructions with 8 differing lines from +0x138 (0x71004ba6b4: the operands of the favorite compare are swapped).
static void unknown011(ui::UIObjectAcc &like, bool isFavorite, u32 imageIndex) {
  if (isFavorite) {
    like.setImageIndex(imageIndex);
    like.setDisp(true);
  } else {
    like.setDisp(false);
  }
}

// Inferred role: hides the favorite icon of an empty blade slot; the game reads the stat of blade 0 and drops it; original name unknown.
static void unknown010(ui::UIObjectAcc &like, FAVORITE favorite) {
  GfMenuObjUtil::getFavoriteStat(OBJECT_TYPE_BLADE, 0, favorite);
  like.setDisp(false);
}

// 0x71004ba57c, 575 insns. The favorite icon blocks go through unknown011 and unknown010 (the two-line `like2` blocks below stay written out: a helper holding `like.setDisp(false)` also matches
// but only wraps one call). Ruling 8: same prologue as ItemListListener; the accessor struct gives 581 instructions (313 lines differ from +0x20, 0x71004ba59c).
void GfMenuObjPouch2::PartyInfoListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(m_menuObjPouch2->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupPartyInfo(acc);
    GfMenuObject::disableInput(handle);
    acc.setDisp(false);
    break;
  case GfMenuTypes::unknown003_257:
    setFadeIn(handle, 2);
    break;
  case GfMenuTypes::unknown003_258:
    setFadeOut(handle, 2);
    break;
  case GfMenuTypes::unknown003_259: {
    u32 driver = GfMenuReference::getReferenceDriverID(0);
    u32 item = event.unknown08;
    int category = GfDataItem::getCategory(item);
    mm::mtl::FixStr<32> name;
    name.format("IMG_chr_fvicon%02dlike@01", 1);
    {
      ui::UIObjectAcc like(acc.searchChild(name.c_str()));
      unknown011(like, GfMenuObjUtil::getFavoriteStat(OBJECT_TYPE_PC, driver, FAVORITE_UNKNOWN_0) == 0 && category == GfDataDriver::getFavorite(driver, FAVORITE_UNKNOWN_0), 0);
    }
    name.format("IMG_chr_fvicon%02dlike@01", 2);
    {
      ui::UIObjectAcc like(acc.searchChild(name.c_str()));
      unknown011(like, GfMenuObjUtil::getFavoriteStat(OBJECT_TYPE_PC, driver, FAVORITE_UNKNOWN_1) == 0 && category == GfDataDriver::getFavorite(driver, FAVORITE_UNKNOWN_1), 0);
    }
    name.format("IMG_chr_fviconit%02dlike@01", 1);
    {
      ui::UIObjectAcc like(acc.searchChild(name.c_str()));
      unknown011(like, GfMenuObjUtil::getFavoriteStat(OBJECT_TYPE_PC, driver, FAVORITE_UNKNOWN_2) == 0 && item == GfDataDriver::getFavorite(driver, FAVORITE_UNKNOWN_2), 1);
    }
    name.format("IMG_chr_fviconit%02dlike@01", 2);
    {
      ui::UIObjectAcc like(acc.searchChild(name.c_str()));
      unknown011(like, GfMenuObjUtil::getFavoriteStat(OBJECT_TYPE_PC, driver, FAVORITE_UNKNOWN_3) == 0 && item == GfDataDriver::getFavorite(driver, FAVORITE_UNKNOWN_3), 1);
    }
    name.format("IMG_chr_fviconit%02dlike2@01", 1);
    {
      ui::UIObjectAcc like(acc.searchChild(name.c_str()));
      like.setDisp(false);
    }
    name.format("IMG_chr_fviconit%02dlike2@01", 2);
    {
      ui::UIObjectAcc like(acc.searchChild(name.c_str()));
      like.setDisp(false);
    }
    // Unused, but the game builds it here (ruling 5): without it 568 instructions and the frame differs from +0x0.
    DataParamAcc param(OBJECT_TYPE_PC, driver, GIMMICK_TYPE_UNKNOWN_0);
    // The loop keeps three induction values (0x71004ba964, 0x71004ba9bc): the slot x22 from 2 with the exit compare `cmp x22, #5`, the index x25 and the
    // 8 byte list offset x23. Both counters are 64 bit (`mov x25, xzr`, `add x25, x25, #1`) and the size test is the 64 bit `sub x21, x22, #2`. `number`
    // is the slot of the else arm: the slot itself on the out of range edge (`mov x26, x22`, 0x71004ba9e0) and `i + 2` on the blade == 0 edge
    // (`add x26, x25, #2`, 0x71004bac68), while the blade arm and the tail use `i + 2` directly (`mov w26, w22`, 0x71004bac60). One value for every use
    // (`u32 slot = i + 2`) gives 563 instructions with the single index counter and `cmp #3`. The `static_cast<u32>` narrow the 64 bit values to the 32 bit format argument: passed as
    // `u64` the format calls give 563 instructions (`i + 2`) and 4 differing lines (`number`).
    u64 i = 0;
    for (u32 slot = 2; slot < 5; i++, slot++) {
      u32 blade = 0;
      u64 number = slot;
      if (i < m_menuObjPouch2->m_menuBladeList->getSize()) {
        blade = m_menuObjPouch2->m_menuBladeList->getContents(i).unknown00;
        number = i + 2;
      }
      if (blade != 0) {
        name.format("IMG_chr_fvicon%02dlike@%02d", 1, static_cast<u32>(i + 2));
        {
          ui::UIObjectAcc like(acc.searchChild(name.c_str()));
          unknown011(like, GfMenuObjUtil::getFavoriteStat(OBJECT_TYPE_BLADE, blade, FAVORITE_UNKNOWN_0) == 0 && category == GfDataBlade::getFavorite(blade, FAVORITE_UNKNOWN_0), 0);
        }
        name.format("IMG_chr_fvicon%02dlike@%02d", 2, static_cast<u32>(i + 2));
        {
          ui::UIObjectAcc like(acc.searchChild(name.c_str()));
          unknown011(like, GfMenuObjUtil::getFavoriteStat(OBJECT_TYPE_BLADE, blade, FAVORITE_UNKNOWN_1) == 0 && category == GfDataBlade::getFavorite(blade, FAVORITE_UNKNOWN_1), 0);
        }
        name.format("IMG_chr_fviconit%02dlike@%02d", 1, static_cast<u32>(i + 2));
        {
          ui::UIObjectAcc like(acc.searchChild(name.c_str()));
          unknown011(like, GfMenuObjUtil::getFavoriteStat(OBJECT_TYPE_BLADE, blade, FAVORITE_UNKNOWN_2) == 0 && item == GfDataBlade::getFavorite(blade, FAVORITE_UNKNOWN_2), 1);
        }
        name.format("IMG_chr_fviconit%02dlike@%02d", 2, static_cast<u32>(i + 2));
        {
          ui::UIObjectAcc like(acc.searchChild(name.c_str()));
          unknown011(like, GfMenuObjUtil::getFavoriteStat(OBJECT_TYPE_BLADE, blade, FAVORITE_UNKNOWN_3) == 0 && item == GfDataBlade::getFavorite(blade, FAVORITE_UNKNOWN_3), 1);
        }
      } else {
        name.format("IMG_chr_fvicon%02dlike@%02d", 1, static_cast<u32>(number));
        {
          ui::UIObjectAcc like(acc.searchChild(name.c_str()));
          unknown010(like, FAVORITE_UNKNOWN_0);
        }
        name.format("IMG_chr_fvicon%02dlike@%02d", 2, static_cast<u32>(number));
        {
          ui::UIObjectAcc like(acc.searchChild(name.c_str()));
          unknown010(like, FAVORITE_UNKNOWN_1);
        }
        name.format("IMG_chr_fviconit%02dlike@%02d", 1, static_cast<u32>(number));
        {
          ui::UIObjectAcc like(acc.searchChild(name.c_str()));
          unknown010(like, FAVORITE_UNKNOWN_2);
        }
        name.format("IMG_chr_fviconit%02dlike@%02d", 2, static_cast<u32>(number));
        {
          ui::UIObjectAcc like(acc.searchChild(name.c_str()));
          unknown010(like, FAVORITE_UNKNOWN_3);
        }
      }
      name.format("IMG_chr_fviconit%02dlike2@%02d", 1, static_cast<u32>(i + 2));
      {
        ui::UIObjectAcc like(acc.searchChild(name.c_str()));
        like.setDisp(false);
      }
      name.format("IMG_chr_fviconit%02dlike2@%02d", 2, static_cast<u32>(i + 2));
      {
        ui::UIObjectAcc like(acc.searchChild(name.c_str()));
        like.setDisp(false);
      }
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjPouch2::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setFadeIn(handle, 0);
    break;
  case 3:
    if (event.unknown08 == 2) {
      acc.setDisp(false);
      acc.setTerm();
      GfMenuObjCharSelect::returnSubMenu();
      GfMenuObject::returnFSSubLayer(handle, 2);
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    setFadeOut(handle, 0);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjPouch2::ResultListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(m_menuObjPouch2->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupResult(acc);
    acc.setDisp(false);
    GfMenuObject::disableInput(handle);
    break;
  case 8:
    if (event.unknown0c == 0xb || event.unknown0c == 2) {
      unknown164(handle, GfMenuTypes::unknown003_258);
      unknown001(owner.searchChild(m_menuObjPouch2->unknown64 == 0 ? "LAY_eqp_fevitem" : "LAY_fvstock_fevitem"), GfMenuTypes::unknown003_257, 0, 0);
      if (m_menuObjPouch2->unknown64 == 0) {
        GfMenuObjCharSelect::dispOnChar(0);
      } else {
        setFadeIn(owner.searchChild("LAY_fvstock_fevitem"), 1);
        setFadeIn(owner.searchChild("LAY_chr_fevinfo"), 2);
      }
      GfMenuObjUtil::playSECommonCloseSubMenu();
    }
    break;
  case GfMenuTypes::unknown003_257:
    refreshResult(acc, m_menuObjPouch2->m_menuBladeList);
    GfMenuObjOperationInfo::setGuideText(0x22, 0);
    GfMenuObjOperationInfo::add(handle, 0, 0, 0);
    setFadeIn(handle, 1);
    GfMenuObject::enableInput(handle);
    break;
  case GfMenuTypes::unknown003_258:
    GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
    setFadeOut(handle, 1);
    GfMenuObject::disableInput(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjPouch2>(const mm::mtl::Delegate<bool()> *);
