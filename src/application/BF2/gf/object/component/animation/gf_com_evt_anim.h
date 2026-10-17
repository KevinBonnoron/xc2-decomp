#pragma once
#include <stddef.h>

#include "anm/anm_asm_listener.h"
#include "framework/anim/anim_control_updater.h"
#include "framework/anim/anim_pose_sampler.h"
#include "gf/object/component/animation/gf_com_animation.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace fw {
class MessageObject;
} // namespace fw

namespace anm {
class ASMControl;
class Blender;
class Control;
class ResASM;
struct QsTransform;
} // namespace anm
namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComModel;
struct MsgDebugActivateComponentWindow;

class GfComEvtAnim : public GfComAnimation {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 2;
  static const u32 CALLBACK_MAX = 5;
  static const u32 EASE_MAX = 16;
  static const u32 MOTION_MAX = 8;

  enum {
    FLAG_REGISTERED = 0,
  };

  enum {
    FLAG_SETUP = 0,
  };

  typedef mm::mtl::Delegate<void(GfComEvtAnim *, const CallBackCache &)> CallBackDelegate;

  struct SetupInfo {
    anm::ResASM *resAsm;
    const char *state;
    bool isLocalSpace;
  };

  struct CallBack {
    CallBack() : name(nullptr) {}

    const char *name;
    CallBackDelegate delegate;
  };

  class Asm {
  public:
    class AsmLisener : public anm::AsmListener {
    public:
      void callback(CallBackType type, const anm::AsmAnnotetion &annotation) override { owner->cacheCallback(type, annotation); }

      Asm *owner;
    };

    class ViewerListener {
    public:
      virtual void onWkStandbyLogout() {
        if (owner != nullptr) {
          owner->viewer = nullptr;
        }
      }

      Asm *owner;
    };

    Asm();
    void cleanup(u32 layer);
    void setup(u32 layer, GfComModel *model, anm::ResASM *resAsm, const char *state, bool isLocalSpace);
    void changeLayer(u32 oldLayer, u32 newLayer);
    bool execCmd(AnimLayer layer, const char *command);
    const char *getStateName(AnimLayer layer) const;
    bool setState(AnimLayer layer, const char *state);
    void setVariable(const char *name, f32 value);
    void setVariable(const char *name, int value);
    void setSpeed(AnimLayer layer, f32 speed);
    void setLocalTime(AnimLayer layer, f32 time);
    bool getPlaybackTime(const char *state, f32 *time) const;
    bool getLocomotionReference(const char *state, f32 time, anm::QsTransform *transform) const;
    const anm::QsTransform &getLocomotion() const;
    void setPause(u32 layer, bool isPause);
    bool isEnd(AnimLayer layer) const;
    bool easeIn(const char *state, AnimLayer layer);
    bool easeOut(const char *state, AnimLayer layer);
    bool setEaseWeight(const char *state, AnimLayer layer, f32 weight);
    bool setEaseSpeed(const char *state, AnimLayer layer, f32 speed);
    void executeCallback(GfComEvtAnim *owner);
    void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
    void cacheCallback(anm::AsmListener::CallBackType type, const anm::AsmAnnotetion &annotation);

    mm::mtl::BitFlag<32> flags;
    GfComModel *model;
    anm::ASMControl *asmControl;
    fw::AnimAsmUpdater updater;
    fw::AnimEventAsmPoseSampler poseSampler;
    CallBack callbacks[CALLBACK_MAX];
    AsmLisener listener;
    mm::mtl::Vector<CallBackCache> callbackCaches;
    ViewerListener viewerListener;
    void *viewer;
  };

  class Mot {
  public:
    Mot();
    void cleanup(u32 layer);
    void stop(u32 layer);
    void setup(GfComModel *model, anm::ResASM *resAsm, bool isLocalSpace);
    void changeLayer(u32 oldLayer, u32 newLayer);
    void init(u32 layer, void **motions, u64 *sizes, u64 count);
    void play(u32 index, f32 time);
    bool isEnd() const;
    void setSpeed(f32 speed);
    void setPause(u32 layer, bool isPause);
    void setWeight(f32 *weights, u64 count);
    bool easeIn(const char *state, AnimLayer layer);
    bool easeOut(const char *state, AnimLayer layer);
    bool setEaseWeight(const char *state, AnimLayer layer, f32 weight);
    bool setEaseSpeed(const char *state, AnimLayer layer, f32 speed);

    mm::mtl::BitFlag<32> flags;
    GfComModel *model;
    anm::ResASM *resAsm;
    anm::Blender *blender;
    fw::AnimBlenderUpdater blenderUpdater;
    fw::AnimEventMotPoseSamper poseSampler;
    mm::mtl::FixedVector<anm::Control *, EASE_MAX> easeControls;
    mm::mtl::FixedVector<mm::mtl::FixStr<32>, EASE_MAX> easeNames;
    anm::Control *controls[MOTION_MAX];
    f32 playBackTimes[MOTION_MAX];
    u64 controlCount;
    u32 current;
    f32 speed;
  };

  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  GfComEvtAnim();
  void cleanup();
  void setup(const SetupInfo &info);
  void updateSetup();
  void changeLayer(u32 oldLayer, u32 newLayer) override;
  bool execCmd(const char *command);
  const char *getStateName() const;
  bool setState(const char *state);
  void setVariable(const char *name, f32 value);
  void setVariable(const char *name, int value);
  void setLocalTime(f32 time, AnimLayer layer);
  bool getPlaybackTime(const char *state, f32 *time) const;
  bool getLocomotionReference(const char *state, f32 time, anm::QsTransform *transform) const;
  const anm::QsTransform &getLocomotion() const;
  bool isEnd(AnimLayer layer) const;
  void play(void *motion, u64 size, f32 time);
  void stop();
  void initMulti(void **motions, u64 *sizes, u64 count);
  void playMulti(u32 index, f32 time);
  void stopMulti();
  bool isEndMulti() const;
  void setWeightMulti(f32 *weights, u64 count);
  void setSpeed(f32 speed, AnimLayer layer);
  bool easeIn(const char *name, AnimLayer layer);
  bool easeOut(const char *name, AnimLayer layer);
  bool setEaseWeight(const char *name, AnimLayer layer, f32 weight);
  bool setEaseSpeed(const char *name, AnimLayer layer, f32 speed);
  const mm::mtl::RTTI *getRTTI() const override;

  Asm animAsm;
  Mot mot;
  anm::ResASM *resAsm;
  mm::mtl::FixStr<32> state;
  mm::mtl::BitFlag<32> flags;
  bool isLocalSpace;
};

static_assert(offsetof(GfComEvtAnim::Asm, model) == 0x08, "");
static_assert(offsetof(GfComEvtAnim::Asm, asmControl) == 0x10, "");
static_assert(offsetof(GfComEvtAnim::Asm, updater) == 0x18, "");
static_assert(offsetof(GfComEvtAnim::Asm, poseSampler) == 0x38, "");
static_assert(offsetof(GfComEvtAnim::Asm, callbacks) == 0x70, "");
static_assert(offsetof(GfComEvtAnim::Asm, listener) == 0x138, "");
static_assert(offsetof(GfComEvtAnim::Asm, callbackCaches) == 0x148, "");
static_assert(offsetof(GfComEvtAnim::Asm, viewerListener) == 0x170, "");
static_assert(offsetof(GfComEvtAnim::Asm, viewer) == 0x180, "");
static_assert(sizeof(GfComEvtAnim::Asm) == 0x188, "");
static_assert(offsetof(GfComEvtAnim::Mot, model) == 0x08, "");
static_assert(offsetof(GfComEvtAnim::Mot, blender) == 0x18, "");
static_assert(offsetof(GfComEvtAnim::Mot, blenderUpdater) == 0x20, "");
static_assert(offsetof(GfComEvtAnim::Mot, poseSampler) == 0x40, "");
static_assert(offsetof(GfComEvtAnim::Mot, easeControls) == 0x78, "");
static_assert(offsetof(GfComEvtAnim::Mot, easeNames) == 0x100, "");
static_assert(offsetof(GfComEvtAnim::Mot, controls) == 0x348, "");
static_assert(offsetof(GfComEvtAnim::Mot, playBackTimes) == 0x388, "");
static_assert(offsetof(GfComEvtAnim::Mot, controlCount) == 0x3a8, "");
static_assert(offsetof(GfComEvtAnim::Mot, current) == 0x3b0, "");
static_assert(offsetof(GfComEvtAnim::Mot, speed) == 0x3b4, "");
static_assert(sizeof(GfComEvtAnim::Mot) == 0x3b8, "");
static_assert(offsetof(GfComEvtAnim, animAsm) == 0x10, "");
static_assert(offsetof(GfComEvtAnim, mot) == 0x198, "");
static_assert(offsetof(GfComEvtAnim, resAsm) == 0x550, "");
static_assert(offsetof(GfComEvtAnim, state) == 0x558, "");
static_assert(offsetof(GfComEvtAnim, isLocalSpace) == 0x580, "");
static_assert(sizeof(GfComEvtAnim) == 0x588, "");

} // namespace gf
