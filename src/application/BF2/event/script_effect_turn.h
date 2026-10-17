#pragma once
#include "event/i_todo.h"
#include "event/rot_axis.h"

namespace event {

class ScriptEffectTurn : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptEffectTurn() {}
  virtual const char *cmdName() const { return "effturn"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param);

private:
  RotAxis prevAxis;
};

static_assert(sizeof(ScriptEffectTurn) == 0x30, "");

} // namespace event
