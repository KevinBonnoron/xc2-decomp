#include "gf/data/gf_bdat_item.h"
#include "bdat.h"

namespace gf {
namespace _gfbit {

enum {
  CrystalListName,
  CrystalListRarity,
  CrystalListPrice,
  CrystalListCondition,
  CrystalListNoMultiple,
  CrystalListValueMax,
  CrystalListRareTableProb,
  CrystalListRareBladeRev,
  CrystalListCommonPow,
  CrystalListAssureP,
  CrystalListBladeID,
  CrystalListCommonID,
  CrystalListCommonWpn,
  CrystalListCommonAtr,
  CrystalListsortJP,
  BoosterName,
  BoosterCaption,
  BoosterCategory,
  BoosterIdea,
  BoosterRarity,
  BoosterPrice,
  BoosterValueMax,
  BoostersortJP,
  CollectionListName,
  CollectionListCaption,
  CollectionListCategory,
  CollectionListZone,
  CollectionListRarity,
  CollectionListPrice,
  CollectionListsortJP,
  EmptyOrbName,
  EmptyOrbDebugName,
  EmptyOrbPrice,
  EmptyOrbRarity,
  EmptyOrbFlagNoSell,
  EmptyOrbFlagNoSellFlag,
  EmptyOrbRecipe,
  EmptyOrbEquipItemID,
  EmptyOrbsortJP,
  OrbRecipeRecipeType,
  OrbRecipeRarity,
  OrbRecipeRscCat,
  OrbRecipeAssortNumber,
  OrbRecipeItemID1,
  OrbRecipeItemNumber1,
  OrbRecipeItemID2,
  OrbRecipeItemNumber2,
  OrbRecipeItemID3,
  OrbRecipeItemNumber3,
  OrbRecipeItemID4,
  OrbRecipeItemNumber4,
  OrbRecipeItemID5,
  OrbRecipeItemNumber5,
  OrbRecipeItemID6,
  OrbRecipeItemNumber6,
  OrbRecipeItemID7,
  OrbRecipeItemNumber7,
  OrbRecipeItemID8,
  OrbRecipeItemNumber8,
  EquipOrbName,
  EquipOrbDebugName,
  EquipOrbEnhance,
  EquipOrbEnhanceCategory,
  EquipOrbPrice,
  EquipOrbRarity,
  EquipOrbFlagNoSell,
  EquipOrbFlagNoSellFlag,
  EquipOrbsortJP,
  PreciousName,
  PreciousCaption,
  PreciousCategory,
  PreciousType,
  PreciousPrice,
  PreciousValueMax,
  PreciousClearNewGame,
  PreciousNoMultiple,
  PrecioussortJP,
  InfoName,
  InfoCaption,
  InfoPrice,
  InfoClearNewGame,
  InfosortJP,
  EventName,
  EventCaption,
  EventsortJP,
  PcWpnName,
  PcWpnDebugName,
  PcWpnRank,
  PcWpnFlagPrivate,
  PcWpnFlagPrivateFlag,
  PcWpnRscR,
  PcWpnRscL,
  PcWpnTypeRange,
  PcWpnWpnType,
  PcWpnDamage,
  PcWpnStability,
  PcWpnPArmor,
  PcWpnEArmor,
  PcWpnCriRate,
  PcWpnGuardRate,
  PcWpnEnhance1,
  PcWpnEnhance2,
  PcWpnTypeName,
  PcWpnTypeRole,
  PcWpnTypeEffType,
  PcWpnTypeJustRange,
  PcWpnTypeJustRange2,
  PcWpnTypeVoiceType,
  PcWpnTypeMotion,
  PcWpnChipName,
  PcWpnChipDebugName,
  PcWpnChipRank,
  PcWpnChipCreateWpn1,
  PcWpnChipCreateWpn2,
  PcWpnChipCreateWpn3,
  PcWpnChipCreateWpn4,
  PcWpnChipCreateWpn5,
  PcWpnChipCreateWpn6,
  PcWpnChipCreateWpn7,
  PcWpnChipCreateWpn8,
  PcWpnChipCreateWpn9,
  PcWpnChipCreateWpn10,
  PcWpnChipCreateWpn11,
  PcWpnChipCreateWpn12,
  PcWpnChipCreateWpn13,
  PcWpnChipCreateWpn14,
  PcWpnChipCreateWpn15,
  PcWpnChipCreateWpn16,
  PcWpnChipPrice,
  PcWpnChipRarity,
  PcWpnChipFlagNoSell,
  PcWpnChipFlagNoSellFlag,
  PcWpnChipsortJP,
  PcEquipName,
  PcEquipDebugName,
  PcEquipArmorType,
  PcEquipPArmor,
  PcEquipEArmor,
  PcEquipBns_HpMax,
  PcEquipBns_Strength,
  PcEquipBns_PowEther,
  PcEquipBns_Dex,
  PcEquipBns_Agility,
  PcEquipBns_Luck,
  PcEquipEnhance1,
  PcEquipPrice,
  PcEquipRarity,
  PcEquipFlagNoSell,
  PcEquipFlagNoSellFlag,
  PcEquipFlagEqPC01,
  PcEquipFlagEqPC01Flag,
  PcEquipFlagEqPC02,
  PcEquipFlagEqPC02Flag,
  PcEquipFlagEqPC03,
  PcEquipFlagEqPC03Flag,
  PcEquipFlagEqPC04,
  PcEquipFlagEqPC04Flag,
  PcEquipFlagEqPC05,
  PcEquipFlagEqPC05Flag,
  PcEquipFlagEqPC06,
  PcEquipFlagEqPC06Flag,
  PcEquipFlagEqPC07,
  PcEquipFlagEqPC07Flag,
  PcEquipFlagEqPC08,
  PcEquipFlagEqPC08Flag,
  PcEquipFlagEqPC09,
  PcEquipFlagEqPC09Flag,
  PcEquipIcon,
  PcEquipsortJP,
  SalvageName,
  SalvageCaption,
  SalvageRarity,
  SalvagePrice,
  SalvageQuest,
  SalvageNoSell,
  SalvagesortJP,
  HealPotDropRsc,
  HealPotHpRatio,
  TresureName,
  TresureCaption,
  TresureCategory,
  TresureGraphic,
  TresureZone,
  TresureRarity,
  TresurePrice,
  TresureFlag,
  TresureNoMultiple,
  TresureClearNewGame,
  TresuresortJP,
  FavoriteName,
  FavoriteCaption,
  FavoriteCategory,
  FavoriteZone,
  FavoriteRarity,
  FavoritePrice,
  FavoriteType,
  FavoriteTime,
  FavoriteValueMax,
  FavoriteTrustPoint,
  FavoritesortJP,
  OwnerBonusCaption,
  OwnerBonusType,
  OwnerBonusValue,
  OwnerBonusParamMax,
  ITM_HanaRoleName,
  ITM_HanaRoleRole,
  ITM_HanaRolePArmor,
  ITM_HanaRoleEArmor,
  ITM_HanaRoleHpMaxRev,
  ITM_HanaRoleStrengthRev,
  ITM_HanaRolePowEtherRev,
  ITM_HanaRoleDexRev,
  ITM_HanaRoleAgilityRev,
  ITM_HanaRoleLuckRev,
  ITM_HanaRoleAutoHate,
  ITM_HanaRoleArtsHate,
  ITM_HanaRoleFlagJS,
  ITM_HanaRoleFlagJSFlag,
  ITM_HanaRoleFlagJK,
  ITM_HanaRoleFlagJKFlag,
  ITM_HanaRoleFlagJD,
  ITM_HanaRoleFlagJDFlag,
  ITM_HanaRoleNeedPow,
  ITM_HanaRoleNeedEther,
  ITM_HanaRoleDustEther,
  ITM_HanaRoleCondition,
  ITM_HanaRoleUI,
  ITM_HanaRolesortJP,
  ITM_HanaAtrName,
  ITM_HanaAtrAtr,
  ITM_HanaAtrFlagJS,
  ITM_HanaAtrFlagJSFlag,
  ITM_HanaAtrFlagJK,
  ITM_HanaAtrFlagJKFlag,
  ITM_HanaAtrFlagJD,
  ITM_HanaAtrFlagJDFlag,
  ITM_HanaAtrNeedPow,
  ITM_HanaAtrNeedEther,
  ITM_HanaAtrDustEther,
  ITM_HanaAtrCondition,
  ITM_HanaAtrUI,
  ITM_HanaAtrsortJP,
  ITM_HanaArtsEnhName,
  ITM_HanaArtsEnhEnhance,
  ITM_HanaArtsEnhFlagJS,
  ITM_HanaArtsEnhFlagJSFlag,
  ITM_HanaArtsEnhFlagJK,
  ITM_HanaArtsEnhFlagJKFlag,
  ITM_HanaArtsEnhFlagJD,
  ITM_HanaArtsEnhFlagJDFlag,
  ITM_HanaArtsEnhNeedPow,
  ITM_HanaArtsEnhNeedEther,
  ITM_HanaArtsEnhDustEther,
  ITM_HanaArtsEnhCondition,
  ITM_HanaArtsEnhUI,
  ITM_HanaArtsEnhsortJP,
  ITM_HanaNArtsSetName,
  ITM_HanaNArtsSetNArts,
  ITM_HanaNArtsSetNArtsRecastRev,
  ITM_HanaNArtsSetFlagJS,
  ITM_HanaNArtsSetFlagJSFlag,
  ITM_HanaNArtsSetFlagJK,
  ITM_HanaNArtsSetFlagJKFlag,
  ITM_HanaNArtsSetFlagJD,
  ITM_HanaNArtsSetFlagJDFlag,
  ITM_HanaNArtsSetNeedPow,
  ITM_HanaNArtsSetNeedEther,
  ITM_HanaNArtsSetDustEther,
  ITM_HanaNArtsSetCondition,
  ITM_HanaNArtsSetUI,
  ITM_HanaNArtsSetsortJP,
  ITM_HanaAssistName,
  ITM_HanaAssistEnhance,
  ITM_HanaAssistEnhanceCategory,
  ITM_HanaAssistFlagJS,
  ITM_HanaAssistFlagJSFlag,
  ITM_HanaAssistFlagJK,
  ITM_HanaAssistFlagJKFlag,
  ITM_HanaAssistFlagJD,
  ITM_HanaAssistFlagJDFlag,
  ITM_HanaAssistNeedPow,
  ITM_HanaAssistNeedEther,
  ITM_HanaAssistDustEther,
  ITM_HanaAssistCondition,
  ITM_HanaAssistUI,
  ITM_HanaAssistsortJP,
  MEMBER_COUNT,
};

static u8 *s_members[MEMBER_COUNT];

void initCrystalListName(const CBdatWrapper &wrapper) { s_members[CrystalListName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getCrystalListName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CrystalListName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CrystalListName], id, 2).valueU16;
}

void initCrystalListRarity(const CBdatWrapper &wrapper) { s_members[CrystalListRarity] = Bdat::getMember(wrapper.data, "Rarity"); }

u32 getCrystalListRarity(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CrystalListRarity] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CrystalListRarity], id, 1).valueU8;
}

void initCrystalListPrice(const CBdatWrapper &wrapper) { s_members[CrystalListPrice] = Bdat::getMember(wrapper.data, "Price"); }

u32 getCrystalListPrice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CrystalListPrice] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CrystalListPrice], id, 3).valueU32;
}

void initCrystalListCondition(const CBdatWrapper &wrapper) { s_members[CrystalListCondition] = Bdat::getMember(wrapper.data, "Condition"); }

u32 getCrystalListCondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CrystalListCondition] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CrystalListCondition], id, 2).valueU16;
}

void initCrystalListNoMultiple(const CBdatWrapper &wrapper) { s_members[CrystalListNoMultiple] = Bdat::getMember(wrapper.data, "NoMultiple"); }

u32 getCrystalListNoMultiple(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CrystalListNoMultiple] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CrystalListNoMultiple], id, 2).valueU16;
}

void initCrystalListValueMax(const CBdatWrapper &wrapper) { s_members[CrystalListValueMax] = Bdat::getMember(wrapper.data, "ValueMax"); }

u32 getCrystalListValueMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CrystalListValueMax] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CrystalListValueMax], id, 1).valueU8;
}

void initCrystalListRareTableProb(const CBdatWrapper &wrapper) {
  s_members[CrystalListRareTableProb] = Bdat::getMember(wrapper.data, "RareTableProb");
}

u32 getCrystalListRareTableProb(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CrystalListRareTableProb] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CrystalListRareTableProb], id, 1).valueU8;
}

void initCrystalListRareBladeRev(const CBdatWrapper &wrapper) { s_members[CrystalListRareBladeRev] = Bdat::getMember(wrapper.data, "RareBladeRev"); }

u32 getCrystalListRareBladeRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CrystalListRareBladeRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CrystalListRareBladeRev], id, 2).valueU16;
}

void initCrystalListCommonPow(const CBdatWrapper &wrapper) { s_members[CrystalListCommonPow] = Bdat::getMember(wrapper.data, "CommonPow"); }

u32 getCrystalListCommonPow(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CrystalListCommonPow] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CrystalListCommonPow], id, 1).valueU8;
}

void initCrystalListAssureP(const CBdatWrapper &wrapper) { s_members[CrystalListAssureP] = Bdat::getMember(wrapper.data, "AssureP"); }

u32 getCrystalListAssureP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CrystalListAssureP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CrystalListAssureP], id, 2).valueU16;
}

void initCrystalListBladeID(const CBdatWrapper &wrapper) { s_members[CrystalListBladeID] = Bdat::getMember(wrapper.data, "BladeID"); }

u32 getCrystalListBladeID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CrystalListBladeID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CrystalListBladeID], id, 2).valueU16;
}

void initCrystalListCommonID(const CBdatWrapper &wrapper) { s_members[CrystalListCommonID] = Bdat::getMember(wrapper.data, "CommonID"); }

u32 getCrystalListCommonID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CrystalListCommonID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CrystalListCommonID], id, 2).valueU16;
}

void initCrystalListCommonWpn(const CBdatWrapper &wrapper) { s_members[CrystalListCommonWpn] = Bdat::getMember(wrapper.data, "CommonWpn"); }

u32 getCrystalListCommonWpn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CrystalListCommonWpn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CrystalListCommonWpn], id, 1).valueU8;
}

void initCrystalListCommonAtr(const CBdatWrapper &wrapper) { s_members[CrystalListCommonAtr] = Bdat::getMember(wrapper.data, "CommonAtr"); }

u32 getCrystalListCommonAtr(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CrystalListCommonAtr] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CrystalListCommonAtr], id, 1).valueU8;
}

void initCrystalListsortJP(const CBdatWrapper &wrapper) { s_members[CrystalListsortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getCrystalListsortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CrystalListsortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CrystalListsortJP], id, 3).valueU32;
}

void initBoosterName(const CBdatWrapper &wrapper) { s_members[BoosterName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getBoosterName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BoosterName] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BoosterName], id, 2).valueU16;
}

void initBoosterCaption(const CBdatWrapper &wrapper) { s_members[BoosterCaption] = Bdat::getMember(wrapper.data, "Caption"); }

u32 getBoosterCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BoosterCaption] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BoosterCaption], id, 2).valueU16;
}

void initBoosterCategory(const CBdatWrapper &wrapper) { s_members[BoosterCategory] = Bdat::getMember(wrapper.data, "Category"); }

u32 getBoosterCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BoosterCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BoosterCategory], id, 1).valueU8;
}

void initBoosterIdea(const CBdatWrapper &wrapper) { s_members[BoosterIdea] = Bdat::getMember(wrapper.data, "Idea"); }

s32 getBoosterIdea(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BoosterIdea] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BoosterIdea], id, 4).valueS8;
}

void initBoosterRarity(const CBdatWrapper &wrapper) { s_members[BoosterRarity] = Bdat::getMember(wrapper.data, "Rarity"); }

u32 getBoosterRarity(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BoosterRarity] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BoosterRarity], id, 1).valueU8;
}

void initBoosterPrice(const CBdatWrapper &wrapper) { s_members[BoosterPrice] = Bdat::getMember(wrapper.data, "Price"); }

u32 getBoosterPrice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BoosterPrice] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BoosterPrice], id, 3).valueU32;
}

void initBoosterValueMax(const CBdatWrapper &wrapper) { s_members[BoosterValueMax] = Bdat::getMember(wrapper.data, "ValueMax"); }

u32 getBoosterValueMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BoosterValueMax] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BoosterValueMax], id, 1).valueU8;
}

void initBoostersortJP(const CBdatWrapper &wrapper) { s_members[BoostersortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getBoostersortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BoostersortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BoostersortJP], id, 3).valueU32;
}

void initCollectionListName(const CBdatWrapper &wrapper) { s_members[CollectionListName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getCollectionListName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CollectionListName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CollectionListName], id, 2).valueU16;
}

void initCollectionListCaption(const CBdatWrapper &wrapper) { s_members[CollectionListCaption] = Bdat::getMember(wrapper.data, "Caption"); }

u32 getCollectionListCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CollectionListCaption] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CollectionListCaption], id, 2).valueU16;
}

void initCollectionListCategory(const CBdatWrapper &wrapper) { s_members[CollectionListCategory] = Bdat::getMember(wrapper.data, "Category"); }

u32 getCollectionListCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CollectionListCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CollectionListCategory], id, 1).valueU8;
}

void initCollectionListZone(const CBdatWrapper &wrapper) { s_members[CollectionListZone] = Bdat::getMember(wrapper.data, "Zone"); }

u32 getCollectionListZone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CollectionListZone] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CollectionListZone], id, 2).valueU16;
}

void initCollectionListRarity(const CBdatWrapper &wrapper) { s_members[CollectionListRarity] = Bdat::getMember(wrapper.data, "Rarity"); }

u32 getCollectionListRarity(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CollectionListRarity] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CollectionListRarity], id, 1).valueU8;
}

void initCollectionListPrice(const CBdatWrapper &wrapper) { s_members[CollectionListPrice] = Bdat::getMember(wrapper.data, "Price"); }

u32 getCollectionListPrice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CollectionListPrice] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CollectionListPrice], id, 3).valueU32;
}

void initCollectionListsortJP(const CBdatWrapper &wrapper) { s_members[CollectionListsortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getCollectionListsortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CollectionListsortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CollectionListsortJP], id, 3).valueU32;
}

void initEmptyOrbName(const CBdatWrapper &wrapper) { s_members[EmptyOrbName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getEmptyOrbName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EmptyOrbName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EmptyOrbName], id, 2).valueU16;
}

void initEmptyOrbDebugName(const CBdatWrapper &wrapper) { s_members[EmptyOrbDebugName] = Bdat::getMember(wrapper.data, "DebugName"); }

const char *getEmptyOrbDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EmptyOrbDebugName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[EmptyOrbDebugName], id, 7).valueString;
}

void initEmptyOrbPrice(const CBdatWrapper &wrapper) { s_members[EmptyOrbPrice] = Bdat::getMember(wrapper.data, "Price"); }

u32 getEmptyOrbPrice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EmptyOrbPrice] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EmptyOrbPrice], id, 3).valueU32;
}

void initEmptyOrbRarity(const CBdatWrapper &wrapper) { s_members[EmptyOrbRarity] = Bdat::getMember(wrapper.data, "Rarity"); }

u32 getEmptyOrbRarity(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EmptyOrbRarity] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EmptyOrbRarity], id, 1).valueU8;
}

void initEmptyOrbFlagNoSell(const CBdatWrapper &wrapper) {
  s_members[EmptyOrbFlagNoSell] = Bdat::getMember(wrapper.data, "Flag");
  s_members[EmptyOrbFlagNoSellFlag] = Bdat::getMember(wrapper.data, "NoSell");
}

bool isEmptyOrbFlagNoSell(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EmptyOrbFlagNoSell] == nullptr || s_members[EmptyOrbFlagNoSellFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[EmptyOrbFlagNoSell], id, s_members[EmptyOrbFlagNoSellFlag]) != 0;
}

void initEmptyOrbRecipe(const CBdatWrapper &wrapper) { s_members[EmptyOrbRecipe] = Bdat::getMember(wrapper.data, "Recipe"); }

u32 getEmptyOrbRecipe(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EmptyOrbRecipe] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EmptyOrbRecipe], id, 2).valueU16;
}

void initEmptyOrbEquipItemID(const CBdatWrapper &wrapper) { s_members[EmptyOrbEquipItemID] = Bdat::getMember(wrapper.data, "EquipItemID"); }

u32 getEmptyOrbEquipItemID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EmptyOrbEquipItemID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EmptyOrbEquipItemID], id, 2).valueU16;
}

void initEmptyOrbsortJP(const CBdatWrapper &wrapper) { s_members[EmptyOrbsortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getEmptyOrbsortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EmptyOrbsortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EmptyOrbsortJP], id, 3).valueU32;
}

void initOrbRecipeRecipeType(const CBdatWrapper &wrapper) { s_members[OrbRecipeRecipeType] = Bdat::getMember(wrapper.data, "RecipeType"); }

u32 getOrbRecipeRecipeType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeRecipeType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeRecipeType], id, 1).valueU8;
}

void initOrbRecipeRarity(const CBdatWrapper &wrapper) { s_members[OrbRecipeRarity] = Bdat::getMember(wrapper.data, "Rarity"); }

u32 getOrbRecipeRarity(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeRarity] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeRarity], id, 1).valueU8;
}

void initOrbRecipeRscCat(const CBdatWrapper &wrapper) { s_members[OrbRecipeRscCat] = Bdat::getMember(wrapper.data, "RscCat"); }

u32 getOrbRecipeRscCat(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeRscCat] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeRscCat], id, 1).valueU8;
}

void initOrbRecipeAssortNumber(const CBdatWrapper &wrapper) { s_members[OrbRecipeAssortNumber] = Bdat::getMember(wrapper.data, "AssortNumber"); }

u32 getOrbRecipeAssortNumber(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeAssortNumber] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeAssortNumber], id, 2).valueU16;
}

void initOrbRecipeItemID1(const CBdatWrapper &wrapper) { s_members[OrbRecipeItemID1] = Bdat::getMember(wrapper.data, "ItemID1"); }

u32 getOrbRecipeItemID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeItemID1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeItemID1], id, 2).valueU16;
}

void initOrbRecipeItemNumber1(const CBdatWrapper &wrapper) { s_members[OrbRecipeItemNumber1] = Bdat::getMember(wrapper.data, "ItemNumber1"); }

u32 getOrbRecipeItemNumber1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeItemNumber1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeItemNumber1], id, 2).valueU16;
}

void initOrbRecipeItemID2(const CBdatWrapper &wrapper) { s_members[OrbRecipeItemID2] = Bdat::getMember(wrapper.data, "ItemID2"); }

u32 getOrbRecipeItemID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeItemID2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeItemID2], id, 2).valueU16;
}

void initOrbRecipeItemNumber2(const CBdatWrapper &wrapper) { s_members[OrbRecipeItemNumber2] = Bdat::getMember(wrapper.data, "ItemNumber2"); }

u32 getOrbRecipeItemNumber2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeItemNumber2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeItemNumber2], id, 2).valueU16;
}

void initOrbRecipeItemID3(const CBdatWrapper &wrapper) { s_members[OrbRecipeItemID3] = Bdat::getMember(wrapper.data, "ItemID3"); }

u32 getOrbRecipeItemID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeItemID3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeItemID3], id, 2).valueU16;
}

void initOrbRecipeItemNumber3(const CBdatWrapper &wrapper) { s_members[OrbRecipeItemNumber3] = Bdat::getMember(wrapper.data, "ItemNumber3"); }

u32 getOrbRecipeItemNumber3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeItemNumber3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeItemNumber3], id, 2).valueU16;
}

void initOrbRecipeItemID4(const CBdatWrapper &wrapper) { s_members[OrbRecipeItemID4] = Bdat::getMember(wrapper.data, "ItemID4"); }

u32 getOrbRecipeItemID4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeItemID4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeItemID4], id, 2).valueU16;
}

void initOrbRecipeItemNumber4(const CBdatWrapper &wrapper) { s_members[OrbRecipeItemNumber4] = Bdat::getMember(wrapper.data, "ItemNumber4"); }

u32 getOrbRecipeItemNumber4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeItemNumber4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeItemNumber4], id, 2).valueU16;
}

void initOrbRecipeItemID5(const CBdatWrapper &wrapper) { s_members[OrbRecipeItemID5] = Bdat::getMember(wrapper.data, "ItemID5"); }

u32 getOrbRecipeItemID5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeItemID5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeItemID5], id, 2).valueU16;
}

void initOrbRecipeItemNumber5(const CBdatWrapper &wrapper) { s_members[OrbRecipeItemNumber5] = Bdat::getMember(wrapper.data, "ItemNumber5"); }

u32 getOrbRecipeItemNumber5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeItemNumber5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeItemNumber5], id, 2).valueU16;
}

void initOrbRecipeItemID6(const CBdatWrapper &wrapper) { s_members[OrbRecipeItemID6] = Bdat::getMember(wrapper.data, "ItemID6"); }

u32 getOrbRecipeItemID6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeItemID6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeItemID6], id, 2).valueU16;
}

void initOrbRecipeItemNumber6(const CBdatWrapper &wrapper) { s_members[OrbRecipeItemNumber6] = Bdat::getMember(wrapper.data, "ItemNumber6"); }

u32 getOrbRecipeItemNumber6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeItemNumber6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeItemNumber6], id, 2).valueU16;
}

void initOrbRecipeItemID7(const CBdatWrapper &wrapper) { s_members[OrbRecipeItemID7] = Bdat::getMember(wrapper.data, "ItemID7"); }

u32 getOrbRecipeItemID7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeItemID7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeItemID7], id, 2).valueU16;
}

void initOrbRecipeItemNumber7(const CBdatWrapper &wrapper) { s_members[OrbRecipeItemNumber7] = Bdat::getMember(wrapper.data, "ItemNumber7"); }

u32 getOrbRecipeItemNumber7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeItemNumber7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeItemNumber7], id, 2).valueU16;
}

void initOrbRecipeItemID8(const CBdatWrapper &wrapper) { s_members[OrbRecipeItemID8] = Bdat::getMember(wrapper.data, "ItemID8"); }

u32 getOrbRecipeItemID8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeItemID8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeItemID8], id, 2).valueU16;
}

void initOrbRecipeItemNumber8(const CBdatWrapper &wrapper) { s_members[OrbRecipeItemNumber8] = Bdat::getMember(wrapper.data, "ItemNumber8"); }

u32 getOrbRecipeItemNumber8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OrbRecipeItemNumber8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OrbRecipeItemNumber8], id, 2).valueU16;
}

void initEquipOrbName(const CBdatWrapper &wrapper) { s_members[EquipOrbName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getEquipOrbName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EquipOrbName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EquipOrbName], id, 2).valueU16;
}

void initEquipOrbDebugName(const CBdatWrapper &wrapper) { s_members[EquipOrbDebugName] = Bdat::getMember(wrapper.data, "DebugName"); }

const char *getEquipOrbDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EquipOrbDebugName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[EquipOrbDebugName], id, 7).valueString;
}

void initEquipOrbEnhance(const CBdatWrapper &wrapper) { s_members[EquipOrbEnhance] = Bdat::getMember(wrapper.data, "Enhance"); }

u32 getEquipOrbEnhance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EquipOrbEnhance] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EquipOrbEnhance], id, 2).valueU16;
}

void initEquipOrbEnhanceCategory(const CBdatWrapper &wrapper) {
  s_members[EquipOrbEnhanceCategory] = Bdat::getMember(wrapper.data, "EnhanceCategory");
}

u32 getEquipOrbEnhanceCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EquipOrbEnhanceCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EquipOrbEnhanceCategory], id, 1).valueU8;
}

void initEquipOrbPrice(const CBdatWrapper &wrapper) { s_members[EquipOrbPrice] = Bdat::getMember(wrapper.data, "Price"); }

u32 getEquipOrbPrice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EquipOrbPrice] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EquipOrbPrice], id, 3).valueU32;
}

void initEquipOrbRarity(const CBdatWrapper &wrapper) { s_members[EquipOrbRarity] = Bdat::getMember(wrapper.data, "Rarity"); }

u32 getEquipOrbRarity(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EquipOrbRarity] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EquipOrbRarity], id, 1).valueU8;
}

void initEquipOrbFlagNoSell(const CBdatWrapper &wrapper) {
  s_members[EquipOrbFlagNoSell] = Bdat::getMember(wrapper.data, "Flag");
  s_members[EquipOrbFlagNoSellFlag] = Bdat::getMember(wrapper.data, "NoSell");
}

bool isEquipOrbFlagNoSell(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EquipOrbFlagNoSell] == nullptr || s_members[EquipOrbFlagNoSellFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[EquipOrbFlagNoSell], id, s_members[EquipOrbFlagNoSellFlag]) != 0;
}

void initEquipOrbsortJP(const CBdatWrapper &wrapper) { s_members[EquipOrbsortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getEquipOrbsortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EquipOrbsortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EquipOrbsortJP], id, 3).valueU32;
}

void initPreciousName(const CBdatWrapper &wrapper) { s_members[PreciousName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getPreciousName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PreciousName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PreciousName], id, 2).valueU16;
}

void initPreciousCaption(const CBdatWrapper &wrapper) { s_members[PreciousCaption] = Bdat::getMember(wrapper.data, "Caption"); }

u32 getPreciousCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PreciousCaption] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PreciousCaption], id, 2).valueU16;
}

void initPreciousCategory(const CBdatWrapper &wrapper) { s_members[PreciousCategory] = Bdat::getMember(wrapper.data, "Category"); }

u32 getPreciousCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PreciousCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PreciousCategory], id, 1).valueU8;
}

void initPreciousType(const CBdatWrapper &wrapper) { s_members[PreciousType] = Bdat::getMember(wrapper.data, "Type"); }

u32 getPreciousType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PreciousType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PreciousType], id, 2).valueU16;
}

void initPreciousPrice(const CBdatWrapper &wrapper) { s_members[PreciousPrice] = Bdat::getMember(wrapper.data, "Price"); }

u32 getPreciousPrice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PreciousPrice] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PreciousPrice], id, 3).valueU32;
}

void initPreciousValueMax(const CBdatWrapper &wrapper) { s_members[PreciousValueMax] = Bdat::getMember(wrapper.data, "ValueMax"); }

u32 getPreciousValueMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PreciousValueMax] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PreciousValueMax], id, 1).valueU8;
}

void initPreciousClearNewGame(const CBdatWrapper &wrapper) { s_members[PreciousClearNewGame] = Bdat::getMember(wrapper.data, "ClearNewGame"); }

u32 getPreciousClearNewGame(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PreciousClearNewGame] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PreciousClearNewGame], id, 1).valueU8;
}

void initPreciousNoMultiple(const CBdatWrapper &wrapper) { s_members[PreciousNoMultiple] = Bdat::getMember(wrapper.data, "NoMultiple"); }

u32 getPreciousNoMultiple(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PreciousNoMultiple] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PreciousNoMultiple], id, 2).valueU16;
}

void initPrecioussortJP(const CBdatWrapper &wrapper) { s_members[PrecioussortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getPrecioussortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PrecioussortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PrecioussortJP], id, 3).valueU32;
}

void initInfoName(const CBdatWrapper &wrapper) { s_members[InfoName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getInfoName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[InfoName] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[InfoName], id, 2).valueU16;
}

void initInfoCaption(const CBdatWrapper &wrapper) { s_members[InfoCaption] = Bdat::getMember(wrapper.data, "Caption"); }

u32 getInfoCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[InfoCaption] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[InfoCaption], id, 2).valueU16;
}

void initInfoPrice(const CBdatWrapper &wrapper) { s_members[InfoPrice] = Bdat::getMember(wrapper.data, "Price"); }

u32 getInfoPrice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[InfoPrice] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[InfoPrice], id, 3).valueU32;
}

void initInfoClearNewGame(const CBdatWrapper &wrapper) { s_members[InfoClearNewGame] = Bdat::getMember(wrapper.data, "ClearNewGame"); }

u32 getInfoClearNewGame(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[InfoClearNewGame] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[InfoClearNewGame], id, 1).valueU8;
}

void initInfosortJP(const CBdatWrapper &wrapper) { s_members[InfosortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getInfosortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[InfosortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[InfosortJP], id, 3).valueU32;
}

void initEventName(const CBdatWrapper &wrapper) { s_members[EventName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getEventName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EventName] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EventName], id, 2).valueU16;
}

void initEventCaption(const CBdatWrapper &wrapper) { s_members[EventCaption] = Bdat::getMember(wrapper.data, "Caption"); }

u32 getEventCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EventCaption] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EventCaption], id, 2).valueU16;
}

void initEventsortJP(const CBdatWrapper &wrapper) { s_members[EventsortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getEventsortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EventsortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EventsortJP], id, 3).valueU32;
}

void initPcWpnName(const CBdatWrapper &wrapper) { s_members[PcWpnName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getPcWpnName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnName] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnName], id, 2).valueU16;
}

void initPcWpnDebugName(const CBdatWrapper &wrapper) { s_members[PcWpnDebugName] = Bdat::getMember(wrapper.data, "DebugName"); }

const char *getPcWpnDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnDebugName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[PcWpnDebugName], id, 7).valueString;
}

void initPcWpnRank(const CBdatWrapper &wrapper) { s_members[PcWpnRank] = Bdat::getMember(wrapper.data, "Rank"); }

u32 getPcWpnRank(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnRank] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnRank], id, 1).valueU8;
}

void initPcWpnFlagPrivate(const CBdatWrapper &wrapper) {
  s_members[PcWpnFlagPrivate] = Bdat::getMember(wrapper.data, "Flag");
  s_members[PcWpnFlagPrivateFlag] = Bdat::getMember(wrapper.data, "Private");
}

bool isPcWpnFlagPrivate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnFlagPrivate] == nullptr || s_members[PcWpnFlagPrivateFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[PcWpnFlagPrivate], id, s_members[PcWpnFlagPrivateFlag]) != 0;
}

void initPcWpnRscR(const CBdatWrapper &wrapper) { s_members[PcWpnRscR] = Bdat::getMember(wrapper.data, "RscR"); }

u32 getPcWpnRscR(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnRscR] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnRscR], id, 2).valueU16;
}

void initPcWpnRscL(const CBdatWrapper &wrapper) { s_members[PcWpnRscL] = Bdat::getMember(wrapper.data, "RscL"); }

u32 getPcWpnRscL(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnRscL] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnRscL], id, 2).valueU16;
}

void initPcWpnTypeRange(const CBdatWrapper &wrapper) { s_members[PcWpnTypeRange] = Bdat::getMember(wrapper.data, "TypeRange"); }

u32 getPcWpnTypeRange(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnTypeRange] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnTypeRange], id, 1).valueU8;
}

void initPcWpnWpnType(const CBdatWrapper &wrapper) { s_members[PcWpnWpnType] = Bdat::getMember(wrapper.data, "WpnType"); }

u32 getPcWpnWpnType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnWpnType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnWpnType], id, 1).valueU8;
}

void initPcWpnDamage(const CBdatWrapper &wrapper) { s_members[PcWpnDamage] = Bdat::getMember(wrapper.data, "Damage"); }

u32 getPcWpnDamage(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnDamage] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnDamage], id, 2).valueU16;
}

void initPcWpnStability(const CBdatWrapper &wrapper) { s_members[PcWpnStability] = Bdat::getMember(wrapper.data, "Stability"); }

u32 getPcWpnStability(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnStability] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnStability], id, 1).valueU8;
}

void initPcWpnPArmor(const CBdatWrapper &wrapper) { s_members[PcWpnPArmor] = Bdat::getMember(wrapper.data, "PArmor"); }

u32 getPcWpnPArmor(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnPArmor] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnPArmor], id, 2).valueU16;
}

void initPcWpnEArmor(const CBdatWrapper &wrapper) { s_members[PcWpnEArmor] = Bdat::getMember(wrapper.data, "EArmor"); }

u32 getPcWpnEArmor(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnEArmor] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnEArmor], id, 2).valueU16;
}

void initPcWpnCriRate(const CBdatWrapper &wrapper) { s_members[PcWpnCriRate] = Bdat::getMember(wrapper.data, "CriRate"); }

u32 getPcWpnCriRate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnCriRate] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnCriRate], id, 1).valueU8;
}

void initPcWpnGuardRate(const CBdatWrapper &wrapper) { s_members[PcWpnGuardRate] = Bdat::getMember(wrapper.data, "GuardRate"); }

u32 getPcWpnGuardRate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnGuardRate] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnGuardRate], id, 1).valueU8;
}

void initPcWpnEnhance1(const CBdatWrapper &wrapper) { s_members[PcWpnEnhance1] = Bdat::getMember(wrapper.data, "Enhance1"); }

u32 getPcWpnEnhance1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnEnhance1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnEnhance1], id, 2).valueU16;
}

void initPcWpnEnhance2(const CBdatWrapper &wrapper) { s_members[PcWpnEnhance2] = Bdat::getMember(wrapper.data, "Enhance2"); }

u32 getPcWpnEnhance2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnEnhance2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnEnhance2], id, 2).valueU16;
}

void initPcWpnTypeName(const CBdatWrapper &wrapper) { s_members[PcWpnTypeName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getPcWpnTypeName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnTypeName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnTypeName], id, 2).valueU16;
}

void initPcWpnTypeRole(const CBdatWrapper &wrapper) { s_members[PcWpnTypeRole] = Bdat::getMember(wrapper.data, "Role"); }

u32 getPcWpnTypeRole(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnTypeRole] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnTypeRole], id, 1).valueU8;
}

void initPcWpnTypeEffType(const CBdatWrapper &wrapper) { s_members[PcWpnTypeEffType] = Bdat::getMember(wrapper.data, "EffType"); }

u32 getPcWpnTypeEffType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnTypeEffType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnTypeEffType], id, 1).valueU8;
}

void initPcWpnTypeJustRange(const CBdatWrapper &wrapper) { s_members[PcWpnTypeJustRange] = Bdat::getMember(wrapper.data, "JustRange"); }

u32 getPcWpnTypeJustRange(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnTypeJustRange] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnTypeJustRange], id, 1).valueU8;
}

void initPcWpnTypeJustRange2(const CBdatWrapper &wrapper) { s_members[PcWpnTypeJustRange2] = Bdat::getMember(wrapper.data, "JustRange2"); }

u32 getPcWpnTypeJustRange2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnTypeJustRange2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnTypeJustRange2], id, 1).valueU8;
}

void initPcWpnTypeVoiceType(const CBdatWrapper &wrapper) { s_members[PcWpnTypeVoiceType] = Bdat::getMember(wrapper.data, "VoiceType"); }

u32 getPcWpnTypeVoiceType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnTypeVoiceType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnTypeVoiceType], id, 1).valueU8;
}

void initPcWpnTypeMotion(const CBdatWrapper &wrapper) { s_members[PcWpnTypeMotion] = Bdat::getMember(wrapper.data, "Motion"); }

u32 getPcWpnTypeMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnTypeMotion] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnTypeMotion], id, 1).valueU8;
}

void initPcWpnChipName(const CBdatWrapper &wrapper) { s_members[PcWpnChipName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getPcWpnChipName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipName], id, 2).valueU16;
}

void initPcWpnChipDebugName(const CBdatWrapper &wrapper) { s_members[PcWpnChipDebugName] = Bdat::getMember(wrapper.data, "DebugName"); }

const char *getPcWpnChipDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipDebugName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[PcWpnChipDebugName], id, 7).valueString;
}

void initPcWpnChipRank(const CBdatWrapper &wrapper) { s_members[PcWpnChipRank] = Bdat::getMember(wrapper.data, "Rank"); }

u32 getPcWpnChipRank(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipRank] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipRank], id, 1).valueU8;
}

void initPcWpnChipCreateWpn1(const CBdatWrapper &wrapper) { s_members[PcWpnChipCreateWpn1] = Bdat::getMember(wrapper.data, "CreateWpn1"); }

u32 getPcWpnChipCreateWpn1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipCreateWpn1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipCreateWpn1], id, 2).valueU16;
}

void initPcWpnChipCreateWpn2(const CBdatWrapper &wrapper) { s_members[PcWpnChipCreateWpn2] = Bdat::getMember(wrapper.data, "CreateWpn2"); }

u32 getPcWpnChipCreateWpn2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipCreateWpn2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipCreateWpn2], id, 2).valueU16;
}

void initPcWpnChipCreateWpn3(const CBdatWrapper &wrapper) { s_members[PcWpnChipCreateWpn3] = Bdat::getMember(wrapper.data, "CreateWpn3"); }

u32 getPcWpnChipCreateWpn3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipCreateWpn3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipCreateWpn3], id, 2).valueU16;
}

void initPcWpnChipCreateWpn4(const CBdatWrapper &wrapper) { s_members[PcWpnChipCreateWpn4] = Bdat::getMember(wrapper.data, "CreateWpn4"); }

u32 getPcWpnChipCreateWpn4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipCreateWpn4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipCreateWpn4], id, 2).valueU16;
}

void initPcWpnChipCreateWpn5(const CBdatWrapper &wrapper) { s_members[PcWpnChipCreateWpn5] = Bdat::getMember(wrapper.data, "CreateWpn5"); }

u32 getPcWpnChipCreateWpn5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipCreateWpn5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipCreateWpn5], id, 2).valueU16;
}

void initPcWpnChipCreateWpn6(const CBdatWrapper &wrapper) { s_members[PcWpnChipCreateWpn6] = Bdat::getMember(wrapper.data, "CreateWpn6"); }

u32 getPcWpnChipCreateWpn6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipCreateWpn6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipCreateWpn6], id, 2).valueU16;
}

void initPcWpnChipCreateWpn7(const CBdatWrapper &wrapper) { s_members[PcWpnChipCreateWpn7] = Bdat::getMember(wrapper.data, "CreateWpn7"); }

u32 getPcWpnChipCreateWpn7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipCreateWpn7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipCreateWpn7], id, 2).valueU16;
}

void initPcWpnChipCreateWpn8(const CBdatWrapper &wrapper) { s_members[PcWpnChipCreateWpn8] = Bdat::getMember(wrapper.data, "CreateWpn8"); }

u32 getPcWpnChipCreateWpn8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipCreateWpn8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipCreateWpn8], id, 2).valueU16;
}

void initPcWpnChipCreateWpn9(const CBdatWrapper &wrapper) { s_members[PcWpnChipCreateWpn9] = Bdat::getMember(wrapper.data, "CreateWpn9"); }

u32 getPcWpnChipCreateWpn9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipCreateWpn9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipCreateWpn9], id, 2).valueU16;
}

void initPcWpnChipCreateWpn10(const CBdatWrapper &wrapper) { s_members[PcWpnChipCreateWpn10] = Bdat::getMember(wrapper.data, "CreateWpn10"); }

u32 getPcWpnChipCreateWpn10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipCreateWpn10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipCreateWpn10], id, 2).valueU16;
}

void initPcWpnChipCreateWpn11(const CBdatWrapper &wrapper) { s_members[PcWpnChipCreateWpn11] = Bdat::getMember(wrapper.data, "CreateWpn11"); }

u32 getPcWpnChipCreateWpn11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipCreateWpn11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipCreateWpn11], id, 2).valueU16;
}

void initPcWpnChipCreateWpn12(const CBdatWrapper &wrapper) { s_members[PcWpnChipCreateWpn12] = Bdat::getMember(wrapper.data, "CreateWpn12"); }

u32 getPcWpnChipCreateWpn12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipCreateWpn12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipCreateWpn12], id, 2).valueU16;
}

void initPcWpnChipCreateWpn13(const CBdatWrapper &wrapper) { s_members[PcWpnChipCreateWpn13] = Bdat::getMember(wrapper.data, "CreateWpn13"); }

u32 getPcWpnChipCreateWpn13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipCreateWpn13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipCreateWpn13], id, 2).valueU16;
}

void initPcWpnChipCreateWpn14(const CBdatWrapper &wrapper) { s_members[PcWpnChipCreateWpn14] = Bdat::getMember(wrapper.data, "CreateWpn14"); }

u32 getPcWpnChipCreateWpn14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipCreateWpn14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipCreateWpn14], id, 2).valueU16;
}

void initPcWpnChipCreateWpn15(const CBdatWrapper &wrapper) { s_members[PcWpnChipCreateWpn15] = Bdat::getMember(wrapper.data, "CreateWpn15"); }

u32 getPcWpnChipCreateWpn15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipCreateWpn15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipCreateWpn15], id, 2).valueU16;
}

void initPcWpnChipCreateWpn16(const CBdatWrapper &wrapper) { s_members[PcWpnChipCreateWpn16] = Bdat::getMember(wrapper.data, "CreateWpn16"); }

u32 getPcWpnChipCreateWpn16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipCreateWpn16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipCreateWpn16], id, 2).valueU16;
}

void initPcWpnChipPrice(const CBdatWrapper &wrapper) { s_members[PcWpnChipPrice] = Bdat::getMember(wrapper.data, "Price"); }

u32 getPcWpnChipPrice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipPrice] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipPrice], id, 3).valueU32;
}

void initPcWpnChipRarity(const CBdatWrapper &wrapper) { s_members[PcWpnChipRarity] = Bdat::getMember(wrapper.data, "Rarity"); }

u32 getPcWpnChipRarity(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipRarity] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipRarity], id, 1).valueU8;
}

void initPcWpnChipFlagNoSell(const CBdatWrapper &wrapper) {
  s_members[PcWpnChipFlagNoSell] = Bdat::getMember(wrapper.data, "Flag");
  s_members[PcWpnChipFlagNoSellFlag] = Bdat::getMember(wrapper.data, "NoSell");
}

bool isPcWpnChipFlagNoSell(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipFlagNoSell] == nullptr || s_members[PcWpnChipFlagNoSellFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[PcWpnChipFlagNoSell], id, s_members[PcWpnChipFlagNoSellFlag]) != 0;
}

void initPcWpnChipsortJP(const CBdatWrapper &wrapper) { s_members[PcWpnChipsortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getPcWpnChipsortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcWpnChipsortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcWpnChipsortJP], id, 3).valueU32;
}

void initPcEquipName(const CBdatWrapper &wrapper) { s_members[PcEquipName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getPcEquipName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipName] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcEquipName], id, 2).valueU16;
}

void initPcEquipDebugName(const CBdatWrapper &wrapper) { s_members[PcEquipDebugName] = Bdat::getMember(wrapper.data, "DebugName"); }

const char *getPcEquipDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipDebugName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[PcEquipDebugName], id, 7).valueString;
}

void initPcEquipArmorType(const CBdatWrapper &wrapper) { s_members[PcEquipArmorType] = Bdat::getMember(wrapper.data, "ArmorType"); }

u32 getPcEquipArmorType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipArmorType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcEquipArmorType], id, 1).valueU8;
}

void initPcEquipPArmor(const CBdatWrapper &wrapper) { s_members[PcEquipPArmor] = Bdat::getMember(wrapper.data, "PArmor"); }

u32 getPcEquipPArmor(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipPArmor] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcEquipPArmor], id, 2).valueU16;
}

void initPcEquipEArmor(const CBdatWrapper &wrapper) { s_members[PcEquipEArmor] = Bdat::getMember(wrapper.data, "EArmor"); }

u32 getPcEquipEArmor(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipEArmor] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcEquipEArmor], id, 2).valueU16;
}

void initPcEquipBns_HpMax(const CBdatWrapper &wrapper) { s_members[PcEquipBns_HpMax] = Bdat::getMember(wrapper.data, "Bns_HpMax"); }

u32 getPcEquipBns_HpMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipBns_HpMax] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcEquipBns_HpMax], id, 2).valueU16;
}

void initPcEquipBns_Strength(const CBdatWrapper &wrapper) { s_members[PcEquipBns_Strength] = Bdat::getMember(wrapper.data, "Bns_Strength"); }

u32 getPcEquipBns_Strength(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipBns_Strength] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcEquipBns_Strength], id, 2).valueU16;
}

void initPcEquipBns_PowEther(const CBdatWrapper &wrapper) { s_members[PcEquipBns_PowEther] = Bdat::getMember(wrapper.data, "Bns_PowEther"); }

u32 getPcEquipBns_PowEther(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipBns_PowEther] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcEquipBns_PowEther], id, 2).valueU16;
}

void initPcEquipBns_Dex(const CBdatWrapper &wrapper) { s_members[PcEquipBns_Dex] = Bdat::getMember(wrapper.data, "Bns_Dex"); }

u32 getPcEquipBns_Dex(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipBns_Dex] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcEquipBns_Dex], id, 2).valueU16;
}

void initPcEquipBns_Agility(const CBdatWrapper &wrapper) { s_members[PcEquipBns_Agility] = Bdat::getMember(wrapper.data, "Bns_Agility"); }

u32 getPcEquipBns_Agility(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipBns_Agility] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcEquipBns_Agility], id, 2).valueU16;
}

void initPcEquipBns_Luck(const CBdatWrapper &wrapper) { s_members[PcEquipBns_Luck] = Bdat::getMember(wrapper.data, "Bns_Luck"); }

u32 getPcEquipBns_Luck(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipBns_Luck] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcEquipBns_Luck], id, 2).valueU16;
}

void initPcEquipEnhance1(const CBdatWrapper &wrapper) { s_members[PcEquipEnhance1] = Bdat::getMember(wrapper.data, "Enhance1"); }

u32 getPcEquipEnhance1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipEnhance1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcEquipEnhance1], id, 2).valueU16;
}

void initPcEquipPrice(const CBdatWrapper &wrapper) { s_members[PcEquipPrice] = Bdat::getMember(wrapper.data, "Price"); }

u32 getPcEquipPrice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipPrice] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcEquipPrice], id, 3).valueU32;
}

void initPcEquipRarity(const CBdatWrapper &wrapper) { s_members[PcEquipRarity] = Bdat::getMember(wrapper.data, "Rarity"); }

u32 getPcEquipRarity(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipRarity] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcEquipRarity], id, 1).valueU8;
}

void initPcEquipFlagNoSell(const CBdatWrapper &wrapper) {
  s_members[PcEquipFlagNoSell] = Bdat::getMember(wrapper.data, "Flag");
  s_members[PcEquipFlagNoSellFlag] = Bdat::getMember(wrapper.data, "NoSell");
}

bool isPcEquipFlagNoSell(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipFlagNoSell] == nullptr || s_members[PcEquipFlagNoSellFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[PcEquipFlagNoSell], id, s_members[PcEquipFlagNoSellFlag]) != 0;
}

void initPcEquipFlagEqPC01(const CBdatWrapper &wrapper) {
  s_members[PcEquipFlagEqPC01] = Bdat::getMember(wrapper.data, "Flag");
  s_members[PcEquipFlagEqPC01Flag] = Bdat::getMember(wrapper.data, "EqPC01");
}

bool isPcEquipFlagEqPC01(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipFlagEqPC01] == nullptr || s_members[PcEquipFlagEqPC01Flag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[PcEquipFlagEqPC01], id, s_members[PcEquipFlagEqPC01Flag]) != 0;
}

void initPcEquipFlagEqPC02(const CBdatWrapper &wrapper) {
  s_members[PcEquipFlagEqPC02] = Bdat::getMember(wrapper.data, "Flag");
  s_members[PcEquipFlagEqPC02Flag] = Bdat::getMember(wrapper.data, "EqPC02");
}

bool isPcEquipFlagEqPC02(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipFlagEqPC02] == nullptr || s_members[PcEquipFlagEqPC02Flag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[PcEquipFlagEqPC02], id, s_members[PcEquipFlagEqPC02Flag]) != 0;
}

void initPcEquipFlagEqPC03(const CBdatWrapper &wrapper) {
  s_members[PcEquipFlagEqPC03] = Bdat::getMember(wrapper.data, "Flag");
  s_members[PcEquipFlagEqPC03Flag] = Bdat::getMember(wrapper.data, "EqPC03");
}

bool isPcEquipFlagEqPC03(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipFlagEqPC03] == nullptr || s_members[PcEquipFlagEqPC03Flag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[PcEquipFlagEqPC03], id, s_members[PcEquipFlagEqPC03Flag]) != 0;
}

void initPcEquipFlagEqPC04(const CBdatWrapper &wrapper) {
  s_members[PcEquipFlagEqPC04] = Bdat::getMember(wrapper.data, "Flag");
  s_members[PcEquipFlagEqPC04Flag] = Bdat::getMember(wrapper.data, "EqPC04");
}

bool isPcEquipFlagEqPC04(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipFlagEqPC04] == nullptr || s_members[PcEquipFlagEqPC04Flag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[PcEquipFlagEqPC04], id, s_members[PcEquipFlagEqPC04Flag]) != 0;
}

void initPcEquipFlagEqPC05(const CBdatWrapper &wrapper) {
  s_members[PcEquipFlagEqPC05] = Bdat::getMember(wrapper.data, "Flag");
  s_members[PcEquipFlagEqPC05Flag] = Bdat::getMember(wrapper.data, "EqPC05");
}

bool isPcEquipFlagEqPC05(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipFlagEqPC05] == nullptr || s_members[PcEquipFlagEqPC05Flag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[PcEquipFlagEqPC05], id, s_members[PcEquipFlagEqPC05Flag]) != 0;
}

void initPcEquipFlagEqPC06(const CBdatWrapper &wrapper) {
  s_members[PcEquipFlagEqPC06] = Bdat::getMember(wrapper.data, "Flag");
  s_members[PcEquipFlagEqPC06Flag] = Bdat::getMember(wrapper.data, "EqPC06");
}

bool isPcEquipFlagEqPC06(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipFlagEqPC06] == nullptr || s_members[PcEquipFlagEqPC06Flag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[PcEquipFlagEqPC06], id, s_members[PcEquipFlagEqPC06Flag]) != 0;
}

void initPcEquipFlagEqPC07(const CBdatWrapper &wrapper) {
  s_members[PcEquipFlagEqPC07] = Bdat::getMember(wrapper.data, "Flag");
  s_members[PcEquipFlagEqPC07Flag] = Bdat::getMember(wrapper.data, "EqPC07");
}

bool isPcEquipFlagEqPC07(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipFlagEqPC07] == nullptr || s_members[PcEquipFlagEqPC07Flag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[PcEquipFlagEqPC07], id, s_members[PcEquipFlagEqPC07Flag]) != 0;
}

void initPcEquipFlagEqPC08(const CBdatWrapper &wrapper) {
  s_members[PcEquipFlagEqPC08] = Bdat::getMember(wrapper.data, "Flag");
  s_members[PcEquipFlagEqPC08Flag] = Bdat::getMember(wrapper.data, "EqPC08");
}

bool isPcEquipFlagEqPC08(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipFlagEqPC08] == nullptr || s_members[PcEquipFlagEqPC08Flag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[PcEquipFlagEqPC08], id, s_members[PcEquipFlagEqPC08Flag]) != 0;
}

void initPcEquipFlagEqPC09(const CBdatWrapper &wrapper) {
  s_members[PcEquipFlagEqPC09] = Bdat::getMember(wrapper.data, "Flag");
  s_members[PcEquipFlagEqPC09Flag] = Bdat::getMember(wrapper.data, "EqPC09");
}

bool isPcEquipFlagEqPC09(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipFlagEqPC09] == nullptr || s_members[PcEquipFlagEqPC09Flag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[PcEquipFlagEqPC09], id, s_members[PcEquipFlagEqPC09Flag]) != 0;
}

void initPcEquipIcon(const CBdatWrapper &wrapper) { s_members[PcEquipIcon] = Bdat::getMember(wrapper.data, "Icon"); }

u32 getPcEquipIcon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipIcon] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcEquipIcon], id, 1).valueU8;
}

void initPcEquipsortJP(const CBdatWrapper &wrapper) { s_members[PcEquipsortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getPcEquipsortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[PcEquipsortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[PcEquipsortJP], id, 3).valueU32;
}

void initSalvageName(const CBdatWrapper &wrapper) { s_members[SalvageName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getSalvageName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[SalvageName] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[SalvageName], id, 2).valueU16;
}

void initSalvageCaption(const CBdatWrapper &wrapper) { s_members[SalvageCaption] = Bdat::getMember(wrapper.data, "Caption"); }

u32 getSalvageCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[SalvageCaption] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[SalvageCaption], id, 2).valueU16;
}

void initSalvageRarity(const CBdatWrapper &wrapper) { s_members[SalvageRarity] = Bdat::getMember(wrapper.data, "Rarity"); }

u32 getSalvageRarity(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[SalvageRarity] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[SalvageRarity], id, 1).valueU8;
}

void initSalvagePrice(const CBdatWrapper &wrapper) { s_members[SalvagePrice] = Bdat::getMember(wrapper.data, "Price"); }

u32 getSalvagePrice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[SalvagePrice] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[SalvagePrice], id, 3).valueU32;
}

void initSalvageQuest(const CBdatWrapper &wrapper) { s_members[SalvageQuest] = Bdat::getMember(wrapper.data, "Quest"); }

u32 getSalvageQuest(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[SalvageQuest] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[SalvageQuest], id, 1).valueU8;
}

void initSalvageNoSell(const CBdatWrapper &wrapper) { s_members[SalvageNoSell] = Bdat::getMember(wrapper.data, "NoSell"); }

u32 getSalvageNoSell(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[SalvageNoSell] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[SalvageNoSell], id, 1).valueU8;
}

void initSalvagesortJP(const CBdatWrapper &wrapper) { s_members[SalvagesortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getSalvagesortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[SalvagesortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[SalvagesortJP], id, 3).valueU32;
}

void initHealPotDropRsc(const CBdatWrapper &wrapper) { s_members[HealPotDropRsc] = Bdat::getMember(wrapper.data, "DropRsc"); }

u32 getHealPotDropRsc(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[HealPotDropRsc] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[HealPotDropRsc], id, 1).valueU8;
}

void initHealPotHpRatio(const CBdatWrapper &wrapper) { s_members[HealPotHpRatio] = Bdat::getMember(wrapper.data, "HpRatio"); }

u32 getHealPotHpRatio(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[HealPotHpRatio] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[HealPotHpRatio], id, 1).valueU8;
}

void initTresureName(const CBdatWrapper &wrapper) { s_members[TresureName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getTresureName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TresureName] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TresureName], id, 2).valueU16;
}

void initTresureCaption(const CBdatWrapper &wrapper) { s_members[TresureCaption] = Bdat::getMember(wrapper.data, "Caption"); }

u32 getTresureCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TresureCaption] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TresureCaption], id, 2).valueU16;
}

void initTresureCategory(const CBdatWrapper &wrapper) { s_members[TresureCategory] = Bdat::getMember(wrapper.data, "Category"); }

u32 getTresureCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TresureCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TresureCategory], id, 1).valueU8;
}

void initTresureGraphic(const CBdatWrapper &wrapper) { s_members[TresureGraphic] = Bdat::getMember(wrapper.data, "Graphic"); }

u32 getTresureGraphic(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TresureGraphic] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TresureGraphic], id, 2).valueU16;
}

void initTresureZone(const CBdatWrapper &wrapper) { s_members[TresureZone] = Bdat::getMember(wrapper.data, "Zone"); }

u32 getTresureZone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TresureZone] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TresureZone], id, 2).valueU16;
}

void initTresureRarity(const CBdatWrapper &wrapper) { s_members[TresureRarity] = Bdat::getMember(wrapper.data, "Rarity"); }

u32 getTresureRarity(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TresureRarity] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TresureRarity], id, 1).valueU8;
}

void initTresurePrice(const CBdatWrapper &wrapper) { s_members[TresurePrice] = Bdat::getMember(wrapper.data, "Price"); }

u32 getTresurePrice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TresurePrice] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TresurePrice], id, 3).valueU32;
}

void initTresureFlag(const CBdatWrapper &wrapper) { s_members[TresureFlag] = Bdat::getMember(wrapper.data, "Flag"); }

u32 getTresureFlag(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TresureFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TresureFlag], id, 2).valueU16;
}

void initTresureNoMultiple(const CBdatWrapper &wrapper) { s_members[TresureNoMultiple] = Bdat::getMember(wrapper.data, "NoMultiple"); }

u32 getTresureNoMultiple(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TresureNoMultiple] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TresureNoMultiple], id, 2).valueU16;
}

void initTresureClearNewGame(const CBdatWrapper &wrapper) { s_members[TresureClearNewGame] = Bdat::getMember(wrapper.data, "ClearNewGame"); }

u32 getTresureClearNewGame(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TresureClearNewGame] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TresureClearNewGame], id, 1).valueU8;
}

void initTresuresortJP(const CBdatWrapper &wrapper) { s_members[TresuresortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getTresuresortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TresuresortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TresuresortJP], id, 3).valueU32;
}

void initFavoriteName(const CBdatWrapper &wrapper) { s_members[FavoriteName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getFavoriteName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FavoriteName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FavoriteName], id, 2).valueU16;
}

void initFavoriteCaption(const CBdatWrapper &wrapper) { s_members[FavoriteCaption] = Bdat::getMember(wrapper.data, "Caption"); }

u32 getFavoriteCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FavoriteCaption] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FavoriteCaption], id, 2).valueU16;
}

void initFavoriteCategory(const CBdatWrapper &wrapper) { s_members[FavoriteCategory] = Bdat::getMember(wrapper.data, "Category"); }

u32 getFavoriteCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FavoriteCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FavoriteCategory], id, 1).valueU8;
}

void initFavoriteZone(const CBdatWrapper &wrapper) { s_members[FavoriteZone] = Bdat::getMember(wrapper.data, "Zone"); }

u32 getFavoriteZone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FavoriteZone] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FavoriteZone], id, 2).valueU16;
}

void initFavoriteRarity(const CBdatWrapper &wrapper) { s_members[FavoriteRarity] = Bdat::getMember(wrapper.data, "Rarity"); }

u32 getFavoriteRarity(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FavoriteRarity] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FavoriteRarity], id, 1).valueU8;
}

void initFavoritePrice(const CBdatWrapper &wrapper) { s_members[FavoritePrice] = Bdat::getMember(wrapper.data, "Price"); }

u32 getFavoritePrice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FavoritePrice] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FavoritePrice], id, 3).valueU32;
}

void initFavoriteType(const CBdatWrapper &wrapper) { s_members[FavoriteType] = Bdat::getMember(wrapper.data, "Type"); }

u32 getFavoriteType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FavoriteType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FavoriteType], id, 2).valueU16;
}

void initFavoriteTime(const CBdatWrapper &wrapper) { s_members[FavoriteTime] = Bdat::getMember(wrapper.data, "Time"); }

u32 getFavoriteTime(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FavoriteTime] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FavoriteTime], id, 2).valueU16;
}

void initFavoriteValueMax(const CBdatWrapper &wrapper) { s_members[FavoriteValueMax] = Bdat::getMember(wrapper.data, "ValueMax"); }

u32 getFavoriteValueMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FavoriteValueMax] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FavoriteValueMax], id, 1).valueU8;
}

void initFavoriteTrustPoint(const CBdatWrapper &wrapper) { s_members[FavoriteTrustPoint] = Bdat::getMember(wrapper.data, "TrustPoint"); }

u32 getFavoriteTrustPoint(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FavoriteTrustPoint] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FavoriteTrustPoint], id, 2).valueU16;
}

void initFavoritesortJP(const CBdatWrapper &wrapper) { s_members[FavoritesortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getFavoritesortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FavoritesortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FavoritesortJP], id, 3).valueU32;
}

void initOwnerBonusCaption(const CBdatWrapper &wrapper) { s_members[OwnerBonusCaption] = Bdat::getMember(wrapper.data, "Caption"); }

u32 getOwnerBonusCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OwnerBonusCaption] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OwnerBonusCaption], id, 2).valueU16;
}

void initOwnerBonusType(const CBdatWrapper &wrapper) { s_members[OwnerBonusType] = Bdat::getMember(wrapper.data, "Type"); }

u32 getOwnerBonusType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OwnerBonusType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OwnerBonusType], id, 2).valueU16;
}

void initOwnerBonusValue(const CBdatWrapper &wrapper) { s_members[OwnerBonusValue] = Bdat::getMember(wrapper.data, "Value"); }

u32 getOwnerBonusValue(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OwnerBonusValue] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OwnerBonusValue], id, 2).valueU16;
}

void initOwnerBonusParamMax(const CBdatWrapper &wrapper) { s_members[OwnerBonusParamMax] = Bdat::getMember(wrapper.data, "Max"); }

u32 getOwnerBonusParamMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[OwnerBonusParamMax] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[OwnerBonusParamMax], id, 2).valueU16;
}

void initITM_HanaRoleName(const CBdatWrapper &wrapper) { s_members[ITM_HanaRoleName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getITM_HanaRoleName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRoleName], id, 1).valueU8;
}

void initITM_HanaRoleRole(const CBdatWrapper &wrapper) { s_members[ITM_HanaRoleRole] = Bdat::getMember(wrapper.data, "Role"); }

u32 getITM_HanaRoleRole(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleRole] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRoleRole], id, 1).valueU8;
}

void initITM_HanaRolePArmor(const CBdatWrapper &wrapper) { s_members[ITM_HanaRolePArmor] = Bdat::getMember(wrapper.data, "PArmor"); }

u32 getITM_HanaRolePArmor(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRolePArmor] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRolePArmor], id, 1).valueU8;
}

void initITM_HanaRoleEArmor(const CBdatWrapper &wrapper) { s_members[ITM_HanaRoleEArmor] = Bdat::getMember(wrapper.data, "EArmor"); }

u32 getITM_HanaRoleEArmor(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleEArmor] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRoleEArmor], id, 1).valueU8;
}

void initITM_HanaRoleHpMaxRev(const CBdatWrapper &wrapper) { s_members[ITM_HanaRoleHpMaxRev] = Bdat::getMember(wrapper.data, "HpMaxRev"); }

u32 getITM_HanaRoleHpMaxRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleHpMaxRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRoleHpMaxRev], id, 1).valueU8;
}

void initITM_HanaRoleStrengthRev(const CBdatWrapper &wrapper) { s_members[ITM_HanaRoleStrengthRev] = Bdat::getMember(wrapper.data, "StrengthRev"); }

u32 getITM_HanaRoleStrengthRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleStrengthRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRoleStrengthRev], id, 1).valueU8;
}

void initITM_HanaRolePowEtherRev(const CBdatWrapper &wrapper) { s_members[ITM_HanaRolePowEtherRev] = Bdat::getMember(wrapper.data, "PowEtherRev"); }

u32 getITM_HanaRolePowEtherRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRolePowEtherRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRolePowEtherRev], id, 1).valueU8;
}

void initITM_HanaRoleDexRev(const CBdatWrapper &wrapper) { s_members[ITM_HanaRoleDexRev] = Bdat::getMember(wrapper.data, "DexRev"); }

u32 getITM_HanaRoleDexRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleDexRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRoleDexRev], id, 1).valueU8;
}

void initITM_HanaRoleAgilityRev(const CBdatWrapper &wrapper) { s_members[ITM_HanaRoleAgilityRev] = Bdat::getMember(wrapper.data, "AgilityRev"); }

u32 getITM_HanaRoleAgilityRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleAgilityRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRoleAgilityRev], id, 1).valueU8;
}

void initITM_HanaRoleLuckRev(const CBdatWrapper &wrapper) { s_members[ITM_HanaRoleLuckRev] = Bdat::getMember(wrapper.data, "LuckRev"); }

u32 getITM_HanaRoleLuckRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleLuckRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRoleLuckRev], id, 1).valueU8;
}

void initITM_HanaRoleAutoHate(const CBdatWrapper &wrapper) { s_members[ITM_HanaRoleAutoHate] = Bdat::getMember(wrapper.data, "AutoHate"); }

s32 getITM_HanaRoleAutoHate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleAutoHate] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRoleAutoHate], id, 4).valueS8;
}

void initITM_HanaRoleArtsHate(const CBdatWrapper &wrapper) { s_members[ITM_HanaRoleArtsHate] = Bdat::getMember(wrapper.data, "ArtsHate"); }

s32 getITM_HanaRoleArtsHate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleArtsHate] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRoleArtsHate], id, 4).valueS8;
}

void initITM_HanaRoleFlagJS(const CBdatWrapper &wrapper) {
  s_members[ITM_HanaRoleFlagJS] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ITM_HanaRoleFlagJSFlag] = Bdat::getMember(wrapper.data, "JS");
}

bool isITM_HanaRoleFlagJS(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleFlagJS] == nullptr || s_members[ITM_HanaRoleFlagJSFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ITM_HanaRoleFlagJS], id, s_members[ITM_HanaRoleFlagJSFlag]) != 0;
}

void initITM_HanaRoleFlagJK(const CBdatWrapper &wrapper) {
  s_members[ITM_HanaRoleFlagJK] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ITM_HanaRoleFlagJKFlag] = Bdat::getMember(wrapper.data, "JK");
}

bool isITM_HanaRoleFlagJK(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleFlagJK] == nullptr || s_members[ITM_HanaRoleFlagJKFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ITM_HanaRoleFlagJK], id, s_members[ITM_HanaRoleFlagJKFlag]) != 0;
}

void initITM_HanaRoleFlagJD(const CBdatWrapper &wrapper) {
  s_members[ITM_HanaRoleFlagJD] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ITM_HanaRoleFlagJDFlag] = Bdat::getMember(wrapper.data, "JD");
}

bool isITM_HanaRoleFlagJD(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleFlagJD] == nullptr || s_members[ITM_HanaRoleFlagJDFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ITM_HanaRoleFlagJD], id, s_members[ITM_HanaRoleFlagJDFlag]) != 0;
}

void initITM_HanaRoleNeedPow(const CBdatWrapper &wrapper) { s_members[ITM_HanaRoleNeedPow] = Bdat::getMember(wrapper.data, "NeedPow"); }

u32 getITM_HanaRoleNeedPow(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleNeedPow] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRoleNeedPow], id, 2).valueU16;
}

void initITM_HanaRoleNeedEther(const CBdatWrapper &wrapper) { s_members[ITM_HanaRoleNeedEther] = Bdat::getMember(wrapper.data, "NeedEther"); }

u32 getITM_HanaRoleNeedEther(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleNeedEther] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRoleNeedEther], id, 3).valueU32;
}

void initITM_HanaRoleDustEther(const CBdatWrapper &wrapper) { s_members[ITM_HanaRoleDustEther] = Bdat::getMember(wrapper.data, "DustEther"); }

u32 getITM_HanaRoleDustEther(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleDustEther] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRoleDustEther], id, 3).valueU32;
}

void initITM_HanaRoleCondition(const CBdatWrapper &wrapper) { s_members[ITM_HanaRoleCondition] = Bdat::getMember(wrapper.data, "Condition"); }

u32 getITM_HanaRoleCondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleCondition] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRoleCondition], id, 2).valueU16;
}

void initITM_HanaRoleUI(const CBdatWrapper &wrapper) { s_members[ITM_HanaRoleUI] = Bdat::getMember(wrapper.data, "UI"); }

const char *getITM_HanaRoleUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRoleUI] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRoleUI], id, 7).valueString;
}

void initITM_HanaRolesortJP(const CBdatWrapper &wrapper) { s_members[ITM_HanaRolesortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getITM_HanaRolesortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaRolesortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaRolesortJP], id, 3).valueU32;
}

void initITM_HanaAtrName(const CBdatWrapper &wrapper) { s_members[ITM_HanaAtrName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getITM_HanaAtrName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAtrName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaAtrName], id, 1).valueU8;
}

void initITM_HanaAtrAtr(const CBdatWrapper &wrapper) { s_members[ITM_HanaAtrAtr] = Bdat::getMember(wrapper.data, "Atr"); }

u32 getITM_HanaAtrAtr(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAtrAtr] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaAtrAtr], id, 1).valueU8;
}

void initITM_HanaAtrFlagJS(const CBdatWrapper &wrapper) {
  s_members[ITM_HanaAtrFlagJS] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ITM_HanaAtrFlagJSFlag] = Bdat::getMember(wrapper.data, "JS");
}

bool isITM_HanaAtrFlagJS(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAtrFlagJS] == nullptr || s_members[ITM_HanaAtrFlagJSFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ITM_HanaAtrFlagJS], id, s_members[ITM_HanaAtrFlagJSFlag]) != 0;
}

void initITM_HanaAtrFlagJK(const CBdatWrapper &wrapper) {
  s_members[ITM_HanaAtrFlagJK] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ITM_HanaAtrFlagJKFlag] = Bdat::getMember(wrapper.data, "JK");
}

bool isITM_HanaAtrFlagJK(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAtrFlagJK] == nullptr || s_members[ITM_HanaAtrFlagJKFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ITM_HanaAtrFlagJK], id, s_members[ITM_HanaAtrFlagJKFlag]) != 0;
}

void initITM_HanaAtrFlagJD(const CBdatWrapper &wrapper) {
  s_members[ITM_HanaAtrFlagJD] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ITM_HanaAtrFlagJDFlag] = Bdat::getMember(wrapper.data, "JD");
}

bool isITM_HanaAtrFlagJD(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAtrFlagJD] == nullptr || s_members[ITM_HanaAtrFlagJDFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ITM_HanaAtrFlagJD], id, s_members[ITM_HanaAtrFlagJDFlag]) != 0;
}

void initITM_HanaAtrNeedPow(const CBdatWrapper &wrapper) { s_members[ITM_HanaAtrNeedPow] = Bdat::getMember(wrapper.data, "NeedPow"); }

u32 getITM_HanaAtrNeedPow(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAtrNeedPow] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaAtrNeedPow], id, 2).valueU16;
}

void initITM_HanaAtrNeedEther(const CBdatWrapper &wrapper) { s_members[ITM_HanaAtrNeedEther] = Bdat::getMember(wrapper.data, "NeedEther"); }

u32 getITM_HanaAtrNeedEther(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAtrNeedEther] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaAtrNeedEther], id, 3).valueU32;
}

void initITM_HanaAtrDustEther(const CBdatWrapper &wrapper) { s_members[ITM_HanaAtrDustEther] = Bdat::getMember(wrapper.data, "DustEther"); }

u32 getITM_HanaAtrDustEther(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAtrDustEther] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaAtrDustEther], id, 3).valueU32;
}

void initITM_HanaAtrCondition(const CBdatWrapper &wrapper) { s_members[ITM_HanaAtrCondition] = Bdat::getMember(wrapper.data, "Condition"); }

u32 getITM_HanaAtrCondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAtrCondition] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaAtrCondition], id, 2).valueU16;
}

void initITM_HanaAtrUI(const CBdatWrapper &wrapper) { s_members[ITM_HanaAtrUI] = Bdat::getMember(wrapper.data, "UI"); }

const char *getITM_HanaAtrUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAtrUI] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ITM_HanaAtrUI], id, 7).valueString;
}

void initITM_HanaAtrsortJP(const CBdatWrapper &wrapper) { s_members[ITM_HanaAtrsortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getITM_HanaAtrsortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAtrsortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaAtrsortJP], id, 3).valueU32;
}

void initITM_HanaArtsEnhName(const CBdatWrapper &wrapper) { s_members[ITM_HanaArtsEnhName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getITM_HanaArtsEnhName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaArtsEnhName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaArtsEnhName], id, 2).valueU16;
}

void initITM_HanaArtsEnhEnhance(const CBdatWrapper &wrapper) { s_members[ITM_HanaArtsEnhEnhance] = Bdat::getMember(wrapper.data, "Enhance"); }

u32 getITM_HanaArtsEnhEnhance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaArtsEnhEnhance] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaArtsEnhEnhance], id, 2).valueU16;
}

void initITM_HanaArtsEnhFlagJS(const CBdatWrapper &wrapper) {
  s_members[ITM_HanaArtsEnhFlagJS] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ITM_HanaArtsEnhFlagJSFlag] = Bdat::getMember(wrapper.data, "JS");
}

bool isITM_HanaArtsEnhFlagJS(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaArtsEnhFlagJS] == nullptr || s_members[ITM_HanaArtsEnhFlagJSFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ITM_HanaArtsEnhFlagJS], id, s_members[ITM_HanaArtsEnhFlagJSFlag]) != 0;
}

void initITM_HanaArtsEnhFlagJK(const CBdatWrapper &wrapper) {
  s_members[ITM_HanaArtsEnhFlagJK] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ITM_HanaArtsEnhFlagJKFlag] = Bdat::getMember(wrapper.data, "JK");
}

bool isITM_HanaArtsEnhFlagJK(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaArtsEnhFlagJK] == nullptr || s_members[ITM_HanaArtsEnhFlagJKFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ITM_HanaArtsEnhFlagJK], id, s_members[ITM_HanaArtsEnhFlagJKFlag]) != 0;
}

void initITM_HanaArtsEnhFlagJD(const CBdatWrapper &wrapper) {
  s_members[ITM_HanaArtsEnhFlagJD] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ITM_HanaArtsEnhFlagJDFlag] = Bdat::getMember(wrapper.data, "JD");
}

bool isITM_HanaArtsEnhFlagJD(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaArtsEnhFlagJD] == nullptr || s_members[ITM_HanaArtsEnhFlagJDFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ITM_HanaArtsEnhFlagJD], id, s_members[ITM_HanaArtsEnhFlagJDFlag]) != 0;
}

void initITM_HanaArtsEnhNeedPow(const CBdatWrapper &wrapper) { s_members[ITM_HanaArtsEnhNeedPow] = Bdat::getMember(wrapper.data, "NeedPow"); }

u32 getITM_HanaArtsEnhNeedPow(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaArtsEnhNeedPow] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaArtsEnhNeedPow], id, 2).valueU16;
}

void initITM_HanaArtsEnhNeedEther(const CBdatWrapper &wrapper) { s_members[ITM_HanaArtsEnhNeedEther] = Bdat::getMember(wrapper.data, "NeedEther"); }

u32 getITM_HanaArtsEnhNeedEther(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaArtsEnhNeedEther] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaArtsEnhNeedEther], id, 3).valueU32;
}

void initITM_HanaArtsEnhDustEther(const CBdatWrapper &wrapper) { s_members[ITM_HanaArtsEnhDustEther] = Bdat::getMember(wrapper.data, "DustEther"); }

u32 getITM_HanaArtsEnhDustEther(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaArtsEnhDustEther] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaArtsEnhDustEther], id, 3).valueU32;
}

void initITM_HanaArtsEnhCondition(const CBdatWrapper &wrapper) { s_members[ITM_HanaArtsEnhCondition] = Bdat::getMember(wrapper.data, "Condition"); }

u32 getITM_HanaArtsEnhCondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaArtsEnhCondition] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaArtsEnhCondition], id, 2).valueU16;
}

void initITM_HanaArtsEnhUI(const CBdatWrapper &wrapper) { s_members[ITM_HanaArtsEnhUI] = Bdat::getMember(wrapper.data, "UI"); }

const char *getITM_HanaArtsEnhUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaArtsEnhUI] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ITM_HanaArtsEnhUI], id, 7).valueString;
}

void initITM_HanaArtsEnhsortJP(const CBdatWrapper &wrapper) { s_members[ITM_HanaArtsEnhsortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getITM_HanaArtsEnhsortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaArtsEnhsortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaArtsEnhsortJP], id, 3).valueU32;
}

void initITM_HanaNArtsSetName(const CBdatWrapper &wrapper) { s_members[ITM_HanaNArtsSetName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getITM_HanaNArtsSetName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaNArtsSetName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaNArtsSetName], id, 1).valueU8;
}

void initITM_HanaNArtsSetNArts(const CBdatWrapper &wrapper) { s_members[ITM_HanaNArtsSetNArts] = Bdat::getMember(wrapper.data, "NArts"); }

u32 getITM_HanaNArtsSetNArts(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaNArtsSetNArts] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaNArtsSetNArts], id, 1).valueU8;
}

void initITM_HanaNArtsSetNArtsRecastRev(const CBdatWrapper &wrapper) {
  s_members[ITM_HanaNArtsSetNArtsRecastRev] = Bdat::getMember(wrapper.data, "NArtsRecastRev");
}

u32 getITM_HanaNArtsSetNArtsRecastRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaNArtsSetNArtsRecastRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaNArtsSetNArtsRecastRev], id, 1).valueU8;
}

void initITM_HanaNArtsSetFlagJS(const CBdatWrapper &wrapper) {
  s_members[ITM_HanaNArtsSetFlagJS] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ITM_HanaNArtsSetFlagJSFlag] = Bdat::getMember(wrapper.data, "JS");
}

bool isITM_HanaNArtsSetFlagJS(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaNArtsSetFlagJS] == nullptr || s_members[ITM_HanaNArtsSetFlagJSFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ITM_HanaNArtsSetFlagJS], id, s_members[ITM_HanaNArtsSetFlagJSFlag]) != 0;
}

void initITM_HanaNArtsSetFlagJK(const CBdatWrapper &wrapper) {
  s_members[ITM_HanaNArtsSetFlagJK] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ITM_HanaNArtsSetFlagJKFlag] = Bdat::getMember(wrapper.data, "JK");
}

bool isITM_HanaNArtsSetFlagJK(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaNArtsSetFlagJK] == nullptr || s_members[ITM_HanaNArtsSetFlagJKFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ITM_HanaNArtsSetFlagJK], id, s_members[ITM_HanaNArtsSetFlagJKFlag]) != 0;
}

void initITM_HanaNArtsSetFlagJD(const CBdatWrapper &wrapper) {
  s_members[ITM_HanaNArtsSetFlagJD] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ITM_HanaNArtsSetFlagJDFlag] = Bdat::getMember(wrapper.data, "JD");
}

bool isITM_HanaNArtsSetFlagJD(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaNArtsSetFlagJD] == nullptr || s_members[ITM_HanaNArtsSetFlagJDFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ITM_HanaNArtsSetFlagJD], id, s_members[ITM_HanaNArtsSetFlagJDFlag]) != 0;
}

void initITM_HanaNArtsSetNeedPow(const CBdatWrapper &wrapper) { s_members[ITM_HanaNArtsSetNeedPow] = Bdat::getMember(wrapper.data, "NeedPow"); }

u32 getITM_HanaNArtsSetNeedPow(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaNArtsSetNeedPow] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaNArtsSetNeedPow], id, 2).valueU16;
}

void initITM_HanaNArtsSetNeedEther(const CBdatWrapper &wrapper) { s_members[ITM_HanaNArtsSetNeedEther] = Bdat::getMember(wrapper.data, "NeedEther"); }

u32 getITM_HanaNArtsSetNeedEther(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaNArtsSetNeedEther] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaNArtsSetNeedEther], id, 3).valueU32;
}

void initITM_HanaNArtsSetDustEther(const CBdatWrapper &wrapper) { s_members[ITM_HanaNArtsSetDustEther] = Bdat::getMember(wrapper.data, "DustEther"); }

u32 getITM_HanaNArtsSetDustEther(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaNArtsSetDustEther] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaNArtsSetDustEther], id, 3).valueU32;
}

void initITM_HanaNArtsSetCondition(const CBdatWrapper &wrapper) { s_members[ITM_HanaNArtsSetCondition] = Bdat::getMember(wrapper.data, "Condition"); }

u32 getITM_HanaNArtsSetCondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaNArtsSetCondition] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaNArtsSetCondition], id, 2).valueU16;
}

void initITM_HanaNArtsSetUI(const CBdatWrapper &wrapper) { s_members[ITM_HanaNArtsSetUI] = Bdat::getMember(wrapper.data, "UI"); }

const char *getITM_HanaNArtsSetUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaNArtsSetUI] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ITM_HanaNArtsSetUI], id, 7).valueString;
}

void initITM_HanaNArtsSetsortJP(const CBdatWrapper &wrapper) { s_members[ITM_HanaNArtsSetsortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getITM_HanaNArtsSetsortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaNArtsSetsortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaNArtsSetsortJP], id, 3).valueU32;
}

void initITM_HanaAssistName(const CBdatWrapper &wrapper) { s_members[ITM_HanaAssistName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getITM_HanaAssistName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAssistName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaAssistName], id, 2).valueU16;
}

void initITM_HanaAssistEnhance(const CBdatWrapper &wrapper) { s_members[ITM_HanaAssistEnhance] = Bdat::getMember(wrapper.data, "Enhance"); }

u32 getITM_HanaAssistEnhance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAssistEnhance] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaAssistEnhance], id, 2).valueU16;
}

void initITM_HanaAssistEnhanceCategory(const CBdatWrapper &wrapper) {
  s_members[ITM_HanaAssistEnhanceCategory] = Bdat::getMember(wrapper.data, "EnhanceCategory");
}

u32 getITM_HanaAssistEnhanceCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAssistEnhanceCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaAssistEnhanceCategory], id, 1).valueU8;
}

void initITM_HanaAssistFlagJS(const CBdatWrapper &wrapper) {
  s_members[ITM_HanaAssistFlagJS] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ITM_HanaAssistFlagJSFlag] = Bdat::getMember(wrapper.data, "JS");
}

bool isITM_HanaAssistFlagJS(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAssistFlagJS] == nullptr || s_members[ITM_HanaAssistFlagJSFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ITM_HanaAssistFlagJS], id, s_members[ITM_HanaAssistFlagJSFlag]) != 0;
}

void initITM_HanaAssistFlagJK(const CBdatWrapper &wrapper) {
  s_members[ITM_HanaAssistFlagJK] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ITM_HanaAssistFlagJKFlag] = Bdat::getMember(wrapper.data, "JK");
}

bool isITM_HanaAssistFlagJK(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAssistFlagJK] == nullptr || s_members[ITM_HanaAssistFlagJKFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ITM_HanaAssistFlagJK], id, s_members[ITM_HanaAssistFlagJKFlag]) != 0;
}

void initITM_HanaAssistFlagJD(const CBdatWrapper &wrapper) {
  s_members[ITM_HanaAssistFlagJD] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ITM_HanaAssistFlagJDFlag] = Bdat::getMember(wrapper.data, "JD");
}

bool isITM_HanaAssistFlagJD(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAssistFlagJD] == nullptr || s_members[ITM_HanaAssistFlagJDFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ITM_HanaAssistFlagJD], id, s_members[ITM_HanaAssistFlagJDFlag]) != 0;
}

void initITM_HanaAssistNeedPow(const CBdatWrapper &wrapper) { s_members[ITM_HanaAssistNeedPow] = Bdat::getMember(wrapper.data, "NeedPow"); }

u32 getITM_HanaAssistNeedPow(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAssistNeedPow] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaAssistNeedPow], id, 2).valueU16;
}

void initITM_HanaAssistNeedEther(const CBdatWrapper &wrapper) { s_members[ITM_HanaAssistNeedEther] = Bdat::getMember(wrapper.data, "NeedEther"); }

u32 getITM_HanaAssistNeedEther(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAssistNeedEther] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaAssistNeedEther], id, 3).valueU32;
}

void initITM_HanaAssistDustEther(const CBdatWrapper &wrapper) { s_members[ITM_HanaAssistDustEther] = Bdat::getMember(wrapper.data, "DustEther"); }

u32 getITM_HanaAssistDustEther(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAssistDustEther] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaAssistDustEther], id, 3).valueU32;
}

void initITM_HanaAssistCondition(const CBdatWrapper &wrapper) { s_members[ITM_HanaAssistCondition] = Bdat::getMember(wrapper.data, "Condition"); }

u32 getITM_HanaAssistCondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAssistCondition] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaAssistCondition], id, 2).valueU16;
}

void initITM_HanaAssistUI(const CBdatWrapper &wrapper) { s_members[ITM_HanaAssistUI] = Bdat::getMember(wrapper.data, "UI"); }

const char *getITM_HanaAssistUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAssistUI] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ITM_HanaAssistUI], id, 7).valueString;
}

void initITM_HanaAssistsortJP(const CBdatWrapper &wrapper) { s_members[ITM_HanaAssistsortJP] = Bdat::getMember(wrapper.data, "sortJP"); }

u32 getITM_HanaAssistsortJP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ITM_HanaAssistsortJP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ITM_HanaAssistsortJP], id, 3).valueU32;
}

} // namespace _gfbit

u32 GfBdatItem::getCrystalListStart() const { return Bdat::getIdTop(unknown10->data); }

u32 GfBdatItem::getCrystalListName(u32 id) const { return _gfbit::getCrystalListName(*unknown10, id); }

u32 GfBdatItem::getCrystalListRarity(u32 id) const { return _gfbit::getCrystalListRarity(*unknown10, id); }

u32 GfBdatItem::getCrystalListPrice(u32 id) const { return _gfbit::getCrystalListPrice(*unknown10, id); }

u32 GfBdatItem::getCrystalListCondition(u32 id) const { return _gfbit::getCrystalListCondition(*unknown10, id); }

u32 GfBdatItem::getCrystalListNoMultiple(u32 id) const { return _gfbit::getCrystalListNoMultiple(*unknown10, id); }

u32 GfBdatItem::getCrystalListValueMax(u32 id) const { return _gfbit::getCrystalListValueMax(*unknown10, id); }

u32 GfBdatItem::getCrystalListRareTableProb(u32 id) const { return _gfbit::getCrystalListRareTableProb(*unknown10, id); }

u32 GfBdatItem::getCrystalListRareBladeRev(u32 id) const { return _gfbit::getCrystalListRareBladeRev(*unknown10, id); }

u32 GfBdatItem::getCrystalListCommonPow(u32 id) const { return _gfbit::getCrystalListCommonPow(*unknown10, id); }

u32 GfBdatItem::getCrystalListAssureP(u32 id) const { return _gfbit::getCrystalListAssureP(*unknown10, id); }

u32 GfBdatItem::getCrystalListBladeID(u32 id) const { return _gfbit::getCrystalListBladeID(*unknown10, id); }

u32 GfBdatItem::getCrystalListCommonID(u32 id) const { return _gfbit::getCrystalListCommonID(*unknown10, id); }

u32 GfBdatItem::getCrystalListCommonWpn(u32 id) const { return _gfbit::getCrystalListCommonWpn(*unknown10, id); }

u32 GfBdatItem::getCrystalListCommonAtr(u32 id) const { return _gfbit::getCrystalListCommonAtr(*unknown10, id); }

u32 GfBdatItem::getCrystalListsortJP(u32 id) const { return _gfbit::getCrystalListsortJP(*unknown10, id); }

u32 GfBdatItem::getBoosterStart() const { return Bdat::getIdTop(unknown80->data); }

u32 GfBdatItem::getBoosterName(u32 id) const { return _gfbit::getBoosterName(*unknown80, id); }

u32 GfBdatItem::getBoosterCaption(u32 id) const { return _gfbit::getBoosterCaption(*unknown80, id); }

u32 GfBdatItem::getBoosterCategory(u32 id) const { return _gfbit::getBoosterCategory(*unknown80, id); }

s32 GfBdatItem::getBoosterIdea(u32 id) const { return _gfbit::getBoosterIdea(*unknown80, id); }

u32 GfBdatItem::getBoosterRarity(u32 id) const { return _gfbit::getBoosterRarity(*unknown80, id); }

u32 GfBdatItem::getBoosterPrice(u32 id) const { return _gfbit::getBoosterPrice(*unknown80, id); }

u32 GfBdatItem::getBoosterValueMax(u32 id) const { return _gfbit::getBoosterValueMax(*unknown80, id); }

u32 GfBdatItem::getBoostersortJP(u32 id) const { return _gfbit::getBoostersortJP(*unknown80, id); }

u32 GfBdatItem::getCollectionListStart() const { return Bdat::getIdTop(unknown18->data); }

u32 GfBdatItem::getCollectionListName(u32 id) const { return _gfbit::getCollectionListName(*unknown18, id); }

u32 GfBdatItem::getCollectionListCaption(u32 id) const { return _gfbit::getCollectionListCaption(*unknown18, id); }

u32 GfBdatItem::getCollectionListCategory(u32 id) const { return _gfbit::getCollectionListCategory(*unknown18, id); }

u32 GfBdatItem::getCollectionListZone(u32 id) const { return _gfbit::getCollectionListZone(*unknown18, id); }

u32 GfBdatItem::getCollectionListRarity(u32 id) const { return _gfbit::getCollectionListRarity(*unknown18, id); }

u32 GfBdatItem::getCollectionListPrice(u32 id) const { return _gfbit::getCollectionListPrice(*unknown18, id); }

u32 GfBdatItem::getCollectionListsortJP(u32 id) const { return _gfbit::getCollectionListsortJP(*unknown18, id); }

u32 GfBdatItem::getEmptyOrbStart() const { return Bdat::getIdTop(unknown20->data); }

u32 GfBdatItem::getEmptyOrbName(u32 id) const { return _gfbit::getEmptyOrbName(*unknown20, id); }

const char *GfBdatItem::getEmptyOrbDebugName(u32 id) const { return _gfbit::getEmptyOrbDebugName(*unknown20, id); }

u32 GfBdatItem::getEmptyOrbPrice(u32 id) const { return _gfbit::getEmptyOrbPrice(*unknown20, id); }

u32 GfBdatItem::getEmptyOrbRarity(u32 id) const { return _gfbit::getEmptyOrbRarity(*unknown20, id); }

bool GfBdatItem::isEmptyOrbFlagNoSell(u32 id) const { return _gfbit::isEmptyOrbFlagNoSell(*unknown20, id); }

u32 GfBdatItem::getEmptyOrbRecipe(u32 id) const { return _gfbit::getEmptyOrbRecipe(*unknown20, id); }

u32 GfBdatItem::getEmptyOrbEquipItemID(u32 id) const { return _gfbit::getEmptyOrbEquipItemID(*unknown20, id); }

u32 GfBdatItem::getEmptyOrbsortJP(u32 id) const { return _gfbit::getEmptyOrbsortJP(*unknown20, id); }

u32 GfBdatItem::getOrbRecipeStart() const { return Bdat::getIdTop(unknown28->data); }

u32 GfBdatItem::getOrbRecipeRecipeType(u32 id) const { return _gfbit::getOrbRecipeRecipeType(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeRarity(u32 id) const { return _gfbit::getOrbRecipeRarity(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeRscCat(u32 id) const { return _gfbit::getOrbRecipeRscCat(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeAssortNumber(u32 id) const { return _gfbit::getOrbRecipeAssortNumber(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeItemID1(u32 id) const { return _gfbit::getOrbRecipeItemID1(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeItemNumber1(u32 id) const { return _gfbit::getOrbRecipeItemNumber1(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeItemID2(u32 id) const { return _gfbit::getOrbRecipeItemID2(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeItemNumber2(u32 id) const { return _gfbit::getOrbRecipeItemNumber2(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeItemID3(u32 id) const { return _gfbit::getOrbRecipeItemID3(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeItemNumber3(u32 id) const { return _gfbit::getOrbRecipeItemNumber3(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeItemID4(u32 id) const { return _gfbit::getOrbRecipeItemID4(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeItemNumber4(u32 id) const { return _gfbit::getOrbRecipeItemNumber4(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeItemID5(u32 id) const { return _gfbit::getOrbRecipeItemID5(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeItemNumber5(u32 id) const { return _gfbit::getOrbRecipeItemNumber5(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeItemID6(u32 id) const { return _gfbit::getOrbRecipeItemID6(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeItemNumber6(u32 id) const { return _gfbit::getOrbRecipeItemNumber6(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeItemID7(u32 id) const { return _gfbit::getOrbRecipeItemID7(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeItemNumber7(u32 id) const { return _gfbit::getOrbRecipeItemNumber7(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeItemID8(u32 id) const { return _gfbit::getOrbRecipeItemID8(*unknown28, id); }

u32 GfBdatItem::getOrbRecipeItemNumber8(u32 id) const { return _gfbit::getOrbRecipeItemNumber8(*unknown28, id); }

u32 GfBdatItem::getEquipOrbStart() const { return Bdat::getIdTop(unknown50->data); }

u32 GfBdatItem::getEquipOrbName(u32 id) const { return _gfbit::getEquipOrbName(*unknown50, id); }

const char *GfBdatItem::getEquipOrbDebugName(u32 id) const { return _gfbit::getEquipOrbDebugName(*unknown50, id); }

u32 GfBdatItem::getEquipOrbEnhance(u32 id) const { return _gfbit::getEquipOrbEnhance(*unknown50, id); }

u32 GfBdatItem::getEquipOrbEnhanceCategory(u32 id) const { return _gfbit::getEquipOrbEnhanceCategory(*unknown50, id); }

u32 GfBdatItem::getEquipOrbPrice(u32 id) const { return _gfbit::getEquipOrbPrice(*unknown50, id); }

u32 GfBdatItem::getEquipOrbRarity(u32 id) const { return _gfbit::getEquipOrbRarity(*unknown50, id); }

bool GfBdatItem::isEquipOrbFlagNoSell(u32 id) const { return _gfbit::isEquipOrbFlagNoSell(*unknown50, id); }

u32 GfBdatItem::getEquipOrbsortJP(u32 id) const { return _gfbit::getEquipOrbsortJP(*unknown50, id); }

u32 GfBdatItem::getPreciousStart() const { return Bdat::getIdTop(unknown58->data); }

u32 GfBdatItem::getPreciousName(u32 id) const { return _gfbit::getPreciousName(*unknown58, id); }

u32 GfBdatItem::getPreciousCaption(u32 id) const { return _gfbit::getPreciousCaption(*unknown58, id); }

u32 GfBdatItem::getPreciousCategory(u32 id) const { return _gfbit::getPreciousCategory(*unknown58, id); }

u32 GfBdatItem::getPreciousType(u32 id) const { return _gfbit::getPreciousType(*unknown58, id); }

u32 GfBdatItem::getPreciousPrice(u32 id) const { return _gfbit::getPreciousPrice(*unknown58, id); }

u32 GfBdatItem::getPreciousValueMax(u32 id) const { return _gfbit::getPreciousValueMax(*unknown58, id); }

u32 GfBdatItem::getPreciousClearNewGame(u32 id) const { return _gfbit::getPreciousClearNewGame(*unknown58, id); }

u32 GfBdatItem::getPreciousNoMultiple(u32 id) const { return _gfbit::getPreciousNoMultiple(*unknown58, id); }

u32 GfBdatItem::getPrecioussortJP(u32 id) const { return _gfbit::getPrecioussortJP(*unknown58, id); }

u32 GfBdatItem::getInfoStart() const { return Bdat::getIdTop(unknown60->data); }

u32 GfBdatItem::getInfoName(u32 id) const { return _gfbit::getInfoName(*unknown60, id); }

u32 GfBdatItem::getInfoCaption(u32 id) const { return _gfbit::getInfoCaption(*unknown60, id); }

u32 GfBdatItem::getInfoPrice(u32 id) const { return _gfbit::getInfoPrice(*unknown60, id); }

u32 GfBdatItem::getInfoClearNewGame(u32 id) const { return _gfbit::getInfoClearNewGame(*unknown60, id); }

u32 GfBdatItem::getInfosortJP(u32 id) const { return _gfbit::getInfosortJP(*unknown60, id); }

u32 GfBdatItem::getEventStart() const { return Bdat::getIdTop(unknown68->data); }

u32 GfBdatItem::getEventName(u32 id) const { return _gfbit::getEventName(*unknown68, id); }

u32 GfBdatItem::getEventCaption(u32 id) const { return _gfbit::getEventCaption(*unknown68, id); }

u32 GfBdatItem::getEventsortJP(u32 id) const { return _gfbit::getEventsortJP(*unknown68, id); }

u32 GfBdatItem::getPcWpnStart() const { return Bdat::getIdTop(unknown30->data); }

u32 GfBdatItem::getPcWpnName(u32 id) const { return _gfbit::getPcWpnName(*unknown30, id); }

const char *GfBdatItem::getPcWpnDebugName(u32 id) const { return _gfbit::getPcWpnDebugName(*unknown30, id); }

u32 GfBdatItem::getPcWpnRank(u32 id) const { return _gfbit::getPcWpnRank(*unknown30, id); }

bool GfBdatItem::isPcWpnFlagPrivate(u32 id) const { return _gfbit::isPcWpnFlagPrivate(*unknown30, id); }

u32 GfBdatItem::getPcWpnRscR(u32 id) const { return _gfbit::getPcWpnRscR(*unknown30, id); }

u32 GfBdatItem::getPcWpnRscL(u32 id) const { return _gfbit::getPcWpnRscL(*unknown30, id); }

u32 GfBdatItem::getPcWpnTypeRange(u32 id) const { return _gfbit::getPcWpnTypeRange(*unknown30, id); }

u32 GfBdatItem::getPcWpnWpnType(u32 id) const { return _gfbit::getPcWpnWpnType(*unknown30, id); }

u32 GfBdatItem::getPcWpnDamage(u32 id) const { return _gfbit::getPcWpnDamage(*unknown30, id); }

u32 GfBdatItem::getPcWpnStability(u32 id) const { return _gfbit::getPcWpnStability(*unknown30, id); }

u32 GfBdatItem::getPcWpnPArmor(u32 id) const { return _gfbit::getPcWpnPArmor(*unknown30, id); }

u32 GfBdatItem::getPcWpnEArmor(u32 id) const { return _gfbit::getPcWpnEArmor(*unknown30, id); }

u32 GfBdatItem::getPcWpnCriRate(u32 id) const { return _gfbit::getPcWpnCriRate(*unknown30, id); }

u32 GfBdatItem::getPcWpnGuardRate(u32 id) const { return _gfbit::getPcWpnGuardRate(*unknown30, id); }

u32 GfBdatItem::getPcWpnEnhance1(u32 id) const { return _gfbit::getPcWpnEnhance1(*unknown30, id); }

u32 GfBdatItem::getPcWpnEnhance2(u32 id) const { return _gfbit::getPcWpnEnhance2(*unknown30, id); }

u32 GfBdatItem::getPcWpnTypeStart() const { return Bdat::getIdTop(unknown40->data); }

u32 GfBdatItem::getPcWpnTypeName(u32 id) const { return _gfbit::getPcWpnTypeName(*unknown40, id); }

u32 GfBdatItem::getPcWpnTypeRole(u32 id) const { return _gfbit::getPcWpnTypeRole(*unknown40, id); }

u32 GfBdatItem::getPcWpnTypeEffType(u32 id) const { return _gfbit::getPcWpnTypeEffType(*unknown40, id); }

u32 GfBdatItem::getPcWpnTypeJustRange(u32 id) const { return _gfbit::getPcWpnTypeJustRange(*unknown40, id); }

u32 GfBdatItem::getPcWpnTypeJustRange2(u32 id) const { return _gfbit::getPcWpnTypeJustRange2(*unknown40, id); }

u32 GfBdatItem::getPcWpnTypeVoiceType(u32 id) const { return _gfbit::getPcWpnTypeVoiceType(*unknown40, id); }

u32 GfBdatItem::getPcWpnTypeMotion(u32 id) const { return _gfbit::getPcWpnTypeMotion(*unknown40, id); }

u32 GfBdatItem::getPcWpnChipStart() const { return Bdat::getIdTop(unknown38->data); }

u32 GfBdatItem::getPcWpnChipName(u32 id) const { return _gfbit::getPcWpnChipName(*unknown38, id); }

const char *GfBdatItem::getPcWpnChipDebugName(u32 id) const { return _gfbit::getPcWpnChipDebugName(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipRank(u32 id) const { return _gfbit::getPcWpnChipRank(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipCreateWpn1(u32 id) const { return _gfbit::getPcWpnChipCreateWpn1(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipCreateWpn2(u32 id) const { return _gfbit::getPcWpnChipCreateWpn2(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipCreateWpn3(u32 id) const { return _gfbit::getPcWpnChipCreateWpn3(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipCreateWpn4(u32 id) const { return _gfbit::getPcWpnChipCreateWpn4(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipCreateWpn5(u32 id) const { return _gfbit::getPcWpnChipCreateWpn5(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipCreateWpn6(u32 id) const { return _gfbit::getPcWpnChipCreateWpn6(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipCreateWpn7(u32 id) const { return _gfbit::getPcWpnChipCreateWpn7(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipCreateWpn8(u32 id) const { return _gfbit::getPcWpnChipCreateWpn8(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipCreateWpn9(u32 id) const { return _gfbit::getPcWpnChipCreateWpn9(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipCreateWpn10(u32 id) const { return _gfbit::getPcWpnChipCreateWpn10(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipCreateWpn11(u32 id) const { return _gfbit::getPcWpnChipCreateWpn11(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipCreateWpn12(u32 id) const { return _gfbit::getPcWpnChipCreateWpn12(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipCreateWpn13(u32 id) const { return _gfbit::getPcWpnChipCreateWpn13(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipCreateWpn14(u32 id) const { return _gfbit::getPcWpnChipCreateWpn14(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipCreateWpn15(u32 id) const { return _gfbit::getPcWpnChipCreateWpn15(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipCreateWpn16(u32 id) const { return _gfbit::getPcWpnChipCreateWpn16(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipPrice(u32 id) const { return _gfbit::getPcWpnChipPrice(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipRarity(u32 id) const { return _gfbit::getPcWpnChipRarity(*unknown38, id); }

bool GfBdatItem::isPcWpnChipFlagNoSell(u32 id) const { return _gfbit::isPcWpnChipFlagNoSell(*unknown38, id); }

u32 GfBdatItem::getPcWpnChipsortJP(u32 id) const { return _gfbit::getPcWpnChipsortJP(*unknown38, id); }

u32 GfBdatItem::getPcEquipStart() const { return Bdat::getIdTop(unknown48->data); }

u32 GfBdatItem::getPcEquipName(u32 id) const { return _gfbit::getPcEquipName(*unknown48, id); }

const char *GfBdatItem::getPcEquipDebugName(u32 id) const { return _gfbit::getPcEquipDebugName(*unknown48, id); }

u32 GfBdatItem::getPcEquipArmorType(u32 id) const { return _gfbit::getPcEquipArmorType(*unknown48, id); }

u32 GfBdatItem::getPcEquipPArmor(u32 id) const { return _gfbit::getPcEquipPArmor(*unknown48, id); }

u32 GfBdatItem::getPcEquipEArmor(u32 id) const { return _gfbit::getPcEquipEArmor(*unknown48, id); }

u32 GfBdatItem::getPcEquipBns_HpMax(u32 id) const { return _gfbit::getPcEquipBns_HpMax(*unknown48, id); }

u32 GfBdatItem::getPcEquipBns_Strength(u32 id) const { return _gfbit::getPcEquipBns_Strength(*unknown48, id); }

u32 GfBdatItem::getPcEquipBns_PowEther(u32 id) const { return _gfbit::getPcEquipBns_PowEther(*unknown48, id); }

u32 GfBdatItem::getPcEquipBns_Dex(u32 id) const { return _gfbit::getPcEquipBns_Dex(*unknown48, id); }

u32 GfBdatItem::getPcEquipBns_Agility(u32 id) const { return _gfbit::getPcEquipBns_Agility(*unknown48, id); }

u32 GfBdatItem::getPcEquipBns_Luck(u32 id) const { return _gfbit::getPcEquipBns_Luck(*unknown48, id); }

u32 GfBdatItem::getPcEquipEnhance1(u32 id) const { return _gfbit::getPcEquipEnhance1(*unknown48, id); }

u32 GfBdatItem::getPcEquipPrice(u32 id) const { return _gfbit::getPcEquipPrice(*unknown48, id); }

u32 GfBdatItem::getPcEquipRarity(u32 id) const { return _gfbit::getPcEquipRarity(*unknown48, id); }

bool GfBdatItem::isPcEquipFlagNoSell(u32 id) const { return _gfbit::isPcEquipFlagNoSell(*unknown48, id); }

bool GfBdatItem::isPcEquipFlagEqPC01(u32 id) const { return _gfbit::isPcEquipFlagEqPC01(*unknown48, id); }

bool GfBdatItem::isPcEquipFlagEqPC02(u32 id) const { return _gfbit::isPcEquipFlagEqPC02(*unknown48, id); }

bool GfBdatItem::isPcEquipFlagEqPC03(u32 id) const { return _gfbit::isPcEquipFlagEqPC03(*unknown48, id); }

bool GfBdatItem::isPcEquipFlagEqPC04(u32 id) const { return _gfbit::isPcEquipFlagEqPC04(*unknown48, id); }

bool GfBdatItem::isPcEquipFlagEqPC05(u32 id) const { return _gfbit::isPcEquipFlagEqPC05(*unknown48, id); }

bool GfBdatItem::isPcEquipFlagEqPC06(u32 id) const { return _gfbit::isPcEquipFlagEqPC06(*unknown48, id); }

bool GfBdatItem::isPcEquipFlagEqPC07(u32 id) const { return _gfbit::isPcEquipFlagEqPC07(*unknown48, id); }

bool GfBdatItem::isPcEquipFlagEqPC08(u32 id) const { return _gfbit::isPcEquipFlagEqPC08(*unknown48, id); }

bool GfBdatItem::isPcEquipFlagEqPC09(u32 id) const { return _gfbit::isPcEquipFlagEqPC09(*unknown48, id); }

u32 GfBdatItem::getPcEquipIcon(u32 id) const { return _gfbit::getPcEquipIcon(*unknown48, id); }

u32 GfBdatItem::getPcEquipsortJP(u32 id) const { return _gfbit::getPcEquipsortJP(*unknown48, id); }

u32 GfBdatItem::getSalvageStart() const { return Bdat::getIdTop(unknown70->data); }

u32 GfBdatItem::getSalvageName(u32 id) const { return _gfbit::getSalvageName(*unknown70, id); }

u32 GfBdatItem::getSalvageCaption(u32 id) const { return _gfbit::getSalvageCaption(*unknown70, id); }

u32 GfBdatItem::getSalvageRarity(u32 id) const { return _gfbit::getSalvageRarity(*unknown70, id); }

u32 GfBdatItem::getSalvagePrice(u32 id) const { return _gfbit::getSalvagePrice(*unknown70, id); }

u32 GfBdatItem::getSalvageQuest(u32 id) const { return _gfbit::getSalvageQuest(*unknown70, id); }

u32 GfBdatItem::getSalvageNoSell(u32 id) const { return _gfbit::getSalvageNoSell(*unknown70, id); }

u32 GfBdatItem::getSalvagesortJP(u32 id) const { return _gfbit::getSalvagesortJP(*unknown70, id); }

u32 GfBdatItem::getHealPotStart() const { return Bdat::getIdTop(unknown78->data); }

u32 GfBdatItem::getHealPotDropRsc(u32 id) const { return _gfbit::getHealPotDropRsc(*unknown78, id); }

u32 GfBdatItem::getHealPotHpRatio(u32 id) const { return _gfbit::getHealPotHpRatio(*unknown78, id); }

u32 GfBdatItem::getTresureStart() const { return Bdat::getIdTop(unknown88->data); }

u32 GfBdatItem::getTresureName(u32 id) const { return _gfbit::getTresureName(*unknown88, id); }

u32 GfBdatItem::getTresureCaption(u32 id) const { return _gfbit::getTresureCaption(*unknown88, id); }

u32 GfBdatItem::getTresureCategory(u32 id) const { return _gfbit::getTresureCategory(*unknown88, id); }

u32 GfBdatItem::getTresureGraphic(u32 id) const { return _gfbit::getTresureGraphic(*unknown88, id); }

u32 GfBdatItem::getTresureZone(u32 id) const { return _gfbit::getTresureZone(*unknown88, id); }

u32 GfBdatItem::getTresureRarity(u32 id) const { return _gfbit::getTresureRarity(*unknown88, id); }

u32 GfBdatItem::getTresurePrice(u32 id) const { return _gfbit::getTresurePrice(*unknown88, id); }

u32 GfBdatItem::getTresureFlag(u32 id) const { return _gfbit::getTresureFlag(*unknown88, id); }

u32 GfBdatItem::getTresureNoMultiple(u32 id) const { return _gfbit::getTresureNoMultiple(*unknown88, id); }

u32 GfBdatItem::getTresureClearNewGame(u32 id) const { return _gfbit::getTresureClearNewGame(*unknown88, id); }

u32 GfBdatItem::getTresuresortJP(u32 id) const { return _gfbit::getTresuresortJP(*unknown88, id); }

u32 GfBdatItem::getFavoriteStart() const { return Bdat::getIdTop(unknown90->data); }

u32 GfBdatItem::getFavoriteName(u32 id) const { return _gfbit::getFavoriteName(*unknown90, id); }

u32 GfBdatItem::getFavoriteCaption(u32 id) const { return _gfbit::getFavoriteCaption(*unknown90, id); }

u32 GfBdatItem::getFavoriteCategory(u32 id) const { return _gfbit::getFavoriteCategory(*unknown90, id); }

u32 GfBdatItem::getFavoriteZone(u32 id) const { return _gfbit::getFavoriteZone(*unknown90, id); }

u32 GfBdatItem::getFavoriteRarity(u32 id) const { return _gfbit::getFavoriteRarity(*unknown90, id); }

u32 GfBdatItem::getFavoritePrice(u32 id) const { return _gfbit::getFavoritePrice(*unknown90, id); }

u32 GfBdatItem::getFavoriteType(u32 id) const { return _gfbit::getFavoriteType(*unknown90, id); }

u32 GfBdatItem::getFavoriteTime(u32 id) const { return _gfbit::getFavoriteTime(*unknown90, id); }

u32 GfBdatItem::getFavoriteValueMax(u32 id) const { return _gfbit::getFavoriteValueMax(*unknown90, id); }

u32 GfBdatItem::getFavoriteTrustPoint(u32 id) const { return _gfbit::getFavoriteTrustPoint(*unknown90, id); }

u32 GfBdatItem::getFavoritesortJP(u32 id) const { return _gfbit::getFavoritesortJP(*unknown90, id); }

u32 GfBdatItem::getOwnerBonusStart() const { return Bdat::getIdTop(unknown98->data); }

u32 GfBdatItem::getOwnerBonusCaption(u32 id) const { return _gfbit::getOwnerBonusCaption(*unknown98, id); }

u32 GfBdatItem::getOwnerBonusType(u32 id) const { return _gfbit::getOwnerBonusType(*unknown98, id); }

u32 GfBdatItem::getOwnerBonusValue(u32 id) const { return _gfbit::getOwnerBonusValue(*unknown98, id); }

u32 GfBdatItem::getOwnerBonusParamStart() const { return Bdat::getIdTop(unknowna0->data); }

u32 GfBdatItem::getOwnerBonusParamMax(u32 id) const { return _gfbit::getOwnerBonusParamMax(*unknowna0, id); }

u32 GfBdatItem::getITM_HanaRoleStart() const { return Bdat::getIdTop(unknowna8->data); }

u32 GfBdatItem::getITM_HanaRoleName(u32 id) const { return _gfbit::getITM_HanaRoleName(*unknowna8, id); }

u32 GfBdatItem::getITM_HanaRoleRole(u32 id) const { return _gfbit::getITM_HanaRoleRole(*unknowna8, id); }

u32 GfBdatItem::getITM_HanaRolePArmor(u32 id) const { return _gfbit::getITM_HanaRolePArmor(*unknowna8, id); }

u32 GfBdatItem::getITM_HanaRoleEArmor(u32 id) const { return _gfbit::getITM_HanaRoleEArmor(*unknowna8, id); }

u32 GfBdatItem::getITM_HanaRoleHpMaxRev(u32 id) const { return _gfbit::getITM_HanaRoleHpMaxRev(*unknowna8, id); }

u32 GfBdatItem::getITM_HanaRoleStrengthRev(u32 id) const { return _gfbit::getITM_HanaRoleStrengthRev(*unknowna8, id); }

u32 GfBdatItem::getITM_HanaRolePowEtherRev(u32 id) const { return _gfbit::getITM_HanaRolePowEtherRev(*unknowna8, id); }

u32 GfBdatItem::getITM_HanaRoleDexRev(u32 id) const { return _gfbit::getITM_HanaRoleDexRev(*unknowna8, id); }

u32 GfBdatItem::getITM_HanaRoleAgilityRev(u32 id) const { return _gfbit::getITM_HanaRoleAgilityRev(*unknowna8, id); }

u32 GfBdatItem::getITM_HanaRoleLuckRev(u32 id) const { return _gfbit::getITM_HanaRoleLuckRev(*unknowna8, id); }

s32 GfBdatItem::getITM_HanaRoleAutoHate(u32 id) const { return _gfbit::getITM_HanaRoleAutoHate(*unknowna8, id); }

s32 GfBdatItem::getITM_HanaRoleArtsHate(u32 id) const { return _gfbit::getITM_HanaRoleArtsHate(*unknowna8, id); }

bool GfBdatItem::isITM_HanaRoleFlagJS(u32 id) const { return _gfbit::isITM_HanaRoleFlagJS(*unknowna8, id); }

bool GfBdatItem::isITM_HanaRoleFlagJK(u32 id) const { return _gfbit::isITM_HanaRoleFlagJK(*unknowna8, id); }

bool GfBdatItem::isITM_HanaRoleFlagJD(u32 id) const { return _gfbit::isITM_HanaRoleFlagJD(*unknowna8, id); }

u32 GfBdatItem::getITM_HanaRoleNeedPow(u32 id) const { return _gfbit::getITM_HanaRoleNeedPow(*unknowna8, id); }

u32 GfBdatItem::getITM_HanaRoleNeedEther(u32 id) const { return _gfbit::getITM_HanaRoleNeedEther(*unknowna8, id); }

u32 GfBdatItem::getITM_HanaRoleDustEther(u32 id) const { return _gfbit::getITM_HanaRoleDustEther(*unknowna8, id); }

u32 GfBdatItem::getITM_HanaRoleCondition(u32 id) const { return _gfbit::getITM_HanaRoleCondition(*unknowna8, id); }

const char *GfBdatItem::getITM_HanaRoleUI(u32 id) const { return _gfbit::getITM_HanaRoleUI(*unknowna8, id); }

u32 GfBdatItem::getITM_HanaRolesortJP(u32 id) const { return _gfbit::getITM_HanaRolesortJP(*unknowna8, id); }

u32 GfBdatItem::getITM_HanaAtrStart() const { return Bdat::getIdTop(unknownb0->data); }

u32 GfBdatItem::getITM_HanaAtrName(u32 id) const { return _gfbit::getITM_HanaAtrName(*unknownb0, id); }

u32 GfBdatItem::getITM_HanaAtrAtr(u32 id) const { return _gfbit::getITM_HanaAtrAtr(*unknownb0, id); }

bool GfBdatItem::isITM_HanaAtrFlagJS(u32 id) const { return _gfbit::isITM_HanaAtrFlagJS(*unknownb0, id); }

bool GfBdatItem::isITM_HanaAtrFlagJK(u32 id) const { return _gfbit::isITM_HanaAtrFlagJK(*unknownb0, id); }

bool GfBdatItem::isITM_HanaAtrFlagJD(u32 id) const { return _gfbit::isITM_HanaAtrFlagJD(*unknownb0, id); }

u32 GfBdatItem::getITM_HanaAtrNeedPow(u32 id) const { return _gfbit::getITM_HanaAtrNeedPow(*unknownb0, id); }

u32 GfBdatItem::getITM_HanaAtrNeedEther(u32 id) const { return _gfbit::getITM_HanaAtrNeedEther(*unknownb0, id); }

u32 GfBdatItem::getITM_HanaAtrDustEther(u32 id) const { return _gfbit::getITM_HanaAtrDustEther(*unknownb0, id); }

u32 GfBdatItem::getITM_HanaAtrCondition(u32 id) const { return _gfbit::getITM_HanaAtrCondition(*unknownb0, id); }

const char *GfBdatItem::getITM_HanaAtrUI(u32 id) const { return _gfbit::getITM_HanaAtrUI(*unknownb0, id); }

u32 GfBdatItem::getITM_HanaAtrsortJP(u32 id) const { return _gfbit::getITM_HanaAtrsortJP(*unknownb0, id); }

u32 GfBdatItem::getITM_HanaArtsEnhStart() const { return Bdat::getIdTop(unknownb8->data); }

u32 GfBdatItem::getITM_HanaArtsEnhName(u32 id) const { return _gfbit::getITM_HanaArtsEnhName(*unknownb8, id); }

u32 GfBdatItem::getITM_HanaArtsEnhEnhance(u32 id) const { return _gfbit::getITM_HanaArtsEnhEnhance(*unknownb8, id); }

bool GfBdatItem::isITM_HanaArtsEnhFlagJS(u32 id) const { return _gfbit::isITM_HanaArtsEnhFlagJS(*unknownb8, id); }

bool GfBdatItem::isITM_HanaArtsEnhFlagJK(u32 id) const { return _gfbit::isITM_HanaArtsEnhFlagJK(*unknownb8, id); }

bool GfBdatItem::isITM_HanaArtsEnhFlagJD(u32 id) const { return _gfbit::isITM_HanaArtsEnhFlagJD(*unknownb8, id); }

u32 GfBdatItem::getITM_HanaArtsEnhNeedPow(u32 id) const { return _gfbit::getITM_HanaArtsEnhNeedPow(*unknownb8, id); }

u32 GfBdatItem::getITM_HanaArtsEnhNeedEther(u32 id) const { return _gfbit::getITM_HanaArtsEnhNeedEther(*unknownb8, id); }

u32 GfBdatItem::getITM_HanaArtsEnhDustEther(u32 id) const { return _gfbit::getITM_HanaArtsEnhDustEther(*unknownb8, id); }

u32 GfBdatItem::getITM_HanaArtsEnhCondition(u32 id) const { return _gfbit::getITM_HanaArtsEnhCondition(*unknownb8, id); }

const char *GfBdatItem::getITM_HanaArtsEnhUI(u32 id) const { return _gfbit::getITM_HanaArtsEnhUI(*unknownb8, id); }

u32 GfBdatItem::getITM_HanaArtsEnhsortJP(u32 id) const { return _gfbit::getITM_HanaArtsEnhsortJP(*unknownb8, id); }

u32 GfBdatItem::getITM_HanaNArtsSetStart() const { return Bdat::getIdTop(unknownc0->data); }

u32 GfBdatItem::getITM_HanaNArtsSetName(u32 id) const { return _gfbit::getITM_HanaNArtsSetName(*unknownc0, id); }

u32 GfBdatItem::getITM_HanaNArtsSetNArts(u32 id) const { return _gfbit::getITM_HanaNArtsSetNArts(*unknownc0, id); }

u32 GfBdatItem::getITM_HanaNArtsSetNArtsRecastRev(u32 id) const { return _gfbit::getITM_HanaNArtsSetNArtsRecastRev(*unknownc0, id); }

bool GfBdatItem::isITM_HanaNArtsSetFlagJS(u32 id) const { return _gfbit::isITM_HanaNArtsSetFlagJS(*unknownc0, id); }

bool GfBdatItem::isITM_HanaNArtsSetFlagJK(u32 id) const { return _gfbit::isITM_HanaNArtsSetFlagJK(*unknownc0, id); }

bool GfBdatItem::isITM_HanaNArtsSetFlagJD(u32 id) const { return _gfbit::isITM_HanaNArtsSetFlagJD(*unknownc0, id); }

u32 GfBdatItem::getITM_HanaNArtsSetNeedPow(u32 id) const { return _gfbit::getITM_HanaNArtsSetNeedPow(*unknownc0, id); }

u32 GfBdatItem::getITM_HanaNArtsSetNeedEther(u32 id) const { return _gfbit::getITM_HanaNArtsSetNeedEther(*unknownc0, id); }

u32 GfBdatItem::getITM_HanaNArtsSetDustEther(u32 id) const { return _gfbit::getITM_HanaNArtsSetDustEther(*unknownc0, id); }

u32 GfBdatItem::getITM_HanaNArtsSetCondition(u32 id) const { return _gfbit::getITM_HanaNArtsSetCondition(*unknownc0, id); }

const char *GfBdatItem::getITM_HanaNArtsSetUI(u32 id) const { return _gfbit::getITM_HanaNArtsSetUI(*unknownc0, id); }

u32 GfBdatItem::getITM_HanaNArtsSetsortJP(u32 id) const { return _gfbit::getITM_HanaNArtsSetsortJP(*unknownc0, id); }

u32 GfBdatItem::getITM_HanaAssistStart() const { return Bdat::getIdTop(unknownc8->data); }

u32 GfBdatItem::getITM_HanaAssistName(u32 id) const { return _gfbit::getITM_HanaAssistName(*unknownc8, id); }

u32 GfBdatItem::getITM_HanaAssistEnhance(u32 id) const { return _gfbit::getITM_HanaAssistEnhance(*unknownc8, id); }

u32 GfBdatItem::getITM_HanaAssistEnhanceCategory(u32 id) const { return _gfbit::getITM_HanaAssistEnhanceCategory(*unknownc8, id); }

bool GfBdatItem::isITM_HanaAssistFlagJS(u32 id) const { return _gfbit::isITM_HanaAssistFlagJS(*unknownc8, id); }

bool GfBdatItem::isITM_HanaAssistFlagJK(u32 id) const { return _gfbit::isITM_HanaAssistFlagJK(*unknownc8, id); }

bool GfBdatItem::isITM_HanaAssistFlagJD(u32 id) const { return _gfbit::isITM_HanaAssistFlagJD(*unknownc8, id); }

u32 GfBdatItem::getITM_HanaAssistNeedPow(u32 id) const { return _gfbit::getITM_HanaAssistNeedPow(*unknownc8, id); }

u32 GfBdatItem::getITM_HanaAssistNeedEther(u32 id) const { return _gfbit::getITM_HanaAssistNeedEther(*unknownc8, id); }

u32 GfBdatItem::getITM_HanaAssistDustEther(u32 id) const { return _gfbit::getITM_HanaAssistDustEther(*unknownc8, id); }

u32 GfBdatItem::getITM_HanaAssistCondition(u32 id) const { return _gfbit::getITM_HanaAssistCondition(*unknownc8, id); }

const char *GfBdatItem::getITM_HanaAssistUI(u32 id) const { return _gfbit::getITM_HanaAssistUI(*unknownc8, id); }

u32 GfBdatItem::getITM_HanaAssistsortJP(u32 id) const { return _gfbit::getITM_HanaAssistsortJP(*unknownc8, id); }

} // namespace gf
