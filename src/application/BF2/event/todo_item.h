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

  f32 getFrame() const { return frame; }
  ITodo *getTodo() const { return mTodo; }
  void setTodo(ITodo *todo) { mTodo = todo; }
  const Param &getParam() const { return mParam; }

private:
  f32 frame;
  CREATE_FUNC mCreate;
  Param mParam;
  ITodo *mTodo;
};

static_assert(sizeof(TodoItem) == 0x118, "");

} // namespace event
