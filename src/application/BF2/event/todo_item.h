#pragma once
#include "event/param.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class ITodo;

class TodoItem {
public:
  typedef ITodo *(*CREATE_FUNC)();

  virtual ~TodoItem() {}
  void createString(mm::mtl::FixStr<256> &string);

  f32 getFrame() const { return unknown08; }
  ITodo *getTodo() const { return unknown110; }
  void setTodo(ITodo *todo) { unknown110 = todo; }
  const Param &getParam() const { return unknown18; }

private:
  f32 unknown08;         // Inferred role: frame; original member name unknown.
  CREATE_FUNC unknown10; // Inferred role: create; original member name unknown.
  Param unknown18;       // Inferred role: param; original member name unknown.
  ITodo *unknown110;     // Inferred role: todo; original member name unknown.
};

static_assert(sizeof(TodoItem) == 0x118, "");

} // namespace event
