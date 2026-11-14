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
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: write flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: close flag; original name unknown.
  };

  TextWindow();
  virtual ~TextWindow() {}
  void clear();
  void update();
  void erase();
  void render();
  void write(const char *text, const char *name, u8 *bdat, u32 textId, gf::GF_OBJ_HANDLE *handle);
  bool isWriting() const;
  bool isDisp() const { return (unknown08 & FLAG_UNKNOWN_0) != 0; }
  void hide() {
    erase();
    unknown218 = gf::unknown020;
    unknown110 = "";
    unknown0c = "";
    unknown08 &= ~(FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1);
  }

private:
  u32 unknown08;                     // Inferred role: flags; original member name unknown.
  mm::mtl::FixStr<256> unknown0c;    // Inferred role: name; original member name unknown.
  mm::mtl::FixStr<256> unknown110;   // Inferred role: text; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown218;     // Inferred role: handle; original member name unknown.
  gf::GfMenuCallContext *unknown220; // Inferred role: context; original member name unknown.
  s32 unknown228;                    // Inferred role: close wait; original member name unknown.
};

static_assert(sizeof(TextWindow) == 0x230, "");

} // namespace event
