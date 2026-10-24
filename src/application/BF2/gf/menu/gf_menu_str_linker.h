#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/ui_str.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace gf {

class GfMenuStrLinker {
public:
  static const u32 STRING_MAX = 128;
  static const u32 SELECT_STRING_MAX = 8;

  GfMenuStrLinker(mm::mtl::IAllocator *allocator);
  virtual ~GfMenuStrLinker();
  u16 addString(const ui::UIStr &string);
  void delString(u16 id);
  const ui::UIStr &getString(u16 id);
  void addSelectString(const ui::UIStr &string);
  void clearSelectString();

  mm::mtl::IAllocator *unknown08;                                // Inferred role: allocator; original member name unknown.
  mm::mtl::FixedArray<ui::UIStr, STRING_MAX> unknown10;          // Inferred role: strings; original member name unknown.
  mm::mtl::FixedVector<u32, STRING_MAX> unknownc10;              // Inferred role: free ids; original member name unknown.
  mm::mtl::FixedVector<ui::UIStr, SELECT_STRING_MAX> unknowne18; // Inferred role: select strings; original member name unknown.
};

static_assert(offsetof(GfMenuStrLinker, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuStrLinker, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuStrLinker, unknownc10) == 0xc10, "");
static_assert(offsetof(GfMenuStrLinker, unknowne18) == 0xe18, "");
static_assert(sizeof(GfMenuStrLinker) == 0xee0, "");

} // namespace gf
