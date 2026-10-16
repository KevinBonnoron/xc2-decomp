#pragma once
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace csvb {

class CCsvbData {
public:
  CCsvbData();
  ~CCsvbData();
  bool Load(mtl::ALLOC_HANDLE handle, const void *data, u32 size);
  u16 GetRowCount() const;
  f32 GetFloat(u16 row, u16 column) const;
};

} // namespace csvb
