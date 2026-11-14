#include "event/agelog_manager.h"

#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "ml/time_util.h"
#include "mm_math/mm_col4.h"

namespace event {

const char *AgelogManager::LOG_DIR = "C:/MonolithSoft/BF2/agelog";

AgelogManager::AgelogManager() : unknown10() {}

void AgelogManager::clear() { unknown10.set(FLAG_UNKNOWN_1, false); }

void AgelogManager::render() {
  if (!isReserved()) {
    return;
  }
  int height = ml::DevGraph::getRootHeight();
  int y = height - 100;
  int x = (ml::DevGraph::getRootWidth() >> 1) - 80;
  fw::debug::drawFontColor(mm::Col4::black);
  fw::debug::drawFont(x + 1, y + 1, "AGELOG RESERVING..");
  fw::debug::drawFontColor(mm::Col4::yellow);
  fw::debug::drawFont(x, y, "AGELOG RESERVING..");
  x = (ml::DevGraph::getRootWidth() >> 1) - 150;
  y = height - 80;
  fw::debug::drawFontColor(mm::Col4::black);
  fw::debug::drawFont(x + 1, y + 1, "agelog path[%s]", LOG_DIR);
  fw::debug::drawFontColor(mm::Col4::yellow);
  fw::debug::drawFont(x, y, "agelog path[%s]", LOG_DIR);
}

void AgelogManager::reserve(bool isReserve) { unknown10.set(FLAG_UNKNOWN_0, isReserve); }

void AgelogManager::start() {
  unknown10.set(FLAG_UNKNOWN_1);
  if (unknown14.c_str()[0] == '\0') {
    char dateName[64];
    mlGetDateName(dateName, 64);
    unknown14.format("%s/%s/agelog_%s.txt", LOG_DIR, "nx", dateName);
  }
}

void AgelogManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_7:
    if (isReserved()) {
      start();
    }
    break;
  case MSG_TYPE_UNKNOWN_10:
    if (unknown10.test(FLAG_UNKNOWN_1)) {
      stop();
    }
    break;
  case MSG_TYPE_UNKNOWN_12:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_17:
    render();
    break;
  default:
    break;
  }
}

void AgelogManager::stop() { unknown10.set(FLAG_UNKNOWN_1, false); }

} // namespace event
