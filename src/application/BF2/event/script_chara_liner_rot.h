#pragma once
#include "event/i_todo.h"
#include "event/rot_axis.h"

namespace event {

class ScriptCharaLinerRot : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCharaLinerRot() {}
  virtual const char *cmdName() const { return "charalinerrot"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param);

private:
  RotAxis unknown10; // Inferred role: prev axis; original member name unknown.
};

static_assert(sizeof(ScriptCharaLinerRot) == 0x30, "");

} // namespace event
