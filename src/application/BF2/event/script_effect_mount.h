#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptEffectMount : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptEffectMount() {}
  virtual const char *cmdName() const { return "effmount"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param) { doit(param); }
};

static_assert(sizeof(ScriptEffectMount) == 0x8, "");

} // namespace event
