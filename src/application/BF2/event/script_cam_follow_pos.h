#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCamFollowPos : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCamFollowPos() {}
  virtual const char *cmdName() const { return "camflwpos"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param) { doit(param); }

private:
  bool prevFollow;
};

static_assert(sizeof(ScriptCamFollowPos) == 0x10, "");

} // namespace event
