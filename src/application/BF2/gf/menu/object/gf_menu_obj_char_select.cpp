#include "gf/menu/object/gf_menu_obj_char_select.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_hana.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/object/gf_menu_obj_cmn_status.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_party_status.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_scom.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x61;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x104;
// Inferred role: customize layer; original name unknown.
constexpr u16 unknown004 = 0x27;
// Inferred role: busy flags of the stream waits; original type name unknown.
struct unknown006 {
  bool m_charBusy;   // Inferred role: character stream wait busy flag; named after the game accessor gf::GfMenuObjCharSelect::getCharBusy.
  bool m_selectBusy; // Inferred role: selection stream wait busy flag; named after the game accessor gf::GfMenuObjCharSelect::getSelectBusy.
};
// Inferred role: busy flags of the stream waits; original name unknown.
static unknown006 unknown007;
// Inferred role: layer names of the driver and the three blades of the character select; original name unknown.
static const char *const unknown008[4] = {"LAY_char_dr", "LAY_char_bl@01", "LAY_char_bl@02", "LAY_char_bl@03"};
// Inferred role: common window ids confirming the special operations; original name unknown.
static const u32 unknown009[4] = {0xb9, 0xba, 0xbb, 0xbc};
// Inferred role: layer names of the status of the driver and the three blades of the character select; original name unknown.
static const char *const unknown010[4] = {"LAY_status_dr", "LAY_status_bl@01", "LAY_status_bl@02", "LAY_status_bl@03"};
// Inferred role: glow image names of the driver and the three blades of the character select; original name unknown.
static const char *const unknown011[4] = {"IMG_char_dr_glow", "IMG_char_bl_glow@01", "IMG_char_bl_glow@02", "IMG_char_bl_glow@03"};

GfMenuObjCharSelect::GfMenuObjCharSelect(u32 handle)
    : GfMenuObject(handle), unknown48(nullptr), unknown3f8(0), unknown3fc(0), unknown428(false), unknown429(false), unknown430(this), unknown6c0(false), unknown6d8(0), unknown6e8(-1),
      unknown740(true), unknown741(false), unknown742(0), unknown744(0), unknown748(0xff), unknown768(false) {
  unknown400.assign(-1);
  m_menuDriverList = nullptr;
  unknown30.assign(nullptr);
  m_menuCallContext = GfMenuCallContext::create();
  unknown750.assign(-1);
  unknown007.m_charBusy = false;
  unknown007.m_selectBusy = false;
}

GfMenuObjCharSelect::~GfMenuObjCharSelect() {
  mm::mtl::safeRelease(m_menuCallContext);
  mm::mtl::safeRelease(m_menuDriverList);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown30[0]);
  mm::mtl::safeRelease(unknown30[1]);
  mm::mtl::safeRelease(unknown30[2]);
}

void GfMenuObjCharSelect::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCharSelect::registOpenCustomizeParam(const OpenCustomizeParam &param) {
  GfMenuTypes::Param layerParam;
  unknown003 &data = layerParam.get<unknown003>();
  data.unknown00 = param.unknown00;
  data.unknown04 = param.unknown04;
  GfMenuFullScreen::registLayerParam(unknown004, layerParam);
}

void GfMenuObjCharSelect::openBladeCustomize(u32 handle, u32 blade, u16 group) {
  OpenCustomizeParam param;
  param.unknown00 = 1;
  param.unknown04 = blade;
  registOpenCustomizeParam(param);
  changeFSSubLayer(handle, group, unknown004, true);
}

void GfMenuObjCharSelect::openDriverCustomize(u32 handle, u32 driver, u16 group) {
  OpenCustomizeParam param;
  param.unknown00 = 0;
  param.unknown04 = driver;
  registOpenCustomizeParam(param);
  changeFSSubLayer(handle, group, unknown004, true);
}

void GfMenuObjCharSelect::setupCharSubMenuBl(ui::UIObjectAcc &acc, u32 blade, u32 index) {
  mm::mtl::FixStr<32> name;
  name.format("IMG_sub_menu_icon_bl@%02d", index + 1);
  ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
  icon.setImageIndex(getMenuIconID(blade));
  icon.setDisp(true);
}

void GfMenuObjCharSelect::setupCharSubMenuHana(ui::UIObjectAcc &acc, u32 blade, u32 index) {
  mm::mtl::FixStr<32> name;
  name.format("IMG_sub_menu_icon_hana@%02d", index + 1);
  ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
  icon.setImageIndex(getMenuIconID(blade));
  icon.setDisp(true);
}

void GfMenuObjCharSelect::setupCharSelectCopy(ui::UIObjectAcc &acc) {
  GfMenuAdapterManager::beginAddAfter();
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_char_dr_move_img"), 0x1c, 0, false);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_char_bl_move_img"), 0x36, 0, false);
  ui::UIObjectAcc(acc.searchChild("IMG_char_bl_move_img")).setStreamImage2nd();
  GfMenuAdapterManager::endAddAfter();
}

bool GfMenuObjCharSelect::seqSpHikariToHomura() {
  GfGameUtil::changeHikariCurrent(false);
  return true;
}

bool GfMenuObjCharSelect::seqSpHomuraToHikari() {
  GfGameUtil::changeHikariCurrent(true);
  return true;
}

void GfMenuObjCharSelect::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

void GfMenuObjCharSelect::returnSubMenu() { GF_MENU_REQUEST_EVENT(unknown001, unknown002); }

bool GfMenuObjCharSelect::attach(GfMenuCallContext *context) { return unknown151(context, unknown001); }

int GfMenuObjCharSelect::setFadeOut(u32 handle, u32 type) {
  int ctrl = unknown005(handle, type);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjCharSelect::setFadeOutSub(u32 handle, u32 type) { unknown005(handle, type); }

int GfMenuObjCharSelect::setFadeIn(u32 handle, u32 type) {
  GfMenuObjUtil::CtrlParam param;
  if (type == 0) {
    param.unknown08 = 1;
    param.unknown00 = GfMenuObjUtil::getPresetCtrlTime(6);
    param.unknown0c = 1;
  } else {
    param.unknown08 = 0x10000000;
    param.unknown50 = "cmn_fade_motion_lr";
    param.unknown58 = type == 2 ? "fade_in_r_early" : "fade_in_l_early";
    param.unknown11 = true;
  }
  param.unknown04 = 1;
  int ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjCharSelect::dispOnCopyChar(ui::UIObjectAcc &acc, u32 type) {
  GfMenuObjUtil::CtrlParam param;
  if (type == 0) {
    u32 handle = acc.searchChild("LAY_char_dr_move");
    param.unknown004("fade_in_r");
    param.unknown11 = true;
    GfMenuObjUtil::startCtrl(handle, param, nullptr);
    GfMenuObjCmnStatus::openDrStatus(1, -1);
  } else {
    u32 handle = acc.searchChild("LAY_char_bl_move");
    param.unknown004("fade_in_r");
    param.unknown11 = true;
    GfMenuObjUtil::startCtrl(handle, param, nullptr);
    GfMenuObjCmnStatus::openBlStatus(1, -1);
  }
}

void GfMenuObjCharSelect::dispOffCopyChar(ui::UIObjectAcc &acc, u32 type) {
  GfMenuObjUtil::CtrlParam param;
  if (type == 0) {
    u32 handle = acc.searchChild("LAY_char_dr_move");
    param.unknown004("warp_r");
    param.unknown11 = true;
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(handle, param, nullptr);
    GfMenuObjCmnStatus::closeDrStatus();
  } else {
    u32 handle = acc.searchChild("LAY_char_bl_move");
    param.unknown004("warp_r");
    param.unknown11 = true;
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(handle, param, nullptr);
    GfMenuObjCmnStatus::closeBlStatus();
  }
}

void GfMenuObjCharSelect::moveCharSubMenuIn(ui::UIObjectAcc &acc, u32 kind, mm::mtl::FixedArray<int, 8> controls, bool fade, bool solo) {
  GfMenuObjUtil::CtrlParam param;
  ui::UIObjectAcc menu(acc.searchChild("LAY_sub_menu"));
  mm::Rect<s16> rect;
  menu.getLayoutRect("character", rect);
  for (u32 i = 0; i < 4; i++) {
    const char *name = unknown008[i];
    if (i == 0 && solo) {
      name = "LAY_char_dr_solo";
    }
    u32 layer = acc.searchChild(name);
    if (i == kind) {
      // The game's code (1.0.0: 0x71004327bc) holds `mov w0, wzr` of both getReference...ID(0) calls above the `if`. clang 3.9 (with -g) hoists it only when
      // a variable holding a constant precedes the branch (240 instructions against the game's 238 without), so `move` starts at 0 (the store is dead).
      u32 move = 0;
      if (i == 0) {
        u32 driver = GfMenuReference::getReferenceDriverID(0);
        ui::UIObjectAcc character(acc.searchChild("LAY_char_dr_move"));
        character.setDisp(true);
        move = character.unknown10;
        setCharPosScale(0, driver, 4, false);
      } else {
        u32 blade = GfMenuReference::getReferenceBladeID(0);
        ui::UIObjectAcc character(acc.searchChild("LAY_char_bl_move"));
        character.setDisp(true);
        move = character.unknown10;
        setCharPosScale(1, blade, 4, false);
      }
      param.unknown004("warp_r");
      param.unknown14 = 10;
      param.unknown11 = true;
      GfMenuObjUtil::startCtrl(layer, param, nullptr);
      if (fade) {
        param.unknown004("fade_in_l");
        param.unknown14 = 0;
        param.unknown11 = true;
        GfMenuObjUtil::startCtrl(move, param, nullptr);
      } else {
        ui::UIObjectAcc(move).setDisp(true);
      }
    } else {
      param.unknown08 = 2;
      param.unknown0c = 0;
      param.unknown00 = 0.4f;
      GfMenuObjUtil::startCtrl(layer, param, nullptr);
    }
  }
}

void GfMenuObjCharSelect::update() {
  unknown430.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjCharSelect::seqStreamWaitStatDrBefore() {
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc move(acc.searchChild("LAY_char_dr_move"));
  int ctrl = GfMenuObjUtil::getCtrlID(move.unknown10);
  if (ctrl != -1) {
    GfMenuObjUtil::stopCtrl(ctrl);
  }
  return true;
}

bool GfMenuObjCharSelect::seqStreamWaitStatBlBefore() {
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc move(acc.searchChild("LAY_char_bl_move"));
  int ctrl = GfMenuObjUtil::getCtrlID(move.unknown10);
  if (ctrl != -1) {
    GfMenuObjUtil::stopCtrl(ctrl);
  }
  return true;
}

bool GfMenuObjCharSelect::seqConfSpecialWaitError() {
  if (!GfMenuManager::isOpenCommonWindow()) {
    unknown430.unknown002(&GfMenuObjCharSelect::seqReturn);
    unknown6c0 = false;
    return true;
  }
  return false;
}

bool GfMenuObjCharSelect::seqReturn() {
  ui::UIObjectAcc acc(unknown18, "LAY_char");
  unknown140(acc.unknown10, 0x107, 0, 0.0f);
  return true;
}

bool GfMenuObjCharSelect::seqReturnChange() {
  ui::UIObjectAcc acc(unknown18, "LAY_char");
  unknown158(acc.unknown10, 0x107, 1, 0.0f);
  return true;
}

bool GfMenuObjCharSelect::seqSpNiaChangeDr() {
  SCOM_NIA_BLADE::create(false);
  return true;
}

void GfMenuObjCharSelect::dispOnChar(u32 type) {
  ui::UIObjectAcc acc(getAttachedObject(unknown001));
  if (acc.isValid()) {
    dispOnCopyChar(acc, type);
  }
}

void GfMenuObjCharSelect::dispOffChar(u32 type) {
  ui::UIObjectAcc acc(getAttachedObject(unknown001));
  if (acc.isValid()) {
    dispOffCopyChar(acc, type);
  }
}

void GfMenuObjCharSelect::execCharPosScale(u32 type) { unknown159(unknown001, 0x109, type); }

int GfMenuObjCharSelect::getEquipBladeNum(u32 driver, const mm::mtl::FixedArray<DriverData, 5> &party) {
  int num = 0;
  for (u32 i = 0; i < 5; i++) {
    if (party[i].unknown00 == driver) {
      for (u32 j = 0; j < 3; j++) {
        num += GfMenuObjUtil::isValidBlade(party[i].unknown04[j]);
      }
    }
  }
  return num;
}

int GfMenuObjCharSelect::setDriverPos(ui::UIObjectAcc &acc, mm::mtl::FixedArray<DriverData, 5> &party, u32 driver) {
  int bladeNum = getEquipBladeNum(driver, party);
  ui::UIObjectAcc status(acc.searchChild("LAY_status_dr"));
  ui::UIObjectAcc normal(acc.searchChild("LAY_char_dr"));
  ui::UIObjectAcc solo(acc.searchChild("LAY_char_dr_solo"));
  if (bladeNum == 0) {
    normal.setDisp(false);
    solo.setDisp(true);
    acc.setLayout(status.unknown10, "driver_index_layout_solo");
  } else {
    normal.setDisp(true);
    solo.setDisp(false);
    acc.setLayout(status.unknown10, "driver_index_layout_normal");
  }
  return bladeNum;
}

void GfMenuObjCharSelect::setCharOffset(ui::UIObjectAcc &acc, const mm::mtl::FixedArray<DriverData, 5> &party, u32 driver) {
  for (u32 i = 0; i < 5; i++) {
    if (party[i].unknown00 == driver) {
      setCharPosScale(0, driver, 0, getEquipBladeNum(driver, party) == 0);
      for (u32 j = 0; j < 3; j++) {
        u32 blade = party[i].unknown04[j];
        if (GfMenuObjUtil::isValidBlade(blade)) {
          setCharPosScale(1, blade, j + 1, false);
        }
      }
    }
  }
}

bool GfMenuObjCharSelect::seqStreamWaitStatDr() {
  unknown007.m_charBusy = true;
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc image(acc.searchChild("IMG_char_dr_move_img"));
  if (image.isStreaming()) {
    return false;
  }
  ui::UIObjectAcc move(acc.searchChild("LAY_char_dr_move"));
  setFadeIn(move.unknown10, 0);
  return true;
}

bool GfMenuObjCharSelect::seqStreamWaitStatBl() {
  unknown007.m_charBusy = true;
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc image(acc.searchChild("IMG_char_bl_move_img"));
  if (image.isStreaming()) {
    return false;
  }
  ui::UIObjectAcc move(acc.searchChild("LAY_char_bl_move"));
  setFadeIn(move.unknown10, 0);
  return true;
}

bool GfMenuObjCharSelect::seqSpNiaChangeBl() {
  SCOM_NIA_BLADE::create(true);
  for (u32 i = 0; i < m_menuDriverList->getSize(); i++) {
    if (m_menuDriverList->getContents(i).unknown00 == 2 && i < 3) {
      GfMenuObjPartyStatus::memberChange(i + 1, 0);
      break;
    }
  }
  return true;
}

void GfMenuObjCharSelect::adjustBladeList(mm::mtl::FixedArray<DriverData, 5> &party, mm::mtl::FixedVector<u16, 422> &blades, mm::mtl::FixedArray<GfMenuBladeList *, 3> &lists, u32 driver) {
  u32 index = 0;
  while (party[index].unknown00 != driver) {
    if (++index == 5) {
      return;
    }
  }
  for (u32 i = 0; i < 3; i++) {
    u32 blade = party[index].unknown04[i];
    lists[i]->clear();
    if (blade != 0 && GfMenuObjUtil::isValidBlade(blade)) {
      MenuBladeInfo info;
      info.unknown00 = blade;
      info.unknown04 = driver;
      lists[i]->addContents(info);
      lists[i]->setIndex(0);
    }
  }
}

bool GfMenuObjCharSelect::seqStreamWaitSelectBefore() {
  ui::UIObjectAcc acc(unknown18);
  int bladeNum = getEquipBladeNum(GfMenuReference::getReferenceDriverID(0), unknown3a8);
  for (u32 i = 0; i < 4; i++) {
    const char *name = "LAY_char_dr_solo";
    if (i != 0 || bladeNum != 0) {
      name = unknown008[i];
    }
    ui::UIObjectAcc layer(acc.searchChild(name));
    int ctrl = GfMenuObjUtil::getCtrlID(layer.unknown10);
    if (ctrl != -1) {
      GfMenuObjUtil::stopCtrl(ctrl);
    }
  }
  return true;
}

bool GfMenuObjCharSelect::seqStreamWaitSelect() {
  unknown007.m_selectBusy = true;
  ui::UIObjectAcc acc(unknown18);
  int bladeNum = getEquipBladeNum(GfMenuReference::getReferenceDriverID(0), unknown3a8);
  {
    ui::UIObjectAcc image(acc.searchChild(bladeNum == 0 ? "IMG_char_dr_img_solo" : "IMG_char_dr_img"));
    if (image.isStreaming()) {
      return false;
    }
  }
  {
    ui::UIObjectAcc image(acc.searchChild("IMG_char_bl_img@01"));
    if (image.isStreaming()) {
      return false;
    }
  }
  {
    ui::UIObjectAcc image(acc.searchChild("IMG_char_bl_img@02"));
    if (image.isStreaming()) {
      return false;
    }
  }
  {
    ui::UIObjectAcc image(acc.searchChild("IMG_char_bl_img@03"));
    if (image.isStreaming()) {
      return false;
    }
  }
  for (u32 i = 0; i < 4; i++) {
    const char *name = "LAY_char_dr_solo";
    if (i != 0 || bladeNum != 0) {
      name = unknown008[i];
    }
    ui::UIObjectAcc layer(acc.searchChild(name));
    setFadeIn(layer.unknown10, 0);
  }
  return true;
}

bool GfMenuObjCharSelect::seqWaitSelect() {
  if (unknown007.m_selectBusy) {
    return false;
  }
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc layer(acc.searchChild("LAY_char"));
  if (!unknown741) {
    GfMenuObjMainMenu2::openCharChange(layer.unknown10, 3, false);
  }
  enableInput(layer.unknown10);
  GfMenuObjMainMenu2::setSystemKeyEnable(true);
  return true;
}

bool GfMenuObjCharSelect::getCharBusy() { return unknown007.m_charBusy; }

bool GfMenuObjCharSelect::getSelectBusy() { return unknown007.m_selectBusy; }

bool GfMenuObjCharSelect::chkSubMenuSpec(u32 character) {
  // The game's code (1.0.0: 0x710042e1bc) has one shared `return true` block (`tbnz` after isCustomEnableDriver, `tbz` after isCustomEnableBlade). Without
  // the bool scoped to the if/else, the same source gives a second `return true` block in the driver branch and one instruction more (21 against 20);
  // the variable changes the block shape, not the register allocation.
  if (bool isDriver = GfDataDriver::isDriver(character)) {
    if (GfMenuObjUtil::isCustomEnableDriver(character)) {
      return true;
    }
  } else if (GfMenuObjUtil::isCustomEnableBlade(character)) {
    return true;
  }
  return false;
}

// Inferred helper: tints the image of a character white when it is selected and gray otherwise; original name unknown.
static void unknown012(ui::UIObjectAcc &acc, const char *name, bool isSelected) {
  ui::UIObjectAcc image(acc.searchChild(name));
  image.setMulColor(isSelected ? "white" : "char_unselect");
}

// Inferred helper: starts the fade of the background of a layer and hooks its end on a handle; original name unknown.
static void unknown013(u32 handle, ui::UIObjectAcc &layer) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 0;
  param.unknown04 = 4;
  param.unknown00 = 0.06f;
  int ctrl = GfMenuObjUtil::startCtrl(layer.searchChild("LAY_bg"), param, nullptr);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
}

// Inferred helper: sets up the emotion fade of a control with a motion name; original name unknown. A helper that also starts the control (taking the handle) gives another
// stack slot for the CtrlParam (61 differing lines in CharListener::reciveEvent, 12 in SubMenuListener::reciveEvent); taking the CtrlParam matches in both.
static void unknown014(GfMenuObjUtil::CtrlParam &param, const char *motion) {
  param.unknown08 = 0x10000000;
  param.unknown50 = "cmn_fade_emotion";
  param.unknown58 = motion;
}

void GfMenuObjCharSelect::CharListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(m_menuObjCharSelect->unknown18);
  switch (event.unknown00) {
  case 1:
    if (!m_menuObjCharSelect->unknown741) {
      unknown164(handle, GfMenuTypes::unknown003_33);
    } else {
      acc.setDisp(false);
      unknown164(owner.searchChild("LAY_sub_menu"), GfMenuTypes::unknown003_33);
    }
    break;
  case 3:
    if (event.unknown08 == 4) {
      u32 driver = GfMenuReference::getReferenceDriverID(0);
      ui::UIObjectAcc main(owner.searchChild("LAY_main"));
      setDriverPos(main, m_menuObjCharSelect->unknown3a8, driver);
      setCharOffset(main, m_menuObjCharSelect->unknown3a8, driver);
      m_menuObjCharSelect->unknown768 = false;
    }
    break;
  case 6: {
    u64 params = event.unknown08_u64;
    int selected = params;
    int previous = params >> 32;
    if (selected != -1 && selected != previous) {
      // The game compares the slot signed against 1 and unsigned against 3 (`cmp w27, #1; b.lt` 0x710042d1b0, `cmp w27, #3; b.hi` 0x710042d1b8); the compares against
      // 3 below (`slot`, the glow test) are unsigned too, a signed one gives another block order or 1335 instructions.
      if (selected >= 1 && selected <= 3u) {
        // The game calls getIndex(false) and getSize() on the list and drops both results (0x710042d1d8, 0x710042d1e8, ruling 5): 1326 instructions against 1336 without them.
        m_menuObjCharSelect->unknown30[selected - 1]->getIndex(false);
        m_menuObjCharSelect->unknown30[selected - 1]->getSize();
        GfMenuBladeList *list = m_menuObjCharSelect->unknown30[selected - 1];
        u32 blade = list->getContents(list->getIndex(false)).unknown00;
        // `isValid` is the loop flag: with `while (!isValidBlade(blade))` the loop is laid out differently (first difference at 0x710042d830).
        bool isValid = GfMenuObjUtil::isValidBlade(blade);
        while (!isValid) {
          int slot = selected < 3u ? selected : 0;
          list = m_menuObjCharSelect->unknown30[slot];
          blade = list->getContents(list->getIndex(false)).unknown00;
          isValid = GfMenuObjUtil::isValidBlade(blade);
          selected = slot + 1;
        }
        GfMenuReference::setReferenceBladeID(0, blade);
      } else {
        GfMenuDriverList *drivers = m_menuObjCharSelect->m_menuDriverList;
        GfMenuReference::setReferenceDriverID(0, drivers->getContents(drivers->getIndex(false)).unknown00);
      }
      m_menuObjCharSelect->unknown3f8 = selected;
      m_menuObjCharSelect->updateSpecialOperation();
      for (u32 i = 0; i < 5; i++) {
        ui::UIObjectAcc glow(acc.searchChild(i != 4 ? unknown011[i] : "IMG_char_dr_glow_solo"));
        glow.setAlpha(0.0f);
        glow.setDisp(false);
        int ctrl = m_menuObjCharSelect->unknown750[i];
        if (ctrl != -1 && ctrl == GfMenuObjUtil::getCtrlID(glow.unknown10)) {
          GfMenuObjUtil::stopCtrl(m_menuObjCharSelect->unknown750[i]);
          m_menuObjCharSelect->unknown750[i] = -1;
        }
      }
      if (selected >= 0) {
        // The game sign-extends the slot once, between its two range tests (`tbnz w27, #31` 0x710042d91c, `cmp w27, #3` 0x710042d920, `sxtw x21, w27` 0x710042d92c), and
        // indexes the glow names (0x710042d94c) and the fade layers (0x710042dc54) with that register. Without the 64-bit index the tests merge into one `cmp #4; b.hs`
        // and each load folds the extension (1334 instructions against 1336).
        s64 selectedIndex = selected;
        if (selected <= 3u) {
          int bladeNum = getEquipBladeNum(GfMenuReference::getReferenceDriverID(0), m_menuObjCharSelect->unknown3a8);
          const char *name;
          u32 index = selected;
          if (bladeNum == 0 && selected == 0) {
            index = 4;
            name = "IMG_char_dr_glow_solo";
          } else {
            name = unknown011[selectedIndex];
          }
          ui::UIObjectAcc glow(acc.searchChild(name));
          GfMenuObjUtil::CtrlParam param;
          // Store order searched over all 720 orders with unknown18 last: only 08, 00, 3c, 10, 14, 0c, 18 gives the game's merged and paired stores.
          param.unknown08 = 4;
          param.unknown00 = 2.0f;
          param.unknown3c = 0.5f;
          param.unknown10 = true;
          param.unknown14 = 8;
          param.unknown0c = 3;
          param.unknown18 = m_menuObjCharSelect->unknown750[index];
          m_menuObjCharSelect->unknown750[index] = GfMenuObjUtil::startCtrl(glow.unknown10, param, nullptr);
          for (u32 i = 0; i < 4; i++) {
            ui::UIObjectAcc layer(acc.searchChild(unknown008[i]));
            u16 priority = m_menuObjCharSelect->unknown6c4[i];
            if (selected == i) {
              priority = priority + 1;
            }
            layer.setDispPriority(priority);
          }
          if (previous >= 0 && !m_menuObjCharSelect->unknown429) {
            GfMenuObjUtil::CtrlParam fade;
            unknown014(fade, "fade_in_select");
            fade.unknown11 = true;
            GfMenuObjUtil::startCtrl(acc.searchChild(unknown008[selectedIndex]), fade, nullptr);
          }
          m_menuObjCharSelect->unknown429 = false;
        }
      }
      unknown012(acc, "IMG_char_dr_img", selected == 0);
      unknown012(acc, "IMG_char_bl_img@01", selected == 1);
      unknown012(acc, "IMG_char_bl_img@02", selected == 2);
      unknown012(acc, "IMG_char_bl_img@03", selected == 3);
      if (previous != -1 && selected != previous) {
        GfMenuObjUtil::playSECommonCursor();
      }
    }
    break;
  }
  // The cases 0x140 and 0x108 of this listener are written in the order of the game's stack slots: with 0x140 after 0x108 the temporary accessor of its
  // `setAlpha` takes the first of the three unshared slots instead of the last (0x42cc14, `add x0, sp, #64` against `#16`).
  case 0x140: {
    m_menuObjCharSelect->refreshCharSelect(event.unknown08);
    m_menuObjCharSelect->updateSpecialOperation();
    int bladeNum = getEquipBladeNum(GfMenuReference::getReferenceDriverID(0), m_menuObjCharSelect->unknown3a8);
    const char *name = bladeNum == 0 ? "LAY_char_dr_solo" : "LAY_char_dr";
    GfMenuObjUtil::setChildDisp(acc.unknown10, name, false);
    ui::UIObjectAcc(acc.searchChild(name)).setAlpha(0.0f);
    mm::mtl::FixStr<32> layerName;
    for (int i = 1; i < 4; i++) {
      layerName.format("LAY_char_bl@%02d", i);
      GfMenuObjUtil::setChildDisp(acc.unknown10, layerName.c_str(), false);
    }
    unknown007.m_selectBusy = true;
    for (u32 i = 0; i < 4; i++) {
      ui::UIObjectAcc glow(acc.searchChild(unknown011[i]));
      int ctrl = m_menuObjCharSelect->unknown750[i];
      if (ctrl != -1 && ctrl == GfMenuObjUtil::getCtrlID(glow.unknown10)) {
        GfMenuObjUtil::stopCtrl(m_menuObjCharSelect->unknown750[i]);
        m_menuObjCharSelect->unknown750[i] = -1;
      }
      glow.setAlpha(0.0f);
      glow.setDisp(false);
    }
    for (u32 i = 0; i < 4; i++) {
      ui::UIObjectAcc layer(acc.searchChild(unknown008[i]));
      layer.setDispPriority(m_menuObjCharSelect->unknown6c4[i]);
    }
    m_menuObjCharSelect->unknown430.unknown005();
    m_menuObjCharSelect->unknown430.unknown002(&GfMenuObjCharSelect::seqStreamWaitSelectBefore);
    m_menuObjCharSelect->unknown430.unknown004(1);
    m_menuObjCharSelect->unknown430.unknown002(&GfMenuObjCharSelect::seqStreamWaitSelect);
    disableInput(handle);
    ui::UIObjectAcc main(owner.searchChild("LAY_main"));
    unknown013(handle, main);
    break;
  }
  case 8:
    if (unknown007.m_selectBusy) {
      break;
    }
    switch (event.unknown0c) {
    case 1: {
      u32 character;
      if (m_menuObjCharSelect->unknown3f8 == 0) {
        GfMenuDriverList *drivers = m_menuObjCharSelect->m_menuDriverList;
        character = drivers->getContents(drivers->getIndex(false)).unknown00;
      } else {
        GfMenuBladeList *list = m_menuObjCharSelect->unknown30[m_menuObjCharSelect->unknown3f8 - 1];
        character = list->getContents(list->getIndex(false)).unknown00;
      }
      if (!m_menuObjCharSelect->chkSubMenuSpec(character)) {
        GfMenuObjUtil::playSECommon(2);
      } else {
        unknown164(handle, GfMenuTypes::unknown003_34);
        unknown163(owner.searchChild("LAY_sub_menu"), GfMenuTypes::unknown003_33, 0);
        disableInput(handle);
        GfMenuObjMainMenu2::setSystemKeyEnable(false);
        GfMenuObjMainMenu2::disableCharChange();
        GfMenuObjUtil::playSECommonDecide();
      }
      break;
    }
    case 2:
      unknown164(owner.searchChild("LAY_main"), GfMenuTypes::unknown003_34);
      disableInput(handle);
      GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
      break;
    case 9:
      if (GfMenuObjUtil::getMenuCondition(0x23)) {
        GfMenuObjMainMenu2::setSubLayer(getMenuLayerID(0x24));
        changeFSSubLayer(owner.unknown10, 1, getMenuLayerID(0x24), true);
        GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
        GfMenuObjUtil::playSECommonDecide();
      }
      break;
    case 0xd:
      if (m_menuObjCharSelect->unknown748 < 4) {
        m_menuObjCharSelect->unknown6c0 = false;
        m_menuObjCharSelect->unknown430.unknown005();
        m_menuObjCharSelect->unknown430.unknown002(&GfMenuObjCharSelect::seqConfSpecial);
        disableInput(handle);
        GfMenuObjMainMenu2::disableCharChange();
        GfMenuObjMainMenu2::cancelEnableMainMenu(false);
      }
      break;
    }
    break;
  case 0x108:
    m_menuObjCharSelect->unknown430.unknown002(&GfMenuObjCharSelect::seqWaitSelect);
    // fall through
  case GfMenuTypes::unknown003_33: {
    ui::EventData sendData;
    sendData.unknown00 = 6;
    sendData.unknown08 = m_menuObjCharSelect->unknown3f8;
    sendData.unknown0c = -1;
    ui::UIManager::get()->requestObjectEvent(handle, sendData, 0.0f);
    GfMenuObjOperationInfo::add(handle, 0, 0, 0);
    GfMenuObjOperationInfo::changeText(handle, 9, !GfMenuObjUtil::getMenuCondition(0x23));
    setInputActionEnable(handle, 0xd, false);
    GfMenuDriverList *drivers = m_menuObjCharSelect->m_menuDriverList;
    u32 driver = drivers->getContents(drivers->getIndex(false)).unknown00;
    ui::UIObjectAcc main(owner.searchChild("LAY_main"));
    int bladeNum = getEquipBladeNum(driver, m_menuObjCharSelect->unknown3a8);
    resetInputSelection(handle);
    setupInputSelection(handle, m_menuObjCharSelect->unknown3f8, bladeNum + 1);
    adjustBladeList(m_menuObjCharSelect->unknown3a8, m_menuObjCharSelect->unknown50, m_menuObjCharSelect->unknown30, driver);
    // The accessors live in a scope of their own: their stack slots are reused by the later ones (ruling 3); without the scope the function has 1356 instructions against 1336.
    {
      ui::UIObjectAcc layer(acc.searchChild("LAY_char_dr"));
      ui::UIObjectAcc solo(acc.searchChild("LAY_char_dr_solo"));
      layer.setDisp(false);
      solo.setDisp(false);
      if (bladeNum == 0) {
        ui::UIObjectAcc status(acc.searchChild("LAY_status_dr"));
        acc.setLayout(status.unknown10, "driver_index_layout_solo");
      }
    }
    unknown013(handle, main);
    break;
  }
  case GfMenuTypes::unknown003_34:
    disableInput(acc.searchChild("LAY_char_dr"));
    disableInput(acc.searchChild("LAY_char_bl@01"));
    disableInput(acc.searchChild("LAY_char_bl@02"));
    disableInput(acc.searchChild("LAY_char_bl@03"));
    disableInput(handle);
    GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
    break;
  case GfMenuTypes::unknown003_257:
  case GfMenuTypes::unknown003_258: {
    // The game loads event.unknown08 into a callee-saved register before resetInputSelection (0x710042cb10, ruling 2).
    int count = event.unknown08;
    resetInputSelection(handle);
    setupInputSelection(handle, 0, count + 1);
    if (event.unknown00 == GfMenuTypes::unknown003_257) {
      acc.setAlpha(0.0f);
      setFadeIn(handle, 0);
    }
    break;
  }
  case GfMenuTypes::unknown003_259: {
    // The game loads event.unknown08 before the load of unknown3f8 (0x710042d390, ruling 2).
    int count = event.unknown08;
    setupInputSelection(handle, m_menuObjCharSelect->unknown3f8, count + 1);
    break;
  }
  case 0x107:
    if (event.unknown08 == 1) {
      unknown140(handle, 0x140, GfMenuReference::getReferenceDriverID(0), 0.0f);
    } else {
      m_menuObjCharSelect->updateSpecialOperation();
    }
    if (!m_menuObjCharSelect->unknown741) {
      GfMenuObjMainMenu2::openCharChange(acc.unknown10, 3, false);
    }
    GfMenuObjMainMenu2::cancelEnableMainMenu(true);
    enableInput(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjCharSelect::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    setupCharSelect(acc, m_menuObjCharSelect->m_menuDriverList, m_menuObjCharSelect->unknown30);
    setupCharSelectCopy(acc);
    GfDataBlade::getListReserverWithSolo(m_menuObjCharSelect->unknown50);
    for (u16 *it = m_menuObjCharSelect->unknown50.begin(); it != m_menuObjCharSelect->unknown50.end();) {
      if (*it == BLADE_HIKARI || *it == BLADE_HOMURI) {
        it = m_menuObjCharSelect->unknown50.erase(it);
      } else {
        ++it;
      }
    }
    setPartyData(m_menuObjCharSelect->unknown3a8, m_menuObjCharSelect->m_menuDriverList);
    GfMenuObjOperationInfo::setGuideText(1, 0);
    GfMenuObjMainMenu2::setSubIndexText(1);
    acc.setDisp(false);
    m_menuObjCharSelect->unknown768 = !m_menuObjCharSelect->unknown741;
    m_menuObjCharSelect->unknown430.unknown005();
    m_menuObjCharSelect->unknown430.unknown002(&GfMenuObjCharSelect::seqStreamWait);
    // The three loops stay written out (ruling 8): a template helper taking the list, the BDAT table and the count (clear, getFP and the loop) gives 997 instructions against
    // the game's 1009 (227 differing lines, first difference 0x710042ab84); one holding only the loop and taking the table pointer gives 1000 (228 lines).
    m_menuObjCharSelect->unknown6f0.clear();
    u8 *driverOrder = GfDataBdat::getFP(BDAT_MNU_CHAR_DRIVER_ORDER);
    for (int i = 0; i < 5; i++) {
      int id = Bdat::getIdTop(driverOrder) + i;
      if (GfMenuObjUtil::getMenuCondition(Bdat::getVal(driverOrder, "useCond", id).valueU16)) {
        m_menuObjCharSelect->unknown6f0.push_back(id);
      }
    }
    m_menuObjCharSelect->unknown710.clear();
    u8 *bladeOrder = GfDataBdat::getFP(BDAT_MNU_CHAR_BLADE_ORDER);
    for (int i = 0; i < 3; i++) {
      int id = Bdat::getIdTop(bladeOrder) + i;
      if (GfMenuObjUtil::getMenuCondition(Bdat::getVal(bladeOrder, "useCond", id).valueU16)) {
        m_menuObjCharSelect->unknown710.push_back(id);
      }
    }
    m_menuObjCharSelect->unknown728.clear();
    u8 *hanaOrder = GfDataBdat::getFP(BDAT_MNU_CHAR_HANA_ORDER);
    for (int i = 0; i < 4; i++) {
      int id = Bdat::getIdTop(hanaOrder) + i;
      if (GfMenuObjUtil::getMenuCondition(Bdat::getVal(hanaOrder, "useCond", id).valueU16)) {
        m_menuObjCharSelect->unknown728.push_back(id);
      }
    }
    m_menuObjCharSelect->unknown740 = true;
    break;
  }
  case 2:
    m_menuObjCharSelect->unknown430.unknown005();
    GfMenuObjMainMenu2::closeCharChange();
    if (m_menuObjCharSelect->unknown428) {
      RQ_SETUP_PARTY party;
      RQ_SETUP_PARTY::Member *member = party.unknown00;
      for (u32 i = 0; i < 5; i++, member++) {
        const DriverData &driver = m_menuObjCharSelect->unknown3a8[i];
        member->unknown00 = driver.unknown00;
        member->unknown04 = 0;
        member->unknown08[0] = driver.unknown04[0];
        member->unknown08[1] = driver.unknown04[1];
        member->unknown08[2] = driver.unknown04[2];
      }
      party.unknownc8 = 3;
      party.unknowncc = 0;
      GfReqCommand::reqChangeParty(party);
    }
    if (!m_menuObjCharSelect->unknown740) {
      ui::EventData sendData;
      sendData.unknown00 = 3;
      sendData.unknown08 = 2;
      ui::UIManager::get()->requestObjectEvent(handle, sendData, 0.0f);
    } else {
      setFadeOut(handle, 0);
    }
    break;
  // Only a case label and one call are shared with other listeners. A helper form that takes the arm out of the switch (`if (unknown019(acc, type)) return;` before it, holding the
  // test `type == unknown003_33` and `setDisp(true)`) gives 1009 instructions and 0 differing lines only because clang folds it back into the switch: it is not a block, so the arm stays.
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    setFadeOutSub(handle, 0);
    disableInput(acc.searchChild("LAY_char"));
    break;
  case 0x24:
    disableInput(acc.searchChild("LAY_char"));
    hookCtrlEvent(0, unknown005(handle, 0));
    m_menuObjCharSelect->unknown740 = false;
    break;
  case GfMenuTypes::unknown003_260:
    unknown164(acc.searchChild("LAY_sub_menu"), GfMenuTypes::unknown003_260);
    break;
  case 0x109: {
    m_menuObjCharSelect->unknown764 = event.unknown08;
    if (m_menuObjCharSelect->unknown764 == 0) {
      GfMenuObjUtil::setChildDisp(acc.unknown10, "LAY_char_dr_move", false);
    } else {
      GfMenuObjUtil::setChildDisp(acc.unknown10, "LAY_char_bl_move", false);
    }
    unknown007.m_charBusy = true;
    if (m_menuObjCharSelect->unknown764 == 0) {
      m_menuObjCharSelect->seqStreamWaitStatDrBefore();
    } else {
      m_menuObjCharSelect->seqStreamWaitStatBlBefore();
    }
    // unknown013 (the same four statements) gives 1011 instructions against the game's 1009 here (measured), so the block stays written out (ruling 8).
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0;
    param.unknown04 = 4;
    param.unknown00 = 0.06f;
    int ctrl = GfMenuObjUtil::startCtrl(acc.searchChild("LAY_bg"), param, nullptr);
    hookCtrlEvent(acc.unknown10, ctrl);
    break;
  }
  case 3:
    switch (event.unknown08) {
    case 2:
      acc.setTerm();
      break;
    case 1:
      if (!m_menuObjCharSelect->unknown741) {
        ui::UIObjectAcc layer(acc.searchChild("LAY_char"));
        GfMenuObjMainMenu2::openCharChange(layer.unknown10, 3, true);
        enableInput(layer.unknown10);
        GfMenuObjMainMenu2::setSystemKeyEnable(true);
      }
      break;
    case 4: {
      int kind = m_menuObjCharSelect->unknown764;
      m_menuObjCharSelect->unknown430.unknown005();
      m_menuObjCharSelect->unknown430.unknown004(1);
      if (kind == 0) {
        m_menuObjCharSelect->unknown430.unknown002(&GfMenuObjCharSelect::seqStreamWaitStatDr);
        setCharPosScale(0, GfMenuReference::getReferenceDriverID(0), 4, false);
      } else {
        m_menuObjCharSelect->unknown430.unknown002(&GfMenuObjCharSelect::seqStreamWaitStatBl);
        setCharPosScale(1, GfMenuReference::getReferenceBladeID(0), 4, false);
      }
      break;
    }
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjCharSelect::DetailListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown0c = 0;
    break;
  case 8:
    if (event.unknown0c == 2) {
      GfMenuObjMainMenu2::setSubIndexText(unknown0c == 0 ? 2 : 3);
    }
    break;
  case GfMenuTypes::unknown003_33: {
    int type = event.unknown08;
    acc.setDisp(true);
    GfMenuObjMainMenu2::setSubIndexText(type == 0 ? 0x12 : 0x13);
    enableInput(acc.unknown10);
    unknown0c = type;
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjCharSelect::StatusListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(m_menuObjCharSelect->unknown18);
  switch (event.unknown00) {
  case 1:
    break;
  case 0x105: {
    acc.getPos(m_menuObjCharSelect->unknown6d4);
    mm::Rect<s16> rect;
    switch (event.unknown08) {
    case 0x1d:
    case 0x20: {
      const char *name = event.unknown08 == 0x1d ? "drindex_atst" : "drindex_acs";
      ui::UIObjectAcc main(owner.searchChild("LAY_main"));
      main.getLayoutRect(name, rect);
      mm::Pnt<s16> pos;
      pos.x = rect.x;
      pos.y = rect.y;
      acc.setPos(pos);
      break;
    }
    case 0x1e: {
      ui::UIObjectAcc main(owner.searchChild("LAY_main"));
      main.getLayoutRect("drindex_atst", rect);
      mm::Pnt<s16> pos;
      pos.x = -(m_menuObjCharSelect->unknown6d4.x + rect.width);
      pos.y = rect.y;
      acc.setPos(pos);
      break;
    }
    }
    break;
  }
  case 0x106:
    acc.setPos(m_menuObjCharSelect->unknown6d4);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjCharSelect::CharDrListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(m_menuObjCharSelect->unknown18);
  if (event.unknown00 != 1) {
    if (event.unknown00 == 3) {
      if (event.unknown08 == 0) {
        return;
      }
      if (event.unknown08 == 1) {
        unknown007.m_selectBusy = false;
        enableInput(acc.searchChild("LAY_char"));
      }
    }
    ui::UIObjectListener::reciveEvent(event, handle);
  }
}

void GfMenuObjCharSelect::CharDrSoloListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(m_menuObjCharSelect->unknown18);
  if (event.unknown00 != 1) {
    if (event.unknown00 == 3) {
      if (event.unknown08 == 0) {
        return;
      }
      if (event.unknown08 == 1) {
        unknown007.m_selectBusy = false;
        enableInput(acc.searchChild("LAY_char"));
      }
    }
    ui::UIObjectListener::reciveEvent(event, handle);
  }
}

void GfMenuObjCharSelect::CharBlMoveListener::reciveEvent(const ui::EventData &event, u32 handle) {
  if (event.unknown00 == 1) {
    return;
  }
  if (event.unknown00 == 3) {
    if (event.unknown08 == 0) {
      return;
    }
    if (event.unknown08 == 1) {
      unknown007.m_charBusy = false;
    }
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjCharSelect::CharDrMoveListener::reciveEvent(const ui::EventData &event, u32 handle) {
  if (event.unknown00 == 1) {
    return;
  }
  if (event.unknown00 == 3) {
    if (event.unknown08 == 0) {
      return;
    }
    if (event.unknown08 == 1) {
      unknown007.m_charBusy = false;
    }
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjCharSelect::SubMenuListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(m_menuObjCharSelect->unknown18);
  switch (event.unknown00) {
  case 1: {
    setupCharSubMenu(acc, m_menuObjCharSelect->unknown6f0, m_menuObjCharSelect->unknown710, m_menuObjCharSelect->unknown728);
    // A static helper holding these statements (taking `handle` and `owner`, returning the cursor) gives 2715 instructions as the game and 156 differing lines (frame of 864 bytes
    // against 880, first difference 0x710042f23c), so the block stays written out (ruling 8).
    GfMenuObjUtil::CursorParam param;
    param.unknown00 = ui::UIObjectAcc(handle).getParentHandle();
    param.unknown04 = owner.searchChild("IMG_sub_cursor");
    param.unknown1a = 0;
    param.m_cursorSetting.unknown18 = 0;
    param.unknown08 = "LAY_sub_menu_dr@%02d";
    m_menuObjCharSelect->unknown48 = GfMenuObjUtil::createCursor(param);
    // The two getLayoutRect calls only share their shape with other functions (a Rect and one call, with different names). A wrapper of both calls taking the accessor and the two
    // rects gives 2715 instructions and 0 differing lines, but it is a helper of two calls with one user, so it is not written.
    mm::Rect<s16> rect;
    acc.getLayoutRect("icon_layout_center", rect);
    mm::Rect<s16> range;
    acc.getLayoutRect("icon_layout_range", range);
    u32 interval = range.x - rect.x - 1;
    mm::Pnt<s16> pos(rect.x + rect.width / 2, rect.y + rect.height / 2);
    ui::UISelectObjList::CreateParam createParam;
    createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
    ui::UISelectObjList *list = ui::UISelectObjList::create(createParam);
    // The three loops stay written out (ruling 8): a template helper holding the loop and placeObjectH, called three times with the list type as the parameter, gives 2712
    // instructions against the game's 2715 (667 differing lines, first difference 0x710042f24c, 1.0.0: 0x710042f220 for the function); one holding only the loop gives the same
    // numbers, and one taking the count gives 2706 (685 lines).
    for (u32 i = 0; i < m_menuObjCharSelect->unknown6f0.size(); i++) {
      mm::mtl::FixStr<32> name;
      name.format("LAY_sub_menu_dr@%02d", i + 1);
      list->addContents(acc.searchChild(name.c_str()));
    }
    GfMenuObjUtil::placeObjectH(list, pos, interval);
    list->clear();
    for (u32 i = 0; i < m_menuObjCharSelect->unknown710.size(); i++) {
      mm::mtl::FixStr<32> name;
      name.format("LAY_sub_menu_bl@%02d", i + 1);
      list->addContents(acc.searchChild(name.c_str()));
    }
    GfMenuObjUtil::placeObjectH(list, pos, interval);
    list->clear();
    for (u32 i = 0; i < m_menuObjCharSelect->unknown728.size(); i++) {
      mm::mtl::FixStr<32> name;
      name.format("LAY_sub_menu_hana@%02d", i + 1);
      list->addContents(acc.searchChild(name.c_str()));
    }
    GfMenuObjUtil::placeObjectH(list, pos, interval);
    mm::mtl::safeRelease(list);
    disableInput(handle);
    unknown0c = 0;
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
  case 0x140: {
    unknown007.m_charBusy = true;
    if (m_menuObjCharSelect->unknown3f8 == 0) {
      u32 character = event.unknown08;
      GfMenuReference::setReferenceDriverID(0, character);
      GfMenuObjUtil::setChildDisp(owner.unknown10, "LAY_char_dr_move", false);
      m_menuObjCharSelect->seqStreamWaitStatDrBefore();
      m_menuObjCharSelect->unknown430.unknown005();
      m_menuObjCharSelect->unknown430.unknown004(1);
      m_menuObjCharSelect->unknown430.unknown002(&GfMenuObjCharSelect::seqStreamWaitStatDr);
    } else {
      u32 character = event.unknown08;
      GfMenuReference::setReferenceBladeID(0, character);
      sendEvent(handle, 0x108, character);
      GfMenuObjUtil::setChildDisp(owner.unknown10, "LAY_char_bl_move", false);
      m_menuObjCharSelect->seqStreamWaitStatBlBefore();
      m_menuObjCharSelect->unknown430.unknown005();
      m_menuObjCharSelect->unknown430.unknown004(1);
      m_menuObjCharSelect->unknown430.unknown002(&GfMenuObjCharSelect::seqStreamWaitStatBl);
    }
    ui::UIObjectAcc main(owner.searchChild("LAY_main"));
    unknown013(handle, main);
    break;
  }
  case 6: {
    int index = event.unknown08;
    int previous = event.unknown0c;
    m_menuObjCharSelect->unknown48->inputChange(index);
    if (m_menuObjCharSelect->unknown3f8 == 0) {
      if (index < m_menuObjCharSelect->unknown6f0.size()) {
        ui::UIObjectAcc number(acc.searchChild("TXT_index_dr"));
        ui::UIObjectAcc info(acc.searchChild("TXT_sub_menu_info_dr"));
        u8 *order = GfDataBdat::getFP(BDAT_MNU_CHAR_DRIVER_ORDER);
        int id = m_menuObjCharSelect->unknown6f0[index];
        u8 *bdat;
        u32 text;
        if (GfMenuObjUtil::getMenuCondition(Bdat::getVal(order, "useCond", id).valueU16)) {
          getMenuText(Bdat::getVal(order, "layer", id).valueU16, bdat, text);
          u8 *descBdat;
          u32 descText;
          getMenuDesc(Bdat::getVal(order, "layer", id).valueU16, descBdat, descText);
          info.setText(ui::UIStr(descBdat, descText));
        } else {
          bdat = GfDataBdat::getFP(BDAT_MENU_MS);
          text = 0x67c;
        }
        number.setText(ui::UIStr(bdat, text));
      }
    } else if (!GfDataHana::isValid(GfMenuReference::getReferenceBladeID(0))) {
      if (index < m_menuObjCharSelect->unknown710.size()) {
        u8 *order = GfDataBdat::getFP(BDAT_MNU_CHAR_BLADE_ORDER);
        int id = m_menuObjCharSelect->unknown710[index];
        u32 layer = Bdat::getVal(order, "layer", id).valueU16;
        u32 condition = Bdat::getVal(order, "useCond", id).valueU16;
        ui::UIObjectAcc number(acc.searchChild("TXT_index_bl"));
        ui::UIObjectAcc info(acc.searchChild("TXT_sub_menu_info_bl"));
        u8 *bdat;
        u32 text;
        if (GfMenuObjUtil::getMenuCondition(condition)) {
          getMenuText(layer, bdat, text);
          u8 *descBdat;
          u32 descText;
          getMenuDesc(Bdat::getVal(order, "layer", id).valueU16, descBdat, descText);
          info.setText(ui::UIStr(descBdat, descText));
        } else {
          bdat = GfDataBdat::getFP(BDAT_MENU_MS);
          text = 0x67c;
        }
        number.setText(ui::UIStr(bdat, text));
      }
    } else if (index < m_menuObjCharSelect->unknown728.size()) {
      u8 *order = GfDataBdat::getFP(BDAT_MNU_CHAR_HANA_ORDER);
      int id = m_menuObjCharSelect->unknown728[index];
      u32 layer = Bdat::getVal(order, "layer", id).valueU16;
      u32 condition = Bdat::getVal(order, "useCond", id).valueU16;
      ui::UIObjectAcc number(acc.searchChild("TXT_index_hana"));
      ui::UIObjectAcc info(acc.searchChild("TXT_sub_menu_info_hana"));
      u8 *bdat;
      u32 text;
      if (GfMenuObjUtil::getMenuCondition(condition)) {
        getMenuText(layer, bdat, text);
        u8 *descBdat;
        u32 descText;
        getMenuDesc(Bdat::getVal(order, "layer", id).valueU16, descBdat, descText);
        info.setText(ui::UIStr(descBdat, descText));
      } else {
        bdat = GfDataBdat::getFP(BDAT_MENU_MS);
        text = 0x67c;
      }
      number.setText(ui::UIStr(bdat, text));
    }
    if (index >= 0) {
      mm::mtl::FixStr<32> name;
      if (m_menuObjCharSelect->unknown3f8 == 0) {
        name.format("LAY_sub_menu_dr@%02d", index + 1);
      } else if (!GfDataHana::isValid(GfMenuReference::getReferenceBladeID(0))) {
        name.format("LAY_sub_menu_bl@%02d", index + 1);
      } else {
        name.format("LAY_sub_menu_hana@%02d", index + 1);
      }
      GfMenuObjUtil::CtrlParam param;
      unknown014(param, "fade_in_select");
      param.unknown11 = true;
      GfMenuObjUtil::startCtrl(acc.searchChild(name.c_str()), param, nullptr);
      m_menuObjCharSelect->unknown3fc = index;
    }
    if (previous >= 0 && index != previous) {
      GfMenuObjUtil::playSECommonCursor();
    }
    break;
  }
  case 8:
    if (!unknown007.m_charBusy) {
      if (event.unknown0c == 1) {
        u32 index = m_menuObjCharSelect->unknown3fc;
        u8 *order;
        u32 layer;
        u32 condition;
        if (m_menuObjCharSelect->unknown3f8 == 0) {
          order = GfDataBdat::getFP(BDAT_MNU_CHAR_DRIVER_ORDER);
          int id = m_menuObjCharSelect->unknown6f0[index];
          if (index < Bdat::getIdCount(order)) {
            layer = Bdat::getVal(order, "layer", id).valueU16;
            condition = Bdat::getVal(order, "useCond", id).valueU16;
          } else {
            layer = 0;
            condition = 0;
          }
          m_menuObjCharSelect->m_menuDriverList->getContents(m_menuObjCharSelect->m_menuDriverList->getIndex(false));
        } else {
          int id;
          if (!GfDataHana::isValid(GfMenuReference::getReferenceBladeID(0))) {
            order = GfDataBdat::getFP(BDAT_MNU_CHAR_BLADE_ORDER);
            id = m_menuObjCharSelect->unknown710[index];
          } else {
            order = GfDataBdat::getFP(BDAT_MNU_CHAR_HANA_ORDER);
            id = m_menuObjCharSelect->unknown728[index];
          }
          if (index >= Bdat::getIdCount(order)) {
            break;
          }
          layer = Bdat::getVal(order, "layer", id).valueU16;
          condition = Bdat::getVal(order, "useCond", id).valueU16;
        }
        if (layer != 0) {
          if (!GfMenuObjUtil::getMenuCondition(condition)) {
            GfMenuObjUtil::playSECommon(2);
          } else {
            unknown140(owner.searchChild("LAY_status"), 0x105, layer, 0.0f);
            m_menuObjCharSelect->unknown48->setDisp(false);
            GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
            if (layer == 0x1e || layer == 0x1f) {
              dispOffCopyChar(owner, 0);
            } else if (layer == 0x22 || layer == 0x2e || layer == 0x2f) {
              dispOffCopyChar(owner, 1);
            }
            m_menuObjCharSelect->unknown6d8 = layer;
            if (m_menuObjCharSelect->unknown3f8 == 0) {
              setFadeOut(owner.searchChild("LAY_sub_menu_base_dr"), 0);
              setFadeOut(owner.searchChild("LAY_sub_menu_contents_dr"), 1);
            } else {
              u32 count;
              if (!GfDataHana::isValid(GfMenuReference::getReferenceBladeID(0))) {
                setFadeOut(owner.searchChild("LAY_sub_menu_base_bl"), 0);
                setFadeOut(owner.searchChild("LAY_sub_menu_contents_bl"), 1);
                count = m_menuObjCharSelect->unknown710.size();
              } else {
                setFadeOut(owner.searchChild("LAY_sub_menu_base_hana"), 0);
                setFadeOut(owner.searchChild("LAY_sub_menu_contents_hana"), 1);
                count = m_menuObjCharSelect->unknown728.size();
              }
              m_menuObjCharSelect->unknown74c = count;
            }
            disableInput(handle);
            u32 group = GfMenuFullScreen::getLayerGroup(m_menuObjCharSelect->unknown20);
            changeFSSubLayer(owner.unknown10, group + 1, getMenuLayerID(layer), true);
            GfMenuObjMainMenu2::disableCharChange();
            unknown0c = 0;
            GfMenuObjUtil::playSECommonDecide();
          }
        }
      } else if (event.unknown0c == 2) {
        int type = m_menuObjCharSelect->unknown3f8;
        GfMenuObjUtil::playSECommonCancel();
        if (!m_menuObjCharSelect->unknown741) {
          int kind = 0xffff;
          // The arms are in this order in the source: the temporary UIObjectAcc copies of the two refreshDriver calls take the frame slots in
          // creation order (the game's: the call without a result first).
          if (type != 0) {
            u32 blade = GfMenuReference::getReferenceBladeID(0);
            u32 driver = GfDataBlade::getSetDriver(blade);
            if (driver != 0 && driver != GfMenuReference::getReferenceDriverID(0)) {
              GfMenuReference::setReferenceDriverID(0, driver);
              m_menuObjCharSelect->refreshDriver(owner, driver);
            } else {
              kind = type;
            }
            u32 index = m_menuObjCharSelect->m_menuDriverList->getIndex(false);
            for (u32 i = 0; i < 3; i++) {
              if (blade == m_menuObjCharSelect->unknown3a8[index].unknown04[i]) {
                m_menuObjCharSelect->unknown3f8 = i + 1;
                break;
              }
            }
            if (m_menuObjCharSelect->unknown3f8 != kind) {
              u32 index = m_menuObjCharSelect->m_menuDriverList->getIndex(false);
              u32 count = GfMenuObjUtil::isValidBlade(m_menuObjCharSelect->unknown3a8[index].unknown04[0]);
              for (u32 i = 1; i < 3; i++) {
                count += GfMenuObjUtil::isValidBlade(m_menuObjCharSelect->unknown3a8[index].unknown04[i]);
              }
              m_menuObjCharSelect->unknown429 = true;
              unknown140(owner.searchChild("LAY_char"), 0x103, count, 0.0f);
            }
          } else {
            u32 driver = GfMenuReference::getReferenceDriverID(0);
            u32 count = m_menuObjCharSelect->refreshDriver(owner, driver);
            unknown140(acc.searchChild("LAY_char"), 0x102, count, 0.0f);
          }
          u32 driver = GfMenuReference::getReferenceDriverID(0);
          unknown140(owner.searchChild("LAY_char"), 0x140, driver, 0.0f);
          moveCharSubMenuOut(owner, m_menuObjCharSelect->unknown3f8, m_menuObjCharSelect->unknown400, kind != 0xffff);
          if (!m_menuObjCharSelect->unknown741) {
            GfMenuObjUtil::CtrlParam param;
            u32 status = acc.searchChild("LAY_status");
            param.unknown08 = 2;
            param.unknown0c = 0;
            param.unknown00 = 0.4f;
            GfMenuObjUtil::startCtrl(status, param, nullptr);
          }
          unknown163(handle, 0x22, 0);
          GfMenuObjMainMenu2::disableCharChange();
        } else {
          GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
          GfMenuObject::termCallContext(owner.searchChild("LAY_main"));
          returnFSSubLayer(m_menuObjCharSelect);
        }
      } else if (event.unknown0c == 0x12) {
        bool isOpen;
        if (m_menuObjCharSelect->unknown3f8 == 0) {
          isOpen = GfMenuObjCmnStatus::swapDrStatus();
        } else {
          isOpen = GfMenuObjCmnStatus::swapBlStatus();
        }
        GfMenuObjOperationInfo::changeText(handle, 0x12, !isOpen);
      }
    }
    break;
  // This case follows the case 8 in the source: the frame slots of the temporaries of its two setDisp calls come after those of the refreshDriver
  // copies of the case 8 (1.0.0: 0x710042f220), whatever the order of the labels in the machine code.
  case 3:
    switch (event.unknown08) {
    case 1:
      m_menuObjCharSelect->unknown48->setDisp(true);
      addResultCallContext(owner.searchChild("LAY_main"), 0, 0);
      enableInput(handle);
      if (!m_menuObjCharSelect->unknown741) {
        GfMenuObjMainMenu2::openCharChange(acc.unknown10, m_menuObjCharSelect->unknown3f8 != 0, false);
      }
      break;
    case 4: {
      if (m_menuObjCharSelect->unknown3f8 == 0) {
        setCharPosScale(0, GfMenuReference::getReferenceDriverID(0), 4, false);
      } else {
        setCharPosScale(1, GfMenuReference::getReferenceBladeID(0), 4, false);
      }
      break;
    }
    case 3: {
      ui::UIObjectAcc(owner.searchChild("LAY_char_dr_move")).setDisp(false);
      ui::UIObjectAcc(owner.searchChild("LAY_char_bl_move")).setDisp(false);
      break;
    }
    }
    break;
  case GfMenuTypes::unknown003_33: {
    if (m_menuObjCharSelect->unknown741) {
      GfMenuObjMainMenu2::setCloseKeyEnable(true);
      if (m_menuObjCharSelect->unknown742 == 0) {
        m_menuObjCharSelect->unknown3f8 = 0;
        GfMenuReference::setReferenceDriverID(0, m_menuObjCharSelect->unknown744);
      } else if (m_menuObjCharSelect->unknown742 == 1) {
        m_menuObjCharSelect->unknown3f8 = 1;
        GfMenuReference::setReferenceBladeID(0, m_menuObjCharSelect->unknown744);
      }
    }
    u32 blade;
    if (m_menuObjCharSelect->unknown3f8 == 0) {
      setFadeIn(owner.searchChild("LAY_sub_menu_base_dr"), 0);
      hookCtrlEvent(handle, setFadeIn(owner.searchChild("LAY_sub_menu_contents_dr"), 1));
      GfMenuObjCmnStatus::openDrStatus(1, -1);
      blade = 0;
      unknown0c = 1;
    } else {
      blade = GfMenuReference::getReferenceBladeID(0);
      if (!GfDataHana::isValid(blade)) {
        setFadeIn(owner.searchChild("LAY_sub_menu_base_bl"), 0);
        hookCtrlEvent(handle, setFadeIn(owner.searchChild("LAY_sub_menu_contents_bl"), 1));
      } else {
        setFadeIn(owner.searchChild("LAY_sub_menu_base_hana"), 0);
        hookCtrlEvent(handle, setFadeIn(owner.searchChild("LAY_sub_menu_contents_hana"), 1));
      }
      if (!m_menuObjCharSelect->unknown741) {
        GfMenuObjCmnStatus::openBlStatus(1, -1);
      }
      unknown0c = 1;
    }
    u32 driver = GfMenuReference::getReferenceDriverID(0);
    int bladeNum = getEquipBladeNum(driver, m_menuObjCharSelect->unknown3a8);
    if (!m_menuObjCharSelect->unknown741) {
      moveCharSubMenuIn(owner, m_menuObjCharSelect->unknown3f8, m_menuObjCharSelect->unknown400, true, bladeNum == 0);
      GfMenuObjUtil::CtrlParam param;
      u32 status = owner.searchChild("LAY_status");
      param.unknown08 = 2;
      param.unknown0c = 0;
      param.unknown00 = 0.4f;
      GfMenuObjUtil::startCtrl(status, param, nullptr);
    } else {
      moveCharSubMenuIn(owner, m_menuObjCharSelect->unknown3f8, m_menuObjCharSelect->unknown400, false, bladeNum == 0);
      owner.setDispChild(false, "LAY_status");
    }
    GfMenuObjOperationInfo::add(handle, 0, 0, 0);
    GfMenuObjOperationInfo::setGuideText(m_menuObjCharSelect->unknown3f8 != 0 ? 10 : 9, 0);
    GfMenuObjMainMenu2::setSubIndexText(m_menuObjCharSelect->unknown3f8 != 0 ? 3 : 2);
    m_menuObjCharSelect->unknown48->open(0);
    m_menuObjCharSelect->unknown48->setDisp(false);
    unknown140(handle, 0x108, blade, 0.0f);
    break;
  }
  case GfMenuTypes::unknown003_34: {
    int type = event.unknown08;
    m_menuObjCharSelect->unknown48->setDisp(false);
    GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
    if (type != 1) {
      GfMenuObjOperationInfo::setGuideText(1, 0);
      GfMenuObjMainMenu2::setSubIndexText(1);
      unknown140(owner.searchChild("LAY_char"), 0x108, 0, 0.0f);
    }
    if (m_menuObjCharSelect->unknown3f8 == 0) {
      setFadeOut(owner.searchChild("LAY_sub_menu_base_dr"), 0);
      setFadeOut(owner.searchChild("LAY_sub_menu_contents_dr"), 1);
    } else if (!GfDataHana::isValid(GfMenuReference::getReferenceBladeID(0))) {
      setFadeOut(owner.searchChild("LAY_sub_menu_base_bl"), 0);
      setFadeOut(owner.searchChild("LAY_sub_menu_contents_bl"), 1);
    } else {
      setFadeOut(owner.searchChild("LAY_sub_menu_base_hana"), 0);
      setFadeOut(owner.searchChild("LAY_sub_menu_contents_hana"), 1);
    }
    if (m_menuObjCharSelect->unknown3f8 == 0) {
      GfMenuObjCmnStatus::closeDrStatus();
    } else {
      GfMenuObjCmnStatus::closeBlStatus();
    }
    disableInput(handle);
    unknown0c = 0;
    break;
  }
  case 0x104:
    if (event.unknown08 != 1) {
      unknown140(owner.searchChild("LAY_status"), 0x106, 0, 0.0f);
      u32 previous = m_menuObjCharSelect->unknown6d8;
      u32 driver = GfMenuReference::getReferenceDriverID(0);
      if (previous == 0x1e || previous == 0x1f) {
        setCharPosScale(0, driver, 4, false);
        dispOnCopyChar(owner, 0);
      } else if (previous == 0x22 || previous == 0x2e || previous == 0x2f) {
        setCharPosScale(1, GfMenuReference::getReferenceBladeID(0), 4, false);
        dispOnCopyChar(owner, 1);
      }
      setPartyData(m_menuObjCharSelect->unknown3a8, m_menuObjCharSelect->m_menuDriverList);
      adjustBladeList(m_menuObjCharSelect->unknown3a8, m_menuObjCharSelect->unknown50, m_menuObjCharSelect->unknown30, driver);
      for (u32 i = 0; i < m_menuObjCharSelect->m_menuDriverList->getSize(); i++) {
        if (m_menuObjCharSelect->m_menuDriverList->getContents(i).unknown00 == driver) {
          m_menuObjCharSelect->m_menuDriverList->setIndex(i);
          break;
        }
      }
      if (m_menuObjCharSelect->unknown3f8 == 0) {
        u32 index = m_menuObjCharSelect->m_menuDriverList->getIndex(false);
        u32 count = 0;
        for (u32 i = 0; i < 3; i++) {
          u32 blade = m_menuObjCharSelect->unknown3a8[index].unknown04[i];
          ui::UIObjectAcc layer(owner.searchChild(unknown008[i + 1]));
          ui::UIObjectAcc status(owner.searchChild(unknown010[i + 1]));
          if (GfMenuObjUtil::isValidBlade(blade)) {
            layer.setDisp(true);
            status.setDisp(true);
            count++;
          } else {
            layer.setDisp(false);
            status.setDisp(false);
          }
        }
        u32 layer = owner.searchChild("LAY_char");
        ui::EventData sendData;
        // The same stores, in the same order, as the event helper of gf_menu_obj_blade_set2.cpp and gf_menu_obj_pouch2.cpp: parameters 2 and 3 as one
        // 64-bit zero, parameter 1, the type, then parameter 0.
        sendData.unknown10_u64 = 0;
        sendData.unknown0c = 0;
        sendData.unknown00 = 0x102;
        sendData.unknown08 = count;
        ui::UIManager::get()->requestObjectEvent(layer, sendData, 0.0f);
      }
    }
    {
      u32 parent = ui::UIObjectAcc(handle).getParentHandle();
      if (m_menuObjCharSelect->unknown3f8 == 0) {
        setFadeIn(owner.searchChild("LAY_sub_menu_base_dr"), 0);
        hookCtrlEvent(handle, setFadeIn(owner.searchChild("LAY_sub_menu_contents_dr"), 1));
        unknown0c = 1;
        GfMenuObjOperationInfo::changeText(handle, 0x12, !GfMenuObjCmnStatus::isOpenDrStatus());
      } else {
        u32 blade = GfMenuReference::getReferenceBladeID(0);
        bool isHana = GfDataHana::isValid(blade);
        u32 subMenu = owner.searchChild("LAY_sub_menu_bl");
        u32 entries;
        // The hana arm comes first in the source (the frame slots of the temporaries in creation order), here and in the case 0x108.
        if (isHana) {
          ui::UIObjectAcc(subMenu).setDisp(false);
          ui::UIObjectAcc(owner.searchChild("LAY_sub_menu_hana")).setDisp(true);
          setFadeIn(owner.searchChild("LAY_sub_menu_base_hana"), 0);
          hookCtrlEvent(handle, setFadeIn(owner.searchChild("LAY_sub_menu_contents_hana"), 1));
          entries = m_menuObjCharSelect->unknown728.size();
        } else {
          ui::UIObjectAcc(subMenu).setDisp(true);
          ui::UIObjectAcc(owner.searchChild("LAY_sub_menu_hana")).setDisp(false);
          setFadeIn(owner.searchChild("LAY_sub_menu_base_bl"), 0);
          hookCtrlEvent(handle, setFadeIn(owner.searchChild("LAY_sub_menu_contents_bl"), 1));
          entries = m_menuObjCharSelect->unknown710.size();
        }
        unknown0c = 1;
        GfMenuObjOperationInfo::changeText(handle, 0x12, !GfMenuObjCmnStatus::isOpenBlStatus());
        if (entries != m_menuObjCharSelect->unknown74c) {
          if (GfDataHana::isValid(blade)) {
            GfMenuObjUtil::changeCursorTarget(m_menuObjCharSelect->unknown48, parent, "LAY_sub_menu_hana@%02d");
          } else {
            GfMenuObjUtil::changeCursorTarget(m_menuObjCharSelect->unknown48, parent, "LAY_sub_menu_bl@%02d");
          }
          setupInputSelection(handle, 0, entries);
        }
      }
    }
    GfMenuObjOperationInfo::add(handle, 0, 0, 0);
    GfMenuObjOperationInfo::setGuideText(m_menuObjCharSelect->unknown3f8 != 0 ? 10 : 9, 0);
    GfMenuObjMainMenu2::setSubIndexText(m_menuObjCharSelect->unknown3f8 != 0 ? 3 : 2);
    enableInput(handle);
    if (!m_menuObjCharSelect->unknown741) {
      GfMenuObjMainMenu2::openCharChange(acc.unknown10, m_menuObjCharSelect->unknown3f8 != 0, false);
    }
    break;
  case 0x108: {
    u32 character = event.unknown08;
    u32 parent = ui::UIObjectAcc(handle).getParentHandle();
    int kind = m_menuObjCharSelect->unknown3f8;
    u32 driverMenu = owner.searchChild("LAY_sub_menu_dr");
    u32 entries;
    if (kind == 0) {
      ui::UIObjectAcc(driverMenu).setDisp(true);
      ui::UIObjectAcc(owner.searchChild("LAY_sub_menu_bl")).setDisp(false);
      ui::UIObjectAcc(owner.searchChild("LAY_sub_menu_hana")).setDisp(false);
      GfMenuObjUtil::changeCursorTarget(m_menuObjCharSelect->unknown48, parent, "LAY_sub_menu_dr@%02d");
      entries = m_menuObjCharSelect->unknown6f0.size();
    } else {
      ui::UIObjectAcc(driverMenu).setDisp(false);
      bool isHana = GfDataHana::isValid(character);
      u32 bladeMenu = owner.searchChild("LAY_sub_menu_bl");
      if (isHana) {
        ui::UIObjectAcc(bladeMenu).setDisp(false);
        ui::UIObjectAcc(owner.searchChild("LAY_sub_menu_hana")).setDisp(true);
        ui::UIObjectAcc(owner.searchChild("LAY_sub_menu_base_hana")).setDisp(true);
        ui::UIObjectAcc(owner.searchChild("LAY_sub_menu_base_hana")).setAlpha(1.0f);
        ui::UIObjectAcc(owner.searchChild("LAY_sub_menu_contents_hana")).setDisp(true);
        GfMenuObjUtil::changeCursorTarget(m_menuObjCharSelect->unknown48, parent, "LAY_sub_menu_hana@%02d");
        entries = m_menuObjCharSelect->unknown728.size();
      } else {
        ui::UIObjectAcc(bladeMenu).setDisp(true);
        ui::UIObjectAcc(owner.searchChild("LAY_sub_menu_hana")).setDisp(false);
        ui::UIObjectAcc(owner.searchChild("LAY_sub_menu_base_bl")).setDisp(true);
        ui::UIObjectAcc(owner.searchChild("LAY_sub_menu_base_bl")).setAlpha(1.0f);
        ui::UIObjectAcc(owner.searchChild("LAY_sub_menu_contents_bl")).setDisp(true);
        GfMenuObjUtil::changeCursorTarget(m_menuObjCharSelect->unknown48, parent, "LAY_sub_menu_bl@%02d");
        entries = m_menuObjCharSelect->unknown710.size();
      }
    }
    resetInputSelection(handle);
    setupInputSelection(handle, 0, entries);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

bool GfMenuObjCharSelect::seqSpUpdateParty() {
  u32 driver = m_menuDriverList->getContents(m_menuDriverList->getIndex(false)).unknown00;
  GfMenuDriverList::PartySetup setup;
  setup.unknown18 = false;
  setup.unknown14 = GfPartySelect::LIST_TYPE_UNKNOWN_2;
  m_menuDriverList->setupFromParty(setup);
  m_menuDriverList->setIndex(0);
  for (u32 i = 0; i < m_menuDriverList->getSize(); i++) {
    if (m_menuDriverList->getContents(i).unknown00 == driver) {
      m_menuDriverList->setIndex(i);
      break;
    }
  }
  setPartyData(unknown3a8, m_menuDriverList);
  return true;
}

bool GfMenuObjCharSelect::seqConfSpecial() {
  ui::UIObjectAcc acc(unknown18, "LAY_char");
  if (!unknown6c0) {
    if (unknown748 == 3 && GfMenuObjUtil::isBladeLastOneInSlot(0x3f3, nullptr)) {
      GfMenuManager::openCommonWindow(0xdf);
      unknown430.unknown002(&GfMenuObjCharSelect::seqConfSpecialWaitError);
      return true;
    }
    GfMenuManager::openCommonWindow(unknown009[unknown748]);
    unknown6c0 = true;
    return false;
  }
  if (GfMenuManager::isOpenCommonWindow()) {
    return false;
  }
  s16 result = GfMenuManager::getCommonWindowResult();
  if (result == 0) {
    switch (unknown748) {
    case 0:
      unknown430.unknown002(&GfMenuObjCharSelect::seqSpHomuraToHikari);
      break;
    case 1:
      unknown430.unknown002(&GfMenuObjCharSelect::seqSpHikariToHomura);
      break;
    case 2:
      unknown430.unknown002(&GfMenuObjCharSelect::seqSpNiaChangeBl);
      break;
    case 3:
      unknown430.unknown002(&GfMenuObjCharSelect::seqSpNiaChangeDr);
      break;
    default:
      unknown430.unknown002(&GfMenuObjCharSelect::seqReturn);
      return true;
    }
    unknown430.unknown004(2);
    unknown430.unknown002(&GfMenuObjCharSelect::seqSpUpdateParty);
    unknown430.unknown002(&GfMenuObjCharSelect::seqReturnChange);
  } else {
    unknown430.unknown002(&GfMenuObjCharSelect::seqReturn);
  }
  return true;
}

bool GfMenuObjCharSelect::seqStreamWait() {
  mm::mtl::FixStr<32> name;
  ui::UIObjectAcc acc(unknown18);
  int bladeNum = getEquipBladeNum(GfMenuReference::getReferenceDriverID(0), unknown3a8);
  if (bladeNum == 0) {
    ui::UIObjectAcc layer(acc.searchChild("LAY_char_dr_solo"));
    if (layer.isStreaming()) {
      return false;
    }
  } else {
    ui::UIObjectAcc layer(acc.searchChild("LAY_char_dr"));
    if (layer.isStreaming()) {
      return false;
    }
  }
  for (u32 i = 0; i < 3; i++) {
    name.format("IMG_char_bl_img@%02d", i + 1);
    ui::UIObjectAcc image(acc.searchChild(name.c_str()));
    if (image.isStreaming()) {
      return false;
    }
  }
  if (unknown768) {
    return false;
  }
  setFadeIn(acc.searchChild("LAY_main"), 0);
  return true;
}

void GfMenuObjCharSelect::setupCharSubMenu(ui::UIObjectAcc &acc, mm::mtl::FixedVector<u32, 5> &drivers, mm::mtl::FixedVector<u32, 3> &blades, mm::mtl::FixedVector<u32, 4> &hanas) {
  u8 *driverBdat = GfDataBdat::getFP(BDAT_MNU_CHAR_DRIVER_ORDER);
  for (u32 i = 0; i < 5; i++) {
    mm::mtl::FixStr<32> name;
    name.format("IMG_sub_menu_icon_dr@%02d", i + 1);
    ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
    if (i < drivers.size()) {
      icon.setImageIndex(getMenuIconID(Bdat::getVal(driverBdat, "layer", drivers[i]).valueU16));
      icon.setDisp(true);
    } else {
      icon.setDisp(false);
    }
  }
  mm::mtl::FixStr<32> name;
  u8 *bladeBdat = GfDataBdat::getFP(BDAT_MNU_CHAR_BLADE_ORDER);
  for (u32 i = 0; i < 3; i++) {
    if (i < blades.size()) {
      setupCharSubMenuBl(acc, Bdat::getVal(bladeBdat, "layer", blades[i]).valueU16, i);
    } else {
      name.format("IMG_sub_menu_icon_bl@%02d", i + 1);
      ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
      icon.setDisp(false);
    }
  }
  u8 *hanaBdat = GfDataBdat::getFP(BDAT_MNU_CHAR_HANA_ORDER);
  for (u32 i = 0; i < 4; i++) {
    if (i < hanas.size()) {
      setupCharSubMenuHana(acc, Bdat::getVal(hanaBdat, "layer", hanas[i]).valueU16, i);
    } else {
      name.format("IMG_sub_menu_icon_hana@%02d", i + 1);
      ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
      icon.setDisp(false);
    }
  }
}

u32 GfMenuObjCharSelect::refreshDriver(ui::UIObjectAcc acc, u32 driver) {
  setPartyData(unknown3a8, m_menuDriverList);
  adjustBladeList(unknown3a8, unknown50, unknown30, driver);
  for (u32 i = 0; i < m_menuDriverList->getSize(); i++) {
    if (m_menuDriverList->getContents(i).unknown00 == driver) {
      m_menuDriverList->setIndex(i);
      break;
    }
  }
  u32 index = m_menuDriverList->getIndex(false);
  u32 count = 0;
  for (u32 i = 0; i < 3; i++) {
    u32 blade = unknown3a8[index].unknown04[i];
    ui::UIObjectAcc layer(acc.searchChild(unknown008[i + 1]));
    ui::UIObjectAcc status(acc.searchChild(unknown010[i + 1]));
    if (GfMenuObjUtil::isValidBlade(blade)) {
      layer.setDisp(true);
      status.setDisp(true);
      count++;
    } else {
      layer.setDisp(false);
      status.setDisp(false);
    }
  }
  return count;
}

void GfMenuObjCharSelect::setupCharSelect(ui::UIObjectAcc &acc, GfMenuDriverList *list, mm::mtl::FixedArray<GfMenuBladeList *, 3> &blades) {
  GfMenuDriverList::PartySetup partySetup;
  partySetup.unknown18 = false;
  partySetup.unknown14 = GfPartySelect::LIST_TYPE_UNKNOWN_2;
  list->setupFromParty(partySetup);
  if (list->getSize() != 0) {
    GfMenuReference::setReferenceDriverID(0, list->getContents(0).unknown00);
  }
  for (u32 i = 0; i < 3; i++) {
    GfMenuBladeList::DriverSetup setup;
    setup.unknown14 = 1;
    setup.unknown18 = list->getContents(list->getIndex(false)).unknown00;
    if (setup.unknown18 == 0) {
      blades[i]->clear();
    } else {
      blades[i]->setupFromDriver(setup);
    }
  }
  GfMenuAdapterManager::beginAddAfter();
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_char_dr_img"), 0x1c, 0, false);
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_char_dr_glow"), 0x1c, 0, false);
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_char_dr_img_solo"), 0x1c, 0, false);
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_char_dr_glow_solo"), 0x1c, 0, false);
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_name"), 2, 0, false);
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_class"), 0x24, 0, true);
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_lv_num"), 1, 0, true);
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_hp_num"), 0, 0, true);
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 3; i++) {
    name.format("IMG_char_bl_img@%02d", i + 1);
    GfMenuCharDataAdapter *image = GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x36, blades[i], -1, false);
    name.format("IMG_char_bl_glow@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x36, blades[i], -1, false);
    ui::UIObjectAcc(acc.searchChild(name.c_str())).setAlpha(0.0f);
    name.format("TXT_status_bl_name@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 2, blades[i], -1, false);
    if (image != nullptr) {
      image->unknown24 = acc.searchChild(unknown010[i + 1]);
    }
    name.format("IMG_status_bl_wpn_icon@%02d", i + 1);
    ui::UIObjectAcc(acc.searchChild(name.c_str())).setDisp(false);
    name.format("IMG_status_bl_elem_icon@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x2a, blades[i], -1, false);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x39, blades[i], -1, false);
    name.format("IMG_status_bl_rank_rarity@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x55, blades[i], -1, false);
    name.format("IMG_status_bl_rank@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x54, blades[i], -1, false);
  }
  GfMenuAdapterManager::endAddAfter();
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjCharSelect, 8>>(const mm::mtl::Delegate<bool()> *);
