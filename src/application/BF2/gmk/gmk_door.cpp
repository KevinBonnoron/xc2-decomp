#include "gmk/gmk_door.h"

#include "bdat.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

bool GmkDoor::BdatInfo::isGfObjMustExist() const {
  if (unknown06 == 0) {
    return false;
  }
  switch (unknown02) {
  case 1:
  case 2:
  case 5:
  case 6:
    return true;
  }
  return false;
}

bool GmkDoor::BdatInfo::isPhantomMustExist() const {
  if (unknown06 == 0) {
    return false;
  }
  switch (unknown02) {
  case 3:
  case 4:
  case 6:
  case 7:
    return true;
  }
  return false;
}

bool GmkDoor::BdatInfo::isPopCondMatched() const {
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  if (unknown3a.isEnable() && !unknown3a.isMatch()) {
    return false;
  }
  return true;
}

void GmkDoor::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  unknown3a = BootedGmkCond(bdat, id, nullptr);
  unknown3e = BootedGmkCond(bdat, id, "OP_");
  unknown02 = bdat.getValCheck("response_type", id, BDAT_TYPE_U8);
  unknown03 = bdat.getValCheck("response_CHR", id, BDAT_TYPE_U8);
  unknown04 = bdat.getValCheck("nameRadius", id, BDAT_TYPE_U16);
  unknown06 = bdat.getValCheck("LODmodel", id, BDAT_TYPE_U16);
  unknown08 = bdat.getValCheck("missMSG_ID", id, BDAT_TYPE_U16);
  unknown0a = Bdat::getFlagVal(bdat.unknown00, "flag", id, "open_LODanime") != 0;
  unknown0b = Bdat::getFlagVal(bdat.unknown00, "flag", id, "open_SE_type") != 0;
  unknown0c = bdat.getValCheck("open_SE", id, BDAT_TYPE_U16);
  unknown0e = bdat.getValCheck("open_SE_size", id, BDAT_TYPE_U8);
  unknown10 = reinterpret_cast<const char *>(bdat.getValCheck("open_camGim_ID", id, BDAT_TYPE_STRING));
  unknown18 = bdat.getValCheck("open_camGim_ATR", id, BDAT_TYPE_U8);
  unknown19 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "close_LODanime") != 0;
  unknown1a = Bdat::getFlagVal(bdat.unknown00, "flag", id, "close_SE_type") != 0;
  unknown1c = bdat.getValCheck("close_SE", id, BDAT_TYPE_U16);
  unknown1e = bdat.getValCheck("close_SE_size", id, BDAT_TYPE_U8);
  unknown20 = reinterpret_cast<const char *>(bdat.getValCheck("close_camGim_ID", id, BDAT_TYPE_STRING));
  unknown28 = bdat.getValCheck("close_camGim_ATR", id, BDAT_TYPE_U8);
  unknown2c = toBdatF32(bdat.getValCheck("door_nextwait", id, BDAT_TYPE_F32));
  unknown30 = reinterpret_cast<const char *>(bdat.getValCheck("sp_close_camGim_ID", id, BDAT_TYPE_STRING));
  unknown38 = bdat.getValCheck("sp_close_camGim_ATR", id, BDAT_TYPE_U8);
  unknown42 = BootedGmkCond(bdat, id, "SPOP_");
  unknown39 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "gmkCamPos") != 0;
}

} // namespace gmk
