#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCharaFade : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCharaFade() {}
  virtual const char *cmdName() const { return "charafade"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param);

private:
  bool isPrevFadeOut;
};

static_assert(sizeof(ScriptCharaFade) == 0x10, "");

} // namespace event
