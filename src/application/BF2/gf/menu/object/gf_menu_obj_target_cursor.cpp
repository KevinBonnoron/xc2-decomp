#include "gf/menu/object/gf_menu_obj_target_cursor.h"

#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_pos_adapter.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/delegate.h" // IWYU pragma: keep
#include "mm_mtl/fixstr.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjTargetCursor::GfMenuObjTargetCursor(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown28(unknown020), unknown30(0), unknown38(nullptr), unknown40(this), unknown2d0(this), unknown560(false), unknown564(0), unknown568(false) {}

GfMenuObjTargetCursor::~GfMenuObjTargetCursor() {}

void GfMenuObjTargetCursor::finalize() { GfMenuObject::finalize(); }

void GfMenuObjTargetCursor::initialize() {
  ui::UIObjectAcc acc(unknown18);
  attachExternalCall(0x12, unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
// __LINE__ must be 107 as in the original file: it is the line argument of operator new.
#line 107
    MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
    unknown24 = main;
    unknown38 = GfMenuPosAdapter::create(acc.searchChild("LAY_en_cursor"), unknown020, nullptr);
    unknown38->setPosAdjustScreen(true);
    unknown38->setPosOffsMode(1);
    unknown38->unknown84 = mm::Pnt<s16>(0, -5);
    addPosEventCondition(main, "LAY_en_cursor", 0, 0);
    GfMenuObjUtil::createSyncPlugin(acc.searchChild("IMG_en_cursor_arrow"), acc.searchChild("IMG_en_cursor"), 0x20);
    GfMenuObjUtil::createSyncPlugin(acc.searchChild("IMG_en_cursor_btl_arrow"), acc.searchChild("IMG_en_cursor_btl"), 0x20);
  }
  GfMenuObject::initialize();
}

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

void GfMenuObjTargetCursor::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown0c = 0;
    break;
  case 0xd: {
    u64 param = event.unknown08_u64;
    if (param >> 32 == 0 && unknown0c == 1) {
      unknown20->unknown40.unknown005();
      if (static_cast<int>(param) == 7) {
        unknown20->unknown40.unknown002(&GfMenuObjTargetCursor::seqEnCursorOutScreen);
        unknown20->unknown560 = false;
      } else {
        unknown20->unknown40.unknown002(&GfMenuObjTargetCursor::seqEnCursorInScreen);
        unknown20->unknown560 = false;
      }
    }
    break;
  }
  case 0x100: {
    u32 level = event.unknown0c;
    {
      mm::mtl::FixStr<32> color;
      ui::UIObjectAcc arrow(acc.unknown10, "IMG_en_cursor_arrow");
      ui::UIObjectAcc battleArrow(acc.unknown10, "IMG_en_cursor_btl_arrow");
      color.format("tgt_cursor_lv%02d", level);
      arrow.setMulColor(color.c_str());
      battleArrow.setMulColor(color.c_str());
    }
    acc.setDispChild(true, "LAY_en_cursor");
    acc.setDispChild(true, "IMG_en_cursor");
    acc.setDispChild(false, "IMG_en_cursor_sub");
    unknown20->unknown40.unknown005();
    unknown20->unknown40.unknown002(&GfMenuObjTargetCursor::seqEnCursorOpen);
    unknown20->unknown560 = false;
    unknown20->unknown38->setPosAdjustSize(0x20, 0x20);
    GfMenuObjUtil::playSE(0x1c);
    acc.setDisp(true);
    unknown0c = 1;
    break;
  }
  case 0x101:
    if (unknown0c == 1) {
      unknown20->unknown40.unknown005();
      unknown20->unknown40.unknown002(&GfMenuObjTargetCursor::seqCursorClose);
      unknown20->unknown560 = false;
      unknown0c = 0;
    }
    break;
  case 0x102: {
    ui::UIObjectAcc sub(acc.unknown10, "IMG_en_cursor_sub");
    if (unknown0c == 1) {
      if (unknown20->unknown30 == 1) {
        unknown20->unknown2d0.unknown005();
        unknown20->unknown2d0.unknown002(&GfMenuObjTargetCursor::seqEnCursorLock);
        unknown20->unknown560 = false;
      } else {
        sub.setDisp(false);
      }
    }
    break;
  }
  case 0x120:
    if (unknown0c == 1) {
      int type = event.unknown08;
      unknown20->unknown40.unknown005();
      if (type == 0) {
        unknown20->unknown40.unknown002(&GfMenuObjTargetCursor::seqEnCursorInTarget);
        unknown20->unknown560 = false;
      } else {
        unknown20->unknown40.unknown002(&GfMenuObjTargetCursor::seqEnCursorInBattle);
        unknown20->unknown560 = false;
      }
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjTargetCursor>(const mm::mtl::Delegate<bool()> *);
