#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjBladeSet : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void update() override;
  struct OpenParam;
  static void registOpenParam(const OpenParam &);
};

} // namespace gf
