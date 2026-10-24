#include "gmk/gmk_tutorial.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

constexpr int GAME_FLAG_SYS_MULTI_FLAG = 35322;

void GmkTutorial::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  ScenarioFlagCond minScenarioFlag(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), 0xffff);
  if (minScenarioFlag.unknown00 != 0) {
    unknown02 = minScenarioFlag;
  }
  unknown06 = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  unknown00 = bdat.getValCheck("SysMultiFlag", id, BDAT_TYPE_U8);
}

bool GmkTutorial::BdatInfo::isCondMatched() const {
  if (unknown02.isEnable()) {
    u16 flag = gf::GfDataUtil::getScenarioFlag();
    if (unknown02.unknown00 > flag) {
      return false;
    }
    if (flag > unknown02.unknown02) {
      return false;
    }
  }
  if (unknown06.isEnable() && !unknown06.isMatch()) {
    return false;
  }
  if (unknown00 != 0 && gf::GfGameFlag::getLocal(1, unknown00 + GAME_FLAG_SYS_MULTI_FLAG) == 0) {
    return false;
  }
  return true;
}

} // namespace gmk
