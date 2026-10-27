#include "gf/field/gf_field_undulator.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"

namespace gf {

void GfFieldUndulator::BdatInfo::create(int id) {
  u8 *bdat = GfDataBdat::getFP(BDAT_RSC_EN_UND);
  unknown00 = Bdat::getFlagVal(bdat, "Flag", id, "UndX") != 0;
  unknown01 = Bdat::getFlagVal(bdat, "Flag", id, "UndZ") != 0;
  unknown04 = static_cast<s8>(Bdat::getValCheck(bdat, "UndMinX", id, 4)) * 0.017453292f;
  unknown08 = static_cast<s8>(Bdat::getValCheck(bdat, "UndMaxX", id, 4)) * 0.017453292f;
  unknown0c = static_cast<s8>(Bdat::getValCheck(bdat, "UndMinZ", id, 4)) * 0.017453292f;
  unknown10 = static_cast<s8>(Bdat::getValCheck(bdat, "UndMaxZ", id, 4)) * 0.017453292f;
  u8 deg = Bdat::getValCheck(bdat, "UndDeg", id, 1);
  unknown14 = static_cast<f32>(deg) * 0.0017453292f;
}

void GfFieldUndulator::create(const CreateInfo &info) {
  unknown08.unknown01 = false;
  unknown08.unknown00 = false;
  unknown00 = info;
  u16 paramId = Bdat::getValCheck(GfDataBdat::getFP(BDAT_CHR_EN_ARRANGE), "ParamID", info.unknown00, 2);
  u32 resourceId = static_cast<u16>(Bdat::getValCheck(GfDataBdat::getFP(BDAT_CHR_EN_PARAM), "ResourceID", paramId, 2));
  u8 undulation = Bdat::getValCheck(GfDataBdat::getFP(BDAT_RSC_EN), "Unduration", resourceId, 1);
  unknown08.create(undulation);
}

void GfFieldUndulator::dispose() {
  unknown08.unknown00 = false;
  unknown08.unknown01 = false;
}

} // namespace gf
