#pragma once
#include <stddef.h>

#include "event/i_manager.h"
#include "event/todo_item.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class Param;

class TodoManager : public IManager, public mm::mtl::Singleton<TodoManager> {
public:
  static constexpr u32 ITEM_COUNT = 128;

  enum {
    FLAG_DISP = 1 << 0,
  };

  static Param s_zero;

  TodoManager();
  virtual ~TodoManager();
  void clear();
  void update();
  void render();
  void add(TodoItem::CREATE_FUNC create, const Param &param);
  void updateAdd();
  void doit();
  void insert(f32 frame, TodoItem::CREATE_FUNC create, const Param &param);
  size_t searchSp(f32 frame, bool isAfter);
  void undo();
  void redo();
  void undoredo(f32 frame, bool isDoit, bool isAfter);
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 unknown10;                                                      // Inferred role: state; original member name unknown.
  u32 unknown14;                                                      // Inferred role: flags; original member name unknown.
  mm::mtl::FixedVector<TodoItem, ITEM_COUNT> unknown18;               // Inferred role: items; original member name unknown.
  size_t unknown8c20;                                                 // Inferred role: current; original member name unknown.
  mm::mtl::FixedVector<mm::mtl::FixStr<256>, ITEM_COUNT> unknown8c28; // Inferred role: lines; original member name unknown.
};

static_assert(sizeof(TodoManager) == 0x10e30, "");

} // namespace event
