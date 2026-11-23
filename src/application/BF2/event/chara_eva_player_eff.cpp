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

CharaEvaPlayerEff::CharaEvaPlayerEff() : unknown08(nullptr), m_charaEffectPlayer(nullptr), m_rchaChrEff(nullptr), unknown20(0.0f) {}

CharaEvaPlayerEff::~CharaEvaPlayerEff() { stop(); }

void CharaEvaPlayerEff::stop() {
  if (m_rchaChrEff != nullptr) {
    delete m_rchaChrEff;
    m_rchaChrEff = nullptr;
  }
  unknown08 = nullptr;
  m_charaEffectPlayer = nullptr;
}

void CharaEvaPlayerEff::update(f32 delta) {
  if (unknown08 == nullptr || gf::GfObjUtil::getObj(unknown08->m_GF_OBJ_HANDLE) == nullptr || m_rchaChrEff == nullptr || m_charaEffectPlayer == nullptr) {
    return;
  }
  f32 speed = mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() ? 1.0f : delta;
  do {
    f32 frame = mm::min(this->unknown20, m_rchaChrEff->getFrameCount() - 1.0f);
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
      m_rchaChrEff->getVolumeFade(volumeFade, frame);
      m_rchaChrEff->getVolumeFadeId(volumeFadeId, frame);
      m_rchaChrEff->getVolumeFadeUVWScale(scale, frame);
      m_rchaChrEff->getVolumeFadeCenterPos(center, frame);
      m_rchaChrEff->getVolumeFadeDistance(distance, frame);
      m_rchaChrEff->getVolumeFadeDirectivity(directivity, frame);
      m_rchaChrEff->getVolumeFadeMesh(mesh, frame);
      m_rchaChrEff->getVolumeFadeRatio(ratio, frame);
      if (volumeFade == 0) {
        m_charaEffectPlayer->stopVolumeFade(CharaEffectPlayer::VF_TYPE_UNKNOWN_0);
      } else {
        m_charaEffectPlayer->playVolumeFade(CharaEffectPlayer::VF_TYPE_UNKNOWN_0, volumeFadeId, scale, center, distance, directivity, mesh, ratio);
      }
    }
    {
      int rimBloom = 0;
      int rimBloomId = 0;
      m_rchaChrEff->getRimBloom(rimBloom, frame);
      m_rchaChrEff->getRimBloomId(rimBloomId, frame);
      if (rimBloom == 1) {
        m_charaEffectPlayer->playRimBloom(rimBloomId);
      } else if (rimBloom == 2) {
        m_charaEffectPlayer->stopRimBloom();
      }
    }
    {
      int afterImage = 0;
      int afterImageId1 = 0;
      int afterImageId2 = 0;
      f32 captureFrame = 30.0f;
      f32 existFrame = 15.0f;
      f32 fadeOutFrame = 0.7f;
      m_rchaChrEff->getAfterImage(afterImage, frame);
      m_rchaChrEff->getAfterImageId1(afterImageId1, frame);
      m_rchaChrEff->getAfterImageId2(afterImageId2, frame);
      m_rchaChrEff->getAfterImageCaptureFrame(captureFrame, frame);
      m_rchaChrEff->getAfterImageExistFrame(existFrame, frame);
      m_rchaChrEff->getAfterImageFadeOutFrame(fadeOutFrame, frame);
      if (afterImage == 1) {
        m_charaEffectPlayer->playAfterImage(afterImageId1, afterImageId2, captureFrame, existFrame, fadeOutFrame);
      } else if (afterImage == 2) {
        m_charaEffectPlayer->stopAfterImage();
      }
    }
    this->unknown20 += speed;
    if (m_rchaChrEff->getFrameCount() - 1.0f < this->unknown20) {
      this->unknown20 = m_rchaChrEff->getFrameCount() - 1.0f;
    }
    speed = rest;
  } while (speed > 0.0f);
}

void CharaEvaPlayerEff::play(gf::GfEvtModel *model, CharaEffectPlayer *effectPlayer, void *data) {
  stop();
  this->unknown08 = model;
  this->m_charaEffectPlayer = effectPlayer;
  m_rchaChrEff = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) RchaChrEff;
  m_rchaChrEff->setup(mtl::ALLOC_HANDLE(), data);
  unknown20 = 0.0f;
}

} // namespace event
