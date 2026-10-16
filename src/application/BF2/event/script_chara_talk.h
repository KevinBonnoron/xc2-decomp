#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCharaTalk : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCharaTalk() {}
  virtual const char *cmdName() const { return "charatalk"; }
  virtual void doit(const Param &param);
  virtual void redo(const Param &param) { doit(param); }
};

static_assert(sizeof(ScriptCharaTalk) == 0x8, "");

} // namespace event
