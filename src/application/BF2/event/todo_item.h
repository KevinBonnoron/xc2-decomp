#pragma once
#include "event/param.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class ITodo;

class TodoItem {
public:
  typedef ITodo *(*CREATE_FUNC)();

  TodoItem(f32 frame, CREATE_FUNC create, const Param &param, ITodo *todo) : unknown08(frame), unknown10(create), m_param(param), m_iTodo(todo) {}
  virtual ~TodoItem() {}
  void createString(mm::mtl::FixStr<256> &string);

  f32 getFrame() const { return unknown08; }
  ITodo *getTodo() const { return m_iTodo; }
  void setTodo(ITodo *todo) { m_iTodo = todo; }
  const Param &getParam() const { return m_param; }

private:
  f32 unknown08;         // Inferred role: frame; original member name unknown.
  CREATE_FUNC unknown10; // Inferred role: create; original member name unknown.
  Param m_param;         // Inferred role: param; original member name unknown.
  ITodo *m_iTodo;        // Inferred role: todo; original member name unknown.
};

static_assert(sizeof(TodoItem) == 0x118, "");

} // namespace event
