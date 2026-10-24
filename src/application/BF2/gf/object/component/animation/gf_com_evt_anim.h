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
    CallBack() : unknown00(nullptr) {}

    const char *unknown00;      // Inferred role: name; original member name unknown.
    CallBackDelegate unknown08; // Inferred role: delegate; original member name unknown.
  };

  class Asm {
  public:
    class AsmLisener : public anm::AsmListener {
    public:
      void callback(CallBackType type, const anm::AsmAnnotetion &annotation) override { unknown08->cacheCallback(type, annotation); }

      Asm *unknown08; // Inferred role: owner; original member name unknown.
    };

    class ViewerListener {
    public:
      virtual void onWkStandbyLogout() {
        if (unknown08 != nullptr) {
          unknown08->unknown180 = nullptr;
        }
      }

      Asm *unknown08; // Inferred role: owner; original member name unknown.
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

    mm::mtl::BitFlag<32> unknown00;            // Inferred role: flags; original member name unknown.
    GfComModel *unknown08;                     // Inferred role: model; original member name unknown.
    anm::ASMControl *unknown10;                // Inferred role: asm control; original member name unknown.
    fw::AnimAsmUpdater unknown18;              // Inferred role: updater; original member name unknown.
    fw::AnimEventAsmPoseSampler unknown38;     // Inferred role: pose sampler; original member name unknown.
    CallBack unknown70[CALLBACK_MAX];          // Inferred role: callbacks; original member name unknown.
    AsmLisener unknown138;                     // Inferred role: listener; original member name unknown.
    mm::mtl::Vector<CallBackCache> unknown148; // Inferred role: callback caches; original member name unknown.
    ViewerListener unknown170;                 // Inferred role: viewer listener; original member name unknown.
    void *unknown180;                          // Inferred role: viewer; original member name unknown.
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

    mm::mtl::BitFlag<32> unknown00;                                 // Inferred role: flags; original member name unknown.
    GfComModel *unknown08;                                          // Inferred role: model; original member name unknown.
    anm::ResASM *unknown10;                                         // Inferred role: res asm; original member name unknown.
    anm::Blender *unknown18;                                        // Inferred role: blender; original member name unknown.
    fw::AnimBlenderUpdater unknown20;                               // Inferred role: blender updater; original member name unknown.
    fw::AnimEventMotPoseSamper unknown40;                           // Inferred role: pose sampler; original member name unknown.
    mm::mtl::FixedVector<anm::Control *, EASE_MAX> unknown78;       // Inferred role: ease controls; original member name unknown.
    mm::mtl::FixedVector<mm::mtl::FixStr<32>, EASE_MAX> unknown100; // Inferred role: ease names; original member name unknown.
    anm::Control *unknown348[MOTION_MAX];                           // Inferred role: controls; original member name unknown.
    f32 unknown388[MOTION_MAX];                                     // Inferred role: play back times; original member name unknown.
    u64 unknown3a8;                                                 // Inferred role: control count; original member name unknown.
    u32 unknown3b0;                                                 // Inferred role: current; original member name unknown.
    f32 unknown3b4;                                                 // Inferred role: speed; original member name unknown.
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

  Asm unknown10;                   // Inferred role: anim asm; original member name unknown.
  Mot unknown198;                  // Inferred role: mot; original member name unknown.
  anm::ResASM *unknown550;         // Inferred role: res asm; original member name unknown.
  mm::mtl::FixStr<32> unknown558;  // Inferred role: state; original member name unknown.
  mm::mtl::BitFlag<32> unknown57c; // Inferred role: flags; original member name unknown.
  bool unknown580;                 // Inferred role: local space; original member name unknown.
};

static_assert(offsetof(GfComEvtAnim::Asm, unknown08) == 0x08, "");
static_assert(offsetof(GfComEvtAnim::Asm, unknown10) == 0x10, "");
static_assert(offsetof(GfComEvtAnim::Asm, unknown18) == 0x18, "");
static_assert(offsetof(GfComEvtAnim::Asm, unknown38) == 0x38, "");
static_assert(offsetof(GfComEvtAnim::Asm, unknown70) == 0x70, "");
static_assert(offsetof(GfComEvtAnim::Asm, unknown138) == 0x138, "");
static_assert(offsetof(GfComEvtAnim::Asm, unknown148) == 0x148, "");
static_assert(offsetof(GfComEvtAnim::Asm, unknown170) == 0x170, "");
static_assert(offsetof(GfComEvtAnim::Asm, unknown180) == 0x180, "");
static_assert(sizeof(GfComEvtAnim::Asm) == 0x188, "");
static_assert(offsetof(GfComEvtAnim::Mot, unknown08) == 0x08, "");
static_assert(offsetof(GfComEvtAnim::Mot, unknown18) == 0x18, "");
static_assert(offsetof(GfComEvtAnim::Mot, unknown20) == 0x20, "");
static_assert(offsetof(GfComEvtAnim::Mot, unknown40) == 0x40, "");
static_assert(offsetof(GfComEvtAnim::Mot, unknown78) == 0x78, "");
static_assert(offsetof(GfComEvtAnim::Mot, unknown100) == 0x100, "");
static_assert(offsetof(GfComEvtAnim::Mot, unknown348) == 0x348, "");
static_assert(offsetof(GfComEvtAnim::Mot, unknown388) == 0x388, "");
static_assert(offsetof(GfComEvtAnim::Mot, unknown3a8) == 0x3a8, "");
static_assert(offsetof(GfComEvtAnim::Mot, unknown3b0) == 0x3b0, "");
static_assert(offsetof(GfComEvtAnim::Mot, unknown3b4) == 0x3b4, "");
static_assert(sizeof(GfComEvtAnim::Mot) == 0x3b8, "");
static_assert(offsetof(GfComEvtAnim, unknown10) == 0x10, "");
static_assert(offsetof(GfComEvtAnim, unknown198) == 0x198, "");
static_assert(offsetof(GfComEvtAnim, unknown550) == 0x550, "");
static_assert(offsetof(GfComEvtAnim, unknown558) == 0x558, "");
static_assert(offsetof(GfComEvtAnim, unknown580) == 0x580, "");
static_assert(sizeof(GfComEvtAnim) == 0x588, "");

} // namespace gf
