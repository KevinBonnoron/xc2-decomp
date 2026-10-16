#include "event/todo_manager.h"

#include "event/i_todo.h"

namespace event {

TodoManager::TodoManager() : state(0), flags(0), mCurrent(0) {}

void TodoManager::doit() {
  size_t index = mCurrent;
  mItems[index].getTodo()->doit(mItems[index].getParam());
  mCurrent++;
}

void TodoManager::undo() {
  if (mCurrent == 0) {
    return;
  }
  size_t index = --mCurrent;
  mItems[index].getTodo()->undo(mItems[index].getParam());
}

void TodoManager::redo() {
  if (mItems.size() > mCurrent) {
    mItems[mCurrent].getTodo()->redo(mItems[mCurrent].getParam());
    mCurrent++;
  }
}

void TodoManager::setDisp(bool isDisp) {
  if (isDisp) {
    flags |= FLAG_DISP;
  } else {
    flags &= ~FLAG_DISP;
  }
}

bool TodoManager::isDisp() const { return (flags & FLAG_DISP) != 0; }

} // namespace event
