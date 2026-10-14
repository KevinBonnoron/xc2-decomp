#include "gf/data/gf_data_npc.h"
#include "bdat.h"
#include "gf/data/gf_bdat_chrbl.h"
#include "gf/data/gf_bdat_chrdr.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"

namespace gf {

enum {
  BDAT_CHR_DR = 0x77,
  BDAT_CHR_BL = 0x78,
  BDAT_RSC_NPC_LIST = 0x93,
  BDAT_BLD_BLADENAME = 0x14e,
  BDAT_CHR_BL_MS = 0x168,
  BDAT_CHR_DR_MS = 0x169,
  BDAT_FLD_NPCNAME = 0x176,
};

constexpr u32 NPC_DRIVER_END = 10;
constexpr u32 NPC_BLADE_FIRST = 1001;
constexpr u32 NPC_BLADE_END = 2001;
constexpr u32 NPC_BLADE_NAME_RANGE_FIRST = 1197;
constexpr u32 NPC_BLADE_NAME_RANGE_COUNT = 226;
constexpr f32 NPC_SCALE_PERCENT = 100.0f;

const char *GfDataNpc::getName(u32 npc) {
  u8 *bdat;
  u32 textId;
  if (!getName(bdat, textId, npc)) {
    return nullptr;
  }

  return Bdat::getMSText(bdat, textId);
}

bool GfDataNpc::getName(u8 *&bdat, u32 &textId, u32 npc) {
  if (npc < NPC_DRIVER_END) {
    textId = GfBdatChrDr::get()->getChrDrName(npc);
    bdat = GfBdatMsg::getFpChrDr();
    return textId != 0;
  }

  if (npc < NPC_BLADE_END) {
    textId = 0;
    return GfDataBlade::getNameWithMsgID(bdat, textId, *GfDataBlade::getSDataBlade(npc));
  }

  bdat = getNameBdatFp(npc);
  textId = GfBdatRsc::get()->getRscNpcListName(npc);
  return textId != 0;
}

u8 *GfDataNpc::getNameBdatFp(int npc) {
  u8 *bdat = GfDataBdat::getFP(BDAT_RSC_NPC_LIST);
  if (npc < static_cast<int>(NPC_DRIVER_END)) {
    bdat = GfDataBdat::getFP(BDAT_CHR_DR_MS);
  } else if (npc < static_cast<int>(GfBdatChrBl::get()->getChrBlEnd())) {
    bdat = GfDataBdat::getFP(BDAT_CHR_BL_MS);
  } else if (npc - NPC_BLADE_NAME_RANGE_FIRST < NPC_BLADE_NAME_RANGE_COUNT) {
    bdat = GfDataBdat::getFP(BDAT_BLD_BLADENAME);
  } else {
    bdat = GfDataBdat::getFP(BDAT_FLD_NPCNAME);
  }

  return bdat;
}

u32 GfDataNpc::getRscRelativeID(u32 npc) {
  u32 start = GfBdatRsc::get()->getRscNpcListStart();
  return npc + 1 - start;
}

u32 GfDataNpc::getRace(u32 npc) {
  if (npc < NPC_DRIVER_END) {
    return GfBdatChrDr::get()->getChrDrRace(npc);
  }

  if (npc < NPC_BLADE_END) {
    return GfDataBlade::getSDataBlade(npc)->race;
  }

  return GfBdatRsc::get()->getRscNpcListRace(npc);
}

u32 GfDataNpc::getGender(u32 npc) {
  if (npc < NPC_DRIVER_END) {
    return GfBdatChrDr::get()->getChrDrGender(npc);
  }

  if (npc < NPC_BLADE_END) {
    return GfDataBlade::getSDataBlade(npc)->gender;
  }

  return GfBdatRsc::get()->getRscNpcListGender(npc);
}

const char *GfDataNpc::getModelName(u32 npc) {
  if (npc < NPC_DRIVER_END) {
    return GfBdatChrDr::get()->getChrDrModel(npc);
  }

  if (npc < NPC_BLADE_END) {
    return GfDataBlade::getSDataBlade(npc)->resourceNameModel;
  }

  return GfBdatRsc::get()->getRscNpcListModel(npc);
}

const char *GfDataNpc::getMotionName(u32 npc) {
  if (npc < NPC_DRIVER_END) {
    return GfBdatChrDr::get()->getChrDrMotion(npc);
  }

  if (npc < NPC_BLADE_END) {
    return GfDataBlade::getSDataBlade(npc)->resourceNameMotion;
  }

  return GfBdatRsc::get()->getRscNpcListMotion(npc);
}

const char *GfDataNpc::getAddMotionName(u32 npc) {
  if (npc >= NPC_BLADE_END) {
    const char *addMotionName = GfBdatRsc::get()->getRscNpcListAddMotion(npc);
    if (addMotionName != nullptr && addMotionName[0] != '\0') {
      return addMotionName;
    }
  }

  return nullptr;
}

const char *GfDataNpc::getEffectName(u32 npc) {
  if (npc >= NPC_BLADE_END) {
    const char *effectName = GfBdatRsc::get()->getRscNpcListComp_Eff(npc);
    if (effectName != nullptr && effectName[0] != '\0') {
      return effectName;
    }
  }

  return nullptr;
}

f32 GfDataNpc::getScale(u32 npc) {
  if (npc < NPC_DRIVER_END) {
    return 1.0f;
  }

  if (npc < NPC_BLADE_END) {
    return GfDataBlade::getSDataBlade(npc)->scale * 0.01f;
  }

  return GfBdatRsc::get()->getRscNpcListScale(npc) / NPC_SCALE_PERCENT;
}

u32 GfDataNpc::getCollisionId(u32 npc) {
  if (npc < NPC_DRIVER_END) {
    return GfBdatChrDr::get()->getChrDrCollisionId(npc);
  }

  if (npc < NPC_BLADE_END) {
    return GfDataBlade::getSDataBlade(npc)->collisionId;
  }

  return GfBdatRsc::get()->getRscNpcListCollisionId(npc);
}

u32 GfDataNpc::getOffsetID(u32 npc) {
  if (npc < NPC_DRIVER_END) {
    return GfBdatChrDr::get()->getChrDrOffsetID(npc);
  }

  if (npc < NPC_BLADE_END) {
    return GfDataBlade::getSDataBlade(npc)->offsetID;
  }

  return GfBdatRsc::get()->getRscNpcListOffsetID(npc);
}

u8 *GfDataNpc::getRscBdatFp(int npc) {
  u8 *bdatDriver = GfDataBdat::getFP(BDAT_CHR_DR);
  u8 *bdatBlade = GfDataBdat::getFP(BDAT_CHR_BL);
  u8 *bdatNpc = GfDataBdat::getFP(BDAT_RSC_NPC_LIST);
  if (npc >= Bdat::getIdTop(bdatDriver) && npc < Bdat::getIdTop(bdatDriver) + Bdat::getIdCount(bdatDriver)) {
    return bdatDriver;
  }

  if (npc >= Bdat::getIdTop(bdatBlade) && npc < Bdat::getIdTop(bdatBlade) + Bdat::getIdCount(bdatBlade)) {
    return bdatBlade;
  }

  if (npc < Bdat::getIdTop(bdatNpc)) {
    bdatNpc = nullptr;
  } else if (npc >= Bdat::getIdTop(bdatNpc) + Bdat::getIdCount(bdatNpc)) {
    bdatNpc = nullptr;
  }

  return bdatNpc;
}

bool GfDataNpc::getExtraParts(u32 npc, u32 part) {
  if (npc < NPC_DRIVER_END) {
    return true;
  }

  if (npc < NPC_BLADE_END) {
    SDataBlade *dataBlade = GfDataBlade::getSDataBlade(npc);
    return dataBlade->extraParts[part] != 0;
  }

  return GfBdatRsc::get()->getRscNpcListExtraParts(npc, part) != 0;
}

bool GfDataNpc::isNeedResourceEvent(u32 npc) {
  if (npc < NPC_BLADE_END) {
    return false;
  }

  const char *addMotionName = GfBdatRsc::get()->getRscNpcListAddMotion(npc);
  return addMotionName != nullptr && addMotionName[0] != '\0';
}

u32 GfDataNpc::getFootStep(u32 npc) {
  if (npc < NPC_BLADE_FIRST) {
    return GfBdatChrDr::get()->getChrDrFootStep(npc);
  }

  if (npc < NPC_BLADE_END) {
    return GfDataBlade::getSDataBlade(npc)->footStep;
  }

  return GfBdatRsc::get()->getRscNpcListFootStep(npc);
}

u32 GfDataNpc::getFootStepEffect(u32 npc) {
  if (npc < NPC_BLADE_FIRST) {
    return GfBdatChrDr::get()->getChrDrFootStepEffect(npc);
  }

  if (npc < NPC_BLADE_END) {
    return GfDataBlade::getSDataBlade(npc)->footStepEffect;
  }

  return GfBdatRsc::get()->getRscNpcListFootStepEffect(npc);
}

u32 GfDataNpc::getEyeRotControl(u32 npc) {
  if (npc < NPC_BLADE_FIRST) {
    if (npc == 0) {
      return 0;
    }

    return GfBdatChrDr::get()->getChrDrEyeRot(npc);
  }

  if (npc < NPC_BLADE_END) {
    return GfDataBlade::getSDataBlade(npc)->eyeRotControl;
  }

  return GfBdatRsc::get()->getRscNpcListEyeRot(npc);
}

} // namespace gf
