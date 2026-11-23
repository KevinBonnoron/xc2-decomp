#pragma once
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/gf_allocator.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_mob/gmk_mob.h"
#include "gmk/gmk_set.h"
#include "gmk/gmk_squad.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

void GmkMobInsts::create(const CreateInfo &info) {
  dispose();
  m_createInfo = info;
  m_bdatInfo.create(CBdatWrapper{info.unknown08}, info.unknown10, *info.m_aGmkBase);
#line 513
  unknowna8 = new (gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) mm::mtl::Vector<gf::GF_OBJ_HANDLE *>();
  createSquad(m_bdatInfo.unknown04);
  unknownc0 = &GmkMobInsts::seqUpdatePopDepop;
}

void GmkMobInsts::createSquad(u16 squadId) {
  disposeSquad();
  if (squadId != 0) {
    GmkSquad::CreateInfo info;
    info.unknown00 = m_createInfo.m_aGmkBase->m_createBaseInfo.m_ownerGmkEnemyList->getCreateInfo().m_gmkSet->m_createInfo.unknown04;
    info.unknown04 = squadId - 1;
    // __LINE__ must be 716 as in the original file: it is the line argument of operator new.
#line 716
    m_gmkSquad = new (gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GmkSquad(&info);
    m_gmkSquad->addRef();
  }
}

} // namespace gmk
