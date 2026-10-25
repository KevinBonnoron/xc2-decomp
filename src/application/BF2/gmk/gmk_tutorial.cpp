#include "gmk/gmk_tutorial.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/gf_game_manager.h"
#include "gmk/gmk_bdat.h"
#include <string.h>

namespace gmk {

bool GmkTutorial::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

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

GmkType GmkTutorial::getGmkType() const { return GMK_TYPE; }

void GmkTutorial::updateInActiveList(f32 deltaTime) {
  if (unknownE3 && gf::GfGameFlag::getLocal(1, getGameFlagId()) == 0 && gf::GfGameManager::isGmkTutorialOK()) {
    beginTutorial();
  }
}

void GmkTutorial::create(const CreateInfo &info) { AGmkBase::create(info); }

void GmkTutorial::dispose() {
  unknownF0 = false;
  disposeGmkPhantom();
  AGmkBase::dispose();
}

int GmkTutorial::getGameFlagId() const { return unknown20.unknown18 + 0xd392; }

bool GmkTutorial::isBooted() const { return gf::GfGameFlag::getLocal(1, getGameFlagId()) != 0; }

void GmkTutorial::setBooted() const { gf::GfGameFlag::setLocal(1, getGameFlagId(), 1); }

void GmkTutorialList::setBootedOthers(const GmkTutorial &gmk) const {
  const GmkTutorial::Data *data = gmk.getData();
  if (data->unknown00 != nullptr) {
    u32 num = getInstNum();
    for (u32 i = 0; i < num; i++) {
      const GmkTutorial *other = static_cast<const GmkTutorial *>(getInst(i));
      if (other != nullptr && other->isValid()) {
        const GmkTutorial::Data *otherData = other->getData();
        if (otherData->unknown00 != nullptr && strcmp(data->unknown00, otherData->unknown00) == 0 && data->unknown08 == otherData->unknown08) {
          gf::GfGameFlag::setLocal(1, other->getGameFlagId(), 1);
        }
      }
    }
  }
}

} // namespace gmk
