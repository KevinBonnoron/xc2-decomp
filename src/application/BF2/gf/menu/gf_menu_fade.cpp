#include "gf/menu/gf_menu_fade.h"

#include "gf/gf_allocator.h"
#include "gf/menu/object/gf_menu_obj_fade.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

namespace gf {

// Inferred role: UI layer of the fade; original name unknown.
constexpr u32 LAYER_UNKNOWN_1 = 1;

enum EVENT {
  EVENT_UNKNOWN_5 = 5,    // Inferred role: event sent when the layer is created; original enumerator name unknown.
  EVENT_UNKNOWN_11 = 0xb, // Inferred role: event sent when a fade ends; original enumerator name unknown.
};

GfMenuFade::GfMenuFade(const GfSetupParam &param) : unknown08(false) { initialize(param); }

void GfMenuFade::initialize(const GfSetupParam &param) {
  for (u32 i = 0; i < FADE_UNKNOWN_3; i++) {
    unknown09[i] = false;
  }
  ui::UIManager::get()->createLayer(LAYER_UNKNOWN_1);
  unknown08 = false;
}

GfMenuFade::~GfMenuFade() {}

void GfMenuFade::build(const GfSetupParam &param) {
// __LINE__ must be 51 as in the original file: its value changes the instruction order.
#line 51
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfMenuFade(param);
}

void GfMenuFade::destroy() {
  GfMenuFade *fade = get();
  fade->finalize();
  delete fade;
}

void GfMenuFade::finalize() { unknown08 = false; }

bool GfMenuFade::isInitialized() {
  if (get() != nullptr) {
    return get()->unknown08;
  }
  return false;
}

void GfMenuFade::postUpdate(const fw::UpdateInfo &info) {}

void GfMenuFade::getFadeColor(u32 type, mm::Col4 &color) {
  if (get() != nullptr && get()->unknown08) {
    GfMenuObjFade::getFadeColor(type, color);
  }
}

void GfMenuFade::setLoading(u32 type, bool disp) { GfMenuObjFade::dispLoading(disp, type); }

bool GfMenuFade::isFading(u32 type) {
  GfMenuFade *fade = get();
  if (type < FADE_UNKNOWN_3 && fade != nullptr) {
    return fade->unknown09[type];
  }
  return false;
}

void GfMenuFade::reciveEvent(const ui::EventData &event, u32 handle) {
  GfMenuFade *fade = get();
  if (fade != nullptr) {
    switch (event.unknown00) {
    case EVENT_UNKNOWN_5:
      if (event.unknown0c == 1) {
        fade->unknown08 = true;
      }
      break;
    case EVENT_UNKNOWN_11: {
      int type = event.unknown08;
      if (type < static_cast<int>(FADE_UNKNOWN_3)) {
        fade->unknown09[type] = false;
      }
      break;
    }
    }
  }
}

} // namespace gf
