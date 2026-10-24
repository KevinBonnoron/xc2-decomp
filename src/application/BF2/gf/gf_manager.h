#pragma once
#include "framework/framework.h"
#include "gf/event/gf_event.h"
#include "ml/ml_mem.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"
#include <stddef.h>

namespace ml {
class Scn;
}

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct SDataGame;
struct SDataOption;
struct SDataSystem;

struct GfSetupParam {
  GfSetupParam() : unknown00(), _08(), _10(), unknown18(ml::MlMem::getProductMem()), unknown1c(0), unknown20(1.0f), unknown24(EXEC_STATE_DEBUG) {}

  ml::Scn *unknown00; // Inferred role: scn; original member name unknown.
  u8 _08[0x10 - 0x08];
  u8 _10[0x18 - 0x10];
  mtl::ALLOC_HANDLE unknown18; // Inferred role: mem handle; original member name unknown.
  u32 unknown1c;               // Inferred role: slot mapping type; original member name unknown.
  f32 unknown20;               // Inferred role: global speed; original member name unknown.
  EXEC_STATE unknown24;        // Inferred role: exec; original member name unknown.
};

static_assert(offsetof(GfSetupParam, unknown18) == 0x18, "");
static_assert(offsetof(GfSetupParam, unknown24) == 0x24, "");
static_assert(sizeof(GfSetupParam) == 0x28, "");

void GfSleep(u32 frame);

class GfManager : public mm::mtl::PtrSingleton<GfManager>, public fw::IPauseTrigger, public IGfEvent {
public:
  enum GAME_START {
    GAME_START_NONE,
    GAME_START_NEW,
    GAME_START_CONTINUE,
  };

  GfManager(const GfSetupParam &param);
  static void setExec(EXEC_STATE exec);
  ~GfManager();
  static void build(const GfSetupParam &param);
  void initialize();
  static void setupDeafult();
  static void destroy();
  void finalize();
  static bool isInitialized();
  static bool isDestroyed();
  static bool isDestroyNow();
  static GfSetupParam &getSetupParam();
  void updatePauseCallback() override;
  static u32 getFrameCount();
  static bool isExecKillPartyCreate();
  static bool isExecModeScenarioGame();
  static bool isExecModeAdvertize();
  static bool isExecModeTool();
  static bool isExecModeDebug();
  static bool isExecModeThater();
  static void setupNewGame();
  static void setupPowerNewGame(const SDataSystem &dataSystem, const SDataGame &dataGame, const SDataOption &dataOption);
  static void setupContinueGame(const SDataSystem &dataSystem, const SDataGame &dataGame, const SDataOption &dataOption);
  static void setupEventTheater();
  static void setupReturnTitle();
  static void setupOptionData(const SDataOption &dataOption);
  static bool isContinueGame();
  static bool isNewGame();
  static bool isExistSaveData();
  static void setSaveDataCreated();
  static void startGame(bool isExistSaveData, bool isClearGameCheck);
  static void startEventTheater(const mm::mtl::FixedVector<u16, 8> &events);
  static void execToAdvertize();
  void gevGameState(GF_STATE previousState, GF_STATE state) override;
  void activate() override;
  static void postUpdate(const fw::UpdateInfo &info);
  static void update(const fw::UpdateInfo &info);

  static GfManager *s_pThis;

  GfSetupParam unknown18; // Inferred role: setup param; original member name unknown.
  bool unknown40;         // Inferred role: initialized; original member name unknown.
  bool unknown41;         // Inferred role: destroy now; original member name unknown.
  EXEC_STATE unknown44;   // Inferred role: exec; original member name unknown.
  u16 unknown48;          // Inferred role: exec flags; original member name unknown.
  GAME_START unknown4c;   // Inferred role: game start; original member name unknown.
  u32 unknown50;          // Inferred role: frame count; original member name unknown.
  f32 unknown54;          // Inferred role: load game time; original member name unknown.
  bool unknown58;         // Inferred role: exist save data; original member name unknown.
};

static_assert(offsetof(GfManager, unknown18) == 0x18, "");
static_assert(offsetof(GfManager, unknown40) == 0x40, "");
static_assert(offsetof(GfManager, unknown44) == 0x44, "");
static_assert(offsetof(GfManager, unknown48) == 0x48, "");
static_assert(offsetof(GfManager, unknown4c) == 0x4c, "");
static_assert(offsetof(GfManager, unknown54) == 0x54, "");
static_assert(offsetof(GfManager, unknown58) == 0x58, "");
static_assert(sizeof(GfManager) == 0x60, "");

} // namespace gf
