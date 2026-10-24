#include "gf/menu/gf_menu_location.h"

#include <math.h>

#include <algorithm>

#include "fw/fw_transform.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/gf_obj_acc.h"
#include "mm_math/mm_vec3.h"

namespace gf {

constexpr u32 ORDER_DISTANCE_OTHER_MAP = 0xffffffff;

void GfMenuLocation::updateDataNum(u32 type) {
  LocatorGroup &group = unknown10[type];
  if (type >= LOCATOR_TYPE_COUNT) {
    return;
  }
  mm::Vec3 position;
  {
    GfObjAcc acc(GfGameManager::getPartyLeaderDriver());
    if (!acc.isValid()) {
      return;
    }
    position = acc.getWorldTransform().position;
  }
  group.unknown30.clear();
  u32 dataNum = 0;
  for (u32 i = 0; i < group.unknown00.size(); i++) {
    if (group.unknown00[i].locator == nullptr) {
      continue;
    }
    u32 posNum = group.unknown00[i].locator->getPosNum();
    if (posNum != 0) {
      for (u32 j = 0; j < posNum; j++) {
        mm::Vec3 delta = *group.unknown00[i].locator->getPos(j);
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

} // namespace gf
