#pragma once
#include "types.h"

namespace fw {

class ManagerObject {
public:
  static const u32 FLAG_INITIALIZED = 1 << 0;
  static const u32 FLAG_FINALIZED = 1 << 1;

  ManagerObject();
  virtual ~ManagerObject();
  virtual bool initialize() { return true; }
  virtual bool finalize() { return true; }
  virtual void enterFinalizeApplet() {}
  virtual const char *getName() const { return "undefined"; }
  virtual bool isInitialized() const { return flags & FLAG_INITIALIZED; }
  virtual bool isFinalized() const { return flags & FLAG_FINALIZED; }

  u32 flags;
};

static_assert(sizeof(ManagerObject) == 0x10, "");

} // namespace fw
