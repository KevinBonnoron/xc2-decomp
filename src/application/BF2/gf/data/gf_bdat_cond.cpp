// clang-format off
#include "gf/data/gf_bdat_cond.h"
#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
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

void initConditionListPremise(const CBdatWrapper &wrapper) { s_members[ConditionListPremise] = Bdat::getMember(wrapper.unknown00, "Premise"); }

u32 getConditionListPremise(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListPremise] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListPremise], id, 1).valueU8;
}

void initConditionListConditionType1(const CBdatWrapper &wrapper) {
  s_members[ConditionListConditionType1] = Bdat::getMember(wrapper.unknown00, "ConditionType1");
}

u32 getConditionListConditionType1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListConditionType1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListConditionType1], id, 1).valueU8;
}

void initConditionListCondition1(const CBdatWrapper &wrapper) { s_members[ConditionListCondition1] = Bdat::getMember(wrapper.unknown00, "Condition1"); }

u32 getConditionListCondition1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListCondition1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListCondition1], id, 2).valueU16;
}

void initConditionListConditionType2(const CBdatWrapper &wrapper) {
  s_members[ConditionListConditionType2] = Bdat::getMember(wrapper.unknown00, "ConditionType2");
}

u32 getConditionListConditionType2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListConditionType2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListConditionType2], id, 1).valueU8;
}

void initConditionListCondition2(const CBdatWrapper &wrapper) { s_members[ConditionListCondition2] = Bdat::getMember(wrapper.unknown00, "Condition2"); }

u32 getConditionListCondition2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListCondition2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListCondition2], id, 2).valueU16;
}

void initConditionListConditionType3(const CBdatWrapper &wrapper) {
  s_members[ConditionListConditionType3] = Bdat::getMember(wrapper.unknown00, "ConditionType3");
}

u32 getConditionListConditionType3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListConditionType3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListConditionType3], id, 1).valueU8;
}

void initConditionListCondition3(const CBdatWrapper &wrapper) { s_members[ConditionListCondition3] = Bdat::getMember(wrapper.unknown00, "Condition3"); }

u32 getConditionListCondition3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListCondition3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListCondition3], id, 2).valueU16;
}

void initConditionListConditionType4(const CBdatWrapper &wrapper) {
  s_members[ConditionListConditionType4] = Bdat::getMember(wrapper.unknown00, "ConditionType4");
}

u32 getConditionListConditionType4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListConditionType4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListConditionType4], id, 1).valueU8;
}

void initConditionListCondition4(const CBdatWrapper &wrapper) { s_members[ConditionListCondition4] = Bdat::getMember(wrapper.unknown00, "Condition4"); }

u32 getConditionListCondition4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListCondition4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListCondition4], id, 2).valueU16;
}

void initConditionListConditionType5(const CBdatWrapper &wrapper) {
  s_members[ConditionListConditionType5] = Bdat::getMember(wrapper.unknown00, "ConditionType5");
}

u32 getConditionListConditionType5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListConditionType5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListConditionType5], id, 1).valueU8;
}

void initConditionListCondition5(const CBdatWrapper &wrapper) { s_members[ConditionListCondition5] = Bdat::getMember(wrapper.unknown00, "Condition5"); }

u32 getConditionListCondition5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListCondition5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListCondition5], id, 2).valueU16;
}

void initConditionListConditionType6(const CBdatWrapper &wrapper) {
  s_members[ConditionListConditionType6] = Bdat::getMember(wrapper.unknown00, "ConditionType6");
}

u32 getConditionListConditionType6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListConditionType6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListConditionType6], id, 1).valueU8;
}

void initConditionListCondition6(const CBdatWrapper &wrapper) { s_members[ConditionListCondition6] = Bdat::getMember(wrapper.unknown00, "Condition6"); }

u32 getConditionListCondition6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListCondition6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListCondition6], id, 2).valueU16;
}

void initConditionListConditionType7(const CBdatWrapper &wrapper) {
  s_members[ConditionListConditionType7] = Bdat::getMember(wrapper.unknown00, "ConditionType7");
}

u32 getConditionListConditionType7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListConditionType7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListConditionType7], id, 1).valueU8;
}

void initConditionListCondition7(const CBdatWrapper &wrapper) { s_members[ConditionListCondition7] = Bdat::getMember(wrapper.unknown00, "Condition7"); }

u32 getConditionListCondition7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListCondition7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListCondition7], id, 2).valueU16;
}

void initConditionListConditionType8(const CBdatWrapper &wrapper) {
  s_members[ConditionListConditionType8] = Bdat::getMember(wrapper.unknown00, "ConditionType8");
}

u32 getConditionListConditionType8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListConditionType8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListConditionType8], id, 1).valueU8;
}

void initConditionListCondition8(const CBdatWrapper &wrapper) { s_members[ConditionListCondition8] = Bdat::getMember(wrapper.unknown00, "Condition8"); }

u32 getConditionListCondition8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionListCondition8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionListCondition8], id, 2).valueU16;
}

void initConditionScenarioScenarioMin(const CBdatWrapper &wrapper) {
  s_members[ConditionScenarioScenarioMin] = Bdat::getMember(wrapper.unknown00, "ScenarioMin");
}

u32 getConditionScenarioScenarioMin(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionScenarioScenarioMin] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionScenarioScenarioMin], id, 2).valueU16;
}

void initConditionScenarioScenarioMax(const CBdatWrapper &wrapper) {
  s_members[ConditionScenarioScenarioMax] = Bdat::getMember(wrapper.unknown00, "ScenarioMax");
}

u32 getConditionScenarioScenarioMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionScenarioScenarioMax] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionScenarioScenarioMax], id, 2).valueU16;
}

void initConditionScenarioNotScenarioMin(const CBdatWrapper &wrapper) {
  s_members[ConditionScenarioNotScenarioMin] = Bdat::getMember(wrapper.unknown00, "NotScenarioMin");
}

u32 getConditionScenarioNotScenarioMin(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionScenarioNotScenarioMin] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionScenarioNotScenarioMin], id, 2).valueU16;
}

void initConditionScenarioNotScenarioMax(const CBdatWrapper &wrapper) {
  s_members[ConditionScenarioNotScenarioMax] = Bdat::getMember(wrapper.unknown00, "NotScenarioMax");
}

u32 getConditionScenarioNotScenarioMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionScenarioNotScenarioMax] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionScenarioNotScenarioMax], id, 2).valueU16;
}

void initConditionQuestQuestFlag1(const CBdatWrapper &wrapper) { s_members[ConditionQuestQuestFlag1] = Bdat::getMember(wrapper.unknown00, "QuestFlag1"); }

u32 getConditionQuestQuestFlag1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestQuestFlag1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestQuestFlag1], id, 2).valueU16;
}

void initConditionQuestQuestFlagMin1(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestQuestFlagMin1] = Bdat::getMember(wrapper.unknown00, "QuestFlagMin1");
}

u32 getConditionQuestQuestFlagMin1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestQuestFlagMin1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestQuestFlagMin1], id, 1).valueU8;
}

void initConditionQuestQuestFlagMax1(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestQuestFlagMax1] = Bdat::getMember(wrapper.unknown00, "QuestFlagMax1");
}

u32 getConditionQuestQuestFlagMax1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestQuestFlagMax1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestQuestFlagMax1], id, 1).valueU8;
}

void initConditionQuestQuestFlag2(const CBdatWrapper &wrapper) { s_members[ConditionQuestQuestFlag2] = Bdat::getMember(wrapper.unknown00, "QuestFlag2"); }

u32 getConditionQuestQuestFlag2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestQuestFlag2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestQuestFlag2], id, 2).valueU16;
}

void initConditionQuestQuestFlagMin2(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestQuestFlagMin2] = Bdat::getMember(wrapper.unknown00, "QuestFlagMin2");
}

u32 getConditionQuestQuestFlagMin2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestQuestFlagMin2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestQuestFlagMin2], id, 1).valueU8;
}

void initConditionQuestQuestFlagMax2(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestQuestFlagMax2] = Bdat::getMember(wrapper.unknown00, "QuestFlagMax2");
}

u32 getConditionQuestQuestFlagMax2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestQuestFlagMax2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestQuestFlagMax2], id, 1).valueU8;
}

void initConditionQuestNotQuestFlag1(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestNotQuestFlag1] = Bdat::getMember(wrapper.unknown00, "NotQuestFlag1");
}

u32 getConditionQuestNotQuestFlag1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestNotQuestFlag1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestNotQuestFlag1], id, 2).valueU16;
}

void initConditionQuestNotQuestFlagMin1(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestNotQuestFlagMin1] = Bdat::getMember(wrapper.unknown00, "NotQuestFlagMin1");
}

u32 getConditionQuestNotQuestFlagMin1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestNotQuestFlagMin1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestNotQuestFlagMin1], id, 1).valueU8;
}

void initConditionQuestNotQuestFlagMax1(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestNotQuestFlagMax1] = Bdat::getMember(wrapper.unknown00, "NotQuestFlagMax1");
}

u32 getConditionQuestNotQuestFlagMax1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestNotQuestFlagMax1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestNotQuestFlagMax1], id, 1).valueU8;
}

void initConditionQuestNotQuestFlag2(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestNotQuestFlag2] = Bdat::getMember(wrapper.unknown00, "NotQuestFlag2");
}

u32 getConditionQuestNotQuestFlag2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestNotQuestFlag2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestNotQuestFlag2], id, 2).valueU16;
}

void initConditionQuestNotQuestFlagMin2(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestNotQuestFlagMin2] = Bdat::getMember(wrapper.unknown00, "NotQuestFlagMin2");
}

u32 getConditionQuestNotQuestFlagMin2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestNotQuestFlagMin2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestNotQuestFlagMin2], id, 1).valueU8;
}

void initConditionQuestNotQuestFlagMax2(const CBdatWrapper &wrapper) {
  s_members[ConditionQuestNotQuestFlagMax2] = Bdat::getMember(wrapper.unknown00, "NotQuestFlagMax2");
}

u32 getConditionQuestNotQuestFlagMax2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionQuestNotQuestFlagMax2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionQuestNotQuestFlagMax2], id, 1).valueU8;
}

void initConditionEnvTimeRange(const CBdatWrapper &wrapper) { s_members[ConditionEnvTimeRange] = Bdat::getMember(wrapper.unknown00, "TimeRange"); }

u32 getConditionEnvTimeRange(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionEnvTimeRange] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionEnvTimeRange], id, 3).valueU32;
}

void initConditionEnvWeather(const CBdatWrapper &wrapper) { s_members[ConditionEnvWeather] = Bdat::getMember(wrapper.unknown00, "Weather"); }

u32 getConditionEnvWeather(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionEnvWeather] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionEnvWeather], id, 3).valueU32;
}

void initConditionEnvCloudHeight(const CBdatWrapper &wrapper) { s_members[ConditionEnvCloudHeight] = Bdat::getMember(wrapper.unknown00, "CloudHeight"); }

u32 getConditionEnvCloudHeight(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionEnvCloudHeight] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionEnvCloudHeight], id, 1).valueU8;
}

void initConditionFlagFlagType(const CBdatWrapper &wrapper) { s_members[ConditionFlagFlagType] = Bdat::getMember(wrapper.unknown00, "FlagType"); }

u32 getConditionFlagFlagType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionFlagFlagType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionFlagFlagType], id, 1).valueU8;
}

void initConditionFlagFlagID(const CBdatWrapper &wrapper) { s_members[ConditionFlagFlagID] = Bdat::getMember(wrapper.unknown00, "FlagID"); }

u32 getConditionFlagFlagID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionFlagFlagID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionFlagFlagID], id, 2).valueU16;
}

void initConditionFlagFlagMin(const CBdatWrapper &wrapper) { s_members[ConditionFlagFlagMin] = Bdat::getMember(wrapper.unknown00, "FlagMin"); }

u32 getConditionFlagFlagMin(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionFlagFlagMin] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionFlagFlagMin], id, 2).valueU16;
}

void initConditionFlagFlagMax(const CBdatWrapper &wrapper) { s_members[ConditionFlagFlagMax] = Bdat::getMember(wrapper.unknown00, "FlagMax"); }

u32 getConditionFlagFlagMax(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionFlagFlagMax] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionFlagFlagMax], id, 2).valueU16;
}

void initConditionItemItemCategory(const CBdatWrapper &wrapper) {
  s_members[ConditionItemItemCategory] = Bdat::getMember(wrapper.unknown00, "ItemCategory");
}

u32 getConditionItemItemCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionItemItemCategory] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionItemItemCategory], id, 1).valueU8;
}

void initConditionItemItemID(const CBdatWrapper &wrapper) { s_members[ConditionItemItemID] = Bdat::getMember(wrapper.unknown00, "ItemID"); }

u32 getConditionItemItemID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionItemItemID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionItemItemID], id, 2).valueU16;
}

void initConditionItemNumber(const CBdatWrapper &wrapper) { s_members[ConditionItemNumber] = Bdat::getMember(wrapper.unknown00, "Number"); }

u32 getConditionItemNumber(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionItemNumber] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionItemNumber], id, 1).valueU8;
}

void initConditionPTCategory(const CBdatWrapper &wrapper) { s_members[ConditionPTCategory] = Bdat::getMember(wrapper.unknown00, "Category"); }

u32 getConditionPTCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionPTCategory] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionPTCategory], id, 1).valueU8;
}

void initConditionPTPCID1(const CBdatWrapper &wrapper) { s_members[ConditionPTPCID1] = Bdat::getMember(wrapper.unknown00, "PCID1"); }

u32 getConditionPTPCID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionPTPCID1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionPTPCID1], id, 2).valueU16;
}

void initConditionPTPCID2(const CBdatWrapper &wrapper) { s_members[ConditionPTPCID2] = Bdat::getMember(wrapper.unknown00, "PCID2"); }

u32 getConditionPTPCID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionPTPCID2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionPTPCID2], id, 2).valueU16;
}

void initConditionPTPCID3(const CBdatWrapper &wrapper) { s_members[ConditionPTPCID3] = Bdat::getMember(wrapper.unknown00, "PCID3"); }

u32 getConditionPTPCID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionPTPCID3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionPTPCID3], id, 2).valueU16;
}

void initConditionIdeaPCID(const CBdatWrapper &wrapper) { s_members[ConditionIdeaPCID] = Bdat::getMember(wrapper.unknown00, "PCID"); }

u32 getConditionIdeaPCID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionIdeaPCID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionIdeaPCID], id, 2).valueU16;
}

void initConditionIdeaIdeaLevelBlue(const CBdatWrapper &wrapper) {
  s_members[ConditionIdeaIdeaLevelBlue] = Bdat::getMember(wrapper.unknown00, "IdeaLevelBlue");
}

u32 getConditionIdeaIdeaLevelBlue(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionIdeaIdeaLevelBlue] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionIdeaIdeaLevelBlue], id, 1).valueU8;
}

void initConditionIdeaIdeaLevelRed(const CBdatWrapper &wrapper) {
  s_members[ConditionIdeaIdeaLevelRed] = Bdat::getMember(wrapper.unknown00, "IdeaLevelRed");
}

u32 getConditionIdeaIdeaLevelRed(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionIdeaIdeaLevelRed] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionIdeaIdeaLevelRed], id, 1).valueU8;
}

void initConditionIdeaIdeaLevelWhite(const CBdatWrapper &wrapper) {
  s_members[ConditionIdeaIdeaLevelWhite] = Bdat::getMember(wrapper.unknown00, "IdeaLevelWhite");
}

u32 getConditionIdeaIdeaLevelWhite(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionIdeaIdeaLevelWhite] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionIdeaIdeaLevelWhite], id, 1).valueU8;
}

void initConditionIdeaIdeaLevelBlack(const CBdatWrapper &wrapper) {
  s_members[ConditionIdeaIdeaLevelBlack] = Bdat::getMember(wrapper.unknown00, "IdeaLevelBlack");
}

u32 getConditionIdeaIdeaLevelBlack(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionIdeaIdeaLevelBlack] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionIdeaIdeaLevelBlack], id, 1).valueU8;
}

void initConditionIdeaCompatibility(const CBdatWrapper &wrapper) {
  s_members[ConditionIdeaCompatibility] = Bdat::getMember(wrapper.unknown00, "Compatibility");
}

u32 getConditionIdeaCompatibility(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionIdeaCompatibility] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionIdeaCompatibility], id, 2).valueU16;
}

void initConditionIdeaTrustPoint(const CBdatWrapper &wrapper) { s_members[ConditionIdeaTrustPoint] = Bdat::getMember(wrapper.unknown00, "TrustPoint"); }

u32 getConditionIdeaTrustPoint(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionIdeaTrustPoint] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionIdeaTrustPoint], id, 2).valueU16;
}

void initConditionLevelPCID(const CBdatWrapper &wrapper) { s_members[ConditionLevelPCID] = Bdat::getMember(wrapper.unknown00, "PCID"); }

u32 getConditionLevelPCID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionLevelPCID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionLevelPCID], id, 2).valueU16;
}

void initConditionLevelLevel(const CBdatWrapper &wrapper) { s_members[ConditionLevelLevel] = Bdat::getMember(wrapper.unknown00, "Level"); }

u32 getConditionLevelLevel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionLevelLevel] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionLevelLevel], id, 1).valueU8;
}

void initConditionAchievementAchievementSetID(const CBdatWrapper &wrapper) {
  s_members[ConditionAchievementAchievementSetID] = Bdat::getMember(wrapper.unknown00, "AchievementSetID");
}

u32 getConditionAchievementAchievementSetID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionAchievementAchievementSetID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionAchievementAchievementSetID], id, 2).valueU16;
}

void initConditionAchievementValue(const CBdatWrapper &wrapper) { s_members[ConditionAchievementValue] = Bdat::getMember(wrapper.unknown00, "Value"); }

u32 getConditionAchievementValue(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionAchievementValue] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionAchievementValue], id, 1).valueU8;
}

void initConditionFieldSkiiLevelFieldSkillID(const CBdatWrapper &wrapper) {
  s_members[ConditionFieldSkiiLevelFieldSkillID] = Bdat::getMember(wrapper.unknown00, "FieldSkillID");
}

u32 getConditionFieldSkiiLevelFieldSkillID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionFieldSkiiLevelFieldSkillID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionFieldSkiiLevelFieldSkillID], id, 2).valueU16;
}

void initConditionFieldSkiiLevelLevel(const CBdatWrapper &wrapper) {
  s_members[ConditionFieldSkiiLevelLevel] = Bdat::getMember(wrapper.unknown00, "Level");
}

u32 getConditionFieldSkiiLevelLevel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionFieldSkiiLevelLevel] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionFieldSkiiLevelLevel], id, 1).valueU8;
}

} // namespace _gfbdb

GfBdatCond::GfBdatCond()
    : m_conditionList(nullptr), m_conditionScenario(nullptr), m_conditionQuest(nullptr), m_conditionEnv(nullptr), m_conditionFlag(nullptr),
      m_conditionItem(nullptr), m_conditionPT(nullptr), m_conditionIdea(nullptr), m_conditionLevel(nullptr), m_conditionAchievement(nullptr),
      m_conditionFieldSkiiLevel(nullptr) {
  bdatRefresh();
}

GfBdatCond::~GfBdatCond() { destroyFP(); }

void GfBdatCond::destroyFP() {
  if (m_conditionList != nullptr) {
    delete m_conditionList;
    m_conditionList = nullptr;
  }

  if (m_conditionScenario != nullptr) {
    delete m_conditionScenario;
    m_conditionScenario = nullptr;
  }

  if (m_conditionQuest != nullptr) {
    delete m_conditionQuest;
    m_conditionQuest = nullptr;
  }

  if (m_conditionEnv != nullptr) {
    delete m_conditionEnv;
    m_conditionEnv = nullptr;
  }

  if (m_conditionFlag != nullptr) {
    delete m_conditionFlag;
    m_conditionFlag = nullptr;
  }

  if (m_conditionItem != nullptr) {
    delete m_conditionItem;
    m_conditionItem = nullptr;
  }

  if (m_conditionPT != nullptr) {
    delete m_conditionPT;
    m_conditionPT = nullptr;
  }

  if (m_conditionIdea != nullptr) {
    delete m_conditionIdea;
    m_conditionIdea = nullptr;
  }

  if (m_conditionLevel != nullptr) {
    delete m_conditionLevel;
    m_conditionLevel = nullptr;
  }

  if (m_conditionAchievement != nullptr) {
    delete m_conditionAchievement;
    m_conditionAchievement = nullptr;
  }

  if (m_conditionFieldSkiiLevel != nullptr) {
    delete m_conditionFieldSkiiLevel;
    m_conditionFieldSkiiLevel = nullptr;
  }
}

#define NEW_BDAT_WRAPPER(bdat)                                                                                                                       \
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper { GfDataBdat::getFP(bdat) }

void GfBdatCond::createFP() {
  m_conditionList = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_LIST);
  m_conditionScenario = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_SCENARIO);
  m_conditionQuest = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_QUEST);
  m_conditionEnv = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_ENV);
  m_conditionFlag = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_FLAG);
  m_conditionItem = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_ITEM);
  m_conditionPT = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_PT);
  m_conditionIdea = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_IDEA);
  m_conditionLevel = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_LEVEL);
  m_conditionAchievement = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_ACHIEVEMENT);
  m_conditionFieldSkiiLevel = NEW_BDAT_WRAPPER(BDAT_FLD_CONDITION_FIELD_SKII_LEVEL);
}

void GfBdatCond::bdatRefresh() {
  destroyFP();
  createFP();
  _gfbdb::initConditionListPremise(*m_conditionList);
  _gfbdb::initConditionListConditionType1(*m_conditionList);
  _gfbdb::initConditionListCondition1(*m_conditionList);
  _gfbdb::initConditionListConditionType2(*m_conditionList);
  _gfbdb::initConditionListCondition2(*m_conditionList);
  _gfbdb::initConditionListConditionType3(*m_conditionList);
  _gfbdb::initConditionListCondition3(*m_conditionList);
  _gfbdb::initConditionListConditionType4(*m_conditionList);
  _gfbdb::initConditionListCondition4(*m_conditionList);
  _gfbdb::initConditionListConditionType5(*m_conditionList);
  _gfbdb::initConditionListCondition5(*m_conditionList);
  _gfbdb::initConditionListConditionType6(*m_conditionList);
  _gfbdb::initConditionListCondition6(*m_conditionList);
  _gfbdb::initConditionListConditionType7(*m_conditionList);
  _gfbdb::initConditionListCondition7(*m_conditionList);
  _gfbdb::initConditionListConditionType8(*m_conditionList);
  _gfbdb::initConditionListCondition8(*m_conditionList);
  _gfbdb::initConditionScenarioScenarioMin(*m_conditionScenario);
  _gfbdb::initConditionScenarioScenarioMax(*m_conditionScenario);
  _gfbdb::initConditionScenarioNotScenarioMin(*m_conditionScenario);
  _gfbdb::initConditionScenarioNotScenarioMax(*m_conditionScenario);
  _gfbdb::initConditionQuestQuestFlag1(*m_conditionQuest);
  _gfbdb::initConditionQuestQuestFlagMin1(*m_conditionQuest);
  _gfbdb::initConditionQuestQuestFlagMax1(*m_conditionQuest);
  _gfbdb::initConditionQuestQuestFlag2(*m_conditionQuest);
  _gfbdb::initConditionQuestQuestFlagMin2(*m_conditionQuest);
  _gfbdb::initConditionQuestQuestFlagMax2(*m_conditionQuest);
  _gfbdb::initConditionQuestNotQuestFlag1(*m_conditionQuest);
  _gfbdb::initConditionQuestNotQuestFlagMin1(*m_conditionQuest);
  _gfbdb::initConditionQuestNotQuestFlagMax1(*m_conditionQuest);
  _gfbdb::initConditionQuestNotQuestFlag2(*m_conditionQuest);
  _gfbdb::initConditionQuestNotQuestFlagMin2(*m_conditionQuest);
  _gfbdb::initConditionQuestNotQuestFlagMax2(*m_conditionQuest);
  _gfbdb::initConditionEnvTimeRange(*m_conditionEnv);
  _gfbdb::initConditionEnvWeather(*m_conditionEnv);
  _gfbdb::initConditionEnvCloudHeight(*m_conditionEnv);
  _gfbdb::initConditionFlagFlagType(*m_conditionFlag);
  _gfbdb::initConditionFlagFlagID(*m_conditionFlag);
  _gfbdb::initConditionFlagFlagMin(*m_conditionFlag);
  _gfbdb::initConditionFlagFlagMax(*m_conditionFlag);
  _gfbdb::initConditionItemItemCategory(*m_conditionItem);
  _gfbdb::initConditionItemItemID(*m_conditionItem);
  _gfbdb::initConditionItemNumber(*m_conditionItem);
  _gfbdb::initConditionPTCategory(*m_conditionPT);
  _gfbdb::initConditionPTPCID1(*m_conditionPT);
  _gfbdb::initConditionPTPCID2(*m_conditionPT);
  _gfbdb::initConditionPTPCID3(*m_conditionPT);
  _gfbdb::initConditionIdeaPCID(*m_conditionIdea);
  _gfbdb::initConditionIdeaIdeaLevelBlue(*m_conditionIdea);
  _gfbdb::initConditionIdeaIdeaLevelRed(*m_conditionIdea);
  _gfbdb::initConditionIdeaIdeaLevelWhite(*m_conditionIdea);
  _gfbdb::initConditionIdeaIdeaLevelBlack(*m_conditionIdea);
  _gfbdb::initConditionIdeaCompatibility(*m_conditionIdea);
  _gfbdb::initConditionIdeaTrustPoint(*m_conditionIdea);
  _gfbdb::initConditionLevelPCID(*m_conditionLevel);
  _gfbdb::initConditionLevelLevel(*m_conditionLevel);
  _gfbdb::initConditionAchievementAchievementSetID(*m_conditionAchievement);
  _gfbdb::initConditionAchievementValue(*m_conditionAchievement);
  _gfbdb::initConditionFieldSkiiLevelFieldSkillID(*m_conditionFieldSkiiLevel);
  _gfbdb::initConditionFieldSkiiLevelLevel(*m_conditionFieldSkiiLevel);
}

u32 GfBdatCond::getConditionListStart() const { return Bdat::getIdTop(m_conditionList->unknown00); }

u32 GfBdatCond::getConditionListEnd() const { return Bdat::getIdTop(m_conditionList->unknown00) + Bdat::getIdCount(m_conditionList->unknown00); }

u32 GfBdatCond::getConditionListPremise(u32 id) const { return _gfbdb::getConditionListPremise(*m_conditionList, id); }

u32 GfBdatCond::getConditionListConditionType1(u32 id) const { return _gfbdb::getConditionListConditionType1(*m_conditionList, id); }

u32 GfBdatCond::getConditionListCondition1(u32 id) const { return _gfbdb::getConditionListCondition1(*m_conditionList, id); }

u32 GfBdatCond::getConditionListConditionType2(u32 id) const { return _gfbdb::getConditionListConditionType2(*m_conditionList, id); }

u32 GfBdatCond::getConditionListCondition2(u32 id) const { return _gfbdb::getConditionListCondition2(*m_conditionList, id); }

u32 GfBdatCond::getConditionListConditionType3(u32 id) const { return _gfbdb::getConditionListConditionType3(*m_conditionList, id); }

u32 GfBdatCond::getConditionListCondition3(u32 id) const { return _gfbdb::getConditionListCondition3(*m_conditionList, id); }

u32 GfBdatCond::getConditionListConditionType4(u32 id) const { return _gfbdb::getConditionListConditionType4(*m_conditionList, id); }

u32 GfBdatCond::getConditionListCondition4(u32 id) const { return _gfbdb::getConditionListCondition4(*m_conditionList, id); }

u32 GfBdatCond::getConditionListConditionType5(u32 id) const { return _gfbdb::getConditionListConditionType5(*m_conditionList, id); }

u32 GfBdatCond::getConditionListCondition5(u32 id) const { return _gfbdb::getConditionListCondition5(*m_conditionList, id); }

u32 GfBdatCond::getConditionListConditionType6(u32 id) const { return _gfbdb::getConditionListConditionType6(*m_conditionList, id); }

u32 GfBdatCond::getConditionListCondition6(u32 id) const { return _gfbdb::getConditionListCondition6(*m_conditionList, id); }

u32 GfBdatCond::getConditionListConditionType7(u32 id) const { return _gfbdb::getConditionListConditionType7(*m_conditionList, id); }

u32 GfBdatCond::getConditionListCondition7(u32 id) const { return _gfbdb::getConditionListCondition7(*m_conditionList, id); }

u32 GfBdatCond::getConditionListConditionType8(u32 id) const { return _gfbdb::getConditionListConditionType8(*m_conditionList, id); }

u32 GfBdatCond::getConditionListCondition8(u32 id) const { return _gfbdb::getConditionListCondition8(*m_conditionList, id); }

u32 GfBdatCond::getConditionListConditionType(u32 condition, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionListConditionType1,
                                                              _gfbdb::getConditionListConditionType2,
                                                              _gfbdb::getConditionListConditionType3,
                                                              _gfbdb::getConditionListConditionType4,
                                                              _gfbdb::getConditionListConditionType5,
                                                              _gfbdb::getConditionListConditionType6,
                                                              _gfbdb::getConditionListConditionType7,
                                                              _gfbdb::getConditionListConditionType8};
  return getters[index](*m_conditionList, condition);
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
  return getters[index](*m_conditionList, condition);
}

u32 GfBdatCond::getConditionScenarioStart() const { return Bdat::getIdTop(m_conditionScenario->unknown00); }

u32 GfBdatCond::getConditionScenarioEnd() const { return Bdat::getIdTop(m_conditionScenario->unknown00) + Bdat::getIdCount(m_conditionScenario->unknown00); }

u32 GfBdatCond::getConditionScenarioScenarioMin(u32 id) const { return _gfbdb::getConditionScenarioScenarioMin(*m_conditionScenario, id); }

u32 GfBdatCond::getConditionScenarioScenarioMax(u32 id) const { return _gfbdb::getConditionScenarioScenarioMax(*m_conditionScenario, id); }

u32 GfBdatCond::getConditionScenarioNotScenarioMin(u32 id) const { return _gfbdb::getConditionScenarioNotScenarioMin(*m_conditionScenario, id); }

u32 GfBdatCond::getConditionScenarioNotScenarioMax(u32 id) const { return _gfbdb::getConditionScenarioNotScenarioMax(*m_conditionScenario, id); }

u32 GfBdatCond::getConditionQuestStart() const { return Bdat::getIdTop(m_conditionQuest->unknown00); }

u32 GfBdatCond::getConditionQuestEnd() const { return Bdat::getIdTop(m_conditionQuest->unknown00) + Bdat::getIdCount(m_conditionQuest->unknown00); }

u32 GfBdatCond::getConditionQuestQuestFlag1(u32 id) const { return _gfbdb::getConditionQuestQuestFlag1(*m_conditionQuest, id); }

u32 GfBdatCond::getConditionQuestQuestFlagMin1(u32 id) const { return _gfbdb::getConditionQuestQuestFlagMin1(*m_conditionQuest, id); }

u32 GfBdatCond::getConditionQuestQuestFlagMax1(u32 id) const { return _gfbdb::getConditionQuestQuestFlagMax1(*m_conditionQuest, id); }

u32 GfBdatCond::getConditionQuestQuestFlag2(u32 id) const { return _gfbdb::getConditionQuestQuestFlag2(*m_conditionQuest, id); }

u32 GfBdatCond::getConditionQuestQuestFlagMin2(u32 id) const { return _gfbdb::getConditionQuestQuestFlagMin2(*m_conditionQuest, id); }

u32 GfBdatCond::getConditionQuestQuestFlagMax2(u32 id) const { return _gfbdb::getConditionQuestQuestFlagMax2(*m_conditionQuest, id); }

u32 GfBdatCond::getConditionQuestNotQuestFlag1(u32 id) const { return _gfbdb::getConditionQuestNotQuestFlag1(*m_conditionQuest, id); }

u32 GfBdatCond::getConditionQuestNotQuestFlagMin1(u32 id) const { return _gfbdb::getConditionQuestNotQuestFlagMin1(*m_conditionQuest, id); }

u32 GfBdatCond::getConditionQuestNotQuestFlagMax1(u32 id) const { return _gfbdb::getConditionQuestNotQuestFlagMax1(*m_conditionQuest, id); }

u32 GfBdatCond::getConditionQuestNotQuestFlag2(u32 id) const { return _gfbdb::getConditionQuestNotQuestFlag2(*m_conditionQuest, id); }

u32 GfBdatCond::getConditionQuestNotQuestFlagMin2(u32 id) const { return _gfbdb::getConditionQuestNotQuestFlagMin2(*m_conditionQuest, id); }

u32 GfBdatCond::getConditionQuestNotQuestFlagMax2(u32 id) const { return _gfbdb::getConditionQuestNotQuestFlagMax2(*m_conditionQuest, id); }

u32 GfBdatCond::getConditionQuestQuestFlag(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionQuestQuestFlag1, _gfbdb::getConditionQuestQuestFlag2};
  return getters[index](*m_conditionQuest, id);
}

u32 GfBdatCond::getConditionQuestQuestFlagMin(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionQuestQuestFlagMin1, _gfbdb::getConditionQuestQuestFlagMin2};
  return getters[index](*m_conditionQuest, id);
}

u32 GfBdatCond::getConditionQuestQuestFlagMax(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionQuestQuestFlagMax1, _gfbdb::getConditionQuestQuestFlagMax2};
  return getters[index](*m_conditionQuest, id);
}

u32 GfBdatCond::getConditionQuestNotQuestFlag(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionQuestNotQuestFlag1, _gfbdb::getConditionQuestNotQuestFlag2};
  return getters[index](*m_conditionQuest, id);
}

u32 GfBdatCond::getConditionQuestNotQuestFlagMin(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionQuestNotQuestFlagMin1, _gfbdb::getConditionQuestNotQuestFlagMin2};
  return getters[index](*m_conditionQuest, id);
}

u32 GfBdatCond::getConditionQuestNotQuestFlagMax(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionQuestNotQuestFlagMax1, _gfbdb::getConditionQuestNotQuestFlagMax2};
  return getters[index](*m_conditionQuest, id);
}

u32 GfBdatCond::getConditionEnvStart() const { return Bdat::getIdTop(m_conditionEnv->unknown00); }

u32 GfBdatCond::getConditionEnvEnd() const { return Bdat::getIdTop(m_conditionEnv->unknown00) + Bdat::getIdCount(m_conditionEnv->unknown00); }

u32 GfBdatCond::getConditionEnvTimeRange(u32 id) const { return _gfbdb::getConditionEnvTimeRange(*m_conditionEnv, id); }

u32 GfBdatCond::getConditionEnvWeather(u32 id) const { return _gfbdb::getConditionEnvWeather(*m_conditionEnv, id); }

u32 GfBdatCond::getConditionEnvCloudHeight(u32 id) const { return _gfbdb::getConditionEnvCloudHeight(*m_conditionEnv, id); }

u32 GfBdatCond::getConditionFlagStart() const { return Bdat::getIdTop(m_conditionFlag->unknown00); }

u32 GfBdatCond::getConditionFlagEnd() const { return Bdat::getIdTop(m_conditionFlag->unknown00) + Bdat::getIdCount(m_conditionFlag->unknown00); }

u32 GfBdatCond::getConditionFlagFlagType(u32 id) const { return _gfbdb::getConditionFlagFlagType(*m_conditionFlag, id); }

u32 GfBdatCond::getConditionFlagFlagID(u32 id) const { return _gfbdb::getConditionFlagFlagID(*m_conditionFlag, id); }

u32 GfBdatCond::getConditionFlagFlagMin(u32 id) const { return _gfbdb::getConditionFlagFlagMin(*m_conditionFlag, id); }

u32 GfBdatCond::getConditionFlagFlagMax(u32 id) const { return _gfbdb::getConditionFlagFlagMax(*m_conditionFlag, id); }

u32 GfBdatCond::getConditionItemStart() const { return Bdat::getIdTop(m_conditionItem->unknown00); }

u32 GfBdatCond::getConditionItemEnd() const { return Bdat::getIdTop(m_conditionItem->unknown00) + Bdat::getIdCount(m_conditionItem->unknown00); }

u32 GfBdatCond::getConditionItemItemCategory(u32 id) const { return _gfbdb::getConditionItemItemCategory(*m_conditionItem, id); }

u32 GfBdatCond::getConditionItemItemID(u32 id) const { return _gfbdb::getConditionItemItemID(*m_conditionItem, id); }

u32 GfBdatCond::getConditionItemNumber(u32 id) const { return _gfbdb::getConditionItemNumber(*m_conditionItem, id); }

u32 GfBdatCond::getConditionPTStart() const { return Bdat::getIdTop(m_conditionPT->unknown00); }

u32 GfBdatCond::getConditionPTEnd() const { return Bdat::getIdTop(m_conditionPT->unknown00) + Bdat::getIdCount(m_conditionPT->unknown00); }

u32 GfBdatCond::getConditionPTCategory(u32 id) const { return _gfbdb::getConditionPTCategory(*m_conditionPT, id); }

u32 GfBdatCond::getConditionPTPCID1(u32 id) const { return _gfbdb::getConditionPTPCID1(*m_conditionPT, id); }

u32 GfBdatCond::getConditionPTPCID2(u32 id) const { return _gfbdb::getConditionPTPCID2(*m_conditionPT, id); }

u32 GfBdatCond::getConditionPTPCID3(u32 id) const { return _gfbdb::getConditionPTPCID3(*m_conditionPT, id); }

u32 GfBdatCond::getConditionPTPCID(u32 condition, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionPTPCID1, _gfbdb::getConditionPTPCID2, _gfbdb::getConditionPTPCID3};
  return getters[index](*m_conditionPT, condition);
}

u32 GfBdatCond::getConditionIdeaStart() const { return Bdat::getIdTop(m_conditionIdea->unknown00); }

u32 GfBdatCond::getConditionIdeaEnd() const { return Bdat::getIdTop(m_conditionIdea->unknown00) + Bdat::getIdCount(m_conditionIdea->unknown00); }

u32 GfBdatCond::getConditionIdeaPCID(u32 id) const { return _gfbdb::getConditionIdeaPCID(*m_conditionIdea, id); }

u32 GfBdatCond::getConditionIdeaIdeaLevelBlue(u32 id) const { return _gfbdb::getConditionIdeaIdeaLevelBlue(*m_conditionIdea, id); }

u32 GfBdatCond::getConditionIdeaIdeaLevelRed(u32 id) const { return _gfbdb::getConditionIdeaIdeaLevelRed(*m_conditionIdea, id); }

u32 GfBdatCond::getConditionIdeaIdeaLevelWhite(u32 id) const { return _gfbdb::getConditionIdeaIdeaLevelWhite(*m_conditionIdea, id); }

u32 GfBdatCond::getConditionIdeaIdeaLevelBlack(u32 id) const { return _gfbdb::getConditionIdeaIdeaLevelBlack(*m_conditionIdea, id); }

u32 GfBdatCond::getConditionIdeaCompatibility(u32 id) const { return _gfbdb::getConditionIdeaCompatibility(*m_conditionIdea, id); }

u32 GfBdatCond::getConditionIdeaTrustPoint(u32 id) const { return _gfbdb::getConditionIdeaTrustPoint(*m_conditionIdea, id); }

u32 GfBdatCond::getConditionIdeaIdeaLevel(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbdb::getConditionIdeaIdeaLevelBlue,
                                                              _gfbdb::getConditionIdeaIdeaLevelRed,
                                                              _gfbdb::getConditionIdeaIdeaLevelWhite,
                                                              _gfbdb::getConditionIdeaIdeaLevelBlack};
  return getters[index](*m_conditionIdea, id);
}

u32 GfBdatCond::getConditionLevelStart() const { return Bdat::getIdTop(m_conditionLevel->unknown00); }

u32 GfBdatCond::getConditionLevelEnd() const { return Bdat::getIdTop(m_conditionLevel->unknown00) + Bdat::getIdCount(m_conditionLevel->unknown00); }

u32 GfBdatCond::getConditionLevelPCID(u32 id) const { return _gfbdb::getConditionLevelPCID(*m_conditionLevel, id); }

u32 GfBdatCond::getConditionLevelLevel(u32 id) const { return _gfbdb::getConditionLevelLevel(*m_conditionLevel, id); }

u32 GfBdatCond::getConditionAchievementStart() const { return Bdat::getIdTop(m_conditionAchievement->unknown00); }

u32 GfBdatCond::getConditionAchievementEnd() const {
  return Bdat::getIdTop(m_conditionAchievement->unknown00) + Bdat::getIdCount(m_conditionAchievement->unknown00);
}

u32 GfBdatCond::getConditionAchievementAchievementSetID(u32 id) const {
  return _gfbdb::getConditionAchievementAchievementSetID(*m_conditionAchievement, id);
}

u32 GfBdatCond::getConditionAchievementValue(u32 id) const { return _gfbdb::getConditionAchievementValue(*m_conditionAchievement, id); }

u32 GfBdatCond::getConditionFieldSkiiLevelStart() const { return Bdat::getIdTop(m_conditionFieldSkiiLevel->unknown00); }

u32 GfBdatCond::getConditionFieldSkiiLevelEnd() const {
  return Bdat::getIdTop(m_conditionFieldSkiiLevel->unknown00) + Bdat::getIdCount(m_conditionFieldSkiiLevel->unknown00);
}

u32 GfBdatCond::getConditionFieldSkiiLevelFieldSkillID(u32 id) const {
  return _gfbdb::getConditionFieldSkiiLevelFieldSkillID(*m_conditionFieldSkiiLevel, id);
}

u32 GfBdatCond::getConditionFieldSkiiLevelLevel(u32 id) const { return _gfbdb::getConditionFieldSkiiLevelLevel(*m_conditionFieldSkiiLevel, id); }

} // namespace gf
