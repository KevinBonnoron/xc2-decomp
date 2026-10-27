#include "dr/dr_res_mdo_lod_parts.h"

namespace ml {

DrResMdoLodParts::DrResMdoLodParts() : unknown00(0), unknown08(0), unknown10(1.0f), unknown14(0), unknown18(nullptr) {}

void DrResMdoLodParts::setup(const MdsMdlLodData *lodData) { unknown18 = lodData; }

} // namespace ml
