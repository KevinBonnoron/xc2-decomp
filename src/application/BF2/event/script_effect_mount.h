#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptEffectMount : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptEffectMount() {}
  virtual const char *cmdName() const;
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param);
};

static_assert(sizeof(ScriptEffectMount) == 0x8, "");

} // namespace event
