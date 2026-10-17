#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjButtonChallenge : public GfMenuObject {
public:
  GfMenuObjButtonChallenge(u32 handle);
  ~GfMenuObjButtonChallenge() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf
