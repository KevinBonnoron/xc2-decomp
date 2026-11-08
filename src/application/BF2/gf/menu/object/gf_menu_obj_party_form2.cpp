#include "gf/menu/object/gf_menu_obj_party_form2.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/delegate.h" // IWYU pragma: keep
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjPartyForm2::GfMenuObjPartyForm2(u32 handle)
    : GfMenuObject(handle), unknown38(false), unknown40(), unknown60(0xff), unknown64(0xff), unknown68(this), unknown2f8(0), unknown2fc(-1), unknown300(-1), unknown304(-1), unknown308(0),
      unknown310(nullptr), unknown318(0) {}

GfMenuObjPartyForm2::~GfMenuObjPartyForm2() {}

void GfMenuObjPartyForm2::update() {
  unknown68.unknown003();
  GfMenuObject::update();
}

void GfMenuObjPartyForm2::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(getMenuLayerID(0xe), layerParam);
}

u32 GfMenuObjPartyForm2::getCursorID(u32 index) {
  u32 id = 0x61;
  if (index == 1) {
    id = 0x62;
  }
  if (index != 0) {
    return id;
  }
  return 0x61;
}

bool GfMenuObjPartyForm2::seqStartOpen() {
  unknown2fc = -1;
  ui::UIObjectAcc(unknown18, "LAY_current").setDisp(false);
  ui::UIObjectAcc(unknown18, "LAY_reserve").setDisp(false);
  ui::UIObjectAcc drSel(unknown18, "LAY_dr_sel");
  disableInput(drSel.unknown10);
  disableFSSwitching();
  return true;
}

bool GfMenuObjPartyForm2::seqAppearTitle() {
  if (unknown2fc == -1) {
    ui::UIObjectAcc title(unknown18, "LAY_title");
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown00 = 1;
    param.unknown04 = 0;
    unknown2fc = GfMenuObjUtil::startPresetCtrl(title.unknown10, param);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2fc)) {
    return false;
  }
  unknown2fc = -1;
  return true;
}

bool GfMenuObjPartyForm2::seqAppearFrame() {
  if (unknown2fc == -1) {
    ui::UIObjectAcc frame(unknown18, "LAY_frame");
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown00 = 3;
    param.unknown04 = 0;
    unknown2fc = GfMenuObjUtil::startPresetCtrl(frame.unknown10, param);
    ui::UIObjectAcc(unknown18, "LAY_dr_sel").setDisp(true);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2fc)) {
    return false;
  }
  unknown2fc = -1;
  return true;
}

bool GfMenuObjPartyForm2::seqAppearPlate() {
  if (unknown2fc == -1) {
    {
      ui::UIObjectAcc current(unknown18, "LAY_current");
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown10 = 0;
      param.unknown00 = 1;
      param.unknown04 = 0;
      unknown2fc = GfMenuObjUtil::startPresetCtrl(current.unknown10, param);
    }
    {
      ui::UIObjectAcc reserve(unknown18, "LAY_reserve");
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown10 = 0;
      param.unknown00 = 0;
      param.unknown04 = 0;
      GfMenuObjUtil::startPresetCtrl(reserve.unknown10, param);
    }
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2fc)) {
    return false;
  }
  unknown2fc = -1;
  return true;
}

bool GfMenuObjPartyForm2::seqAnnounceChange() {
  if (unknown310 != nullptr) {
    return unknown310->isTerm();
  }
  unknown310 = GfMenuCallContext::create();
  GfMenuObjCommonText::open(unknown310, 0xd, 0);
  return false;
}

bool GfMenuObjPartyForm2::seqWaitOpenEnd() {
  changeCursorMode(0);
  {
    ui::UIObjectAcc drSel(unknown18, "LAY_dr_sel");
    enableInput(drSel.unknown10);
    GfMenuObjOperationInfo::open(drSel.unknown10, 0, 0, 0);
  }
  enableFSSwitching();
  return true;
}

bool GfMenuObjPartyForm2::seqStartSwap() {
  ui::UIObjectAcc drSel(unknown18, "LAY_dr_sel");
  disableInput(drSel.unknown10);
  disableFSSwitching();
  GfMenuObjOperationInfo::setDisp(false);
  {
    mm::mtl::FixStr<32> name;
    name.format("LAY_cursor_%c", 0x61);
    drSel.setDispChild(false, name.c_str());
    name.format("LAY_cursor_%c", 0x62);
    drSel.setDispChild(false, name.c_str());
  }
  drSel.setDispChild(false, "IMG_head_cursor");
  ui::UIObjectAcc plate(unknown40[unknown64].unknown00->getSelectObject());
  unknown300 = -1;
  unknown304 = -1;
  unknown308 = plate.getDispPriority();
  return true;
}

bool GfMenuObjPartyForm2::seqTakePlate() {
  if (unknown300 == -1 && unknown304 == -1) {
    ui::UIObjectAcc taken(unknown40[unknown64].unknown00->getSelectObject());
    ui::UIObjectAcc target(unknown40[unknown60].unknown00->getSelectObject());
    taken.setDispPriority(unknown308 + 1);
    target.setDispPriority(unknown308 + 2);
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x80000;
    param.unknown00 = 0.25f;
    param.unknown2c = 1.1f;
    param.unknown0c = 1;
    param.unknown14 = 4;
    unknown300 = GfMenuObjUtil::startCtrl(taken.unknown10, param, nullptr);
    unknown304 = GfMenuObjUtil::startCtrl(target.unknown10, param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown300)) {
    return false;
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown304)) {
    return false;
  }
  unknown300 = -1;
  unknown304 = -1;
  return true;
}

bool GfMenuObjPartyForm2::seqWaitSwapEnd() {
  changeCursorMode(0);
  ui::UIObjectAcc drSel(unknown18, "LAY_dr_sel");
  enableInput(drSel.unknown10);
  enableFSSwitching();
  GfMenuObjOperationInfo::setDisp(true);
  return true;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjPartyForm2>(const mm::mtl::Delegate<bool()> *);
