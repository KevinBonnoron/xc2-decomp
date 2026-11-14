#include "gf/menu/object/gf_menu_obj_party_form2.h"

#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/list/gf_menu_field_skill_list.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/delegate.h" // IWYU pragma: keep
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h" // IWYU pragma: keep
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjPartyForm2::GfMenuObjPartyForm2(u32 handle)
    : GfMenuObject(handle), unknown38(false), unknown40(), unknown60(0xff), unknown64(0xff), unknown68(this), unknown2f8(0), unknown2fc(-1), unknown300(-1), unknown304(-1), unknown308(0),
      unknown310(nullptr), unknown318(nullptr) {}

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

void GfMenuObjPartyForm2::finalize() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown318);
  mm::mtl::safeRelease(unknown320);
  mm::mtl::safeRelease(unknown40[0].unknown08);
  mm::mtl::safeRelease(unknown40[0].unknown00);
  mm::mtl::safeRelease(unknown40[1].unknown08);
  mm::mtl::safeRelease(unknown40[1].unknown00);
  GfMenuObject::finalize();
}

void GfMenuObjPartyForm2::setupPlate(u32 plate, GfMenuDriverList *list, u32 index, bool isNumber) {
  ui::UIObjectAcc acc(plate);
  if (acc.isValid()) {
    int driver = GfMenuObjUtil::convMenuDriverID(list->getContents(index).unknown00);
    ui::UIObjectAcc(acc.unknown10, "LAY_plate_dr_info").setDisp(driver != 0);
    if (driver == 0) {
      ui::UIObjectAcc(acc.unknown10, "IMG_bustup").setDisp(false);
    } else {
      ui::UIObjectAcc(acc.unknown10, "IMG_bustup").setImageIndex(driver - 1);
    }
    if (isNumber) {
      ui::UIObjectAcc(acc.unknown10, "IMG_number").setImageIndex(index);
    } else {
      ui::UIObjectAcc(acc.unknown10, "LAY_order").setDisp(false);
    }
    GfMenuCharDataAdapter::createFromDriverList(acc.searchChild("TXT_dr_name"), 2, list, index, false);
    GfMenuCharDataAdapter::createFromDriverList(acc.searchChild("IMG_bl_icon"), 0x1b, list, index, false);
    GfMenuCharDataAdapter::createFromDriverList(acc.searchChild("TXT_lv_num"), 1, list, index, false);
    GfMenuCharDataAdapter::createFromDriverList(acc.searchChild("TXT_hp_num"), 0, list, index, false);
    GfMenuCharDataAdapter::createFromDriverList(acc.searchChild("TXT_hp_max"), 0, list, index, false);
    if (unknown38) {
      acc.setMulColor("gray");
    }
    if (index == 0) {
      ui::UIObjectAcc(acc.unknown10, "IMG_lock").setDisp(true);
    } else {
      ui::UIObjectAcc(acc.unknown10, "IMG_lock").setDisp(false);
    }
  }
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

void GfMenuObjPartyForm2::swapDriver(u32 index, u32 other) {
  if (index < unknown28->getSize()) {
    if (other < unknown28->getSize()) {
      unknown28->swapContents(index, other);
    } else {
      unknown28->swapContents(index, unknown30, other - unknown28->getSize());
    }
  }
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  if (acc.isValid()) {
    ui::UISelectObjList *list = unknown40[1].unknown00;
    {
      ui::UIObjectAcc first(list->getObject(index), "IMG_bustup");
      ui::UIObjectAcc second(list->getObject(other), "IMG_bustup");
      u32 firstImage = first.getImageIndex();
      u32 secondImage = second.getImageIndex();
      first.setImageIndex(secondImage);
      second.setImageIndex(firstImage);
    }
    {
      ui::UIObjectAcc first(list->getObject(index), "IMG_lock");
      ui::UIObjectAcc second(list->getObject(other), "IMG_lock");
      bool firstDisp = first.isDisp();
      bool secondDisp = second.isDisp();
      first.setDisp(secondDisp);
      second.setDisp(firstDisp);
    }
  }
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

bool GfMenuObjPartyForm2::seqMovePlate() {
  if (unknown300 == -1 && unknown304 == -1) {
    ui::UIObjectAcc taken(unknown40[unknown64].unknown00->getSelectObject());
    ui::UIObjectAcc target(unknown40[unknown60].unknown00->getSelectObject());
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x80;
    param.unknown00 = 0.5f;
    param.unknown0c = 1;
    param.unknown14 = 4;
    mm::Pnt<s16> pos;
    target.getPos(pos);
    param.unknown26 = pos;
    param.unknown18 = unknown300;
    unknown300 = GfMenuObjUtil::startCtrl(taken.unknown10, param, nullptr);
    taken.getPos(pos);
    param.unknown26 = pos;
    param.unknown18 = unknown304;
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

bool GfMenuObjPartyForm2::seqPutPlate() {
  if (unknown300 == -1 && unknown304 == -1) {
    ui::UIObjectAcc taken(unknown40[unknown64].unknown00->getSelectObject());
    ui::UIObjectAcc target(unknown40[unknown60].unknown00->getSelectObject());
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x80000;
    param.unknown00 = 0.25f;
    param.unknown2c = 1.0f;
    param.unknown0c = 1;
    param.unknown14 = 4;
    param.unknown18 = unknown300;
    unknown300 = GfMenuObjUtil::startCtrl(taken.unknown10, param, nullptr);
    param.unknown18 = unknown304;
    unknown304 = GfMenuObjUtil::startCtrl(target.unknown10, param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown300)) {
    return false;
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown304)) {
    return false;
  }
  GfMenuObjUtil::setCtrlDefault(unknown300);
  GfMenuObjUtil::releaseCtrl(unknown300);
  GfMenuObjUtil::setCtrlDefault(unknown304);
  GfMenuObjUtil::releaseCtrl(unknown304);
  ui::UIObjectAcc taken(unknown40[unknown64].unknown00->getSelectObject());
  ui::UIObjectAcc target(unknown40[unknown60].unknown00->getSelectObject());
  taken.setDispPriority(unknown308);
  target.setDispPriority(unknown308);
  swapDriver(unknown40[unknown64].unknown00->getIndex(false), unknown40[unknown60].unknown00->getIndex(false));
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

void GfMenuObjPartyForm2::DrDetailListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 8:
    if (event.unknown0c != 9) {
      break;
    }
    {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x400002;
      param.unknown0c = 1;
      param.unknown00 = 0.5f;
      param.unknown04 = 2;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    }
    // fall through
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    break;
  case GfMenuTypes::unknown003_33: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x200001;
    param.unknown0c = 1;
    param.unknown00 = 0.5f;
    param.unknown04 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
    } else if (event.unknown08 == 2) {
      ui::UIObjectAcc parent(acc.getParentHandle());
      ui::EventData request;
      request.unknown00 = 0x41;
      GfMenuObject::sendEvent(parent.unknown10, request, 0.0f);
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjPartyForm2::FieldSkillListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 8:
    if (event.unknown0c != 9) {
      break;
    }
    {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x400002;
      param.unknown0c = 1;
      param.unknown00 = 0.5f;
      param.unknown04 = 2;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    }
    // fall through
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    break;
  case GfMenuTypes::unknown003_33: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x200001;
    param.unknown0c = 1;
    param.unknown00 = 0.5f;
    param.unknown04 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
    } else if (event.unknown08 == 2) {
      ui::UIObjectAcc parent(acc.getParentHandle());
      ui::EventData request;
      request.unknown00 = 0x41;
      GfMenuObject::sendEvent(parent.unknown10, request, 0.0f);
    }
    break;
  case 6: {
    int page = event.unknown08;
    ui::UIListInfoBase *list = unknown20->unknown318;
    list->setIndex(list->getPageSize() * page);
    GfMenuReference::setReferenceNumber(0, page + 1);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjPartyForm2>(const mm::mtl::Delegate<bool()> *);
