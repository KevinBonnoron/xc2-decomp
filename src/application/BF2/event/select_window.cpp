#include "event/select_window.h"

namespace event {

SelectWindow::SelectWindow() : flags(), mResult(0), mContext(nullptr) {}

int SelectWindow::getResult() {
  if (!isOpen()) {
    return mResult;
  }
  return 0;
}

} // namespace event
