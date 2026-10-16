#pragma once
#include "event/i_todo.h"
#include "mm_mtl/fixstr.h"

namespace event {

class ScriptCamCut : public ITodo {
public:
  static ITodo *exec();
  virtual ~ScriptCamCut() {}
  virtual const char *cmdName() const { return "camcut"; }
  virtual void doit(const Param &param);
  virtual void undo(const Param &param);
  virtual void redo(const Param &param) { doit(param); }

private:
  mm::mtl::FixStr<64> mPrevCutName;
};

static_assert(sizeof(ScriptCamCut) == 0x50, "");

} // namespace event
