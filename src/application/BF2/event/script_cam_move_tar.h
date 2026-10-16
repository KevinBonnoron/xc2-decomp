#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCamMoveTar : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCamMoveTar() {}
  virtual const char *cmdName() const { return "camtar"; }
  virtual void doit(const Param &param);
  virtual void redo(const Param &param);
};

static_assert(sizeof(ScriptCamMoveTar) == 0x8, "");

} // namespace event
