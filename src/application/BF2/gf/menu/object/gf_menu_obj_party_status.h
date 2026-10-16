#pragma once

namespace gf {

class GfMenuCallContext;

class GfMenuObjPartyStatus {
public:
  static void lock(bool lock);
  static void attachComboRequest(GfMenuCallContext *context);
};

} // namespace gf
