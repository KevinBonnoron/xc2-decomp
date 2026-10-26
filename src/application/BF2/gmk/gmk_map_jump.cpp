#include "gmk/gmk_map_jump.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/request/gf_req_command.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

template bool TGmkList<GmkMapJump, GmkMapJump::BdatInfo, 1347047501u, 2u, GmkMapJumpGob>::initGmkBdatInfo(GmkMapJump::BdatInfo &, int &, const AGmkBase &);

GmkMapJump::GmkMapJump() : unknown50(nullptr), unknownE0(false), unknownE1(false) {}

void GmkMapJump::debugDraw() const { isValid(); }

void GmkMapJump::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("MapJumpId", id, BDAT_TYPE_U16);
  unknown04 = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  unknown08 = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  unknown02 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
}

bool GmkMapJump::BdatInfo::isCondMatched() const {
  if (unknown04.isEnable() && !unknown04.isMatch()) {
    return false;
  }
  if (unknown08.isEnable() && !unknown08.isMatch()) {
    return false;
  }
  if (unknown02 != 0 && !gf::GfGameCond::isGameCond(unknown02)) {
    return false;
  }
  return true;
}

GmkType GmkMapJump::getGmkType() const { return GMK_TYPE; }

void GmkMapJump::createGmkPhantom() {
  if (canCreateGameEntity()) {
    unknown50.create(*this, nullptr, false);
  }
}

void GmkMapJump::dispose() {
  unknown50.dispose();
  AGmkBase::dispose();
}

void GmkMapJump::update(f32 deltaTime) {
  debugUpdateMmf();
  if (!isValid()) {
    return;
  }
  bool isCondMatched = getBdatInfo()->isCondMatched();
  if (unknownE0 != isCondMatched) {
    if (isCondMatched) {
      createGmkPhantom();
    } else {
      unknown50.dispose();
    }
    unknownE0 = isCondMatched;
  }
  if (unknown50.unknown83) {
    beginEvent();
  } else {
    endEvent();
  }
}

void GmkMapJump::beginEvent() {
  if (!unknownE1 && gf::GfGameManager::isMapjumpOK()) {
    unknownE1 = true;
    gf::GfMapjumpInfo info(getBdatInfo()->unknown00);
    gf::GfPlayFactory::createMapjump(info);
  }
}

void GmkMapJump::endEvent() {
  if (unknownE1) {
    unknownE1 = false;
  }
}

} // namespace gmk
