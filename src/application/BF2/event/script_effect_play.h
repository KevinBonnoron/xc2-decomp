#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptEffectPlay : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptEffectPlay() {}
  virtual const char *cmdName() const { return "effplay"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param);
};

static_assert(sizeof(ScriptEffectPlay) == 0x8, "");

} // namespace event
