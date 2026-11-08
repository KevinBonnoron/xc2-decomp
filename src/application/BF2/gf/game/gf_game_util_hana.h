#pragma once
#include "gf/data/gf_item_handle.h"
#include "types.h"

namespace gf {

struct EquipHana;

// Result codes of the GfGameUtilHana circuit, rank and exchange functions and of the GfMenuHanaAdapter checks.
enum RESULT_HANA {
  RESULT_HANA_UNKNOWN_0 = 0,   // Inferred role: success; original enumerator name unknown.
  RESULT_HANA_UNKNOWN_1 = 1,   // Inferred role: circuit already open; original enumerator name unknown.
  RESULT_HANA_UNKNOWN_2 = 2,   // Inferred role: circuit has no open cost; original enumerator name unknown.
  RESULT_HANA_UNKNOWN_3 = 3,   // Inferred role: not enough ether; original enumerator name unknown.
  RESULT_HANA_UNKNOWN_4 = 4,   // Inferred role: invalid blade; original enumerator name unknown.
  RESULT_HANA_UNKNOWN_5 = 5,   // Inferred role: power over capacity or condition not met; original enumerator name unknown.
  RESULT_HANA_UNKNOWN_6 = 6,   // Inferred role: rank unreachable or unsupported type; original enumerator name unknown.
  RESULT_HANA_UNKNOWN_7 = 7,   // Inferred role: stock full; original enumerator name unknown.
  RESULT_HANA_UNKNOWN_8 = 8,   // Inferred role: no item owned; original enumerator name unknown.
  RESULT_HANA_UNKNOWN_10 = 10, // Inferred role: circuit not open; original enumerator name unknown.
};

class GfGameUtilHana {
public:
  static void setupDefaultParts(u32 blade);
  static RESULT_HANA openArtsCircuit(u32 blade, u32 circuit);
  static RESULT_HANA isOpenArtsCircuit(u32 blade, u32 circuit);
  static u32 getConvertToEther(u32 parts);
  static RESULT_HANA execConvertToEther(u32 parts);
  static u32 getEmptyParts(u32 parts);
  static u32 getEtherForOpenArtsCircuit(u32 blade, u32 circuit);
  static RESULT_HANA openCondenserCircuit(u32 blade, u32 circuit);
  static RESULT_HANA isOpenCondenserCircuit(u32 blade, u32 circuit);
  static u32 getEtherForOpenCondenserCircuit(u32 blade, u32 circuit);
  static RESULT_HANA checkEquip(u32 blade, const EquipHana &equipParts);
  static RESULT_HANA getEquip(EquipHana &equipParts, u32 blade);
  static RESULT_HANA setEquip(u32 blade, const EquipHana &equipParts);
  static RESULT_HANA execPowerRankup(u32 blade, u32 rank);
  static RESULT_HANA isExecPowerRankup(u32 blade, u32 rank);
  static u32 getNeedEtherForExecPowerRankup(u32 blade, u32 rank);
  static u32 getPowerRank(u32 blade);
  static RESULT_HANA exchangeRoleParts(u32 parts);
  static RESULT_HANA isExchangeRoleParts(u32 parts);
  static RESULT_HANA exchangeAttributeParts(u32 parts);
  static RESULT_HANA isExchangeAttributeParts(u32 parts);
  static RESULT_HANA exchangeArtsParts(u32 parts);
  static RESULT_HANA isExchangeArtsParts(u32 parts);
  static RESULT_HANA exchangeNArtsParts(u32 parts);
  static RESULT_HANA isExchangeNArtsParts(u32 parts);
  static RESULT_HANA exchangeCondenserParts(u32 parts);
  static RESULT_HANA isExchangeCondenserParts(u32 parts);
  static RESULT_HANA isEnableEquipRoleParts(u32 blade, u32 parts);
  static RESULT_HANA isEnableEquipAttributeParts(u32 blade, u32 parts);
  static RESULT_HANA isEnableEquipNArtsParts(u32 blade, u32 parts, u32 slot);
  static RESULT_HANA isEnableEquipCondenserParts(u32 blade, u32 parts, u32 slot);
  static RESULT_HANA isEnableEquipArtsParts(u32 blade, u32 parts, u32 slot);
  static RESULT_HANA isEnableEquipExtendCondenserParts(u32 blade, u32 parts, u32 slot);
  static RESULT_HANA execEquipRoleParts(u32 blade, u32 parts, GfItemHandle handle);
  static RESULT_HANA execEquipAttributeParts(u32 blade, u32 parts, GfItemHandle handle);
  static RESULT_HANA execEquipNArtsParts(u32 blade, u32 parts, GfItemHandle handle, u32 slot);
  static RESULT_HANA execEquipCondenserParts(u32 blade, u32 parts, GfItemHandle handle, u32 slot);
  static RESULT_HANA execEquipArtsParts(u32 blade, u32 parts, GfItemHandle handle, u32 slot);
  static RESULT_HANA execEquipExtendCondenserParts(u32 blade, u32 parts, GfItemHandle handle, u32 slot);
};

} // namespace gf
