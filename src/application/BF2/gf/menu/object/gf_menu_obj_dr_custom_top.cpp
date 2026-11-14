#include "gf/menu/object/gf_menu_obj_dr_custom_top.h"

#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/object/gf_menu_obj_blade_set.h"
#include "gf/menu/object/gf_menu_obj_common_detail.h"
#include "gf/menu/object/gf_menu_obj_common_jog.h"
#include "gf/menu/object/gf_menu_obj_dr_arts_set.h"
#include "gf/menu/object/gf_menu_obj_dr_equip.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_curve.h"
#include "ui/ctrl/ui_ctrl_object.h"
#include "ui/ctrl/ui_ctrl_revolve_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjDrCustomTop::GfMenuObjDrCustomTop(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown50(nullptr), unknown58(this) {}

GfMenuObjDrCustomTop::~GfMenuObjDrCustomTop() {
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
}

void GfMenuObjDrCustomTop::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (!main.isValid()) {
    return;
  }
// __LINE__ must be 74 as in the original file: it is the line argument of operator new.
#line 74
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  {
    GfMenuDriverList::PartySetup setup;
    setup.unknown18 = false;
    setup.unknown14 = GfPartySelect::LIST_TYPE_UNKNOWN_2;
    unknown28 = GfMenuDriverList::create();
    unknown28->setupFromParty(setup);
    unknown28->setIndex(0);
  }
  {
    ui::UIObjectAcc select(unknown18, "LAY_dr_select");
    ui::UISelectObjList::CreateParam createParam = {};
    createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
    unknown30 = ui::UISelectObjList::create(createParam);
    for (u32 i = 0; i < unknown28->getSize(); i++) {
      ui::UIObjectAcc image(select.duplicateChild("LAY_dr_image"));
      if (image.isValid()) {
        GfMenuCharDataAdapter::create(image.searchChild("IMG_dr_image"), 0x1c, OBJECT_TYPE_PC, unknown28->getContents(i).unknown00, false);
        image.setDisp(true);
        unknown30->addObject(image.unknown10);
      }
    }
    ui::UICtrlRevolveSelect::RevolveSetting setting;
    {
      ui::UIObjectAcc spot(select.unknown10, "IMG_dr_spot");
      mm::Rect<s16> rect;
      spot.getRect(rect, ui::UIObjectAcc::RECT_SCALED);
      s16 centerX = rect.x + rect.width / 2;
      select.getLayoutRect("dr_fimege", rect);
      s16 centerY = rect.y + rect.height / 2;
      u32 priority = select.getDispPriority();
      if (unknown30->getSize() >= 4) {
        priority = unknown30->getSize() - 3;
      }
      setting.unknown00 = 360;
      setting.unknown02 = 2;
      setting.unknown08 = mm::Pnt<s16>(centerX, centerY);
      setting.unknown0c = 150;
      setting.unknown24 = ui::CURVE_TYPE_SIN90;
      setting.unknown20 = priority;
      setting.unknown04 = 0.5f;
      setting.unknown2c = 0.5f;
      setting.unknown18 = 0.25f;
    }
    unknown38 = ui::UICtrlRevolveSelect::create(select.unknown10, setting, unknown30);
    if (unknown38 != nullptr) {
      unknown38->setupEventHanding(select.unknown10, 1);
    }
    GfMenuCharDataAdapter::createFromReferenceDriver(select.searchChild("TXT_dr_select_name"), 2, 0, false);
    GfMenuReference::setReferenceDriverID(0, unknown28->getContents(unknown28->getIndex(false)).unknown00);
    if (unknown28->getSize() >= 2) {
      setupInputSelectionFromList(select.unknown10, *unknown28);
    } else {
      select.setDispChild(false, "LAY_dr_select_input");
    }
// __LINE__ must be 174 as in the original file: it is the line argument of operator new.
#line 174
    DrSelectListener *drSelectListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DrSelectListener(this);
    drSelectListener->addRef();
    ui::UIEventManager::get()->registObjectListener(select.unknown10, drSelectListener);
    if (drSelectListener != nullptr) {
      drSelectListener->release();
    }
  }
  GfMenuObject::initialize();
}

void GfMenuObjDrCustomTop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrCustomTop::update() {
  unknown58.unknown003();
  GfMenuObject::update();
}

void GfMenuObjDrCustomTop::suspendInput() {
  GfMenuObject::disableFSSwitching();
  if (unknown40 != nullptr) {
    GfMenuObjCommonJog::disable(unknown40);
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::disableInput(acc.searchChild("LAY_main"));
  GfMenuObject::disableInput(acc.searchChild("LAY_dr_select"));
}

void GfMenuObjDrCustomTop::resumeInput() {
  GfMenuObject::enableFSSwitching();
  if (unknown40 != nullptr && unknown40->isActive()) {
    GfMenuObjCommonJog::enable(unknown40);
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_main"));
  GfMenuObject::enableInput(acc.searchChild("LAY_dr_select"));
}

bool GfMenuObjDrCustomTop::seqStartOpen() {
  suspendInput();
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjDrCustomTop::seqAppearPhase1() {
  if (unknown2e8 == -1) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    unknown2e8 = GfMenuObjUtil::startCtrl(acc.searchChild("IMG_bg"), param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
    return false;
  }
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjDrCustomTop::seqAppearPhase2() {
  if (unknown2e8 == -1) {
    ui::UIObjectAcc acc(unknown18, "LAY_index");
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown00 = 1;
    param.unknown04 = 0;
    unknown2e8 = GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
    return false;
  }
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjDrCustomTop::seqAppearPhase3() {
  if (unknown40 == nullptr) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjCommonJog::OpenParam jog;
    jog.unknown04 = -1;
    unknown40 = GfMenuCallContext::create();
    jog.unknown00 = 5;
    GfMenuObjCommonJog::open(unknown40, jog);
    GfMenuObject::setCallContextEventHandler(unknown40, acc.unknown10);
    GfMenuObjCommonDetail::OpenParam detail;
    unknown48 = GfMenuCallContext::create();
    detail.unknown00.push_back(0x1ec);
    detail.unknown18 = 0;
    detail.unknown1c = 0;
    detail.unknown2c = acc.searchChild("LAY_dr_detail");
    acc.getLayoutRect("driver_detail", detail.unknown20);
    GfMenuObjCommonDetail::open(unknown48, detail);
  }
  GfMenuCallContext::GfMenuResult result;
  if (!unknown40->isActive()) {
    return true;
  }
  if (!unknown40->unknown18.empty() && unknown40->popResult(result) && result.unknown04 == 0) {
    return true;
  }
  return false;
}

bool GfMenuObjDrCustomTop::seqAppearPhase4() {
  if (unknown2e8 == -1) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    unknown2e8 = GfMenuObjUtil::startCtrl(acc.searchChild("LAY_driver"), param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
    return false;
  }
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjDrCustomTop::seqEndOpen() {
  resumeInput();
  return true;
}

bool GfMenuObjDrCustomTop::seqStartAddLayer() {
  suspendInput();
  unknown2e8 = -1;
  return true;
}

void GfMenuObjDrCustomTop::DrSelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case 6: {
    u32 index = event.unknown08;
    if (index != 0xffffffff) {
      unknown20->unknown28->setIndex(index);
      unknown20->unknown30->setIndex(index);
      GfMenuDriverList *list = unknown20->unknown28;
      GfMenuReference::setReferenceDriverID(0, list->getContents(list->getIndex(false)).unknown00);
    }
    break;
  }
  case 0xe:
    if (ui::UICtrlObject::getEventCtrlObjID(event) == 1) {
      // The game never sets x0 for this call (0x7100450708): receiveRevolveEvent, defined in this file, does not read its object, so the compiler dropped the argument and the original
      // expression cannot be checked. The owner is the object the other listeners of this class call their owner's functions on.
      unknown20->receiveRevolveEvent(event, acc.unknown10);
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjDrCustomTop::receiveRevolveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  if (ui::UICtrlObject::getEventType(event) == 0) {
    ui::uiEventParam param;
    ui::UICtrlObject::getEventParam(event, 1, param);
    if (param.valueF32 != 0.0f) {
      ui::UIObjectAcc spot(acc.unknown10, "IMG_dr_spot");
      spot.setAlpha(1.0f);
      GfMenuObjUtil::CtrlParam ctrl;
      ctrl.unknown08 = 2;
      ctrl.unknown0c = 4;
      ctrl.unknown00 = param.valueF32;
      GfMenuObjUtil::startCtrl(acc.searchChild("IMG_dr_spot"), ctrl, nullptr);
    }
  }
}

bool GfMenuObjDrCustomTop::seqAddLayerPhase2() {
  GfMenuObject::enableFSSwitching();
  GfMenuObject::changeFSSubLayer(unknown18, 2, unknown2ec, true);
  if (unknown50 == nullptr) {
    unknown50 = GfMenuCallContext::create();
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_dr_select"));
  return true;
}

bool GfMenuObjDrCustomTop::seqAddLayerPhase3_DrEquip() { return GfMenuObjDrEquip::attach(unknown50); }

bool GfMenuObjDrCustomTop::seqAddLayerPhase3_DrArtsSet() { return GfMenuObjDrArtsSet::attach(unknown50); }

bool GfMenuObjDrCustomTop::seqAddLayerPhase4() { return unknown50->isTerm(); }

bool GfMenuObjDrCustomTop::seqEndAddLayer() {
  mm::mtl::safeRelease(unknown50);
  resumeInput();
  return true;
}

void GfMenuObjDrCustomTop::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown20->unknown58.unknown002(&GfMenuObjDrCustomTop::seqStartOpen);
    unknown20->unknown58.unknown002(&GfMenuObjDrCustomTop::seqAppearPhase1);
    unknown20->unknown58.unknown002(&GfMenuObjDrCustomTop::seqAppearPhase2);
    unknown20->unknown58.unknown002(&GfMenuObjDrCustomTop::seqAppearPhase3);
    unknown20->unknown58.unknown002(&GfMenuObjDrCustomTop::seqAppearPhase4);
    unknown20->unknown58.unknown002(&GfMenuObjDrCustomTop::seqEndOpen);
    break;
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = 0.25f;
    param.unknown14 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  case 3:
    GfMenuObject::enableFSSwitching();
    GfMenuObject::returnFSSubLayer(acc.unknown10, 1);
    break;
  case 8:
    if (event.unknown0c == 2) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 2;
      param.unknown00 = 0.25f;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
      GfMenuObjCommonJog::close(unknown20->unknown40);
      unknown20->suspendInput();
    }
    break;
  default:
    if (event.unknown00 == 0x41) {
      u32 layer = event.unknown14;
      if (unknown20->unknown40 == nullptr || unknown20->unknown40->unknown0c != event.unknown08 || event.unknown10_u16 != 3) {
        break;
      }
      if ((layer & 0xffff) == 6) {
        GfMenuObjBladeSet::OpenParam param;
        param.unknown00 = 0;
        param.unknown04 = unknown20->unknown28->getContents(unknown20->unknown28->getIndex(false)).unknown00;
        GfMenuObjBladeSet::registOpenParam(param);
        GfMenuObject::changeFSSubLayer(acc.unknown10, 1, 6, true);
        GfMenuObjCommonJog::close(unknown20->unknown40);
      } else if ((layer & 0xffff) == 0x22) {
        GfMenuObject::changeFSSubLayer(acc.unknown10, 1, 0x22, true);
        GfMenuObjCommonJog::close(unknown20->unknown40);
      } else {
        unknown20->unknown2ec = layer;
        unknown20->unknown58.unknown002(&GfMenuObjDrCustomTop::seqStartAddLayer);
        unknown20->unknown58.unknown002(&GfMenuObjDrCustomTop::seqAddLayerPhase1);
        unknown20->unknown58.unknown002(&GfMenuObjDrCustomTop::seqAddLayerPhase2);
        if ((layer & 0xffff) == 0x21) {
          unknown20->unknown58.unknown002(&GfMenuObjDrCustomTop::seqAddLayerPhase3_DrEquip);
        } else if ((layer & 0xffff) == 0x20) {
          unknown20->unknown58.unknown002(&GfMenuObjDrCustomTop::seqAddLayerPhase3_DrArtsSet);
        }
        unknown20->unknown58.unknown002(&GfMenuObjDrCustomTop::seqAddLayerPhase4);
        unknown20->unknown58.unknown002(&GfMenuObjDrCustomTop::seqAddLayerPhase5);
        unknown20->unknown58.unknown002(&GfMenuObjDrCustomTop::seqEndAddLayer);
      }
      break;
    }
  case 4:
  case 5:
  case 6:
  case 7:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjDrCustomTop>(const mm::mtl::Delegate<bool()> *);
