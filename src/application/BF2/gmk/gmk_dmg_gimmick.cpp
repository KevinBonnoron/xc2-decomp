#include "gmk/gmk_dmg_gimmick.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkDmgGimmick::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  condition = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  depopBootedGmk = BootedGmkCond(bdat, id, "DEPOP_");
  depopCondition = bdat.getValCheck("DEPOP_Condition", id, BDAT_TYPE_U16);
  damageInterval = toBdatF32(bdat.getValCheck("DMG_interval", id, BDAT_TYPE_F32));
  pcDamage = bdat.getValCheck("Pc_dmg", id, BDAT_TYPE_U8);
  enemyDamage = bdat.getValCheck("EN_dmg", id, BDAT_TYPE_U8);
  effectName = reinterpret_cast<const char *>(bdat.getValCheck("effect_name", id, BDAT_TYPE_STRING));
  seName = bdat.getValCheck("SE_name", id, BDAT_TYPE_U8);
  volumeMax = bdat.getValCheck("volumeMAX", id, BDAT_TYPE_U8);
  volumeMin = bdat.getValCheck("volumeMIN", id, BDAT_TYPE_U8);
  u16 effectDispRadius = bdat.getValCheck("effect_disp_r", id, BDAT_TYPE_U16);
  effectDispDist.distSq = static_cast<f32>(effectDispRadius) * static_cast<f32>(effectDispRadius);
  u8 effectReleaseRadius = bdat.getValCheck("effect_release_r", id, BDAT_TYPE_U8);
  f32 effectReleaseDistance = effectDispRadius + effectReleaseRadius;
  effectReleaseDist.distSq = effectReleaseDistance * effectReleaseDistance;
}

bool GmkDmgGimmick::BdatInfo::isCondMatched() const {
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  if (depopBootedGmk.isEnable() && depopBootedGmk.isMatch()) {
    return false;
  }
  if (depopCondition != 0 && gf::GfGameCond::isGameCond(depopCondition)) {
    return false;
  }
  return true;
}

} // namespace gmk
