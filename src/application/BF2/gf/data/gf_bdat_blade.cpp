#include "gf/data/gf_bdat_blade.h"
#include "bdat.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"

namespace gf {
namespace _gfbdb {

enum {
  IdeaTableItem,
  IdeaTableIdeaBlue,
  IdeaTableIdeaRed,
  IdeaTableIdeaWhite,
  IdeaTableIdeaBlack,
  IdeaTableCondition,
  IdeaTableBladeTable,
  BladeTableCharaID1,
  BladeTableCharID1Percent,
  BladeTableCharaID2,
  BladeTableCharID2Percent,
  BladeTableCharaID3,
  BladeTableCharID3Percent,
  BladeTableCharaID4,
  BladeTableCharID4Percent,
  BladeTableCharaID5,
  BladeTableCharID5Percent,
  BladeTableCharaID6,
  BladeTableCharID6Percent,
  BladeTableCharaID7,
  BladeTableCharID7Percent,
  BladeTableCharaID8,
  BladeTableCharID8Percent,
  BladeTableCharaID9,
  BladeTableCharID9Percent,
  BladeTableCharaID10,
  BladeTableCharID10Percent,
  BladeTableCharaID11,
  BladeTableCharID11Percent,
  BladeTableCharaID12,
  BladeTableCharID12Percent,
  BladeTableCharaID13,
  BladeTableCharID13Percent,
  BladeTableCharaID14,
  BladeTableCharID14Percent,
  BladeTableCharaID15,
  BladeTableCharID15Percent,
  BladeTableCharaID16,
  BladeTableCharID16Percent,
  BladeListCategory,
  BladeListStatusID,
  CommonListQuestRace,
  CommonListGender,
  CommonListWeapon,
  CommonListAtr,
  CommonListModelTable,
  CommonListIdeaType,
  CommonListIdeaMin,
  CommonListIdeaMax,
  CommonListRatio,
  CommonListRarityMin,
  CommonListRarityMax,
  CommonListFskill,
  CommonListArtsAchievementSet1,
  CommonListArtsAchievementSet2,
  CommonListArtsAchievementSet3,
  CommonListSkillAchievementSet1,
  CommonListSkillAchievementSet2,
  CommonListSkillAchievementSet3,
  CommonListFskillAchivementSet1,
  CommonListFskillAchivementSet2,
  CommonListFskillAchivementSet3,
  CommonListKeyAchievementSet,
  CommonListFavoriteCategoryMax,
  CommonListFavoriteItemMax,
  NameListCategory,
  NameListRace,
  NameListGender,
  BladeModelListQuestRace,
  BladeModelListGender,
  BladeModelListIdeaMin,
  BladeModelListIdeaMax,
  BladeModelListModel1,
  BladeModelListModel2,
  BladeModelListPartsNumMin,
  BladeModelListPartsNumMax,
  BladeModelListParts1,
  BladeModelListParts2,
  BladeModelListParts3,
  BladeModelListParts4,
  CreateConfigValue,
  CmnBl_CapacityArtsNum1Prob,
  CmnBl_CapacityArtsNum2Prob,
  CmnBl_CapacityArtsNum3Prob,
  CmnBl_CapacityArtsLv1Prob,
  CmnBl_CapacityArtsLv2Prob,
  CmnBl_CapacityArtsLv3Prob,
  CmnBl_CapacityArtsLv4Prob,
  CmnBl_CapacityArtsLv5Prob,
  CmnBl_CapacityArtsRevCon,
  CmnBl_CapacityArtsRevRand,
  CmnBl_CapacitySpArtsRevCon,
  CmnBl_CapacitySpArtsRevRand,
  CmnBl_CapacitySkillNum1Prob,
  CmnBl_CapacitySkillNum2Prob,
  CmnBl_CapacitySkillNum3Prob,
  CmnBl_CapacitySkillLv1Prob,
  CmnBl_CapacitySkillLv2Prob,
  CmnBl_CapacitySkillLv3Prob,
  CmnBl_CapacitySkillLv4Prob,
  CmnBl_CapacitySkillLv5Prob,
  CmnBl_CapacityOrbNum0Prob,
  CmnBl_CapacityOrbNum1Prob,
  CmnBl_CapacityOrbNum2Prob,
  CmnBl_CapacityOrbNum3Prob,
  CmnBl_CapacityNartsNum1Prob,
  CmnBl_CapacityNartsNum2Prob,
  CmnBl_CapacityNartsNum3Prob,
  CmnBl_CapacityNartsRevCon,
  CmnBl_CapacityNartsRevRand,
  CmnBl_CapacityStatusRevCon,
  CmnBl_CapacityStatusRevRand,
  CmnBl_PowerMinLv,
  CmnBl_PowerMaxLv,
  CmnBl_PowerPow01,
  CmnBl_PowerPow02,
  CmnBl_PowerPow03,
  CmnBl_PowerPow04,
  CmnBl_PowerPow05,
  CmnBl_PowerPow06,
  CmnBl_PowerPow07,
  CmnBl_PowerPow08,
  CmnBl_PowerPow09,
  CmnBl_PowerPow10,
  CmnBl_NewBlArtsWpnType,
  CmnBl_NewBlArtsNBA_01,
  CmnBl_NewBlArtsNBA_02,
  CmnBl_NewBlArtsNBA_03,
  CmnBl_NewBlArtsNBA_04,
  CmnBl_NewBlArtsNBA_05,
  CmnBl_NewBlArtsNBA_06,
  CmnBl_NewBlArtsNBA_07,
  CmnBl_NewBlArtsNBA_08,
  CmnBl_StatusTypeWpnType,
  CmnBl_StatusTypeStatus01,
  CmnBl_StatusTypeStatus02,
  CmnBl_StatusTypeStatus03,
  CmnBl_StatusTypeStatus04,
  CmnBl_StatusTypeStatus05,
  CmnBl_StatusTypeStatus06,
  CmnBl_ArmorWpnType,
  CmnBl_ArmorPArmorCon,
  CmnBl_ArmorPArmorRand,
  CmnBl_ArmorEArmorCon,
  CmnBl_ArmorEArmorRand,
  FLD_IdeaTableTrustPoint,
  FLD_IdeaTableWpnRatio,
  FLD_IdeaTableNArtsProbRev,
  FLD_IdeaTableBladeChangeRev,
  FLD_IdeaTableBladeArtsRev,
  BLD_IdeaNeedPoint,
  BLD_IdeaProbRev,
  BLD_IdeaAtrDamRev,
  BLD_RareListBlade,
  BLD_RareListCondition,
  BLD_RareListProb1,
  BLD_RareListAssure1,
  BLD_RareListProb2,
  BLD_RareListAssure2,
  BLD_RareListProb3,
  BLD_RareListAssure3,
  BLD_RareListProb4,
  BLD_RareListAssure4,
  BLD_RareListProb5,
  BLD_RareListAssure5,
  BLD_ReleaceRewardReleace001,
  BLD_ReleaceRewardReleace002,
  BLD_ReleaceRewardReleace003,
  BLD_ReleaceRewardReleace004,
  BLD_ReleaceRewardReleace005,
  BLD_ReleaceRewardReleace006,
  BLD_ReleaceRewardReleace007,
  MEMBER_COUNT,
};

static u8 *s_members[MEMBER_COUNT];

void initIdeaTableItem(const CBdatWrapper &wrapper) { s_members[IdeaTableItem] = Bdat::getMember(wrapper.data, "Item"); }

u32 getIdeaTableItem(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[IdeaTableItem] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[IdeaTableItem], id, 2).valueU16;
}

void initIdeaTableIdeaBlue(const CBdatWrapper &wrapper) { s_members[IdeaTableIdeaBlue] = Bdat::getMember(wrapper.data, "IdeaBlue"); }

u32 getIdeaTableIdeaBlue(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[IdeaTableIdeaBlue] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[IdeaTableIdeaBlue], id, 1).valueU8;
}

void initIdeaTableIdeaRed(const CBdatWrapper &wrapper) { s_members[IdeaTableIdeaRed] = Bdat::getMember(wrapper.data, "IdeaRed"); }

u32 getIdeaTableIdeaRed(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[IdeaTableIdeaRed] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[IdeaTableIdeaRed], id, 1).valueU8;
}

void initIdeaTableIdeaWhite(const CBdatWrapper &wrapper) { s_members[IdeaTableIdeaWhite] = Bdat::getMember(wrapper.data, "IdeaWhite"); }

u32 getIdeaTableIdeaWhite(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[IdeaTableIdeaWhite] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[IdeaTableIdeaWhite], id, 1).valueU8;
}

void initIdeaTableIdeaBlack(const CBdatWrapper &wrapper) { s_members[IdeaTableIdeaBlack] = Bdat::getMember(wrapper.data, "IdeaBlack"); }

u32 getIdeaTableIdeaBlack(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[IdeaTableIdeaBlack] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[IdeaTableIdeaBlack], id, 1).valueU8;
}

void initIdeaTableCondition(const CBdatWrapper &wrapper) { s_members[IdeaTableCondition] = Bdat::getMember(wrapper.data, "Condition"); }

u32 getIdeaTableCondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[IdeaTableCondition] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[IdeaTableCondition], id, 2).valueU16;
}

void initIdeaTableBladeTable(const CBdatWrapper &wrapper) { s_members[IdeaTableBladeTable] = Bdat::getMember(wrapper.data, "BladeTable"); }

u32 getIdeaTableBladeTable(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[IdeaTableBladeTable] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[IdeaTableBladeTable], id, 2).valueU16;
}

void initBladeTableCharaID1(const CBdatWrapper &wrapper) { s_members[BladeTableCharaID1] = Bdat::getMember(wrapper.data, "CharaID1"); }

u32 getBladeTableCharaID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharaID1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharaID1], id, 2).valueU16;
}

void initBladeTableCharID1Percent(const CBdatWrapper &wrapper) {
  s_members[BladeTableCharID1Percent] = Bdat::getMember(wrapper.data, "CharID1Percent");
}

u32 getBladeTableCharID1Percent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharID1Percent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharID1Percent], id, 1).valueU8;
}

void initBladeTableCharaID2(const CBdatWrapper &wrapper) { s_members[BladeTableCharaID2] = Bdat::getMember(wrapper.data, "CharaID2"); }

u32 getBladeTableCharaID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharaID2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharaID2], id, 2).valueU16;
}

void initBladeTableCharID2Percent(const CBdatWrapper &wrapper) {
  s_members[BladeTableCharID2Percent] = Bdat::getMember(wrapper.data, "CharID2Percent");
}

u32 getBladeTableCharID2Percent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharID2Percent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharID2Percent], id, 1).valueU8;
}

void initBladeTableCharaID3(const CBdatWrapper &wrapper) { s_members[BladeTableCharaID3] = Bdat::getMember(wrapper.data, "CharaID3"); }

u32 getBladeTableCharaID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharaID3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharaID3], id, 2).valueU16;
}

void initBladeTableCharID3Percent(const CBdatWrapper &wrapper) {
  s_members[BladeTableCharID3Percent] = Bdat::getMember(wrapper.data, "CharID3Percent");
}

u32 getBladeTableCharID3Percent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharID3Percent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharID3Percent], id, 1).valueU8;
}

void initBladeTableCharaID4(const CBdatWrapper &wrapper) { s_members[BladeTableCharaID4] = Bdat::getMember(wrapper.data, "CharaID4"); }

u32 getBladeTableCharaID4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharaID4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharaID4], id, 2).valueU16;
}

void initBladeTableCharID4Percent(const CBdatWrapper &wrapper) {
  s_members[BladeTableCharID4Percent] = Bdat::getMember(wrapper.data, "CharID4Percent");
}

u32 getBladeTableCharID4Percent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharID4Percent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharID4Percent], id, 1).valueU8;
}

void initBladeTableCharaID5(const CBdatWrapper &wrapper) { s_members[BladeTableCharaID5] = Bdat::getMember(wrapper.data, "CharaID5"); }

u32 getBladeTableCharaID5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharaID5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharaID5], id, 2).valueU16;
}

void initBladeTableCharID5Percent(const CBdatWrapper &wrapper) {
  s_members[BladeTableCharID5Percent] = Bdat::getMember(wrapper.data, "CharID5Percent");
}

u32 getBladeTableCharID5Percent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharID5Percent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharID5Percent], id, 1).valueU8;
}

void initBladeTableCharaID6(const CBdatWrapper &wrapper) { s_members[BladeTableCharaID6] = Bdat::getMember(wrapper.data, "CharaID6"); }

u32 getBladeTableCharaID6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharaID6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharaID6], id, 2).valueU16;
}

void initBladeTableCharID6Percent(const CBdatWrapper &wrapper) {
  s_members[BladeTableCharID6Percent] = Bdat::getMember(wrapper.data, "CharID6Percent");
}

u32 getBladeTableCharID6Percent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharID6Percent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharID6Percent], id, 1).valueU8;
}

void initBladeTableCharaID7(const CBdatWrapper &wrapper) { s_members[BladeTableCharaID7] = Bdat::getMember(wrapper.data, "CharaID7"); }

u32 getBladeTableCharaID7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharaID7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharaID7], id, 2).valueU16;
}

void initBladeTableCharID7Percent(const CBdatWrapper &wrapper) {
  s_members[BladeTableCharID7Percent] = Bdat::getMember(wrapper.data, "CharID7Percent");
}

u32 getBladeTableCharID7Percent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharID7Percent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharID7Percent], id, 1).valueU8;
}

void initBladeTableCharaID8(const CBdatWrapper &wrapper) { s_members[BladeTableCharaID8] = Bdat::getMember(wrapper.data, "CharaID8"); }

u32 getBladeTableCharaID8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharaID8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharaID8], id, 2).valueU16;
}

void initBladeTableCharID8Percent(const CBdatWrapper &wrapper) {
  s_members[BladeTableCharID8Percent] = Bdat::getMember(wrapper.data, "CharID8Percent");
}

u32 getBladeTableCharID8Percent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharID8Percent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharID8Percent], id, 1).valueU8;
}

void initBladeTableCharaID9(const CBdatWrapper &wrapper) { s_members[BladeTableCharaID9] = Bdat::getMember(wrapper.data, "CharaID9"); }

u32 getBladeTableCharaID9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharaID9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharaID9], id, 2).valueU16;
}

void initBladeTableCharID9Percent(const CBdatWrapper &wrapper) {
  s_members[BladeTableCharID9Percent] = Bdat::getMember(wrapper.data, "CharID9Percent");
}

u32 getBladeTableCharID9Percent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharID9Percent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharID9Percent], id, 1).valueU8;
}

void initBladeTableCharaID10(const CBdatWrapper &wrapper) { s_members[BladeTableCharaID10] = Bdat::getMember(wrapper.data, "CharaID10"); }

u32 getBladeTableCharaID10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharaID10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharaID10], id, 2).valueU16;
}

void initBladeTableCharID10Percent(const CBdatWrapper &wrapper) {
  s_members[BladeTableCharID10Percent] = Bdat::getMember(wrapper.data, "CharID10Percent");
}

u32 getBladeTableCharID10Percent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharID10Percent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharID10Percent], id, 1).valueU8;
}

void initBladeTableCharaID11(const CBdatWrapper &wrapper) { s_members[BladeTableCharaID11] = Bdat::getMember(wrapper.data, "CharaID11"); }

u32 getBladeTableCharaID11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharaID11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharaID11], id, 2).valueU16;
}

void initBladeTableCharID11Percent(const CBdatWrapper &wrapper) {
  s_members[BladeTableCharID11Percent] = Bdat::getMember(wrapper.data, "CharID11Percent");
}

u32 getBladeTableCharID11Percent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharID11Percent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharID11Percent], id, 1).valueU8;
}

void initBladeTableCharaID12(const CBdatWrapper &wrapper) { s_members[BladeTableCharaID12] = Bdat::getMember(wrapper.data, "CharaID12"); }

u32 getBladeTableCharaID12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharaID12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharaID12], id, 2).valueU16;
}

void initBladeTableCharID12Percent(const CBdatWrapper &wrapper) {
  s_members[BladeTableCharID12Percent] = Bdat::getMember(wrapper.data, "CharID12Percent");
}

u32 getBladeTableCharID12Percent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharID12Percent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharID12Percent], id, 1).valueU8;
}

void initBladeTableCharaID13(const CBdatWrapper &wrapper) { s_members[BladeTableCharaID13] = Bdat::getMember(wrapper.data, "CharaID13"); }

u32 getBladeTableCharaID13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharaID13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharaID13], id, 2).valueU16;
}

void initBladeTableCharID13Percent(const CBdatWrapper &wrapper) {
  s_members[BladeTableCharID13Percent] = Bdat::getMember(wrapper.data, "CharID13Percent");
}

u32 getBladeTableCharID13Percent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharID13Percent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharID13Percent], id, 1).valueU8;
}

void initBladeTableCharaID14(const CBdatWrapper &wrapper) { s_members[BladeTableCharaID14] = Bdat::getMember(wrapper.data, "CharaID14"); }

u32 getBladeTableCharaID14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharaID14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharaID14], id, 2).valueU16;
}

void initBladeTableCharID14Percent(const CBdatWrapper &wrapper) {
  s_members[BladeTableCharID14Percent] = Bdat::getMember(wrapper.data, "CharID14Percent");
}

u32 getBladeTableCharID14Percent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharID14Percent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharID14Percent], id, 1).valueU8;
}

void initBladeTableCharaID15(const CBdatWrapper &wrapper) { s_members[BladeTableCharaID15] = Bdat::getMember(wrapper.data, "CharaID15"); }

u32 getBladeTableCharaID15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharaID15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharaID15], id, 2).valueU16;
}

void initBladeTableCharID15Percent(const CBdatWrapper &wrapper) {
  s_members[BladeTableCharID15Percent] = Bdat::getMember(wrapper.data, "CharID15Percent");
}

u32 getBladeTableCharID15Percent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharID15Percent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharID15Percent], id, 1).valueU8;
}

void initBladeTableCharaID16(const CBdatWrapper &wrapper) { s_members[BladeTableCharaID16] = Bdat::getMember(wrapper.data, "CharaID16"); }

u32 getBladeTableCharaID16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharaID16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharaID16], id, 2).valueU16;
}

void initBladeTableCharID16Percent(const CBdatWrapper &wrapper) {
  s_members[BladeTableCharID16Percent] = Bdat::getMember(wrapper.data, "CharID16Percent");
}

u32 getBladeTableCharID16Percent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeTableCharID16Percent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeTableCharID16Percent], id, 1).valueU8;
}

void initBladeListCategory(const CBdatWrapper &wrapper) { s_members[BladeListCategory] = Bdat::getMember(wrapper.data, "Category"); }

u32 getBladeListCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeListCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeListCategory], id, 1).valueU8;
}

void initBladeListStatusID(const CBdatWrapper &wrapper) { s_members[BladeListStatusID] = Bdat::getMember(wrapper.data, "StatusID"); }

u32 getBladeListStatusID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeListStatusID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeListStatusID], id, 2).valueU16;
}

void initCommonListQuestRace(const CBdatWrapper &wrapper) { s_members[CommonListQuestRace] = Bdat::getMember(wrapper.data, "QuestRace"); }

u32 getCommonListQuestRace(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListQuestRace] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListQuestRace], id, 1).valueU8;
}

void initCommonListGender(const CBdatWrapper &wrapper) { s_members[CommonListGender] = Bdat::getMember(wrapper.data, "Gender"); }

u32 getCommonListGender(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListGender] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListGender], id, 1).valueU8;
}

void initCommonListWeapon(const CBdatWrapper &wrapper) { s_members[CommonListWeapon] = Bdat::getMember(wrapper.data, "Weapon"); }

u32 getCommonListWeapon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListWeapon] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListWeapon], id, 3).valueU32;
}

void initCommonListAtr(const CBdatWrapper &wrapper) { s_members[CommonListAtr] = Bdat::getMember(wrapper.data, "Atr"); }

u32 getCommonListAtr(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListAtr] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListAtr], id, 1).valueU8;
}

void initCommonListModelTable(const CBdatWrapper &wrapper) { s_members[CommonListModelTable] = Bdat::getMember(wrapper.data, "ModelTable"); }

u32 getCommonListModelTable(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListModelTable] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListModelTable], id, 2).valueU16;
}

void initCommonListIdeaType(const CBdatWrapper &wrapper) { s_members[CommonListIdeaType] = Bdat::getMember(wrapper.data, "IdeaType"); }

u32 getCommonListIdeaType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListIdeaType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListIdeaType], id, 1).valueU8;
}

void initCommonListIdeaMin(const CBdatWrapper &wrapper) { s_members[CommonListIdeaMin] = Bdat::getMember(wrapper.data, "IdeaMin"); }

u32 getCommonListIdeaMin(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListIdeaMin] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListIdeaMin], id, 1).valueU8;
}

void initCommonListIdeaMax(const CBdatWrapper &wrapper) { s_members[CommonListIdeaMax] = Bdat::getMember(wrapper.data, "IdeaMax"); }

u32 getCommonListIdeaMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListIdeaMax] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListIdeaMax], id, 1).valueU8;
}

void initCommonListRatio(const CBdatWrapper &wrapper) { s_members[CommonListRatio] = Bdat::getMember(wrapper.data, "Ratio"); }

u32 getCommonListRatio(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListRatio] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListRatio], id, 1).valueU8;
}

void initCommonListRarityMin(const CBdatWrapper &wrapper) { s_members[CommonListRarityMin] = Bdat::getMember(wrapper.data, "RarityMin"); }

u32 getCommonListRarityMin(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListRarityMin] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListRarityMin], id, 1).valueU8;
}

void initCommonListRarityMax(const CBdatWrapper &wrapper) { s_members[CommonListRarityMax] = Bdat::getMember(wrapper.data, "RarityMax"); }

u32 getCommonListRarityMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListRarityMax] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListRarityMax], id, 1).valueU8;
}

void initCommonListFskill(const CBdatWrapper &wrapper) { s_members[CommonListFskill] = Bdat::getMember(wrapper.data, "Fskill"); }

u32 getCommonListFskill(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListFskill] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListFskill], id, 1).valueU8;
}

void initCommonListArtsAchievementSet1(const CBdatWrapper &wrapper) {
  s_members[CommonListArtsAchievementSet1] = Bdat::getMember(wrapper.data, "ArtsAchievementSet1");
}

u32 getCommonListArtsAchievementSet1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListArtsAchievementSet1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListArtsAchievementSet1], id, 1).valueU8;
}

void initCommonListArtsAchievementSet2(const CBdatWrapper &wrapper) {
  s_members[CommonListArtsAchievementSet2] = Bdat::getMember(wrapper.data, "ArtsAchievementSet2");
}

u32 getCommonListArtsAchievementSet2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListArtsAchievementSet2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListArtsAchievementSet2], id, 1).valueU8;
}

void initCommonListArtsAchievementSet3(const CBdatWrapper &wrapper) {
  s_members[CommonListArtsAchievementSet3] = Bdat::getMember(wrapper.data, "ArtsAchievementSet3");
}

u32 getCommonListArtsAchievementSet3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListArtsAchievementSet3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListArtsAchievementSet3], id, 1).valueU8;
}

void initCommonListSkillAchievementSet1(const CBdatWrapper &wrapper) {
  s_members[CommonListSkillAchievementSet1] = Bdat::getMember(wrapper.data, "SkillAchievementSet1");
}

u32 getCommonListSkillAchievementSet1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListSkillAchievementSet1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListSkillAchievementSet1], id, 1).valueU8;
}

void initCommonListSkillAchievementSet2(const CBdatWrapper &wrapper) {
  s_members[CommonListSkillAchievementSet2] = Bdat::getMember(wrapper.data, "SkillAchievementSet2");
}

u32 getCommonListSkillAchievementSet2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListSkillAchievementSet2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListSkillAchievementSet2], id, 1).valueU8;
}

void initCommonListSkillAchievementSet3(const CBdatWrapper &wrapper) {
  s_members[CommonListSkillAchievementSet3] = Bdat::getMember(wrapper.data, "SkillAchievementSet3");
}

u32 getCommonListSkillAchievementSet3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListSkillAchievementSet3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListSkillAchievementSet3], id, 1).valueU8;
}

void initCommonListFskillAchivementSet1(const CBdatWrapper &wrapper) {
  s_members[CommonListFskillAchivementSet1] = Bdat::getMember(wrapper.data, "FskillAchivementSet1");
}

u32 getCommonListFskillAchivementSet1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListFskillAchivementSet1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListFskillAchivementSet1], id, 1).valueU8;
}

void initCommonListFskillAchivementSet2(const CBdatWrapper &wrapper) {
  s_members[CommonListFskillAchivementSet2] = Bdat::getMember(wrapper.data, "FskillAchivementSet2");
}

u32 getCommonListFskillAchivementSet2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListFskillAchivementSet2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListFskillAchivementSet2], id, 1).valueU8;
}

void initCommonListFskillAchivementSet3(const CBdatWrapper &wrapper) {
  s_members[CommonListFskillAchivementSet3] = Bdat::getMember(wrapper.data, "FskillAchivementSet3");
}

u32 getCommonListFskillAchivementSet3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListFskillAchivementSet3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListFskillAchivementSet3], id, 1).valueU8;
}

void initCommonListKeyAchievementSet(const CBdatWrapper &wrapper) {
  s_members[CommonListKeyAchievementSet] = Bdat::getMember(wrapper.data, "KeyAchievementSet");
}

u32 getCommonListKeyAchievementSet(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListKeyAchievementSet] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListKeyAchievementSet], id, 1).valueU8;
}

void initCommonListFavoriteCategoryMax(const CBdatWrapper &wrapper) {
  s_members[CommonListFavoriteCategoryMax] = Bdat::getMember(wrapper.data, "FavoriteCategoryMax");
}

u32 getCommonListFavoriteCategoryMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListFavoriteCategoryMax] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListFavoriteCategoryMax], id, 1).valueU8;
}

void initCommonListFavoriteItemMax(const CBdatWrapper &wrapper) {
  s_members[CommonListFavoriteItemMax] = Bdat::getMember(wrapper.data, "FavoriteItemMax");
}

u32 getCommonListFavoriteItemMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CommonListFavoriteItemMax] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CommonListFavoriteItemMax], id, 1).valueU8;
}

void initNameListCategory(const CBdatWrapper &wrapper) { s_members[NameListCategory] = Bdat::getMember(wrapper.data, "Category"); }

u32 getNameListCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[NameListCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[NameListCategory], id, 2).valueU16;
}

void initNameListRace(const CBdatWrapper &wrapper) { s_members[NameListRace] = Bdat::getMember(wrapper.data, "Race"); }

u32 getNameListRace(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[NameListRace] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[NameListRace], id, 1).valueU8;
}

void initNameListGender(const CBdatWrapper &wrapper) { s_members[NameListGender] = Bdat::getMember(wrapper.data, "Gender"); }

u32 getNameListGender(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[NameListGender] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[NameListGender], id, 1).valueU8;
}

void initBladeModelListQuestRace(const CBdatWrapper &wrapper) { s_members[BladeModelListQuestRace] = Bdat::getMember(wrapper.data, "QuestRace"); }

u32 getBladeModelListQuestRace(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeModelListQuestRace] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeModelListQuestRace], id, 1).valueU8;
}

void initBladeModelListGender(const CBdatWrapper &wrapper) { s_members[BladeModelListGender] = Bdat::getMember(wrapper.data, "Gender"); }

u32 getBladeModelListGender(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeModelListGender] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeModelListGender], id, 1).valueU8;
}

void initBladeModelListIdeaMin(const CBdatWrapper &wrapper) { s_members[BladeModelListIdeaMin] = Bdat::getMember(wrapper.data, "IdeaMin"); }

u32 getBladeModelListIdeaMin(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeModelListIdeaMin] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeModelListIdeaMin], id, 1).valueU8;
}

void initBladeModelListIdeaMax(const CBdatWrapper &wrapper) { s_members[BladeModelListIdeaMax] = Bdat::getMember(wrapper.data, "IdeaMax"); }

u32 getBladeModelListIdeaMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeModelListIdeaMax] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeModelListIdeaMax], id, 1).valueU8;
}

void initBladeModelListModel1(const CBdatWrapper &wrapper) { s_members[BladeModelListModel1] = Bdat::getMember(wrapper.data, "Model1"); }

u32 getBladeModelListModel1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeModelListModel1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeModelListModel1], id, 1).valueU8;
}

void initBladeModelListModel2(const CBdatWrapper &wrapper) { s_members[BladeModelListModel2] = Bdat::getMember(wrapper.data, "Model2"); }

u32 getBladeModelListModel2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeModelListModel2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeModelListModel2], id, 1).valueU8;
}

void initBladeModelListPartsNumMin(const CBdatWrapper &wrapper) {
  s_members[BladeModelListPartsNumMin] = Bdat::getMember(wrapper.data, "PartsNumMin");
}

u32 getBladeModelListPartsNumMin(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeModelListPartsNumMin] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeModelListPartsNumMin], id, 1).valueU8;
}

void initBladeModelListPartsNumMax(const CBdatWrapper &wrapper) {
  s_members[BladeModelListPartsNumMax] = Bdat::getMember(wrapper.data, "PartsNumMax");
}

u32 getBladeModelListPartsNumMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeModelListPartsNumMax] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeModelListPartsNumMax], id, 1).valueU8;
}

void initBladeModelListParts1(const CBdatWrapper &wrapper) { s_members[BladeModelListParts1] = Bdat::getMember(wrapper.data, "Parts1"); }

u32 getBladeModelListParts1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeModelListParts1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeModelListParts1], id, 1).valueU8;
}

void initBladeModelListParts2(const CBdatWrapper &wrapper) { s_members[BladeModelListParts2] = Bdat::getMember(wrapper.data, "Parts2"); }

u32 getBladeModelListParts2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeModelListParts2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeModelListParts2], id, 1).valueU8;
}

void initBladeModelListParts3(const CBdatWrapper &wrapper) { s_members[BladeModelListParts3] = Bdat::getMember(wrapper.data, "Parts3"); }

u32 getBladeModelListParts3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeModelListParts3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeModelListParts3], id, 1).valueU8;
}

void initBladeModelListParts4(const CBdatWrapper &wrapper) { s_members[BladeModelListParts4] = Bdat::getMember(wrapper.data, "Parts4"); }

u32 getBladeModelListParts4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BladeModelListParts4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BladeModelListParts4], id, 1).valueU8;
}

void initCreateConfigValue(const CBdatWrapper &wrapper) { s_members[CreateConfigValue] = Bdat::getMember(wrapper.data, "Value"); }

u32 getCreateConfigValue(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CreateConfigValue] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CreateConfigValue], id, 3).valueU32;
}

void initCmnBl_CapacityArtsNum1Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityArtsNum1Prob] = Bdat::getMember(wrapper.data, "ArtsNum1Prob");
}

u32 getCmnBl_CapacityArtsNum1Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityArtsNum1Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityArtsNum1Prob], id, 1).valueU8;
}

void initCmnBl_CapacityArtsNum2Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityArtsNum2Prob] = Bdat::getMember(wrapper.data, "ArtsNum2Prob");
}

u32 getCmnBl_CapacityArtsNum2Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityArtsNum2Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityArtsNum2Prob], id, 1).valueU8;
}

void initCmnBl_CapacityArtsNum3Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityArtsNum3Prob] = Bdat::getMember(wrapper.data, "ArtsNum3Prob");
}

u32 getCmnBl_CapacityArtsNum3Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityArtsNum3Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityArtsNum3Prob], id, 1).valueU8;
}

void initCmnBl_CapacityArtsLv1Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityArtsLv1Prob] = Bdat::getMember(wrapper.data, "ArtsLv1Prob");
}

u32 getCmnBl_CapacityArtsLv1Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityArtsLv1Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityArtsLv1Prob], id, 1).valueU8;
}

void initCmnBl_CapacityArtsLv2Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityArtsLv2Prob] = Bdat::getMember(wrapper.data, "ArtsLv2Prob");
}

u32 getCmnBl_CapacityArtsLv2Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityArtsLv2Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityArtsLv2Prob], id, 1).valueU8;
}

void initCmnBl_CapacityArtsLv3Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityArtsLv3Prob] = Bdat::getMember(wrapper.data, "ArtsLv3Prob");
}

u32 getCmnBl_CapacityArtsLv3Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityArtsLv3Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityArtsLv3Prob], id, 1).valueU8;
}

void initCmnBl_CapacityArtsLv4Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityArtsLv4Prob] = Bdat::getMember(wrapper.data, "ArtsLv4Prob");
}

u32 getCmnBl_CapacityArtsLv4Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityArtsLv4Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityArtsLv4Prob], id, 1).valueU8;
}

void initCmnBl_CapacityArtsLv5Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityArtsLv5Prob] = Bdat::getMember(wrapper.data, "ArtsLv5Prob");
}

u32 getCmnBl_CapacityArtsLv5Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityArtsLv5Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityArtsLv5Prob], id, 1).valueU8;
}

void initCmnBl_CapacityArtsRevCon(const CBdatWrapper &wrapper) { s_members[CmnBl_CapacityArtsRevCon] = Bdat::getMember(wrapper.data, "ArtsRevCon"); }

u32 getCmnBl_CapacityArtsRevCon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityArtsRevCon] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityArtsRevCon], id, 1).valueU8;
}

void initCmnBl_CapacityArtsRevRand(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityArtsRevRand] = Bdat::getMember(wrapper.data, "ArtsRevRand");
}

u32 getCmnBl_CapacityArtsRevRand(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityArtsRevRand] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityArtsRevRand], id, 1).valueU8;
}

void initCmnBl_CapacitySpArtsRevCon(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacitySpArtsRevCon] = Bdat::getMember(wrapper.data, "SpArtsRevCon");
}

u32 getCmnBl_CapacitySpArtsRevCon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacitySpArtsRevCon] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacitySpArtsRevCon], id, 1).valueU8;
}

void initCmnBl_CapacitySpArtsRevRand(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacitySpArtsRevRand] = Bdat::getMember(wrapper.data, "SpArtsRevRand");
}

u32 getCmnBl_CapacitySpArtsRevRand(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacitySpArtsRevRand] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacitySpArtsRevRand], id, 1).valueU8;
}

void initCmnBl_CapacitySkillNum1Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacitySkillNum1Prob] = Bdat::getMember(wrapper.data, "SkillNum1Prob");
}

u32 getCmnBl_CapacitySkillNum1Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacitySkillNum1Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacitySkillNum1Prob], id, 1).valueU8;
}

void initCmnBl_CapacitySkillNum2Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacitySkillNum2Prob] = Bdat::getMember(wrapper.data, "SkillNum2Prob");
}

u32 getCmnBl_CapacitySkillNum2Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacitySkillNum2Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacitySkillNum2Prob], id, 1).valueU8;
}

void initCmnBl_CapacitySkillNum3Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacitySkillNum3Prob] = Bdat::getMember(wrapper.data, "SkillNum3Prob");
}

u32 getCmnBl_CapacitySkillNum3Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacitySkillNum3Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacitySkillNum3Prob], id, 1).valueU8;
}

void initCmnBl_CapacitySkillLv1Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacitySkillLv1Prob] = Bdat::getMember(wrapper.data, "SkillLv1Prob");
}

u32 getCmnBl_CapacitySkillLv1Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacitySkillLv1Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacitySkillLv1Prob], id, 1).valueU8;
}

void initCmnBl_CapacitySkillLv2Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacitySkillLv2Prob] = Bdat::getMember(wrapper.data, "SkillLv2Prob");
}

u32 getCmnBl_CapacitySkillLv2Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacitySkillLv2Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacitySkillLv2Prob], id, 1).valueU8;
}

void initCmnBl_CapacitySkillLv3Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacitySkillLv3Prob] = Bdat::getMember(wrapper.data, "SkillLv3Prob");
}

u32 getCmnBl_CapacitySkillLv3Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacitySkillLv3Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacitySkillLv3Prob], id, 1).valueU8;
}

void initCmnBl_CapacitySkillLv4Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacitySkillLv4Prob] = Bdat::getMember(wrapper.data, "SkillLv4Prob");
}

u32 getCmnBl_CapacitySkillLv4Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacitySkillLv4Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacitySkillLv4Prob], id, 1).valueU8;
}

void initCmnBl_CapacitySkillLv5Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacitySkillLv5Prob] = Bdat::getMember(wrapper.data, "SkillLv5Prob");
}

u32 getCmnBl_CapacitySkillLv5Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacitySkillLv5Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacitySkillLv5Prob], id, 1).valueU8;
}

void initCmnBl_CapacityOrbNum0Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityOrbNum0Prob] = Bdat::getMember(wrapper.data, "OrbNum0Prob");
}

u32 getCmnBl_CapacityOrbNum0Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityOrbNum0Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityOrbNum0Prob], id, 1).valueU8;
}

void initCmnBl_CapacityOrbNum1Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityOrbNum1Prob] = Bdat::getMember(wrapper.data, "OrbNum1Prob");
}

u32 getCmnBl_CapacityOrbNum1Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityOrbNum1Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityOrbNum1Prob], id, 1).valueU8;
}

void initCmnBl_CapacityOrbNum2Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityOrbNum2Prob] = Bdat::getMember(wrapper.data, "OrbNum2Prob");
}

u32 getCmnBl_CapacityOrbNum2Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityOrbNum2Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityOrbNum2Prob], id, 1).valueU8;
}

void initCmnBl_CapacityOrbNum3Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityOrbNum3Prob] = Bdat::getMember(wrapper.data, "OrbNum3Prob");
}

u32 getCmnBl_CapacityOrbNum3Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityOrbNum3Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityOrbNum3Prob], id, 1).valueU8;
}

void initCmnBl_CapacityNartsNum1Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityNartsNum1Prob] = Bdat::getMember(wrapper.data, "NartsNum1Prob");
}

u32 getCmnBl_CapacityNartsNum1Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityNartsNum1Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityNartsNum1Prob], id, 1).valueU8;
}

void initCmnBl_CapacityNartsNum2Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityNartsNum2Prob] = Bdat::getMember(wrapper.data, "NartsNum2Prob");
}

u32 getCmnBl_CapacityNartsNum2Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityNartsNum2Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityNartsNum2Prob], id, 1).valueU8;
}

void initCmnBl_CapacityNartsNum3Prob(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityNartsNum3Prob] = Bdat::getMember(wrapper.data, "NartsNum3Prob");
}

u32 getCmnBl_CapacityNartsNum3Prob(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityNartsNum3Prob] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityNartsNum3Prob], id, 1).valueU8;
}

void initCmnBl_CapacityNartsRevCon(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityNartsRevCon] = Bdat::getMember(wrapper.data, "NartsRevCon");
}

u32 getCmnBl_CapacityNartsRevCon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityNartsRevCon] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityNartsRevCon], id, 1).valueU8;
}

void initCmnBl_CapacityNartsRevRand(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityNartsRevRand] = Bdat::getMember(wrapper.data, "NartsRevRand");
}

u32 getCmnBl_CapacityNartsRevRand(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityNartsRevRand] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityNartsRevRand], id, 1).valueU8;
}

void initCmnBl_CapacityStatusRevCon(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityStatusRevCon] = Bdat::getMember(wrapper.data, "StatusRevCon");
}

u32 getCmnBl_CapacityStatusRevCon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityStatusRevCon] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityStatusRevCon], id, 1).valueU8;
}

void initCmnBl_CapacityStatusRevRand(const CBdatWrapper &wrapper) {
  s_members[CmnBl_CapacityStatusRevRand] = Bdat::getMember(wrapper.data, "StatusRevRand");
}

u32 getCmnBl_CapacityStatusRevRand(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_CapacityStatusRevRand] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_CapacityStatusRevRand], id, 1).valueU8;
}

void initCmnBl_PowerMinLv(const CBdatWrapper &wrapper) { s_members[CmnBl_PowerMinLv] = Bdat::getMember(wrapper.data, "MinLv"); }

u32 getCmnBl_PowerMinLv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_PowerMinLv] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_PowerMinLv], id, 1).valueU8;
}

void initCmnBl_PowerMaxLv(const CBdatWrapper &wrapper) { s_members[CmnBl_PowerMaxLv] = Bdat::getMember(wrapper.data, "MaxLv"); }

u32 getCmnBl_PowerMaxLv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_PowerMaxLv] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_PowerMaxLv], id, 1).valueU8;
}

void initCmnBl_PowerPow01(const CBdatWrapper &wrapper) { s_members[CmnBl_PowerPow01] = Bdat::getMember(wrapper.data, "Pow01"); }

u32 getCmnBl_PowerPow01(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_PowerPow01] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_PowerPow01], id, 2).valueU16;
}

void initCmnBl_PowerPow02(const CBdatWrapper &wrapper) { s_members[CmnBl_PowerPow02] = Bdat::getMember(wrapper.data, "Pow02"); }

u32 getCmnBl_PowerPow02(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_PowerPow02] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_PowerPow02], id, 2).valueU16;
}

void initCmnBl_PowerPow03(const CBdatWrapper &wrapper) { s_members[CmnBl_PowerPow03] = Bdat::getMember(wrapper.data, "Pow03"); }

u32 getCmnBl_PowerPow03(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_PowerPow03] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_PowerPow03], id, 2).valueU16;
}

void initCmnBl_PowerPow04(const CBdatWrapper &wrapper) { s_members[CmnBl_PowerPow04] = Bdat::getMember(wrapper.data, "Pow04"); }

u32 getCmnBl_PowerPow04(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_PowerPow04] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_PowerPow04], id, 2).valueU16;
}

void initCmnBl_PowerPow05(const CBdatWrapper &wrapper) { s_members[CmnBl_PowerPow05] = Bdat::getMember(wrapper.data, "Pow05"); }

u32 getCmnBl_PowerPow05(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_PowerPow05] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_PowerPow05], id, 2).valueU16;
}

void initCmnBl_PowerPow06(const CBdatWrapper &wrapper) { s_members[CmnBl_PowerPow06] = Bdat::getMember(wrapper.data, "Pow06"); }

u32 getCmnBl_PowerPow06(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_PowerPow06] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_PowerPow06], id, 2).valueU16;
}

void initCmnBl_PowerPow07(const CBdatWrapper &wrapper) { s_members[CmnBl_PowerPow07] = Bdat::getMember(wrapper.data, "Pow07"); }

u32 getCmnBl_PowerPow07(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_PowerPow07] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_PowerPow07], id, 2).valueU16;
}

void initCmnBl_PowerPow08(const CBdatWrapper &wrapper) { s_members[CmnBl_PowerPow08] = Bdat::getMember(wrapper.data, "Pow08"); }

u32 getCmnBl_PowerPow08(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_PowerPow08] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_PowerPow08], id, 2).valueU16;
}

void initCmnBl_PowerPow09(const CBdatWrapper &wrapper) { s_members[CmnBl_PowerPow09] = Bdat::getMember(wrapper.data, "Pow09"); }

u32 getCmnBl_PowerPow09(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_PowerPow09] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_PowerPow09], id, 2).valueU16;
}

void initCmnBl_PowerPow10(const CBdatWrapper &wrapper) { s_members[CmnBl_PowerPow10] = Bdat::getMember(wrapper.data, "Pow10"); }

u32 getCmnBl_PowerPow10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_PowerPow10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_PowerPow10], id, 2).valueU16;
}

void initCmnBl_NewBlArtsWpnType(const CBdatWrapper &wrapper) { s_members[CmnBl_NewBlArtsWpnType] = Bdat::getMember(wrapper.data, "WpnType"); }

u32 getCmnBl_NewBlArtsWpnType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_NewBlArtsWpnType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_NewBlArtsWpnType], id, 1).valueU8;
}

void initCmnBl_NewBlArtsNBA_01(const CBdatWrapper &wrapper) { s_members[CmnBl_NewBlArtsNBA_01] = Bdat::getMember(wrapper.data, "NBA_01"); }

u32 getCmnBl_NewBlArtsNBA_01(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_NewBlArtsNBA_01] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_NewBlArtsNBA_01], id, 1).valueU8;
}

void initCmnBl_NewBlArtsNBA_02(const CBdatWrapper &wrapper) { s_members[CmnBl_NewBlArtsNBA_02] = Bdat::getMember(wrapper.data, "NBA_02"); }

u32 getCmnBl_NewBlArtsNBA_02(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_NewBlArtsNBA_02] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_NewBlArtsNBA_02], id, 1).valueU8;
}

void initCmnBl_NewBlArtsNBA_03(const CBdatWrapper &wrapper) { s_members[CmnBl_NewBlArtsNBA_03] = Bdat::getMember(wrapper.data, "NBA_03"); }

u32 getCmnBl_NewBlArtsNBA_03(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_NewBlArtsNBA_03] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_NewBlArtsNBA_03], id, 1).valueU8;
}

void initCmnBl_NewBlArtsNBA_04(const CBdatWrapper &wrapper) { s_members[CmnBl_NewBlArtsNBA_04] = Bdat::getMember(wrapper.data, "NBA_04"); }

u32 getCmnBl_NewBlArtsNBA_04(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_NewBlArtsNBA_04] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_NewBlArtsNBA_04], id, 1).valueU8;
}

void initCmnBl_NewBlArtsNBA_05(const CBdatWrapper &wrapper) { s_members[CmnBl_NewBlArtsNBA_05] = Bdat::getMember(wrapper.data, "NBA_05"); }

u32 getCmnBl_NewBlArtsNBA_05(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_NewBlArtsNBA_05] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_NewBlArtsNBA_05], id, 1).valueU8;
}

void initCmnBl_NewBlArtsNBA_06(const CBdatWrapper &wrapper) { s_members[CmnBl_NewBlArtsNBA_06] = Bdat::getMember(wrapper.data, "NBA_06"); }

u32 getCmnBl_NewBlArtsNBA_06(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_NewBlArtsNBA_06] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_NewBlArtsNBA_06], id, 1).valueU8;
}

void initCmnBl_NewBlArtsNBA_07(const CBdatWrapper &wrapper) { s_members[CmnBl_NewBlArtsNBA_07] = Bdat::getMember(wrapper.data, "NBA_07"); }

u32 getCmnBl_NewBlArtsNBA_07(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_NewBlArtsNBA_07] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_NewBlArtsNBA_07], id, 1).valueU8;
}

void initCmnBl_NewBlArtsNBA_08(const CBdatWrapper &wrapper) { s_members[CmnBl_NewBlArtsNBA_08] = Bdat::getMember(wrapper.data, "NBA_08"); }

u32 getCmnBl_NewBlArtsNBA_08(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_NewBlArtsNBA_08] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_NewBlArtsNBA_08], id, 1).valueU8;
}

void initCmnBl_StatusTypeWpnType(const CBdatWrapper &wrapper) { s_members[CmnBl_StatusTypeWpnType] = Bdat::getMember(wrapper.data, "WpnType"); }

u32 getCmnBl_StatusTypeWpnType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_StatusTypeWpnType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_StatusTypeWpnType], id, 1).valueU8;
}

void initCmnBl_StatusTypeStatus01(const CBdatWrapper &wrapper) { s_members[CmnBl_StatusTypeStatus01] = Bdat::getMember(wrapper.data, "Status01"); }

u32 getCmnBl_StatusTypeStatus01(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_StatusTypeStatus01] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_StatusTypeStatus01], id, 1).valueU8;
}

void initCmnBl_StatusTypeStatus02(const CBdatWrapper &wrapper) { s_members[CmnBl_StatusTypeStatus02] = Bdat::getMember(wrapper.data, "Status02"); }

u32 getCmnBl_StatusTypeStatus02(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_StatusTypeStatus02] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_StatusTypeStatus02], id, 1).valueU8;
}

void initCmnBl_StatusTypeStatus03(const CBdatWrapper &wrapper) { s_members[CmnBl_StatusTypeStatus03] = Bdat::getMember(wrapper.data, "Status03"); }

u32 getCmnBl_StatusTypeStatus03(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_StatusTypeStatus03] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_StatusTypeStatus03], id, 1).valueU8;
}

void initCmnBl_StatusTypeStatus04(const CBdatWrapper &wrapper) { s_members[CmnBl_StatusTypeStatus04] = Bdat::getMember(wrapper.data, "Status04"); }

u32 getCmnBl_StatusTypeStatus04(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_StatusTypeStatus04] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_StatusTypeStatus04], id, 1).valueU8;
}

void initCmnBl_StatusTypeStatus05(const CBdatWrapper &wrapper) { s_members[CmnBl_StatusTypeStatus05] = Bdat::getMember(wrapper.data, "Status05"); }

u32 getCmnBl_StatusTypeStatus05(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_StatusTypeStatus05] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_StatusTypeStatus05], id, 1).valueU8;
}

void initCmnBl_StatusTypeStatus06(const CBdatWrapper &wrapper) { s_members[CmnBl_StatusTypeStatus06] = Bdat::getMember(wrapper.data, "Status06"); }

u32 getCmnBl_StatusTypeStatus06(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_StatusTypeStatus06] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_StatusTypeStatus06], id, 1).valueU8;
}

void initCmnBl_ArmorWpnType(const CBdatWrapper &wrapper) { s_members[CmnBl_ArmorWpnType] = Bdat::getMember(wrapper.data, "WpnType"); }

u32 getCmnBl_ArmorWpnType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_ArmorWpnType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_ArmorWpnType], id, 1).valueU8;
}

void initCmnBl_ArmorPArmorCon(const CBdatWrapper &wrapper) { s_members[CmnBl_ArmorPArmorCon] = Bdat::getMember(wrapper.data, "PArmorCon"); }

u32 getCmnBl_ArmorPArmorCon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_ArmorPArmorCon] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_ArmorPArmorCon], id, 1).valueU8;
}

void initCmnBl_ArmorPArmorRand(const CBdatWrapper &wrapper) { s_members[CmnBl_ArmorPArmorRand] = Bdat::getMember(wrapper.data, "PArmorRand"); }

u32 getCmnBl_ArmorPArmorRand(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_ArmorPArmorRand] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_ArmorPArmorRand], id, 1).valueU8;
}

void initCmnBl_ArmorEArmorCon(const CBdatWrapper &wrapper) { s_members[CmnBl_ArmorEArmorCon] = Bdat::getMember(wrapper.data, "EArmorCon"); }

u32 getCmnBl_ArmorEArmorCon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_ArmorEArmorCon] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_ArmorEArmorCon], id, 1).valueU8;
}

void initCmnBl_ArmorEArmorRand(const CBdatWrapper &wrapper) { s_members[CmnBl_ArmorEArmorRand] = Bdat::getMember(wrapper.data, "EArmorRand"); }

u32 getCmnBl_ArmorEArmorRand(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CmnBl_ArmorEArmorRand] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CmnBl_ArmorEArmorRand], id, 1).valueU8;
}

void initFLD_IdeaTableTrustPoint(const CBdatWrapper &wrapper) { s_members[FLD_IdeaTableTrustPoint] = Bdat::getMember(wrapper.data, "TrustPoint"); }

u32 getFLD_IdeaTableTrustPoint(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_IdeaTableTrustPoint] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_IdeaTableTrustPoint], id, 3).valueU32;
}

void initFLD_IdeaTableWpnRatio(const CBdatWrapper &wrapper) { s_members[FLD_IdeaTableWpnRatio] = Bdat::getMember(wrapper.data, "WpnRatio"); }

u32 getFLD_IdeaTableWpnRatio(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_IdeaTableWpnRatio] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_IdeaTableWpnRatio], id, 2).valueU16;
}

void initFLD_IdeaTableNArtsProbRev(const CBdatWrapper &wrapper) {
  s_members[FLD_IdeaTableNArtsProbRev] = Bdat::getMember(wrapper.data, "NArtsProbRev");
}

u32 getFLD_IdeaTableNArtsProbRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_IdeaTableNArtsProbRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_IdeaTableNArtsProbRev], id, 1).valueU8;
}

void initFLD_IdeaTableBladeChangeRev(const CBdatWrapper &wrapper) {
  s_members[FLD_IdeaTableBladeChangeRev] = Bdat::getMember(wrapper.data, "BladeChangeRev");
}

s32 getFLD_IdeaTableBladeChangeRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_IdeaTableBladeChangeRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_IdeaTableBladeChangeRev], id, 5).valueS16;
}

void initFLD_IdeaTableBladeArtsRev(const CBdatWrapper &wrapper) {
  s_members[FLD_IdeaTableBladeArtsRev] = Bdat::getMember(wrapper.data, "BladeArtsRev");
}

s32 getFLD_IdeaTableBladeArtsRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_IdeaTableBladeArtsRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_IdeaTableBladeArtsRev], id, 5).valueS16;
}

void initBLD_IdeaNeedPoint(const CBdatWrapper &wrapper) { s_members[BLD_IdeaNeedPoint] = Bdat::getMember(wrapper.data, "NeedPoint"); }

u32 getBLD_IdeaNeedPoint(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BLD_IdeaNeedPoint] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BLD_IdeaNeedPoint], id, 3).valueU32;
}

void initBLD_IdeaProbRev(const CBdatWrapper &wrapper) { s_members[BLD_IdeaProbRev] = Bdat::getMember(wrapper.data, "ProbRev"); }

u32 getBLD_IdeaProbRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BLD_IdeaProbRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BLD_IdeaProbRev], id, 2).valueU16;
}

void initBLD_IdeaAtrDamRev(const CBdatWrapper &wrapper) { s_members[BLD_IdeaAtrDamRev] = Bdat::getMember(wrapper.data, "AtrDamRev"); }

u32 getBLD_IdeaAtrDamRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BLD_IdeaAtrDamRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BLD_IdeaAtrDamRev], id, 2).valueU16;
}

void initBLD_RareListBlade(const CBdatWrapper &wrapper) { s_members[BLD_RareListBlade] = Bdat::getMember(wrapper.data, "Blade"); }

u32 getBLD_RareListBlade(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BLD_RareListBlade] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BLD_RareListBlade], id, 2).valueU16;
}

void initBLD_RareListCondition(const CBdatWrapper &wrapper) { s_members[BLD_RareListCondition] = Bdat::getMember(wrapper.data, "Condition"); }

u32 getBLD_RareListCondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BLD_RareListCondition] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BLD_RareListCondition], id, 2).valueU16;
}

void initBLD_RareListProb1(const CBdatWrapper &wrapper) { s_members[BLD_RareListProb1] = Bdat::getMember(wrapper.data, "Prob1"); }

f32 getBLD_RareListProb1(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[BLD_RareListProb1] != nullptr && id >= Bdat::getIdTop(wrapper.data) &&
      id < Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    value = wrapper.getValCheck(s_members[BLD_RareListProb1], id, 8).valueF32;
  }

  return value;
}

void initBLD_RareListAssure1(const CBdatWrapper &wrapper) { s_members[BLD_RareListAssure1] = Bdat::getMember(wrapper.data, "Assure1"); }

u32 getBLD_RareListAssure1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BLD_RareListAssure1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BLD_RareListAssure1], id, 1).valueU8;
}

void initBLD_RareListProb2(const CBdatWrapper &wrapper) { s_members[BLD_RareListProb2] = Bdat::getMember(wrapper.data, "Prob2"); }

f32 getBLD_RareListProb2(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[BLD_RareListProb2] != nullptr && id >= Bdat::getIdTop(wrapper.data) &&
      id < Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    value = wrapper.getValCheck(s_members[BLD_RareListProb2], id, 8).valueF32;
  }

  return value;
}

void initBLD_RareListAssure2(const CBdatWrapper &wrapper) { s_members[BLD_RareListAssure2] = Bdat::getMember(wrapper.data, "Assure2"); }

u32 getBLD_RareListAssure2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BLD_RareListAssure2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BLD_RareListAssure2], id, 1).valueU8;
}

void initBLD_RareListProb3(const CBdatWrapper &wrapper) { s_members[BLD_RareListProb3] = Bdat::getMember(wrapper.data, "Prob3"); }

f32 getBLD_RareListProb3(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[BLD_RareListProb3] != nullptr && id >= Bdat::getIdTop(wrapper.data) &&
      id < Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    value = wrapper.getValCheck(s_members[BLD_RareListProb3], id, 8).valueF32;
  }

  return value;
}

void initBLD_RareListAssure3(const CBdatWrapper &wrapper) { s_members[BLD_RareListAssure3] = Bdat::getMember(wrapper.data, "Assure3"); }

u32 getBLD_RareListAssure3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BLD_RareListAssure3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BLD_RareListAssure3], id, 1).valueU8;
}

void initBLD_RareListProb4(const CBdatWrapper &wrapper) { s_members[BLD_RareListProb4] = Bdat::getMember(wrapper.data, "Prob4"); }

f32 getBLD_RareListProb4(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[BLD_RareListProb4] != nullptr && id >= Bdat::getIdTop(wrapper.data) &&
      id < Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    value = wrapper.getValCheck(s_members[BLD_RareListProb4], id, 8).valueF32;
  }

  return value;
}

void initBLD_RareListAssure4(const CBdatWrapper &wrapper) { s_members[BLD_RareListAssure4] = Bdat::getMember(wrapper.data, "Assure4"); }

u32 getBLD_RareListAssure4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BLD_RareListAssure4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BLD_RareListAssure4], id, 1).valueU8;
}

void initBLD_RareListProb5(const CBdatWrapper &wrapper) { s_members[BLD_RareListProb5] = Bdat::getMember(wrapper.data, "Prob5"); }

f32 getBLD_RareListProb5(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[BLD_RareListProb5] != nullptr && id >= Bdat::getIdTop(wrapper.data) &&
      id < Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    value = wrapper.getValCheck(s_members[BLD_RareListProb5], id, 8).valueF32;
  }

  return value;
}

void initBLD_RareListAssure5(const CBdatWrapper &wrapper) { s_members[BLD_RareListAssure5] = Bdat::getMember(wrapper.data, "Assure5"); }

u32 getBLD_RareListAssure5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BLD_RareListAssure5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BLD_RareListAssure5], id, 1).valueU8;
}

void initBLD_ReleaceRewardReleace001(const CBdatWrapper &wrapper) {
  s_members[BLD_ReleaceRewardReleace001] = Bdat::getMember(wrapper.data, "Releace001");
}

u32 getBLD_ReleaceRewardReleace001(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BLD_ReleaceRewardReleace001] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BLD_ReleaceRewardReleace001], id, 2).valueU16;
}

void initBLD_ReleaceRewardReleace002(const CBdatWrapper &wrapper) {
  s_members[BLD_ReleaceRewardReleace002] = Bdat::getMember(wrapper.data, "Releace002");
}

u32 getBLD_ReleaceRewardReleace002(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BLD_ReleaceRewardReleace002] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BLD_ReleaceRewardReleace002], id, 2).valueU16;
}

void initBLD_ReleaceRewardReleace003(const CBdatWrapper &wrapper) {
  s_members[BLD_ReleaceRewardReleace003] = Bdat::getMember(wrapper.data, "Releace003");
}

u32 getBLD_ReleaceRewardReleace003(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BLD_ReleaceRewardReleace003] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BLD_ReleaceRewardReleace003], id, 2).valueU16;
}

void initBLD_ReleaceRewardReleace004(const CBdatWrapper &wrapper) {
  s_members[BLD_ReleaceRewardReleace004] = Bdat::getMember(wrapper.data, "Releace004");
}

u32 getBLD_ReleaceRewardReleace004(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BLD_ReleaceRewardReleace004] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BLD_ReleaceRewardReleace004], id, 2).valueU16;
}

void initBLD_ReleaceRewardReleace005(const CBdatWrapper &wrapper) {
  s_members[BLD_ReleaceRewardReleace005] = Bdat::getMember(wrapper.data, "Releace005");
}

u32 getBLD_ReleaceRewardReleace005(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BLD_ReleaceRewardReleace005] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BLD_ReleaceRewardReleace005], id, 2).valueU16;
}

void initBLD_ReleaceRewardReleace006(const CBdatWrapper &wrapper) {
  s_members[BLD_ReleaceRewardReleace006] = Bdat::getMember(wrapper.data, "Releace006");
}

u32 getBLD_ReleaceRewardReleace006(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BLD_ReleaceRewardReleace006] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BLD_ReleaceRewardReleace006], id, 2).valueU16;
}

void initBLD_ReleaceRewardReleace007(const CBdatWrapper &wrapper) {
  s_members[BLD_ReleaceRewardReleace007] = Bdat::getMember(wrapper.data, "Releace007");
}

u32 getBLD_ReleaceRewardReleace007(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BLD_ReleaceRewardReleace007] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BLD_ReleaceRewardReleace007], id, 2).valueU16;
}

u32 getCmnBl_CapacitySkillNumProb(const CBdatWrapper &wrapper, u32 id, u32 index) {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {getCmnBl_CapacitySkillNum1Prob, getCmnBl_CapacitySkillNum2Prob, getCmnBl_CapacitySkillNum3Prob};
  return getters[index](wrapper, id);
}

u32 getCmnBl_CapacitySkillLvProb(const CBdatWrapper &wrapper, u32 id, u32 index) {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {getCmnBl_CapacitySkillLv1Prob,
                                                              getCmnBl_CapacitySkillLv2Prob,
                                                              getCmnBl_CapacitySkillLv3Prob,
                                                              getCmnBl_CapacitySkillLv4Prob,
                                                              getCmnBl_CapacitySkillLv5Prob};
  return getters[index](wrapper, id);
}

u32 getCmnBl_CapacityOrbNumProb(const CBdatWrapper &wrapper, u32 id, u32 index) {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {
      getCmnBl_CapacityOrbNum0Prob, getCmnBl_CapacityOrbNum1Prob, getCmnBl_CapacityOrbNum2Prob, getCmnBl_CapacityOrbNum3Prob};
  return getters[index](wrapper, id);
}

u32 getCmnBl_PowerPow(const CBdatWrapper &wrapper, u32 id, u32 index) {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {getCmnBl_PowerPow01,
                                                              getCmnBl_PowerPow02,
                                                              getCmnBl_PowerPow03,
                                                              getCmnBl_PowerPow04,
                                                              getCmnBl_PowerPow05,
                                                              getCmnBl_PowerPow06,
                                                              getCmnBl_PowerPow07,
                                                              getCmnBl_PowerPow08,
                                                              getCmnBl_PowerPow09,
                                                              getCmnBl_PowerPow10};
  return getters[index](wrapper, id);
}

u32 getCmnBl_NewBlArtsNBA(const CBdatWrapper &wrapper, u32 id, u32 index) {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {getCmnBl_NewBlArtsNBA_01,
                                                              getCmnBl_NewBlArtsNBA_02,
                                                              getCmnBl_NewBlArtsNBA_03,
                                                              getCmnBl_NewBlArtsNBA_04,
                                                              getCmnBl_NewBlArtsNBA_05,
                                                              getCmnBl_NewBlArtsNBA_06,
                                                              getCmnBl_NewBlArtsNBA_07,
                                                              getCmnBl_NewBlArtsNBA_08};
  return getters[index](wrapper, id);
}

u32 getCmnBl_StatusTypeStatus(const CBdatWrapper &wrapper, u32 id, u32 index) {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {getCmnBl_StatusTypeStatus01,
                                                              getCmnBl_StatusTypeStatus02,
                                                              getCmnBl_StatusTypeStatus03,
                                                              getCmnBl_StatusTypeStatus04,
                                                              getCmnBl_StatusTypeStatus05,
                                                              getCmnBl_StatusTypeStatus06};
  return getters[index](wrapper, id);
}

u32 getCommonListArtsAchievementSet(const CBdatWrapper &wrapper, u32 id, u32 index) {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {getCommonListArtsAchievementSet1, getCommonListArtsAchievementSet2, getCommonListArtsAchievementSet3};
  return getters[index](wrapper, id);
}

u32 getCommonListSkillAchievementSet(const CBdatWrapper &wrapper, u32 id, u32 index) {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {getCommonListSkillAchievementSet1, getCommonListSkillAchievementSet2, getCommonListSkillAchievementSet3};
  return getters[index](wrapper, id);
}

u32 getCommonListFskillAchivementSet(const CBdatWrapper &wrapper, u32 id, u32 index) {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {getCommonListFskillAchivementSet1, getCommonListFskillAchivementSet2, getCommonListFskillAchivementSet3};
  return getters[index](wrapper, id);
}

f32 getBLD_RareListProb(const CBdatWrapper &wrapper, u32 id, u32 index) {
  static f32 (*const getters[])(const CBdatWrapper &,
                                u32) = {getBLD_RareListProb1, getBLD_RareListProb2, getBLD_RareListProb3, getBLD_RareListProb4, getBLD_RareListProb5};
  return getters[index](wrapper, id);
}

u32 getBLD_RareListAssure(const CBdatWrapper &wrapper, u32 id, u32 index) {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {
      getBLD_RareListAssure1, getBLD_RareListAssure1, getBLD_RareListAssure2, getBLD_RareListAssure3, getBLD_RareListAssure4};
  return getters[index](wrapper, id);
}

u32 getBLD_ReleaceRewardReleace(const CBdatWrapper &wrapper, u32 id, u32 index) {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {getBLD_ReleaceRewardReleace001,
                                                              getBLD_ReleaceRewardReleace002,
                                                              getBLD_ReleaceRewardReleace003,
                                                              getBLD_ReleaceRewardReleace004,
                                                              getBLD_ReleaceRewardReleace005,
                                                              getBLD_ReleaceRewardReleace006};
  return getters[index](wrapper, id);
}

} // namespace _gfbdb

enum {
  BDAT_BTL_CMN_BL_CAPACITY = 0x19,
  BDAT_BTL_CMN_BL_POWER = 0x1a,
  BDAT_BTL_CMN_BL_NEW_BL_ARTS = 0x1b,
  BDAT_BTL_CMN_BL_STATUS_TYPE = 0x1c,
  BDAT_BTL_CMN_BL_ARMOR = 0x1d,
  BDAT_FLD_IDEA_TABLE = 0x71,
  BDAT_BLD_IDEA = 0xc5,
  BDAT_BLD_IDEA_TABLE = 0xc6,
  BDAT_BLD_BLADE_TABLE = 0xc7,
  BDAT_BLD_BLADE_LIST = 0xc8,
  BDAT_BLD_COMMON_LIST = 0xc9,
  BDAT_BLD_NAME_LIST = 0xca,
  BDAT_BLD_BLADE_MODEL_LIST = 0xcb,
  BDAT_BLD_CREATE_CONFIG = 0xcc,
  BDAT_BLD_RARE_LIST = 0xcd,
  BDAT_BLD_RELEACE_REWARD = 0xce,
};

GfBdatBlade::GfBdatBlade()
    : unknown10(nullptr), unknown18(nullptr), unknown20(nullptr), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr),
      unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(nullptr), unknown60(nullptr),
      unknown68(nullptr), unknown70(nullptr), unknown78(nullptr), unknown80(nullptr), unknown88(nullptr) {
  bdatRefresh();
}

GfBdatBlade::~GfBdatBlade() { destroyFP(); }

void GfBdatBlade::destroyFP() {
  if (unknown10 != nullptr) {
    delete unknown10;
    unknown10 = nullptr;
  }

  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }

  if (unknown20 != nullptr) {
    delete unknown20;
    unknown20 = nullptr;
  }

  if (unknown28 != nullptr) {
    delete unknown28;
    unknown28 = nullptr;
  }

  if (unknown30 != nullptr) {
    delete unknown30;
    unknown30 = nullptr;
  }

  if (unknown38 != nullptr) {
    delete unknown38;
    unknown38 = nullptr;
  }

  if (unknown40 != nullptr) {
    delete unknown40;
    unknown40 = nullptr;
  }

  if (unknown48 != nullptr) {
    delete unknown48;
    unknown48 = nullptr;
  }

  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }

  if (unknown58 != nullptr) {
    delete unknown58;
    unknown58 = nullptr;
  }

  if (unknown60 != nullptr) {
    delete unknown60;
    unknown60 = nullptr;
  }

  if (unknown68 != nullptr) {
    delete unknown68;
    unknown68 = nullptr;
  }

  if (unknown70 != nullptr) {
    delete unknown70;
    unknown70 = nullptr;
  }

  if (unknown78 != nullptr) {
    delete unknown78;
    unknown78 = nullptr;
  }

  if (unknown80 != nullptr) {
    delete unknown80;
    unknown80 = nullptr;
  }

  if (unknown88 != nullptr) {
    delete unknown88;
    unknown88 = nullptr;
  }
}

#define NEW_BDAT_WRAPPER(bdat)                                                                                                                       \
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper { GfDataBdat::getFP(bdat) }

void GfBdatBlade::createFP() {
  unknown10 = NEW_BDAT_WRAPPER(BDAT_BLD_IDEA_TABLE);
  unknown18 = NEW_BDAT_WRAPPER(BDAT_BLD_BLADE_TABLE);
  unknown20 = NEW_BDAT_WRAPPER(BDAT_BLD_BLADE_LIST);
  unknown28 = NEW_BDAT_WRAPPER(BDAT_BLD_COMMON_LIST);
  unknown30 = NEW_BDAT_WRAPPER(BDAT_BLD_NAME_LIST);
  unknown38 = NEW_BDAT_WRAPPER(BDAT_BLD_BLADE_MODEL_LIST);
  unknown40 = NEW_BDAT_WRAPPER(BDAT_BLD_CREATE_CONFIG);
  unknown48 = NEW_BDAT_WRAPPER(BDAT_BTL_CMN_BL_CAPACITY);
  unknown50 = NEW_BDAT_WRAPPER(BDAT_BTL_CMN_BL_POWER);
  unknown58 = NEW_BDAT_WRAPPER(BDAT_BTL_CMN_BL_NEW_BL_ARTS);
  unknown60 = NEW_BDAT_WRAPPER(BDAT_BTL_CMN_BL_STATUS_TYPE);
  unknown68 = NEW_BDAT_WRAPPER(BDAT_BTL_CMN_BL_ARMOR);
  unknown70 = NEW_BDAT_WRAPPER(BDAT_FLD_IDEA_TABLE);
  unknown78 = NEW_BDAT_WRAPPER(BDAT_BLD_IDEA);
  unknown80 = NEW_BDAT_WRAPPER(BDAT_BLD_RARE_LIST);
  unknown88 = NEW_BDAT_WRAPPER(BDAT_BLD_RELEACE_REWARD);
}

void GfBdatBlade::bdatRefresh() {
  destroyFP();
  createFP();
  _gfbdb::initIdeaTableItem(*unknown10);
  _gfbdb::initIdeaTableIdeaBlue(*unknown10);
  _gfbdb::initIdeaTableIdeaRed(*unknown10);
  _gfbdb::initIdeaTableIdeaWhite(*unknown10);
  _gfbdb::initIdeaTableIdeaBlack(*unknown10);
  _gfbdb::initIdeaTableCondition(*unknown10);
  _gfbdb::initIdeaTableBladeTable(*unknown10);
  _gfbdb::initBladeTableCharaID1(*unknown18);
  _gfbdb::initBladeTableCharID1Percent(*unknown18);
  _gfbdb::initBladeTableCharaID2(*unknown18);
  _gfbdb::initBladeTableCharID2Percent(*unknown18);
  _gfbdb::initBladeTableCharaID3(*unknown18);
  _gfbdb::initBladeTableCharID3Percent(*unknown18);
  _gfbdb::initBladeTableCharaID4(*unknown18);
  _gfbdb::initBladeTableCharID4Percent(*unknown18);
  _gfbdb::initBladeTableCharaID5(*unknown18);
  _gfbdb::initBladeTableCharID5Percent(*unknown18);
  _gfbdb::initBladeTableCharaID6(*unknown18);
  _gfbdb::initBladeTableCharID6Percent(*unknown18);
  _gfbdb::initBladeTableCharaID7(*unknown18);
  _gfbdb::initBladeTableCharID7Percent(*unknown18);
  _gfbdb::initBladeTableCharaID8(*unknown18);
  _gfbdb::initBladeTableCharID8Percent(*unknown18);
  _gfbdb::initBladeTableCharaID9(*unknown18);
  _gfbdb::initBladeTableCharID9Percent(*unknown18);
  _gfbdb::initBladeTableCharaID10(*unknown18);
  _gfbdb::initBladeTableCharID10Percent(*unknown18);
  _gfbdb::initBladeTableCharaID11(*unknown18);
  _gfbdb::initBladeTableCharID11Percent(*unknown18);
  _gfbdb::initBladeTableCharaID12(*unknown18);
  _gfbdb::initBladeTableCharID12Percent(*unknown18);
  _gfbdb::initBladeTableCharaID13(*unknown18);
  _gfbdb::initBladeTableCharID13Percent(*unknown18);
  _gfbdb::initBladeTableCharaID14(*unknown18);
  _gfbdb::initBladeTableCharID14Percent(*unknown18);
  _gfbdb::initBladeTableCharaID15(*unknown18);
  _gfbdb::initBladeTableCharID15Percent(*unknown18);
  _gfbdb::initBladeTableCharaID16(*unknown18);
  _gfbdb::initBladeTableCharID16Percent(*unknown18);
  _gfbdb::initBladeListCategory(*unknown20);
  _gfbdb::initBladeListStatusID(*unknown20);
  _gfbdb::initCommonListQuestRace(*unknown28);
  _gfbdb::initCommonListGender(*unknown28);
  _gfbdb::initCommonListWeapon(*unknown28);
  _gfbdb::initCommonListAtr(*unknown28);
  _gfbdb::initCommonListModelTable(*unknown28);
  _gfbdb::initCommonListIdeaType(*unknown28);
  _gfbdb::initCommonListIdeaMin(*unknown28);
  _gfbdb::initCommonListIdeaMax(*unknown28);
  _gfbdb::initCommonListRatio(*unknown28);
  _gfbdb::initCommonListRarityMin(*unknown28);
  _gfbdb::initCommonListRarityMax(*unknown28);
  _gfbdb::initCommonListFskill(*unknown28);
  _gfbdb::initCommonListArtsAchievementSet1(*unknown28);
  _gfbdb::initCommonListArtsAchievementSet2(*unknown28);
  _gfbdb::initCommonListArtsAchievementSet3(*unknown28);
  _gfbdb::initCommonListSkillAchievementSet1(*unknown28);
  _gfbdb::initCommonListSkillAchievementSet2(*unknown28);
  _gfbdb::initCommonListSkillAchievementSet3(*unknown28);
  _gfbdb::initCommonListFskillAchivementSet1(*unknown28);
  _gfbdb::initCommonListFskillAchivementSet2(*unknown28);
  _gfbdb::initCommonListFskillAchivementSet3(*unknown28);
  _gfbdb::initCommonListKeyAchievementSet(*unknown28);
  _gfbdb::initCommonListFavoriteCategoryMax(*unknown28);
  _gfbdb::initCommonListFavoriteItemMax(*unknown28);
  _gfbdb::initNameListCategory(*unknown30);
  _gfbdb::initNameListRace(*unknown30);
  _gfbdb::initNameListGender(*unknown30);
  _gfbdb::initBladeModelListQuestRace(*unknown38);
  _gfbdb::initBladeModelListGender(*unknown38);
  _gfbdb::initBladeModelListIdeaMin(*unknown38);
  _gfbdb::initBladeModelListIdeaMax(*unknown38);
  _gfbdb::initBladeModelListModel1(*unknown38);
  _gfbdb::initBladeModelListModel2(*unknown38);
  _gfbdb::initBladeModelListPartsNumMin(*unknown38);
  _gfbdb::initBladeModelListPartsNumMax(*unknown38);
  _gfbdb::initBladeModelListParts1(*unknown38);
  _gfbdb::initBladeModelListParts2(*unknown38);
  _gfbdb::initBladeModelListParts3(*unknown38);
  _gfbdb::initBladeModelListParts4(*unknown38);
  _gfbdb::initCreateConfigValue(*unknown40);
  _gfbdb::initCmnBl_CapacityArtsNum1Prob(*unknown48);
  _gfbdb::initCmnBl_CapacityArtsNum2Prob(*unknown48);
  _gfbdb::initCmnBl_CapacityArtsNum3Prob(*unknown48);
  _gfbdb::initCmnBl_CapacityArtsLv1Prob(*unknown48);
  _gfbdb::initCmnBl_CapacityArtsLv2Prob(*unknown48);
  _gfbdb::initCmnBl_CapacityArtsLv3Prob(*unknown48);
  _gfbdb::initCmnBl_CapacityArtsLv4Prob(*unknown48);
  _gfbdb::initCmnBl_CapacityArtsLv5Prob(*unknown48);
  _gfbdb::initCmnBl_CapacityArtsRevCon(*unknown48);
  _gfbdb::initCmnBl_CapacityArtsRevRand(*unknown48);
  _gfbdb::initCmnBl_CapacitySpArtsRevCon(*unknown48);
  _gfbdb::initCmnBl_CapacitySpArtsRevRand(*unknown48);
  _gfbdb::initCmnBl_CapacitySkillNum1Prob(*unknown48);
  _gfbdb::initCmnBl_CapacitySkillNum2Prob(*unknown48);
  _gfbdb::initCmnBl_CapacitySkillNum3Prob(*unknown48);
  _gfbdb::initCmnBl_CapacitySkillLv1Prob(*unknown48);
  _gfbdb::initCmnBl_CapacitySkillLv2Prob(*unknown48);
  _gfbdb::initCmnBl_CapacitySkillLv3Prob(*unknown48);
  _gfbdb::initCmnBl_CapacitySkillLv4Prob(*unknown48);
  _gfbdb::initCmnBl_CapacitySkillLv5Prob(*unknown48);
  _gfbdb::initCmnBl_CapacityOrbNum0Prob(*unknown48);
  _gfbdb::initCmnBl_CapacityOrbNum1Prob(*unknown48);
  _gfbdb::initCmnBl_CapacityOrbNum2Prob(*unknown48);
  _gfbdb::initCmnBl_CapacityOrbNum3Prob(*unknown48);
  _gfbdb::initCmnBl_CapacityNartsNum1Prob(*unknown48);
  _gfbdb::initCmnBl_CapacityNartsNum2Prob(*unknown48);
  _gfbdb::initCmnBl_CapacityNartsNum3Prob(*unknown48);
  _gfbdb::initCmnBl_CapacityNartsRevCon(*unknown48);
  _gfbdb::initCmnBl_CapacityNartsRevRand(*unknown48);
  _gfbdb::initCmnBl_CapacityStatusRevCon(*unknown48);
  _gfbdb::initCmnBl_CapacityStatusRevRand(*unknown48);
  _gfbdb::initCmnBl_PowerMinLv(*unknown50);
  _gfbdb::initCmnBl_PowerMaxLv(*unknown50);
  _gfbdb::initCmnBl_PowerPow01(*unknown50);
  _gfbdb::initCmnBl_PowerPow02(*unknown50);
  _gfbdb::initCmnBl_PowerPow03(*unknown50);
  _gfbdb::initCmnBl_PowerPow04(*unknown50);
  _gfbdb::initCmnBl_PowerPow05(*unknown50);
  _gfbdb::initCmnBl_PowerPow06(*unknown50);
  _gfbdb::initCmnBl_PowerPow07(*unknown50);
  _gfbdb::initCmnBl_PowerPow08(*unknown50);
  _gfbdb::initCmnBl_PowerPow09(*unknown50);
  _gfbdb::initCmnBl_PowerPow10(*unknown50);
  _gfbdb::initCmnBl_NewBlArtsWpnType(*unknown58);
  _gfbdb::initCmnBl_NewBlArtsNBA_01(*unknown58);
  _gfbdb::initCmnBl_NewBlArtsNBA_02(*unknown58);
  _gfbdb::initCmnBl_NewBlArtsNBA_03(*unknown58);
  _gfbdb::initCmnBl_NewBlArtsNBA_04(*unknown58);
  _gfbdb::initCmnBl_NewBlArtsNBA_05(*unknown58);
  _gfbdb::initCmnBl_NewBlArtsNBA_06(*unknown58);
  _gfbdb::initCmnBl_NewBlArtsNBA_07(*unknown58);
  _gfbdb::initCmnBl_NewBlArtsNBA_08(*unknown58);
  _gfbdb::initCmnBl_StatusTypeWpnType(*unknown60);
  _gfbdb::initCmnBl_StatusTypeStatus01(*unknown60);
  _gfbdb::initCmnBl_StatusTypeStatus02(*unknown60);
  _gfbdb::initCmnBl_StatusTypeStatus03(*unknown60);
  _gfbdb::initCmnBl_StatusTypeStatus04(*unknown60);
  _gfbdb::initCmnBl_StatusTypeStatus05(*unknown60);
  _gfbdb::initCmnBl_StatusTypeStatus06(*unknown60);
  _gfbdb::initCmnBl_ArmorWpnType(*unknown68);
  _gfbdb::initCmnBl_ArmorPArmorCon(*unknown68);
  _gfbdb::initCmnBl_ArmorPArmorRand(*unknown68);
  _gfbdb::initCmnBl_ArmorEArmorCon(*unknown68);
  _gfbdb::initCmnBl_ArmorEArmorRand(*unknown68);
  _gfbdb::initFLD_IdeaTableTrustPoint(*unknown70);
  _gfbdb::initFLD_IdeaTableWpnRatio(*unknown70);
  _gfbdb::initFLD_IdeaTableNArtsProbRev(*unknown70);
  _gfbdb::initFLD_IdeaTableBladeChangeRev(*unknown70);
  _gfbdb::initFLD_IdeaTableBladeArtsRev(*unknown70);
  _gfbdb::initBLD_IdeaNeedPoint(*unknown78);
  _gfbdb::initBLD_IdeaProbRev(*unknown78);
  _gfbdb::initBLD_IdeaAtrDamRev(*unknown78);
  _gfbdb::initBLD_RareListBlade(*unknown80);
  _gfbdb::initBLD_RareListCondition(*unknown80);
  _gfbdb::initBLD_RareListProb1(*unknown80);
  _gfbdb::initBLD_RareListAssure1(*unknown80);
  _gfbdb::initBLD_RareListProb2(*unknown80);
  _gfbdb::initBLD_RareListAssure2(*unknown80);
  _gfbdb::initBLD_RareListProb3(*unknown80);
  _gfbdb::initBLD_RareListAssure3(*unknown80);
  _gfbdb::initBLD_RareListProb4(*unknown80);
  _gfbdb::initBLD_RareListAssure4(*unknown80);
  _gfbdb::initBLD_RareListProb5(*unknown80);
  _gfbdb::initBLD_RareListAssure5(*unknown80);
  _gfbdb::initBLD_ReleaceRewardReleace001(*unknown88);
  _gfbdb::initBLD_ReleaceRewardReleace002(*unknown88);
  _gfbdb::initBLD_ReleaceRewardReleace003(*unknown88);
  _gfbdb::initBLD_ReleaceRewardReleace004(*unknown88);
  _gfbdb::initBLD_ReleaceRewardReleace005(*unknown88);
  _gfbdb::initBLD_ReleaceRewardReleace006(*unknown88);
  _gfbdb::initBLD_ReleaceRewardReleace007(*unknown88);
}

u32 GfBdatBlade::getIdeaTableStart() const { return Bdat::getIdTop(unknown10->data); }

u32 GfBdatBlade::getIdeaTableEnd() const { return Bdat::getIdTop(unknown10->data) + Bdat::getIdCount(unknown10->data); }

u32 GfBdatBlade::getIdeaTableItem(u32 id) const { return _gfbdb::getIdeaTableItem(*unknown10, id); }

u32 GfBdatBlade::getIdeaTableIdeaBlue(u32 id) const { return _gfbdb::getIdeaTableIdeaBlue(*unknown10, id); }

u32 GfBdatBlade::getIdeaTableIdeaRed(u32 id) const { return _gfbdb::getIdeaTableIdeaRed(*unknown10, id); }

u32 GfBdatBlade::getIdeaTableIdeaWhite(u32 id) const { return _gfbdb::getIdeaTableIdeaWhite(*unknown10, id); }

u32 GfBdatBlade::getIdeaTableIdeaBlack(u32 id) const { return _gfbdb::getIdeaTableIdeaBlack(*unknown10, id); }

u32 GfBdatBlade::getIdeaTableCondition(u32 id) const { return _gfbdb::getIdeaTableCondition(*unknown10, id); }

u32 GfBdatBlade::getIdeaTableBladeTable(u32 id) const { return _gfbdb::getIdeaTableBladeTable(*unknown10, id); }

u32 GfBdatBlade::getBladeTableStart() const { return Bdat::getIdTop(unknown18->data); }

u32 GfBdatBlade::getBladeTableEnd() const { return Bdat::getIdTop(unknown18->data) + Bdat::getIdCount(unknown18->data); }

u32 GfBdatBlade::getBladeTableCharaID1(u32 id) const { return _gfbdb::getBladeTableCharaID1(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharID1Percent(u32 id) const { return _gfbdb::getBladeTableCharID1Percent(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharaID2(u32 id) const { return _gfbdb::getBladeTableCharaID2(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharID2Percent(u32 id) const { return _gfbdb::getBladeTableCharID2Percent(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharaID3(u32 id) const { return _gfbdb::getBladeTableCharaID3(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharID3Percent(u32 id) const { return _gfbdb::getBladeTableCharID3Percent(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharaID4(u32 id) const { return _gfbdb::getBladeTableCharaID4(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharID4Percent(u32 id) const { return _gfbdb::getBladeTableCharID4Percent(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharaID5(u32 id) const { return _gfbdb::getBladeTableCharaID5(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharID5Percent(u32 id) const { return _gfbdb::getBladeTableCharID5Percent(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharaID6(u32 id) const { return _gfbdb::getBladeTableCharaID6(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharID6Percent(u32 id) const { return _gfbdb::getBladeTableCharID6Percent(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharaID7(u32 id) const { return _gfbdb::getBladeTableCharaID7(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharID7Percent(u32 id) const { return _gfbdb::getBladeTableCharID7Percent(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharaID8(u32 id) const { return _gfbdb::getBladeTableCharaID8(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharID8Percent(u32 id) const { return _gfbdb::getBladeTableCharID8Percent(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharaID9(u32 id) const { return _gfbdb::getBladeTableCharaID9(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharID9Percent(u32 id) const { return _gfbdb::getBladeTableCharID9Percent(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharaID10(u32 id) const { return _gfbdb::getBladeTableCharaID10(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharID10Percent(u32 id) const { return _gfbdb::getBladeTableCharID10Percent(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharaID11(u32 id) const { return _gfbdb::getBladeTableCharaID11(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharID11Percent(u32 id) const { return _gfbdb::getBladeTableCharID11Percent(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharaID12(u32 id) const { return _gfbdb::getBladeTableCharaID12(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharID12Percent(u32 id) const { return _gfbdb::getBladeTableCharID12Percent(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharaID13(u32 id) const { return _gfbdb::getBladeTableCharaID13(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharID13Percent(u32 id) const { return _gfbdb::getBladeTableCharID13Percent(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharaID14(u32 id) const { return _gfbdb::getBladeTableCharaID14(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharID14Percent(u32 id) const { return _gfbdb::getBladeTableCharID14Percent(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharaID15(u32 id) const { return _gfbdb::getBladeTableCharaID15(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharID15Percent(u32 id) const { return _gfbdb::getBladeTableCharID15Percent(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharaID16(u32 id) const { return _gfbdb::getBladeTableCharaID16(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharID16Percent(u32 id) const { return _gfbdb::getBladeTableCharID16Percent(*unknown18, id); }

u32 GfBdatBlade::getBladeTableCharaID(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getBladeTableCharaID1,
                                                              _gfbdb::getBladeTableCharaID2,
                                                              _gfbdb::getBladeTableCharaID3,
                                                              _gfbdb::getBladeTableCharaID4,
                                                              _gfbdb::getBladeTableCharaID5,
                                                              _gfbdb::getBladeTableCharaID6,
                                                              _gfbdb::getBladeTableCharaID7,
                                                              _gfbdb::getBladeTableCharaID8,
                                                              _gfbdb::getBladeTableCharaID9,
                                                              _gfbdb::getBladeTableCharaID10,
                                                              _gfbdb::getBladeTableCharaID11,
                                                              _gfbdb::getBladeTableCharaID12,
                                                              _gfbdb::getBladeTableCharaID13,
                                                              _gfbdb::getBladeTableCharaID14,
                                                              _gfbdb::getBladeTableCharaID15,
                                                              _gfbdb::getBladeTableCharaID16};
  return getters[index](*unknown18, id);
}

u32 GfBdatBlade::getBladeTableCharaIDPercent(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getBladeTableCharID1Percent,
                                                              _gfbdb::getBladeTableCharID2Percent,
                                                              _gfbdb::getBladeTableCharID3Percent,
                                                              _gfbdb::getBladeTableCharID4Percent,
                                                              _gfbdb::getBladeTableCharID5Percent,
                                                              _gfbdb::getBladeTableCharID6Percent,
                                                              _gfbdb::getBladeTableCharID7Percent,
                                                              _gfbdb::getBladeTableCharID8Percent,
                                                              _gfbdb::getBladeTableCharID9Percent,
                                                              _gfbdb::getBladeTableCharID10Percent,
                                                              _gfbdb::getBladeTableCharID11Percent,
                                                              _gfbdb::getBladeTableCharID12Percent,
                                                              _gfbdb::getBladeTableCharID13Percent,
                                                              _gfbdb::getBladeTableCharID15Percent,
                                                              _gfbdb::getBladeTableCharID15Percent,
                                                              _gfbdb::getBladeTableCharID16Percent};
  return getters[index](*unknown18, id);
}

u32 GfBdatBlade::getBladeListStart() const { return Bdat::getIdTop(unknown20->data); }

u32 GfBdatBlade::getBladeListEnd() const { return Bdat::getIdTop(unknown20->data) + Bdat::getIdCount(unknown20->data); }

u32 GfBdatBlade::getBladeListCategory(u32 id) const { return _gfbdb::getBladeListCategory(*unknown20, id); }

u32 GfBdatBlade::getBladeListStatusID(u32 id) const { return _gfbdb::getBladeListStatusID(*unknown20, id); }

u32 GfBdatBlade::getCommonListStart() const { return Bdat::getIdTop(unknown28->data); }

u32 GfBdatBlade::getCommonListEnd() const { return Bdat::getIdTop(unknown28->data) + Bdat::getIdCount(unknown28->data); }

u32 GfBdatBlade::getCommonListQuestRace(u32 id) const { return _gfbdb::getCommonListQuestRace(*unknown28, id); }

u32 GfBdatBlade::getCommonListGender(u32 id) const { return _gfbdb::getCommonListGender(*unknown28, id); }

u32 GfBdatBlade::getCommonListWeapon(u32 id) const { return _gfbdb::getCommonListWeapon(*unknown28, id); }

u32 GfBdatBlade::getCommonListAtr(u32 id) const { return _gfbdb::getCommonListAtr(*unknown28, id); }

u32 GfBdatBlade::getCommonListModelTable(u32 id) const { return _gfbdb::getCommonListModelTable(*unknown28, id); }

u32 GfBdatBlade::getCommonListIdeaType(u32 id) const { return _gfbdb::getCommonListIdeaType(*unknown28, id); }

u32 GfBdatBlade::getCommonListIdeaMin(u32 id) const { return _gfbdb::getCommonListIdeaMin(*unknown28, id); }

u32 GfBdatBlade::getCommonListIdeaMax(u32 id) const { return _gfbdb::getCommonListIdeaMax(*unknown28, id); }

u32 GfBdatBlade::getCommonListRatio(u32 id) const { return _gfbdb::getCommonListRatio(*unknown28, id); }

u32 GfBdatBlade::getCommonListRarityMin(u32 id) const { return _gfbdb::getCommonListRarityMin(*unknown28, id); }

u32 GfBdatBlade::getCommonListRarityMax(u32 id) const { return _gfbdb::getCommonListRarityMax(*unknown28, id); }

u32 GfBdatBlade::getCommonListFskill(u32 id) const { return _gfbdb::getCommonListFskill(*unknown28, id); }

u32 GfBdatBlade::getCommonListArtsAchievementSet1(u32 id) const { return _gfbdb::getCommonListArtsAchievementSet1(*unknown28, id); }

u32 GfBdatBlade::getCommonListArtsAchievementSet2(u32 id) const { return _gfbdb::getCommonListArtsAchievementSet2(*unknown28, id); }

u32 GfBdatBlade::getCommonListArtsAchievementSet3(u32 id) const { return _gfbdb::getCommonListArtsAchievementSet3(*unknown28, id); }

u32 GfBdatBlade::getCommonListSkillAchievementSet1(u32 id) const { return _gfbdb::getCommonListSkillAchievementSet1(*unknown28, id); }

u32 GfBdatBlade::getCommonListSkillAchievementSet2(u32 id) const { return _gfbdb::getCommonListSkillAchievementSet2(*unknown28, id); }

u32 GfBdatBlade::getCommonListSkillAchievementSet3(u32 id) const { return _gfbdb::getCommonListSkillAchievementSet3(*unknown28, id); }

u32 GfBdatBlade::getCommonListFskillAchivementSet1(u32 id) const { return _gfbdb::getCommonListFskillAchivementSet1(*unknown28, id); }

u32 GfBdatBlade::getCommonListFskillAchivementSet2(u32 id) const { return _gfbdb::getCommonListFskillAchivementSet2(*unknown28, id); }

u32 GfBdatBlade::getCommonListFskillAchivementSet3(u32 id) const { return _gfbdb::getCommonListFskillAchivementSet3(*unknown28, id); }

u32 GfBdatBlade::getCommonListKeyAchievementSet(u32 id) const { return _gfbdb::getCommonListKeyAchievementSet(*unknown28, id); }

u32 GfBdatBlade::getCommonListFavoriteCategoryMax(u32 id) const { return _gfbdb::getCommonListFavoriteCategoryMax(*unknown28, id); }

u32 GfBdatBlade::getCommonListFavoriteItemMax(u32 id) const { return _gfbdb::getCommonListFavoriteItemMax(*unknown28, id); }

u32 GfBdatBlade::getCommonListArtsAchievementSet(u32 id, u32 index) const { return _gfbdb::getCommonListArtsAchievementSet(*unknown28, id, index); }

u32 GfBdatBlade::getCommonListSkillAchievementSet(u32 id, u32 index) const {
  return _gfbdb::getCommonListSkillAchievementSet(*unknown28, id, index);
}

u32 GfBdatBlade::getCommonListFskillAchivementSet(u32 id, u32 index) const {
  return _gfbdb::getCommonListFskillAchivementSet(*unknown28, id, index);
}

u32 GfBdatBlade::getNameListStart() const { return Bdat::getIdTop(unknown30->data); }

u32 GfBdatBlade::getNameListEnd() const { return Bdat::getIdTop(unknown30->data) + Bdat::getIdCount(unknown30->data); }

u32 GfBdatBlade::getNameListCategory(u32 id) const { return _gfbdb::getNameListCategory(*unknown30, id); }

u32 GfBdatBlade::getNameListRace(u32 id) const { return _gfbdb::getNameListRace(*unknown30, id); }

u32 GfBdatBlade::getNameListGender(u32 id) const { return _gfbdb::getNameListGender(*unknown30, id); }

u32 GfBdatBlade::getBladeModelListStart() const { return Bdat::getIdTop(unknown38->data); }

u32 GfBdatBlade::getBladeModelListEnd() const { return Bdat::getIdTop(unknown38->data) + Bdat::getIdCount(unknown38->data); }

u32 GfBdatBlade::getBladeModelListQuestRace(u32 id) const { return _gfbdb::getBladeModelListQuestRace(*unknown38, id); }

u32 GfBdatBlade::getBladeModelListGender(u32 id) const { return _gfbdb::getBladeModelListGender(*unknown38, id); }

u32 GfBdatBlade::getBladeModelListIdeaMin(u32 id) const { return _gfbdb::getBladeModelListIdeaMin(*unknown38, id); }

u32 GfBdatBlade::getBladeModelListIdeaMax(u32 id) const { return _gfbdb::getBladeModelListIdeaMax(*unknown38, id); }

u32 GfBdatBlade::getBladeModelListModel1(u32 id) const { return _gfbdb::getBladeModelListModel1(*unknown38, id); }

u32 GfBdatBlade::getBladeModelListModel2(u32 id) const { return _gfbdb::getBladeModelListModel2(*unknown38, id); }

u32 GfBdatBlade::getBladeModelListPartsNumMin(u32 id) const { return _gfbdb::getBladeModelListPartsNumMin(*unknown38, id); }

u32 GfBdatBlade::getBladeModelListPartsNumMax(u32 id) const { return _gfbdb::getBladeModelListPartsNumMax(*unknown38, id); }

u32 GfBdatBlade::getBladeModelListParts1(u32 id) const { return _gfbdb::getBladeModelListParts1(*unknown38, id); }

u32 GfBdatBlade::getBladeModelListParts2(u32 id) const { return _gfbdb::getBladeModelListParts2(*unknown38, id); }

u32 GfBdatBlade::getBladeModelListParts3(u32 id) const { return _gfbdb::getBladeModelListParts3(*unknown38, id); }

u32 GfBdatBlade::getBladeModelListParts4(u32 id) const { return _gfbdb::getBladeModelListParts4(*unknown38, id); }

u32 GfBdatBlade::getBladeModelListModel(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getBladeModelListModel1, _gfbdb::getBladeModelListModel2};
  return getters[index](*unknown38, id);
}

u32 GfBdatBlade::getBladeModelListParts(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {
      _gfbdb::getBladeModelListParts1, _gfbdb::getBladeModelListParts2, _gfbdb::getBladeModelListParts3, _gfbdb::getBladeModelListParts4};
  return getters[index](*unknown38, id);
}

u32 GfBdatBlade::getCreateConfigStart() const { return Bdat::getIdTop(unknown40->data); }

u32 GfBdatBlade::getCreateConfigEnd() const { return Bdat::getIdTop(unknown40->data) + Bdat::getIdCount(unknown40->data); }

u32 GfBdatBlade::getCreateConfigValue(u32 id) const { return _gfbdb::getCreateConfigValue(*unknown40, id); }

u32 GfBdatBlade::getCmnBl_CapacityStart() const { return Bdat::getIdTop(unknown48->data); }

u32 GfBdatBlade::getCmnBl_CapacityEnd() const { return Bdat::getIdTop(unknown48->data) + Bdat::getIdCount(unknown48->data); }

u32 GfBdatBlade::getCmnBl_CapacityArtsNum1Prob(u32 id) const { return _gfbdb::getCmnBl_CapacityArtsNum1Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityArtsNum2Prob(u32 id) const { return _gfbdb::getCmnBl_CapacityArtsNum2Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityArtsNum3Prob(u32 id) const { return _gfbdb::getCmnBl_CapacityArtsNum3Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityArtsLv1Prob(u32 id) const { return _gfbdb::getCmnBl_CapacityArtsLv1Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityArtsLv2Prob(u32 id) const { return _gfbdb::getCmnBl_CapacityArtsLv2Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityArtsLv3Prob(u32 id) const { return _gfbdb::getCmnBl_CapacityArtsLv3Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityArtsLv4Prob(u32 id) const { return _gfbdb::getCmnBl_CapacityArtsLv4Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityArtsLv5Prob(u32 id) const { return _gfbdb::getCmnBl_CapacityArtsLv5Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityArtsRevCon(u32 id) const { return _gfbdb::getCmnBl_CapacityArtsRevCon(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityArtsRevRand(u32 id) const { return _gfbdb::getCmnBl_CapacityArtsRevRand(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacitySpArtsRevCon(u32 id) const { return _gfbdb::getCmnBl_CapacitySpArtsRevCon(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacitySpArtsRevRand(u32 id) const { return _gfbdb::getCmnBl_CapacitySpArtsRevRand(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacitySkillNum1Prob(u32 id) const { return _gfbdb::getCmnBl_CapacitySkillNum1Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacitySkillNum2Prob(u32 id) const { return _gfbdb::getCmnBl_CapacitySkillNum2Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacitySkillNum3Prob(u32 id) const { return _gfbdb::getCmnBl_CapacitySkillNum3Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacitySkillLv1Prob(u32 id) const { return _gfbdb::getCmnBl_CapacitySkillLv1Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacitySkillLv2Prob(u32 id) const { return _gfbdb::getCmnBl_CapacitySkillLv2Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacitySkillLv3Prob(u32 id) const { return _gfbdb::getCmnBl_CapacitySkillLv3Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacitySkillLv4Prob(u32 id) const { return _gfbdb::getCmnBl_CapacitySkillLv4Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacitySkillLv5Prob(u32 id) const { return _gfbdb::getCmnBl_CapacitySkillLv5Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityOrbNum0Prob(u32 id) const { return _gfbdb::getCmnBl_CapacityOrbNum0Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityOrbNum1Prob(u32 id) const { return _gfbdb::getCmnBl_CapacityOrbNum1Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityOrbNum2Prob(u32 id) const { return _gfbdb::getCmnBl_CapacityOrbNum2Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityOrbNum3Prob(u32 id) const { return _gfbdb::getCmnBl_CapacityOrbNum3Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityNartsNum1Prob(u32 id) const { return _gfbdb::getCmnBl_CapacityNartsNum1Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityNartsNum2Prob(u32 id) const { return _gfbdb::getCmnBl_CapacityNartsNum2Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityNartsNum3Prob(u32 id) const { return _gfbdb::getCmnBl_CapacityNartsNum3Prob(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityNartsRevCon(u32 id) const { return _gfbdb::getCmnBl_CapacityNartsRevCon(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityNartsRevRand(u32 id) const { return _gfbdb::getCmnBl_CapacityNartsRevRand(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityStatusRevCon(u32 id) const { return _gfbdb::getCmnBl_CapacityStatusRevCon(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityStatusRevRand(u32 id) const { return _gfbdb::getCmnBl_CapacityStatusRevRand(*unknown48, id); }

u32 GfBdatBlade::getCmnBl_CapacityArtsNumProb(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {
      _gfbdb::getCmnBl_CapacityArtsNum1Prob, _gfbdb::getCmnBl_CapacityArtsNum2Prob, _gfbdb::getCmnBl_CapacityArtsNum3Prob};
  return getters[index](*unknown48, id);
}

u32 GfBdatBlade::getCmnBl_CapacityArtsLvProb(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getCmnBl_CapacityArtsLv1Prob,
                                                              _gfbdb::getCmnBl_CapacityArtsLv2Prob,
                                                              _gfbdb::getCmnBl_CapacityArtsLv3Prob,
                                                              _gfbdb::getCmnBl_CapacityArtsLv4Prob,
                                                              _gfbdb::getCmnBl_CapacityArtsLv5Prob};
  return getters[index](*unknown48, id);
}

u32 GfBdatBlade::getCmnBl_CapacitySkillNumProb(u32 id, u32 index) const { return _gfbdb::getCmnBl_CapacitySkillNumProb(*unknown48, id, index); }

u32 GfBdatBlade::getCmnBl_CapacitySkillLvProb(u32 id, u32 index) const { return _gfbdb::getCmnBl_CapacitySkillLvProb(*unknown48, id, index); }

u32 GfBdatBlade::getCmnBl_CapacityOrbNumProb(u32 id, u32 index) const { return _gfbdb::getCmnBl_CapacityOrbNumProb(*unknown48, id, index); }

u32 GfBdatBlade::getCmnBl_CapacityNartsNumProb(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {
      _gfbdb::getCmnBl_CapacityNartsNum1Prob, _gfbdb::getCmnBl_CapacityNartsNum2Prob, _gfbdb::getCmnBl_CapacityNartsNum3Prob};
  return getters[index](*unknown48, id);
}

u32 GfBdatBlade::getCmnBl_PowerStart() const { return Bdat::getIdTop(unknown50->data); }

u32 GfBdatBlade::getCmnBl_PowerEnd() const { return Bdat::getIdTop(unknown50->data) + Bdat::getIdCount(unknown50->data); }

u32 GfBdatBlade::getCmnBl_PowerMinLv(u32 id) const { return _gfbdb::getCmnBl_PowerMinLv(*unknown50, id); }

u32 GfBdatBlade::getCmnBl_PowerMaxLv(u32 id) const { return _gfbdb::getCmnBl_PowerMaxLv(*unknown50, id); }

u32 GfBdatBlade::getCmnBl_PowerPow01(u32 id) const { return _gfbdb::getCmnBl_PowerPow01(*unknown50, id); }

u32 GfBdatBlade::getCmnBl_PowerPow02(u32 id) const { return _gfbdb::getCmnBl_PowerPow02(*unknown50, id); }

u32 GfBdatBlade::getCmnBl_PowerPow03(u32 id) const { return _gfbdb::getCmnBl_PowerPow03(*unknown50, id); }

u32 GfBdatBlade::getCmnBl_PowerPow04(u32 id) const { return _gfbdb::getCmnBl_PowerPow04(*unknown50, id); }

u32 GfBdatBlade::getCmnBl_PowerPow05(u32 id) const { return _gfbdb::getCmnBl_PowerPow05(*unknown50, id); }

u32 GfBdatBlade::getCmnBl_PowerPow06(u32 id) const { return _gfbdb::getCmnBl_PowerPow06(*unknown50, id); }

u32 GfBdatBlade::getCmnBl_PowerPow07(u32 id) const { return _gfbdb::getCmnBl_PowerPow07(*unknown50, id); }

u32 GfBdatBlade::getCmnBl_PowerPow08(u32 id) const { return _gfbdb::getCmnBl_PowerPow08(*unknown50, id); }

u32 GfBdatBlade::getCmnBl_PowerPow09(u32 id) const { return _gfbdb::getCmnBl_PowerPow09(*unknown50, id); }

u32 GfBdatBlade::getCmnBl_PowerPow10(u32 id) const { return _gfbdb::getCmnBl_PowerPow10(*unknown50, id); }

u32 GfBdatBlade::getCmnBl_PowerPow(u32 id, u32 index) const { return _gfbdb::getCmnBl_PowerPow(*unknown50, id, index); }

u32 GfBdatBlade::getCmnBl_NewBlArtsStart() const { return Bdat::getIdTop(unknown58->data); }

u32 GfBdatBlade::getCmnBl_NewBlArtsEnd() const { return Bdat::getIdTop(unknown58->data) + Bdat::getIdCount(unknown58->data); }

u32 GfBdatBlade::getCmnBl_NewBlArtsWpnType(u32 id) const { return _gfbdb::getCmnBl_NewBlArtsWpnType(*unknown58, id); }

u32 GfBdatBlade::getCmnBl_NewBlArtsNBA_01(u32 id) const { return _gfbdb::getCmnBl_NewBlArtsNBA_01(*unknown58, id); }

u32 GfBdatBlade::getCmnBl_NewBlArtsNBA_02(u32 id) const { return _gfbdb::getCmnBl_NewBlArtsNBA_02(*unknown58, id); }

u32 GfBdatBlade::getCmnBl_NewBlArtsNBA_03(u32 id) const { return _gfbdb::getCmnBl_NewBlArtsNBA_03(*unknown58, id); }

u32 GfBdatBlade::getCmnBl_NewBlArtsNBA_04(u32 id) const { return _gfbdb::getCmnBl_NewBlArtsNBA_04(*unknown58, id); }

u32 GfBdatBlade::getCmnBl_NewBlArtsNBA_05(u32 id) const { return _gfbdb::getCmnBl_NewBlArtsNBA_05(*unknown58, id); }

u32 GfBdatBlade::getCmnBl_NewBlArtsNBA_06(u32 id) const { return _gfbdb::getCmnBl_NewBlArtsNBA_06(*unknown58, id); }

u32 GfBdatBlade::getCmnBl_NewBlArtsNBA_07(u32 id) const { return _gfbdb::getCmnBl_NewBlArtsNBA_07(*unknown58, id); }

u32 GfBdatBlade::getCmnBl_NewBlArtsNBA_08(u32 id) const { return _gfbdb::getCmnBl_NewBlArtsNBA_08(*unknown58, id); }

u32 GfBdatBlade::getCmnBl_NewBlArtsNBA(u32 id, u32 index) const { return _gfbdb::getCmnBl_NewBlArtsNBA(*unknown58, id, index); }

u32 GfBdatBlade::getCmnBl_StatusTypeStart() const { return Bdat::getIdTop(unknown60->data); }

u32 GfBdatBlade::getCmnBl_StatusTypeEnd() const { return Bdat::getIdTop(unknown60->data) + Bdat::getIdCount(unknown60->data); }

u32 GfBdatBlade::getCmnBl_StatusTypeWpnType(u32 id) const { return _gfbdb::getCmnBl_StatusTypeWpnType(*unknown60, id); }

u32 GfBdatBlade::getCmnBl_StatusTypeStatus01(u32 id) const { return _gfbdb::getCmnBl_StatusTypeStatus01(*unknown60, id); }

u32 GfBdatBlade::getCmnBl_StatusTypeStatus02(u32 id) const { return _gfbdb::getCmnBl_StatusTypeStatus02(*unknown60, id); }

u32 GfBdatBlade::getCmnBl_StatusTypeStatus03(u32 id) const { return _gfbdb::getCmnBl_StatusTypeStatus03(*unknown60, id); }

u32 GfBdatBlade::getCmnBl_StatusTypeStatus04(u32 id) const { return _gfbdb::getCmnBl_StatusTypeStatus04(*unknown60, id); }

u32 GfBdatBlade::getCmnBl_StatusTypeStatus05(u32 id) const { return _gfbdb::getCmnBl_StatusTypeStatus05(*unknown60, id); }

u32 GfBdatBlade::getCmnBl_StatusTypeStatus06(u32 id) const { return _gfbdb::getCmnBl_StatusTypeStatus06(*unknown60, id); }

u32 GfBdatBlade::getCmnBl_StatusTypeStatus(u32 id, u32 index) const { return _gfbdb::getCmnBl_StatusTypeStatus(*unknown60, id, index); }

u32 GfBdatBlade::getCmnBl_ArmorStart() const { return Bdat::getIdTop(unknown68->data); }

u32 GfBdatBlade::getCmnBl_ArmorEnd() const { return Bdat::getIdTop(unknown68->data) + Bdat::getIdCount(unknown68->data); }

u32 GfBdatBlade::getCmnBl_ArmorWpnType(u32 id) const { return _gfbdb::getCmnBl_ArmorWpnType(*unknown68, id); }

u32 GfBdatBlade::getCmnBl_ArmorPArmorCon(u32 id) const { return _gfbdb::getCmnBl_ArmorPArmorCon(*unknown68, id); }

u32 GfBdatBlade::getCmnBl_ArmorPArmorRand(u32 id) const { return _gfbdb::getCmnBl_ArmorPArmorRand(*unknown68, id); }

u32 GfBdatBlade::getCmnBl_ArmorEArmorCon(u32 id) const { return _gfbdb::getCmnBl_ArmorEArmorCon(*unknown68, id); }

u32 GfBdatBlade::getCmnBl_ArmorEArmorRand(u32 id) const { return _gfbdb::getCmnBl_ArmorEArmorRand(*unknown68, id); }

u32 GfBdatBlade::getFLD_IdeaTableStart() const { return Bdat::getIdTop(unknown70->data); }

u32 GfBdatBlade::getFLD_IdeaTableEnd() const { return Bdat::getIdTop(unknown70->data) + Bdat::getIdCount(unknown70->data); }

u32 GfBdatBlade::getFLD_IdeaTableTrustPoint(u32 id) const { return _gfbdb::getFLD_IdeaTableTrustPoint(*unknown70, id); }

u32 GfBdatBlade::getFLD_IdeaTableWpnRatio(u32 id) const { return _gfbdb::getFLD_IdeaTableWpnRatio(*unknown70, id); }

u32 GfBdatBlade::getFLD_IdeaTableNArtsProbRev(u32 id) const { return _gfbdb::getFLD_IdeaTableNArtsProbRev(*unknown70, id); }

s32 GfBdatBlade::getFLD_IdeaTableBladeChangeRev(u32 id) const { return _gfbdb::getFLD_IdeaTableBladeChangeRev(*unknown70, id); }

s32 GfBdatBlade::getFLD_IdeaTableBladeArtsRev(u32 id) const { return _gfbdb::getFLD_IdeaTableBladeArtsRev(*unknown70, id); }

u32 GfBdatBlade::getBLD_IdeaStart() const { return Bdat::getIdTop(unknown78->data); }

u32 GfBdatBlade::getBLD_IdeaEnd() const { return Bdat::getIdTop(unknown78->data) + Bdat::getIdCount(unknown78->data); }

u32 GfBdatBlade::getBLD_IdeaNeedPoint(u32 id) const { return _gfbdb::getBLD_IdeaNeedPoint(*unknown78, id); }

u32 GfBdatBlade::getBLD_IdeaProbRev(u32 id) const { return _gfbdb::getBLD_IdeaProbRev(*unknown78, id); }

u32 GfBdatBlade::getBLD_IdeaAtrDamRev(u32 id) const { return _gfbdb::getBLD_IdeaAtrDamRev(*unknown78, id); }

u32 GfBdatBlade::getBLD_RareListStart() const { return Bdat::getIdTop(unknown80->data); }

u32 GfBdatBlade::getBLD_RareListEnd() const { return Bdat::getIdTop(unknown80->data) + Bdat::getIdCount(unknown80->data); }

u32 GfBdatBlade::getBLD_RareListBlade(u32 id) const { return _gfbdb::getBLD_RareListBlade(*unknown80, id); }

u32 GfBdatBlade::getBLD_RareListCondition(u32 id) const { return _gfbdb::getBLD_RareListCondition(*unknown80, id); }

f32 GfBdatBlade::getBLD_RareListProb1(u32 id) const { return _gfbdb::getBLD_RareListProb1(*unknown80, id); }

u32 GfBdatBlade::getBLD_RareListAssure1(u32 id) const { return _gfbdb::getBLD_RareListAssure1(*unknown80, id); }

f32 GfBdatBlade::getBLD_RareListProb2(u32 id) const { return _gfbdb::getBLD_RareListProb2(*unknown80, id); }

u32 GfBdatBlade::getBLD_RareListAssure2(u32 id) const { return _gfbdb::getBLD_RareListAssure2(*unknown80, id); }

f32 GfBdatBlade::getBLD_RareListProb3(u32 id) const { return _gfbdb::getBLD_RareListProb3(*unknown80, id); }

u32 GfBdatBlade::getBLD_RareListAssure3(u32 id) const { return _gfbdb::getBLD_RareListAssure3(*unknown80, id); }

f32 GfBdatBlade::getBLD_RareListProb4(u32 id) const { return _gfbdb::getBLD_RareListProb4(*unknown80, id); }

u32 GfBdatBlade::getBLD_RareListAssure4(u32 id) const { return _gfbdb::getBLD_RareListAssure4(*unknown80, id); }

f32 GfBdatBlade::getBLD_RareListProb5(u32 id) const { return _gfbdb::getBLD_RareListProb5(*unknown80, id); }

u32 GfBdatBlade::getBLD_RareListAssure5(u32 id) const { return _gfbdb::getBLD_RareListAssure5(*unknown80, id); }

f32 GfBdatBlade::getBLD_RareListProb(u32 id, u32 index) const { return _gfbdb::getBLD_RareListProb(*unknown80, id, index); }

u32 GfBdatBlade::getBLD_RareListAssure(u32 id, u32 index) const { return _gfbdb::getBLD_RareListAssure(*unknown80, id, index); }

u32 GfBdatBlade::getBLD_ReleaceRewardStart() const { return Bdat::getIdTop(unknown88->data); }

u32 GfBdatBlade::getBLD_ReleaceRewardEnd() const { return Bdat::getIdTop(unknown88->data) + Bdat::getIdCount(unknown88->data); }

u32 GfBdatBlade::getBLD_ReleaceRewardReleace001(u32 id) const { return _gfbdb::getBLD_ReleaceRewardReleace001(*unknown88, id); }

u32 GfBdatBlade::getBLD_ReleaceRewardReleace002(u32 id) const { return _gfbdb::getBLD_ReleaceRewardReleace002(*unknown88, id); }

u32 GfBdatBlade::getBLD_ReleaceRewardReleace003(u32 id) const { return _gfbdb::getBLD_ReleaceRewardReleace003(*unknown88, id); }

u32 GfBdatBlade::getBLD_ReleaceRewardReleace004(u32 id) const { return _gfbdb::getBLD_ReleaceRewardReleace004(*unknown88, id); }

u32 GfBdatBlade::getBLD_ReleaceRewardReleace005(u32 id) const { return _gfbdb::getBLD_ReleaceRewardReleace005(*unknown88, id); }

u32 GfBdatBlade::getBLD_ReleaceRewardReleace006(u32 id) const { return _gfbdb::getBLD_ReleaceRewardReleace006(*unknown88, id); }

u32 GfBdatBlade::getBLD_ReleaceRewardReleace007(u32 id) const { return _gfbdb::getBLD_ReleaceRewardReleace007(*unknown88, id); }

u32 GfBdatBlade::getBLD_ReleaceRewardReleace(u32 id, u32 index) const { return _gfbdb::getBLD_ReleaceRewardReleace(*unknown88, id, index); }

} // namespace gf
