#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCharaAction : public ITodo {
public:
  ScriptCharaAction() : mPrevId(0) {}
  static ITodo *exec();
  virtual ~ScriptCharaAction() {}
  virtual const char *cmdName() const { return "charaact"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param);

private:
  int mPrevId;
};

static_assert(sizeof(ScriptCharaAction) == 0x10, "");

} // namespace event
