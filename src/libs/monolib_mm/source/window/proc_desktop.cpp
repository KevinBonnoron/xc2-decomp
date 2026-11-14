#include "ml/proc_desktop.h"

#include <string.h>

#include "ml/desktop_icon.h"
#include "ml/dev_file_th.h"
#include "ml/dev_graph.h"
#include "ml/lib_main.h"
#include "ml/micro_thread.h"
#include "ml/msg_param.h"
#include "ml/reslist.h"
#include "ml/win_proc_root.h"
#include "ml/win_view.h"
#include "ml/win_view_root.h"
#include "ml/work_cpu.h"
#include "ml/work_flow_shutdown_all.h"
#include "ml/work_obj.h"
#include "ml/work_root.h"
#include "ml/work_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

namespace _dsk {

enum Flag {
  FLAG_UNKNOWN_0 = 0x1,  // Inferred role: disp info; original name unknown.
  FLAG_UNKNOWN_1 = 0x2,  // Inferred role: simple info; original name unknown.
  FLAG_UNKNOWN_3 = 0x8,  // Inferred role: auto execute; original name unknown.
  FLAG_UNKNOWN_4 = 0x10, // Inferred role: screen log; original name unknown.
  FLAG_UNKNOWN_5 = 0x20, // Inferred role: pause; original name unknown.
  FLAG_UNKNOWN_6 = 0x40, // Inferred role: simple cost; original name unknown.
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
mm::mtl::FixStr<128> s_selectAppName;
mm::mtl::FixStr<128> s_revision;
int s_nEnableHomeBtn;
const char *s_szDesktop = "Desktop";

} // namespace _dsk

void ProcDesktop::setSimpleCost(bool isSimpleCost) { _dsk::s_flg = !isSimpleCost ? _dsk::s_flg & ~_dsk::FLAG_UNKNOWN_6 : _dsk::s_flg | _dsk::FLAG_UNKNOWN_6; }

ProcDesktop::~ProcDesktop() {
  unknown218 = 0;
  if (unknown220.isValid() && unknown210 != nullptr) {
    mtl::MemManager::deallocate(unknown210, 0, false);
    unknown210 = nullptr;
  }
  unknown210 = nullptr;
  unknown21c = 0;
  unknown220 = mtl::ALLOC_HANDLE();
}

bool ProcDesktop::isSimpleCost() { return _dsk::s_flg & _dsk::FLAG_UNKNOWN_6; }

void ProcDesktop::setScreenLog(bool isScreenLog) { _dsk::s_flg = !isScreenLog ? _dsk::s_flg & ~_dsk::FLAG_UNKNOWN_4 : _dsk::s_flg | _dsk::FLAG_UNKNOWN_4; }

bool ProcDesktop::isDispScreenLog() { return _dsk::s_flg & _dsk::FLAG_UNKNOWN_4; }

void ProcDesktop::executeApp(const char *name) {
  ProcDesktop *desktop = get();
  if (desktop == nullptr) {
    return;
  }
  for (DesktopIcon **icon = desktop->unknown210; icon != desktop->unknown210 + desktop->unknown218; icon++) {
    if (strcmp((*icon)->unknown08.c_str(), name) == 0) {
      _dsk::s_selectAppName = (*icon)->unknown08.c_str();
      (*icon)->execute();
      return;
    }
  }
}

void DesktopIcon::execute() {
  if (unknown50 != nullptr) {
    unknown50();
  }
}

void ProcDesktop::executeSelectApp() { executeApp(_dsk::s_selectAppName.c_str()); }

f32 ProcDesktop::setUpdateSec(f32 sec) { return setUpdateRatio(sec / DevGraph::getFrameSyncSec()); }

f32 ProcDesktop::setUpdateRatio(f32 ratio) {
  ProcDesktop *desktop = get();
  if (desktop == nullptr) {
    return 0.0f;
  }
  f32 oldRatio = desktop->unknown25c;
  desktop->unknown260 = ratio;
  if (oldRatio != ratio) {
    f32 scale = (_dsk::s_flg & _dsk::FLAG_UNKNOWN_5) ? 0.0f : 1.0f;
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
  _dsk::s_flg = !isAutoExecute ? _dsk::s_flg & ~_dsk::FLAG_UNKNOWN_3 : _dsk::s_flg | _dsk::FLAG_UNKNOWN_3;
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

WinProc *ProcDesktop::getCurrentProc() {
  WinView *current = WinViewRoot::getCurrent();
  if (current == nullptr) {
    return nullptr;
  }
  WinView *view = WinViewRoot::getRootView(current);
  if (view == nullptr) {
    return nullptr;
  }
  for (reslist<u32>::Node *node = view->unknown338.begin(); node != view->unknown338.end(); node = node->getNext()) {
    WinProc *proc = WinProc::pssGetRoot(static_cast<WinProc *>(WorkRootState::getWork(node->value)));
    if (proc != nullptr) {
      return proc;
    }
  }
  return nullptr;
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

void ProcDesktop::dispInfo(bool isDisp) { _dsk::s_flg = !isDisp ? _dsk::s_flg & ~_dsk::FLAG_UNKNOWN_0 : _dsk::s_flg | _dsk::FLAG_UNKNOWN_0; }

void ProcDesktop::setSimpleInfo(bool isSimple) { _dsk::s_flg = !isSimple ? _dsk::s_flg & ~_dsk::FLAG_UNKNOWN_1 : _dsk::s_flg | _dsk::FLAG_UNKNOWN_1; }

bool ProcDesktop::isDispInfo() { return _dsk::s_flg & _dsk::FLAG_UNKNOWN_0; }

WinView *ProcDesktop::getSelectedView() { return get()->m_selectedView; }

WinView *ProcDesktop::getView() {
  ProcDesktop *desktop = get();
  if (desktop == nullptr) {
    return nullptr;
  }
  return desktop->unknown208;
}

const mm::Col4 &ProcDesktop::getDefaultFrameColor() { return get()->m_defaultFrameColor; }

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

void ProcDesktop::deleteApp(const char *name) {
  ProcDesktop *desktop = get();
  if (desktop == nullptr) {
    return;
  }

  reslist<WorkObj *> *children = desktop->wkGetChild();
  for (reslist<WorkObj *>::Node *node = children->begin(); node != desktop->wkGetChild()->end(); node = node->getNext()) {
    WorkObj *child = node->value;
    if (strcmp(child->unknown08.c_str(), name) == 0) {
      child->wkSetEvent(static_cast<WorkObj::EVT>(0));
      return;
    }
  }
}

bool ProcDesktop::wkStandbyLogin() {
  if (!(DevGraph::isIgnore() || (!DevGraph::isIgnore() && DevGraph::get() != nullptr)) || DevFileTh::get() == nullptr || !DevFileTh::isInitialized() || !LibMain::isInitialized()) {
    return false;
  }
  if (unknown270 == 0) {
    DevGraph::grSetClearCol(mm::Col4::black);
    DevFileTh::entryCb(this);
    unknown208 = pssCreateView(unknown08.c_str(), WinViewRoot::get(), 128);
    unknown208->unknown514 = mm::Col4::black;
    unknown208->unknown3c0.add(4);
    unknown208->unknown528 = 19;
    unknown208->setTitle(_dsk::s_szDesktop);
    unknown208->unknown3b8 |= 0x100;
    _dsk::ProcDesktopBackGround *backGround = WorkUtil::createWork<_dsk::ProcDesktopBackGround>("ProcDesktopBackGround", WinProcRoot::get(), false);
    backGround->unknown1e8 = get()->unknown208->unknown50;
    _dsk::ProcDesktopException *exception = WorkUtil::createWork<_dsk::ProcDesktopException>("ProcDesktopException", WinProcRoot::get(), false);
    exception->unknown1e8 = get()->unknown208->unknown50;
    MicroThread::create();
    if (WorkFlowShutdownAll::get() == nullptr) {
      debugEntryIcon();
      DESKTOP_ICON_DEF *def = _dsk::s_pStaticTable;
      if (def != nullptr) {
        for (; def->name != nullptr; def++) {
          def->func();
        }
      }
    }
    unknown270++;
    return false;
  }
  if (unknown270++ < 3) {
    return false;
  }
  if (WorkFlowShutdownAll::get() == nullptr) {
    if ((_dsk::s_flg & _dsk::FLAG_UNKNOWN_3) && unknown218 != 0) {
      unknown210[0]->execute();
      _dsk::s_selectAppName = unknown210[0]->unknown08.c_str();
    }
    if (_dsk::s_pszAutorun != nullptr) {
      for (DesktopIcon **icon = unknown210; icon != unknown210 + unknown218; icon++) {
        if (strcmp((*icon)->unknown08.c_str(), _dsk::s_pszAutorun) == 0) {
          (*icon)->execute();
          _dsk::s_selectAppName = (*icon)->unknown08.c_str();
        }
      }
    }
  }
  if (_dsk::s_initializeNotify != nullptr) {
    _dsk::s_initializeNotify();
  }
  return WinProc::wkStandbyLogin();
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

bool ProcDesktop::wkStandbyLogout() {
  if (unknown60.size() != 0 || WorkRootState::getWork(WinProcRoot::get(), "ProcDesktopBack") != nullptr) {
    return false;
  }
  MicroThread::destroy();
  if (_dsk::s_finalizeNotify != nullptr) {
    _dsk::s_finalizeNotify();
    _dsk::s_finalizeNotify = nullptr;
  }
  for (DesktopIcon **icon = unknown210; icon != unknown210 + unknown218; icon++) {
    if (*icon != nullptr) {
      delete *icon;
      *icon = nullptr;
    }
  }
  DevFileTh::removeCb(this);
  return WinProc::wkStandbyLogout();
}

DesktopIcon *DesktopIcon::create(mtl::ALLOC_HANDLE handle, const char *name, void (*func)()) {
  mm::mtl::FixStr<64> label("(ICON)");
  label += name;
  return new (handle) DesktopIcon(name, func);
}

DesktopIcon::DesktopIcon(const char *name, void (*func)()) : unknown08(name), unknown50(func) {
  unknown68 = false;
  unknown58 = mm::Rect<int>(0, 0, DevGraph::fontGetWidth(name, FONT_STYLE_UNKNOWN_0, 1.0f), 25);
}

void DesktopIcon::render(WinView *view) {
  view->fontStyle(FONT_STYLE_UNKNOWN_0);
  view->fontScale(1.0f, 1.0f);
  view->fontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  if (unknown68) {
    view->fontBack(mm::Col4(0.0f, 0.0f, 0.2f, 1.0f));
  } else {
    view->fontBack(mm::Col4::zero);
  }
  view->fontShadow(true);
  view->font(unknown58.x, unknown58.y, unknown08.c_str());
}

void ProcDesktop::wkStandby() { WorkObj::wkStandby(); }

void ProcDesktop::wkTail() {
  if (MicroThread::get() != nullptr) {
    MicroThread::get()->tail();
  }
  if (wkIsWaitException()) {
    return;
  }
  if (wkIsActive() && _dsk::s_nEnableHomeBtn < 30) {
    _dsk::s_nEnableHomeBtn++;
    if (_dsk::s_nEnableHomeBtn >= 30) {
      WorkCpu::setEnableSystem();
    }
  }
}

void ProcDesktop::wkRender() {}

void ProcDesktop::wkRenderAfter() {}

void ProcDesktop::debugSimpleCost(int x, int y) {}

void ProcDesktop::OnPauseTrigger(bool isPause, const char *name) {
  _dsk::s_flg = !isPause ? _dsk::s_flg & ~_dsk::FLAG_UNKNOWN_5 : _dsk::s_flg | _dsk::FLAG_UNKNOWN_5;
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

template mm::mtl::PtrSingleton<ml::ProcDesktop>::~PtrSingleton();
template mm::mtl::PtrSingleton<ml::_dsk::ProcDesktopBackGround>::~PtrSingleton();
template mm::mtl::PtrSingleton<ml::_dsk::ProcDesktopException>::~PtrSingleton();
