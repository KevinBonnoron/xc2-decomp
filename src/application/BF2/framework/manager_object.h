#pragma once
#include "types.h"

namespace fw {

class ManagerObject {
public:
  static const u32 FLAG_UNKNOWN_0 = 1 << 0; // Inferred role: initialized; original name unknown.
  static const u32 FLAG_UNKNOWN_1 = 1 << 1; // Inferred role: finalized; original name unknown.

  ManagerObject();
  virtual ~ManagerObject();
  virtual bool initialize() { return true; }
  virtual bool finalize() { return true; }
  virtual void enterFinalizeApplet() {}
  virtual const char *getName() const { return "undefined"; }
  virtual bool isInitialized() const { return unknown08 & FLAG_UNKNOWN_0; }
  virtual bool isFinalized() const { return unknown08 & FLAG_UNKNOWN_1; }

  u32 unknown08; // Inferred role: flags; original member name unknown.
};

static_assert(sizeof(ManagerObject) == 0x10, "");

} // namespace fw
