#include "gf/menu/object/gf_menu_obj_title.h"

#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x18;

bool GfMenuObjTitle::s_NoSaveData = true;

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
} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjTitle>(const mm::mtl::Delegate<bool()> *);
