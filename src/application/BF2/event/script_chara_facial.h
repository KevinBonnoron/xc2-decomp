#pragma once
#include "event/i_todo.h"

namespace event {

class ScriptCharaFacial : public ITodo {
public:
  ScriptCharaFacial() : mPrevId(0) {}
  static ITodo *exec();
  virtual ~ScriptCharaFacial() {}
  virtual const char *cmdName() const { return "charafacial"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param) { doit(param); }

private:
  int mPrevId;
};

static_assert(sizeof(ScriptCharaFacial) == 0x10, "");

} // namespace event
