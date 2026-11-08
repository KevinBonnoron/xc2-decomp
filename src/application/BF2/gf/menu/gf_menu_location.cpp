#include "gf/menu/gf_menu_location.h"

#include <math.h>

#include <algorithm>

#include "fw/fw_transform.h"
#include "gf/data/gf_data_quest.h"
#include "gf/field/gf_field_locator.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_task.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_acc.h"
#include "mm_math/mm_vec3.h"

namespace gf {

constexpr u32 ORDER_DISTANCE_OTHER_MAP = 0xffffffff;
constexpr u32 ICON_DEFAULT = 455;

// Inferred role: locator type to icon entry; original type name unknown.
struct unknown002 {
  u32 unknown00; // Inferred role: locator type; original member name unknown.
  u32 unknown04; // Inferred role: icon; original member name unknown.
};

// Inferred role: locator type to icon table; original table name unknown.
static const unknown002 ICON_TABLE[] = {{415, 455}, {416, 456}, {417, 457}};
constexpr u32 ICON_TABLE_COUNT = sizeof(ICON_TABLE) / sizeof(ICON_TABLE[0]);

bool GfMenuLocation::isInitialized() {
  GfMenuLocation *location = get();
  if (location != nullptr) {
    return location->unknown08;
  }
  return false;
}

GfMenuLocation::GfMenuLocation(const GfSetupParam &param) : unknown10(), unknown10f0(0) {}

u32 GfMenuLocation::getLocatorDataNum(u32 type) {
  GfMenuLocation *location = get();
  if (type < LOCATOR_TYPE_COUNT && location != nullptr) {
    return location->unknown10[type].unknown28;
  }
  return 0;
}

void GfMenuLocation::refreshLocatorFromQuest(u32 index, u32 type) {
  QuestID current = GfMenuObjUtil::getCurrentQuest(type);
  mm::mtl::FixedVector<QuestID, 16> linkQuests;
  GfQuestManager::getLinkQuest(linkQuests, current);
  mm::mtl::Vector<GfFieldLocator> &locators = unknown10[index].unknown00;
  QuestID *end = linkQuests.end();
  for (QuestID *quest = linkQuests.begin(); quest != end; ++quest) {
    if (!GfMenuObjUtil::isQuestCompleted(*quest)) {
      u32 purpose = GfDataQuest::getListPurposeID(*quest);
      for (u32 task = 0; task < 4; task++) {
        QuestTaskParam param(*quest, task, purpose, TASK_STATE_NONE);
        if (param.unknown10 == 0) {
          break;
        }
        if (!GfQuestInfo::isCompleteTask(param) && GfQuestTask::isEnableTaskCondition(param)) {
          GfFieldLocator::CreateInfoByQuest info;
          info.unknown00 = *quest;
          info.unknown08 = param.unknown14;
          info.unknown04 = param.unknown10;
          GfFieldLocator locator(&info);
          locators.push_back(locator);
        }
      }
    }
  }
}

void GfMenuLocation::updateDataNum(u32 type) {
  unknown001 &group = unknown10[type];
  if (type >= LOCATOR_TYPE_COUNT) {
    return;
  }
  mm::Vec3 position;
  {
    GfObjAcc acc(GfGameManager::getPartyLeaderDriver());
    if (!acc.isValid()) {
      return;
    }
    position = acc.getWorldTransform().unknown00;
  }
  group.unknown30.clear();
  u32 dataNum = 0;
  for (u32 i = 0; i < group.unknown00.size(); i++) {
    if (group.unknown00[i].unknown18 == nullptr) {
      continue;
    }
    u32 posNum = group.unknown00[i].unknown18->getPosNum();
    if (posNum != 0) {
      for (u32 j = 0; j < posNum; j++) {
        mm::Vec3 delta = *group.unknown00[i].unknown18->getPos(j);
        delta -= position;
        int distance = static_cast<int>(sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z)) - 1;
        if (distance < 0) {
          distance = 0;
        }
        OrderInfo order = {dataNum + j, static_cast<u32>(distance)};
        group.unknown30.push_back(order);
      }
    } else if (group.unknown00[i].isOtherMap()) {
      OrderInfo order = {dataNum, ORDER_DISTANCE_OTHER_MAP};
      group.unknown30.push_back(order);
      posNum = 1;
    }
    dataNum += posNum;
  }
  group.unknown28 = dataNum;
  std::sort(group.unknown30.begin(), group.unknown30.end(), CompareOrder());
}

void GfMenuLocation::postUpdate(const fw::UpdateInfo &) {
  if (get() != nullptr && !GfMenuFullScreen::isOpen() && !GfGameManager::isEvent(false)) {
    updateLocator();
  }
}

u32 GfMenuLocation::convIcon(u32 type) {
  for (u32 i = 0; i < ICON_TABLE_COUNT; i++) {
    if (ICON_TABLE[i].unknown00 == type) {
      return ICON_TABLE[i].unknown04;
    }
  }
  return ICON_DEFAULT;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfMenuLocation>::~PtrSingleton();
template void mm::mtl::Vector<gf::GfFieldLocator>::expand(size_t, size_t);
template void mm::mtl::Vector<gf::GfFieldLocator>::push_back(const gf::GfFieldLocator &);
