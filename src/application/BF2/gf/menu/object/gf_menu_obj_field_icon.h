#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjFieldIcon : public GfMenuObject {
public:
  struct OpenParam {
    int unknown00;      // Inferred role: icon; original member name unknown.
    mm::Vec3 unknown10; // Inferred role: position; original member name unknown.
    mm::Vec3 unknown20; // Inferred role: offset; original member name unknown.
  };

  GfMenuObjFieldIcon(u32 handle);
  ~GfMenuObjFieldIcon() override;
  static void open(GfMenuCallContext *context, const OpenParam &param);
  static void close(GfMenuCallContext *context);
  static void disp(GfMenuCallContext *context, bool isDisp);
  static void dispAll(bool isDisp);
  void initialize() override;
  void finalize() override;
  void update() override;
};

static_assert(offsetof(GfMenuObjFieldIcon::OpenParam, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjFieldIcon::OpenParam, unknown20) == 0x20, "");

} // namespace gf
