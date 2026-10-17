#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjIdeaGram : public GfMenuObject {
public:
  GfMenuObjIdeaGram(u32 handle);
  ~GfMenuObjIdeaGram() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf
