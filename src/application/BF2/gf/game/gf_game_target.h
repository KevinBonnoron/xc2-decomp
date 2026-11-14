#pragma once
#include <stddef.h>

#include "ai/ai_state.h"
#include "ai/ai_state_fsm.h"
#include "framework/message/message_object.h"
#include "fw/fw_pad.h"
#include "fw/fw_param_manager.h"
#include "gf/event/gf_event.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
class Reflection;
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
struct GF_SEARCH_OBJ;
struct GfSearchInfo;
struct GfSetupParam;
struct MsgGameChangeTarget;
struct MsgGameDebugTarget;

class GfGameTarget : public mm::mtl::PtrSingleton<GfGameTarget>, public fw::MessageObject, public IGfEvent {
public:
  struct Param {
    static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

    f32 nearRadius;
    f32 nearAngle;
    f32 fadeTime;
    f32 resetKeyTime;
  };

  class StateDriverNotActive;
  class StateAutoTarget;
  class StateEnemyTarget;
  class StateBattleTarget;

  // Inferred role: ids of the states registered by setup; original enumerator names unknown.
  enum {
    STATE_UNKNOWN_0 = 0, // Inferred role: state driver not active; original name unknown.
    STATE_UNKNOWN_1 = 1, // Inferred role: state auto target; original name unknown.
    STATE_UNKNOWN_2 = 2, // Inferred role: state enemy target; original name unknown.
    STATE_UNKNOWN_3 = 3, // Inferred role: state battle target; original name unknown.
  };

  GfGameTarget();
  ~GfGameTarget();
  static fw::Reflection *createReflection();
  static void build(const GfSetupParam &param);
  void setup(const GfSetupParam &param);
  static void destroy();
  void cleanup();
  static void update(const fw::UpdateInfo &info);
  void updateImpl(const fw::UpdateInfo &info);
  static bool testActive();
  static bool testLockTarget();
  static void lockTarget(bool isLock);
  static void setDispTargetMode(bool isDisp);
  static bool testDispTargetMode();
  static void disableTargetWithoutEnemy();
  void changeBattleTarget(bool isEnable);
  void changeMode();
  void selectRight();
  void selectLeft();
  void startNearTarget();
  void judgeNearTarget();
  void destroySearchObj();
  const Param *getParam() const;
  void resetTarget();
  void notifyTarget();
  void createSearchObj();
  GfSearchInfo *selectTarget(const mm::mtl::FixedList<GfSearchInfo *, 256> &list);
  void setTarget(GF_OBJ_HANDLE *handle);
  void updateTarget(const mm::mtl::FixedList<GfSearchInfo *, 256> &list);
  void fadeOutTarget();
  bool setTargetNearest(const mm::mtl::FixedList<GfSearchInfo *, 256> &list);
  bool isSwimPlayer() const;
  bool isWaterHole(GF_OBJ_HANDLE *handle);
  bool setTargetNearestEnemy(const mm::mtl::FixedList<GfSearchInfo *, 256> &list);
  bool setTargetNearestEnemyBattle(const mm::mtl::FixedList<GfSearchInfo *, 256> &list);
  // The order of the overrides follows the game's vtable (0x710118c008).
  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void gevChangeLeader(GF_OBJ_HANDLE *handle) override;
  void gevSwapFormation(u32 slot, u32 otherSlot) override;
  void procMsgGameChangeTarget(fw::MessageObject *sender, MsgGameChangeTarget &message);
  void procMsgGameDebugTarget(fw::MessageObject *sender, MsgGameDebugTarget &message);

  // Inferred role: switches the target and requests its notification; original name unknown.
  void unknown001(GF_OBJ_HANDLE *handle) {
    if (unknownb8 != handle) {
      unknownb8 = handle;
      unknownc0 = true;
      unknownc2 = false;
    }
  }

  // Inferred role: tests that the state machine left StateDriverNotActive; original name unknown.
  static bool unknown002(const ai::Fsm &fsm) {
    const ai::State *state = fsm.getState();
    return state != nullptr && state->unknown08 != STATE_UNKNOWN_0;
  }

  // Inferred role: first param of the list, without the checks of getParam; original name unknown.
  const Param *unknown003() const { return static_cast<const Param *>(unknown110->unknown10->param); }

  ai::Fsm unknown28;                               // Inferred role: state machine; original member name unknown.
  GF_SEARCH_OBJ *unknowna0;                        // Inferred role: enemy search; original member name unknown.
  GF_SEARCH_OBJ *unknowna8;                        // Inferred role: near target search; original member name unknown.
  GF_OBJ_HANDLE *unknownb0;                        // Inferred role: control mover; original member name unknown.
  GF_OBJ_HANDLE *unknownb8;                        // Inferred role: target; original member name unknown.
  bool unknownc0;                                  // Inferred role: target changed; original member name unknown.
  bool unknownc1;                                  // Inferred role: target locked; original member name unknown.
  bool unknownc2;                                  // Inferred role: target fading out; original member name unknown.
  f32 unknownc4;                                   // Inferred role: fade out time; original member name unknown.
  bool unknownc8;                                  // Inferred role: change mode requested; original member name unknown.
  bool unknownc9;                                  // Inferred role: select right requested; original member name unknown.
  bool unknownca;                                  // Inferred role: select left requested; original member name unknown.
  bool unknowncb;                                  // Inferred role: near target judged; original member name unknown.
  bool unknowncc;                                  // Inferred role: near target counting; original member name unknown.
  f32 unknownd0;                                   // Inferred role: near target time; original member name unknown.
  fw::PadRelay unknownd8;                          // Inferred role: pad relay; original member name unknown.
  mm::mtl::IntrusivePtr<fw::ParamList> unknown110; // Inferred role: param list; original member name unknown.
};

static_assert(offsetof(GfGameTarget, unknown28) == 0x28, "");
static_assert(offsetof(GfGameTarget, unknowna0) == 0xa0, "");
static_assert(offsetof(GfGameTarget, unknownb8) == 0xb8, "");
static_assert(offsetof(GfGameTarget, unknownc0) == 0xc0, "");
static_assert(offsetof(GfGameTarget, unknownc4) == 0xc4, "");
static_assert(offsetof(GfGameTarget, unknownc8) == 0xc8, "");
static_assert(offsetof(GfGameTarget, unknownd0) == 0xd0, "");
static_assert(offsetof(GfGameTarget, unknownd8) == 0xd8, "");
static_assert(offsetof(GfGameTarget, unknown110) == 0x110, "");
static_assert(sizeof(GfGameTarget::Param) == 0x10, "");
static_assert(sizeof(GfGameTarget) == 0x118, "");

bool isEnableTarget(GF_OBJ_HANDLE *handle);
bool isEnableTargetBattle(GF_OBJ_HANDLE *handle);
bool disableTarget(GF_OBJ_HANDLE *handle);
bool disableTargetBattle(GF_OBJ_HANDLE *handle);

} // namespace gf
