#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCamMoveFov : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCamMoveFov() {}
  virtual const char *cmdName() const { return "camfov"; }
  virtual void doit(const Param &param);
  virtual void redo(const Param &param);
};

static_assert(sizeof(ScriptCamMoveFov) == 0x8, "");

} // namespace event
