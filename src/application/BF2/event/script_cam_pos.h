#pragma once
#include "event/i_todo.h"
#include "event/pos_axis.h"

namespace event {

class ScriptCamPos : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCamPos() {}
  virtual const char *cmdName() const { return "campos"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param) { doit(param); }

private:
  PosAxis prevAxis;
};

static_assert(sizeof(ScriptCamPos) == 0x30, "");

} // namespace event
