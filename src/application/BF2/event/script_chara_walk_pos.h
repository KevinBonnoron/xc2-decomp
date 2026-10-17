#pragma once
#include "event/i_todo.h"
#include "event/pos_axis.h"

namespace event {

class ScriptCharaWalkPos : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCharaWalkPos() {}
  virtual const char *cmdName() const { return "charawalkpos"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param);

private:
  PosAxis prevAxis;
};

static_assert(sizeof(ScriptCharaWalkPos) == 0x30, "");

} // namespace event
