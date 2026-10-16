#pragma once
#include "event/i_todo.h"
#include "types.h"

namespace event {

class ScriptEffectColor : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptEffectColor() {}
  virtual const char *cmdName() const { return "effcol"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param);

private:
  u8 _08[0x18 - 0x08];
};

static_assert(sizeof(ScriptEffectColor) == 0x18, "");

} // namespace event
