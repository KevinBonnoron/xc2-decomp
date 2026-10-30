#include "gf/menu/adapter/gf_menu_mission_adapter.h"

#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "mm_mtl/reference_object.h"
#include "ui/plugin/ui_object_time_plugin.h"
#include "ui/ui_str.h"

namespace gf {

constexpr int MISSION_STATE_READY = 0;
constexpr int MISSION_STATE_WORKING = 1;
constexpr int MISSION_STATE_COMPLETE = 2;
constexpr int MISSION_TASK_MAX = 3;

GfMenuMissionAdapter::GfMenuMissionAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways)
    : GfMenuAdapter(plugin, false, isUpdateAlways), unknown50(nullptr), unknown58(0), unknown5c(0), unknown60(0), unknown64(0), unknown68(nullptr), unknown70(0) {}

GfMenuMissionAdapter::~GfMenuMissionAdapter() {
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
  mm::mtl::safeRelease(unknown68);
}

bool GfMenuMissionAdapter::update_MissionName() {
  u8 *bdat;
  u32 textId;
  if (GfDataMercenaries::getMsgTitleName(bdat, textId, unknown58)) {
    setText(ui::UIStr(bdat, textId));
    return true;
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionCategoryIcon() {
  setNumber(GfDataMercenaries::isOrderOnlyOne(unknown58) ? 2 : 1);
  return true;
}

bool GfMenuMissionAdapter::update_MissionRewardIdeaPoint() {
  setNumber(GfGameMercenaries::getRewardTrust(unknown58));
  return true;
}

bool GfMenuMissionAdapter::update_MissionFieldSkill() {
  u8 *bdat;
  u32 textId;
  if (GfDataMercenaries::getFieldSkillInfo(bdat, textId, unknown58, unknown70)) {
    setText(ui::UIStr(bdat, textId));
    return true;
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionCondIcon() {
  if (unknown70 < MISSION_TASK_MAX) {
    GfRequestBladeData data = {};
    if (GfDataMercenaries::getRequestCondition(data, unknown58, unknown70)) {
      setNumber(data.unknown00 - 1);
      return true;
    }
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionCondParam() {
  if (unknown70 < MISSION_TASK_MAX) {
    GfRequestBladeData data = {};
    if (GfDataMercenaries::getRequestCondition(data, unknown58, unknown70) && data.unknown00 == 2) {
      setNumber(data.unknown08);
      return true;
    }
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionCondBladeMax() {
  if (unknown70 < MISSION_TASK_MAX) {
    GfRequestBladeData data = {};
    if (GfDataMercenaries::getRequestCondition(data, unknown58, unknown70)) {
      setNumber(data.unknown0c == 0 ? 1 : data.unknown0c);
      return true;
    }
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionTeamIcon() {
  u32 team = GfDataMercenaries::getTeamIDByMissionID(unknown58);
  if (team != 0) {
    setNumber(team - 1);
    return true;
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionStateIcon() {
  if (GfDataMercenaries::isMissionCompleteFlag(unknown58)) {
    setNumber(2);
    return true;
  }
  if (GfDataMercenaries::isNewMission(unknown58)) {
    setNumber(0);
    return true;
  }
  if (GfDataMercenaries::isMissionOrderTeam(unknown58)) {
    setNumber(1);
    return true;
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionNewDisp() { return unknown58 != 0 && GfDataMercenaries::isNewMission(unknown58); }

bool GfMenuMissionAdapter::update_MissionCondParamIcon() {
  if (unknown70 >= MISSION_TASK_MAX) {
    return false;
  }
  GfRequestBladeData data = {};
  if (!GfDataMercenaries::getRequestCondition(data, unknown58, unknown70) || data.unknown00 != unknown64) {
    return false;
  }
  u32 icon;
  if (data.unknown00 == 1) {
    icon = data.unknown04;
  } else if (data.unknown00 == 3) {
    icon = data.unknown04 - 1;
  } else if (data.unknown00 == 4) {
    icon = data.unknown04 >> 1;
  } else {
    return false;
  }
  setNumber(icon);
  return true;
}

bool GfMenuMissionAdapter::update_MissionProgressDisp() {
  u32 mission = unknown58;
  if (mission == 0) {
    return false;
  }
  u32 team = GfDataMercenaries::getTeamIDByMissionID(mission);
  if (team == 0) {
    return GfDataMercenaries::isMissionComplete(mission);
  }
  GfDataMercenaries::isTeamStateReward(team);
  return true;
}

bool GfMenuMissionAdapter::update_MissionFieldSkillColor() {
  int fieldSkill = GfDataMercenaries::getFieldSkill(unknown58, unknown70);
  if (fieldSkill != 0) {
    unknown120 *team = GfDataMercenaries::getTeamMember(GfMenuReference::getReferenceTeamID());
    if (team != nullptr) {
      for (u16 blade : team->unknown00) {
        if (blade != 0) {
          DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_NONE);
          if (acc.getFieldSkill(0, false) == fieldSkill || acc.getFieldSkill(1, false) == fieldSkill || acc.getFieldSkill(2, false) == fieldSkill) {
            setMulColor(nullptr);
            return true;
          }
        }
      }
      setMulColor("darkgray");
      return true;
    }
  }
  return false;
}

bool GfMenuMissionAdapter::update_MemberFieldSkillLv() {
  int fieldSkill = GfDataMercenaries::getFieldSkill(unknown58, unknown70);
  if (fieldSkill == 0) {
    return false;
  }
  unknown120 *team = GfDataMercenaries::getTeamMember(GfMenuReference::getReferenceTeamID());
  if (team == nullptr) {
    return false;
  }
  u16 blade = team->unknown00[unknown60];
  if (blade == 0) {
    return false;
  }
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_NONE);
  u32 index;
  if (acc.getFieldSkill(0, false) == fieldSkill) {
    index = 0;
  } else if (acc.getFieldSkill(1, false) == fieldSkill) {
    index = 1;
  } else if (acc.getFieldSkill(2, false) == fieldSkill) {
    index = 2;
  } else {
    return false;
  }
  setNumber(acc.getFieldSkillLevel(index, false));
  return true;
}

bool GfMenuMissionAdapter::update_MemberFieldSkillColor() {
  int fieldSkill = GfDataMercenaries::getFieldSkill(unknown58, unknown70);
  if (fieldSkill != 0) {
    unknown120 *team = GfDataMercenaries::getTeamMember(GfMenuReference::getReferenceTeamID());
    if (team == nullptr) {
      return false;
    }
    u16 blade = team->unknown00[unknown60];
    if (blade != 0) {
      DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_NONE);
      if (acc.getFieldSkill(0, false) == fieldSkill || acc.getFieldSkill(1, false) == fieldSkill || acc.getFieldSkill(2, false) == fieldSkill) {
        setMulColor(nullptr);
      } else {
        setMulColor("gray");
      }
      return true;
    }
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionTimeOriginal() {
  u32 minutes = GfDataMercenaries::getMissionTime(unknown58);
  ui::uiDateTime time = {};
  time.unknown03_7 = minutes / 60;
  time.unknown04_6 = minutes % 60;
  if (time.unknown03_7 != 0 || time.unknown04_6 != 0) {
    setTime(time);
    return true;
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionTimeAdjust() {
  u32 team = GfDataMercenaries::getTeamIDByMissionID(unknown58);
  if (team != 0) {
    u32 minutes = GfDataMercenaries::getTeamMissionTime(team, unknown58);
    ui::uiDateTime time = {};
    time.unknown03_7 = minutes / 60;
    time.unknown04_6 = minutes % 60;
    setTime(time);
    return true;
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionFieldSkillDisp() { return GfDataMercenaries::getFieldSkill(unknown58, unknown70) != 0; }

bool GfMenuMissionAdapter::update_MissionFieldSkillBladeMax() {
  if (GfDataMercenaries::getFieldSkill(unknown58, unknown70) != 0) {
    setNumber(6);
    return true;
  }
  return false;
}

} // namespace gf
