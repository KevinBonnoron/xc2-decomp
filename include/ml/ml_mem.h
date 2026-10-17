#pragma once

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {

class MlMem {
public:
  static mtl::ALLOC_HANDLE getProductMem();
};

} // namespace ml
