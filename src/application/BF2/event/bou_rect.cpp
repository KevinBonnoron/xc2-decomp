#include "event/bou_rect.h"

#include "fw/fw_debug.h"
#include "mm_math/mm_col4.h"

namespace event {

BouRect::BouRect() : mm::Rect<int>(mm::Rect<int>::zero()) {}

BouRect::~BouRect() {}

void BouRect::render() {
  fw::debug::drawSquare2D(mm::Rect<int>(*this), mm::Col4(0.25f, 0.25f, 1.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<int>(*this), mm::Col4(0.25f, 0.25f, 1.0f, 1.0f));
}

} // namespace event
