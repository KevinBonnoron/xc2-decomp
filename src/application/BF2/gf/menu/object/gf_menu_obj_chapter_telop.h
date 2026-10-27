#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjChapterTelop : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  static void openBeginTelop(GfMenuCallContext *context, int chapter);
  static void openEndTelop(GfMenuCallContext *context, int chapter);
  static void openAvanTitle(GfMenuCallContext *context, int title);
  static void close(u16 title);
};

} // namespace gf
