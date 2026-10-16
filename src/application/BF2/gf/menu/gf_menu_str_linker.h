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

  mm::mtl::IAllocator *allocator;
  mm::mtl::FixedArray<ui::UIStr, STRING_MAX> strings;
  mm::mtl::FixedVector<u32, STRING_MAX> freeIds;
  mm::mtl::FixedVector<ui::UIStr, SELECT_STRING_MAX> selectStrings;
};

static_assert(offsetof(GfMenuStrLinker, allocator) == 0x08, "");
static_assert(offsetof(GfMenuStrLinker, strings) == 0x10, "");
static_assert(offsetof(GfMenuStrLinker, freeIds) == 0xc10, "");
static_assert(offsetof(GfMenuStrLinker, selectStrings) == 0xe18, "");
static_assert(sizeof(GfMenuStrLinker) == 0xee0, "");

} // namespace gf
