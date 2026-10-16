#pragma once
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
  void write(const char *text, u8 *message, int length, int type);
  bool isDisp() const { return (flags & FLAG_DISP) != 0; }

private:
  u32 flags;
  mm::mtl::FixStr<256> mText;
};

static_assert(sizeof(TextCaption) == 0x110, "");

} // namespace event
