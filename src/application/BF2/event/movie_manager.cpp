#include "event/movie_manager.h"

#include "event/manager.h"
#include "gf/movie/gf_movie_manager.h"
#include "scn/scn.h"
#include "scn/scn_render_dr_sys_parm_acc.h"

namespace event {

constexpr int CLOSE_WAIT_FRAMES = 2;

MovieManager::MovieManager() : flags(0), mIsPreloadFullSize(false), mUnused(-1) {}

void MovieManager::close() {
  stop();
  if (flags & FLAG_OPEN) {
    gf::GfMovieManager::get()->stop();
    gf::GfMovieManager::get()->close();
    flags &= ~(FLAG_OPEN | FLAG_CLOSE_WAIT);
  }
}

void MovieManager::captureScreen(bool isCapture) {
  if (isCapture) {
    if (!(flags & FLAG_CAPTURE)) {
      ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->renderDrSys, 0);
      parmAcc.setCaptureMode(true);
      flags |= FLAG_CAPTURE;
    }
  } else if (flags & FLAG_CAPTURE) {
    ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->renderDrSys, 0);
    parmAcc.setCaptureMode(false);
    flags &= ~FLAG_CAPTURE;
  }
}

void MovieManager::update() {
  if ((flags & (FLAG_PLAY | FLAG_AUTO_STOP)) == (FLAG_PLAY | FLAG_AUTO_STOP) && !gf::GfMovieManager::get()->isplaying()) {
    stop();
  }
  if (flags & FLAG_DISP_WAIT) {
    if (mDispTimer-- <= 0) {
      flags &= ~FLAG_DISP_WAIT;
    }
  }
  if (flags & FLAG_CLOSE_WAIT) {
    if (mCloseTimer-- <= 0) {
      close();
    }
  }
}

void MovieManager::stop() {
  if (flags & (FLAG_LOADED | FLAG_PLAY)) {
    if (flags & FLAG_DISP_REQUEST) {
      flags &= ~(FLAG_DISP_REQUEST | FLAG_DISP_WAIT);
    }
    mCloseTimer = CLOSE_WAIT_FRAMES;
    flags = (flags & ~(FLAG_LOADED | FLAG_PLAY | FLAG_DISP_WAIT | FLAG_CLOSE_WAIT)) | FLAG_CLOSE_WAIT;
  }
}

void MovieManager::dispOff() { flags &= ~FLAG_DISP_WAIT; }

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
  if ((flags & FLAG_LOADED) && !gf::GfMovieManager::get()->isstandby()) {
    return true;
  }
  return false;
}

void MovieManager::playAuto(const char *name, bool isFullSize, bool isAutoStop) {
  mm::mtl::FixStr<256> path;
  makePath(path, name);
  play(path.c_str(), isFullSize, isAutoStop);
}

void MovieManager::dispOn() { flags &= ~FLAG_DISP_WAIT; }

void MovieManager::setScriptFlag(bool isScript) {
  if (isScript) {
    flags |= FLAG_SCRIPT;
  } else {
    flags &= ~FLAG_SCRIPT;
  }
}

bool MovieManager::isLoadedAuto(const char *name, bool isFullSize) const {
  mm::mtl::FixStr<256> path;
  makePath(path, name);
  return isLoaded(path.c_str(), isFullSize);
}

bool MovieManager::isLoaded(const char *path, bool isFullSize) const {
  if ((flags & FLAG_LOADED) && __builtin_strcmp(mPreloadPath.c_str(), path) == 0 && mIsPreloadFullSize == isFullSize) {
    return gf::GfMovieManager::get()->isstandby();
  }
  return false;
}

void MovieManager::pause(bool isPause) {
  if (flags & FLAG_PLAY) {
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
