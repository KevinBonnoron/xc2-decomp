#pragma once
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/gf_allocator.h"
#include "gmk/gmk_mob/gmk_mob.h"
#include "mm_mtl/vector.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

void GmkMobInsts::create(const CreateInfo &info) {
  dispose();
  unknown00 = info;
  unknown18.create(CBdatWrapper{info.unknown08}, info.unknown10, *info.unknown00);
#line 513
  unknowna8 = new (gf::getAllocator(gf::ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) mm::mtl::Vector<gf::GF_OBJ_HANDLE *>();
  createSquad(unknown18.unknown04);
  unknownc0 = &GmkMobInsts::seqUpdatePopDepop;
}

} // namespace gmk
