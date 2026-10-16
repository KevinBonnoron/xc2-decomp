#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCharaSetIdle : public ITodo {
public:
  ScriptCharaSetIdle() : mPrevId(0) {}
  static ITodo *exec();
  virtual ~ScriptCharaSetIdle() {}
  virtual const char *cmdName() const { return "charasetidle"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);

private:
  int mPrevId;
};

static_assert(sizeof(ScriptCharaSetIdle) == 0x10, "");

} // namespace event
