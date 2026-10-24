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

CharaEvaPlayerEff::CharaEvaPlayerEff() : unknown08(nullptr), unknown10(nullptr), unknown18(nullptr), unknown20(0.0f) {}

CharaEvaPlayerEff::~CharaEvaPlayerEff() { stop(); }

void CharaEvaPlayerEff::stop() {
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
  unknown08 = nullptr;
  unknown10 = nullptr;
}

void CharaEvaPlayerEff::update(f32 delta) {
  if (unknown08 == nullptr || gf::GfObjUtil::getObj(unknown08->unknown20) == nullptr || unknown18 == nullptr || unknown10 == nullptr) {
    return;
  }
  f32 speed = mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() ? 1.0f : delta;
  do {
    f32 frame = mm::min(this->unknown20, unknown18->getFrameCount() - 1.0f);
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
      unknown18->getVolumeFade(volumeFade, frame);
      unknown18->getVolumeFadeId(volumeFadeId, frame);
      unknown18->getVolumeFadeUVWScale(scale, frame);
      unknown18->getVolumeFadeCenterPos(center, frame);
      unknown18->getVolumeFadeDistance(distance, frame);
      unknown18->getVolumeFadeDirectivity(directivity, frame);
      unknown18->getVolumeFadeMesh(mesh, frame);
      unknown18->getVolumeFadeRatio(ratio, frame);
      if (volumeFade == 0) {
        unknown10->stopVolumeFade(CharaEffectPlayer::VF_TYPE_MAIN);
      } else {
        unknown10->playVolumeFade(CharaEffectPlayer::VF_TYPE_MAIN, volumeFadeId, scale, center, distance, directivity, mesh, ratio);
      }
    }
    {
      int rimBloom = 0;
      int rimBloomId = 0;
      unknown18->getRimBloom(rimBloom, frame);
      unknown18->getRimBloomId(rimBloomId, frame);
      if (rimBloom == 1) {
        unknown10->playRimBloom(rimBloomId);
      } else if (rimBloom == 2) {
        unknown10->stopRimBloom();
      }
    }
    {
      int afterImage = 0;
      int afterImageId1 = 0;
      int afterImageId2 = 0;
      f32 captureFrame = 30.0f;
      f32 existFrame = 15.0f;
      f32 fadeOutFrame = 0.7f;
      unknown18->getAfterImage(afterImage, frame);
      unknown18->getAfterImageId1(afterImageId1, frame);
      unknown18->getAfterImageId2(afterImageId2, frame);
      unknown18->getAfterImageCaptureFrame(captureFrame, frame);
      unknown18->getAfterImageExistFrame(existFrame, frame);
      unknown18->getAfterImageFadeOutFrame(fadeOutFrame, frame);
      if (afterImage == 1) {
        unknown10->playAfterImage(afterImageId1, afterImageId2, captureFrame, existFrame, fadeOutFrame);
      } else if (afterImage == 2) {
        unknown10->stopAfterImage();
      }
    }
    this->unknown20 += speed;
    if (unknown18->getFrameCount() - 1.0f < this->unknown20) {
      this->unknown20 = unknown18->getFrameCount() - 1.0f;
    }
    speed = rest;
  } while (speed > 0.0f);
}

void CharaEvaPlayerEff::play(gf::GfEvtModel *model, CharaEffectPlayer *effectPlayer, void *data) {
  stop();
  this->unknown08 = model;
  this->unknown10 = effectPlayer;
  unknown18 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) RchaChrEff;
  unknown18->setup(mtl::ALLOC_HANDLE(), data);
  unknown20 = 0.0f;
}

} // namespace event
