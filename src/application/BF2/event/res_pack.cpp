#include "event/res_pack.h"

#include "event/extend.h"
#include "event/memory_manager.h"
#include "fw/fw_debug.h"
#include "fw/fw_render_resource.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/singleton.h"

namespace event {

ResPack::ResPack() : unknown90(nullptr), unknown98(nullptr), unknowna8(nullptr) {}

ResPack::~ResPack() { clear(); }

void ResPack::clear() {
  if (unknowna8 != nullptr) {
    unknowna8->release();
    unknowna8 = nullptr;
  }
  unknown08 = mtl::ALLOC_HANDLE();
  unknown98 = nullptr;
  unknown90 = nullptr;
}

void ResPack::update() {
  if (!unknown98) {
    return;
  }
  while (unknown98) {
    void (ResPack::*func)() = unknown98;
    (this->*func)();
    if (func != unknown98) {
      continue;
    }
    break;
  }
}

void ResPack::draw() {
  fw::debug::drawSquare2D(mm::Rect<int>(330, 180, 190, 45), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<int>(330, 180, 190, 45), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(335, 185, "PACK");
  if (unknowna8 == nullptr) {
    return;
  }
  const Data *data = static_cast<const Data *>(unknowna8->getAssetData());
  if (data != nullptr) {
    fw::debug::drawFont(390, 185, "       %d", data->count);
  }
  if (isLoading()) {
    fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 0.5f, 1.0f));
    fw::debug::drawFont(340, 205, "LOADING.. ->");
  } else {
    fw::debug::drawFontColor(mm::Col4(0.7f, 0.7f, 1.0f, 1.0f));
    fw::debug::drawFont(340, 205, "COMPLEATE ->");
  }
}

void ResPack::load(mtl::ALLOC_HANDLE handle, const char *path, IResPackEvent *event) {
  this->unknown08 = handle;
  this->unknown0c = path;
  unknown90 = event;
  unknowna8 = fw::RenderResource::request(mm::mtl::Singleton<MemoryManager>::getPtr()->getResHandle(), mm::mtl::Singleton<Extend>::getPtr()->evpa(this->unknown0c.c_str()), 0);
  unknown98 = &ResPack::func_loading;
}

} // namespace event
