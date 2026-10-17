#include "gmk/gmk_kizuna_talk.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_cond.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

constexpr int WILDCARD_KIZUNA_TALK_POP_DIST_ROW = 30;

void GmkKizunaTalk::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  condition = bdat.getValCheck("ConditionID", id, BDAT_TYPE_U16);
  title = bdat.getValCheck("Title", id, BDAT_TYPE_U16);
  eventCondition = bdat.getValCheck("EVCondition", id, BDAT_TYPE_U16);
}

bool GmkKizunaTalk::BdatInfo::isCondMatched() const {
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  return true;
}

int GmkKizunaTalk::getGameFlagId() const { return createInfo.bdatIndex; }

void GmkKizunaTalk::create(const CreateInfo &info) {
  AGmkBase::create(info);
  f32 popDist = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_FLD_WILDCARD_DATA), 0, WILDCARD_KIZUNA_TALK_POP_DIST_ROW, BDAT_TYPE_F32).valueF32;
  distCond.distSq = popDist * popDist;
}

void GmkKizunaTalk::dispose() {
  disposeGfObjHandle();
  AGmkBase::dispose();
}

void GmkKizunaTalk::disposeGfObjHandle() {
  if (handle != gf::INVALID_HANDLE) {
    unbindToGameObj(handle);
    gf::GfObjUtil::destroy(handle);
    handle = gf::INVALID_HANDLE;
  }
}

void GmkKizunaTalk::update(f32 deltaTime) {
  AGmkBase::update(deltaTime);
  if (!isValid()) {
    return;
  }
  if (getBdatInfo()->isCondMatched() && DistCond::isMatch(distCond.distSq, baseInfo.xform->position)) {
    if (handle == gf::INVALID_HANDLE) {
      createGfObjHandle();
    }
  } else {
    disposeGfObjHandle();
  }
}

void GmkKizunaTalk::debugDraw() const {
  if (!isValid()) {
    return;
  }
  getBdatInfo()->isCondMatched();
}

} // namespace gmk
