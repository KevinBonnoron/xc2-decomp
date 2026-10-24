#include "framework/movie/movie_manager.h"

#include "movie/cmovie.h"

namespace fw {

void MovieManager::stop() {
  if (unknown30 != nullptr) {
    unknown30->stop();
    unknown38 = false;
  }
}

f32 MovieManager::get_length() {
  if (unknown30 == nullptr) {
    return 0.0f;
  }

  return unknown30->get_length();
}

f32 MovieManager::pos() {
  if (unknown30 == nullptr) {
    return 0.0f;
  }

  return unknown30->pos();
}

void MovieManager::play() {
  if (unknown30 != nullptr) {
    unknown30->play();
    if (unknown30->isplaying()) {
      unknown38 = true;
    }
  }
}

void MovieManager::pause() {
  if (unknown30 != nullptr) {
    unknown30->pause();
  }
}

bool MovieManager::isstandby() {
  if (unknown30 == nullptr) {
    return false;
  }

  return unknown30->isstandby();
}

bool MovieManager::ispause() {
  if (unknown30 == nullptr) {
    return false;
  }

  return unknown30->ispause();
}

bool MovieManager::isplaying() {
  if (unknown30 == nullptr) {
    return false;
  }

  return unknown30->isplaying();
}

void MovieManager::bkgHomeMenu(bool isEnter) {
  if (unknown30 != nullptr) {
    unknown30->doHomeMenu(true);
    if (!isEnter) {
      unknown30->doHomeMenu(false);
    }
  }
}

} // namespace fw
