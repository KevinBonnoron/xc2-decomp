#include "anm/anm_util.h"

#include <algorithm>
#include <math.h>
#include <string.h>

#include "anm/anm_animation.h"
#include "anm/anm_array-inl.h"
#include "anm/anm_array.h"
#include "anm/anm_asm_variable.h"
#include "anm/anm_binding.h"
#include "anm/anm_control.h"
#include "anm/anm_res_asm.h"
#include "anm/anm_res_clip_data.h"
#include "anm/anm_res_state_data.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/set.h"
#include "mm_mtl/vector.h"

namespace anm {

static_assert(sizeof(mm::mtl::Set<StringPtr>) == 0x18, "");
static_assert(sizeof(mm::mtl::RedBlackTreeBase<mm::mtl::Set<StringPtr>::TreeTraits<StringPtr>>::node) == 0x28, "");

static const char *s_layerNames[LAYER_NUM] = {"base", "upperbody", "head", "eye", "mouth", "brow", "extra"};

const char *Util::getName(const Binding &binding) {
  MM_ASSERT(binding.m_pAnimation);
  return binding.m_pAnimation->unknown18;
}

s32 Util::getAnimationType(const Binding &binding) { return binding.m_pAnimation->getImplType(); }

PlayMode Util::getPlayMode(const Binding &binding) {
  MM_ASSERT(binding.m_pAnimation);
  return static_cast<PlayMode>(binding.m_pAnimation->unknown22);
}

u8 Util::getBlendHint(const Binding &binding) {
  MM_ASSERT(binding.m_pAnimation);
  return binding.m_pAnimation->unknown23;
}

u32 Util::getFrameCount(const Binding &binding) {
  MM_ASSERT(binding.m_pAnimation);
  return binding.m_pAnimation->unknown2c;
}

f32 Util::getPlayBackTime(const Binding &binding) {
  const Animation *pAnimation = binding.m_pAnimation;
  MM_ASSERT(pAnimation);
  return pAnimation->unknown28 * (pAnimation->unknown2c - 1);
}

bool Util::hasLocomotion(const Binding &binding) {
  MM_ASSERT(binding.m_pAnimation);
  return binding.m_pAnimation->unknown40 != nullptr;
}

f32 Util::getFps(const Binding &binding) {
  MM_ASSERT(binding.m_pAnimation);
  return binding.m_pAnimation->unknown24;
}

f32 Util::getInvFps(const Binding &binding) {
  MM_ASSERT(binding.m_pAnimation);
  return binding.m_pAnimation->unknown28;
}

f32 Util::calcLocalTime(f32 time, f32 start, f32 end, PlayMode playMode) {
  if (playMode == PLAY_MODE_LOOP) {
    return fmodf(time - start, end) + start;
  }
  return mm::clamp(time, start, end);
}

void Util::setKeyFrame(Control &control, f32 frame) { control.setLocalTime(control.m_pBinding->m_pAnimation->unknown28 * frame); }

void Util::queryState(u32 mask, const ResASM &resAsm, mm::mtl::Set<StringPtr> *pDst) {
  MM_ASSERT(pDst);
  const ResStateArray *states = resAsm.unknown20;
  if (states != nullptr) {
    for (ArrayIterartor<ResState *const> it = states->unknown18.begin(), last = states->unknown18.end(); it != last; ++it) {
      const ResState *resState = *it;
      if (resState != nullptr && ((1 << resState->unknown18) & mask) != 0) {
        pDst->insert(resState->name);
      }
    }
  }
}

void Util::queryCmd(u32 mask, const ResASM &resAsm, mm::mtl::Set<StringPtr> *pDst) {
  MM_ASSERT(pDst);
  const ResStateArray *states = resAsm.unknown20;
  if (states != nullptr) {
    for (ArrayIterartor<ResState *const> it = states->unknown18.begin(), last = states->unknown18.end(); it != last; ++it) {
      const ResState *resState = *it;
      if (resState != nullptr && ((1 << resState->unknown18) & mask) != 0) {
        for (ArrayIterartor<unknown007 *const> cmd = resState->unknown20.begin(), cmdLast = resState->unknown20.end(); cmd != cmdLast; ++cmd) {
          const unknown007 *resCmd = *cmd;
          if (resCmd != nullptr) {
            pDst->insert(resCmd->unknown00);
          }
        }
      }
    }
  }
}

const ResState *searchState(u32 mask, const ResASM &resAsm, const StringPtr &name) {
  const ResStateArray *states = resAsm.unknown20;
  if (states != nullptr) {
    for (ArrayIterartor<ResState *const> it = states->unknown18.begin(), last = states->unknown18.end(); it != last; ++it) {
      const ResState *resState = *it;
      if (resState != nullptr && ((1 << resState->unknown18) & mask) != 0 && name == resState->name) {
        return resState;
      }
    }
  }
  return nullptr;
}

const unknown007 *searchCmd(const ResState *pResState, const StringPtr &name) {
  MM_ASSERT(pResState);
  for (ArrayIterartor<unknown007 *const> it = pResState->unknown20.begin(), last = pResState->unknown20.end(); it != last; ++it) {
    if (name == (*it)->unknown00) {
      return *it;
    }
  }
  return nullptr;
}

void Util::queryCmdFromStateSimple(u32 mask, const ResASM &resAsm, const StringPtr &state, mm::mtl::Set<StringPtr> *pDst) {
  const ResState *resState = searchState(mask, resAsm, state);
  if (resState != nullptr) {
    for (ArrayIterartor<unknown007 *const> it = resState->unknown20.begin(), last = resState->unknown20.end(); it != last; ++it) {
      pDst->insert((*it)->unknown00);
    }
  }
}

void Util::queryStateFromStateCmd(u32 mask, const ResASM &resAsm, const StringPtr &state, const StringPtr &cmd, mm::mtl::Set<StringPtr> *pDst) {
  const ResState *resState = searchState(mask, resAsm, state);
  if (resState != nullptr) {
    for (ArrayIterartor<unknown007 *const> it = resState->unknown20.begin(), last = resState->unknown20.end(); it != last; ++it) {
      const unknown007 *resCmd = *it;
      if (resCmd->unknown00 == cmd) {
        switch (resCmd->unknown08) {
        case 0:
          pDst->insert(static_cast<const unknown008 *>(resCmd)->unknown10);
          break;
        case 1: {
          const unknown009 *cmd1 = static_cast<const unknown009 *>(resCmd);
          for (ArrayIterartor<const unknown005> target = cmd1->unknown10.begin(), targetLast = cmd1->unknown10.end(); target != targetLast; ++target) {
            pDst->insert((*target).unknown10);
          }
          break;
        }
        case 2: {
          const unknown00a *cmd2 = static_cast<const unknown00a *>(resCmd);
          for (ArrayIterartor<const unknown006> target = cmd2->unknown18.begin(), targetLast = cmd2->unknown18.end(); target != targetLast; ++target) {
            pDst->insert((*target).unknown08);
          }
          break;
        }
        }
      }
    }
  }
}

bool Util::queryStateAutoTrans(u32 mask, const ResASM &resAsm, const StringPtr &state, StringPtr *pAutoTrans) {
  const ResState *resState = searchState(mask, resAsm, state);
  if (resState != nullptr) {
    if (resState->loopCount == nullptr) {
      return false;
    }
    *pAutoTrans = resState->loopCount->unknown00;
    return true;
  }
  return false;
}

void Util::queryVariableFloat(const ResASM &resAsm, mm::mtl::Set<StringPtr> *pDst) {
  MM_ASSERT(pDst);
  const ResStateArray *states = resAsm.unknown20;
  if (states != nullptr) {
    for (ArrayIterartor<const ResVariable> it = states->unknown28.begin(), last = states->unknown28.end(); it != last; ++it) {
      if (it->type == VAR_FLOAT) {
        pDst->insert(it->name);
      }
    }
  }
}

void Util::queryVariableInt(const ResASM &resAsm, mm::mtl::Set<StringPtr> *pDst) {
  MM_ASSERT(pDst);
  const ResStateArray *states = resAsm.unknown20;
  if (states != nullptr) {
    for (ArrayIterartor<const ResVariable> it = states->unknown28.begin(), last = states->unknown28.end(); it != last; ++it) {
      if (it->type == VAR_INT) {
        pDst->insert(it->name);
      }
    }
  }
}

bool Util::getAsmPlaybackTime(const ResASM &resAsm, const char *state, u32 index, f32 *time) {
  const ResStateData *resStateData = resAsm.findResStateData(state);
  if (resStateData == nullptr || index >= resStateData->unknown08.size()) {
    return false;
  }
  *time = resStateData->unknown08[index].unknown14;
  return true;
}

const Binding *Util::getAsmBinding(const ResASM &resAsm, const char *state, u32 index) {
  if (state == nullptr) {
    return nullptr;
  }
  const ResStateData *resStateData = resAsm.findResStateData(state);
  if (resStateData == nullptr || index >= resStateData->unknown08.size()) {
    return nullptr;
  }
  return resStateData->unknown08[index].m_pBinding;
}

struct lessAppendix {
  bool operator()(const ResAppendix &lhs, const char *rhs) const { return strcmp(lhs.name, rhs) < 0; }
};

const char *Util::getLayerName(Layer layer) { return s_layerNames[layer]; }

const ResAppendix *Util::findAppendix(const ResASM &resAsm, const char *name) {
  const ResStateArray *states = resAsm.unknown20;
  if (states == nullptr || states->unknown50.size() == 0) {
    return nullptr;
  }
  ArrayIterartor<const ResAppendix> it = std::lower_bound(states->unknown50.begin(), states->unknown50.end(), name, lessAppendix());
  if (it == states->unknown50.end()) {
    return nullptr;
  }
  const ResAppendix *appendix = it.operator->();
  if (strcmp(appendix->name, name) != 0) {
    appendix = nullptr;
  }
  return appendix;
}

const ResState *Util::getStateResource(const ResASM &resAsm, const char *name) {
  const ResStateData *resStateData = resAsm.findResStateData(name);
  if (resStateData == nullptr) {
    return nullptr;
  }
  return resStateData->unknown00;
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
