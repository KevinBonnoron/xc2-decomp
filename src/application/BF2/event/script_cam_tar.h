#pragma once
#include "event/i_todo.h"
#include "event/tar_axis.h"

namespace event {

class ScriptCamTar : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCamTar() {}
  virtual const char *cmdName() const { return "camtar"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param) { doit(param); }

private:
  TarAxis prevAxis;
};

static_assert(sizeof(ScriptCamTar) == 0x30, "");

} // namespace event
