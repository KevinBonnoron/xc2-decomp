#include "gf/data/gf_data_hana.h"
#include "bdat.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_manager.h"

namespace gf {

constexpr u32 HANA_COUNT = 3;
constexpr u32 HANA_BASE_FIRST = BLADE_HANA_JS - 1;
constexpr u32 EXTEND_CIRCUIT_FIRST = 3;
constexpr u32 POWER_RANK_MAX = 20;

void EquipHana::setArtsParts(u32 parts, u32 handle, u32 index) {
  unknown04[index].unknown04 = parts;
  unknown04[index].unknown0a = handle;
  unknown04[index].unknown00 = GfBdatItem::get()->getITM_HanaArtsEnhEnhance(parts);
}

void EquipHana::setNArtsParts(u32 parts, u32 handle, u32 index) {
  unknown28[index].unknown04 = parts;
  unknown28[index].unknown0a = handle;
  unknown28[index].unknown00 = GfBdatItem::get()->getITM_HanaNArtsSetNArts(parts);
  unknown28[index].unknown02 = GfBdatItem::get()->getITM_HanaNArtsSetNArtsRecastRev(parts);
}

bool GfDataHana::getRoleName(u8 *&bdat, u32 &textId, u32 parts) {
  textId = GfBdatItem::get()->getITM_HanaRoleName(parts);
  bdat = GfBdatMsg::getFpBtlHanaRole();
  return textId != 0;
}

bool GfDataHana::getAttributeName(u8 *&bdat, u32 &textId, u32 parts) {
  textId = GfBdatItem::get()->getITM_HanaAtrName(parts);
  bdat = GfBdatMsg::getFpBtlHanaAtr();
  return textId != 0;
}

bool GfDataHana::getArtsName(u8 *&bdat, u32 &textId, u32 parts) {
  textId = GfBdatItem::get()->getITM_HanaArtsEnhName(parts);
  bdat = GfBdatMsg::getFpOrb();
  return textId != 0;
}

bool GfDataHana::getNArtsName(u8 *&bdat, u32 &textId, u32 parts) {
  textId = GfBdatItem::get()->getITM_HanaNArtsSetName(parts);
  bdat = GfBdatMsg::getFpBtlHanaNArts();
  return textId != 0;
}

bool GfDataHana::getAssistName(u8 *&bdat, u32 &textId, u32 parts) {
  textId = GfBdatItem::get()->getITM_HanaAssistName(parts);
  bdat = GfBdatMsg::getFpOrb();
  return textId != 0;
}

bool GfDataHana::isValid(u32 blade) { return blade - BLADE_HANA_JS < HANA_COUNT; }

u32 GfDataHana::getRole(u32 blade) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  return bdatItem->getITM_HanaRoleRole(GfDataBlade::getSDataBlade(blade)->unknown68c.unknown00);
}

u32 GfDataHana::getCondenserNum(u32 blade) { return GfBdatBtl::get()->getBTL_HanaBaseNCondNum(blade - HANA_BASE_FIRST); }

EquipHana *GfDataHana::getEquipParts(SDataBlade &dataBlade) { return &dataBlade.unknown68c; }

u32 GfDataHana::getExtendCondenserNum(u32 blade) { return GfBdatBtl::get()->getBTL_HanaBaseECondNum(blade - HANA_BASE_FIRST); }

bool GfDataHana::isOpenCircuit(SDataBlade &dataBlade, u32 circuit) { return (dataBlade.unknown706 & 1 << circuit) != 0; }

u32 GfDataHana::getAttribute(u32 blade) {
  u32 attribute = GfDataBlade::getSDataBlade(blade)->unknown68c.unknown02;
  if (attribute == 0) {
    return 0;
  }

  return GfBdatItem::get()->getITM_HanaAtrAtr(attribute);
}

u16 GfDataHana::getArtsEnhance(u32 blade, u32 slot) { return GfDataBlade::getSDataBlade(blade)->unknown68c.unknown04[slot].unknown00; }

EquipHana *GfDataHana::getEquipParts(u32 blade) { return &GfDataBlade::getSDataBlade(blade)->unknown68c; }

u32 GfDataHana::getParmor(u32 blade) {
  u32 role = getEquipParts(blade)->unknown00;
  GfBdatItem *bdatItem = GfBdatItem::get();
  return bdatItem->getITM_HanaRolePArmor(role);
}

u32 GfDataHana::getEarmor(u32 blade) {
  u32 role = getEquipParts(blade)->unknown00;
  GfBdatItem *bdatItem = GfBdatItem::get();
  return bdatItem->getITM_HanaRoleEArmor(role);
}

u32 GfDataHana::getHpMaxRev(u32 blade) {
  u32 role = getEquipParts(blade)->unknown00;
  GfBdatItem *bdatItem = GfBdatItem::get();
  return bdatItem->getITM_HanaRoleHpMaxRev(role);
}

u32 GfDataHana::getStrengthRev(u32 blade) {
  u32 role = getEquipParts(blade)->unknown00;
  GfBdatItem *bdatItem = GfBdatItem::get();
  return bdatItem->getITM_HanaRoleStrengthRev(role);
}

u32 GfDataHana::getPowerEtherRev(u32 blade) {
  u32 role = getEquipParts(blade)->unknown00;
  GfBdatItem *bdatItem = GfBdatItem::get();
  return bdatItem->getITM_HanaRolePowEtherRev(role);
}

u32 GfDataHana::getDexRev(u32 blade) {
  u32 role = getEquipParts(blade)->unknown00;
  GfBdatItem *bdatItem = GfBdatItem::get();
  return bdatItem->getITM_HanaRoleDexRev(role);
}

u32 GfDataHana::getAgilityRev(u32 blade) {
  u32 role = getEquipParts(blade)->unknown00;
  GfBdatItem *bdatItem = GfBdatItem::get();
  return bdatItem->getITM_HanaRoleAgilityRev(role);
}

u32 GfDataHana::getLuckRev(u32 blade) {
  u32 role = getEquipParts(blade)->unknown00;
  GfBdatItem *bdatItem = GfBdatItem::get();
  return bdatItem->getITM_HanaRoleLuckRev(role);
}

u32 GfDataHana::getEther() { return GfDataManager::getDataGame()->unknown10ad3c; }

void GfDataHana::setEther(u32 ether) { GfDataManager::getDataGame()->unknown10ad3c = ether; }

u32 GfDataHana::getNartsNum(u32 blade) { return GfBdatBtl::get()->getBTL_HanaBaseNArtsNum(blade - HANA_BASE_FIRST); }

u32 GfDataHana::getNeedArtsEther(u32 blade, u32 circuit) { return GfBdatBtl::get()->getBTL_HanaBaseCircuitNum(blade - HANA_BASE_FIRST, circuit); }

u32 GfDataHana::getNeedExtendCircuitEther(u32 blade, u32 circuit) { return GfBdatBtl::get()->getBTL_HanaBaseCircuitNum(blade - HANA_BASE_FIRST, circuit + EXTEND_CIRCUIT_FIRST); }

u32 GfDataHana::getNeedRolePartsEther(u32 parts) { return GfBdatItem::get()->getITM_HanaRoleNeedEther(parts); }

u32 GfDataHana::getNeedAttributePartsEther(u32 parts) { return GfBdatItem::get()->getITM_HanaAtrNeedEther(parts); }

u32 GfDataHana::getNeedArtsPartsEther(u32 parts) { return GfBdatItem::get()->getITM_HanaArtsEnhNeedEther(parts); }

u32 GfDataHana::getNeedNArtsPartsEther(u32 parts) { return GfBdatItem::get()->getITM_HanaNArtsSetNeedEther(parts); }

u32 GfDataHana::getNeedCondenserPartsEther(u32 parts) { return GfBdatItem::get()->getITM_HanaAssistNeedEther(parts); }

u32 GfDataHana::getDefaultRoleParts(u32 blade) { return GfBdatBtl::get()->getBTL_HanaChipsetRoleParts(blade - HANA_BASE_FIRST); }

u32 GfDataHana::getDefaultAttributeParts(u32 blade) { return GfBdatBtl::get()->getBTL_HanaChipsetAtrParts(blade - HANA_BASE_FIRST); }

u32 GfDataHana::getDefaultNArtsParts(u32 blade, u32 slot) { return GfBdatBtl::get()->getBTL_HanaChipsetNArtsParts(blade - HANA_BASE_FIRST, slot); }

u32 GfDataHana::getDefaultCondenserParts(u32 blade, u32 slot) { return GfBdatBtl::get()->getBTL_HanaChipsetNCondParts(blade - HANA_BASE_FIRST, slot); }

bool GfDataHana::isOpenCircuit(u32 blade, u32 circuit) { return (GfDataBlade::getSDataBlade(blade)->unknown706 & 1 << circuit) != 0; }

void GfDataHana::setOpenCircuit(u32 blade, u32 circuit, bool openCircuit) {
  u16 mask = 1 << circuit;
  if (openCircuit) {
    GfDataBlade::getSDataBlade(blade)->unknown706 |= mask;
  } else {
    GfDataBlade::getSDataBlade(blade)->unknown706 &= ~mask;
  }
}

u32 GfDataHana::getOpenCircuitEther(u32 blade, u32 circuit) { return GfBdatBtl::get()->getBTL_HanaBaseCircuitNum(blade - HANA_BASE_FIRST, circuit); }

void GfDataHana::setEquipParts(u32 blade, const EquipHana &equipParts) { __builtin_memcpy(&GfDataBlade::getSDataBlade(blade)->unknown68c, &equipParts, sizeof(EquipHana)); }

void GfDataHana::setEquipRoleParts(u32 blade, u32 parts, GfItemHandle handle) {
  SDataBlade *dataBlade = GfDataBlade::getSDataBlade(blade);
  GfItemHandle roleHandle = handle;
  dataBlade->unknown68c.unknown00 = parts;
  dataBlade->unknown68c.unknown58 = roleHandle;
}

u32 GfDataHana::getAutoHate(u32 blade) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  return bdatItem->getITM_HanaRoleAutoHate(GfDataBlade::getSDataBlade(blade)->unknown68c.unknown00);
}

u32 GfDataHana::getArtsHate(u32 blade) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  return bdatItem->getITM_HanaRoleArtsHate(GfDataBlade::getSDataBlade(blade)->unknown68c.unknown00);
}

void GfDataHana::setEquipAttributeParts(u32 blade, u32 parts, GfItemHandle handle) {
  SDataBlade *dataBlade = GfDataBlade::getSDataBlade(blade);
  GfItemHandle attributeHandle = handle;
  dataBlade->unknown68c.unknown02 = parts;
  dataBlade->unknown68c.unknown5c = attributeHandle;
}

void GfDataHana::setEquipArtsParts(u32 blade, u32 slot, u32 parts, GfItemHandle handle) {
  SDataBlade *dataBlade = GfDataBlade::getSDataBlade(blade);
  GfItemHandle artsHandle = handle;
  EquipHanaArts &arts = dataBlade->unknown68c.unknown04[slot];
  arts.unknown04 = parts;
  arts.unknown0a = artsHandle.value;
  arts.unknown00 = GfBdatItem::get()->getITM_HanaArtsEnhEnhance(parts);
}

void GfDataHana::getEquipCondenserParts(mm::mtl::FixedArray<u16, 3> &condenser, u32 blade) { condenser = GfDataBlade::getSDataBlade(blade)->unknown68c.unknown4c; }

void GfDataHana::setEquipCondenserParts(u32 blade, u32 slot, u32 parts, GfItemHandle handle) {
  SDataBlade *dataBlade = GfDataBlade::getSDataBlade(blade);
  GfItemHandle condenserHandle = handle;
  dataBlade->unknown68c.unknown4c[slot] = parts;
  dataBlade->unknown68c.unknown60[slot] = condenserHandle;
}

bool GfDataHana::getEquipExtendCondenserParts(mm::mtl::FixedArray<u16, 3> &extendCondenser, u32 blade) {
  extendCondenser = GfDataBlade::getSDataBlade(blade)->unknown68c.unknown52;
  return true;
}

void GfDataHana::setEquipExtendCondenserParts(u32 blade, u32 slot, u32 parts, GfItemHandle handle) {
  SDataBlade *dataBlade = GfDataBlade::getSDataBlade(blade);
  GfItemHandle extendCondenserHandle = handle;
  dataBlade->unknown68c.unknown52[slot] = parts;
  dataBlade->unknown68c.unknown6c[slot] = extendCondenserHandle;
}

u32 GfDataHana::getEquipPowerRank(u32 blade) { return GfDataBlade::getSDataBlade(blade)->unknown704; }

u16 GfDataHana::getEquipPowerRank(const SDataBlade &dataBlade) { return dataBlade.unknown704; }

void GfDataHana::setEquipPowerRank(u32 blade, u32 equipPowerRank) { GfDataBlade::getSDataBlade(blade)->unknown704 = equipPowerRank; }

u32 GfDataHana::getPowerCapacity(u32 blade) {
  u32 equipPowerRank = GfDataBlade::getSDataBlade(blade)->unknown704;
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  return bdatBattle->getBTL_HanaPowerPowerNum(equipPowerRank, blade - BLADE_HANA_JS);
}

u32 GfDataHana::getPowerCapacity(const SDataBlade &dataBlade) {
  u32 equipPowerRank = dataBlade.unknown704;
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  return bdatBattle->getBTL_HanaPowerPowerNum(equipPowerRank, dataBlade.unknown06 - BLADE_HANA_JS);
}

u32 GfDataHana::getPartsPower(u32 parts) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  ItemType::Type type;
  u32 index;
  ItemType::Type partsType = GfDataItem::getItemType(type, index, parts) ? type : ItemType::NONE;
  u32 power = 0;
  switch (partsType) {
  case ItemType::HANA_ROLE:
    power = bdatItem->getITM_HanaRoleNeedPow(parts);
    break;
  case ItemType::HANA_ATR:
    power = bdatItem->getITM_HanaAtrNeedPow(parts);
    break;
  case ItemType::HANA_ARTS_ENH:
    power = bdatItem->getITM_HanaArtsEnhNeedPow(parts);
    break;
  case ItemType::HANA_N_ARTS_SET:
    power = bdatItem->getITM_HanaNArtsSetNeedPow(parts);
    break;
  case ItemType::HANA_ASSIST:
    power = bdatItem->getITM_HanaAssistNeedPow(parts);
    break;
  default:
    break;
  }

  return power;
}

u32 GfDataHana::getEquipPower(u32 blade) { return getEquipPower(GfDataBlade::getSDataBlade(blade)->unknown68c); }

u32 GfDataHana::getEquipPower(const EquipHana &equipParts) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 power = 0;
  if (equipParts.unknown00 != 0) {
    power += bdatItem->getITM_HanaRoleNeedPow(equipParts.unknown00);
  }

  if (equipParts.unknown02 != 0) {
    power += bdatItem->getITM_HanaAtrNeedPow(equipParts.unknown02);
  }

  for (u32 slot = 0; slot < 3; slot++) {
    if (equipParts.unknown04[slot].unknown00 != 0) {
      power += bdatItem->getITM_HanaArtsEnhNeedPow(equipParts.unknown04[slot].unknown04);
    }
  }

  for (u32 slot = 0; slot < 3; slot++) {
    if (equipParts.unknown28[slot].unknown00 != 0) {
      power += bdatItem->getITM_HanaNArtsSetNeedPow(equipParts.unknown28[slot].unknown04);
    }
  }

  for (u32 slot = 0; slot < 3; slot++) {
    if (equipParts.unknown4c[slot] != 0) {
      power += bdatItem->getITM_HanaAssistNeedPow(equipParts.unknown4c[slot]);
    }
  }

  for (u32 slot = 0; slot < 3; slot++) {
    if (equipParts.unknown52[slot] != 0) {
      power += bdatItem->getITM_HanaAssistNeedPow(equipParts.unknown52[slot]);
    }
  }

  return power;
}

u32 GfDataHana::getEquipPower(const SDataBlade &dataBlade) { return getEquipPower(dataBlade.unknown68c); }

u16 GfDataHana::getPowerRankEther(u32 blade, u32 ether) {
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  u16 rank = GfDataBlade::getSDataBlade(blade)->unknown704;
  if (rank >= POWER_RANK_MAX) {
    return POWER_RANK_MAX;
  }

  for (;;) {
    u32 needEther = bdatBattle->getBTL_HanaPowerEtherNum(rank + 1, blade - BLADE_HANA_JS);
    if (needEther > ether) {
      break;
    }

    ether -= needEther;
  }

  return rank;
}

bool GfDataHana::isEquipRoleParts(u32 blade, u32 parts) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  switch (blade) {
  case BLADE_HANA_JS:
    return bdatItem->isITM_HanaRoleFlagJS(parts);
  case BLADE_HANA_JK:
    return bdatItem->isITM_HanaRoleFlagJK(parts);
  case BLADE_HANA_JD:
    return bdatItem->isITM_HanaRoleFlagJD(parts);
  default:
    return false;
  }
}

bool GfDataHana::isEquipAttributeParts(u32 blade, u32 parts) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  switch (blade) {
  case BLADE_HANA_JS:
    return bdatItem->isITM_HanaAtrFlagJS(parts);
  case BLADE_HANA_JK:
    return bdatItem->isITM_HanaAtrFlagJK(parts);
  case BLADE_HANA_JD:
    return bdatItem->isITM_HanaAtrFlagJD(parts);
  default:
    return false;
  }
}

bool GfDataHana::isEquipArtsParts(u32 blade, u32 parts) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  switch (blade) {
  case BLADE_HANA_JS:
    return bdatItem->isITM_HanaArtsEnhFlagJS(parts);
  case BLADE_HANA_JK:
    return bdatItem->isITM_HanaArtsEnhFlagJK(parts);
  case BLADE_HANA_JD:
    return bdatItem->isITM_HanaArtsEnhFlagJD(parts);
  default:
    return false;
  }
}

bool GfDataHana::isEquipNArtsParts(u32 blade, u32 parts) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  switch (blade) {
  case BLADE_HANA_JS:
    return bdatItem->isITM_HanaNArtsSetFlagJS(parts);
  case BLADE_HANA_JK:
    return bdatItem->isITM_HanaNArtsSetFlagJK(parts);
  case BLADE_HANA_JD:
    return bdatItem->isITM_HanaNArtsSetFlagJD(parts);
  default:
    return false;
  }
}

bool GfDataHana::isEquipCondenserParts(u32 blade, u32 parts) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  switch (blade) {
  case BLADE_HANA_JS:
    return bdatItem->isITM_HanaAssistFlagJS(parts);
  case BLADE_HANA_JK:
    return bdatItem->isITM_HanaAssistFlagJK(parts);
  case BLADE_HANA_JD:
    return bdatItem->isITM_HanaAssistFlagJD(parts);
  default:
    return false;
  }
}

const char *GfDataHana::getRoleName(u32 parts) {
  u8 *bdat;
  u32 textId;
  const char *name = getRoleName(bdat, textId, parts) ? Bdat::getMSText(bdat, textId) : nullptr;
  return name != nullptr ? name : "";
}

const char *GfDataHana::getAttributeName(u32 parts) {
  u8 *bdat;
  u32 textId;
  const char *name = getAttributeName(bdat, textId, parts) ? Bdat::getMSText(bdat, textId) : nullptr;
  return name != nullptr ? name : "";
}

const char *GfDataHana::getNArtsName(u32 parts) {
  u8 *bdat;
  u32 textId;
  const char *name = getNArtsName(bdat, textId, parts) ? Bdat::getMSText(bdat, textId) : nullptr;
  return name != nullptr ? name : "";
}

const char *GfDataHana::getArtsName(u32 parts) {
  u8 *bdat;
  u32 textId;
  const char *name = getArtsName(bdat, textId, parts) ? Bdat::getMSText(bdat, textId) : nullptr;
  return name != nullptr ? name : "";
}

const char *GfDataHana::getAssistName(u32 parts) {
  u8 *bdat;
  u32 textId;
  const char *name = getAssistName(bdat, textId, parts) ? Bdat::getMSText(bdat, textId) : nullptr;
  return name != nullptr ? name : "";
}

u32 GfDataHana::getEquipRoleItemNum(u32 blade, u32 parts) {
  u32 role = GfDataBlade::getSDataBlade(blade)->unknown68c.unknown00;
  if (role == 0) {
    return 0;
  }

  return role == parts;
}

u32 GfDataHana::getEquipAttributeItemNum(u32 blade, u32 parts) {
  u32 attribute = GfDataBlade::getSDataBlade(blade)->unknown68c.unknown02;
  if (attribute == 0) {
    return 0;
  }

  return attribute == parts;
}

} // namespace gf
