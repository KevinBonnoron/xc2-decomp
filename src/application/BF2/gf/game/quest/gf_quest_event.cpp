#include "gf/game/quest/gf_quest_event.h"

#include "gf/data/gf_data_quest.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_task.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/game/sequential_play/gf_play_factory.h"

namespace gf {

GfQuestEvent::GfQuestEvent() : isEntryOpen(false), isResultOpen(false) {}

GfQuestEvent::~GfQuestEvent() {}

bool GfQuestEvent::setQuestEntry(u32 quest) {
  bool isEntry = false;
  GfQuestEvent *event = get();
  if (quest != 1 && event != nullptr) {
    isEntry = true;
    if (GfQuestManager::openOrder(toQuestID(quest), true)) {
      event->isEntryOpen = GfDataQuest::getListVisible(toQuestID(quest));
    }
  }

  return isEntry;
}

u32 GfQuestEvent::getQuestState(u32 quest) { return GfQuestInfo::getState(toQuestID(quest)); }

void GfQuestEvent::setQuestComp(u32 quest, u32 taskIndex) {
  QuestTaskParam param(toQuestID(quest), taskIndex, TASK_STATE_NONE);
  GfQuestTask::completeTask(param);
}

bool GfQuestEvent::getQuestComp(u32 quest, u32 taskIndex) {
  QuestTaskParam param(toQuestID(quest), taskIndex, TASK_STATE_NONE);
  return GfQuestInfo::isCompleteTask(param);
}

bool GfQuestEvent::isActive() {
  GfQuestEvent *event = get();
  if (event == nullptr) {
    return false;
  }

  return event->isEntryOpen || event->isResultOpen;
}

void GfQuestEvent::openEntry(u32 quest) {
  GfQuestEvent *event = get();
  if (event != nullptr) {
    event->isEntryOpen = GfPlayFactory::createQuestUIOrder(toQuestID(quest), true, false);
  }
}

void GfQuestEvent::openResult(u32 quest) {
  GfQuestEvent *event = get();
  if (event != nullptr) {
    event->isResultOpen = GfPlayFactory::createQuestUIComplete(toQuestID(quest));
  }
}

void GfQuestEvent::clearDispUI() {
  GfQuestEvent *event = get();
  if (event != nullptr) {
    event->isEntryOpen = false;
    event->isResultOpen = false;
  }
}

} // namespace gf
