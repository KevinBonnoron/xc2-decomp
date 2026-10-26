#include "dr/dr_irr_vol_sector.h"

namespace ml {
namespace irrvol {

DrIrrVolSector::DrIrrVolSector(const SSectorInfo *sectorInfo, const SCascadeInfo *cascadeInfo) : unknown00(sectorInfo), unknown08(cascadeInfo->unknown20) {}

DrIrrVolSector::~DrIrrVolSector() {}

const SLightProbe *DrIrrVolSector::getProbe(int index) const { return unknown00->unknown40 + index; }

} // namespace irrvol
} // namespace ml
