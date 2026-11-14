#include "event/chara_effect_player.h"

#include "event/chara_manager.h"
#include "event/curve.h"
#include "event/debug_manager.h"
#include "framework/effect/effect_manager.h"
#include "fw/fw_model_object.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/singleton.h"
#include "scn/scn_obj_acc.h"

namespace event {

CharaEffectPlayer::CharaEffectPlayer() : unknown08(0), unknown10(gf::unknown020) {}

void CharaEffectPlayer::create(gf::GF_OBJ_HANDLE *handle) { this->unknown10 = handle; }

void CharaEffectPlayer::destroy() {
  if (unknown10 == gf::unknown020) {
    if (unknown08 & FLAG_UNKNOWN_3) {
      stopAfterImage();
    }
    if (unknown08 & FLAG_UNKNOWN_2) {
      stopRimBloom();
    }
    if (unknown08 & FLAG_UNKNOWN_1) {
      stopVolumeFade(VF_TYPE_UNKNOWN_1);
    }
    if (unknown08 & FLAG_UNKNOWN_0) {
      stopVolumeFade(VF_TYPE_UNKNOWN_0);
    }
  }
  unknown10 = gf::unknown020;
  unknown08 = 0;
}

void CharaEffectPlayer::stopAfterImage() {
  if (unknown10 == gf::unknown020 || !(unknown08 & FLAG_UNKNOWN_3)) {
    return;
  }

  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown10);
  if (obj != nullptr) {
    gf::GfComModel *model = obj->getComponent<gf::GfComModel>();
    if (model != nullptr) {
      ml::ScnObjAccResMdlInfo info(model->unknown18->getInterface());
      info.releaseAfterImage();
    }
  }
  unknown08 &= ~FLAG_UNKNOWN_3;
}

void CharaEffectPlayer::stopVolumeFade(VF_TYPE type) {
  if (unknown10 == gf::unknown020) {
    return;
  }

  u32 fadeFlag = type == VF_TYPE_UNKNOWN_1 ? FLAG_UNKNOWN_1 : FLAG_UNKNOWN_0;
  if (unknown08 & fadeFlag) {
    gf::GfObj *obj = gf::GfObjUtil::getObj(unknown10);
    if (obj != nullptr) {
      gf::GfComModel *model = obj->getComponent<gf::GfComModel>();
      if (model != nullptr) {
        ml::ScnObjAccVolumeFade fade(model->unknown18->getInterface());
        fade.setRatio(0.0f, unknown70[type]);
      }
    }
    unknown08 &= ~fadeFlag;
  }
  unknown80[type].clear();
  unknown08 &= ~(type == VF_TYPE_UNKNOWN_1 ? FLAG_UNKNOWN_5 : FLAG_UNKNOWN_4);
}

void CharaEffectPlayer::update(f32 delta) {
  if (gf::GfObjUtil::getObj(unknown10) == nullptr) {
    return;
  }
  if (unknown08 & FLAG_UNKNOWN_4) {
    updateVolumeFadeAnim(VF_TYPE_UNKNOWN_0, delta);
  }
  if (unknown08 & FLAG_UNKNOWN_5) {
    updateVolumeFadeAnim(VF_TYPE_UNKNOWN_1, delta);
  }
}

void CharaEffectPlayer::updateVolumeFadeAnim(VF_TYPE type, f32 delta) {
  unknown80[type].update(delta);
  unknown78[type] = unknown80[type].getValue();
  if (unknown80[type].isEnd()) {
    unknown08 &= ~(type == VF_TYPE_UNKNOWN_1 ? FLAG_UNKNOWN_5 : FLAG_UNKNOWN_4);
  }
  gf::GfComModel *model = gf::GfObjUtil::getObj(unknown10)->getComponent<gf::GfComModel>();
  ml::VolumeFadeParams params;
  if (fw::EffectManager::get()->getVolumeFadeParam(unknown18[type], params)) {
    params.unknown40 = unknown20[type];
    params.unknown50 = unknown40[type];
    params.unknown9c = unknown60[type];
    params.unknowna0 = unknown68[type];
    if (model != nullptr) {
      ml::ScnObjAccVolumeFade fade(model->unknown18->getInterface());
      fade.setParams(params, unknown70[type]);
      fade.setRatio(unknown78[type], unknown70[type]);
    }
  }
}

void CharaEffectPlayer::render(const mm::Vec3 &position, f32 height) {}

void CharaEffectPlayer::playVolumeFade(VF_TYPE type, int id, const mm::Vec3 &position, const mm::Vec3 &scale, f32 frame, f32 rate, int mode, f32 speed) {
  u32 fadeFlag = type == VF_TYPE_UNKNOWN_1 ? FLAG_UNKNOWN_1 : FLAG_UNKNOWN_0;
  if (((unknown08 & fadeFlag) == 0 || unknown18[type] != id || !(__builtin_fabsf(position.x - unknown20[type].x) <= 1e-6f) || !(__builtin_fabsf(position.y - unknown20[type].y) <= 1e-6f) ||
       !(__builtin_fabsf(position.z - unknown20[type].z) <= 1e-6f) || !(__builtin_fabsf(scale.x - unknown40[type].x) <= 1e-6f) || !(__builtin_fabsf(scale.y - unknown40[type].y) <= 1e-6f) ||
       !(__builtin_fabsf(scale.z - unknown40[type].z) <= 1e-6f) || unknown60[type] != frame || unknown68[type] != rate || unknown70[type] != mode || unknown78[type] != speed) &&
      unknown10 != gf::unknown020) {
    if (!mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode()) {
      gf::GfObjAcc acc(unknown10);
      mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("volumeFade %s %d", acc.getDebugName(), id);
    }
    gf::GfComModel *model = gf::GfObjUtil::getObj(unknown10)->getComponent<gf::GfComModel>();
    ml::VolumeFadeParams params;
    if (fw::EffectManager::get()->getVolumeFadeParam(id, params)) {
      mm::clampRef(rate, 0.0f, 1.0f);
      params.unknown40 = position;
      params.unknown50 = scale;
      params.unknown9c = frame;
      params.unknowna0 = rate;
      if (model != nullptr) {
        ml::ScnObjAccVolumeFade fade(model->unknown18->getInterface());
        // The game calls getMax twice here and ignores the first result.
        fade.getMax();
        mm::clampRef(mode, -1, static_cast<int>(fade.getMax()) - 1);
        mm::clampRef(speed, 0.0f, 1.0f);
        fade.setParams(params, mode);
        fade.setRatio(speed, mode);
      }
      unknown18[type] = id;
      unknown20[type] = position;
      unknown40[type] = scale;
      unknown60[type] = frame;
      unknown68[type] = rate;
      unknown70[type] = mode;
      unknown78[type] = speed;
      unknown08 |= fadeFlag;
    }
  }
}

void CharaEffectPlayer::playVolumeFadeAnim(VF_TYPE type, f32 rate, f32 frame) {
  u32 fadeFlag = type == VF_TYPE_UNKNOWN_1 ? FLAG_UNKNOWN_1 : FLAG_UNKNOWN_0;
  if ((unknown08 & fadeFlag) == 0 || unknown10 == gf::unknown020) {
    return;
  }
  unknown80[type].clear();
  unknown80[type].append(0.0f, unknown78[type], CV_TYPE_UNKNOWN_1);
  unknown80[type].append(frame, rate, CV_TYPE_UNKNOWN_1);
  unknown08 |= type == VF_TYPE_UNKNOWN_1 ? FLAG_UNKNOWN_5 : FLAG_UNKNOWN_4;
}

} // namespace event
