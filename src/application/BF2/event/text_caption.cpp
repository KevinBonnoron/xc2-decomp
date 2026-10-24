#include "event/text_caption.h"

#include "fw/fw_debug.h"
#include "gf/menu/object/gf_menu_obj_event_subtitle.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"

namespace event {

TextCaption::TextCaption() : unknown08(0) {}

void TextCaption::clear() {
  if (isDisp()) {
    gf::GfMenuObjEventSubtitle::hideText();
  }
  unknown0c = "";
  unknown08 = 0;
}

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
  fw::debug::drawFont(265, height - 175, unknown0c.c_str());
}

void TextCaption::write(const char *text, u8 *bdat, int textId, int position) {
  if (textId < 0 || *text == '\0' || bdat == nullptr) {
    hide();
    return;
  }
  gf::GfMenuObjEventSubtitle::dispText(bdat, textId, position);
  this->unknown0c = text;
  unknown08 |= FLAG_DISP;
}

} // namespace event
