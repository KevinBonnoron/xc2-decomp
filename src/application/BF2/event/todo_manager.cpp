#include "event/todo_manager.h"

#include "event/frame_manager.h"
#include "event/i_todo.h"
#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_math.h"
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

// The countdown `for (int i = size; i-- > 0;)` keeps the 64-bit counter that the game's copy inlined in undoredo (1.0.0: 0x710010d04c) decrements with
// `subs; b.lt`; `for (int i = size; i > 0; i--)` with `[i - 1]` gives the same standalone function (69 instructions) but 169 to 172 in undoredo.
size_t TodoManager::searchSp(f32 frame, bool isAfter) {
  if (unknown18.empty()) {
    return 0;
  }
  if (isAfter) {
    for (int i = unknown18.size(); i-- > 0;) {
      if (unknown18[i].getFrame() <= frame) {
        return i + 1;
      }
    }
  } else {
    for (int i = unknown18.size(); i-- > 0;) {
      if (unknown18[i].getFrame() < frame) {
        return i + 1;
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

void TodoManager::add(TodoItem::CREATE_FUNC create, const Param &param) {
  f32 frame = mm::mtl::Singleton<FrameManager>::getPtr()->getFrame();
  updateAdd();
  ITodo *todo = create();
  unknown18.push_back(TodoItem(frame, create, param, todo));
  doit();
}

void TodoManager::updateAdd() {
  while (unknown8c20 < unknown18.size()) {
    size_t last = unknown18.size() - 1;
    size_t index = 0;
    for (TodoItem *it = unknown18.begin(); it != unknown18.end(); ++it, ++index) {
      if (index == last) {
        if (it->getTodo() != nullptr) {
          delete it->getTodo();
          it->setTodo(nullptr);
        }
        unknown18.erase(it);
        break;
      }
    }
  }
  while (unknown18.capacity() <= unknown18.size()) {
    TodoItem *item = unknown18.begin();
    if (item->getTodo() != nullptr) {
      delete item->getTodo();
      item->setTodo(nullptr);
    }
    unknown8c20--;
    unknown18.erase(item);
  }
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

// The undo loop is written with the target on the left (`target < current`): the game compares `cmp target, current; b.hs` there (0x710010d04c).
void TodoManager::undoredo(f32 frame, bool isDoit, bool isAfter) {
  size_t target = searchSp(frame, isAfter);
  target = mm::min(target, unknown18.size());
  while (target < unknown8c20) {
    undo();
  }
  if (isDoit) {
    while (unknown8c20 < target) {
      doit();
    }
  } else {
    while (unknown8c20 < target) {
      redo();
    }
  }
}

void TodoManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_4:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_7:
  case MSG_TYPE_UNKNOWN_8:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_12:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_14:
    update();
    break;
  case MSG_TYPE_UNKNOWN_16:
    render();
    break;
  default:
    break;
  }
}

void TodoManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown14 |= FLAG_UNKNOWN_0;
  } else {
    unknown14 &= ~FLAG_UNKNOWN_0;
  }
}

bool TodoManager::isDisp() const { return (unknown14 & FLAG_UNKNOWN_0) != 0; }

} // namespace event
