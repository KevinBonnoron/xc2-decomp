#include "gf/menu/object/gf_menu_obj_help_hud.h"

#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/delegate.h" // IWYU pragma: keep
#include "types.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x84;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x102;

GfMenuObjHelpHud::GfMenuObjHelpHud(u32 handle) : GfMenuObject(handle), unknown24(0), unknown30(this), unknown2c0(false) {}

GfMenuObjHelpHud::~GfMenuObjHelpHud() { ; }

void GfMenuObjHelpHud::finalize() { GfMenuObject::finalize(); }

void GfMenuObjHelpHud::enable() { unknown144(unknown001, unknown002); }

void GfMenuObjHelpHud::disable() { unknown144(unknown001, unknown003); }

void GfMenuObjHelpHud::ctrlFadeOut(u32 handle) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 2;
  param.unknown00 = 0.1f;
  param.unknown14 = 2;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

void GfMenuObjHelpHud::ctrlFadeIn(u32 handle) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 1;
  param.unknown00 = 0.1f;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

bool GfMenuObjHelpHud::seqPageFadeIn() {
  ui::UIObjectAcc acc(unknown18, "IMG_help");
  bool isEnd;
  if (!unknown2c0) {
    ctrlFadeIn(acc.unknown10);
    isEnd = false;
    unknown2c0 = true;
  } else {
    int ctrl = GfMenuObjUtil::getCtrlID(acc.unknown10);
    if (ctrl == -1 || !GfMenuObjUtil::isBusyCtrl(ctrl)) {
      isEnd = true;
      unknown2c0 = false;
    } else {
      isEnd = false;
    }
  }
  return isEnd;
}

bool GfMenuObjHelpHud::seqPageFadeOut() {
  ui::UIObjectAcc acc(unknown18, "IMG_help");
  bool isEnd;
  if (!unknown2c0) {
    ctrlFadeOut(acc.unknown10);
    isEnd = false;
    unknown2c0 = true;
  } else {
    int ctrl = GfMenuObjUtil::getCtrlID(acc.unknown10);
    if (ctrl == -1 || !GfMenuObjUtil::isBusyCtrl(ctrl)) {
      isEnd = true;
      unknown2c0 = false;
    } else {
      isEnd = false;
    }
  }
  return isEnd;
}
} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjHelpHud>(const mm::mtl::Delegate<bool()> *);
