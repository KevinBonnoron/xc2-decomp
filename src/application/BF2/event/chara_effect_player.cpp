#include "event/chara_effect_player.h"

#include "fw/fw_model_object.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "scn/scn_obj_acc.h"

namespace event {

void CharaEffectPlayer::create(gf::GF_OBJ_HANDLE *handle) { this->handle = handle; }

void CharaEffectPlayer::destroy() {
  if (handle == gf::INVALID_HANDLE) {
    if (flags.test(FLAG_AFTER_IMAGE)) {
      stopAfterImage();
    }
    if (flags.test(FLAG_RIM_BLOOM)) {
      stopRimBloom();
    }
    if (flags.test(FLAG_VOLUME_FADE_SUB)) {
      stopVolumeFade(VF_TYPE_SUB);
    }
    if (flags.test(FLAG_VOLUME_FADE_MAIN)) {
      stopVolumeFade(VF_TYPE_MAIN);
    }
  }
  handle = gf::INVALID_HANDLE;
  flags.clear();
}

void CharaEffectPlayer::stopAfterImage() {
  if (handle == gf::INVALID_HANDLE || !flags.test(FLAG_AFTER_IMAGE)) {
    return;
  }

  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj != nullptr) {
    gf::GfComModel *model = obj->getComponent<gf::GfComModel>();
    if (model != nullptr) {
      ml::ScnObjAccResMdlInfo info(model->unknown18->getInterface());
      info.releaseAfterImage();
    }
  }
  flags.set(FLAG_AFTER_IMAGE, false);
}

void CharaEffectPlayer::update(f32 delta) {
  if (gf::GfObjUtil::getObj(handle) == nullptr) {
    return;
  }
  if (flags.test(FLAG_VOLUME_FADE_ANIM_MAIN)) {
    updateVolumeFadeAnim(VF_TYPE_MAIN, delta);
  }
  if (flags.test(FLAG_VOLUME_FADE_ANIM_SUB)) {
    updateVolumeFadeAnim(VF_TYPE_SUB, delta);
  }
}

void CharaEffectPlayer::render(const mm::Vec3 &position, f32 height) {}

} // namespace event
