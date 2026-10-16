#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptEffectAnim : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptEffectAnim() {}
  virtual const char *cmdName() const { return "effanim"; }
  virtual void doit(const Param &param);
};

static_assert(sizeof(ScriptEffectAnim) == 0x8, "");

} // namespace event
