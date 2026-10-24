#include "event/todo_item.h"

#include "event/i_todo.h"
#include "mm_mtl/fixstr.h"

namespace event {

void TodoItem::createString(mm::mtl::FixStr<256> &string) {
  mm::mtl::FixStr<256> work;
  work.format("%d", static_cast<int>(unknown08));
  string += work.c_str();
  string += " ";
  string += unknown110->cmdName();
  string += " ";
  unknown18.createString(work);
  string += work.c_str();
}

} // namespace event
