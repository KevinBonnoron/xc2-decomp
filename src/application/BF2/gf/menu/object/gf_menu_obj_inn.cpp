#include "gf/menu/object/gf_menu_obj_inn.h"

#include "gf/data/gf_data_driver.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/object/gf_menu_obj_common_detail.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/ctrl/ui_ctrl_slide_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/plugin/ui_object_number_plugin.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id of the inn layouts; original name unknown.
constexpr u32 CALL_UNKNOWN_86 = 86;

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

bool GfMenuObjInn::isEnableLevelUp() {
  mm::mtl::FixedVector<u16, 16> drivers;
  GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_UNKNOWN_2, 0);
  for (u32 i = 0; i < drivers.size(); i++) {
    if (GfDataDriver::isEnableLevelUp(drivers[i])) {
      return true;
    }
  }
  return false;
}

void GfMenuObjInn::initialize() {
  ui::UIObjectAcc acc(unknown18);
  unknown28 = GfMenuCallContext::create();
  unknown30 = GfMenuCallContext::create();
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 151 as in the original file: it is the line argument of operator new.
#line 151
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_86, main);
  u32 driverList = acc.searchChild("LAY_dr_list");
// __LINE__ must be 156 as in the original file: it is the line argument of operator new.
#line 156
  DriverListener *driverListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DriverListener(this);
  driverListener->addRef();
  ui::UIEventManager::get()->registObjectListener(driverList, driverListener);
  if (driverListener != nullptr) {
    driverListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_86, driverList);
  u32 modeSelect = acc.searchChild("LAY_mode_select");
// __LINE__ must be 161 as in the original file: it is the line argument of operator new.
#line 161
  ModeListener *modeListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ModeListener(this);
  modeListener->addRef();
  ui::UIEventManager::get()->registObjectListener(modeSelect, modeListener);
  if (modeListener != nullptr) {
    modeListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_86, modeSelect);
  u32 driverSelect = acc.searchChild("LAY_dr_select");
// __LINE__ must be 166 as in the original file: it is the line argument of operator new.
#line 166
  ManualListener *manualListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ManualListener(this);
  manualListener->addRef();
  ui::UIEventManager::get()->registObjectListener(driverSelect, manualListener);
  if (manualListener != nullptr) {
    manualListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_86, driverSelect);
  u32 lvSelect = acc.searchChild("LAY_lv_select");
// __LINE__ must be 171 as in the original file: it is the line argument of operator new.
#line 171
  LvSelectListener *lvSelectListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LvSelectListener(this);
  lvSelectListener->addRef();
  ui::UIEventManager::get()->registObjectListener(lvSelect, lvSelectListener);
  if (lvSelectListener != nullptr) {
    lvSelectListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_86, lvSelect);
  u32 lvUp = acc.searchChild("LAY_lv_up");
// __LINE__ must be 176 as in the original file: it is the line argument of operator new.
#line 176
  LvUpListener *lvUpListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LvUpListener(this);
  lvUpListener->addRef();
  ui::UIEventManager::get()->registObjectListener(lvUp, lvUpListener);
  if (lvUpListener != nullptr) {
    lvUpListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_86, lvUp);
  GfMenuObject::initialize();
}

void GfMenuObjInn::finalize() { GfMenuObject::finalize(); }

void GfMenuObjInn::update() {
  unknown0a0.unknown003();
  GfMenuObject::update();
}

void GfMenuObjInn::setupDriverAdapter(ui::UIObjectAcc &acc, const GfMenuDriverList *list) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 5; i++) {
    name.format("TXT_dr_name@%02d", i + 1);
    GfMenuCharDataAdapter *adapter = GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 2, list, i, false);
    name.format("LAY_dr_prop@%02d", i + 1);
    adapter->unknown24 = acc.searchChild(name.c_str());
    name.format("TXT_dr_lv@%02d", i + 1);
    GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 1, list, i, true);
    name.format("IMG_dr_bustup@%02d", i + 1);
    GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 0x1d, list, i, false);
    name.format("TXT_dr_hpmax@%02d", i + 1);
    GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 0, list, i, true);
    name.format("TXT_dr_exp@%02d", i + 1);
    GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 0x13, list, i, true);
    name.format("TXT_dr_lv_up@%02d", i + 1);
    GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 0x18, list, i, true);
  }
}

void GfMenuObjInn::setupLvSelectAdapter(ui::UIObjectAcc &acc, ui::UISelectObjList *list) {
  mm::mtl::FixStr<32> name;
  name = "LAY_lv_select_num@01";
  GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
  name = "LAY_lv_select_num@02";
  GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
  name = "LAY_lv_select_num@03";
  GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
  name = "TXT_lv_select_info_num@01";
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild(name.c_str()), 0x23, 0, true);
  name = "TXT_lv_select_info_num@02";
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild(name.c_str()), 0x15, 0, true);
  name = "TXT_lv_select_info_num@03";
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild(name.c_str()), 0x13, 0, true);
}

void GfMenuObjInn::detailOpen(GfMenuObjInn *object, ui::UIObjectAcc &acc, const char *layout, u32 driver) {
  object->unknown30->reset();
  GfMenuObjCommonDetail::OpenParam param;
  param.unknown00.push_back(0x10c);
  param.unknown1c = 0;
  param.unknown28 = true;
  param.unknown30 = 0;
  acc.getLayoutRect(layout, param.unknown20);
  GfMenuReference::setReferenceDriverID(0, driver);
  GfMenuObjCommonDetail::open(object->unknown30, param);
}

void GfMenuObjInn::setupLvUpAdapter(ui::UIObjectAcc &acc) {
  mm::mtl::FixStr<32> name;
  name.format("IMG_lv_up_bustup");
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild(name.c_str()), 0x1c, 0, true);
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

void GfMenuObjInn::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_33:
    break;
  case GfMenuTypes::unknown003_34:
    unknown20->unknown0a0.unknown005();
    unknown20->unknown0a0.unknown002(&GfMenuObjInn::seqFadeOut);
    unknown20->unknown0a0.unknown002(&GfMenuObjInn::seqFadeOutWait);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjInn::ManualListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(unknown20->unknown18);
  switch (event.unknown00) {
  case 1: {
    GfMenuObjUtil::setChildDisp(handle, "IMG_dr_cursor", true);
    GfMenuObjUtil::CursorParam param;
    param.unknown00 = acc.getParentHandle();
    param.unknown04 = handle;
    param.unknown08 = "LAY_dr@%02d";
    param.unknown1a = 1;
    param.unknown20.unknown18 = 5;
    unknown20->unknown40 = GfMenuObjUtil::createCursor(param);
    unknown20->unknown40->open(0);
    acc.setDisp(false);
    break;
  }
  case 6: {
    u32 index = event.unknown08;
    unknown20->unknown48->setIndex(index);
    u32 selected = unknown20->unknown48->getIndex(true);
    unknown20->unknown40->inputChange(selected);
    break;
  }
  case 8:
    switch (event.unknown0c) {
    case 1: {
      GfMenuDriverList *drivers = unknown20->unknown48;
      if (!GfDataDriver::isEnableLevelUp(drivers->getContents(drivers->getIndex(false)).unknown00)) {
        break;
      }
      if (unknown20->unknown88 != 2) {
        unknown20->unknown28->reset();
        GfMenuObjCommonText::open(unknown20->unknown28, 0xf, 0);
        GfMenuObject::setCallContextEventHandler(unknown20->unknown28, handle);
        GfMenuObject::disableInput(handle);
        break;
      }
      unknown164(handle, GfMenuTypes::unknown003_34);
      unknown163(owner.searchChild("LAY_lv_select"), GfMenuTypes::unknown003_33, 0);
      u32 index = unknown20->unknown48->getIndex(true);
      unknown163(owner.searchChild("LAY_dr_list"), 0x101, index);
      break;
    }
    case 2:
      unknown164(handle, GfMenuTypes::unknown003_34);
      unknown163(owner.searchChild("LAY_mode_select"), GfMenuTypes::unknown003_33, 0);
      break;
    }
    break;
  case GfMenuTypes::unknown003_33:
    GfMenuObject::setupInputSelectionFromList(handle, *unknown20->unknown48);
    GfMenuObject::enableInput(handle);
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    GfMenuObject::disableInput(handle);
    acc.setDisp(false);
    break;
  case 0x41:
    if (unknown20->unknown28 == nullptr) {
      break;
    }
    if (unknown20->unknown28->unknown0c == event.unknown08) {
      if (event.unknown10_u16 == 0) {
        unknown164(handle, GfMenuTypes::unknown003_34);
        unknown163(owner.searchChild("LAY_dr_list"), 0x103, 0);
        GfMenuDriverList *drivers = unknown20->unknown48;
        unknown20->unknown8c = drivers->getContents(drivers->getIndex(false)).unknown00;
        u32 maxLevel;
        GfDataDriver::getEnableLevel(unknown20->unknown90, maxLevel, unknown20->unknown8c);
        GfMenuReference::setReferenceDriverID(0, unknown20->unknown8c);
        unknown163(owner.searchChild("LAY_lv_up"), GfMenuTypes::unknown003_33, 0);
      } else {
        GfMenuObject::enableInput(handle);
      }
    }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjInn::LvSelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(unknown20->unknown18);
  switch (event.unknown00) {
  case 1: {
    ui::UISelectObjList::CreateParam createParam;
    createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
    unknown20->unknown58 = ui::UISelectObjList::create(createParam);
    setupLvSelectAdapter(acc, unknown20->unknown58);
    break;
  }
  case 6: {
    int index = event.unknown08;
    unknown20->unknown58->setIndex(index);
    GfMenuReference::setDriverVirtualLevel(unknown20->unknown58->getIndex(true) + GfDataDriver::getLevel(unknown20->unknown48->getContents(unknown20->unknown48->getIndex(false)).unknown00));
    ui::UIObjectAcc(acc.searchChild("IMG_lv_select_arrow_prev")).setDisp(index > 0);
    ui::UIObjectAcc(acc.searchChild("IMG_lv_select_arrow_next")).setDisp(index < static_cast<int>(unknown20->unknown58->getSize() - 1));
    break;
  }
  case 8:
    switch (event.unknown0c) {
    case 1: {
      unknown164(handle, GfMenuTypes::unknown003_34);
      unknown20->unknown8c = unknown20->unknown48->getContents(unknown20->unknown48->getIndex(false)).unknown00;
      unknown20->unknown90 = GfDataDriver::getLevel(unknown20->unknown8c) + unknown20->unknown58->getIndex(true);
      unknown163(owner.searchChild("LAY_lv_up"), GfMenuTypes::unknown003_33, 0);
      unknown163(owner.searchChild("LAY_dr_list"), GfMenuTypes::unknown003_259, 0);
      break;
    }
    case 2:
      unknown164(handle, GfMenuTypes::unknown003_34);
      unknown163(owner.searchChild("LAY_dr_list"), GfMenuTypes::unknown003_258, 0);
      unknown163(owner.searchChild("LAY_dr_select"), GfMenuTypes::unknown003_33, 0);
      break;
    }
    break;
  case GfMenuTypes::unknown003_33: {
    u32 driver = unknown20->unknown48->getContents(unknown20->unknown48->getIndex(false)).unknown00;
    u32 level = GfDataDriver::getLevel(driver);
    u32 enableLevel;
    u32 maxLevel;
    GfDataDriver::getEnableLevel(enableLevel, maxLevel, driver);
    if (enableLevel < level) {
      enableLevel = level;
    }
    for (u32 i = 0; i < unknown20->unknown58->getSize(); i++) {
      ui::UIObjectAcc object(unknown20->unknown58->getContents(i));
      object.setTerm();
    }
    unknown20->unknown58->clear();
    ui::UIListInfoBase::SetupParam setup;
    setup.unknown08 = enableLevel - level + 1;
    unknown20->unknown58->setup(getAllocator(ALLOCATOR_UNKNOWN_0), setup);
    {
      ui::UIObjectAcc numbers(acc.searchChild("LAY_lv_select_num"));
      for (u32 i = 0; i < enableLevel - level + 1; i++) {
        ui::UIObjectAcc number(numbers.duplicateChild("LAY_lv_select_num@01"));
        number.setDisp(true);
        unknown20->unknown58->addObject(number.unknown10);
        ui::UIObjectNumberPlugin *plugin = ui::UIObjectNumberPlugin::create(number.searchChild("TXT_lv_select_num@01"));
        if (plugin != nullptr) {
          plugin->setNumber(level + i);
          plugin->release();
        }
      }
      ui::UIObjectAcc center(acc.searchChild("LAY_lv_select_num@02"));
      if (unknown20->unknown50 != nullptr) {
        unknown20->unknown50->release();
        unknown20->unknown50 = nullptr;
      }
      ui::UICtrlSlideSelect::SlideSetting setting;
      setting.unknown08 = 3;
      setting.unknown00 = 0.4f;
      center.getPosCenter(setting.unknown0c);
      setting.unknown10.x = 0x70;
      setting.unknown10.y = 0;
      unknown20->unknown50 = ui::UICtrlSlideSelect::create(handle, setting, unknown20->unknown58);
    }
    detailOpen(unknown20, acc, "lv_select_dr_detail", unknown20->unknown48->getContents(unknown20->unknown48->getIndex(false)).unknown00);
    GfMenuObject::setupInputSelectionFromList(handle, *unknown20->unknown58);
    GfMenuObject::enableInput(handle);
    setFadeIn(handle);
    break;
  }
  case GfMenuTypes::unknown003_34:
    GfMenuObjCommonDetail::close(unknown20->unknown30);
    GfMenuObject::disableInput(handle);
    setFadeOut(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjInn::LvUpListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(unknown20->unknown18);
  switch (event.unknown00) {
  case 1:
    setupLvUpAdapter(acc);
    break;
  case 3:
    switch (event.unknown08) {
    case 1: {
      u32 label = acc.searchChild("LAY_lv_up_label");
      ui::UIObjectAcc labelAcc(label);
      labelAcc.setDisp(false);
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x800;
      param.unknown0c = 1;
      param.unknown04 = 3;
      param.unknown00 = 0.25f;
      param.unknown14 = 4;
      unknown20->unknown94 = GfMenuObjUtil::startCtrl(label, param, nullptr);
      GfMenuObject::hookCtrlEvent(acc.unknown10, unknown20->unknown94);
      break;
    }
    case 3: {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0;
      param.unknown04 = 4;
      param.unknown00 = 2.0f;
      int ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
      GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
      break;
    }
    case 4: {
      u32 label = acc.searchChild("LAY_lv_up_label");
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x4000;
      param.unknown0c = 1;
      param.unknown04 = 5;
      param.unknown00 = 0.5f;
      param.unknown14 = 8;
      param.unknown18 = unknown20->unknown94;
      GfMenuObjUtil::startCtrl(label, param, nullptr);
      GfMenuObject::hookCtrlEvent(acc.unknown10, unknown20->unknown94);
      break;
    }
    case 5:
      GfGameUtil::execLevelUp(unknown20->unknown8c, unknown20->unknown90);
      unknown20->unknown98 = true;
      unknown164(handle, GfMenuTypes::unknown003_34);
      if (unknown20->unknown88 != 0) {
        unknown163(owner.searchChild("LAY_dr_list"), GfMenuTypes::unknown003_258, 0);
        unknown163(owner.searchChild("LAY_dr_select"), GfMenuTypes::unknown003_33, 0);
      } else {
        unknown163(owner.searchChild("LAY_mode_select"), GfMenuTypes::unknown003_260, 0);
      }
      break;
    }
    break;
  case GfMenuTypes::unknown003_33:
    detailOpen(unknown20, acc, "lv_up_detail", unknown20->unknown8c);
    GfMenuReference::setDriverVirtualLevel(unknown20->unknown90);
    GfMenuObject::enableInput(handle);
    setFadeIn(handle);
    GfMenuObjUtil::setChildDisp(handle, "LAY_lv_up_label", false);
    break;
  case GfMenuTypes::unknown003_34:
    GfMenuObjCommonDetail::close(unknown20->unknown30);
    GfMenuObject::disableInput(handle);
    setFadeOut(handle);
    break;
  case 0x41:
    if (unknown20->unknown28 != nullptr && unknown20->unknown28->unknown0c == event.unknown08) {
      unknown164(owner.searchChild("LAY_dr_list"), GfMenuTypes::unknown003_34);
    }
    break;
  case 0x105:
    unknown20->unknown28->reset();
    GfMenuObjCommonText::open(unknown20->unknown28, 0x10, 0);
    GfMenuObject::setCallContextEventHandler(unknown20->unknown28, handle);
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjInn>(const mm::mtl::Delegate<bool()> *);
