#include "framework/movie/movie_manager.h"

#include "movie/cmovie.h"

namespace fw {

void MovieManager::stop() {
  if (movie != nullptr) {
    movie->stop();
    isPlaying = false;
  }
}

f32 MovieManager::get_length() {
  if (movie == nullptr) {
    return 0.0f;
  }

  return movie->get_length();
}

f32 MovieManager::pos() {
  if (movie == nullptr) {
    return 0.0f;
  }

  return movie->pos();
}

void MovieManager::play() {
  if (movie != nullptr) {
    movie->play();
    if (movie->isplaying()) {
      isPlaying = true;
    }
  }
}

void MovieManager::pause() {
  if (movie != nullptr) {
    movie->pause();
  }
}

bool MovieManager::isstandby() {
  if (movie == nullptr) {
    return false;
  }

  return movie->isstandby();
}

bool MovieManager::ispause() {
  if (movie == nullptr) {
    return false;
  }

  return movie->ispause();
}

bool MovieManager::isplaying() {
  if (movie == nullptr) {
    return false;
  }

  return movie->isplaying();
}

void MovieManager::bkgHomeMenu(bool isEnter) {
  if (movie != nullptr) {
    movie->doHomeMenu(true);
    if (!isEnter) {
      movie->doHomeMenu(false);
    }
  }
}

} // namespace fw
