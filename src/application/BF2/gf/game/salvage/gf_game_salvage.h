#pragma once
#include <stddef.h>

#include "ai/ai_state.h"
#include "ai/ai_state_fsm.h"
#include "gf/gf_state.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
class Camera;
} // namespace fw

namespace mm {
struct Mat44;
struct Vec3;
} // namespace mm

namespace gf {

struct GAME_VOICE_HANDLE;
class GfMenuCallContext;
struct GF_OBJ_HANDLE;
class GfComAsm;
class GfComBehaviorSalvage;
class GfEvtModelSalvage;
class GfGameSalvage;
struct GfSetupParam;

class StateSalvageWait : public ai::State {
  GF_STATE_CLASS(StateSalvageWait, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);
};

class StateSalvageTBoxCheck : public ai::State {
  GF_STATE_CLASS(StateSalvageTBoxCheck, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);
};

class StateSalvageErrorMessage : public ai::State {
  GF_STATE_CLASS(StateSalvageErrorMessage, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);

private:
  GfMenuCallContext *context;
};

class StateSalvageItemSelect : public ai::State {
  GF_STATE_CLASS(StateSalvageItemSelect, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);

private:
  GfMenuCallContext *context;
};

class StateSalvageSetupFadeOut : public ai::State {
  GF_STATE_CLASS(StateSalvageSetupFadeOut, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);

private:
  long startClock;
};

class StateSalvageLoad : public ai::State {
  GF_STATE_CLASS(StateSalvageLoad, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);
};

class StateSalvageSetupFadeIn : public ai::State {
  GF_STATE_CLASS(StateSalvageSetupFadeIn, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);

private:
  long startClock;
};

class StateSalvageSkillCheck : public ai::State {
  GF_STATE_CLASS(StateSalvageSkillCheck, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);

private:
  mm::mtl::FixedVector<u32, 8> skills;
};

class StateSalvageStartVoice : public ai::State {
  GF_STATE_CLASS(StateSalvageStartVoice, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);

private:
  long startClock;
};

class StateSalvageDiveStart : public ai::State {
  GF_STATE_CLASS(StateSalvageDiveStart, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);
  void callback();

  GfMenuCallContext *unknown18[3]; // Inferred role: contexts of the button challenges; original member name unknown.
  int unknown30;                   // Inferred role: number of button challenges started; original member name unknown.
  u32 unknown34;                   // Inferred role: current button challenge id; original member name unknown.
  int unknown38;                   // Inferred role: number of great successes; original member name unknown.
  u32 unknown3c[3];                // Inferred role: button challenge id of each step; original member name unknown.
};

static_assert(offsetof(StateSalvageDiveStart, unknown18) == 0x18, "");
static_assert(offsetof(StateSalvageDiveStart, unknown30) == 0x30, "");
static_assert(offsetof(StateSalvageDiveStart, unknown3c) == 0x3c, "");
static_assert(sizeof(StateSalvageDiveStart) == 0x48, "");

class StateSalvageDiveWait : public ai::State {
  GF_STATE_CLASS(StateSalvageDiveWait, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);
};

class StateSalvageDiveEnd : public ai::State {
  GF_STATE_CLASS(StateSalvageDiveEnd, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);
};

class StateSalvageDiveFadeOut : public ai::State {
  GF_STATE_CLASS(StateSalvageDiveFadeOut, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);

private:
  long startClock;
};

class StateSalvageDiveFadeWait : public ai::State {
  GF_STATE_CLASS(StateSalvageDiveFadeWait, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);

private:
  long startClock;
};

class StateSalvageDiveFadeIn : public ai::State {
  GF_STATE_CLASS(StateSalvageDiveFadeIn, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);

private:
  long startClock;
};

class StateSalvageClimbStart : public ai::State {
  GF_STATE_CLASS(StateSalvageClimbStart, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);
  void callback();

private:
  u8 unknown18; // Inferred role: climb animation type; original member name unknown.
  u8 unknown19; // Inferred role: number of vibrations played; original member name unknown.
  u8 _1a[0x20 - 0x1a];
};

class StateSalvageResult : public ai::State {
  GF_STATE_CLASS(StateSalvageResult, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);

private:
  long startClock;
  bool isVibrated;
};

class StateSalvageResultUi : public ai::State {
  GF_STATE_CLASS(StateSalvageResultUi, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);

private:
  GfMenuCallContext *context;
};

class StateSalvagePartyFormDelay : public ai::State {
  GF_STATE_CLASS(StateSalvagePartyFormDelay, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);

private:
  long startClock;
};

class StateSalvageCamWait : public ai::State {
  GF_STATE_CLASS(StateSalvageCamWait, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);

private:
  long startClock;
};

class StateSalvageFinish : public ai::State {
  GF_STATE_CLASS(StateSalvageFinish, GfGameSalvage)
  void enter(GfGameSalvage *salvage, ai::State *previous);
  void leave(GfGameSalvage *salvage, ai::State *next);
  void update(GfGameSalvage *salvage, const fw::UpdateInfo &info);

private:
  long startClock;
};

class GfGameSalvage : public mm::mtl::PtrSingleton<GfGameSalvage> {
public:
  enum STATE {
    STATE_UNKNOWN_0,  // Inferred role: state wait; original name unknown.
    STATE_UNKNOWN_1,  // Inferred role: state tbox check; original name unknown.
    STATE_UNKNOWN_2,  // Inferred role: state error message; original name unknown.
    STATE_UNKNOWN_3,  // Inferred role: state item select; original name unknown.
    STATE_UNKNOWN_4,  // Inferred role: state setup fade out; original name unknown.
    STATE_UNKNOWN_5,  // Inferred role: state load; original name unknown.
    STATE_UNKNOWN_6,  // Inferred role: state setup fade in; original name unknown.
    STATE_UNKNOWN_7,  // Inferred role: state skill check; original name unknown.
    STATE_UNKNOWN_8,  // Inferred role: state start voice; original name unknown.
    STATE_UNKNOWN_9,  // Inferred role: state dive start; original name unknown.
    STATE_UNKNOWN_10, // Inferred role: state dive wait; original name unknown.
    STATE_UNKNOWN_11, // Inferred role: state dive end; original name unknown.
    STATE_UNKNOWN_12, // Inferred role: state dive fade out; original name unknown.
    STATE_UNKNOWN_13, // Inferred role: state dive fade wait; original name unknown.
    STATE_UNKNOWN_14, // Inferred role: state dive fade in; original name unknown.
    STATE_UNKNOWN_15, // Inferred role: state climb start; original name unknown.
    STATE_UNKNOWN_16, // Inferred role: state result; original name unknown.
    STATE_UNKNOWN_17, // Inferred role: state result ui; original name unknown.
    STATE_UNKNOWN_18, // Inferred role: state party form delay; original name unknown.
    STATE_UNKNOWN_19, // Inferred role: state cam wait; original name unknown.
    STATE_UNKNOWN_20, // Inferred role: state finish; original name unknown.
    // STATE_MAX is the number of enumerators above.
    STATE_MAX,
  };

  enum VoiceType {
    VOICETYPE_UNKNOWN_0, // Inferred role: voice start; original name unknown.
    VOICETYPE_UNKNOWN_1, // Inferred role: voice start skill; original name unknown.
    VOICETYPE_UNKNOWN_2,
    VOICETYPE_UNKNOWN_3,
    VOICETYPE_UNKNOWN_4,
    VOICETYPE_UNKNOWN_5,
    VOICETYPE_UNKNOWN_6,
  };

  enum AnimationType {
    ANIMATION_UNKNOWN_0,  // Inferred role: animation idle; original name unknown.
    ANIMATION_UNKNOWN_1,  // Inferred role: animation salvage; original name unknown.
    ANIMATION_UNKNOWN_2,  // Inferred role: animation success; original name unknown.
    ANIMATION_UNKNOWN_3,  // Inferred role: animation great success; original name unknown.
    ANIMATION_UNKNOWN_4,  // Inferred role: animation failure; original name unknown.
    ANIMATION_UNKNOWN_5,  // Inferred role: animation result 00; original name unknown.
    ANIMATION_UNKNOWN_6,  // Inferred role: animation result 01; original name unknown.
    ANIMATION_UNKNOWN_7,  // Inferred role: animation result 02; original name unknown.
    ANIMATION_UNKNOWN_8,  // Inferred role: animation result 03; original name unknown.
    ANIMATION_UNKNOWN_9,  // Inferred role: animation result 04; original name unknown.
    ANIMATION_UNKNOWN_10, // Inferred role: animation result 05; original name unknown.
  };

  enum SEID {
    SEID_UNKNOWN_604 = 0x25c, // Inferred role: sound effect played when the dive starts; original name unknown.
  };

  struct RaffleInfo {
    u32 unknown00; // Inferred role: number of treasure boxes; original member name unknown.
    f32 unknown04; // Inferred role: button challenge point; original member name unknown.
    u32 unknown08; // Inferred role: skill point; original member name unknown.
  };

  struct RaffleRet {
    RaffleRet() : unknown00(0), unknown04(0), unknown08(false), unknown09(false) {}

    u32 unknown00;  // Inferred role: number of treasure boxes; original member name unknown.
    u32 unknown04;  // Inferred role: highest RSC_ID of the treasure boxes; original member name unknown.
    bool unknown08; // Inferred role: enemies pop; original member name unknown.
    bool unknown09; // Inferred role: a powerful enemy pops; original member name unknown.
  };

  GfGameSalvage(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfGameSalvage();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void update(const fw::UpdateInfo &info);
  static void startSalvage(GF_OBJ_HANDLE *handle);
  static bool isStateWait();
  static void cancelSalvage();
  void createCameraDiveStart(const mm::Vec3 &position, f32 rotation);
  void createCameraDive(AnimationType animation, const mm::Vec3 &position, f32 rotation);
  void createCameraClimb(AnimationType animation, const mm::Vec3 &position, f32 rotation);
  void createCameraCut01(const mm::Vec3 &position, f32 rotation);
  void destroyCameraDiveStart();
  void destroyCameraDive();
  void destroyCameraClimb();
  void destroyCameraCut01();
  void playCameraDiveStart();
  void playCameraDive();
  void playCameraClimb();
  void playCameraCut01();
  bool isCameraDiveStartEnd();
  bool isCameraDiveEnd();
  bool isCameraClimbEnd();
  bool isCameraCut01End();
  bool isCameraDive();
  bool isTboxExist() const;
  u8 *getBindedBdatFp() const;
  int getBindedBdatId() const;
  bool getEventOrigin(mm::Mat44 &matrix) const;
  bool getEventTbox(mm::Mat44 &matrix) const;
  bool applyPartyForm() const;
  void execPop();
  bool getRaffleResult(RaffleRet &ret) const;
  void createModel();
  void destroyModel();
  bool isValidModel();
  GfComAsm *getGfComAsm() const;
  GfComBehaviorSalvage *getGfComBehaviorSalvage() const;
  void playAnimation(AnimationType animation);
  bool isAnimationEnd() const;
  u32 getButtonChallengeId(int index);
  void setModelTransform(const mm::Vec3 &position, f32 rotation);
  void setPartyDisp(bool isDisp);
  void playVoice(VoiceType voice);
  bool isVoiceEnd();
  void playClimbReady();
  void playClimb();
  bool isClimbEnd();
  AnimationType getClimbAnimationType() const;
  void playWireStart(f32 time, f32 speed, f32 length);
  void addSalvagerPoint(u32 point);
  bool isChaseKikuInSupervia();
  void createLog();
  void setLogSkill(bool isSuccess, u32 skill);
  void clearLogSkill();
  void setLogButtonChallenge(int index, int challenge);
  void clearLogButtonChallenge();
  void setLogButtonChallengeResult(int result);
  void setLogLapsedTime(int time);
  u32 getTBoxNum();
  void execRaffle(const RaffleInfo &info);
  void calcClimb();
  void playSE(SEID id);
  void playDiveVibration();

  ai::Fsm unknown08;                           // Inferred role: fsm; original member name unknown.
  mm::mtl::IntrusivePtr<fw::Camera> unknown80; // Inferred role: camera dive start; original member name unknown.
  mm::mtl::IntrusivePtr<fw::Camera> unknown88; // Inferred role: camera dive; original member name unknown.
  mm::mtl::IntrusivePtr<fw::Camera> unknown90; // Inferred role: camera climb; original member name unknown.
  mm::mtl::IntrusivePtr<fw::Camera> unknown98; // Inferred role: camera cut 01; original member name unknown.
  bool unknowna0;                              // Inferred role: initialized; original member name unknown.
  GF_OBJ_HANDLE *unknowna8;                    // Inferred role: handle; original member name unknown.
  int unknownb0;                               // Inferred role: button challenge point; original member name unknown.
  int unknownb4;                               // Inferred role: skill point; original member name unknown.
  u32 unknownb8;                               // Inferred role: cylinder item; original member name unknown.
  GfEvtModelSalvage *unknownc0;                // Inferred role: model; original member name unknown.
  GAME_VOICE_HANDLE *unknownc8;                // Inferred role: voice; original member name unknown.
  AnimationType m_climbAnimationType;
  u32 unknownd4; // Inferred role: climb voice; original member name unknown.
  u32 unknownd8; // Inferred role: dive vibration; original member name unknown.
};

static_assert(sizeof(GfGameSalvage) == 0xe0, "");

} // namespace gf
