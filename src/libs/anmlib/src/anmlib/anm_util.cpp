#include "anm/anm_util.h"

#include <algorithm>
#include <math.h>
#include <string.h>

#include "anm/anm_animation.h"
#include "anm/anm_array-inl.h"
#include "anm/anm_array.h"
#include "anm/anm_asm_lerp_blend.h"
#include "anm/anm_asm_speed_lerp_blend.h"
#include "anm/anm_asm_variable.h"
#include "anm/anm_binding.h"
#include "anm/anm_control.h"
#include "anm/anm_extra_truck.h"
#include "anm/anm_pose.h"
#include "anm/anm_res_asm.h"
#include "anm/anm_res_clip_data.h"
#include "anm/anm_res_state_data.h"
#include "anm/anm_skeleton.h"
#include "anm/anm_space_resolve_util.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/set.h"
#include "mm_mtl/vector.h"

namespace anm {

static_assert(sizeof(mm::mtl::Set<StringPtr>) == 0x18, "");
static_assert(sizeof(mm::mtl::RedBlackTreeBase<mm::mtl::Set<StringPtr>::TreeTraits<StringPtr>>::node) == 0x28, "");

static const char *s_layerNames[LAYER_NUM] = {"base", "upperbody", "head", "eye", "mouth", "brow", "extra"};

void Util::computeIgnoreMirrorFromName(const mm::mtl::Vector<IgnoreName> &names, const Skeleton *skeleton, mm::mtl::Vector<s8> *ignore) {
  if (skeleton != nullptr) {
    ignore->clear();
    u32 boneCount = skeleton->getBoneCount();
    if (ignore->capacity() < boneCount) {
      ignore->reserve(boneCount);
    }
    for (u32 i = 0; i < boneCount; i++) {
      s8 value = 0;
      for (u32 j = 0; j < names.size(); j++) {
        if (strncmp(skeleton->unknown001(i).unknown00, names[j].unknown00, names[j].unknown08) == 0) {
          value = -1;
          break;
        }
      }
      ignore->push_back(value);
    }
  }
}

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

void Util::setReferrenceExtraTruck(const ExtraTruckSlot &slot, u32 count, f32 *values) {
  for (u32 i = 0; i < count; i++) {
    values[i] = slot.unknown18[i];
  }
}

void Util::samplePoseSmartFromControl(Control *control, Pose *pose, bool localSpace) {
  if (control != nullptr && pose != nullptr) {
    const Binding *pBinding = control->m_pBinding;
    MM_ASSERT(pBinding);
    u8 blendHint = pBinding->m_pAnimation->unknown21;
    if (localSpace) {
      if (blendHint == 0) {
        mm::mtl::Vector<QsTransform> &local = pose->accessSyncedPoseLocalSpace();
        control->sampleTrucks(local.size(), local.m_buffer);
      } else if (blendHint == 1) {
        mm::mtl::Vector<QsTransform> &local = pose->accessSyncedPoseLocalSpace();
        control->sampleTrucks(local.size(), local.m_buffer);
        const Skeleton *pSkeleton = pose->unknown18;
        MM_ASSERT(pSkeleton);
        SpaceResolveUtil::clacPoseMSNoTruck(pBinding, pSkeleton, local.m_buffer);
        SpaceResolveUtil::convertMStoLS(pSkeleton, local.m_buffer);
      } else {
        return;
      }
      pose->syncModelSpace();
    } else if (blendHint == 0) {
      mm::mtl::Vector<QsTransform> &model = pose->accessSyncedPoseModelSpace();
      control->sampleTrucks(model.size(), model.m_buffer);
      const Skeleton *pSkeleton = pose->unknown18;
      MM_ASSERT(pSkeleton);
      SpaceResolveUtil::setReferencePoseNoTruck(pBinding, pSkeleton, model.m_buffer);
      SpaceResolveUtil::convertLStoMS(pSkeleton, model.m_buffer);
    } else if (blendHint == 1) {
      mm::mtl::Vector<QsTransform> &model = pose->accessSyncedPoseModelSpace();
      control->sampleTrucks(model.size(), model.m_buffer);
    }
  }
}

void Util::clampLimitExtraTruck(const ExtraTruckSlot &slot, u32 count, f32 *values) {
  for (u32 i = 0; i < count; i++) {
    const unknown00f &limit = slot.unknown28[i];
    values[i] = mm::clamp(values[i], limit.unknown00, limit.unknown04);
  }
}

void Util::setKeyFrame(Control &control, f32 frame) { control.setLocalTime(control.m_pBinding->m_pAnimation->unknown28 * frame); }

struct CompResState {
  bool operator()(const ResState *lhs, const char *rhs) const { return strcmp(lhs->name, rhs) < 0; }
};

bool Util::getVariableMinMax(const ResASM &resAsm, const char *stateName, const char *variableName, f32 *pMin, f32 *pMax) {
  MM_ASSERT(stateName);
  const ResStateArray *states = resAsm.unknown20;
  if (states != nullptr) {
    ArrayIterartor<ResState *const> it = std::lower_bound(states->unknown18.begin(), states->unknown18.end(), stateName, CompResState());
    if (it != states->unknown18.end()) {
      const ResState *resState = *it;
      if (strcmp(resState->name, stateName) == 0 && resState->type == unknown103_2) {
        const unknown00c *resTree = resState->unknown68;
        switch (resTree->unknown00) {
        case 0: {
          const ResLerpTree *tree = reinterpret_cast<const ResLerpTree *>(resTree);
          if (states->unknown28.size() > tree->variableIndex) {
            if (strcmp(states->unknown28[tree->variableIndex].name, variableName) == 0) {
              *pMin = tree->unknown08.begin()->unknown00;
              *pMax = tree->unknown08[tree->unknown08.size() - 1].unknown00;
              return true;
            }
          }
          break;
        }
        case 2: {
          const ResSpeedLerpTree *tree = reinterpret_cast<const ResSpeedLerpTree *>(resTree);
          if (states->unknown28.size() > tree->variableIndex) {
            if (strcmp(states->unknown28[tree->variableIndex].name, variableName) == 0) {
              *pMin = tree->unknown08.begin()->unknown00;
              *pMax = tree->unknown08[tree->unknown08.size() - 1].unknown00;
              return true;
            }
          }
          break;
        }
        default:
          return false;
        }
      }
    }
  }
  return false;
}

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
        for (ArrayIterartor<ResCmd *const> cmd = resState->unknown20.begin(), cmdLast = resState->unknown20.end(); cmd != cmdLast; ++cmd) {
          const ResCmd *resCmd = *cmd;
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

const ResCmd *searchCmd(const ResState *pResState, const StringPtr &name) {
  MM_ASSERT(pResState);
  for (ArrayIterartor<ResCmd *const> it = pResState->unknown20.begin(), last = pResState->unknown20.end(); it != last; ++it) {
    if (name == (*it)->unknown00) {
      return *it;
    }
  }
  return nullptr;
}

void Util::queryCmdFromStateSimple(u32 mask, const ResASM &resAsm, const StringPtr &state, mm::mtl::Set<StringPtr> *pDst) {
  const ResState *resState = searchState(mask, resAsm, state);
  if (resState != nullptr) {
    for (ArrayIterartor<ResCmd *const> it = resState->unknown20.begin(), last = resState->unknown20.end(); it != last; ++it) {
      pDst->insert((*it)->unknown00);
    }
  }
}

void Util::queryStateFromStateCmd(u32 mask, const ResASM &resAsm, const StringPtr &state, const StringPtr &cmd, mm::mtl::Set<StringPtr> *pDst) {
  const ResState *resState = searchState(mask, resAsm, state);
  if (resState != nullptr) {
    for (ArrayIterartor<ResCmd *const> it = resState->unknown20.begin(), last = resState->unknown20.end(); it != last; ++it) {
      const ResCmd *resCmd = *it;
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
          for (ArrayIterartor<const SelectNode> target = cmd2->unknown18.begin(), targetLast = cmd2->unknown18.end(); target != targetLast; ++target) {
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
      if (it->type == unknown132_0) {
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

bool Util::getAsmLocomotionReference(const ResASM &resAsm, const char *state, f32 time, u32 index, QsTransform *transform) {
  const ResStateData *resStateData = resAsm.findResStateData(state);
  if (resStateData == nullptr || index >= resStateData->unknown08.size()) {
    return false;
  }
  return resStateData->unknown08[index].getReference(time, transform);
}

bool Util::getAsmLocomotionDeltaReference(const ResASM &resAsm, const char *state, f32 startTime, f32 endTime, u32 index, QsTransform *transform) {
  const ResStateData *resStateData = resAsm.findResStateData(state);
  if (resStateData == nullptr || index >= resStateData->unknown08.size()) {
    return false;
  }
  return resStateData->unknown08[index].getDeltaReference(startTime, endTime, transform);
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
  if (resState == nullptr || resState->type != unknown103_0) {
    return nullptr;
  }
  return resState;
}

const ResState *Util::getComplexStateResource(const ResASM &resAsm, const char *name) {
  const ResState *resState = getStateResource(resAsm, name);
  if (resState == nullptr || resState->type != unknown103_2) {
    return nullptr;
  }
  return resState;
}

const ResState *Util::getFrozenStateResource(const ResASM &resAsm, const char *name) {
  const ResState *resState = getStateResource(resAsm, name);
  if (resState == nullptr || resState->type != unknown103_1) {
    return nullptr;
  }
  return resState;
}

} // namespace anm
