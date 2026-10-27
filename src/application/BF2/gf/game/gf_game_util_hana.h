#pragma once
#include "types.h"

namespace gf {

struct EquipHana;

// Inferred role: result codes of the GfGameUtilHana circuit, rank and exchange functions; original enum and enumerator names unknown.
enum unknown003 {
  unknown003_0 = 0,
  unknown003_1 = 1,
  unknown003_2 = 2,
  unknown003_3 = 3,
  unknown003_4 = 4,
  unknown003_5 = 5,
  unknown003_6 = 6,
  unknown003_7 = 7,
  unknown003_10 = 10,
};

class GfGameUtilHana {
public:
  static void setupDefaultParts(u32 blade);
  static u32 openArtsCircuit(u32 blade, u32 circuit);
  static u32 isOpenArtsCircuit(u32 blade, u32 circuit);
  static u32 getConvertToEther(u32 parts);
  static u32 getEtherForOpenArtsCircuit(u32 blade, u32 circuit);
  static u32 openCondenserCircuit(u32 blade, u32 circuit);
  static u32 isOpenCondenserCircuit(u32 blade, u32 circuit);
  static u32 getEtherForOpenCondenserCircuit(u32 blade, u32 circuit);
  static u32 checkEquip(u32 blade, const EquipHana &equipParts);
  static u32 getEquip(EquipHana &equipParts, u32 blade);
  static u32 setEquip(u32 blade, const EquipHana &equipParts);
  static u32 execPowerRankup(u32 blade, u32 rank);
  static u32 isExecPowerRankup(u32 blade, u32 rank);
  static u32 getNeedEtherForExecPowerRankup(u32 blade, u32 rank);
  static u32 getPowerRank(u32 blade);
  static u32 exchangeRoleParts(u32 parts);
  static u32 isExchangeRoleParts(u32 parts);
  static u32 exchangeAttributeParts(u32 parts);
  static u32 isExchangeAttributeParts(u32 parts);
  static u32 exchangeArtsParts(u32 parts);
  static u32 isExchangeArtsParts(u32 parts);
  static u32 exchangeNArtsParts(u32 parts);
  static u32 isExchangeNArtsParts(u32 parts);
  static u32 exchangeCondenserParts(u32 parts);
  static u32 isExchangeCondenserParts(u32 parts);
};

} // namespace gf
