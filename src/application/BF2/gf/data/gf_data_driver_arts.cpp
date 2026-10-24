#include "gf/data/gf_data_driver_arts.h"

#include "bdat.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_driver.h"
#include "mm_mtl/fixed_array.h"

namespace gf {

constexpr u32 ARTS_LEVEL_MAX = 5;

bool GfDataDriverArts::getEnableArts(mm::mtl::FixedArray<u32, 4> &enableArts, u32 driver, u32 weaponType) {
  for (u32 i = 0; i < enableArts.size(); i++) {
    enableArts[i] = 0;
  }

  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  u32 count = 0;
  u32 arts = bdatBattle->getArtsDrStart();
  u32 end = bdatBattle->getArtsDrEnd();
  for (; arts < end; arts++) {
    if (bdatBattle->getArtsDrDriver(arts) == driver && bdatBattle->getArtsDrWpnType(arts) == weaponType && !bdatBattle->isArtsDrFlagNormal(arts)) {
      enableArts[count] = arts;
      count++;
      if (count >= enableArts.size()) {
        break;
      }
    }
  }

  return count != 0;
}

void GfDataDriverArts::getSlotArts(mm::mtl::FixedArray<u32, 3> &slotArts, u32 driver, u32 weaponType) { slotArts = GfDataDriver::getSDataDriver(driver)->unknownc0[weaponType].unknown00; }

void GfDataDriverArts::setSlotArts(u32 driver, u32 weaponType, const mm::mtl::FixedArray<u32, 3> &slotArts) { GfDataDriver::getSDataDriver(driver)->unknownc0[weaponType].unknown00 = slotArts; }

u32 GfDataDriverArts::getArtsLevel(u32 driver, u32 arts) { return GfDataDriver::getSDataDriver(driver)->unknown2f0[arts]; }

u32 GfDataDriverArts::getNeedLevelupWp(u32 driver, u32 arts) {
  u32 level = GfDataDriver::getSDataDriver(driver)->unknown2f0[arts];
  if (level >= ARTS_LEVEL_MAX) {
    return 0;
  }

  return GfBdatBtl::get()->getArtsDrNeedWP(arts, level + 1);
}

u32 GfDataDriverArts::getLevelCap(u32 arts, u32 level) { return GfBdatBtl::get()->getArtsDrReleaseLv(arts, level); }

u32 GfDataDriverArts::getWp(u32 driver, u32 weaponType) { return GfDataDriver::getSDataDriver(driver)->unknownc0[weaponType].unknown0c; }

void GfDataDriverArts::addWp(u32 driver, u32 weaponType, int wp) {
  SDataDriver *dataDriver = GfDataDriver::getSDataDriver(driver);
  dataDriver->unknownc0[weaponType].unknown0c += wp;
  if (wp > 0) {
    dataDriver->unknownc0[weaponType].unknown10 += wp;
  }
}

void GfDataDriverArts::initializeWp(u32 driver, u32 weaponType) {
  SDataDriverWeapon &weapon = GfDataDriver::getSDataDriver(driver)->unknownc0[weaponType];
  weapon.unknown0c = 0;
  weapon.unknown10 = 0;
}

u8 *GfDataDriverArts::getNameFP() { return GfDataBdat::getFP(BDAT_BTL_ARTS_DR_MS); }

u8 *GfDataDriverArts::getCaptionFP() { return GfDataBdat::getFP(BDAT_BTL_ARTS_DR_CAP); }

u32 GfDataDriverArts::getNameID(u32 arts) { return GfBdatBtl::get()->getArtsDrName(arts); }

u32 GfDataDriverArts::getIconID(u32 arts) { return GfBdatBtl::get()->getArtsDrUI(arts); }

const char *GfDataDriverArts::getName(u32 arts) {
  u32 name = GfBdatBtl::get()->getArtsDrName(arts);
  if (name == 0) {
    return GfBdatBtl::get()->getArtsDrDebugName(arts);
  }

  const char *text = Bdat::getMSText(GfDataBdat::getFP(BDAT_BTL_ARTS_DR_MS), name);
  if (text == nullptr) {
    text = "";
  }

  return text;
}

const char *GfDataDriverArts::getDebugName(u32 arts) { return GfBdatBtl::get()->getArtsDrDebugName(arts); }

u32 GfDataDriverArts::getWpnType(u32 arts) {
  if (arts == 0) {
    return 0;
  }

  return GfBdatBtl::get()->getArtsDrWpnType(arts);
}

u32 GfDataDriverArts::getRangeType(u32 arts) {
  if (arts == 0) {
    return 0;
  }

  return GfBdatBtl::get()->getArtsDrRangeType(arts);
}

u32 GfDataDriverArts::getReaction(u32 arts, u32 level) {
  if (arts == 0 || level == 0) {
    return 0;
  }

  return GfBdatBtl::get()->getArtsDrReAct(arts, level - 1);
}

u32 GfDataDriverArts::getDamageMul(u32 arts, u32 level) {
  if (arts == 0 || level == 0) {
    return 0;
  }

  return GfBdatBtl::get()->getArtsDrDmgMgn(arts, level - 1);
}

u32 GfDataDriverArts::getRecast(u32 arts, u32 level) {
  if (arts == 0 || level == 0) {
    return 0;
  }

  return GfBdatBtl::get()->getArtsDrRecast(arts, level - 1);
}

u32 GfDataDriverArts::getEnhance(u32 arts, u32 level) {
  if (arts == 0 || level == 0) {
    return 0;
  }

  return GfBdatBtl::get()->getArtsDrEnhance(arts, level - 1);
}

u32 GfDataDriverArts::getArtsType(u32 arts) {
  if (arts == 0) {
    return 0;
  }

  return GfBdatBtl::get()->getArtsDrArtsType(arts);
}

} // namespace gf
