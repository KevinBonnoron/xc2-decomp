#include "gf/menu/adapter/gf_menu_game_adapter.h"

#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_util.h"
#include "gf/field/gf_field_manager.h"
#include "gf/field/gf_field_time.h"
#include "gf/field/gf_field_weather.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_reference.h"
#include "ui/plugin/ui_object_time_plugin.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

constexpr u32 ELAPSE_HOUR_MAX = 999;
constexpr u32 ELAPSE_MINUTE_MAX = 59;
constexpr u32 ELAPSE_SECOND_MAX = 59;
constexpr int CHAPTER_MAX = 10;

static GfMenuGameAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuGameAdapter::update_GamePlayTime, {GfMenuAdapter::unknown004_7, 7, 0}},
    {&GfMenuGameAdapter::update_Money, {GfMenuAdapter::unknown004_0, 0, 999999999}},
    {&GfMenuGameAdapter::update_FieldTime, {GfMenuAdapter::unknown004_7, 6, 0}},
    {&GfMenuGameAdapter::update_WeatherIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuGameAdapter::update_CloudIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuGameAdapter::update_MapName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuGameAdapter::update_LocationName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuGameAdapter::update_TimeZoneName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuGameAdapter::update_TimeZoneIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuGameAdapter::update_ReferenceNum, {GfMenuAdapter::unknown004_0, 0, 99999}},
    {&GfMenuGameAdapter::update_MercenariesName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuGameAdapter::update_MercenariesLv, {GfMenuAdapter::unknown004_0, 0, 5}},
    {&GfMenuGameAdapter::update_MercenariesPoint, {GfMenuAdapter::unknown004_0, 0, 99999}},
    {&GfMenuGameAdapter::update_MercenariesPointMax, {GfMenuAdapter::unknown004_0, 0, 99999}},
    {&GfMenuGameAdapter::update_RealYear, {GfMenuAdapter::unknown004_7, 1, 0}},
    {&GfMenuGameAdapter::update_RealTime, {GfMenuAdapter::unknown004_7, 6, 0}},
    {&GfMenuGameAdapter::update_Chapter, {GfMenuAdapter::unknown004_0, 1, 99}},
    {&GfMenuGameAdapter::update_DispAccess, {GfMenuAdapter::unknown004_3, 0, 0}},
};

GfMenuGameAdapter::GfMenuGameAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways) : GfMenuAdapter(plugin, false, isUpdateAlways) {}

GfMenuGameAdapter::~GfMenuGameAdapter() {}

GfMenuAdapter *GfMenuGameAdapter::create(u32 handle, u32 type, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 79 as in the original source: it is the line argument of operator new.
#line 79
      GfMenuGameAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuGameAdapter(plugin, isUpdateAlways);
      adapter->unknown30.bind(adapter, info.update);
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuGameAdapter::update_GamePlayTime() {
  if (GfFieldTime::get() != nullptr) {
    ElapseTime time = GfFieldTime::get()->getElapseTime();
    if (time.unknown01_4 > ELAPSE_HOUR_MAX) {
      time.unknown01_4 = ELAPSE_HOUR_MAX;
      time.unknown00_6 = ELAPSE_MINUTE_MAX;
      time.unknown00_0 = ELAPSE_SECOND_MAX;
    }
    setElapseTime(time);
  }
  return true;
}

bool GfMenuGameAdapter::update_Money() {
  setNumber(GfDataUtil::getMoney());
  return true;
}

bool GfMenuGameAdapter::update_FieldTime() {
  ui::uiDateTime time = {};
  GfFieldTime *fieldTime = GfFieldTime::get();
  if (fieldTime != nullptr) {
    time.unknown03_7 = fieldTime->getHour();
    time.unknown04_6 = fieldTime->getMin();
  }
  setTime(time);
  return true;
}

bool GfMenuGameAdapter::update_WeatherIcon() {
  setNumber(GfMenuBdat::getIconImageIndex(GfMenuBdat::getIconIDFromWeatherType(GfFieldWeather::getCurrentWtrType(false))));
  return true;
}

bool GfMenuGameAdapter::update_CloudIcon() {
  setNumber(GfGameUtilCloudSea::getCloudSea() == 0);
  return GfGameManager::getMapID() == MAP_GULA || GfGameManager::getMapID() == MAP_SUPERBIA;
}

bool GfMenuGameAdapter::update_MapName() {
  const char *name = GfFieldManager::getMapName();
  if (name == nullptr) {
    return false;
  }
  setText(ui::UIStr(name, false));
  return true;
}

bool GfMenuGameAdapter::update_LocationName() {
  u8 *bdat;
  int textId;
  if (!GfFieldManager::getLandmarkNameId(bdat, textId)) {
    return false;
  }
  setText(ui::UIStr(bdat, textId));
  return true;
}

bool GfMenuGameAdapter::update_TimeZoneName() {
  u8 *bdat;
  u32 textId;
  if (GfFieldTime::get() != nullptr && !GfFieldTime::get()->getTimeRangeName(bdat, textId)) {
    return false;
  }
  setText(ui::UIStr(bdat, textId));
  return true;
}

bool GfMenuGameAdapter::update_TimeZoneIcon() {
  if (GfFieldTime::get() == nullptr) {
    return false;
  }
  setNumber(GfFieldTime::get()->getTimeRange());
  return true;
}

bool GfMenuGameAdapter::update_ReferenceNum() {
  int number = GfMenuReference::getReferenceNumber(unknown50);
  setNumber(number);
  return number >= GfMenuReference::getReferenceNumberMin(unknown50) && number <= GfMenuReference::getReferenceNumberMax(unknown50);
}

bool GfMenuGameAdapter::update_MercenariesName() {
  setText(ui::UIStr("Mercenaries", false));
  return true;
}

bool GfMenuGameAdapter::update_MercenariesLv() {
  setNumber(GfDataMercenaries::getLevel());
  return true;
}

bool GfMenuGameAdapter::update_MercenariesPoint() {
  if (GfDataMercenaries::getLevel() == MERCENARIES_LEVEL_MAX) {
    setNumber(0);
  } else {
    setNumberMax(GfDataMercenaries::getPointMax());
    setNumber(GfDataMercenaries::getPoint());
  }
  return true;
}

bool GfMenuGameAdapter::update_MercenariesPointMax() {
  setNumberMax(GfDataMercenaries::getPointMax());
  setNumber(GfDataMercenaries::getPointMax());
  return true;
}

bool GfMenuGameAdapter::update_RealYear() {
  RealTime realTime = {};
  GfFieldTime::get()->getRealTime(realTime);
  ui::uiDateTime time = {};
  time.unknown00_0 = realTime.unknown06_3;
  time.unknown01_5 = realTime.unknown05_7;
  time.unknown03_2 = realTime.unknown04_1;
  setTime(time);
  return true;
}

bool GfMenuGameAdapter::update_RealTime() {
  RealTime realTime = {};
  GfFieldTime::get()->getRealTime(realTime);
  ui::uiDateTime time = {};
  time.unknown03_7 = realTime.unknown03_4;
  time.unknown04_6 = realTime.unknown02_6;
  setTime(time);
  return true;
}

bool GfMenuGameAdapter::update_Chapter() {
  setNumber(GfGameManager::getScenarioId());
  setNumberMax(CHAPTER_MAX);
  return true;
}

bool GfMenuGameAdapter::update_DispAccess() { return GfGameManager::isPlaySequenceClear(); }

void GfMenuGameAdapter::update(const fw::UpdateInfo &info) {
  if (unknown30.isValid() && (unknown20 & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    setDisp(unknown30());
    unknown20 &= ~FLAG_CHANGED;
  }
}

} // namespace gf
