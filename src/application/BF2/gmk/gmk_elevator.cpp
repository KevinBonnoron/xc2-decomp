#include "gmk/gmk_elevator.h"

#include "bdat.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkElevator::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("OP_Condition", id, BDAT_TYPE_U16);
  unknown02 = bdat.getValCheck("callnameRadius", id, BDAT_TYPE_U16);
  unknown04 = bdat.getValCheck("liftnameRadius", id, BDAT_TYPE_U16);
  unknown06 = bdat.getValCheck("LIFTLOD", id, BDAT_TYPE_U16);
  unknown08 = bdat.getValCheck("shtALOD", id, BDAT_TYPE_U16);
  unknown0a = bdat.getValCheck("shtBLOD", id, BDAT_TYPE_U16);
  unknown0c = bdat.getValCheck("switchALOD", id, BDAT_TYPE_U16);
  unknown0e = bdat.getValCheck("switchBLOD", id, BDAT_TYPE_U16);
  unknown10 = bdat.getValCheck("switchSE", id, BDAT_TYPE_U16);
  unknown12 = bdat.getValCheck("shutterSE", id, BDAT_TYPE_U16);
  unknown14 = bdat.getValCheck("LiftStartSE", id, BDAT_TYPE_U16);
  unknown16 = bdat.getValCheck("LiftLoopSE", id, BDAT_TYPE_U16);
  unknown18 = bdat.getValCheck("LiftStopSE", id, BDAT_TYPE_U16);
  unknown1a = bdat.getValCheck("LiftMinVolDist", id, BDAT_TYPE_U8);
  unknown1b = bdat.getValCheck("LiftMaxVolDist", id, BDAT_TYPE_U8);
  unknown1c = Bdat::getFlagVal(bdat.unknown00, "flag", id, "lift_reverse") != 0;
  unknown20 = toBdatF32(bdat.getValCheck("call_liftspeed", id, BDAT_TYPE_F32));
  unknown24 = bdat.getValCheck("missMSG_ID", id, BDAT_TYPE_U16);
  unknown28 = static_cast<s16>(bdat.getValCheck("elevator_nextwait", id, BDAT_TYPE_S16));
  unknown2c = bdat.getValCheck("liftAMapJumpId", id, BDAT_TYPE_U16);
  unknown2e = bdat.getValCheck("liftBMapJumpId", id, BDAT_TYPE_U16);
}

} // namespace gmk
