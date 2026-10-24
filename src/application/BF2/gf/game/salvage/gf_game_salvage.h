#pragma once
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
struct Vec3;
}

namespace gf {

struct GAME_VOICE_HANDLE;
class GfMenuCallContext;
struct GF_OBJ_HANDLE;
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

private:
  u8 _18[0x48 - 0x18];
};

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

private:
  u8 _18[0x20 - 0x18];
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
    STATE_WAIT,
    STATE_TBOX_CHECK,
    STATE_ERROR_MESSAGE,
    STATE_ITEM_SELECT,
    STATE_SETUP_FADE_OUT,
    STATE_LOAD,
    STATE_SETUP_FADE_IN,
    STATE_SKILL_CHECK,
    STATE_START_VOICE,
    STATE_DIVE_START,
    STATE_DIVE_WAIT,
    STATE_DIVE_END,
    STATE_DIVE_FADE_OUT,
    STATE_DIVE_FADE_WAIT,
    STATE_DIVE_FADE_IN,
    STATE_CLIMB_START,
    STATE_RESULT,
    STATE_RESULT_UI,
    STATE_PARTY_FORM_DELAY,
    STATE_CAM_WAIT,
    STATE_FINISH,
    STATE_MAX,
  };

  enum VoiceType {
    VOICE_START,
    VOICE_START_SKILL,
  };

  enum AnimationType {
    ANIMATION_IDLE,
    ANIMATION_SALVAGE,
    ANIMATION_SUCCESS,
    ANIMATION_GREAT_SUCCESS,
    ANIMATION_FAILURE,
    ANIMATION_RESULT_00,
    ANIMATION_RESULT_01,
    ANIMATION_RESULT_02,
    ANIMATION_RESULT_03,
    ANIMATION_RESULT_04,
    ANIMATION_RESULT_05,
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
  void execPop();
  void createModel();
  void destroyModel();
  bool isValidModel();
  bool isAnimationEnd() const;
  void setModelTransform(const mm::Vec3 &position, f32 rotation);
  void setPartyDisp(bool isDisp);
  void playVoice(VoiceType voice);
  bool isVoiceEnd();
  void playClimbReady();
  AnimationType getClimbAnimationType() const;
  void playWireStart(f32 time, f32 speed, f32 length);
  void addSalvagerPoint(u32 point);
  static bool isChaseKikuInSupervia();
  static void createLog();
  static void setLogSkill(bool isSuccess, u32 skill);
  static void clearLogSkill();
  static void setLogButtonChallenge(int index, int challenge);
  static void clearLogButtonChallenge();
  static void setLogButtonChallengeResult(int result);
  static void setLogLapsedTime(int time);

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
