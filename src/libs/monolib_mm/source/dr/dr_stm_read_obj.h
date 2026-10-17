#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrCalcStmListObj;

class DrStmReadObj {
public:
  DrStmReadObj() : m_next(nullptr), m_prev(nullptr) {}
  virtual ~DrStmReadObj() {}
  virtual void release() = 0;
  virtual bool update() = 0;
  virtual u64 getAdder() = 0;

  DrStmReadObj *m_next;
  DrStmReadObj *m_prev;
  u32 m_readType;
  u32 m_flags;
};

static_assert(offsetof(DrStmReadObj, m_readType) == 0x18, "");
static_assert(offsetof(DrStmReadObj, m_flags) == 0x1c, "");

class DrStmReadCheck : public DrStmReadObj {
public:
  DrStmReadCheck(const char *path);
  DrStmReadCheck(u32 size);
  ~DrStmReadCheck() override;
  void release() override;
  u64 getAdder() override;
  bool update() override;

  DrCalcStmListObj *m_stmList;
};

static_assert(offsetof(DrStmReadCheck, m_stmList) == 0x20, "");

} // namespace ml
