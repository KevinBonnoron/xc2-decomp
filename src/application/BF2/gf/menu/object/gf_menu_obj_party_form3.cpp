#include "gf/menu/object/gf_menu_obj_party_form3.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: menu id; original name unknown.
constexpr u32 unknown001 = 0x24;

GfMenuObjPartyForm3::GfMenuObjPartyForm3(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(0), unknown34(0), unknown38(0), unknown3c(0), unknown40(-1), unknown44(false), unknown80(this), unknown310(nullptr), unknown318(true),
      unknown319(false) {
  unknown48.assign(mm::mtl::IntrusivePtr<GfMenuReferenceNumber>());
}

GfMenuObjPartyForm3::~GfMenuObjPartyForm3() {
  unknown48.assign(mm::mtl::IntrusivePtr<GfMenuReferenceNumber>());
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown310);
}
void GfMenuObjPartyForm3::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPartyForm3::update() {
  unknown80.unknown003();
  GfMenuObject::update();
}

void GfMenuObjPartyForm3::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown001), layerParam);
}

void GfMenuObjPartyForm3::setupBGLayout(ui::UIObjectAcc &, u32, bool) {}

void GfMenuObjPartyForm3::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjPartyForm3::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjPartyForm3::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjPartyForm3::seqWaitOpenEnd() {
  ui::UIObjectAcc acc(unknown18, "LAY_dr_select");
  enableInput(acc.unknown10);
  return true;
}

void GfMenuObjPartyForm3::refreshRemoveAddOperation(u32 handle, int index) {
  if (unknown40 >= 0) {
    return;
  }
  u32 count = unknown34;
  if (!unknown318) {
    if (static_cast<u32>(index) < count) {
      GfMenuObjOperationInfo::setActionEnable(handle, 9, false);
      return;
    }
  } else if (static_cast<u32>(index) < count) {
    if (count < 2) {
      GfMenuObjOperationInfo::setActionEnable(handle, 9, false);
      return;
    }
    GfMenuObjOperationInfo::setActionEnable(handle, 9, true);
    GfMenuObjOperationInfo::changeText(handle, 9, false);
    return;
  }
  if (count > 2) {
    GfMenuObjOperationInfo::setActionEnable(handle, 9, false);
  } else {
    GfMenuObjOperationInfo::setActionEnable(handle, 9, true);
    GfMenuObjOperationInfo::changeText(handle, 9, true);
  }
}

bool GfMenuObjPartyForm3::seqAnnounceChange() {
  if (unknown310 != nullptr) {
    return unknown310->isTerm();
  }
  unknown310 = GfMenuCallContext::create();
  GfMenuObjCommonText::open(unknown310, 0xd, 0);
  return false;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjPartyForm3>(const mm::mtl::Delegate<bool()> *);
