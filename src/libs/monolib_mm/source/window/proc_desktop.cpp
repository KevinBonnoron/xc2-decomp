#include "ml/proc_desktop.h"

#include "ml/desktop_icon.h"
#include "ml/dev_graph.h"
#include "ml/work_obj.h"
#include "ml/work_util.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"

namespace ml {

namespace _dsk {

enum Flag {
  FLAG_DISP_INFO = 0x1,
  FLAG_SIMPLE_INFO = 0x2,
  FLAG_AUTO_EXECUTE = 0x8,
  FLAG_SCREEN_LOG = 0x10,
  FLAG_PAUSE = 0x20,
  FLAG_SIMPLE_COST = 0x40,
};

u32 s_flg;
u32 s_bitDisable;
int s_nInfoX;
int s_nInfoY;
const char *s_pszInfo;
const char *s_pszAutorun;
ProcDesktop::DESKTOP_ICON_DEF *s_pIconTable;
ProcDesktop::DESKTOP_ICON_DEF *s_pStaticTable;
void (*s_initializeNotify)();
void (*s_updateNotify)();
void (*s_finalizeNotify)();
mm::mtl::FixStr<128> s_revision;

} // namespace _dsk

void ProcDesktop::setSimpleCost(bool isSimpleCost) { _dsk::s_flg = !isSimpleCost ? _dsk::s_flg & ~_dsk::FLAG_SIMPLE_COST : _dsk::s_flg | _dsk::FLAG_SIMPLE_COST; }

bool ProcDesktop::isSimpleCost() { return _dsk::s_flg & _dsk::FLAG_SIMPLE_COST; }

void ProcDesktop::setScreenLog(bool isScreenLog) { _dsk::s_flg = !isScreenLog ? _dsk::s_flg & ~_dsk::FLAG_SCREEN_LOG : _dsk::s_flg | _dsk::FLAG_SCREEN_LOG; }

bool ProcDesktop::isDispScreenLog() { return _dsk::s_flg & _dsk::FLAG_SCREEN_LOG; }

f32 ProcDesktop::setUpdateSec(f32 sec) { return setUpdateRatio(sec / DevGraph::getFrameSyncSec()); }

f32 ProcDesktop::setUpdateRatio(f32 ratio) {
  ProcDesktop *desktop = get();
  if (desktop == nullptr) {
    return 0.0f;
  }
  f32 oldRatio = desktop->unknown25c;
  desktop->unknown260 = ratio;
  if (oldRatio != ratio) {
    f32 scale = (_dsk::s_flg & _dsk::FLAG_PAUSE) ? 0.0f : 1.0f;
    desktop->unknown25c = ratio;
    DevGraph::setFrameSpd(ratio * scale);
  }
  return oldRatio;
}

f32 ProcDesktop::getUpdateSec() {
  ProcDesktop *desktop = get();
  if (desktop == nullptr) {
    return 0.0f;
  }
  return desktop->unknown25c * DevGraph::getFrameSyncSec();
}

f32 ProcDesktop::getUpdateRatio() {
  ProcDesktop *desktop = get();
  if (desktop == nullptr) {
    return 0.0f;
  }
  return desktop->unknown25c;
}

void ProcDesktop::entryTable(DESKTOP_ICON_DEF *table, bool isAutoExecute) {
  _dsk::s_pIconTable = table;
  _dsk::s_flg = !isAutoExecute ? _dsk::s_flg & ~_dsk::FLAG_AUTO_EXECUTE : _dsk::s_flg | _dsk::FLAG_AUTO_EXECUTE;
}

void ProcDesktop::entryStaticApp(DESKTOP_ICON_DEF *table) { _dsk::s_pStaticTable = table; }

void ProcDesktop::setAppException(bool isException) {
  ProcDesktop *desktop = get();
  if (desktop != nullptr) {
    desktop->wkSetEvent(static_cast<EVT>(isException ? 10 : 11));
  }
}

void ProcDesktop::setInfo(int x, int y, const char *info) {
  _dsk::s_nInfoX = x;
  _dsk::s_nInfoY = y;
  _dsk::s_pszInfo = info;
}

bool ProcDesktop::isDeleteApp() {
  ProcDesktop *desktop = get();
  if (desktop == nullptr) {
    return true;
  }
  return desktop->unknown274;
}

void ProcDesktop::setDisableFlag(u32 flag) { _dsk::s_bitDisable = flag; }

void ProcDesktop::autorun(const char *name) { _dsk::s_pszAutorun = name; }

void ProcDesktop::dispInfo(bool isDisp) { _dsk::s_flg = !isDisp ? _dsk::s_flg & ~_dsk::FLAG_DISP_INFO : _dsk::s_flg | _dsk::FLAG_DISP_INFO; }

void ProcDesktop::setSimpleInfo(bool isSimple) { _dsk::s_flg = !isSimple ? _dsk::s_flg & ~_dsk::FLAG_SIMPLE_INFO : _dsk::s_flg | _dsk::FLAG_SIMPLE_INFO; }

bool ProcDesktop::isDispInfo() { return _dsk::s_flg & _dsk::FLAG_DISP_INFO; }

WinView *ProcDesktop::getSelectedView() { return get()->unknown248; }

WinView *ProcDesktop::getView() {
  ProcDesktop *desktop = get();
  if (desktop == nullptr) {
    return nullptr;
  }
  return desktop->unknown208;
}

const mm::Col4 &ProcDesktop::getDefaultFrameColor() { return get()->unknown1f8; }

_dsk::ProcDesktopBackGround *ProcDesktop::getBackGround() { return mm::mtl::PtrSingleton<_dsk::ProcDesktopBackGround>::get(); }

_dsk::ProcDesktopException *ProcDesktop::getException() {
  if (get() == nullptr) {
    return nullptr;
  }
  return mm::mtl::PtrSingleton<_dsk::ProcDesktopException>::get();
}

void ProcDesktop::deleteApp() {
  ProcDesktop *desktop = get();
  desktop->unknown274 = true;
  desktop->wkSetEventChild(static_cast<EVT>(0));
}

void ProcDesktop::debugEntryIcon() {
  DESKTOP_ICON_DEF *def = _dsk::s_pIconTable;
  if (def == nullptr) {
    return;
  }
  for (; def->name != nullptr; def++) {
    unknown210[unknown218++] = DesktopIcon::create(WorkUtil::getWorkMem(), def->name, def->func);
  }
}

void ProcDesktop::wkStandby() { WorkObj::wkStandby(); }

void ProcDesktop::wkRender() {}

void ProcDesktop::wkRenderAfter() {}

void ProcDesktop::debugSimpleCost(int x, int y) {}

void ProcDesktop::OnPauseTrigger(bool isPause, const char *name) {
  _dsk::s_flg = !isPause ? _dsk::s_flg & ~_dsk::FLAG_PAUSE : _dsk::s_flg | _dsk::FLAG_PAUSE;
  f32 ratio = unknown25c;
  unknown25c = 0.0f;
  setUpdateRatio(ratio);
}

void ProcDesktop::debugFormIcon() {}

void ProcDesktop::debugDispErrorLogLoop() {}

void ProcDesktop::debugDispScreenLog() {}

void ProcDesktop::debugRenderDesktop(WinView *view) {}

void ProcDesktop::debugPadInput() {}

void ProcDesktop::setStartNotify(void (*initialize)(), void (*update)(), void (*finalize)()) {
  _dsk::s_initializeNotify = initialize;
  _dsk::s_updateNotify = update;
  _dsk::s_finalizeNotify = finalize;
}

const char *ProcDesktop::getBuildRevision() { return _dsk::s_revision.c_str(); }

void ProcDesktop::setBuildRevision(const char *revision) {
  if (revision != nullptr) {
    _dsk::s_revision = revision;
  }
}

} // namespace ml
