#include "event/text_caption.h"

#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"

namespace event {

TextCaption::TextCaption() : flags(0) {}

void TextCaption::update() {}

void TextCaption::render() {
  if (!isDisp()) {
    return;
  }
  s32 height = ml::DevGraph::getRootHeight();
  s32 y = height - 200;
  s32 width = ml::DevGraph::getRootWidth() - 500;
  fw::debug::drawSquare2D(mm::Rect<s32>(250, y, width, 60), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(250, y, width, 60), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(260, height - 190, "CAPTION");
  fw::debug::drawFont(265, height - 175, mText.c_str());
}

} // namespace event
