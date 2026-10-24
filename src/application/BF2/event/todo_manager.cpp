#include "event/todo_manager.h"

#include "event/i_todo.h"

namespace event {

TodoManager::TodoManager() : unknown10(0), unknown14(0), unknown8c20(0) {}

void TodoManager::doit() {
  size_t index = unknown8c20;
  unknown18[index].getTodo()->doit(unknown18[index].getParam());
  unknown8c20++;
}

void TodoManager::undo() {
  if (unknown8c20 == 0) {
    return;
  }
  size_t index = --unknown8c20;
  unknown18[index].getTodo()->undo(unknown18[index].getParam());
}

void TodoManager::redo() {
  if (unknown18.size() > unknown8c20) {
    unknown18[unknown8c20].getTodo()->redo(unknown18[unknown8c20].getParam());
    unknown8c20++;
  }
}

void TodoManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown14 |= FLAG_DISP;
  } else {
    unknown14 &= ~FLAG_DISP;
  }
}

bool TodoManager::isDisp() const { return (unknown14 & FLAG_DISP) != 0; }

} // namespace event
