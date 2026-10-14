#include "gf/data/gf_data_mob.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/util/gf_util.h"

namespace gf {

const char *GfDataMob::getName(u32 mob) { return util::getFilePtrFromPath(GfBdatRsc::get()->getRscMobListModel(mob)); }

bool GfDataMob::getName(u8 *&, u32 &, u32) { return false; }

u8 GfDataMob::getRace(u32 mob) { return GfBdatRsc::get()->getRscMobListRace(mob); }

const char *GfDataMob::getModelName(u32 mob) { return GfBdatRsc::get()->getRscMobListModel(mob); }

const char *GfDataMob::getMotionName(u32 mob) { return GfBdatRsc::get()->getRscMobListMotion(mob); }

const char *GfDataMob::getAddMotionName(u32 mob) {
  const char *addMotionName = GfBdatRsc::get()->getRscMobListAddMotion(mob);
  if (addMotionName == nullptr || addMotionName[0] == '\0') {
    addMotionName = nullptr;
  }

  return addMotionName;
}

const char *GfDataMob::getEffectName(u32 mob) {
  const char *effectName = GfBdatRsc::get()->getRscMobListComp_Eff(mob);
  if (effectName[0] == '\0') {
    effectName = nullptr;
  }

  return effectName;
}

u16 GfDataMob::getFootStep(u32 mob) { return GfBdatRsc::get()->getRscMobListFootStep(mob); }

u8 GfDataMob::getFootStepEffect(u32 mob) { return GfBdatRsc::get()->getRscMobListFootStepEffect(mob); }

} // namespace gf
