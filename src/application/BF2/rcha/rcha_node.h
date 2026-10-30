#pragma once
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

// Base of RchaCam, RchaEff, RchaChrEff and RchaCamEff. Declared from the symbols _ZN8RchaNodeC1Ev (0x710069f5e0),
// _ZN8RchaNode5clearEv (0x710069f660) and the vtable _ZTV8RchaNode (0x71011a78d8): the destructor, setup and clear
// are its three virtual functions, and clear() zeroes the fields up to 0x199c.
class RchaNode {
public:
  RchaNode();
  virtual ~RchaNode();
  virtual void setup(mtl::ALLOC_HANDLE handle, const void *data);
  virtual void clear();

  int getFrameCount() const { return unknown199c; }

private:
  u8 _8[0x199c - 0x8];
  int unknown199c; // Inferred role: frame count; original member name unknown.
};

static_assert(sizeof(RchaNode) == 0x19a0, "");
