#include "event/group_manager.h"

namespace event {

GroupManager::GroupManager() : dispFlags(0), mMatrix(mm::Mat44::identity), mRadius(0.0f) {}

void GroupManager::push(const CharaObj *chara) { mGroup.push(chara); }

void GroupManager::pop(const CharaObj *chara) { mGroup.pop(chara); }

void GroupManager::clear() {
  mMatrix = mm::Mat44::identity;
  mRadius = 0.0f;
  mGroup.clear();
}

void GroupManager::setDisp(bool isDisp) {
  if (isDisp) {
    dispFlags |= DISP_FLAG_DISP;
  } else {
    dispFlags &= ~DISP_FLAG_DISP;
  }
}

bool GroupManager::isDisp() const { return (dispFlags & DISP_FLAG_DISP) != 0; }

void GroupManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
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

} // namespace event
