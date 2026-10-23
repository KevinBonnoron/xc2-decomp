#include "event/cam_obj.h"

namespace event {

void CamObj::start() {}

void CamObj::end() {
  mCmdQueue.eraseAll();
  mMotion.stop();
}

void CamObj::render(const mm::Col4 &color) {
  if (mActive != nullptr) {
    mActive->render(color);
  }
}

void CamObj::tail() {
  if (mActive != nullptr) {
    mCmdQueue.update();
  }
}

} // namespace event
