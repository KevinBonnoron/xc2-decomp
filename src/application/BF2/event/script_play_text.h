#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptPlayText : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptPlayText() {}
  virtual const char *cmdName() const { return "text"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
};

static_assert(sizeof(ScriptPlayText) == 0x8, "");

} // namespace event
