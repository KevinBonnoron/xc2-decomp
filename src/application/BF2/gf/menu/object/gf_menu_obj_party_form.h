#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

class GfMenuObjPartyForm : public GfMenuObject {
public:
  GfMenuObjPartyForm(u32 handle);
  ~GfMenuObjPartyForm() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void selectDriver(u32 handle, u32 index, u32 state);
  static void selectBlade(u32 handle, u32 index, u32 state);

  u8 _24[0x28 - 0x24];
  mm::mtl::FixedVector<mm::mtl::FixedVector<u32, 8>, 5> unknown28;  // Inferred role: list rows; element type inferred from the size of the storage; original member name unknown.
  mm::mtl::FixedVector<u64, 5> unknown0f8;                          // Inferred role: unused; element type inferred from the size of the storage; original member name unknown.
  mm::mtl::FixedVector<mm::mtl::FixedVector<u32, 8>, 3> unknown128; // Inferred role: list rows; element type inferred from the size of the storage; original member name unknown.
};

static_assert(offsetof(GfMenuObjPartyForm, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjPartyForm, unknown0f8) == 0xf8, "");
static_assert(offsetof(GfMenuObjPartyForm, unknown128) == 0x128, "");

} // namespace gf
