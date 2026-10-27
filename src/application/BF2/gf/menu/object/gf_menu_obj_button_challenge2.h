#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjButtonChallenge2 : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  static void open(GfMenuCallContext *context, unsigned int challenge, bool isDispButton, bool isSound);
  static void openSequence(GfMenuCallContext *context, unsigned int challenge, bool isDispButton, bool isSound);
  static void resume(GfMenuCallContext *context);
  static void close(GfMenuCallContext *context);
};

} // namespace gf
