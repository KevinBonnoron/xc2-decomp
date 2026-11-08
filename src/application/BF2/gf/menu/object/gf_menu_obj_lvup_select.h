#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;
class GfMenuReferenceNumber;

class GfMenuObjLvupSelect : public GfMenuObject {
public:
  GfMenuObjLvupSelect(u32 handle);
  ~GfMenuObjLvupSelect() override;
  static void openLevelSelect(GfMenuCallContext *context, u32 level);
  static void openLevelup(GfMenuCallContext *context, u32 level, u32 levelMax);
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x28 - 0x24];
  GfMenuSequence<GfMenuObjLvupSelect, 8> unknown28; // Inferred role: queued steps; original member name unknown.
  bool unknown2b8;                                  // Role and original member name unknown, cleared by the constructor.
  u8 _2b9[0x2c8 - 0x2b9];
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown2c8; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown2d0; // Inferred role: reference number; original member name unknown.
  GfMenuCallContext *unknown2d8;                           // Inferred role: call context; original member name unknown.
};

static_assert(offsetof(GfMenuObjLvupSelect, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjLvupSelect, unknown2b8) == 0x2b8, "");
static_assert(offsetof(GfMenuObjLvupSelect, unknown2c8) == 0x2c8, "");
static_assert(offsetof(GfMenuObjLvupSelect, unknown2d0) == 0x2d0, "");
static_assert(offsetof(GfMenuObjLvupSelect, unknown2d8) == 0x2d8, "");
static_assert(sizeof(GfMenuObjLvupSelect) == 0x2e0, "");
} // namespace gf
