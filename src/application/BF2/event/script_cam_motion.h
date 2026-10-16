#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCamMotion : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCamMotion() {}
  virtual const char *cmdName() const { return "cammotion"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param) { doit(param); }
};

static_assert(sizeof(ScriptCamMotion) == 0x8, "");

} // namespace event
