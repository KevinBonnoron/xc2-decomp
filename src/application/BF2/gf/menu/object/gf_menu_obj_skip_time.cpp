#include "gf/menu/object/gf_menu_obj_skip_time.h"

#include "gf/field/gf_field_time.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/plugin/ui_object_time_plugin.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjSkipTime::GfMenuObjSkipTime(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(), unknown34() {}

GfMenuObjSkipTime::~GfMenuObjSkipTime() { mm::mtl::safeRelease(unknown28); }

void GfMenuObjSkipTime::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 98 as in the original file: it is the line argument of operator new.
#line 98
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(0x6d, main);
  u32 skipTime = acc.searchChild("LAY_skiptime_main");
// __LINE__ must be 104 as in the original file: it is the line argument of operator new.
#line 104
  TimeChangeListener *timeChangeListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) TimeChangeListener(this);
  timeChangeListener->addRef();
  ui::UIEventManager::get()->registObjectListener(skipTime, timeChangeListener);
  if (timeChangeListener != nullptr) {
    timeChangeListener->release();
  }
  GfMenuObject::initialize();
}

void GfMenuObjSkipTime::finalize() { GfMenuObject::finalize(); }

void GfMenuObjSkipTime::update() { GfMenuObject::update(); }

void GfMenuObjSkipTime::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjSkipTime::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjSkipTime::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjSkipTime::rotHand(ui::UIObjectAcc &acc, u32 value) { acc.setRot(static_cast<f32>(value) * -0.2617994f); }

void GfMenuObjSkipTime::setTime(ui::UIObjectTimePlugin *plugin, GameTime &time) {
  plugin->setHour(time.unknown01_4);
  plugin->setMin(time.unknown00_6);
  plugin->setSec(time.unknown00_0);
}

void GfMenuObjSkipTime::refreshSelect(ui::UIObjectAcc &acc, u32 select) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 2; i++) {
    name.format("IMG_tagbase@%02d", i + 1);
    ui::UIObjectAcc tag(acc.searchChild(name.c_str()));
    const char *color = select == i ? "txt_bl_index" : "txt_dr_index";
    tag.setImageIndex(select == i);
    name.format("TXT_sellect@%02d", i + 1);
    ui::UIObjectAcc text(acc.searchChild(name.c_str()));
    GfMenuObjUtil::setColMulandAdd(text.unknown10, color);
  }
}

ui::UIObjectTimePlugin *GfMenuObjSkipTime::setupTimeChange(ui::UIObjectAcc &acc, GameTime &time, GameTime &afterTime) {
  GfMenuObjUtil::setChildIcon(acc.unknown10, "IMG_buttonicon@01", 0x1d);
  GfMenuObjUtil::setChildIcon(acc.unknown10, "IMG_buttonicon@02", 0x1c);
  refreshSelect(acc, 0);
  ui::UIObjectAcc needle(acc.searchChild("IMG_watchneedle@01"));
  rotHand(needle, time.unknown01_4);
  ui::UIObjectAcc timeText(acc.searchChild("TXT_bftimenum"));
  ui::UIObjectTimePlugin *plugin = ui::UIObjectTimePlugin::create(timeText.unknown10, 3);
  setTime(plugin, time);
  mm::mtl::safeRelease(plugin);
  ui::UIObjectAcc afterNeedle(acc.searchChild("IMG_watchneedle@02"));
  rotHand(afterNeedle, afterTime.unknown01_4);
  ui::UIObjectAcc afterTimeText(acc.searchChild("TXT_aftimenum"));
  plugin = ui::UIObjectTimePlugin::create(afterTimeText.unknown10, 3);
  setTime(plugin, afterTime);
  return plugin;
}

void GfMenuObjSkipTime::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObjOperationInfo::add(acc.searchChild("LAY_skiptime_main"), 0, 0, 0);
    GfMenuObjOperationInfo::setGuideText(0x38, 0);
    GfMenuObjMainMenu2::setSubIndexText(0x17);
    setFadeIn(handle);
    break;
  case 3:
    if (event.unknown08 == 2) {
      GfMenuObjOperationInfo::remove(acc.searchChild("LAY_skiptime_main"), 0, 0, 0);
      acc.setDisp(false);
      acc.setTerm();
      GfMenuObject::returnFSSubLayer(unknown20);
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    setFadeOut(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjSkipTime::TimeChangeListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc menu(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    if (GfFieldTime::get() != nullptr) {
      unknown20->unknown30 = GfFieldTime::get()->getGameTime();
    }
    unknown20->unknown34 = unknown20->unknown30;
    unknown20->unknown34.unknown00_6 = 0;
    unknown20->unknown34.unknown00_0 = 0;
    unknown20->unknown28 = setupTimeChange(acc, unknown20->unknown30, unknown20->unknown34);
    GfMenuObject::setupInputSelection(handle, unknown20->unknown34.unknown01_4, 0x18);
    GfMenuObject::enableInput(handle);
    break;
  case 8:
    if (event.unknown0c == 1) {
      if (GfFieldTime::get() != nullptr) {
        GfFieldTime::get()->setGameTime(unknown20->unknown34);
      }
      unknown164(menu.searchChild("LAY_main"), GfMenuTypes::unknown003_34);
      GfMenuObject::disableInput(handle);
      GfMenuObjMainMenu2::setCloseKeyEnable(false);
      GfMenuObjUtil::playSECommonDecide();
    } else if (event.unknown0c == 2) {
      unknown164(menu.searchChild("LAY_main"), GfMenuTypes::unknown003_34);
      GfMenuObject::disableInput(handle);
      GfMenuObjMainMenu2::setCloseKeyEnable(false);
      GfMenuObjUtil::playSECommonCancel();
    }
    break;
  case 6: {
    u64 param = event.unknown08_u64;
    unknown20->unknown34.unknown01_4 = param;
    ui::UIObjectAcc needle(acc.searchChild("IMG_watchneedle@02"));
    rotHand(needle, unknown20->unknown34.unknown01_4);
    setTime(unknown20->unknown28, unknown20->unknown34);
    if (param >> 32 != 0xffffffff) {
      GfMenuObjUtil::playSE(0x16);
    }
    if (GfFieldTime::get() != nullptr) {
      u32 timeRange = GfFieldTime::get()->getTimeRange(unknown20->unknown34.unknown01_4, unknown20->unknown34.unknown00_6);
      ui::UIObjectAcc zoneIcon(acc.searchChild("IMG_tmzoneicon"));
      zoneIcon.setImageIndex(timeRange);
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
