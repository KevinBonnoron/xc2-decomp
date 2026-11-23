#include "gmk/gmk_climbing.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "bdat.h"
#include "fw/fw_coli_check.h"
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

constexpr int WILDCARD_UNKNOWN_37 = 37; // Inferred role: wildcard climbing icon height row; original name unknown.

void GmkClimbing::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  m_scenarioFlagCond = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_UNKNOWN_2), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_UNKNOWN_2));
  m_questFlagCond =
      QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_UNKNOWN_2), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_UNKNOWN_1), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_UNKNOWN_1));
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_UNKNOWN_2);
  m_bootedGmkCond = BootedGmkCond(bdat, id, "OP_");
  unknown02 = bdat.getValCheck("climiconRadius", id, BDAT_TYPE_UNKNOWN_2);
}

bool GmkClimbing::BdatInfo::isPopCondMatched() const {
  if (m_scenarioFlagCond.isEnable() && !m_scenarioFlagCond.isMatch()) {
    return false;
  }
  if (m_questFlagCond.isEnable() && !m_questFlagCond.isMatch()) {
    return false;
  }
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  if (m_bootedGmkCond.isEnable() && !m_bootedGmkCond.isMatch()) {
    return false;
  }
  return true;
}

GmkType GmkClimbing::getGmkType() const { return GMK_TYPE; }

// The game's updateIconPos (0x710061cfa0, called from nowhere else in the binary) is what create inlines at 0x710061cf0c. Defined inline
// because the out-of-line copy does not match: it only differs in the operand order of the fadd (fadd s0, s1, s0 in the game, fadd s0, s0, s1
// here; 98 permuter candidates and the source orders found nothing). The standalone copy stays a target (check lists it as TODO).
inline void GmkClimbing::updateIconPos() {
  unknown50 = m_createBaseInfo.m_xform->unknown00;
  unknown50.y += Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_FLD_WILDCARD_DATA), 0, WILDCARD_UNKNOWN_37, BDAT_TYPE_UNKNOWN_8).valueF32;
}

void GmkClimbing::create(const CreateInfo &info) {
  updateIconPos();
  AGmkBase::create(info);
}

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
  param.unknown00 = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_FLD_WILDCARD_DATA), 1, unknown001, BDAT_TYPE_UNKNOWN_2).valueU16;
  param.unknown10 = unknown50;
  gf::GfMenuObjFieldIcon::open(unknown48, param);
}

// The game inlines gmk::isPointBehindGround (0x71005e4344, matched in gmk_manager.cpp, called from nowhere) here: 59 instructions. The call form compiles to 16 instructions
// (`disp(unknown48, !isPointBehindGround(unknown50))`; 18 with a `bool isBehind` local): the inliner costs the callee at 275 against its threshold of 275
// (-Rpass-analysis=inline) wherever it is defined in the unit (before or after the callers, isCameraExist and
// getCameraPos before or after it), and defining it inline would inline it but stop emitting its matching standalone copy. The body is therefore written out again (ruling 8,
// measured above). The callee's parameter is bound to a local reference before the camera test: the game computes &unknown50 once, in x20, and keeps it across the two
// getCam calls, as it does for an inlined argument (without the reference the address is computed after them: 58 instructions); the flag set by the camera test is
// inverted after the join, where the game's eor is, not inside the test.
void GmkClimbing::updateIcon() {
  if (unknown48 == nullptr) {
    return;
  }
  bool isBehind = false;
  const mm::Vec3 &position = unknown50;
  if (isCameraExist()) {
    fw::TColiCheckResult<256> result;
    result.clear();
    mm::Vec3 start = getCameraPos();
    fw::ColiCheckConfig config;
    config.unknown08 = 0.0f;
    config.unknown0c = 0.0f;
    config.unknown14 = false;
    config.unknown15 = false;
    config.unknown00 = fw::ColiCheckConfig::FLAG_UNKNOWN_0 | fw::ColiCheckConfig::FLAG_UNKNOWN_3;
    config.unknown10 = 0;
    config.unknown04 = 0x80000020;
    isBehind = fw::ColiCheck::testLineChara(result, start, position, config);
  }
  gf::GfMenuObjFieldIcon::disp(unknown48, !isBehind);
}

bool GmkClimbing::isPopCondMatched() const {
  const BdatInfo *info = getBdatInfo();
  if (!info->isPopCondMatched()) {
    return false;
  }
  const mm::Vec3 &interestPos = getInterestPos();
  const mm::Vec3 &position = m_createBaseInfo.m_xform->unknown00;
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
template void mm::mtl::Vector<gmk::GmkClimbing>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkClimbing>::resize(size_t);
