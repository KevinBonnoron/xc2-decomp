#pragma once
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class TextWindow {
public:
  enum {
    FLAG_WRITE = 1 << 0,
    FLAG_CLOSE = 1 << 1,
  };

  TextWindow();
  virtual ~TextWindow() {}
  void clear();
  void update();
  void erase();
  void render();
  void write(const char *name, const char *text, u8 *message, u32 length, gf::GF_OBJ_HANDLE *handle);
  bool isWriting() const;
  bool isDisp() const { return (flags & FLAG_WRITE) != 0; }

private:
  u32 flags;
  mm::mtl::FixStr<256> mName;
  mm::mtl::FixStr<256> mText;
  gf::GF_OBJ_HANDLE *handle;
  gf::GfMenuCallContext *mContext;
  s32 mCloseWait;
};

static_assert(sizeof(TextWindow) == 0x230, "");

} // namespace event
