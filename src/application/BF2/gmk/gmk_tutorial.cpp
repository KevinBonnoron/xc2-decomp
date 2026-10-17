#include "gmk/gmk_tutorial.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

constexpr int GAME_FLAG_SYS_MULTI_FLAG = 35322;

void GmkTutorial::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  ScenarioFlagCond minScenarioFlag(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), 0xffff);
  if (minScenarioFlag.min != 0) {
    scenarioFlag = minScenarioFlag;
  }
  questFlag = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16),
                            bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8),
                            bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  sysMultiFlag = bdat.getValCheck("SysMultiFlag", id, BDAT_TYPE_U8);
}

bool GmkTutorial::BdatInfo::isCondMatched() const {
  if (scenarioFlag.isEnable()) {
    u16 flag = gf::GfDataUtil::getScenarioFlag();
    if (scenarioFlag.min > flag) {
      return false;
    }
    if (flag > scenarioFlag.max) {
      return false;
    }
  }
  if (questFlag.isEnable() && !questFlag.isMatch()) {
    return false;
  }
  if (sysMultiFlag != 0 && gf::GfGameFlag::getLocal(1, sysMultiFlag + GAME_FLAG_SYS_MULTI_FLAG) == 0) {
    return false;
  }
  return true;
}

} // namespace gmk
