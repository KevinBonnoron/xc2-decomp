#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCharaHead : public ITodo {
public:
  ScriptCharaHead() : mPrevId(0) {}
  static ITodo *exec();
  virtual ~ScriptCharaHead() {}
  virtual const char *cmdName() const { return "charahead"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param);

private:
  int mPrevId;
};

static_assert(sizeof(ScriptCharaHead) == 0x10, "");

} // namespace event
