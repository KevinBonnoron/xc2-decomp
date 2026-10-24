#include "event/quest_manager.h"

#include "gf/game/quest/gf_quest_event.h"

namespace event {

QuestManager::QuestManager() : unknown10(0) {}

void QuestManager::clear() { unknown10 = 0; }

void QuestManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    clear();
    break;
  case MSG_TYPE_CLEAR:
    clear();
    break;
  default:
    break;
  }
}

u32 QuestManager::getState(u32 quest) { return gf::GfQuestEvent::getQuestState(quest); }

bool QuestManager::getComp(u32 quest, u32 taskIndex) { return gf::GfQuestEvent::getQuestComp(quest, taskIndex); }

bool QuestManager::isActive() const { return (unknown10 & FLAG_ACTIVE) != 0; }

} // namespace event
