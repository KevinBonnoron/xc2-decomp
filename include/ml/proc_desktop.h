#pragma once
#include <stddef.h>

#include "ml/reslist.h"
#include "ml/win_proc.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace ml {
class DesktopIcon;
class WinView;
class WorkObj;

namespace _dsk {

// Defined here rather than in proc_desktop.cpp: ProcException::create uses the ProcDesktopException that
// ProcDesktop::getException returns as a WinProc.
class ProcDesktopBackGround : public WinProc, public mm::mtl::PtrSingleton<ProcDesktopBackGround> {
public:
  ProcDesktopBackGround(const char *name, WorkObj *parent) : WinProc(name, parent, 8) {}

  bool wkStandbyLogout() override {
    if (unknown60.size() != 0) {
      return false;
    }
    return WinProc::wkStandbyLogout();
  }
};

class ProcDesktopException : public WinProc, public mm::mtl::PtrSingleton<ProcDesktopException> {
public:
  ProcDesktopException(const char *name, WorkObj *parent) : WinProc(name, parent, 64) {}

  bool wkStandbyLogout() override {
    if (unknown60.size() != 0) {
      return false;
    }
    return WinProc::wkStandbyLogout();
  }
};

} // namespace _dsk

class ProcDesktop : public WinProc, public mm::mtl::PtrSingleton<ProcDesktop> {
public:
  struct DESKTOP_ICON_DEF {
    const char *name;
    void (*func)();
  };

  ProcDesktop(const char *name, WorkObj *parent);
  static void setSimpleCost(bool isSimpleCost);
  ~ProcDesktop() override;
  static bool isSimpleCost();
  static void setScreenLog(bool isScreenLog);
  static bool isDispScreenLog();
  static void executeApp(const char *name);
  static void executeSelectApp();
  static f32 setUpdateSec(f32 sec);
  static f32 setUpdateRatio(f32 ratio);
  static f32 getUpdateSec();
  static f32 getUpdateRatio();
  static void entryTable(DESKTOP_ICON_DEF *table, bool isAutoExecute);
  static void entryStaticApp(DESKTOP_ICON_DEF *table);
  static void setAppException(bool isException);
  static void setInfo(int x, int y, const char *info);
  static WinProc *getCurrentProc();
  static bool isDeleteApp();
  static void setDisableFlag(u32 flag);
  static void autorun(const char *name);
  static void dispInfo(bool isDisp);
  static void setSimpleInfo(bool isSimple);
  static bool isDispInfo();
  static WinView *getSelectedView();
  static WinView *getView();
  static const mm::Col4 &getDefaultFrameColor();
  static _dsk::ProcDesktopBackGround *getBackGround();
  static _dsk::ProcDesktopException *getException();
  static void deleteApp();
  static void deleteApp(const char *name);
  bool wkStandbyLogin() override;
  void debugEntryIcon();
  bool wkStandbyLogout() override;
  void wkStandby() override;
  void wkTail() override;
  void wkRender() override;
  void wkRenderAfter() override;
  void debugSimpleCost(int x, int y);
  void OnPauseTrigger(bool isPause, const char *name);
  void debugFormIcon();
  void debugDispErrorLogLoop();
  void debugDispScreenLog();
  void debugRenderDesktop(WinView *view);
  void debugPadInput();
  static void setStartNotify(void (*initialize)(), void (*update)(), void (*finalize)());
  static const char *getBuildRevision();
  static void setBuildRevision(const char *revision);

  mm::Col4 m_defaultFrameColor;
  WinView *unknown208;          // Inferred role: view; original member name unknown.
  DesktopIcon **unknown210;     // Inferred role: icons; original member name unknown.
  u32 unknown218;               // Inferred role: icon num; original member name unknown.
  u32 unknown21c;               // Inferred role: icon max; original member name unknown.
  mtl::ALLOC_HANDLE unknown220; // Inferred role: memory of the icons; original member name unknown.
  u8 _224[0x248 - 0x224];
  WinView *m_selectedView;
  u8 _250[0x25c - 0x250];
  f32 unknown25c; // Inferred role: update ratio; original member name unknown.
  f32 unknown260; // Inferred role: request update ratio; original member name unknown.
  u8 _264[0x270 - 0x264];
  s32 unknown270;  // Inferred role: login step counter; original member name unknown.
  bool unknown274; // Inferred role: delete app; original member name unknown.
};

static_assert(offsetof(ProcDesktop, m_defaultFrameColor) == 0x1f8, "");
static_assert(offsetof(ProcDesktop, unknown210) == 0x210, "");
static_assert(offsetof(ProcDesktop, unknown220) == 0x220, "");
static_assert(offsetof(ProcDesktop, m_selectedView) == 0x248, "");
static_assert(offsetof(ProcDesktop, unknown270) == 0x270, "");
static_assert(offsetof(ProcDesktop, unknown25c) == 0x25c, "");
static_assert(offsetof(ProcDesktop, unknown274) == 0x274, "");

} // namespace ml
