#pragma once

namespace mm {
namespace mtl {

class NoncopyableBase {
public:
  NoncopyableBase() {}
  virtual ~NoncopyableBase() {}

private:
  NoncopyableBase(const NoncopyableBase &);
  NoncopyableBase &operator=(const NoncopyableBase &);
};

} // namespace mtl
} // namespace mm
