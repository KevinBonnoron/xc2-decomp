#include "event/alpha_manager.h"

#include <stddef.h>

#include "event/memory_manager.h"
#include "fw/fw_debug.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

AlphaManager::AlphaManager() : unknown10(0), unknown14(0) {}

void AlphaManager::clear() {
  for (size_t i = 0; i < unknown18.size(); i++) {
    delete unknown18[i];
  }
  unknown18.clear();
  unknown10 = 0;
}

void AlphaManager::render() {
  if (!(unknown14 & DISP_FLAG_DISP) || !(unknown10 & FLAG_ACTIVE)) {
    return;
  }
  int height = unknown18.size() * 20 + 50;
  fw::debug::drawSquare2D(mm::Rect<int>(210, 140, 700, height), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<int>(210, 140, 700, height), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(215, 145, "ALPHA");
  fw::debug::drawFont(560, 145, "TOTAL %d", unknown18.size());
  for (size_t i = 0; i < unknown18.size(); i++) {
    unknown18[i]->draw(230, 170 + i * 20);
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
    unknown18.push_back(obj);
  }
  unknown10 |= FLAG_ACTIVE;
}

AlphaObj *AlphaManager::search(gf::GF_OBJ_HANDLE *handle) const {
  for (size_t i = 0; i < unknown18.size(); i++) {
    if (unknown18[i]->getHandle() == handle) {
      return unknown18[i];
    }
  }
  return nullptr;
}

void AlphaManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown14 |= DISP_FLAG_DISP;
  } else {
    unknown14 &= ~DISP_FLAG_DISP;
  }
}

bool AlphaManager::isDisp() const { return (unknown14 & DISP_FLAG_DISP) != 0; }

void AlphaManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UPDATE:
    update();
    break;
  case MSG_TYPE_CLEAR:
    clear();
    break;
  case MSG_TYPE_RENDER:
    render();
    break;
  default:
    break;
  }
}

} // namespace event
