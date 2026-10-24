#include "ui/ui_manager.h"

#include "bdat.h"
#include "mm_mtl/fixstr.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/factory/ui_obj_factory.h"
#include "ui/plugin/ui_object_number_plugin.h"
#include "ui/text/ui_text_manager.h"
#include "ui/timer/ui_timer_manager.h"
#include "ui/ui_util.h"

namespace ui {

void UIManager::terminate() {
  for (int i = 0; i < GROUP_MAX; i++) {
    unknown08[i].terminateObjectAll(true);
  }
}

bool UIManager::isLayerCreated(u32 layer) {
  for (LayerInfo *it = unknown348.begin(); it != unknown348.end(); ++it) {
    if (it->unknown02 == layer) {
      return true;
    }
  }
  return false;
}

u32 UIManager::searchObject(const char *name, u16 group) {
  if (name != nullptr && group < GROUP_MAX && *name != '\0') {
    return unknown08[group].searchObject(name);
  }
  return 0;
}

bool UIManager::preloadLayer(u32 layer) {
  u8 *bdat = UIUtil::getBdatFP(UI_BDAT_LAYER);
  if (bdat == nullptr) {
    return false;
  }

  Bdat::getVal(bdat, "group", layer);
  int memberSize = Bdat::getMemberSize(bdat);
  int sheetCount = (memberSize - 1) / 2;
  mm::mtl::FixStr<32> member;
  if (memberSize >= 3) {
    for (u32 i = 0; i < static_cast<u32>(sheetCount); i++) {
      member.format("sheet%02d", i + 1);
      if (Bdat::getMember(bdat, member.c_str()) != nullptr) {
        const char *sheet = Bdat::getVal(bdat, member.c_str(), layer).valueString;
        if (sheet != nullptr && *sheet != '\0') {
          UIObjFactory::get()->registPreloadResource(1, sheet);
        }
      }
    }
  }
  return true;
}

void UIManager::terminateObject(const char *name, u8 group, bool isImmediate) {
  if (name != nullptr && group < GROUP_MAX && *name != '\0') {
    unknown08[group].terminateObject(name, isImmediate);
  }
}

void UIManager::requestObjectEvent(u32 handle, const EventData &event, f32 delay) {
  if (UIUtil::isValid(handle)) {
    UIEventManager::EventInfo info;
    info.unknown00 = handle;
    info.unknown08 = event;
    info.unknown04 = delay;
    UIEventManager::get()->pushObjectEvent(info);
  }
}

void UIManager::requestGameEvent(u32 handle, const EventData &event) {
  if (UIUtil::isValid(handle)) {
    UIEventManager::EventInfo info;
    info.unknown00 = handle;
    info.unknown08 = event;
    UIEventManager::get()->pushGameEvent(info);
  }
}

void UIManager::setGameEventLisenter(UIGameListener *listener) { UIEventManager::get()->setGameListener(listener); }

void UIManager::setUpdateCallback(UIUpdateCallback *callback) { m_updateCallback = callback; }

void UIManager::registObjectTimer(u32 handle, u16 id, u64 time, bool repeat) { UITimerManager::get()->registTimer(handle, id, time, repeat); }

void UIManager::releaseObjectTimer(u32 handle) {
  u32 timer = UITimerManager::get()->getTimerHandle(handle);
  if (timer != 0) {
    UITimerManager::get()->releaseTimer(timer);
  }
}

void UIManager::setDisp(u16 group, bool disp) {
  if (group < GROUP_MAX) {
    unknown08[group].disp(disp);
  }
}

bool UIManager::isLoading() const { return UIObjFactory::get()->isLoading(); }

void UIManager::reloadText() {
  UIObjectNumberPlugin::refreshMoneySeparetor();
  UITextManager::get()->reloadAll();
  for (int i = 0; i < GROUP_MAX; i++) {
    unknown08[i].reloadText();
  }
}

u32 UIManager::getLoadedResourceSize() {
  u32 size = 0;
  for (int i = 0; i < GROUP_MAX; i++) {
    size += unknown08[i].getLoadedResourceSize();
  }
  return size;
}

bool UIManager::isTerminated() const {
  for (int i = 0; i < GROUP_MAX; i++) {
    if (unknown08[i].hasObject()) {
      return false;
    }
  }
  return true;
}

} // namespace ui
