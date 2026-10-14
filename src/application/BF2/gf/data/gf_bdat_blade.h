#pragma once
#include "gf/data/gf_bdat_wrapper.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatBlade : public mm::mtl::PtrSingleton<GfBdatBlade>, public GfBdatRefresh {
public:
  u32 getIdeaTableStart() const;
  u32 getIdeaTableItem(u32 id) const;
  u32 getIdeaTableIdeaBlue(u32 id) const;
  u32 getIdeaTableIdeaRed(u32 id) const;
  u32 getIdeaTableIdeaWhite(u32 id) const;
  u32 getIdeaTableIdeaBlack(u32 id) const;
  u32 getIdeaTableCondition(u32 id) const;
  u32 getIdeaTableBladeTable(u32 id) const;
  u32 getBladeTableStart() const;
  u32 getBladeTableCharaID1(u32 id) const;
  u32 getBladeTableCharID1Percent(u32 id) const;
  u32 getBladeTableCharaID2(u32 id) const;
  u32 getBladeTableCharID2Percent(u32 id) const;
  u32 getBladeTableCharaID3(u32 id) const;
  u32 getBladeTableCharID3Percent(u32 id) const;
  u32 getBladeTableCharaID4(u32 id) const;
  u32 getBladeTableCharID4Percent(u32 id) const;
  u32 getBladeTableCharaID5(u32 id) const;
  u32 getBladeTableCharID5Percent(u32 id) const;
  u32 getBladeTableCharaID6(u32 id) const;
  u32 getBladeTableCharID6Percent(u32 id) const;
  u32 getBladeTableCharaID7(u32 id) const;
  u32 getBladeTableCharID7Percent(u32 id) const;
  u32 getBladeTableCharaID8(u32 id) const;
  u32 getBladeTableCharID8Percent(u32 id) const;
  u32 getBladeTableCharaID9(u32 id) const;
  u32 getBladeTableCharID9Percent(u32 id) const;
  u32 getBladeTableCharaID10(u32 id) const;
  u32 getBladeTableCharID10Percent(u32 id) const;
  u32 getBladeTableCharaID11(u32 id) const;
  u32 getBladeTableCharID11Percent(u32 id) const;
  u32 getBladeTableCharaID12(u32 id) const;
  u32 getBladeTableCharID12Percent(u32 id) const;
  u32 getBladeTableCharaID13(u32 id) const;
  u32 getBladeTableCharID13Percent(u32 id) const;
  u32 getBladeTableCharaID14(u32 id) const;
  u32 getBladeTableCharID14Percent(u32 id) const;
  u32 getBladeTableCharaID15(u32 id) const;
  u32 getBladeTableCharID15Percent(u32 id) const;
  u32 getBladeTableCharaID16(u32 id) const;
  u32 getBladeTableCharID16Percent(u32 id) const;
  u32 getBladeListStart() const;
  u32 getBladeListCategory(u32 id) const;
  u32 getBladeListStatusID(u32 id) const;
  u32 getCommonListStart() const;
  u32 getCommonListQuestRace(u32 id) const;
  u32 getCommonListGender(u32 id) const;
  u32 getCommonListWeapon(u32 id) const;
  u32 getCommonListAtr(u32 id) const;
  u32 getCommonListModelTable(u32 id) const;
  u32 getCommonListIdeaType(u32 id) const;
  u32 getCommonListIdeaMin(u32 id) const;
  u32 getCommonListIdeaMax(u32 id) const;
  u32 getCommonListRatio(u32 id) const;
  u32 getCommonListRarityMin(u32 id) const;
  u32 getCommonListRarityMax(u32 id) const;
  u32 getCommonListFskill(u32 id) const;
  u32 getCommonListArtsAchievementSet1(u32 id) const;
  u32 getCommonListArtsAchievementSet2(u32 id) const;
  u32 getCommonListArtsAchievementSet3(u32 id) const;
  u32 getCommonListSkillAchievementSet1(u32 id) const;
  u32 getCommonListSkillAchievementSet2(u32 id) const;
  u32 getCommonListSkillAchievementSet3(u32 id) const;
  u32 getCommonListFskillAchivementSet1(u32 id) const;
  u32 getCommonListFskillAchivementSet2(u32 id) const;
  u32 getCommonListFskillAchivementSet3(u32 id) const;
  u32 getCommonListKeyAchievementSet(u32 id) const;
  u32 getCommonListFavoriteCategoryMax(u32 id) const;
  u32 getCommonListFavoriteItemMax(u32 id) const;
  u32 getNameListStart() const;
  u32 getNameListCategory(u32 id) const;
  u32 getNameListRace(u32 id) const;
  u32 getNameListGender(u32 id) const;
  u32 getBladeModelListStart() const;
  u32 getBladeModelListQuestRace(u32 id) const;
  u32 getBladeModelListGender(u32 id) const;
  u32 getBladeModelListIdeaMin(u32 id) const;
  u32 getBladeModelListIdeaMax(u32 id) const;
  u32 getBladeModelListModel1(u32 id) const;
  u32 getBladeModelListModel2(u32 id) const;
  u32 getBladeModelListPartsNumMin(u32 id) const;
  u32 getBladeModelListPartsNumMax(u32 id) const;
  u32 getBladeModelListParts1(u32 id) const;
  u32 getBladeModelListParts2(u32 id) const;
  u32 getBladeModelListParts3(u32 id) const;
  u32 getBladeModelListParts4(u32 id) const;
  u32 getCreateConfigStart() const;
  u32 getCreateConfigValue(u32 id) const;
  u32 getCmnBl_CapacityStart() const;
  u32 getCmnBl_CapacityArtsNum1Prob(u32 id) const;
  u32 getCmnBl_CapacityArtsNum2Prob(u32 id) const;
  u32 getCmnBl_CapacityArtsNum3Prob(u32 id) const;
  u32 getCmnBl_CapacityArtsLv1Prob(u32 id) const;
  u32 getCmnBl_CapacityArtsLv2Prob(u32 id) const;
  u32 getCmnBl_CapacityArtsLv3Prob(u32 id) const;
  u32 getCmnBl_CapacityArtsLv4Prob(u32 id) const;
  u32 getCmnBl_CapacityArtsLv5Prob(u32 id) const;
  u32 getCmnBl_CapacityArtsRevCon(u32 id) const;
  u32 getCmnBl_CapacityArtsRevRand(u32 id) const;
  u32 getCmnBl_CapacitySpArtsRevCon(u32 id) const;
  u32 getCmnBl_CapacitySpArtsRevRand(u32 id) const;
  u32 getCmnBl_CapacitySkillNum1Prob(u32 id) const;
  u32 getCmnBl_CapacitySkillNum2Prob(u32 id) const;
  u32 getCmnBl_CapacitySkillNum3Prob(u32 id) const;
  u32 getCmnBl_CapacitySkillLv1Prob(u32 id) const;
  u32 getCmnBl_CapacitySkillLv2Prob(u32 id) const;
  u32 getCmnBl_CapacitySkillLv3Prob(u32 id) const;
  u32 getCmnBl_CapacitySkillLv4Prob(u32 id) const;
  u32 getCmnBl_CapacitySkillLv5Prob(u32 id) const;
  u32 getCmnBl_CapacityOrbNum0Prob(u32 id) const;
  u32 getCmnBl_CapacityOrbNum1Prob(u32 id) const;
  u32 getCmnBl_CapacityOrbNum2Prob(u32 id) const;
  u32 getCmnBl_CapacityOrbNum3Prob(u32 id) const;
  u32 getCmnBl_CapacityNartsNum1Prob(u32 id) const;
  u32 getCmnBl_CapacityNartsNum2Prob(u32 id) const;
  u32 getCmnBl_CapacityNartsNum3Prob(u32 id) const;
  u32 getCmnBl_CapacityNartsRevCon(u32 id) const;
  u32 getCmnBl_CapacityNartsRevRand(u32 id) const;
  u32 getCmnBl_CapacityStatusRevCon(u32 id) const;
  u32 getCmnBl_CapacityStatusRevRand(u32 id) const;
  u32 getCmnBl_PowerStart() const;
  u32 getCmnBl_PowerMinLv(u32 id) const;
  u32 getCmnBl_PowerMaxLv(u32 id) const;
  u32 getCmnBl_PowerPow01(u32 id) const;
  u32 getCmnBl_PowerPow02(u32 id) const;
  u32 getCmnBl_PowerPow03(u32 id) const;
  u32 getCmnBl_PowerPow04(u32 id) const;
  u32 getCmnBl_PowerPow05(u32 id) const;
  u32 getCmnBl_PowerPow06(u32 id) const;
  u32 getCmnBl_PowerPow07(u32 id) const;
  u32 getCmnBl_PowerPow08(u32 id) const;
  u32 getCmnBl_PowerPow09(u32 id) const;
  u32 getCmnBl_PowerPow10(u32 id) const;
  u32 getCmnBl_NewBlArtsStart() const;
  u32 getCmnBl_NewBlArtsWpnType(u32 id) const;
  u32 getCmnBl_NewBlArtsNBA_01(u32 id) const;
  u32 getCmnBl_NewBlArtsNBA_02(u32 id) const;
  u32 getCmnBl_NewBlArtsNBA_03(u32 id) const;
  u32 getCmnBl_NewBlArtsNBA_04(u32 id) const;
  u32 getCmnBl_NewBlArtsNBA_05(u32 id) const;
  u32 getCmnBl_NewBlArtsNBA_06(u32 id) const;
  u32 getCmnBl_NewBlArtsNBA_07(u32 id) const;
  u32 getCmnBl_NewBlArtsNBA_08(u32 id) const;
  u32 getCmnBl_StatusTypeStart() const;
  u32 getCmnBl_StatusTypeWpnType(u32 id) const;
  u32 getCmnBl_StatusTypeStatus01(u32 id) const;
  u32 getCmnBl_StatusTypeStatus02(u32 id) const;
  u32 getCmnBl_StatusTypeStatus03(u32 id) const;
  u32 getCmnBl_StatusTypeStatus04(u32 id) const;
  u32 getCmnBl_StatusTypeStatus05(u32 id) const;
  u32 getCmnBl_StatusTypeStatus06(u32 id) const;
  u32 getCmnBl_ArmorStart() const;
  u32 getCmnBl_ArmorWpnType(u32 id) const;
  u32 getCmnBl_ArmorPArmorCon(u32 id) const;
  u32 getCmnBl_ArmorPArmorRand(u32 id) const;
  u32 getCmnBl_ArmorEArmorCon(u32 id) const;
  u32 getCmnBl_ArmorEArmorRand(u32 id) const;
  u32 getFLD_IdeaTableStart() const;
  u32 getFLD_IdeaTableTrustPoint(u32 id) const;
  u32 getFLD_IdeaTableWpnRatio(u32 id) const;
  u32 getFLD_IdeaTableNArtsProbRev(u32 id) const;
  s32 getFLD_IdeaTableBladeChangeRev(u32 id) const;
  s32 getFLD_IdeaTableBladeArtsRev(u32 id) const;
  u32 getBLD_IdeaStart() const;
  u32 getBLD_IdeaNeedPoint(u32 id) const;
  u32 getBLD_IdeaProbRev(u32 id) const;
  u32 getBLD_IdeaAtrDamRev(u32 id) const;
  u32 getBLD_RareListStart() const;
  u32 getBLD_RareListBlade(u32 id) const;
  u32 getBLD_RareListCondition(u32 id) const;
  f32 getBLD_RareListProb1(u32 id) const;
  u32 getBLD_RareListAssure1(u32 id) const;
  f32 getBLD_RareListProb2(u32 id) const;
  u32 getBLD_RareListAssure2(u32 id) const;
  f32 getBLD_RareListProb3(u32 id) const;
  u32 getBLD_RareListAssure3(u32 id) const;
  f32 getBLD_RareListProb4(u32 id) const;
  u32 getBLD_RareListAssure4(u32 id) const;
  f32 getBLD_RareListProb5(u32 id) const;
  u32 getBLD_RareListAssure5(u32 id) const;
  u32 getBLD_ReleaceRewardStart() const;
  u32 getBLD_ReleaceRewardReleace001(u32 id) const;
  u32 getBLD_ReleaceRewardReleace002(u32 id) const;
  u32 getBLD_ReleaceRewardReleace003(u32 id) const;
  u32 getBLD_ReleaceRewardReleace004(u32 id) const;
  u32 getBLD_ReleaceRewardReleace005(u32 id) const;
  u32 getBLD_ReleaceRewardReleace006(u32 id) const;
  u32 getBLD_ReleaceRewardReleace007(u32 id) const;

  u32 getNameListEnd() const;

private:
  CBdatWrapper *unknown10; // Inferred label: mIdeaTable; original member name unknown.
  CBdatWrapper *unknown18; // Inferred label: mBladeTable; original member name unknown.
  CBdatWrapper *unknown20; // Inferred label: mBladeList; original member name unknown.
  CBdatWrapper *unknown28; // Inferred label: mCommonList; original member name unknown.
  CBdatWrapper *unknown30; // Inferred label: mNameList; original member name unknown.
  CBdatWrapper *unknown38; // Inferred label: mBladeModelList; original member name unknown.
  CBdatWrapper *unknown40; // Inferred label: mCreateConfig; original member name unknown.
  CBdatWrapper *unknown48; // Inferred label: mCmnBl_Capacity; original member name unknown.
  CBdatWrapper *unknown50; // Inferred label: mCmnBl_Power; original member name unknown.
  CBdatWrapper *unknown58; // Inferred label: mCmnBl_NewBlArts; original member name unknown.
  CBdatWrapper *unknown60; // Inferred label: mCmnBl_StatusType; original member name unknown.
  CBdatWrapper *unknown68; // Inferred label: mCmnBl_Armor; original member name unknown.
  CBdatWrapper *unknown70; // Inferred label: mFLD_IdeaTable; original member name unknown.
  CBdatWrapper *unknown78; // Inferred label: mBLD_Idea; original member name unknown.
  CBdatWrapper *unknown80; // Inferred label: mBLD_RareList; original member name unknown.
  CBdatWrapper *unknown88; // Inferred label: mBLD_ReleaceReward; original member name unknown.
};

} // namespace gf
