#include "gf/menu/object/gf_menu_obj_inn.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/ctrl/ui_ctrl_slide_select.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjInn::GfMenuObjInn(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(nullptr), unknown88(1), unknown98(false),
      unknown0a0(this) {}

GfMenuObjInn::~GfMenuObjInn() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown58);
  mm::mtl::safeRelease(unknown50);
}

void GfMenuObjInn::finalize() { GfMenuObject::finalize(); }

void GfMenuObjInn::update() {
  unknown0a0.unknown003();
  GfMenuObject::update();
}

void GfMenuObjInn::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjInn::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjInn::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjInn::seqFadeOut() {
  GfMenuFade::setFade(2, 60, mm::Col4::black);
  return true;
}

bool GfMenuObjInn::seqFadeOutWait() {
  ui::UIObjectAcc acc(unknown18);
  bool isEnd;
  if (GfMenuFade::isFading(2)) {
    isEnd = false;
  } else {
    closeFSLayer(acc.unknown10, true, true);
    isEnd = true;
  }
  return isEnd;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjInn>(const mm::mtl::Delegate<bool()> *);
