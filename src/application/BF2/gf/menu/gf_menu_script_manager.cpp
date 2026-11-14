// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/menu/gf_menu_script_manager.cpp.
#include "gf/menu/gf_menu_script_manager.h"

#include <string.h>

#include "bdat.h"
#include "gf/gf_allocator.h"
#include "gf/script/gf_script_manager.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuScriptManager::GfMenuScriptManager(const GfSetupParam &param) : unknown08(false), unknown4118(nullptr) { initialize(param); }

void GfMenuScriptManager::initialize(const GfSetupParam &) {
  for (u32 i = 0; i < 32; i++) {
    unknown4018[i].unknown00 = i + 4;
    unknown4018[i].unknown04 = false;
  }

  // __LINE__ must be 234 as in the original file: it is the line argument of operator new.
#line 234
  unknown4118 = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ScriptListener();
  unknown4118->addRef();
  unknown08 = true;
}

GfMenuScriptManager::~GfMenuScriptManager() {}

void GfMenuScriptManager::build(const GfSetupParam &param) {
  // __LINE__ must be 38 as in the original file: it is the line argument of operator new.
#line 38
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfMenuScriptManager(param);
}

void GfMenuScriptManager::destroy() {
  GfMenuScriptManager *manager = get();
  manager->finalize();
  delete manager;
}

void GfMenuScriptManager::finalize() {
  mm::mtl::safeRelease(unknown4118);
  unknown08 = false;
}

bool GfMenuScriptManager::isInitialized() {
  if (get() != nullptr) {
    return get()->unknown08;
  }

  return false;
}

void GfMenuScriptManager::postUpdate(const fw::UpdateInfo &) {}

bool GfMenuScriptManager::regist(const char *script, u32 handle, u32 id) {
  GfMenuScriptManager *manager = get();
  u32 slot;
  if (!manager->getEmptySlot(slot)) {
    return false;
  }

  unknown002 info;
  info.unknown00 = slot;
  info.unknown48 = id;
  info.unknown04 = script;
  info.unknown4c = handle;
  info.unknown50 = -1;
  info.unknown58.unknown00 = 0;
  manager->unknown10.push_back(info);
  ui::UIEventManager::get()->registObjectListener(handle, manager->unknown4118);
  GfScriptManager::loadScript(slot, script);
  GfScriptManager::startScript(slot);
  return true;
}

bool GfMenuScriptManager::getEmptySlot(u32 &slot) {
  for (u32 i = 0; i < 32; i++) {
    if (!unknown4018[i].unknown04) {
      slot = unknown4018[i].unknown00;
      unknown4018[i].unknown04 = true;
      return true;
    }
  }

  return false;
}

bool GfMenuScriptManager::regist(u32 object, u32 handle, u32 id) { return regist(getScriptName(object), handle, id); }

const char *GfMenuScriptManager::getScriptName(u32 object) {
  ui::UIObjectAcc acc(object);
  const char *name = acc.getName();
  u8 *bdat = Bdat::getFP("MNU_ScriptList");
  for (int id = Bdat::getIdTop(bdat); id <= Bdat::getIdEnd(bdat); id++) {
    if (strcmp(Bdat::getVal(bdat, "name", id).valueString, name) == 0) {
      return Bdat::getVal(bdat, "script", id).valueString;
    }
  }

  return nullptr;
}

bool GfMenuScriptManager::freeSlot(u32 slot) {
  for (size_t i = 0; i < 32; i++) {
    if (!unknown4018[i].unknown04 && unknown4018[i].unknown00 == slot) {
      unknown4018[i].unknown04 = false;
      return true;
    }
  }

  return false;
}

u32 GfMenuScriptManager::getHandle(u32 id) {
  for (unknown002 *info = get()->unknown10.begin(); info != get()->unknown10.end(); info++) {
    if (info->unknown48 == id) {
      return info->unknown4c;
    }
  }

  return 0;
}

bool GfMenuScriptManager::checkEvent(u32 handle) {
  for (unknown002 &info : get()->unknown10) {
    if (info.unknown4c == handle && !info.unknown70.empty()) {
      info.unknown58 = info.unknown70.pop_front();
      return true;
    }
  }

  return false;
}

bool GfMenuScriptManager::getEventData(u32 handle, ui::EventData &event) {
  for (unknown002 *info = get()->unknown10.begin(); info != get()->unknown10.end(); info++) {
    if (info->unknown4c == handle) {
      event = info->unknown58;
      return true;
    }
  }

  return false;
}

int GfMenuScriptManager::getCtrlId(u32 handle) {
  for (unknown002 *info = get()->unknown10.begin(); info != get()->unknown10.end(); info++) {
    if (info->unknown4c == handle) {
      return info->unknown50;
    }
  }

  return -1;
}

void GfMenuScriptManager::setCtrlId(u32 handle, int ctrlId) {
  for (unknown002 *info = get()->unknown10.begin(); info != get()->unknown10.end(); info++) {
    if (info->unknown4c == handle) {
      info->unknown50 = ctrlId;
    }
  }
}

void GfMenuScriptManager::ScriptListener::reciveEvent(const ui::EventData &event, u32 handle) {
  for (unknown002 &info : get()->unknown10) {
    if (info.unknown4c == handle) {
      if (!info.unknown70.full()) {
        info.unknown70.push(event);
      }
      return;
    }
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfMenuScriptManager>::~PtrSingleton();
