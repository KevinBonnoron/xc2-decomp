#include "gmk/gmk_climbing.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_cond.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_field_icon.h"
#include "gmk/gmk_bdat.h"
#include "mm_mtl/reference_object.h"

namespace gmk {

template bool TGmkList<GmkClimbing, GmkClimbing::BdatInfo, 1112362051u, 2u, GmkClimbingGob>::initGmkBdatInfo(GmkClimbing::BdatInfo &, int &, const AGmkBase &);

void GmkClimbing::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown04 = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  unknown08 = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  unknown0c = BootedGmkCond(bdat, id, "OP_");
  unknown02 = bdat.getValCheck("climiconRadius", id, BDAT_TYPE_U16);
}

bool GmkClimbing::BdatInfo::isPopCondMatched() const {
  if (unknown04.isEnable() && !unknown04.isMatch()) {
    return false;
  }
  if (unknown08.isEnable() && !unknown08.isMatch()) {
    return false;
  }
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  if (unknown0c.isEnable() && !unknown0c.isMatch()) {
    return false;
  }
  return true;
}

GmkType GmkClimbing::getGmkType() const { return GMK_TYPE; }

void GmkClimbing::disposeIcon() {
  if (unknown48 != nullptr) {
    gf::GfMenuObjFieldIcon::close(unknown48);
    mm::mtl::safeRelease(unknown48);
  }
}

void GmkClimbing::dispose() {
  disposeIcon();
  AGmkBase::dispose();
}

void GmkClimbing::update(f32 deltaTime) {
  debugUpdateMmf();
  if (!isValid()) {
    return;
  }
  if (isInterestPosExist()) {
    if (!isPopCondMatched()) {
      disposeIcon();
    } else if (unknown48 == nullptr) {
      createIcon();
    }
  }
  updateIcon();
}

void GmkClimbing::createIcon() {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeIcon();
  unknown48 = gf::GfMenuCallContext::create();
  gf::GfMenuObjFieldIcon::OpenParam param;
  const int unknown001 = 38; // Inferred role: wildcard data column of the climbing icon; original name unknown.
  param.unknown00 = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_FLD_WILDCARD_DATA), 1, unknown001, BDAT_TYPE_U16).valueU16;
  param.unknown10 = unknown50;
  gf::GfMenuObjFieldIcon::open(unknown48, param);
}

bool GmkClimbing::isPopCondMatched() const {
  const BdatInfo *info = getBdatInfo();
  if (!info->isPopCondMatched()) {
    return false;
  }
  const mm::Vec3 &interestPos = getInterestPos();
  const mm::Vec3 &position = unknown08.unknown08->unknown00;
  f32 x = interestPos.x - position.x;
  f32 y = interestPos.y - position.y;
  f32 z = interestPos.z - position.z;
  return x * x + y * y + z * z < static_cast<f32>(info->unknown02 * info->unknown02);
}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkClimbing::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkClimbing>::expand(size_t, size_t);

template void mm::mtl::Vector<gmk::GmkClimbing::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkClimbing::BdatInfo>::resize(size_t);
