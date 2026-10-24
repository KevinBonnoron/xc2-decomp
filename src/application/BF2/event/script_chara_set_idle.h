#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCharaSetIdle : public ITodo {
public:
  ScriptCharaSetIdle() : unknown08(0) {}
  static ITodo *exec();
  virtual ~ScriptCharaSetIdle() {}
  virtual const char *cmdName() const { return "charasetidle"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);

private:
  int unknown08; // Inferred role: prev id; original member name unknown.
};

static_assert(sizeof(ScriptCharaSetIdle) == 0x10, "");

} // namespace event
