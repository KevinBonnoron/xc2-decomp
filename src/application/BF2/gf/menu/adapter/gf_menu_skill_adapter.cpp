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
    : GfMenuAdapter(plugin, false, isUpdateAlways), converter(nullptr), _58(), driver(0), line(0), level(0), round(0) {}

GfMenuSkillAdapter::~GfMenuSkillAdapter() {
  if (converter != nullptr) {
    delete converter;
    converter = nullptr;
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
      adapter->updater.bind(adapter, info.update);
      adapter->driver = driver;
      adapter->line = line;
      adapter->level = level;
      adapter->round = round;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuSkillAdapter::update_SkillName() {
  if (line >= SKILL_ROW_COUNT) {
    return false;
  }
  u32 skill = GfDataDriverSkill::getSkillFromBdat(driver, line, level, round != 0);
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
  if (line >= SKILL_ROW_COUNT) {
    return false;
  }
  bool isHidden = round != 0;
  u32 skill = GfDataDriverSkill::getSkillFromBdat(driver, line, level, isHidden);
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
  text.option = GfDataDriverSkill::getEnhanceFromBdat(driver, line, level, isHidden);
  setText(text);
  return true;
}

bool GfMenuSkillAdapter::update_SkillPoint() {
  if (line >= SKILL_ROW_COUNT) {
    return false;
  }
  bool isHidden = round != 0;
  if (GfDataDriverSkill::getSkillFromBdat(driver, line, level, isHidden) == 0) {
    return false;
  }
  if (GfDataDriverSkill::getSkill(driver, line, level, isHidden) != 0) {
    return false;
  }
  setNumber(GfDataDriverSkill::getSkillPointFromBdat(driver, line, level, isHidden));
  return true;
}

bool GfMenuSkillAdapter::update_SkillReleaseFlagIcon() {
  if (line >= SKILL_ROW_COUNT) {
    return false;
  }
  bool isHidden = round != 0;
  if (GfDataDriverSkill::isSkillUnlock(driver, line, level, isHidden)) {
    setNumber(GfDataDriverSkill::getSkillCategoryFromBdat(driver, line, level, isHidden) + 6);
  } else {
    setNumber(23);
  }
  return true;
}

bool GfMenuSkillAdapter::update_SkillReleaseFlagColor() {
  if (line >= SKILL_ROW_COUNT) {
    return false;
  }
  bool isHidden = round != 0;
  const char *color = "gray";
  if (GfDataDriverSkill::isSkillUnlock(driver, line, level, isHidden) && GfDataDriverSkill::getSkill(driver, line, level, isHidden) != 0) {
    color = "white";
  }
  setColorMode(0);
  setColor(color);
  return true;
}

bool GfMenuSkillAdapter::update_SkillReleaseFlagColorIcon() {
  if (line >= SKILL_ROW_COUNT) {
    return false;
  }
  setNumber(GfDataDriverSkill::getSkillCategoryFromBdat(driver, line, level, round != 0) + 18);
  return true;
}

bool GfMenuSkillAdapter::update_SkillLearnDisp() {
  if (line >= SKILL_ROW_COUNT) {
    return false;
  }
  bool isHidden = round != 0;
  if (!GfDataDriverSkill::isSkillUnlock(driver, line, level, isHidden)) {
    return false;
  }
  if (GfDataDriverSkill::getSkill(driver, line, level, isHidden) != 0) {
    setMulColor("white");
  } else {
    setMulColor("black");
  }
  return true;
}

bool GfMenuSkillAdapter::update_SkillLevelLockIcon() {
  setNumber(level == SKILL_LEVEL_FIRST || GfDataDriverSkill::isSkillLevelUnlock(driver, level, round != 0) ? 5 : 11);
  return true;
}

bool GfMenuSkillAdapter::update_SkillLearnNum() {
  setNumber(GfDataDriverSkill::getValidSkillNum(driver, round != 0));
  return true;
}

bool GfMenuSkillAdapter::update_SkillLearnMax() {
  setNumber(SKILL_ROW_COUNT * SKILL_COLUMN_COUNT);
  return true;
}

bool GfMenuSkillAdapter::update_SkillLevelUnlockNum() {
  if (line == SKILL_ROW_COUNT) {
    u32 num = GfDataDriverSkill::getSkillLevelUnlockNum(driver, level, round != 0);
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
    adapter->converter = converter;
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
  if (converter != nullptr) {
    u32 newDriver = converter->getDriverId();
    if (driver != newDriver) {
      driver = newDriver;
      setChange();
    }
    u32 newLine = converter->getKizunaLine();
    if (line != newLine) {
      line = newLine;
      setChange();
    }
    u32 newLevel = converter->getKizunaLevel();
    if (level != newLevel) {
      level = newLevel;
      setChange();
    }
    u32 newRound = converter->getRound();
    if (round != newRound) {
      round = newRound;
      setChange();
    }
  }

  if (updater.isValid() && (flags & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    setDisp(updater());
    flags &= ~FLAG_CHANGED;
  }
}

} // namespace gf
