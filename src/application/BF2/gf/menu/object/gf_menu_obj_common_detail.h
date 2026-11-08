#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjCommonDetail : public GfMenuObject {
public:
  struct OpenParam {
    OpenParam() : unknown18(0), unknown28(false), unknown29(false), unknown2c(0), unknown30(-1) {}

    mm::mtl::FixedVector<u32, 4> unknown00; // Inferred role: detail ids; original member name unknown.
    u32 unknown18;                          // Role and original member name unknown.
    int unknown1c;                          // Inferred role: kind of the detail, 0 driver and 1 blade; original member name unknown.
    mm::Rect<s16> unknown20;                // Inferred role: layout rect; original member name unknown.
    bool unknown28;                         // Role and original member name unknown.
    bool unknown29;                         // Role and original member name unknown.
    u32 unknown2c;                          // Inferred role: parent object handle; original member name unknown.
    int unknown30;                          // Role and original member name unknown.
  };

  GfMenuObjCommonDetail(u32 handle);
  ~GfMenuObjCommonDetail() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void close(GfMenuCallContext *context);
  static void open(GfMenuCallContext *context, const OpenParam &param);
};

static_assert(offsetof(GfMenuObjCommonDetail::OpenParam, unknown18) == 0x18, "");
static_assert(offsetof(GfMenuObjCommonDetail::OpenParam, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjCommonDetail::OpenParam, unknown30) == 0x30, "");

} // namespace gf
