#include "gf/menu/adapter/gf_menu_skill_adapter.h"

#include "gf/data/gf_data_driver_skill.h"
#include "gf/gf_allocator.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

constexpr u32 SKILL_LEVEL_FIRST = 1;

static GfMenuSkillAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuSkillAdapter::update_SkillName, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuSkillAdapter::update_SkillCaption, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuSkillAdapter::update_SkillPoint, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 99999}},
    {&GfMenuSkillAdapter::update_SkillReleaseFlagIcon, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuSkillAdapter::update_SkillReleaseFlagColor, {GfMenuAdapter::PLUGIN_TYPE_COLOR, 0, 0}},
    {&GfMenuSkillAdapter::update_SkillReleaseFlagColorIcon, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuSkillAdapter::update_SkillLearnDisp, {GfMenuAdapter::PLUGIN_TYPE_COLOR, 0, 0}},
    {&GfMenuSkillAdapter::update_SkillLevelLockIcon, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuSkillAdapter::update_SkillLearnNum, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 15}},
    {&GfMenuSkillAdapter::update_SkillLearnMax, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 15}},
    {&GfMenuSkillAdapter::update_SkillLevelUnlockNum, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 15}},
};

GfMenuSkillAdapter::GfMenuSkillAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways)
    : GfMenuAdapter(plugin, false, isUpdateAlways), unknown50(nullptr), _58(), unknown5c(0), unknown60(0), unknown64(0), unknown68(0) {}

GfMenuSkillAdapter::~GfMenuSkillAdapter() {
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
}

GfMenuSkillAdapter *GfMenuSkillAdapter::create(u32 handle, u32 type, u32 driver, u16 line, u16 level, u16 round, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 192 as in the original source: it is the line argument of operator new.
#line 192
      GfMenuSkillAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuSkillAdapter(plugin, isUpdateAlways);
      adapter->unknown30.bind(adapter, info.update);
      adapter->unknown5c = driver;
      adapter->unknown60 = line;
      adapter->unknown64 = level;
      adapter->unknown68 = round;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuSkillAdapter::update_SkillName() {
  if (unknown60 >= SKILL_ROW_COUNT) {
    return false;
  }
  u32 skill = GfDataDriverSkill::getSkillFromBdat(unknown5c, unknown60, unknown64, unknown68 != 0);
  if (skill == 0) {
    return false;
  }
  u8 *bdat;
  u32 textId;
  GfDataDriverSkill::getName(bdat, textId, skill);
  if (textId == 0) {
    return false;
  }
  setText(ui::UIStr(bdat, textId));
  return true;
}

bool GfMenuSkillAdapter::update_SkillCaption() {
  if (unknown60 >= SKILL_ROW_COUNT) {
    return false;
  }
  bool isHidden = unknown68 != 0;
  u32 skill = GfDataDriverSkill::getSkillFromBdat(unknown5c, unknown60, unknown64, isHidden);
  if (skill == 0) {
    return false;
  }
  u8 *bdat;
  u32 textId;
  GfDataDriverSkill::getEnhanceCaption(bdat, textId, skill);
  if (textId == 0) {
    return false;
  }
  ui::UIStr text(bdat, textId);
  text.unknown12 = GfDataDriverSkill::getEnhanceFromBdat(unknown5c, unknown60, unknown64, isHidden);
  setText(text);
  return true;
}

bool GfMenuSkillAdapter::update_SkillPoint() {
  if (unknown60 >= SKILL_ROW_COUNT) {
    return false;
  }
  bool isHidden = unknown68 != 0;
  if (GfDataDriverSkill::getSkillFromBdat(unknown5c, unknown60, unknown64, isHidden) == 0) {
    return false;
  }
  if (GfDataDriverSkill::getSkill(unknown5c, unknown60, unknown64, isHidden) != 0) {
    return false;
  }
  setNumber(GfDataDriverSkill::getSkillPointFromBdat(unknown5c, unknown60, unknown64, isHidden));
  return true;
}

bool GfMenuSkillAdapter::update_SkillReleaseFlagIcon() {
  if (unknown60 >= SKILL_ROW_COUNT) {
    return false;
  }
  bool isHidden = unknown68 != 0;
  if (GfDataDriverSkill::isSkillUnlock(unknown5c, unknown60, unknown64, isHidden)) {
    setNumber(GfDataDriverSkill::getSkillCategoryFromBdat(unknown5c, unknown60, unknown64, isHidden) + 6);
  } else {
    setNumber(23);
  }
  return true;
}

bool GfMenuSkillAdapter::update_SkillReleaseFlagColor() {
  if (unknown60 >= SKILL_ROW_COUNT) {
    return false;
  }
  bool isHidden = unknown68 != 0;
  const char *color = "gray";
  if (GfDataDriverSkill::isSkillUnlock(unknown5c, unknown60, unknown64, isHidden) && GfDataDriverSkill::getSkill(unknown5c, unknown60, unknown64, isHidden) != 0) {
    color = "white";
  }
  setColorMode(0);
  setColor(color);
  return true;
}

bool GfMenuSkillAdapter::update_SkillReleaseFlagColorIcon() {
  if (unknown60 >= SKILL_ROW_COUNT) {
    return false;
  }
  setNumber(GfDataDriverSkill::getSkillCategoryFromBdat(unknown5c, unknown60, unknown64, unknown68 != 0) + 18);
  return true;
}

bool GfMenuSkillAdapter::update_SkillLearnDisp() {
  if (unknown60 >= SKILL_ROW_COUNT) {
    return false;
  }
  bool isHidden = unknown68 != 0;
  if (!GfDataDriverSkill::isSkillUnlock(unknown5c, unknown60, unknown64, isHidden)) {
    return false;
  }
  if (GfDataDriverSkill::getSkill(unknown5c, unknown60, unknown64, isHidden) != 0) {
    setMulColor("white");
  } else {
    setMulColor("black");
  }
  return true;
}

bool GfMenuSkillAdapter::update_SkillLevelLockIcon() {
  setNumber(unknown64 == SKILL_LEVEL_FIRST || GfDataDriverSkill::isSkillLevelUnlock(unknown5c, unknown64, unknown68 != 0) ? 5 : 11);
  return true;
}

bool GfMenuSkillAdapter::update_SkillLearnNum() {
  setNumber(GfDataDriverSkill::getValidSkillNum(unknown5c, unknown68 != 0));
  return true;
}

bool GfMenuSkillAdapter::update_SkillLearnMax() {
  setNumber(SKILL_ROW_COUNT * SKILL_COLUMN_COUNT);
  return true;
}

bool GfMenuSkillAdapter::update_SkillLevelUnlockNum() {
  if (unknown60 == SKILL_ROW_COUNT) {
    u32 num = GfDataDriverSkill::getSkillLevelUnlockNum(unknown5c, unknown64, unknown68 != 0);
    if (num != 0) {
      setNumber(num);
      return true;
    }
  }
  return false;
}

GfMenuSkillAdapter *GfMenuSkillAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  u32 driver = converter->getDriverId();
  u16 line = converter->getKizunaLine();
  u16 level = converter->getKizunaLevel();
  u16 round = converter->getRound();
  GfMenuSkillAdapter *adapter = create(handle, type, driver, line, level, round, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

GfMenuSkillAdapter *GfMenuSkillAdapter::createFromReferenceDriver(u32 handle, u32 type, u32 driverIndex, u16 line, u16 level, u16 roundIndex, bool isUpdateAlways) {
  // __LINE__ must be 225 as in the original source: it is the line argument of operator new.
#line 225
  ReferenceDriverConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceDriverConverter(driverIndex, line, level, roundIndex);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

GfMenuSkillAdapter *GfMenuSkillAdapter::createFromReferenceDriverLineLevel(u32 handle, u32 type, u32 driverIndex, u16 lineIndex, u16 levelIndex, u16 roundIndex, bool isUpdateAlways) {
  // __LINE__ must be 233 as in the original source: it is the line argument of operator new.
#line 233
  ReferenceDriverLineLevelConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceDriverLineLevelConverter(driverIndex, lineIndex, levelIndex, roundIndex);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

void GfMenuSkillAdapter::update(const fw::UpdateInfo &info) {
  if (unknown50 != nullptr) {
    u32 newDriver = unknown50->getDriverId();
    if (unknown5c != newDriver) {
      unknown5c = newDriver;
      setChange();
    }
    u32 newLine = unknown50->getKizunaLine();
    if (unknown60 != newLine) {
      unknown60 = newLine;
      setChange();
    }
    u32 newLevel = unknown50->getKizunaLevel();
    if (unknown64 != newLevel) {
      unknown64 = newLevel;
      setChange();
    }
    u32 newRound = unknown50->getRound();
    if (unknown68 != newRound) {
      unknown68 = newRound;
      setChange();
    }
  }

  if (unknown30.isValid() && (unknown20 & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    setDisp(unknown30());
    unknown20 &= ~FLAG_CHANGED;
  }
}

} // namespace gf
