#pragma once
#include "gf/object/gf_obj_handle.h"
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
  void write(const char *text, const char *name, u8 *bdat, u32 textId, gf::GF_OBJ_HANDLE *handle);
  bool isWriting() const;
  bool isDisp() const { return (flags & FLAG_WRITE) != 0; }
  void hide() {
    erase();
    handle = gf::INVALID_HANDLE;
    text = "";
    name = "";
    flags &= ~(FLAG_WRITE | FLAG_CLOSE);
  }

private:
  u32 flags;
  mm::mtl::FixStr<256> name;
  mm::mtl::FixStr<256> text;
  gf::GF_OBJ_HANDLE *handle;
  gf::GfMenuCallContext *context;
  s32 closeWait;
};

static_assert(sizeof(TextWindow) == 0x230, "");

} // namespace event
