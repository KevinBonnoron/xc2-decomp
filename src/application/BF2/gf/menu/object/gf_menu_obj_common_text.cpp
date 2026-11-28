#include "gf/menu/object/gf_menu_obj_common_text.h"

#include "bdat.h"
#include "gf/data/gf_bdat_cond.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/adapter/gf_menu_mercenaries_adapter.h"
#include "gf/menu/adapter/gf_menu_mission_adapter.h"
#include "gf/menu/adapter/gf_menu_reference_adapter.h"
#include "gf/menu/adapter/gf_menu_zone_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_common_window_param.h"
#include "gf/menu/gf_menu_item_util.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/input/ui_input_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/plugin/ui_object_sync_plugin.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"
#include "ui/ui_util.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x64;

constexpr u32 CONDITION_PT_CATEGORY_UNKNOWN_0 = 0; // Inferred role: party condition category listing the characters; original name unknown.
constexpr u32 CONDITION_PT_CATEGORY_UNKNOWN_6 = 6; // Inferred role: party condition category naming a blade; original name unknown.
constexpr u32 CONDITION_UNKNOWN_3 = 3;             // Inferred role: characters of a party condition; original name unknown.

// Inferred role: docks the left and right cursor images beside a layout; original name unknown.
static void unknown002(ui::UIObjectAcc &acc, const ui::UIObjectAcc &layout, const char *left, const char *right) {
  GfMenuObjUtil::setDockPos(acc.searchChild(left), layout.unknown10, 1, true);
  GfMenuObjUtil::addPos(acc.searchChild(left), -10, 0);
  GfMenuObjUtil::setDockPos(acc.searchChild(right), layout.unknown10, 2, true);
  GfMenuObjUtil::addPos(acc.searchChild(right), 10, 0);
}

// Inferred role: disables the input of a dialog and hides it; original name unknown.
static void unknown003(ui::UIObjectAcc &acc) {
  GfMenuObject::disableInput(acc.unknown10);
  acc.setDisp(false);
  acc.setSuspend(true);
}

// Inferred role: hides one part of a list item and shows the other; original name unknown.
static void unknown004(ui::UIObjectAcc &acc, mm::mtl::FixStr<32> &name, u32 number, const char *hide, const char *show) {
  name.format(hide, number);
  acc.setDispChild(false, name.c_str());
  name.format(show, number);
  acc.setDispChild(true, name.c_str());
}

// Inferred role: fits the window image around a layout; original name unknown. Two users (MerListener, KizunaListener; 588 and 449 instructions with the helper, 0 differing lines).
static void unknown005(ui::UIObjectAcc &acc, const char *image, const char *layout) {
  GfMenuObjUtil::FitOption option;
  option.unknown00 = true;
  option.unknown01 = true;
  GfMenuObjUtil::createFitPlugin(acc.searchChild(image), acc.searchChild(layout), 0, 0, option);
}

// Inferred role: reads the layout rectangles of two neighbouring items; original name unknown.
static void unknown006(ui::UIObjectAcc &acc, const char *first, const char *second, mm::Rect<s16> &rect, mm::Rect<s16> &next) {
  acc.getLayoutRect(first, rect);
  acc.getLayoutRect(second, next);
}

// Inferred role: fills the fade parameter shared by the dialog fades; original name unknown.
static void unknown007(GfMenuObjUtil::CtrlParam &param, int type) {
  param.unknown00 = 0.25f;
  param.unknown04 = type;
  param.unknown08 = type;
}

// Inferred role: plays the cursor sound when the selection moves from a previous entry; original name unknown.
static void unknown008(u32 index, u32 previous) {
  if (previous != 0xffffffff && index != previous) {
    GfMenuObjUtil::playSECommonCursor();
  }
}

// Inferred role: enables the input of a dialog when it opens and tells whether it has closed; original name unknown.
static bool unknown009(ui::UIObjectAcc &acc, const ui::EventData &event) {
  if (event.unknown08 == 1) {
    GfMenuObject::enableInput(acc.unknown10);
    return false;
  }
  return event.unknown08 == 2;
}

GfMenuItemList *GfMenuObjCommonText::s_pItemList;
GfMenuIDList *GfMenuObjCommonText::s_pSubMenuIDList;
GfMenuDriverList *GfMenuObjCommonText::s_pChangeDrList;

// The game's constructor (0x710043bb30) does not store the member at 0x60, which the destructor releases.
GfMenuObjCommonText::GfMenuObjCommonText(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), m_menuBladeList(nullptr), unknown58(nullptr), unknown68(nullptr), unknown70(nullptr), unknown88(0) {
  unknown40 = unknown160();
  unknown40->unknown162(0);
  unknown48 = unknown160();
  unknown48->unknown162(0);
  m_menuBladeList = GfMenuBladeList::create();
  unknown58 = GfMenuDriverList::create();
  s_pItemList = GfMenuItemList::create();
  s_pSubMenuIDList = GfMenuIDList::create();
  ui::UIListInfoBase::SetupParam subMenuSetup;
  subMenuSetup.unknown08 = 3;
  s_pSubMenuIDList->setup(getAllocator(ALLOCATOR_UNKNOWN_0), subMenuSetup);
  s_pChangeDrList = GfMenuDriverList::create();
  unknown78 = unknown160();
  unknown78->unknown162(0);
  unknown80 = unknown160();
  unknown80->unknown162(0);
}

GfMenuObjCommonText::~GfMenuObjCommonText() {
  unknown40 = nullptr;
  unknown48 = nullptr;
  mm::mtl::safeRelease(unknown70);
  mm::mtl::safeRelease(unknown68);
  mm::mtl::safeRelease(s_pChangeDrList);
  mm::mtl::safeRelease(s_pSubMenuIDList);
  mm::mtl::safeRelease(s_pItemList);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown60);
  mm::mtl::safeRelease(m_menuBladeList);
  mm::mtl::safeRelease(unknown58);
  mm::mtl::safeRelease(unknown28);
  unknown78 = nullptr;
  unknown80 = nullptr;
}

void GfMenuObjCommonText::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 219 as in the original file: it is the line argument of operator new.
#line 219
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(unknown001, main);
  u32 dialog = acc.searchChild("LAY_dialog");
// __LINE__ must be 225 as in the original file: it is the line argument of operator new.
#line 225
  DialogListener *dialogListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DialogListener(this);
  dialogListener->addRef();
  ui::UIEventManager::get()->registObjectListener(dialog, dialogListener);
  if (dialogListener != nullptr) {
    dialogListener->release();
  }
  u32 error = acc.searchChild("LAY_error");
// __LINE__ must be 229 as in the original file: it is the line argument of operator new.
#line 229
  ErrorListener *errorListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ErrorListener(this);
  errorListener->addRef();
  ui::UIEventManager::get()->registObjectListener(error, errorListener);
  if (errorListener != nullptr) {
    errorListener->release();
  }
  u32 mer = acc.searchChild("LAY_dialog_mer");
// __LINE__ must be 233 as in the original file: it is the line argument of operator new.
#line 233
  MerListener *merListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MerListener(this);
  merListener->addRef();
  ui::UIEventManager::get()->registObjectListener(mer, merListener);
  if (merListener != nullptr) {
    merListener->release();
  }
  u32 kizuna = acc.searchChild("LAY_dialog_kizuna");
// __LINE__ must be 237 as in the original file: it is the line argument of operator new.
#line 237
  KizunaListener *kizunaListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) KizunaListener(this);
  kizunaListener->addRef();
  ui::UIEventManager::get()->registObjectListener(kizuna, kizunaListener);
  if (kizunaListener != nullptr) {
    kizunaListener->release();
  }
  GfMenuAdapterManager::beginCategory(3);
  {
    ui::UIObjectAcc getItem(acc.unknown10, "LAY_get_item");
    u32 count = getItem.countChild("LAY_get_item@%02d", 1);
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < count; i++) {
      name.format("TXT_get_item_name@%02d", i + 1);
      GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(getItem.searchChild(name.c_str()), 0, s_pItemList, i, false);
      if (adapter != nullptr) {
        name.format("LAY_get_item@%02d", i + 1);
        adapter->unknown24 = getItem.searchChild(name.c_str());
      }
      name.format("TXT_get_item_num@%02d", i + 1);
      GfMenuItemAdapter::createFromList(getItem.searchChild(name.c_str()), 3, s_pItemList, i, false);
      name.format("IMG_get_item_icon@%02d", i + 1);
      GfMenuItemAdapter *icon = GfMenuItemAdapter::createFromList(getItem.searchChild(name.c_str()), 2, s_pItemList, i, false);
      if (icon != nullptr) {
        icon->setDispAlphaMode(true);
      }
    }
    ui::UIListInfoBase::SetupParam itemSetup;
    itemSetup.unknown08 = count;
    s_pItemList->setup(getAllocator(ALLOCATOR_UNKNOWN_0), itemSetup);
// __LINE__ must be 277 as in the original file: it is the line argument of operator new.
#line 277
    GetItemListener *getItemListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GetItemListener(this);
    getItemListener->addRef();
    ui::UIEventManager::get()->registObjectListener(getItem.unknown10, getItemListener);
    if (getItemListener != nullptr) {
      getItemListener->release();
    }
  }
  {
    ui::UIObjectAcc select(acc.unknown10, "LAY_select");
    // The scopes of this section and of the driver change one follow the game's stack layout (frame of 224 bytes, the fit option and the dock offset of 0x710043cccc share the slot at sp). Each is
    // needed: without the first scope of this section the frame is 240 bytes, without the create parameter's 240, without the cursor setting's 256 (and without the fit option's the option moves to
    // sp + 80).
    {
      mm::mtl::FixStr<32> name;
      u32 count = select.countChild("LAY_sel_item@%02d", 1);
      ui::UIListInfoBase::SetupParam subMenuSetup;
      subMenuSetup.unknown08 = count;
      s_pSubMenuIDList->setup(getAllocator(ALLOCATOR_UNKNOWN_0), subMenuSetup);
      for (u32 i = 0; i < count; i++) {
        name.format("TXT_sel_item_name@%02d", i + 1);
        GfMenuItemAdapter::createFromList(select.searchChild(name.c_str()), 0, s_pItemList, i, false);
        name.format("TXT_sel_item_num@%02d", i + 1);
        GfMenuItemAdapter::createFromList(select.searchChild(name.c_str()), 3, s_pItemList, i, false);
      }
    }
    {
      GfMenuObjUtil::FitOption option;
      option.unknown01 = true;
      GfMenuObjUtil::createFitPlugin(select.searchChild("IMG_select_item_bg"), select.searchChild("LAY_sel_item"), 0, 0x1c, option);
    }
    GfMenuObjUtil::createDockPlugin(select.searchChild("IMG_select_item_line_down"), select.searchChild("IMG_select_item_bg"), 3, mm::Pnt<s16>(0, -0x17), 0);
// __LINE__ must be 323 as in the original file: it is the line argument of operator new.
#line 323
    SelectListener *selectListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SelectListener(this);
    selectListener->addRef();
    ui::UIEventManager::get()->registObjectListener(select.unknown10, selectListener);
    if (selectListener != nullptr) {
      selectListener->release();
    }
  }
  {
    ui::UIObjectAcc drChange(acc.unknown10, "LAY_dr_change");
    mm::mtl::FixStr<32> name;
    {
      ui::UISelectObjList::CreateParam createParam;
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      unknown68 = ui::UISelectObjList::create(createParam);
    }
    unknown68->pickupObject(drChange.unknown10, "LAY_dr_change@%02d", 1);
    {
      ui::UICtrlCursorSelect::CursorSetting setting;
      setting.setType(0);
      setting.unknown18 = 0;
      unknown70 = ui::UICtrlCursorSelect::create(drChange.searchChild("IMG_dr_change_cursor"), setting, unknown68);
    }
    ui::UIListInfoBase::SetupParam driverSetup;
    driverSetup.unknown08 = unknown68->getSize();
    s_pChangeDrList->setup(getAllocator(ALLOCATOR_UNKNOWN_0), driverSetup);
    for (u32 i = 0; i < unknown68->getSize(); i++) {
      name.format("IMG_dr_change_face@%02d", i + 1);
      GfMenuCharDataAdapter *adapter = GfMenuCharDataAdapter::createFromDriverList(drChange.searchChild(name.c_str()), 3, s_pChangeDrList, i, false);
      if (adapter != nullptr) {
        name.format("LAY_dr_change@%02d", i + 1);
        adapter->unknown24 = drChange.searchChild(name.c_str());
      }
    }
// __LINE__ must be 373 as in the original file: it is the line argument of operator new.
#line 373
    DrChangeListener *drChangeListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DrChangeListener(this);
    drChangeListener->addRef();
    ui::UIEventManager::get()->registObjectListener(drChange.unknown10, drChangeListener);
    if (drChangeListener != nullptr) {
      drChangeListener->release();
    }
  }
  {
    ui::UIObjectAcc ownerChange(acc.unknown10, "LAY_owner_change");
    GfMenuCharDataAdapter::createFromReferenceDriver(ownerChange.searchChild("IMG_owner_ch_before_face"), 3, 4, false);
    GfMenuCharDataAdapter::createFromReferenceDriver(ownerChange.searchChild("IMG_owner_ch_after_face"), 3, 5, false);
// __LINE__ must be 387 as in the original file: it is the line argument of operator new.
#line 387
    OwnerChangeListener *ownerChangeListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) OwnerChangeListener(this);
    ownerChangeListener->addRef();
    ui::UIEventManager::get()->registObjectListener(ownerChange.unknown10, ownerChangeListener);
    if (ownerChangeListener != nullptr) {
      ownerChangeListener->release();
    }
  }
  GfMenuAdapterManager::endCategory();
  u32 numSelect = acc.searchChild("LAY_num_select");
// __LINE__ must be 394 as in the original file: it is the line argument of operator new.
#line 394
  NumSelectListener *numSelectListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) NumSelectListener(this);
  numSelectListener->addRef();
  ui::UIEventManager::get()->registObjectListener(numSelect, numSelectListener);
  if (numSelectListener != nullptr) {
    numSelectListener->release();
  }
  GfMenuObject::initialize();
}

void GfMenuObjCommonText::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCommonText::update() { GfMenuObject::update(); }

void GfMenuObjCommonText::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown10 = 0xff;
    break;
  case GfMenuTypes::unknown003_33: {
    GfMenuAdapterManager::addActiveCategory(3);
    unknown10 = event.unknown16;
    u32 window;
    switch (unknown10) {
    case 0:
      window = acc.searchChild("LAY_dialog");
      break;
    case 1:
      window = acc.searchChild("LAY_error");
      break;
    case 2:
      window = acc.searchChild("LAY_dialog_mer");
      break;
    case 3:
      window = acc.searchChild("LAY_dialog_kizuna");
      break;
    case 4:
      window = acc.searchChild("LAY_get_item");
      break;
    case 5:
      window = acc.searchChild("LAY_select");
      break;
    case 6:
      window = acc.searchChild("LAY_dr_change");
      break;
    case 7:
      window = acc.searchChild("LAY_owner_change");
      break;
    case 8:
      window = acc.searchChild("LAY_num_select");
      break;
    default:
      GfMenuObject::termCallContext(acc.unknown10);
      return;
    }
    if (window == 0) {
      return;
    }
    if (unknown10 == 5) {
      GfMenuObject::sendEvent(window, event, 0.06666667f);
    } else {
      GfMenuObject::sendEvent(window, event, 0.0f);
    }
    ui::UIObjectAcc(window).setSuspend(false);
    ui::UIInputManager *inputManager = ui::UIInputManager::get();
    unknown0c = inputManager->unknown20;
    inputManager->unknown20 = ui::UIUtil::getGroupPriority(4);
    GfMenuObjUtil::playSE(9);
    break;
  }
  case GfMenuTypes::unknown003_34: {
    // The game holds the window lookup of event 0x21 a second time here (its own jump table at 0x7100f6e0a8), with a default that only leaves.
    u32 window;
    switch (unknown10) {
    case 0:
      window = acc.searchChild("LAY_dialog");
      break;
    case 1:
      window = acc.searchChild("LAY_error");
      break;
    case 2:
      window = acc.searchChild("LAY_dialog_mer");
      break;
    case 3:
      window = acc.searchChild("LAY_dialog_kizuna");
      break;
    case 4:
      window = acc.searchChild("LAY_get_item");
      break;
    case 5:
      window = acc.searchChild("LAY_select");
      break;
    case 6:
      window = acc.searchChild("LAY_dr_change");
      break;
    case 7:
      window = acc.searchChild("LAY_owner_change");
      break;
    case 8:
      window = acc.searchChild("LAY_num_select");
      break;
    default:
      return;
    }
    if (window == 0) {
      return;
    }
    GfMenuObject::sendEvent(window, event, 0.0f);
    ui::UIInputManager *inputManager = ui::UIInputManager::get();
    inputManager->unknown20 = unknown0c;
    GfMenuObject::termCallContext(handle);
    unknown10 = 0xff;
    GfMenuAdapterManager::delActiveCategory(3);
    break;
  }
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjCommonText::setupDialog(u32 handle) {
  GfMenuObjUtil::FitOption option;
  option.unknown00 = true;
  option.unknown01 = true;
  u32 text = ui::UIUtil::searchChild(handle, "LAY_dialog_text");
  GfMenuObjUtil::createFitPlugin(ui::UIUtil::searchChild(handle, "IMG_dialog_win@01"), text, 0, 0, option);
  GfMenuObjUtil::createFitPlugin(ui::UIUtil::searchChild(handle, "IMG_dialog_win@02"), text, 0, 0, option);
  u32 cursor = ui::UIUtil::searchChild(handle, "LAY_dialog_cursor");
  ui::UIObjectSyncPlugin *plugin;
  {
    ui::UIObjectAcc acc(cursor);
    plugin = ui::UIObjectSyncPlugin::create(acc.searchSibiling("LAY_dialog_cursor_base"));
  }
  plugin->setTargetObject(cursor);
  plugin->setTargetFlag(0x3e);
  if (plugin != nullptr) {
    plugin->release();
  }
}

void GfMenuObjCommonText::sendEvent(u32 handle, u32 type, u32 param, f32 delay) { unknown140(handle, type, param, delay); }

int GfMenuObjCommonText::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjCommonText::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjCommonText::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjCommonText::open(GfMenuCallContext *context, const MenuCommonWindowParam &param) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (!isTerm) {
      startCallContext(context, unknown001, handle);
      u16 title = 0xffff;
      if (param.unknown00 != nullptr) {
        ui::UIStr str(param.unknown00, param.unknown08);
        title = registString(str);
      }
      u16 text = 0xffff;
      if (param.unknown10 != nullptr) {
        ui::UIStr str(param.unknown10, param.unknown18);
        text = registString(str);
      }
      u16 ok = 0xffff;
      if (param.unknown20 != nullptr) {
        ui::UIStr str(param.unknown20, param.unknown28);
        ok = registString(str);
      }
      u16 cancel = 0xffff;
      if (param.unknown30 != nullptr) {
        ui::UIStr str(param.unknown30, param.unknown38);
        cancel = registString(str);
      }
      ui::EventData event;
      event.unknown00 = 0x21;
      event.unknown08_u16 = title;
      event.unknown0a = text;
      event.unknown0c_u16 = ok;
      event.unknown0e = cancel;
      event.unknown10_u16 = param.unknown3c;
      event.unknown12 = param.unknown40 != 0;
      event.unknown14_u16 = param.unknown44;
      event.unknown16 = param.unknown48;
      GfMenuObject::sendEvent(handle, event, 0.0f);
    }
  }
}

void GfMenuObjCommonText::open(GfMenuCallContext *context, u32 window, u32 param) {
  u8 *windowBdat = GfDataBdat::getFP(BDAT_MNU_CMN_WINDOW);
  if (windowBdat != nullptr) {
    u8 *textBdat = GfDataBdat::getFP(BDAT_MENU_CMNWINDOW);
    if (textBdat != nullptr) {
      MenuCommonWindowParam windowParam;
      u16 title = Bdat::getVal(windowBdat, "title", window).valueU16;
      if (title != 0) {
        windowParam.unknown00 = textBdat;
        windowParam.unknown08 = title;
      }
      u16 text = Bdat::getVal(windowBdat, "text", window).valueU16;
      if (text != 0) {
        windowParam.unknown10 = textBdat;
        windowParam.unknown18 = text;
      }
      u16 ok = Bdat::getVal(windowBdat, "select_ok_txt", window).valueU16;
      if (ok != 0) {
        windowParam.unknown20 = textBdat;
        windowParam.unknown28 = ok;
      }
      u16 cancel = Bdat::getVal(windowBdat, "select_cancel_txt", window).valueU16;
      if (cancel != 0) {
        windowParam.unknown30 = textBdat;
        windowParam.unknown38 = cancel;
      }
      windowParam.unknown3c = Bdat::getVal(windowBdat, "type", window).valueU8;
      windowParam.unknown40 = Bdat::getVal(windowBdat, "select", window).valueU8;
      windowParam.unknown44 = param;
      windowParam.unknown48 = 0;
      open(context, windowParam);
    }
  }
}

void GfMenuObjCommonText::openItem(GfMenuCallContext *context, u32 window, u32 item) {
  u8 *windowBdat = GfDataBdat::getFP(BDAT_MNU_CMN_WINDOW);
  if (windowBdat != nullptr) {
    u8 *textBdat = GfDataBdat::getFP(BDAT_MENU_CMNWINDOW);
    if (textBdat != nullptr) {
      MenuCommonWindowParam windowParam;
      windowParam.unknown00 = textBdat;
      windowParam.unknown08 = Bdat::getVal(windowBdat, "title", window).valueU16;
      {
        u8 itemType = GfDataItem::getItemType(item);
        ui::UIStr name;
        GfMenuItemUtil::getItemName(itemType, item, name);
        windowParam.unknown10 = name.getMsgFP();
        windowParam.unknown18 = name.getMsgID();
      }
      windowParam.unknown3c = Bdat::getVal(windowBdat, "type", window).valueU8;
      windowParam.unknown40 = Bdat::getVal(windowBdat, "select", window).valueU8;
      windowParam.unknown48 = 0;
      open(context, windowParam);
    }
  }
}

void GfMenuObjCommonText::openError(GfMenuCallContext *context, u32 error, u32 param) {
  u8 *errorBdat = GfDataBdat::getFP(BDAT_MNU_MSG_ERROR_INFO);
  if (errorBdat != nullptr) {
    u8 *textBdat = GfDataBdat::getFP(BDAT_MENU_ERROR_INFO_MS);
    if (textBdat != nullptr) {
      MenuCommonWindowParam windowParam;
      u16 name = Bdat::getVal(errorBdat, "name", error).valueU16;
      if (name != 0) {
        windowParam.unknown10 = textBdat;
        windowParam.unknown18 = name;
      }
      windowParam.unknown44 = param;
      windowParam.unknown48 = 1;
      open(context, windowParam);
    }
  }
}

void GfMenuObjCommonText::openMissionStop(GfMenuCallContext *context, u32 mission, u32 param) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      u8 *windowBdat = GfDataBdat::getFP(BDAT_MNU_CMN_WINDOW);
      if (windowBdat != nullptr) {
        u16 text = Bdat::getVal(windowBdat, "text", mission).valueU16;
        if (text == 0) {
          context->abort();
        } else {
          u16 textId;
          {
            ui::UIStr str(GfDataBdat::getFP(BDAT_MENU_CMNWINDOW), text);
            textId = registString(str);
          }
          ui::EventData event;
          event.unknown00 = 0x21;
          event.unknown08 = param;
          event.unknown0c_u16 = textId;
          event.unknown0e = Bdat::getVal(windowBdat, "type", mission).valueU8;
          event.unknown10_u16 = Bdat::getVal(windowBdat, "select", mission).valueU8;
          event.unknown16 = 2;
          GfMenuObject::sendEvent(handle, event, 0.0f);
          startCallContext(context, unknown001, handle);
        }
      }
    }
  }
}

void GfMenuObjCommonText::openKizunaDialog(GfMenuCallContext *context, const OpenKizunaParam &param) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm && GfDataBdat::getFP(BDAT_MNU_CMN_WINDOW) != nullptr) {
      u16 textId;
      {
        ui::UIStr str(param.unknown00, param.unknown08);
        textId = registString(str);
      }
      ui::EventData event;
      event.unknown0c = 0;
      event.unknown00 = 0x21;
      event.unknown08 = param.unknown0c;
      event.unknown0c_u16 = textId;
      event.unknown16 = 3;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::openGetItem(GfMenuCallContext *context, const GfMenuItemList *items) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      s_pItemList->clear();
      for (u32 i = 0; i < items->getSize(); i++) {
        s_pItemList->addContents(items->getContents(i));
      }
      ui::EventData event;
      event.unknown00 = 0x21;
      event.unknown16 = 4;
      GfMenuObject::sendEvent(handle, event, 0.033333335f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::openSubMenu(GfMenuCallContext *context, const GfMenuIDList *list) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      s_pSubMenuIDList->clear();
      for (u32 i = 0; i < list->getSize(); i++) {
        s_pSubMenuIDList->addContents(list->getContents(i));
      }
      ui::EventData event;
      event.unknown00 = 0x21;
      event.unknown16 = 5;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::openSelectItem(GfMenuCallContext *context, const GfMenuItemList *list) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      s_pItemList->clear();
      for (u32 i = 0; i < list->getSize(); i++) {
        s_pItemList->addContents(list->getContents(i));
      }
      ui::EventData event;
      event.unknown00 = 0x21;
      event.unknown08 = 1;
      event.unknown16 = 5;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::openDrChange(GfMenuCallContext *context, u32 driver, const GfMenuDriverList *list) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      s_pChangeDrList->clear();
      for (u32 i = 0; i < list->getSize(); i++) {
        s_pChangeDrList->addContents(list->getContents(i));
      }
      s_pChangeDrList->setIndex(0);
      GfMenuReference::setReferenceDriverID(4, driver);
      ui::EventData event;
      event.unknown00 = 0x21;
      event.unknown16 = 6;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::openOwnerChange(GfMenuCallContext *context, u32 driver, u32 other) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      GfMenuReference::setReferenceDriverID(4, driver);
      GfMenuReference::setReferenceDriverID(5, other);
      ui::EventData event;
      event.unknown08_u16 = 0;
      event.unknown00 = 0x21;
      event.unknown16 = 7;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::openNumSelect(GfMenuCallContext *context, const OpenNumSelectParam &param) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      ui::EventData event;
      event.unknown0c = 0;
      event.unknown00 = 0x21;
      event.unknown08_u16 = param.unknown00;
      event.unknown0a = param.unknown04;
      event.unknown0c_u16 = param.unknown08;
      event.unknown10 = param.unknown0c;
      event.unknown16 = 8;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::ErrorListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(m_menuObjCommonText->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setSuspend(true);
    unknown18 = 0;
    break;
  case 3:
    if (event.unknown08 == 0) {
      return;
    }
    if (event.unknown08 == 2 && unknown18 == 0) {
      acc.setSuspend(true);
    }
    break;
  case 8:
    GfMenuObject::addResultCallContext(owner.searchChild("LAY_main"), 0, 0);
    close();
    break;
  case GfMenuTypes::unknown003_33: {
    u16 text = event.unknown0a;
    s16 bottom = event.unknown14_u16;
    if (text != 0xffff) {
      GfMenuObjUtil::setChildText(handle, "TXT_error", text);
    }
    setFadeIn(handle);
    GfMenuObject::enableInput(handle);
    mm::Rect<s16> rect;
    acc.getLayoutRect(bottom == 0 ? "error_dialog_top" : "error_dialog_bottom", rect);
    mm::Pnt<s16> center(rect.x + rect.width / 2, rect.y + rect.height / 2);
    acc.setPosCenter(center);
    unknown18 = 1;
    break;
  }
  case GfMenuTypes::unknown003_34: {
    setFadeOut(handle);
    GfMenuObject::disableInput(handle);
    unknown18 = 0;
    break;
  }
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjCommonText::MerListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case GfMenuTypes::unknown003_34:
    GfMenuObjUtil::setCommonFadeOut(acc.unknown10, 2, 0);
    m_menuObjCommonText->unknown38->setDisp(false);
    GfMenuObject::disableInput(acc.unknown10);
    unknown18 = 0;
    break;
  case 1: {
    GfMenuAdapterManager::beginCategory(3);
    GfMenuZoneAdapter::createFromReference(acc.searchChild("IMG_dialog_mer_info_flag"), 2, m_menuObjCommonText->unknown48, false);
    GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_dialog_mer_info_bl_face"), 3, 4, false);
    GfMenuMercenariesAdapter::createFromReferenceBlade(acc.searchChild("TXT_dialog_mer_info_unit_name"), 0, 4, false);
    GfMenuMissionAdapter::createFromReference(acc.searchChild("TXT_dialog_mer_info_mis_name"), 0, m_menuObjCommonText->unknown40, false);
    GfMenuMissionAdapter::createFromReference(acc.searchChild("TXT_dialog_mer_info_time"), 4, m_menuObjCommonText->unknown40, true);
    GfMenuObjUtil::createSyncPlugin(acc.searchChild("TXT_dialog_mer_info_time_inf"), acc.searchChild("TXT_dialog_mer_info_time"), 0x40);
    GfMenuAdapterManager::endCategory();
    unknown005(acc, "IMG_dialog_mer_win", "LAY_dialog_mer_main");
    // The scope of the list parameter is the game's: without it the function differs on 41 lines (measured).
    {
      ui::UISelectObjList::CreateParam createParam;
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      m_menuObjCommonText->unknown30 = ui::UISelectObjList::create(createParam);
    }
    ui::UICtrlCursorSelect::CursorSetting setting;
    setting.setType(0);
    setting.unknown18 = 0;
    setting.unknown20 = false;
    m_menuObjCommonText->unknown38 = ui::UICtrlCursorSelect::create(acc.searchChild("LAY_dialog_mer_cursor"), setting, m_menuObjCommonText->unknown30);
    GfMenuObjUtil::createSyncPlugin(acc.searchChild("LAY_dialog_mer_cursor_base"), acc.searchChild("LAY_dialog_mer_cursor"), 2);
    acc.setDisp(false);
    acc.setSuspend(true);
    unknown18 = 0;
    break;
  }
  case 3:
    if (event.unknown08 == 0) {
      break;
    }
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
    } else {
      GfGameMercenaries::stopMissionTime(false);
      GfMenuObject::termCallContext(acc.getParentHandle());
      if (unknown18 == 0) {
        acc.setSuspend(true);
      }
    }
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 6:
    if (event.unknown08 != 0xffffffff) {
      // The game reads the event words into registers before the call (ruling 2): without the local of index 6 lines differ, without that of previous 3 (measured).
      u32 index = event.unknown08;
      u32 previous = event.unknown0c;
      m_menuObjCommonText->unknown30->setIndex(index);
      unknown008(index, previous);
    }
    break;
  case 8: {
    u32 input = event.unknown0c;
    if (input == 1) {
      // The game reads the selection before the call to getParentHandle (ruling 2; 2 differing lines without the local, measured).
      int selected = event.unknown08;
      GfMenuObject::addResultCallContext(acc.getParentHandle(), selected != 0, 0);
      GfMenuObjCommonText::close();
    } else if (input == 2) {
      GfMenuObject::addResultCallContext(acc.getParentHandle(), 1, 0);
      GfMenuObjCommonText::close();
    }
    GfMenuObjUtil::playSECommonFromInput(input);
    break;
  }
  case GfMenuTypes::unknown003_33: {
    // The accessors named timeInf stay per arm: they share the slot at sp + 104 with the event of the tail (0x710043e6c4).
    // The event words are read into locals before the first call (ruling 2); at their uses the function has 85 (mission), 116 (select), 82 (text) and 102 (selected) differing lines (measured).
    u32 mission = event.unknown08;
    u16 text = event.unknown0c_u16;
    u16 select = event.unknown0e;
    s16 selected = event.unknown10_u16;
    GfMenuObject::setText(acc.searchChild("TXT_dialog_mer_main_text"), text);
    GfGameMercenaries::stopMissionTime(true);
    if (mission == 0) {
      GfMenuObject::termCallContext(acc.getParentHandle());
    } else {
      u32 team = GfDataMercenaries::getTeamID(mission);
      u32 leader = GfDataMercenaries::getTeamLeader(team);
      u32 teamMission = GfDataMercenaries::getTeamMission(team);
      u32 zone = GfDataMercenaries::getMissionZoneID(teamMission);
      if (team == 0 || teamMission == 0 || zone == 0) {
        GfMenuObject::termCallContext(acc.getParentHandle());
      } else {
        m_menuObjCommonText->unknown40->unknown0c = teamMission;
        m_menuObjCommonText->unknown48->unknown0c = zone;
        GfMenuReference::setReferenceBladeID(4, leader);
        bool isReward = GfDataMercenaries::isTeamStateReward(team);
        m_menuObjCommonText->unknown30->clear();
        if (select == 0) {
          acc.setDispChild(true, "LAY_dialog_mer_ok_only");
          acc.setDispChild(false, "LAY_dialog_mer_select");
          m_menuObjCommonText->unknown30->addObject(acc.searchChild("TXT_dialog_mer_ok_only"));
          m_menuObjCommonText->unknown30->setIndex(0);
        } else {
          acc.setDispChild(false, "LAY_dialog_mer_ok_only");
          acc.setDispChild(true, "LAY_dialog_mer_select");
          m_menuObjCommonText->unknown30->addObject(acc.searchChild("TXT_dialog_mer_ok"));
          m_menuObjCommonText->unknown30->addObject(acc.searchChild("TXT_dialog_mer_cancel"));
          m_menuObjCommonText->unknown30->setIndex(selected);
        }
        // The game writes the reward arm first: its four setAlpha temporaries sit at sp + 80 and sp + 56 (0x710043e504), the default arm's at sp + 32 and sp + 8.
        if (isReward) {
          GfMenuObjUtil::setColMulandAdd(acc.searchChild("TXT_dialog_mer_info_unit_name"), "txt_disable");
          ui::UIObjectAcc(acc.searchChild("TXT_dialog_mer_info_unit_name")).setAlpha(0.5f);
          GfMenuObjUtil::setColMulandAdd(acc.searchChild("TXT_dialog_mer_info_mis_name"), "txt_disable");
          ui::UIObjectAcc(acc.searchChild("TXT_dialog_mer_info_mis_name")).setAlpha(0.5f);
          GfMenuObjUtil::setColMulandAdd(acc.searchChild("TXT_dialog_mer_info_time"), "txt_disable");
          GfMenuObjUtil::setChildAddColor(acc.unknown10, "IMG_dialog_mer_info_base", "black");
          ui::UIObjectAcc timeInf(acc.unknown10, "TXT_dialog_mer_info_time_inf");
          timeInf.setAlpha(0.0f);
        } else {
          GfMenuObjUtil::setColDefault(acc.searchChild("TXT_dialog_mer_info_unit_name"));
          ui::UIObjectAcc(acc.searchChild("TXT_dialog_mer_info_unit_name")).setAlpha(1.0f);
          GfMenuObjUtil::setColDefault(acc.searchChild("TXT_dialog_mer_info_mis_name"));
          ui::UIObjectAcc(acc.searchChild("TXT_dialog_mer_info_mis_name")).setAlpha(1.0f);
          GfMenuObjUtil::setColDefault(acc.searchChild("TXT_dialog_mer_info_time"));
          GfMenuObjUtil::setColDefault(acc.searchChild("IMG_dialog_mer_info_base"));
          ui::UIObjectAcc timeInf(acc.unknown10, "TXT_dialog_mer_info_time_inf");
          timeInf.setAlpha(1.0f);
        }
        acc.setDispChild(isReward, "TXT_dialog_mer_come_back");
        m_menuObjCommonText->unknown38->setDisp(true);
        GfMenuObject::resetInputSelection(acc.unknown10);
        GfMenuObject::setupInputSelectionFromList(acc.unknown10, *m_menuObjCommonText->unknown30);
      }
    }
    // The game's tail is the class sender (inlined), whose event sets the type last; a hand-built event loads the UIManager instance before the stores (0x710043e6c4).
    sendEvent(acc.unknown10, GfMenuTypes::unknown003_257, 0, 0.033333335f);
    unknown18 = 1;
    break;
  }
  case GfMenuTypes::unknown003_257: {
    mm::Rect<s16> rect;
    acc.getLayoutRect("dialog_top", rect);
    acc.setPosCenter(mm::Pnt<s16>(rect.x + rect.width / 2, rect.y + rect.height / 2));
    GfMenuObjUtil::setCommonFadeIn(acc.unknown10, 1, 0);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjCommonText::OwnerChangeListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    acc.setSuspend(true);
    GfMenuObject::disableInput(acc.unknown10);
    unknown18 = 0;
    break;
  case 3:
    if (unknown009(acc, event)) {
      acc.setDisp(false);
      acc.setAlpha(1.0f);
      if (unknown18 == 0) {
        acc.setSuspend(true);
      }
      GfMenuObject::termCallContext(acc.getParentHandle());
    }
    break;
  case 8: {
    u32 input = event.unknown0c;
    if (input == 1 || input == 2) {
      close();
    }
    GfMenuObjUtil::playSECommonFromInput(input);
    break;
  }
  case GfMenuTypes::unknown003_33: {
    s16 owner = event.unknown08_u16;
    {
      GfMenuObjUtil::CtrlParam param;
      unknown007(param, 1);
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    }
    acc.setDispChild(owner == 0, "TXT_owner_change_caption");
    acc.setDispChild(owner == 1, "TXT_owner_change_caption_rex");
    acc.setDispChild(owner == 2, "TXT_owner_change_caption_rex2");
    {
      ui::UIObjectAcc okOnly(acc.searchChild("LAY_owner_ch_ok_only"));
      unknown002(acc, okOnly, "IMG_owner_ch_cursor_l", "IMG_owner_ch_cursor_r");
    }
    unknown18 = 1;
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObject::disableInput(acc.unknown10);
    GfMenuObjUtil::CtrlParam param;
    unknown007(param, 2);
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    unknown18 = 0;
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjCommonText::GetItemListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    acc.setSuspend(true);
    GfMenuObject::disableInput(acc.unknown10);
    unknown18 = 0;
    break;
  case 3:
    if (unknown009(acc, event)) {
      acc.setDisp(false);
      acc.setAlpha(1.0f);
      if (unknown18 == 0) {
        acc.setSuspend(true);
      }
    }
    break;
  case 8: {
    u32 input = event.unknown0c;
    if (input == 1 || input == 2) {
      close();
    }
    GfMenuObjUtil::playSECommonFromInput(input);
    break;
  }
  case GfMenuTypes::unknown003_33: {
    {
      GfMenuObjUtil::CtrlParam param;
      param.unknown00 = 0.25f;
      param.unknown08 = 1;
      param.unknown1c = 1.0f / 30.0f;
      param.unknown04 = 1;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    }
    acc.setAlpha(0.0f);
    {
      ui::UIObjectAcc okOnly(acc.searchChild("LAY_get_item_ok_only"));
      unknown002(acc, okOnly, "IMG_get_item_cursor_l", "IMG_get_item_cursor_r");
    }
    mm::Rect<s16> rect;
    mm::Rect<s16> next;
    unknown006(acc, "item_3", "item_4", rect, next);
    GfMenuObjUtil::placeObjectV(acc.unknown10, "LAY_get_item@%02d", s_pItemList->getSize(), mm::Pnt<s16>(rect.x + rect.width / 2, rect.y + rect.height / 2), next.y - rect.y);
    unknown18 = 1;
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObject::disableInput(acc.unknown10);
    GfMenuObjUtil::CtrlParam param;
    unknown007(param, 2);
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    unknown18 = 0;
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjCommonText::SelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case GfMenuTypes::unknown003_34: {
    // The parameter stays in the caller: a helper that also builds and starts it (handle, type) puts its CtrlParam above the accessor (acc moves from x29 - 104 to sp + 104, 0x710043f150; 496
    // instructions, 92 differing lines, measured).
    GfMenuObjUtil::CtrlParam param;
    unknown007(param, 2);
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    GfMenuObject::disableInput(acc.unknown10);
    unknown18 = 0;
    break;
  }
  case 1:
    unknown003(acc);
    unknown0c = 0;
    unknown18 = 0;
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 3:
    if (event.unknown08 == 1) {
      // The game loads the type before resetInputSelection (0x710043f2e4).
      int type = unknown0c;
      GfMenuObject::resetInputSelection(acc.unknown10);
      if (type != 0) {
        GfMenuObject::setupInputSelectionFromList(handle, *s_pItemList);
      } else {
        GfMenuObject::setupInputSelectionFromList(handle, *s_pSubMenuIDList);
      }
      GfMenuObject::enableInput(acc.unknown10);
      acc.setDispChild(true, "LAY_select_cursor");
    } else if (event.unknown08 == 2) {
      if (unknown18 == 0) {
        acc.setSuspend(true);
      }
    }
    break;
  case 6: {
    int index = event.unknown08;
    const char *format = unknown0c == 1 ? "TXT_sel_item_name@%02d" : "TXT_sel_item@%02d";
    if (index != -1) {
      int previous = event.unknown0c;
      // The items and the layout end before the cursor sound (0x710043f884); without the scope 6 lines differ (measured).
      {
        mm::mtl::FixStr<32> name;
        if (previous != -1) {
          name.format(format, previous + 1);
          ui::UIObjectAcc previousItem(acc.unknown10, name.c_str());
          previousItem.loadDefColor();
        }
        name.format(format, index + 1);
        ui::UIObjectAcc item(acc.unknown10, name.c_str());
        GfMenuObjUtil::setColMulandAdd(item.unknown10, "txt_normal");
        if (unknown0c == 0) {
          name.format("LAY_sel_item_text@%02d", index + 1);
        } else {
          name.format("LAY_sel_item_item@%02d", index + 1);
        }
        ui::UIObjectAcc layout(acc.unknown10, name.c_str());
        layout.updateLayoutSize();
        unknown002(acc, layout, "IMG_select_cursor_l", "IMG_select_cursor_r");
      }
      // Written out, not unknown008 (ruling 8): the game keeps the previous-index compare as a value (cset eq, 0x710043f874) before the index compare; with the helper the function has 495
      // instructions against 496 and 19 differing lines, the first at 0x710043f1a8 (measured). The reverse order of the compares has 495 instructions too.
      if (previous != -1 && index != previous) {
        GfMenuObjUtil::playSECommonCursor();
      }
    } else {
      acc.setDispChild(false, "LAY_select_cursor");
    }
    break;
  }
  case 8: {
    u32 input = event.unknown0c;
    if (input == 1) {
      GfMenuObject::addResultCallContext(acc.getParentHandle(), event.unknown08, 0);
      acc.setDispChild(false, "LAY_select_cursor");
      close();
    } else if (input == 2) {
      acc.setDispChild(false, "LAY_select_cursor");
      close();
    }
    GfMenuObjUtil::playSECommonFromInput(input);
    break;
  }
  case GfMenuTypes::unknown003_33: {
    u32 type = event.unknown08;
    // The game keeps the negated equality as a value before the branch (cset ne next to the compare, spilled together with the type, 0x710043f3a4) and compares the type again for the title item at
    // the join; `type != 1` gives 496 instructions but 157 differing lines (measured).
    bool isSubMenu = !(type == 1);
    acc.setAlpha(1.0f);
    // The scope of the parameter ends before the loops: without it the function has 497 instructions against 496, a 368 byte frame against 320 and 209 differing lines (measured).
    {
      GfMenuObjUtil::CtrlParam param;
      unknown007(param, 1);
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    }
    if (isSubMenu) {
      mm::mtl::FixStr<32> name;
      for (u32 i = 0; i < s_pSubMenuIDList->getPageRowSize(); i++) {
        name.format("TXT_sel_item@%02d", i + 1);
        ui::UIObjectAcc item(acc.unknown10, name.c_str());
        if (item.isValid()) {
          u32 size = s_pSubMenuIDList->getSize();
          if (i < size) {
            // The game builds a default string before the message string and destroys it after (0x710043f5d4, 0x710043f6d0); nothing reads it, and 173 lines differ without it (measured).
            ui::UIStr unused;
            // Held in a local: written inside the setText call the function is 501 instructions against 496 (measured).
            u16 messageId = GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_SELECT, s_pSubMenuIDList->getContents(i).unknown00);
            item.setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_MS), messageId));
            item.loadDefColor();
            unknown004(acc, name, i + 1, "LAY_sel_item_item@%02d", "LAY_sel_item_text@%02d");
          }
          name.format("LAY_sel_item@%02d", i + 1);
          acc.setDispChild(i < size, name.c_str());
          if (i != 0) {
            mm::mtl::FixStr<32> accent;
            accent.format("IMG_sel_item_accent@%02d", i);
            acc.setDispChild(i < size, accent.c_str());
          }
        }
      }
    } else {
      mm::mtl::FixStr<32> name;
      for (u32 i = 0; i < s_pSubMenuIDList->getPageRowSize(); i++) {
        name.format("TXT_sel_item_name@%02d", i + 1);
        ui::UIObjectAcc item(acc.unknown10, name.c_str());
        if (item.isValid()) {
          u32 size = s_pItemList->getSize();
          if (i < size) {
            item.loadDefColor();
            unknown004(acc, name, i + 1, "LAY_sel_item_text@%02d", "LAY_sel_item_item@%02d");
            name.format("LAY_sel_item_item@%02d", i + 1);
            ui::UIObjectAcc layout(acc.unknown10, name.c_str());
            name.format("IMG_sel_item_dummy@%02d", i + 1);
            GfMenuObjUtil::setDockPos(layout.unknown10, acc.searchChild(name.c_str()), 0, false);
          }
          name.format("LAY_sel_item@%02d", i + 1);
          acc.setDispChild(i < size, name.c_str());
          if (i != 0) {
            mm::mtl::FixStr<32> accent;
            accent.format("IMG_sel_item_accent@%02d", i);
            acc.setDispChild(i < size, accent.c_str());
          }
        }
      }
    }
    acc.setDispChild(isSubMenu, "TXT_sel_title");
    acc.setDispChild(type == 1, "TXT_sel_title_item");
    unknown0c = event.unknown08;
    unknown18 = 1;
    break;
  }
  }
}

void GfMenuObjCommonText::DrChangeListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown003(acc);
    unknown18 = 0;
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
      m_menuObjCommonText->unknown70->setDisp(true);
    } else if (event.unknown08 == 2) {
      if (unknown18 == 0) {
        acc.setSuspend(true);
      }
    }
    break;
  case 6: {
    u32 index = event.unknown08;
    u32 previous = event.unknown0c;
    s_pChangeDrList->setIndex(index);
    m_menuObjCommonText->unknown68->setIndex(index);
    unknown008(index, previous);
    break;
  }
  case 8:
    if (event.unknown0c == 1) {
      u32 driver = event.unknown08;
      GfMenuObject::addResultCallContext(acc.getParentHandle(), driver, 0);
      GfMenuObjUtil::playSE(10);
    } else if (event.unknown0c == 2) {
      GfMenuObjUtil::playSECommonCancel();
    } else {
      break;
    }
    close();
    m_menuObjCommonText->unknown70->setDisp(true);
    break;
  case GfMenuTypes::unknown003_33: {
    acc.setAlpha(1.0f);
    {
      GfMenuObjUtil::CtrlParam param;
      unknown007(param, 1);
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    }
    mm::Rect<s16> rect;
    mm::Rect<s16> next;
    unknown006(acc, "dr_select", "dr_select_next", rect, next);
    GfMenuObjUtil::placeObjectH(acc.unknown10, "LAY_dr_change@%02d", s_pChangeDrList->getSize(), mm::Pnt<s16>(rect.x + rect.width / 2, rect.y + rect.height / 2), next.x - rect.x);
    m_menuObjCommonText->unknown70->setDisp(false);
    GfMenuObject::resetInputSelection(acc.unknown10);
    GfMenuObject::setupInputSelectionFromList(acc.unknown10, *s_pChangeDrList);
    unknown18 = 1;
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::CtrlParam param;
    unknown007(param, 2);
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    GfMenuObject::disableInput(acc.unknown10);
    unknown18 = 0;
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjCommonText::NumSelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(m_menuObjCommonText->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuAdapterManager::beginCategory(3);
    GfMenuReferenceAdapter::create(acc.searchChild("TXT_num_select_value"), m_menuObjCommonText->unknown78, true);
    GfMenuReferenceAdapter::create(acc.searchChild("TXT_num_select_total_price"), m_menuObjCommonText->unknown80, true);
    GfMenuAdapterManager::endCategory();
    unknown003(acc);
    unknown18 = 0;
    break;
  case 3:
    if (unknown009(acc, event)) {
      if (unknown18 == 0) {
        acc.setSuspend(true);
      }
    }
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 6: {
    int index = event.unknown08;
    int previous = event.unknown0c;
    m_menuObjCommonText->unknown78->unknown162(index);
    m_menuObjCommonText->unknown80->unknown162(m_menuObjCommonText->unknown88 * index);
    if (previous != -1 && index != previous) {
      GfMenuObjUtil::playSE(0x19);
    }
    break;
  }
  case 8:
    if (event.unknown0c == 1) {
      if (m_menuObjCommonText->unknown78->unknown0c == 0) {
        break;
      }
      GfMenuObject::addResultCallContext(owner.searchChild("LAY_main"), 0, m_menuObjCommonText->unknown78->unknown0c);
      unknown164(owner.searchChild("LAY_main"), GfMenuTypes::unknown003_34);
    } else if (event.unknown0c == 2) {
      GfMenuObject::addResultCallContext(owner.searchChild("LAY_main"), 1, 0);
      unknown164(owner.searchChild("LAY_main"), GfMenuTypes::unknown003_34);
    }
    GfMenuObjUtil::playSECommonFromInput(event.unknown0c);
    break;
  case GfMenuTypes::unknown003_33: {
    s16 isSingle = event.unknown08_u16;
    ui::UIObjectAcc first(acc.searchChild("TXT_num_select_index@01"));
    first.setDisp(isSingle == 0);
    ui::UIObjectAcc second(acc.searchChild("TXT_num_select_index@02"));
    second.setDisp(isSingle != 0);
    m_menuObjCommonText->unknown78->unknown162(0);
    m_menuObjCommonText->unknown78->unknown165(event.unknown0a);
    m_menuObjCommonText->unknown78->unknown166(event.unknown0c_u16);
    m_menuObjCommonText->unknown80->unknown162(0);
    m_menuObjCommonText->unknown80->unknown165(0);
    m_menuObjCommonText->unknown80->unknown166(999999999);
    m_menuObjCommonText->unknown88 = event.unknown10;
    GfMenuObject::resetInputSelection(handle);
    GfMenuObject::setupInputSelection(handle, 0, event.unknown0c_u16 + 1);
    setFadeIn(handle);
    unknown18 = 1;
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObject::disableInput(acc.unknown10);
    setFadeOut(handle);
    unknown18 = 0;
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjCommonText::KizunaListener::reciveEvent(const ui::EventData &event, u32 handle) {
  // The owner accessor is built on entry: built in case 8 instead, 167 lines differ (measured).
  ui::UIObjectAcc owner(m_menuObjCommonText->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    GfMenuAdapterManager::beginCategory(3);
    // The scopes of name and bladeSetup are the game's: without them 6 and 4 lines differ (measured).
    {
      mm::mtl::FixStr<32> name;
      u32 bladeCount = acc.countChild("LAY_dialog_kizuna_bl@%02d", 1);
      {
        ui::UIListInfoBase::SetupParam bladeSetup;
        bladeSetup.unknown08 = bladeCount;
        m_menuObjCommonText->m_menuBladeList->setup(getAllocator(ALLOCATOR_UNKNOWN_0), bladeSetup);
      }
      for (u32 i = 0; i < bladeCount; i++) {
        name.format("IMG_dialog_kizuna_bl_face@%02d", i + 1);
        GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 3, m_menuObjCommonText->m_menuBladeList, i, false);
      }
      u32 driverCount = acc.countChild("LAY_dialog_kizuna_dr@%02d", 1);
      ui::UIListInfoBase::SetupParam driverSetup;
      driverSetup.unknown08 = driverCount;
      m_menuObjCommonText->unknown58->setup(getAllocator(ALLOCATOR_UNKNOWN_0), driverSetup);
      for (u32 i = 0; i < driverCount; i++) {
        name.format("IMG_dialog_kizuna_dr_face@%02d", i + 1);
        GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 3, m_menuObjCommonText->unknown58, i, false);
      }
    }
    GfMenuAdapterManager::endCategory();
    // The scope of createParam is the game's: without it 2 lines differ (measured).
    {
      ui::UISelectObjList::CreateParam createParam;
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      m_menuObjCommonText->unknown60 = ui::UISelectObjList::create(createParam);
    }
    unknown005(acc, "IMG_kizuna_kizuna_win", "LAY_dialog_kizuna_main");
    acc.setSuspend(true);
    unknown18 = 0;
    break;
  }
  case 3:
    if (event.unknown08 == 0) {
      return;
    }
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
    } else {
      GfMenuObject::termCallContext(acc.getParentHandle());
      if (unknown18 == 0) {
        acc.setSuspend(true);
      }
    }
    break;
  case 8: {
    // The input is read into a local before the calls (ruling 2): 52 lines differ without it (measured).
    u32 input = event.unknown0c;
    GfMenuObject::addResultCallContext(owner.searchChild("LAY_main"), 0, 0);
    GfMenuObject::disableInput(handle);
    close();
    GfMenuObjUtil::playSECommonFromInput(input);
    break;
  }
  case GfMenuTypes::unknown003_33: {
    u32 condition = event.unknown08;
    // The title is read into a local before the calls (ruling 2): 51 lines differ without it (measured).
    u32 title = event.unknown0c;
    mm::mtl::FixStr<32> name;
    GfMenuObject::setText(acc.searchChild("TXT_dialog_kizuna_title"), title);
    m_menuObjCommonText->unknown58->clear();
    m_menuObjCommonText->m_menuBladeList->clear();
    m_menuObjCommonText->unknown60->clear();
    GfBdatCond *bdatCond = GfBdatCond::get();
    for (u32 index = 0; index < CONDITION_UNKNOWN_8; index++) {
      if (bdatCond->getConditionListConditionType(condition, index) == CONDITION_TYPE_UNKNOWN_6) {
        u32 partyCondition = bdatCond->getConditionListCondition(condition, index);
        if (partyCondition != 0) {
          if (bdatCond->getConditionPTCategory(partyCondition) == CONDITION_PT_CATEGORY_UNKNOWN_0) {
            for (u32 member = 0; member < CONDITION_UNKNOWN_3; member++) {
              u32 character = bdatCond->getConditionPTPCID(partyCondition, member);
              if (character != 0) {
                if (GfDataDriver::isDriver(character)) {
                  MenuDriverInfo info;
                  info.unknown00 = character;
                  m_menuObjCommonText->unknown58->addContents(info);
                  name.format("LAY_dialog_kizuna_dr@%02d", m_menuObjCommonText->unknown58->getSize());
                } else if (GfDataBlade::isBladeID(character)) {
                  MenuBladeInfo info;
                  info.unknown00 = character;
                  info.unknown04 = 0;
                  m_menuObjCommonText->m_menuBladeList->addContents(info);
                  name.format("LAY_dialog_kizuna_bl@%02d", m_menuObjCommonText->m_menuBladeList->getSize());
                } else {
                  continue;
                }
                m_menuObjCommonText->unknown60->addObject(acc.searchChild(name.c_str()));
                acc.setDispChild(true, name.c_str());
              }
            }
          } else if (bdatCond->getConditionPTCategory(partyCondition) == CONDITION_PT_CATEGORY_UNKNOWN_6) {
            u32 blade = bdatCond->getConditionPTPCID(partyCondition, 0);
            if (blade != 0) {
              // The game clears the element before getCreator (str wzr, [sp, #40] at 0x710043eaa4): 38 lines differ without the initialiser (measured).
              MenuDriverInfo info = {};
              info.unknown00 = GfDataBlade::getCreator(blade);
              if (info.unknown00 != 0) {
                m_menuObjCommonText->unknown58->addContents(info);
                name.format("LAY_dialog_kizuna_dr@%02d", m_menuObjCommonText->unknown58->getSize());
                m_menuObjCommonText->unknown60->addObject(acc.searchChild(name.c_str()));
                acc.setDispChild(true, name.c_str());
              }
            }
          }
        }
      }
    }
    for (u32 i = m_menuObjCommonText->unknown58->getSize(); i < m_menuObjCommonText->unknown58->getPageRowSize(); i++) {
      name.format("LAY_dialog_kizuna_dr@%02d", i + 1);
      acc.setDispChild(false, name.c_str());
    }
    for (u32 i = m_menuObjCommonText->m_menuBladeList->getSize(); i < m_menuObjCommonText->m_menuBladeList->getPageRowSize(); i++) {
      name.format("LAY_dialog_kizuna_bl@%02d", i + 1);
      acc.setDispChild(false, name.c_str());
    }
    // The scopes of the rectangles and of the ok accessor are the game's: without them 90 and 4 lines differ (measured).
    {
      mm::Rect<s16> rect;
      mm::Rect<s16> next;
      unknown006(acc, "kizuna_blade", "kizuna_blade_next", rect, next);
      GfMenuObjUtil::placeObjectH(m_menuObjCommonText->unknown60, mm::Pnt<s16>(rect.x + rect.width / 2, rect.y + rect.height / 2), next.x - rect.x);
    }
    {
      ui::UIObjectAcc okOnly(acc.unknown10, "LAY_dialog_kizuna_ok_only");
      mm::Pnt<s16> center;
      okOnly.getPosCenter(center);
      ui::UIObjectAcc cursor(acc.unknown10, "LAY_dialog_kizuna_cursor");
      cursor.setPosCenter(center);
    }
    setFadeIn(handle);
    unknown18 = 1;
    break;
  }
  case GfMenuTypes::unknown003_34:
    setFadeOut(handle);
    unknown18 = 0;
    break;
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

} // namespace gf
