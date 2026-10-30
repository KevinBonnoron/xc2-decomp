#include "gmk/gmk_field_volume.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

namespace gmk {

template bool TGmkList<GmkFieldVolume, GmkFieldVolume::BdatInfo, 1296848454u, 2u, GmkFieldVolumeGob>::initGmkBdatInfo(GmkFieldVolume::BdatInfo &, int &, const AGmkBase &);

void GmkFieldVolume::create(const CreateInfo &info) { AGmkBase::create(info); }

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkFieldVolume::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkFieldVolume::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkFieldVolume::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkFieldVolume>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkFieldVolume>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkFieldVolume>::resize(size_t);
