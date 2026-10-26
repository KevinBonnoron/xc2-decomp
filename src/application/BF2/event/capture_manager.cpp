#include "event/capture_manager.h"

#include "event/env_manager.h"
#include "event/fade_ctrl.h"
#include "event/fade_manager.h"
#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"

namespace event {

const char *CaptureManager::MOV_PATH = "C:/MonolithSoft/BF2/movie";
const char *CaptureManager::MOV_PATH_OFS = "../../movie";
const char *CaptureManager::JPG_PATH = "C:/MonolithSoft/BF2/jpeg";
const char *CaptureManager::JPG_PATH_OFS = "../../jpeg";
const char *CaptureManager::CONV_PATH = "C:/Monolithsoft/BF2/execute/bf2tools/event/bmp2avi/bmp2avi";

CaptureManager::CaptureManager() : unknown10(0), unknown14(MODE_MOVIE), unknown18(0) {}

void CaptureManager::clear() {
  if ((unknown10 & FLAG_CAPTURE) != 0) {
    stop();
  }
}

void CaptureManager::ready() {
  switch (unknown14) {
  case MODE_MOVIE:
    mm::mtl::Singleton<FadeManager>::getPtr()->play(false, 0, FadeCtrl::PRIO_LOW, nullptr);
    mm::mtl::Singleton<FadeManager>::getPtr()->setDisableFade(true);
    break;
  case MODE_DEVELOPER:
    mm::mtl::Singleton<FadeManager>::getPtr()->play(false, 0, FadeCtrl::PRIO_LOW, nullptr);
    mm::mtl::Singleton<FadeManager>::getPtr()->setDisableFade(true);
    break;
  case MODE_COMPOSER:
    mm::mtl::Singleton<FadeManager>::getPtr()->play(false, 0, FadeCtrl::PRIO_LOW, nullptr);
    mm::mtl::Singleton<FadeManager>::getPtr()->setDisableFade(true);
    break;
  case MODE_AFTEREFFECT:
    mm::mtl::Singleton<FadeManager>::getPtr()->play(false, 0, FadeCtrl::PRIO_LOW, nullptr);
    mm::mtl::Singleton<FadeManager>::getPtr()->setDisableFade(true);
    break;
  default:
    break;
  }
  if (unknown18 != 0) {
    mm::mtl::Singleton<EnvManager>::getPtr()->setColorFilter(EnvManager::COLORFILTER_TYPE_PLAY, unknown18, unknown18, 0.0f);
  }
}

void CaptureManager::stop() {
  MODE mode = unknown14;
  unknown10 &= ~FLAG_CAPTURE;
  switch (mode) {
  case MODE_MOVIE:
    mm::mtl::Singleton<FadeManager>::getPtr()->setDisableFade(false);
    break;
  case MODE_DEVELOPER:
    mm::mtl::Singleton<FadeManager>::getPtr()->setDisableFade(false);
    break;
  case MODE_COMPOSER:
    mm::mtl::Singleton<FadeManager>::getPtr()->setDisableFade(false);
    break;
  case MODE_AFTEREFFECT:
    mm::mtl::Singleton<FadeManager>::getPtr()->setDisableFade(false);
    break;
  default:
    break;
  }
  if (unknown18 != 0) {
    mm::mtl::Singleton<EnvManager>::getPtr()->setColorFilter(EnvManager::COLORFILTER_TYPE_STOP, -1, -1, 0.0f);
  }
}

void CaptureManager::render() {
  if ((unknown10 & (FLAG_RESERVE | FLAG_CAPTURE)) != FLAG_RESERVE) {
    return;
  }
  s32 height = ml::DevGraph::getRootHeight();
  s32 y = height - 100;
  s32 x = (ml::DevGraph::getRootWidth() >> 1) - 80;
  fw::debug::drawFontColor(mm::Col4::black);
  fw::debug::drawFont(x + 1, y + 1, "CAPTURE RESERVING..");
  fw::debug::drawFontColor(mm::Col4::yellow);
  fw::debug::drawFont(x, y, "CAPTURE RESERVING..");
  x = (ml::DevGraph::getRootWidth() >> 1) - 150;
  y = height - 75;
  mm::mtl::FixStr<64> filter = "";
  if (unknown18 != 0) {
    filter.format("(+filter%d)", unknown18);
  }
  switch (unknown14) {
  case MODE_MOVIE:
    fw::debug::drawFontColor(mm::Col4::black);
    fw::debug::drawFont(x + 1, y + 1, "      mode[movie mode] %s%s", filter.c_str(), (unknown10 & FLAG_MULTI) != 0 ? "(+multi)" : "");
    fw::debug::drawFontColor(mm::Col4::yellow);
    fw::debug::drawFont(x, y, "      mode[movie mode] %s%s", filter.c_str(), (unknown10 & FLAG_MULTI) != 0 ? "(+multi)" : "");
    break;
  case MODE_DEVELOPER:
    fw::debug::drawFontColor(mm::Col4::black);
    fw::debug::drawFont(x + 1, y + 1, "      mode[developer mode] %s%s", filter.c_str(), (unknown10 & FLAG_MULTI) != 0 ? "(+multi)" : "");
    fw::debug::drawFontColor(mm::Col4::yellow);
    fw::debug::drawFont(x, y, "      mode[developer mode] %s%s", filter.c_str(), (unknown10 & FLAG_MULTI) != 0 ? "(+multi)" : "");
    break;
  case MODE_COMPOSER:
    fw::debug::drawFontColor(mm::Col4::black);
    fw::debug::drawFont(x + 1, y + 1, "      mode[composer mode] %s%s", filter.c_str(), (unknown10 & FLAG_MULTI) != 0 ? "(+multi)" : "");
    fw::debug::drawFontColor(mm::Col4::yellow);
    fw::debug::drawFont(x, y, "      mode[composer mode] %s%s", filter.c_str(), (unknown10 & FLAG_MULTI) != 0 ? "(+multi)" : "");
    break;
  case MODE_AFTEREFFECT:
    fw::debug::drawFontColor(mm::Col4::black);
    fw::debug::drawFont(x + 1, y + 1, "      mode[aftereffect mode] %s", filter.c_str());
    fw::debug::drawFontColor(mm::Col4::yellow);
    fw::debug::drawFont(x, y, "      mode[aftereffect mode] %s", filter.c_str());
    break;
  case MODE_SOUND:
    fw::debug::drawFontColor(mm::Col4::black);
    fw::debug::drawFont(x + 1, y + 1, "      mode[sound mode] %s%s", filter.c_str(), (unknown10 & FLAG_MULTI) != 0 ? "(+multi)" : "");
    fw::debug::drawFontColor(mm::Col4::yellow);
    fw::debug::drawFont(x, y, "      mode[sound mode] %s%s", filter.c_str(), (unknown10 & FLAG_MULTI) != 0 ? "(+multi)" : "");
    break;
  case MODE_EFFECT:
    fw::debug::drawFontColor(mm::Col4::black);
    fw::debug::drawFont(x + 1, y + 1, "      mode[effect mode] %s", filter.c_str());
    fw::debug::drawFontColor(mm::Col4::yellow);
    fw::debug::drawFont(x, y, "      mode[effect mode] %s", filter.c_str());
    break;
  }
  y = height - 55;
  bool isMovie = !isJpegMode();
  fw::debug::drawFontColor(mm::Col4::black);
  if (isMovie) {
    fw::debug::drawFont(x + 1, y + 1, "movie path[%s]", MOV_PATH);
    fw::debug::drawFontColor(mm::Col4::yellow);
    fw::debug::drawFont(x, y, "movie path[%s]", MOV_PATH);
  } else {
    fw::debug::drawFont(x + 1, y + 1, " jpeg path[%s]", JPG_PATH);
    fw::debug::drawFontColor(mm::Col4::yellow);
    fw::debug::drawFont(x, y, " jpeg path[%s]", JPG_PATH);
  }
}

void CaptureManager::reserve(bool isReserve, MODE mode, bool isMulti) {
  if (isReserve) {
    unknown10 |= FLAG_RESERVE;
    if (isMulti) {
      unknown10 |= FLAG_MULTI;
    } else {
      unknown10 &= ~FLAG_MULTI;
    }
    unknown14 = mode;
  } else {
    unknown10 &= ~FLAG_RESERVE;
  }
}

void CaptureManager::reserveFilter(int filter) { unknown18 = filter; }

void CaptureManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    if ((unknown10 & FLAG_RESERVE) != 0) {
      ready();
    }
    break;
  case MSG_TYPE_START_PAGE:
    if ((unknown10 & (FLAG_RESERVE | FLAG_CAPTURE)) == FLAG_RESERVE) {
      start();
    }
    break;
  case MSG_TYPE_END_SCENE:
    if ((unknown10 & FLAG_CAPTURE) != 0) {
      stop();
    }
    break;
  case MSG_TYPE_CLEAR:
    clear();
    break;
  case MSG_TYPE_UPDATE:
    update();
    break;
  case MSG_TYPE_RENDER_POST:
    render();
    break;
  default:
    break;
  }
}

} // namespace event
