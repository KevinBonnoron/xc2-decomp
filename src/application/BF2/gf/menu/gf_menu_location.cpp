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
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/object/gf_menu_obj_compass.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_acc.h"
#include "mm_math/mm_vec3.h"

namespace gf {

// Inferred role: distance of the locators of another map; original name unknown.
constexpr u32 ORDER_DISTANCE_UNKNOWN_4294967295 = 0xffffffff;
// Inferred role: icon of an unknown locator type; original name unknown.
constexpr u32 ICON_UNKNOWN_455 = 455;

// Inferred role: locator type to icon entry; original type name unknown.
struct unknown002 {
  u32 unknown00; // Inferred role: locator type; original member name unknown.
  u32 unknown04; // Inferred role: icon; original member name unknown.
};

// Inferred role: locator type to icon table; original table name unknown.
static const unknown002 unknown003[] = {{415, 455}, {416, 456}, {417, 457}};
// Inferred role: number of entries of the locator type to icon table; original name unknown.
constexpr u32 unknown004 = sizeof(unknown003) / sizeof(unknown003[0]);

// Inferred role: capacity of the locators of each locator type; original name unknown.
static const u32 unknown005[GfMenuLocation::LOCATOR_TYPE_UNKNOWN_4] = {4, 4, 1, 16};
// Inferred role: number of locators of each locator type shown on the compass; original name unknown.
static const u32 unknown006[GfMenuLocation::LOCATOR_TYPE_UNKNOWN_4] = {5, 5, 1, 2};
// Role unknown; the game passes 50 for the last locator type and 0 for the others; original name unknown.
constexpr int OFFSET_UNKNOWN_50 = 50;

bool GfMenuLocation::isInitialized() {
  GfMenuLocation *location = get();
  if (location != nullptr) {
    return location->unknown08;
  }
  return false;
}

GfMenuLocation::GfMenuLocation(const GfSetupParam &param) : unknown10(), unknown10f0(0) {}

void GfMenuLocation::build(const GfSetupParam &param) {
// __LINE__ must be 74 as in the original file: it is the line argument of operator new.
#line 74
  GfMenuLocation *location = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfMenuLocation(param);
  for (u32 type = 0; type < LOCATOR_TYPE_UNKNOWN_4; type++) {
    unknown001 &group = location->unknown10[type];
    group.unknown28 = 0;
    group.unknown00.setAllocator(getAllocator(ALLOCATOR_UNKNOWN_0));
    group.unknown00.reserve(unknown005[type]);
    group.unknown2c = 0;
  }
  location->unknown08 = true;
  location->unknown10f0 = 0;
}

void GfMenuLocation::destroy() {
  GfMenuLocation *location = get();
  for (u32 type = 0; type < LOCATOR_TYPE_UNKNOWN_4; type++) {
    if (location->unknown10[type].unknown00.capacity() != 0) {
      location->unknown10[type].unknown00.destroy();
    }
  }
  delete location;
}

void GfMenuLocation::updateLocator() {
  GfMenuLocation *location = get();
  if (location != nullptr) {
    for (u32 type = 0; type < LOCATOR_TYPE_UNKNOWN_4; type++) {
      unknown001 &group = location->unknown10[type];
      for (size_t i = 0; i < group.unknown00.size(); i++) {
        group.unknown00[i].update();
      }
      location->updateDataNum(type);
      if (group.unknown2c < group.unknown28) {
        int count = group.unknown28 - group.unknown2c;
        int i;
        for (i = 0; i < count && group.unknown2c + i + 1 <= unknown006[type]; i++) {
          GfMenuObjCompass::LocatorParam param;
          param.unknown00 = type;
          param.unknown02 = group.unknown2c + i;
          param.unknown04 = type == 3 ? OFFSET_UNKNOWN_50 : 0;
          GfMenuObjCompass::addLocator(param);
        }
        group.unknown2c += i;
      }
    }
  }
}

u32 GfMenuLocation::getLocatorDataNum(u32 type) {
  GfMenuLocation *location = get();
  if (type < LOCATOR_TYPE_UNKNOWN_4 && location != nullptr) {
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
        QuestTaskParam param(*quest, task, purpose, TASK_STATE_UNKNOWN_0);
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
  if (type >= LOCATOR_TYPE_UNKNOWN_4) {
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
      OrderInfo order = {dataNum, ORDER_DISTANCE_UNKNOWN_4294967295};
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
  for (u32 i = 0; i < unknown004; i++) {
    if (unknown003[i].unknown00 == type) {
      return unknown003[i].unknown04;
    }
  }
  return ICON_UNKNOWN_455;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfMenuLocation>::~PtrSingleton();
template void mm::mtl::Vector<gf::GfFieldLocator>::expand(size_t, size_t);
template void mm::mtl::Vector<gf::GfFieldLocator>::push_back(const gf::GfFieldLocator &);
