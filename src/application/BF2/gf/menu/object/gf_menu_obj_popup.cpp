#include "gf/menu/object/gf_menu_obj_popup.h"

#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x76;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;

void GfMenuObjPopup::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPopup::update() {
  unknown60.unknown003();
  GfMenuObject::update();
}

void GfMenuObjPopup::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjPopup::setFadeIn(u32 handle, u32 type) {
  int ctrl = -1;
  switch (type) {
  case 0:
    ctrl = GfMenuObjUtil::unknown002(handle);
    break;
  case 1: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_l_early");
    param.unknown04 = 1;
    param.unknown11 = true;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_r_early");
    param.unknown04 = 1;
    param.unknown11 = true;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  }
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjPopup::setFadeOut(u32 handle, u32 type) {
  int ctrl = -1;
  switch (type) {
  case 0:
    ctrl = GfMenuObjUtil::unknown003(handle);
    break;
  case 1: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_l_early");
    param.unknown14 = 10;
    param.unknown04 = 2;
    param.unknown11 = true;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_r_early");
    param.unknown14 = 10;
    param.unknown04 = 2;
    param.unknown11 = true;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  }
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjPopup::pausePickup() { GF_MENU_REQUEST_EVENT(unknown001, unknown002); }

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjPopup>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjPopup, 8>>(const mm::mtl::Delegate<bool()> *);
