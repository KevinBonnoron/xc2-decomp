#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCharaAction : public ITodo {
public:
  ScriptCharaAction() : unknown08(0) {}
  static ITodo *exec();
  virtual ~ScriptCharaAction() {}
  virtual const char *cmdName() const { return "charaact"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param);

private:
  int unknown08; // Inferred role: prev id; original member name unknown.
};

static_assert(sizeof(ScriptCharaAction) == 0x10, "");

} // namespace event
