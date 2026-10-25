#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/object/ui_screen_object.h"

namespace gf {

class GfMenuObjMovieLayer : public GfMenuObject {
public:
  GfMenuObjMovieLayer(u32 handle);
  ~GfMenuObjMovieLayer() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static u32 getMovieLayerObject();
  static u32 createMovieLayer(u32 width, u32 height, const ui::UIScreenObject::OnMemoryInfo &info);

  static u32 m_CreatedCount;
};

} // namespace gf
