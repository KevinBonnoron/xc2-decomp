#pragma once
#include "gf/gf_allocator.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_enemy/gmk_enemy.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_set.h"
#include "gmk/gmk_squad.h"
#include "types.h"

namespace gmk {

void GmkEnemyInsts::createSquad(u16 squadId, u32 memberNum, f32 scale) {
  disposeSquad();
  if (squadId != 0) {
    GmkSquad::CreateInfo info;
    info.unknown00 = unknown00.unknown00->unknown08.unknown00->getCreateInfo().unknown08->unknown10.unknown04;
    info.unknown04 = squadId - 1;
    info.unknown08 = memberNum;
    // __LINE__ must be 1279 as in the original file: it is the line argument of operator new.
#line 1279
    unknown150 = new (gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GmkSquad(&info);
    unknown150->addRef();
    unknown150->unknown2c = scale;
  }
}

} // namespace gmk
