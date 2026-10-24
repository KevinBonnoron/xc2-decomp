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
  f32 unknown08;       // Inferred role: speed; original member name unknown.
  AnimLayer unknown0c; // Inferred role: layer; original member name unknown.
};

static_assert(offsetof(MsgObjectSetAsmPlaybackSpeed, unknown08) == 0x08, "");
static_assert(offsetof(MsgObjectSetAsmPlaybackSpeed, unknown0c) == 0x0c, "");

inline anm::StateMachine *getStateMachine(anm::ASMControl *asmControl, AnimLayer layer) {
  if (layer < anm::ASMControl::LAYER_MAX && asmControl != nullptr) {
    return &asmControl->m_stateMachines[layer];
  }

  return nullptr;
}

struct CallBackCache {
  CallBackCache(anm::AsmListener::CallBackType type, const anm::AsmAnnotetion *annotation) : unknown00(type), unknown08(annotation) {}

  anm::AsmListener::CallBackType unknown00; // Inferred role: type; original member name unknown.
  const anm::AsmAnnotetion *unknown08;      // Inferred role: annotation; original member name unknown.
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
    CallBack() : unknown00(nullptr) {}

    const char *unknown00;      // Inferred role: name; original member name unknown.
    CallBackDelegate unknown08; // Inferred role: delegate; original member name unknown.
  };

  class AsmLisener : public anm::AsmListener {
  public:
    void callback(CallBackType type, const anm::AsmAnnotetion &annotation) override { unknown08->cacheCallback(type, annotation); }

    GfComAsm *unknown08; // Inferred role: owner; original member name unknown.
  };

  class ViewerListener {
  public:
    virtual void onWkStandbyLogout() {
      if (unknown08 != nullptr) {
        unknown08->unknown180 = nullptr;
      }
    }

    GfComAsm *unknown08; // Inferred role: owner; original member name unknown.
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

  anm::ASMControl *unknown10;                // Inferred role: asm control; original member name unknown.
  fw::AnimAsmUpdater unknown18;              // Inferred role: updater; original member name unknown.
  fw::AnimAsmPoseSampler unknown38;          // Inferred role: pose sampler; original member name unknown.
  CallBack unknown70[CALLBACK_MAX];          // Inferred role: callbacks; original member name unknown.
  AsmLisener unknown138;                     // Inferred role: listener; original member name unknown.
  mm::mtl::Vector<CallBackCache> unknown148; // Inferred role: callback caches; original member name unknown.
  ViewerListener unknown170;                 // Inferred role: viewer listener; original member name unknown.
  void *unknown180;                          // Inferred role: viewer; original member name unknown.
};

static_assert(offsetof(GfComAsm, unknown10) == 0x10, "");
static_assert(offsetof(GfComAsm, unknown18) == 0x18, "");
static_assert(offsetof(GfComAsm, unknown38) == 0x38, "");
static_assert(offsetof(GfComAsm, unknown70) == 0x70, "");
static_assert(offsetof(GfComAsm, unknown138) == 0x138, "");
static_assert(offsetof(GfComAsm, unknown148) == 0x148, "");
static_assert(offsetof(GfComAsm, unknown170) == 0x170, "");
static_assert(offsetof(GfComAsm, unknown180) == 0x180, "");
static_assert(sizeof(GfComAsm) == 0x188, "");

} // namespace gf
