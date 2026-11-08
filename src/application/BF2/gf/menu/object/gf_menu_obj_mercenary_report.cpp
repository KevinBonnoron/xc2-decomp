#include "gf/menu/object/gf_menu_obj_mercenary_report.h"

#include "gf/data/gf_data_mercenaries.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/object/gf_menu_obj_bl_kizuna_ring.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjMercenaryReport::GfMenuObjMercenaryReport(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown28(nullptr), unknown30(this), unknown358(false), unknown359(false), unknown360(nullptr), unknown368(nullptr), unknown370(nullptr) {
  unknown360 = unknown160();
  unknown368 = GfMenuCallContext::create();
  unknown370 = GfMenuCallContext::create();
}

GfMenuObjMercenaryReport::~GfMenuObjMercenaryReport() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown370);
  mm::mtl::safeRelease(unknown368);
  unknown360 = nullptr;
}

void GfMenuObjMercenaryReport::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMercenaryReport::update() {
  unknown30.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjMercenaryReport::seqEnd() {
  bool isEnd;
  if (!GfMenuManager::isSwitchingFullScreen()) {
    changeFSSubLayer(unknown18, 2, 0x34, false);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryReport::seqDispInfo() {
  ui::UIObjectAcc report(unknown18, "LAY_report");
  ui::UIObjectAcc effect(report.unknown10, "IMG_report_eff");
  bool isEnd;
  if (!unknown358) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_r");
    GfMenuObjUtil::startCtrl(report.unknown10, param, nullptr);
    effect.startAnimation("start", false);
    effect.setDisp(true);
    GfMenuObjUtil::playSE(16);
    isEnd = false;
    unknown358 = true;
  } else if (!effect.isPlayingAnimation()) {
    unknown358 = false;
    unknown30.unknown004(60);
    unknown30.unknown002(&GfMenuObjMercenaryReport::seqDispReward);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryReport::seqDispReward() {
  bool isEnd;
  if (!unknown358) {
    ui::UIObjectAcc reward(unknown18, "LAY_reward");
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    sendEvent(reward.unknown10, event, 0.0f);
    unknown358 = true;
    isEnd = false;
  } else if (!unknown359) {
    isEnd = false;
  } else {
    unknown358 = false;
    unknown30.unknown002(&GfMenuObjMercenaryReport::seqClose);
    isEnd = true;
  }
  return isEnd;
}

bool GfMenuObjMercenaryReport::seqClose() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  bool isEnd;
  if (!unknown358) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_l");
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(main.unknown10, param, "LAY_report");
    GfMenuObjUtil::startCtrl(main.unknown10, param, "LAY_bl_img");
    isEnd = false;
    unknown358 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(main.searchChild("LAY_report")))) {
    main.setDispChild(false, "LAY_bl_img");
    u32 mission = GfDataMercenaries::getTeamMission(unknown24);
    GfGameMercenaries::execMissionRewardByTeamID(unknown24);
    GfGameMercenaries::clearTeamMember(unknown24);
    if (GfDataMercenaries::isEnableOrder(mission)) {
      GfGameMercenaries::setMissionFlag(mission, 1);
    }
    unknown24 = 0;
    unknown30.unknown004(15);
    unknown30.unknown002(&GfMenuObjMercenaryReport::seqCheckAchive);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryReport::seqWaitLoadKizuna() {
  if (!GfMenuManager::isSwitchingFullScreen()) {
    unknown370->reset();
    if (GfMenuObjBlKizunaRing::attach(unknown370)) {
      unknown30.unknown002(&GfMenuObjMercenaryReport::seqWaitEndKizuna);
      return true;
    }
  }
  return false;
}

bool GfMenuObjMercenaryReport::seqWaitEndKizuna() {
  bool isEnd;
  if (unknown370->isTerm() && !GfMenuManager::isSwitchingFullScreen()) {
    unknown30.unknown002(&GfMenuObjMercenaryReport::seqCheckAchive);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

void GfMenuObjMercenaryReport::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown20->unknown30.unknown005();
    unknown20->unknown30.unknown002(&GfMenuObjMercenaryReport::seqStart);
    GfMenuObjOperationInfo::setGuideDisp(false);
    break;
  case 2: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 1;
    param.unknown00 = 6;
    param.unknown0c = true;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  case 3:
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
