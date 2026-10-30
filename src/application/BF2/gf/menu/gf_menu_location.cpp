#include "gf/menu/gf_menu_location.h"

#include <math.h>

#include <algorithm>

#include "fw/fw_transform.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/gf_obj_acc.h"
#include "mm_math/mm_vec3.h"

namespace gf {

constexpr u32 ORDER_DISTANCE_OTHER_MAP = 0xffffffff;

bool GfMenuLocation::isInitialized() {
  GfMenuLocation *location = get();
  if (location != nullptr) {
    return location->unknown08;
  }
  return false;
}

u32 GfMenuLocation::getLocatorDataNum(u32 type) {
  GfMenuLocation *location = get();
  if (type < LOCATOR_TYPE_COUNT && location != nullptr) {
    return location->unknown10[type].unknown28;
  }
  return 0;
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

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfMenuLocation>::~PtrSingleton();
template void mm::mtl::Vector<gf::GfFieldLocator>::expand(size_t, size_t);
template void mm::mtl::Vector<gf::GfFieldLocator>::push_back(const gf::GfFieldLocator &);
