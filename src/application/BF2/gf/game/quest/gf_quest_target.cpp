// No game string names this file: named after its header and gf_quest_manager.cpp in the same directory (game string C:/Monolithsoft/BF2/prog/application/BF2/gf/game/quest/gf_quest_manager.cpp).
#include "gf/game/quest/gf_quest_target.h"

#include "gf/data/gf_data_quest.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "mm_mtl/algorithm.h"

namespace gf {

namespace {

// Inferred role: frames after which a target cache expires; original constant name unknown.
constexpr u16 TARGET_CACHE_LIFE_FRAMES = 300;

} // namespace

GfQuestTarget::GfQuestTarget() { GfQuestManager::addEvent(this); }

GfQuestTarget::~GfQuestTarget() { GfQuestManager::removeEvent(this); }

void GfQuestTarget::update(const fw::UpdateInfo &) {
  for (mm::mtl::FixedList<TargetCache, 512>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    TargetCache &cache = *it;
    if (!cache.unknown16 && ++cache.unknown14 > TARGET_CACHE_LIFE_FRAMES) {
      cache.unknown16 = true;
    }
  }
  for (mm::mtl::FixedList<TargetCache, 512>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    if (it->unknown16) {
      unknown10.erase(it);
      return;
    }
  }
}

void GfQuestTarget::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_MAPJUMP_CHANGE_MAP) {
    unknown10.clear();
  }
}

void GfQuestTarget::destroyTargetQuest(QuestID quest) {
  for (mm::mtl::FixedList<TargetCache, 512>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    TargetCache &cache = *it;
    if (cache.unknown10 == quest) {
      cache.unknown16 = true;
    }
  }
}

void GfQuestTarget::qevChangeTaskState(const QuestTaskParam &param) { destroyTargetQuest(param.unknown04); }

void GfQuestTarget::qevChangeQuestState(const QuestStateParam &param) { destroyTargetQuest(param.unknown04); }

void GfQuestTarget::qevOrderQuest(const QuestOrderParam &param) { destroyTargetQuest(GfDataQuest::getListNextQuestA(param.unknown04)); }

void GfQuestTarget::qevCompleteChildQuest(const QuestCompleteChildParam &param) { destroyTargetQuest(param.unknown04); }

void GfQuestTarget::qevChangeCurrentQuest(const QuestChangeParam &param) {
  destroyTargetQuest(param.unknown08);
  destroyTargetQuest(param.unknown04);
}

void GfQuestTarget::qevChangeTaskCondition(const QuestTaskParam &param) { destroyTargetQuest(param.unknown04); }

GfQuestTarget::TargetCache *GfQuestTarget::getTargetCache(GF_OBJ_HANDLE *handle) {
  ParamObj object = {handle, 0, 0};
  mm::mtl::FixedList<TargetCache, 512>::iterator it = mm::mtl::find_if(unknown10.begin(), unknown10.end(), [object](const TargetCache &cache) { return cache == object; });
  if (it == unknown10.end()) {
    return nullptr;
  }
  return &*it;
}

void GfQuestTarget::entryTargetCache(GF_OBJ_HANDLE *handle, QuestID quest) {
  if (unknown10.size() != 512) {
    unknown10.push_back(TargetCache(handle, quest));
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfQuestTarget>::~PtrSingleton();
