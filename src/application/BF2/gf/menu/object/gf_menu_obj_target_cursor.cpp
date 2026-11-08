#include "gf/menu/object/gf_menu_obj_target_cursor.h"

#include "gf/menu/gf_menu_manager.h"
#include "mm_mtl/delegate.h" // IWYU pragma: keep
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjTargetCursor::GfMenuObjTargetCursor(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown28(-1), unknown30(0), unknown38(0), unknown40(this), unknown2d0(this), unknown560(false), unknown564(0), unknown568(false) {}

GfMenuObjTargetCursor::~GfMenuObjTargetCursor() {}

void GfMenuObjTargetCursor::finalize() { GfMenuObject::finalize(); }

void GfMenuObjTargetCursor::disp(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x12));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjTargetCursor::refreshDisp(u32 kind) {
  ui::UIObjectAcc field(unknown18, "IMG_en_cursor");
  ui::UIObjectAcc fieldArrow(unknown18, "IMG_en_cursor_arrow");
  ui::UIObjectAcc battle(unknown18, "IMG_en_cursor_btl");
  ui::UIObjectAcc battleArrow(unknown18, "IMG_en_cursor_btl_arrow");
  field.setDisp(kind == 0);
  fieldArrow.setDisp(kind == 0);
  battle.setDisp(kind == 1);
  battleArrow.setDisp(kind == 1);
}

void GfMenuObjTargetCursor::startCursorAnimation(const char *name) {
  refreshDisp(unknown56c);
  if (unknown56c == 0) {
    ui::UIObjectAcc cursor(unknown18, "IMG_en_cursor");
    ui::UIObjectAcc arrow(unknown18, "IMG_en_cursor_arrow");
    cursor.startAnimation(name, false);
    arrow.startAnimation(name, false);
  } else {
    ui::UIObjectAcc cursor(unknown18, "IMG_en_cursor_btl");
    ui::UIObjectAcc arrow(unknown18, "IMG_en_cursor_btl_arrow");
    cursor.startAnimation(name, false);
    arrow.startAnimation(name, false);
  }
}

bool GfMenuObjTargetCursor::seqEnCursorInTarget() {
  ui::UIObjectAcc cursor(unknown18, "IMG_en_cursor");
  bool isEnd;
  if (!unknown560) {
    startCursorAnimation("fadein");
    isEnd = false;
    unknown560 = true;
  } else if (!cursor.isPlayingAnimation()) {
    startCursorAnimation("idol");
    isEnd = true;
    unknown560 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjTargetCursor::seqEnCursorInBattle() {
  ui::UIObjectAcc cursor(unknown18, "IMG_en_cursor_btl");
  bool isEnd;
  if (!unknown560) {
    startCursorAnimation("fadein");
    isEnd = false;
    unknown560 = true;
  } else if (!cursor.isPlayingAnimation()) {
    startCursorAnimation("idol");
    isEnd = true;
    unknown560 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjTargetCursor::seqEnCursorLock() {
  ui::UIObjectAcc cursor(unknown18, "IMG_en_cursor_sub");
  bool isEnd;
  if (!unknown560) {
    cursor.startAnimation("lock", false);
    cursor.setDisp(true);
    isEnd = false;
    unknown560 = true;
  } else if (!cursor.isPlayingAnimation()) {
    unknown560 = false;
    cursor.startAnimation("idol", false);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjTargetCursor::seqEnCursorOutScreen() {
  ui::UIObjectAcc field(unknown18, "IMG_en_cursor");
  ui::UIObjectAcc battle(unknown18, "IMG_en_cursor_btl");
  bool isEnd;
  if (!unknown560) {
    startCursorAnimation("cursor_in");
    isEnd = false;
    unknown560 = true;
    unknown568 = true;
  } else if (!field.isPlayingAnimation()) {
    if (!battle.isPlayingAnimation()) {
      startCursorAnimation("mini_idol");
      isEnd = true;
      unknown560 = false;
    } else {
      isEnd = false;
    }
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjTargetCursor::seqEnCursorInScreen() {
  ui::UIObjectAcc field(unknown18, "IMG_en_cursor");
  ui::UIObjectAcc battle(unknown18, "IMG_en_cursor_btl");
  bool isEnd;
  if (!unknown560) {
    startCursorAnimation("cursor_out");
    isEnd = false;
    unknown568 = false;
    unknown560 = true;
  } else if (!field.isPlayingAnimation()) {
    if (!battle.isPlayingAnimation()) {
      startCursorAnimation("idol");
      isEnd = true;
      unknown560 = false;
    } else {
      isEnd = false;
    }
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjTargetCursor::seqEnCursorOpen() {
  ui::UIObjectAcc cursor(unknown18, "IMG_en_cursor");
  ui::UIObjectAcc arrow(unknown18, "IMG_en_cursor_arrow");
  bool isEnd;
  if (!unknown560) {
    refreshDisp(0);
    cursor.startAnimation("fadein", false);
    arrow.startAnimation("fadein", false);
    isEnd = false;
    unknown560 = true;
  } else if (!cursor.isPlayingAnimation()) {
    unknown560 = false;
    if (GfMenuManager::isBattleState(0) && unknown30 == 1) {
      unknown40.unknown002(&GfMenuObjTargetCursor::seqEnCursorLock);
    } else {
      cursor.startAnimation("idol", false);
      arrow.startAnimation("idol", false);
    }
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjTargetCursor::seqCursorClose() {
  ui::UIObjectAcc field(unknown18, "IMG_en_cursor");
  ui::UIObjectAcc battle(unknown18, "IMG_en_cursor_btl");
  ui::UIObjectAcc sub(unknown18, "IMG_en_cursor_sub");
  bool isStarted = unknown560;
  bool isFieldDisp = field.isDisp();
  bool isEnd;
  if (!isStarted) {
    if (!isFieldDisp) {
      ui::UIObjectAcc other(unknown18, "IMG_other_cursor");
      other.setDisp(false);
    } else {
      if (!unknown568) {
        startCursorAnimation("fadeout");
      } else {
        startCursorAnimation("mini_fadeout");
      }
      sub.startAnimation("fadeout", false);
    }
    isEnd = false;
    unknown560 = true;
  } else if (!isFieldDisp || !field.isPlayingAnimation()) {
    if (!battle.isDisp() || !battle.isPlayingAnimation()) {
      field.setDisp(false);
      battle.setDisp(false);
      sub.setDisp(false);
      isEnd = true;
      unknown560 = false;
    } else {
      isEnd = false;
    }
  } else {
    isEnd = false;
  }
  return isEnd;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjTargetCursor>(const mm::mtl::Delegate<bool()> *);
