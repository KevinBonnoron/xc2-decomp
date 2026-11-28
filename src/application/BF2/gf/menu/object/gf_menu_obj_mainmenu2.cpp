#include "gf/menu/object/gf_menu_obj_mainmenu2.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_game_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_sound_manager.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2bg.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_popup.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/plugin/ui_object_number_plugin.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: full screen layer index; original name unknown.
constexpr u32 unknown001 = 1;
// Inferred role: attached call id; original name unknown.
constexpr u32 unknown002 = 0x5f;
// Inferred role: no open menu; original name unknown.
constexpr u32 unknown003 = 0x28;
// Inferred role: character change menu; original name unknown.
constexpr u32 unknown004 = 0x27;

u32 GfMenuObjMainMenu2::s_openMenuID;
bool GfMenuObjMainMenu2::s_cancelEnable;
// Inferred role: number of main menu order entries; original name unknown.
static u32 unknown006;

GfMenuObjMainMenu2::GfMenuObjMainMenu2(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), m_menuCallContext(nullptr), unknown38(false), unknown39(false), unknown3c(-1), unknown40(-1), unknown44(0), m_menuDriverList(nullptr),
      m_menuBladeList(nullptr), m_selectionChecker(nullptr), unknown88(0), unknown8c(false), unknown90(this), unknown320(false) {
  m_menuDriverList = GfMenuDriverList::create();
  m_menuBladeList = GfMenuBladeList::create();
  // __LINE__ must be 186 as in the original source: it is the line argument of operator new.
#line 186
  m_selectionChecker = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SelectionChecker();
  s_openMenuID = 0;
}

GfMenuObjMainMenu2::~GfMenuObjMainMenu2() {
  mm::mtl::safeRelease(m_menuBladeList);
  mm::mtl::safeRelease(m_menuDriverList);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(m_menuCallContext);
  if (m_selectionChecker != nullptr) {
    delete m_selectionChecker;
    m_selectionChecker = nullptr;
  }
  s_openMenuID = 0;
}

void GfMenuObjMainMenu2::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u8 *order = GfDataBdat::getFP(BDAT_MNU_MAIN_ORDER);
  unknown60.clear();
  for (u32 i = 0; i < Bdat::getIdCount(order); i++) {
    unknown60.push_back(Bdat::getIdTop(order) + i);
  }
  unknown006 = unknown60.size();
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 225 as in the original file: it is the line argument of operator new.
#line 225
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(unknown002, main);
  u32 contents = acc.searchChild("LAY_contents");
// __LINE__ must be 231 as in the original file: it is the line argument of operator new.
#line 231
  ContentsListener *contentsListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ContentsListener(this);
  contentsListener->addRef();
  ui::UIEventManager::get()->registObjectListener(contents, contentsListener);
  if (contentsListener != nullptr) {
    contentsListener->release();
  }
  u32 index = acc.searchChild("LAY_index");
// __LINE__ must be 235 as in the original file: it is the line argument of operator new.
#line 235
  IndexListener *indexListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) IndexListener(this);
  indexListener->addRef();
  ui::UIEventManager::get()->registObjectListener(index, indexListener);
  if (indexListener != nullptr) {
    indexListener->release();
  }
  u32 close = acc.searchChild("LAY_close");
// __LINE__ must be 240 as in the original file: it is the line argument of operator new.
#line 240
  CloseListener *closeListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) CloseListener(this);
  closeListener->addRef();
  ui::UIEventManager::get()->registObjectListener(close, closeListener);
  if (closeListener != nullptr) {
    closeListener->release();
  }
  u32 change = acc.searchChild("LAY_chr_change");
// __LINE__ must be 248 as in the original file: it is the line argument of operator new.
#line 248
  ChrChangeListener *changeListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ChrChangeListener(this);
  changeListener->addRef();
  ui::UIEventManager::get()->registObjectListener(change, changeListener);
  if (changeListener != nullptr) {
    changeListener->release();
  }
  m_menuCallContext = GfMenuCallContext::create();
  acc.setDispChild(GfMenuManager::isClearCheck(), "IMG_clear_mark");
  GfMenuObject::initialize();
}

bool GfMenuObjMainMenu2::isOpenCharMenu() { return s_openMenuID == unknown004; }

void GfMenuObjMainMenu2::finalize() {
  GfMenuSoundManager::fadeInFieldBgm(1.0f);
  GfMenuObject::finalize();
}

void GfMenuObjMainMenu2::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(GfMenuFullScreen::getScreenLayerID(unknown001), layerParam);
}

void GfMenuObjMainMenu2::sendEvent(u32 handle, u32 type, u32 param) {
  if (handle != 0) {
    unknown140(handle, type, param, 0.0f);
  }
}

void GfMenuObjMainMenu2::setCloseKeyEnable(bool enable) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    GfMenuObject::setInputActionEnable(acc.searchChild("LAY_close"), 3, enable);
  }
}

void GfMenuObjMainMenu2::closeCharChange() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    ui::UIObjectAcc change(acc.searchChild("LAY_chr_change"));
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    ui::UIManager::get()->requestObjectEvent(change.unknown10, event, 0.0f);
  }
}

void GfMenuObjMainMenu2::openMainMenu() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = 0x105;
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjMainMenu2::setContentsIcon(ui::UIObjectNumberPlugin *plugin, u32 icon) { plugin->setNumber(icon); }

void GfMenuObjMainMenu2::disableCharChange() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    ui::UIObjectAcc change(acc.searchChild("LAY_chr_change"));
    ui::EventData event;
    event.unknown00 = 0x109;
    ui::UIManager::get()->requestObjectEvent(change.unknown10, event, 0.0f);
    GfMenuObject::disableInput(change.unknown10);
  }
}

void GfMenuObjMainMenu2::setSubLayer(u32 layer) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    sendEvent(acc.unknown10, 0x108, layer);
  }
}

void GfMenuObjMainMenu2::setGuideText(u32 text) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    sendEvent(acc.unknown10, 0x10a, text);
  }
}

void GfMenuObjMainMenu2::dispCloseButton() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    sendEvent(acc.searchChild("LAY_close"), 0x10d, 0);
  }
}

void GfMenuObjMainMenu2::execMapJump() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    sendEvent(acc.unknown10, 0x10e, 0);
  }
}

void GfMenuObjMainMenu2::setSubIndexText(u32 text) {
  u32 handle = GfMenuObject::getAttachedObject(unknown002);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown0c = 0;
      event.unknown00 = 0x102;
      event.unknown08 = text;
      ui::UIObjectAcc acc(handle);
      ui::UIManager::get()->requestObjectEvent(acc.searchChild("LAY_index"), event, 0.0f);
    }
  }
}

// Inferred helper: sends the system key enable event and remembers the flag; original name unknown.
static inline void unknown005(bool enable) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown0c = 0;
    event.unknown00 = 0x106;
    event.unknown08 = enable;
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
    GfMenuObjMainMenu2::s_cancelEnable = enable;
  }
}

void GfMenuObjMainMenu2::setSystemKeyEnable(bool enable) { unknown005(enable); }

void GfMenuObjMainMenu2::cancelEnableMainMenu(bool enable) { unknown005(enable); }

void GfMenuObjMainMenu2::setDispGold(bool isDisp) {
  u32 handle = GfMenuObject::getAttachedObject(unknown002);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      GfMenuObjUtil::setChildDisp(handle, "LAY_info_money", isDisp);
      GfMenuObjUtil::setChildDisp(handle, "LAY_info_time", isDisp);
      GfMenuObjUtil::setChildDisp(handle, "LAY_clear_mark", isDisp);
    }
  }
}

void GfMenuObjMainMenu2::openCharChange(u32 handle, u32 type, bool flag) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    ui::UIObjectAcc change(acc.searchChild("LAY_chr_change"));
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08 = type;
    event.unknown0c = handle;
    event.unknown10 = flag;
    ui::UIManager::get()->requestObjectEvent(change.unknown10, event, 0.0f);
  }
}

void GfMenuObjMainMenu2::setContentsSubText(u32 handle, u32 index, u32 child) {
  bool isDisp = false;
  if (index != 0) {
    ui::UIObjectAcc acc(handle);
    u8 *sub = GfDataBdat::getFP(BDAT_MNU_MSG_SUB_CONTENTS);
    u32 name = Bdat::getVal(sub, "name", index).valueU16;
    acc.setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_SUB_CONTENTS_MS), name));
    isDisp = true;
  }
  GfMenuObjUtil::setChildDisp(child, "LAY_index", isDisp);
}

void GfMenuObjMainMenu2::setContentsText(u32 handle, u32 index) {
  ui::UIObjectAcc acc(handle);
  u8 *bdat;
  u32 text;
  getContentsText(index, bdat, text);
  acc.setText(ui::UIStr(bdat, text));
}

void GfMenuObjMainMenu2::getContentsText(u32 index, u8 *&bdat, u32 &text) {
  u8 *order = GfDataBdat::getFP(BDAT_MNU_MAIN_ORDER);
  int top = Bdat::getIdTop(order);
  u32 condition = Bdat::getVal(order, "useCond", top + index).valueU16;
  if (GfMenuObjUtil::getMenuCondition(condition)) {
    bdat = GfDataBdat::getFP(BDAT_MENU_MAIN_CONTENTS_MS);
    text = Bdat::getVal(order, "title", top + index).valueU16;
  } else {
    bdat = GfDataBdat::getFP(BDAT_MENU_MS);
    text = 0x67c;
  }
}

void GfMenuObjMainMenu2::initChrChangeDr(ui::UIObjectAcc &acc, GfMenuDriverList *list) {
  ui::UIObjectAcc change(acc.searchChild("LAY_chr_change"));
  mm::mtl::FixStr<32> name;
  u32 count = change.countChild("LAY_chr_change_dr@%02d", 1);
  mm::mtl::FixedVector<u16, 16> drivers;
  GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_UNKNOWN_0, 0);
  u32 driverCount = drivers.size();
  for (u32 i = 0; i < count;) {
    name.format("IMG_chr_change_dr_icon@%02d", i + 1);
    GfMenuCharDataAdapter *adapter = GfMenuCharDataAdapter::createFromDriverList(change.searchChild(name.c_str()), 3, list, i, false);
    if (adapter != nullptr) {
      name.format("LAY_chr_change_dr@%02d", i + 1);
      adapter->unknown24 = change.searchChild(name.c_str());
    }
    name.format("IMG_chr_change_no@%02d", i + 1);
    ui::UIObjectAcc number(change.searchChild(name.c_str()));
    if (i < driverCount) {
      number.setImageIndex(i);
      number.setDisp(true);
    } else {
      number.setDisp(false);
    }
    i++;
  }
}

void GfMenuObjMainMenu2::initChrChangeBl(ui::UIObjectAcc &acc, GfMenuBladeList *list) {
  ui::UIObjectAcc change(acc.searchChild("LAY_chr_change"));
  mm::mtl::FixStr<32> name;
  u32 count = change.countChild("LAY_chr_change_bl@%02d", 1);
  for (u32 i = 0; i < count;) {
    name.format("IMG_chr_change_bl_icon@%02d", i + 1);
    GfMenuCharDataAdapter *adapter = GfMenuCharDataAdapter::createFromBladeList(change.searchChild(name.c_str()), 3, list, i, false);
    if (adapter != nullptr) {
      name.format("LAY_chr_change_bl@%02d", i + 1);
      adapter->unknown24 = change.searchChild(name.c_str());
    }
    i++;
  }
}

int GfMenuObjMainMenu2::moveMainMenu(ui::UIObjectAcc &acc, u32 index, bool) {
  ui::UIObjectAcc move(acc.searchChild("LAY_move"));
  GfMenuObjUtil::CtrlParam param;
  param.unknown0c = 1;
  mm::Rect<s16> rect;
  move.getLayoutRect("move_guide_line", rect);
  param.unknown20 = rect.y;
  param.unknown00 = 0.35f;
  mm::Pnt<s16> pos(0, 0);
  switch (index) {
  case 3:
    move.setPos(pos);
    param.unknown04 = 3;
    param.unknown08 = 0x20;
    break;
  case 4:
    pos.y = -param.unknown20;
    move.setPos(pos);
    param.unknown04 = 4;
    param.unknown08 = 0x40;
    break;
  case 5:
    move.setPos(pos);
    param.unknown04 = 5;
    param.unknown08 = 0;
    break;
  case 6:
    pos.y = -param.unknown20;
    move.setPos(pos);
    param.unknown04 = 6;
    param.unknown08 = 0;
    break;
  }
  return GfMenuObjUtil::startCtrl(move.unknown10, param, nullptr);
}

void GfMenuObjMainMenu2::refreshCharChangeDr(ui::UIObjectAcc &acc, GfMenuDriverList *list) {
  ui::UIObjectAcc change(acc.unknown10, "LAY_chr_change_dr");
  mm::mtl::FixStr<32> name;
  u32 driverCount;
  {
    mm::mtl::FixedVector<u16, 16> drivers;
    GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_UNKNOWN_0, 0);
    driverCount = drivers.size();
  }
  if (list->getSize() != 0) {
    u32 i = 0;
    do {
      name.format("IMG_chr_change_dr_cursor@%02d", i + 1);
      ui::UIObjectAcc cursor(change.unknown10, name.c_str());
      name.format("IMG_chr_change_no@%02d", i + 1);
      ui::UIObjectAcc number(change.unknown10, name.c_str());
      if (i < driverCount) {
        number.setImageIndex(i);
        number.setDisp(true);
      } else {
        number.setDisp(false);
      }
      if (i == list->getIndex(false)) {
        cursor.setDisp(true);
        cursor.startAnimation("loop", false);
      } else {
        cursor.stopAnimation();
        cursor.setDisp(false);
      }
      i++;
    } while (i < list->getSize());
  }
}

void GfMenuObjMainMenu2::refreshCharChangeBl(ui::UIObjectAcc &acc, GfMenuBladeList *list) {
  ui::UIObjectAcc change(acc.unknown10, "LAY_chr_change_bl");
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < list->getPageSize(); i++) {
    name.format("IMG_chr_change_bl_cursor@%02d", i + 1);
    ui::UIObjectAcc cursor(change.unknown10, name.c_str());
    if (i == list->getIndex(true)) {
      cursor.setDisp(true);
      cursor.startAnimation("loop", false);
    } else {
      cursor.stopAnimation();
      cursor.setDisp(false);
    }
  }
  ui::UIObjectAcc left(change.unknown10, "IMG_chr_change_bl_icon_l");
  left.setDisp(false);
  u32 leftIndex = list->getPageIndex(0);
  if (leftIndex != 0) {
    DataParamAcc blade(OBJECT_TYPE_BLADE, list->getContents(leftIndex - 1).unknown00, GIMMICK_TYPE_UNKNOWN_0);
    int icon = GfMenuObjUtil::getFaceIconID(blade);
    if (icon != 0) {
      left.setImageIndex(GfMenuBdat::getIconImageIndex(icon));
      left.setDisp(true);
    }
  }
  ui::UIObjectAcc right(change.unknown10, "IMG_chr_change_bl_icon_r");
  right.setDisp(false);
  u32 pageSize = list->getPageSize();
  if (pageSize != 0) {
    u32 rightIndex = list->getPageIndex(pageSize - 1);
    if (rightIndex < list->getSize() - 1) {
      DataParamAcc blade(OBJECT_TYPE_BLADE, list->getContents(rightIndex + 1).unknown00, GIMMICK_TYPE_UNKNOWN_0);
      int icon = GfMenuObjUtil::getFaceIconID(blade);
      if (icon != 0) {
        right.setImageIndex(GfMenuBdat::getIconImageIndex(icon));
        right.setDisp(true);
      }
    }
  }
}

void GfMenuObjMainMenu2::closeChrChangeSub(ui::UIObjectAcc &acc, ChrChangeParam &param) {
  u32 layer;
  if (param.unknown00 == 0) {
    layer = acc.searchChild("LAY_chr_change_dr");
  } else {
    layer = acc.searchChild("LAY_chr_change_bl");
  }
  GfMenuObjUtil::CtrlParam ctrl;
  ctrl.unknown004("fade_out_r");
  ctrl.unknown11 = true;
  ctrl.unknown14 = 10;
  ctrl.unknown04 = 2;
  int hook = GfMenuObjUtil::startCtrl(layer, ctrl, nullptr);
  GfMenuObjUtil::startCtrl(acc.searchChild("LAY_chr_change_input"), ctrl, nullptr);
  ctrl = GfMenuObjUtil::CtrlParam();
  ctrl.unknown08 = 2;
  ctrl.unknown00 = 0.2f;
  GfMenuObjUtil::startCtrl(acc.searchChild("IMG_chr_change_base"), ctrl, nullptr);
  GfMenuObject::hookCtrlEvent(acc.unknown10, hook);
  GfMenuObject::disableInput(acc.unknown10);
}

void GfMenuObjMainMenu2::inputChrChangeSub(ui::UIObjectAcc &acc, ChrChangeParam &param, int index) {
  switch (param.unknown00) {
  case 0:
    if (index == -1) {
      return;
    }
    param.m_menuDriverList->setIndex(index);
    refreshCharChangeDr(acc, param.m_menuDriverList);
    if (GfMenuReference::getReferenceDriverID(0) == param.m_menuDriverList->getContents(param.m_menuDriverList->getIndex(false)).unknown00) {
      return;
    }
    {
      u32 handle = param.unknown10;
      u32 selected = param.m_menuDriverList->getContents(param.m_menuDriverList->getIndex(false)).unknown00;
      if (handle != 0) {
        unknown163(handle, 0x140, selected);
      }
    }
    break;
  case 1:
  case 2:
    if (index == -1) {
      return;
    }
    param.m_menuBladeList->setIndex(index);
    refreshCharChangeBl(acc, param.m_menuBladeList);
    if (GfMenuReference::getReferenceBladeID(0) == param.m_menuBladeList->getContents(param.m_menuBladeList->getIndex(false)).unknown00) {
      return;
    }
    {
      u32 handle = param.unknown10;
      u32 selected = param.m_menuBladeList->getContents(param.m_menuBladeList->getIndex(false)).unknown00;
      if (handle != 0) {
        unknown163(handle, 0x140, selected);
      }
    }
    break;
  }
}

void GfMenuObjMainMenu2::setupMainMenu(ui::UIObjectAcc &acc) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < unknown006; i++) {
    name.format("TXT_contents_item@%02d", i + 1);
    u32 text = acc.searchChild(name.c_str());
    if (text != 0) {
      setContentsText(text, i);
      GfMenuObjUtil::setColMulandAdd(text, "txt_main_title");
    }
  }
  GfMenuGameAdapter::create(acc.searchChild("TXT_info_time"), 0, true);
  GfMenuGameAdapter::create(acc.searchChild("TXT_info_money"), 1, true);
  ui::UIObjectAcc background(acc.searchChild("IMG_contents_bg"));
  background.startAnimation("loop", false);
}

void GfMenuObjMainMenu2::update() {
  if (unknown44 != unknown003) {
    s_openMenuID = unknown44;
  }
  unknown90.unknown003();
  GfMenuObject::update();
}

void GfMenuObjMainMenu2::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc root(m_menuObjMainMenu2->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case GfMenuTypes::unknown003_259: {
    u32 enable = event.unknown08;
    ui::UIObjectAcc(acc.unknown10, "LAY_contents_input").setAlpha(enable == 1 ? 1.0f : 0.5f);
    if (enable == 1) {
      ui::UIObjectAcc(acc.unknown10, "LAY_contents_bg_sep").setAlpha(1.0f);
    } else {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 4;
      param.unknown3c = 0.5f;
      param.unknown00 = 0.33f;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, "LAY_contents_bg_sep");
    }
    if (m_menuObjMainMenu2->unknown28 != nullptr) {
      mm::mtl::FixStr<32> name;
      m_menuObjMainMenu2->unknown28->setDisp(enable == 1);
      u32 item = m_menuObjMainMenu2->unknown28->unknown58->getIndex(false) + 1;
      name.format("TXT_contents_item@%02d", item);
      {
        ui::UIObjectAcc text(acc.unknown10, name.c_str());
        if (enable == 1) {
          GfMenuObjUtil::setColMulandAdd(text.unknown10, "txt_title_sel");
        } else {
          GfMenuObjUtil::setColMulandAdd(text.unknown10, "txt_sys_disable");
        }
      }
      name.format("IMG_contents_item_bg@%02d", item);
      {
        ui::UIObjectAcc background(acc.unknown10, name.c_str());
        background.startAnimation(enable == 1 ? "loop" : "idol", false);
        if (enable == 1) {
          background.setMulColor("white");
          background.setAddColor("black");
        } else {
          background.setMulColor("black");
          background.setAddColor("sys_disable");
        }
      }
      for (int i = 0; i < 7; i++) {
        if (m_menuObjMainMenu2->unknown3c != i) {
          name.format("TXT_contents_item@%02d", i + 1);
          ui::UIObjectAcc text(acc.unknown10, name.c_str());
          text.setDisp(enable == 1);
        }
      }
    }
    break;
  }
  case 1:
    setupMainMenu(acc);
    acc.setDisp(true);
    unknown0c = 1;
    GfMenuSoundManager::fadeFieldBgm(1.0f, 0.5f);
    GfMenuObjPopup::pausePickup();
    break;
  case 0x105:
    GfMenuObject::hookCtrlEvent(handle, moveMainMenu(root, 4, false));
    GfMenuObjOperationInfo::open(root.searchChild("LAY_close"), root.searchChild("LAY_contents"), 0, 0);
    setDispGold(true);
    {
      u8 *order = GfDataBdat::getFP(BDAT_MNU_MAIN_ORDER);
      GfMenuObjOperationInfo::setGuideText(Bdat::getVal(order, "guide", m_menuObjMainMenu2->unknown60[m_menuObjMainMenu2->unknown3c]).valueU16, 0);
    }
    m_menuObjMainMenu2->unknown44 = 0;
    if (m_menuObjMainMenu2->unknown8c) {
      setCloseKeyEnable(true);
    }
    break;
  case 0x106: {
    bool enable = event.unknown08 == 1;
    GfMenuObject::setInputActionEnable(root.searchChild("LAY_close"), 2, enable);
    break;
  }
  case 0x107:
    if (!GfMenuManager::isSwitchingFullScreen()) {
      GfMenuObject::closeFSLayer(root.unknown10, true, true);
      GfMenuObjUtil::playSE(4);
    }
    break;
  case 0x108:
    if (!m_menuObjMainMenu2->unknown8c) {
      m_menuObjMainMenu2->unknown44 = event.unknown08;
    }
    break;
  case 0x10a: {
    ui::UIStr text;
    if (event.unknown08 == 0) {
      text.copy(ui::UIStr(" ", false));
    } else {
      u32 name = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_MSG_OPERATION_GUIDE), "name", event.unknown08).valueU16;
      text.copy(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_OPERATION_GUIDE), name));
    }
    ui::UIObjectAcc guide(acc.searchChild("TXT_guide"));
    guide.setText(text);
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_l");
    param.unknown11 = true;
    param.unknown14 = 8;
    param.unknown00 = 0.2f;
    GfMenuObjUtil::startCtrl(guide.unknown10, param, nullptr);
    break;
  }
  case 0x10b:
    if (unknown0c != event.unknown08) {
      if (event.unknown08 == 1) {
        GfMenuObjUtil::setCommonFadeIn(acc.unknown10, 0, 0);
      } else {
        GfMenuObjUtil::setCommonFadeOut(acc.unknown10, 0, 0);
      }
      unknown0c = event.unknown08;
    }
    break;
  case 0x10e:
    m_menuObjMainMenu2->unknown320 = true;
    break;
  case 2:
    m_menuObjMainMenu2->unknown90.unknown005();
    m_menuObjMainMenu2->unknown90.unknown004(0x10);
    m_menuObjMainMenu2->unknown90.unknown002(&GfMenuObjMainMenu2::seqExecTerm);
    break;
  case 3:
    if (event.unknown08 == 2) {
      if (handle != 0) {
        ui::EventData request;
        request.unknown00 = 0x107;
        ui::UIManager::get()->requestObjectEvent(handle, request, 0.0f);
      }
    } else if (event.unknown08 == 4) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0;
      param.unknown00 = 0.1f;
      param.unknown04 = 7;
      GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr));
    } else if (event.unknown08 == 7) {
      GfMenuObject::enableInput(root.searchChild("LAY_contents"));
      if (handle != 0) {
        ui::EventData request;
        request.unknown00 = GfMenuTypes::unknown003_259;
        request.unknown08 = 1;
        ui::UIManager::get()->requestObjectEvent(handle, request, 0.0f);
      }
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeOut(handle, 2, 0));
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

bool GfMenuObjMainMenu2::seqExecTerm() {
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc main(acc.searchChild("LAY_main"));
  if (!unknown320) {
    GfMenuObjPopup::continuePickup(20);
  } else {
    unknown320 = false;
  }
  main.setTerm();
  return true;
}

void GfMenuObjMainMenu2::ContentsListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc root(m_menuObjMainMenu2->unknown18);
  switch (event.unknown00) {
  // Case 8 is written before case 1, as the game lays out the blocks: with case 8 after case 1 the function has the same 735 instructions but 103 lines differ, the first at 0x7100485ecc (the slot
  // of the CtrlParam of the inlined moveMainMenu, measured).
  case 8:
    switch (event.unknown0c) {
    case 1: {
      int index = m_menuObjMainMenu2->unknown3c;
      u8 *order = GfDataBdat::getFP(BDAT_MNU_MAIN_ORDER);
      int count = m_menuObjMainMenu2->unknown60.size();
      if (index < count) {
        int entry = m_menuObjMainMenu2->unknown60[index];
        if (GfMenuObjUtil::getMenuCondition(Bdat::getVal(order, "useCond", entry).valueU16)) {
          m_menuObjMainMenu2->unknown44 = Bdat::getVal(order, "layer", entry).valueU16;
          GfMenuObject::changeFSSubLayer(root.unknown10, 1, m_menuObjMainMenu2->unknown44, false);
          moveMainMenu(root, 3, false);
          sendEvent(root.searchChild("LAY_main"), GfMenuTypes::unknown003_259, 0);
          GfMenuObject::disableInput(handle);
          cancelEnableMainMenu(false);
          GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
          GfMenuObjUtil::playSECommonDecide();
        }
      }
      setDispGold(false);
      break;
    }
    case 10:
      GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_chr_change"), 0, 0.0f);
      break;
    }
    break;
  case 1: {
    m_menuObjMainMenu2->unknown38 = false;
    m_menuObjMainMenu2->unknown39 = false;
    // Written out like the cursor setup of GfMenuObjCharSelect::SubMenuListener, GfMenuObjHanaSubmenu::SubmenuListener and GfMenuObjPouch2::SlotListener (ruling 8). Measured against the game's 735
    // instructions and 384 byte frame (both helper forms differ first at 0x7100485e6c, the frame size `sub sp, sp, #N`): a file-local helper that fills the parameter (handle, accessor, cursor name,
    // format) gives 735 instructions, a 368 byte frame and 174 differing lines; a helper that creates the cursor and returns it (the base through a reference) gives 736 instructions, a 320 byte frame
    // and 335 differing lines. The three stores after the search of the cursor base are the game's (0x7100485f48 to 0x7100485f50: strh wzr, strh wzr, strb wzr).
    GfMenuObjUtil::CursorParam param;
    param.unknown00 = ui::UIObjectAcc(handle).getParentHandle();
    param.unknown04 = acc.searchChild("IMG_contents_cursor_base");
    param.unknown1a = 0;
    param.m_cursorSetting.unknown18 = 0;
    param.m_cursorSetting.unknown20 = false;
    param.unknown08 = "LAY_contents_item@%02d";
    m_menuObjMainMenu2->unknown28 = GfMenuObjUtil::createCursor(param);
    m_menuObjMainMenu2->unknown28->open(0);
    GfMenuObjUtil::createSyncPlugin(acc.searchChild("IMG_contents_cursor"), param.unknown04, 0x32);
    m_menuObjMainMenu2->unknown8c = false;
    int page = 0;
    // The scope: the game's parameter shares the frame slot of the inlined CtrlParam (0x7100485f98: add x1, sp, #168); with the parameter alive to the end of the case 184 lines differ (measured).
    {
      GfMenuTypes::Param layerParam;
      if (GfMenuObject::getFSLayerParam(m_menuObjMainMenu2->unknown20, layerParam)) {
        page = layerParam.get<OpenParam>().unknown00;
        m_menuObjMainMenu2->unknown8c = true;
        GfMenuObject::removeFSLayerParam(m_menuObjMainMenu2->unknown20);
      }
    }
    sendEvent(root.searchChild("LAY_close"), GfMenuTypes::unknown003_33, 0);
    if (m_menuObjMainMenu2->unknown8c) {
      setCloseKeyEnable(false);
    }
    GfMenuObject::setupInputSelection(handle, page, unknown006);
    GfMenuObject::enableInput(handle);
    sendEvent(root.searchChild("LAY_index"), GfMenuTypes::unknown003_257, page);
    GfMenuObject::startCallContext(m_menuObjMainMenu2->m_menuCallContext, unknown002, handle);
    GfMenuObject::setCallContextEventHandler(m_menuObjMainMenu2->m_menuCallContext, handle);
    GfMenuObject::registFSLayerObject(9, handle);
    GfMenuObject::setInputSelectionChecker(handle, m_menuObjMainMenu2->m_selectionChecker);
    m_menuObjMainMenu2->unknown3c = -1;
    m_menuObjMainMenu2->unknown40 = -1;
    m_menuObjMainMenu2->unknown44 = 0;
    u8 *order = GfDataBdat::getFP(BDAT_MNU_MAIN_ORDER);
    GfMenuObjOperationInfo::setGuideText(Bdat::getVal(order, "guide", m_menuObjMainMenu2->unknown60[page]).valueU16, 0);
    if (m_menuObjMainMenu2->unknown8c) {
      GfMenuObjOperationInfo::open(0, 0, 0, 0);
      GfMenuObject::setInputActionEnable(root.searchChild("LAY_close"), 2, false);
      moveMainMenu(root, 6, false);
      setDispGold(false);
      int entry = m_menuObjMainMenu2->unknown60[page];
      order = GfDataBdat::getFP(BDAT_MNU_MAIN_ORDER);
      if (GfMenuObjUtil::getMenuCondition(Bdat::getVal(order, "useCond", entry).valueU16)) {
        m_menuObjMainMenu2->unknown44 = Bdat::getVal(order, "layer", entry).valueU16;
        GfMenuObject::changeFSSubLayer(root.unknown10, 1, m_menuObjMainMenu2->unknown44, false);
        sendEvent(root.searchChild("LAY_main"), GfMenuTypes::unknown003_259, 0);
        GfMenuObject::disableInput(handle);
        GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
      }
    } else {
      GfMenuObjOperationInfo::open(root.searchChild("LAY_close"), handle, 0, 0);
      moveMainMenu(root, 5, false);
    }
    break;
  }
  case 2:
    GfMenuObject::termCallContext(handle);
    GfMenuObject::setInputSelectionChecker(handle, nullptr);
    acc.setTerm();
    break;
  case 6: {
    int next = event.unknown08;
    int previous = event.unknown0c;
    m_menuObjMainMenu2->unknown28->inputChange(next);
    GfMenuObjUtil::playAnime(acc.unknown10, "IMG_contents_cursor", "loop");
    sendEvent(root.searchChild("LAY_index"), GfMenuTypes::unknown003_257, next);
    // The game calls getParamMenu before the test of unknown38 (0x7100486408) and reads the result only inside it; calling it inside the if gives 736 instructions and 65 differing lines (measured).
    const GfMenuObjUtil::unknown001 *menu = GfMenuObjUtil::getParamMenu();
    if (m_menuObjMainMenu2->unknown38) {
      GfMenuObjMainMenu2BG::OpenMainMenuBg move;
      move.unknown00 = next;
      move.unknown04 = unknown006;
      move.unknown08 = menu != nullptr ? menu->unknown0c : 0.0f;
      GfMenuObjMainMenu2BG::move(m_menuObjMainMenu2->m_menuCallContext, handle, move);
      mm::mtl::FixStr<32> arrow;
      if (next > previous) {
        // The game loads unknown006 and stores the name's length before its first test (0x7100486764 to 0x7100486770: ldr w8, [x22, #696]; mov w9, #20; str w9, [sp, #72]; cbnz w24): the condition is
        // flattened and the store hoisted, which needs the load first in the condition (`previous == 0 && next == ...` gives 728 instructions against 735, `previous == ... - 1 && next == 0` in the
        // else arm 727, measured). The else arm tests next first and loads after it (0x710048678c: cbnz w21).
        if (next == unknown006 - 1 && previous == 0) {
          arrow = "IMG_contents_input_l";
        } else {
          arrow = "IMG_contents_input_r";
        }
      } else if (next == 0 && previous == unknown006 - 1) {
        arrow = "IMG_contents_input_r";
      } else {
        arrow = "IMG_contents_input_l";
      }
      ui::UIObjectAcc input(acc.searchChild(arrow.c_str()));
      input.setAddColor("black");
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x40000000;
      param.unknown0c = 3;
      param.unknown00 = 0.2f;
      param.unknown38 = 1.0f;
      GfMenuObjUtil::startCtrl(input.unknown10, param, nullptr);
    }
    // old is the index shown before the move (0 when the cursor starts); `u32 old = previous + 1;` gives 734 instructions and 40 differing lines (measured).
    u32 old = 0;
    mm::mtl::FixStr<32> name;
    if (previous != -1) {
      old = previous + 1;
      name.format("TXT_contents_item@%02d", old);
      GfMenuObjUtil::setColMulandAdd(acc.searchChild(name.c_str()), "txt_main_title");
      GfMenuObjUtil::playSE(5);
    }
    name.format("TXT_contents_item@%02d", next + 1);
    GfMenuObjUtil::setColMulandAdd(acc.searchChild(name.c_str()), "txt_main_select");
    name.format("IMG_contents_item_bg@%02d", old);
    GfMenuObjUtil::playAnime(acc.unknown10, name.c_str(), "idol");
    name.format("IMG_contents_item_bg@%02d", next + 1);
    GfMenuObjUtil::playAnime(acc.unknown10, name.c_str(), "loop");
    m_menuObjMainMenu2->unknown3c = next;
    m_menuObjMainMenu2->unknown40 = previous;
    m_menuObjMainMenu2->unknown44 = 0;
    u8 *order = GfDataBdat::getFP(BDAT_MNU_MAIN_ORDER);
    GfMenuObjOperationInfo::setGuideText(Bdat::getVal(order, "guide", m_menuObjMainMenu2->unknown60[next]).valueU16, 0);
    m_menuObjMainMenu2->unknown38 = true;
    m_menuObjMainMenu2->unknown39 = false;
    break;
  }
  case 0x41:
  case 0x43:
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjMainMenu2::IndexListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    setContentsSubText(acc.searchChild("TXT_index"), 0, acc.unknown10);
    setContentsSubText(acc.searchChild("TXT_index_shadow"), 0, acc.unknown10);
    ui::UIObjectAcc image(acc.searchChild("IMG_index_icon"));
    image.setImageIndex(0);
    acc.setDisp(true);
    break;
  }
  case GfMenuTypes::unknown003_258: {
    u32 text = event.unknown08;
    ui::UIObjectAcc title(acc.searchChild("LAY_title"));
    if (text != 0) {
      setContentsSubText(acc.searchChild("TXT_index"), text, acc.unknown10);
      setContentsSubText(acc.searchChild("TXT_index_shadow"), text, acc.unknown10);
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 1;
      param.unknown0c = 1;
      param.unknown00 = 0.3f;
      GfMenuObjUtil::startCtrl(title.unknown10, param, nullptr);
      title.setDisp(true);
    } else {
      title.setDisp(false);
    }
    break;
  }
  case GfMenuTypes::unknown003_257: {
    int index = event.unknown08;
    u8 *order = GfDataBdat::getFP(BDAT_MNU_MAIN_ORDER);
    int entry = m_menuObjMainMenu2->unknown60[index];
    u32 subTitle = Bdat::getVal(order, "subTitle", entry).valueU16;
    if (handle != 0) {
      unknown163(handle, GfMenuTypes::unknown003_258, subTitle);
    }
    u32 icon = Bdat::getVal(order, "titleIcon", entry).valueU16;
    ui::UIObjectAcc image(acc.searchChild("IMG_index_icon"));
    image.setImageIndex(icon);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjMainMenu2::CloseListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc root(m_menuObjMainMenu2->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::disableInput(handle);
    s_cancelEnable = false;
    break;
  case 8:
    if (event.unknown0c == 2) {
      if (s_cancelEnable && !GfMenuManager::isSwitchingFullScreen()) {
        if (m_menuObjMainMenu2->unknown44 != 0) {
          GfMenuObject::returnFSSubLayer(handle, 1);
          openMainMenu();
          GfMenuObjUtil::playSECommonCancel();
        } else {
          u32 main = root.searchChild("LAY_main");
          if (main != 0) {
            ui::EventData request;
            request.unknown00 = 0x107;
            ui::UIManager::get()->requestObjectEvent(main, request, 0.0f);
          }
          GfMenuObject::disableInput(handle);
        }
      }
    } else if (event.unknown0c == 3) {
      if (!GfMenuManager::isSwitchingFullScreen()) {
        u32 main = root.searchChild("LAY_main");
        if (main != 0) {
          ui::EventData request;
          request.unknown00 = 0x107;
          ui::UIManager::get()->requestObjectEvent(main, request, 0.0f);
        }
        GfMenuObject::disableInput(handle);
      }
    }
    break;
  case GfMenuTypes::unknown003_33:
    GfMenuObject::enableInput(handle);
    s_cancelEnable = true;
    break;
  case 0x10d:
    GfMenuObjOperationInfo::open(handle, 0, 0, 0);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjMainMenu2::ChrChangeListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc root(m_menuObjMainMenu2->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    initChrChangeDr(root, m_menuObjMainMenu2->m_menuDriverList);
    initChrChangeBl(root, m_menuObjMainMenu2->m_menuBladeList);
    acc.setDisp(false);
    GfMenuObject::disableInput(acc.unknown10);
    unknown0c = 0;
    unknown10 = unknown007(-1, 0);
    break;
  }
  case 3:
    switch (event.unknown08) {
    case 0:
      return;
    case 1:
      if (unknown10.unknown00 == 1 || unknown10.unknown00 == 2) {
        GfMenuObject::resetInputSelection(acc.unknown10);
        GfMenuObject::setupInputSelectionFromList(acc.unknown10, *m_menuObjMainMenu2->m_menuBladeList);
      } else if (unknown10.unknown00 == 0) {
        GfMenuObject::resetInputSelection(acc.unknown10);
        GfMenuObject::setupInputSelectionFromList(acc.unknown10, *m_menuObjMainMenu2->m_menuDriverList);
      }
      if (m_menuObjMainMenu2->unknown88 == 0) {
        GfMenuObject::disableInput(acc.unknown10);
      } else {
        GfMenuObject::enableInput(acc.unknown10);
      }
      break;
    case 2:
      GfMenuObject::termCallContext(acc.unknown10);
      acc.setDisp(false);
      break;
    case 3:
      if (handle != 0) {
        ui::EventData request;
        request.unknown00 = 0x10c;
        ui::UIManager::get()->requestObjectEvent(handle, request, 0.0f);
      }
      break;
    }
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 6: {
    int next = event.unknown08;
    int previous = event.unknown0c;
    ChrChangeParam param;
    param.unknown00 = unknown10.unknown00;
    param.unknown10 = m_menuObjMainMenu2->unknown88;
    param.m_menuDriverList = m_menuObjMainMenu2->m_menuDriverList;
    param.m_menuBladeList = m_menuObjMainMenu2->m_menuBladeList;
    inputChrChangeSub(acc, param, next);
    if (previous != -1 && next != previous) {
      GfMenuObjUtil::playSECommonTab();
    }
    break;
  }
  case GfMenuTypes::unknown003_33: {
    u32 type = event.unknown08;
    u32 flag = event.unknown10;
    m_menuObjMainMenu2->unknown88 = event.unknown0c;
    ChrChangeParam param;
    if (type == 3) {
      type = 0;
      param.unknown2c = false;
    }
    param.unknown00 = type;
    param.unknown04 = flag == 1;
    param.unknown08 = unknown10.unknown00;
    param.unknown0c = unknown0c == 1;
    param.unknown10 = m_menuObjMainMenu2->unknown88;
    param.m_menuDriverList = m_menuObjMainMenu2->m_menuDriverList;
    param.m_menuBladeList = m_menuObjMainMenu2->m_menuBladeList;
    param.unknown28 = GfMenuReference::getReferenceDriverID(0);
    param.unknown30 = unknown10.unknown04;
    u32 value = 0;
    if (openChrChangeSub(acc, param, value)) {
      unknown0c = 1;
      unknown10.unknown00 = type;
      unknown10.unknown04 = value;
    }
    break;
  }
  case GfMenuTypes::unknown003_34: {
    ChrChangeParam param;
    param.unknown00 = unknown10.unknown00;
    closeChrChangeSub(acc, param);
    unknown0c = 0;
    break;
  }
  case 0x109:
    m_menuObjMainMenu2->unknown88 = 0;
    break;
  case 0x10c: {
    ChrChangeParam param;
    param.unknown00 = unknown10.unknown00;
    param.m_menuDriverList = m_menuObjMainMenu2->m_menuDriverList;
    param.m_menuBladeList = m_menuObjMainMenu2->m_menuBladeList;
    openChrChange2Sub(acc, param);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

bool SelectionChecker::isEnableSelect(u32 handle, int index) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_MAIN_ORDER);
  return GfMenuObjUtil::getMenuCondition(Bdat::getVal(bdat, "useCond", Bdat::getIdTop(bdat) + index).valueU16);
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjMainMenu2, 8>>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjMainMenu2>(const mm::mtl::Delegate<bool()> *);
