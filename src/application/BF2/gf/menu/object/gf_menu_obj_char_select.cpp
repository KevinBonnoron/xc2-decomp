#include "gf/menu/object/gf_menu_obj_char_select.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_util.h"
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
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x61;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x104;
// Inferred role: customize layer; original name unknown.
constexpr u16 unknown004 = 0x27;
// Inferred role: busy flags of the stream waits; original type name unknown.
struct unknown006 {
  bool unknown00; // Inferred role: character stream wait busy flag; original member name unknown.
  bool unknown01; // Inferred role: selection stream wait busy flag; original member name unknown.
};
// Inferred role: busy flags of the stream waits; original name unknown.
static unknown006 unknown007;
// Inferred role: layer names of the driver and the three blades of the character select; original name unknown.
static const char *const unknown008[4] = {"LAY_char_dr", "LAY_char_bl@01", "LAY_char_bl@02", "LAY_char_bl@03"};
// Inferred role: common window ids confirming the special operations; original name unknown.
static const u32 unknown009[4] = {0xb9, 0xba, 0xbb, 0xbc};
// Inferred role: layer names of the status of the driver and the three blades of the character select; original name unknown.
static const char *const unknown010[4] = {"LAY_status_dr", "LAY_status_bl@01", "LAY_status_bl@02", "LAY_status_bl@03"};

GfMenuObjCharSelect::GfMenuObjCharSelect(u32 handle)
    : GfMenuObject(handle), unknown48(nullptr), unknown3f8(0), unknown3fc(0), unknown428(false), unknown429(false), unknown430(this), unknown6c0(false), unknown6d8(0), unknown6e8(-1),
      unknown740(true), unknown741(false), unknown742(0), unknown744(0), unknown748(0xff), unknown768(false) {
  unknown400.assign(-1);
  unknown28 = nullptr;
  unknown30.assign(nullptr);
  unknown6e0 = GfMenuCallContext::create();
  unknown750.assign(-1);
  unknown007.unknown00 = false;
  unknown007.unknown01 = false;
}

GfMenuObjCharSelect::~GfMenuObjCharSelect() {
  mm::mtl::safeRelease(unknown6e0);
  mm::mtl::safeRelease(unknown28);
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
  unknown007.unknown00 = true;
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
  unknown007.unknown00 = true;
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
  for (u32 i = 0; i < unknown28->getSize(); i++) {
    if (unknown28->getContents(i).unknown00 == 2 && i < 3) {
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
  unknown007.unknown01 = true;
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
  if (unknown007.unknown01) {
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

bool GfMenuObjCharSelect::getCharBusy() { return unknown007.unknown00; }

bool GfMenuObjCharSelect::getSelectBusy() { return unknown007.unknown01; }

void GfMenuObjCharSelect::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    setupCharSelect(acc, unknown20->unknown28, unknown20->unknown30);
    setupCharSelectCopy(acc);
    GfDataBlade::getListReserverWithSolo(unknown20->unknown50);
    for (u16 *it = unknown20->unknown50.begin(); it != unknown20->unknown50.end();) {
      if (*it == BLADE_HIKARI || *it == BLADE_HOMURI) {
        it = unknown20->unknown50.erase(it);
      } else {
        ++it;
      }
    }
    setPartyData(unknown20->unknown3a8, unknown20->unknown28);
    GfMenuObjOperationInfo::setGuideText(1, 0);
    GfMenuObjMainMenu2::setSubIndexText(1);
    acc.setDisp(false);
    unknown20->unknown768 = !unknown20->unknown741;
    unknown20->unknown430.unknown005();
    unknown20->unknown430.unknown002(&GfMenuObjCharSelect::seqStreamWait);
    unknown20->unknown6f0.clear();
    u8 *driverOrder = GfDataBdat::getFP(BDAT_MNU_CHAR_DRIVER_ORDER);
    for (int i = 0; i < 5; i++) {
      int id = Bdat::getIdTop(driverOrder) + i;
      if (GfMenuObjUtil::getMenuCondition(Bdat::getVal(driverOrder, "useCond", id).valueU16)) {
        unknown20->unknown6f0.push_back(id);
      }
    }
    unknown20->unknown710.clear();
    u8 *bladeOrder = GfDataBdat::getFP(BDAT_MNU_CHAR_BLADE_ORDER);
    for (int i = 0; i < 3; i++) {
      int id = Bdat::getIdTop(bladeOrder) + i;
      if (GfMenuObjUtil::getMenuCondition(Bdat::getVal(bladeOrder, "useCond", id).valueU16)) {
        unknown20->unknown710.push_back(id);
      }
    }
    unknown20->unknown728.clear();
    u8 *hanaOrder = GfDataBdat::getFP(BDAT_MNU_CHAR_HANA_ORDER);
    for (int i = 0; i < 4; i++) {
      int id = Bdat::getIdTop(hanaOrder) + i;
      if (GfMenuObjUtil::getMenuCondition(Bdat::getVal(hanaOrder, "useCond", id).valueU16)) {
        unknown20->unknown728.push_back(id);
      }
    }
    unknown20->unknown740 = true;
    break;
  }
  case 2:
    unknown20->unknown430.unknown005();
    GfMenuObjMainMenu2::closeCharChange();
    if (unknown20->unknown428) {
      RQ_SETUP_PARTY party;
      RQ_SETUP_PARTY::Member *member = party.unknown00;
      for (u32 i = 0; i < 5; i++, member++) {
        const DriverData &driver = unknown20->unknown3a8[i];
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
    if (!unknown20->unknown740) {
      ui::EventData sendData;
      sendData.unknown00 = 3;
      sendData.unknown08 = 2;
      ui::UIManager::get()->requestObjectEvent(handle, sendData, 0.0f);
    } else {
      setFadeOut(handle, 0);
    }
    break;
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
    unknown20->unknown740 = false;
    break;
  case GfMenuTypes::unknown003_260:
    unknown164(acc.searchChild("LAY_sub_menu"), GfMenuTypes::unknown003_260);
    break;
  case 0x109: {
    unknown20->unknown764 = event.unknown08;
    if (unknown20->unknown764 == 0) {
      GfMenuObjUtil::setChildDisp(acc.unknown10, "LAY_char_dr_move", false);
    } else {
      GfMenuObjUtil::setChildDisp(acc.unknown10, "LAY_char_bl_move", false);
    }
    unknown007.unknown00 = true;
    if (unknown20->unknown764 == 0) {
      unknown20->seqStreamWaitStatDrBefore();
    } else {
      unknown20->seqStreamWaitStatBlBefore();
    }
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
      if (!unknown20->unknown741) {
        ui::UIObjectAcc layer(acc.searchChild("LAY_char"));
        GfMenuObjMainMenu2::openCharChange(layer.unknown10, 3, true);
        enableInput(layer.unknown10);
        GfMenuObjMainMenu2::setSystemKeyEnable(true);
      }
      break;
    case 4: {
      int kind = unknown20->unknown764;
      unknown20->unknown430.unknown005();
      unknown20->unknown430.unknown004(1);
      if (kind == 0) {
        unknown20->unknown430.unknown002(&GfMenuObjCharSelect::seqStreamWaitStatDr);
        setCharPosScale(0, GfMenuReference::getReferenceDriverID(0), 4, false);
      } else {
        unknown20->unknown430.unknown002(&GfMenuObjCharSelect::seqStreamWaitStatBl);
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
  ui::UIObjectAcc owner(unknown20->unknown18);
  switch (event.unknown00) {
  case 1:
    break;
  case 0x105: {
    acc.getPos(unknown20->unknown6d4);
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
      pos.x = -(unknown20->unknown6d4.x + rect.width);
      pos.y = rect.y;
      acc.setPos(pos);
      break;
    }
    }
    break;
  }
  case 0x106:
    acc.setPos(unknown20->unknown6d4);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjCharSelect::CharDrListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(unknown20->unknown18);
  if (event.unknown00 != 1) {
    if (event.unknown00 == 3) {
      if (event.unknown08 == 0) {
        return;
      }
      if (event.unknown08 == 1) {
        unknown007.unknown01 = false;
        enableInput(acc.searchChild("LAY_char"));
      }
    }
    ui::UIObjectListener::reciveEvent(event, handle);
  }
}

void GfMenuObjCharSelect::CharDrSoloListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(unknown20->unknown18);
  if (event.unknown00 != 1) {
    if (event.unknown00 == 3) {
      if (event.unknown08 == 0) {
        return;
      }
      if (event.unknown08 == 1) {
        unknown007.unknown01 = false;
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
      unknown007.unknown00 = false;
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
      unknown007.unknown00 = false;
    }
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

bool GfMenuObjCharSelect::seqSpUpdateParty() {
  u32 driver = unknown28->getContents(unknown28->getIndex(false)).unknown00;
  GfMenuDriverList::PartySetup setup;
  setup.unknown18 = false;
  setup.unknown14 = GfPartySelect::LIST_TYPE_UNKNOWN_2;
  unknown28->setupFromParty(setup);
  unknown28->setIndex(0);
  for (u32 i = 0; i < unknown28->getSize(); i++) {
    if (unknown28->getContents(i).unknown00 == driver) {
      unknown28->setIndex(i);
      break;
    }
  }
  setPartyData(unknown3a8, unknown28);
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

u8 GfMenuObjCharSelect::refreshDriver(ui::UIObjectAcc acc, u32 driver) {
  setPartyData(unknown3a8, unknown28);
  adjustBladeList(unknown3a8, unknown50, unknown30, driver);
  for (u32 i = 0; i < unknown28->getSize(); i++) {
    if (unknown28->getContents(i).unknown00 == driver) {
      unknown28->setIndex(i);
      break;
    }
  }
  u32 index = unknown28->getIndex(false);
  u8 count = 0;
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
