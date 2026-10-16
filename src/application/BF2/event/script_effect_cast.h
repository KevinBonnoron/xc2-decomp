#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptEffectCast : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptEffectCast() {}
  virtual const char *cmdName() const { return "effcast"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param) { doit(param); }
};

static_assert(sizeof(ScriptEffectCast) == 0x8, "");

} // namespace event
