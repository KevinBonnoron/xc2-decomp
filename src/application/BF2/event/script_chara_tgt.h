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
  bool unknown08;    // Inferred role: prev tar; original member name unknown.
  TarAxis unknown10; // Inferred role: prev axis; original member name unknown.
};

static_assert(sizeof(ScriptCharaTgt) == 0x30, "");

} // namespace event
