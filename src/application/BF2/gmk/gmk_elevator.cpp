#include "gmk/gmk_elevator.h"

#include "bdat.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/gf_game_manager.h"
#include "gmk/gmk_bdat.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

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

GmkType GmkElevatorLocator::getGmkType() const { return GMK_TYPE; }

bool GmkElevatorLocator::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

GmkType GmkElevator::getGmkType() const { return GMK_TYPE; }

int GmkElevator::getGameFlagId() const { return unknown20.unknown18 + 0xb248; }

void GmkElevator::onLeavePhantom(const IGmkPhantomEventListener::OnLeaveInfo &info) {}

void GmkElevator::clearRequests() { unknown4C8 = 0; }

bool GmkElevator::isCallSwitch(gf::GF_OBJ_HANDLE *handle) const {
  for (int i = 0; i < 4; i++) {
    if (unknown290[i] == handle) {
      return i % 2 == 0;
    }
  }
  return false;
}

bool GmkElevator::isLiftSwitch(gf::GF_OBJ_HANDLE *handle) const {
  for (int i = 0; i < 4; i++) {
    if (unknown290[i] == handle) {
      return i % 2 == 1;
    }
  }
  return false;
}

bool GmkElevator::isElevatorMoveOK() const {
  if (!isValid()) {
    return false;
  }
  return gf::GfGameManager::isElevatorMoveOK(getBdatInfo()->unknown06);
}

bool GmkElevator::isGmkFinished() const {
  if (unknown4CC < getBdatInfo()->unknown28) {
    return false;
  }
  return gf::GfGameFlag::getLocal(1, getGameFlagId()) != 0;
}

} // namespace gmk
