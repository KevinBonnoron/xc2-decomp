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
class WinProc;
} // namespace ml

namespace fw {

class Applet;
class IPauseTrigger;

struct FrameworkConfig {
  u8 _00[0x04 - 0x00];
  f32 unknown04; // Inferred role: frame rate; original member name unknown.
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
  f32 unknown00;  // Inferred role: speed; original member name unknown.
  f32 unknown04;  // Inferred role: scaled speed; original member name unknown.
  f32 unknown08;  // Inferred role: frame speed; original member name unknown.
  bool unknown0c; // Inferred role: pause; original member name unknown.
  bool unknown0d; // Inferred role: frame pause; original member name unknown.
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

  bool isUpdating() const { return unknown84 >= STATE_MANAGER_INITIALIZED && unknown84 <= STATE_FINALIZING; }

  Applet *m_applet;
  FrameworkConfig unknown10; // Inferred role: config; original member name unknown.
  u8 _4c[0x50 - 0x4c];
  ml::WinProc *unknown50; // Inferred role: win proc; original member name unknown.
  ml::Scn *unknown58;     // Inferred role: scn; original member name unknown.
  u8 _60[0x68 - 0x60];
  mtl::ALLOC_HANDLE unknown68; // Inferred role: mem handle; original member name unknown.
  ILauncher *unknown70;        // Inferred role: launcher; original member name unknown.
  UpdateInfo unknown78;        // Inferred role: update info; original member name unknown.
  u32 unknown84;               // Inferred role: state; original member name unknown.
  u8 _88[0x8c - 0x88];
  f32 unknown8c; // Inferred role: update speed; original member name unknown.
  u8 _90[0x98 - 0x90];
  LayerUpdateInfo unknown98[LAYER_MAX];                                // Inferred role: layers; original member name unknown.
  mm::mtl::FixedVector<IPauseTrigger *, PAUSE_TRIGGER_MAX> unknown298; // Inferred role: pause triggers; original member name unknown.
  MemHandlebaseAllocator unknown3a0;                                   // Inferred role: allocator; original member name unknown.
};

static_assert(offsetof(Framework, unknown10) == 0x10, "");
static_assert(offsetof(Framework, unknown58) == 0x58, "");
static_assert(offsetof(Framework, unknown68) == 0x68, "");
static_assert(offsetof(Framework, unknown70) == 0x70, "");
static_assert(offsetof(Framework, unknown78) == 0x78, "");
static_assert(offsetof(Framework, unknown84) == 0x84, "");
static_assert(offsetof(Framework, unknown8c) == 0x8c, "");
static_assert(offsetof(Framework, unknown98) == 0x98, "");
static_assert(offsetof(Framework, unknown298) == 0x298, "");
static_assert(offsetof(Framework, unknown3a0) == 0x3a0, "");
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
