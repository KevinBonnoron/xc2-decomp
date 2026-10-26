#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjCommonDetail : public GfMenuObject {
public:
  GfMenuObjCommonDetail(u32 handle);
  ~GfMenuObjCommonDetail() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void close(GfMenuCallContext *context);
};

} // namespace gf
