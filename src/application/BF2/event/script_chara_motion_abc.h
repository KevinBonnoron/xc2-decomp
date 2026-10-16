#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCharaMotionABC : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCharaMotionABC() {}
  virtual const char *cmdName() const { return "charamotABC"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
};

static_assert(sizeof(ScriptCharaMotionABC) == 0x8, "");

} // namespace event
