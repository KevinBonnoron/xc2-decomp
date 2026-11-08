#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjSpecialGauge : public GfMenuObject {
public:
  GfMenuObjSpecialGauge(u32 handle);
  ~GfMenuObjSpecialGauge() override;
  static void close();
  static void open();
  static void reverse(bool isReverse);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void push();
};

} // namespace gf
