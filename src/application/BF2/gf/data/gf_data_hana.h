#pragma once
#include "gf/data/gf_item_handle.h"
#include "mm_mtl/fixed_array.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct SDataBlade;

struct EquipHanaArts {
  u16 unknown00; // Inferred role: enhance; original member name unknown.
  u16 unknown02; // Inferred role: recast reverse of the n arts; original member name unknown.
  u16 unknown04; // Inferred role: parts; original member name unknown.
  u8 _06[0x0a - 0x06];
  u16 unknown0a; // Inferred role: handle; original member name unknown.
};

static_assert(offsetof(EquipHanaArts, unknown02) == 0x02, "");
static_assert(offsetof(EquipHanaArts, unknown04) == 0x04, "");
static_assert(offsetof(EquipHanaArts, unknown0a) == 0x0a, "");
static_assert(sizeof(EquipHanaArts) == 0x0c, "");

struct EquipHana {
  void setArtsParts(u32 parts, u32 handle, u32 index);
  void setNArtsParts(u32 parts, u32 handle, u32 index);

  u16 unknown00;                                   // Inferred role: role; original member name unknown.
  u16 unknown02;                                   // Inferred role: attribute; original member name unknown.
  mm::mtl::FixedArray<EquipHanaArts, 3> unknown04; // Inferred role: arts; original member name unknown.
  mm::mtl::FixedArray<EquipHanaArts, 3> unknown28; // Inferred role: n arts; original member name unknown.
  mm::mtl::FixedArray<u16, 3> unknown4c;           // Inferred role: condenser; original member name unknown.
  mm::mtl::FixedArray<u16, 3> unknown52;           // Inferred role: extend condenser; original member name unknown.
  GfItemHandle unknown58;                          // Inferred role: role handle; original member name unknown.
  GfItemHandle unknown5c;                          // Inferred role: attribute handle; original member name unknown.
  GfItemHandle unknown60[3];                       // Inferred role: condenser handles; original member name unknown.
  GfItemHandle unknown6c[3];                       // Inferred role: extend condenser handles; original member name unknown.
};

static_assert(offsetof(EquipHana, unknown04) == 0x04, "");
static_assert(offsetof(EquipHana, unknown28) == 0x28, "");
static_assert(offsetof(EquipHana, unknown4c) == 0x4c, "");
static_assert(offsetof(EquipHana, unknown52) == 0x52, "");
static_assert(offsetof(EquipHana, unknown58) == 0x58, "");
static_assert(offsetof(EquipHana, unknown5c) == 0x5c, "");
static_assert(offsetof(EquipHana, unknown60) == 0x60, "");
static_assert(offsetof(EquipHana, unknown6c) == 0x6c, "");
static_assert(sizeof(EquipHana) == 0x78, "");

class GfDataHana {
public:
  static bool getRoleName(u8 *&bdat, u32 &textId, u32 parts);
  static bool getAttributeName(u8 *&bdat, u32 &textId, u32 parts);
  static bool getArtsName(u8 *&bdat, u32 &textId, u32 parts);
  static bool getNArtsName(u8 *&bdat, u32 &textId, u32 parts);
  static bool getAssistName(u8 *&bdat, u32 &textId, u32 parts);
  static bool isValid(u32 blade);
  static u32 getRole(u32 blade);
  static u32 getCondenserNum(u32 blade);
  static EquipHana *getEquipParts(SDataBlade &dataBlade);
  static u32 getExtendCondenserNum(u32 blade);
  static bool isOpenCircuit(SDataBlade &dataBlade, u32 circuit);
  static u32 getAttribute(u32 blade);
  static u16 getArtsEnhance(u32 blade, u32 slot);
  static EquipHana *getEquipParts(u32 blade);
  static void setEquipParts(u32 blade, const EquipHana &equipParts);
  static u32 getParmor(u32 blade);
  static u32 getEarmor(u32 blade);
  static u32 getHpMaxRev(u32 blade);
  static u32 getStrengthRev(u32 blade);
  static u32 getPowerEtherRev(u32 blade);
  static u32 getDexRev(u32 blade);
  static u32 getAgilityRev(u32 blade);
  static u32 getLuckRev(u32 blade);
  static u32 getEther();
  static void setEther(u32 ether);
  static u32 getNartsNum(u32 blade);
  static u32 getNeedArtsEther(u32 blade, u32 circuit);
  static u32 getNeedExtendCircuitEther(u32 blade, u32 circuit);
  static u32 getNeedRolePartsEther(u32 parts);
  static u32 getNeedAttributePartsEther(u32 parts);
  static u32 getNeedArtsPartsEther(u32 parts);
  static u32 getNeedNArtsPartsEther(u32 parts);
  static u32 getNeedCondenserPartsEther(u32 parts);
  static u32 getDefaultRoleParts(u32 blade);
  static u32 getDefaultAttributeParts(u32 blade);
  static u32 getDefaultNArtsParts(u32 blade, u32 slot);
  static u32 getDefaultCondenserParts(u32 blade, u32 slot);
  static bool isOpenCircuit(u32 blade, u32 circuit);
  static void setOpenCircuit(u32 blade, u32 circuit, bool openCircuit);
  static u32 getOpenCircuitEther(u32 blade, u32 circuit);
  static void setEquipRoleParts(u32 blade, u32 parts, GfItemHandle handle);
  static u32 getAutoHate(u32 blade);
  static u32 getArtsHate(u32 blade);
  static void setEquipAttributeParts(u32 blade, u32 parts, GfItemHandle handle);
  static void setEquipArtsParts(u32 blade, u32 slot, u32 parts, GfItemHandle handle);
  static void getEquipCondenserParts(mm::mtl::FixedArray<u16, 3> &condenser, u32 blade);
  static void setEquipCondenserParts(u32 blade, u32 slot, u32 parts, GfItemHandle handle);
  static bool getEquipExtendCondenserParts(mm::mtl::FixedArray<u16, 3> &extendCondenser, u32 blade);
  static void setEquipExtendCondenserParts(u32 blade, u32 slot, u32 parts, GfItemHandle handle);
  static u32 getEquipPowerRank(u32 blade);
  static u16 getEquipPowerRank(const SDataBlade &dataBlade);
  static void setEquipPowerRank(u32 blade, u32 equipPowerRank);
  static u32 getPowerCapacity(u32 blade);
  static u32 getPowerCapacity(const SDataBlade &dataBlade);
  static u32 getPartsPower(u32 parts);
  static u32 getEquipPower(u32 blade);
  static u32 getEquipPower(const EquipHana &equipParts);
  static u32 getEquipPower(const SDataBlade &dataBlade);
  static u16 getPowerRankEther(u32 blade, u32 ether);
  static bool isEquipRoleParts(u32 blade, u32 parts);
  static bool isEquipAttributeParts(u32 blade, u32 parts);
  static bool isEquipArtsParts(u32 blade, u32 parts);
  static bool isEquipNArtsParts(u32 blade, u32 parts);
  static bool isEquipCondenserParts(u32 blade, u32 parts);
  static const char *getRoleName(u32 parts);
  static const char *getAttributeName(u32 parts);
  static const char *getNArtsName(u32 parts);
  static const char *getArtsName(u32 parts);
  static const char *getAssistName(u32 parts);
  static u32 getEquipArtsItemNum(u32 blade, u32 parts);
  static u32 getEquipNArtsItemNum(u32 blade, u32 parts);
  static u32 getEquipCondenserItemNum(u32 blade, u32 parts);
  static u32 getEquipRoleItemNum(u32 blade, u32 parts);
  static u32 getEquipAttributeItemNum(u32 blade, u32 parts);
};

} // namespace gf
