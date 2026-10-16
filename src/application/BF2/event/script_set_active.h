#pragma once
#include "event/i_todo.h"

namespace event {

class Object;

class ScriptSetActive : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptSetActive() {}
  virtual const char *cmdName() const { return "setactive"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param) { doit(param); }

private:
  Object *mPrevActive;
};

static_assert(sizeof(ScriptSetActive) == 0x10, "");

} // namespace event
