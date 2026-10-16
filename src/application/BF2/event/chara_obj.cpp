#include "event/chara_obj.h"

#include "event/skip_manager.h"
#include "gf/event/gf_evt_model.h"
#include "gf/object/gf_obj_acc.h"
#include "mm_mtl/singleton.h"

namespace event {

const mm::Vec3 &CharaObj::getPos() const { return pos; }

f32 CharaObj::getEyeOffset() const { return eyeOffset; }

void CharaObj::renderHead() { cmdPlayHead.render(pos, eyeOffset); }

void CharaObj::renderFacial() { cmdPlayFacial.render(pos, eyeOffset); }

void CharaObj::renderLens() { lensPlayer.render(pos, eyeOffset); }

void CharaObj::renderWeight() { weightPlayer.render(pos, eyeOffset); }

void CharaObj::renderIK() { ikUpdater.render(pos, eyeOffset); }

const mm::Vec3 &CharaObj::getRot() const { return rot; }

void CharaObj::setLensTarget(const mm::Vec2 &target) { lensPlayer.setManualTarget(true, target, true); }

const mm::Vec2 &CharaObj::getLensTarget() const { return lensPlayer.getTarget(); }

bool CharaObj::isFadeOut() const { return (flags & FLAG_FADE_OUT) != 0; }

void CharaObj::playVolumeFade(CharaEffectPlayer::VF_TYPE type, int id, const mm::Vec3 &position, const mm::Vec3 &scale, f32 frame, f32 rate, int mode,
                              f32 speed) {
  effectPlayer.playVolumeFade(type, id, position, scale, frame, rate, mode, speed);
}

void CharaObj::playVolumeFadeAnim(CharaEffectPlayer::VF_TYPE type, f32 rate, f32 frame) { effectPlayer.playVolumeFadeAnim(type, rate, frame); }

void CharaObj::stopVolumeFade(CharaEffectPlayer::VF_TYPE type) { effectPlayer.stopVolumeFade(type); }

void CharaObj::playRimBloom(int id) { effectPlayer.playRimBloom(id); }

void CharaObj::stopRimBloom() { effectPlayer.stopRimBloom(); }

void CharaObj::setExtDisp(const char *name, bool isDisp) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  partUpdater.setExtDisp(name, isDisp);
}

void CharaObj::setExtDispWeapon(const char *name, bool isDisp) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  partUpdater.setExtDispWeapon(name, isDisp);
}

void CharaObj::setExtParam(const char *name, f32 value) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  partUpdater.setExtParam(name, value);
}

void CharaObj::setScaleWeapon(f32 scale) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  weaponScale = scale;
  updateScaleWeapon();
}

void CharaObj::updateScaleWeapon() {
  if (model != nullptr && model->type == gf::GF_EVT_MODEL_WEAPON) {
    static_cast<gf::GfEvtModelWeapon *>(model)->setScale(weaponScale);
  }
}

void CharaObj::setDispJiji(bool isDisp) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (isDisp) {
    flags |= FLAG_DISP_JIJI;
  } else {
    flags &= ~FLAG_DISP_JIJI;
  }
  updateDispJiji();
}

void CharaObj::updateDispJiji() {
  if (model != nullptr && model->type == gf::GF_EVT_MODEL_DRIVER) {
    bool isDisp = (flags & FLAG_DISP_JIJI) != 0;
    if (gf::GfObjAcc(model->handle).getBdatId() == 1 && model != nullptr) {
      static_cast<gf::GfEvtModelDriver *>(model)->setDispJiji(isDisp);
    }
  }
}

} // namespace event
