#pragma once
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace csvb {

class CCsvbData {
public:
  CCsvbData();
  ~CCsvbData();
  bool Load(mtl::ALLOC_HANDLE handle, const void *data, u32 size);
  bool Load(mm::mtl::IAllocator *allocator, const void *data, u32 size);
  bool Copy(mtl::ALLOC_HANDLE handle, const CCsvbData *source);
  bool Copy(mm::mtl::IAllocator *allocator, const CCsvbData *source);
  u16 GetRowCount() const;
  f32 GetFloat(u16 row, u16 column) const;

  u8 _00[0x38 - 0x00];
};

static_assert(sizeof(CCsvbData) == 0x38, "");

} // namespace csvb
