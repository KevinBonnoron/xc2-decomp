#include "gf/data/gf_bdat_cond.h"
#include "bdat.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"

namespace gf {
namespace _gfbdb {

enum {
  ConditionListPremise,
  ConditionListConditionType1,
  ConditionListCondition1,
  ConditionListConditionType2,
  ConditionListCondition2,
  ConditionListConditionType3,
  ConditionListCondition3,
  ConditionListConditionType4,
  ConditionListCondition4,
  ConditionListConditionType5,
  ConditionListCondition5,
  ConditionListConditionType6,
  ConditionListCondition6,
  ConditionListConditionType7,
  ConditionListCondition7,
  ConditionListConditionType8,
  ConditionListCondition8,
  ConditionScenarioScenarioMin,
  ConditionScenarioScenarioMax,
  ConditionScenarioNotScenarioMin,
  ConditionScenarioNotScenarioMax,
  ConditionQuestQuestFlag1,
  ConditionQuestQuestFlagMin1,
  ConditionQuestQuestFlagMax1,
  ConditionQuestQuestFlag2,
  ConditionQuestQuestFlagMin2,
  ConditionQuestQuestFlagMax2,
  ConditionQuestNotQuestFlag1,
  ConditionQuestNotQuestFlagMin1,
  ConditionQuestNotQuestFlagMax1,
  ConditionQuestNotQuestFlag2,
  ConditionQuestNotQuestFlagMin2,
  ConditionQuestNotQuestFlagMax2,
  ConditionEnvTimeRange,
  ConditionEnvWeather,
  ConditionEnvCloudHeight,
  ConditionFlagFlagType,
  ConditionFlagFlagID,
  ConditionFlagFlagMin,
  ConditionFlagFlagMax,
  ConditionItemItemCategory,
  ConditionItemItemID,
  ConditionItemNumber,
  ConditionPTCategory,
  ConditionPTPCID1,
  ConditionPTPCID2,
  ConditionPTPCID3,
  ConditionIdeaPCID,
  ConditionIdeaIdeaLevelBlue,
  ConditionIdeaIdeaLevelRed,
  ConditionIdeaIdeaLevelWhite,
  ConditionIdeaIdeaLevelBlack,
  ConditionIdeaCompatibility,
  ConditionIdeaTrustPoint,
  ConditionLevelPCID,
  ConditionLevelLevel,
  ConditionAchievementAchievementSetID,
  ConditionAchievementValue,
  ConditionFieldSkiiLevelFieldSkillID,
  ConditionFieldSkiiLevelLevel,
  MEMBER_COUNT,
};

static u8 *s_members[MEMBER_COUNT];

void initConditionListPremise(const CBdatWrapper &wrapper) { s_members[ConditionListPremise] = Bdat::getMember(wrapper.data, "Premise"); }

u32 getConditionListPremise(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListPremise] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListPremise], id, 1).valueU8;
}

void initConditionListConditionType1(const CBdatWrapper &wrapper) {
  s_members[ConditionListConditionType1] = Bdat::getMember(wrapper.data, "ConditionType1");
}

u32 getConditionListConditionType1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListConditionType1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListConditionType1], id, 1).valueU8;
}

void initConditionListCondition1(const CBdatWrapper &wrapper) { s_members[ConditionListCondition1] = Bdat::getMember(wrapper.data, "Condition1"); }

u32 getConditionListCondition1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListCondition1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListCondition1], id, 2).valueU16;
}

void initConditionListConditionType2(const CBdatWrapper &wrapper) {
  s_members[ConditionListConditionType2] = Bdat::getMember(wrapper.data, "ConditionType2");
}

u32 getConditionListConditionType2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListConditionType2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListConditionType2], id, 1).valueU8;
}

void initConditionListCondition2(const CBdatWrapper &wrapper) { s_members[ConditionListCondition2] = Bdat::getMember(wrapper.data, "Condition2"); }

u32 getConditionListCondition2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListCondition2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListCondition2], id, 2).valueU16;
}

void initConditionListConditionType3(const CBdatWrapper &wrapper) {
  s_members[ConditionListConditionType3] = Bdat::getMember(wrapper.data, "ConditionType3");
}

u32 getConditionListConditionType3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListConditionType3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListConditionType3], id, 1).valueU8;
}

void initConditionListCondition3(const CBdatWrapper &wrapper) { s_members[ConditionListCondition3] = Bdat::getMember(wrapper.data, "Condition3"); }

u32 getConditionListCondition3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListCondition3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListCondition3], id, 2).valueU16;
}

void initConditionListConditionType4(const CBdatWrapper &wrapper) {
  s_members[ConditionListConditionType4] = Bdat::getMember(wrapper.data, "ConditionType4");
}

u32 getConditionListConditionType4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListConditionType4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListConditionType4], id, 1).valueU8;
}

void initConditionListCondition4(const CBdatWrapper &wrapper) { s_members[ConditionListCondition4] = Bdat::getMember(wrapper.data, "Condition4"); }

u32 getConditionListCondition4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListCondition4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListCondition4], id, 2).valueU16;
}

void initConditionListConditionType5(const CBdatWrapper &wrapper) {
  s_members[ConditionListConditionType5] = Bdat::getMember(wrapper.data, "ConditionType5");
}

u32 getConditionListConditionType5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListConditionType5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListConditionType5], id, 1).valueU8;
}

void initConditionListCondition5(const CBdatWrapper &wrapper) { s_members[ConditionListCondition5] = Bdat::getMember(wrapper.data, "Condition5"); }

u32 getConditionListCondition5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListCondition5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListCondition5], id, 2).valueU16;
}

void initConditionListConditionType6(const CBdatWrapper &wrapper) {
  s_members[ConditionListConditionType6] = Bdat::getMember(wrapper.data, "ConditionType6");
}

u32 getConditionListConditionType6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListConditionType6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListConditionType6], id, 1).valueU8;
}

void initConditionListCondition6(const CBdatWrapper &wrapper) { s_members[ConditionListCondition6] = Bdat::getMember(wrapper.data, "Condition6"); }

u32 getConditionListCondition6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListCondition6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListCondition6], id, 2).valueU16;
}

void initConditionListConditionType7(const CBdatWrapper &wrapper) {
  s_members[ConditionListConditionType7] = Bdat::getMember(wrapper.data, "ConditionType7");
}

u32 getConditionListConditionType7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListConditionType7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListConditionType7], id, 1).valueU8;
}

void initConditionListCondition7(const CBdatWrapper &wrapper) { s_members[ConditionListCondition7] = Bdat::getMember(wrapper.data, "Condition7"); }

u32 getConditionListCondition7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListCondition7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListCondition7], id, 2).valueU16;
}

void initConditionListConditionType8(const CBdatWrapper &wrapper) {
  s_members[ConditionListConditionType8] = Bdat::getMember(wrapper.data, "ConditionType8");
}

u32 getConditionListConditionType8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListConditionType8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListConditionType8], id, 1).valueU8;
}

void initConditionListCondition8(const CBdatWrapper &wrapper) { s_members[ConditionListCondition8] = Bdat::getMember(wrapper.data, "Condition8"); }

u32 getConditionListCondition8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListCondition8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListCondition8], id, 2).valueU16;
}

void initConditionScenarioScenarioMin(const CBdatWrapper &wrapper) {
  s_members[ConditionScenarioScenarioMin] = Bdat::getMember(wrapper.data, "ScenarioMin");
}

u32 getConditionScenarioScenarioMin(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionScenarioScenarioMin] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionScenarioScenarioMin], id, 2).valueU16;
}

void initConditionScenarioScenarioMax(const CBdatWrapper &wrapper) {
  s_members[ConditionScenarioScenarioMax] = Bdat::getMember(wrapper.data, "ScenarioMax");
}

u32 getConditionScenarioScenarioMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionScenarioScenarioMax] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionScenarioScenarioMax], id, 2).valueU16;
}

void initConditionScenarioNotScenarioMin(const CBdatWrapper &wrapper) {
  s_members[ConditionScenarioNotScenarioMin] = Bdat::getMember(wrapper.data, "NotScenarioMin");
}

u32 getConditionScenarioNotScenarioMin(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionScenarioNotScenarioMin] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionScenarioNotScenarioMin], id, 2).valueU16;
}

void initConditionScenarioNotScenarioMax(const CBdatWrapper &wrapper) {
  s_members[ConditionScenarioNotScenarioMax] = Bdat::getMember(wrapper.data, "NotScenarioMax");
}

u32 getConditionScenarioNotScenarioMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionScenarioNotScenarioMax] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionScenarioNotScenarioMax], id, 2).valueU16;
}

void initConditionQuestQuestFlag1(const CBdatWrapper &wrapper) { s_members[ConditionQuestQuestFlag1] = Bdat::getMember(wrapper.data, "QuestFlag1"); }

u32 getConditionQuestQuestFlag1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestQuestFlag1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestQuestFlag1], id, 2).valueU16;
}

void initConditionQuestQuestFlagMin1(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestQuestFlagMin1] = Bdat::getMember(wrapper.data, "QuestFlagMin1");
}

u32 getConditionQuestQuestFlagMin1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestQuestFlagMin1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestQuestFlagMin1], id, 1).valueU8;
}

void initConditionQuestQuestFlagMax1(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestQuestFlagMax1] = Bdat::getMember(wrapper.data, "QuestFlagMax1");
}

u32 getConditionQuestQuestFlagMax1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestQuestFlagMax1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestQuestFlagMax1], id, 1).valueU8;
}

void initConditionQuestQuestFlag2(const CBdatWrapper &wrapper) { s_members[ConditionQuestQuestFlag2] = Bdat::getMember(wrapper.data, "QuestFlag2"); }

u32 getConditionQuestQuestFlag2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestQuestFlag2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestQuestFlag2], id, 2).valueU16;
}

void initConditionQuestQuestFlagMin2(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestQuestFlagMin2] = Bdat::getMember(wrapper.data, "QuestFlagMin2");
}

u32 getConditionQuestQuestFlagMin2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestQuestFlagMin2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestQuestFlagMin2], id, 1).valueU8;
}

void initConditionQuestQuestFlagMax2(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestQuestFlagMax2] = Bdat::getMember(wrapper.data, "QuestFlagMax2");
}

u32 getConditionQuestQuestFlagMax2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestQuestFlagMax2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestQuestFlagMax2], id, 1).valueU8;
}

void initConditionQuestNotQuestFlag1(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestNotQuestFlag1] = Bdat::getMember(wrapper.data, "NotQuestFlag1");
}

u32 getConditionQuestNotQuestFlag1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestNotQuestFlag1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestNotQuestFlag1], id, 2).valueU16;
}

void initConditionQuestNotQuestFlagMin1(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestNotQuestFlagMin1] = Bdat::getMember(wrapper.data, "NotQuestFlagMin1");
}

u32 getConditionQuestNotQuestFlagMin1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestNotQuestFlagMin1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestNotQuestFlagMin1], id, 1).valueU8;
}

void initConditionQuestNotQuestFlagMax1(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestNotQuestFlagMax1] = Bdat::getMember(wrapper.data, "NotQuestFlagMax1");
}

u32 getConditionQuestNotQuestFlagMax1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestNotQuestFlagMax1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestNotQuestFlagMax1], id, 1).valueU8;
}

void initConditionQuestNotQuestFlag2(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestNotQuestFlag2] = Bdat::getMember(wrapper.data, "NotQuestFlag2");
}

u32 getConditionQuestNotQuestFlag2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestNotQuestFlag2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestNotQuestFlag2], id, 2).valueU16;
}

void initConditionQuestNotQuestFlagMin2(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestNotQuestFlagMin2] = Bdat::getMember(wrapper.data, "NotQuestFlagMin2");
}

u32 getConditionQuestNotQuestFlagMin2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestNotQuestFlagMin2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestNotQuestFlagMin2], id, 1).valueU8;
}

void initConditionQuestNotQuestFlagMax2(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestNotQuestFlagMax2] = Bdat::getMember(wrapper.data, "NotQuestFlagMax2");
}

u32 getConditionQuestNotQuestFlagMax2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestNotQuestFlagMax2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestNotQuestFlagMax2], id, 1).valueU8;
}

void initConditionEnvTimeRange(const CBdatWrapper &wrapper) { s_members[ConditionEnvTimeRange] = Bdat::getMember(wrapper.data, "TimeRange"); }

u32 getConditionEnvTimeRange(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionEnvTimeRange] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionEnvTimeRange], id, 3).valueU32;
}

void initConditionEnvWeather(const CBdatWrapper &wrapper) { s_members[ConditionEnvWeather] = Bdat::getMember(wrapper.data, "Weather"); }

u32 getConditionEnvWeather(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionEnvWeather] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionEnvWeather], id, 3).valueU32;
}

void initConditionEnvCloudHeight(const CBdatWrapper &wrapper) { s_members[ConditionEnvCloudHeight] = Bdat::getMember(wrapper.data, "CloudHeight"); }

u32 getConditionEnvCloudHeight(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionEnvCloudHeight] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionEnvCloudHeight], id, 1).valueU8;
}

void initConditionFlagFlagType(const CBdatWrapper &wrapper) { s_members[ConditionFlagFlagType] = Bdat::getMember(wrapper.data, "FlagType"); }

u32 getConditionFlagFlagType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionFlagFlagType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionFlagFlagType], id, 1).valueU8;
}

void initConditionFlagFlagID(const CBdatWrapper &wrapper) { s_members[ConditionFlagFlagID] = Bdat::getMember(wrapper.data, "FlagID"); }

u32 getConditionFlagFlagID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionFlagFlagID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionFlagFlagID], id, 2).valueU16;
}

void initConditionFlagFlagMin(const CBdatWrapper &wrapper) { s_members[ConditionFlagFlagMin] = Bdat::getMember(wrapper.data, "FlagMin"); }

u32 getConditionFlagFlagMin(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionFlagFlagMin] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionFlagFlagMin], id, 2).valueU16;
}

void initConditionFlagFlagMax(const CBdatWrapper &wrapper) { s_members[ConditionFlagFlagMax] = Bdat::getMember(wrapper.data, "FlagMax"); }

u32 getConditionFlagFlagMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionFlagFlagMax] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionFlagFlagMax], id, 2).valueU16;
}

void initConditionItemItemCategory(const CBdatWrapper &wrapper) {
  s_members[ConditionItemItemCategory] = Bdat::getMember(wrapper.data, "ItemCategory");
}

u32 getConditionItemItemCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionItemItemCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionItemItemCategory], id, 1).valueU8;
}

void initConditionItemItemID(const CBdatWrapper &wrapper) { s_members[ConditionItemItemID] = Bdat::getMember(wrapper.data, "ItemID"); }

u32 getConditionItemItemID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionItemItemID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionItemItemID], id, 2).valueU16;
}

void initConditionItemNumber(const CBdatWrapper &wrapper) { s_members[ConditionItemNumber] = Bdat::getMember(wrapper.data, "Number"); }

u32 getConditionItemNumber(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionItemNumber] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionItemNumber], id, 1).valueU8;
}

void initConditionPTCategory(const CBdatWrapper &wrapper) { s_members[ConditionPTCategory] = Bdat::getMember(wrapper.data, "Category"); }

u32 getConditionPTCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionPTCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionPTCategory], id, 1).valueU8;
}

void initConditionPTPCID1(const CBdatWrapper &wrapper) { s_members[ConditionPTPCID1] = Bdat::getMember(wrapper.data, "PCID1"); }

u32 getConditionPTPCID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionPTPCID1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionPTPCID1], id, 2).valueU16;
}

void initConditionPTPCID2(const CBdatWrapper &wrapper) { s_members[ConditionPTPCID2] = Bdat::getMember(wrapper.data, "PCID2"); }

u32 getConditionPTPCID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionPTPCID2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionPTPCID2], id, 2).valueU16;
}

void initConditionPTPCID3(const CBdatWrapper &wrapper) { s_members[ConditionPTPCID3] = Bdat::getMember(wrapper.data, "PCID3"); }

u32 getConditionPTPCID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionPTPCID3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionPTPCID3], id, 2).valueU16;
}

void initConditionIdeaPCID(const CBdatWrapper &wrapper) { s_members[ConditionIdeaPCID] = Bdat::getMember(wrapper.data, "PCID"); }

u32 getConditionIdeaPCID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionIdeaPCID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionIdeaPCID], id, 2).valueU16;
}

void initConditionIdeaIdeaLevelBlue(const CBdatWrapper &wrapper) {
  s_members[ConditionIdeaIdeaLevelBlue] = Bdat::getMember(wrapper.data, "IdeaLevelBlue");
}

u32 getConditionIdeaIdeaLevelBlue(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionIdeaIdeaLevelBlue] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionIdeaIdeaLevelBlue], id, 1).valueU8;
}

void initConditionIdeaIdeaLevelRed(const CBdatWrapper &wrapper) {
  s_members[ConditionIdeaIdeaLevelRed] = Bdat::getMember(wrapper.data, "IdeaLevelRed");
}

u32 getConditionIdeaIdeaLevelRed(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionIdeaIdeaLevelRed] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionIdeaIdeaLevelRed], id, 1).valueU8;
}

void initConditionIdeaIdeaLevelWhite(const CBdatWrapper &wrapper) {
  s_members[ConditionIdeaIdeaLevelWhite] = Bdat::getMember(wrapper.data, "IdeaLevelWhite");
}

u32 getConditionIdeaIdeaLevelWhite(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionIdeaIdeaLevelWhite] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionIdeaIdeaLevelWhite], id, 1).valueU8;
}

void initConditionIdeaIdeaLevelBlack(const CBdatWrapper &wrapper) {
  s_members[ConditionIdeaIdeaLevelBlack] = Bdat::getMember(wrapper.data, "IdeaLevelBlack");
}

u32 getConditionIdeaIdeaLevelBlack(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionIdeaIdeaLevelBlack] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionIdeaIdeaLevelBlack], id, 1).valueU8;
}

void initConditionIdeaCompatibility(const CBdatWrapper &wrapper) {
  s_members[ConditionIdeaCompatibility] = Bdat::getMember(wrapper.data, "Compatibility");
}

u32 getConditionIdeaCompatibility(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionIdeaCompatibility] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionIdeaCompatibility], id, 2).valueU16;
}

void initConditionIdeaTrustPoint(const CBdatWrapper &wrapper) { s_members[ConditionIdeaTrustPoint] = Bdat::getMember(wrapper.data, "TrustPoint"); }

u32 getConditionIdeaTrustPoint(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionIdeaTrustPoint] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionIdeaTrustPoint], id, 2).valueU16;
}

void initConditionLevelPCID(const CBdatWrapper &wrapper) { s_members[ConditionLevelPCID] = Bdat::getMember(wrapper.data, "PCID"); }

u32 getConditionLevelPCID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionLevelPCID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionLevelPCID], id, 2).valueU16;
}

void initConditionLevelLevel(const CBdatWrapper &wrapper) { s_members[ConditionLevelLevel] = Bdat::getMember(wrapper.data, "Level"); }

u32 getConditionLevelLevel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionLevelLevel] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionLevelLevel], id, 1).valueU8;
}

void initConditionAchievementAchievementSetID(const CBdatWrapper &wrapper) {
  s_members[ConditionAchievementAchievementSetID] = Bdat::getMember(wrapper.data, "AchievementSetID");
}

u32 getConditionAchievementAchievementSetID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionAchievementAchievementSetID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionAchievementAchievementSetID], id, 2).valueU16;
}

void initConditionAchievementValue(const CBdatWrapper &wrapper) { s_members[ConditionAchievementValue] = Bdat::getMember(wrapper.data, "Value"); }

u32 getConditionAchievementValue(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionAchievementValue] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionAchievementValue], id, 1).valueU8;
}

void initConditionFieldSkiiLevelFieldSkillID(const CBdatWrapper &wrapper) {
  s_members[ConditionFieldSkiiLevelFieldSkillID] = Bdat::getMember(wrapper.data, "FieldSkillID");
}

u32 getConditionFieldSkiiLevelFieldSkillID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionFieldSkiiLevelFieldSkillID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionFieldSkiiLevelFieldSkillID], id, 2).valueU16;
}

void initConditionFieldSkiiLevelLevel(const CBdatWrapper &wrapper) {
  s_members[ConditionFieldSkiiLevelLevel] = Bdat::getMember(wrapper.data, "Level");
}

u32 getConditionFieldSkiiLevelLevel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionFieldSkiiLevelLevel] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionFieldSkiiLevelLevel], id, 1).valueU8;
}

} // namespace _gfbdb

enum {
  BDAT_FLD_CONDITION_SCENARIO = 0x51,
  BDAT_FLD_CONDITION_FLAG = 0x52,
  BDAT_FLD_CONDITION_LIST = 0x53,
  BDAT_FLD_CONDITION_QUEST = 0x54,
  BDAT_FLD_CONDITION_ENV = 0x55,
  BDAT_FLD_CONDITION_LEVEL = 0x56,
  BDAT_FLD_CONDITION_PT = 0x57,
  BDAT_FLD_CONDITION_ITEM = 0x58,
  BDAT_FLD_CONDITION_IDEA = 0x59,
  BDAT_FLD_CONDITION_ACHIEVEMENT = 0x5a,
  BDAT_FLD_CONDITION_FIELD_SKII_LEVEL = 0x5b,
};

GfBdatCond::GfBdatCond()
    : unknown10(nullptr), unknown18(nullptr), unknown20(nullptr), unknown28(nullptr), unknown30(nullptr),
      unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(nullptr),
      unknown60(nullptr) {
  bdatRefresh();
}

GfBdatCond::~GfBdatCond() { destroyFP(); }

void GfBdatCond::destroyFP() {
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
}

#define NEW_BDAT_WRAPPER(bdat)                                                                                                                       \
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper { GfDataBdat::getFP(bdat) }

void GfBdatCond::createFP() {
  unknown10 = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_LIST);
  unknown18 = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_SCENARIO);
  unknown20 = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_QUEST);
  unknown28 = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_ENV);
  unknown30 = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_FLAG);
  unknown38 = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_ITEM);
  unknown40 = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_PT);
  unknown48 = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_IDEA);
  unknown50 = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_LEVEL);
  unknown58 = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_ACHIEVEMENT);
  unknown60 = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_FIELD_SKII_LEVEL);
}

void GfBdatCond::bdatRefresh() {
  destroyFP();
  createFP();
  _gfbdb::initConditionListPremise(*unknown10);
  _gfbdb::initConditionListConditionType1(*unknown10);
  _gfbdb::initConditionListCondition1(*unknown10);
  _gfbdb::initConditionListConditionType2(*unknown10);
  _gfbdb::initConditionListCondition2(*unknown10);
  _gfbdb::initConditionListConditionType3(*unknown10);
  _gfbdb::initConditionListCondition3(*unknown10);
  _gfbdb::initConditionListConditionType4(*unknown10);
  _gfbdb::initConditionListCondition4(*unknown10);
  _gfbdb::initConditionListConditionType5(*unknown10);
  _gfbdb::initConditionListCondition5(*unknown10);
  _gfbdb::initConditionListConditionType6(*unknown10);
  _gfbdb::initConditionListCondition6(*unknown10);
  _gfbdb::initConditionListConditionType7(*unknown10);
  _gfbdb::initConditionListCondition7(*unknown10);
  _gfbdb::initConditionListConditionType8(*unknown10);
  _gfbdb::initConditionListCondition8(*unknown10);
  _gfbdb::initConditionScenarioScenarioMin(*unknown18);
  _gfbdb::initConditionScenarioScenarioMax(*unknown18);
  _gfbdb::initConditionScenarioNotScenarioMin(*unknown18);
  _gfbdb::initConditionScenarioNotScenarioMax(*unknown18);
  _gfbdb::initConditionQuestQuestFlag1(*unknown20);
  _gfbdb::initConditionQuestQuestFlagMin1(*unknown20);
  _gfbdb::initConditionQuestQuestFlagMax1(*unknown20);
  _gfbdb::initConditionQuestQuestFlag2(*unknown20);
  _gfbdb::initConditionQuestQuestFlagMin2(*unknown20);
  _gfbdb::initConditionQuestQuestFlagMax2(*unknown20);
  _gfbdb::initConditionQuestNotQuestFlag1(*unknown20);
  _gfbdb::initConditionQuestNotQuestFlagMin1(*unknown20);
  _gfbdb::initConditionQuestNotQuestFlagMax1(*unknown20);
  _gfbdb::initConditionQuestNotQuestFlag2(*unknown20);
  _gfbdb::initConditionQuestNotQuestFlagMin2(*unknown20);
  _gfbdb::initConditionQuestNotQuestFlagMax2(*unknown20);
  _gfbdb::initConditionEnvTimeRange(*unknown28);
  _gfbdb::initConditionEnvWeather(*unknown28);
  _gfbdb::initConditionEnvCloudHeight(*unknown28);
  _gfbdb::initConditionFlagFlagType(*unknown30);
  _gfbdb::initConditionFlagFlagID(*unknown30);
  _gfbdb::initConditionFlagFlagMin(*unknown30);
  _gfbdb::initConditionFlagFlagMax(*unknown30);
  _gfbdb::initConditionItemItemCategory(*unknown38);
  _gfbdb::initConditionItemItemID(*unknown38);
  _gfbdb::initConditionItemNumber(*unknown38);
  _gfbdb::initConditionPTCategory(*unknown40);
  _gfbdb::initConditionPTPCID1(*unknown40);
  _gfbdb::initConditionPTPCID2(*unknown40);
  _gfbdb::initConditionPTPCID3(*unknown40);
  _gfbdb::initConditionIdeaPCID(*unknown48);
  _gfbdb::initConditionIdeaIdeaLevelBlue(*unknown48);
  _gfbdb::initConditionIdeaIdeaLevelRed(*unknown48);
  _gfbdb::initConditionIdeaIdeaLevelWhite(*unknown48);
  _gfbdb::initConditionIdeaIdeaLevelBlack(*unknown48);
  _gfbdb::initConditionIdeaCompatibility(*unknown48);
  _gfbdb::initConditionIdeaTrustPoint(*unknown48);
  _gfbdb::initConditionLevelPCID(*unknown50);
  _gfbdb::initConditionLevelLevel(*unknown50);
  _gfbdb::initConditionAchievementAchievementSetID(*unknown58);
  _gfbdb::initConditionAchievementValue(*unknown58);
  _gfbdb::initConditionFieldSkiiLevelFieldSkillID(*unknown60);
  _gfbdb::initConditionFieldSkiiLevelLevel(*unknown60);
}

u32 GfBdatCond::getConditionListStart() const { return Bdat::getIdTop(unknown10->data); }

u32 GfBdatCond::getConditionListEnd() const { return Bdat::getIdTop(unknown10->data) + Bdat::getIdCount(unknown10->data); }

u32 GfBdatCond::getConditionListPremise(u32 id) const { return _gfbdb::getConditionListPremise(*unknown10, id); }

u32 GfBdatCond::getConditionListConditionType1(u32 id) const { return _gfbdb::getConditionListConditionType1(*unknown10, id); }

u32 GfBdatCond::getConditionListCondition1(u32 id) const { return _gfbdb::getConditionListCondition1(*unknown10, id); }

u32 GfBdatCond::getConditionListConditionType2(u32 id) const { return _gfbdb::getConditionListConditionType2(*unknown10, id); }

u32 GfBdatCond::getConditionListCondition2(u32 id) const { return _gfbdb::getConditionListCondition2(*unknown10, id); }

u32 GfBdatCond::getConditionListConditionType3(u32 id) const { return _gfbdb::getConditionListConditionType3(*unknown10, id); }

u32 GfBdatCond::getConditionListCondition3(u32 id) const { return _gfbdb::getConditionListCondition3(*unknown10, id); }

u32 GfBdatCond::getConditionListConditionType4(u32 id) const { return _gfbdb::getConditionListConditionType4(*unknown10, id); }

u32 GfBdatCond::getConditionListCondition4(u32 id) const { return _gfbdb::getConditionListCondition4(*unknown10, id); }

u32 GfBdatCond::getConditionListConditionType5(u32 id) const { return _gfbdb::getConditionListConditionType5(*unknown10, id); }

u32 GfBdatCond::getConditionListCondition5(u32 id) const { return _gfbdb::getConditionListCondition5(*unknown10, id); }

u32 GfBdatCond::getConditionListConditionType6(u32 id) const { return _gfbdb::getConditionListConditionType6(*unknown10, id); }

u32 GfBdatCond::getConditionListCondition6(u32 id) const { return _gfbdb::getConditionListCondition6(*unknown10, id); }

u32 GfBdatCond::getConditionListConditionType7(u32 id) const { return _gfbdb::getConditionListConditionType7(*unknown10, id); }

u32 GfBdatCond::getConditionListCondition7(u32 id) const { return _gfbdb::getConditionListCondition7(*unknown10, id); }

u32 GfBdatCond::getConditionListConditionType8(u32 id) const { return _gfbdb::getConditionListConditionType8(*unknown10, id); }

u32 GfBdatCond::getConditionListCondition8(u32 id) const { return _gfbdb::getConditionListCondition8(*unknown10, id); }

u32 GfBdatCond::getConditionListConditionType(u32 condition, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionListConditionType1,
                                                              _gfbdb::getConditionListConditionType2,
                                                              _gfbdb::getConditionListConditionType3,
                                                              _gfbdb::getConditionListConditionType4,
                                                              _gfbdb::getConditionListConditionType5,
                                                              _gfbdb::getConditionListConditionType6,
                                                              _gfbdb::getConditionListConditionType7,
                                                              _gfbdb::getConditionListConditionType8};
  return getters[index](*unknown10, condition);
}

u32 GfBdatCond::getConditionListCondition(u32 condition, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionListCondition1,
                                                              _gfbdb::getConditionListCondition2,
                                                              _gfbdb::getConditionListCondition3,
                                                              _gfbdb::getConditionListCondition4,
                                                              _gfbdb::getConditionListCondition5,
                                                              _gfbdb::getConditionListCondition6,
                                                              _gfbdb::getConditionListCondition7,
                                                              _gfbdb::getConditionListCondition8};
  return getters[index](*unknown10, condition);
}

u32 GfBdatCond::getConditionScenarioStart() const { return Bdat::getIdTop(unknown18->data); }

u32 GfBdatCond::getConditionScenarioEnd() const { return Bdat::getIdTop(unknown18->data) + Bdat::getIdCount(unknown18->data); }

u32 GfBdatCond::getConditionScenarioScenarioMin(u32 id) const { return _gfbdb::getConditionScenarioScenarioMin(*unknown18, id); }

u32 GfBdatCond::getConditionScenarioScenarioMax(u32 id) const { return _gfbdb::getConditionScenarioScenarioMax(*unknown18, id); }

u32 GfBdatCond::getConditionScenarioNotScenarioMin(u32 id) const { return _gfbdb::getConditionScenarioNotScenarioMin(*unknown18, id); }

u32 GfBdatCond::getConditionScenarioNotScenarioMax(u32 id) const { return _gfbdb::getConditionScenarioNotScenarioMax(*unknown18, id); }

u32 GfBdatCond::getConditionQuestStart() const { return Bdat::getIdTop(unknown20->data); }

u32 GfBdatCond::getConditionQuestEnd() const { return Bdat::getIdTop(unknown20->data) + Bdat::getIdCount(unknown20->data); }

u32 GfBdatCond::getConditionQuestQuestFlag1(u32 id) const { return _gfbdb::getConditionQuestQuestFlag1(*unknown20, id); }

u32 GfBdatCond::getConditionQuestQuestFlagMin1(u32 id) const { return _gfbdb::getConditionQuestQuestFlagMin1(*unknown20, id); }

u32 GfBdatCond::getConditionQuestQuestFlagMax1(u32 id) const { return _gfbdb::getConditionQuestQuestFlagMax1(*unknown20, id); }

u32 GfBdatCond::getConditionQuestQuestFlag2(u32 id) const { return _gfbdb::getConditionQuestQuestFlag2(*unknown20, id); }

u32 GfBdatCond::getConditionQuestQuestFlagMin2(u32 id) const { return _gfbdb::getConditionQuestQuestFlagMin2(*unknown20, id); }

u32 GfBdatCond::getConditionQuestQuestFlagMax2(u32 id) const { return _gfbdb::getConditionQuestQuestFlagMax2(*unknown20, id); }

u32 GfBdatCond::getConditionQuestNotQuestFlag1(u32 id) const { return _gfbdb::getConditionQuestNotQuestFlag1(*unknown20, id); }

u32 GfBdatCond::getConditionQuestNotQuestFlagMin1(u32 id) const { return _gfbdb::getConditionQuestNotQuestFlagMin1(*unknown20, id); }

u32 GfBdatCond::getConditionQuestNotQuestFlagMax1(u32 id) const { return _gfbdb::getConditionQuestNotQuestFlagMax1(*unknown20, id); }

u32 GfBdatCond::getConditionQuestNotQuestFlag2(u32 id) const { return _gfbdb::getConditionQuestNotQuestFlag2(*unknown20, id); }

u32 GfBdatCond::getConditionQuestNotQuestFlagMin2(u32 id) const { return _gfbdb::getConditionQuestNotQuestFlagMin2(*unknown20, id); }

u32 GfBdatCond::getConditionQuestNotQuestFlagMax2(u32 id) const { return _gfbdb::getConditionQuestNotQuestFlagMax2(*unknown20, id); }

u32 GfBdatCond::getConditionQuestQuestFlag(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionQuestQuestFlag1, _gfbdb::getConditionQuestQuestFlag2};
  return getters[index](*unknown20, id);
}

u32 GfBdatCond::getConditionQuestQuestFlagMin(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionQuestQuestFlagMin1, _gfbdb::getConditionQuestQuestFlagMin2};
  return getters[index](*unknown20, id);
}

u32 GfBdatCond::getConditionQuestQuestFlagMax(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionQuestQuestFlagMax1, _gfbdb::getConditionQuestQuestFlagMax2};
  return getters[index](*unknown20, id);
}

u32 GfBdatCond::getConditionQuestNotQuestFlag(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionQuestNotQuestFlag1, _gfbdb::getConditionQuestNotQuestFlag2};
  return getters[index](*unknown20, id);
}

u32 GfBdatCond::getConditionQuestNotQuestFlagMin(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionQuestNotQuestFlagMin1, _gfbdb::getConditionQuestNotQuestFlagMin2};
  return getters[index](*unknown20, id);
}

u32 GfBdatCond::getConditionQuestNotQuestFlagMax(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionQuestNotQuestFlagMax1, _gfbdb::getConditionQuestNotQuestFlagMax2};
  return getters[index](*unknown20, id);
}

u32 GfBdatCond::getConditionEnvStart() const { return Bdat::getIdTop(unknown28->data); }

u32 GfBdatCond::getConditionEnvEnd() const { return Bdat::getIdTop(unknown28->data) + Bdat::getIdCount(unknown28->data); }

u32 GfBdatCond::getConditionEnvTimeRange(u32 id) const { return _gfbdb::getConditionEnvTimeRange(*unknown28, id); }

u32 GfBdatCond::getConditionEnvWeather(u32 id) const { return _gfbdb::getConditionEnvWeather(*unknown28, id); }

u32 GfBdatCond::getConditionEnvCloudHeight(u32 id) const { return _gfbdb::getConditionEnvCloudHeight(*unknown28, id); }

u32 GfBdatCond::getConditionFlagStart() const { return Bdat::getIdTop(unknown30->data); }

u32 GfBdatCond::getConditionFlagEnd() const { return Bdat::getIdTop(unknown30->data) + Bdat::getIdCount(unknown30->data); }

u32 GfBdatCond::getConditionFlagFlagType(u32 id) const { return _gfbdb::getConditionFlagFlagType(*unknown30, id); }

u32 GfBdatCond::getConditionFlagFlagID(u32 id) const { return _gfbdb::getConditionFlagFlagID(*unknown30, id); }

u32 GfBdatCond::getConditionFlagFlagMin(u32 id) const { return _gfbdb::getConditionFlagFlagMin(*unknown30, id); }

u32 GfBdatCond::getConditionFlagFlagMax(u32 id) const { return _gfbdb::getConditionFlagFlagMax(*unknown30, id); }

u32 GfBdatCond::getConditionItemStart() const { return Bdat::getIdTop(unknown38->data); }

u32 GfBdatCond::getConditionItemEnd() const { return Bdat::getIdTop(unknown38->data) + Bdat::getIdCount(unknown38->data); }

u32 GfBdatCond::getConditionItemItemCategory(u32 id) const { return _gfbdb::getConditionItemItemCategory(*unknown38, id); }

u32 GfBdatCond::getConditionItemItemID(u32 id) const { return _gfbdb::getConditionItemItemID(*unknown38, id); }

u32 GfBdatCond::getConditionItemNumber(u32 id) const { return _gfbdb::getConditionItemNumber(*unknown38, id); }

u32 GfBdatCond::getConditionPTStart() const { return Bdat::getIdTop(unknown40->data); }

u32 GfBdatCond::getConditionPTEnd() const { return Bdat::getIdTop(unknown40->data) + Bdat::getIdCount(unknown40->data); }

u32 GfBdatCond::getConditionPTCategory(u32 id) const { return _gfbdb::getConditionPTCategory(*unknown40, id); }

u32 GfBdatCond::getConditionPTPCID1(u32 id) const { return _gfbdb::getConditionPTPCID1(*unknown40, id); }

u32 GfBdatCond::getConditionPTPCID2(u32 id) const { return _gfbdb::getConditionPTPCID2(*unknown40, id); }

u32 GfBdatCond::getConditionPTPCID3(u32 id) const { return _gfbdb::getConditionPTPCID3(*unknown40, id); }

u32 GfBdatCond::getConditionPTPCID(u32 condition, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionPTPCID1, _gfbdb::getConditionPTPCID2, _gfbdb::getConditionPTPCID3};
  return getters[index](*unknown40, condition);
}

u32 GfBdatCond::getConditionIdeaStart() const { return Bdat::getIdTop(unknown48->data); }

u32 GfBdatCond::getConditionIdeaEnd() const { return Bdat::getIdTop(unknown48->data) + Bdat::getIdCount(unknown48->data); }

u32 GfBdatCond::getConditionIdeaPCID(u32 id) const { return _gfbdb::getConditionIdeaPCID(*unknown48, id); }

u32 GfBdatCond::getConditionIdeaIdeaLevelBlue(u32 id) const { return _gfbdb::getConditionIdeaIdeaLevelBlue(*unknown48, id); }

u32 GfBdatCond::getConditionIdeaIdeaLevelRed(u32 id) const { return _gfbdb::getConditionIdeaIdeaLevelRed(*unknown48, id); }

u32 GfBdatCond::getConditionIdeaIdeaLevelWhite(u32 id) const { return _gfbdb::getConditionIdeaIdeaLevelWhite(*unknown48, id); }

u32 GfBdatCond::getConditionIdeaIdeaLevelBlack(u32 id) const { return _gfbdb::getConditionIdeaIdeaLevelBlack(*unknown48, id); }

u32 GfBdatCond::getConditionIdeaCompatibility(u32 id) const { return _gfbdb::getConditionIdeaCompatibility(*unknown48, id); }

u32 GfBdatCond::getConditionIdeaTrustPoint(u32 id) const { return _gfbdb::getConditionIdeaTrustPoint(*unknown48, id); }

u32 GfBdatCond::getConditionIdeaIdeaLevel(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionIdeaIdeaLevelBlue,
                                                              _gfbdb::getConditionIdeaIdeaLevelRed,
                                                              _gfbdb::getConditionIdeaIdeaLevelWhite,
                                                              _gfbdb::getConditionIdeaIdeaLevelBlack};
  return getters[index](*unknown48, id);
}

u32 GfBdatCond::getConditionLevelStart() const { return Bdat::getIdTop(unknown50->data); }

u32 GfBdatCond::getConditionLevelEnd() const { return Bdat::getIdTop(unknown50->data) + Bdat::getIdCount(unknown50->data); }

u32 GfBdatCond::getConditionLevelPCID(u32 id) const { return _gfbdb::getConditionLevelPCID(*unknown50, id); }

u32 GfBdatCond::getConditionLevelLevel(u32 id) const { return _gfbdb::getConditionLevelLevel(*unknown50, id); }

u32 GfBdatCond::getConditionAchievementStart() const { return Bdat::getIdTop(unknown58->data); }

u32 GfBdatCond::getConditionAchievementEnd() const {
  return Bdat::getIdTop(unknown58->data) + Bdat::getIdCount(unknown58->data);
}

u32 GfBdatCond::getConditionAchievementAchievementSetID(u32 id) const {
  return _gfbdb::getConditionAchievementAchievementSetID(*unknown58, id);
}

u32 GfBdatCond::getConditionAchievementValue(u32 id) const { return _gfbdb::getConditionAchievementValue(*unknown58, id); }

u32 GfBdatCond::getConditionFieldSkiiLevelStart() const { return Bdat::getIdTop(unknown60->data); }

u32 GfBdatCond::getConditionFieldSkiiLevelEnd() const {
  return Bdat::getIdTop(unknown60->data) + Bdat::getIdCount(unknown60->data);
}

u32 GfBdatCond::getConditionFieldSkiiLevelFieldSkillID(u32 id) const {
  return _gfbdb::getConditionFieldSkiiLevelFieldSkillID(*unknown60, id);
}

u32 GfBdatCond::getConditionFieldSkiiLevelLevel(u32 id) const { return _gfbdb::getConditionFieldSkiiLevelLevel(*unknown60, id); }

} // namespace gf
