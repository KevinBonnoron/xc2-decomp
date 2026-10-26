#include "event/movie_manager.h"

#include "event/extend.h"
#include "event/manager.h"
#include "event/skip_manager.h"
#include "gf/gf_allocator.h"
#include "gf/movie/gf_movie_manager.h"
#include "ml/scn.h"
#include "scn/scn_render_dr_sys_parm_acc.h"

namespace event {

constexpr int CLOSE_WAIT_FRAMES = 2;

MovieManager::MovieManager() : unknown10(0), unknown118(false), unknown220(-1) {}

void MovieManager::close() {
  stop();
  if (unknown10 & FLAG_OPEN) {
    gf::GfMovieManager::get()->stop();
    gf::GfMovieManager::get()->close();
    unknown10 &= ~(FLAG_OPEN | FLAG_CLOSE_WAIT);
  }
}

void MovieManager::captureScreen(bool isCapture) {
  if (isCapture) {
    if (!(unknown10 & FLAG_CAPTURE)) {
      ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->unknown38, 0);
      parmAcc.setCaptureMode(true);
      unknown10 |= FLAG_CAPTURE;
    }
  } else if (unknown10 & FLAG_CAPTURE) {
    ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->unknown38, 0);
    parmAcc.setCaptureMode(false);
    unknown10 &= ~FLAG_CAPTURE;
  }
}

void MovieManager::update() {
  if ((unknown10 & (FLAG_PLAY | FLAG_AUTO_STOP)) == (FLAG_PLAY | FLAG_AUTO_STOP) && !gf::GfMovieManager::get()->isplaying()) {
    stop();
  }
  if (unknown10 & FLAG_DISP_WAIT) {
    if (unknown228-- <= 0) {
      unknown10 &= ~FLAG_DISP_WAIT;
    }
  }
  if (unknown10 & FLAG_CLOSE_WAIT) {
    if (unknown22c-- <= 0) {
      close();
    }
  }
}

void MovieManager::play(const char *path, bool isFullSize, bool isAutoStop) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    clear();
    return;
  }
  if (!(unknown10 & FLAG_LOADED) || !isSame(unknown14.c_str(), path) || unknown118 != isFullSize) {
    gf::GfMovieManager::get()->stop();
    gf::GfMovieManager::get()->close();
    gf::GfMovieManager *movie = gf::GfMovieManager::get();
    gf::GfAllocator *allocator = gf::getAllocator(gf::ALLOCATOR_DEBUG);
    if (isFullSize) {
      movie->open(allocator, 1280, 720);
    } else {
      movie->open(allocator);
    }
    if (!gf::GfMovieManager::get()->set_file(mm::mtl::Singleton<Extend>::getPtr()->webm(path))) {
      gf::GfMovieManager::get()->close();
      return;
    }
    gf::GfMovieManager::get()->play();
    unknown11c = path;
  } else {
    gf::GfMovieManager::get()->play();
    unknown11c = path;
    unknown10 &= ~FLAG_LOADED;
    unknown14 = "";
    unknown118 = false;
  }
  unknown10 |= FLAG_OPEN | FLAG_PLAY;
  if (isAutoStop) {
    unknown10 |= FLAG_AUTO_STOP;
  } else {
    unknown10 &= ~FLAG_AUTO_STOP;
  }
  unknown10 &= ~(FLAG_DISP_WAIT | FLAG_CLOSE_WAIT);
  if (!isFullSize) {
    unknown228 = 1;
    unknown10 |= FLAG_DISP_REQUEST | FLAG_DISP_WAIT;
  }
}

void MovieManager::stop() {
  if (unknown10 & (FLAG_LOADED | FLAG_PLAY)) {
    if (unknown10 & FLAG_DISP_REQUEST) {
      unknown10 &= ~(FLAG_DISP_REQUEST | FLAG_DISP_WAIT);
    }
    unknown22c = CLOSE_WAIT_FRAMES;
    unknown10 = (unknown10 & ~(FLAG_LOADED | FLAG_PLAY | FLAG_DISP_WAIT | FLAG_CLOSE_WAIT)) | FLAG_CLOSE_WAIT;
  }
}

void MovieManager::dispOff() { unknown10 &= ~FLAG_DISP_WAIT; }

void MovieManager::preloadAuto(const char *name, bool isFullSize) {
  mm::mtl::FixStr<256> path;
  makePath(path, name);
  preload(path.c_str(), isFullSize);
}

bool MovieManager::isSame(const char *path, const char *otherPath) {
  mm::mtl::FixStr<256> rootedPath;
  if (path[0] != '\0' && path[0] != '/') {
    rootedPath = "/";
    rootedPath += path;
    path = rootedPath.c_str();
  }
  mm::mtl::FixStr<256> rootedOtherPath;
  if (otherPath[0] != '\0' && otherPath[0] != '/') {
    rootedOtherPath = "/";
    rootedOtherPath += otherPath;
    otherPath = rootedOtherPath.c_str();
  }
  return __builtin_strcmp(path, otherPath) == 0;
}

bool MovieManager::isLoading() const {
  if ((unknown10 & FLAG_LOADED) && !gf::GfMovieManager::get()->isstandby()) {
    return true;
  }
  return false;
}

void MovieManager::playAuto(const char *name, bool isFullSize, bool isAutoStop) {
  mm::mtl::FixStr<256> path;
  makePath(path, name);
  play(path.c_str(), isFullSize, isAutoStop);
}

void MovieManager::dispOn() { unknown10 &= ~FLAG_DISP_WAIT; }

void MovieManager::setScriptFlag(bool isScript) {
  if (isScript) {
    unknown10 |= FLAG_SCRIPT;
  } else {
    unknown10 &= ~FLAG_SCRIPT;
  }
}

bool MovieManager::isLoadedAuto(const char *name, bool isFullSize) const {
  mm::mtl::FixStr<256> path;
  makePath(path, name);
  return isLoaded(path.c_str(), isFullSize);
}

bool MovieManager::isLoaded(const char *path, bool isFullSize) const {
  if ((unknown10 & FLAG_LOADED) && __builtin_strcmp(unknown14.c_str(), path) == 0 && unknown118 == isFullSize) {
    return gf::GfMovieManager::get()->isstandby();
  }
  return false;
}

void MovieManager::pause(bool isPause) {
  if (unknown10 & FLAG_PLAY) {
    bool isPaused = gf::GfMovieManager::get()->ispause();
    if (isPause) {
      if (!isPaused) {
        gf::GfMovieManager::get()->pause();
      }
    } else if (isPaused) {
      gf::GfMovieManager::get()->play();
    }
  }
}

void MovieManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    clear();
    break;
  case MSG_TYPE_UPDATE_POST:
    update();
    break;
  case MSG_TYPE_RENDER_POST:
    render();
    break;
  default:
    break;
  }
  if (type == MSG_TYPE_CLEAR) {
    clear();
  }
}

} // namespace event
