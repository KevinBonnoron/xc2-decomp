#include "event/agelog_manager.h"

#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"

namespace event {

const char *AgelogManager::LOG_DIR = "C:/MonolithSoft/BF2/agelog";

AgelogManager::AgelogManager() : flags(0) {}

void AgelogManager::clear() { flags &= ~FLAG_ACTIVE; }

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

void AgelogManager::reserve(bool isReserve) {
  if (isReserve) {
    flags |= FLAG_RESERVE;
  } else {
    flags &= ~FLAG_RESERVE;
  }
}

void AgelogManager::stop() { flags &= ~FLAG_ACTIVE; }

} // namespace event
