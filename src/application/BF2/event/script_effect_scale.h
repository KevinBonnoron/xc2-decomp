#pragma once
#include "event/i_todo.h"
#include "types.h"

namespace event {

class ScriptEffectScale : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptEffectScale() {}
  virtual const char *cmdName() const { return "effscale"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param);

private:
  u8 _08[0x20 - 0x08];
};

static_assert(sizeof(ScriptEffectScale) == 0x20, "");

} // namespace event
