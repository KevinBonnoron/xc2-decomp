#include "gf/menu/object/gf_menu_obj_environment_info.h"

#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_game_adapter.h"
#include "gf/menu/gf_menu_flag.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {
class GfMenuAdapter;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x2a;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x100;
// Inferred role: enabled flag and fade control of a list that was just created; original name unknown.
// Decision 2026-11-14 #20: the pair is stored as a unit (one 64-bit constant at 0x710045d9b4), not merged with 0x0c, which is the evidence of a sub-object (as in GfMenuObjArtsPalette and the
// compass).
static const GfMenuObjEnvironmentInfo::ListListener::unknown004 unknown005 = {1, -1};

GfMenuObjEnvironmentInfo::GfMenuObjEnvironmentInfo(u32 handle) : GfMenuObject(handle) {}

GfMenuObjEnvironmentInfo::~GfMenuObjEnvironmentInfo() { ; }

void GfMenuObjEnvironmentInfo::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
// __LINE__ must be 86 as in the original file: it is the line argument of operator new.
#line 86
    ListListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
    attachExternalCall(unknown001, main);
    setupScreen(main);
  }
  GfMenuObject::initialize();
}

void GfMenuObjEnvironmentInfo::finalize() { GfMenuObject::finalize(); }

void GfMenuObjEnvironmentInfo::update() { GfMenuObject::update(); }

void GfMenuObjEnvironmentInfo::ListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown0c = 0;
    unknown10 = unknown005;
    break;
  case 2:
    acc.setTerm();
    break;
  case GfMenuTypes::unknown003_33: {
    int flag = GfMenuFlag::get1(0x1e);
    unknown10.unknown00 = flag == 0;
    if (flag == 0 && unknown0c == 0) {
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown10 = 0;
      param.unknown00 = 0;
      param.unknown04 = 0;
      param.unknown0d = true;
      param.unknown08 = unknown10.unknown04;
      // Decision 2026-11-14 #21: the game calls startPresetCtrl first and stores both members after the call.
      int ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
      unknown0c = 1;
      unknown10.unknown04 = ctrl;
    }
    break;
  }
  case GfMenuTypes::unknown003_34:
    if (unknown0c == 1) {
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown10 = 0;
      param.unknown04 = 1;
      param.unknown0d = true;
      param.unknown08 = unknown10.unknown04;
      int ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
      unknown0c = 0;
      unknown10.unknown04 = ctrl;
    }
    break;
  case unknown003:
    if (unknown10.unknown00 == 0) {
      unknown10.unknown00 = 1;
    }
    break;
  case unknown002:
    if (unknown10.unknown00 == 1) {
      unknown10.unknown00 = 0;
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjEnvironmentInfo::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjEnvironmentInfo::open() { unknown143(unknown001, GfMenuTypes::unknown003_33); }

void GfMenuObjEnvironmentInfo::disable() {
  if (unknown143(unknown001, unknown002)) {
    GfMenuFlag::set1(0x1e, 1);
  }
}

void GfMenuObjEnvironmentInfo::enable() {
  if (unknown143(unknown001, unknown003)) {
    GfMenuFlag::set1(0x1e, 0);
  }
}

void GfMenuObjEnvironmentInfo::createAdapter(u32 handle, const char *name, u32 type) {
  ui::UIObjectAcc acc(handle, name);
  if (acc.isValid()) {
    GfMenuAdapter *adapter = GfMenuGameAdapter::create(acc.unknown10, type, true);
    acc.setDisp(adapter != nullptr);
  }
}

void GfMenuObjEnvironmentInfo::setupScreen(u32 handle) {
  createAdapter(handle, "IMG_weather_icon", 3);
  createAdapter(handle, "IMG_cloud", 4);
  createAdapter(handle, "TXT_time", 2);
  createAdapter(handle, "TXT_location", 6);
  createAdapter(handle, "IMG_timezone", 8);
}

} // namespace gf
