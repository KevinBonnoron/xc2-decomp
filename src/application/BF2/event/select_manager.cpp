#include "event/select_manager.h"

namespace event {

SelectManager::SelectManager() : unknown10(0), unknown14(0), unknown38(0), m_result(0) {}

void SelectManager::clear() {
  m_selectWindow.clear();
  unknown38 = 0;
  m_result = 0;
  unknown10 = 0;
  unknown14 = 0;
}

void SelectManager::update() {
  if (isActive()) {
    m_selectWindow.update();
  }
}

void SelectManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_4:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_12:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_14:
    update();
    break;
  default:
    break;
  }
}

int SelectManager::getResult() const { return m_result; }

bool SelectManager::isActive() const { return (unknown10 & FLAG_UNKNOWN_0) != 0; }

} // namespace event
