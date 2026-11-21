#include "gf/menu/object/gf_menu_obj_title.h"

#include "execute/title/title_main.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_system.h"
#include "gf/data/gf_game_flag.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x18;

bool GfMenuObjTitle::s_NoSaveData = true;

// Inferred role: name and enable test of each title menu entry; original type name unknown.
struct unknown002 {
  const char *unknown00; // Inferred role: entry text; original member name unknown.
  bool (*unknown08)();   // Inferred role: enable test; original member name unknown.
};

// Inferred role: title menu entries (new game, continue, option, theater, new game advanced); original name unknown.
static const unknown002 unknown003[5] = {
    {"TXT_newgame", GfMenuObjTitle::isEnableNewGame},
    {"TXT_continue", GfMenuObjTitle::isEnableContinue},
    {"TXT_option", GfMenuObjTitle::isEnableOption},
    {"TXT_theater", GfMenuObjTitle::isEnableEventsTheater},
    {"TXT_newgame_adv", GfMenuObjTitle::isEnableNewGameAdv},
};

GfMenuObjTitle::GfMenuObjTitle(u32 handle) : GfMenuObject(handle), unknown48(0), unknown50(nullptr), unknown58(this), unknown1b8(false) { s_NoSaveData = true; }

GfMenuObjTitle::~GfMenuObjTitle() { mm::mtl::safeRelease(unknown50); }

void GfMenuObjTitle::finalize() { GfMenuObject::finalize(); }

void GfMenuObjTitle::update() {
  unknown58.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjTitle::isEnableNewGame() { return true; }

bool GfMenuObjTitle::isEnableNewGameAdv() { return false; }

bool GfMenuObjTitle::isEnableContinue() { return !s_NoSaveData; }

bool GfMenuObjTitle::isEnableOption() { return true; }

bool GfMenuObjTitle::isEnableEventsTheater() {
  if (s_NoSaveData) {
    return false;
  }
  return GfGameFlag::getLocal(tl::TitleMain::get()->getSaveBuffer()->unknown10.unknownfbbc4, 1, FLAG_UNKNOWN_39487) == 1;
}

void GfMenuObjTitle::moveCursor(u32 handle, int index) {
  ui::UIObjectAcc item(handle, unknown003[unknown28[index]].unknown00);
  ui::UIObjectAcc cursor(handle, "LAY_Cursor");
  if (item.isValid() && cursor.isValid()) {
    GfMenuObjUtil::setDockPos(cursor.unknown10, item.unknown10, 0, true);
  }
}

void GfMenuObjTitle::setDispMode(u32 handle, int mode) {
  if (mode == 0) {
    GfMenuObjUtil::setChildDisp(handle, "LAY_keywait", true);
    GfMenuObjUtil::setChildDisp(handle, "LAY_list", false);
  } else if (mode == 1) {
    GfMenuObjUtil::setChildDisp(handle, "LAY_keywait", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_list", true);
  } else {
    GfMenuObjUtil::setChildDisp(handle, "LAY_keywait", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_list", false);
  }
}

void GfMenuObjTitle::setInputMode(u32 handle, int mode) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    if (mode == 0) {
      GfMenuObject::enableInput(acc.searchChild("LAY_keywait"));
      GfMenuObject::disableInput(acc.searchChild("LAY_list"));
    } else if (mode == 1) {
      GfMenuObject::enableInput(acc.searchChild("LAY_list"));
      GfMenuObject::disableInput(acc.searchChild("LAY_keywait"));
    }
  }
}

bool GfMenuObjTitle::seqConfirmNewGame() {
  if (!unknown1b8) {
    GfMenuManager::openCommonWindow(0xe1);
    unknown1b8 = true;
    return false;
  }
  if (GfMenuManager::isOpenCommonWindow()) {
    return false;
  }
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  s16 result = GfMenuManager::getCommonWindowResult();
  if (result == 0) {
    addResultCallContext(acc.unknown10, unknown48, 0);
  } else {
    ui::EventData event;
    event.unknown00 = 0x101;
    sendEvent(acc.unknown10, event, 0.0f);
  }
  return true;
}

bool GfMenuObjTitle::attach(GfMenuCallContext *context) { return unknown151(context, unknown001); }

// Inferred role: switches the title to the key wait (0) or list (1) mode: display, input and the listener state; original name unknown. Shared by the three places of
// ListListener::reciveEvent that do it (the game has the three blocks inlined, each ending with the store to unknown0c at 0x71004dd570, 0x71004dd7a0 and 0x71004dd820);
// written out three times it matches too.
static void unknown004(GfMenuObjTitle::ListListener &listener, u32 handle, int mode) {
  GfMenuObjTitle::setDispMode(handle, mode);
  GfMenuObjTitle::setInputMode(handle, mode);
  listener.unknown0c = mode;
}

void GfMenuObjTitle::ListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    ui::UIObjectAcc cursor(acc.unknown10, "LAY_keywait_cursor");
    GfMenuObjUtil::setDockPos(cursor.unknown10, acc.searchChild("TXT_keywait"), 0, true);
  }
    unknown004(*this, handle, 0);
    acc.setDisp(true);
    break;
  case 2:
    GfMenuObject::termCallContext(handle);
    acc.setTerm();
    break;
  case 6:
    if (unknown0c == 1) {
      u32 index = event.unknown08;
      if (index != 0xffffffff) {
        u32 previous = event.unknown0c;
        if (previous != 0xffffffff) {
          ui::UIObjectAcc old(unknown20->unknown50->getObject(previous));
          old.loadDefColor();
          old.setBorderWeight(2.0f);
        }
        unknown20->moveCursor(handle, index);
        {
          ui::UIObjectAcc select(unknown20->unknown50->getObject(index));
          GfMenuObjUtil::setColMulandAdd(select.unknown10, "txt_title_sel");
          select.setBorderWeight(2.0f);
        }
        if (index != previous) {
          GfMenuObjUtil::playSECommonCursor();
        }
      }
    }
    break;
  case 8: {
    int state = unknown0c;
    // Measured: with case 2 written before case 1 the case blocks of the outer jump table (0x7100f7337c) come out with case 2 after case 6; the game has it before.
    switch (event.unknown0c) {
    case 1:
      if (state == 1) {
        // The game sign-extends the slot (ldrsw, 0x71004dd644) and ui::EventData has only an unsigned view, so the index is a typed local.
        int index = event.unknown08;
        u32 type = unknown20->unknown28[index];
        if (!s_NoSaveData && (type == 0 || type == 4)) {
          unknown20->unknown1b8 = false;
          unknown20->unknown58.unknown005();
          unknown20->unknown58.unknown002(&GfMenuObjTitle::seqConfirmNewGame);
        } else {
          addResultCallContext(handle, type, 0);
        }
        unknown20->unknown48 = type;
        unknown0c = 2;
        GfMenuObject::disableInput(acc.unknown10);
      }
      break;
    case 2:
      if (state == 1) {
        unknown004(*this, handle, 0);
      }
      break;
    default:
      if (state == 0) {
        unknown004(*this, handle, 1);
        u32 selected = 0;
        for (u32 i = 0; i < unknown20->unknown28.size(); i++) {
          if (unknown20->unknown28[i] == 1) {
            selected = i;
            break;
          }
        }
        setupInputSelection(acc.searchChild("LAY_list"), selected, unknown20->unknown28.size());
      }
      break;
    }
    if (state != unknown0c) {
      if (unknown0c == 1) {
        GfMenuObjUtil::playSECommonDecide();
      } else {
        GfMenuObjUtil::playSECommonFromInput(event.unknown0c);
      }
    }
    break;
  }
  case 0x101:
    unknown0c = 1;
    GfMenuObject::enableInput(acc.unknown10);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
  }
}

void GfMenuObjTitle::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
// __LINE__ must be 112 as in the original file: it is the line argument of operator new.
#line 112
    ListListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
    attachExternalCall(unknown001, main);
    u32 keyWait = acc.searchChild("LAY_keywait");
    u32 list = acc.searchChild("LAY_list");
    migrateInput(list, main);
    migrateInput(keyWait, main);
  }
  u32 version = tl::TitleMain::get()->getSaveBuffer()->unknown00;
  s_NoSaveData = version != SAVE_UNKNOWN_237915;
  acc.setDispChild(version == SAVE_UNKNOWN_237915, "IMG_Logo");
  {
    ui::UISelectObjList::CreateParam createParam;
    createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
    unknown50 = ui::UISelectObjList::create(createParam);
  }
  unknown28.clear();
  for (u32 i = 0; i < 5; i++) {
    ui::UIObjectAcc item(acc.unknown10, unknown003[i].unknown00);
    if (item.isValid()) {
      if (unknown003[i].unknown08()) {
        item.setDisp(true);
        unknown28.push_back(i);
        unknown50->addObject(item.unknown10);
      } else {
        item.setDisp(false);
      }
    }
  }
  {
    ui::UIObjectAcc root(main);
    mm::Rect<s16> option;
    root.getLayoutRect("option", option);
    mm::Rect<s16> theater;
    root.getLayoutRect("theater", theater);
    GfMenuObjUtil::placeObjectV(unknown50, mm::Pnt<s16>(option.x + option.width / 2, option.y + option.height / 2), theater.y - option.y);
  }
  GfMenuObject::initialize();
}
} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjTitle>(const mm::mtl::Delegate<bool()> *);
