#pragma once
#include "event/i_todo.h"
#include "event/tar_axis.h"

namespace event {

class ScriptCharaTgt : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCharaTgt() {}
  virtual const char *cmdName() const { return "charatgt"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param);

private:
  bool isPrevTar;
  TarAxis prevAxis;
};

static_assert(sizeof(ScriptCharaTgt) == 0x30, "");

} // namespace event
