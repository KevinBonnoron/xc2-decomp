#include "gmk/gmk_field_volume.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

namespace gmk {

template bool TGmkList<GmkFieldVolume, GmkFieldVolume::BdatInfo, 1296848454u, 2u, GmkFieldVolumeGob>::initGmkBdatInfo(GmkFieldVolume::BdatInfo &, int &, const AGmkBase &);

void GmkFieldVolume::create(const CreateInfo &info) { AGmkBase::create(info); }

} // namespace gmk
