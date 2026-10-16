#pragma once
#include "event/i_todo.h"
#include "types.h"

namespace event {

class ScriptCamRotZ : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCamRotZ() {}
  virtual const char *cmdName() const { return "camrotz"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param) { doit(param); }

private:
  u8 _08[0x10 - 0x08];
};

static_assert(sizeof(ScriptCamRotZ) == 0x10, "");

} // namespace event
