#pragma once
#include <stddef.h>

#include "anm/anm_asm_control.h"
#include "anm/anm_asm_listener.h"
#include "anm/anm_state_machine.h"
#include "framework/anim/anim_control_updater.h"
#include "framework/anim/anim_pose_sampler.h"
#include "framework/message/message_object.h"
#include "gf/object/component/animation/gf_com_animation.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace anm {
class ResASM;
struct QsTransform;
} // namespace anm
namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {
struct MsgDebugActivateComponentWindow;

enum AnimLayer {
  ANIM_LAYER_BASE = 0,
  ANIM_LAYER_HEAD = 2,
  ANIM_LAYER_EYE = 3,
  ANIM_LAYER_LIP = 4,
  ANIM_LAYER_BROW = 5,
};

enum AsmCategory {};

enum {
  MSG_OBJECT_SET_ASM_PLAYBACK_SPEED = 0x1000047,
};

struct MsgObjectSetAsmPlaybackSpeed : fw::Message {
  f32 speed;
  AnimLayer layer;
};

static_assert(offsetof(MsgObjectSetAsmPlaybackSpeed, speed) == 0x08, "");
static_assert(offsetof(MsgObjectSetAsmPlaybackSpeed, layer) == 0x0c, "");

inline anm::StateMachine *getStateMachine(anm::ASMControl *asmControl, AnimLayer layer) {
  if (layer < anm::ASMControl::LAYER_MAX && asmControl != nullptr) {
    return &asmControl->m_stateMachines[layer];
  }

  return nullptr;
}

struct CallBackCache {
  CallBackCache(anm::AsmListener::CallBackType type, const anm::AsmAnnotetion *annotation) : type(type), annotation(annotation) {}

  anm::AsmListener::CallBackType type;
  const anm::AsmAnnotetion *annotation;
};

static_assert(sizeof(CallBackCache) == 0x10, "");

class GfComAsm : public GfComAnimation {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 2;
  static const u32 CALLBACK_MAX = 5;

  typedef mm::mtl::Delegate<void(GfComAsm *, const CallBackCache &)> CallBackDelegate;

  struct SetupInfo {
    const anm::ResASM *resAsm;
    const char *state;
    u8 startFrame;
    bool isLocalSpace;
  };

  struct CallBack {
    CallBack() : name(nullptr) {}

    const char *name;
    CallBackDelegate delegate;
  };

  class AsmLisener : public anm::AsmListener {
  public:
    void callback(CallBackType type, const anm::AsmAnnotetion &annotation) override { owner->cacheCallback(type, annotation); }

    GfComAsm *owner;
  };

  class ViewerListener {
  public:
    virtual void onWkStandbyLogout() {
      if (owner != nullptr) {
        owner->viewer = nullptr;
      }
    }

    GfComAsm *owner;
  };

  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void procMsgObjectSetAsmPlaybackSpeed(fw::MessageObject *sender, MsgObjectSetAsmPlaybackSpeed &message);
  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  GfComAsm();
  ~GfComAsm() override;
  void setup(const SetupInfo &info);
  void cleanup();
  void clearCallback();
  const anm::ResASM *getResource() const;
  bool getPlaybackTime(const char *state, f32 *time) const;
  bool getLocomotionReference(const char *state, f32 time, anm::QsTransform *transform) const;
  bool getLocomotionDeltaReference(const char *state, f32 startTime, f32 endTime, anm::QsTransform *transform) const;
  bool getClipInvFps(const char *state, u32 index, f32 *invFps) const;
  bool getClipFps(const char *state, u32 index, f32 *fps) const;
  bool existEndTrans(const char *state);
  const void *getAppendix(const char *name) const;
  bool existState(const char *state);
  void executeCallback();
  bool execCmd(const char *command, AnimLayer layer);
  const char *getStateName(AnimLayer layer) const;
  bool setState(const char *state, AnimLayer layer);
  void clearState(AnimLayer layer);
  bool resetState(const char *state, AnimLayer layer);
  bool easeIn(const char *state, f32 time, AnimLayer layer);
  bool easeOut(const char *state, f32 time, AnimLayer layer);
  void clearAdditiveState(AnimLayer layer);
  bool isActiveAdditiveState(const char *state, AnimLayer layer);
  bool setWeightAdditiveState(const char *state, f32 weight, AnimLayer layer);
  bool setSpeedAdditiveState(const char *state, f32 speed, AnimLayer layer);
  bool isEnd(AnimLayer layer) const;
  bool isLoop(AnimLayer layer) const;
  bool isInterpolate(AnimLayer layer) const;
  void setLocalTime(f32 time, AnimLayer layer);
  f32 getLocalTime(AnimLayer layer) const;
  void setSpeed(f32 speed, AnimLayer layer);
  f32 getSpeed(AnimLayer layer) const;
  u64 getAttribute(AsmCategory category, AnimLayer layer) const;
  const anm::QsTransform &getLocomotion() const;
  void setVariable(const char *name, f32 value);
  void getVariable(const char *name, f32 *value) const;
  void setVariable(const char *name, int value);
  void getVariable(const char *name, int *value) const;
  void cacheCallback(anm::AsmListener::CallBackType type, const anm::AsmAnnotetion &annotation);
  void changeLayer(u32 oldLayer, u32 newLayer) override;
  const mm::mtl::RTTI *getRTTI() const override;

  anm::ASMControl *asmControl;
  fw::AnimAsmUpdater updater;
  fw::AnimAsmPoseSampler poseSampler;
  CallBack callbacks[CALLBACK_MAX];
  AsmLisener listener;
  mm::mtl::Vector<CallBackCache> callbackCaches;
  ViewerListener viewerListener;
  void *viewer;
};

static_assert(offsetof(GfComAsm, asmControl) == 0x10, "");
static_assert(offsetof(GfComAsm, updater) == 0x18, "");
static_assert(offsetof(GfComAsm, poseSampler) == 0x38, "");
static_assert(offsetof(GfComAsm, callbacks) == 0x70, "");
static_assert(offsetof(GfComAsm, listener) == 0x138, "");
static_assert(offsetof(GfComAsm, callbackCaches) == 0x148, "");
static_assert(offsetof(GfComAsm, viewerListener) == 0x170, "");
static_assert(offsetof(GfComAsm, viewer) == 0x180, "");
static_assert(sizeof(GfComAsm) == 0x188, "");

} // namespace gf
