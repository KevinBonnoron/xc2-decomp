#pragma once
#include "event/i_todo.h"
#include "mm_math/mm_col4.h"

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
  mm::Col4 prevColor;
};

static_assert(sizeof(ScriptEffectColor) == 0x18, "");

} // namespace event
