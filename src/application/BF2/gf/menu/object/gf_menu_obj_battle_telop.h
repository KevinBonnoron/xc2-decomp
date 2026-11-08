#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace gf {

class GfMenuReferenceNumber;

class GfMenuObjBattleTelop : public GfMenuObject {
public:
  struct OpenParam {
    u16 unknown00; // Inferred role: telop message; original member name unknown.
  };

  GfMenuObjBattleTelop(u32 handle);
  ~GfMenuObjBattleTelop() override;
  static void open(const OpenParam &param);
  static void close();
  static void closeUniteCombo();
  void initialize() override;
  void finalize() override;
  void update() override;

  u32 unknown24;                                     // Role and original member name unknown, cleared by the constructor.
  GfMenuSequence<GfMenuObjBattleTelop, 8> unknown28; // Inferred role: queued steps; original member name unknown.
  bool unknown2b8;                                   // Role and original member name unknown, cleared by the constructor.
  u8 _2b9[0x2c0 - 0x2b9];
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown2c0[3]; // Inferred role: reference numbers; original member name unknown.
  mm::mtl::FixedVector<u32, 4> unknown2d8;                    // Inferred role: unite combo elements; original member name unknown.
};

static_assert(offsetof(GfMenuObjBattleTelop, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjBattleTelop, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBattleTelop, unknown2b8) == 0x2b8, "");
static_assert(offsetof(GfMenuObjBattleTelop, unknown2c0) == 0x2c0, "");
static_assert(offsetof(GfMenuObjBattleTelop, unknown2d8) == 0x2d8, "");
static_assert(sizeof(GfMenuObjBattleTelop) == 0x2f0, "");

} // namespace gf
