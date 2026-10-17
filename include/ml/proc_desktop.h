#pragma once
#include <stddef.h>

#include "ml/win_proc.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {
class DesktopIcon;
class WinView;
class WorkObj;

namespace _dsk {
class ProcDesktopBackGround;
class ProcDesktopException;
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
  static f32 setUpdateSec(f32 sec);
  static f32 setUpdateRatio(f32 ratio);
  static f32 getUpdateSec();
  static f32 getUpdateRatio();
  static void entryTable(DESKTOP_ICON_DEF *table, bool isAutoExecute);
  static void entryStaticApp(DESKTOP_ICON_DEF *table);
  static void setAppException(bool isException);
  static void setInfo(int x, int y, const char *info);
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
  WinView *m_view;
  DesktopIcon **m_icons;
  u32 m_iconNum;
  u8 _21c[0x248 - 0x21c];
  WinView *m_selectedView;
  u8 _250[0x25c - 0x250];
  f32 m_updateRatio;
  f32 m_requestUpdateRatio;
  u8 _264[0x274 - 0x264];
  bool m_isDeleteApp;
};

static_assert(offsetof(ProcDesktop, m_defaultFrameColor) == 0x1f8, "");
static_assert(offsetof(ProcDesktop, m_icons) == 0x210, "");
static_assert(offsetof(ProcDesktop, m_selectedView) == 0x248, "");
static_assert(offsetof(ProcDesktop, m_updateRatio) == 0x25c, "");
static_assert(offsetof(ProcDesktop, m_isDeleteApp) == 0x274, "");

} // namespace ml
