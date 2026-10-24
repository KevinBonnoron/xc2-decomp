#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCharaHead : public ITodo {
public:
  ScriptCharaHead() : unknown08(0) {}
  static ITodo *exec();
  virtual ~ScriptCharaHead() {}
  virtual const char *cmdName() const { return "charahead"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param);

private:
  int unknown08; // Inferred role: prev id; original member name unknown.
};

static_assert(sizeof(ScriptCharaHead) == 0x10, "");

} // namespace event
