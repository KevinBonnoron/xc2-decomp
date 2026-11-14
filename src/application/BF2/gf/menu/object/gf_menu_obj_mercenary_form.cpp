#include "gf/menu/object/gf_menu_obj_mercenary_form.h"

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/game/gf_game_voice.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/object/gf_menu_obj_cmn_status.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_mercenary_top.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/vector.h"
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

bool GfMenuObjMercenaryForm::seqOpenImage() {
  ui::UIObjectAcc image(unknown18, "IMG_leader_bl_img");
  bool isEnd;
  if (!image.isStreaming()) {
    ui::UIObjectAcc layout(unknown18, "LAY_bl_img");
    u32 blade = GfMenuReference::getReferenceBladeID(0);
    layout.setLayout(image.unknown10, "character");
    GfMenuObjUtil::ImageParam imageParam;
    if (GfMenuObjUtil::getImageParam(1, blade, imageParam, 1)) {
      mm::Vec2 scale;
      image.getScale(scale);
      scale.x = imageParam.unknown04 * scale.x;
      scale.y = imageParam.unknown04 * scale.y;
      image.setScale(scale);
      GfMenuObjUtil::addPos(image.unknown10, imageParam.unknown00, imageParam.unknown02);
    }
    image.setAlpha(1.0f);
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_r");
    param.unknown14 = 8;
    param.unknown11 = true;
    GfMenuObjUtil::startCtrl(image.unknown10, param, nullptr);
    image.setAlpha(0.0f);
    GfMenuObjUtil::playSE("se_fld_allmap_503");
    isEnd = true;
  } else {
    image.setAlpha(0.0f);
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqDepartureStart() {
  unknown430 = false;
  unknown108.unknown002(&GfMenuObjMercenaryForm::seqApperBlade);
  unknown8f8 = SCOM_FIELD_VOICE::createMercenariesLeader(GfMenuReference::getReferenceBladeID(0));
  return true;
}

bool GfMenuObjMercenaryForm::seqApperBlade() {
  if (unknown8f8 != nullptr) {
    if (GfGameVoice::getResult(unknown8f8) >= 3) {
      unknown8f8 = nullptr;
    } else {
      return false;
    }
  }
  ui::UIObjectAcc image(unknown18, "LAY_bl_img");
  bool isEnd;
  if (!unknown430) {
    {
      ui::EventData event;
      event.unknown00 = 0x100;
      sendEvent(image.unknown10, event, 0.0f);
    }
    {
      ui::UIObjectAcc start(unknown18, "LAY_start");
      mm::mtl::FixStr<32> name;
      mm::mtl::FixStr<32> anime;
      for (u32 i = 0; i < unknown78->getSize(); i++) {
        u32 blade = unknown28->getContents(i + 1).unknown00;
        name.format("IMG_mis_start_bl@%02d", i + 1);
        {
          ui::UIObjectAcc bladeImage(start.unknown10, name.c_str());
          start.setLayout(bladeImage.unknown10, "mnu090_anim_sub_1");
          GfMenuObjUtil::ImageParam imageParam;
          if (GfMenuObjUtil::getImageParam(1, blade, imageParam, 1)) {
            mm::Vec2 scale;
            bladeImage.getScale(scale);
            scale.x = imageParam.unknown04 * scale.x;
            scale.y = imageParam.unknown04 * scale.y;
            bladeImage.setScale(scale);
            GfMenuObjUtil::addPos(bladeImage.unknown10, imageParam.unknown00, imageParam.unknown02);
          }
        }
        anime.format("mnu090_anim_sub_%d", i + 1);
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 0x10000000;
        param.unknown50 = anime.c_str();
        param.unknown58 = "start";
        GfMenuObjUtil::startCtrl(unknown78->getObject(i), param, nullptr);
      }
    }
    isEnd = false;
    unknown430 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(image.unknown10))) {
    SCOM_FIELD_VOICE::createMercenariesStart(unknown28->getContents(0).unknown00);
    unknown108.unknown004(60);
    unknown108.unknown002(&GfMenuObjMercenaryForm::seqLeaveBlade);
    isEnd = true;
    unknown430 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
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

void GfMenuObjMercenaryForm::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 0;
    param.unknown00 = 6;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  case 2: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 1;
    param.unknown00 = 6;
    param.unknown0c = true;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjMercenaryForm::FormListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown0c = 0;
    unknown10 = 0;
    GfMenuObjOperationInfo::setGuideText(0x25, 0);
    GfMenuObjCmnStatus::openBlStatus(0, -1);
    break;
  case 3:
    if (event.unknown08 == 0) {
      break;
    }
    if (event.unknown08 == 2) {
      unknown20->sendOpenEvent(acc.searchSibiling("LAY_leader"), 0, 0.0f);
    }
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case GfMenuTypes::unknown003_258: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown04 = 1;
    param.unknown00 = 6;
    param.unknown10 = 2;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    GfMenuObjCmnStatus::closeBlStatus();
    break;
  }
  case GfMenuTypes::unknown003_259: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown04 = 0;
    param.unknown00 = 6;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    unknown20->sendOpenEvent(acc.searchChild("LAY_form_list_bl"), 1, 0.0f);
    GfMenuObjOperationInfo::setGuideText(0x25, 0);
    GfMenuObjCmnStatus::openBlStatus(0, -1);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjMercenaryForm::ApplyListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    acc.setDisp(true);
    ui::UIObjectAcc base(acc.unknown10, "IMG_form_apply_base");
    base.startAnimation("non", false);
    acc.setDispChild(false, "LAY_form_apply_caption");
    unknown0c = 0;
    break;
  }
  case 0xc:
    if (unknown0c == 1) {
      ui::UIObjectAcc base(acc.unknown10, "IMG_form_apply_base");
      base.startAnimation("loop", false);
    }
    break;
  case GfMenuTypes::unknown003_33:
    if (unknown0c == 0) {
      ui::UIObjectAcc caption(acc.unknown10, "LAY_form_apply_caption");
      caption.setDisp(true);
      caption.setAlpha(1.0f);
      GfMenuObjUtil::CtrlParam param;
      param.unknown004("fade_in_r");
      param.unknown11 = true;
      param.unknown14 = 8;
      GfMenuObjUtil::startCtrl(caption.unknown10, param, nullptr);
      {
        ui::UIObjectAcc base(acc.unknown10, "IMG_form_apply_base");
        base.startAnimation("start", false);
        GfMenuObject::hookAnimationEvent(acc.unknown10, base.unknown10);
      }
      acc.setDisp(true);
      unknown0c = 1;
    }
    break;
  case GfMenuTypes::unknown003_34: {
    ui::UIObjectAcc base(acc.unknown10, "IMG_form_apply_base");
    base.startAnimation("non", false);
    {
      ui::UIObjectAcc caption(acc.unknown10, "LAY_form_apply_caption");
      int ctrl = GfMenuObjUtil::getCtrlID(caption.unknown10);
      if (ctrl != -1) {
        GfMenuObjUtil::stopCtrl(ctrl);
      }
      caption.setDisp(false);
    }
    unknown0c = 0;
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjMercenaryForm::BlImgListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case 3:
    break;
  case GfMenuTypes::unknown003_33:
    if (GfMenuReference::getReferenceBladeID(0) != 0) {
      acc.setDisp(true);
      acc.setAlpha(1.0f);
      unknown20->unknown438.unknown005();
      unknown20->unknown438.unknown002(&GfMenuObjMercenaryForm::seqOpenImage);
    }
    break;
  case GfMenuTypes::unknown003_34: {
    ui::UIObjectAcc image(acc.unknown10, "IMG_leader_bl_img");
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_r");
    param.unknown14 = 2;
    param.unknown11 = true;
    GfMenuObjUtil::startCtrl(image.unknown10, param, nullptr);
    break;
  }
  case GfMenuTypes::unknown003_256: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "mnu090_anim_leader";
    param.unknown58 = "start";
    param.unknown11 = true;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    GfMenuObjUtil::playSE(0xf);
    break;
  }
  case GfMenuTypes::unknown003_257: {
    {
      mm::Vec2 scale = {1.0f, 1.0f};
      acc.setScale(scale);
    }
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "mnu090_anim_leader";
    param.unknown58 = "end";
    param.unknown11 = true;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    GfMenuObjUtil::playSE("se_fld_allmap_503");
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjMercenaryForm::StartListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case GfMenuTypes::unknown003_34: {
    GfMenuObjMercenaryTop::OpenParam param;
    param.unknown00 = 0;
    GfMenuObjMercenaryTop::registOpenParam(param);
    GfMenuObject::returnFSSubLayer(acc.unknown10, 2);
    break;
  }
  case GfMenuTypes::unknown003_33: {
    {
      GfMenuBladeList *blades = unknown20->unknown28;
      MenuBladeInfo info = blades->getContents(blades->getIndex(false));
      blades = unknown20->unknown28;
      blades->contents.erase(blades->getIndex(false) + blades->contents.begin());
      blades->subSize(1);
      blades->contentsChanged = true;
      blades = unknown20->unknown28;
      if (blades->getSize() == 0) {
        blades->addContents(info);
      } else {
        blades->contents.insert(blades->contents.begin(), info);
        blades->addSize(1);
        blades->contentsChanged = true;
      }
    }
    mm::mtl::FixStr<32> name;
    unknown20->unknown78->clear();
    for (u32 i = 0; i < 5; i++) {
      if (i < unknown20->unknown28->getSize() - 1) {
        name.format("LAY_mis_start_bl@%02d", i + 1);
        unknown20->unknown78->addObject(acc.searchChild(name.c_str()));
      }
      acc.setDispChild(false, name.c_str());
    }
    acc.setDisp(true);
    unknown20->unknown108.unknown005();
    unknown20->unknown108.unknown002(&GfMenuObjMercenaryForm::seqDepartureStart);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
