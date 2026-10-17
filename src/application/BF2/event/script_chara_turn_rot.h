#pragma once
#include "event/i_todo.h"
#include "event/rot_axis.h"

namespace event {

class ScriptCharaTurnRot : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCharaTurnRot() {}
  virtual const char *cmdName() const { return "charaturnrot"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param);

private:
  RotAxis prevAxis;
};

static_assert(sizeof(ScriptCharaTurnRot) == 0x30, "");

} // namespace event
