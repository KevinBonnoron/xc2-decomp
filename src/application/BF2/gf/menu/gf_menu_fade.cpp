#include "gf/menu/gf_menu_fade.h"

#include "gf/gf_allocator.h"
#include "gf/menu/object/gf_menu_obj_fade.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

namespace gf {

constexpr u32 FADE_LAYER = 1;

enum EVENT {
  EVENT_LAYER_CREATED = 5,
  EVENT_FADE_END = 0xb,
};

GfMenuFade::GfMenuFade(const GfSetupParam &param) : unknown08(false) { initialize(param); }

void GfMenuFade::initialize(const GfSetupParam &param) {
  for (u32 i = 0; i < FADE_COUNT; i++) {
    unknown09[i] = false;
  }
  ui::UIManager::get()->createLayer(FADE_LAYER);
  unknown08 = false;
}

GfMenuFade::~GfMenuFade() {}

void GfMenuFade::build(const GfSetupParam &param) {
// __LINE__ must be 51 as in the original file: its value changes the instruction order.
#line 51
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfMenuFade(param);
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
  if (type < FADE_COUNT && fade != nullptr) {
    return fade->unknown09[type];
  }
  return false;
}

void GfMenuFade::reciveEvent(const ui::EventData &event, u32 handle) {
  GfMenuFade *fade = get();
  if (fade != nullptr) {
    switch (event.type) {
    case EVENT_LAYER_CREATED:
      if (event.param1 == 1) {
        fade->unknown08 = true;
      }
      break;
    case EVENT_FADE_END: {
      int type = event.param0;
      if (type < static_cast<int>(FADE_COUNT)) {
        fade->unknown09[type] = false;
      }
      break;
    }
    }
  }
}

} // namespace gf
