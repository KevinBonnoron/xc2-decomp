#pragma once

namespace mm {
namespace mtl {

class IAllocator {
public:
  virtual ~IAllocator();
  virtual const char *getName();
};

} // namespace mtl
} // namespace mm
