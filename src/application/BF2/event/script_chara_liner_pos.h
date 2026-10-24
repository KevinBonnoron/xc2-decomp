#pragma once
#include "event/i_todo.h"
#include "event/pos_axis.h"

namespace event {

class ScriptCharaLinerPos : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCharaLinerPos() {}
  virtual const char *cmdName() const { return "charalinerpos"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param);

private:
  PosAxis unknown10; // Inferred role: prev axis; original member name unknown.
};

static_assert(sizeof(ScriptCharaLinerPos) == 0x30, "");

} // namespace event
