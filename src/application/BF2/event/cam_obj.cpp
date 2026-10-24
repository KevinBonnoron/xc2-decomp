#include "event/cam_obj.h"

namespace event {

void CamObj::start() {}

void CamObj::end() {
  unknownc78.eraseAll();
  unknownbb0.stop();
}

void CamObj::render(const mm::Col4 &color) {
  if (unknownc70 != nullptr) {
    unknownc70->render(color);
  }
}

void CamObj::tail() {
  if (unknownc70 != nullptr) {
    unknownc78.update();
  }
}

} // namespace event
