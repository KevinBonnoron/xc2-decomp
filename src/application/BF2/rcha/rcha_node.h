#pragma once
#include <stddef.h>

#include "mtl/alloc_handle.h"
#include "rcha/rcha_anm.h"
#include "types.h"

// Base of RchaCam, RchaEff, RchaChrEff and RchaCamEff. Declared from the symbols _ZN8RchaNodeC1Ev (0x710069f5e0),
// _ZN8RchaNode5clearEv (0x710069f660) and the vtable _ZTV8RchaNode (0x71011a78d8): the destructor, setup and clear
// are its three virtual functions, and clear() zeroes the fields up to 0x199c.
class RchaNode {
public:
  static const int TRACK_UNKNOWN_48 = 48; // Inferred role: track max; original name unknown.

  RchaNode();
  virtual ~RchaNode() {}
  virtual bool setup(mtl::ALLOC_HANDLE handle, const void *data);
  virtual void clear();
  u32 hashStr(const char *name) const;

  int getFrameCount() const { return unknown199c; }

protected:
  mtl::ALLOC_HANDLE unknown08;         // Inferred role: allocation handle given to setup; original member name unknown.
  RchaAnm unknown10[TRACK_UNKNOWN_48]; // Inferred role: tracks; original member name unknown.
  int unknown1990;                     // Inferred role: track count; original member name unknown.
  int unknown1994;                     // Inferred role: set by setup from the resource header; original member name unknown.
  int unknown1998;                     // Inferred role: set by setup from the resource header; original member name unknown.
  int unknown199c;                     // Inferred role: frame count; original member name unknown.

  friend struct RchaNodeLayout;
};

struct RchaNodeLayout {
  static_assert(offsetof(RchaNode, unknown08) == 0x8, "");
  static_assert(offsetof(RchaNode, unknown10) == 0x10, "");
  static_assert(offsetof(RchaNode, unknown1990) == 0x1990, "");
  static_assert(offsetof(RchaNode, unknown1994) == 0x1994, "");
  static_assert(offsetof(RchaNode, unknown1998) == 0x1998, "");
  static_assert(offsetof(RchaNode, unknown199c) == 0x199c, "");
  static_assert(sizeof(RchaNode) == 0x19a0, "");
};
