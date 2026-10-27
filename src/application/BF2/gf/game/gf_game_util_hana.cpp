#include "gf/game/gf_game_util_hana.h"

#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_hana.h"
#include "gf/util/gf_item_util.h"

namespace gf {

constexpr u32 EXTEND_CIRCUIT_FIRST = 3;
constexpr u32 POWER_RANK_MAX = 20;
constexpr s32 ETHER_MAX = 999999999;

namespace {

// Inferred role: checks whether parts can be exchanged for ether; original name unknown.
template <u32 (*getNeedEther)(u32)> u32 unknown001(u32 parts) {
  u32 count = GfItemUtil::getItemBoxCount(parts);
  if (GfItemUtil::getEnableStock(parts) <= count) {
    return unknown003_7;
  }

  u32 needEther = getNeedEther(parts);
  return GfDataHana::getEther() < needEther ? unknown003_3 : unknown003_0;
}

// Inferred role: exchanges ether for parts; original name unknown.
template <u32 (*getNeedEther)(u32)> u32 unknown002(u32 parts) {
  u32 count = GfItemUtil::getItemBoxCount(parts);
  if (GfItemUtil::getEnableStock(parts) <= count) {
    return unknown003_7;
  }

  u32 needEther = getNeedEther(parts);
  if (GfDataHana::getEther() < needEther) {
    return unknown003_3;
  }

  s32 rest = GfDataHana::getEther() - needEther;
  s32 ether = rest;
  if (rest > ETHER_MAX) {
    ether = ETHER_MAX;
  }

  if (rest < 0) {
    ether = 0;
  }

  GfDataHana::setEther(ether);
  GfItemUtil::addItemBox(parts, 1);
  return unknown003_0;
}

} // namespace

u32 GfGameUtilHana::openArtsCircuit(u32 blade, u32 circuit) {
  if (!GfDataHana::isValid(blade)) {
    return unknown003_4;
  }

  if (GfDataHana::isOpenCircuit(blade, circuit)) {
    return unknown003_1;
  }

  u32 needEther = GfDataHana::getOpenCircuitEther(blade, circuit);
  if (needEther == 0) {
    return unknown003_2;
  }

  if (needEther > GfDataHana::getEther()) {
    return unknown003_3;
  }

  GfDataHana::setEther(GfDataHana::getEther() - needEther);
  GfDataHana::setOpenCircuit(blade, circuit, true);
  return unknown003_0;
}

u32 GfGameUtilHana::isOpenArtsCircuit(u32 blade, u32 circuit) {
  if (!GfDataHana::isValid(blade)) {
    return unknown003_4;
  }

  return GfDataHana::isOpenCircuit(blade, circuit) ? unknown003_0 : unknown003_10;
}

u32 GfGameUtilHana::getEtherForOpenArtsCircuit(u32 blade, u32 circuit) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getOpenCircuitEther(blade, circuit);
  }

  return 0;
}

u32 GfGameUtilHana::openCondenserCircuit(u32 blade, u32 circuit) {
  if (!GfDataHana::isValid(blade)) {
    return unknown003_4;
  }

  u32 condenserCircuit = circuit + EXTEND_CIRCUIT_FIRST;
  if (GfDataHana::isOpenCircuit(blade, condenserCircuit)) {
    return unknown003_1;
  }

  u32 needEther = GfDataHana::getOpenCircuitEther(blade, condenserCircuit);
  if (needEther == 0) {
    return unknown003_2;
  }

  if (needEther > GfDataHana::getEther()) {
    return unknown003_3;
  }

  GfDataHana::setEther(GfDataHana::getEther() - needEther);
  GfDataHana::setOpenCircuit(blade, condenserCircuit, true);
  return unknown003_0;
}

u32 GfGameUtilHana::isOpenCondenserCircuit(u32 blade, u32 circuit) {
  if (!GfDataHana::isValid(blade)) {
    return unknown003_4;
  }

  return GfDataHana::isOpenCircuit(blade, circuit + EXTEND_CIRCUIT_FIRST) ? unknown003_0 : unknown003_10;
}

u32 GfGameUtilHana::getEtherForOpenCondenserCircuit(u32 blade, u32 circuit) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getOpenCircuitEther(blade, circuit + EXTEND_CIRCUIT_FIRST);
  }

  return 0;
}

u32 GfGameUtilHana::checkEquip(u32 blade, const EquipHana &equipParts) {
  if (!GfDataHana::isValid(blade)) {
    return unknown003_4;
  }

  u32 power = GfDataHana::getEquipPower(equipParts);
  return GfDataHana::getPowerCapacity(blade) < power ? unknown003_5 : unknown003_0;
}

u32 GfGameUtilHana::getEquip(EquipHana &equipParts, u32 blade) {
  if (!GfDataHana::isValid(blade)) {
    return unknown003_4;
  }

  equipParts = *GfDataHana::getEquipParts(blade);
  return unknown003_0;
}

u32 GfGameUtilHana::setEquip(u32 blade, const EquipHana &equipParts) {
  if (!GfDataHana::isValid(blade)) {
    return unknown003_4;
  }

  u32 power = GfDataHana::getEquipPower(equipParts);
  if (GfDataHana::getPowerCapacity(blade) < power) {
    return unknown003_5;
  }

  GfDataHana::setEquipParts(blade, equipParts);
  return unknown003_0;
}

u32 GfGameUtilHana::execPowerRankup(u32 blade, u32 rank) {
  if (!GfDataHana::isValid(blade)) {
    return unknown003_4;
  }

  u32 currentRank = GfDataHana::getEquipPowerRank(blade);
  u32 ether = GfDataHana::getEther();
  if (currentRank < rank) {
    GfBdatBtl *bdatBattle = GfBdatBtl::get();
    do {
      currentRank++;
      u32 needEther = bdatBattle->getBTL_HanaPowerEtherNum(currentRank, blade - BLADE_HANA_JS);
      bool isShort = ether < needEther;
      ether -= needEther;
      if (isShort) {
        return unknown003_3;
      }

      if (rank == currentRank) {
        GfDataHana::setEquipPowerRank(blade, rank);
        GfDataHana::setEther(ether);
        return unknown003_0;
      }
    } while (currentRank < POWER_RANK_MAX);
  }

  return unknown003_6;
}

u32 GfGameUtilHana::isExecPowerRankup(u32 blade, u32 rank) {
  if (!GfDataHana::isValid(blade)) {
    return unknown003_4;
  }

  u32 currentRank = GfDataHana::getEquipPowerRank(blade);
  u32 ether = GfDataHana::getEther();
  if (currentRank < rank) {
    GfBdatBtl *bdatBattle = GfBdatBtl::get();
    do {
      currentRank++;
      u32 needEther = bdatBattle->getBTL_HanaPowerEtherNum(currentRank, blade - BLADE_HANA_JS);
      bool isShort = ether < needEther;
      ether -= needEther;
      if (isShort) {
        return unknown003_3;
      }

      if (rank == currentRank) {
        return unknown003_0;
      }
    } while (currentRank < POWER_RANK_MAX);
  }

  return unknown003_6;
}

u32 GfGameUtilHana::getNeedEtherForExecPowerRankup(u32 blade, u32 rank) {
  u32 currentRank = GfDataHana::getEquipPowerRank(blade);
  u32 totalEther = 0;
  if (currentRank < rank) {
    GfBdatBtl *bdatBattle = GfBdatBtl::get();
    for (u32 nextRank = currentRank + 1; nextRank <= rank; nextRank++) {
      totalEther += bdatBattle->getBTL_HanaPowerEtherNum(nextRank, blade - BLADE_HANA_JS);
    }
  }

  return totalEther;
}

u32 GfGameUtilHana::getPowerRank(u32 blade) { return GfDataHana::getEquipPowerRank(blade); }

u32 GfGameUtilHana::exchangeRoleParts(u32 parts) { return unknown002<GfDataHana::getNeedRolePartsEther>(parts); }

u32 GfGameUtilHana::isExchangeRoleParts(u32 parts) { return unknown001<GfDataHana::getNeedRolePartsEther>(parts); }

u32 GfGameUtilHana::exchangeAttributeParts(u32 parts) { return unknown002<GfDataHana::getNeedAttributePartsEther>(parts); }

u32 GfGameUtilHana::isExchangeAttributeParts(u32 parts) { return unknown001<GfDataHana::getNeedAttributePartsEther>(parts); }

u32 GfGameUtilHana::exchangeArtsParts(u32 parts) { return unknown002<GfDataHana::getNeedArtsPartsEther>(parts); }

u32 GfGameUtilHana::isExchangeArtsParts(u32 parts) { return unknown001<GfDataHana::getNeedArtsPartsEther>(parts); }

u32 GfGameUtilHana::exchangeNArtsParts(u32 parts) { return unknown002<GfDataHana::getNeedNArtsPartsEther>(parts); }

u32 GfGameUtilHana::isExchangeNArtsParts(u32 parts) { return unknown001<GfDataHana::getNeedNArtsPartsEther>(parts); }

u32 GfGameUtilHana::exchangeCondenserParts(u32 parts) { return unknown002<GfDataHana::getNeedCondenserPartsEther>(parts); }

u32 GfGameUtilHana::isExchangeCondenserParts(u32 parts) { return unknown001<GfDataHana::getNeedCondenserPartsEther>(parts); }

} // namespace gf
