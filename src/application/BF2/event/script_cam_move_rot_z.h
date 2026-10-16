#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCamMoveRotZ : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCamMoveRotZ() {}
  virtual const char *cmdName() const { return "camrotz"; }
  virtual void doit(const Param &param);
  virtual void redo(const Param &param);
};

static_assert(sizeof(ScriptCamMoveRotZ) == 0x8, "");

} // namespace event
