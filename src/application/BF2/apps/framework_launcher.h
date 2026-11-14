#pragma once
#include <stddef.h>

#include "framework/framework.h"
#include "ml/work_background.h"
#include "ml/work_obj.h"
#include "mm_mtl/singleton.h"
#include "scn/scn_render_callback.h"
#include "types.h"

namespace nn {
namespace os {
struct FiberType;
} // namespace os
} // namespace nn

namespace fw {
class Applet;
} // namespace fw

namespace ml {
class MLTHG;
class Scn;
class WinProc;
class WinView;
} // namespace ml

namespace apps {

// Name given by the xc2 symbol _ZN4apps17FrameworkLauncher12getBuildInfoEv; the members are unknown.
struct SceneBuildInfo {
  u64 unknown00[0xd]; // Inferred role: scene description, 0x64 bytes used; original members unknown.
};

static_assert(sizeof(SceneBuildInfo) == 0x68, "");

class FrameworkLauncher : public ml::WorkObj, public ml::IScnRender, public ml::IWorkBackground, public mm::mtl::PtrSingleton<FrameworkLauncher>, public fw::unknown076 {
public:
  enum {
    FLAG_UNKNOWN_1 = 1 << 1,   // Inferred role: initialized; original name unknown.
    FLAG_UNKNOWN_4 = 1 << 4,   // Inferred role: finalized; original name unknown.
    FLAG_UNKNOWN_6 = 1 << 6,   // Inferred role: sound initialized; original name unknown.
    FLAG_UNKNOWN_7 = 1 << 7,   // Inferred role: initializing; original name unknown.
    FLAG_UNKNOWN_10 = 1 << 10, // Inferred role: applet initialized; original name unknown.
    FLAG_UNKNOWN_11 = 1 << 11, // Inferred role: resources loaded; original name unknown.
    FLAG_UNKNOWN_21 = 1 << 21, // Inferred role: step of the debug pause; original name unknown.
    FLAG_UNKNOWN_28 = 1 << 28, // Inferred role: reset requested; original name unknown.
    FLAG_UNKNOWN_29 = 1 << 29, // Inferred role: finalizing; original name unknown.
    FLAG_UNKNOWN_30 = 1 << 30, // Inferred role: reset requested; original name unknown.
  };

  FrameworkLauncher(const char *name, ml::WorkObj *parent);
  ~FrameworkLauncher() override;
  void destroyScn();
  void update();
  static ml::Scn *getScn();
  static ml::WinView *getView();
  static fw::Applet *getApplet();
  static SceneBuildInfo *getBuildInfo();
  static bool isInitialized();
  static bool isInitializing();
  static bool isInitializedSound();
  static void reqSoftReset();
  static bool createBuildThread(ml::WinProc *proc, SceneBuildInfo &buildInfo, const fw::FrameworkConfig &config, void (*initialize)(), void (*finalize)());
  static bool createAppletInitializeThread();
  static bool createWaitLoadResourceThread();
  static bool destroy();
  static void drawTask();
  static nn::os::FiberType *mlthFnBuild(void *argument);
  static nn::os::FiberType *mlthFnTermUpdate(void *argument);
  static nn::os::FiberType *mlthFnLoadResource(void *argument);
  static nn::os::FiberType *mlthFnAppletInitialize(void *argument);
  void updatePause();
  void wkUpdate() override;
  void wkTail() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  void setDebugPause(bool isPause) override;
  void stepDebugPause() override;
  bool isDebugPause() const override;
  bool resetApp() override;
  void cbRenderAfter(ml::Scn *scn, ml::SCNPRIO_CB priority) override;
  virtual void rdkReaded(const char *name, void *data, int size);
  void bkgHomeMenu(bool isOpen) override;

  u32 unknown1c8; // Inferred role: state flags; original member name unknown.
  u8 _1cc[0x1d0 - 0x1cc];
  ml::MLTHG *unknown1d0; // Inferred role: thread group of the update; original member name unknown.
  ml::MLTHG *unknown1d8; // Inferred role: thread group of the tail; original member name unknown.
  u64 unknown1e0;        // Inferred role: handle of the termination thread; original member name unknown.
  u64 unknown1e8;        // Inferred role: handle of the build thread; original member name unknown.
  u64 unknown1f0;        // Inferred role: handle of the applet initialization thread; original member name unknown.
  u64 unknown1f8;        // Inferred role: handle of the resource loading thread; original member name unknown.
  u8 _200[0x240 - 0x200];
  SceneBuildInfo m_buildInfo;
  u8 _2a8[0x2b8 - 0x2a8];
  ml::Scn *m_scn;
  ml::WinView *m_view;
  u8 _2c8[0x418 - 0x2c8];
  bool unknown418; // Inferred role: home menu open; original member name unknown.
  bool unknown419; // Inferred role: debug pause enabled; original member name unknown.
  bool m_debugPause;
};

static_assert(offsetof(FrameworkLauncher, unknown1c8) == 0x1c8, "");
static_assert(offsetof(FrameworkLauncher, unknown1d0) == 0x1d0, "");
static_assert(offsetof(FrameworkLauncher, m_buildInfo) == 0x240, "");
static_assert(offsetof(FrameworkLauncher, m_scn) == 0x2b8, "");
static_assert(offsetof(FrameworkLauncher, m_view) == 0x2c0, "");
static_assert(offsetof(FrameworkLauncher, unknown418) == 0x418, "");
static_assert(offsetof(FrameworkLauncher, m_debugPause) == 0x41a, "");
static_assert(sizeof(FrameworkLauncher) == 0x420, "");

} // namespace apps
