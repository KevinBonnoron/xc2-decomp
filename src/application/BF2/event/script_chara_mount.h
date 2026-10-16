#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCharaMount : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCharaMount() {}
  virtual const char *cmdName() const { return "charamount"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
};

static_assert(sizeof(ScriptCharaMount) == 0x8, "");

} // namespace event
