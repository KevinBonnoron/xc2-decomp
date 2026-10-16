#include "event/alpha_manager.h"

#include <stddef.h>

#include "event/memory_manager.h"
#include "fw/fw_debug.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

AlphaManager::AlphaManager() : flags(0), dispFlags(0) {}

void AlphaManager::clear() {
  for (size_t i = 0; i < objs.size(); i++) {
    delete objs[i];
  }
  objs.clear();
  flags = 0;
}

void AlphaManager::render() {
  if (!(dispFlags & DISP_FLAG_DISP) || !(flags & FLAG_ACTIVE)) {
    return;
  }
  int height = objs.size() * 20 + 50;
  fw::debug::drawSquare2D(mm::Rect<int>(210, 140, 700, height), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<int>(210, 140, 700, height), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(215, 145, "ALPHA");
  fw::debug::drawFont(560, 145, "TOTAL %d", objs.size());
  for (size_t i = 0; i < objs.size(); i++) {
    objs[i]->draw(230, 170 + i * 20);
    if (i > 40) {
      fw::debug::drawFont(580, 195 + i * 20, "and more..");
      return;
    }
  }
}

void AlphaManager::setAlpha(gf::GF_OBJ_HANDLE *handle, ALPHA_ATTR attr, f32 alpha, f32 belongingAlpha) {
  AlphaObj *obj = search(handle);
  if (obj != nullptr) {
    obj->setAlpha(attr, alpha, belongingAlpha);
  } else {
    obj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle()) AlphaObj(handle);
    obj->setAlpha(attr, alpha, belongingAlpha);
    objs.push_back(obj);
  }
  flags |= FLAG_ACTIVE;
}

AlphaObj *AlphaManager::search(gf::GF_OBJ_HANDLE *handle) const {
  for (size_t i = 0; i < objs.size(); i++) {
    if (objs[i]->getHandle() == handle) {
      return objs[i];
    }
  }
  return nullptr;
}

void AlphaManager::setDisp(bool isDisp) {
  if (isDisp) {
    dispFlags |= DISP_FLAG_DISP;
  } else {
    dispFlags &= ~DISP_FLAG_DISP;
  }
}

bool AlphaManager::isDisp() const { return (dispFlags & DISP_FLAG_DISP) != 0; }

} // namespace event
