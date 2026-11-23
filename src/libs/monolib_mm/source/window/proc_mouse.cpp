#include "ml/proc_mouse.h"

#include "ml/cache_draw.h"
#include "ml/dev_mouse.h"
#include "ml/msg_param.h"
#include "ml/proc_desktop.h"
#include "ml/reslist.h"
#include "ml/win_view.h"
#include "mm_math/mm_rect.h"

namespace ml {

namespace {

// Inferred role: draw the mouse cursor, set by ProcMouse::setDisp; original name unknown.
bool unknown001 = true;

} // namespace

class WorkObj;

ProcMouse::ProcMouse(const char *name, WorkObj *parent) : WinProc(name, parent, 10), m_pos(0, 0), unknown200(0, 0), m_move(0, 0), unknown234(false) { unknown210 = "ARROW"; }

ProcMouse::~ProcMouse() {}

void ProcMouse::setDisp(bool isDisp) { unknown001 = isDisp; }

mm::Pnt<int> *ProcMouse::getPos() { return &get()->m_pos; }

mm::Pnt<int> *ProcMouse::getMove() { return &get()->m_move; }

void ProcMouse::setPos(const mm::Pnt<int> &position) {
  ProcMouse *mouse = get();
  mouse->unknown200 = position;
  mouse->m_pos = position;
}

void ProcMouse::setCursorResize(MCURSOR cursor) {
  switch (cursor) {
  case MCURSOR_UNKNOWN_1:
    get()->unknown210 = "SIZE1";
    get()->unknown234 = true;
    break;
  case MCURSOR_UNKNOWN_2:
    get()->unknown210 = "SIZE2";
    get()->unknown234 = true;
    break;
  case MCURSOR_UNKNOWN_3:
    get()->unknown210 = "SIZE3";
    get()->unknown234 = true;
    break;
  case MCURSOR_UNKNOWN_4:
    get()->unknown210 = "SIZE4";
    get()->unknown234 = true;
    break;
  default:
    get()->unknown210 = "ARROW";
    get()->unknown234 = false;
    break;
  }
}

void ProcMouse::update(bool isUpdate) {
  ProcMouse *mouse = get();
  if (mouse == nullptr || DevMouse::get() == nullptr) {
    return;
  }
  WinView *view = mouse->pssGetView(0xffffffff);
  if (view == nullptr) {
    return;
  }
  get()->m_move = DevMouse::getMove();
  get()->unknown200 = get()->m_pos;
  get()->m_pos = DevMouse::getPos();
  mouse = get();
  const mm::Pnt<int> &pos = mouse->m_pos;
  const mm::Pnt<int> &prev = mouse->unknown200;
  if (pos.x != prev.x || pos.y != prev.y) {
    mouse->unknown235 = 60;
  }
  view->setRect(ProcDesktop::get()->unknown208->getRect(false));
  mm::Rect<int> rect = ProcDesktop::get()->unknown208->getRect(false);
  mm::Pnt<int> *clamped = getPos();
  if (clamped->x < rect.x) {
    clamped->x = rect.x;
  }
  if (clamped->y < rect.y) {
    clamped->y = rect.y;
  }
  if (clamped->x >= rect.x + rect.width - 1) {
    clamped->x = rect.x + rect.width - 1;
  }
  if (clamped->y >= rect.y + rect.height - 1) {
    clamped->y = rect.y + rect.height - 1;
  }
}

void ProcMouse::wkRenderAfter() {
  if (!unknown001 || unknown235 == 0) {
    return;
  }
  unknown235--;
  WinView::getView(true);
  DebDraw *draw = DebDraw::get(0xffffffff);
  draw->setZComp(false);
  draw->setZWrite(false);
  draw->setCol(1.0f, 1.0f, 1.0f, 1.0f);
  draw->setAlphaBlend(true);
  draw->begin(2, 2);
  draw->add(m_pos.x, m_pos.y - 10, m_pos.x, m_pos.y + 10);
  draw->add(m_pos.x - 10, m_pos.y, m_pos.x + 10, m_pos.y);
  draw->end();
  draw->setZComp(true);
  draw->setZWrite(true);
}

bool ProcMouse::wkStandbyLogin() {
  WinView *view = pssCreateView(unknown08.c_str(), pssGetParentView(), 0);
  mm::Rect<int> rect = ProcDesktop::getView()->getRect(false);
  view->setRect(rect);
  view->unknown3c0.add(5);
  view->unknown528 = 2;
  view->unknown3b8 |= 8;
  get()->m_pos = mm::Pnt<int>(0, 0);
  get()->unknown200 = mm::Pnt<int>(0, 0);
  return WinProc::wkStandbyLogin();
}

bool ProcMouse::wkStandbyLogout() {
  if (unknown60.size() != 0) {
    return false;
  }
  WinView *desktopView = ProcDesktop::getView();
  if (desktopView != nullptr && desktopView->unknown60.size() != 0) {
    if (desktopView->wkGetChild()->begin()->value == pssGetView(0xffffffff)) {
      return false;
    }
  }
  return WinProc::wkStandbyLogout();
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::ProcMouse>::~PtrSingleton();
