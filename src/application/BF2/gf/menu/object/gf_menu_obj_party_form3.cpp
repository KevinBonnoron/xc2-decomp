#include "gf/menu/object/gf_menu_obj_party_form3.h"

#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_reference_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_party_status.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: menu id; original name unknown.
constexpr u32 unknown001 = 0x24;

// Inferred role: call id of the party form layout; original name unknown.
constexpr u32 CALL_UNKNOWN_98 = 98;

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

void GfMenuObjPartyForm3::initialize() {
  unknown318 = !GfGameCond::isGameCond(0xa70);
  {
    GfMenuTypes::Param layerParam;
    if (getFSLayerParam(unknown20, layerParam)) {
      unknown30 = layerParam.get<OpenParam>().unknown00;
      removeFSLayerParam(unknown20);
    }
  }
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 173 as in the original file: it is the line argument of operator new.
#line 173
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_98, main);
  u32 bg = acc.searchChild("LAY_bg");
// __LINE__ must be 179 as in the original file: it is the line argument of operator new.
#line 179
  BGListener *bgListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) BGListener(this);
  bgListener->addRef();
  ui::UIEventManager::get()->registObjectListener(bg, bgListener);
  if (bgListener != nullptr) {
    bgListener->release();
  }
  u32 driverSelect = acc.searchChild("LAY_dr_select");
// __LINE__ must be 183 as in the original file: it is the line argument of operator new.
#line 183
  DriverSelectListener *driverSelectListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DriverSelectListener(this);
  driverSelectListener->addRef();
  ui::UIEventManager::get()->registObjectListener(driverSelect, driverSelectListener);
  if (driverSelectListener != nullptr) {
    driverSelectListener->release();
  }
  unknown28 = GfMenuDriverList::create();
  unknown34 = 0;
  unknown38 = 0;
  {
    mm::mtl::FixedVector<u16, 16> drivers;
    GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_UNKNOWN_0, 0);
    unknown34 = drivers.size();
    drivers.clear();
    GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_UNKNOWN_1, 0);
    unknown38 = drivers.size();
    GfMenuDriverList::PartySetup setup;
    setup.unknown14 = GfPartySelect::LIST_TYPE_UNKNOWN_2;
    setup.unknown18 = false;
    unknown28->setupFromParty(setup);
  }
  if (unknown28->getSize() == 1) {
    unknown318 = false;
  }
  for (int i = 0; i < 7; i++) {
    unknown48[i] = unknown160();
    unknown48[i]->unknown162(3);
  }
  disableInput(acc.searchChild("LAY_dr_select"));
  GfMenuObject::initialize();
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

void GfMenuObjPartyForm3::setupDriverSelect(ui::UIObjectAcc &acc, GfMenuDriverList *list, u32 first, u32 second, mm::mtl::FixedArray<mm::mtl::IntrusivePtr<GfMenuReferenceNumber>, 7> &numbers) {
  setupDriverLayout(acc, first, second, numbers, 0);
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 7; i++) {
    name.format("LAY_dr@%02d", i + 1);
    ui::UIObjectAcc layer(acc.searchChild(name.c_str()));
    if (i < second + first) {
      name.format("IMG_dr_bustup@%02d", i + 1);
      GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 3, list, i, false);
      name.format("TXT_dr_status_lv_num@%02d", i + 1);
      GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 1, list, i, false);
      name.format("TXT_dr_status_hp_num@%02d", i + 1);
      GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 0, list, i, false);
      name.format("IMG_dr_bl_icon@%02d", i + 1);
      GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 0x1b, list, i, false);
      name.format("IMG_dr_party_no@%02d", i + 1);
      GfMenuReferenceAdapter::create(acc.searchChild(name.c_str()), numbers[i], false);
      if (i == 0) {
        layer.setDispChild(GfGameCond::isGameCond(0xa9d), "IMG_dr_lock@01");
      }
    }
  }
}

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

void GfMenuObjPartyForm3::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc main(unknown20->unknown18);
  switch (event.unknown00) {
  case 1:
    unknown20->unknown80.unknown005();
    if (unknown20->unknown30 == 0) {
      GfMenuObjOperationInfo::add(main.searchChild("LAY_dr_select"), 0, 0, 0);
      unknown20->refreshRemoveAddOperation(main.searchChild("LAY_dr_select"), 0);
      acc.setDispChild(false, "LAY_index");
      GfMenuObjMainMenu2::setSubIndexText(4);
      GfMenuObjMainMenu2::cancelEnableMainMenu(false);
      GfMenuObjOperationInfo::setGuideText(0xb, 0);
    } else {
      GfMenuObjOperationInfo::open(main.searchChild("LAY_dr_select"), 0, 0, 0);
      unknown20->refreshRemoveAddOperation(main.searchChild("LAY_dr_select"), 0);
      unknown20->unknown80.unknown002(&GfMenuObjPartyForm3::seqAnnounceChange);
      GfMenuObjOperationInfo::setGuideText(0xb, 2);
    }
    GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeIn(handle, 1, 0));
    break;
  case 2:
    if (unknown20->unknown44) {
      mm::mtl::FixedVector<u16, 16> drivers;
      for (u32 i = 0; i < 3; i++) {
        drivers.push_back(i < unknown20->unknown34 ? unknown20->unknown28->getContents(i).unknown00 : 0);
      }
      for (u32 i = unknown20->unknown34; i < unknown20->unknown28->getSize(); i++) {
        drivers.push_back(unknown20->unknown28->getContents(i).unknown00);
      }
      GfMenuObjPartyStatus::memberChange(1, drivers[0]);
      GfMenuObjPartyStatus::memberChange(2, drivers[1]);
      GfMenuObjPartyStatus::memberChange(3, drivers[2]);
      GfMenuObjUtil::setupPartyDriver(drivers);
    }
    if (unknown20->unknown30 == 0) {
      GfMenuObjOperationInfo::remove(main.searchChild("LAY_dr_select"), 0, 0, 0);
    } else {
      GfMenuObjOperationInfo::close();
    }
    GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeOut(handle, 2, 0));
    break;
  case 3:
    if (event.unknown08 == 2) {
      acc.setTerm();
    } else if (event.unknown08 == 1) {
      unknown20->unknown80.unknown002(&GfMenuObjPartyForm3::seqWaitOpenEnd);
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    acc.setDisp(false);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjPartyForm3::BGListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(unknown20->unknown18);
  if (event.unknown00 != 1) {
    ui::UIObjectListener::reciveEvent(event, handle);
  }
}
} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjPartyForm3>(const mm::mtl::Delegate<bool()> *);
