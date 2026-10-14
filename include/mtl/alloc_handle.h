#pragma once

namespace mtl {

class ALLOC_HANDLE {
public:
  ALLOC_HANDLE(const ALLOC_HANDLE &other);

private:
  unsigned long mHandle;
};

} // namespace mtl
