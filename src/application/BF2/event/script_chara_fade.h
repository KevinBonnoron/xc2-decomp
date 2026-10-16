#pragma once
#include "event/i_todo.h"
#include "types.h"

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
  u8 _08[0x10 - 0x08];
};

static_assert(sizeof(ScriptCharaFade) == 0x10, "");

} // namespace event
