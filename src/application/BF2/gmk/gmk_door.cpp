#include "gmk/gmk_door.h"

#include "bdat.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

bool GmkDoor::BdatInfo::isGfObjMustExist() const {
  if (lodModel == 0) {
    return false;
  }
  switch (responseType) {
  case 1:
  case 2:
  case 5:
  case 6:
    return true;
  }
  return false;
}

bool GmkDoor::BdatInfo::isPhantomMustExist() const {
  if (lodModel == 0) {
    return false;
  }
  switch (responseType) {
  case 3:
  case 4:
  case 6:
  case 7:
    return true;
  }
  return false;
}

bool GmkDoor::BdatInfo::isPopCondMatched() const {
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  if (bootedGmk.isEnable() && !bootedGmk.isMatch()) {
    return false;
  }
  return true;
}

void GmkDoor::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  condition = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  bootedGmk = BootedGmkCond(bdat, id, nullptr);
  opBootedGmk = BootedGmkCond(bdat, id, "OP_");
  responseType = bdat.getValCheck("response_type", id, BDAT_TYPE_U8);
  responseCharacter = bdat.getValCheck("response_CHR", id, BDAT_TYPE_U8);
  nameRadius = bdat.getValCheck("nameRadius", id, BDAT_TYPE_U16);
  lodModel = bdat.getValCheck("LODmodel", id, BDAT_TYPE_U16);
  missMsgId = bdat.getValCheck("missMSG_ID", id, BDAT_TYPE_U16);
  isOpenLodAnime = Bdat::getFlagVal(bdat.unknown00, "flag", id, "open_LODanime") != 0;
  isOpenSeMapPack = Bdat::getFlagVal(bdat.unknown00, "flag", id, "open_SE_type") != 0;
  openSe = bdat.getValCheck("open_SE", id, BDAT_TYPE_U16);
  openSeSize = bdat.getValCheck("open_SE_size", id, BDAT_TYPE_U8);
  openCameraGimmickId = reinterpret_cast<const char *>(bdat.getValCheck("open_camGim_ID", id, BDAT_TYPE_STRING));
  openCameraGimmickAttribute = bdat.getValCheck("open_camGim_ATR", id, BDAT_TYPE_U8);
  isCloseLodAnime = Bdat::getFlagVal(bdat.unknown00, "flag", id, "close_LODanime") != 0;
  isCloseSeMapPack = Bdat::getFlagVal(bdat.unknown00, "flag", id, "close_SE_type") != 0;
  closeSe = bdat.getValCheck("close_SE", id, BDAT_TYPE_U16);
  closeSeSize = bdat.getValCheck("close_SE_size", id, BDAT_TYPE_U8);
  closeCameraGimmickId = reinterpret_cast<const char *>(bdat.getValCheck("close_camGim_ID", id, BDAT_TYPE_STRING));
  closeCameraGimmickAttribute = bdat.getValCheck("close_camGim_ATR", id, BDAT_TYPE_U8);
  doorNextWait = toBdatF32(bdat.getValCheck("door_nextwait", id, BDAT_TYPE_F32));
  specialCloseCameraGimmickId = reinterpret_cast<const char *>(bdat.getValCheck("sp_close_camGim_ID", id, BDAT_TYPE_STRING));
  specialCloseCameraGimmickAttribute = bdat.getValCheck("sp_close_camGim_ATR", id, BDAT_TYPE_U8);
  specialPopBootedGmk = BootedGmkCond(bdat, id, "SPOP_");
  isGmkCameraPos = Bdat::getFlagVal(bdat.unknown00, "flag", id, "gmkCamPos") != 0;
}

} // namespace gmk
