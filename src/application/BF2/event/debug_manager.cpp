#include "event/debug_manager.h"

#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include <stdarg.h>
#include <stdio.h>

namespace event {

constexpr s32 MESSAGE_DISP_UNKNOWN_90 = 90; // Inferred role: message disp frames; original name unknown.
constexpr s32 SIGHT_UNKNOWN_30 = 30;        // Inferred role: sight margin; original name unknown.

DebugManager::DebugManager() : unknown10(0), m_dispSight(SIGHT_UNKNOWN_0) {}

void DebugManager::update() {
  if (unknown10 & FLAG_UNKNOWN_1) {
    if (unknown118-- <= 0) {
      unknown10 &= ~FLAG_UNKNOWN_1;
    }
  }
  if (unknown10 & FLAG_UNKNOWN_2) {
    if (unknown220-- <= 0) {
      unknown10 &= ~FLAG_UNKNOWN_2;
    }
  }
}

void DebugManager::render() {
  if (!(unknown10 & FLAG_UNKNOWN_0)) {
    return;
  }
  if (unknown10 & FLAG_UNKNOWN_1) {
    s32 x = ml::DevGraph::getRootWidth() - 320;
    s32 y = ml::DevGraph::getRootHeight() - 150;
    fw::debug::drawSquare2D(mm::Rect<s32>(x, y, 300, 25), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
    fw::debug::drawLineSquare2D(mm::Rect<s32>(x, y, 300, 25), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFont(x + 5, y + 5, unknown14.c_str());
  }
  if (unknown10 & FLAG_UNKNOWN_2) {
    s32 x = ml::DevGraph::getRootWidth() - 520;
    s32 y = ml::DevGraph::getRootHeight() - 90;
    fw::debug::drawSquare2D(mm::Rect<s32>(x, y, 500, 25), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
    fw::debug::drawLineSquare2D(mm::Rect<s32>(x, y, 500, 25), mm::Col4(0.8f, 1.0f, 0.8f, 1.0f));
    fw::debug::drawFontColor(mm::Col4(0.8f, 1.0f, 0.8f, 1.0f));
    fw::debug::drawFont(x + 5, y + 5, unknown11c.c_str());
  }
  if (m_dispSight < SIGHT_UNKNOWN_1) {
    return;
  }
  switch (m_dispSight) {
  case SIGHT_UNKNOWN_1: {
    s32 startX = SIGHT_UNKNOWN_30;
    s32 startY = ml::DevGraph::getRootHeight() >> 1;
    s32 endX = ml::DevGraph::getRootWidth() - SIGHT_UNKNOWN_30;
    s32 endY = ml::DevGraph::getRootHeight() >> 1;
    fw::debug::drawLine2D(mm::Pnt<s32>(startX, startY), mm::Pnt<s32>(endX, endY), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawLine2D(mm::Pnt<s32>(startX + 1, startY + 1), mm::Pnt<s32>(endX + 1, endY + 1), mm::Col4(0.0f, 0.0f, 0.0f, 1.0f));
    s32 startX2 = ml::DevGraph::getRootWidth() >> 1;
    s32 startY2 = SIGHT_UNKNOWN_30;
    s32 endX2 = ml::DevGraph::getRootWidth() >> 1;
    s32 endY2 = ml::DevGraph::getRootHeight() - SIGHT_UNKNOWN_30;
    fw::debug::drawLine2D(mm::Pnt<s32>(startX2, startY2), mm::Pnt<s32>(endX2, endY2), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawLine2D(mm::Pnt<s32>(startX2 + 1, startY2 + 1), mm::Pnt<s32>(endX2 + 1, endY2 + 1), mm::Col4(0.0f, 0.0f, 0.0f, 1.0f));
    break;
  }
  case SIGHT_UNKNOWN_2: {
    s32 startX = SIGHT_UNKNOWN_30;
    s32 startY = ml::DevGraph::getRootHeight() / 3;
    s32 endX = ml::DevGraph::getRootWidth() - SIGHT_UNKNOWN_30;
    s32 endY = ml::DevGraph::getRootHeight() / 3;
    fw::debug::drawLine2D(mm::Pnt<s32>(startX, startY), mm::Pnt<s32>(endX, endY), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawLine2D(mm::Pnt<s32>(startX + 1, startY + 1), mm::Pnt<s32>(endX + 1, endY + 1), mm::Col4(0.0f, 0.0f, 0.0f, 1.0f));
    s32 startX2 = SIGHT_UNKNOWN_30;
    s32 startY2 = ml::DevGraph::getRootHeight() * 2 / 3;
    s32 endX2 = ml::DevGraph::getRootWidth() - SIGHT_UNKNOWN_30;
    s32 endY2 = ml::DevGraph::getRootHeight() * 2 / 3;
    fw::debug::drawLine2D(mm::Pnt<s32>(startX2, startY2), mm::Pnt<s32>(endX2, endY2), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawLine2D(mm::Pnt<s32>(startX2 + 1, startY2 + 1), mm::Pnt<s32>(endX2 + 1, endY2 + 1), mm::Col4(0.0f, 0.0f, 0.0f, 1.0f));
    s32 startX3 = ml::DevGraph::getRootWidth() / 3;
    s32 startY3 = SIGHT_UNKNOWN_30;
    s32 endX3 = ml::DevGraph::getRootWidth() / 3;
    s32 endY3 = ml::DevGraph::getRootHeight() - SIGHT_UNKNOWN_30;
    fw::debug::drawLine2D(mm::Pnt<s32>(startX3, startY3), mm::Pnt<s32>(endX3, endY3), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawLine2D(mm::Pnt<s32>(startX3 + 1, startY3 + 1), mm::Pnt<s32>(endX3 + 1, endY3 + 1), mm::Col4(0.0f, 0.0f, 0.0f, 1.0f));
    s32 startX4 = ml::DevGraph::getRootWidth() * 2 / 3;
    s32 startY4 = SIGHT_UNKNOWN_30;
    s32 endX4 = ml::DevGraph::getRootWidth() * 2 / 3;
    s32 endY4 = ml::DevGraph::getRootHeight() - SIGHT_UNKNOWN_30;
    fw::debug::drawLine2D(mm::Pnt<s32>(startX4, startY4), mm::Pnt<s32>(endX4, endY4), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawLine2D(mm::Pnt<s32>(startX4 + 1, startY4 + 1), mm::Pnt<s32>(endX4 + 1, endY4 + 1), mm::Col4(0.0f, 0.0f, 0.0f, 1.0f));
    break;
  }
  default:
    break;
  }
}

void DebugManager::tail() {
  if (unknown10 & FLAG_UNKNOWN_14) {
    unknown10 &= ~(FLAG_UNKNOWN_13 | FLAG_UNKNOWN_14);
  }
}

void DebugManager::playMessage(const char *format, ...) {
  char buffer[512];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  unknown14 = buffer;
  unknown118 = MESSAGE_DISP_UNKNOWN_90;
  unknown10 |= FLAG_UNKNOWN_1;
}

void DebugManager::playWarning(const char *format, ...) {
  char buffer[512];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  unknown11c = buffer;
  unknown220 = MESSAGE_DISP_UNKNOWN_90;
  unknown10 |= FLAG_UNKNOWN_2;
}

void DebugManager::setPlayOnetime(bool isPlayOnetime) { setFlag(FLAG_UNKNOWN_3, isPlayOnetime); }

bool DebugManager::isPlayOnetime() const { return (unknown10 & FLAG_UNKNOWN_3) != 0; }

void DebugManager::setPlayCancel(bool isPlayCancel) { setFlag(FLAG_UNKNOWN_4, isPlayCancel); }

bool DebugManager::isPlayCancel() const { return (unknown10 & FLAG_UNKNOWN_4) != 0; }

void DebugManager::setFastSkipDisable(bool isDisable) { setFlag(FLAG_UNKNOWN_5, isDisable); }

bool DebugManager::isFastSkipDisable() const { return (unknown10 & FLAG_UNKNOWN_5) != 0; }

void DebugManager::setFastSkipEnableOneTime(bool isEnable) { setFlag(FLAG_UNKNOWN_6, isEnable); }

bool DebugManager::isFastSkipEnableOneTime() const { return (unknown10 & FLAG_UNKNOWN_6) != 0; }

void DebugManager::setAgeingSkipEnable(bool isEnable) { setFlag(FLAG_UNKNOWN_7, isEnable); }

bool DebugManager::isAgeingSkip() const { return (unknown10 & FLAG_UNKNOWN_7) != 0; }

void DebugManager::failureSkip() { unknown10 |= FLAG_UNKNOWN_8; }

bool DebugManager::isFailureSkip() const { return (unknown10 & FLAG_UNKNOWN_8) != 0; }

void DebugManager::setDisableBgm(bool isDisable) { setFlag(FLAG_UNKNOWN_9, isDisable); }

bool DebugManager::isDisableBgm() const { return (unknown10 & FLAG_UNKNOWN_9) != 0; }

void DebugManager::setReplaceDefaultEquip(bool isReplace, u32 slot, u32 item) {
  if (slot > 0 && slot < EQUIP_SLOT_UNKNOWN_16) {
    unknown228[slot] = isReplace ? item : 0;
  }
}

bool DebugManager::isReplaceDefaultEquip(u32 slot, u32 *item) {
  if (slot > 0 && slot < EQUIP_SLOT_UNKNOWN_16) {
    u32 replace = unknown228[slot];
    if (replace != 0) {
      if (item != nullptr) {
        *item = replace;
      }
      return true;
    }
  }
  return false;
}

void DebugManager::setReplaceMaximumEquip(bool isReplace) { setFlag(FLAG_UNKNOWN_10, isReplace); }

bool DebugManager::isReplaceMaximumEquip() const { return (unknown10 & FLAG_UNKNOWN_10) != 0; }

void DebugManager::setReplaceMaximumBlade(bool isReplace) { setFlag(FLAG_UNKNOWN_11, isReplace); }

bool DebugManager::isReplaceMaximumBlade() const { return (unknown10 & FLAG_UNKNOWN_11) != 0; }

void DebugManager::setDisableNewGameWait(bool isDisable) { setFlag(FLAG_UNKNOWN_12, isDisable); }

bool DebugManager::isDisableNewGameWait() const { return (unknown10 & FLAG_UNKNOWN_12) != 0; }

void DebugManager::setSyncFreeCam(bool isSync, bool isOneTime) {
  setFlag(FLAG_UNKNOWN_13, isSync);
  setFlag(FLAG_UNKNOWN_14, isOneTime);
}

bool DebugManager::isSyncFreeCam() const { return (unknown10 & FLAG_UNKNOWN_13) != 0; }

void DebugManager::setDisp(bool isDisp) { setFlag(FLAG_UNKNOWN_0, isDisp); }

bool DebugManager::isDisp() const { return (unknown10 & FLAG_UNKNOWN_0) != 0; }

void DebugManager::setDispSight(int sight) { m_dispSight = sight; }

int DebugManager::getDispSight() const { return m_dispSight; }

void DebugManager::setDisableReuse(bool isDisable) { setFlag(FLAG_UNKNOWN_15, isDisable); }

bool DebugManager::isDisableReuse() const { return (unknown10 & FLAG_UNKNOWN_15) != 0; }

void DebugManager::setMovieDebug(bool isMovieDebug) { setFlag(FLAG_UNKNOWN_16, isMovieDebug); }

bool DebugManager::isMovieDebug() const { return (unknown10 & FLAG_UNKNOWN_16) != 0; }

void DebugManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_4:
    unknown10 &= ~(FLAG_UNKNOWN_4 | FLAG_UNKNOWN_6 | FLAG_UNKNOWN_8);
    break;
  case MSG_TYPE_UNKNOWN_15:
    update();
    break;
  case MSG_TYPE_UNKNOWN_17:
    render();
    break;
  case MSG_TYPE_UNKNOWN_19:
    tail();
    break;
  default:
    break;
  }
}

} // namespace event
