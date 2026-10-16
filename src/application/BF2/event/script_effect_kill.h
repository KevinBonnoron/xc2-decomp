#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptEffectKill : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptEffectKill() {}
  virtual const char *cmdName() const { return "effkill"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param) {}
  virtual void redo(const Param &param);
};

static_assert(sizeof(ScriptEffectKill) == 0x8, "");

} // namespace event
