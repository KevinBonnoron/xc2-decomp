#pragma once
#include "mm_mtl/singleton.h"

namespace gf {

class GfMovieManager : public mm::mtl::PtrSingleton<GfMovieManager> {
public:
  void close();
  void play();
  void pause();
  void stop();
  bool isstandby();
  bool ispause();
  bool isplaying();
};

} // namespace gf
