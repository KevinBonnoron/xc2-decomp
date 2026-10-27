#include "gf/object/component/effect/gf_effect_ground.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/object/component/effect/gf_com_effect_caster.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/component/property/gf_env_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"

namespace gf {

u32 GfEffectGround::getWaterHeightStateImpl(f32 height, f32 first, f32 second) {
  if (height < first) {
    return 1;
  }
  if (height < second) {
    return 2;
  }
  return 3;
}

bool GfEffectGround::isOnWaterSurface(const GfComEffectCaster *caster) {
  GfComProperty *property = static_cast<GfObj *>(caster->unknown08)->getComponent<GfComProperty>();
  if (property->unknown28 != nullptr) {
    return property->unknown28->unknown2d0 & 1;
  }
  return false;
}

u32 GfEffectGround::getWaterHeightState(const GfComEffectCaster *caster) {
  GfComProperty *property = static_cast<GfObj *>(caster->unknown08)->getComponent<GfComProperty>();
  GfEnvProperty *env = property->unknown28;
  if (env != nullptr && (env->unknown2d0 & 1)) {
    return getWaterHeightStateImpl(env->unknown2b4, caster->unknown24, caster->unknown28);
  }
  return 0;
}

bool GfEffectGround::tryGetWaterDepth(const GfComEffectCaster *caster, const GfCharaWaterInfo *waterInfo, f32 &depth) {
  if (waterInfo != nullptr) {
    GfObjProperty *property = GfObjUtil::getProperty(static_cast<GfObj *>(caster->unknown08)->unknownf8);
    if (property == nullptr) {
      return false;
    }
    if (property->unknown18 != nullptr) {
      depth = waterInfo->unknown00 - property->unknown18->unknown34;
      return true;
    }
  }
  return false;
}

bool GfEffectGround::getGroundEffectFileNameImpl(u32 type, u32 effectType, u32 material, const char *&fileName) {
  fileName = nullptr;
  if (effectType != 0) {
    u8 *surfaceTable = GfDataBdat::getFP(BDAT_FX_ACT_SURFACE_TABLE);
    if (surfaceTable == nullptr) {
      return false;
    }
    u32 surface = Bdat::getVal(surfaceTable, material, type).valueU8;
    u8 *charaTable = GfDataBdat::getFP(BDAT_FX_SURFACE_CHARA_TABLE);
    if (charaTable == nullptr) {
      return false;
    }
    if (surface == 0) {
      return false;
    }
    u32 effect = Bdat::getVal(charaTable, effectType - 1, surface).valueU8;
    if (effect != 0) {
      u8 *fileNameTable = GfDataBdat::getFP(BDAT_FX_FILE_NAME);
      fileName = Bdat::getVal(fileNameTable, "file_name", effect).valueString;
      return fileName != nullptr;
    }
  }
  return false;
}

} // namespace gf
