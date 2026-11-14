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

// Name and template shape from the symbol _ZN2mm3mtl11NoncopyableIN3mtl10MemManagerEED2Ev (0x710077aa20), the only instantiation of the
// game: its destructor is the 4 byte `ret`. Nothing proves that a class derives from it (no caller, no vtable).
template <typename T> class Noncopyable {
public:
  ~Noncopyable() {}
};

} // namespace mtl
} // namespace mm
