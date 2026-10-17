#pragma once
#include "event/i_todo.h"
#include "mm_math/mm_vec3.h"

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
  mm::Vec3 prevScale;
};

static_assert(sizeof(ScriptEffectScale) == 0x20, "");

} // namespace event
