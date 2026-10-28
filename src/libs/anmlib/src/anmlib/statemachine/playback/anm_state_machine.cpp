#include "anm/anm_state_machine.h"

#include <new>

#include "anm/anm_additive_info.h"
#include "anm/anm_array-inl.h"
#include "anm/anm_asm_add_blend.h"
#include "anm/anm_asm_blender.h"
#include "anm/anm_asm_frozen.h"
#include "anm/anm_asm_lerp_add_blend.h"
#include "anm/anm_asm_lerp_blend.h"
#include "anm/anm_asm_simplex.h"
#include "anm/anm_asm_speed_lerp_blend.h"
#include "anm/anm_asm_state.h"
#include "anm/anm_res_asm.h"
#include "anm/anm_res_clip_data.h"
#include "anm/anm_res_state_data.h"
#include "anm/anm_string_ptr.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"

namespace anm {

StateMachine::StateMachine() : unknown28(nullptr), unknown30(0.0f), unknown50(nullptr), unknown58(nullptr), unknown60(nullptr), unknown68(nullptr) {}

StateMachine::~StateMachine() {}

void StateMachine::setup(const ResASM &resAsm, u32 layer, mm::mtl::IAllocator &allocator) {
  unknown68 = &allocator;
  unknown38.setAllocator(&allocator);
  unknown10.setAllocator(unknown68);
  for (u32 i = 0; i < resAsm.unknown28.size(); i++) {
    const ResStateData &resStateData = resAsm.unknown28[i];
    const ResState *resState = resStateData.unknown00;
    if (resState->unknown18 == layer) {
      AsmState *state = createState(resStateData);
      mm::mtl::MapPair<StringPtr, mm::mtl::IntrusivePtr<AsmState>> pair = {resState->name, state};
      unknown38.insert(pair);
    }
  }
}

AsmState *StateMachine::createState(const ResStateData &resStateData) {
  AsmState *state;
  const ResState *resState = resStateData.unknown00;
  switch (resState->type) {
  case STATE_TYPE_SIMPLE:
    state = new (unknown68->allocate(sizeof(SimplexState), 8)) SimplexState(&resStateData, *unknown68);
    break;
  case STATE_TYPE_FROZEN:
    state = new (unknown68->allocate(sizeof(FrozenState), 8)) FrozenState(&resStateData, *unknown68);
    break;
  case STATE_TYPE_COMPLEX: {
    const unknown00c *resTree = resState->unknown68;
    switch (resTree->unknown00) {
    case 0:
      state = new (unknown68->allocate(sizeof(LerpBlendTree), 8)) LerpBlendTree(&resStateData, reinterpret_cast<const ResLerpTree *>(resTree), *unknown60, *unknown68);
      break;
    case 2:
      state = new (unknown68->allocate(sizeof(SpeedLerpBlendTree), 8)) SpeedLerpBlendTree(&resStateData, reinterpret_cast<const ResSpeedLerpTree *>(resTree), *unknown60, *unknown68);
      break;
    case 3:
      state = new (unknown68->allocate(sizeof(AddBlendTree), 8)) AddBlendTree(&resStateData, reinterpret_cast<const ResAddTree *>(resTree), *unknown60, *unknown68);
      break;
    case 4:
      state = new (unknown68->allocate(sizeof(LerpAddBlendTree), 8)) LerpAddBlendTree(&resStateData, reinterpret_cast<const ResLerpAddTree *>(resTree), *unknown60, *unknown68);
      break;
    default:
#line 754
      MM_ASSERT(0);
      state = nullptr;
    }
    break;
  }
  default:
#line 760
    MM_ASSERT(0);
    state = nullptr;
  }
  return state;
}

void StateMachine::cleanup() {
  if (unknown00.get() != nullptr) {
    unknown00.get()->dettach(unknown58);
    unknown00 = nullptr;
  }
  if (unknown08.get() != nullptr) {
    unknown08.get()->dettach(unknown58);
    unknown08 = nullptr;
  }
  for (mm::mtl::Map<StringPtr, AdditiveInfo>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    it->second.unknown00->dettach(unknown58);
  }
  unknown10.clear();
  unknown38.clear();
}

void StateMachine::clearState() {
  if (unknown08.get() != nullptr) {
    unknown08.get()->onLeave(unknown50);
    unknown08->dettach(unknown58);
    unknown08 = nullptr;
  }
  if (unknown00.get() != nullptr) {
    unknown00.get()->onLeave(unknown50);
    unknown00->dettach(unknown58);
    unknown00 = nullptr;
  }
  resetInterpolate();
}

bool StateMachine::setState(const char *state, StartFrameType startFrame) {
  mm::mtl::Map<StringPtr, mm::mtl::IntrusivePtr<AsmState>>::iterator it = unknown38.find(state);
  if (it == unknown38.end()) {
    return false;
  }
  clearState();
  AsmState *pState = it->second.get();
  MM_ASSERT(pState->getRefCount() == 1);
  unknown00 = pState;
  const AsmClip *baseClip = unknown00->getBaseClip();
  f32 time = 0.0f;
  if (baseClip != nullptr) {
    const ResClipData *resClipData = baseClip->unknown18;
    if (startFrame == START_FRAME_TYPE_UNKNOWN_0) {
      time = resClipData->unknown10;
    } else if (startFrame == START_FRAME_TYPE_UNKNOWN_1) {
      time = resClipData->unknown10 + resClipData->unknown14 * rand();
    }
  }
  unknown00->setLocalTime(time);
  AsmState *current = unknown00.operator->();
  current->unknown24 = 1.0f;
  current->onSetWeight();
  unknown00->attach(unknown58);
  unknown00->onEnter(unknown50);
  return true;
}

bool StateMachine::doEaseInAdditive(const char *state, f32 time, f32 weight, InterpolateType type, InterpolateCurve curve) {
  mm::mtl::Map<StringPtr, mm::mtl::IntrusivePtr<AsmState>>::iterator it = unknown38.find(state);
  if (it == unknown38.end()) {
    return false;
  }
  AsmState *pState = it->second.get();
  if (pState->getRefCount() != 1) {
    pState = createState(*pState->unknown18);
  }
  AdditiveInfo info;
  unknown10.insert(mm::mtl::MapPair<StringPtr, AdditiveInfo>{it->first, info});
  mm::mtl::Map<StringPtr, AdditiveInfo>::iterator additive = unknown10.find(it->first);
  if (additive != unknown10.end()) {
    additive->second.easeIn(unknown58, unknown50, pState, time, weight, type, curve);
  }
  return true;
}

bool StateMachine::doEaseOutAdditive(const char *state, f32 time, InterpolateType type, InterpolateCurve curve) {
  mm::mtl::Map<StringPtr, AdditiveInfo>::iterator it = unknown10.find(state);
  if (it == unknown10.end()) {
    return false;
  }
  it->second.easeOut(unknown58, unknown50, time, type, curve);
  return true;
}

void StateMachine::clearAdditiveState() {
  for (mm::mtl::Map<StringPtr, AdditiveInfo>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    it->second.easeOut(unknown58, unknown50, 0.0f, INTERPOLATE_TYPE_UNKNOWN_0, INTERPOLATE_CURVE_UNKNOWN_0);
  }
  unknown10.clear();
}

bool StateMachine::resetState(const char *state, StartFrameType startFrame) {
  mm::mtl::Map<StringPtr, mm::mtl::IntrusivePtr<AsmState>>::iterator it = unknown38.find(state);
  if (it == unknown38.end()) {
    return false;
  }
  if (unknown08.get() != nullptr) {
    unknown08->dettach(unknown58);
    unknown08 = nullptr;
  }
  if (unknown00.get() != nullptr) {
    unknown00->dettach(unknown58);
    unknown00 = nullptr;
  }
  resetInterpolate();
  AsmState *pState = it->second.get();
  MM_ASSERT(pState->getRefCount() == 1);
  unknown00 = pState;
  const AsmClip *baseClip = unknown00->getBaseClip();
  f32 time = 0.0f;
  if (baseClip != nullptr) {
    const ResClipData *resClipData = baseClip->unknown18;
    if (startFrame == START_FRAME_TYPE_UNKNOWN_0) {
      time = resClipData->unknown10;
    } else if (startFrame == START_FRAME_TYPE_UNKNOWN_1) {
      time = resClipData->unknown10 + resClipData->unknown14 * rand();
    }
  }
  unknown00->setLocalTime(time);
  AsmState *current = unknown00.operator->();
  current->unknown24 = 1.0f;
  current->onSetWeight();
  unknown00->attach(unknown58);
  unknown00->onEnter(unknown50);
  return true;
}

bool StateMachine::setAdditiveStateSpeed(const char *state, f32 speed) {
  mm::mtl::Map<StringPtr, AdditiveInfo>::iterator it = unknown10.find(state);
  if (it == unknown10.end()) {
    return false;
  }
  AsmState *pState = it->second.unknown00.get();
  if (pState != nullptr) {
    pState->setSpeed(speed);
  }
  return true;
}

void StateMachine::resetInterpolate() {
  unknown28 = nullptr;
  unknown30 = 0.0f;
}

const char *StateMachine::getStateName() const {
  if (unknown00.get() == nullptr) {
    return nullptr;
  }
  return unknown00.get()->unknown18->unknown00->name;
}

u64 StateMachine::getAttribute(u32 index) const {
  if (unknown00.get() == nullptr) {
    return 0;
  }
  const ResStateData *resStateData = unknown00.get()->unknown18;
  if (index == 0) {
    return resStateData->unknown00->attribute;
  }
  return resStateData->unknown30[index - 1];
}

bool StateMachine::isEnd() const {
  if (unknown00.get() == nullptr) {
    return false;
  }
  bool isOver = unknown00.get()->unknown2c >= unknown00.get()->unknown28;
  bool isFinite = unknown00.get()->unknown28 != 0;
  return isFinite & isOver;
}

bool StateMachine::isLoop() const {
  if (unknown00.get() == nullptr) {
    return false;
  }
  return unknown00.get()->unknown28 == 0;
}

void StateMachine::setLocalTime(f32 time) {
  if (unknown00.get() != nullptr) {
    unknown00.get()->setLocalTime(time);
  }
}

f32 StateMachine::getLocalTime() const {
  if (unknown00.get() == nullptr) {
    return 0.0f;
  }
  return unknown00.get()->getLocalTime();
}

void StateMachine::setSpeed(f32 speed) {
  if (unknown00.get() != nullptr) {
    unknown00.get()->setSpeed(speed);
  }
  if (unknown08.get() != nullptr) {
    unknown08.get()->setSpeed(speed);
  }
}

f32 StateMachine::getSpeed() const {
  if (unknown00.get() == nullptr) {
    return 0.0f;
  }
  return unknown00.get()->unknown20;
}

} // namespace anm

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<anm::StringPtr, anm::AdditiveInfo>::MapTraits<anm::StringPtr, anm::AdditiveInfo>> unknown101;

template unknown101::node *unknown101::insert(const mm::mtl::MapPair<anm::StringPtr, anm::AdditiveInfo> &);
template void unknown101::rebalance(unknown101::node *);
template void unknown101::rebalance_after_erase(unknown101::node *);
