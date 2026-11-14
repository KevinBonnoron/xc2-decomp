#include "event/capture_manager.h"

#include <string.h>

#include "event/env_manager.h"
#include "event/fade_ctrl.h"
#include "event/fade_manager.h"
#include "event/frame_manager.h"
#include "event/manager.h"
#include "event/object_camera.h"
#include "event/object_manager.h"
#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"

namespace event {

const char *CaptureManager::MOV_PATH = "C:/MonolithSoft/BF2/movie";
const char *CaptureManager::MOV_PATH_OFS = "../../movie";
const char *CaptureManager::JPG_PATH = "C:/MonolithSoft/BF2/jpeg";
const char *CaptureManager::JPG_PATH_OFS = "../../jpeg";
const char *CaptureManager::CONV_PATH = "C:/Monolithsoft/BF2/execute/bf2tools/event/bmp2avi/bmp2avi";

CaptureManager::CaptureManager() : unknown10(0), unknown14(MODE_UNKNOWN_0), unknown18(0) {}

void CaptureManager::clear() {
  if ((unknown10 & FLAG_UNKNOWN_1) != 0) {
    stop();
  }
}

void CaptureManager::ready() {
  switch (unknown14) {
  case MODE_UNKNOWN_0:
    mm::mtl::Singleton<FadeManager>::getPtr()->play(false, 0, FadeCtrl::PRIO_LOW, nullptr);
    mm::mtl::Singleton<FadeManager>::getPtr()->setDisableFade(true);
    break;
  case MODE_UNKNOWN_1:
    mm::mtl::Singleton<FadeManager>::getPtr()->play(false, 0, FadeCtrl::PRIO_LOW, nullptr);
    mm::mtl::Singleton<FadeManager>::getPtr()->setDisableFade(true);
    break;
  case MODE_UNKNOWN_2:
    mm::mtl::Singleton<FadeManager>::getPtr()->play(false, 0, FadeCtrl::PRIO_LOW, nullptr);
    mm::mtl::Singleton<FadeManager>::getPtr()->setDisableFade(true);
    break;
  case MODE_UNKNOWN_3:
    mm::mtl::Singleton<FadeManager>::getPtr()->play(false, 0, FadeCtrl::PRIO_LOW, nullptr);
    mm::mtl::Singleton<FadeManager>::getPtr()->setDisableFade(true);
    break;
  default:
    break;
  }
  if (unknown18 != 0) {
    mm::mtl::Singleton<EnvManager>::getPtr()->setColorFilter(EnvManager::COLORFILTER_TYPE_UNKNOWN_1, unknown18, unknown18, 0.0f);
  }
}

void CaptureManager::stop() {
  MODE mode = unknown14;
  unknown10 &= ~FLAG_UNKNOWN_1;
  switch (mode) {
  case MODE_UNKNOWN_0:
    mm::mtl::Singleton<FadeManager>::getPtr()->setDisableFade(false);
    break;
  case MODE_UNKNOWN_1:
    mm::mtl::Singleton<FadeManager>::getPtr()->setDisableFade(false);
    break;
  case MODE_UNKNOWN_2:
    mm::mtl::Singleton<FadeManager>::getPtr()->setDisableFade(false);
    break;
  case MODE_UNKNOWN_3:
    mm::mtl::Singleton<FadeManager>::getPtr()->setDisableFade(false);
    break;
  default:
    break;
  }
  if (unknown18 != 0) {
    mm::mtl::Singleton<EnvManager>::getPtr()->setColorFilter(EnvManager::COLORFILTER_TYPE_UNKNOWN_0, -1, -1, 0.0f);
  }
}

void CaptureManager::update() {
  if ((unknown10 & FLAG_UNKNOWN_1) == 0) {
    return;
  }
  if (mm::mtl::Singleton<FrameManager>::getPtr()->isPause(FrameManager::PAUSE_TYPE_UNKNOWN_17_2)) {
    return;
  }
  if (unknown1c > 0) {
    mm::mtl::FixStr<128> path;
    const char *sceneName = Manager::get()->getSceneName();
    if (!isJpegMode()) {
      path.format("%s/%s/%s_%08d", MOV_PATH_OFS, sceneName, sceneName, unknown1c);
    } else {
      path.format("%s/%s/%s_%08d", JPG_PATH_OFS, sceneName, sceneName, unknown1c);
    }
    mm::mtl::FixStr<16> cutName = "_cxx";
    if (mm::mtl::Singleton<ObjectManager>::getPtr()->getCameraCount() != 0) {
      const char *name = strstr(mm::mtl::Singleton<ObjectManager>::getPtr()->getCamera(0)->getCutName(), "_c");
      if (name != nullptr) {
        cutName = name;
      }
    }
    if (unknown20.empty() || strcmp(unknown20.back().c_str(), cutName.c_str()) != 0) {
      unknown20.push_back(cutName);
    }
  }
  unknown1c++;
}

void CaptureManager::render() {
  if ((unknown10 & (FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1)) != FLAG_UNKNOWN_0) {
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
  case MODE_UNKNOWN_0:
    fw::debug::drawFontColor(mm::Col4::black);
    fw::debug::drawFont(x + 1, y + 1, "      mode[movie mode] %s%s", filter.c_str(), (unknown10 & FLAG_UNKNOWN_2) != 0 ? "(+multi)" : "");
    fw::debug::drawFontColor(mm::Col4::yellow);
    fw::debug::drawFont(x, y, "      mode[movie mode] %s%s", filter.c_str(), (unknown10 & FLAG_UNKNOWN_2) != 0 ? "(+multi)" : "");
    break;
  case MODE_UNKNOWN_1:
    fw::debug::drawFontColor(mm::Col4::black);
    fw::debug::drawFont(x + 1, y + 1, "      mode[developer mode] %s%s", filter.c_str(), (unknown10 & FLAG_UNKNOWN_2) != 0 ? "(+multi)" : "");
    fw::debug::drawFontColor(mm::Col4::yellow);
    fw::debug::drawFont(x, y, "      mode[developer mode] %s%s", filter.c_str(), (unknown10 & FLAG_UNKNOWN_2) != 0 ? "(+multi)" : "");
    break;
  case MODE_UNKNOWN_2:
    fw::debug::drawFontColor(mm::Col4::black);
    fw::debug::drawFont(x + 1, y + 1, "      mode[composer mode] %s%s", filter.c_str(), (unknown10 & FLAG_UNKNOWN_2) != 0 ? "(+multi)" : "");
    fw::debug::drawFontColor(mm::Col4::yellow);
    fw::debug::drawFont(x, y, "      mode[composer mode] %s%s", filter.c_str(), (unknown10 & FLAG_UNKNOWN_2) != 0 ? "(+multi)" : "");
    break;
  case MODE_UNKNOWN_3:
    fw::debug::drawFontColor(mm::Col4::black);
    fw::debug::drawFont(x + 1, y + 1, "      mode[aftereffect mode] %s", filter.c_str());
    fw::debug::drawFontColor(mm::Col4::yellow);
    fw::debug::drawFont(x, y, "      mode[aftereffect mode] %s", filter.c_str());
    break;
  case MODE_UNKNOWN_4:
    fw::debug::drawFontColor(mm::Col4::black);
    fw::debug::drawFont(x + 1, y + 1, "      mode[sound mode] %s%s", filter.c_str(), (unknown10 & FLAG_UNKNOWN_2) != 0 ? "(+multi)" : "");
    fw::debug::drawFontColor(mm::Col4::yellow);
    fw::debug::drawFont(x, y, "      mode[sound mode] %s%s", filter.c_str(), (unknown10 & FLAG_UNKNOWN_2) != 0 ? "(+multi)" : "");
    break;
  case MODE_UNKNOWN_5:
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
    unknown10 |= FLAG_UNKNOWN_0;
    if (isMulti) {
      unknown10 |= FLAG_UNKNOWN_2;
    } else {
      unknown10 &= ~FLAG_UNKNOWN_2;
    }
    unknown14 = mode;
  } else {
    unknown10 &= ~FLAG_UNKNOWN_0;
  }
}

void CaptureManager::reserveFilter(int filter) { unknown18 = filter; }

void CaptureManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_4:
    if ((unknown10 & FLAG_UNKNOWN_0) != 0) {
      ready();
    }
    break;
  case MSG_TYPE_UNKNOWN_8:
    if ((unknown10 & (FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1)) == FLAG_UNKNOWN_0) {
      start();
    }
    break;
  case MSG_TYPE_UNKNOWN_10:
    if ((unknown10 & FLAG_UNKNOWN_1) != 0) {
      stop();
    }
    break;
  case MSG_TYPE_UNKNOWN_12:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_14:
    update();
    break;
  case MSG_TYPE_UNKNOWN_17:
    render();
    break;
  default:
    break;
  }
}

} // namespace event
