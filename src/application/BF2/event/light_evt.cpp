#include "event/light_evt.h"

#include "event/extend.h"
#include "event/manager.h"
#include "fw/fw_debug.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/singleton.h"
#include "scn/scn.h"

namespace event {

LightEvt::LightEvt() : mLight(nullptr), mScreenID(0) {}

LightEvt::~LightEvt() { clear(); }

void LightEvt::clear() {
  if (mLight != nullptr) {
    Manager::get()->getScn()->releaseItem(mLight);
    mLight = nullptr;
  }
  path.clear();
  mScreenID = 0;
}

void LightEvt::render(int x, int y) {
  fw::debug::drawSquare2D(mm::Rect<int>(x, y, 230, 45), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<int>(x, y, 230, 45), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(x + 5, y + 5, "[EVT_LIGHT]");
  fw::debug::drawFont(x + 150, y + 5, "scrID:%d", mScreenID);
  fw::debug::drawFont(x + 10, y + 22, "file:    %s", mm::mtl::Singleton<Extend>::getPtr()->filename(path.c_str()));
}

bool LightEvt::isPlaying() const { return mLight != nullptr; }

} // namespace event
