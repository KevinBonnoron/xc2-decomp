#include "gf/menu/adapter/gf_menu_char_data_adapter.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_battle.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_blade_arts.h"
#include "gf/data/gf_data_blade_arts_n.h"
#include "gf/data/gf_data_blade_skill.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_driver_skill.h"
#include "gf/data/gf_data_en_book.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_field_skill.h"
#include "gf/data/gf_data_idea.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_manager.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/util/gf_equip_util.h"
#include "mm_mtl/fixstr.h"
#include "ui/ui_str.h"

namespace gf {

bool GfMenuCharDataAdapter::update_DR_Exp(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    u32 used = GfDataDriver::getExpUsed(acc.getValidDriverId());
    setNumber(acc.getBattleExp() + used);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_ClassName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    u8 *bdat;
    u32 textId;
    if (GfDataBattle::getClassName(bdat, textId, acc.getClass(unknown79 == 1))) {
      if (bdat == nullptr) {
        return false;
      }
      if (textId == 0) {
        return false;
      }
      ui::UIStr text(bdat, textId);
      setText(text);
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_BtlFace(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    int icon;
    if (acc.isValid() && acc.getObjType() == OBJECT_TYPE_DRIVER && acc.getBdatId() == 1 && GfGameManager::isRexAwakening()) {
      icon = 8;
    } else {
      u32 iconData = acc.getIconData();
      if (iconData == 0) {
        return false;
      }
      icon = GfMenuBdat::getIconImageIndex(iconData);
    }
    setNumber(icon);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_FieldSkillLv(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 index = getBL_FieldSkillIndex(acc);
    if (index >= 3) {
      return false;
    }
    bool result = false;
    if (acc.getFieldSkill(index, false) != 0) {
      setNumber(acc.getFieldSkillLevel(index, false));
      result = true;
    }
    return result;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_SkillLv(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 index = getBL_SkillIndex(acc);
    if (index >= 3) {
      return false;
    }
    setNumber(acc.getBladeSkillLevel(index, false));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_AttrCol2(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 attribute = GfMenuObjUtil::getBladeAttributeID(acc.getValidBdatId());
    mm::mtl::FixStr<32> color;
    color.format("elemental%02d", attribute);
    setColor(color.c_str());
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_RoleName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u8 *bdat = GfDataBdat::getFP(BDAT_MENU_ROLE_NAME_MS);
    if (bdat != nullptr) {
      ui::UIStr text(bdat, acc.getRole(false));
      setText(text);
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_Selectable2(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    if (GfMenuReference::getReferenceDriverID(0) == 1) {
      setMulColor("white");
    } else {
      const char *color = "unuse";
      if (!GfDataBlade::isEnableEngageRex(acc.getValidBdatId())) {
        color = "white";
      }
      setMulColor(color);
    }
  }
  return true;
}

bool GfMenuCharDataAdapter::update_BL_CorrectiveValue(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    if (GfMenuObjUtil::getBladeCorrectiveType(acc.getValidBdatId()) != 0) {
      setNumber(GfMenuObjUtil::getBladeCorrectiveRatio(acc.getValidBdatId()));
      return true;
    }
    return false;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_ArtsName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 arts = acc.getBladeArtsN(unknown80, false);
    if (arts == 0) {
      return false;
    }
    u8 *bdat;
    u32 textId;
    if (GfDataBladeArtsN::getName(bdat, textId, arts)) {
      ui::UIStr text(bdat, textId);
      setText(text);
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_ArtsDesc(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 arts = acc.getBladeArtsN(unknown80, false);
    if (arts == 0) {
      return false;
    }
    u8 *bdat;
    u32 textId;
    if (GfDataBladeArtsN::getCaption(bdat, textId, arts)) {
      ui::UIStr text(bdat, textId);
      setText(text);
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_GenderIcon(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    int icon;
    if (GfDataBlade::isMale(acc.getValidBdatId())) {
      icon = 0;
    } else if (GfDataBlade::isFemale(acc.getValidBdatId())) {
      icon = 1;
    } else {
      icon = 2;
    }
    setNumber(icon);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_DR_Face(const DataParamAcc &acc) {
  u32 driver = GfDataBlade::getCreator(acc.getValidBdatId());
  if (driver == 0) {
    return false;
  }
  DataParamAcc driverAcc(OBJECT_TYPE_DRIVER, driver, GIMMICK_TYPE_NONE);
  int icon = GfMenuObjUtil::getFaceIconID(driverAcc);
  bool result = false;
  if (icon != 0) {
    setNumber(GfMenuBdat::getIconImageIndex(icon));
    result = true;
  }
  return result;
}

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

bool GfMenuCharDataAdapter::update_AttrName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE || acc.getObjType() == OBJECT_TYPE_ENEMY) {
    u8 *bdat = GfDataBdat::getFP(BDAT_MNU_MSG_ATTR);
    int attribute = acc.getAttribute(-1, false);
    u8 *msBdat = GfDataBdat::getFP(BDAT_MENU_ATTR_MS);
    u16 name = Bdat::getVal(bdat, "name", Bdat::getIdTop(msBdat) + attribute).valueU16;
    ui::UIStr text(msBdat, name);
    setText(text);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_SpecialName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u8 *bdat;
    u32 textId;
    bool found;
    if (unknown80 < 3) {
      u32 arts = acc.getBladeArts(unknown80, false);
      if (arts == 0) {
        return false;
      }
      found = GfDataBladeArts::getName(bdat, textId, arts);
    } else {
      u32 arts = acc.getBladeArtsEx(false);
      if (arts == 0) {
        return false;
      }
      found = GfDataBladeArts::getExName(bdat, textId, arts);
    }
    if (found) {
      ui::UIStr text(bdat, textId);
      setText(text);
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_SpecialDesc(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u8 *bdat;
    u32 textId;
    bool found;
    u32 artsEx = acc.getBladeArtsEx(false);
    if (artsEx == 0) {
      return false;
    }
    if (unknown80 < 3) {
      u32 arts = acc.getBladeArts(unknown80, false);
      if (arts == 0) {
        return false;
      }
      found = GfDataBladeArts::getCaption(bdat, textId, arts);
    } else {
      found = GfDataBladeArts::getExCaption(bdat, textId, artsEx);
    }
    if (found) {
      ui::UIStr text(bdat, textId);
      setText(text);
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_FieldSkillName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 index = getBL_FieldSkillIndex(acc);
    if (index < 3) {
      u32 fieldSkill = acc.getFieldSkill(index, false);
      if (fieldSkill == 0) {
        return false;
      }
      if (acc.getFieldSkillLevel(index, false) == 0) {
        return false;
      }
      u8 *bdat;
      u32 textId;
      if (GfDataFieldSkill::getName(bdat, textId, fieldSkill)) {
        ui::UIStr text(bdat, textId);
        setText(text);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_FieldSkillDesc(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 index = getBL_FieldSkillIndex(acc);
    if (index < 3) {
      u32 fieldSkill = acc.getFieldSkill(index, false);
      if (fieldSkill == 0) {
        return false;
      }
      u8 *bdat;
      u32 textId;
      if (GfDataFieldSkill::getCaption(bdat, textId, fieldSkill)) {
        ui::UIStr text(bdat, textId);
        setText(text);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_SkillName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 index = getBL_SkillIndex(acc);
    if (index < 3) {
      u32 skill = acc.getBladeSkill(index, false);
      if (skill == 0) {
        return false;
      }
      if (acc.getBladeSkillLevel(index, false) == 0) {
        return false;
      }
      u8 *bdat;
      u32 textId;
      if (GfDataBladeSkill::getName(bdat, textId, skill)) {
        ui::UIStr text(bdat, textId);
        setText(text);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_weaponTypeName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u8 *bdat = GfDataBdat::getFP(BDAT_MNU_MSG_WEAPON_TYPE);
    u32 weaponType = GfDataBlade::getSDataBlade(acc.getValidBdatId())->unknown821;
    u8 *msBdat = GfDataBdat::getFP(BDAT_ITM_PCWPNTYPE_MS);
    u16 name = Bdat::getVal(bdat, "name", weaponType).valueU16;
    ui::UIStr text(msBdat, name);
    setText(text);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_CorrectiveTypeName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u8 *bdat = GfDataBdat::getFP(BDAT_MENU_ST_CORRECTIONVALUE);
    if (bdat != nullptr) {
      u32 type = GfMenuObjUtil::getBladeCorrectiveType(acc.getValidBdatId());
      if (type != 0) {
        ui::UIStr text(bdat, type);
        setText(text);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_TeamName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 blade = acc.getValidBdatId();
    if (GfMenuObjUtil::isValidBlade(blade)) {
      ui::UIStr text;
      if (GfMenuObjUtil::getBladeTeamName(blade, text)) {
        setText(text);
        return true;
      }
      return false;
    }
    return false;
  }
  return false;
}

u32 GfMenuCharDataAdapter::getBL_FieldSkillIndex(const DataParamAcc &acc) {
  u32 count = 0;
  for (u32 index = 0; index < 3; index++) {
    if (acc.getFieldSkill(index, false) != 0 && acc.getFieldSkillLevel(index, false) != 0) {
      if (count == unknown80) {
        return index;
      }
      count++;
    }
  }
  return 3;
}

u32 GfMenuCharDataAdapter::getBL_SkillIndex(const DataParamAcc &acc) {
  u32 count = 0;
  for (u32 index = 0; index < 3; index++) {
    if (acc.getBladeSkill(index, false) != 0 && acc.getBladeSkillLevel(index, false) != 0) {
      if (count == unknown80) {
        return index;
      }
      count++;
    }
  }
  return 3;
}

bool GfMenuCharDataAdapter::update_EN_Genus(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_ENEMY) {
    GfBdatRsc *bdatRsc = GfBdatRsc::get();
    if (bdatRsc != nullptr) {
      u32 rsc = GfDataEnemy::getRscIdByArrangeId(acc.getValidBdatId());
      if (rsc != 0) {
        u32 name = bdatRsc->getRscEnGenusNAME(bdatRsc->getRscEnTypeGenus(rsc));
        ui::UIStr text(GfDataBdat::getFP(BDAT_BTL_ENGENUS_MS), name);
        setText(text);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_FaceIcon(const DataParamAcc &acc) {
  u32 icon = GfMenuObjUtil::getFaceIconID(acc);
  if (icon != 0) {
    setNumber(GfMenuBdat::getIconImageIndex(icon));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_SetBladeFace(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    u32 blade = acc.getBlade(-1, false);
    if (blade == 0) {
      return false;
    }
    if (!GfDataBlade::isDummyBlade(blade)) {
      DataParamAcc bladeAcc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_NONE);
      int icon = GfMenuObjUtil::getFaceIconID(bladeAcc);
      if (icon != 0) {
        setNumber(GfMenuBdat::getIconImageIndex(icon));
        return true;
      }
      return false;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_IdeaLv(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
    SDataIdea *idea = GfDataDriver::getSDataIdea(acc.getValidDriverId());
    u32 level = idea->unknown00[unknown80].unknown04;
    if (unknown79 != 0) {
      setNumberMax(15);
      int virtualLevel = level + GfMenuReference::getDriverAddIdeaLv(unknown80);
      u32 clamped = 0;
      if (virtualLevel >= 0) {
        clamped = virtualLevel;
      }
      level = 15;
      if (clamped < 16) {
        level = clamped;
      }
    }
    setNumber(level);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_ExpNextVirtual(const DataParamAcc &acc) {
  if (acc.getObjType() != OBJECT_TYPE_DRIVER) {
    return false;
  }

  int exp;
  if (GfMenuReference::getDriverVirtualLevel() == 0) {
    if (acc.getObjType() != OBJECT_TYPE_DRIVER) {
      return false;
    }
    if (acc.getLevel(false) > 98) {
      return false;
    }
    exp = acc.getExpNext(false);
  } else {
    exp = GfDataDriver::getExpSetLevel(acc.getValidDriverId(), GfMenuReference::getDriverVirtualLevel() + 1);
  }
  setNumber(exp);
  return true;
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
