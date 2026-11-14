#include "gf/menu/adapter/gf_menu_mission_adapter.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade_arts.h"
#include "gf/data/gf_data_field_skill.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_quest.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_field_time.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/plugin/ui_object_time_plugin.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: mission not started; original name unknown.
constexpr int MISSION_STATE_UNKNOWN_0 = 0;
// Inferred role: mission in progress; original name unknown.
constexpr int MISSION_STATE_UNKNOWN_1 = 1;
// Inferred role: mission complete or its reward received; original name unknown.
constexpr int MISSION_STATE_UNKNOWN_2 = 2;
// Inferred role: number of conditions of a mission; original name unknown.
constexpr int MISSION_TASK_UNKNOWN_3 = 3;

// Inferred role: color of the mission status icon for each state; original name unknown.
static const char *unknown003[] = {"mer_unit_ready", "mer_unit_active", "mer_unit_complete"};

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

bool GfMenuMissionAdapter::update_MissionSummary() {
  u8 *bdat;
  u32 textId;
  u32 mission = unknown58;
  u32 team = GfDataMercenaries::getTeamIDByMissionID(mission);
  if (team == 0 ? GfDataMercenaries::isMissionComplete(mission) : GfDataMercenaries::isTeamStateReward(team)) {
    QuestID quest = GfDataMercenaries::getMissionQuestID(unknown58);
    GfDataQuest::getResult(bdat, textId, quest);
  } else if (!GfDataMercenaries::getMsgSummaryName(bdat, textId, unknown58)) {
    return false;
  }
  if (textId != 0 && bdat != nullptr) {
    setText(ui::UIStr(bdat, textId));
    return true;
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionCategoryIcon() {
  setNumber(GfDataMercenaries::isOrderOnlyOne(unknown58) ? 2 : 1);
  return true;
}

bool GfMenuMissionAdapter::update_MissionTime() {
  ui::uiDateTime time = {};
  int stat = getStat(unknown58, false);
  if (stat == MISSION_STATE_UNKNOWN_2) {
    return false;
  }
  if (stat == MISSION_STATE_UNKNOWN_0) {
    u32 minutes = GfDataMercenaries::getMissionTime(unknown58);
    time.unknown03_7 = minutes / 60;
    time.unknown04_6 = minutes % 60;
  } else if (stat == MISSION_STATE_UNKNOWN_1) {
    ElapseTime elapse = GfDataMercenaries::getTeamMissionTime(GfDataMercenaries::getTeamIDByMissionID(unknown58));
    time.unknown03_7 = elapse.unknown01_4;
    time.unknown04_6 = elapse.unknown00_6;
    time.unknown05_5 = elapse.unknown00_0;
  }
  setTime(time);
  return true;
}

bool GfMenuMissionAdapter::update_MissionStatusIcon() {
  setNumber(getStat(unknown58, true));
  return true;
}

bool GfMenuMissionAdapter::update_MissionStatus() {
  int stat = getStat(unknown58, true);
  int name;
  if (stat == 2) {
    name = 13;
  } else if (stat == 0) {
    if (!GfMenuObjUtil::checkMissionCond(unknown58, unknown68)) {
      return false;
    }
    name = 11;
  } else {
    name = 12;
  }
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_MSG_MERCENARIES);
  u8 *msBdat = GfDataBdat::getFP(BDAT_MENU_MS);
  u16 id = Bdat::getVal(bdat, "name", name).valueU16;
  setText(ui::UIStr(msBdat, id));
  return true;
}

bool GfMenuMissionAdapter::update_MissionStatusColor() {
  const char *color = unknown003[getStat(unknown58, true)];
  switch (unknown70) {
  case 0:
    setAddColor(color);
    return true;
  case 1:
    setMulColor(color);
    return true;
  case 2:
    if (GfDataMercenaries::getTeamIDByMissionID(unknown58) != 0) {
      setAddColor(color);
      return true;
    }
    return false;
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionRewardGold() {
  bool isOrder = GfDataMercenaries::isMissionOrderTeam(unknown58);
  setNumber(GfGameMercenaries::getRewardGold(unknown58, isOrder));
  return true;
}

bool GfMenuMissionAdapter::update_MissionRewardGoldBonus() {
  bool isOrder = GfDataMercenaries::isMissionOrderTeam(unknown58);
  setNumber(GfGameMercenaries::getRewardGoldHosei(unknown58, isOrder));
  return true;
}

bool GfMenuMissionAdapter::update_MissionRewardExp() {
  bool isOrder = GfDataMercenaries::isMissionOrderTeam(unknown58);
  setNumber(GfGameMercenaries::getRewardExp(unknown58, isOrder));
  return true;
}

bool GfMenuMissionAdapter::update_MissionRewardZone() {
  u8 *bdat;
  u32 textId;
  if (GfDataMercenaries::getMsgZoneName(bdat, textId, unknown58)) {
    setText(ui::UIStr(bdat, textId));
    return true;
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionRewardZonePoint() {
  bool isOrder = GfDataMercenaries::isMissionOrderTeam(unknown58);
  setNumber(GfGameMercenaries::getRewardDevelop(unknown58, isOrder) - GfGameMercenaries::getRewardDevelopHosei(unknown58, isOrder));
  return true;
}

bool GfMenuMissionAdapter::update_MissionRewardZonePointBonus() {
  bool isOrder = GfDataMercenaries::isMissionOrderTeam(unknown58);
  setNumber(GfGameMercenaries::getRewardDevelopHosei(unknown58, isOrder));
  return true;
}

bool GfMenuMissionAdapter::update_MissionRewardIdeaPoint() {
  setNumber(GfGameMercenaries::getRewardTrust(unknown58));
  return true;
}

bool GfMenuMissionAdapter::update_MissionRewardMerPoint() {
  setNumber(GfGameMercenaries::getRewardMercenariesPoint(unknown58));
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

// Inferred role: looks up the text of a menu message list entry; original name unknown.
static void unknown001(u8 *&bdat, u32 &textId, u32 bdatId, u32 listId, u16 id) {
  bdat = GfDataBdat::getFP(bdatId);
  textId = GfMenuObjUtil::getMsgIDFromList(listId, id);
}

// Inferred role: looks up the text of a menu message list entry with a 1-based index; original name unknown.
static void unknown002(u8 *&bdat, u32 &textId, u32 bdatId, u32 listId, u16 id) {
  bdat = GfDataBdat::getFP(bdatId);
  textId = GfMenuObjUtil::getMsgIDFromList(listId, id + 1);
}

bool GfMenuMissionAdapter::update_MissionCond() {
  if (unknown70 >= MISSION_TASK_UNKNOWN_3) {
    return false;
  }
  GfRequestBladeData data = {};
  if (!GfDataMercenaries::getRequestCondition(data, unknown58, unknown70)) {
    return false;
  }
  u8 *bdat = nullptr;
  u32 textId = 0;
  switch (data.unknown00) {
  case 1:
    unknown001(bdat, textId, BDAT_ITM_PCWPNTYPE_MS, BDAT_MNU_MSG_WEAPON_TYPE, data.unknown04);
    break;
  case 2:
    unknown001(bdat, textId, BDAT_MENU_MS, BDAT_MNU_MSG_MERCENARIES, 19);
    break;
  case 3:
    unknown001(bdat, textId, BDAT_MENU_MS, BDAT_MNU_MSG_RACE, data.unknown04);
    break;
  case 4:
    unknown001(bdat, textId, BDAT_MENU_MS, BDAT_MNU_MSG_GENDER, data.unknown04);
    break;
  case 5:
    if (!GfDataBladeArts::getName(bdat, textId, data.unknown04)) {
      return false;
    }
    break;
  case 6:
    if (!GfDataFieldSkill::getName(bdat, textId, data.unknown04)) {
      return false;
    }
    break;
  case 7:
    unknown002(bdat, textId, BDAT_MENU_ATTR_MS, BDAT_MNU_MSG_ATTR, data.unknown04);
    break;
  default:
    return false;
  }
  setText(ui::UIStr(bdat, textId));
  return true;
}

bool GfMenuMissionAdapter::update_MissionCondIcon() {
  if (unknown70 < MISSION_TASK_UNKNOWN_3) {
    GfRequestBladeData data = {};
    if (GfDataMercenaries::getRequestCondition(data, unknown58, unknown70)) {
      setNumber(data.unknown00 - 1);
      return true;
    }
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionCondParam() {
  if (unknown70 < MISSION_TASK_UNKNOWN_3) {
    GfRequestBladeData data = {};
    if (GfDataMercenaries::getRequestCondition(data, unknown58, unknown70) && data.unknown00 == 2) {
      setNumber(data.unknown08);
      return true;
    }
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionCondLv() {
  if (unknown70 < MISSION_TASK_UNKNOWN_3) {
    GfRequestBladeData data = {};
    if (GfDataMercenaries::getRequestCondition(data, unknown58, unknown70)) {
      if (data.unknown00 == 5) {
        setNumber(data.unknown08);
      } else if (data.unknown00 == 6) {
        setNumber(data.unknown08);
      } else {
        return false;
      }
      return true;
    }
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionCondBladeMax() {
  if (unknown70 < MISSION_TASK_UNKNOWN_3) {
    GfRequestBladeData data = {};
    if (GfDataMercenaries::getRequestCondition(data, unknown58, unknown70)) {
      setNumber(data.unknown0c == 0 ? 1 : data.unknown0c);
      return true;
    }
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionCondBladeCount() {
  if (unknown70 < MISSION_TASK_UNKNOWN_3 && unknown68 != nullptr && unknown68->getSize() != 0) {
    GfRequestBladeData data = {};
    if (GfDataMercenaries::getRequestCondition(data, unknown58, unknown70)) {
      setNumber(GfMenuObjUtil::getMissionCondBladeCount(data, unknown68));
      return true;
    }
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionCondCheckIcon() {
  if (unknown70 < MISSION_TASK_UNKNOWN_3 && unknown68 != nullptr && unknown68->getSize() != 0) {
    GfRequestBladeData data = {};
    if (GfDataMercenaries::getRequestCondition(data, unknown58, unknown70)) {
      u32 count = GfMenuObjUtil::getMissionCondBladeCount(data, unknown68);
      u32 need = data.unknown0c == 0 ? 1 : data.unknown0c;
      setNumber(count >= need);
      return true;
    }
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionCondCheckDisp() {
  if (unknown68 != nullptr && unknown68->getSize() != 0) {
    if (unknown70 == -1) {
      return GfMenuObjUtil::checkMissionCond(unknown58, unknown68);
    }
    if (unknown70 < MISSION_TASK_UNKNOWN_3) {
      GfRequestBladeData data = {};
      if (GfDataMercenaries::getRequestCondition(data, unknown58, unknown70)) {
        u32 count = GfMenuObjUtil::getMissionCondBladeCount(data, unknown68);
        u32 need = data.unknown0c == 0 ? 1 : data.unknown0c;
        return count >= need;
      }
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

bool GfMenuMissionAdapter::update_MissionPartyIcon() {
  if (GfDataMercenaries::isMissionOrderParty(unknown58)) {
    setNumber(0);
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
  if (unknown70 >= MISSION_TASK_UNKNOWN_3) {
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
          DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_UNKNOWN_0);
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
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_UNKNOWN_0);
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
      DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_UNKNOWN_0);
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

bool GfMenuMissionAdapter::update_MissionFieldSkillLevelCount() {
  if (unknown68 != nullptr && unknown68->getSize() != 0) {
    int fieldSkill = GfDataMercenaries::getFieldSkill(unknown58, unknown70);
    if (fieldSkill == 0) {
      return false;
    }
    int level = 0;
    for (u32 i = 0; i < unknown68->getSize(); i++) {
      DataParamAcc acc(OBJECT_TYPE_BLADE, unknown68->getContents(i).unknown00, GIMMICK_TYPE_UNKNOWN_0);
      u32 index;
      if (acc.getFieldSkill(0, false) == fieldSkill) {
        index = 0;
      } else if (acc.getFieldSkill(1, false) == fieldSkill) {
        index = 1;
      } else if (acc.getFieldSkill(2, false) == fieldSkill) {
        index = 2;
      } else {
        continue;
      }
      level += acc.getFieldSkillLevel(index, false);
    }
    setNumber(level);
    return true;
  }
  return false;
}

bool GfMenuMissionAdapter::update_MissionFieldSkillBladeCount() {
  if (unknown68 != nullptr && unknown68->getSize() != 0) {
    int fieldSkill = GfDataMercenaries::getFieldSkill(unknown58, unknown70);
    if (fieldSkill == 0) {
      return false;
    }
    int count = 0;
    for (u32 i = 0; i < unknown68->getSize(); i++) {
      DataParamAcc acc(OBJECT_TYPE_BLADE, unknown68->getContents(i).unknown00, GIMMICK_TYPE_UNKNOWN_0);
      if (acc.getFieldSkill(0, false) == fieldSkill || acc.getFieldSkill(1, false) == fieldSkill || acc.getFieldSkill(2, false) == fieldSkill) {
        count++;
      }
    }
    setNumber(count);
    return true;
  }
  return false;
}

GfMenuMissionAdapter *GfMenuMissionAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  GfMenuMissionAdapter *adapter = create(handle, type, converter->getMissionId(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

GfMenuMissionAdapter *GfMenuMissionAdapter::createFromList(u32 handle, u32 type, GfMenuIDList *list, u32 index, GfMenuBladeList *bladeList, bool isUpdateAlways) {
  // __LINE__ must be 261 as in the original source: it is the line argument of operator new.
#line 261
  ListConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListConverter(list, index);
  GfMenuMissionAdapter *adapter = create(handle, type, converter->getMissionId(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
    if (bladeList != nullptr) {
      adapter->unknown68 = bladeList;
      bladeList->addRef();
    }
  }
  return adapter;
}

GfMenuMissionAdapter *GfMenuMissionAdapter::createFromMissionList(u32 handle, u32 type, GfMenuMissionList *list, u32 index, bool isUpdateAlways) {
  // __LINE__ must be 276 as in the original source: it is the line argument of operator new.
#line 276
  MissionListConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MissionListConverter(list, index);
  GfMenuMissionAdapter *adapter = create(handle, type, converter->getMissionId(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

GfMenuMissionAdapter *GfMenuMissionAdapter::createFromReference(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, bool isUpdateAlways) {
  // __LINE__ must be 284 as in the original source: it is the line argument of operator new.
#line 284
  ReferenceConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceConverter(number);
  GfMenuMissionAdapter *adapter = create(handle, type, converter->getMissionId(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

GfMenuMissionAdapter *GfMenuMissionAdapter::createFromReferenceMission(u32 handle, u32 type, u32 index, bool isUpdateAlways) {
  // __LINE__ must be 296 as in the original source: it is the line argument of operator new.
#line 296
  ReferenceMissionConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceMissionConverter();
  GfMenuMissionAdapter *adapter = create(handle, type, GfMenuReference::getReferenceMissionID(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
    adapter->unknown70 = index;
  }
  return adapter;
}

GfMenuMissionAdapter *GfMenuMissionAdapter::createFromBladeList(u32 handle, u32 type, u32 mission, GfMenuBladeList *list, bool isUpdateAlways) {
  GfMenuMissionAdapter *adapter = create(handle, type, mission, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown68 = list;
    list->addRef();
  }
  return adapter;
}

GfMenuMissionAdapter *GfMenuMissionAdapter::createFromReferenceMissionBladeList(u32 handle, u32 type, int index, GfMenuBladeList *list, bool isUpdateAlways) {
  // __LINE__ must be 323 as in the original source: it is the line argument of operator new.
#line 323
  ReferenceMissionConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceMissionConverter();
  GfMenuMissionAdapter *adapter = create(handle, type, GfMenuReference::getReferenceMissionID(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
    adapter->unknown68 = list;
    list->addRef();
    adapter->unknown70 = index;
  }
  return adapter;
}

void GfMenuMissionAdapter::update(const fw::UpdateInfo &info) {
  if (unknown50 != nullptr) {
    u32 newMission = unknown50->getMissionId();
    if (newMission != unknown58) {
      unknown58 = newMission;
      setChange();
    }
  }
  int stat = getStat(unknown58, false);
  if (unknown5c != stat) {
    unknown5c = stat;
    setChange();
  }
  if (unknown30.isValid() && (unknown20 & (FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1)) != 0) {
    setDisp(unknown58 != 0 ? unknown30() : false);
    unknown20 &= ~FLAG_UNKNOWN_0;
  }
}

int GfMenuMissionAdapter::getStat(u32 mission, bool isOrderParty) {
  u32 team = GfDataMercenaries::getTeamIDByMissionID(mission);
  if (team == 0 && isOrderParty && GfDataMercenaries::isMissionOrderParty(mission)) {
    return MISSION_STATE_UNKNOWN_1;
  }
  if (team == 0) {
    return GfDataMercenaries::isMissionComplete(mission) ? MISSION_STATE_UNKNOWN_2 : MISSION_STATE_UNKNOWN_0;
  }
  return GfDataMercenaries::isTeamStateReward(team) ? MISSION_STATE_UNKNOWN_2 : MISSION_STATE_UNKNOWN_1;
}

u32 GfMenuMissionAdapter::MissionListConverter::getMissionId() {
  if (listIndex < list->getSize()) {
    return list->getContents(listIndex).unknown00;
  }
  return 0;
}

u32 GfMenuMissionAdapter::ReferenceConverter::getMissionId() { return number->unknown0c; }

u32 GfMenuMissionAdapter::ListConverter::getMissionId() {
  if (listIndex < list->getSize()) {
    return list->getContents(list->getPageIndex(listIndex)).unknown00;
  }
  return 0;
}

u32 GfMenuMissionAdapter::ReferenceMissionConverter::getMissionId() { return GfMenuReference::getReferenceMissionID(); }

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuMissionAdapter>(const mm::mtl::Delegate<bool()> *);
