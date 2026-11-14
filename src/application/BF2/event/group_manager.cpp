#include "event/group_manager.h"

namespace event {

GroupManager::GroupManager() : unknown10(0), unknown450(mm::Mat44::identity), unknown490(0.0f) {}

void GroupManager::push(const CharaObj *chara) { unknown20.push(chara); }

void GroupManager::pop(const CharaObj *chara) { unknown20.pop(chara); }

void GroupManager::clear() {
  unknown450 = mm::Mat44::identity;
  unknown490 = 0.0f;
  unknown20.clear();
}

void GroupManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown10 |= DISP_FLAG_UNKNOWN_0;
  } else {
    unknown10 &= ~DISP_FLAG_UNKNOWN_0;
  }
}

bool GroupManager::isDisp() const { return (unknown10 & DISP_FLAG_UNKNOWN_0) != 0; }

void GroupManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_4:
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

} // namespace event
