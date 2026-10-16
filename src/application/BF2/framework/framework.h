#pragma once
#include <stddef.h>

#include "framework/memory/allocator.h"
#include "fw/fw_update_info.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace ml {
class Scn;
} // namespace ml

namespace fw {

class Applet;
class IPauseTrigger;

struct FrameworkConfig {
  u8 _00[0x04 - 0x00];
  f32 frameRate;
  u8 _08[0x3c - 0x08];
};

static_assert(sizeof(FrameworkConfig) == 0x3c, "");

struct UpdateState {
  bool isPause;
};

class ILauncher {
public:
  virtual void setDebugPause(bool isPause) = 0;
  virtual void stepDebugPause() = 0;
  virtual bool isDebugPause() const = 0;
  virtual bool resetApp() = 0;
};

struct LayerUpdateInfo {
  f32 speed;
  f32 scaledSpeed;
  f32 frameSpeed;
  bool pause;
  bool framePause;
};

static_assert(sizeof(LayerUpdateInfo) == 0x10, "");

class Framework : public mm::mtl::PtrSingleton<Framework> {
public:
  enum State {
    STATE_NONE = 0,
    STATE_INITIALIZED = 1,
    STATE_MANAGER_INITIALIZED = 2,
    STATE_ENTERED = 3,
    STATE_FINALIZING = 4,
    STATE_FINALIZED = 5,
  };

  static const u32 LAYER_MAX = 32;
  static const u32 PAUSE_TRIGGER_MAX = 32;

  ~Framework();
  void finalize();
  static mm::mtl::IAllocator *getAllocator();
  bool initializeManager();
  void destroyManager();
  bool finalizeManager();
  void prepareEnter();
  void prepareExit();
  void pauseEnter();
  void pauseExit();
  void activate();
  void deactivate();
  void endFrame(const UpdateState &updateState);
  void preUpdate();
  static bool canUpdate();
  void render();
  Applet *getApplet() const;
  bool isAppletClosed();
  void destroyApplet();
  void enterFinalizeApplet();
  static bool isInitialized();
  static mtl::ALLOC_HANDLE getMemHandle();
  static void setPause(bool isPause);
  static bool isPause();
  static void stepPause();
  static bool reqSoftReset();
  static void setUpdateSpeed(f32 speed);
  static void setLayerUpdateSpeed(u32 layer, f32 speed);
  static f32 getLayerUpdateSpeed(u32 layer);
  static void setLayerPause(u32 layer, bool isPause);
  static bool isLayerPause(u32 layer);
  static u32 getFrameCount();
  static const UpdateInfo *getUpdateInfo();
  static void addPauseCallback(IPauseTrigger *trigger);
  static void removePauseCallback(IPauseTrigger *trigger);

  bool isUpdating() const { return state >= STATE_MANAGER_INITIALIZED && state <= STATE_FINALIZING; }

  Applet *applet;
  FrameworkConfig config;
  u8 _4c[0x58 - 0x4c];
  ml::Scn *scn;
  u8 _60[0x68 - 0x60];
  mtl::ALLOC_HANDLE memHandle;
  ILauncher *launcher;
  UpdateInfo updateInfo;
  u32 state;
  u8 _88[0x8c - 0x88];
  f32 updateSpeed;
  u8 _90[0x98 - 0x90];
  LayerUpdateInfo layers[LAYER_MAX];
  mm::mtl::FixedVector<IPauseTrigger *, PAUSE_TRIGGER_MAX> pauseTriggers;
  MemHandlebaseAllocator allocator;
};

static_assert(offsetof(Framework, config) == 0x10, "");
static_assert(offsetof(Framework, scn) == 0x58, "");
static_assert(offsetof(Framework, memHandle) == 0x68, "");
static_assert(offsetof(Framework, launcher) == 0x70, "");
static_assert(offsetof(Framework, updateInfo) == 0x78, "");
static_assert(offsetof(Framework, state) == 0x84, "");
static_assert(offsetof(Framework, updateSpeed) == 0x8c, "");
static_assert(offsetof(Framework, layers) == 0x98, "");
static_assert(offsetof(Framework, pauseTriggers) == 0x298, "");
static_assert(offsetof(Framework, allocator) == 0x3a0, "");
static_assert(sizeof(Framework) == 0x3f0, "");

class IPauseTrigger {
public:
  IPauseTrigger();
  virtual ~IPauseTrigger();
  virtual void enterPauseCallback() {}
  virtual void exitPauseCallback() {}
  virtual void updatePauseCallback() {}
  virtual void activate() {}
  virtual void deactivate() {}
};

} // namespace fw
