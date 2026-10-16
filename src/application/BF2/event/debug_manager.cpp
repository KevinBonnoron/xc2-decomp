#include "event/debug_manager.h"

#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include <stdarg.h>
#include <stdio.h>

namespace event {

constexpr s32 MESSAGE_DISP_FRAMES = 90;
constexpr s32 SIGHT_MARGIN = 30;

DebugManager::DebugManager() : flags(0), mDispSight(SIGHT_NONE) {}

void DebugManager::update() {
  if (flags & FLAG_MESSAGE) {
    if (mMessageTimer-- <= 0) {
      flags &= ~FLAG_MESSAGE;
    }
  }
  if (flags & FLAG_WARNING) {
    if (mWarningTimer-- <= 0) {
      flags &= ~FLAG_WARNING;
    }
  }
}

void DebugManager::render() {
  if (!(flags & FLAG_DISP)) {
    return;
  }
  if (flags & FLAG_MESSAGE) {
    s32 x = ml::DevGraph::getRootWidth() - 320;
    s32 y = ml::DevGraph::getRootHeight() - 150;
    fw::debug::drawSquare2D(mm::Rect<s32>(x, y, 300, 25), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
    fw::debug::drawLineSquare2D(mm::Rect<s32>(x, y, 300, 25), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFont(x + 5, y + 5, mMessage.c_str());
  }
  if (flags & FLAG_WARNING) {
    s32 x = ml::DevGraph::getRootWidth() - 520;
    s32 y = ml::DevGraph::getRootHeight() - 90;
    fw::debug::drawSquare2D(mm::Rect<s32>(x, y, 500, 25), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
    fw::debug::drawLineSquare2D(mm::Rect<s32>(x, y, 500, 25), mm::Col4(0.8f, 1.0f, 0.8f, 1.0f));
    fw::debug::drawFontColor(mm::Col4(0.8f, 1.0f, 0.8f, 1.0f));
    fw::debug::drawFont(x + 5, y + 5, mWarning.c_str());
  }
  if (mDispSight < SIGHT_CROSS) {
    return;
  }
  switch (mDispSight) {
  case SIGHT_CROSS: {
    s32 startX = SIGHT_MARGIN;
    s32 startY = ml::DevGraph::getRootHeight() >> 1;
    s32 endX = ml::DevGraph::getRootWidth() - SIGHT_MARGIN;
    s32 endY = ml::DevGraph::getRootHeight() >> 1;
    fw::debug::drawLine2D(mm::Pnt<s32>(startX, startY), mm::Pnt<s32>(endX, endY), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawLine2D(mm::Pnt<s32>(startX + 1, startY + 1), mm::Pnt<s32>(endX + 1, endY + 1), mm::Col4(0.0f, 0.0f, 0.0f, 1.0f));
    s32 startX2 = ml::DevGraph::getRootWidth() >> 1;
    s32 startY2 = SIGHT_MARGIN;
    s32 endX2 = ml::DevGraph::getRootWidth() >> 1;
    s32 endY2 = ml::DevGraph::getRootHeight() - SIGHT_MARGIN;
    fw::debug::drawLine2D(mm::Pnt<s32>(startX2, startY2), mm::Pnt<s32>(endX2, endY2), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawLine2D(mm::Pnt<s32>(startX2 + 1, startY2 + 1), mm::Pnt<s32>(endX2 + 1, endY2 + 1), mm::Col4(0.0f, 0.0f, 0.0f, 1.0f));
    break;
  }
  case SIGHT_THIRDS: {
    s32 startX = SIGHT_MARGIN;
    s32 startY = ml::DevGraph::getRootHeight() / 3;
    s32 endX = ml::DevGraph::getRootWidth() - SIGHT_MARGIN;
    s32 endY = ml::DevGraph::getRootHeight() / 3;
    fw::debug::drawLine2D(mm::Pnt<s32>(startX, startY), mm::Pnt<s32>(endX, endY), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawLine2D(mm::Pnt<s32>(startX + 1, startY + 1), mm::Pnt<s32>(endX + 1, endY + 1), mm::Col4(0.0f, 0.0f, 0.0f, 1.0f));
    s32 startX2 = SIGHT_MARGIN;
    s32 startY2 = ml::DevGraph::getRootHeight() * 2 / 3;
    s32 endX2 = ml::DevGraph::getRootWidth() - SIGHT_MARGIN;
    s32 endY2 = ml::DevGraph::getRootHeight() * 2 / 3;
    fw::debug::drawLine2D(mm::Pnt<s32>(startX2, startY2), mm::Pnt<s32>(endX2, endY2), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawLine2D(mm::Pnt<s32>(startX2 + 1, startY2 + 1), mm::Pnt<s32>(endX2 + 1, endY2 + 1), mm::Col4(0.0f, 0.0f, 0.0f, 1.0f));
    s32 startX3 = ml::DevGraph::getRootWidth() / 3;
    s32 startY3 = SIGHT_MARGIN;
    s32 endX3 = ml::DevGraph::getRootWidth() / 3;
    s32 endY3 = ml::DevGraph::getRootHeight() - SIGHT_MARGIN;
    fw::debug::drawLine2D(mm::Pnt<s32>(startX3, startY3), mm::Pnt<s32>(endX3, endY3), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawLine2D(mm::Pnt<s32>(startX3 + 1, startY3 + 1), mm::Pnt<s32>(endX3 + 1, endY3 + 1), mm::Col4(0.0f, 0.0f, 0.0f, 1.0f));
    s32 startX4 = ml::DevGraph::getRootWidth() * 2 / 3;
    s32 startY4 = SIGHT_MARGIN;
    s32 endX4 = ml::DevGraph::getRootWidth() * 2 / 3;
    s32 endY4 = ml::DevGraph::getRootHeight() - SIGHT_MARGIN;
    fw::debug::drawLine2D(mm::Pnt<s32>(startX4, startY4), mm::Pnt<s32>(endX4, endY4), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawLine2D(mm::Pnt<s32>(startX4 + 1, startY4 + 1), mm::Pnt<s32>(endX4 + 1, endY4 + 1), mm::Col4(0.0f, 0.0f, 0.0f, 1.0f));
    break;
  }
  default:
    break;
  }
}

void DebugManager::tail() {
  if (flags & FLAG_SYNC_FREE_CAM_ONE_TIME) {
    flags &= ~(FLAG_SYNC_FREE_CAM | FLAG_SYNC_FREE_CAM_ONE_TIME);
  }
}

void DebugManager::playMessage(const char *format, ...) {
  char buffer[512];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  mMessage = buffer;
  mMessageTimer = MESSAGE_DISP_FRAMES;
  flags |= FLAG_MESSAGE;
}

void DebugManager::playWarning(const char *format, ...) {
  char buffer[512];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  mWarning = buffer;
  mWarningTimer = MESSAGE_DISP_FRAMES;
  flags |= FLAG_WARNING;
}

void DebugManager::setPlayOnetime(bool isPlayOnetime) { setFlag(FLAG_PLAY_ONETIME, isPlayOnetime); }

bool DebugManager::isPlayOnetime() const { return (flags & FLAG_PLAY_ONETIME) != 0; }

void DebugManager::setPlayCancel(bool isPlayCancel) { setFlag(FLAG_PLAY_CANCEL, isPlayCancel); }

bool DebugManager::isPlayCancel() const { return (flags & FLAG_PLAY_CANCEL) != 0; }

void DebugManager::setFastSkipDisable(bool isDisable) { setFlag(FLAG_FAST_SKIP_DISABLE, isDisable); }

bool DebugManager::isFastSkipDisable() const { return (flags & FLAG_FAST_SKIP_DISABLE) != 0; }

void DebugManager::setFastSkipEnableOneTime(bool isEnable) { setFlag(FLAG_FAST_SKIP_ENABLE_ONE_TIME, isEnable); }

bool DebugManager::isFastSkipEnableOneTime() const { return (flags & FLAG_FAST_SKIP_ENABLE_ONE_TIME) != 0; }

void DebugManager::setAgeingSkipEnable(bool isEnable) { setFlag(FLAG_AGEING_SKIP_ENABLE, isEnable); }

bool DebugManager::isAgeingSkip() const { return (flags & FLAG_AGEING_SKIP_ENABLE) != 0; }

void DebugManager::failureSkip() { flags |= FLAG_FAILURE_SKIP; }

bool DebugManager::isFailureSkip() const { return (flags & FLAG_FAILURE_SKIP) != 0; }

void DebugManager::setDisableBgm(bool isDisable) { setFlag(FLAG_DISABLE_BGM, isDisable); }

bool DebugManager::isDisableBgm() const { return (flags & FLAG_DISABLE_BGM) != 0; }

void DebugManager::setReplaceDefaultEquip(bool isReplace, u32 slot, u32 item) {
  if (slot > 0 && slot < EQUIP_SLOT_COUNT) {
    mReplaceDefaultEquips[slot] = isReplace ? item : 0;
  }
}

bool DebugManager::isReplaceDefaultEquip(u32 slot, u32 *item) {
  if (slot > 0 && slot < EQUIP_SLOT_COUNT) {
    u32 replace = mReplaceDefaultEquips[slot];
    if (replace != 0) {
      if (item != nullptr) {
        *item = replace;
      }
      return true;
    }
  }
  return false;
}

void DebugManager::setReplaceMaximumEquip(bool isReplace) { setFlag(FLAG_REPLACE_MAXIMUM_EQUIP, isReplace); }

bool DebugManager::isReplaceMaximumEquip() const { return (flags & FLAG_REPLACE_MAXIMUM_EQUIP) != 0; }

void DebugManager::setReplaceMaximumBlade(bool isReplace) { setFlag(FLAG_REPLACE_MAXIMUM_BLADE, isReplace); }

bool DebugManager::isReplaceMaximumBlade() const { return (flags & FLAG_REPLACE_MAXIMUM_BLADE) != 0; }

void DebugManager::setDisableNewGameWait(bool isDisable) { setFlag(FLAG_DISABLE_NEW_GAME_WAIT, isDisable); }

bool DebugManager::isDisableNewGameWait() const { return (flags & FLAG_DISABLE_NEW_GAME_WAIT) != 0; }

void DebugManager::setSyncFreeCam(bool isSync, bool isOneTime) {
  setFlag(FLAG_SYNC_FREE_CAM, isSync);
  setFlag(FLAG_SYNC_FREE_CAM_ONE_TIME, isOneTime);
}

bool DebugManager::isSyncFreeCam() const { return (flags & FLAG_SYNC_FREE_CAM) != 0; }

void DebugManager::setDisp(bool isDisp) { setFlag(FLAG_DISP, isDisp); }

bool DebugManager::isDisp() const { return (flags & FLAG_DISP) != 0; }

void DebugManager::setDispSight(int sight) { mDispSight = sight; }

int DebugManager::getDispSight() const { return mDispSight; }

void DebugManager::setDisableReuse(bool isDisable) { setFlag(FLAG_DISABLE_REUSE, isDisable); }

bool DebugManager::isDisableReuse() const { return (flags & FLAG_DISABLE_REUSE) != 0; }

void DebugManager::setMovieDebug(bool isMovieDebug) { setFlag(FLAG_MOVIE_DEBUG, isMovieDebug); }

bool DebugManager::isMovieDebug() const { return (flags & FLAG_MOVIE_DEBUG) != 0; }

void DebugManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    flags &= ~(FLAG_PLAY_CANCEL | FLAG_FAST_SKIP_ENABLE_ONE_TIME | FLAG_FAILURE_SKIP);
    break;
  case MSG_TYPE_UPDATE_POST:
    update();
    break;
  case MSG_TYPE_RENDER_POST:
    render();
    break;
  case MSG_TYPE_TAIL_POST:
    tail();
    break;
  default:
    break;
  }
}

} // namespace event
