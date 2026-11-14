#include "event/quest_manager.h"

#include "event/frame_manager.h"
#include "event/skip_manager.h"
#include "gf/game/quest/gf_quest_event.h"
#include "mm_mtl/singleton.h"

namespace event {

QuestManager::QuestManager() : unknown10(0) {}

void QuestManager::clear() { unknown10 = 0; }

void QuestManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_4:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_12:
    clear();
    break;
  default:
    break;
  }
}

u32 QuestManager::getState(u32 quest) { return gf::GfQuestEvent::getQuestState(quest); }

bool QuestManager::entry(u32 quest, bool *isOrdered) {
  if ((unknown10 & FLAG_UNKNOWN_0) == 0) {
    gf::GfQuestEvent::setQuestEntry(quest);
    unknown10 |= FLAG_UNKNOWN_0;
  }
  if (!gf::GfQuestEvent::isActive()) {
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_3, false);
    unknown10 = 0;
    if (isOrdered != nullptr) {
      *isOrdered = getState(quest) != 0;
    }
    return true;
  }
  mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
  mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_3, true);
  return false;
}

bool QuestManager::setComp(u32 quest, u32 taskIndex, bool isComp) {
  if ((unknown10 & FLAG_UNKNOWN_0) == 0) {
    gf::GfQuestEvent::setQuestComp(quest, taskIndex);
    unknown10 |= FLAG_UNKNOWN_0;
  }
  if (gf::GfQuestEvent::isActive()) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_3, true);
    return false;
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_3, false);
  unknown10 = 0;
  return true;
}

bool QuestManager::disp(u32 quest, bool isResult) {
  if ((unknown10 & FLAG_UNKNOWN_0) == 0) {
    if (isResult) {
      gf::GfQuestEvent::openResult(quest);
    } else {
      gf::GfQuestEvent::openEntry(quest);
    }
    unknown10 |= FLAG_UNKNOWN_0;
  }
  if (gf::GfQuestEvent::isActive()) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_3, true);
    return false;
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_3, false);
  unknown10 = 0;
  return true;
}

bool QuestManager::getComp(u32 quest, u32 taskIndex) { return gf::GfQuestEvent::getQuestComp(quest, taskIndex); }

bool QuestManager::isActive() const { return (unknown10 & FLAG_UNKNOWN_0) != 0; }

} // namespace event
