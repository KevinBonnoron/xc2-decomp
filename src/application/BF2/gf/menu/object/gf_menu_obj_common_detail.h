#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjCommonDetail : public GfMenuObject {
public:
  struct OpenParam {
    // Decision 2026-11-14 #3: the game's `new OpenParam()` in GfMenuObjCommonDetail::open zeroes unknown18 and unknown1c with one store (str xzr, [x22, #0x18] at 0x7100437868).
    OpenParam() : unknown18(0), unknown1c(0), unknown28(false), unknown29(false), unknown2c(0), unknown30(-1) {}

    mm::mtl::FixedVector<u32, 4> unknown00; // Inferred role: detail ids; original member name unknown.
    u32 unknown18;                          // Role and original member name unknown.
    int unknown1c;                          // Inferred role: kind of the detail, 0 driver and 1 blade; original member name unknown.
    mm::Rect<s16> unknown20;                // Inferred role: layout rect; original member name unknown.
    bool unknown28;                         // Role and original member name unknown.
    bool unknown29;                         // Role and original member name unknown.
    u32 unknown2c;                          // Inferred role: parent object handle; original member name unknown.
    int unknown30;                          // Role and original member name unknown.
  };

  class DetailListener : public ui::UIObjectListener {
  public:
    DetailListener() {
      unknown0c = unknown142();
      unknown20 = nullptr;
    }
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    unknown142 unknown0c;             // Inferred role: work values; original member name unknown.
    GfMenuObjCommonDetail *unknown20; // Inferred role: owner, always null; original member name unknown.
    OpenParam unknown28;              // Inferred role: param of the opened detail; original member name unknown.
    u8 _60[0xa0 - 0x60];
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
static_assert(sizeof(GfMenuObjCommonDetail::OpenParam) == 0x38, "");
static_assert(offsetof(GfMenuObjCommonDetail::DetailListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjCommonDetail::DetailListener, unknown28) == 0x28, "");
static_assert(sizeof(GfMenuObjCommonDetail::DetailListener) == 0xa0, "");

} // namespace gf
