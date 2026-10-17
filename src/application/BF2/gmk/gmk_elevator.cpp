#include "gmk/gmk_elevator.h"

#include "bdat.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkElevator::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  condition = bdat.getValCheck("OP_Condition", id, BDAT_TYPE_U16);
  callNameRadius = bdat.getValCheck("callnameRadius", id, BDAT_TYPE_U16);
  liftNameRadius = bdat.getValCheck("liftnameRadius", id, BDAT_TYPE_U16);
  liftLod = bdat.getValCheck("LIFTLOD", id, BDAT_TYPE_U16);
  shutterALod = bdat.getValCheck("shtALOD", id, BDAT_TYPE_U16);
  shutterBLod = bdat.getValCheck("shtBLOD", id, BDAT_TYPE_U16);
  switchALod = bdat.getValCheck("switchALOD", id, BDAT_TYPE_U16);
  switchBLod = bdat.getValCheck("switchBLOD", id, BDAT_TYPE_U16);
  switchSe = bdat.getValCheck("switchSE", id, BDAT_TYPE_U16);
  shutterSe = bdat.getValCheck("shutterSE", id, BDAT_TYPE_U16);
  liftStartSe = bdat.getValCheck("LiftStartSE", id, BDAT_TYPE_U16);
  liftLoopSe = bdat.getValCheck("LiftLoopSE", id, BDAT_TYPE_U16);
  liftStopSe = bdat.getValCheck("LiftStopSE", id, BDAT_TYPE_U16);
  liftMinVolumeDist = bdat.getValCheck("LiftMinVolDist", id, BDAT_TYPE_U8);
  liftMaxVolumeDist = bdat.getValCheck("LiftMaxVolDist", id, BDAT_TYPE_U8);
  isLiftReverse = Bdat::getFlagVal(bdat.data, "flag", id, "lift_reverse") != 0;
  callLiftSpeed = toBdatF32(bdat.getValCheck("call_liftspeed", id, BDAT_TYPE_F32));
  missMsgId = bdat.getValCheck("missMSG_ID", id, BDAT_TYPE_U16);
  nextWait = static_cast<s16>(bdat.getValCheck("elevator_nextwait", id, BDAT_TYPE_S16));
  liftAMapJumpId = bdat.getValCheck("liftAMapJumpId", id, BDAT_TYPE_U16);
  liftBMapJumpId = bdat.getValCheck("liftBMapJumpId", id, BDAT_TYPE_U16);
}

} // namespace gmk
