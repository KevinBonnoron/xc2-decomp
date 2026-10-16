#include "event/text_window.h"

#include "fw/fw_debug.h"
#include "gf/object/gf_obj_handle.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"

namespace event {

TextWindow::TextWindow() : flags(0), handle(gf::INVALID_HANDLE), mContext(nullptr) {}

void TextWindow::render() {
  if (!isDisp()) {
    return;
  }
  s32 height = ml::DevGraph::getRootHeight();
  s32 y = height - 200;
  s32 width = ml::DevGraph::getRootWidth() - 500;
  fw::debug::drawSquare2D(mm::Rect<s32>(250, y, width, 60), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(250, y, width, 60), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(260, height - 190, "TEXTWIN");
  fw::debug::drawFont(335, height - 190, "[%s]", mName.c_str());
  fw::debug::drawFont(265, height - 175, mText.c_str());
}

bool TextWindow::isWriting() const { return (flags & (FLAG_WRITE | FLAG_CLOSE)) == FLAG_WRITE; }

} // namespace event
