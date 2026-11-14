#include "gf/game/gf_game_util_hana.h"

#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_hana.h"
#include "gf/data/gf_data_item.h"
#include "gf/request/gf_req_scom.h"
#include "gf/util/gf_item_util.h"
#include "mm_mtl/fixed_array.h"

namespace gf {

constexpr u32 CIRCUIT_UNKNOWN_3 = 3;               // Inferred role: extend circuit first; original name unknown.
constexpr u32 RANK_UNKNOWN_20 = 20;                // Inferred role: power rank max; original name unknown.
constexpr s32 ETHER_UNKNOWN_999999999 = 999999999; // Inferred role: ether max; original name unknown.

namespace {

// Inferred role: checks whether parts can be exchanged for ether; original name unknown.
template <u32 (*getNeedEther)(u32)> RESULT_HANA unknown001(u32 parts) {
  u32 count = GfItemUtil::getItemBoxCount(parts);
  if (GfItemUtil::getEnableStock(parts) <= count) {
    return RESULT_HANA_UNKNOWN_7;
  }

  u32 needEther = getNeedEther(parts);
  return GfDataHana::getEther() < needEther ? RESULT_HANA_UNKNOWN_3 : RESULT_HANA_UNKNOWN_0;
}

// Inferred role: exchanges ether for parts; original name unknown.
template <u32 (*getNeedEther)(u32)> RESULT_HANA unknown002(u32 parts) {
  u32 count = GfItemUtil::getItemBoxCount(parts);
  if (GfItemUtil::getEnableStock(parts) <= count) {
    return RESULT_HANA_UNKNOWN_7;
  }

  u32 needEther = getNeedEther(parts);
  if (GfDataHana::getEther() < needEther) {
    return RESULT_HANA_UNKNOWN_3;
  }

  s32 rest = GfDataHana::getEther() - needEther;
  s32 ether = rest;
  if (rest > ETHER_UNKNOWN_999999999) {
    ether = ETHER_UNKNOWN_999999999;
  }

  if (rest < 0) {
    ether = 0;
  }

  GfDataHana::setEther(ether);
  GfItemUtil::addItemBox(parts, 1);
  return RESULT_HANA_UNKNOWN_0;
}

} // namespace

RESULT_HANA GfGameUtilHana::openArtsCircuit(u32 blade, u32 circuit) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  if (GfDataHana::isOpenCircuit(blade, circuit)) {
    return RESULT_HANA_UNKNOWN_1;
  }

  u32 needEther = GfDataHana::getOpenCircuitEther(blade, circuit);
  if (needEther == 0) {
    return RESULT_HANA_UNKNOWN_2;
  }

  if (needEther > GfDataHana::getEther()) {
    return RESULT_HANA_UNKNOWN_3;
  }

  GfDataHana::setEther(GfDataHana::getEther() - needEther);
  GfDataHana::setOpenCircuit(blade, circuit, true);
  return RESULT_HANA_UNKNOWN_0;
}

RESULT_HANA GfGameUtilHana::isOpenArtsCircuit(u32 blade, u32 circuit) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  return GfDataHana::isOpenCircuit(blade, circuit) ? RESULT_HANA_UNKNOWN_0 : RESULT_HANA_UNKNOWN_10;
}

u32 GfGameUtilHana::getConvertToEther(u32 parts) {
  ItemProperty property;
  GfItemUtil::getProperty(property, parts, 0);
  if (property.unknown08 >= ItemType::ITEM_TYPE_UNKNOWN_16 && property.unknown08 <= ItemType::ITEM_TYPE_UNKNOWN_20) {
    return GfItemUtil::getItemBoxCountWithoutEquip(parts);
  }
  return 0;
}

RESULT_HANA GfGameUtilHana::execConvertToEther(u32 parts) {
  ItemProperty property;
  GfItemUtil::getProperty(property, parts, 0);
  if (property.unknown08 >= ItemType::ITEM_TYPE_UNKNOWN_16 && property.unknown08 <= ItemType::ITEM_TYPE_UNKNOWN_20) {
    if (GfItemUtil::getItemBoxCountWithoutEquip(parts) == 0) {
      return RESULT_HANA_UNKNOWN_8;
    }
    GfItemUtil::addItemBox(parts, -1);
    if (property.unknown6c != 0) {
      SCOM_ADD_ETHER::create(property.unknown6c);
    }
  }
  return RESULT_HANA_UNKNOWN_0;
}

u32 GfGameUtilHana::getEmptyParts(u32 parts) {
  u32 start;
  u32 end;
  if (!GfDataItem::getItemBdatCount(start, end, GfDataItem::getItemType(parts))) {
    return 0;
  }

  u32 count = 0;
  for (u32 item = start; item < end; item++) {
    count += GfItemUtil::getItemBoxCount(item);
  }
  return GfItemUtil::getEnableStock(parts) - count;
}

u32 GfGameUtilHana::getEtherForOpenArtsCircuit(u32 blade, u32 circuit) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getOpenCircuitEther(blade, circuit);
  }

  return 0;
}

RESULT_HANA GfGameUtilHana::openCondenserCircuit(u32 blade, u32 circuit) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  u32 condenserCircuit = circuit + CIRCUIT_UNKNOWN_3;
  if (GfDataHana::isOpenCircuit(blade, condenserCircuit)) {
    return RESULT_HANA_UNKNOWN_1;
  }

  u32 needEther = GfDataHana::getOpenCircuitEther(blade, condenserCircuit);
  if (needEther == 0) {
    return RESULT_HANA_UNKNOWN_2;
  }

  if (needEther > GfDataHana::getEther()) {
    return RESULT_HANA_UNKNOWN_3;
  }

  GfDataHana::setEther(GfDataHana::getEther() - needEther);
  GfDataHana::setOpenCircuit(blade, condenserCircuit, true);
  return RESULT_HANA_UNKNOWN_0;
}

RESULT_HANA GfGameUtilHana::isOpenCondenserCircuit(u32 blade, u32 circuit) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  return GfDataHana::isOpenCircuit(blade, circuit + CIRCUIT_UNKNOWN_3) ? RESULT_HANA_UNKNOWN_0 : RESULT_HANA_UNKNOWN_10;
}

u32 GfGameUtilHana::getEtherForOpenCondenserCircuit(u32 blade, u32 circuit) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getOpenCircuitEther(blade, circuit + CIRCUIT_UNKNOWN_3);
  }

  return 0;
}

RESULT_HANA GfGameUtilHana::checkEquip(u32 blade, const EquipHana &equipParts) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  u32 power = GfDataHana::getEquipPower(equipParts);
  return GfDataHana::getPowerCapacity(blade) < power ? RESULT_HANA_UNKNOWN_5 : RESULT_HANA_UNKNOWN_0;
}

RESULT_HANA GfGameUtilHana::getEquip(EquipHana &equipParts, u32 blade) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  equipParts = *GfDataHana::getEquipParts(blade);
  return RESULT_HANA_UNKNOWN_0;
}

RESULT_HANA GfGameUtilHana::setEquip(u32 blade, const EquipHana &equipParts) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  u32 power = GfDataHana::getEquipPower(equipParts);
  if (GfDataHana::getPowerCapacity(blade) < power) {
    return RESULT_HANA_UNKNOWN_5;
  }

  GfDataHana::setEquipParts(blade, equipParts);
  return RESULT_HANA_UNKNOWN_0;
}

RESULT_HANA GfGameUtilHana::execPowerRankup(u32 blade, u32 rank) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  u32 currentRank = GfDataHana::getEquipPowerRank(blade);
  u32 ether = GfDataHana::getEther();
  if (currentRank < rank) {
    GfBdatBtl *bdatBattle = GfBdatBtl::get();
    do {
      currentRank++;
      u32 needEther = bdatBattle->getBTL_HanaPowerEtherNum(currentRank, blade - BLADE_UNKNOWN_1005);
      bool isShort = ether < needEther;
      ether -= needEther;
      if (isShort) {
        return RESULT_HANA_UNKNOWN_3;
      }

      if (rank == currentRank) {
        GfDataHana::setEquipPowerRank(blade, rank);
        GfDataHana::setEther(ether);
        return RESULT_HANA_UNKNOWN_0;
      }
    } while (currentRank < RANK_UNKNOWN_20);
  }

  return RESULT_HANA_UNKNOWN_6;
}

RESULT_HANA GfGameUtilHana::isExecPowerRankup(u32 blade, u32 rank) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  u32 currentRank = GfDataHana::getEquipPowerRank(blade);
  u32 ether = GfDataHana::getEther();
  if (currentRank < rank) {
    GfBdatBtl *bdatBattle = GfBdatBtl::get();
    do {
      currentRank++;
      u32 needEther = bdatBattle->getBTL_HanaPowerEtherNum(currentRank, blade - BLADE_UNKNOWN_1005);
      bool isShort = ether < needEther;
      ether -= needEther;
      if (isShort) {
        return RESULT_HANA_UNKNOWN_3;
      }

      if (rank == currentRank) {
        return RESULT_HANA_UNKNOWN_0;
      }
    } while (currentRank < RANK_UNKNOWN_20);
  }

  return RESULT_HANA_UNKNOWN_6;
}

u32 GfGameUtilHana::getNeedEtherForExecPowerRankup(u32 blade, u32 rank) {
  u32 currentRank = GfDataHana::getEquipPowerRank(blade);
  u32 totalEther = 0;
  if (currentRank < rank) {
    GfBdatBtl *bdatBattle = GfBdatBtl::get();
    for (u32 nextRank = currentRank + 1; nextRank <= rank; nextRank++) {
      totalEther += bdatBattle->getBTL_HanaPowerEtherNum(nextRank, blade - BLADE_UNKNOWN_1005);
    }
  }

  return totalEther;
}

u32 GfGameUtilHana::getPowerRank(u32 blade) { return GfDataHana::getEquipPowerRank(blade); }

RESULT_HANA GfGameUtilHana::exchangeRoleParts(u32 parts) { return unknown002<GfDataHana::getNeedRolePartsEther>(parts); }

RESULT_HANA GfGameUtilHana::isExchangeRoleParts(u32 parts) { return unknown001<GfDataHana::getNeedRolePartsEther>(parts); }

RESULT_HANA GfGameUtilHana::exchangeAttributeParts(u32 parts) { return unknown002<GfDataHana::getNeedAttributePartsEther>(parts); }

RESULT_HANA GfGameUtilHana::isExchangeAttributeParts(u32 parts) { return unknown001<GfDataHana::getNeedAttributePartsEther>(parts); }

RESULT_HANA GfGameUtilHana::exchangeArtsParts(u32 parts) { return unknown002<GfDataHana::getNeedArtsPartsEther>(parts); }

RESULT_HANA GfGameUtilHana::isExchangeArtsParts(u32 parts) { return unknown001<GfDataHana::getNeedArtsPartsEther>(parts); }

RESULT_HANA GfGameUtilHana::exchangeNArtsParts(u32 parts) { return unknown002<GfDataHana::getNeedNArtsPartsEther>(parts); }

RESULT_HANA GfGameUtilHana::isExchangeNArtsParts(u32 parts) { return unknown001<GfDataHana::getNeedNArtsPartsEther>(parts); }

RESULT_HANA GfGameUtilHana::exchangeCondenserParts(u32 parts) { return unknown002<GfDataHana::getNeedCondenserPartsEther>(parts); }

RESULT_HANA GfGameUtilHana::isExchangeCondenserParts(u32 parts) { return unknown001<GfDataHana::getNeedCondenserPartsEther>(parts); }

RESULT_HANA GfGameUtilHana::isEnableEquipRoleParts(u32 blade, u32 parts) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  if (!GfDataHana::isEquipRoleParts(blade, parts)) {
    return RESULT_HANA_UNKNOWN_12;
  }

  if (GfItemUtil::getItemBoxCount(parts) == 0) {
    return RESULT_HANA_UNKNOWN_8;
  }

  GfItemHandle handle = GfItemUtil::getNoEquipItemHandle(parts);
  if (handle.value == 0) {
    return RESULT_HANA_UNKNOWN_9;
  }

  EquipHana equipParts = *GfDataHana::getEquipParts(blade);
  equipParts.unknown00 = parts;
  equipParts.unknown58 = handle.value;
  return checkEquip(blade, equipParts);
}

RESULT_HANA GfGameUtilHana::isEnableEquipAttributeParts(u32 blade, u32 parts) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  if (!GfDataHana::isEquipAttributeParts(blade, parts)) {
    return RESULT_HANA_UNKNOWN_12;
  }

  if (GfItemUtil::getItemBoxCount(parts) == 0) {
    return RESULT_HANA_UNKNOWN_8;
  }

  GfItemHandle handle = GfItemUtil::getNoEquipItemHandle(parts);
  if (handle.value == 0) {
    return RESULT_HANA_UNKNOWN_9;
  }

  EquipHana equipParts = *GfDataHana::getEquipParts(blade);
  equipParts.unknown02 = parts;
  equipParts.unknown5c = handle.value;
  return checkEquip(blade, equipParts);
}

RESULT_HANA GfGameUtilHana::isEnableEquipArtsParts(u32 blade, u32 parts, u32 slot) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  if (!GfDataHana::isEquipArtsParts(blade, parts)) {
    return RESULT_HANA_UNKNOWN_12;
  }

  if (GfItemUtil::getItemBoxCount(parts) == 0) {
    return RESULT_HANA_UNKNOWN_8;
  }

  GfItemHandle handle = GfItemUtil::getNoEquipItemHandle(parts);
  if (handle.value == 0) {
    return RESULT_HANA_UNKNOWN_9;
  }

  EquipHana equipParts = *GfDataHana::getEquipParts(blade);
  equipParts.setArtsParts(parts, handle.value, slot);
  return checkEquip(blade, equipParts);
}

RESULT_HANA GfGameUtilHana::isEnableEquipNArtsParts(u32 blade, u32 parts, u32 slot) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  if (!GfDataHana::isEquipNArtsParts(blade, parts)) {
    return RESULT_HANA_UNKNOWN_12;
  }

  if (GfItemUtil::getItemBoxCount(parts) == 0) {
    return RESULT_HANA_UNKNOWN_8;
  }

  GfItemHandle handle = GfItemUtil::getNoEquipItemHandle(parts);
  if (handle.value == 0) {
    return RESULT_HANA_UNKNOWN_9;
  }

  if (GfDataHana::isExistSameEffectNArtsParts(blade, parts, slot)) {
    return RESULT_HANA_UNKNOWN_13;
  }

  EquipHana equipParts = *GfDataHana::getEquipParts(blade);
  equipParts.setNArtsParts(parts, handle.value, slot);
  return checkEquip(blade, equipParts);
}

RESULT_HANA GfGameUtilHana::isEnableEquipCondenserParts(u32 blade, u32 parts, u32 slot) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  if (!GfDataHana::isEquipCondenserParts(blade, parts)) {
    return RESULT_HANA_UNKNOWN_12;
  }

  if (GfDataHana::isExistSameEffectCondenserParts(blade, parts, slot, false)) {
    return RESULT_HANA_UNKNOWN_13;
  }

  if (GfItemUtil::getItemBoxCount(parts) == 0) {
    return RESULT_HANA_UNKNOWN_8;
  }

  GfItemHandle handle = GfItemUtil::getNoEquipItemHandle(parts);
  if (handle.value == 0) {
    return RESULT_HANA_UNKNOWN_9;
  }

  EquipHana equipParts = *GfDataHana::getEquipParts(blade);
  equipParts.unknown001(parts, handle.value, slot);
  return checkEquip(blade, equipParts);
}

RESULT_HANA GfGameUtilHana::isEnableEquipExtendCondenserParts(u32 blade, u32 parts, u32 slot) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  if (!GfDataHana::isEquipCondenserParts(blade, parts)) {
    return RESULT_HANA_UNKNOWN_12;
  }

  if (GfDataHana::isExistSameEffectCondenserParts(blade, parts, slot, true)) {
    return RESULT_HANA_UNKNOWN_13;
  }

  if (GfItemUtil::getItemBoxCount(parts) == 0) {
    return RESULT_HANA_UNKNOWN_8;
  }

  GfItemHandle handle = GfItemUtil::getNoEquipItemHandle(parts);
  if (handle.value == 0) {
    return RESULT_HANA_UNKNOWN_9;
  }

  EquipHana equipParts = *GfDataHana::getEquipParts(blade);
  equipParts.unknown002(parts, handle.value, slot);
  return checkEquip(blade, equipParts);
}

RESULT_HANA GfGameUtilHana::execEquipRoleParts(u32 blade, u32 parts, GfItemHandle handle) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  if (parts == 0) {
    return RESULT_HANA_UNKNOWN_11;
  }

  EquipHana equipParts = *GfDataHana::getEquipParts(blade);
  u16 oldParts = equipParts.unknown00;
  u32 oldHandle = equipParts.unknown58;
  if (GfItemUtil::getItemBoxCount(parts) == 0) {
    return RESULT_HANA_UNKNOWN_8;
  }

  if (handle.value == 0) {
    handle = GfItemUtil::getNoEquipItemHandle(parts);
    if (handle.value == 0) {
      return RESULT_HANA_UNKNOWN_9;
    }
  }

  equipParts.unknown00 = parts;
  equipParts.unknown58 = handle.value;
  if (GfDataHana::isValid(blade)) {
    u32 power = GfDataHana::getEquipPower(equipParts);
    if (GfDataHana::getPowerCapacity(blade) < power) {
      return RESULT_HANA_UNKNOWN_5;
    }
  }

  GfItemUtil::setEquipFlag(parts, handle, true);
  if (oldParts != 0) {
    if (oldHandle == 0) {
      GfItemUtil::addItemBox(oldParts, 1);
    } else {
      GfItemUtil::setEquipFlag(oldParts, oldHandle, false);
    }
  }

  GfDataHana::setEquipParts(blade, equipParts);
  return RESULT_HANA_UNKNOWN_0;
}

RESULT_HANA GfGameUtilHana::execEquipAttributeParts(u32 blade, u32 parts, GfItemHandle handle) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  if (parts == 0) {
    return RESULT_HANA_UNKNOWN_11;
  }

  EquipHana equipParts = *GfDataHana::getEquipParts(blade);
  u16 oldParts = equipParts.unknown02;
  u32 oldHandle = equipParts.unknown5c;
  if (GfItemUtil::getItemBoxCount(parts) == 0) {
    return RESULT_HANA_UNKNOWN_8;
  }

  if (handle.value == 0) {
    handle = GfItemUtil::getNoEquipItemHandle(parts);
    if (handle.value == 0) {
      return RESULT_HANA_UNKNOWN_9;
    }
  }

  equipParts.unknown02 = parts;
  equipParts.unknown5c = handle.value;
  if (GfDataHana::isValid(blade)) {
    u32 power = GfDataHana::getEquipPower(equipParts);
    if (GfDataHana::getPowerCapacity(blade) < power) {
      return RESULT_HANA_UNKNOWN_5;
    }
  }

  GfItemUtil::setEquipFlag(parts, handle, true);
  if (oldParts != 0) {
    if (oldHandle == 0) {
      GfItemUtil::addItemBox(oldParts, 1);
    } else {
      GfItemUtil::setEquipFlag(oldParts, oldHandle, false);
    }
  }

  GfDataHana::setEquipParts(blade, equipParts);
  return RESULT_HANA_UNKNOWN_0;
}

RESULT_HANA GfGameUtilHana::execEquipArtsParts(u32 blade, u32 parts, GfItemHandle handle, u32 slot) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  EquipHana equipParts = *GfDataHana::getEquipParts(blade);
  u16 oldParts = equipParts.unknown04[slot].unknown04;
  u16 oldHandle = equipParts.unknown04[slot].unknown0a;
  if (parts != 0) {
    if (GfItemUtil::getItemBoxCount(parts) == 0) {
      return RESULT_HANA_UNKNOWN_8;
    }

    if (handle.value == 0) {
      handle = GfItemUtil::getNoEquipItemHandle(parts);
      if (handle.value == 0) {
        return RESULT_HANA_UNKNOWN_9;
      }
    }
  }

  equipParts.setArtsParts(parts, handle.value, slot);
  if (GfDataHana::isValid(blade)) {
    u32 power = GfDataHana::getEquipPower(equipParts);
    if (GfDataHana::getPowerCapacity(blade) < power) {
      return RESULT_HANA_UNKNOWN_5;
    }
  }

  if (parts != 0) {
    GfItemUtil::setEquipFlag(parts, handle, true);
  }

  if (oldParts != 0) {
    if (oldHandle == 0) {
      GfItemUtil::addItemBox(oldParts, 1);
    } else {
      GfItemUtil::setEquipFlag(oldParts, oldHandle, false);
    }
  }

  GfDataHana::setEquipParts(blade, equipParts);
  return RESULT_HANA_UNKNOWN_0;
}

RESULT_HANA GfGameUtilHana::execEquipNArtsParts(u32 blade, u32 parts, GfItemHandle handle, u32 slot) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  EquipHana equipParts = *GfDataHana::getEquipParts(blade);
  u16 oldParts = equipParts.unknown28[slot].unknown04;
  u16 oldHandle = equipParts.unknown28[slot].unknown0a;
  if (parts != 0) {
    if (GfItemUtil::getItemBoxCount(parts) == 0) {
      return RESULT_HANA_UNKNOWN_8;
    }

    if (handle.value == 0) {
      handle = GfItemUtil::getNoEquipItemHandle(parts);
      if (handle.value == 0) {
        return RESULT_HANA_UNKNOWN_9;
      }
    }
  }

  equipParts.setNArtsParts(parts, handle.value, slot);
  if (GfDataHana::isValid(blade)) {
    u32 power = GfDataHana::getEquipPower(equipParts);
    if (GfDataHana::getPowerCapacity(blade) < power) {
      return RESULT_HANA_UNKNOWN_5;
    }
  }

  if (parts != 0) {
    GfItemUtil::setEquipFlag(parts, handle, true);
  }

  if (oldParts != 0) {
    if (oldHandle == 0) {
      GfItemUtil::addItemBox(oldParts, 1);
    } else {
      GfItemUtil::setEquipFlag(oldParts, oldHandle, false);
    }
  }

  GfDataHana::setEquipParts(blade, equipParts);
  return RESULT_HANA_UNKNOWN_0;
}

RESULT_HANA GfGameUtilHana::execEquipCondenserParts(u32 blade, u32 parts, GfItemHandle handle, u32 slot) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  EquipHana equipParts = *GfDataHana::getEquipParts(blade);
  u16 oldParts = equipParts.unknown4c[slot];
  u16 oldHandle = equipParts.unknown60[slot];
  if (parts != 0) {
    if (GfItemUtil::getItemBoxCount(parts) == 0) {
      return RESULT_HANA_UNKNOWN_8;
    }

    if (handle.value == 0) {
      handle = GfItemUtil::getNoEquipItemHandle(parts);
      if (handle.value == 0) {
        return RESULT_HANA_UNKNOWN_9;
      }
    }
  }

  equipParts.unknown001(parts, handle.value, slot);
  if (GfDataHana::isValid(blade)) {
    u32 power = GfDataHana::getEquipPower(equipParts);
    if (GfDataHana::getPowerCapacity(blade) < power) {
      return RESULT_HANA_UNKNOWN_5;
    }
  }

  if (parts != 0) {
    GfItemUtil::setEquipFlag(parts, handle, true);
  }

  if (oldParts != 0) {
    if (oldHandle == 0) {
      GfItemUtil::addItemBox(oldParts, 1);
    } else {
      GfItemUtil::setEquipFlag(oldParts, oldHandle, false);
    }
  }

  GfDataHana::setEquipParts(blade, equipParts);
  return RESULT_HANA_UNKNOWN_0;
}

RESULT_HANA GfGameUtilHana::execEquipExtendCondenserParts(u32 blade, u32 parts, GfItemHandle handle, u32 slot) {
  if (!GfDataHana::isValid(blade)) {
    return RESULT_HANA_UNKNOWN_4;
  }

  EquipHana equipParts = *GfDataHana::getEquipParts(blade);
  u16 oldParts = equipParts.unknown52[slot];
  u16 oldHandle = equipParts.unknown6c[slot];
  if (parts != 0) {
    if (GfItemUtil::getItemBoxCount(parts) == 0) {
      return RESULT_HANA_UNKNOWN_8;
    }

    if (handle.value == 0) {
      handle = GfItemUtil::getNoEquipItemHandle(parts);
      if (handle.value == 0) {
        return RESULT_HANA_UNKNOWN_9;
      }
    }
  }

  equipParts.unknown002(parts, handle.value, slot);
  if (GfDataHana::isValid(blade)) {
    u32 power = GfDataHana::getEquipPower(equipParts);
    if (GfDataHana::getPowerCapacity(blade) < power) {
      return RESULT_HANA_UNKNOWN_5;
    }
  }

  if (parts != 0) {
    GfItemUtil::setEquipFlag(parts, handle, true);
  }

  if (oldParts != 0) {
    if (oldHandle == 0) {
      GfItemUtil::addItemBox(oldParts, 1);
    } else {
      GfItemUtil::setEquipFlag(oldParts, oldHandle, false);
    }
  }

  GfDataHana::setEquipParts(blade, equipParts);
  return RESULT_HANA_UNKNOWN_0;
}

void GfGameUtilHana::setupDefaultParts(u32 blade) {
  if (!GfDataHana::isValid(blade) || GfDataBlade::getSDataBlade(blade).unknown68c.unknown00 != 0) {
    return;
  }

  u32 rolePartsId = GfDataHana::getDefaultRoleParts(blade);
  if (rolePartsId != 0) {
    GfItemUtil::addItemBox(rolePartsId, 1);
    execEquipRoleParts(blade, rolePartsId, GfItemUtil::getNoEquipItemHandle(rolePartsId));
  }

  u32 attributePartsId = GfDataHana::getDefaultAttributeParts(blade);
  if (attributePartsId != 0) {
    GfItemUtil::addItemBox(attributePartsId, 1);
    execEquipAttributeParts(blade, attributePartsId, GfItemUtil::getNoEquipItemHandle(attributePartsId));
  }

  for (u32 slot = 0; slot < GfDataHana::getNartsNum(blade); slot++) {
    u32 nartsParts = GfDataHana::getDefaultNArtsParts(blade, slot);
    if (nartsParts != 0) {
      GfItemUtil::addItemBox(nartsParts, 1);
      execEquipNArtsParts(blade, nartsParts, GfItemUtil::getNoEquipItemHandle(nartsParts), slot);
    }
  }

  for (u32 slot = 0; slot < GfDataHana::getCondenserNum(blade); slot++) {
    u32 condenserParts = GfDataHana::getDefaultCondenserParts(blade, slot);
    if (condenserParts != 0) {
      GfItemUtil::addItemBox(condenserParts, 1);
      execEquipCondenserParts(blade, condenserParts, GfItemUtil::getNoEquipItemHandle(condenserParts), slot);
    }
  }
}

} // namespace gf
