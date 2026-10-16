#pragma once
#include "event/i_todo.h"
#include "types.h"

namespace event {

class ScriptCamFollowTar : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCamFollowTar() {}
  virtual const char *cmdName() const { return "camflwtar"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param) { doit(param); }

private:
  u8 _08[0x10 - 0x08];
};

static_assert(sizeof(ScriptCamFollowTar) == 0x10, "");

} // namespace event
