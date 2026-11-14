#include "gf/object/gf_volume_fade.h"

#include "framework/anim/anim_volume_fade_modifier.h"
#include "framework/effect/effect_manager.h"
#include "framework/effect/volume_fade_params.h"
#include "gf/gf_info.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec3_na.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

GfVolumeFade::GfVolumeFade(GF_OBJ_HANDLE *handle, ml::ScnObjModel *model) : unknown00(handle), unknown08(model) { initializeParam(); }

void GfVolumeFade::initializeParam() {
  for (u32 acc = 0; acc < 5; acc++) {
    for (u32 parts = 0; parts < 6; parts++) {
      unknown14[acc][parts] = 1.0f;
    }
  }
  unknown140 = VFEFF_UNKNOWN_0;
  unknown10 = true;
}

void GfVolumeFade::setEffectType(VFEFF effect) {
  if (unknown140 != effect) {
    unknown140 = effect;
    switch (effect) {
    case VFEFF_UNKNOWN_0:
      break;
    case VFEFF_UNKNOWN_9:
      setupVolumeFadeParamForDead(unknown90, VFEFF_UNKNOWN_9);
      break;
    default:
      setupVolumeFadeParamForDead(unknown90, effect);
      break;
    }
  }
}

bool GfVolumeFade::setupVolumeFadeParamForDead(ml::VolumeFadeParams &params, VFEFF effect) {
  if (effect < fw::EffectManager::unknown005) {
    const fw::VolumeFadeParams *source = fw::EffectManager::get()->m_volumeFadeParam[effect];
    if (source != nullptr) {
      copyVolumeFadeParams(params, *source);
      return true;
    }
  }
  return false;
}

void GfVolumeFade::applyFadeRatio() {
  if (GfObjUtil::isValid(unknown00) && unknown10) {
    unknown10 = false;
    if (unknown140 != VFEFF_UNKNOWN_0) {
      ml::ScnObjAccVolumeFade acc(unknown08);
      MM_VERIFY(acc.getMax());
      for (u32 i = 0; i < fw::AnimVolumeFadeModifier::RATIO_UNKNOWN_6; i++) {
        f32 ratio = getFadeRatioForParts(static_cast<VFPARTS>(i));
        acc.setParams(unknown90, -1);
        GfObj *obj = GfObjUtil::getObj(unknown00);
        if (obj != nullptr) {
          GfComModel *model = obj->getComponent<GfComModel>();
          if (model != nullptr) {
            model->unknown10c8.unknown20[i] = 1.0f - ratio;
          }
        }
      }
    }
  }
}

f32 GfVolumeFade::getFadeRatio(VFACC acc, VFPARTS parts) const {
  if (parts != VFPARTS_UNKNOWN_FFFFFFFF) {
    return unknown14[acc][parts];
  }
  f32 total = 0.0f;
  for (u32 i = 0; i < 6; i++) {
    total += unknown14[acc][i];
  }
  return total / 6.0f;
}

f32 GfVolumeFade::getFadeRatioForParts(VFPARTS parts) const {
  f32 ratio = 1.0f;
  for (u32 acc = 0; acc < 5; acc++) {
    ratio *= getFadeRatio(static_cast<VFACC>(acc), parts);
  }
  return ratio;
}

void GfVolumeFade::copyVolumeFadeParams(ml::VolumeFadeParams &params, const fw::VolumeFadeParams &source) {
  for (u32 i = 0; i < 5; i++) {
    params.unknown00[i] = source.unknown00[i];
    params.unknown60[i] = source.unknown54[i];
    params.unknown74[i] = source.unknown68[i];
    params.unknown88[i] = source.unknown7c[i];
  }
  params.unknown40 = mm::Vec3(source.unknown3c.x, source.unknown3c.y, source.unknown3c.z);
  params.unknown50 = mm::Vec3(source.unknown48.x, source.unknown48.y, source.unknown48.z);
  params.unknown9c = source.unknown90;
  params.unknowna0 = source.unknown94;
  params.unknowna4 = source.unknown98;
}

void GfVolumeFade::setupKeyFrame(mm::mtl::FixedVector<VFKEYDATA, 4> &keys, VFEFF effect) {
  keys.clear();
  if (effect < fw::EffectManager::unknown005) {
    const fw::VolumeFadeParams *source = fw::EffectManager::get()->m_volumeFadeParam[effect];
    if (source != nullptr) {
      u32 count;
      if (source->unknown9c[3] == 0.0f) {
        if (source->unknown9c[2] == 0.0f) {
          if (source->unknown9c[1] == 0.0f) {
            if (source->unknown9c[0] == 0.0f) {
              return;
            }
            count = 1;
          } else {
            count = 2;
          }
        } else {
          count = 3;
        }
      } else {
        count = 4;
      }
      const f32 *time = source->unknown9c;
      const f32 *value = source->unknownac;
      for (; count != 0; time++, value++, count--) {
        VFKEYDATA key;
        key.unknown00 = *time * GfInfo::m_fSecPerFrame;
        key.unknown04 = 1.0f - *value;
        keys.push_back(key);
      }
    }
  }
}

} // namespace gf
