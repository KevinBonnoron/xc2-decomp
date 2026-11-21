#include "gf/menu/object/gf_menu_obj_bl_custom_top.h"

#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/object/gf_menu_obj_bl_orb.h"
#include "gf/menu/object/gf_menu_obj_bl_weapon.h"
#include "gf/menu/object/gf_menu_obj_blade_set.h"
#include "gf/menu/object/gf_menu_obj_common_detail.h"
#include "gf/menu/object/gf_menu_obj_common_jog.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_object.h"
#include "ui/ctrl/ui_ctrl_revolve_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjBlCustomTop::GfMenuObjBlCustomTop(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown50(nullptr), unknown58(this) {}

GfMenuObjBlCustomTop::~GfMenuObjBlCustomTop() {
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
}

void GfMenuObjBlCustomTop::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
// __LINE__ must be 74 as in the original file: it is the line argument of operator new.
#line 74
    MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
    mainListener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
    if (mainListener != nullptr) {
      mainListener->release();
    }
    {
      GfMenuBladeList::DriverSetup setup;
      setup.unknown14 = 1;
      setup.unknown18 = 1;
      unknown28 = GfMenuBladeList::create();
      unknown28->setupFromDriver(setup);
    }
    unknown28->setIndex(0);
    {
      ui::UIObjectAcc select(unknown18, "LAY_bl_select");
      select.setDispChild(true, "LAY_bl_image");
      GfMenuCharDataAdapter::createFromReferenceBlade(select.searchChild("TXT_bl_select_name"), 2, 0, false);
      GfMenuReference::setReferenceBladeID(0, unknown28->getContents(unknown28->getIndex(false)).unknown00);
      if (unknown28->getSize() >= 3) {
        setupInputSelectionFromList(select.unknown10, *unknown28);
      } else {
        select.setDispChild(false, "LAY_bl_select_input");
      }
// __LINE__ must be 179 as in the original file: it is the line argument of operator new.
#line 179
      DrSelectListener *selectListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DrSelectListener(this);
      selectListener->addRef();
      ui::UIEventManager::get()->registObjectListener(select.unknown10, selectListener);
      if (selectListener != nullptr) {
        selectListener->release();
      }
    }
    GfMenuObject::initialize();
  }
}

void GfMenuObjBlCustomTop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlCustomTop::update() {
  unknown58.unknown003();
  GfMenuObject::update();
}

void GfMenuObjBlCustomTop::suspendInput() {
  GfMenuObject::disableFSSwitching();
  if (unknown40 != nullptr) {
    GfMenuObjCommonJog::disable(unknown40);
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::disableInput(acc.searchChild("LAY_main"));
  GfMenuObject::disableInput(acc.searchChild("LAY_bl_select"));
}

void GfMenuObjBlCustomTop::resumeInput() {
  GfMenuObject::enableFSSwitching();
  if (unknown40 != nullptr && unknown40->isActive()) {
    GfMenuObjCommonJog::enable(unknown40);
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_main"));
  GfMenuObject::enableInput(acc.searchChild("LAY_bl_select"));
}

bool GfMenuObjBlCustomTop::seqStartOpen() {
  suspendInput();
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlCustomTop::seqAppearPhase1() {
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

bool GfMenuObjBlCustomTop::seqAppearPhase2() {
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

bool GfMenuObjBlCustomTop::seqAppearPhase3() {
  if (unknown40 == nullptr) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjCommonJog::OpenParam jogParam;
    unknown40 = GfMenuCallContext::create();
    jogParam.unknown00 = 6;
    GfMenuObjCommonJog::open(unknown40, jogParam);
    GfMenuObject::setCallContextEventHandler(unknown40, acc.unknown10);
    GfMenuObjCommonDetail::OpenParam detailParam;
    unknown48 = GfMenuCallContext::create();
    detailParam.unknown18 = 0;
    detailParam.unknown1c = 1;
    detailParam.unknown00.push_back(0xff);
    detailParam.unknown2c = acc.searchChild("LAY_bl_detail");
    // The game ignores the result of getLayoutRect, as the other menu objects do, and keeps the rect as it is.
    acc.getLayoutRect("driver_detail", detailParam.unknown20);
    GfMenuObjCommonDetail::open(unknown48, detailParam);
  }
  GfMenuCallContext::GfMenuResult result;
  if (!unknown40->isActive() || (!unknown40->unknown18.empty() && unknown40->popResult(result) && result.unknown04 == 0)) {
    return true;
  }
  return false;
}

bool GfMenuObjBlCustomTop::seqAppearPhase4() {
  if (unknown2e8 == -1) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    unknown2e8 = GfMenuObjUtil::startCtrl(acc.searchChild("LAY_blade"), param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
    return false;
  }
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlCustomTop::seqEndOpen() {
  resumeInput();
  return true;
}

bool GfMenuObjBlCustomTop::seqStartAddLayer() {
  suspendInput();
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlCustomTop::seqAddLayerPhase1() {
  if (unknown2e8 == -1) {
    GfMenuObjCommonJog::close(unknown40);
    ui::UIObjectAcc acc(unknown18, "LAY_blade");
    mm::Pnt<s16> pos;
    mm::Rect<s16> to;
    // Ruling 2026-11-13 #3: the first rect shares its stack slot with the control parameter, its lifetime ends before the parameter exists (0x710040fe18).
    {
      mm::Rect<s16> from;
      // The game ignores the result of getLayoutRect, as in seqAppearPhase3.
      acc.getLayoutRect("dr_chage _position01", from);
      acc.getLayoutRect("dr_chage _position02", to);
      acc.getPos(pos);
      pos.x += to.x - from.x;
      pos.y += to.y - from.y;
    }
    GfMenuObjUtil::CtrlParam param;
    // Ruling 2026-11-13 #4, 0x710040fe18: of the 24 orders of these four stores only this one gives the game's bytes, the others give 89 instructions or another order of the stores.
    param.unknown08 = 0x80;
    param.unknown26 = pos;
    param.unknown0c = 1;
    param.unknown00 = 0.25f;
    unknown2e8 = GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
  }
  // Ruling 2026-11-13 #3: the result shares its stack slot with the control parameter and its lifetime ends here; without the block the return value
  // is set before the store of -1 at the end (0x710040ff68), the game stores first.
  {
    GfMenuCallContext::GfMenuResult result;
    if (unknown40->isActive()) {
      if (unknown40->unknown18.empty() || !unknown40->popResult(result) || result.unknown04 != 1) {
        return false;
      }
      unknown40->reset();
    }
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
    return false;
  }
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlCustomTop::seqAddLayerPhase2() {
  GfMenuObject::enableFSSwitching();
  GfMenuObject::changeFSSubLayer(unknown18, 2, unknown2ec, true);
  if (unknown50 == nullptr) {
    unknown50 = GfMenuCallContext::create();
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_bl_select"));
  return true;
}

bool GfMenuObjBlCustomTop::seqAddLayerPhase3_BlWeapon() { return GfMenuObjBlWeapon::attach(unknown50); }

bool GfMenuObjBlCustomTop::seqAddLayerPhase3_BlOrb() { return GfMenuObjBlOrb::attach(unknown50); }

bool GfMenuObjBlCustomTop::seqAddLayerPhase4() { return unknown50->isTerm(); }

bool GfMenuObjBlCustomTop::seqAddLayerPhase5() {
  if (unknown2e8 == -1) {
    ui::UIObjectAcc main(unknown18, "LAY_main");
    GfMenuObjCommonJog::OpenParam jogParam;
    jogParam.unknown00 = 6;
    GfMenuObjCommonJog::open(unknown40, jogParam);
    GfMenuObject::setCallContextEventHandler(unknown40, main.unknown10);
    ui::UIObjectAcc acc(unknown18, "LAY_blade");
    mm::Pnt<s16> pos;
    mm::Rect<s16> to;
    // Ruling 2026-11-13 #8: the game writes the rect block of seqAddLayerPhase1 again here (0x7100410010, the two names swapped). A shared helper that returns the position
    // gives 93 instructions against 90 and a frame of 176 against 160 bytes in seqAddLayerPhase1, so the block stays written out. Ruling 2026-11-13 #3 for the scope of `from`.
    {
      mm::Rect<s16> from;
      // The game ignores the result of getLayoutRect, as in seqAppearPhase3.
      acc.getLayoutRect("dr_chage _position02", from);
      acc.getLayoutRect("dr_chage _position01", to);
      acc.getPos(pos);
      pos.x += to.x - from.x;
      pos.y += to.y - from.y;
    }
    GfMenuObjUtil::CtrlParam param;
    // Ruling 2026-11-13 #4, same order as in seqAddLayerPhase1 (0x7100410010): the only one of the 24 that matches.
    param.unknown08 = 0x80;
    param.unknown26 = pos;
    param.unknown0c = 1;
    param.unknown00 = 0.25f;
    unknown2e8 = GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
  }
  // Ruling 2026-11-13 #3: `result` has its own scope as in seqAddLayerPhase1 (0x7100410010); without the block the bytes differ there.
  {
    GfMenuCallContext::GfMenuResult result;
    if ((!unknown40->isActive() || (!unknown40->unknown18.empty() && unknown40->popResult(result) && result.unknown04 == 0)) && !GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
      unknown2e8 = -1;
      return true;
    }
  }
  return false;
}

bool GfMenuObjBlCustomTop::seqEndAddLayer() {
  mm::mtl::safeRelease(unknown50);
  resumeInput();
  return true;
}

// Twin of GfMenuObjDrCustomTop::DrSelectListener::reciveEvent (1.0.0: 0x7100450604), whose case 6 selects the driver; here cases 1 and 6 do nothing (1.0.0: 0x710041025c, one ccmp).
void GfMenuObjBlCustomTop::DrSelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
  case 6:
    break;
  case 0xe:
    if (ui::UICtrlObject::getEventCtrlObjID(event) == 1) {
      // The game never sets x0 for this call (0x7100410288): receiveRevolveEvent, defined in this file, does not read its object, so the compiler dropped the argument and the original
      // expression cannot be checked. The owner is the object the other listeners of this class call their owner's functions on.
      unknown20->receiveRevolveEvent(event, acc.unknown10);
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

// Repeats the statements of GfMenuObjDrCustomTop::receiveRevolveEvent (1.0.0: 0x7100450750) with the child "IMG_bl_spot" instead of "IMG_dr_spot": the game has two functions of the same code at
// 0x71004102bc and 0x7100450750, one per class, and the two classes only share GfMenuObject. A function taking the child name, inlined into both, matches too, but nothing in the binary (a call, a
// symbol) shows that the original had one, and every other function of the two classes is written out twice on main.
void GfMenuObjBlCustomTop::receiveRevolveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  if (ui::UICtrlObject::getEventType(event) == 0) {
    ui::uiEventParam param;
    ui::UICtrlObject::getEventParam(event, 1, param);
    if (param.valueF32 != 0.0f) {
      ui::UIObjectAcc spot(acc.unknown10, "IMG_bl_spot");
      spot.setAlpha(1.0f);
      GfMenuObjUtil::CtrlParam ctrl;
      ctrl.unknown08 = 2;
      ctrl.unknown0c = 4;
      ctrl.unknown00 = param.valueF32;
      GfMenuObjUtil::startCtrl(acc.searchChild("IMG_bl_spot"), ctrl, nullptr);
    }
  }
}

void GfMenuObjBlCustomTop::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqStartOpen);
    unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAppearPhase1);
    unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAppearPhase2);
    unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAppearPhase3);
    unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAppearPhase4);
    unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqEndOpen);
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
      u32 call = event.unknown08;
      u32 layer = event.unknown14;
      if (unknown20->unknown40 == nullptr || unknown20->unknown40->unknown0c != call || event.unknown10_u16 != 3) {
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
        unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqStartAddLayer);
        unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAddLayerPhase1);
        unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAddLayerPhase2);
        if ((layer & 0xffff) == 0x24) {
          unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAddLayerPhase3_BlWeapon);
        } else if ((layer & 0xffff) == 0x26) {
          unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAddLayerPhase3_BlOrb);
        }
        unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAddLayerPhase4);
        unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAddLayerPhase5);
        unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqEndAddLayer);
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

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBlCustomTop>(const mm::mtl::Delegate<bool()> *);
