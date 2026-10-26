#include "gmk/gmk_kizuna_talk.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

template bool TGmkList<GmkKizunaTalk, GmkKizunaTalk::BdatInfo, 1414421067u, 1u, GmkKizunaTalkGob>::initGmkBdatInfo(GmkKizunaTalk::BdatInfo &, int &, const AGmkBase &);

constexpr int WILDCARD_KIZUNA_TALK_POP_DIST_ROW = 30;

void GmkKizunaTalk::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("ConditionID", id, BDAT_TYPE_U16);
  unknown02 = bdat.getValCheck("Title", id, BDAT_TYPE_U16);
  unknown04 = bdat.getValCheck("EVCondition", id, BDAT_TYPE_U16);
}

bool GmkKizunaTalk::BdatInfo::isCondMatched() const {
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  return true;
}

int GmkKizunaTalk::getGameFlagId() const { return unknown20.unknown18; }

void GmkKizunaTalk::create(const CreateInfo &info) {
  AGmkBase::create(info);
  f32 popDist = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_FLD_WILDCARD_DATA), 0, WILDCARD_KIZUNA_TALK_POP_DIST_ROW, BDAT_TYPE_F32).valueF32;
  unknown50.unknown00 = popDist * popDist;
}

void GmkKizunaTalk::dispose() {
  disposeGfObjHandle();
  AGmkBase::dispose();
}

void GmkKizunaTalk::disposeGfObjHandle() {
  if (unknown48 != gf::INVALID_HANDLE) {
    unbindToGameObj(unknown48);
    gf::GfObjUtil::destroy(unknown48);
    unknown48 = gf::INVALID_HANDLE;
  }
}

void GmkKizunaTalk::update(f32 deltaTime) {
  AGmkBase::update(deltaTime);
  if (!isValid()) {
    return;
  }
  if (getBdatInfo()->isCondMatched() && DistCond::isMatch(unknown50.unknown00, unknown08.unknown08->unknown00)) {
    if (unknown48 == gf::INVALID_HANDLE) {
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

void GmkKizunaTalk::validateDisp() const {
  bool isDisp = unknown54 && debugIsDispGmkType(getGmkType());
  if (unknown48 == gf::INVALID_HANDLE) {
    return;
  }
  gf::GfObjAcc acc(unknown48);
  if (acc.isValid()) {
    acc.setDisp(gf::OBJDISP_GMK_EVENT, isDisp);
  }
}

void GmkKizunaTalk::onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) {
  disposeGfObjHandle();
  if (getBdatInfo()->unknown04 == 0 || gf::GfGameCond::isGameCond(getBdatInfo()->unknown04)) {
    u16 eventId = Bdat::getValCheck(getBindedBdatFp(), "EventID", unknown20.unknown18, BDAT_TYPE_U16);
    gf::GfPlayFactory::createOneEvent(eventId);
    gf::GfGameFlag::setLocal(2, unknown20.unknown18, 2);
  } else {
    const BdatInfo *bdatInfo = getBdatInfo();
    gf::GfMenuObjCommonText::OpenKizunaParam param = {gf::GfDataBdat::getFP(gf::BDAT_FLD_KIZUNATALKTITLE), bdatInfo->unknown02, bdatInfo->unknown04};
    gf::GfPlayFactory::createMenuObjCommonText(param);
  }
}

} // namespace gmk
