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
  unknown00 = info;
  unknown18.create(CBdatWrapper{info.unknown08}, info.unknown10, *info.unknown00);
#line 513
  unknowna8 = new (gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) mm::mtl::Vector<gf::GF_OBJ_HANDLE *>();
  createSquad(unknown18.unknown04);
  unknownc0 = &GmkMobInsts::seqUpdatePopDepop;
}

void GmkMobInsts::createSquad(u16 squadId) {
  disposeSquad();
  if (squadId != 0) {
    GmkSquad::CreateInfo info;
    info.unknown00 = unknown00.unknown00->unknown08.unknown00->getCreateInfo().unknown08->unknown10.unknown04;
    info.unknown04 = squadId - 1;
    // __LINE__ must be 716 as in the original file: it is the line argument of operator new.
#line 716
    unknownb0 = new (gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GmkSquad(&info);
    unknownb0->addRef();
  }
}

} // namespace gmk
