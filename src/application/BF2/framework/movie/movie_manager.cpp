#include "framework/movie/movie_manager.h"

#include "layer/layer_acc_mem_obj.h"
#include "movie/cmovie.h"
#include "ui/ui_object_acc.h"

namespace fw {

const char *MovieManager::getName() const { return "MovieManager"; }

void MovieManager::update() {
  unknown40++;
  if (unknown30 != nullptr) {
    if (unknown28 == nullptr) {
      if (unknown20 != 0) {
        ui::UIObjectAcc acc(unknown20);
        if (acc.isValid()) {
          acc.setDisp(unknown38);
          s16 width;
          s16 height;
          acc.getSize(false, width, height);
          void *buffer = acc.getOnMemoryBuffer();
          unknown30->update(static_cast<u8 *>(buffer), width, height, unknown3c);
          acc.swapOnMemoryBuffer();
        }
      }
    } else {
      layer::LayerAccMemObj acc(unknown28);
      void *buffer = acc.getMemBufer();
      u32 width = acc.getMemWidth();
      u32 height = acc.getMemHeight();
      unknown30->update(static_cast<u8 *>(buffer), width, height, unknown3c);
      acc.updateMemBufer();
    }
  }
}

bool MovieManager::set_file(const char *path) {
  if (unknown30 != nullptr) {
    if (unknown30->set_file(path) == 0) {
      return true;
    }
  }

  return false;
}

void MovieManager::stop() {
  if (unknown30 != nullptr) {
    unknown30->stop();
  }
  unknown38 = false;
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

template mm::mtl::PtrSingleton<fw::MovieManager>::~PtrSingleton();
// The game emits it here, next to the inline CMovie destructor: ICMovie has no source file of its own.
template mm::mtl::PtrSingleton<ICMovie>::~PtrSingleton();
