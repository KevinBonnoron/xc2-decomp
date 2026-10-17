#pragma once
#include "framework/framework.h"
#include "gf/event/gf_event.h"
#include "ml/ml_mem.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct SDataGame;
struct SDataOption;
struct SDataSystem;

struct GfSetupParam {
  GfSetupParam() : _00(), _08(), _10(), memHandle(ml::MlMem::getProductMem()), _1c(), globalSpeed(1.0f), exec(EXEC_STATE_DEBUG) {}

  u8 _00[0x08 - 0x00];
  u8 _08[0x10 - 0x08];
  u8 _10[0x18 - 0x10];
  mtl::ALLOC_HANDLE memHandle;
  u8 _1c[0x20 - 0x1c];
  f32 globalSpeed;
  EXEC_STATE exec;
};

static_assert(offsetof(GfSetupParam, memHandle) == 0x18, "");
static_assert(offsetof(GfSetupParam, exec) == 0x24, "");
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

  GfSetupParam setupParam;
  bool initialized;
  bool destroyNow;
  EXEC_STATE exec;
  u16 execFlags;
  GAME_START gameStart;
  u32 frameCount;
  f32 loadGameTime;
  bool existSaveData;
};

static_assert(offsetof(GfManager, setupParam) == 0x18, "");
static_assert(offsetof(GfManager, initialized) == 0x40, "");
static_assert(offsetof(GfManager, exec) == 0x44, "");
static_assert(offsetof(GfManager, execFlags) == 0x48, "");
static_assert(offsetof(GfManager, gameStart) == 0x4c, "");
static_assert(offsetof(GfManager, loadGameTime) == 0x54, "");
static_assert(offsetof(GfManager, existSaveData) == 0x58, "");
static_assert(sizeof(GfManager) == 0x60, "");

} // namespace gf
