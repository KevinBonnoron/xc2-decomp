#include "gf/menu/gf_menu_object.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/menu/call/gf_menu_call_manager.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/rtti.h"
#include "ui/animation/ui_animation_manager.h"
#include "ui/ctrl/ui_ctrl_manager.h"
#include "ui/event/ui_event_condition.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_disp_condition.h"
#include "ui/event/ui_event_manager.h"
#include "ui/event/ui_event_number_condition.h"
#include "ui/event/ui_event_pos_condition.h"
#include "ui/input/ui_input_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/plugin/ui_object_disp_plugin.h"
#include "ui/plugin/ui_object_number_plugin.h"
#include "ui/plugin/ui_object_pos_plugin.h"
#include "ui/timer/ui_timer_manager.h"
#include "ui/ui_manager.h"
#include "ui/ui_object.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_base.h"
#include "ui/ui_str.h"
#include "ui/ui_util.h"

namespace gf {

GfMenuObject::GfMenuObject(u32 handle) : unknown18(handle), unknown1c(0) {}

GfMenuObject::~GfMenuObject() { ; }

void GfMenuObject::initialize() { unknown1c |= FLAG_INITIALIZED; }

void GfMenuObject::finalize() {
  unknown18 = 0;
  unknown1c |= FLAG_FINALIZED;
}

void GfMenuObject::update() {}

void GfMenuObject::reloadParam() {}

void GfMenuObject::attachExternalCall(u32 call, u32 object) {
  if (GfMenuCallManager::get() != nullptr) {
    GfMenuCallManager::get()->attachCall(call, object);
  }
}

void GfMenuObject::detachExternalCall(u32 call) {
  if (GfMenuCallManager::get() != nullptr) {
    GfMenuCallManager::get()->detachCall(call);
  }
}

bool GfMenuObject::existAttachedObject(u32 call) {
  if (GfMenuCallManager::get() != nullptr) {
    return GfMenuCallManager::get()->canCall(call);
  }
  return false;
}

u32 GfMenuObject::getAttachedObject(u32 call) {
  if (GfMenuCallManager::get() != nullptr) {
    return GfMenuCallManager::get()->getAttachedObject(call);
  }
  return 0;
}

u16 GfMenuObject::registString(const ui::UIStr &string) {
  if (GfMenuCallManager::get() != nullptr) {
    return GfMenuCallManager::get()->registString(string);
  }
  return 0;
}

void GfMenuObject::releaseString(u16 id) {
  if (GfMenuCallManager::get() != nullptr) {
    GfMenuCallManager::get()->releaseString(id);
  }
}

const ui::UIStr &GfMenuObject::getString(u16 id) { return GfMenuCallManager::get()->getString(id); }

void GfMenuObject::startCallContext(GfMenuCallContext *context, u32 menu, u32 object) {
  if (GfMenuCallManager::get() != nullptr) {
    GfMenuCallManager::get()->startCallContext(context, menu, object);
  }
}

void GfMenuObject::nextCallContext(GfMenuCallContext *context, u32 menu) {
  if (GfMenuCallManager::get() != nullptr) {
    GfMenuCallManager::get()->nextCallContext(context, menu);
  }
}

void GfMenuObject::addResultCallContext(u32 handle, u32 type, int value) {
  ui::EventData event;
  event.unknown00 = 8;
  event.unknown08 = type;
  event.unknown0c = value;
  ui::UIManager::get()->requestGameEvent(handle, event);
}

void GfMenuObject::termCallContext(u32 handle) {
  ui::EventData event;
  event.unknown00 = 9;
  ui::UIManager::get()->requestGameEvent(handle, event);
}

void GfMenuObject::setCallContextEventHandler(GfMenuCallContext *context, u32 handler) {
  if (GfMenuCallManager::get() != nullptr) {
    GfMenuCallManager::get()->setCallContextEventHandler(context, handler);
  }
}

void GfMenuObject::setupInputSelection(u32 handle, int index, u32 size) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(handle);
  if (input != 0) {
    ui::UIInputManager::get()->setupInputSelection(input, index, size);
  }
}

void GfMenuObject::resetInputSelection(u32 handle) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(handle);
  if (input != 0) {
    ui::UIInputManager::get()->resetInputSelection(input);
  }
}

void GfMenuObject::setupInputSelectionFromList(u32 handle, const ui::UIListInfoBase &list) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(handle);
  if (input != 0) {
    ui::UIInputManager::get()->setupInputSelection(input, list.getIndex(false), list.getSize());
    if (list.getColumnSize() == 1) {
      ui::UIInputManager::get()->setPadPageSize(input, list.getPageRowSize());
    }
  }
}

void GfMenuObject::setInputSelectionChecker(u32 handle, ui::IUIInputSelectionChecker *checker) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(handle);
  if (input != 0) {
    ui::UIInputManager::get()->setSelectionChecker(input, checker);
  }
}

void GfMenuObject::setupPadLineSelection(u32 handle, u32 line) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(handle);
  if (input != 0) {
    ui::UIInputManager::get()->setPadLineSelection(input, line);
  }
}

void GfMenuObject::setPadLineSelectionLoop(u32 handle, bool loop) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(handle);
  if (input != 0) {
    ui::UIInputManager::get()->setPadLineSelectionLoop(input, loop);
  }
}

void GfMenuObject::setPadLoopSetting(u32 handle, bool loop) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(handle);
  if (input != 0) {
    ui::UIInputManager::get()->setPadLoopSetting(input, loop);
  }
}

void GfMenuObject::setupPointerSelection(u32 handle, const ui::UIInputPointer::SelectionSetup &setup) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(handle);
  if (input != 0) {
    ui::UIInputManager::get()->setupPointerSelection(input, setup);
  }
}

void GfMenuObject::changePointerPos(u32 handle, const mm::Pnt<s16> &pos) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(handle);
  if (input != 0) {
    ui::UIInputManager::get()->changePointerPos(input, pos);
  }
}

void GfMenuObject::changePointerPosFromObject(u32 handle, u32 object) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(handle);
  if (input != 0) {
    ui::UIObjectAcc acc(object);
    if (acc.isValid()) {
      mm::Pnt<s16> pos;
      acc.getPosCenter(pos);
      ui::UIInputManager::get()->changePointerPos(input, pos);
    }
  }
}

void GfMenuObject::changePointerRegionScale(u32 handle, f32 scale) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(handle);
  if (input != 0) {
    ui::UIInputManager::get()->changeRegionScale(input, scale);
  }
}

void GfMenuObject::changePointerRegionRect(u32 handle, const mm::Rect<s16> &rect) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(handle);
  if (input != 0) {
    ui::UIInputManager::get()->changeRegionRect(input, rect);
  }
}

void GfMenuObject::migrateInput(u32 handle, u32 target) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(handle);
  if (input != 0) {
    ui::UIInputManager::get()->migrateInput(input, target);
  }
}

void GfMenuObject::enableInput(u32 handle) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(handle);
  if (input != 0) {
    ui::UIInputManager::get()->enableInput(input);
  }
}

void GfMenuObject::disableInput(u32 handle) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(handle);
  if (input != 0) {
    ui::UIInputManager::get()->disableInput(input);
  }
}

bool GfMenuObject::setFSInputObject(u32 layer, u32 object) { return GfMenuFullScreen::setInputObject(layer, object); }

u32 GfMenuObject::getFSInputObject(u32 layer) { return GfMenuFullScreen::getInputObject(layer); }

void GfMenuObject::enableFSInput(u32 layer) { GfMenuFullScreen::enableInput(layer); }

void GfMenuObject::disableFSInput() { GfMenuFullScreen::disableInput(); }

bool GfMenuObject::isActiveFSInput(u32 layer) { return GfMenuFullScreen::isActiveInput(layer); }

void GfMenuObject::setInputActionEnable(u32 handle, u32 action, bool enable) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(handle);
  if (input != 0) {
    ui::UIInputManager::get()->setInputActionEnable(input, action, enable);
  }
}

void GfMenuObject::setInputSelectEnable(u32 handle, bool enable) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(handle);
  if (input != 0) {
    ui::UIInputManager::get()->setInputSelectEnable(input, enable);
  }
}

void GfMenuObject::sendEvent(u32 handle, const ui::EventData &event, f32 delay) {
  if (handle != 0) {
    ui::UIManager::get()->requestObjectEvent(handle, event, delay);
  }
}

void GfMenuObject::sendOpenEvent(u32 handle, int type, f32 delay) {
  if (handle != 0) {
    ui::EventData event;
    event.unknown08 = type;
    event.unknown0c = 0;
    event.unknown00 = 0x21;
    ui::UIManager::get()->requestObjectEvent(handle, event, delay);
  }
}

void GfMenuObject::sendCloseEvent(u32 handle, int type, f32 delay) {
  if (handle != 0) {
    ui::EventData event;
    event.unknown08 = type;
    event.unknown0c = 0;
    event.unknown00 = 0x22;
    ui::UIManager::get()->requestObjectEvent(handle, event, delay);
  }
}

void GfMenuObject::sendEventToChild(u32 handle, const ui::EventData &event, const char *name, f32 delay) {
  ui::UIObjectAcc acc(handle, name);
  if (acc.isValid() && acc.unknown10 != 0) {
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, delay);
  }
}

void GfMenuObject::sendEventToParent(u32 handle, const ui::EventData &event, const char *name, f32 delay) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    u32 sibiling = acc.searchSibiling(name);
    if (sibiling != 0) {
      ui::UIManager::get()->requestObjectEvent(sibiling, event, delay);
    }
  }
}

void GfMenuObject::sendEventToParent(u32 handle, const ui::EventData &event, f32 delay) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    u32 parent = acc.getParentHandle();
    if (parent != 0) {
      ui::UIManager::get()->requestObjectEvent(parent, event, delay);
    }
  }
}

static bool hasListener(u32 handle) { return handle != 0 && ui::UIUtil::getObject(handle)->unknown98.test(ui::UI_OBJECT_FLAG_LISTENER); }

template <typename T> static T *getPlugin(u32 handle) {
  ui::UIObject *object = ui::UIUtil::getObject(handle);
  if (object == nullptr || object->unknowne0 == nullptr) {
    return nullptr;
  }
  return mm::mtl::dynamicCast<T>(object->unknowne0);
}

static void addCondition(u32 handle, ui::UIEventCondition *condition) {
  ui::UIEventManager::get()->addCondition(handle, condition);
  if (condition != nullptr) {
    condition->release();
  }
}

void GfMenuObject::addNumberEventCondition(u32 handle, const char *name, u32 event, u32 value, f32 time) {
  if (hasListener(handle)) {
    u32 target = handle;
    if (name != nullptr) {
      target = ui::UIObjectAcc(handle).searchChild(name);
    }
    ui::UIObjectNumberPlugin *plugin = getPlugin<ui::UIObjectNumberPlugin>(target);
    if (plugin != nullptr) {
      addCondition(handle, ui::UIEventNumberCondition::create(event, value, plugin, time));
    }
  }
}

void GfMenuObject::addNumberEventCondition(u32 handle, const char *name, u32 event, u32 value) {
  if (hasListener(handle)) {
    u32 target = handle;
    if (name != nullptr) {
      target = ui::UIObjectAcc(handle).searchChild(name);
    }
    ui::UIObjectNumberPlugin *plugin = getPlugin<ui::UIObjectNumberPlugin>(target);
    if (plugin != nullptr) {
      addCondition(handle, ui::UIEventNumberCondition::create(event, value, plugin));
    }
  }
}

void GfMenuObject::addDispEventCondition(u32 handle, const char *name, u32 event, u32 value, bool duplicated) {
  if (hasListener(handle)) {
    u32 target = handle;
    if (name != nullptr) {
      if (!duplicated) {
        target = ui::UIObjectAcc(handle).searchChild(name);
      } else {
        target = ui::UIObjectAcc(handle).searchDuplicatedChild(name, value);
      }
    }
    ui::UIObjectDispPlugin *plugin = getPlugin<ui::UIObjectDispPlugin>(target);
    if (plugin != nullptr) {
      addCondition(handle, ui::UIEventDispCondition::create(event, value, plugin));
    }
  }
}

void GfMenuObject::addPosEventCondition(u32 handle, const char *name, u32 event, u32 value) {
  if (hasListener(handle)) {
    u32 target = handle;
    if (name != nullptr) {
      target = ui::UIObjectAcc(handle).searchChild(name);
    }
    ui::UIObjectPosPlugin *plugin = getPlugin<ui::UIObjectPosPlugin>(target);
    if (plugin != nullptr) {
      addCondition(handle, ui::UIEventPosCondition::create(event, value, plugin));
    }
  }
}

void GfMenuObject::hookCtrlEvent(u32 handle, int ctrl) { ui::UICtrlManager::get()->changeEventHandleObject(ctrl, handle); }

void GfMenuObject::hookAnimationEvent(u32 handle, u32 object) { ui::UIAnimationManager::get()->changeEventHandleObject(object, handle); }

void GfMenuObject::changeFSLayer(u32 handle, u16 layer, bool keep) {
  ui::EventData event;
  event.unknown00 = 1;
  event.unknown08 = layer;
  event.unknown0c = 0;
  event.unknown10 = keep;
  event.unknown14 = 0;
  ui::UIManager::get()->requestGameEvent(handle, event);
}

void GfMenuObject::returnFSLayer(u32 handle) {
  ui::EventData event;
  event.unknown00 = 3;
  ui::UIManager::get()->requestGameEvent(handle, event);
}

void GfMenuObject::closeFSLayer(u32 handle, bool fade, bool keep) {
  ui::EventData event;
  event.unknown00 = 7;
  event.unknown08 = fade;
  event.unknown0c = keep;
  ui::UIManager::get()->requestGameEvent(handle, event);
}

u32 GfMenuObject::getMenuLayerID(u32 id) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_FSMENU);
  if (bdat == nullptr || !GfMenuBdat::isValidBdatID(bdat, id)) {
    return 1;
  }
  return Bdat::getVal(bdat, "layer_id", id).valueU16;
}

u32 GfMenuObject::getMenuIconID(u32 id) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_FSMENU);
  if (bdat == nullptr || !GfMenuBdat::isValidBdatID(bdat, id)) {
    return 0;
  }
  return Bdat::getVal(bdat, "icon", id).valueU16;
}

bool GfMenuObject::getMenuText(u32 id, u8 *&bdat, u32 &textId) {
  u8 *menu = GfDataBdat::getFP(BDAT_MNU_FSMENU);
  if (menu == nullptr || !GfMenuBdat::isValidBdatID(menu, id)) {
    return false;
  }
  textId = Bdat::getVal(menu, "text", id).valueU16;
  bdat = GfDataBdat::getFP(BDAT_MENU_SUB_CONTENTS_MS);
  return true;
}

bool GfMenuObject::getMenuDesc(u32 id, u8 *&bdat, u32 &textId) {
  u8 *menu = GfDataBdat::getFP(BDAT_MNU_FSMENU);
  if (menu == nullptr || !GfMenuBdat::isValidBdatID(menu, id)) {
    return false;
  }
  textId = GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_MENU_DESCRIPTION, Bdat::getVal(menu, "desc", id).valueU16);
  bdat = GfDataBdat::getFP(BDAT_MENU_SUB_CONTENTS_MS);
  return true;
}

void GfMenuObject::registFSLayerObject(u32 layer, u32 object) { GfMenuFullScreen::registLayerObject(layer, object); }

void GfMenuObject::setFSShadowLayer(u32 layer, bool shadow) { GfMenuFullScreen::setShadowLayer(layer, shadow); }

void GfMenuObject::registFSLayerParam(u32 layer, const GfMenuTypes::Param &param) { GfMenuFullScreen::registLayerParam(layer, param); }

bool GfMenuObject::getFSLayerParam(u32 layer, GfMenuTypes::Param &param) { return GfMenuFullScreen::getLayerParam(layer, param); }

void GfMenuObject::removeFSLayerParam(u32 layer) { GfMenuFullScreen::removeLayerParam(layer); }

void GfMenuObject::enableFSSwitching() { GfMenuFullScreen::enableSwitching(); }

void GfMenuObject::disableFSSwitching() { GfMenuFullScreen::disableSwitching(); }

void GfMenuObject::overrideFadeOutTime(u32 frame) { GfMenuFullScreen::overrideFadeOutFrame(frame); }

void GfMenuObject::clearLayerStatck(u32 handle, u16 group) {
  ui::EventData event;
  event.unknown00 = 0xc;
  event.unknown08 = group;
  event.unknown0c = 0;
  ui::UIManager::get()->requestGameEvent(handle, event);
}

void GfMenuObject::registTimer(u32 handle, u16 id, f32 time, bool repeat) { ui::UIManager::get()->registObjectTimer(handle, id, ui::UIUtil::timeSecToUITime(time), repeat); }

void GfMenuObject::releaseTimer(u32 handle) { ui::UIManager::get()->releaseObjectTimer(handle); }

void GfMenuObject::setTimerSpeedFactor(u32 handle, f32 speedFactor) {
  u32 timer = ui::UITimerManager::get()->getTimerHandle(handle);
  if (timer != 0) {
    ui::UITimerManager::get()->setTimerSpeedFactor(timer, speedFactor);
  }
}

void GfMenuObject::setText(u32 handle, u16 id) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    const ui::UIStr &string = getString(id);
    if (string.isValid()) {
      acc.setText(string);
    }
  }
  releaseString(id);
}

void GfMenuObject::setTextWithStyle(u32 handle, u16 id) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    const ui::UIStr &string = getString(id);
    if (string.isValid()) {
      acc.setText(string);
    }
  }
  releaseString(id);
}

void GfMenuObject::eventHudSceneChange(u32 scene) {}

} // namespace gf
