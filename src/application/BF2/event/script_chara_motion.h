#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCharaMotion : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCharaMotion() {}
  virtual const char *cmdName() const { return "charamot"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
};

static_assert(sizeof(ScriptCharaMotion) == 0x8, "");

} // namespace event
