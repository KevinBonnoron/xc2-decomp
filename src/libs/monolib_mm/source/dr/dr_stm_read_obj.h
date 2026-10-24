#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrCalcStmListObj;

class DrStmReadObj {
public:
  DrStmReadObj() : unknown08(nullptr), unknown10(nullptr) {}
  virtual ~DrStmReadObj() {}
  virtual void release() = 0;
  virtual bool update() = 0;
  virtual u64 getAdder() = 0;

  DrStmReadObj *unknown08; // Inferred role: next; original member name unknown.
  DrStmReadObj *unknown10; // Inferred role: prev; original member name unknown.
  u32 unknown18;           // Inferred role: read type; original member name unknown.
  u32 unknown1c;           // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(DrStmReadObj, unknown18) == 0x18, "");
static_assert(offsetof(DrStmReadObj, unknown1c) == 0x1c, "");

class DrStmReadCheck : public DrStmReadObj {
public:
  DrStmReadCheck(const char *path);
  DrStmReadCheck(u32 size);
  ~DrStmReadCheck() override;
  void release() override;
  u64 getAdder() override;
  bool update() override;

  DrCalcStmListObj *unknown20; // Inferred role: stm list; original member name unknown.
};

static_assert(offsetof(DrStmReadCheck, unknown20) == 0x20, "");

} // namespace ml
