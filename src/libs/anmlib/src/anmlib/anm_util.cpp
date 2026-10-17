#include "anm/anm_util.h"

#include "anm/anm_animation.h"
#include "anm/anm_binding.h"
#include "anm/anm_control.h"
#include "anm/anm_res_asm.h"
#include "anm/anm_res_state_data.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_math.h"
#include <math.h>

namespace anm {

static const char *s_layerNames[LAYER_NUM] = {"base", "upperbody", "head", "eye", "mouth", "brow", "extra"};

const char *Util::getName(const Binding &binding) {
  MM_ASSERT(binding.m_pAnimation);
  return binding.m_pAnimation->m_name;
}

s32 Util::getAnimationType(const Binding &binding) { return binding.m_pAnimation->getImplType(); }

PlayMode Util::getPlayMode(const Binding &binding) {
  MM_ASSERT(binding.m_pAnimation);
  return static_cast<PlayMode>(binding.m_pAnimation->m_playMode);
}

u8 Util::getBlendHint(const Binding &binding) {
  MM_ASSERT(binding.m_pAnimation);
  return binding.m_pAnimation->m_blendHint;
}

u32 Util::getFrameCount(const Binding &binding) {
  MM_ASSERT(binding.m_pAnimation);
  return binding.m_pAnimation->m_frameCount;
}

f32 Util::getPlayBackTime(const Binding &binding) {
  const Animation *pAnimation = binding.m_pAnimation;
  MM_ASSERT(pAnimation);
  return pAnimation->m_invFps * (pAnimation->m_frameCount - 1);
}

bool Util::hasLocomotion(const Binding &binding) {
  MM_ASSERT(binding.m_pAnimation);
  return binding.m_pAnimation->m_pLocomotion != nullptr;
}

f32 Util::getFps(const Binding &binding) {
  MM_ASSERT(binding.m_pAnimation);
  return binding.m_pAnimation->m_fps;
}

f32 Util::getInvFps(const Binding &binding) {
  MM_ASSERT(binding.m_pAnimation);
  return binding.m_pAnimation->m_invFps;
}

f32 Util::calcLocalTime(f32 time, f32 start, f32 end, PlayMode playMode) {
  if (playMode == PLAY_MODE_LOOP) {
    return fmodf(time - start, end) + start;
  }
  return mm::clamp(time, start, end);
}

void Util::setKeyFrame(Control &control, f32 frame) { control.setLocalTime(control.m_pBinding->m_pAnimation->m_invFps * frame); }

const char *Util::getLayerName(Layer layer) { return s_layerNames[layer]; }

const ResState *Util::getStateResource(const ResASM &resAsm, const char *name) {
  const ResStateData *resStateData = resAsm.findResStateData(name);
  if (resStateData == nullptr) {
    return nullptr;
  }
  return resStateData->m_pResState;
}

const ResState *Util::getSimpleStateResource(const ResASM &resAsm, const char *name) {
  const ResState *resState = getStateResource(resAsm, name);
  if (resState == nullptr || resState->type != STATE_TYPE_SIMPLE) {
    return nullptr;
  }
  return resState;
}

const ResState *Util::getComplexStateResource(const ResASM &resAsm, const char *name) {
  const ResState *resState = getStateResource(resAsm, name);
  if (resState == nullptr || resState->type != STATE_TYPE_COMPLEX) {
    return nullptr;
  }
  return resState;
}

const ResState *Util::getFrozenStateResource(const ResASM &resAsm, const char *name) {
  const ResState *resState = getStateResource(resAsm, name);
  if (resState == nullptr || resState->type != STATE_TYPE_FROZEN) {
    return nullptr;
  }
  return resState;
}

} // namespace anm
