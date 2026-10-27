#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjSalvage : public GfMenuObject {
public:
  bool seqResultEnd();
  void initialize() override;
  void finalize() override;
};

} // namespace gf
