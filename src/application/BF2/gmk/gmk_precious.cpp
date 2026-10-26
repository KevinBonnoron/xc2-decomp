#include "gmk/gmk_precious.h"

#include "bdat.h"
#include "framework/effect/effect_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/gf_game_cond.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_field_icon.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/util/gf_item_util.h"
#include "gmk/gmk_bdat.h"
#include "mm_mtl/reference_object.h"

namespace gmk {

GmkPrecious::GmkPrecious() : unknown48(), unknown58(gf::INVALID_HANDLE), unknown60(0), unknown68(nullptr), unknown70{0.0f}, unknown74(true) {}

constexpr int WILDCARD_PRECIOUS_POP_DIST_ROW = 34;

void GmkPrecious::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  dispose();
  unknown00 = bdat.getValCheck("itmID", id, BDAT_TYPE_U16);
  gf::GfItemUtil::isPrecious(unknown00);
  unknown02 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  unknown04 = bdat.getValCheck("QuestID", id, BDAT_TYPE_U16);
  unknown06 = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  unknown0a = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  unknown10.unknown08 = bdat.getValCheck("POP_TIME", id, BDAT_TYPE_U32);
  unknown20.unknown08 = bdat.getValCheck("popWeather", id, BDAT_TYPE_U8);
}

void GmkPrecious::BdatInfo::dispose() { unknown00 = 0; }

bool GmkPrecious::BdatInfo::isPopCondMatched() const {
  if (unknown06.isEnable() && !unknown06.isMatch()) {
    return false;
  }
  if (unknown0a.isEnable() && !unknown0a.isMatch()) {
    return false;
  }
  if (unknown10.isEnable() && !unknown10.isMatch()) {
    return false;
  }
  if (unknown20.isEnable() && !unknown20.isMatch()) {
    return false;
  }
  if (unknown02 != 0 && !gf::GfGameCond::isGameCond(unknown02)) {
    return false;
  }
  return true;
}

GmkType GmkPrecious::getGmkType() const { return GMK_TYPE; }

int GmkPrecious::getGameFlagId() const { return unknown20.unknown18 + 0xb7ef; }

void GmkPrecious::create(const CreateInfo &info) {
  AGmkBase::create(info);
  f32 popDist = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_FLD_WILDCARD_DATA), 0, WILDCARD_PRECIOUS_POP_DIST_ROW, BDAT_TYPE_F32).valueF32;
  unknown70.unknown00 = popDist * popDist;
}

bool GmkPrecious::isObtained() const { return gf::GfGameFlag::getLocal(1, getGameFlagId()) != 0; }

void GmkPrecious::disposeMenuIcon() {
  if (unknown68 != nullptr) {
    gf::GfMenuObjFieldIcon::close(unknown68);
    mm::mtl::safeRelease(unknown68);
  }
}

void GmkPrecious::disposeEffectIcon(bool isFadeOut) {
  if (unknown60 != 0) {
    if (isFadeOut) {
      fw::EffectManager::get()->fadeOutDead(unknown60, 5);
    } else {
      fw::EffectManager::get()->remove(unknown60);
    }
    unknown60 = 0;
  }
}

bool GmkPrecious::isPopCondMatched() const {
  const BdatInfo *info = getBdatInfo();
  if (isObtained() || !info->isPopCondMatched()) {
    return false;
  }
  return DistCond::isMatch(unknown70.unknown00, unknown08.unknown08->unknown00);
}

void GmkPrecious::validateDisp() const {
  bool isDisp = unknown74 && debugIsDispGmkType(getGmkType());
  if (unknown58 != gf::INVALID_HANDLE) {
    setEventDisp(unknown58, isDisp);
  }
  if (unknown60 != 0) {
    fw::EffectManager::get()->setDisp(unknown60, isDisp);
  }
}

void GmkPrecious::debugDraw() const {
  if (!isValid()) {
    return;
  }
  const BdatInfo *info = getBdatInfo();
  if (isObtained() || !info->isPopCondMatched()) {
    return;
  }
  DistCond::isMatch(unknown70.unknown00, unknown08.unknown08->unknown00);
}

} // namespace gmk
