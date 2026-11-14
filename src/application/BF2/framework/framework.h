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
  FrameworkConfig()
      : unknown00(0xffffff), unknown04(30.0f), unknown08(0x400), unknown10(0x1d00000), unknown18(0x20), unknown1c(0x400), unknown20(0x400), unknown24(0x400), unknown28(0x800), unknown2c(0x600),
        unknown30(0x1000), unknown34(0x48), unknown38(0) {}

  u32 unknown00; // Inferred role: flags, 0x20 creates the CameraManager; original member name unknown.
  f32 unknown04; // Inferred role: frame rate; original member name unknown.
  u32 unknown08; // Inferred role: capacity, 0x400 by default; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  u64 unknown10; // Inferred role: size, 0x1d00000 by default; original member name unknown.
  u32 unknown18; // Inferred role: count, 0x20 by default; original member name unknown.
  u32 unknown1c; // Inferred role: capacity, 0x400 by default; original member name unknown.
  u32 unknown20; // Inferred role: asset capacity; original member name unknown.
  u32 unknown24; // Inferred role: capacity, 0x400 by default; original member name unknown.
  u32 unknown28; // Inferred role: effect count; original member name unknown.
  u32 unknown2c; // Inferred role: resource capacity; original member name unknown.
  u32 unknown30; // Inferred role: updatable object capacity; original member name unknown.
  u32 unknown34; // Inferred role: script count; original member name unknown.
  u32 unknown38; // Inferred role: language type passed to LangUtil::setLangType; original member name unknown.
};

static_assert(offsetof(FrameworkConfig, unknown10) == 0x10, "");
static_assert(offsetof(FrameworkConfig, unknown20) == 0x20, "");
static_assert(offsetof(FrameworkConfig, unknown28) == 0x28, "");
static_assert(offsetof(FrameworkConfig, unknown34) == 0x34, "");
static_assert(offsetof(FrameworkConfig, unknown38) == 0x38, "");
// The user-provided constructor makes the struct non-POD: its copy leaves out the tail padding (0x3c bytes).
static_assert(sizeof(FrameworkConfig) == 0x40, "");

struct UpdateState {
  bool isPause;
};

// Inferred role: launcher interface; original type name unknown.
class unknown076 {
public:
  virtual void setDebugPause(bool isPause) = 0;
  virtual void stepDebugPause() = 0;
  virtual bool isDebugPause() const = 0;
  virtual bool resetApp() = 0;
};

// Inferred role: layer update info; original type name unknown.
struct unknown077 {
  unknown077() : unknown00(1.0f), unknown04(1.0f), unknown08(1.0f), unknown0c(false), unknown0d(false) {}

  f32 unknown00;  // Inferred role: speed; original member name unknown.
  f32 unknown04;  // Inferred role: scaled speed; original member name unknown.
  f32 unknown08;  // Inferred role: frame speed; original member name unknown.
  bool unknown0c; // Inferred role: pause; original member name unknown.
  bool unknown0d; // Inferred role: frame pause; original member name unknown.
};

static_assert(sizeof(unknown077) == 0x10, "");

class Framework : public mm::mtl::PtrSingleton<Framework> {
public:
  enum State {
    STATE_UNKNOWN_0 = 0, // Inferred role: none; original name unknown.
    STATE_UNKNOWN_1 = 1, // Inferred role: initialized; original name unknown.
    STATE_UNKNOWN_2 = 2, // Inferred role: manager initialized; original name unknown.
    STATE_UNKNOWN_3 = 3, // Inferred role: entered; original name unknown.
    STATE_UNKNOWN_4 = 4, // Inferred role: finalizing; original name unknown.
    STATE_UNKNOWN_5 = 5, // Inferred role: finalized; original name unknown.
  };

  static const u32 LAYER_UNKNOWN_32 = 32;         // Inferred role: maximum number of layers; original name unknown.
  static const u32 PAUSE_TRIGGER_UNKNOWN_32 = 32; // Inferred role: maximum number of pause triggers; original name unknown.
  static const u32 unknown001 = 14;               // Inferred role: count of the layers run by update; original name unknown.

  Framework();
  ~Framework();
  void createMemorySection();
  void finalize();
  static mm::mtl::IAllocator *getAllocator();
  bool initializeManager();
  void createManager();
  static void destroyManager();
  bool finalizeManager();
  void prepareEnter();
  void prepareExit();
  void pauseEnter();
  void pauseExit();
  void activate();
  void deactivate();
  void beginFrame(const UpdateState &updateState);
  void endFrame(const UpdateState &updateState);
  void preUpdate();
  void update();
  static bool canUpdate();
  void tail(const UpdateState &updateState);
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

  bool isUpdating() const { return unknown84 >= STATE_UNKNOWN_2 && unknown84 <= STATE_UNKNOWN_4; }

  Applet *m_applet;
  FrameworkConfig unknown10;   // Inferred role: config; original member name unknown.
  ml::WinProc *unknown50;      // Inferred role: win proc; original member name unknown.
  ml::Scn *unknown58;          // Inferred role: scn; original member name unknown.
  void *unknown60;             // Inferred role: unknown pointer, 8 bytes at 0x60 cleared by the constructor; original member name and type unknown.
  mtl::ALLOC_HANDLE unknown68; // Inferred role: mem handle; original member name unknown.
  unknown076 *unknown70;       // Inferred role: launcher; original member name unknown.
  UpdateInfo unknown78;        // Inferred role: update info; original member name unknown.
  u32 unknown84;               // Inferred role: state; original member name unknown.
  bool unknown88;              // Inferred role: unknown flag, cleared by the constructor; original member name unknown.
  bool unknown89;              // Inferred role: unknown flag, cleared by the constructor; original member name unknown.
  bool unknown8a;              // Inferred role: updated this frame; original member name unknown.
  u8 _8b[0x8c - 0x8b];
  f32 unknown8c; // Inferred role: update speed; original member name unknown.
  u8 _90[0x98 - 0x90];
  unknown077 unknown98[LAYER_UNKNOWN_32];                                     // Inferred role: layers; original member name unknown.
  mm::mtl::FixedVector<IPauseTrigger *, PAUSE_TRIGGER_UNKNOWN_32> unknown298; // Inferred role: pause triggers; original member name unknown.
  MemHandlebaseAllocator unknown3a0;                                          // Inferred role: allocator; original member name unknown.
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
