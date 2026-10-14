#pragma once
#include "gf/data/gf_bdat_wrapper.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatCond : public mm::mtl::PtrSingleton<GfBdatCond>, public GfBdatRefresh {
public:
  GfBdatCond();
  virtual ~GfBdatCond();
  void destroyFP();
  void createFP();
  void bdatRefresh() override;
  u32 getConditionListStart() const;
  u32 getConditionListEnd() const;
  u32 getConditionListPremise(u32 id) const;
  u32 getConditionListConditionType1(u32 id) const;
  u32 getConditionListCondition1(u32 id) const;
  u32 getConditionListConditionType2(u32 id) const;
  u32 getConditionListCondition2(u32 id) const;
  u32 getConditionListConditionType3(u32 id) const;
  u32 getConditionListCondition3(u32 id) const;
  u32 getConditionListConditionType4(u32 id) const;
  u32 getConditionListCondition4(u32 id) const;
  u32 getConditionListConditionType5(u32 id) const;
  u32 getConditionListCondition5(u32 id) const;
  u32 getConditionListConditionType6(u32 id) const;
  u32 getConditionListCondition6(u32 id) const;
  u32 getConditionListConditionType7(u32 id) const;
  u32 getConditionListCondition7(u32 id) const;
  u32 getConditionListConditionType8(u32 id) const;
  u32 getConditionListCondition8(u32 id) const;
  u32 getConditionListConditionType(u32 condition, u32 index) const;
  u32 getConditionListCondition(u32 condition, u32 index) const;
  u32 getConditionScenarioStart() const;
  u32 getConditionScenarioEnd() const;
  u32 getConditionScenarioScenarioMin(u32 id) const;
  u32 getConditionScenarioScenarioMax(u32 id) const;
  u32 getConditionScenarioNotScenarioMin(u32 id) const;
  u32 getConditionScenarioNotScenarioMax(u32 id) const;
  u32 getConditionQuestStart() const;
  u32 getConditionQuestEnd() const;
  u32 getConditionQuestQuestFlag1(u32 id) const;
  u32 getConditionQuestQuestFlagMin1(u32 id) const;
  u32 getConditionQuestQuestFlagMax1(u32 id) const;
  u32 getConditionQuestQuestFlag2(u32 id) const;
  u32 getConditionQuestQuestFlagMin2(u32 id) const;
  u32 getConditionQuestQuestFlagMax2(u32 id) const;
  u32 getConditionQuestNotQuestFlag1(u32 id) const;
  u32 getConditionQuestNotQuestFlagMin1(u32 id) const;
  u32 getConditionQuestNotQuestFlagMax1(u32 id) const;
  u32 getConditionQuestNotQuestFlag2(u32 id) const;
  u32 getConditionQuestNotQuestFlagMin2(u32 id) const;
  u32 getConditionQuestNotQuestFlagMax2(u32 id) const;
  u32 getConditionQuestQuestFlag(u32 id, u32 index) const;
  u32 getConditionQuestQuestFlagMin(u32 id, u32 index) const;
  u32 getConditionQuestQuestFlagMax(u32 id, u32 index) const;
  u32 getConditionQuestNotQuestFlag(u32 id, u32 index) const;
  u32 getConditionQuestNotQuestFlagMin(u32 id, u32 index) const;
  u32 getConditionQuestNotQuestFlagMax(u32 id, u32 index) const;
  u32 getConditionEnvStart() const;
  u32 getConditionEnvEnd() const;
  u32 getConditionEnvTimeRange(u32 id) const;
  u32 getConditionEnvWeather(u32 id) const;
  u32 getConditionEnvCloudHeight(u32 id) const;
  u32 getConditionFlagStart() const;
  u32 getConditionFlagEnd() const;
  u32 getConditionFlagFlagType(u32 id) const;
  u32 getConditionFlagFlagID(u32 id) const;
  u32 getConditionFlagFlagMin(u32 id) const;
  u32 getConditionFlagFlagMax(u32 id) const;
  u32 getConditionItemStart() const;
  u32 getConditionItemEnd() const;
  u32 getConditionItemItemCategory(u32 id) const;
  u32 getConditionItemItemID(u32 id) const;
  u32 getConditionItemNumber(u32 id) const;
  u32 getConditionPTStart() const;
  u32 getConditionPTEnd() const;
  u32 getConditionPTCategory(u32 id) const;
  u32 getConditionPTPCID1(u32 id) const;
  u32 getConditionPTPCID2(u32 id) const;
  u32 getConditionPTPCID3(u32 id) const;
  u32 getConditionPTPCID(u32 condition, u32 index) const;
  u32 getConditionIdeaStart() const;
  u32 getConditionIdeaEnd() const;
  u32 getConditionIdeaPCID(u32 id) const;
  u32 getConditionIdeaIdeaLevelBlue(u32 id) const;
  u32 getConditionIdeaIdeaLevelRed(u32 id) const;
  u32 getConditionIdeaIdeaLevelWhite(u32 id) const;
  u32 getConditionIdeaIdeaLevelBlack(u32 id) const;
  u32 getConditionIdeaCompatibility(u32 id) const;
  u32 getConditionIdeaTrustPoint(u32 id) const;
  u32 getConditionIdeaIdeaLevel(u32 id, u32 index) const;
  u32 getConditionLevelStart() const;
  u32 getConditionLevelEnd() const;
  u32 getConditionLevelPCID(u32 id) const;
  u32 getConditionLevelLevel(u32 id) const;
  u32 getConditionAchievementStart() const;
  u32 getConditionAchievementEnd() const;
  u32 getConditionAchievementAchievementSetID(u32 id) const;
  u32 getConditionAchievementValue(u32 id) const;
  u32 getConditionFieldSkiiLevelStart() const;
  u32 getConditionFieldSkiiLevelEnd() const;
  u32 getConditionFieldSkiiLevelFieldSkillID(u32 id) const;
  u32 getConditionFieldSkiiLevelLevel(u32 id) const;

private:
  CBdatWrapper *unknown10; // Inferred label: mConditionList; original member name unknown.
  CBdatWrapper *unknown18; // Inferred label: mConditionScenario; original member name unknown.
  CBdatWrapper *unknown20; // Inferred label: mConditionQuest; original member name unknown.
  CBdatWrapper *unknown28; // Inferred label: mConditionEnv; original member name unknown.
  CBdatWrapper *unknown30; // Inferred label: mConditionFlag; original member name unknown.
  CBdatWrapper *unknown38; // Inferred label: mConditionItem; original member name unknown.
  CBdatWrapper *unknown40; // Inferred label: mConditionPT; original member name unknown.
  CBdatWrapper *unknown48; // Inferred label: mConditionIdea; original member name unknown.
  CBdatWrapper *unknown50; // Inferred label: mConditionLevel; original member name unknown.
  CBdatWrapper *unknown58; // Inferred label: mConditionAchievement; original member name unknown.
  CBdatWrapper *unknown60; // Inferred label: mConditionFieldSkiiLevel; original member name unknown.
};

} // namespace gf
