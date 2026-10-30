#include "gf/menu/adapter/gf_menu_zone_adapter.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_develop.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/fixed_vector.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

constexpr u32 MISSION_CATEGORY_QUEST = 3;
constexpr u32 NOTICE_TEAM_FIRST = 1;
constexpr u32 MERCENARIES_MSG_QUEST_MISSION = 0x11;
constexpr u32 MERCENARIES_MSG_NEW_MISSION = 0x12;

static GfMenuZoneAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuZoneAdapter::update_ZoneName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuZoneAdapter::update_ZoneLv, {GfMenuAdapter::unknown004_0, 1, 5}},
    {&GfMenuZoneAdapter::update_ZoneIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuZoneAdapter::update_ZoneLvIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuZoneAdapter::update_ZoneStatColor, {GfMenuAdapter::unknown004_8, 0, 0}},
    {&GfMenuZoneAdapter::update_ZoneNoticeDisp, {GfMenuAdapter::unknown004_3, 0, 0}},
    {&GfMenuZoneAdapter::update_ZoneNotice, {GfMenuAdapter::unknown004_2, 0, 0}},
};

GfMenuZoneAdapter::GfMenuZoneAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways) : GfMenuAdapter(plugin, false, isUpdateAlways), unknown50(nullptr), unknown58(0), unknown5c(0) {}

GfMenuZoneAdapter::~GfMenuZoneAdapter() {
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
}

GfMenuZoneAdapter *GfMenuZoneAdapter::create(u32 handle, u32 type, u16 zone, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 125 as in the original source: it is the line argument of operator new.
#line 125
      GfMenuZoneAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuZoneAdapter(plugin, isUpdateAlways);
      adapter->unknown30.bind(adapter, info.update);
      adapter->unknown58 = zone;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuZoneAdapter::update_ZoneName() {
  setText(ui::UIStr(GfDataBdat::getFP(BDAT_FLD_DEVELOPMENTNAME), unknown58));
  return true;
}

bool GfMenuZoneAdapter::update_ZoneLv() {
  setNumber(GfDataDevelop::getLevel(unknown58));
  return true;
}

bool GfMenuZoneAdapter::update_ZoneIcon() {
  if (unknown58 == 0) {
    return false;
  }
  setNumber(unknown58 - 1);
  return true;
}

bool GfMenuZoneAdapter::update_ZoneLvIcon() {
  setNumber(GfDataDevelop::getLevel(unknown58));
  return true;
}

bool GfMenuZoneAdapter::update_ZoneStatColor() {
  if (GfDataMercenaries::getTeamNum() < unknown5c) {
    return false;
  }
  mm::mtl::FixedVector<u16, 3> workingTeams;
  GfDataMercenaries::getTeamByZoneMissionWorking(workingTeams, unknown58);
  mm::mtl::FixedVector<u16, 3> completeTeams;
  GfDataMercenaries::getTeamByZoneMissionComplete(completeTeams, unknown58);

  const char *color = "mer_unit_ready";
  bool isWorking = false;
  for (u16 i = 0; i < workingTeams.size(); i++) {
    if (*workingTeams.at(i) == unknown5c) {
      color = "mer_unit_active";
      isWorking = true;
      break;
    }
  }
  bool isComplete = false;
  for (u16 i = 0; i < completeTeams.size(); i++) {
    if (*completeTeams.at(i) == unknown5c) {
      isComplete = true;
      break;
    }
  }
  if (isComplete) {
    color = "blue";
  } else if (!isWorking) {
    color = GfDataMercenaries::isTeamStateExpedition(unknown5c) || GfDataMercenaries::isTeamStateReward(unknown5c) ? "darkgray" : color;
  }
  setAddColor(color);
  return true;
}

bool GfMenuZoneAdapter::update_ZoneNoticeDisp() {
  mm::mtl::FixedVector<u16, 500> missions;
  GfGameMercenaries::getZoneMission(missions, unknown58);
  for (u16 *mission = missions.begin(); mission != missions.end(); mission++) {
    if (GfDataMercenaries::getMissionCategory(*mission) == MISSION_CATEGORY_QUEST) {
      return true;
    }
    if (GfDataMercenaries::isNewMission(*mission)) {
      return true;
    }
  }
  return false;
}

bool GfMenuZoneAdapter::update_ZoneNotice() {
  mm::mtl::FixedVector<u16, 500> missions;
  GfGameMercenaries::getZoneMission(missions, unknown58);
  int questNum = 0;
  int newNum = 0;
  for (u16 *mission = missions.begin(); mission != missions.end(); mission++) {
    if (GfDataMercenaries::getMissionCategory(*mission) == MISSION_CATEGORY_QUEST) {
      questNum++;
    }
    newNum += GfDataMercenaries::isNewMission(*mission);
  }
  bool hasQuest = questNum > 0;

  u8 *menuBdat = GfDataBdat::getFP(BDAT_MENU_MS);
  u8 *msgBdat = GfDataBdat::getFP(BDAT_MNU_MSG_MERCENARIES);
  int msg;
  if (unknown5c == NOTICE_TEAM_FIRST) {
    if (hasQuest) {
      msg = MERCENARIES_MSG_QUEST_MISSION;
    } else if (newNum > 0) {
      msg = MERCENARIES_MSG_NEW_MISSION;
    } else {
      return false;
    }
  } else if (hasQuest && newNum > 0) {
    msg = MERCENARIES_MSG_NEW_MISSION;
  } else {
    return false;
  }
  setText(ui::UIStr(menuBdat, Bdat::getVal(msgBdat, "name", msg).valueU16));
  return true;
}

GfMenuZoneAdapter *GfMenuZoneAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  GfMenuZoneAdapter *adapter = create(handle, type, converter->getZoneId(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

GfMenuZoneAdapter *GfMenuZoneAdapter::createFromReferenceZone(u32 handle, u32 type, bool isUpdateAlways) {
  // __LINE__ must be 153 as in the original source: it is the line argument of operator new.
#line 153
  ReferenceZoneConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceZoneConverter();
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

GfMenuZoneAdapter *GfMenuZoneAdapter::createFromReference(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, bool isUpdateAlways) {
  // __LINE__ must be 161 as in the original source: it is the line argument of operator new.
#line 161
  ReferenceNumberConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceNumberConverter(number);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

void GfMenuZoneAdapter::update(const fw::UpdateInfo &info) {
  if (unknown50 != nullptr) {
    u32 newZone = unknown50->getZoneId();
    if (unknown58 != newZone) {
      unknown58 = newZone;
      setChange();
    }
  }

  if (unknown30.isValid() && (unknown20 & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    if (unknown58 != 0) {
      setDisp(unknown30());
    } else {
      setDisp(false);
    }
    unknown20 &= ~FLAG_CHANGED;
  }
}

} // namespace gf
