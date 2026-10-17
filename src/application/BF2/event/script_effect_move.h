#pragma once
#include "event/i_todo.h"
#include "event/pos_axis.h"

namespace event {

class ScriptEffectMove : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptEffectMove() {}
  virtual const char *cmdName() const { return "effmove"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param);

private:
  PosAxis prevAxis;
};

static_assert(sizeof(ScriptEffectMove) == 0x30, "");

} // namespace event
