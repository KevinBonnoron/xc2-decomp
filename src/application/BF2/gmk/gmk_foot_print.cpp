#include "gmk/gmk_foot_print.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "framework/effect/effect_manager.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_set.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec3.h"

namespace fw {
enum EF_CATEGORY : int;
} // namespace fw

namespace gmk {

template bool TGmkList<GmkRoutedFootPrint, GmkRoutedFootPrint::BdatInfo, 1414547026u, 2u, GmkRoutedFootPrintGobCustom>::initGmkBdatInfo(GmkRoutedFootPrint::BdatInfo &, int &, const AGmkBase &);
template bool TGmkList<GmkRoutedFootPrintPoint, GmkRoutedFootPrintPoint::BdatInfo, 1347438162u, 1u, GmkRoutedFootPrintPointGobCustom>::initGmkBdatInfo(GmkRoutedFootPrintPoint::BdatInfo &, int &,
                                                                                                                                                       const AGmkBase &);

void GmkRoutedFootPrint::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = reinterpret_cast<const char *>(bdat.getValCheck("FootEffect", id, BDAT_TYPE_STRING));
  unknown0a = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  unknown0e = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  unknown08 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
}

bool GmkRoutedFootPrint::BdatInfo::isPopCondMatched() const {
  if (unknown0a.isEnable() && !unknown0a.isMatch()) {
    return false;
  }
  if (unknown0e.isEnable() && !unknown0e.isMatch()) {
    return false;
  }
  if (unknown08 != 0 && !gf::GfGameCond::isGameCond(unknown08)) {
    return false;
  }
  return true;
}

GmkRoutedFootPrint::GmkRoutedFootPrint() : unknown48(nullptr), unknown50(nullptr), unknown58(nullptr) {}

GmkType GmkRoutedFootPrint::getGmkType() const { return GMK_TYPE; }

u32 GmkRoutedFootPrint::getRoutePointNum() const { return getData()->unknown10 - getData()->unknown0c; }

const GmkRoutedFootPrintPointList *GmkRoutedFootPrint::getBindedRoutePointList() const {
  return static_cast<const GmkRoutedFootPrintPointList *>(unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_ROUTED_FOOT_PRINT_POINT]);
}

const GmkRoutedFootPrintPoint *GmkRoutedFootPrint::getRoutePoint(u32 index) const {
  const IGmkList *list = getBindedRoutePointList();
  if (list == nullptr) {
    return nullptr;
  }
  u32 pointIndex = getData()->unknown0c + index;
  if (list->getInstNum() > pointIndex) {
    return static_cast<const GmkRoutedFootPrintPointList *>(list)->unknown001(pointIndex);
  }
  return nullptr;
}

bool GmkRoutedFootPrint::getRoutePointPos(mm::Vec3 &position, u32 index) const {
  const GmkRoutedFootPrintPoint *point = getRoutePoint(index);
  if (point == nullptr || !point->isValid()) {
    return false;
  }
  position = point->getData()->unknown00;
  return true;
}

void GmkRoutedFootPrint::debugDraw() const {
  AGmkBase::debugDraw();
  if (!isValid()) {
    return;
  }
  debugDrawRoute(mm::Col4::yellow);
}

void GmkRoutedFootPrint::debugDraw(bool isSelected) const {
  if (!isValid()) {
    return;
  }
  mm::Col4 color;
  if (isSelected) {
    color = mm::Col4::yellow;
  } else {
    color = mm::Col4::gray;
  }
  debugDrawRoute(color);
}

void GmkRoutedFootPrint::dispose() {
  AGmkBase::dispose();
  unknown50 = nullptr;
  unknown58 = nullptr;
}

GmkRoutedFootPrintPoint::GmkRoutedFootPrintPoint() : unknown50(0), unknown54(true) { unknown48.set(30.0f, 10.0f); }

GmkType GmkRoutedFootPrintPoint::getGmkType() const { return GMK_TYPE; }

bool GmkRoutedFootPrintPoint::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

void GmkRoutedFootPrintPoint::validateDisp() const {
  if (unknown50 == 0) {
    return;
  }
  bool isDisp = unknown54 && debugIsDispGmkType(getGmkType());
  fw::EffectManager::get()->setDisp(unknown50, isDisp);
}

void GmkRoutedFootPrintPoint::createEffInst(void *data) {
  const GmkSet *set = unknown08.unknown00->getCreateInfo().unknown08;
  if (set != nullptr && set->unknown10.unknown24) {
    return;
  }
  if (unknown50 != 0) {
    fw::EffectManager::get()->dead(unknown50);
    unknown50 = 0;
  }
  unknown50 = fw::EffectManager::get()->create(data, true);
  fw::EffectManager::get()->setCategory(unknown50, static_cast<fw::EF_CATEGORY>(1));
  applyEffectParam(false);
}

void GmkRoutedFootPrintPoint::updateConcrete(void *data, f32 deltaTime) {
  debugUpdateMmf();
  if (!isValid()) {
    return;
  }
  u32 effect = unknown50;
  bool isCondMatched = unknown48.isMatch(getData()->unknown00);
  if (effect == 0) {
    if (isCondMatched) {
      createEffInst(data);
    }
  } else if (!isCondMatched) {
    disposeEffInst(false);
  }
}

void GmkRoutedFootPrintPoint::disposeEffInst(bool isFadeOut) {
  if (unknown50 != 0) {
    fw::EffectManager::get()->dead(unknown50);
    unknown50 = 0;
  }
}

void GmkRoutedFootPrintPoint::dispose() {
  disposeEffInst(false);
  unknown20.unknown00 = 0;
  unknown20.unknown08 = nullptr;
  unknown20.unknown10 = nullptr;
}

} // namespace gmk
