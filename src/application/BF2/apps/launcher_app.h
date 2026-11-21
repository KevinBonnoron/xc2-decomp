#pragma once

#include "ml/error_cb.h"
#include "ml/win_proc.h"
#include "ml/work_cpu.h"
#include "types.h"

namespace ml {
class EventButton;
class EventFloatingMenu;
class EventView;
class WorkObj;
} // namespace ml

namespace apps {

// Declared from the vtable _ZTVN4apps11LauncherAppE (1.0.0: 0x7101171300) and the symbols of its functions. The constructor (0x7100001c90) calls
// ml::WinProc::WinProc, stores the address point of the second base (IErrorCB, vtable + 0xd0) at 0x1f0 and registers it with ml::WorkCpu::registErrorCB,
// so the members from 0x1f8 up to the end of the object are not declared here. The size is the offset of the PtrSingleton<tl::TitleApp> base of
// tl::TitleApp (0x760, thunk _ZThn1888_N2tl8TitleAppD1Ev).
//
// Only what matched code needs is declared: the constructor and wkStandbyLogout (called by tl::TitleApp), errcbCallback (pure in IErrorCB: without it the
// class is abstract and createWork<tl::TitleApp> cannot create it) and the four virtuals that LauncherApp adds after wkStandbyExceptionRetry (slots
// 0x98-0xb0 of the vtable, each `mov w0, wzr`; the bool return type is inferred from OnFileEvent). Those four change the layout: the constructor of
// tl::TitleApp inlined in createWork<tl::TitleApp> (0x7100142828) stores the address points of its vtable (+0xd0 for IErrorCB, +0xf8 for PtrSingleton),
// and each missing virtual moves them by 8 bytes (createWork<tl::TitleApp> stops matching with OnMouseButtonDown or OnCButtonSelect removed). The other
// entries of the vtable (the overrides of OnSystemPause, OnShutdownForce, OnPauseTrigger, OnViewResize, OnFileEvent, wkUpdate, wkRender and wkTail, and the
// empty slot 0x80 of the pure wkStandbyLogin) change no code until a function that emits the vtable is decompiled, and are declared then. The out-of-line
// destructor (D1 at 0x7100001da0) is not declared until it is decompiled.
class LauncherApp : public ml::WinProc, public ml::IErrorCB {
public:
  LauncherApp(const char *name, ml::WorkObj *parent, int childNum);
  bool wkStandbyLogout() override;
  virtual bool OnMouseButtonDown(ml::EventView *view);
  virtual bool OnKeyDown(ml::EventView *view);
  virtual bool OnFMenuSelect(ml::EventFloatingMenu *event);
  virtual bool OnCButtonSelect(ml::EventButton *event);
  void errcbCallback(ml::CPUID cpu, unsigned long value) override;

  u8 _1f8[0x760 - 0x1f8];
};

static_assert(sizeof(LauncherApp) == 0x760, "");

} // namespace apps
