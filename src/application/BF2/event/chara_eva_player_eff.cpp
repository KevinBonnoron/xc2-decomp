#include "event/chara_eva_player_eff.h"

#include "event/chara_effect_player.h"
#include "event/memory_manager.h"
#include "event/skip_manager.h"
#include "gf/event/gf_evt_model.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "rcha/rcha_chr_eff.h"

namespace event {

CharaEvaPlayerEff::CharaEvaPlayerEff() : model(nullptr), effectPlayer(nullptr), rcha(nullptr), frame(0.0f) {}

CharaEvaPlayerEff::~CharaEvaPlayerEff() { stop(); }

void CharaEvaPlayerEff::stop() {
  if (rcha != nullptr) {
    delete rcha;
    rcha = nullptr;
  }
  model = nullptr;
  effectPlayer = nullptr;
}

void CharaEvaPlayerEff::update(f32 delta) {
  if (model == nullptr || gf::GfObjUtil::getObj(model->handle) == nullptr || rcha == nullptr || effectPlayer == nullptr) {
    return;
  }
  f32 speed = mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() ? 1.0f : delta;
  do {
    f32 frame = mm::min(this->frame, rcha->getFrameCount() - 1.0f);
    f32 rest = 0.0f;
    if (speed >= 1.0f) {
      rest = speed - 1.0f;
    }
    if (speed > 1.0f) {
      speed = 1.0f;
    }
    {
      int volumeFade = 0;
      int volumeFadeId = 0;
      mm::Vec3 scale(0.0f, 0.0f, 0.0f);
      mm::Vec3 center(0.0f, 0.0f, 0.0f);
      f32 distance = 0.0f;
      f32 directivity = 0.0f;
      int mesh = 0;
      f32 ratio = 0.0f;
      rcha->getVolumeFade(volumeFade, frame);
      rcha->getVolumeFadeId(volumeFadeId, frame);
      rcha->getVolumeFadeUVWScale(scale, frame);
      rcha->getVolumeFadeCenterPos(center, frame);
      rcha->getVolumeFadeDistance(distance, frame);
      rcha->getVolumeFadeDirectivity(directivity, frame);
      rcha->getVolumeFadeMesh(mesh, frame);
      rcha->getVolumeFadeRatio(ratio, frame);
      if (volumeFade == 0) {
        effectPlayer->stopVolumeFade(CharaEffectPlayer::VF_TYPE_MAIN);
      } else {
        effectPlayer->playVolumeFade(CharaEffectPlayer::VF_TYPE_MAIN, volumeFadeId, scale, center, distance, directivity, mesh, ratio);
      }
    }
    {
      int rimBloom = 0;
      int rimBloomId = 0;
      rcha->getRimBloom(rimBloom, frame);
      rcha->getRimBloomId(rimBloomId, frame);
      if (rimBloom == 1) {
        effectPlayer->playRimBloom(rimBloomId);
      } else if (rimBloom == 2) {
        effectPlayer->stopRimBloom();
      }
    }
    {
      int afterImage = 0;
      int afterImageId1 = 0;
      int afterImageId2 = 0;
      f32 captureFrame = 30.0f;
      f32 existFrame = 15.0f;
      f32 fadeOutFrame = 0.7f;
      rcha->getAfterImage(afterImage, frame);
      rcha->getAfterImageId1(afterImageId1, frame);
      rcha->getAfterImageId2(afterImageId2, frame);
      rcha->getAfterImageCaptureFrame(captureFrame, frame);
      rcha->getAfterImageExistFrame(existFrame, frame);
      rcha->getAfterImageFadeOutFrame(fadeOutFrame, frame);
      if (afterImage == 1) {
        effectPlayer->playAfterImage(afterImageId1, afterImageId2, captureFrame, existFrame, fadeOutFrame);
      } else if (afterImage == 2) {
        effectPlayer->stopAfterImage();
      }
    }
    this->frame += speed;
    if (rcha->getFrameCount() - 1.0f < this->frame) {
      this->frame = rcha->getFrameCount() - 1.0f;
    }
    speed = rest;
  } while (speed > 0.0f);
}

void CharaEvaPlayerEff::play(gf::GfEvtModel *model, CharaEffectPlayer *effectPlayer, void *data) {
  stop();
  this->model = model;
  this->effectPlayer = effectPlayer;
  rcha = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) RchaChrEff;
  rcha->setup(mtl::ALLOC_HANDLE(), data);
  frame = 0.0f;
}

} // namespace event
