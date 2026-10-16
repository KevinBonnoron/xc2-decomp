#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCamMovePos : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCamMovePos() {}
  virtual const char *cmdName() const { return "campos"; }
  virtual void doit(const Param &param);
  virtual void redo(const Param &param);
};

static_assert(sizeof(ScriptCamMovePos) == 0x8, "");

} // namespace event
