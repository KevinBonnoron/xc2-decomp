#pragma once
#include "gf/menu/object/gf_menu_obj_event_subtitle.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class TextCaption {
public:
  enum {
    FLAG_DISP = 1 << 0,
  };

  TextCaption();
  virtual ~TextCaption() {}
  void clear();
  void update();
  void render();
  void write(const char *text, u8 *bdat, int textId, int position);
  bool isDisp() const { return (flags & FLAG_DISP) != 0; }
  void hide() {
    gf::GfMenuObjEventSubtitle::hideText();
    text = "";
    flags &= ~FLAG_DISP;
  }

private:
  u32 flags;
  mm::mtl::FixStr<256> text;
};

static_assert(sizeof(TextCaption) == 0x110, "");

} // namespace event
