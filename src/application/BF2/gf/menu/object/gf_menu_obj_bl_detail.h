#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjBlDetail : public GfMenuObject {
public:
  GfMenuObjBlDetail(u32 handle);
  ~GfMenuObjBlDetail() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void open(GfMenuCallContext *context);
  static void close(GfMenuCallContext *context, bool flag);
  static void nextPage(GfMenuCallContext *context);
  static void prevPage(GfMenuCallContext *context);
  static void disp(GfMenuCallContext *context, bool flag);
};

} // namespace gf
