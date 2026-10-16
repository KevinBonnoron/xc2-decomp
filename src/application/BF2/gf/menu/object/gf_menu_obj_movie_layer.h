#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjMovieLayer : public GfMenuObject {
public:
  GfMenuObjMovieLayer(u32 handle);
  ~GfMenuObjMovieLayer() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static u32 getMovieLayerObject();
};

} // namespace gf
