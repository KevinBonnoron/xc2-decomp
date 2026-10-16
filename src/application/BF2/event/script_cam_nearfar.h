#pragma once
#include "event/i_todo.h"
#include "types.h"

namespace event {

class ScriptCamNearfar : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCamNearfar() {}
  virtual const char *cmdName() const { return "camnearfar"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param) { doit(param); }

private:
  f32 prevNear;
  f32 prevFar;
};

static_assert(sizeof(ScriptCamNearfar) == 0x10, "");

} // namespace event
