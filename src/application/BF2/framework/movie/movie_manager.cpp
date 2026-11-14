#include "framework/movie/movie_manager.h"

#include "framework/memory/framework_memory.h"
#include "layer/layer_acc_manager.h"
#include "layer/layer_acc_mem_obj.h"
#include "layer/layer_base.h"
#include "layer/layer_obj_manager.h"
#include "libs/movie/cmovie_nx.h"
#include "ml/scn.h"
#include "movie/cmovie.h"
#include "scn/scn_render_dr_sys_parm_acc.h"
#include "ui/ui_object.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

// The class MovieManager::open creates (vtable _ZTV6CMovie, destructor _ZN6CMovieD0Ev next to MovieManager): it overrides nothing of the
// platform movie class.
class CMovie : public CMovieNX::CMovie {};

namespace fw {

const char *MovieManager::getName() const { return "MovieManager"; }

void MovieManager::open(mm::mtl::IAllocator *allocator, u32 layer) {
  if (unknown30 != nullptr) {
    close();
  }
  unknown20 = layer;
// __LINE__ is the line argument of the operator new call.
#line 33
  unknown30 = new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) CMovie;
  unknown30->initialize(FrameworkMemory::getAllocator(9));
  if (unknown20 != 0) {
    ui::UIObjectAcc acc(unknown20);
    if (acc.isValid()) {
      unknown3c = acc.getOnMemoryPixelSize();
      acc.setDisp(false);
    }
  }
}

void MovieManager::close() {
  stop();
  if (unknown30 != nullptr) {
    unknown30->finalize();
    delete unknown30;
    unknown30 = nullptr;
  }
  if (unknown28 != nullptr) {
    ml::ScnRenderDrSysParmAcc parm(ml::Scn::get()->unknown38, 0);
    parm.resetModelTexture(0);
    parm.resetModelTexture(1);
    if (unknown20 == 0) {
      if (unknown28 != nullptr) {
        unknown28->release();
      }
      unknown20 = 0;
    }
    unknown28 = nullptr;
  }
  if (unknown20 != 0) {
    ui::UIObjectAcc acc(unknown20);
    if (acc.isValid()) {
      acc.setTerm();
    }
    unknown20 = 0;
  }
}

void MovieManager::open(mm::mtl::IAllocator *allocator, int width, int height, u32 layer) {
  if (unknown30 != nullptr) {
    close();
  }
  layer::LayerAccManager manager;
  unknown20 = layer;
  layer::LayerBase *layerBase;
  if (layer == 0) {
    layerBase = manager.createMemObj(width, height, static_cast<layer::LayerMemType>(3));
    unknown3c = 1;
  } else {
    ui::UIObjectAcc acc(layer);
    unknown3c = acc.getOnMemoryPixelSize();
    layerBase = ui::UIUtil::getObject(acc.unknown10)->unknownc8;
  }
  unknown28 = layerBase;
  layer::LayerAccMemObj memAcc(layerBase);
  if (layer == 0) {
    memAcc.setRender(false);
  }
  grlib::CGLibTextureBuffer *buffer = memAcc.getTexture();
  ml::ScnRenderDrSysParmAcc parm(ml::Scn::get()->unknown38, 0);
  ml::ScnRenderDrMdlTexture texture;
  texture.unknown00 = buffer;
  texture.unknown08 = 0;
  texture.unknown0c = true;
  parm.setModelTexture(texture);
// __LINE__ is the line argument of the operator new call.
#line 104
  unknown30 = new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) CMovie;
  unknown30->initialize(FrameworkMemory::getAllocator(9));
}

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
