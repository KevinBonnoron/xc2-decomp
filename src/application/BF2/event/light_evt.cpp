#include "event/light_evt.h"

#include "event/extend.h"
#include "event/manager.h"
#include "fw/fw_debug.h"
#include "ml/scn.h"
#include "ml/scn_obj_light.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/singleton.h"

namespace event {

LightEvt::LightEvt() : unknown08(nullptr), unknown94(0) {}

LightEvt::~LightEvt() { clear(); }

void LightEvt::clear() {
  if (unknown08 != nullptr) {
    Manager::get()->getScn()->releaseItem(unknown08);
    unknown08 = nullptr;
  }
  unknown10.clear();
  unknown94 = 0;
}

void LightEvt::play(void *data, const char *name, u32 screenID) {
  if (unknown08 != nullptr) {
    Manager::get()->getScn()->releaseItem(unknown08);
    unknown08 = nullptr;
  }
  unknown10 = "";
  unknown94 = 0;
  unknown10 = name;
  unknown08 = static_cast<ml::ScnObjLight *>(Manager::get()->getScn()->createLgt(data, screenID));
  unknown94 = screenID;
}

void LightEvt::render(int x, int y) {
  fw::debug::drawSquare2D(mm::Rect<int>(x, y, 230, 45), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<int>(x, y, 230, 45), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(x + 5, y + 5, "[EVT_LIGHT]");
  fw::debug::drawFont(x + 150, y + 5, "scrID:%d", unknown94);
  fw::debug::drawFont(x + 10, y + 22, "file:    %s", mm::mtl::Singleton<Extend>::getPtr()->filename(unknown10.c_str()));
}

bool LightEvt::isPlaying() const { return unknown08 != nullptr; }

void LightEvt::setPos(const mm::Vec3 &pos) {
  // The call at 0x71000e2cf8 dispatches through vtable offset 0x80.
  if (unknown08 != nullptr)
    unknown08->setOffsetPos(pos);
}

} // namespace event
