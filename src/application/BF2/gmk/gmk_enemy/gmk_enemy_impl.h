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
    info.unknown00 = m_createInfo.m_aGmkBase->m_createBaseInfo.m_ownerGmkEnemyList->getCreateInfo().m_gmkSet->m_createInfo.unknown04;
    info.unknown04 = squadId - 1;
    info.unknown08 = memberNum;
    // __LINE__ must be 1279 as in the original file: it is the line argument of operator new.
#line 1279
    m_gmkSquad = new (gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GmkSquad(&info);
    m_gmkSquad->addRef();
    m_gmkSquad->unknown2c = scale;
  }
}

} // namespace gmk
