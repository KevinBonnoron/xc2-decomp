#include "gf/data/gf_data_quest.h"

#include "bdat.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_game_flag.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

enum {
  FLAG_ORDER_TIMMING_FIRST = 0x619,
  FLAG_ORDER_TIMMING_END = 0x763,
};

enum {
  QUEST_NEXT_NONE = 30000,
  QUEST_NEXT_NONE_ALTERNATE = 30001,
};

void GfDataQuest::registAchievementBlade(u32 achievement, u16 blade) { m_achieve2blade[achievement] = blade; }

QuestID GfDataQuest::getListNextQuestA(QuestID quest) {
  if (quest.empty()) {
    return QuestID();
  }

  QuestID next = {0, 0};
  u16 nextId = QuestListAcc::get()->getListNextQuestA(quest);
  if (nextId != QUEST_NEXT_NONE && nextId != QUEST_NEXT_NONE_ALTERNATE) {
    next.unknown00 = nextId;
    next.unknown02 = quest.unknown02;
  }

  return next;
}

u32 GfDataQuest::getListPurposeID(QuestID quest) {
  if (quest.empty()) {
    return 0;
  }

  return QuestListAcc::get()->getListPurposeID(quest);
}

u32 GfDataQuest::getAchievementLine(u32 achievement) { return (achievement - 1) % ACHIEVEMENT_PER_BLADE / ACHIEVEMENT_LEVEL_COUNT; }

u32 GfDataQuest::getAchievementLevel(u32 achievement) { return (achievement - 1) % ACHIEVEMENT_PER_BLADE % ACHIEVEMENT_LEVEL_COUNT + 1; }

void GfDataQuest::setOrderTimming(QuestID quest) {
  if (getListQuestCategory(quest) >= 5 || QuestListAcc::get()->getListAutoStart(quest) != 0) {
    return;
  }

  for (u32 flag = FLAG_ORDER_TIMMING_FIRST; flag < FLAG_ORDER_TIMMING_END; flag++) {
    u32 orderQuest = GfGameFlag::getLocal(16, flag);
    if (orderQuest == quest.unknown00) {
      return;
    }

    if (orderQuest == 0) {
      GfGameFlag::setLocal(16, flag, quest.unknown00);
      return;
    }
  }
}

bool GfDataQuest::getOrderTimming(mm::mtl::FixedVector<QuestID, 330> &quests) {
  for (u32 flag = FLAG_ORDER_TIMMING_FIRST; flag < FLAG_ORDER_TIMMING_END; flag++) {
    u32 orderQuest = GfGameFlag::getLocal(16, flag);
    if (orderQuest == 0) {
      break;
    }

    QuestID quest = {static_cast<u16>(orderQuest), static_cast<u16>(orderQuest >> 16)};
    quests.push_back(quest);
  }

  return !quests.empty();
}

u16 GfDataQuest::getAchievementBlade(u32 achievement) { return m_achieve2blade[achievement]; }

u32 GfDataQuest::getListTalker(QuestID quest) {
  if (quest.empty()) {
    return 0;
  }

  return QuestListAcc::get()->getListTalker(quest);
}

u32 GfDataQuest::getListRewardSetA(QuestID quest) {
  if (quest.empty()) {
    return 0;
  }

  return QuestListAcc::get()->getListRewardSetA(quest);
}

u32 GfDataQuest::getListRewardSetB(QuestID quest) {
  if (quest.empty()) {
    return 0;
  }

  return QuestListAcc::get()->getListRewardSetB(quest);
}

bool GfDataQuest::getListRewardDisp(QuestID quest) {
  if (quest.empty()) {
    return false;
  }

  return QuestListAcc::get()->getListRewardDisp(quest) != 0;
}

u32 GfDataQuest::getListResultA(QuestID quest) {
  if (quest.empty()) {
    return 0;
  }

  return QuestListAcc::get()->getListResultA(quest);
}

u32 GfDataQuest::getListResultB(QuestID quest) {
  if (quest.empty()) {
    return 0;
  }

  return QuestListAcc::get()->getListResultB(quest);
}

u32 GfDataQuest::getListSummary(QuestID quest) {
  if (quest.empty()) {
    return 0;
  }

  return QuestListAcc::get()->getListSummary(quest);
}

bool GfDataQuest::getListVisible(QuestID quest) {
  if (quest.empty()) {
    return false;
  }

  return QuestListAcc::get()->getListVisible(quest) != 0;
}

u32 GfDataQuest::getListQuestCategory(QuestID quest) {
  if (quest.unknown00 == 0) {
    return 0;
  }

  if (quest.unknown00 < 1000) {
    return 1;
  }

  if (quest.unknown00 < 5000) {
    return 3;
  }

  if (quest.unknown00 < 6000) {
    return 2;
  }

  if (quest.unknown00 < 7000) {
    return 5;
  }

  return 6;
}

u32 GfDataQuest::getQuestCategory(QuestID quest) {
  if (quest.empty()) {
    return 0;
  }

  u32 category = QuestListAcc::get()->getListQuestCategory(quest);
  if (category != 0) {
    return category;
  }

  return getListQuestCategory(getListPRTQuestID(quest));
}

QuestID GfDataQuest::getListPRTQuestID(QuestID quest) {
  if (quest.empty()) {
    return QuestID();
  }

  QuestID parent;
  u32 parentQuest = QuestListAcc::get()->getListPRTQuestID(quest);
  parent.unknown00 = parentQuest;
  parent.unknown02 = quest.unknown02;
  if (parent.unknown02 == 0) {
    parent.unknown02 = parentQuest >> 16;
  }

  return parent;
}

u32 GfDataQuest::getListFlagPRT(QuestID quest) {
  if (quest.empty()) {
    return 0;
  }

  return QuestListAcc::get()->getListFlagPRT(quest);
}

u32 GfDataQuest::getListFlagCLD(QuestID quest) {
  if (quest.empty()) {
    return 0;
  }

  return QuestListAcc::get()->getListFlagCLD(quest);
}

QuestID GfDataQuest::getListNextQuestB(QuestID quest) {
  if (quest.empty()) {
    return QuestID();
  }

  QuestID next = {0, 0};
  u16 nextId = QuestListAcc::get()->getListNextQuestB(quest);
  if (nextId != QUEST_NEXT_NONE && nextId != QUEST_NEXT_NONE_ALTERNATE) {
    next.unknown00 = nextId;
    next.unknown02 = quest.unknown02;
  }

  return next;
}

u32 GfDataQuest::getListCallEventA(QuestID quest) {
  if (quest.empty()) {
    return 0;
  }

  return QuestListAcc::get()->getListCallEventA(quest);
}

u32 GfDataQuest::getListCallEventB(QuestID quest) {
  if (quest.empty()) {
    return 0;
  }

  return QuestListAcc::get()->getListCallEventB(quest);
}

u32 GfDataQuest::getListHintsID(QuestID quest) {
  if (quest.empty()) {
    return 0;
  }

  return QuestListAcc::get()->getListHintsID(quest);
}

bool GfDataQuest::getTitle(u8 *&bdat, u32 &textId, QuestID quest) {
  textId = QuestListAcc::get()->getListQuestTitle(quest);
  if (textId == 0) {
    return false;
  }

  bdat = GfBdatMsg::getFpQuest(quest);
  return true;
}

const char *GfDataQuest::getTitle(QuestID quest) {
  u8 *bdat;
  u32 textId;
  if (getTitle(bdat, textId, quest)) {
    const char *title = Bdat::getMSText(bdat, textId);
    if (title != nullptr) {
      return title;
    }
  }

  return "";
}

bool GfDataQuest::getSummary(u8 *&bdat, u32 &textId, QuestID quest) {
  textId = QuestListAcc::get()->getListSummary(quest);
  if (textId == 0) {
    return false;
  }

  bdat = GfBdatMsg::getFpQuest(quest);
  return true;
}

const char *GfDataQuest::getSummary(QuestID quest) {
  u8 *bdat;
  u32 textId;
  if (getSummary(bdat, textId, quest)) {
    const char *summary = Bdat::getMSText(bdat, textId);
    if (summary != nullptr) {
      return summary;
    }
  }

  return "";
}

bool GfDataQuest::getResult(u8 *&bdat, u32 &textId, QuestID quest) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  textId = questListAcc->getListResultA(quest);
  if (textId == 0) {
    textId = questListAcc->getListResultB(quest);
    if (textId == 0) {
      return false;
    }
  }

  bdat = GfBdatMsg::getFpQuest(quest);
  return true;
}

const char *GfDataQuest::getTaskLog(QuestID quest, u32 line) {
  const char *taskLog = GfBdatMsg::getNameQuest(quest, line);
  return taskLog != nullptr ? taskLog : "";
}

void GfDataQuest::setScenario(QuestID scenario) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->unknown1097e4.unknown00 = scenario.unknown00;
  dataGame->unknown1097e4.unknown02 = scenario.unknown02;
}

QuestID GfDataQuest::getScenario() { return GfDataManager::getDataGame()->unknown1097e4; }

void GfDataQuest::setSelect(QuestID select) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->unknown1097e8.unknown00 = select.unknown00;
  dataGame->unknown1097e8.unknown02 = select.unknown02;
}

QuestID GfDataQuest::getSelect() { return GfDataManager::getDataGame()->unknown1097e8; }

mm::mtl::FixedVector<unknown106, 128> &GfDataQuest::getTaskAchieve() { return GfDataManager::getDataGame()->unknown109b30; }

} // namespace gf
