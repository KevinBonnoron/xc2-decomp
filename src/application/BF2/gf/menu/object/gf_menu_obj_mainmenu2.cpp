#include "gf/menu/object/gf_menu_obj_mainmenu2.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sound_manager.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/object/gf_menu_obj_popup.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
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

GfMenuObjMainMenu2::GfMenuObjMainMenu2(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(0), unknown3c(-1), unknown40(-1), unknown44(0), unknown48(nullptr), unknown50(nullptr), unknown58(nullptr), unknown88(0),
      unknown8c(false), unknown90(this), unknown320(false) {
  unknown48 = GfMenuDriverList::create();
  unknown50 = GfMenuBladeList::create();
  // __LINE__ must be 186 as in the original source: it is the line argument of operator new.
#line 186
  unknown58 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SelectionChecker();
  s_openMenuID = 0;
}

GfMenuObjMainMenu2::~GfMenuObjMainMenu2() {
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  if (unknown58 != nullptr) {
    delete unknown58;
    unknown58 = nullptr;
  }
  s_openMenuID = 0;
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
  u8 *order = GfDataBdat::getFP(BDAT_MNU_MAIN_ORDER);
  int top = Bdat::getIdTop(order);
  u32 condition = Bdat::getVal(order, "useCond", top + index).valueU16;
  u8 *bdat;
  u32 text;
  if (!GfMenuObjUtil::getMenuCondition(condition)) {
    bdat = GfDataBdat::getFP(BDAT_MENU_MS);
    text = 0x67c;
  } else {
    bdat = GfDataBdat::getFP(BDAT_MENU_MAIN_CONTENTS_MS);
    text = Bdat::getVal(order, "title", top + index).valueU16;
  }
  acc.setText(ui::UIStr(bdat, text));
}

void GfMenuObjMainMenu2::initChrChangeDr(ui::UIObjectAcc &acc, GfMenuDriverList *list) {
  ui::UIObjectAcc change(acc.searchChild("LAY_chr_change"));
  mm::mtl::FixStr<32> name;
  u32 count = change.countChild("LAY_chr_change_dr@%02d", 1);
  mm::mtl::FixedVector<u16, 16> drivers;
  GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_PARTY, 0);
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
  param.unknown00 = 0.35f;
  param.unknown20 = rect.y;
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
    GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_PARTY, 0);
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

void GfMenuObjMainMenu2::update() {
  if (unknown44 != unknown003) {
    s_openMenuID = unknown44;
  }
  unknown90.unknown003();
  GfMenuObject::update();
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

bool SelectionChecker::isEnableSelect(u32 handle, int index) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_MAIN_ORDER);
  return GfMenuObjUtil::getMenuCondition(Bdat::getVal(bdat, "useCond", Bdat::getIdTop(bdat) + index).valueU16);
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjMainMenu2, 8>>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjMainMenu2>(const mm::mtl::Delegate<bool()> *);
