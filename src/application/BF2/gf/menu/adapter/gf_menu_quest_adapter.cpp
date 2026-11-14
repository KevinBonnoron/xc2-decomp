#include "gf/menu/adapter/gf_menu_quest_adapter.h"

#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_quest.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/rtti.h"
#include "ui/plugin/ui_object_disp_plugin.h"
#include "ui/plugin/ui_object_number_plugin.h"
#include "ui/plugin/ui_object_text_plugin.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: update kind of each parameter; original name unknown.
static const GfMenuQuestAdapter::unknown001 unknown003[] = {
    GfMenuQuestAdapter::unknown001_0, GfMenuQuestAdapter::unknown001_0, GfMenuQuestAdapter::unknown001_0, GfMenuQuestAdapter::unknown001_2, GfMenuQuestAdapter::unknown001_2,
    GfMenuQuestAdapter::unknown001_2, GfMenuQuestAdapter::unknown001_2, GfMenuQuestAdapter::unknown001_2, GfMenuQuestAdapter::unknown001_2, GfMenuQuestAdapter::unknown001_2,
    GfMenuQuestAdapter::unknown001_2, GfMenuQuestAdapter::unknown001_2, GfMenuQuestAdapter::unknown001_2, GfMenuQuestAdapter::unknown001_2, GfMenuQuestAdapter::unknown001_2,
    GfMenuQuestAdapter::unknown001_0, GfMenuQuestAdapter::unknown001_0, GfMenuQuestAdapter::unknown001_0, GfMenuQuestAdapter::unknown001_3, GfMenuQuestAdapter::unknown001_3,
    GfMenuQuestAdapter::unknown001_3, GfMenuQuestAdapter::unknown001_3, GfMenuQuestAdapter::unknown001_1, GfMenuQuestAdapter::unknown001_1, GfMenuQuestAdapter::unknown001_1,
    GfMenuQuestAdapter::unknown001_1, GfMenuQuestAdapter::unknown001_1, GfMenuQuestAdapter::unknown001_1, GfMenuQuestAdapter::unknown001_1, GfMenuQuestAdapter::unknown001_1,
    GfMenuQuestAdapter::unknown001_4, GfMenuQuestAdapter::unknown001_4, GfMenuQuestAdapter::unknown001_4, GfMenuQuestAdapter::unknown001_4, GfMenuQuestAdapter::unknown001_4,
    GfMenuQuestAdapter::unknown001_4, GfMenuQuestAdapter::unknown001_4, GfMenuQuestAdapter::unknown001_4, GfMenuQuestAdapter::unknown001_1, GfMenuQuestAdapter::unknown001_1,
    GfMenuQuestAdapter::unknown001_1, GfMenuQuestAdapter::unknown001_1, GfMenuQuestAdapter::unknown001_1, GfMenuQuestAdapter::unknown001_1, GfMenuQuestAdapter::unknown001_1,
    GfMenuQuestAdapter::unknown001_1, GfMenuQuestAdapter::unknown001_0, GfMenuQuestAdapter::unknown001_1, GfMenuQuestAdapter::unknown001_1, GfMenuQuestAdapter::unknown001_1,
    GfMenuQuestAdapter::unknown001_1, GfMenuQuestAdapter::unknown001_1, GfMenuQuestAdapter::unknown001_1, GfMenuQuestAdapter::unknown001_5, GfMenuQuestAdapter::unknown001_5,
    GfMenuQuestAdapter::unknown001_5, GfMenuQuestAdapter::unknown001_5, GfMenuQuestAdapter::unknown001_2, GfMenuQuestAdapter::unknown001_1,
};

// Inferred role: index into GfQuestReward of each reward number parameter; original name unknown.
static const QUEST_REWARD unknown006[] = {QUEST_REWARD_UNKNOWN_0, QUEST_REWARD_UNKNOWN_3, QUEST_REWARD_UNKNOWN_2, QUEST_REWARD_UNKNOWN_1, QUEST_REWARD_UNKNOWN_7};

// Inferred role: maximum of each reward number parameter; original name unknown.
static const u32 unknown007[] = {999999999, 999999999, 99999, 9999, 99999};

GfMenuQuestAdapter::GfMenuQuestAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways)
    : GfMenuAdapter(plugin, false, isUpdateAlways), unknown30(), unknown34(0), unknown38(0), unknown3c(false), unknown88(nullptr), unknown90(nullptr) {}

GfMenuQuestAdapter::~GfMenuQuestAdapter() {
  if (unknown88 != nullptr) {
    delete unknown88;
    unknown88 = nullptr;
  }
  unknown90 = nullptr;
}

GfMenuQuestAdapter *GfMenuQuestAdapter::create(u32 handle, QuestID quest, u32 type, bool isUpdateAlways) {
  switch (unknown003[type]) {
  case unknown001_0: {
    ui::UIObjectPlugin *plugin = ui::UIObjectTextPlugin::create(handle);
    if (plugin == nullptr) {
      return nullptr;
    }
    // __LINE__ must be 217 as in the original source: it is the line argument of operator new.
#line 217
    GfMenuQuestAdapter *adapter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuQuestAdapter(plugin, isUpdateAlways);
    init(adapter, quest, type, unknown001_0);
    plugin->release();
    return adapter;
  }
  case unknown001_1: {
    ui::UIObjectPlugin *plugin = ui::UIObjectNumberPlugin::create(handle);
    if (plugin == nullptr) {
      return nullptr;
    }
    // __LINE__ must be 230 as in the original source: it is the line argument of operator new.
#line 230
    GfMenuQuestAdapter *adapter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuQuestAdapter(plugin, isUpdateAlways);
    init(adapter, quest, type, unknown001_1);
    plugin->release();
    return adapter;
  }
  case unknown001_2: {
    ui::UIObjectPlugin *plugin = ui::UIObjectNumberPlugin::create(handle);
    if (plugin == nullptr) {
      return nullptr;
    }
    // __LINE__ must be 243 as in the original source: it is the line argument of operator new.
#line 243
    GfMenuQuestAdapter *adapter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuQuestAdapter(plugin, isUpdateAlways);
    init(adapter, quest, type, unknown001_2);
    plugin->release();
    return adapter;
  }
  case unknown001_3: {
    ui::UIObjectPlugin *plugin = ui::UIObjectTextPlugin::create(handle);
    if (plugin == nullptr) {
      return nullptr;
    }
    // __LINE__ must be 256 as in the original source: it is the line argument of operator new.
#line 256
    GfMenuQuestAdapter *adapter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuQuestAdapter(plugin, isUpdateAlways);
    init(adapter, quest, type, unknown001_3);
    plugin->release();
    return adapter;
  }
  case unknown001_4: {
    ui::UIObjectPlugin *plugin = ui::UIObjectTextPlugin::create(handle);
    if (plugin == nullptr) {
      return nullptr;
    }
    // __LINE__ must be 271 as in the original source: it is the line argument of operator new.
#line 271
    GfMenuQuestAdapter *adapter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuQuestAdapter(plugin, isUpdateAlways);
    init(adapter, quest, type, unknown001_4);
    plugin->release();
    return adapter;
  }
  case unknown001_5: {
    ui::UIObjectPlugin *plugin = ui::UIObjectDispPlugin::create(handle);
    if (plugin == nullptr) {
      return nullptr;
    }
    // __LINE__ must be 284 as in the original source: it is the line argument of operator new.
#line 284
    GfMenuQuestAdapter *adapter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuQuestAdapter(plugin, isUpdateAlways);
    init(adapter, quest, type, unknown001_5);
    plugin->release();
    return adapter;
  }
  default:
    return nullptr;
  }
}

void GfMenuQuestAdapter::init(GfMenuQuestAdapter *adapter, QuestID quest, u32 type, u32 kind) {
  if (adapter != nullptr) {
    adapter->unknown30 = quest;
    adapter->unknown34 = type;
    adapter->unknown38 = kind;
    adapter->unknown3c = true;
  }
}

GfMenuQuestAdapter *GfMenuQuestAdapter::createFromReference(u32 handle, mm::mtl::IntrusivePtr<GfMenuReferenceQuest> reference, u32 type, bool isUpdateAlways) {
  // __LINE__ must be 299 as in the original source: it is the line argument of operator new.
#line 299
  ReferenceConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceConverter(reference);
  QuestID quest = {};
  converter->getQuestID(quest);
  GfMenuQuestAdapter *adapter = create(handle, quest, type, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown88 = converter;
  }
  return adapter;
}

GfMenuQuestAdapter *GfMenuQuestAdapter::createFromList(u32 handle, GfMenuQuestList *list, int listIndex, u32 type, bool isUpdateAlways) {
  // __LINE__ must be 317 as in the original source: it is the line argument of operator new.
#line 317
  ListConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListConverter(list, listIndex);
  QuestID quest = {};
  converter->getQuestID(quest);
  GfMenuQuestAdapter *adapter = create(handle, quest, type, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown88 = converter;
  }
  return adapter;
}

void GfMenuQuestAdapter::update(const fw::UpdateInfo &info) {
  if (unknown88 != nullptr) {
    QuestID quest = {};
    unknown88->getQuestID(quest);
    if (!(unknown30 == quest)) {
      unknown30 = quest;
      setChange();
    }
  }

  if (unknown90.get() != nullptr) {
    int number = unknown90->unknown0c;
    if (unknown98 != number) {
      unknown98 = number;
      setChange();
    }
  }

  if ((unknown20 & (FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1)) != 0) {
    if (unknown30.unknown00 != 0) {
      setDisp(true);
    } else {
      setDisp(false);
    }
    bool isDisp;
    switch (unknown38) {
    case unknown001_0: {
      const char *text;
      isDisp = getParamText(unknown30, unknown34, &text);
      if (isDisp) {
        setText(ui::UIStr(text, false));
      }
      break;
    }
    case unknown001_1: {
      u32 number;
      u32 max;
      isDisp = getParamNumber(unknown30, unknown34, number, max);
      if (isDisp) {
        ui::UIObjectNumberPlugin *plugin = unknown18 != nullptr ? mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(unknown18) : nullptr;
        if (plugin != nullptr) {
          plugin->setMax(max);
          plugin->setNumber(number);
        }
      }
      break;
    }
    case unknown001_2: {
      u32 icon;
      isDisp = getParamIcon(unknown30, unknown34, icon);
      if (isDisp) {
        ui::UIObjectNumberPlugin *plugin = unknown18 != nullptr ? mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(unknown18) : nullptr;
        if (plugin != nullptr) {
          plugin->setNumber(icon);
        }
      }
      break;
    }
    case unknown001_3: {
      const char *text;
      const char *color;
      isDisp = getParamTextColor(unknown30, unknown34, &text, &color);
      if (isDisp) {
        ui::UIObjectTextPlugin *plugin = unknown18 != nullptr ? mm::mtl::dynamicCast<ui::UIObjectTextPlugin>(unknown18) : nullptr;
        if (plugin != nullptr) {
          plugin->setText(ui::UIStr(text, false));
        }
      }
      break;
    }
    case unknown001_4: {
      isDisp = getParamRewardText(unknown30, unknown34, unknown40);
      if (isDisp) {
        ui::UIObjectTextPlugin *plugin = unknown18 != nullptr ? mm::mtl::dynamicCast<ui::UIObjectTextPlugin>(unknown18) : nullptr;
        if (plugin != nullptr) {
          plugin->setText(ui::UIStr(unknown40.c_str(), false));
        }
      }
      break;
    }
    case unknown001_5:
      isDisp = getParamDisp(unknown30, unknown34);
      break;
    default:
      isDisp = false;
      break;
    }
    setDisp(isDisp);
    unknown3c = false;
  }
  unknown20 &= ~FLAG_UNKNOWN_0;
}

bool GfMenuQuestAdapter::getParamText(QuestID quest, u32 type, const char **text) {
  if (quest.empty()) {
    return false;
  }
  switch (type) {
  case unknown002_0: {
    u32 line = GfQuestUtil::getMsgQuestTitle(quest);
    return getQuestText(quest, line, text);
  }
  case unknown002_1: {
    u32 line = GfQuestUtil::getMsgQuestSummary(quest);
    return getQuestText(quest, line, text);
  }
  case unknown002_2: {
    u32 line = GfQuestUtil::getMsgQuestResult(quest);
    return getQuestText(quest, line, text);
  }
  case unknown002_15:
  case unknown002_16: {
    u32 line = GfQuestUtil::getMsgQuestNeedFieldSkill(type - unknown002_15, quest);
    return getQuestText(quest, line, text);
  }
  case unknown002_17: {
    const char *menuText = GfMenuObjUtil::getMenuMS(GfQuestInfo::getQuestNeedTaskCond(quest) ? 0x88 : 0x89);
    *text = menuText;
    return menuText != nullptr;
  }
  case unknown002_46: {
    GfQuestTaskLogResult result;
    QuestTaskParam param(quest, unknown98, TASK_STATE_UNKNOWN_0);
    if (!GfQuestUtil::getMsgQuestTaskLog(result, param)) {
      return false;
    }
    return getQuestText(quest, result.unknown00, text);
  }
  default:
    return false;
  }
}

bool GfMenuQuestAdapter::getParamNumber(QuestID quest, u32 type, u32 &number, u32 &max) {
  if (quest.empty()) {
    return false;
  }
  switch (type) {
  case unknown002_22:
  case unknown002_22 + 1:
  case unknown002_22 + 2:
  case unknown002_22 + 3: {
    GfQuestTaskLogResult result;
    QuestTaskParam param(quest, type - unknown002_22, TASK_STATE_UNKNOWN_0);
    GfQuestUtil::getMsgQuestTaskLog(result, param);
    number = result.unknown18;
    max = 999;
    return true;
  }
  case unknown002_26:
  case unknown002_26 + 1:
  case unknown002_26 + 2:
  case unknown002_26 + 3: {
    GfQuestTaskLogResult result;
    QuestTaskParam param(quest, type - unknown002_26, TASK_STATE_UNKNOWN_0);
    GfQuestUtil::getMsgQuestTaskLog(result, param);
    number = result.unknown14;
    max = 999;
    return number != 0;
  }
  case unknown002_38:
  case unknown002_38 + 1:
  case unknown002_38 + 2:
  case unknown002_38 + 3:
  case unknown002_38 + 4:
  case unknown002_38 + 5:
  case unknown002_38 + 6:
  case unknown002_38 + 7: {
    GfQuestReward reward;
    if (!GfQuestManager::getRewardItem(reward, quest, true)) {
      return false;
    }
    int index = type - unknown002_38;
    if (index < 0) {
      return false;
    }
    if (index >= sizeof(unknown006) / sizeof(unknown006[0])) {
      return false;
    }
    u32 value;
    switch (unknown006[index]) {
    case QUEST_REWARD_UNKNOWN_0:
      value = reward.unknown00[0].unknown44_u32;
      break;
    case QUEST_REWARD_UNKNOWN_1:
      value = reward.unknown00[1].unknown44_u32;
      break;
    case QUEST_REWARD_UNKNOWN_2:
      value = reward.unknown00[2].unknown44_u32;
      break;
    case QUEST_REWARD_UNKNOWN_3:
      value = reward.unknown00[3].unknown44_u32;
      break;
    case QUEST_REWARD_UNKNOWN_4:
      value = reward.unknown00[4].unknown44;
      break;
    case QUEST_REWARD_UNKNOWN_5:
      value = reward.unknown00[5].unknown44;
      break;
    case QUEST_REWARD_UNKNOWN_6:
      value = reward.unknown00[6].unknown44;
      break;
    case QUEST_REWARD_UNKNOWN_7:
      value = reward.unknown00[7].unknown44;
      break;
    case QUEST_REWARD_UNKNOWN_8:
    case QUEST_REWARD_UNKNOWN_9:
    case QUEST_REWARD_UNKNOWN_10:
    case QUEST_REWARD_UNKNOWN_11:
      value = reward.unknown00[unknown006[index]].m_developZone;
      break;
    default:
      value = 0;
      break;
    }
    number = value;
    max = unknown007[index];
    return true;
  }
  case unknown002_47: {
    GfQuestTaskLogResult result;
    QuestTaskParam param(quest, unknown98, TASK_STATE_UNKNOWN_0);
    GfQuestUtil::getMsgQuestTaskLog(result, param);
    number = result.unknown18;
    max = 999;
    return true;
  }
  case unknown002_48: {
    GfQuestTaskLogResult result;
    QuestTaskParam param(quest, unknown98, TASK_STATE_UNKNOWN_0);
    GfQuestUtil::getMsgQuestTaskLog(result, param);
    number = result.unknown14;
    max = 999;
    return true;
  }
  case unknown002_49: {
    QuestTaskParam param(GfQuestInfo::getProgressQuest(quest), unknown98, TASK_STATE_UNKNOWN_0);
    s32 weather = GfQuestInfo::getQuestTaskWeatherInfo(param);
    if (weather == -1) {
      return false;
    }
    number = weather;
    return true;
  }
  case unknown002_50: {
    QuestTaskParam param(GfQuestInfo::getProgressQuest(quest), unknown98, TASK_STATE_UNKNOWN_0);
    s32 time = GfQuestInfo::getQuestTaskTimeInfo(param);
    if (time == -1) {
      return false;
    }
    number = getTimeZoneIconNumber(time, 0);
    return true;
  }
  case unknown002_51: {
    QuestTaskParam param(GfQuestInfo::getProgressQuest(quest), unknown98, TASK_STATE_UNKNOWN_0);
    s32 time = GfQuestInfo::getQuestTaskTimeInfo(param);
    if (time == 6) {
      number = 1;
    } else if (time == 7) {
      number = 4;
    } else {
      return false;
    }
    return true;
  }
  case unknown002_52: {
    QuestTaskParam param(GfQuestInfo::getProgressQuest(quest), unknown98, TASK_STATE_UNKNOWN_0);
    s32 time = GfQuestInfo::getQuestTaskTimeInfo(param);
    if (time == 6) {
      number = 2;
    } else if (time == 7) {
      number = 5;
    } else {
      return false;
    }
    return true;
  }
  case unknown002_58: {
    if (GfQuestInfo::isQuestFin(quest)) {
      return false;
    }
    QuestID parent = GfQuestInfo::getParentQuest(quest);
    if (!parent.empty()) {
      quest = parent;
    }
    number = GfQuestUtil::getClearChildQuest(parent) + 1;
    max = 99;
    return true;
  }
  default:
    return false;
  }
}

bool GfMenuQuestAdapter::getParamIcon(QuestID quest, u32 type, u32 &icon) {
  if (quest.empty()) {
    return false;
  }
  switch (type) {
  case unknown002_3:
  case unknown002_3 + 1:
  case unknown002_3 + 2:
  case unknown002_3 + 3:
  case unknown002_3 + 4:
  case unknown002_3 + 5:
  case unknown002_3 + 6:
  case unknown002_3 + 7:
  case unknown002_3 + 8:
  case unknown002_3 + 9:
  case unknown002_3 + 10:
  case unknown002_3 + 11: {
    u64 index = type - unknown002_3;
    mm::mtl::FixedVector<u16, 32> characters;
    GfQuestUtil::getNeedCharacterByQuestTask(characters, quest, unknown98);
    if (index >= characters.size() || characters[index] == 0) {
      return false;
    }

    u32 objectType = GfDataUtil::getObjTypeByCharaId(characters[index]);
    if (objectType - OBJECT_TYPE_PC >= 2) {
      return false;
    }

    DataParamAcc acc(objectType, characters[index], GIMMICK_TYPE_UNKNOWN_0);
    if (!acc.isValid()) {
      return false;
    }

    u32 iconData = acc.getIconData();
    if (iconData == 0) {
      return false;
    }

    icon = GfMenuBdat::getIconImageIndex(iconData);
    return true;
  }
  case unknown002_57: {
    u32 questIcon = QuestListAcc::get()->getListQuestIcon(quest);
    if (questIcon != 0) {
      icon = questIcon;
    }
    return true;
  }
  default:
    return false;
  }
}

bool GfMenuQuestAdapter::getParamTextColor(QuestID quest, u32 type, const char **text, const char **color) {
  u32 isEmpty = quest.empty();
  if (type - unknown002_18 < 4 && isEmpty == 0) {
    GfQuestTaskLogResult taskLog;
    QuestTaskParam param(quest, type - unknown002_18, TASK_STATE_UNKNOWN_0);
    GfQuestUtil::getMsgQuestTaskLog(taskLog, param);
    *color = taskLog.unknown24 ? "cyan" : nullptr;
    return getQuestText(quest, taskLog.unknown00, text);
  }
  return false;
}

bool GfMenuQuestAdapter::getParamRewardText(QuestID quest, u32 type, mm::mtl::FixStr<64> &text) {
  u32 isEmpty = quest.empty();
  bool result = false;
  if (type - unknown002_30 < 8 && isEmpty == 0) {
    GfQuestReward reward;
    if (GfQuestManager::getRewardItem(reward, quest, true)) {
      text = reward.unknown00[type - unknown002_30].unknown00;
      result = text.c_str()[0] != '\0';
    }
  }
  return result;
}

bool GfMenuQuestAdapter::getQuestText(QuestID quest, u32 line, const char **text) {
  const char *log;
  if (line == 0 || (log = GfDataQuest::getTaskLog(quest, line)) == nullptr) {
    log = "<error> no text";
  }
  *text = log;
  return true;
}

bool GfMenuQuestAdapter::getFaceIcon(u32 icon, u32 &image) {
  if (icon != 0) {
    image = GfMenuBdat::getIconImageIndex(icon);
    return true;
  }
  return false;
}

u32 GfMenuQuestAdapter::getTimeZoneIconNumber(int time, u32 zone) {
  if (time == 6) {
    if (zone < 3) {
      return zone;
    }
    return 6;
  }
  if (time == 7) {
    if (zone < 3) {
      time = zone + 3;
    } else {
      time = 7;
    }
  } else if (zone != 0) {
    return -1;
  }
  return time;
}

void GfMenuQuestAdapter::ListConverter::getQuestID(QuestID &quest) {
  if (list != nullptr) {
    if (listIndex == -1) {
      quest = list->getContents(list->getIndex(false));
    } else if (listIndex < static_cast<int>(list->getPageSize())) {
      quest = list->getContents(list->getPageIndex(listIndex));
    }
  }
}

void GfMenuQuestAdapter::ReferenceConverter::getQuestID(QuestID &quest) { reference->getQuest(quest); }

} // namespace gf
