#include "gf/menu/adapter/gf_menu_achievement_adapter.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_achievement.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_blade_arts.h"
#include "gf/data/gf_data_blade_skill.h"
#include "gf/data/gf_data_field_skill.h"
#include "gf/data/gf_data_hana.h"
#include "gf/data/gf_data_quest.h"
#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/game/quest/gf_achiev_quest.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_reference.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

constexpr u32 KEY_LEVEL_FIRST = 1;
constexpr u32 KEY_ACHIEVEMENT_LINK_THREE = 6;
constexpr u32 KEY_ACHIEVEMENT_LINK_FIVE = 7;
constexpr u32 POUCH_MSG_HIDDEN = 1;
constexpr u32 POUCH_MSG_HANA = 3;

static GfMenuAchievementAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuAchievementAdapter::update_AchievementReleaseFlagIcon, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuAchievementAdapter::update_AchievementCategory, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 99}},
    {&GfMenuAchievementAdapter::update_AchievementTitle, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuAchievementAdapter::update_AchievementResult, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuAchievementAdapter::update_AchievementIcon, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuAchievementAdapter::update_AchievementVoiceCategory, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 99}},
    {&GfMenuAchievementAdapter::update_AchievementVoiceAfter, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 99}},
    {&GfMenuAchievementAdapter::update_AchievementDifficulty, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 1, 5}},
    {&GfMenuAchievementAdapter::update_AchievementQuest, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 99}},
    {&GfMenuAchievementAdapter::update_AchievementSetCategory, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 12}},
    {&GfMenuAchievementAdapter::update_AchievementSetAbilityLevel, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 1, 5}},
    {&GfMenuAchievementAdapter::update_AchievementTypeIcon, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuAchievementAdapter::update_AchievementCategoryIcon, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuAchievementAdapter::update_AchievementReleaseFlagColor, {GfMenuAdapter::PLUGIN_TYPE_COLOR, 0, 0}},
    {&GfMenuAchievementAdapter::update_AchievementReleaseFlagIcon, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuAchievementAdapter::update_AchievementSkillName, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuAchievementAdapter::update_LearnNum, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 99}},
    {&GfMenuAchievementAdapter::update_LearnMax, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 99}},
    {&GfMenuAchievementAdapter::update_QuestNum, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 9999999}},
    {&GfMenuAchievementAdapter::update_QuestMax, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 9999999}},
    {&GfMenuAchievementAdapter::update_IdeaText, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuAchievementAdapter::update_IdeaIcon, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuAchievementAdapter::update_QuestCaptionText, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuAchievementAdapter::update_QuestResultText, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuAchievementAdapter::update_KeyIcon, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuAchievementAdapter::update_NetabareOkDisp, {GfMenuAdapter::PLUGIN_TYPE_DISP, 0, 0}},
};

GfMenuAchievementAdapter::GfMenuAchievementAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways)
    : GfMenuAdapter(plugin, false, isUpdateAlways), converter(nullptr), isDispComplete(0), blade(0), line(0), level(0) {}

GfMenuAchievementAdapter::~GfMenuAchievementAdapter() {
  if (converter != nullptr) {
    delete converter;
    converter = nullptr;
  }
}

GfMenuAchievementAdapter *GfMenuAchievementAdapter::create(u32 handle, u32 type, u32 blade, u16 line, u16 level, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 190 as in the original source: it is the line argument of operator new.
#line 190
      GfMenuAchievementAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuAchievementAdapter(plugin, isUpdateAlways);
      adapter->updater.bind(adapter, info.update);
      adapter->blade = blade;
      adapter->line = line;
      adapter->level = level;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuAchievementAdapter::update_AchievementReleaseFlagIcon() {
  setNumber(GfKizunaringBlade::getReleaseAchievement(blade, line, level));
  return true;
}

bool GfMenuAchievementAdapter::update_AchievementCategory() {
  setNumber(GfKizunaringBlade::getAchievementCategory(blade, line, level));
  return true;
}

bool GfMenuAchievementAdapter::update_AchievementTitle() {
  if (line == ACHIEVEMENT_LINE_KEY && level == KEY_LEVEL_FIRST) {
    return false;
  }
  if (GfKizunaringBlade::getReleaseAchievement(blade, line, level) == 0) {
    return false;
  }
  u8 *bdat;
  u32 textId;
  if (!GfDataBlade::getTaskSkillMessage(bdat, textId, blade, line)) {
    return false;
  }
  setText(ui::UIStr(bdat, textId));
  return true;
}

bool GfMenuAchievementAdapter::update_AchievementResult() {
  if (GfKizunaringBlade::getReleaseAchievement(blade, line, level) == 0) {
    return false;
  }
  u8 *bdat;
  u32 textId;
  if (GfKizunaringBlade::getAchievementResultMsg(bdat, textId, blade, line, level)) {
    u16 enhance = GfKizunaringBlade::getAchievementResultEnhance(blade, line, level);
    ui::UIStr text(bdat, textId);
    text.option = enhance;
    setText(text);
  } else if (line == ACHIEVEMENT_LINE_KEY && level >= 2 && level <= 5) {
    u32 index = level;
    u32 linkNum = GfDataBlade::getLinkChNum(blade);
    if (linkNum == 3 && index == 3) {
      index = KEY_ACHIEVEMENT_LINK_THREE;
    }
    if (index == 5 && linkNum == 5) {
      index = KEY_ACHIEVEMENT_LINK_FIVE;
    }
    u32 nameId = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_MSG_KEY_ACHIEVE), "name", index).valueU16;
    setText(ui::UIStr(GfDataBdat::getFP(BDAT_FLD_QUEST_ACHIEVEMENT), nameId));
  } else if (line != ACHIEVEMENT_LINE_KEY && GfDataHana::isValid(blade)) {
    textId = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_MSG_POUCH), "name", POUCH_MSG_HANA).valueU16;
    bdat = GfDataBdat::getFP(BDAT_MENU_MS);
    setText(ui::UIStr(bdat, textId));
  } else {
    return false;
  }
  return true;
}

bool GfMenuAchievementAdapter::update_AchievementIcon() {
  setNumber(GfKizunaringBlade::getAchievementIcon(blade, line, level));
  return true;
}

bool GfMenuAchievementAdapter::update_AchievementVoiceCategory() {
  setNumber(GfKizunaringBlade::getAchievementVoiceCategory(blade, line, level));
  return true;
}

bool GfMenuAchievementAdapter::update_AchievementVoiceAfter() {
  GfKizunaringBlade::getAchievementAfterVoice(blade, line, level);
  return true;
}

bool GfMenuAchievementAdapter::update_AchievementDifficulty() {
  setNumber(GfKizunaringBlade::getAchievementDifficulty(blade, line, level));
  return true;
}

bool GfMenuAchievementAdapter::update_AchievementQuest() {
  setNumber(GfKizunaringBlade::getAchievementQuest(blade, line, level));
  return true;
}

bool GfMenuAchievementAdapter::update_AchievementSetCategory() {
  setNumber(GfKizunaringBlade::getAchievementSetCategory(blade, line));
  return true;
}

bool GfMenuAchievementAdapter::update_AchievementSetAbilityLevel() {
  setNumber(GfKizunaringBlade::getAchievementSetAbilityLevel(blade, line));
  return true;
}

bool GfMenuAchievementAdapter::update_AchievementTypeIcon() {
  u32 release = GfKizunaringBlade::getReleaseAchievement(blade, line, level);
  int icon;
  if (line == ACHIEVEMENT_LINE_KEY) {
    if (level == KEY_LEVEL_FIRST) {
      return false;
    }
    icon = (release == 4 || release == 5) ? 5 : 11;
  } else if (release == 1) {
    icon = 23;
  } else if (release == 0) {
    icon = 10;
  } else {
    ACHIEVEMENT_TYPE type;
    u32 index;
    icon = 10;
    if (GfDataAchievement::getAchievementType(type, index, line)) {
      switch (type) {
      case ACHIEVEMENT_TYPE_ARTS:
        icon = 12;
        break;
      case ACHIEVEMENT_TYPE_SKILL:
        icon = 13;
        break;
      case ACHIEVEMENT_TYPE_FIELD_SKILL:
        icon = 14;
        break;
      default:
        break;
      }
    }
  }
  setNumber(icon);
  return true;
}

bool GfMenuAchievementAdapter::update_AchievementCategoryIcon() {
  if (GfKizunaringBlade::getReleaseAchievement(blade, line, level) == 0) {
    return false;
  }
  ACHIEVEMENT_TYPE type;
  u32 index;
  if (GfDataAchievement::getAchievementType(type, index, line) && type == ACHIEVEMENT_TYPE_KEY && line == ACHIEVEMENT_LINE_KEY && level == KEY_LEVEL_FIRST) {
    return false;
  }
  int icon;
  switch (type) {
  case ACHIEVEMENT_TYPE_ARTS:
    icon = 0;
    break;
  case ACHIEVEMENT_TYPE_SKILL:
    icon = 3;
    break;
  case ACHIEVEMENT_TYPE_FIELD_SKILL:
    icon = 1;
    break;
  default:
    icon = 9;
    break;
  }
  setNumber(icon);
  return true;
}

bool GfMenuAchievementAdapter::update_AchievementReleaseFlagColor() {
  u32 release = GfKizunaringBlade::getReleaseAchievement(blade, line, level);
  if (release == 0 || release == 1) {
    return true;
  }
  if (release == 4 || release == 5) {
    setMulColor("white");
  } else {
    setMulColor("black");
  }
  return true;
}

bool GfMenuAchievementAdapter::update_AchievementSkillName() {
  ACHIEVEMENT_TYPE type;
  u32 index;
  if (!GfDataAchievement::getAchievementType(type, index, line)) {
    return false;
  }
  u32 skill = GfDataBlade::getSkillLineId(blade, line);
  if (skill == 0) {
    return false;
  }
  u8 *bdat;
  u32 textId;
  switch (type) {
  case ACHIEVEMENT_TYPE_ARTS:
    GfDataBladeArts::getName(bdat, textId, skill);
    break;
  case ACHIEVEMENT_TYPE_SKILL:
    GfDataBladeSkill::getName(bdat, textId, skill);
    break;
  case ACHIEVEMENT_TYPE_FIELD_SKILL:
    GfDataFieldSkill::getName(bdat, textId, skill);
    break;
  default:
    return false;
  }
  setText(ui::UIStr(bdat, textId));
  return true;
}

bool GfMenuAchievementAdapter::update_LearnNum() {
  setNumber(GfDataBlade::getKizunaringCompleteNum(blade));
  return true;
}

bool GfMenuAchievementAdapter::update_LearnMax() {
  setNumber(GfDataBlade::getKizunaringMax(blade));
  return true;
}

bool GfMenuAchievementAdapter::update_QuestNum() {
  SDataBladeAchievement *info = GfDataBlade::getAchievInfo(blade, line);
  u32 count;
  u32 limit;
  if (!GfQuestUtil::getDispCount(count, limit, info->unknown04[level - 1])) {
    return false;
  }
  setNumber(count);
  return true;
}

bool GfMenuAchievementAdapter::update_QuestMax() {
  SDataBladeAchievement *info = GfDataBlade::getAchievInfo(blade, line);
  u32 count;
  u32 limit;
  if (!GfQuestUtil::getDispCount(count, limit, info->unknown04[level - 1])) {
    return false;
  }
  setNumber(limit);
  return true;
}

bool GfMenuAchievementAdapter::update_IdeaText() {
  u32 category;
  u32 value;
  if (GfQuestUtil::getResultIdea(category, value, blade, line, level) && value != 0) {
    setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_IDEACOLLAR_MS), category + 1));
    return true;
  }
  return false;
}

bool GfMenuAchievementAdapter::update_IdeaIcon() {
  u32 category;
  u32 value;
  if (GfQuestUtil::getResultIdea(category, value, blade, line, level) && value != 0) {
    setNumber(category);
    return true;
  }
  return false;
}

bool GfMenuAchievementAdapter::update_QuestCaptionText() {
  u8 *bdat;
  u32 textId;
  if (!GfKizunaringBlade::isNetabareOK(blade, line, level)) {
    u32 nameId = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_MSG_POUCH), "name", POUCH_MSG_HIDDEN).valueU16;
    setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_MS), nameId));
    return true;
  }
  if (GfDataBlade::getTaskTitleMessage(bdat, textId, blade, line, level)) {
    ui::UIStr text(bdat, textId);
    if (text.size() != 0 && GfDataBlade::getTaskSkillMessage(bdat, textId, blade, line)) {
      ui::UIStr skillName(bdat, textId);
      GfMenuReference::setReferenceString(skillName, 0);
      text.option = 0;
      setText(text);
      return true;
    }
  }
  return false;
}

bool GfMenuAchievementAdapter::update_QuestResultText() {
  u8 *bdat;
  u32 textId;
  if (GfDataBlade::getTaskResultMessage(bdat, textId, blade, line, level)) {
    ui::UIStr text(bdat, textId);
    if (text.size() != 0 && GfDataBlade::getTaskSkillMessage(bdat, textId, blade, line)) {
      ui::UIStr skillName(bdat, textId);
      GfMenuReference::setReferenceString(skillName, 1);
      text.option = 1;
      setText(text);
      return true;
    }
  }
  return false;
}

bool GfMenuAchievementAdapter::update_KeyIcon() {
  u32 release = GfKizunaringBlade::getReleaseAchievement(blade, line, level);
  setNumber(level == KEY_LEVEL_FIRST || release == 4 || release == 5 ? 5 : 11);
  return true;
}

bool GfMenuAchievementAdapter::update_NetabareOkDisp() { return GfKizunaringBlade::isNetabareOK(blade, line, level); }

GfMenuAchievementAdapter *GfMenuAchievementAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  u32 blade = converter->getBladeId();
  u16 line = converter->getKizunaLine();
  u16 level = converter->getKizunaLevel();
  GfMenuAchievementAdapter *adapter = create(handle, type, blade, line, level, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->converter = converter;
  }
  return adapter;
}

GfMenuAchievementAdapter *GfMenuAchievementAdapter::createFromReferenceBlade(u32 handle, u32 type, u32 bladeIndex, u16 line, u16 level, bool isUpdateAlways) {
  // __LINE__ must be 221 as in the original source: it is the line argument of operator new.
#line 221
  ReferenceBladeConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceBladeConverter(bladeIndex, line, level);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

GfMenuAchievementAdapter *GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(u32 handle, u32 type, u32 bladeIndex, u16 lineIndex, u16 levelIndex, bool isUpdateAlways) {
  // __LINE__ must be 229 as in the original source: it is the line argument of operator new.
#line 229
  ReferenceBladeLineLevelConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceBladeLineLevelConverter(bladeIndex, lineIndex, levelIndex);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

void GfMenuAchievementAdapter::update(const fw::UpdateInfo &info) {
  if (converter != nullptr) {
    u32 newBlade = converter->getBladeId();
    if (blade != newBlade) {
      blade = newBlade;
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
  }

  if (updater.isValid() && (flags & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    setDisp(updater());
    flags &= ~FLAG_CHANGED;
  }
}

bool GfMenuAchievementAdapter::update_AchievementReleaseFlagDisp() {
  if (line == ACHIEVEMENT_LINE_KEY && level == KEY_LEVEL_FIRST) {
    return false;
  }
  u32 release = GfKizunaringBlade::getReleaseAchievement(blade, line, level);
  if (release == 0) {
    return false;
  }
  return (release == 4 || release == 5) != (isDispComplete == 0);
}

} // namespace gf
