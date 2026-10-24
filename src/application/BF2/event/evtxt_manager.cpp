#include "event/evtxt_manager.h"

#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"

namespace event {

const char *EvtxtManager::EVTXT_PATH = "C:/MonolithSoft/BF2/evtxt";

EvtxtManager::EvtxtManager() : unknown10(0) {}

void EvtxtManager::render() {
  if (!isReserve()) {
    return;
  }
  s32 height = ml::DevGraph::getRootHeight();
  s32 y = height - 100;
  s32 x = (ml::DevGraph::getRootWidth() >> 1) + 240;
  fw::debug::drawFontColor(mm::Col4::black);
  fw::debug::drawFont(x + 1, y + 1, "POS RESERVING..");
  fw::debug::drawFontColor(mm::Col4::yellow);
  fw::debug::drawFont(x, y, "POS RESERVING..");
  x = (ml::DevGraph::getRootWidth() >> 1) + 170;
  y = height - 75;
  fw::debug::drawFontColor(mm::Col4::black);
  fw::debug::drawFont(x + 1, y + 1, "pos path[%s]", EVTXT_PATH);
  fw::debug::drawFontColor(mm::Col4::yellow);
  fw::debug::drawFont(x, y, "pos path[%s]", EVTXT_PATH);
}

void EvtxtManager::write() {}

void EvtxtManager::reserve(bool isReserve) {
  if (isReserve) {
    unknown10 |= FLAG_RESERVE;
  } else {
    unknown10 &= ~FLAG_RESERVE;
  }
}

bool EvtxtManager::isReserve() const { return (unknown10 & FLAG_RESERVE) != 0; }

void EvtxtManager::OnEventProc(MSG_TYPE type) {
  if (type == MSG_TYPE_RENDER_POST) {
    render();
  }
}

} // namespace event
