#include "ml/proc_exception.h"

#include "ml/cache_draw.h"
#include "ml/dev_graph.h"
#include "ml/device.h"
#include "ml/proc_desktop.h"
#include "ml/reslist.h"
#include "ml/win_view.h"
#include "ml/work_obj.h"
#include "ml/work_system.h"
#include "ml/work_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "window/window.h"

namespace ml {

ProcException::ProcException(const char *name, WorkObj *parent)
    : WinProc(name, parent, 10), unknown1f8(0xffffffff), unknown200(nullptr), unknown208(0.0f), unknown20c(0.0f), unknown210(0), unknown214(), unknown224(false), m_info(EXCEPTION_PRIO_UNKNOWN_5) {}

ProcException::~ProcException() {}

bool ProcException::isCheckOK() const { return unknown20c == 0.8f; }

void ProcException::forceShutdown() {
  unknown224 = true;
  wkSetEvent(static_cast<EVT>(0));
}

void ProcException::setInfo(EXCEPTION_PRIO prio) { m_info = prio; }

ProcException *ProcException::create(WorkObj *parent, const wchar_t *message, EXCEPTION_PRIO prio) {
  ProcException *current = get();
  if (current != nullptr) {
    if (current->m_info <= prio) {
      return nullptr;
    }
    current->forceShutdown();
  }

  ProcException *proc;
  _dsk::ProcDesktopException *exception = ProcDesktop::getException();
  if (exception == nullptr) {
    proc = WorkUtil::createWork<ProcException>("ProcException", Device::getException(), false);
  } else {
    proc = WorkUtil::createWork<ProcException>("ProcException", exception, false);
    WinView *view = ProcDesktop::getException()->pssGetApplicationView() != nullptr ? ProcDesktop::getException()->pssGetApplicationView() : ProcDesktop::getView();
    proc->unknown1e8 = view->unknown50;
  }
  if (proc != nullptr) {
    proc->setInfo(prio);
    proc->setInfo(parent->unknown50, message);
    u32 wid = proc->unknown50;
    parent->wkSetEventCurrent(static_cast<EVT>(2), wid);
  }
  return proc;
}

void ProcException::setInfo(u32 wid, const wchar_t *message) {
  unknown1f8 = wid;
  unknown200 = message;
}

void ProcException::wkRender() {
  switch (unknown210) {
  case 0:
    unknown20c += unknown208;
    if (unknown20c >= 0.8f) {
      unknown20c = 0.8f;
      unknown210 = 1;
    }
    break;
  case 1:
    if (wkIsShutdown()) {
      unknown20c -= unknown208;
      if (unknown20c <= 0.0f) {
        unknown20c = 0.0f;
        unknown210 = 2;
      }
    }
    break;
  }

  WinView *view = WinView::getView(true);
  int width = DevGraph::getRootWidth();
  int height = DevGraph::getRootHeight();
  if (view != nullptr) {
    width = WinView::getView(true)->getSize(false).x;
    height = WinView::getView(true)->getSize(false).y;
  }
  DebDraw *draw = DebDraw::get(0xffffffff);
  draw->setCol(0.0f, 0.0f, 0.0f, unknown20c);
  draw->renderRectFill(mm::Rect<int>(0, 0, width, height));
}

void ProcException::renderWide(const wchar_t *message) {}

bool ProcException::wkStandbyLogout() {
  if (unknown60.size() == 0 && (unknown20c == 0.0f || WorkSystem::isOff() || unknown224)) {
    ProcDesktop::setAppException(false);
    return WinProc::wkStandbyLogout();
  }

  return false;
}

void ProcException::fatal(const wchar_t *message) {}

void ProcException::entry(IException *exception) { unknown004.unknown38[unknown004.unknown00++] = exception; }

void ProcException::remove(IException *exception) {
  for (int i = 0; i < unknown004.unknown00; i++) {
    if (unknown004.unknown38[i] == exception) {
      for (int j = i; j < unknown004.unknown00 - 1; j++) {
        unknown004.unknown38[j] = unknown004.unknown38[j + 1];
      }
      unknown004.unknown00--;
      return;
    }
  }
}

void ProcException::setMessage(const wchar_t *message) {
  if (get() != nullptr) {
    get()->unknown200 = message;
  }
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::ProcException>::~PtrSingleton();
