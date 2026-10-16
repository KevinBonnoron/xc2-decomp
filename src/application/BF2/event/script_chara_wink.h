#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCharaWink : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCharaWink() {}
  virtual const char *cmdName() const { return "charawink"; }
  virtual void doit(const Param &param);
  virtual void redo(const Param &param) { doit(param); }
};

static_assert(sizeof(ScriptCharaWink) == 0x8, "");

} // namespace event
