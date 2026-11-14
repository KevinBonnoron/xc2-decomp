#pragma once
#include <stddef.h>

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_balloon.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

enum SELECT_TYPE {
  SELECT_TYPE_UNKNOWN_0 = 0, // Inferred role: balloon; original name unknown.
  SELECT_TYPE_UNKNOWN_1 = 1, // Inferred role: box; original name unknown.
};

class SelectWindow {
public:
  enum {
    FLAG_UNKNOWN_0 = 0, // Inferred role: open flag; original name unknown.
  };

  SelectWindow();
  virtual ~SelectWindow() {}
  void clear();
  void update();
  void close();
  void open(SELECT_TYPE type, int textId, const int *selectIds, size_t count, u8 *bdat, gf::GF_OBJ_HANDLE *handle);
  int getResult();
  bool isOpen() const { return unknown08.test(FLAG_UNKNOWN_0); }
  int getSelected() const { return unknown0c; }

private:
  void closeContext() {
    if (unknown10 != nullptr) {
      gf::GfMenuObjBalloon::close(unknown10, true);
      mm::mtl::safeRelease(unknown10);
    }
  }

  mm::mtl::unknown027<32> unknown08; // Inferred role: flags; original member name unknown.
  int unknown0c;                     // Inferred role: result; original member name unknown.
  gf::GfMenuCallContext *unknown10;  // Inferred role: context; original member name unknown.
};

static_assert(sizeof(SelectWindow) == 0x18, "");

} // namespace event
