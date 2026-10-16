#pragma once
#include "event/i_todo.h"
#include "types.h"

namespace event {

class ScriptCamFov : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCamFov() {}
  virtual const char *cmdName() const { return "camfov"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param) { doit(param); }

private:
  u8 _08[0x10 - 0x08];
};

static_assert(sizeof(ScriptCamFov) == 0x10, "");

} // namespace event
