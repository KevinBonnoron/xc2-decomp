#include "gf/menu/adapter/gf_menu_char_data_adapter.h"

#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_driver_skill.h"
#include "gf/data/gf_data_en_book.h"
#include "gf/data/gf_data_idea.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/util/gf_equip_util.h"

namespace gf {

bool GfMenuCharDataAdapter::update_HpMax(const DataParamAcc &acc) {
  setNumber(acc.getHpMax(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_PhysDef(const DataParamAcc &acc) {
  setNumber(acc.getPArmor(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_EtherDef(const DataParamAcc &acc) {
  setNumber(acc.getEArmor(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_Guard(const DataParamAcc &acc) {
  setNumber(acc.getGuardRate(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_AutoAtkDmg(const DataParamAcc &acc) {
  u32 min = acc.getNorAtkDmgMin(unknown79 == 1);
  u32 max = acc.getNorAtkDmgMax(unknown79 == 1);
  setNumber((min + max) / 2);
  return true;
}

bool GfMenuCharDataAdapter::update_Critical(const DataParamAcc &acc) {
  setNumber(acc.getCriticalRate(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_Strength(const DataParamAcc &acc) {
  setNumber(acc.getStrength(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_EtherPow(const DataParamAcc &acc) {
  setNumber(acc.getPowerEther(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_Dex(const DataParamAcc &acc) {
  setNumber(acc.getDex(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_Agl(const DataParamAcc &acc) {
  setNumber(acc.getAgility(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_Luck(const DataParamAcc &acc) {
  setNumber(acc.getLuck(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_Lv(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER || acc.getObjType() == OBJECT_TYPE_BLADE || acc.getObjType() == OBJECT_TYPE_ENEMY) {
    setNumber(acc.getLevel(unknown79 == 1));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_ExpNext(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    if (acc.getLevel(false) < 99) {
      setNumber(acc.getExpNext(false));
      return true;
    }
    return false;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_ExpBonus(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    setNumber(acc.getExp());
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_LevelUpEnable(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    return GfDataDriver::isEnableLevelUp(acc.getValidDriverId());
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_Wp(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    setNumber(acc.getWeaponPoint(unknown80));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_Sp(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    setNumber(acc.getSkillPoint());
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_Bustup(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    setNumber(GfMenuObjUtil::convMenuDriverID(acc.getValidDriverId()));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_BustupPlate(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    int driver = GfMenuObjUtil::convMenuDriverID(acc.getValidDriverId());
    int plate = 0;
    if (driver != 0) {
      plate = driver - 1;
    }
    setNumber(plate);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_BladeEnable(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    return GfMenuObjUtil::isValidBlade(acc.getBlade(unknown80, false));
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_KizunaRingOpen(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    setNumber(GfDataDriverSkill::getValidSkillNum(acc.getValidDriverId(), false));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_KizunaRingMax(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    setNumber(15);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_IdeaPoint(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    SDataIdea *idea = GfDataDriver::getSDataIdea(acc.getValidDriverId());
    setNumber(idea->unknown00[unknown80].unknown00);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_ClassBuffVal(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    setNumber(GfMenuObjUtil::getDriverClassBuffRatio(acc.getClass(unknown79 == 1), unknown80));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_ClassBuffLv(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    u8 level = GfMenuObjUtil::getDriverClassBuffLv(acc.getClass(unknown79 == 1), unknown80);
    if (level != 0) {
      setNumber(level - 1);
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_WeaponIcon(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 weaponType = GfDataBlade::getBladeWpnType(acc.getValidBdatId());
    if (weaponType != 0) {
      setNumber(weaponType - 1);
      return true;
    }
    return false;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_AttrIcon(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 icon = GfMenuObjUtil::getBladeAttributeIconID(acc.getValidBdatId());
    if (icon != 0) {
      setNumber(GfMenuBdat::getIconImageIndex(icon));
      return true;
    }
    return false;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_RareIcon(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 icon = GfMenuObjUtil::getBladeRareIconID(acc.getValidBdatId());
    if (icon != 0) {
      setNumber(GfMenuBdat::getIconImageIndex(icon));
      return true;
    }
    return false;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_Bustup(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    setNumber(GfMenuObjUtil::convMenuBladeID(acc.getValidBdatId()));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_Power(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    setNumber(acc.getBladePower(unknown79 == 1));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_Attr(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    setNumber(GfMenuObjUtil::getBladeAttributeID(acc.getValidBdatId()));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_AttrCol(const DataParamAcc &acc) { return acc.getObjType() == OBJECT_TYPE_BLADE; }

bool GfMenuCharDataAdapter::update_BL_Enable(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    return GfMenuObjUtil::isValidBlade(acc.getValidBdatId());
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_IdeaPoint(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    SDataIdea *idea = GfDataBlade::getSDataIdea(acc.getValidBdatId());
    setNumber(idea->unknown00[unknown80].unknown00);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_IdeaLv(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    SDataIdea *idea = GfDataBlade::getSDataIdea(acc.getValidBdatId());
    setNumber(idea->unknown00[unknown80].unknown04);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_RecastLv(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u8 *bdat = GfDataBdat::getFP(0x137);
    setNumber(GfMenuBdat::getValueLevel(bdat, acc.getCoolTime()));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_BtlSkillIcon(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    acc.getBladeSkill(unknown80, false);
    setNumber(0);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_BtlSkillLv(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    setNumber(acc.getBladeSkillLevel(unknown80, false));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_Selectable(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    const char *color = nullptr;
    if (!GfMenuObjUtil::isBladeSelectable(acc.getValidBdatId(), unknown88.get())) {
      color = "unuse";
    }
    setMulColor(color);
  }
  return true;
}

bool GfMenuCharDataAdapter::update_BL_Releasable(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    const char *color = nullptr;
    if (!GfMenuObjUtil::isBladeReleasable(acc.getValidBdatId(), unknown88.get())) {
      color = "unuse";
    }
    setMulColor(color);
  }
  return true;
}

bool GfMenuCharDataAdapter::update_BL_AffinityIcon(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 rank = GfDataBlade::getTrustRank(acc.getValidBdatId());
    if (rank > 1) {
      setNumber(rank - 1);
    }
    return rank != 0;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_KizunaRingOpen(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    setNumber(GfDataBlade::getKizunaringCompleteNum(acc.getValidBdatId()));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_KizunaRingMax(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    setNumber(GfDataBlade::getKizunaringMax(acc.getValidBdatId()));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_OrbSlotEnable(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    return unknown80 < GfEquipUtil::getEquipOrbMax(acc.getValidBdatId());
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_InMercenry(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    return GfDataBlade::isActivateMercenaryTeam(acc.getValidBdatId());
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_Rank(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 blade = acc.getValidBdatId();
    if (GfMenuObjUtil::isValidBlade(blade)) {
      setNumber(GfMenuObjUtil::getBladeRank(blade));
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_Rarity(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 blade = acc.getValidBdatId();
    if (GfMenuObjUtil::isValidBlade(blade)) {
      setNumber(GfMenuObjUtil::getBladeRarity(blade));
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_EN_BookID(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_ENEMY) {
    setNumber(GfDataEnBook::getEnBoolId(acc.getValidBdatId()));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_EN_RewardExp(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_ENEMY) {
    setNumber(acc.getLevelExp());
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_EN_RewardGold(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_ENEMY) {
    setNumber(acc.getLevelGold());
    return true;
  }
  return false;
}

} // namespace gf
