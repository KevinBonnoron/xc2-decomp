#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCharaTgtOff : public ITodo {
public:
  virtual ~ScriptCharaTgtOff() {}
  virtual const char *cmdName() const { return "charatgtoff"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param);
};

static_assert(sizeof(ScriptCharaTgtOff) == 0x8, "");

} // namespace event
