#include "event/todo_manager.h"

#include "event/i_todo.h"
#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"

namespace event {

TodoManager::TodoManager() : unknown10(0), unknown14(0), unknown8c20(0) {}

TodoManager::~TodoManager() { clear(); }

void TodoManager::clear() {
  for (size_t i = 0; i < unknown18.size(); i++) {
    TodoItem *item = unknown18.at(i);
    if (item->getTodo() != nullptr) {
      delete item->getTodo();
      item->setTodo(nullptr);
    }
  }
  unknown18.clear();
  unknown8c20 = 0;
  unknown10 = 0;
}

size_t TodoManager::searchSp(f32 frame, bool isAfter) {
  if (unknown18.empty()) {
    return 0;
  }
  if (isAfter) {
    for (int i = unknown18.size(); i > 0; i--) {
      if (unknown18[i - 1].getFrame() <= frame) {
        return i;
      }
    }
  } else {
    for (int i = unknown18.size(); i > 0; i--) {
      if (unknown18[i - 1].getFrame() < frame) {
        return i;
      }
    }
  }
  return 0;
}

void TodoManager::update() {
  if (!isDisp()) {
    return;
  }
  unknown8c28.clear();
  for (size_t i = 0; i < unknown18.size(); i++) {
    if (unknown18.at(i)->getTodo() != nullptr) {
      mm::mtl::FixStr<256> string;
      unknown18[i].createString(string);
      unknown8c28.push_back(string);
    }
  }
}

void TodoManager::render() {
  if (!isDisp()) {
    return;
  }
  int width = ml::DevGraph::getRootWidth();
  fw::debug::drawSquare2D(mm::Rect<int>(width - 350, 200, 330, 265), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<int>(width - 350, 200, 330, 265), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(width - 345, 205, "TODO");
  size_t first = unknown8c28.size() > 16 ? unknown8c28.size() - 16 : 0;
  int y = 220;
  for (size_t i = first; i < unknown8c28.size(); i++) {
    if (unknown8c20 <= i) {
      fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 0.5f, 1.0f));
    }
    fw::debug::drawFont(width - 330, y, unknown8c28[i].c_str());
    y += 15;
  }
  unknown8c28.clear();
}

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

void TodoManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    clear();
    break;
  case MSG_TYPE_START_SCENE:
  case MSG_TYPE_START_PAGE:
    clear();
    break;
  case MSG_TYPE_CLEAR:
    clear();
    break;
  case MSG_TYPE_UPDATE:
    update();
    break;
  case MSG_TYPE_RENDER:
    render();
    break;
  default:
    break;
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
