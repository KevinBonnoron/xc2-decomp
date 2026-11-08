#include "gf/menu/object/gf_menu_obj_mercenary_form.h"

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjMercenaryForm::GfMenuObjMercenaryForm(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown28(nullptr), unknown30(nullptr), unknown78(nullptr), unknown80(nullptr), unknown98(nullptr), unknowna0(nullptr), unknowna8(nullptr),
      unknownb0(nullptr), unknownb8(nullptr), unknown100(0), unknown104(0), unknown108(this), unknown430(false), unknown438(this), unknown8f0(false), unknown8f8(nullptr) {
  for (int i = 0; i < 8; i++) {
    unknownc0[i] = unknown160();
  }
  unknownb8 = GfMenuCallContext::create();
}

GfMenuObjMercenaryForm::~GfMenuObjMercenaryForm() {
  for (int i = 0; i < 8; i++) {
    unknownc0[i] = nullptr;
  }
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknownb8);
  mm::mtl::safeRelease(unknownb0);
  mm::mtl::safeRelease(unknowna8);
  mm::mtl::safeRelease(unknowna0);
  mm::mtl::safeRelease(unknown98);
  mm::mtl::safeRelease(unknown80);
  mm::mtl::safeRelease(unknown78);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown88);
  mm::mtl::safeRelease(unknown90);
  mm::mtl::safeRelease(unknown68);
  mm::mtl::safeRelease(unknown50[0]);
  mm::mtl::safeRelease(unknown50[1]);
  mm::mtl::safeRelease(unknown50[2]);
}

void GfMenuObjMercenaryForm::sendOpenEvent(u32 handle, int type, f32 delay) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_form_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = type;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_33;
  GfMenuObject::sendEvent(handle, event, delay);
}

void GfMenuObjMercenaryForm::sendCloseEvent(u32 handle, int type, f32 delay) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_form_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = type;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_34;
  GfMenuObject::sendEvent(handle, event, delay);
}

void GfMenuObjMercenaryForm::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMercenaryForm::update() {
  unknown108.unknown003();
  unknown438.unknown003();
  if (unknown104 != 0) {
    unknown104--;
  }
  GfMenuObject::update();
}

void GfMenuObjMercenaryForm::refreshBladeInfo() {
  {
    ui::UIObjectAcc info(unknown18, "LAY_form_list_bl_info");
    u32 count = info.countChild("LAY_form_list_bl_info@%02d", 1);
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < count; i++) {
      name.format("IMG_form_list_bl_info_elem@%02d", i + 1);
      info.setDispChild(true, name.c_str());
      name.format("LAY_form_list_bl_info_wpn@%02d", i + 1);
      info.setDispChild(false, name.c_str());
    }
  }
  {
    ui::UIObjectAcc info(unknown18, "LAY_form_unit_bl_info");
    u32 count = info.countChild("LAY_form_unit_bl_info@%02d", 1);
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < count; i++) {
      name.format("IMG_form_unit_bl_info_elem@%02d", i + 1);
      info.setDispChild(true, name.c_str());
      name.format("LAY_form_unit_bl_info_wpn@%02d", i + 1);
      info.setDispChild(false, name.c_str());
    }
  }
}

void GfMenuObjMercenaryForm::setDetailBladePos(u32 handle) {
  ui::UIObjectAcc detail(unknown18, "LAY_form_bl_detail_bl");
  if (handle == 0) {
    detail.setDisp(false);
  } else {
    ui::UIObjectAcc blade(handle);
    mm::Rect<s16> rect;
    blade.getRect(rect, 1);
    mm::Pnt<s16> pos;
    pos.x = rect.x;
    pos.y = rect.y;
    detail.setPos(pos);
    detail.setDisp(true);
  }
}

void GfMenuObjMercenaryForm::updateReserveBlade(u32 index) {
  u32 blade = unknown30->getContents(index).unknown00;
  GfMenuReference::setReferenceBladeID(0, blade);
  updateBladeCount(blade != 0, true);
  refreshBladeList();
}

bool GfMenuObjMercenaryForm::chkTempUnlink(u32 blade) { return mm::mtl::find(unknown598.begin(), unknown598.end(), static_cast<u16>(blade)) != unknown598.end(); }

void GfMenuObjMercenaryForm::addTempUnlink(u32 blade) {
  if (!chkTempUnlink(blade)) {
    unknown598.push_back(blade);
  }
}

void GfMenuObjMercenaryForm::delTempUnlink(u32 blade) {
  u16 *it = mm::mtl::find(unknown598.begin(), unknown598.end(), static_cast<u16>(blade));
  if (it != unknown598.end()) {
    unknown598.erase(it);
  }
}

bool GfMenuObjMercenaryForm::chkUnitBladeList(u32 blade) {
  for (u32 i = 0; i < unknown28->getSize(); i++) {
    if (unknown28->getContents(i).unknown00 == blade) {
      return true;
    }
  }
  return false;
}

bool GfMenuObjMercenaryForm::seqDepartureNotice() {
  bool isEnd;
  if (!unknown430) {
    GfMenuManager::openCommonWindow(0x25);
    isEnd = false;
    unknown430 = true;
  } else {
    isEnd = !GfMenuManager::isOpenCommonWindow();
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqStartActiveFS() {
  ui::UIObjectAcc base(unknown18, "IMG_start_fs_base");
  bool isEnd;
  if (!unknown430) {
    ui::UIObjectAcc fs(unknown18, "LAY_start_fs");
    fs.setDisp(true);
    base.startAnimation("start", false);
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_r");
    GfMenuObjUtil::startCtrl(unknown18, param, "LAY_start_fs_on");
    unknown430 = true;
    isEnd = false;
  } else if (!base.isPlayingAnimation()) {
    unknown430 = false;
    unknown108.unknown002(&GfMenuObjMercenaryForm::seqOpenActiveFS);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqOpenActiveFS() {
  ui::UIObjectAcc base(unknown18, "IMG_start_fs_base");
  bool isEnd;
  if (!unknown430) {
    ui::UIObjectAcc fs(unknown18, "LAY_start_fs");
    fs.setDispChild(false, "LAY_start_fs_on");
    base.startAnimation("result", false);
    unknown430 = true;
    isEnd = false;
  } else if (!base.isPlayingAnimation()) {
    unknown430 = false;
    unknown108.unknown002(&GfMenuObjMercenaryForm::seqDispActiveFS);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqDispActiveFS() {
  ui::UIObjectAcc base(unknown18, "IMG_start_fs_base");
  bool isEnd;
  if (!unknown430) {
    base.startAnimation("fade_in_info", false);
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_r");
    GfMenuObjUtil::startCtrl(unknown18, param, "LAY_start_fs_info");
    isEnd = false;
    unknown430 = true;
  } else if (!base.isPlayingAnimation()) {
    unknown108.unknown004(90);
    unknown108.unknown002(&GfMenuObjMercenaryForm::seqEndActiveFS);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqEndActiveFS() {
  ui::UIObjectAcc fs(unknown18, "LAY_start_fs");
  fs.setDisp(false);
  unknown108.unknown002(&GfMenuObjMercenaryForm::seqLeaveBlade);
  return true;
}

bool GfMenuObjMercenaryForm::seqPresetEnd() {
  ui::UIObjectAcc preset(unknown18, "LAY_preset");
  sendCloseEvent(preset.unknown10, 0, 0.0f);
  sendOpenEvent(preset.searchSibiling("LAY_form_menu"), 0, 0.0f);
  return true;
}

bool GfMenuObjMercenaryForm::seqRevertBladeSet() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  bool isEnd;
  if (!unknown430) {
    GfMenuManager::openCommonWindow(200);
    isEnd = false;
    unknown430 = true;
  } else if (!GfMenuManager::isOpenCommonWindow()) {
    returnFSSubLayer(this);
    isEnd = true;
    unknown430 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqReturnMissionSelect() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  bool isEnd;
  if (!unknown430) {
    GfMenuManager::openCommonWindow(0x9f);
    isEnd = false;
    unknown430 = true;
  } else if (!GfMenuManager::isOpenCommonWindow()) {
    s16 result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
      if (unknown598.empty()) {
        returnFSSubLayer(this);
      } else {
        unknown108.unknown002(&GfMenuObjMercenaryForm::seqRevertBladeSet);
      }
    } else {
      GfMenuObjMainMenu2::setCloseKeyEnable(true);
      sendOpenEvent(main.searchSibiling("LAY_form_list_bl"), 0, 0.0f);
    }
    isEnd = true;
    unknown430 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqConfirmRemoveBladeSet() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  bool isEnd;
  if (!unknown430) {
    GfMenuManager::openCommonWindow(199);
    isEnd = false;
    unknown430 = true;
  } else if (!GfMenuManager::isOpenCommonWindow()) {
    s16 result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
      addTempUnlink(unknown30->getContents(unknown30->getIndex(false)).unknown00);
      addUnitBladeList(unknown30->getContents(unknown30->getIndex(false)).unknown00);
    }
    sendOpenEvent(main.searchSibiling("LAY_form_list_bl"), 0, 0.0f);
    isEnd = true;
    unknown430 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

void GfMenuObjMercenaryForm::addUnitBladeList(u32 blade) {
  if (chkUnitBladeList(blade)) {
    return;
  }
  MenuBladeInfo info;
  info.unknown00 = blade;
  info.unknown04 = GfDataBlade::getCreator(blade);
  unknown28->addContents(info);
  updateBladeCount(false, true);
  SCOM_FIELD_VOICE::createMercenariesIn(info.unknown00);
}

bool GfMenuObjMercenaryForm::seqDepartureStart() {
  unknown430 = false;
  unknown108.unknown002(&GfMenuObjMercenaryForm::seqApperBlade);
  unknown8f8 = SCOM_FIELD_VOICE::createMercenariesLeader(GfMenuReference::getReferenceBladeID(0));
  return true;
}

bool GfMenuObjMercenaryForm::seqDepartureEnd() {
  bool isEnd;
  if (!unknown430) {
    GfMenuManager::openCommonWindow(0x25);
    isEnd = false;
    unknown430 = true;
  } else if (!GfMenuManager::isOpenCommonWindow()) {
    ui::UIObjectAcc start(unknown18, "LAY_start");
    sendCloseEvent(start.unknown10, 0, 0.0f);
    u32 team = GfMenuReference::getReferenceTeamID();
    u32 mission = GfMenuReference::getReferenceMissionID();
    for (u32 i = 0; i < unknown28->getSize(); i++) {
      GfGameMercenaries::addTeamMember(team, unknown28->getContents(i).unknown00);
    }
    GfGameMercenaries::orderMission(team, mission);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqLeaveBlade() {
  ui::UIObjectAcc image(unknown18, "LAY_bl_img");
  bool isEnd;
  if (!unknown430) {
    {
      ui::EventData event;
      event.unknown00 = 0x101;
      sendEvent(image.unknown10, event, 0.0f);
    }
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < unknown78->getSize(); i++) {
      name.format("mnu090_anim_sub_%d", i + 1);
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x10000000;
      param.unknown50 = name.c_str();
      param.unknown58 = "end";
      GfMenuObjUtil::startCtrl(unknown78->getObject(i), param, nullptr);
    }
    {
      ui::UIObjectAcc effect(unknown18, "IMG_start_eff");
      effect.setDisp(true);
      effect.startAnimation("end", false);
    }
    isEnd = false;
    unknown430 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(image.unknown10))) {
    unknown108.unknown002(&GfMenuObjMercenaryForm::seqDepartureEnd);
    isEnd = true;
    unknown430 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqPresetSave() {
  bool isEnd;
  if (!unknown430) {
    GfMenuManager::openCommonWindow(0x43);
    isEnd = false;
    unknown430 = true;
  } else if (!GfMenuManager::isOpenCommonWindow()) {
    s16 result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
      u32 index = unknown68->getIndex(true);
      GfMenuBladeList *list = unknown50[index];
      unknown121 *preset = GfDataMercenaries::getPreset(index);
      MenuBladeInfo info;
      info.unknown00 = 0;
      info.unknown04 = 0;
      list->clear();
      for (u32 i = 0; i < 6 && i < unknown28->getSize(); i++) {
        u16 blade = unknown28->getContents(i).unknown00;
        preset->unknown00[i] = blade;
        info.unknown00 = blade;
        if (blade != 0) {
          info.unknown04 = GfDataBlade::getCreator(blade);
        } else {
          info.unknown04 = blade;
        }
        list->addContents(info);
      }
    }
    unknown108.unknown004(30);
    unknown108.unknown002(&GfMenuObjMercenaryForm::seqPresetEnd);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqPresetLoad() {
  u32 index = unknown68->getIndex(true);
  unknown121 *preset = GfDataMercenaries::getPreset(index);
  MenuBladeInfo info;
  info.unknown00 = 0;
  info.unknown04 = 0;
  unknown28->clear();
  for (u32 i = 0; i < 6; i++) {
    u16 blade = preset->unknown00[i];
    u32 creator = 0;
    if (blade == 0) {
      info.unknown00 = blade;
    } else if (GfMenuObjUtil::isBladeSelectable(blade, nullptr)) {
      info.unknown00 = blade;
      creator = GfDataBlade::getCreator(blade);
    } else {
      info.unknown00 = 0;
    }
    info.unknown04 = creator;
    unknown28->addContents(info);
  }
  unknown108.unknown002(&GfMenuObjMercenaryForm::seqPresetEnd);
  return true;
}

} // namespace gf
